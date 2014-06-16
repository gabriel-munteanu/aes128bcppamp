#pragma once

#include <vector>
#include <string>

struct ProcessingUnitInfo{
	std::string name;
	//if is set to 0 then we are working with the RAM memory and the CPU as PU
	unsigned long availalbeMemory;
	bool isEmulated;

	ProcessingUnitInfo(std::string pName, unsigned long pAvailalbeMemory, bool pIsEmulated) {
		name = pName;
		availalbeMemory = pAvailalbeMemory;
		isEmulated = pIsEmulated;
	}
};

class AES128Base {

private:

protected:
	unsigned char _key[17];
	unsigned char _expandedKey[11][4][4];
	unsigned char *_data;
	unsigned long _dataLength;

	//processing units identifiers
	std::vector<void*> _puIdentifiers;

	AES128Base();
	void KeyExpansion();

public:
	virtual std::vector<ProcessingUnitInfo> GetAvailableProcessingUnits() = 0;

	void SetKey(std::string key);
	//The data will be overwrite by the encryption/decryption process
	void SetData(unsigned char *data, unsigned long length);

	//Encrypt using the specified Processing Unit
	//If the index is not valid it will throw an exception
	virtual void Encrypt(unsigned int puIndex) = 0;

	//Decrypt using the specified Processing Unit
	//If the index is not valid it will throw an exception
	virtual void Decrypt(unsigned int puIndex) = 0;
};