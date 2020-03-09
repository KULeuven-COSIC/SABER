/*---------------------------------------------------------------------
This file has been adapted from the implementation 
(available at, Public Domain https://github.com/pq-crystals/kyber) 
of "CRYSTALS – Kyber: a CCA-secure module-lattice-based KEM"
by : Joppe Bos, Leo Ducas, Eike Kiltz, Tancrede Lepoint, 
Vadim Lyubashevsky, John M. Schanck, Peter Schwabe & Damien stehle
----------------------------------------------------------------------*/
#include <stdio.h>
#include "api.h"
#include "poly.h"
#include "cbd.h"
#include "fips202.h"


/*
void GenSecret(uint16_t r[SABER_K][SABER_N],const unsigned char *seed){


		uint32_t i;

		uint8_t buf[SABER_NOISEBUFSIZE];//SABER_MU*SABER_N*SABER_K/8

		shake128(buf, SABER_NOISEBUFSIZE, seed,SABER_NOISESEEDBYTES);

		for(i=0;i<SABER_K;i++)
		{
			cbd(r[i],buf+i*SABER_MU*SABER_N/8);
		}
}
*/

void GenSecret(uint16_t r[SABER_K][SABER_N],const unsigned char *seed){

  		unsigned char shake_op_buf[SHAKE128_RATE+80];
		uint32_t i;


		//shake128(buf, buf_size, seed,SABER_NOISESEEDBYTES);


  		uint64_t s[25];
  

	  	for (i = 0; i < 25; ++i)
		    s[i] = 0;
  
  		keccak_absorb(s, SHAKE128_RATE, seed, SABER_SEEDBYTES, 0x1F);
		

		/////////////////////////////////////////////////
		// construction of first secret polynomial

		keccak_squeezeblocks(shake_op_buf, 1, s, SHAKE128_RATE);
		cbd(0, r[0], SHAKE128_RATE, shake_op_buf);			// consume all SHAKE_op bytes to construct first SHAKE128_RATE coefficients of r[0] 
			
		keccak_squeezeblocks(shake_op_buf, 1, s, SHAKE128_RATE);
		cbd(SHAKE128_RATE, r[0], 88, shake_op_buf);			// consume first 88 op bytes to construct remaining coefficients of r[0]  
				
		for(i=88; i<SHAKE128_RATE; i++)
		shake_op_buf[i-88] = shake_op_buf[i];


		/////////////////////////////////////////////////
		// construction of second secret polynomial

		keccak_squeezeblocks(shake_op_buf+80, 1, s, SHAKE128_RATE);
		cbd(0, r[1], 248, shake_op_buf);				// first 248 coeffs of r[1] 
				
		keccak_squeezeblocks(shake_op_buf, 1, s, SHAKE128_RATE);
		cbd(248, r[1], 8, shake_op_buf);				// next 8 coeffs of r[1] 

		for(i=8; i<SHAKE128_RATE; i++)
		shake_op_buf[i-8] = shake_op_buf[i];

		/////////////////////////////////////////////////
		// construction of third secret polynomial

		cbd(0, r[2], 160, shake_op_buf);				// first 248 coeffs of r[1] 

		keccak_squeezeblocks(shake_op_buf, 1, s, SHAKE128_RATE);
		cbd(160, r[2], 96, shake_op_buf);				// first 248 coeffs of r[1] 
}

