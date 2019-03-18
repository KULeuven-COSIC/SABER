#include "../SABER_indcpa.h"
#include "../kem.h"
#include "../api.h"
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
extern int crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);
extern int crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);

/*
uint64_t test_poly_mul()
{

	__m256i a_avx[16], b_avx[16], c_avx[16];
	__m256i mask_load;
	uint16_t c_ar[256];
	
	int i, j;
	uint16_t temp[16];
	uint64_t pmod = 8192;
	uint64_t repeat = 100000;
	uint64_t COUNT;
	uint64_t garbage=0;

  	uint64_t CLOCK1,CLOCK2,CLOCK3;
	CLOCK3 = 0;

	uint64_t mask_ar[4];
 	mask_ar[0]=~(0UL);mask_ar[1]=~(0UL);mask_ar[2]=~(0UL);mask_ar[3]=~(0UL);
        mask_load = _mm256_loadu_si256 ((__m256i const *)mask_ar);

	for(COUNT=0; COUNT<repeat; COUNT ++)
	{
		// random a_avx
		for(i=0; i<16; i++)
		{	
			for(j=0; j<16; j++)
			{
				temp[j] = rand() & 0x1fff;
			}
			a_avx[i] = _mm256_loadu_si256 ((__m256i const *) (&temp));	

			for(j=0; j<16; j++)
			{
				temp[j] = rand() & 0x1fff;
			}
			b_avx[i] = _mm256_loadu_si256 ((__m256i const *) (&temp));				
		}

		CLOCK1 = cpucycles();		
		toom_cook_4way_avx(a_avx, b_avx, pmod, c_avx);
		CLOCK2 = cpucycles();		
		CLOCK3 = CLOCK3 + CLOCK2 - CLOCK1;
		
		for(i=0; i<16; i++)
		_mm256_maskstore_epi32 ((int *)(c_ar+i*16), mask_load, c_avx[i]);

		for(i=0; i<256; i++)
		garbage = garbage + c_ar[i];
	}
	printf("Repeat is : %ld\n",repeat);
	printf("Average time for Toom-Cook multiplication: \t %lu \n",CLOCK3/repeat);

	return(garbage);
}

uint64_t test_poly_sampling()
{

	unsigned char noiseseed[SABER_COINBYTES];
  	uint64_t CLOCK1,CLOCK2,CLOCK3;
	CLOCK3 = 0;
	uint16_t skpv1[SABER_K][SABER_N];

	int i;

	uint64_t COUNT;
	uint64_t garbage=0;
	uint64_t repeat=100000;

	for(COUNT=0; COUNT<repeat; COUNT++)
	{
		
		for(i=0; i<SABER_COINBYTES; i++)
			noiseseed[i] = rand() & 0xff;

		CLOCK1 = cpucycles();		
		poly_getnoise4x(skpv1[0], skpv1[1], skpv1[2], noiseseed, 0x0001, 0x0002, 0x0003, 0x0004);
		CLOCK2 = cpucycles();		
		CLOCK3 = CLOCK3 + CLOCK2 - CLOCK1;

		for(i=0; i<256; i++)
		garbage = garbage + skpv1[0][i] + skpv1[1][i] + skpv1[2][i];

	}
	printf("Repeat is : %ld\n",repeat);
	printf("Average time for 3x polynomial sampling: \t %lu \n",CLOCK3/repeat);

	return(garbage);
}

int test_sample_matrix()
{

  unsigned char seed[SABER_SEEDBYTES];
  polyvec a[SABER_K];
	
	
  uint64_t i, repeat;
  repeat=1000000;

  uint64_t CLOCK1, CLOCK2, CLOCK3;

  	CLOCK3 = 0;

	time_t t;
   	// Intializes random number generator
   	srand((unsigned) time(&t));

  	for(i=0; i<repeat; i++)
  	{
	    //printf("i : %lu\n",i);

  	    randombytes(seed, SABER_SEEDBYTES);

	    //Generation of secret key sk and public key pk pair
	    CLOCK1=cpucycles();	
	    GenMatrix(a, seed); //sample matrix A
	    CLOCK2=cpucycles();	
	    CLOCK3=CLOCK3+(CLOCK2-CLOCK1);	
  
 		
  	}

	printf("Repeat is : %ld\n",repeat);
	printf("Average times full sample_matrix: \t %lu \n",CLOCK3/repeat);

  	return 0;
}
*/


int test_kem_cca()
{


  uint8_t pk[SABER_PUBLICKEYBYTES];
  uint8_t sk[SABER_SECRETKEYBYTES];
  uint8_t c[SABER_BYTES_CCA_DEC];	
  uint8_t k_a[SABER_KEYBYTES], k_b[SABER_KEYBYTES];
	
  unsigned char entropy_input[48];
	
  uint64_t i, j, repeat;
  repeat=4000000;
  //repeat = 1;

  uint64_t CLOCK1,CLOCK2;
  uint64_t CLOCK_kp,CLOCK_enc,CLOCK_dec;

  	CLOCK1 = 0;
        CLOCK2 = 0;
	CLOCK_kp = CLOCK_enc = CLOCK_dec = 0;
        clock_arith = clock_samp = clock_load = 0;

	time_t t;
   	// Intializes random number generator
   	srand((unsigned) time(&t));

    	for (i=0; i<48; i++){
        	entropy_input[i] = i;
        	//entropy_input[i] = rand()%256;
	}
    	randombytes_init(entropy_input, NULL, 256);


  	for(i=0; i<repeat; i++)
  	{
	    //printf("i : %lu\n",i);

	    //Generation of secret key sk and public key pk pair
	    CLOCK1=cpucycles();	
	    crypto_kem_keypair(pk, sk);
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
	    for(j=0; j<SABER_KEYBYTES; j++)
	    {
		//printf("%u \t %u\n", k_a[j], k_b[j]);
		if(k_a[j] != k_b[j])
		{
			printf("----- ERR CCA KEM ------\n");
			return 0;		
			break;
		}
	    }
   		
  	}
	
	
	printf("Repeat is : %ld\n",repeat);
	printf("Average times key_pair: \t %lu \n",CLOCK_kp/repeat);

	printf("Average times enc: \t %lu \n",CLOCK_enc/repeat);
	printf("Average times dec: \t %lu \n",CLOCK_dec/repeat);
	printf("Average time sample_matrix: \t %lu \n",clock_matrix/repeat);
	printf("Average times sample_secret: \t %lu \n",clock_secret/repeat);
	printf("Average times polynomial mul: \t %lu \n",clock_mul/(3*repeat));
	printf("Average times polynomial mul: \t %lu \n",clock_mul/(3*count_mul));
	printf("Number of times polynomial mul: \t %lu \n",count_mul);


  	return 0;
}



int main()
{

	//test_poly_mul();
	//test_poly_sampling();
	//test_sample_matrix();
	test_kem_cca();
	return 0;
}
