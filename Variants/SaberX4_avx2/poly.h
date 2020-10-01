/*---------------------------------------------------------------------
This file has been adapted from the implementation 
(available at, Public Domain https://github.com/pq-crystals/kyber) 
of "CRYSTALS – Kyber: a CCA-secure module-lattice-based KEM"
by : Joppe Bos, Leo Ducas, Eike Kiltz, Tancrede Lepoint, 
Vadim Lyubashevsky, John M. Schanck, Peter Schwabe & Damien stehle
----------------------------------------------------------------------*/

#ifndef POLY_H
#define POLY_H

#include <stdint.h>
#include "SABER_params.h"
#include <immintrin.h>

uint64_t clock_mul, clock_matrix, clock_secret,count_mul;


typedef struct
{
  uint16_t coeffs[SABER_N];
} poly;

typedef struct{
  poly vec[SABER_K];
} polyvec;

typedef struct{
	__m256i coeffs[SABER_N/16];
} polyNew;

typedef struct{
  polyNew vec[SABER_K];
} polyvecNew;




void poly_getnoise(uint16_t *r,const unsigned char *seed, unsigned char nonce);

void poly_getnoise4x(uint16_t *r0, uint16_t *r1, uint16_t *r2, const unsigned char *seed, unsigned char nonce0, unsigned char nonce1, unsigned char nonce2, unsigned char nonce3);


#endif
