#ifndef POLYMUL_H
#define POLYMUL_H

#include "SABER_params.h"

extern void toom_cook_4way_striding_asm(uint16_t a[SABER_N], uint16_t b[SABER_N], uint16_t res[SABER_N]);
extern void kara_strd_mem_asm(uint16_t a[64], uint16_t b[64], uint16_t res[64], uint16_t extra_mem[64]);

void poly_mul(uint16_t a[SABER_N], uint16_t b[SABER_N], uint16_t res[SABER_N]);
void poly_mul_acc(uint16_t a[SABER_N], uint16_t b[SABER_N], uint16_t res[SABER_N]);

#endif
