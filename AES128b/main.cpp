#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mainAMP.h"
#include <iostream>

typedef unsigned char word8;

word8 Logtable[256] = { 0, 0, 25, 1, 50, 2, 26, 198, 75, 199, 27, 104, 51, 238, 223, 3, 100, 4, 224, 14, 52, 141, 129, 239, 76, 113, 8, 200, 248, 105, 28, 193, 125, 194, 29, 181, 249, 185, 39, 106, 77, 228, 166, 114, 154, 201, 9, 120, 101, 47, 138, 5, 33, 15, 225, 36, 18, 240, 130, 69, 53, 147, 218, 142, 150, 143, 219, 189, 54, 208, 206, 148, 19, 92, 210, 241, 64, 70, 131, 56, 102, 221, 253, 48, 191, 6, 139, 98, 179, 37, 226, 152, 34, 136, 145, 16, 126, 110, 72, 195, 163, 182, 30, 66, 58, 107, 40, 84, 250, 133, 61, 186, 43, 121, 10, 21, 155, 159, 94, 202, 78, 212, 172, 229, 243, 115, 167, 87, 175, 88, 168, 80, 244, 234, 214, 116, 79, 174, 233, 213, 231, 230, 173, 232, 44, 215, 117, 122, 235, 22, 11, 245, 89, 203, 95, 176, 156, 169, 81, 160, 127, 12, 246, 111, 23, 196, 73, 236, 216, 67, 31, 45, 164, 118, 123, 183, 204, 187, 62, 90, 251, 96, 177, 134, 59, 82, 161, 108, 170, 85, 41, 157, 151, 178, 135, 144, 97, 190, 220, 252, 188, 149, 207, 205, 55, 63, 91, 209, 83, 57, 132, 60, 65, 162, 109, 71, 20, 42, 158, 93, 86, 242, 211, 171, 68, 17, 146, 217, 35, 32, 46, 137, 180, 124, 184, 38, 119, 153, 227, 165, 103, 74, 237, 222, 197, 49, 254, 24, 13, 99, 140, 128, 192, 247, 112, 7 };
word8 Alogtable[256] = { 1, 3, 5, 15, 17, 51, 85, 255, 26, 46, 114, 150, 161, 248, 19, 53, 95, 225, 56, 72, 216, 115, 149, 164, 247, 2, 6, 10, 30, 34, 102, 170, 229, 52, 92, 228, 55, 89, 235, 38, 106, 190, 217, 112, 144, 171, 230, 49, 83, 245, 4, 12, 20, 60, 68, 204, 79, 209, 104, 184, 211, 110, 178, 205, 76, 212, 103, 169, 224, 59, 77, 215, 98, 166, 241, 8, 24, 40, 120, 136, 131, 158, 185, 208, 107, 189, 220, 127, 129, 152, 179, 206, 73, 219, 118, 154, 181, 196, 87, 249, 16, 48, 80, 240, 11, 29, 39, 105, 187, 214, 97, 163, 254, 25, 43, 125, 135, 146, 173, 236, 47, 113, 147, 174, 233, 32, 96, 160, 251, 22, 58, 78, 210, 109, 183, 194, 93, 231, 50, 86, 250, 21, 63, 65, 195, 94, 226, 61, 71, 201, 64, 192, 91, 237, 44, 116, 156, 191, 218, 117, 159, 186, 213, 100, 172, 239, 42, 126, 130, 157, 188, 223, 122, 142, 137, 128, 155, 182, 193, 88, 232, 35, 101, 175, 234, 37, 111, 177, 200, 67, 197, 84, 252, 31, 33, 99, 165, 244, 7, 9, 27, 45, 119, 153, 176, 203, 70, 202, 69, 207, 74, 222, 121, 139, 134, 145, 168, 227, 62, 66, 198, 81, 243, 14, 18, 54, 90, 238, 41, 123, 141, 140, 143, 138, 133, 148, 167, 242, 13, 23, 57, 75, 221, 124, 132, 151, 162, 253, 28, 36, 108, 180, 199, 82, 246, 1 };
word8 S[256] = { 99, 124, 119, 123, 242, 107, 111, 197, 48, 1, 103, 43, 254, 215, 171, 118, 202, 130, 201, 125, 250, 89, 71, 240, 173, 212, 162, 175, 156, 164, 114, 192, 183, 253, 147, 38, 54, 63, 247, 204, 52, 165, 229, 241, 113, 216, 49, 21, 4, 199, 35, 195, 24, 150, 5, 154, 7, 18, 128, 226, 235, 39, 178, 117, 9, 131, 44, 26, 27, 110, 90, 160, 82, 59, 214, 179, 41, 227, 47, 132, 83, 209, 0, 237, 32, 252, 177, 91, 106, 203, 190, 57, 74, 76, 88, 207, 208, 239, 170, 251, 67, 77, 51, 133, 69, 249, 2, 127, 80, 60, 159, 168, 81, 163, 64, 143, 146, 157, 56, 245, 188, 182, 218, 33, 16, 255, 243, 210, 205, 12, 19, 236, 95, 151, 68, 23, 196, 167, 126, 61, 100, 93, 25, 115, 96, 129, 79, 220, 34, 42, 144, 136, 70, 238, 184, 20, 222, 94, 11, 219, 224, 50, 58, 10, 73, 6, 36, 92, 194, 211, 172, 98, 145, 149, 228, 121, 231, 200, 55, 109, 141, 213, 78, 169, 108, 86, 244, 234, 101, 122, 174, 8, 186, 120, 37, 46, 28, 166, 180, 198, 232, 221, 116, 31, 75, 189, 139, 138, 112, 62, 181, 102, 72, 3, 246, 14, 97, 53, 87, 185, 134, 193, 29, 158, 225, 248, 152, 17, 105, 217, 142, 148, 155, 30, 135, 233, 206, 85, 40, 223, 140, 161, 137, 13, 191, 230, 66, 104, 65, 153, 45, 15, 176, 84, 187, 22 };
word8 Si[256] = { 82, 9, 106, 213, 48, 54, 165, 56, 191, 64, 163, 158, 129, 243, 215, 251, 124, 227, 57, 130, 155, 47, 255, 135, 52, 142, 67, 68, 196, 222, 233, 203, 84, 123, 148, 50, 166, 194, 35, 61, 238, 76, 149, 11, 66, 250, 195, 78, 8, 46, 161, 102, 40, 217, 36, 178, 118, 91, 162, 73, 109, 139, 209, 37, 114, 248, 246, 100, 134, 104, 152, 22, 212, 164, 92, 204, 93, 101, 182, 146, 108, 112, 72, 80, 253, 237, 185, 218, 94, 21, 70, 87, 167, 141, 157, 132, 144, 216, 171, 0, 140, 188, 211, 10, 247, 228, 88, 5, 184, 179, 69, 6, 208, 44, 30, 143, 202, 63, 15, 2, 193, 175, 189, 3, 1, 19, 138, 107, 58, 145, 17, 65, 79, 103, 220, 234, 151, 242, 207, 206, 240, 180, 230, 115, 150, 172, 116, 34, 231, 173, 53, 133, 226, 249, 55, 232, 28, 117, 223, 110, 71, 241, 26, 113, 29, 41, 197, 137, 111, 183, 98, 14, 170, 24, 190, 27, 252, 86, 62, 75, 198, 210, 121, 32, 154, 219, 192, 254, 120, 205, 90, 244, 31, 221, 168, 51, 136, 7, 199, 49, 177, 18, 16, 89, 39, 128, 236, 95, 96, 81, 127, 169, 25, 181, 74, 13, 45, 229, 122, 159, 147, 201, 156, 239, 160, 224, 59, 77, 174, 42, 245, 176, 200, 235, 187, 60, 131, 83, 153, 97, 23, 43, 4, 126, 186, 119, 214, 38, 225, 105, 20, 99, 85, 33, 12, 125 };

int RC[30] = { 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A, 0x2F, 0x5E, 0xBC, 0x63, 0xC6, 0x97, 0x35, 0x6A, 0xD4, 0xB3, 0x7D, 0xFA, 0xEF, 0xC5 };


void showLayer(word8 l[4][4])
{
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
			printf("%03i ", l[i][j]);
		printf("\r\n");
	}
	printf("\r\n");
}

void KeyExpansion(word8 input[4][4], word8 output[11][4][4])
{
	int Ri = 1; // round index
	word8 tk[4][4]; // temporary key

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tk[i][j] = input[i][j];
			output[0][i][j] = input[i][j];
		}
	}

	for (int ri = 1; ri <= 10; ri++) // round index
	{
		// circulary shift last column by on position, run each element through a Substitution box and xor it with the first colum
		// saving the result in the first column
		// this is the first column of the new round
		tk[0][0] ^= S[tk[1][3]];
		tk[1][0] ^= S[tk[2][3]];
		tk[2][0] ^= S[tk[3][3]];
		tk[3][0] ^= S[tk[0][3]];

		//xor with the round constant
		tk[0][0] ^= RC[ri];

		// for the next columns, xor the same column from previous round with the previous column from current round
		for (int i = 0; i < 4; i++)
			for (int j = 1; j < 4; j++)
				tk[i][j] ^= tk[i][j - 1];

		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				output[ri][i][j] = tk[i][j];
	}
}

word8 mul(word8 a, word8 b) { /* multiply two elements of GF(256)  required for MixColumns and InvMixColumns */

	if (a && b) return Alogtable[(Logtable[a] + Logtable[b]) % 255];
	else return 0;
}

void AddRoundKey(word8 data[4][4], word8 rk[4][4]) {
	/* XOR corresponding text input and round key input bytes */
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			data[i][j] ^= rk[i][j];
}

void SubBytes(word8 data[4][4], word8 box[256]) {
	/* Replace every byte of the input by the byte at that place  in the non-linear S-box */
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			data[i][j] = box[data[i][j]];
}

void ShiftRows(word8 a[4][4], word8 d) {
	/* Row 0 remains unchanged
	* The other three rows are shifted at left by i*/
	word8 tmp[4];
	int i, j;
	if (d == 0) {//at encrypting

		for (i = 1; i < 4; i++) {
			for (j = 0; j < 4; j++)
				tmp[j] = a[i][(i + j) % 4];
			for (j = 0; j < 4; j++)
				a[i][j] = tmp[j];
		}
	}
	else {//at decrypting

		for (i = 1; i < 4; i++) {
			for (j = 0; j < 4; j++)
				tmp[j] = a[i][(4 + j - i) % 4];
			for (j = 0; j < 4; j++)
				a[i][j] = tmp[j];
		}
	}
}

void MixColumns(word8 a[4][4]) {
	/* Mix the four bytes of every column in a linear way */
	word8 b[4][4]; int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			b[i][j] = mul(2, a[i][j]) ^ mul(3, a[(i + 1) % 4][j]) ^ a[(i + 2) % 4][j] ^ a[(i + 3) % 4][j];
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			a[i][j] = b[i][j];
}

void InvMixColumns(word8 a[4][4]) {
	/* Mix the four bytes of every column in a linear way
	* This is the opposite operation of Mixcolumns */
	word8 b[4][4];
	int i, j;

	for (j = 0; j < 4; j++)
		for (i = 0; i < 4; i++)
			b[i][j] = mul(0xe, a[i][j]) ^ mul(0xb, a[(i + 1) % 4][j]) ^ mul(0xd, a[(i + 2) % 4][j]) ^ mul(0x9, a[(i + 3) % 4][j]);
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			a[i][j] = b[i][j];
}

void Encrypt(word8 data[4][4], word8 rk[11][4][4]) {
	/* Encryption of one block. */
	int r;
	/* begin with a key addition */
	AddRoundKey(data, rk[0]);
	/* RDUNDS-1 ordinary rounds */
	for (r = 1; r < 10; r++)
	{
		SubBytes(data, S);
		ShiftRows(data, 0);
		MixColumns(data);
		AddRoundKey(data, rk[r]);
	}
	/* Last round is special : there is no MixColumns */
	SubBytes(data, S);
	ShiftRows(data, 0);
	AddRoundKey(data, rk[10]);
}

void Decrypt(word8 data[4][4], word8 rk[11][4][4]) {
	int r;
	/* To decrypt :
	* apply the inverse operations of the encrypt routine,
	* in opposite order
	*
	* - AddRoundKey is equal to its inverse)
	* -the inverse of SubBytes with table S is
	* SubBytes with the inverse table of S)
	* - the inverse of Shiftrows is Shiftrows over
	* a suitable distance) */

	/* First the special round:
	* without InvMixColumns
	* with extra AddRoundKey */
	AddRoundKey(data, rk[10]);
	SubBytes(data, Si); ShiftRows(data, 1);
	/* RDUNDS-1 ordinary rounds */

	for (r = 10 - 1; r > 0; r--)
	{
		AddRoundKey(data, rk[r]);
		InvMixColumns(data);
		SubBytes(data, Si);
		ShiftRows(data, 1);
	}
	/* End with the extra key addition */
	AddRoundKey(data, rk[0]);
}


void EncDecTest()
{
	word8 k[4][4], ek[11][4][4];

	memset(k, 0, sizeof(word8) * 16);

	KeyExpansion(k, ek);

	//Encrypt(data, ek);
	//showLayer(data);

	//Decrypt(data, ek);
	//showLayer(data);

	unsigned char *data;
	data = (unsigned char*)malloc(16 * 100);
	memset(data, 0, 16 * 100);
	for (int i = 0; i < 16; i++)
		data[i] = i;
	AES128AmpEncrypt(data, 16 * 100, ek);

	AES128AmpDecrypt(data, 16 * 100, ek);


	word8 d2[4][4];
	memcpy(d2, data, 16);
	//Decrypt(d2, ek);
	showLayer(d2);


	/*int l = 0;
	for (int i = 0; i < 100; i++){
	for (int j = 0; j < 16; j++)
	printf("%d ", data[l++]);
	getchar();
	}*/


}

void AcceleratorInfo()
{
	bool show_all = true;
	bool old_format = false;
	

	std::vector<accelerator> accls = accelerator::get_all();
	if (!show_all)
	{
		accls.erase(std::remove_if(accls.begin(), accls.end(), [](accelerator& a)
		{
			return (a.device_path == accelerator::cpu_accelerator) || (a.device_path == accelerator::direct3d_ref);
		}), accls.end());
	}

	if (accls.empty())
	{
		std::wcout << "No accelerators found that are compatible with C++ AMP" << std::endl << std::endl;
		return;
	}
	std::cout << "Show " << (show_all ? "all " : "") << "AMP Devices (";
#if defined(_DEBUG)
	std::cout << "DEBUG";
#else
	std::cout << "RELEASE";
#endif
	std::cout << " build)" << std::endl;
	std::wcout << "Found " << accls.size()
		<< " accelerator device(s) that are compatible with C++ AMP:" << std::endl;
	int n = 0;
	if (old_format)
	{
		std::for_each(accls.cbegin(), accls.cend(), [=, &n](const accelerator& a)
		{
			std::wcout << "  " << ++n << ": " << a.description
				<< ", has_display=" << (a.has_display ? "true" : "false")
				<< ", is_emulated=" << (a.is_emulated ? "true" : "false")
				<< std::endl;
		});
		std::wcout << std::endl;
		return;
	}

	std::for_each(accls.cbegin(), accls.cend(), [=, &n](const accelerator& a)
	{
		std::wcout << "  " << ++n << ": " << a.description << " "
			<< std::endl << "       device_path                       = " << a.device_path
			<< std::endl << "       dedicated_memory                  = " <<  float(a.dedicated_memory) / (1024.0f * 1024.0f) << " Mb"
			<< std::endl << "       has_display                       = " << (a.has_display ? "true" : "false")
			<< std::endl << "       is_debug                          = " << (a.is_debug ? "true" : "false")
			<< std::endl << "       is_emulated                       = " << (a.is_emulated ? "true" : "false")
			<< std::endl << "       supports_double_precision         = " << (a.supports_double_precision ? "true" : "false")
			<< std::endl << "       supports_limited_double_precision = " << (a.supports_limited_double_precision ? "true" : "false")
			<< std::endl;
	});
}

int main()
{
	//EncDecTest();
	AcceleratorInfo();
	getchar();

}