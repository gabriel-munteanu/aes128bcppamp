#pragma once

#include "AES128Base.h"

typedef unsigned char word8;


class AES128CPU : public AES128Base {

private:
	static word8 Logtable[256];
	static word8 Alogtable[256];
	static word8 S[256];
	static word8 Si[256];

	static word8 mul(word8 a, word8 b);
	static void AddRoundKey(word8 data[4][4], word8 rk[4][4]);
	static void SubBytes(word8 data[4][4], word8 box[256]);
	static void ShiftRows(word8 a[4][4], word8 d);
	static void MixColumns(word8 a[4][4]);
	static void InvMixColumns(word8 a[4][4]);	

	void EncryptBlock(word8 block[4][4]);
	void DecryptBlock(word8 block[4][4]);

	void SequentialEncryption();
	void SequentialDecryption();

public:
	std::vector<ProcessingUnitInfo> GetAvailableProcessingUnits();

	//Encrypt using the specified Processing Unit
	//If the index is not valid it will throw an exception
	void Encrypt(unsigned int puIndex);

	//Decrypt using the specified Processing Unit
	//If the index is not valid it will throw an exception
	void Decrypt(unsigned int puIndex);

};