#include <iostream>

#include "AESTest.h"
#include "AES128AMP.h"
#include "AES128CPU.h"

int main()
{
	AES128AMP aesAMP;
	AES128CPU aesCPU;

	std::cout << "Testing AMP Encryption implementation\r\n";
	AESEncryptionTest(&aesAMP);

	std::cout << "Testing CPU Encryption implementation\r\n";
	AESEncryptionTest(&aesCPU);

	getchar();
}