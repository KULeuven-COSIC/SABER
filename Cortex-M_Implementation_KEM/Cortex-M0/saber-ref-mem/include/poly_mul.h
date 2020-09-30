#include "SABER_params.h"

void pol_mul(uint16_t* a, uint16_t* b, uint16_t* res);

extern void school_book_mul2_16(const uint16_t* a, const uint16_t* b, uint16_t *c);

extern void unrolled_kara_mem(const uint16_t * a, const uint16_t * c, uint16_t * d, const uint16_t k);
