#include <iostream>

#include "AESTest.h"


const unsigned char inputData[] = { 0x32, 0x88, 0x31, 0xe0, 0x43, 0x5a, 0x31, 0x37, 0xf6, 0x30, 0x98, 0x07, 0xa8, 0x8d, 0xa2, 0x34 };
const unsigned char key[] = { 0x2b, 0x28, 0xab, 0x09, 0x7e, 0xae, 0xf7, 0xcf, 0x15, 0xd2, 0x15, 0x4f, 0x16, 0xa6, 0x88, 0x3c, 0x0 };
const unsigned char outputData[] = { 0x39, 0x02, 0xdc, 0x19, 0x25, 0xdc, 0x11, 0x6a, 0x84, 0x09, 0x85, 0x0b, 0x1d, 0xfb, 0x97, 0x32 };

unsigned char testBuffer[16 * 1024];

void ShowAsMatrix(unsigned char matr[4][4]) {
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
			printf("%03i ", matr[i][j]);
		printf("\r\n");
	}
	printf("\r\n");
}

void initInput(const unsigned char *data) {
	for (unsigned char *p = testBuffer; p < testBuffer + 16 * 1024; p += 16)
		memcpy(p, data, 16);
}

bool TestResult(const unsigned char *againstData) {
	for (unsigned char *p = testBuffer; p < testBuffer + 16 * 1024; p += 16) {
		if (memcmp(p, againstData, 16) != 0) {
			std::cout << "\r\nInvalid output. Index = " << (p - testBuffer) / 16 << "\r\n";

			std::cout << "Actual result:\r\n";
			ShowAsMatrix((unsigned char(*)[4])p);

			std::cout << "Expected result:\r\n";
			ShowAsMatrix((unsigned char(*)[4])againstData);

			return false;
		}
	}

	return true;
}

void AESEncryptionTest(AES128Base* implementation) {

	implementation->SetKey(std::string((const char*)key));
	implementation->SetData(testBuffer, 16 * 1024);

	auto pu = implementation->GetAvailableProcessingUnits();
	for (int i = 0; i < pu.size(); i++)
	{
		initInput(inputData);
		std::cout << i << ". " << pu[i].name << " ";

		implementation->Encrypt(i);

		if (TestResult(outputData))
			std::cout << "OK\r\n";

		std::cout << "\r\n";
	}
}


void AESDecryptionTest(AES128Base* implementation){
	implementation->SetKey(std::string((const char*)key));
	implementation->SetData(testBuffer, 16 * 1024);

	auto pu = implementation->GetAvailableProcessingUnits();
	for (int i = 0; i < pu.size(); i++)
	{
		initInput(outputData);
		std::cout << i << ". " << pu[i].name << " ";

		implementation->Decrypt(i);

		if (TestResult(inputData))
			std::cout << "OK\r\n";

		std::cout << "\r\n";
	}
}

void AESEncryptionTestAll() {
	AES128AMP aesAMP;
	AES128CPU aesCPU;

	std::cout << "Testing AMP Encryption implementation\r\n";
	AESEncryptionTest(&aesAMP);

	std::cout << "Testing CPU Encryption implementation\r\n";
	AESEncryptionTest(&aesCPU);
}

void AESDecryptionTestAll() {
	AES128AMP aesAMP;
	AES128CPU aesCPU;

	std::cout << "Testing AMP Decryption implementation\r\n";
	AESDecryptionTest(&aesAMP);

	std::cout << "Testing CPU Decryption implementation\r\n";
	AESDecryptionTest(&aesCPU);
}

//This test is for a NVIDIA GTX 480 which has 1.5 GB of memory
void AESAMPGPUMemoryTest() {
	AES128AMP aesAMP;
	unsigned int dataSize = 1024 * 1024 * 1024 * 2; //2GB of data

	try {
		unsigned char *data = new unsigned char[dataSize];
		memset(data, 0, dataSize);


		aesAMP.SetKey(std::string((const char*)key));
		aesAMP.SetData(data, dataSize);
		aesAMP.GetAvailableProcessingUnits();

		aesAMP.Encrypt(0);//this is the first GPU, or the only one if there is a GPU installed on the sistem.
	}
	catch (std::exception &ex) {//out_of_memory: Failed to create buffer
		std::cout << ex.what();
		return;
	}

	std::cout << "GPU Memory Test OK";
}

//This will test the parallel implementation on the CPU
// I want to see if the curent process uses more than one CPU
void AESCPUParallelTest() {
	AES128CPU aesCPU;
	unsigned int dataSize = 1024 * 1024 * 1024; //1GB of data

	unsigned char *data = new unsigned char[dataSize];
	memset(data, 0, dataSize);

	aesCPU.SetKey(std::string((const char*)key));
	aesCPU.SetData(data, dataSize);
	aesCPU.Encrypt(1);//this is the parallel implementation

	std::cout << "CPU Parallel implementatin Test OK";
}