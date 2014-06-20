#pragma once

#include <fstream>
#include <vector>
#include <string>

//50MB by default
#define DEFAULT_MEMORY_PER_KERNEL_RUN 1024*1024*50

struct ProcessingUnitSettings {
	unsigned int ImplementationId;
	unsigned int ProcessingUnitId;
	//The upper memory limit that this PU is recommened to consider
	//The lower limit can be obtain from the previous PU in the sorted list
	//in bytes
	unsigned long MaxMemoryRecommended;//to be used by the memory Management Module
	bool IsGPU;
	//in bytes
	//it must be a multiple of 16
	unsigned long MaxMemoryPerKernelExecution;//this will be set only if IsGPU is true

	ProcessingUnitSettings(unsigned int pImplementationId, unsigned int pProcessingUnitId, unsigned long pMaxMemoryRecommended,
		bool pIsGPU, unsigned long pMaxMemoryPerKernelExecution) {
		ImplementationId = pImplementationId;
		ProcessingUnitId = pProcessingUnitId;
		MaxMemoryRecommended = pMaxMemoryRecommended;
		IsGPU = pIsGPU;
		MaxMemoryPerKernelExecution = pMaxMemoryPerKernelExecution;
	}
	ProcessingUnitSettings() {}

	bool operator ==(ProcessingUnitSettings &compWith) {
		if (ImplementationId == compWith.ImplementationId &&
			ProcessingUnitId == compWith.ProcessingUnitId &&
			MaxMemoryPerKernelExecution == compWith.MaxMemoryPerKernelExecution &&
			IsGPU == compWith.IsGPU &&
			MaxMemoryRecommended == compWith.MaxMemoryRecommended)
			return true;
		else
			return false;
	}

	static ProcessingUnitSettings Invalid() {
		return ProcessingUnitSettings{ -1 };
	}

private:
	ProcessingUnitSettings(int n) { ProcessingUnitSettings(n, n, n, false, n); }
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
	ProcessingUnitSettings GetProcessingUnitSettings(unsigned int index) {
		if (index < _pusSettings.size())
			return _pusSettings[index];
		else
			return ProcessingUnitSettings::Invalid();
	}
	ProcessingUnitSettings GetProcessingUnitSettings(unsigned int implementationId, unsigned int puId);
	bool UpdateProcessingUnitSettings(ProcessingUnitSettings puSettings);
	void AddProcessingUnitSettings(ProcessingUnitSettings puSettings) { _pusSettings.push_back(puSettings); FlushSettings(); }
	void ClearAllProcessingUnitsSettings();
};

