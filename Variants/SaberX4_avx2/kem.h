#ifndef INDCPA_H
#define INDCPA_H

int crypto_kem_keypair(unsigned char *pk, unsigned char *sk);
int crypto_kem_enc(unsigned char *c, unsigned char *k, const unsigned char *pk);
int crypto_kem_dec(unsigned char *k, const unsigned char *c, const unsigned char *sk);

uint64_t clock1,clock2;
uint64_t clock_kp_mv,clock_cl_mv, clock_kp_sm, clock_cl_sm;


#endif

