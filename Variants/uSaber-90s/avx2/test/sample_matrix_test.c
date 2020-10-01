#include "../poly.h"
#include "../rng.h"
#include "../SABER_indcpa.h"
#include "../kem.h"
#include "../cpucycles.c"
#include "../verify.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>
#include <string.h>



int test_kem_cca()
{

  unsigned char seed[SABER_SEEDBYTES];
  polyvec a[SABER_K];
	
	
  uint64_t i, repeat;
  repeat=100000;

  uint64_t CLOCK1,CLOCK2;
  uint64_t CLOCK_kp,CLOCK_enc,CLOCK_dec;

  	CLOCK1 = 0;
        CLOCK2 = 0;
	CLOCK_kp = CLOCK_enc = CLOCK_dec = 0;

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
	    CLOCK_dec=CLOCK_dec+(CLOCK2-CLOCK1);	
  
 		
  	}

	printf("Repeat is : %ld\n",repeat);
	printf("Average times full sample_matrix: \t %lu \n",CLOCK_kp/repeat);
	printf("Average times partial sample_matrix: \t %lu \n",CLOCK_enc/repeat);
	printf("Average times schwabe sample_matrix: \t %lu \n",CLOCK_dec/repeat);


  	return 0;
}



int main()
{

	test_kem_cca();
	return 0;
}
