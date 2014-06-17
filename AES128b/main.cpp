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

	int i = ApplicationSettings::Current->GetProcessingUnitsCount();
}

int main()
{
	//AESAMPGPUMemoryTest();
	//AESCPUParallelTest();

	TestApplicationSettings();

	getchar();
	return 0;
}