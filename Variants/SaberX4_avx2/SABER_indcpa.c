#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "SABER_indcpa.h"
#include "pack_unpack.h"
#include "cbd.h"
#include "SABER_params.h"
#include "./polymul/toom-cook_4way.c"
#include "rng.h"
#include "fips202.h"
#include "fips202x4.h"
#include <unistd.h>


#define h1 4 //2^(EQ-EP-1)

#define h2 ( (1<<(SABER_EP-2)) - (1<<(SABER_EP-SABER_ET-1)) + (1<<(SABER_EQ-SABER_EP-1)) )



uint64_t mask_ar[4]={0xFFFFFFFFUL,0xFFFFFFFFUL,0xFFFFFFFFUL,0xFFFFFFFFUL};
__m256i mask_load;
__m256i floor_round;
__m256i H1_avx;	
__m256i H2_avx;

/*--------------------------------------------------------------------------------------
	Andodo Add funtions & defintions
----------------------------------------------------------------------------------------*/
// __m256i avx_epi64_01, avx_epi64_03, avx_epi64_07, avx_epi64_0f, avx_epi64_1f, avx_epi64_3f, avx_epi64_7f, avx_epi64_ff;
// __m256i avx_epi32_01, avx_epi32_03, avx_epi32_07, avx_epi32_0f, avx_epi32_1f, avx_epi32_3f, avx_epi32_7f, avx_epi32_ff;


void init_aux_avx(){
	avx_epi64_01 = _mm256_set1_epi64x(0x01);
	avx_epi64_03 = _mm256_set1_epi64x(0x03);
	avx_epi64_07 = _mm256_set1_epi64x(0x07);
	avx_epi64_0f = _mm256_set1_epi64x(0x0f);
	avx_epi64_1f = _mm256_set1_epi64x(0x1f);
	avx_epi64_3f = _mm256_set1_epi64x(0x3f);
	avx_epi64_7f = _mm256_set1_epi64x(0x7f);
	avx_epi64_ff = _mm256_set1_epi64x(0xff);

	avx_epi32_01 = _mm256_set1_epi32(0x01);
	avx_epi32_03 = _mm256_set1_epi32(0x03);
	avx_epi32_07 = _mm256_set1_epi32(0x07);
	avx_epi32_0f = _mm256_set1_epi32(0x0f);
	avx_epi32_1f = _mm256_set1_epi32(0x1f);
	avx_epi32_3f = _mm256_set1_epi32(0x3f);
	avx_epi32_7f = _mm256_set1_epi32(0x7f);
	avx_epi32_ff = _mm256_set1_epi32(0xff);
}
/*--------------------------------------------------------------------------------------
	Andodo Add funtions & defintions
----------------------------------------------------------------------------------------*/

void POL2MSG(uint16_t *message_dec_unpacked, unsigned char *message_dec);

/*--------------------------------------------------------------------------------------
	This routine loads the constant values for Toom-Cook multiplication 
----------------------------------------------------------------------------------------*/
void load_values(){
	init_aux_avx();
	int64_t i;

	int64_t inv3=43691;
	int64_t inv9=36409;
	int64_t inv15=61167;

	int64_t int45=45;
	int64_t int30=30;
	int64_t int0=0;


	int16_t inv3_avx_load[16],inv9_avx_load[16],inv15_avx_load[16],int45_avx_load[16],int30_avx_load[16],int0_avx_load[16];

	for(i=0;i<16;i++){
		inv3_avx_load[i]=inv3;
		inv9_avx_load[i]=inv9;
		inv15_avx_load[i]=inv15;
		int45_avx_load[i]=int45;
		int30_avx_load[i]=int30;
		int0_avx_load[i]=int0;
	}

	inv3_avx = _mm256_loadu_si256 ((__m256i const *) (&inv3_avx_load));
	inv9_avx = _mm256_loadu_si256 ((__m256i const *) (&inv9_avx_load));
	inv15_avx = _mm256_loadu_si256 ((__m256i const *) (&inv15_avx_load));
	int45_avx = _mm256_loadu_si256 ((__m256i const *) (&int45_avx_load));
	int30_avx = _mm256_loadu_si256 ((__m256i const *) (&int30_avx_load));
	int0_avx = _mm256_loadu_si256 ((__m256i const *) (&int0_avx_load));
	mask = _mm256_loadu_si256 ((__m256i const *)mask_ar);	
}



/*-----------------------------------------------------------------------------------
	This routine generates a=[Matrix K x K] of 256-coefficient polynomials 
-------------------------------------------------------------------------------------*/

void BS2POLq(const unsigned char *bytes, uint16_t data[SABER_N]){
	
	uint32_t j;
	uint32_t offset_data=0,offset_byte=0;	
	
	offset_byte=0;

		for(j=0;j<SABER_N/8;j++){
			offset_byte=13*j;
			offset_data=8*j;
			data[offset_data + 0]= ( bytes[ offset_byte + 0 ] & (0xff)) | ((bytes[offset_byte + 1] & 0x1f)<<8);
			data[offset_data + 1]= ( bytes[ offset_byte + 1 ]>>5 & (0x07)) | ((bytes[offset_byte + 2] & 0xff)<<3) | ((bytes[offset_byte + 3] & 0x03)<<11);
			data[offset_data + 2]= ( bytes[ offset_byte + 3 ]>>2 & (0x3f)) | ((bytes[offset_byte + 4] & 0x7f)<<6);
			data[offset_data + 3]= ( bytes[ offset_byte + 4 ]>>7 & (0x01)) | ((bytes[offset_byte + 5] & 0xff)<<1) | ((bytes[offset_byte + 6] & 0x0f)<<9);
			data[offset_data + 4]= ( bytes[ offset_byte + 6 ]>>4 & (0x0f)) | ((bytes[offset_byte + 7] & 0xff)<<4) | ((bytes[offset_byte + 8] & 0x01)<<12);
			data[offset_data + 5]= ( bytes[ offset_byte + 8]>>1 & (0x7f)) | ((bytes[offset_byte + 9] & 0x3f)<<7);
			data[offset_data + 6]= ( bytes[ offset_byte + 9]>>6 & (0x03)) | ((bytes[offset_byte + 10] & 0xff)<<2) | ((bytes[offset_byte + 11] & 0x07)<<10);
			data[offset_data + 7]= ( bytes[ offset_byte + 11]>>3 & (0x1f)) | ((bytes[offset_byte + 12] & 0xff)<<5);
		}


}

void BS2POLq4x(unsigned char * bs0, unsigned char * bs1, unsigned char * bs2, unsigned char * bs3,
				__m256i data0[SABER_N/16], __m256i data1[SABER_N/16], __m256i data2[SABER_N/16], __m256i data3[SABER_N/16]){
	
	/*--------------------------------------------------------*/
	/*------------------Load to avx_bytes---------------------*/
	/*--------------------------------------------------------*/
	// int flag=1;
	// int flag0=1;
	// int flag1=1;
	//clock_S10 = cpucycles();

	const float * cfbs0 = (const float *)bs0;
	const float * cfbs1 = (const float *)bs1;
	const float * cfbs2 = (const float *)bs2;
	const float * cfbs3 = (const float *)bs3;

	const float * cfbs4, * cfbs5, * cfbs6, * cfbs7;
	
	__m128 l0,l1,l2,l3,l4,l5,l6,l7;
	__m128 l8,l9,l10,l11,l12,l13,l14,l15;
	__m256i l0_256,l1_256,l2_256,l3_256;
	__m256i avx_bytes[32*13/2];
	__m256i avx_data[256/2];
	

	cfbs4 = cfbs0+13*8/2;
	cfbs5 = cfbs1+13*8/2;
	cfbs6 = cfbs2+13*8/2;
	cfbs7 = cfbs3+13*8/2;
	int p=0;
	int i;
	
	//num/32   (32 8-bit) 
	for(i = 0;i<13;i++){
		//Load 128 bit from bs0, bs1, bs2, bs3
		l0 = _mm_load_ps(cfbs0+p*4); //0
		l1 = _mm_load_ps(cfbs1+p*4); //160
		l2 = _mm_load_ps(cfbs2+p*4); //64
		l3 = _mm_load_ps(cfbs3+p*4); //224
		
		//Load 128 bit from middle of bs0, bs1, bs2, bs3
		l4 = _mm_load_ps(cfbs4+p*4); //208
		l5 = _mm_load_ps(cfbs5+p*4); //112
		l6 = _mm_load_ps(cfbs6+p*4); //16
		l7 = _mm_load_ps(cfbs7+p*4); //176

		//Transpose 4x4 matrix
		_MM_TRANSPOSE4_PS(l0,l1,l2,l3);
		_MM_TRANSPOSE4_PS(l4,l5,l6,l7);

		//merge front half of vec(128-bit) and back half of vec(128-bit) = 256bit
		l0_256 = _mm256_insertf128_si256(_mm256_castsi128_si256((__m128i)l0),(__m128i)l4,1);
		l1_256 = _mm256_insertf128_si256(_mm256_castsi128_si256((__m128i)l1),(__m128i)l5,1);
		l2_256 = _mm256_insertf128_si256(_mm256_castsi128_si256((__m128i)l2),(__m128i)l6,1);
		l3_256 = _mm256_insertf128_si256(_mm256_castsi128_si256((__m128i)l3),(__m128i)l7,1);

		//extract avx[i] = load(bs0[i], bs1[i], bs2[i], bs3[i], bs0[i+128], bs1[i+128], bs2[i+128], bs3[i+128])
		avx_bytes[i*16+3] = _mm256_srli_epi32(l0_256,24);
		avx_bytes[i*16+2] = _mm256_srli_epi32(_mm256_slli_epi32(l0_256,8),24);
		avx_bytes[i*16+1] = _mm256_srli_epi32(_mm256_slli_epi32(l0_256,16),24);
		avx_bytes[i*16+0] = _mm256_srli_epi32(_mm256_slli_epi32(l0_256,24),24);

		avx_bytes[i*16+7] = _mm256_srli_epi32(l1_256,24);
		avx_bytes[i*16+6] = _mm256_srli_epi32(_mm256_slli_epi32(l1_256,8),24);
		avx_bytes[i*16+5] = _mm256_srli_epi32(_mm256_slli_epi32(l1_256,16),24);
		avx_bytes[i*16+4] = _mm256_srli_epi32(_mm256_slli_epi32(l1_256,24),24);

		avx_bytes[i*16+11] = _mm256_srli_epi32(l2_256,24);
		avx_bytes[i*16+10] = _mm256_srli_epi32(_mm256_slli_epi32(l2_256,8),24);
		avx_bytes[i*16+9] = _mm256_srli_epi32(_mm256_slli_epi32(l2_256,16),24);
		avx_bytes[i*16+8] = _mm256_srli_epi32(_mm256_slli_epi32(l2_256,24),24);

		avx_bytes[i*16+15] = _mm256_srli_epi32(l3_256,24);
		avx_bytes[i*16+14] = _mm256_srli_epi32(_mm256_slli_epi32(l3_256,8),24);
		avx_bytes[i*16+13] = _mm256_srli_epi32(_mm256_slli_epi32(l3_256,16),24);
		avx_bytes[i*16+12] = _mm256_srli_epi32(_mm256_slli_epi32(l3_256,24),24);
		p++;
	}

	//clock_E10 = cpucycles();
	//clock_T10 += clock_E10 - clock_S10;
	

	/*--------------------------------------------------------*/
	/*---------------------Do the shifts----------------------*/
	/*--------------------------------------------------------*/
	//clock_S11 = cpucycles();
	
	uint32_t j;
	uint32_t offset_data=0,offset_byte=0;
	offset_byte=0;
	for(j=0;j<(SABER_N/8)/2;j++){
		offset_byte=13*j;
		offset_data=8*j;
		avx_data[offset_data + 0] = _mm256_or_si256(_mm256_and_si256(avx_bytes[offset_byte+0],avx_epi32_ff),
									_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte+1],avx_epi32_1f),8));
		
		avx_data[offset_data + 1] = _mm256_or_si256(_mm256_srli_epi32(avx_bytes[offset_byte+1],5),
									_mm256_or_si256(_mm256_slli_epi32(avx_bytes[offset_byte+2],3),
									_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte+3],avx_epi32_03),11)));
		avx_data[offset_data + 2] = _mm256_or_si256(_mm256_srli_epi32(avx_bytes[offset_byte+3],2),
									_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte+4],avx_epi32_7f),6));
		avx_data[offset_data + 3] = _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_bytes[offset_byte+4],7),avx_epi32_01),
									_mm256_or_si256(_mm256_slli_epi32(avx_bytes[offset_byte+5],1),
									_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte+6],avx_epi32_0f),9)));
		avx_data[offset_data + 4] = _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_bytes[offset_byte+6],4),avx_epi32_0f),
									_mm256_or_si256(_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte+7],avx_epi32_ff),4),
									_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte+8],avx_epi32_01),12)));
		avx_data[offset_data + 5] = _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_bytes[offset_byte+8],1),avx_epi32_7f),
									_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte+9],avx_epi32_3f),7));
		avx_data[offset_data + 6] = _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_bytes[offset_byte+9],6),avx_epi32_03),
									_mm256_or_si256(_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte+10],avx_epi32_ff),2),
									_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte+11],avx_epi32_07),10)));
		avx_data[offset_data + 7] = _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_bytes[offset_byte+11],3),avx_epi32_1f),
									_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte+12],avx_epi32_ff),5));
	}
	//clock_E11 = cpucycles();
	//clock_T11 += clock_E11 - clock_S11;
	
	
	/*--------------------------------------------------------*/
	/*---------------------Store back-------------------------*/
	/*--------------------------------------------------------*/
	// _mm256_cvtps_ph
	// _mm_cvtps_ph(l0,0x08)
	// _mm_cvtps_pi16
	__m128i ph0,ph1,ph2,ph3;
	__m128i ph4,ph5,ph6,ph7;

	
	//clock_S12 = cpucycles();
	
	int offset0 = 0;
	int k;
	for(k=0;k<8;k++){
		//get the front half(4 number) from 256-bit avx to 128bit
		l0 = _mm256_extractf128_ps((__m256)avx_data[offset0+0],0);
		l1 = _mm256_extractf128_ps((__m256)avx_data[offset0+1],0);
		l2 = _mm256_extractf128_ps((__m256)avx_data[offset0+2],0);
		l3 = _mm256_extractf128_ps((__m256)avx_data[offset0+3],0);
		
		l4 = _mm256_extractf128_ps((__m256)avx_data[offset0+4],0);
		l5 = _mm256_extractf128_ps((__m256)avx_data[offset0+5],0);
		l6 = _mm256_extractf128_ps((__m256)avx_data[offset0+6],0);
		l7 = _mm256_extractf128_ps((__m256)avx_data[offset0+7],0);
		
		l8 = _mm256_extractf128_ps((__m256)avx_data[offset0+8],0);
		l9 = _mm256_extractf128_ps((__m256)avx_data[offset0+9],0);
		l10 = _mm256_extractf128_ps((__m256)avx_data[offset0+10],0);
		l11 = _mm256_extractf128_ps((__m256)avx_data[offset0+11],0);
		
		l12 = _mm256_extractf128_ps((__m256)avx_data[offset0+12],0);
		l13 = _mm256_extractf128_ps((__m256)avx_data[offset0+13],0);
		l14 = _mm256_extractf128_ps((__m256)avx_data[offset0+14],0);
		l15 = _mm256_extractf128_ps((__m256)avx_data[offset0+15],0);

		//transpose matrix
		_MM_TRANSPOSE4_PS(l0,l1,l2,l3);
		_MM_TRANSPOSE4_PS(l4,l5,l6,l7);
		_MM_TRANSPOSE4_PS(l8,l9,l10,l11);
		_MM_TRANSPOSE4_PS(l12,l13,l14,l15);
		
		//compress every 32-bit to 16-bit
		ph0 = _mm_packs_epi32((__m128i)l0,(__m128i)l4);
		ph1 = _mm_packs_epi32((__m128i)l1,(__m128i)l5);
		ph2 = _mm_packs_epi32((__m128i)l2,(__m128i)l6);
		ph3 = _mm_packs_epi32((__m128i)l3,(__m128i)l7);
		ph4 = _mm_packs_epi32((__m128i)l8,(__m128i)l12);
		ph5 = _mm_packs_epi32((__m128i)l9,(__m128i)l13);
		ph6 = _mm_packs_epi32((__m128i)l10,(__m128i)l14);
		ph7 = _mm_packs_epi32((__m128i)l11,(__m128i)l15);
		
		//do the same thing to back half(4 number) from 256-bit avx to 128bit
		//SHOW(__m256i,_mm256_insertf128_si256(_mm256_castsi128_si256(ph0),ph4,1));
		data0[k] = _mm256_insertf128_si256(_mm256_castsi128_si256(ph0),ph4,1);
		data1[k] = _mm256_insertf128_si256(_mm256_castsi128_si256(ph1),ph5,1);
		data2[k] = _mm256_insertf128_si256(_mm256_castsi128_si256(ph2),ph6,1);
		data3[k] = _mm256_insertf128_si256(_mm256_castsi128_si256(ph3),ph7,1);
		
		l0 = _mm256_extractf128_ps((__m256)avx_data[offset0+0],1);
		l1 = _mm256_extractf128_ps((__m256)avx_data[offset0+1],1);
		l2 = _mm256_extractf128_ps((__m256)avx_data[offset0+2],1);
		l3 = _mm256_extractf128_ps((__m256)avx_data[offset0+3],1);
		
		l4 = _mm256_extractf128_ps((__m256)avx_data[offset0+4],1);
		l5 = _mm256_extractf128_ps((__m256)avx_data[offset0+5],1);
		l6 = _mm256_extractf128_ps((__m256)avx_data[offset0+6],1);
		l7 = _mm256_extractf128_ps((__m256)avx_data[offset0+7],1);
		
		l8 = _mm256_extractf128_ps((__m256)avx_data[offset0+8],1);
		l9 = _mm256_extractf128_ps((__m256)avx_data[offset0+9],1);
		l10 = _mm256_extractf128_ps((__m256)avx_data[offset0+10],1);
		l11 = _mm256_extractf128_ps((__m256)avx_data[offset0+11],1);
		
		l12 = _mm256_extractf128_ps((__m256)avx_data[offset0+12],1);
		l13 = _mm256_extractf128_ps((__m256)avx_data[offset0+13],1);
		l14 = _mm256_extractf128_ps((__m256)avx_data[offset0+14],1);
		l15 = _mm256_extractf128_ps((__m256)avx_data[offset0+15],1);

		_MM_TRANSPOSE4_PS(l0,l1,l2,l3);
		_MM_TRANSPOSE4_PS(l4,l5,l6,l7);
		_MM_TRANSPOSE4_PS(l8,l9,l10,l11);
		_MM_TRANSPOSE4_PS(l12,l13,l14,l15);
		
		ph0 = _mm_packs_epi32((__m128i)l0,(__m128i)l4);
		ph1 = _mm_packs_epi32((__m128i)l1,(__m128i)l5);
		ph2 = _mm_packs_epi32((__m128i)l2,(__m128i)l6);
		ph3 = _mm_packs_epi32((__m128i)l3,(__m128i)l7);
		ph4 = _mm_packs_epi32((__m128i)l8,(__m128i)l12);
		ph5 = _mm_packs_epi32((__m128i)l9,(__m128i)l13);
		ph6 = _mm_packs_epi32((__m128i)l10,(__m128i)l14);
		ph7 = _mm_packs_epi32((__m128i)l11,(__m128i)l15);

		
		data0[k+8] = _mm256_insertf128_si256(_mm256_castsi128_si256(ph0),ph4,1);
		data1[k+8] = _mm256_insertf128_si256(_mm256_castsi128_si256(ph1),ph5,1);
		data2[k+8] = _mm256_insertf128_si256(_mm256_castsi128_si256(ph2),ph6,1);
		data3[k+8] = _mm256_insertf128_si256(_mm256_castsi128_si256(ph3),ph7,1);
		
		offset0 += 16;
	}
}




void GenMatrix(polyvec *a, const unsigned char *seed) {
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
			BS2POLq(buf+(i*SABER_K+j)*one_vector,temp_ar);
			for(k=0;k<SABER_N;k++){
				a[i].vec[j].coeffs[k] = (temp_ar[k])& mod ;
			}
    }
  }
}

void GenMatrix4x(polyvecNew *a0, polyvecNew *a1, polyvecNew *a2, polyvecNew *a3, 
								const unsigned char *seed0, const unsigned char *seed1, 
								const unsigned char *seed2, const unsigned char *seed3) 
{
  unsigned int one_vector=13*SABER_N/8;
  unsigned int byte_bank_length=SABER_K*SABER_K*one_vector;

  unsigned char buf0[byte_bank_length], buf1[byte_bank_length], buf2[byte_bank_length], buf3[byte_bank_length];

  int i,j;

  shake128x4(buf0,buf1,buf2,buf3, byte_bank_length, seed0, seed1, seed2, seed3, SABER_SEEDBYTES);

  for(i=0;i<SABER_K;i++)
  {
    for(j=0;j<SABER_K;j++)
    {
			BS2POLq4x(buf0+(i*SABER_K+j)*one_vector, buf1+(i*SABER_K+j)*one_vector, buf2+(i*SABER_K+j)*one_vector, buf3+(i*SABER_K+j)*one_vector,
					&a0[i].vec[j].coeffs[0], &a1[i].vec[j].coeffs[0], &a2[i].vec[j].coeffs[0], &a3[i].vec[j].coeffs[0]);

    }
  }
}



void GenSecret(uint16_t r[SABER_K][SABER_N],const unsigned char *seed){


		uint32_t i;

		int32_t buf_size= SABER_MU*SABER_N*SABER_K/8;

		uint8_t buf[buf_size];

		shake128(buf, buf_size, seed,SABER_NOISESEEDBYTES);

		for(i=0;i<SABER_K;i++)
		{
			cbd(r[i],buf+i*SABER_MU*SABER_N/8);
		}
}

void GenSecret4x(uint16_t r0[SABER_K][SABER_N], uint16_t r1[SABER_K][SABER_N], 
								uint16_t r2[SABER_K][SABER_N], uint16_t r3[SABER_K][SABER_N],
								const unsigned char *seed0, const unsigned char *seed1,
								const unsigned char *seed2, const unsigned char *seed3)
{

		uint32_t i;

		int32_t buf_size= SABER_MU*SABER_N*SABER_K/8;

		uint8_t buf0[buf_size], buf1[buf_size], buf2[buf_size], buf3[buf_size];

  	shake128x4(buf0, buf1, buf2, buf3, buf_size, seed0, seed1, seed2, seed3, SABER_SEEDBYTES);

		for(i=0;i<SABER_K;i++)
		{
			cbd(r0[i],buf0+i*SABER_MU*SABER_N/8);
			cbd(r1[i],buf1+i*SABER_MU*SABER_N/8);
			cbd(r2[i],buf2+i*SABER_MU*SABER_N/8);
			cbd(r3[i],buf3+i*SABER_MU*SABER_N/8);
		}
}

//********************************matrix-vector mul routines*****************************************************
void matrix_vector_mul(__m256i a1_avx_combined[NUM_POLY][NUM_POLY][AVX_N1], __m256i b_bucket[NUM_POLY][SCHB_N*4], __m256i res_avx[NUM_POLY][AVX_N1], int isTranspose);
void vector_vector_mul(__m256i a_avx[NUM_POLY][AVX_N1], __m256i b_bucket[NUM_POLY][SCHB_N*4], __m256i res_avx[AVX_N1]);



void indcpa_kem_keypair(unsigned char *pk0, unsigned char *sk0,
						unsigned char *pk1, unsigned char *sk1,
						unsigned char *pk2, unsigned char *sk2,
						unsigned char *pk3, unsigned char *sk3,
						unsigned char seed_arr[4][SABER_SEEDBYTES], 
						unsigned char noiseseed_arr[4][SABER_COINBYTES] )
{
 
	polyvecNew a0[SABER_K], a1[SABER_K], a2[SABER_K], a3[SABER_K];

	uint16_t skpv1_0[SABER_K][SABER_N], skpv1_1[SABER_K][SABER_N], skpv1_2[SABER_K][SABER_N], skpv1_3[SABER_K][SABER_N];

	int32_t i,j,k;


	//--------------AVX declaration------------------
	__m256i sk0_avx[SABER_K][SABER_N/16], sk1_avx[SABER_K][SABER_N/16];
	__m256i sk2_avx[SABER_K][SABER_N/16], sk3_avx[SABER_K][SABER_N/16];
	__m256i a0_avx[SABER_K][SABER_K][SABER_N/16], a1_avx[SABER_K][SABER_K][SABER_N/16];
	__m256i a2_avx[SABER_K][SABER_K][SABER_N/16], a3_avx[SABER_K][SABER_K][SABER_N/16];
	
	__m256i res0_avx[SABER_K][SABER_N/16], res1_avx[SABER_K][SABER_N/16], res2_avx[SABER_K][SABER_N/16], res3_avx[SABER_K][SABER_N/16];
	  

	mask_ar[0]=~(0UL); mask_ar[1]=~(0UL); mask_ar[2]=~(0UL); mask_ar[3]=~(0UL);
	mask_load = _mm256_loadu_si256 ((__m256i const *)mask_ar);

	floor_round=_mm256_set1_epi16(4);

	H1_avx=_mm256_set1_epi16(h1);


	__m256i b0_bucket[NUM_POLY][SCHB_N*4];
	__m256i b1_bucket[NUM_POLY][SCHB_N*4];
	__m256i b2_bucket[NUM_POLY][SCHB_N*4];
	__m256i b3_bucket[NUM_POLY][SCHB_N*4];


	//--------------AVX declaration ends------------------

	load_values();


	shake128x4(seed_arr[0], seed_arr[1], seed_arr[2], seed_arr[3], SABER_SEEDBYTES, 
			   seed_arr[0], seed_arr[1], seed_arr[2], seed_arr[3], SABER_SEEDBYTES);

	GenMatrix4x(a0, a1, a2, a3, seed_arr[0], seed_arr[1], seed_arr[2], seed_arr[3]);

	GenSecret4x(skpv1_0, skpv1_1, skpv1_2, skpv1_3, noiseseed_arr[0], noiseseed_arr[1], noiseseed_arr[2], noiseseed_arr[3]);


 	// Load sk into avx vectors		
 	for(i=0;i<SABER_K;i++)
 	{
		for(j=0; j<SABER_N/16; j++){
  		sk0_avx[i][j] = _mm256_loadu_si256 ((__m256i const *) (&skpv1_0[i][j*16]));
  		sk1_avx[i][j] = _mm256_loadu_si256 ((__m256i const *) (&skpv1_1[i][j*16]));
  		sk2_avx[i][j] = _mm256_loadu_si256 ((__m256i const *) (&skpv1_2[i][j*16]));
  		sk3_avx[i][j] = _mm256_loadu_si256 ((__m256i const *) (&skpv1_3[i][j*16]));
		}
	}

	// Load a into avx vectors	
	for(i=0;i<SABER_K;i++){ 
		for(j=0;j<SABER_K;j++){
			for(k=0;k<SABER_N/16;k++){
				a0_avx[i][j][k]=a0[i].vec[j].coeffs[k];
				a1_avx[i][j][k]=a1[i].vec[j].coeffs[k];
				a2_avx[i][j][k]=a2[i].vec[j].coeffs[k];
				a3_avx[i][j][k]=a3[i].vec[j].coeffs[k];
			}
		}
	}

		for(i=0;i<SABER_K;i++){
			for(j=0;j<SABER_N/16;j++){
				res0_avx[i][j]=_mm256_xor_si256(res0_avx[i][j],res0_avx[i][j]);
				res1_avx[i][j]=_mm256_xor_si256(res1_avx[i][j],res1_avx[i][j]);
				res2_avx[i][j]=_mm256_xor_si256(res2_avx[i][j],res2_avx[i][j]);
				res3_avx[i][j]=_mm256_xor_si256(res3_avx[i][j],res3_avx[i][j]);
			}
		}

		for(j=0; j<NUM_POLY; j++) {
			TC_eval(sk0_avx[j], b0_bucket[j]);
			TC_eval(sk1_avx[j], b1_bucket[j]);
			TC_eval(sk2_avx[j], b2_bucket[j]);
			TC_eval(sk3_avx[j], b3_bucket[j]);
		}

		// Matrix-vector multiplication; Matrix in transposed order
		matrix_vector_mul(a0_avx, b0_bucket, res0_avx, 1);
		matrix_vector_mul(a1_avx, b1_bucket, res1_avx, 1);
		matrix_vector_mul(a2_avx, b2_bucket, res2_avx, 1);
		matrix_vector_mul(a3_avx, b3_bucket, res3_avx, 1);

		// Now truncation
		for(i=0;i<SABER_K;i++){ //shift right EQ-EP bits
			for(j=0;j<SABER_N/16;j++){
				res0_avx[i][j]=_mm256_add_epi16 (res0_avx[i][j], H1_avx);
				res0_avx[i][j]=_mm256_srli_epi16 (res0_avx[i][j], (SABER_EQ-SABER_EP) );
				
				res1_avx[i][j]=_mm256_add_epi16 (res1_avx[i][j], H1_avx);
				res1_avx[i][j]=_mm256_srli_epi16 (res1_avx[i][j], (SABER_EQ-SABER_EP) );
				
				res2_avx[i][j]=_mm256_add_epi16 (res2_avx[i][j], H1_avx);
				res2_avx[i][j]=_mm256_srli_epi16 (res2_avx[i][j], (SABER_EQ-SABER_EP) );
				
				res3_avx[i][j]=_mm256_add_epi16 (res3_avx[i][j], H1_avx);
				res3_avx[i][j]=_mm256_srli_epi16 (res3_avx[i][j], (SABER_EQ-SABER_EP) );
			}
		}

		//------------------Pack sk into byte string-------
		POLVEC2BSX4(sk0,sk1,sk2,sk3,skpv1_0,skpv1_1,skpv1_2,skpv1_3,SABER_Q);
		//------------------Pack pk into byte string-------
	
		for(i=0;i<SABER_K;i++){ // reuses skpv1[] for unpacking avx of public-key
				for(j=0;j<SABER_N/16;j++){
					_mm256_maskstore_epi32 ((int *) (skpv1_0[i]+j*16), mask_load, res0_avx[i][j]);
					_mm256_maskstore_epi32 ((int *) (skpv1_1[i]+j*16), mask_load, res1_avx[i][j]);
					_mm256_maskstore_epi32 ((int *) (skpv1_2[i]+j*16), mask_load, res2_avx[i][j]);
					_mm256_maskstore_epi32 ((int *) (skpv1_3[i]+j*16), mask_load, res3_avx[i][j]);
				}
			}
		// load the public-key into pk byte string
		POLVEC2BSX4(pk0,pk1,pk2,pk3,skpv1_0,skpv1_1,skpv1_2,skpv1_3,SABER_P);

		for(i=0;i<SABER_SEEDBYTES;i++){ 
		// now load the seedbytes in PK. Easy since seed bytes are kept in byte format.
			pk0[SABER_POLYVECCOMPRESSEDBYTES + i]=seed_arr[0][i]; 
			pk1[SABER_POLYVECCOMPRESSEDBYTES + i]=seed_arr[1][i]; 
			pk2[SABER_POLYVECCOMPRESSEDBYTES + i]=seed_arr[2][i]; 
			pk3[SABER_POLYVECCOMPRESSEDBYTES + i]=seed_arr[3][i]; 
		}
}



void indcpa_kem_enc(
					unsigned char *message_received0, unsigned char *message_received1,
					unsigned char *message_received2, unsigned char *message_received3,
					unsigned char *noiseseed0, unsigned char *noiseseed1, 
					unsigned char *noiseseed2, unsigned char *noiseseed3,
					const unsigned char *pk0, unsigned char *ciphertext0,
					const unsigned char *pk1, unsigned char *ciphertext1,
					const unsigned char *pk2, unsigned char *ciphertext2,
					const unsigned char *pk3, unsigned char *ciphertext3)
{ 

	uint32_t i,j,k;
	polyvecNew a0[SABER_K], a1[SABER_K], a2[SABER_K], a3[SABER_K];
	unsigned char seed0[SABER_SEEDBYTES], seed1[SABER_SEEDBYTES], seed2[SABER_SEEDBYTES], seed3[SABER_SEEDBYTES];

	uint16_t skpv1_0[SABER_K][SABER_N], skpv1_1[SABER_K][SABER_N], skpv1_2[SABER_K][SABER_N], skpv1_3[SABER_K][SABER_N];
	uint16_t temp0[SABER_K][SABER_N], temp1[SABER_K][SABER_N], temp2[SABER_K][SABER_N], temp3[SABER_K][SABER_N];
	uint16_t message0[SABER_KEYBYTES*8], message1[SABER_KEYBYTES*8], message2[SABER_KEYBYTES*8], message3[SABER_KEYBYTES*8];

	//--------------AVX declaration------------------
	
	  __m256i sk0_avx[SABER_K][SABER_N/16], sk1_avx[SABER_K][SABER_N/16], sk2_avx[SABER_K][SABER_N/16], sk3_avx[SABER_K][SABER_N/16];
	  __m256i mod_p;
	  
	  //Add
	  __m256i res0_avx[SABER_K][SABER_N/16], res1_avx[SABER_K][SABER_N/16], res2_avx[SABER_K][SABER_N/16], res3_avx[SABER_K][SABER_N/16];
	  __m256i vprime0_avx[SABER_N/16], vprime1_avx[SABER_N/16], vprime2_avx[SABER_N/16], vprime3_avx[SABER_N/16];
	  
	  
	  __m256i a0_avx[SABER_K][SABER_K][SABER_N/16], a1_avx[SABER_K][SABER_K][SABER_N/16];
	  __m256i a2_avx[SABER_K][SABER_K][SABER_N/16], a3_avx[SABER_K][SABER_K][SABER_N/16];
	  

	  __m256i pkcl_avx0[SABER_K][SABER_N/16];//public key of received by the client
	  __m256i pkcl_avx1[SABER_K][SABER_N/16];//public key of received by the client
	  __m256i pkcl_avx2[SABER_K][SABER_N/16];//public key of received by the client
	  __m256i pkcl_avx3[SABER_K][SABER_N/16];//public key of received by the client

		//__m256i message_avx[SABER_N/16];
		__m256i message0_avx[SABER_N/16], message1_avx[SABER_N/16], message2_avx[SABER_N/16], message3_avx[SABER_N/16];


		
	mask_ar[0]=~(0UL);mask_ar[1]=~(0UL);mask_ar[2]=~(0UL);mask_ar[3]=~(0UL);
	mask_load = _mm256_loadu_si256 ((__m256i const *)mask_ar);

	mod_p=_mm256_set1_epi16(SABER_P-1);

	floor_round=_mm256_set1_epi16(4);

	H1_avx=_mm256_set1_epi16(h1);

	__m256i b0_bucket[NUM_POLY][SCHB_N*4];
	__m256i b1_bucket[NUM_POLY][SCHB_N*4];
	__m256i b2_bucket[NUM_POLY][SCHB_N*4];
	__m256i b3_bucket[NUM_POLY][SCHB_N*4];

 
	//--------------AVX declaration ends------------------
	load_values();
      
	//SABER_SEEDBYTES=32
	for(i=0;i<SABER_SEEDBYTES;i++){ // Load the seedbytes in the client seed from PK.
		seed0[i]=pk0[ SABER_POLYVECCOMPRESSEDBYTES + i];
		seed1[i]=pk1[ SABER_POLYVECCOMPRESSEDBYTES + i];
		seed2[i]=pk2[ SABER_POLYVECCOMPRESSEDBYTES + i];
		seed3[i]=pk3[ SABER_POLYVECCOMPRESSEDBYTES + i]; 
	}

	GenMatrix4x(a0,a1,a2,a3, seed0, seed1, seed2, seed3);				

	GenSecret4x(skpv1_0,skpv1_1,skpv1_2,skpv1_3, noiseseed0, noiseseed1, noiseseed2, noiseseed3);

	// ----------- Load skpv1 into avx vectors ---------- 
	for(i=0;i<SABER_K;i++){ 
		for(j=0; j<SABER_N/16; j++){
		    sk0_avx[i][j] = _mm256_loadu_si256 ((__m256i const *) (&skpv1_0[i][j*16]));
		    sk1_avx[i][j] = _mm256_loadu_si256 ((__m256i const *) (&skpv1_1[i][j*16]));
		    sk2_avx[i][j] = _mm256_loadu_si256 ((__m256i const *) (&skpv1_2[i][j*16]));
		    sk3_avx[i][j] = _mm256_loadu_si256 ((__m256i const *) (&skpv1_3[i][j*16]));
		}
  	}
	
	
	// ----------- Load skpv1 into avx vectors ---------- 
	  for(i=0;i<SABER_K;i++){ 
		  for(j=0;j<SABER_K;j++){
			  for(k=0;k<SABER_N/16;k++){
				a0_avx[i][j][k]=a0[i].vec[j].coeffs[k];
				a1_avx[i][j][k]=a1[i].vec[j].coeffs[k];
				a2_avx[i][j][k]=a2[i].vec[j].coeffs[k];
				a3_avx[i][j][k]=a3[i].vec[j].coeffs[k];
				
			  }
		  }
 	 }


		for(i=0;i<SABER_K;i++){
			for(j=0;j<SABER_N/16;j++){
				res0_avx[i][j]=_mm256_xor_si256(res0_avx[i][j],res0_avx[i][j]);
				res1_avx[i][j]=_mm256_xor_si256(res1_avx[i][j],res1_avx[i][j]);
				res2_avx[i][j]=_mm256_xor_si256(res2_avx[i][j],res2_avx[i][j]);
				res3_avx[i][j]=_mm256_xor_si256(res3_avx[i][j],res3_avx[i][j]);
			}
		}	
		
		// Matrix-vector multiplication; 

		for (j=0;j<NUM_POLY;j++) {
			TC_eval(sk0_avx[j], b0_bucket[j]);
			TC_eval(sk1_avx[j], b1_bucket[j]);
			TC_eval(sk2_avx[j], b2_bucket[j]);
			TC_eval(sk3_avx[j], b3_bucket[j]);

		}
		// Matrix-vector multiplication; Matrix in normal order
		matrix_vector_mul(a0_avx, b0_bucket, res0_avx, 0);
		matrix_vector_mul(a1_avx, b1_bucket, res1_avx, 0);
		matrix_vector_mul(a2_avx, b2_bucket, res2_avx, 0);
		matrix_vector_mul(a3_avx, b3_bucket, res3_avx, 0);

	
		// Now truncation

		for(i=0;i<SABER_K;i++){ //shift right EQ-EP bits
			for(j=0;j<SABER_N/16;j++){
				res0_avx[i][j]=_mm256_add_epi16 (res0_avx[i][j], H1_avx);
				res0_avx[i][j]=_mm256_srli_epi16 (res0_avx[i][j], (SABER_EQ-SABER_EP) );
				
				res1_avx[i][j]=_mm256_add_epi16 (res1_avx[i][j], H1_avx);
				res1_avx[i][j]=_mm256_srli_epi16 (res1_avx[i][j], (SABER_EQ-SABER_EP) );
				
				res2_avx[i][j]=_mm256_add_epi16 (res2_avx[i][j], H1_avx);
				res2_avx[i][j]=_mm256_srli_epi16 (res2_avx[i][j], (SABER_EQ-SABER_EP) );
				
				res3_avx[i][j]=_mm256_add_epi16 (res3_avx[i][j], H1_avx);
				res3_avx[i][j]=_mm256_srli_epi16 (res3_avx[i][j], (SABER_EQ-SABER_EP) );
			}
		}


		

		//-----this result should be put in b_prime for later use in server.
		for(i=0;i<SABER_K;i++){ // first store in 16 bit arrays
			for(j=0;j<SABER_N/16;j++){
				_mm256_maskstore_epi32 ((int *)(temp0[i]+j*16), mask_load, res0_avx[i][j]);
				_mm256_maskstore_epi32 ((int *)(temp1[i]+j*16), mask_load, res1_avx[i][j]);
				_mm256_maskstore_epi32 ((int *)(temp2[i]+j*16), mask_load, res2_avx[i][j]);
				_mm256_maskstore_epi32 ((int *)(temp3[i]+j*16), mask_load, res3_avx[i][j]);
			}
		}


		// Pack b_prime into ciphertext byte string
		POLVEC2BSX4(ciphertext0, ciphertext1, ciphertext2, ciphertext3, temp0, temp1, temp2, temp3, SABER_P);
		// client matrix-vector multiplication ends

		//------now calculate the v'

		//-------unpack the public_key
		BS2POLVECX4(pk0, pk1, pk2, pk3, pkcl_avx0, pkcl_avx1, pkcl_avx2, pkcl_avx3, SABER_P);
		// InnerProduct (truncate)
		for(k=0;k<SABER_N/16;k++){
			vprime0_avx[k]=_mm256_xor_si256(vprime0_avx[k],vprime0_avx[k]);
			vprime1_avx[k]=_mm256_xor_si256(vprime1_avx[k],vprime1_avx[k]);
			vprime2_avx[k]=_mm256_xor_si256(vprime2_avx[k],vprime2_avx[k]);
			vprime3_avx[k]=_mm256_xor_si256(vprime3_avx[k],vprime3_avx[k]);
		}

		// vector-vector scalar multiplication with mod p
		vector_vector_mul(pkcl_avx0, b0_bucket, vprime0_avx);
		vector_vector_mul(pkcl_avx1, b1_bucket, vprime1_avx);
		vector_vector_mul(pkcl_avx2, b2_bucket, vprime2_avx);
		vector_vector_mul(pkcl_avx3, b3_bucket, vprime3_avx);

		// Computation of v'+h1 
		for(i=0;i<SABER_N/16;i++){//adding h1
	 		vprime0_avx[i]=_mm256_add_epi16(vprime0_avx[i], H1_avx);
			vprime1_avx[i]=_mm256_add_epi16(vprime1_avx[i], H1_avx);
			vprime2_avx[i]=_mm256_add_epi16(vprime2_avx[i], H1_avx);
			vprime3_avx[i]=_mm256_add_epi16(vprime3_avx[i], H1_avx);
		}

		// unpack message_received;
		//(SABER_KEYBYTES)=32
		for(j=0; j<SABER_KEYBYTES; j++)
		{
			for(i=0; i<8; i++)
			{
				message0[8*j+i] = ((message_received0[j]>>i) & 0x01);
				message1[8*j+i] = ((message_received1[j]>>i) & 0x01);
				message2[8*j+i] = ((message_received2[j]>>i) & 0x01);
				message3[8*j+i] = ((message_received3[j]>>i) & 0x01);
			}
		}
		// message encoding
		for(i=0; i<SABER_N/16; i++)
		{
			message0_avx[i] = _mm256_loadu_si256 ((__m256i const *) (&message0[i*16]));
			message0_avx[i] = _mm256_slli_epi16 (message0_avx[i], (SABER_EP-1) );
			
			message1_avx[i] = _mm256_loadu_si256 ((__m256i const *) (&message1[i*16]));
			message1_avx[i] = _mm256_slli_epi16 (message1_avx[i], (SABER_EP-1) );
			
			message2_avx[i] = _mm256_loadu_si256 ((__m256i const *) (&message2[i*16]));
			message2_avx[i] = _mm256_slli_epi16 (message2_avx[i], (SABER_EP-1) );
			
			message3_avx[i] = _mm256_loadu_si256 ((__m256i const *) (&message3[i*16]));
			message3_avx[i] = _mm256_slli_epi16 (message3_avx[i], (SABER_EP-1) );
		}	

		// SHIFTRIGHT(v'+h1-m mod p, EP-ET)
		for(k=0;k<SABER_N/16;k++)
		{
			vprime0_avx[k]=_mm256_sub_epi16(vprime0_avx[k], message0_avx[k]);
			vprime0_avx[k]=_mm256_and_si256(vprime0_avx[k], mod_p);
			vprime0_avx[k]=_mm256_srli_epi16 (vprime0_avx[k], (SABER_EP-SABER_ET) );
			
			vprime1_avx[k]=_mm256_sub_epi16(vprime1_avx[k], message1_avx[k]);
			vprime1_avx[k]=_mm256_and_si256(vprime1_avx[k], mod_p);
			vprime1_avx[k]=_mm256_srli_epi16 (vprime1_avx[k], (SABER_EP-SABER_ET) );
			
			vprime2_avx[k]=_mm256_sub_epi16(vprime2_avx[k], message2_avx[k]);
			vprime2_avx[k]=_mm256_and_si256(vprime2_avx[k], mod_p);
			vprime2_avx[k]=_mm256_srli_epi16 (vprime2_avx[k], (SABER_EP-SABER_ET) );
			
			vprime3_avx[k]=_mm256_sub_epi16(vprime3_avx[k], message3_avx[k]);
			vprime3_avx[k]=_mm256_and_si256(vprime3_avx[k], mod_p);
			vprime3_avx[k]=_mm256_srli_epi16 (vprime3_avx[k], (SABER_EP-SABER_ET) );
		}
		

		// Unpack avx
		for(j=0;j<SABER_N/16;j++)
		{
				_mm256_maskstore_epi32 ((int *) (temp0[0]+j*16), mask_load, vprime0_avx[j]);
				_mm256_maskstore_epi32 ((int *) (temp1[0]+j*16), mask_load, vprime1_avx[j]);
				_mm256_maskstore_epi32 ((int *) (temp2[0]+j*16), mask_load, vprime2_avx[j]);
				_mm256_maskstore_epi32 ((int *) (temp3[0]+j*16), mask_load, vprime3_avx[j]);
		}
	

	SABER_pack_4bit(&ciphertext0[SABER_CIPHERTEXTBYTES],temp0[0]);
	SABER_pack_4bit(&ciphertext1[SABER_CIPHERTEXTBYTES],temp1[0]);
	SABER_pack_4bit(&ciphertext2[SABER_CIPHERTEXTBYTES],temp2[0]);
	SABER_pack_4bit(&ciphertext3[SABER_CIPHERTEXTBYTES],temp3[0]);

}


void indcpa_kem_dec(
					const unsigned char *sk0, const unsigned char *ciphertext0, unsigned char message0_dec[],
					const unsigned char *sk1, const unsigned char *ciphertext1, unsigned char message1_dec[],
					const unsigned char *sk2, const unsigned char *ciphertext2, unsigned char message2_dec[],
					const unsigned char *sk3, const unsigned char *ciphertext3, unsigned char message3_dec[])
{
	uint32_t i,j;

	//--------------AVX declaration------------------
	
	uint16_t op0[SABER_N], op1[SABER_N], op2[SABER_N], op3[SABER_N];
	uint16_t message0_dec_unpacked[SABER_KEYBYTES*8], message1_dec_unpacked[SABER_KEYBYTES*8], message2_dec_unpacked[SABER_KEYBYTES*8], message3_dec_unpacked[SABER_KEYBYTES*8];
	__m256i v0_avx[SABER_N/16], v1_avx[SABER_N/16], v2_avx[SABER_N/16], v3_avx[SABER_N/16];
	__m256i sksv0_avx[SABER_K][SABER_N/16], sksv1_avx[SABER_K][SABER_N/16], sksv2_avx[SABER_K][SABER_N/16], sksv3_avx[SABER_K][SABER_N/16];
	__m256i pksv0_avx[SABER_K][SABER_N/16], pksv1_avx[SABER_K][SABER_N/16], pksv2_avx[SABER_K][SABER_N/16], pksv3_avx[SABER_K][SABER_N/16];
	  
	mask_ar[0]=~(0UL);mask_ar[1]=~(0UL);mask_ar[2]=~(0UL);mask_ar[3]=~(0UL);
	mask_load = _mm256_loadu_si256 ((__m256i const *)mask_ar);


	H2_avx=_mm256_set1_epi16(h2);

	__m256i b0_bucket[NUM_POLY][SCHB_N*4];
	__m256i b1_bucket[NUM_POLY][SCHB_N*4];
	__m256i b2_bucket[NUM_POLY][SCHB_N*4];
	__m256i b3_bucket[NUM_POLY][SCHB_N*4];

	//--------------AVX declaration ends------------------
	
 	load_values();
	
		//-------unpack the public_key
		//sksv is the secret-key
		BS2POLVECX4(sk0, sk1, sk2, sk3, sksv0_avx, sksv1_avx, sksv2_avx, sksv3_avx, SABER_Q);
		
		//pksv is the ciphertext
		BS2POLVECX4(ciphertext0, ciphertext1, ciphertext2, ciphertext3, pksv0_avx, pksv1_avx, pksv2_avx, pksv3_avx, SABER_P);

		//NOT serial so no need to truncate
		for(i=0;i<SABER_N/16;i++){
			//v_avx[i]=_mm256_xor_si256(v_avx[i],v_avx[i]);
			v0_avx[i]=_mm256_xor_si256(v0_avx[i],v0_avx[i]);
			v1_avx[i]=_mm256_xor_si256(v1_avx[i],v1_avx[i]);
			v2_avx[i]=_mm256_xor_si256(v2_avx[i],v2_avx[i]);
			v3_avx[i]=_mm256_xor_si256(v3_avx[i],v3_avx[i]);
		}

		// InnerProduct(b', s, mod p)

		for(j=0;j<NUM_POLY;j++){
			TC_eval(sksv0_avx[j], b0_bucket[j]);
			TC_eval(sksv1_avx[j], b1_bucket[j]);
			TC_eval(sksv2_avx[j], b2_bucket[j]);
			TC_eval(sksv3_avx[j], b3_bucket[j]);
		}

		vector_vector_mul(pksv0_avx, b0_bucket, v0_avx);
		vector_vector_mul(pksv1_avx, b1_bucket, v1_avx);
		vector_vector_mul(pksv2_avx, b2_bucket, v2_avx);
		vector_vector_mul(pksv3_avx, b3_bucket, v3_avx); 

		for(i=0; i<SABER_N/16; i++){
			_mm256_maskstore_epi32 ((int *)(message0_dec_unpacked+i*16), mask_load, v0_avx[i]);
			_mm256_maskstore_epi32 ((int *)(message1_dec_unpacked+i*16), mask_load, v1_avx[i]);
			_mm256_maskstore_epi32 ((int *)(message2_dec_unpacked+i*16), mask_load, v2_avx[i]);
			_mm256_maskstore_epi32 ((int *)(message3_dec_unpacked+i*16), mask_load, v3_avx[i]);
		}


		// #if Saber_type == 1
			// SABER_un_pack3bit(&ciphertext_ptr[SABER_CIPHERTEXTBYTES], op);
		// #elif Saber_type == 2
			// SABER_un_pack4bit(&ciphertext_ptr[SABER_CIPHERTEXTBYTES], op);
			SABER_un_pack4bitX4(&ciphertext0[SABER_CIPHERTEXTBYTES], &ciphertext1[SABER_CIPHERTEXTBYTES], &ciphertext2[SABER_CIPHERTEXTBYTES], &ciphertext3[SABER_CIPHERTEXTBYTES], 
								op0, op1, op2, op3);
		// #elif Saber_type == 3
			// SABER_un_pack6bit(&ciphertext_ptr[SABER_CIPHERTEXTBYTES], op);
		// #endif

		//addition of h2
		for(i=0;i<SABER_N;i++){
			message0_dec_unpacked[i]= ( ( message0_dec_unpacked[i] + h2 - (op0[i]<<(SABER_EP-SABER_ET)) ) & (SABER_P-1) ) >> (SABER_EP-1);
			message1_dec_unpacked[i]= ( ( message1_dec_unpacked[i] + h2 - (op1[i]<<(SABER_EP-SABER_ET)) ) & (SABER_P-1) ) >> (SABER_EP-1);
			message2_dec_unpacked[i]= ( ( message2_dec_unpacked[i] + h2 - (op2[i]<<(SABER_EP-SABER_ET)) ) & (SABER_P-1) ) >> (SABER_EP-1);
			message3_dec_unpacked[i]= ( ( message3_dec_unpacked[i] + h2 - (op3[i]<<(SABER_EP-SABER_ET)) ) & (SABER_P-1) ) >> (SABER_EP-1);
		}

		POL2MSG(message0_dec_unpacked, message0_dec);
		POL2MSG(message1_dec_unpacked, message1_dec);
		POL2MSG(message2_dec_unpacked, message2_dec);
		POL2MSG(message3_dec_unpacked, message3_dec);
	//}
	// End: Decrypt ciphertext
	////////////////////////////////////////////////////////////////////////////

}


void POL2MSG(uint16_t *message_dec_unpacked, unsigned char *message_dec){

	int32_t i,j;

	for(j=0; j<SABER_KEYBYTES; j++)
	{
		message_dec[j] = 0;
		for(i=0; i<8; i++)
		message_dec[j] = message_dec[j] | (message_dec_unpacked[j*8 + i] <<i);
	} 

}

void matrix_vector_mul(__m256i a1_avx_combined[NUM_POLY][NUM_POLY][AVX_N1], __m256i b_bucket[NUM_POLY][SCHB_N*4], __m256i res_avx[NUM_POLY][AVX_N1], int isTranspose){



	int64_t i,j;

	__m256i c_bucket[2*SCM_SIZE*4]; //Holds results for 9 Karatsuba at a time

	for(i=0;i<NUM_POLY;i++){
		for(j=0;j<NUM_POLY;j++){

			if(isTranspose==0){
				toom_cook_4way_avx_n1(a1_avx_combined[i][j], b_bucket[j], c_bucket, j);
			}
			else{
				toom_cook_4way_avx_n1(a1_avx_combined[j][i], b_bucket[j], c_bucket, j);
			}
		}

		TC_interpol(c_bucket, res_avx[i]);
	}

}

void vector_vector_mul(__m256i a_avx[NUM_POLY][AVX_N1], __m256i b_bucket[NUM_POLY][SCHB_N*4], __m256i res_avx[AVX_N1]){

	int64_t i;

	__m256i c_bucket[2*SCM_SIZE*4]; //Holds results for 9 Karatsuba at a time

	for(i=0;i<NUM_POLY;i++){
		toom_cook_4way_avx_n1(a_avx[i], b_bucket[i], c_bucket, i);		
	}
	TC_interpol(c_bucket, res_avx);
}




