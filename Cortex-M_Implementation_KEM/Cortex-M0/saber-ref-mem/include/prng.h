#ifndef PRNG_H
#define PRNG_H

#include <stdint.h>

void rng_enable(void);

void randombytes(unsigned char *x,unsigned long long xlen);

#endif /* PRNG_H */