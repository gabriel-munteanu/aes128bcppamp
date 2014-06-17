#pragma once

#include <fstream>
#include <vector>
#include <string>

struct ProcessingUnitSettings {
	unsigned int ImplementationId;
	unsigned int ProcessingUnitId;
	//in bytes
	unsigned long MaxMemoryRecomanded;
	bool IsGPU;
	//in bytes
	unsigned long MaxMemoryPerKernelExecution;//this will be set only if IsGPU is true
};


class ApplicationSettings {
private:
	//static members	

	//instance members

	bool _hasSettings;
	ApplicationSettings();
	void ReadSettings();
	void FlushSettings();

	//settings

	std::vector< ProcessingUnitSettings > _pusSettings;

public:
	//static members

	static ApplicationSettings *Current;
	static void InitAppSettings();

	//instance members

	bool HasSettings() { return _hasSettings; }
	unsigned int GetProcessingUnitsCount() { return _pusSettings.size(); }
	ProcessingUnitSettings GetProcessingUnitSettings(unsigned int index) { return _pusSettings[index]; }
	void UpdateProcessingUnitSettings(unsigned int index, ProcessingUnitSettings puSettings) { _pusSettings[index] = puSettings; FlushSettings(); }
	void AddProcessingUnitSettings(ProcessingUnitSettings puSettings) { _pusSettings.push_back(puSettings); FlushSettings(); }
	void ClearAllProcessingUnitsSettings() { _pusSettings.clear(); }
};

