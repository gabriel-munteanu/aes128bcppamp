#include "ApplicationSettings.h"

#define APPSETTINGSFILENAME "aes128.data"
ApplicationSettings *ApplicationSettings::Current = NULL;


ApplicationSettings::ApplicationSettings() {
	_hasSettings = false;
}

void ApplicationSettings::ReadSettings() {
	std::ifstream fin;
	unsigned int pusCount;
	ProcessingUnitSettings *pusSettings;

	fin.open(APPSETTINGSFILENAME, std::fstream::in | std::fstream::binary);
	if (fin.fail()) {
		_hasSettings = false;
		return;
	}

	fin.read((char*)&pusCount, sizeof(pusCount));
	pusSettings = new ProcessingUnitSettings[pusCount];

	fin.read((char*)pusSettings, pusCount*sizeof(ProcessingUnitSettings));
	for (unsigned int i = 0; i < pusCount; i++)
		_pusSettings.push_back(pusSettings[i]);

	delete[] pusSettings;
	fin.close();
	_hasSettings = true;
}

void ApplicationSettings::FlushSettings() {
	std::ofstream fout;
	unsigned int pusCount = _pusSettings.size();

	//overwrite the previous file
	fout.open(APPSETTINGSFILENAME, std::fstream::out | std::fstream::binary);
	if (fout.fail())
		throw std::exception("Could not save application settings file!");

	fout.write((const char*)&pusCount, sizeof(pusCount));
	//it shouldn't be a 'performance problem' since the are only a few Processing Units
	for (auto puInfo : _pusSettings)
		fout.write((const char*)&puInfo, sizeof(ProcessingUnitSettings));

	fout.close();
}


void ApplicationSettings::InitAppSettings() {
	if (Current != NULL)
		return;

	Current = new ApplicationSettings();
	Current->ReadSettings();
}

ProcessingUnitSettings ApplicationSettings::GetProcessingUnitSettings(unsigned int implementationId, unsigned int puId) {
	for (auto &pu : _pusSettings)
		if (pu.ImplementationId == implementationId && pu.ProcessingUnitId == puId)
			return pu;
	return ProcessingUnitSettings::Invalid();
}

bool ApplicationSettings::UpdateProcessingUnitSettings(ProcessingUnitSettings puSettings) {
	for (auto &pu : _pusSettings) {
		if (pu.ImplementationId == puSettings.ImplementationId && pu.ProcessingUnitId == puSettings.ProcessingUnitId) {
			pu = puSettings;
			FlushSettings();
			return true;
		}
	}
	return false;
}

void ApplicationSettings::ClearAllProcessingUnitsSettings() {
	remove(APPSETTINGSFILENAME);
	_pusSettings.clear();
}

