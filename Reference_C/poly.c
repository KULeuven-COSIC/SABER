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
#include "poly_mul.h"
#include "pack_unpack.h"
#include "cbd.h"
#include "fips202.h"

void MatrixVectorMul(polyvec *a, uint16_t skpv[SABER_K][SABER_N], uint16_t res[SABER_K][SABER_N], uint16_t mod, int16_t transpose){

	uint16_t acc[SABER_N]; 
	int32_t i,j,k;

	if(transpose==1){
		for(i=0;i<SABER_K;i++){
			for(j=0;j<SABER_K;j++){
				pol_mul((uint16_t *)&a[j].vec[i], skpv[j], acc, SABER_Q, SABER_N);			

				for(k=0;k<SABER_N;k++){
					res[i][k]=res[i][k]+acc[k];
					res[i][k]=(res[i][k]&mod); //reduction mod p
					acc[k]=0; //clear the accumulator
				}
			
			}
		}
	}
	else{

		for(i=0;i<SABER_K;i++){
			for(j=0;j<SABER_K;j++){
				pol_mul((uint16_t *)&a[i].vec[j], skpv[j], acc, SABER_Q, SABER_N);			
				for(k=0;k<SABER_N;k++){
					res[i][k]=res[i][k]+acc[k];
					res[i][k]=res[i][k]&mod; //reduction
					acc[k]=0; //clear the accumulator
				}
			
			}
		}
	}
				

}

void InnerProd(uint16_t pkcl[SABER_K][SABER_N],uint16_t skpv[SABER_K][SABER_N],uint16_t mod,uint16_t res[SABER_N]){


	uint32_t j,k;
	uint16_t acc[SABER_N]; 

	// vector-vector scalar multiplication with mod p
	for(j=0;j<SABER_K;j++){
		pol_mul(pkcl[j], skpv[j], acc , SABER_P, SABER_N);

			for(k=0;k<SABER_N;k++){
				res[k]=res[k]+acc[k];
				res[k]=res[k]&mod; //reduction
				acc[k]=0; //clear the accumulator
			}
	}




}

void GenMatrix(polyvec *a, const unsigned char *seed) 
{
  unsigned int one_vector=13*SABER_N/8;
  unsigned int byte_bank_length=SABER_K*SABER_K*one_vector;
  unsigned char buf[byte_bank_length];

  uint16_t temp_ar[SABER_N];

  int i,j,k;
  uint16_t mod = (SABER_Q-1);

  shake128(buf,byte_bank_length,seed,SABER_SEEDBYTES);
  
  for(i=0;i<SABER_K;i++)
  {
    for(j=0;j<SABER_K;j++)
    {
	BS2POL(buf+(i*SABER_K+j)*one_vector,temp_ar);
	for(k=0;k<SABER_N;k++){
		a[i].vec[j].coeffs[k] = (temp_ar[k])& mod ;
	}
    }
  }


}

void GenSecret(uint16_t r[SABER_K][SABER_N],const unsigned char *seed){


		uint32_t i;

		int32_t buf_size= SABER_MU*SABER_N*SABER_K/8;

		uint8_t buf[buf_size];

		shake128(buf, buf_size, seed,SABER_NOISE_SEEDBYTES);

		for(i=0;i<SABER_K;i++)
		{
			cbd(r[i],buf+i*SABER_MU*SABER_N/8);
		}
}
