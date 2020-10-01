#include <immintrin.h>
#include <string.h>
#include "SABER_params.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "SABER_indcpa.h"
#include "kem.h"
#include "verify.h"
#include "rng.h"
#include "fips202.h"
#include "symmetric.h"

int crypto_kem_keypair(unsigned char *pk, unsigned char *sk)
{
  uint64_t CLOCK1, CLOCK2;
  int i;

  CLOCK1=cpucycles(); 
  indcpa_kem_keypair(pk, sk);					      // sk[0:SABER_INDCPA_SECRETKEYBYTES-1] <-- sk
  CLOCK2=cpucycles(); 
  clock_kp_kex= clock_kp_kex + (CLOCK2-CLOCK1);

  CLOCK1=cpucycles(); 
  for(i=0;i<SABER_INDCPA_PUBLICKEYBYTES;i++)
    sk[i+SABER_INDCPA_SECRETKEYBYTES] = pk[i];			      // sk[SABER_INDCPA_SECRETKEYBYTES:SABER_INDCPA_SECRETKEYBYTES+SABER_INDCPA_SECRETKEYBYTES-1] <-- pk	
  //memcpy(sk+SABER_INDCPA_SECRETKEYBYTES, pk, SABER_INDCPA_PUBLICKEYBYTES);
  hash_h(sk+SABER_SECRETKEYBYTES-64, pk, SABER_INDCPA_PUBLICKEYBYTES);  // Then hash(pk) is appended.	

  randombytes(sk+SABER_SECRETKEYBYTES-SABER_KEYBYTES , SABER_KEYBYTES );    // Remaining part of sk contains a pseudo-random number. 
								      	    // This is output when check in crypto_kem_dec() fails. 
  CLOCK2=cpucycles(); 
  clock_kp_temp= clock_kp_temp + (CLOCK2-CLOCK1);

  return(0);	
}

int crypto_kem_enc(unsigned char *c, unsigned char *k, const unsigned char *pk)
{
  uint64_t CLOCK1, CLOCK2;
  unsigned char kr[64];                             	  // Will contain key, coins
  unsigned char buf[64];                          

  randombytes(buf, 32);

  hash_h(buf,buf,32);            			  // BUF[0:31] <-- random message (will be used as the key for client) Note: hash doesnot release system RNG output

  hash_h(buf+32, pk, SABER_INDCPA_PUBLICKEYBYTES);    // BUF[32:63] <-- Hash(public key);  Multitarget countermeasure for coins + contributory KEM 

  hash_g(kr, buf, 64);				// kr[0:63] <-- Hash(buf[0:63]);  	
							  								// K^ <-- kr[0:31]
							  								// noiseseed (r) <-- kr[32:63];	
  CLOCK1=cpucycles();
  indcpa_kem_enc(buf, kr+32, pk,  c);	// buf[0:31] contains message; kr[32:63] contains randomness r;
  CLOCK2=cpucycles();
  clock_enc_kex= clock_enc_kex + (CLOCK2-CLOCK1);

  hash_h(kr+32, c, SABER_BYTES_CCA_DEC);              

  hash_h(k, kr, 64);                          					// hash concatenation of pre-k and h(c) to k 
  return(0);	
}


int crypto_kem_dec(unsigned char *k, const unsigned char *c, const unsigned char *sk)
{
  int i, fail;
  unsigned char cmp[SABER_BYTES_CCA_DEC];
  unsigned char buf[64];
  unsigned char kr[64];                             // Will contain key, coins
  const unsigned char *pk = sk + SABER_INDCPA_SECRETKEYBYTES;

   indcpa_kem_dec(sk, c, buf);			     // buf[0:31] <-- message

 
  // Multitarget countermeasure for coins + contributory KEM 
  for(i=0;i<32;i++)                                  // Save hash by storing h(pk) in sk 
    buf[32+i] = sk[SABER_SECRETKEYBYTES-64+i]; 

  hash_g(kr, buf, 64);

  indcpa_kem_enc(buf, kr+32, pk, cmp);


  fail = verify(c, cmp, SABER_BYTES_CCA_DEC);

  hash_h(kr+32, c, SABER_BYTES_CCA_DEC);        		     // overwrite coins in kr with h(c)  

  cmov(kr, sk+SABER_SECRETKEYBYTES-SABER_KEYBYTES, SABER_KEYBYTES, fail); 

  hash_h(k, kr, 64);                          	   	     // hash concatenation of pre-k and h(c) to k

  return(0);	
}
