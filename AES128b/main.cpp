#include <iostream>

#include "Tests\AESTest.h"
#include "AES128AMP.h"
#include "AES128CPU.h"
#include "Utils\ApplicationSettings.h"
#include "Utils\Benchmark.h"

void TestApplicationSettings() {
	ApplicationSettings::InitAppSettings();

	ProcessingUnitSettings puSettings;
	puSettings.ImplementationId = 1;
	puSettings.IsGPU = false;
	puSettings.ProcessingUnitId = 4;

	ApplicationSettings::Current->AddProcessingUnitSettings(puSettings);

	delete ApplicationSettings::Current;
	ApplicationSettings::Current = NULL;

	ApplicationSettings::InitAppSettings();

	auto settings = ApplicationSettings::Current->GetProcessingUnitSettings(0);
	if (settings == puSettings)
		std::cout << "Application Settings Test OK";
	else
		std::cout << "Application Settings Test Failed";
}

void GenerateSettingsFile() {
	ApplicationSettings::InitAppSettings();
	if (ApplicationSettings::Current->HasSettings())
		return;

	AES128Base *implementations[] = { new AES128AMP(), new AES128CPU() };
	int implementationsCount = sizeof(implementations) / sizeof(implementations[0]);

	std::vector<ProcessingUnitInfo> pusInfo;
	for (int i = 0; i < implementationsCount; i++) {
		auto implPus = implementations[i]->GetAvailableProcessingUnits();
		pusInfo.insert(pusInfo.end(), implPus.begin(), implPus.end());
	}

	for (auto pu : pusInfo) {
		ApplicationSettings::Current->AddProcessingUnitSettings(
			ProcessingUnitSettings(
			pu.implementation->ImplementationId(),
			pu.processingUnitId,
			pu.availableMemory,
			pu.isGPU,
			pu.isGPU ? DEFAULT_MEMORY_PER_KERNEL_RUN : 0));
	}
}

int main() {
	GenerateSettingsFile();
	
	for (int i = 0; i < 10; i++)
		try {

		Benchmark::HardPerformanceTest();
	}
	catch (std::exception &ex) {
		std::cout << ex.what() << "\n";
	}

	getchar();
	return 0;
}