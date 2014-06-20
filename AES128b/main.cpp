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

int main()
{
	
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