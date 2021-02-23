#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "poly_mul.h"

//define to use assembly
#define PQM4_POLY_MUL

// extra memory for unrolled karatsuba
uint16_t kara_tmp[16];

extern void polymul_asm(uint16_t *r, const uint16_t *a, const uint16_t *b);

void pol_mul(uint16_t* a, uint16_t* b, uint16_t* res, uint16_t p, uint32_t n)
{ 
	uint32_t i;

	uint16_t c[2*SABER_N];
	for (i = 0; i < 2*n; i++) c[i] = 0;

//-------------------normal multiplication-----------------

#ifdef PQM4_POLY_MUL

	polymul_asm(c, a, b);

#else

	uint32_t j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			c[i+j]=( c[i+j] + (a[i] * b[j]) );//&(p-1);
		}
	}

#endif

	for (i = n; i < 2*n-1; i++){
		res[i - n] = (c[i - n] - c[i]) & (p - 1);
	}
	res[n - 1] = c[n - 1];

}

