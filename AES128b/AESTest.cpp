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

void initInputForEnryption() {
	for (unsigned char *p = testBuffer; p < testBuffer + 16 * 1024; p += 16)
		memcpy(p, inputData, 16);
}

bool TestEncryptionResult() {
	for (unsigned char *p = testBuffer; p < testBuffer + 16 * 1024; p += 16) {
		if (memcmp(p, outputData, 16) != 0) {
			std::cout << "\r\nInvalid output. Index = " << (p - testBuffer) / 16 << "\r\n";

			std::cout << "Actual result:\r\n";
			ShowAsMatrix((unsigned char(*)[4])p);			

			std::cout << "Expected result:\r\n";
			ShowAsMatrix((unsigned char(*)[4])outputData);

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
		initInputForEnryption();
		std::cout << i << ". " << pu[i] << " ";

		implementation->Encrypt(i);

		if (TestEncryptionResult())
			std::cout << "OK\r\n";

		std::cout << "\r\n"; 		
	}
}