#include <stdint.h>
#include "poly_mul.h"
#include <string.h>

void poly_mul(uint16_t a[SABER_N], uint16_t b[SABER_N], uint16_t res[SABER_N])
{
    // uint32_t i;
    // uint16_t c[2*SABER_N - 1];

    // polymul_asm(c, a, b);

    // for (i = SABER_N; i < 2*SABER_N-1; i++){
    //     res[i - SABER_N] = (c[i - SABER_N] - c[i]);
    // }
    // res[SABER_N - 1] = c[SABER_N - 1];

    memset(res, 0, 2*SABER_N);
    toom_cook_4way_mem_asm(a, b, res);
}

void poly_mul_acc(uint16_t a[SABER_N], uint16_t b[SABER_N], uint16_t res[SABER_N])
{
    // uint32_t i;
    // uint16_t c[2*SABER_N - 1];

    // polymul_asm(c, a, b);

    // for (i = SABER_N; i < 2*SABER_N-1; i++){
    //     res[i - SABER_N] += (c[i - SABER_N] - c[i]);
    // }
    // res[SABER_N - 1] += c[SABER_N - 1];

    toom_cook_4way_mem_asm(a, b, res);
}