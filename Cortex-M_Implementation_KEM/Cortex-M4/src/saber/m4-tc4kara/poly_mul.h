#ifndef POLYMUL_H
#define POLYMUL_H

#include "SABER_params.h"

extern void polymul_asm(uint16_t *r, const uint16_t *a, const uint16_t *b);
extern void toom_cook_4way_mem_asm(const uint16_t* a1,const uint16_t* b1, uint16_t* result);
extern void karatsuba_asm(const uint16_t *a, const uint16_t *b, uint16_t *result);



void poly_mul(uint16_t a[SABER_N], uint16_t b[SABER_N], uint16_t res[SABER_N]);
void poly_mul_acc(uint16_t a[SABER_N], uint16_t b[SABER_N], uint16_t res[SABER_N]);

#endif
