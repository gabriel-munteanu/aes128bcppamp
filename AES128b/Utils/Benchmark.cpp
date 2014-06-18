#include <fstream>
#include "Benchmark.h"
#include "..\AES128AMP.h"
#include "..\AES128CPU.h"
#include "..\Tests\AESTest.h"

std::vector<unsigned long> Benchmark::_memTestValues;

void Benchmark::GenerateTestValues() {
	unsigned long value = 1024U;
	const unsigned long _128mb = value << 17;

	_memTestValues.clear();

	//this will add powers of 2 starting from 1KB until it reach 64MB
	for (int i = 0; i < 10 + 7; i++, value *= 2)
		if (i % 2 == 0)
			_memTestValues.push_back(value);
	//TODO: remove the return, just for testing purpose
	return;
	// add from 128MB to 1GB with 128MB step
	for (int i = 0; i < 8; i++, value += _128mb)
		_memTestValues.push_back(value);

}

//this will return time difference in miliseconds
//TODO: move this method to Windows Helpers
double Benchmark::ElapsedTime(const __int64 &start, const __int64 &end) {
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	return (double(end) - double(start)) * 1000.0 / double(freq.QuadPart);
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
		memset(data, 0, _memTestValues[testIndex]);

		for (unsigned int puIndex = 0; puIndex < pusInfo.size(); puIndex++) {
			LARGE_INTEGER tStart, tEnd;
			pusInfo[puIndex].implementation->SetKey(std::string((const char*)key));
			pusInfo[puIndex].implementation->SetData(data, _memTestValues[testIndex]);

			//TODO: Create Windows Helpers method using below method of getting the current 'time'. We should make thing portable 
			QueryPerformanceCounter(&tStart);
			pusInfo[puIndex].implementation->Encrypt(pusInfo[puIndex].processingUnitId);
			QueryPerformanceCounter(&tEnd);

			pusTimings[puIndex].push_back(ElapsedTime(tStart.QuadPart, tEnd.QuadPart));

			//when we are testing with 128MB or higher we take a break because, for PU like CPU, the temperature 
			//can increase dramatically
			if (_memTestValues[testIndex] >= (1024U << 17))
				Sleep(10 * 1000);
		}

		delete data;
	}

	ExportHardBenchmarkData(pusInfo, pusTimings);
}

void Benchmark::ExportHardBenchmarkData(std::vector<ProcessingUnitInfo> pusInfo, std::vector<std::vector<double>> timings) {
	std::ofstream fout;

	fout.open("HardBenchmarkResults.csv");

	for (unsigned int puIndex = 0; puIndex < pusInfo.size(); puIndex++) {
		auto pu = pusInfo[puIndex];

		fout << pu.name << ";" << pu.isGPU << ";" << pu.availableMemory / 1024 << ";\r\n";//display availabelMemory in MB
		for (auto time : timings[puIndex])
			fout << time / 1000 << ";";//display elapsed time in seconds
		fout << "\r\n";
	}

	fout.close();
}
