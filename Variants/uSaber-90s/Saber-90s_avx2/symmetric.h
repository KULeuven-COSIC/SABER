#ifndef SYMMETRIC_H
#define SYMMETRIC_H

#include "SABER_params.h"

void saber_aes256ctr_prf(unsigned char *output, unsigned long long outlen, const unsigned char *input);

#ifdef Saber90s

    #include <openssl/sha.h>

    #define hash_h(OUT, IN, INBYTES) SHA256(IN, INBYTES, OUT)
    #define hash_g(OUT, IN, INBYTES) SHA512(IN, INBYTES, OUT)

	#define prf(OUT, OUTLEN, IN, INLEN) saber_aes256ctr_prf(OUT, OUTLEN, IN)

#else

    #include "fips202.h"

    #define hash_h(OUT, IN, INBYTES) sha3_256(OUT, IN, INBYTES)
    #define hash_g(OUT, IN, INBYTES) sha3_512(OUT, IN, INBYTES)

    #define prf(OUT, OUTLEN, IN, INLEN) shake128(OUT, OUTLEN, IN, INLEN)

#endif

#endif
