#include <immintrin.h>
#include "SABER_params.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "SABER_indcpa.h"
#include "crypto_kem.h"
#include "kem.h"
#include "verify.h"
#include "randombytes.h"
#include "fips202.h"
#include "fips202x4.h"
#include "kem4x.c"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int crypto_kem_keypair(unsigned char *pk, unsigned char *sk)
{
	uint8_t *pk0=pk;
	uint8_t *sk0=sk;
	uint8_t *pk1=pk+(CRYPTO_PUBLICKEYBYTES/4);
	uint8_t *sk1=sk+(CRYPTO_SECRETKEYBYTES/4);
	uint8_t *pk2=pk+2*(CRYPTO_PUBLICKEYBYTES/4);
	uint8_t *sk2=sk+2*(CRYPTO_SECRETKEYBYTES/4);
	uint8_t *pk3=pk+3*(CRYPTO_PUBLICKEYBYTES/4);
	uint8_t *sk3=sk+3*(CRYPTO_SECRETKEYBYTES/4);

	crypto_kem_keypair4x(pk0,sk0, pk1,sk1, pk2,sk2, pk3,sk3);

	return(0);
}


int crypto_kem_enc(unsigned char *c, unsigned char *k, const unsigned char *pk)
{
	uint8_t *c0=c;
	uint8_t *k0=k;
	const uint8_t *pk0=pk;

	uint8_t *c1=c+(CRYPTO_CIPHERTEXTBYTES/4);
	uint8_t *k1=k+(CRYPTO_BYTES/4);
	const uint8_t *pk1=pk+(CRYPTO_PUBLICKEYBYTES/4);

	uint8_t *c2=c+2*(CRYPTO_CIPHERTEXTBYTES/4);
	uint8_t *k2=k+2*(CRYPTO_BYTES/4);
	const uint8_t *pk2=pk+2*(CRYPTO_PUBLICKEYBYTES/4);

	uint8_t *c3=c+3*(CRYPTO_CIPHERTEXTBYTES/4);
	uint8_t *k3=k+3*(CRYPTO_BYTES/4);
	const uint8_t *pk3=pk+3*(CRYPTO_PUBLICKEYBYTES/4);

	crypto_kem_enc4x(c0, k0, pk0, c1, k1, pk1, c2, k2, pk2, c3, k3, pk3);

	return(0);
}


int crypto_kem_dec(unsigned char *k, const unsigned char *c, const unsigned char *sk)
{
	uint8_t *k0=k;
	const uint8_t *c0=c;
	const uint8_t *sk0=sk;

	uint8_t *k1=k+(CRYPTO_BYTES/4);
	const uint8_t *c1=c+(CRYPTO_CIPHERTEXTBYTES/4);
	const uint8_t *sk1=sk+(CRYPTO_SECRETKEYBYTES/4);

	uint8_t *k2=k+2*(CRYPTO_BYTES/4);
	const uint8_t *c2=c+2*(CRYPTO_CIPHERTEXTBYTES/4);
	const uint8_t *sk2=sk+2*(CRYPTO_SECRETKEYBYTES/4);

	uint8_t *k3=k+3*(CRYPTO_BYTES/4);
	const uint8_t *c3=c+3*(CRYPTO_CIPHERTEXTBYTES/4);
	const uint8_t *sk3=sk+3*(CRYPTO_SECRETKEYBYTES/4);

	crypto_kem_dec4x(k0, c0, sk0, k1, c1, sk1, k2, c2, sk2, k3, c3, sk3);

	return(0);
}


