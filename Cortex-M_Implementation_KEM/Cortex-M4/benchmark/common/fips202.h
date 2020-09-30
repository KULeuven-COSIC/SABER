#ifndef FIPS202_H
#define FIPS202_H

#include <stdint.h>
#include <stddef.h>

#define SHAKE128_RATE 168
#define SHAKE256_RATE 136
#define SHA3_256_RATE 136
#define SHA3_512_RATE  72

void shake128_absorb(uint64_t *s, const unsigned char *input, unsigned int inputByteLen);
void shake128_squeezeblocks(unsigned char *output, unsigned long long nblocks, uint64_t *s);
void shake128(unsigned char *output, unsigned long long outlen, const unsigned char *input, unsigned long long inlen);

void shake128_inc_init(uint64_t *s_inc);
void shake128_inc_absorb(uint64_t *s_inc, const uint8_t *input, size_t inlen);
void shake128_inc_finalize(uint64_t *s_inc);
void shake128_inc_squeeze(uint8_t *output, size_t outlen, uint64_t *s_inc);

void cshake128_simple_absorb(uint64_t *s, uint16_t cstm, const unsigned char *in, unsigned long long inlen);
void cshake128_simple_squeezeblocks(unsigned char *output, unsigned long long nblocks, uint64_t *s);
void cshake128_simple(unsigned char *output, unsigned long long outlen, uint16_t cstm, const unsigned char *in, unsigned long long inlen);

void shake256_absorb(uint64_t *s, const unsigned char *input, unsigned int inputByteLen);
void shake256_squeezeblocks(unsigned char *output, unsigned long long nblocks, uint64_t *s);
void shake256(unsigned char *output, unsigned long long outlen, const unsigned char *input, unsigned long long inlen);

void shake256_inc_init(uint64_t *s_inc);
void shake256_inc_absorb(uint64_t *s_inc, const uint8_t *input, size_t inlen);
void shake256_inc_finalize(uint64_t *s_inc);
void shake256_inc_squeeze(uint8_t *output, size_t outlen, uint64_t *s_inc);

void cshake256_simple_absorb(uint64_t *s, uint16_t cstm, const unsigned char *in, unsigned long long inlen);
void cshake256_simple_squeezeblocks(unsigned char *output, unsigned long long nblocks, uint64_t *s);
void cshake256_simple(unsigned char *output, unsigned long long outlen, uint16_t cstm, const unsigned char *in, unsigned long long inlen);

void sha3_256_inc_init(uint64_t *s_inc);
void sha3_256_inc_absorb(uint64_t *s_inc, const uint8_t *input, size_t inlen);
void sha3_256_inc_finalize(uint8_t *output, uint64_t *s_inc);

void sha3_256(unsigned char *output, const unsigned char *input, unsigned long long inlen);

void sha3_512_inc_init(uint64_t *s_inc);
void sha3_512_inc_absorb(uint64_t *s_inc, const uint8_t *input, size_t inlen);
void sha3_512_inc_finalize(uint8_t *output, uint64_t *s_inc);

void sha3_512(unsigned char *output, const unsigned char *input, unsigned long long inlen);


#endif
