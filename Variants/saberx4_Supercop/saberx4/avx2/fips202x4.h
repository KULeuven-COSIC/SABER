#ifndef FIPS202X4_H
#define FIPS202X4_H

#include <stdint.h>
#include <immintrin.h>

typedef struct {
  __m256i s[25];
} keccak4x_state;


void shake128x4_squeezeblocks(unsigned char *out0,
                              unsigned char *out1,
                              unsigned char *out2,
                              unsigned char *out3,
                              unsigned long long nblocks,
                              keccak4x_state *state);


void shake256x4(unsigned char *out0,
                       unsigned char *out1,
                       unsigned char *out2,
                       unsigned char *out3, unsigned long long outlen,
                       const unsigned char *in0,
                       const unsigned char *in1,
                       const unsigned char *in2,
                       const unsigned char *in3, unsigned long long inlen);

void shake128x4(unsigned char *out0,
                       unsigned char *out1,
                       unsigned char *out2,
                       unsigned char *out3, unsigned long long outlen,
                       const unsigned char *in0,
                       const unsigned char *in1,
                       const unsigned char *in2,
                       const unsigned char *in3, unsigned long long inlen);

void sha3_512x4(unsigned char *out0,
                unsigned char *out1,
                unsigned char *out2,
                unsigned char *out3, 
                const unsigned char *in0,
                const unsigned char *in1,
                const unsigned char *in2,
                const unsigned char *in3, 
				unsigned long long inlen);

void sha3_256x4(unsigned char *out0,
                unsigned char *out1,
                unsigned char *out2,
                unsigned char *out3, 
                const unsigned char *in0,
                const unsigned char *in1,
                const unsigned char *in2,
                const unsigned char *in3, 
				unsigned long long inlen);


#endif
