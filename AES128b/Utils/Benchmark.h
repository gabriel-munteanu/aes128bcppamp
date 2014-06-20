#pragma once
#include <vector>
#include "..\AES128Base.h"

class Benchmark {

private:
	static std::vector<unsigned long> _memTestValues;
	static void ExportHardBenchmarkData(std::vector<ProcessingUnitInfo>, std::vector<std::vector<double>>);

public:
	static void GenerateTestValues();

	//Test all Processing Units against all memory test values
	static void HardPerformanceTest();
	static void SoftPerformanceTest();
};

