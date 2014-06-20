#include <fstream>
#include <iostream>
#include "Benchmark.h"
#include "..\AES128AMP.h"
#include "..\AES128CPU.h"
#include "..\Tests\AESTest.h"
#include "..\Helpers\WindowsHelpers.h"

std::vector<unsigned long> Benchmark::_memTestValues;

void Benchmark::GenerateTestValues() {
	unsigned long value = 1024U;
	const unsigned long _128mb = value << 17;

	_memTestValues.clear();

	//we add this dummy value first because some PU, like GPU, will run very slowly the first time,
	//so TAKE CARE, the first value from each result set is a dummy one!!!!!!!!!!
	_memTestValues.push_back(value);
	//this will add powers of 2 starting from 1KB until it reach 64MB
	for (int i = 0; i < 10 + 7; i++, value *= 2)
		if (i % 2 == 0)
			_memTestValues.push_back(value);
	//TODO: remove the return, just for testing purpose
	//return;	
	// add from 128MB to 1GB with 128MB step
	for (int i = 0; i < 8; i++, value += _128mb)
		_memTestValues.push_back(value);

}


void Benchmark::HardPerformanceTest() {
	GenerateTestValues();

	AES128Base *implementations[] = { new AES128AMP(), new AES128CPU() };
	int implementationsCount = sizeof(implementations) / sizeof(implementations[0]);

	std::vector<ProcessingUnitInfo> pusInfo;
	std::vector<std::vector<double>> pusTimings;// each PU have a vector with timings


	for (int i = 0; i < implementationsCount; i++) {
		auto implPus = implementations[i]->GetAvailableProcessingUnits();
		pusInfo.insert(pusInfo.end(), implPus.begin(), implPus.end());
	}

	//add all necessary vectors
	for (unsigned int i = 0; i < pusInfo.size(); i++)
		pusTimings.push_back(std::vector<double>());


	unsigned char key[17] = { 1 }; key[16] = 0;

	//for each test run all PUs, this way we don't stress to much one PU at once
	for (unsigned int testIndex = 0; testIndex < _memTestValues.size(); testIndex++) {
		unsigned char *data = new unsigned char[_memTestValues[testIndex]];
		std::cout << "# " << _memTestValues[testIndex] / 1024 / 1024 << "MB\n";

		for (unsigned int puIndex = 0; puIndex < pusInfo.size(); puIndex++) {
			LARGE_INTEGER tStart, tEnd;
			memset(data, 0, _memTestValues[testIndex]);
			pusInfo[puIndex].implementation->SetKey(std::string((const char*)key));
			pusInfo[puIndex].implementation->SetData(data, _memTestValues[testIndex]);
			std::cout << pusInfo[puIndex].name << "\n";

			//TODO: Create Windows Helpers method using below method of getting the current 'time'. We should make this thing portable 
			QueryPerformanceCounter(&tStart);
			pusInfo[puIndex].implementation->Encrypt(pusInfo[puIndex].processingUnitId);
			QueryPerformanceCounter(&tEnd);

			pusTimings[puIndex].push_back(Helper::ElapsedTime(tStart.QuadPart, tEnd.QuadPart));

			//when we are testing with 128MB or higher we take a break because, for PU like CPU, the temperature 
			//can increase dramatically
			//if (_memTestValues[testIndex] >= (1024U << 17))
			//	Sleep(3 * 1000);
		}

		delete[] data;
	}

	for (int i = 0; i < implementationsCount; i++)
		delete implementations[i];

	ExportHardBenchmarkData(pusInfo, pusTimings);
	std::cout << "HardPerformanceTest finished.\r\n";
}

void Benchmark::ExportHardBenchmarkData(std::vector<ProcessingUnitInfo> pusInfo, std::vector<std::vector<double>> timings) {
	std::ofstream fout;
	time_t rawtime;
	tm timeinfo;
	char filename[100];

	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);

	strftime(filename, 100, "HardBenchmarkResults-%Y-%m-%d_%H-%M-%S.csv", &timeinfo);//2001-08-29_23-50-15

	fout.open(filename);

	//the first line will contain the memory values used for tests
	fout << ",,,";//this is an 'empty PU description'
	for (auto memValue : _memTestValues) {
		if (memValue < 2 << 19)//if memValue unde 1MB then write KB, else MB
			fout << memValue / 1024 << "KB, ";
		else
			fout << memValue / 1024 / 1024 << "MB, ";
	}
	fout << "\n";

	for (unsigned int puIndex = 0; puIndex < pusInfo.size(); puIndex++) {
		auto pu = pusInfo[puIndex];

		fout << pu.name << "," << pu.isGPU << "," << pu.availableMemory / 1024 << ",";//display availabelMemory in MB
		for (auto time : timings[puIndex])
			fout << time / 1000 << ",";//display elapsed time in seconds
		fout << "\n";

		if (pu.isGPU) {
			fout << "Kernel Execution Time,,,";
			for (auto time : ((AES128AMP*)pu.implementation)->EncryptionKernelTimings[pu.processingUnitId])
				fout << time / 1000 << ",";//display elapsed time in seconds
			fout << "\n";
		}
	}

	fout.close();
}
