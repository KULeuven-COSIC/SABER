#include <stdio.h>
#include "api.h"
#include "poly.h"
#include "poly_mul.h"
#include "pack_unpack.h"
#include "cbd.h"
#include "fips202.h"

void MatrixVectorMul(const uint16_t A[SABER_K][SABER_K][SABER_N], const uint16_t s[SABER_K][SABER_N], uint16_t res[SABER_K][SABER_N], int16_t transpose)
{
	for (size_t i = 0; i < SABER_K; i++)
	{
		for (size_t j = 0; j < SABER_K; j++)
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

void InnerProd(const uint16_t b[SABER_K][SABER_N], const uint16_t s[SABER_K][SABER_N], uint16_t res[SABER_N])
{
	for (size_t j = 0; j < SABER_K; j++)
	{
		poly_mul_acc(b[j], s[j], res);
	}
}

void GenMatrix(uint16_t A[SABER_K][SABER_K][SABER_N], const uint8_t seed[SABER_SEEDBYTES])
{
	uint8_t buf[SABER_K * SABER_POLYVECBYTES];

	shake128(buf, sizeof(buf), seed, SABER_SEEDBYTES);

	for (size_t i = 0; i < SABER_K; i++)
	{
		BS2POLVECq(buf + i * SABER_K * SABER_POLYBYTES, A[i]);
	}
}

void GenSecret(uint16_t s[SABER_K][SABER_N], const uint8_t seed[SABER_NOISE_SEEDBYTES])
{
	uint8_t buf[SABER_COINBYTES];

	shake128(buf, sizeof(buf), seed, SABER_NOISE_SEEDBYTES);

	for (size_t i = 0; i < SABER_K; i++)
	{
		cbd(s[i], buf + i * (SABER_COINBYTES / SABER_K));
	}
}
