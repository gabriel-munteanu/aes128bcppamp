#include <amp.h>

using namespace concurrency;

//this method must receive the data array a multiple of 16
//size = number of chars
//key = expanded key
void AES128AmpEncrypt(unsigned char *data, long size, unsigned char key[11][4][4]);

//this method must receive the data array a multiple of 16
//size = number of chars
//key = expanded key
void AES128AmpDecrypt(unsigned char *data, long size, unsigned char key[11][4][4]);