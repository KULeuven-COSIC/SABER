#include "SABER_indcpa.h"
#include "randombytes.h"
#include "fips202.h"
#include "poly.h"
#include <string.h>
#include <stdlib.h>

void indcpa_kem_keypair(uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES], uint8_t sk[SABER_INDCPA_SECRETKEYBYTES])
{
    uint8_t *seed_A = pk + SABER_POLYVECCOMPRESSEDBYTES; // pk[1] <- seed_A
    uint8_t *seed_s = sk; // temporary storage

    randombytes(seed_A, SABER_SEEDBYTES);
    randombytes(seed_s, SABER_NOISE_SEEDBYTES);
    shake128(seed_A, SABER_SEEDBYTES, seed_A, SABER_SEEDBYTES); // for not revealing system RNG state

    MatrixVectorMulKeyPair(pk, sk); // pk[0] <- Pack(Round((A^T)*s)), sk <- s
}


void indcpa_kem_enc(const uint8_t m[SABER_KEYBYTES], const uint8_t seed_sp[SABER_NOISE_SEEDBYTES], const uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES], uint8_t ciphertext[SABER_BYTES_CCA_DEC])
{
    const uint8_t *seed_A = pk + SABER_POLYVECCOMPRESSEDBYTES;
    uint8_t *ct0 = ciphertext;
    uint8_t *ct1 = ciphertext + SABER_POLYVECCOMPRESSEDBYTES;
    uint16_t sp[SABER_L][SABER_N];
    
    GenSecret(sp, (uint8_t *)seed_sp, 0);
    MatrixVectorMulEnc(ct0, seed_A, sp, 0); // ct[0] <- Pack(Round(A*s'))
    InnerProdEnc(ct1, pk, sp, m, 0); // ct[1] <- Pack(Round(b*s' + m'))
}

uint8_t indcpa_kem_enc_cmp(const uint8_t m[SABER_KEYBYTES], const uint8_t seed_sp[SABER_NOISE_SEEDBYTES], const uint8_t pk[SABER_INDCPA_PUBLICKEYBYTES], const uint8_t ciphertext[SABER_BYTES_CCA_DEC])
{
    uint32_t fail = 0;
    const uint8_t *seed_A = pk + SABER_POLYVECCOMPRESSEDBYTES;
    const uint8_t *ct0 = ciphertext;
    const uint8_t *ct1 = ciphertext + SABER_POLYVECCOMPRESSEDBYTES;
    uint16_t sp[SABER_L][SABER_N];

    GenSecret(sp, (uint8_t *)seed_sp, 0);
    fail |= MatrixVectorMulEnc((uint8_t *)ct0, seed_A, sp, 1); // verify(ct[0], Pack(Round(A*s')))
    fail |= InnerProdEnc((uint8_t *)ct1, pk, sp, m, 1); // verify(ct[1], Pack(Round(b*s' + m')))
    fail = (~fail + 1);
    fail >>= 31;

    return (uint8_t)fail;
}

void indcpa_kem_dec(const uint8_t sk[SABER_INDCPA_SECRETKEYBYTES], const uint8_t ciphertext[SABER_BYTES_CCA_DEC], uint8_t m[SABER_KEYBYTES])
{
    InnerProdDec(m, ciphertext, sk); // m <- Pack(Round(b'*s - cm))
}