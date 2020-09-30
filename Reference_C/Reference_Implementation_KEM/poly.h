#ifndef POLY_H
#define POLY_H

#include <stdint.h>
#include "SABER_params.h"

void MatrixVectorMul(const uint16_t a[SABER_K][SABER_K][SABER_N], const uint16_t s[SABER_K][SABER_N], uint16_t res[SABER_K][SABER_N], int16_t transpose);
void InnerProd(const uint16_t b[SABER_K][SABER_N], const uint16_t s[SABER_K][SABER_N], uint16_t res[SABER_N]);
void GenMatrix(uint16_t a[SABER_K][SABER_K][SABER_N], const uint8_t seed[SABER_SEEDBYTES]);
void GenSecret(uint16_t s[SABER_K][SABER_N], const uint8_t seed[SABER_NOISE_SEEDBYTES]);

#endif
