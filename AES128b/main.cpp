#include <iostream>

#include "AESTest.h"
#include "AES128AMP.h"
#include "AES128CPU.h"
#include "Utils\ApplicationSettings.h"

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
	//AESAMPGPUMemoryTest();
	//AESCPUParallelTest();

	//TestApplicationSettings();

	AES128AMP aesAMP;
	AESEncryptionTest(&aesAMP);

	AESAMPGPUTDRTest();

	getchar();
	return 0;
}