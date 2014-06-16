#pragma once

#include <vector>
#include <string>


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
	virtual std::vector<std::string> GetAvailableProcessingUnits() = 0;

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