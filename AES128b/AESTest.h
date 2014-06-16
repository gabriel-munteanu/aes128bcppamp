#pragma once

#include "AES128AMP.h"
#include "AES128CPU.h"

void AESEncryptionTest(AES128Base* implementation);
void AESDecryptionTest(AES128Base* implementation);

void AESEncryptionTestAll();
void AESDecryptionTestAll();

void AESAMPGPUMemoryTest();
void AESCPUParallelTest();