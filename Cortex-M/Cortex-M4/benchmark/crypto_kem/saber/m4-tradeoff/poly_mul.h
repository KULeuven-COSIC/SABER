#include "SABER_params.h"

void pol_mul(uint16_t* a, uint16_t* b, uint16_t* res, uint16_t p, uint32_t n);

//void toom_cook_4way_mem(const uint16_t* a1,const uint16_t* b1, uint16_t* result_final);
#define toom_cook_4way_mem toom_cook_4way_mem_asm

//void karatsuba_unroll(const uint16_t *a, const uint16_t *b, uint16_t *result);
#define karatsuba_unroll karatsuba_asm

extern void toom_cook_4way_mem_asm(const uint16_t* a1,const uint16_t* b1, uint16_t* result);

extern void karatsuba_asm(const uint16_t *a, const uint16_t *b, uint16_t *result);
