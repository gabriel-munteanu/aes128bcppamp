#include "AES128Base.h"
#include <math.h>

AES128Base::AES128Base() {
	_data = NULL;
	_dataLength = 0;
}

void AES128Base::KeyExpansion() {
	unsigned char S[256] = { 99, 124, 119, 123, 242, 107, 111, 197, 48, 1, 103, 43, 254, 215, 171, 118, 202, 130, 201, 125, 250, 89, 71, 240, 173, 212, 162, 175, 156, 164, 114, 192, 183, 253, 147, 38, 54, 63, 247, 204, 52, 165, 229, 241, 113, 216, 49, 21, 4, 199, 35, 195, 24, 150, 5, 154, 7, 18, 128, 226, 235, 39, 178, 117, 9, 131, 44, 26, 27, 110, 90, 160, 82, 59, 214, 179, 41, 227, 47, 132, 83, 209, 0, 237, 32, 252, 177, 91, 106, 203, 190, 57, 74, 76, 88, 207, 208, 239, 170, 251, 67, 77, 51, 133, 69, 249, 2, 127, 80, 60, 159, 168, 81, 163, 64, 143, 146, 157, 56, 245, 188, 182, 218, 33, 16, 255, 243, 210, 205, 12, 19, 236, 95, 151, 68, 23, 196, 167, 126, 61, 100, 93, 25, 115, 96, 129, 79, 220, 34, 42, 144, 136, 70, 238, 184, 20, 222, 94, 11, 219, 224, 50, 58, 10, 73, 6, 36, 92, 194, 211, 172, 98, 145, 149, 228, 121, 231, 200, 55, 109, 141, 213, 78, 169, 108, 86, 244, 234, 101, 122, 174, 8, 186, 120, 37, 46, 28, 166, 180, 198, 232, 221, 116, 31, 75, 189, 139, 138, 112, 62, 181, 102, 72, 3, 246, 14, 97, 53, 87, 185, 134, 193, 29, 158, 225, 248, 152, 17, 105, 217, 142, 148, 155, 30, 135, 233, 206, 85, 40, 223, 140, 161, 137, 13, 191, 230, 66, 104, 65, 153, 45, 15, 176, 84, 187, 22 };
	int RC[30] = { 0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36, 0x6C, 0xD8, 0xAB, 0x4D, 0x9A, 0x2F, 0x5E, 0xBC, 0x63, 0xC6, 0x97, 0x35, 0x6A, 0xD4, 0xB3, 0x7D, 0xFA, 0xEF, 0xC5 };

	unsigned char tk[4][4]; // temporary key

	memcpy(tk, _key, 16 * sizeof(unsigned char));
	memcpy(_expandedKey[0], _key, 16 * sizeof(unsigned char));

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
				_expandedKey[ri][i][j] = tk[i][j];
	}
}

void AES128Base::SetData(unsigned char *data, unsigned long length) {
	if (length % 16 != 0)
		throw std::exception("Data length must be a multiple of 16");

	_data = data;
	_dataLength = length;
}

void AES128Base::SetKey(std::string key) {
	memset(_key, 0, 16 * sizeof(unsigned char));
	strcpy_s((char*)_key, (key.size() < 16 ? key.size() : 16) + 1, key.c_str());
	KeyExpansion();
}