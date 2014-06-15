#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "AES128AMP.h"
#include <iostream>


typedef unsigned char word8;

void showLayer(word8 l[4][4])
{
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++)
			printf("%03i ", l[i][j]);
		printf("\r\n");
	}
	printf("\r\n");
}


void EncDecTest()
{
	word8 k[16];

	memset(k, 0, sizeof(word8) * 16);

	//KeyExpansion(k, ek);

	//Encrypt(data, ek);
	//showLayer(data);

	//Decrypt(data, ek);
	//showLayer(data);

	unsigned char *data;
	data = (unsigned char*)malloc(16 * 100);
	memset(data, 0, 16 * 100);
	for (int i = 0; i < 16; i++)
		data[i] = i;
	//AES128AmpEncrypt(data, 16 * 100, k);

	//AES128AmpDecrypt(data, 16 * 100, k);


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




int main()
{
	AES128AMP aesAmp;
	auto pu = aesAmp.GetAvailableProcessingUnits();
	std::for_each(pu.begin(), pu.end(), [](const std::string &d){
		std::cout << d << std::endl;
	});
	getchar();

}