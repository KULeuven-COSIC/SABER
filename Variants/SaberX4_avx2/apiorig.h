//
//  api.h
//
//  Created by Bassham, Lawrence E (Fed) on 9/6/17.
//  Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
//


//   This is a sample 'api.h' for use 'sign.c'

#ifndef api_h
#define api_h

// Available algorithms for different security levels
#define Saber 2

#define CRYPTO_ALGNAME "SaberX4"

// Change the algorithm name 
#define SABER_TYPE Saber

//  Set these three values apropriately for your algorithm
#if SABER_TYPE == Saber
	#define CRYPTO_SECRETKEYBYTES 2304*4
	#define CRYPTO_PUBLICKEYBYTES (3*320+32)*4
	#define CRYPTO_CIPHERTEXTBYTES 1088*4
	#define CRYPTO_BYTES 32*4
	#define Saber_type 2
#endif


int crypto_kem_keypair(unsigned char *pk, unsigned char *sk);
int crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);
int crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);

#endif /* api_h */
