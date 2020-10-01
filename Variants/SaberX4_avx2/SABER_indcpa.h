#ifndef INDCPA_H
#define INDCPA_H

#include <immintrin.h>
#include"cpucycles.h"
#include"poly.h"
uint64_t clock_S, clock_E;
uint64_t clock_BS2POLVEC_S, clock_BS2POLVEC_E;
uint64_t clock_inBS2POLq, clock_outBS2POLq; 
uint64_t clock_before_temp_loop,clock_after_temp_loop,clock_before_shift,clock_after_shift,clock_after_store,clock_before_store;
uint64_t clock_bs2polqS, clock_bs2polqE, clock_bs2polq;

uint64_t clock_samp, clock_arith, clock_load;

//void indcpa_keypair(unsigned char *pk, unsigned char *sk);
void indcpa_keypair(unsigned char *pk0, unsigned char *sk0,
					unsigned char *pk1, unsigned char *sk1,
					unsigned char *pk2, unsigned char *sk2,
					unsigned char *pk3, unsigned char *sk3,
					unsigned char seed_arr[4][SABER_SEEDBYTES], unsigned char noiseseed_arr[4][SABER_COINBYTES]);

//void GenMatrix(polyvecNew *a, const unsigned char *seed);
void GenMatrix(polyvec *a, const unsigned char *seed);

void GenMatrix4x(polyvecNew *a0, polyvecNew *a1, polyvecNew *a2, polyvecNew *a3,  
				const unsigned char *seed0, const unsigned char *seed1,
				const unsigned char *seed2, const unsigned char *seed3);

void indcpa_client(unsigned char *pk, unsigned char *b_prime, unsigned char *c, unsigned char *key);

void indcpa_server(unsigned char *pk, unsigned char *b_prime, unsigned char *c, unsigned char *key);

void indcpa_kem_keypair(unsigned char *pk0, unsigned char *sk0,
						unsigned char *pk1, unsigned char *sk1,
						unsigned char *pk2, unsigned char *sk2,
						unsigned char *pk3, unsigned char *sk3,
						unsigned char seed_arr[4][SABER_SEEDBYTES], unsigned char noiseseed_arr[4][SABER_COINBYTES]);

//void indcpa_kem_enc(unsigned char *message, unsigned char *noiseseed, const unsigned char *pk, unsigned char *ciphertext);

void indcpa_kem_enc(unsigned char *m0, unsigned char *m1, unsigned char *m2, unsigned char *m3,
				    unsigned char *noiseseed0, unsigned char *noiseseed1, 
					unsigned char *noiseseed2, unsigned char *noiseseed3,
					const unsigned char *pk0, unsigned char *c0,
					const unsigned char *pk1, unsigned char *c1,
					const unsigned char *pk2, unsigned char *c2,
					const unsigned char *pk3, unsigned char *c3);


//void indcpa_kem_dec(const unsigned char *sk, const unsigned char *ciphertext, unsigned char *message_dec);

void indcpa_kem_dec(
					const unsigned char *sk0, const unsigned char *ciphertext0, unsigned char *message0_dec,
					const unsigned char *sk1, const unsigned char *ciphertext1, unsigned char *message1_dec,
					const unsigned char *sk2, const unsigned char *ciphertext2, unsigned char *message2_dec,
					const unsigned char *sk3, const unsigned char *ciphertext3, unsigned char *message3_dec);

uint64_t clock1,clock2;

__m256i mask,inv3_avx,inv9_avx,inv15_avx,int45_avx,int30_avx,int0_avx;

__m256i avx_epi64_01, avx_epi64_03, avx_epi64_07, avx_epi64_0f, avx_epi64_1f, avx_epi64_3f, avx_epi64_7f, avx_epi64_ff;
__m256i avx_epi32_01, avx_epi32_03, avx_epi32_07, avx_epi32_0f, avx_epi32_1f, avx_epi32_3f, avx_epi32_7f, avx_epi32_ff;

#endif

