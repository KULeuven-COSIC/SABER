#ifndef API_H
#define API_H

#include "SABER_params.h"

#ifdef uSaber
	#define SABER_PREFIX "u"
#else
	#define SABER_PREFIX ""
#endif

#if SABER_L == 2
	#define SABER_VARIANT "LightSaber"
#elif SABER_L == 3
	#define SABER_VARIANT "Saber"
#elif SABER_L == 4
	#define SABER_VARIANT "FireSaber"
#endif

#ifdef Saber90s
	#define SABER_POSTFIX "-90s"
#else
	#define SABER_POSTFIX ""
#endif

#define CRYPTO_ALGNAME SABER_PREFIX SABER_VARIANT SABER_POSTFIX
#define CRYPTO_SECRETKEYBYTES SABER_SECRETKEYBYTES
#define CRYPTO_PUBLICKEYBYTES SABER_PUBLICKEYBYTES
#define CRYPTO_BYTES SABER_KEYBYTES
#define CRYPTO_CIPHERTEXTBYTES SABER_BYTES_CCA_DEC

int crypto_kem_keypair(unsigned char *pk, unsigned char *sk);
int crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);
int crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);

#endif /* api_h */
