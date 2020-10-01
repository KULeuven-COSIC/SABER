#include "../SABER_indcpa.h"
#include "../kem.h"
#include "../apiorig.h"
#include "../poly.h"
//#include "../randombytes.h"
#include "../rng.h"

#include "../cpucycles.c"
#include "../verify.h"

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<time.h>
#include<immintrin.h>
#include<string.h>


extern int crypto_kem_keypair(unsigned char *pk, unsigned char *sk);

extern int crypto_kem_enc(unsigned char *c, unsigned char *k, const unsigned char *pk);

extern int crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);

int test_kem_cca()
{


  uint8_t pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES];
	uint8_t c[CRYPTO_CIPHERTEXTBYTES];
	uint8_t k_a[CRYPTO_BYTES], k_b[CRYPTO_BYTES];
	
  unsigned char entropy_input[48];
	
  uint64_t i, j, repeat;
  repeat=100000;

  uint64_t CLOCK1,CLOCK2;
  uint64_t CLOCK_kp,CLOCK_enc,CLOCK_dec;

  CLOCK1 = 0;
  CLOCK2 = 0;
	CLOCK_kp = CLOCK_enc = CLOCK_dec = 0;

	time_t t;
   	// Intializes random number generator
   	srand((unsigned) time(&t));

    	for (i=0; i<48; i++){
        	entropy_input[i] = i;
	}
    	randombytes_init(entropy_input, NULL, 256);


		// Each operation batches 4 kegen, 4 encaps, and 4 decaps. The session key is a string of 4 keys appended one after another.
  	for(i=0; i<repeat; i++)
  	{
	    //printf("i : %lu\n",i);

	    //Generation of secret key sk and public key pk pair
	    CLOCK1=cpucycles();	
	    crypto_kem_keypair(pk,sk);
	    CLOCK2=cpucycles();	
	    CLOCK_kp=CLOCK_kp+(CLOCK2-CLOCK1);	
	
	    //Key-Encapsulation call; input: pk; output: ciphertext c, shared-secret k_a;	
	    CLOCK1=cpucycles();
			crypto_kem_enc(c, k_a, pk);


	    CLOCK2=cpucycles();	
	    CLOCK_enc=CLOCK_enc+(CLOCK2-CLOCK1);	

	
	    //Key-Decapsulation call; input: sk, c; output: shared-secret k_b;	
	    CLOCK1=cpucycles();
			crypto_kem_dec(k_b, c, sk);

	    CLOCK2=cpucycles();	
	    CLOCK_dec=CLOCK_dec+(CLOCK2-CLOCK1);	
  
			
	    		
	    // Functional verification: check if k_a == k_b?
	    for(j=0; j<CRYPTO_BYTES; j++)
	    {

				if(k_a[j] != k_b[j])
				{
					printf("----- ERR CCA KEM0 ------\n");
					return 0;		
					break;
				}
	    }
   		
  	}
	
	
	printf("Repeat is : %ld\n",repeat);
	printf("Average times key_pair: \t %lu \n",CLOCK_kp/repeat);
	printf("Average times enc: \t %lu \n",CLOCK_enc/repeat);
	printf("Average times dec: \t %lu \n",CLOCK_dec/repeat);


	return 0;
}



int main()
{

	test_kem_cca();
	return 0;
}
