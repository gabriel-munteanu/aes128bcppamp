#include <iostream>

#include "AESTest.h"
#include "AES128AMP.h"
#include "AES128CPU.h"

int main()
{
	//AESAMPGPUMemoryTest();
	AESCPUParallelTest();

	getchar();
	return 0;
}