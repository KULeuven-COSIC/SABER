#include <stdio.h>
#include "api.h"
#include "poly.h"
#include "poly_mul.h"
#include "pack_unpack.h"
#include "cbd.h"
#include "fips202.h"
#include "symmetric.h"

void MatrixVectorMul(const uint16_t A[SABER_L][SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N], uint16_t res[SABER_L][SABER_N], int16_t transpose)
{
	size_t i, j;

	for (i = 0; i < SABER_L; i++)
	{
		for (j = 0; j < SABER_L; j++)
		{
			if (transpose == 1)
			{
				poly_mul_acc(A[j][i], s[j], res[i]);
			}
			else
			{
				poly_mul_acc(A[i][j], s[j], res[i]);
			}	
		}
	}
}

void InnerProd(const uint16_t b[SABER_L][SABER_N], const uint16_t s[SABER_L][SABER_N], uint16_t res[SABER_N])
{
	size_t j;
	for (j = 0; j < SABER_L; j++)
	{
		poly_mul_acc(b[j], s[j], res);
	}
}

void GenMatrix(uint16_t A[SABER_L][SABER_L][SABER_N], const uint8_t seed[SABER_SEEDBYTES])
{
	size_t i;
	uint8_t buf[SABER_L * SABER_POLYVECBYTES];

	prf(buf, sizeof(buf), seed, SABER_SEEDBYTES);

	for (i = 0; i < SABER_L; i++)
	{
		BS2POLVECq(buf + i * SABER_POLYVECBYTES, A[i]);
	}
}

void GenSecret(uint16_t s[SABER_L][SABER_N], const uint8_t seed[SABER_NOISE_SEEDBYTES])
{
	size_t i;
	uint8_t buf[SABER_L * SABER_POLYCOINBYTES];

	prf(buf, sizeof(buf), seed, SABER_NOISE_SEEDBYTES);

	for (i = 0; i < SABER_L; i++)
	{

	#ifndef uSaber
		cbd(s[i], buf + i * SABER_POLYCOINBYTES);
	#else

		// struct int2_t {signed int bits:2;} two; 
		size_t j;

		for(j=0;j<SABER_N/4;j++)
		{
			// s[i][4*j] = two.bits = ((buf[j + i * SABER_POLYCOINBYTES]) & 0x03); 
			// s[i][4*j+1] = two.bits = ((buf[j + i * SABER_POLYCOINBYTES] >> 2) & 0x03);
			// s[i][4*j+2] = two.bits = ((buf[j + i * SABER_POLYCOINBYTES] >> 4) & 0x03);
			// s[i][4*j+3] = two.bits = ((buf[j + i * SABER_POLYCOINBYTES] >> 6) & 0x03);
			s[i][4*j] = (((buf[j + i * SABER_POLYCOINBYTES]) & 0x03) ^ 2) - 2; 
			s[i][4*j+1] = (((buf[j + i * SABER_POLYCOINBYTES] >> 2) & 0x03)  ^ 2) - 2;
			s[i][4*j+2] = (((buf[j + i * SABER_POLYCOINBYTES] >> 4) & 0x03)  ^ 2) - 2;
			s[i][4*j+3] = (((buf[j + i * SABER_POLYCOINBYTES] >> 6) & 0x03)  ^ 2) - 2;
		}
	#endif
	}
}
