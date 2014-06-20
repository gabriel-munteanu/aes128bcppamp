#pragma once

#include <amp.h>
#include "AES128Base.h"

using namespace concurrency;

class AES128AMP : public AES128Base {

private:
	std::vector<accelerator> _availableAccelerator;

	static int mul(unsigned int a, unsigned int b, const unsigned int alogtable[246], const unsigned int logtable[256]) restrict(amp);
	static void AddRoundKey(unsigned int data[4][4], const unsigned int rk[4][4]) restrict(amp);
	static void SubBytes(unsigned int data[4][4], const unsigned int box[256]) restrict(amp);
	static void ShiftRows(unsigned int a[4][4], int d) restrict(amp);
	static void MixColumns(unsigned int a[4][4], const unsigned int alogtable[246], const unsigned int logtable[256]) restrict(amp);
	static void InvMixColumns(unsigned int a[4][4], const unsigned int alogtable[246], const unsigned int logtable[256]) restrict(amp);

	unsigned long GetMaxMemoryPerKernelExecution(unsigned int puIndex);
	void UpdateMaxMemoryPerKernelExecution(unsigned int puIndex, unsigned long memory);
	void AMPEncrypt(unsigned int puIndex);
	void AMPDecryption(unsigned int puIndex);

public:
	unsigned int ImplementationId();
	std::vector<ProcessingUnitInfo> GetAvailableProcessingUnits();
	std::vector<std::vector<double>> EncryptionKernelTimings;

	//Encrypt using the specified Processing Unit
	//If the index is not valid it will throw an exception
	void Encrypt(unsigned int puIndex);

	//Decrypt using the specified Processing Unit
	//If the index is not valid it will throw an exception
	void Decrypt(unsigned int puIndex);

};