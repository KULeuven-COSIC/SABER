#ifndef SYMMETRIC_H
#define SYMMETRIC_H

#include "SABER_params.h"

#ifdef Saber90s

    #include <openssl/sha.h>
	#include "crypto_stream.h"

    #define hash_h(OUT, IN, INBYTES) SHA256(IN, INBYTES, OUT)
    #define hash_g(OUT, IN, INBYTES) SHA512(IN, INBYTES, OUT)

	#define prf(OUT, OUTLEN, IN, INLEN) crypto_stream_aes256ctr(OUT, OUTLEN, IN, IN)

#else

    #include "fips202.h"

    #define hash_h(OUT, IN, INBYTES) sha3_256(OUT, IN, INBYTES)
    #define hash_g(OUT, IN, INBYTES) sha3_512(OUT, IN, INBYTES)

    #define prf(OUT, OUTLEN, IN, INLEN) shake128(OUT, OUTLEN, IN, INLEN)

#endif

#endif
