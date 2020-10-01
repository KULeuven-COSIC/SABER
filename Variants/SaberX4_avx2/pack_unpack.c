#include "pack_unpack.h"
//#include "SABER_indcpa.h"
#include <immintrin.h>
#include <tmmintrin.h>

extern __m256i avx_epi64_01, avx_epi64_03, avx_epi64_07, avx_epi64_0f, avx_epi64_1f, avx_epi64_3f, avx_epi64_7f, avx_epi64_ff;
extern __m256i avx_epi32_01, avx_epi32_03, avx_epi32_07, avx_epi32_0f, avx_epi32_1f, avx_epi32_3f, avx_epi32_7f, avx_epi32_ff;

void avx_load_16bit_8bit(const float * cfbs0, const float * cfbs1, 
					const float * cfbs2, const float * cfbs3, 
					const float * cfbs4, const float * cfbs5, 
					const float * cfbs6, const float * cfbs7,
					__m256i * avx_data){
	__m128 l0,l1,l2,l3,l4,l5,l6,l7;
	__m256i l0_256,l1_256,l2_256,l3_256;
	
	int p=0;
	int i;
	
	// 3*256*16bit/128 = loop
	// i = size/32
	for(i = 0;i<SABER_K*SABER_N*16/(128*2);i++){
		//Load 128 bit from bs0, bs1, bs2, bs3
		l0 = _mm_load_ps(cfbs0+p*4); 
		l1 = _mm_load_ps(cfbs1+p*4); 
		l2 = _mm_load_ps(cfbs2+p*4); 
		l3 = _mm_load_ps(cfbs3+p*4); 
		
		//Load 128 bit from middle of bs0, bs1, bs2, bs3
		l4 = _mm_load_ps(cfbs4+p*4); 
		l5 = _mm_load_ps(cfbs5+p*4); 
		l6 = _mm_load_ps(cfbs6+p*4); 
		l7 = _mm_load_ps(cfbs7+p*4); 
		
		//Transpose 4x4 matrix
		_MM_TRANSPOSE4_PS(l0,l1,l2,l3);
		_MM_TRANSPOSE4_PS(l4,l5,l6,l7);

		//merge front half of vec(128-bit) and back half of vec(128-bit) = 256bit
		l0_256 = _mm256_insertf128_si256(_mm256_castsi128_si256((__m128i)l0),(__m128i)l4,1);
		l1_256 = _mm256_insertf128_si256(_mm256_castsi128_si256((__m128i)l1),(__m128i)l5,1);
		l2_256 = _mm256_insertf128_si256(_mm256_castsi128_si256((__m128i)l2),(__m128i)l6,1);
		l3_256 = _mm256_insertf128_si256(_mm256_castsi128_si256((__m128i)l3),(__m128i)l7,1);
		
		//extract avx[i] = load(bs0[i], bs1[i], bs2[i], bs3[i], bs0[i+128], bs1[i+128], bs2[i+128], bs3[i+128])
		avx_data[i*8+0] = _mm256_srli_epi32(_mm256_slli_epi32(l0_256,16),16);
		avx_data[i*8+1] = _mm256_srli_epi32(l0_256,16);
		
		avx_data[i*8+2] = _mm256_srli_epi32(_mm256_slli_epi32(l1_256,16),16);
		avx_data[i*8+3] = _mm256_srli_epi32(l1_256,16);

		avx_data[i*8+4] = _mm256_srli_epi32(_mm256_slli_epi32(l2_256,16),16);
		avx_data[i*8+5] = _mm256_srli_epi32(l2_256,16);
		
		avx_data[i*8+6] = _mm256_srli_epi32(_mm256_slli_epi32(l3_256,16),16);
		avx_data[i*8+7] = _mm256_srli_epi32(l3_256,16);

		p++;
	}
}

void avx_store_8bit_bs(__m256i * avx_bytes, uint16_t size, 
					__m128i *bs0, __m128i * bs1, __m128i * bs2, __m128i * bs3,
					__m128i *bs4, __m128i * bs5, __m128i * bs6, __m128i * bs7){
	int offset0 = 0;
	int k;
	__m128 l0,l1,l2,l3,l4,l5,l6,l7;
	__m128 l8,l9,l10,l11,l12,l13,l14,l15;
	
	__m128i ph0,ph1,ph2,ph3;
	__m128i ph4,ph5,ph6,ph7;
	
	//480
	for(k=0;k<(size/16);k++){
		//get the front half(4 number) from 256-bit avx to 128bit
		l0 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+0],0);
		l1 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+1],0);
		l2 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+2],0);
		l3 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+3],0);

		l4 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+4],0);
		l5 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+5],0);
		l6 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+6],0);
		l7 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+7],0);
		
		l8 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+8],0);
		l9 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+9],0);
		l10 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+10],0);
		l11 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+11],0);
		
		l12 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+12],0);
		l13 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+13],0);
		l14 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+14],0);
		l15 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+15],0);

		//transpose matrix
		_MM_TRANSPOSE4_PS(l0,l1,l2,l3);
		_MM_TRANSPOSE4_PS(l4,l5,l6,l7);
		_MM_TRANSPOSE4_PS(l8,l9,l10,l11);
		_MM_TRANSPOSE4_PS(l12,l13,l14,l15);
		
		// _mm256_packus_epi16(a, b) u stand for unsigned - not effient
		//compress every 32-bit to 16-bit
		ph0 = _mm_packus_epi32((__m128i)l0,(__m128i)l4);
		ph1 = _mm_packus_epi32((__m128i)l1,(__m128i)l5);
		ph2 = _mm_packus_epi32((__m128i)l2,(__m128i)l6);
		ph3 = _mm_packus_epi32((__m128i)l3,(__m128i)l7);
		
		ph4 = _mm_packus_epi32((__m128i)l8,(__m128i)l12);
		ph5 = _mm_packus_epi32((__m128i)l9,(__m128i)l13);
		ph6 = _mm_packus_epi32((__m128i)l10,(__m128i)l14);
		ph7 = _mm_packus_epi32((__m128i)l11,(__m128i)l15);
		
		//compress every 16-bit to 8-bit
		ph0 = _mm_packus_epi16((__m128i)ph0,(__m128i)ph4);
		ph1 = _mm_packus_epi16((__m128i)ph1,(__m128i)ph5);
		ph2 = _mm_packus_epi16((__m128i)ph2,(__m128i)ph6);
		ph3 = _mm_packus_epi16((__m128i)ph3,(__m128i)ph7);
		
		
		//do the same thing to back half(4 number) from 256-bit avx to 128bit
		_mm_store_si128(bs0+k,ph0);
		_mm_store_si128(bs1+k,ph1);
		_mm_store_si128(bs2+k,ph2);
		_mm_store_si128(bs3+k,ph3);
		
		//pack second half
		l0 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+0],1);
		l1 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+1],1);
		l2 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+2],1);
		l3 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+3],1);
		
		l4 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+4],1);
		l5 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+5],1);
		l6 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+6],1);
		l7 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+7],1);
		
		l8 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+8],1);
		l9 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+9],1);
		l10 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+10],1);
		l11 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+11],1);
		
		l12 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+12],1);
		l13 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+13],1);
		l14 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+14],1);
		l15 = _mm256_extractf128_ps((__m256)avx_bytes[offset0+15],1);

		//transpose matrix
		_MM_TRANSPOSE4_PS(l0,l1,l2,l3);
		_MM_TRANSPOSE4_PS(l4,l5,l6,l7);
		_MM_TRANSPOSE4_PS(l8,l9,l10,l11);
		_MM_TRANSPOSE4_PS(l12,l13,l14,l15);
		
		//compress every 32-bit to 16-bit
		ph0 = _mm_packus_epi32((__m128i)l0,(__m128i)l4);
		ph1 = _mm_packus_epi32((__m128i)l1,(__m128i)l5);
		ph2 = _mm_packus_epi32((__m128i)l2,(__m128i)l6);
		ph3 = _mm_packus_epi32((__m128i)l3,(__m128i)l7);
		
		ph4 = _mm_packus_epi32((__m128i)l8,(__m128i)l12);
		ph5 = _mm_packus_epi32((__m128i)l9,(__m128i)l13);
		ph6 = _mm_packus_epi32((__m128i)l10,(__m128i)l14);
		ph7 = _mm_packus_epi32((__m128i)l11,(__m128i)l15);
		
		//compress every 16-bit to 8-bit(Notice)
		ph0 = _mm_packus_epi16((__m128i)ph0,(__m128i)ph4);
		ph1 = _mm_packus_epi16((__m128i)ph1,(__m128i)ph5);
		ph2 = _mm_packus_epi16((__m128i)ph2,(__m128i)ph6);
		ph3 = _mm_packus_epi16((__m128i)ph3,(__m128i)ph7);
		
		//store back
		//(256*3)*(5/4)=960(Total number)
		//(128 every store bit)/(8 bit/number)=32number
		//pointer space 128bit 
		
		_mm_store_si128(bs4+k,ph0);
		_mm_store_si128(bs5+k,ph1);
		_mm_store_si128(bs6+k,ph2);
		_mm_store_si128(bs7+k,ph3);
		
		//depend on how many lines in this part
		offset0 += 16;
	}
}

void avx_load_8bit_16bit(const float * cfbs0, const float * cfbs1, 
					const float * cfbs2, const float * cfbs3, 
					__m256i * avx_bytes, uint16_t size){
						
	/*--------------------------------------------------------*/
	/*------------------Load to avx_bytes---------------------*/
	/*--------------------------------------------------------*/
	
	__m128 l0,l1,l2,l3,l4,l5,l6,l7;
	__m256i l0_256,l1_256,l2_256,l3_256;
	
	int p=0;
	int i;
	
	const float * cfbs4, * cfbs5, * cfbs6, * cfbs7;
	cfbs4 = cfbs0+size*8/(32*2);
	cfbs5 = cfbs1+size*8/(32*2);
	cfbs6 = cfbs2+size*8/(32*2);
	cfbs7 = cfbs3+size*8/(32*2);
	
	// i = size/32
	for(i = 0;i<(size)/32;i++){
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
}

void avx_store_16bit_KN(__m256i * avx_data_new, __m256i data0[SABER_K][SABER_N/16], __m256i data1[SABER_K][SABER_N/16], 
												__m256i data2[SABER_K][SABER_N/16], __m256i data3[SABER_K][SABER_N/16]){
	__m128 l0,l1,l2,l3,l4,l5,l6,l7;
	__m128 l8,l9,l10,l11,l12,l13,l14,l15;
	
	__m128i ph0,ph1,ph2,ph3;
	__m128i ph4,ph5,ph6,ph7;
	
	int offset0 = 0;
	int k,m,n;
	//store [0][0:15] - [1][0:7]
	for(k=0;k<SABER_K*(SABER_N/16)/2;k++){
		n = k / 16;
		m = k % 16;
		// get the front half(4 number) from 256-bit avx to 128bit
		l0 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+0],0);
		l1 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+1],0);
		l2 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+2],0);
		l3 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+3],0);
		
		l4 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+4],0);
		l5 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+5],0);
		l6 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+6],0);
		l7 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+7],0);
		
		l8 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+8],0);
		l9 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+9],0);
		l10 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+10],0);
		l11 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+11],0);
		
		l12 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+12],0);
		l13 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+13],0);
		l14 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+14],0);
		l15 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+15],0);

		// transpose matrix
		// l0 =d0 [0 :3] ,l1 =d1 [0 :3] ,l2 =d2 [0:3]  ,l3 =d3 [0 :3]
		// l4 =d0 [4 :7] ,l5 =d1 [4 :7] ,l6 =d2 [4:7]  ,l7 =d3 [4 :7]
		// l8 =d0 [8 :11],l9 =d1 [8 :11],l10=d2 [8:11] ,l11=d3 [8 :11]
		// l12=d0 [12:15],l13=d1 [12:15],l14=d2 [12:15],l15=d3 [12:15]
		_MM_TRANSPOSE4_PS(l0,l1,l2,l3);
		_MM_TRANSPOSE4_PS(l4,l5,l6,l7);
		_MM_TRANSPOSE4_PS(l8,l9,l10,l11);
		_MM_TRANSPOSE4_PS(l12,l13,l14,l15);
		
		// compress every 32-bit to 16-bit
		// ph0 = d0[0:7] , ph1 = d1[0:7] , ph2 = d2[0:7] , ph3 = d3[0:7]
		// ph4 = d0[8:15], ph5 = d1[8:15], ph6 = d2[8:15], ph7 = d3[0:7]
		ph0 = _mm_packs_epi32((__m128i)l0,(__m128i)l4);
		ph1 = _mm_packs_epi32((__m128i)l1,(__m128i)l5);
		ph2 = _mm_packs_epi32((__m128i)l2,(__m128i)l6);
		ph3 = _mm_packs_epi32((__m128i)l3,(__m128i)l7);
		ph4 = _mm_packs_epi32((__m128i)l8,(__m128i)l12);
		ph5 = _mm_packs_epi32((__m128i)l9,(__m128i)l13);
		ph6 = _mm_packs_epi32((__m128i)l10,(__m128i)l14);
		ph7 = _mm_packs_epi32((__m128i)l11,(__m128i)l15);
		
		
		// do the same thing to back half(4 number) from 256-bit avx to 128bit
		// data0 = d0[0:16]
		data0[n][m] = _mm256_insertf128_si256(_mm256_castsi128_si256(ph0),ph4,1);
		data1[n][m] = _mm256_insertf128_si256(_mm256_castsi128_si256(ph1),ph5,1);
		data2[n][m] = _mm256_insertf128_si256(_mm256_castsi128_si256(ph2),ph6,1);
		data3[n][m] = _mm256_insertf128_si256(_mm256_castsi128_si256(ph3),ph7,1);
		
		
		//store [1][8:15] - [2][0:15]
		n = (SABER_K * (SABER_N/16)/2 + k) / 16;
		m = (SABER_K * (SABER_N/16)/2 + k) % 16;
		
		l0 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+0],1);
		l1 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+1],1);
		l2 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+2],1);
		l3 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+3],1);
		
		l4 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+4],1);
		l5 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+5],1);
		l6 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+6],1);
		l7 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+7],1);
		
		l8 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+8],1);
		l9 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+9],1);
		l10 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+10],1);
		l11 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+11],1);
		
		l12 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+12],1);
		l13 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+13],1);
		l14 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+14],1);
		l15 = _mm256_extractf128_ps((__m256)avx_data_new[offset0+15],1);

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

		
		data0[n][m] = _mm256_insertf128_si256(_mm256_castsi128_si256(ph0),ph4,1);
		data1[n][m] = _mm256_insertf128_si256(_mm256_castsi128_si256(ph1),ph5,1);
		data2[n][m] = _mm256_insertf128_si256(_mm256_castsi128_si256(ph2),ph6,1);
		data3[n][m] = _mm256_insertf128_si256(_mm256_castsi128_si256(ph3),ph7,1);
		
		offset0 += 16;
		
	}
}



void SABER_pack_3bit(uint8_t *bytes, uint16_t *data){

	uint32_t j;
	uint32_t offset_data=0,offset_byte=0;
	
	offset_byte=0;
	for(j=0;j<SABER_N/8;j++){
		offset_byte=3*j;
		offset_data=8*j;
		bytes[offset_byte + 0]= (data[offset_data + 0] & 0x7) | ( (data[offset_data + 1] & 0x7)<<3 ) | ((data[offset_data + 2] & 0x3)<<6);
		bytes[offset_byte + 1]= ((data[offset_data + 2] >> 2 ) & 0x01)  | ( (data[offset_data + 3] & 0x7)<<1 ) | ( (data[offset_data + 4] & 0x7)<<4 ) | (((data[offset_data + 5]) & 0x01)<<7);
		bytes[offset_byte + 2]= ((data[offset_data + 5] >> 1 ) & 0x03) | ( (data[offset_data + 6] & 0x7)<<2 ) | ( (data[offset_data + 7] & 0x7)<<5 );
	}
}

void SABER_un_pack3bit(uint8_t *bytes, uint16_t *data){

	uint32_t j;
	uint32_t offset_data=0,offset_byte=0;	
	
	offset_byte=0;
	for(j=0;j<SABER_N/8;j++){
		offset_byte=3*j;
		offset_data=8*j;
		data[offset_data + 0] = (bytes[offset_byte+0])&0x07;
		data[offset_data + 1] = ( (bytes[offset_byte+0])>>3 )&0x07;
		data[offset_data + 2] = ( ( (bytes[offset_byte+0])>>6 )&0x03) | ( ( (bytes[offset_byte+1])&0x01)<<2 );
		data[offset_data + 3] = ( (bytes[offset_byte+1])>>1 )&0x07;
		data[offset_data + 4] = ( (bytes[offset_byte+1])>>4 )&0x07;
		data[offset_data + 5] = ( ( (bytes[offset_byte+1])>>7 )&0x01) | ( ( (bytes[offset_byte+2])&0x03)<<1 );
		data[offset_data + 6] = ( (bytes[offset_byte+2]>>2)&0x07 );
		data[offset_data + 7] = ( (bytes[offset_byte+2]>>5)&0x07 );
	}

}


void SABER_pack_4bit(uint8_t *bytes, uint16_t *data){

	uint32_t j;
	uint32_t offset_data=0;
	
	for(j=0;j<SABER_N/2;j++)
	{
		offset_data=2*j;
		bytes[j]= (data[offset_data] & 0x0f) | ( (data[offset_data + 1] & 0x0f)<<4 );
	}
	
}

void SABER_pack_4bitX4(uint8_t *bytes0, uint8_t *bytes1, uint8_t *bytes2, uint8_t *bytes3, uint16_t *data0, uint16_t *data1, uint16_t *data2, uint16_t *data3){
	uint32_t i,j,k;
	uint32_t offset_data=0;
	
	__m256i avx_data[256];
	for(i=0;i<256;++i){
		avx_data[i] = _mm256_set_epi64x(data3[i], data2[i], data1[i], data0[i]);
	}
	
	__m256i avx_bytes[128];
	__m256i avx_epi64_0f = _mm256_set1_epi64x(0x0f);
	for(j=0;j<SABER_N/2;++j)
	{
		offset_data=2*j;
		avx_bytes[j]= _mm256_or_si256((_mm256_and_si256(avx_data[offset_data],avx_epi64_0f)),(_mm256_slli_epi64(_mm256_and_si256(avx_data[offset_data + 1],avx_epi64_0f),4)));
	}

	__m256i *avx_byte0_ptr = (__m256i*)bytes0;
	__m256i *avx_byte1_ptr = (__m256i*)bytes1;
	__m256i *avx_byte2_ptr = (__m256i*)bytes2;
	__m256i *avx_byte3_ptr = (__m256i*)bytes3;
	
	//k<4
	uint32_t offset_bytes = 0;
	//256/8=everytime store 32 value
	//totally have SABER_N/2 = 128 value need to be stored
	//(SABER_N/2)/(256/8)
	
	__m256i temp_byte0, temp_byte1, temp_byte2, temp_byte3;
	for(k=0;k<4;++k){

		offset_bytes = (256/8)*k;

		temp_byte0 = _mm256_set_epi8(avx_bytes[offset_bytes + 31][0], avx_bytes[offset_bytes + 30][0], avx_bytes[offset_bytes + 29][0], avx_bytes[offset_bytes + 28][0],
						avx_bytes[offset_bytes + 27][0], avx_bytes[offset_bytes + 26][0], avx_bytes[offset_bytes + 25][0], avx_bytes[offset_bytes + 24][0],
						avx_bytes[offset_bytes + 23][0], avx_bytes[offset_bytes + 22][0], avx_bytes[offset_bytes + 21][0], avx_bytes[offset_bytes + 20][0],
						avx_bytes[offset_bytes + 19][0], avx_bytes[offset_bytes + 18][0], avx_bytes[offset_bytes + 17][0], avx_bytes[offset_bytes + 16][0],
						avx_bytes[offset_bytes + 15][0], avx_bytes[offset_bytes + 14][0], avx_bytes[offset_bytes + 13][0], avx_bytes[offset_bytes + 12][0],
						avx_bytes[offset_bytes + 11][0], avx_bytes[offset_bytes + 10][0], avx_bytes[offset_bytes + 9][0], avx_bytes[offset_bytes + 8][0],
						avx_bytes[offset_bytes + 7][0], avx_bytes[offset_bytes + 6][0], avx_bytes[offset_bytes + 5][0], avx_bytes[offset_bytes + 4][0],
						avx_bytes[offset_bytes + 3][0], avx_bytes[offset_bytes + 2][0], avx_bytes[offset_bytes + 1][0], avx_bytes[offset_bytes + 0][0]);
				_mm256_storeu_si256(avx_byte0_ptr+k,temp_byte0);
		
		temp_byte1 = _mm256_set_epi8(avx_bytes[offset_bytes + 31][1], avx_bytes[offset_bytes + 30][1], avx_bytes[offset_bytes + 29][1], avx_bytes[offset_bytes + 28][1],
						avx_bytes[offset_bytes + 27][1], avx_bytes[offset_bytes + 26][1], avx_bytes[offset_bytes + 25][1], avx_bytes[offset_bytes + 24][1],
						avx_bytes[offset_bytes + 23][1], avx_bytes[offset_bytes + 22][1], avx_bytes[offset_bytes + 21][1], avx_bytes[offset_bytes + 20][1],
						avx_bytes[offset_bytes + 19][1], avx_bytes[offset_bytes + 18][1], avx_bytes[offset_bytes + 17][1], avx_bytes[offset_bytes + 16][1],
						avx_bytes[offset_bytes + 15][1], avx_bytes[offset_bytes + 14][1], avx_bytes[offset_bytes + 13][1], avx_bytes[offset_bytes + 12][1],
						avx_bytes[offset_bytes + 11][1], avx_bytes[offset_bytes + 10][1], avx_bytes[offset_bytes + 9][1], avx_bytes[offset_bytes + 8][1],
						avx_bytes[offset_bytes + 7][1], avx_bytes[offset_bytes + 6][1], avx_bytes[offset_bytes + 5][1], avx_bytes[offset_bytes + 4][1],
						avx_bytes[offset_bytes + 3][1], avx_bytes[offset_bytes + 2][1], avx_bytes[offset_bytes + 1][1], avx_bytes[offset_bytes + 0][1]);
				_mm256_storeu_si256(avx_byte1_ptr+k,temp_byte1);
						
		temp_byte2 = _mm256_set_epi8(avx_bytes[offset_bytes + 31][2], avx_bytes[offset_bytes + 30][2], avx_bytes[offset_bytes + 29][2], avx_bytes[offset_bytes + 28][2],
						avx_bytes[offset_bytes + 27][2], avx_bytes[offset_bytes + 26][2], avx_bytes[offset_bytes + 25][2], avx_bytes[offset_bytes + 24][2],
						avx_bytes[offset_bytes + 23][2], avx_bytes[offset_bytes + 22][2], avx_bytes[offset_bytes + 21][2], avx_bytes[offset_bytes + 20][2],
						avx_bytes[offset_bytes + 19][2], avx_bytes[offset_bytes + 18][2], avx_bytes[offset_bytes + 17][2], avx_bytes[offset_bytes + 16][2],
						avx_bytes[offset_bytes + 15][2], avx_bytes[offset_bytes + 14][2], avx_bytes[offset_bytes + 13][2], avx_bytes[offset_bytes + 12][2],
						avx_bytes[offset_bytes + 11][2], avx_bytes[offset_bytes + 10][2], avx_bytes[offset_bytes + 9][2], avx_bytes[offset_bytes + 8][2],
						avx_bytes[offset_bytes + 7][2], avx_bytes[offset_bytes + 6][2], avx_bytes[offset_bytes + 5][2], avx_bytes[offset_bytes + 4][2],
						avx_bytes[offset_bytes + 3][2], avx_bytes[offset_bytes + 2][2], avx_bytes[offset_bytes + 1][2], avx_bytes[offset_bytes + 0][2]);
				_mm256_storeu_si256(avx_byte2_ptr+k,temp_byte2);
						
		temp_byte3 = _mm256_set_epi8(avx_bytes[offset_bytes + 31][3], avx_bytes[offset_bytes + 30][3], avx_bytes[offset_bytes + 29][3], avx_bytes[offset_bytes + 28][3],
						avx_bytes[offset_bytes + 27][3], avx_bytes[offset_bytes + 26][3], avx_bytes[offset_bytes + 25][3], avx_bytes[offset_bytes + 24][3],
						avx_bytes[offset_bytes + 23][3], avx_bytes[offset_bytes + 22][3], avx_bytes[offset_bytes + 21][3], avx_bytes[offset_bytes + 20][3],
						avx_bytes[offset_bytes + 19][3], avx_bytes[offset_bytes + 18][3], avx_bytes[offset_bytes + 17][3], avx_bytes[offset_bytes + 16][3],
						avx_bytes[offset_bytes + 15][3], avx_bytes[offset_bytes + 14][3], avx_bytes[offset_bytes + 13][3], avx_bytes[offset_bytes + 12][3],
						avx_bytes[offset_bytes + 11][3], avx_bytes[offset_bytes + 10][3], avx_bytes[offset_bytes + 9][3], avx_bytes[offset_bytes + 8][3],
						avx_bytes[offset_bytes + 7][3], avx_bytes[offset_bytes + 6][3], avx_bytes[offset_bytes + 5][3], avx_bytes[offset_bytes + 4][3],
						avx_bytes[offset_bytes + 3][3], avx_bytes[offset_bytes + 2][3], avx_bytes[offset_bytes + 1][3], avx_bytes[offset_bytes + 0][3]);
				_mm256_storeu_si256(avx_byte3_ptr+k,temp_byte3);
	}

}






void SABER_un_pack4bit(const unsigned char *bytes, uint16_t *Mask_ar){

	uint32_t j;
	uint32_t offset_data=0;
	
	for(j=0;j<SABER_N/2;j++)
	{
		offset_data=2*j;
		Mask_ar[offset_data] = bytes[j] & 0x0f;
		Mask_ar[offset_data+1] = (bytes[j]>>4) & 0x0f;
	}
}

void SABER_un_pack4bitX4(const unsigned char *bytes0, const unsigned char *bytes1, const unsigned char *bytes2, const unsigned char *bytes3, 
		uint16_t *Mask_ar0, uint16_t *Mask_ar1, uint16_t *Mask_ar2, uint16_t *Mask_ar3){

	uint32_t j;
	uint32_t offset_data=0;
	
	for(j=0;j<SABER_N/2;j++)
	{
		offset_data=2*j;
		Mask_ar0[offset_data] = bytes0[j] & 0x0f;
		Mask_ar0[offset_data+1] = (bytes0[j]>>4) & 0x0f;
		
		Mask_ar1[offset_data] = bytes1[j] & 0x0f;
		Mask_ar1[offset_data+1] = (bytes1[j]>>4) & 0x0f;

		Mask_ar2[offset_data] = bytes2[j] & 0x0f;
		Mask_ar2[offset_data+1] = (bytes2[j]>>4) & 0x0f;

		Mask_ar3[offset_data] = bytes3[j] & 0x0f;
		Mask_ar3[offset_data+1] = (bytes3[j]>>4) & 0x0f;
	}
}


void SABER_pack_6bit(uint8_t *bytes, uint16_t *data){

	uint32_t j;
	uint32_t offset_data=0,offset_byte=0;
	
	offset_byte=0;
	for(j=0;j<SABER_N/4;j++){
		offset_byte=3*j;
		offset_data=4*j;
		bytes[offset_byte + 0]= (data[offset_data + 0]&0x3f) | ((data[offset_data+1]&0x03)<<6);
 		bytes[offset_byte + 1]= ((data[offset_data+1]>>2)&0x0f) | ((data[offset_data+2]&0x0f)<<4);
 		bytes[offset_byte + 2]= ((data[offset_data+2]>>4)&0x03) | ((data[offset_data+3]&0x3f)<<2);
	}
}

void SABER_un_pack6bit(const unsigned char *bytes, uint16_t *data){

	uint32_t j;
	uint32_t offset_data=0,offset_byte=0;	
	
	offset_byte=0;
	for(j=0;j<SABER_N/4;j++){
		offset_byte=3*j;
		offset_data=4*j;
		data[offset_data + 0] = bytes[offset_byte+0]&0x3f;
		data[offset_data + 1] = ((bytes[offset_byte+0]>>6)&0x03) |  ((bytes[offset_byte+1]&0x0f)<<2)  ;
		data[offset_data + 2] = ((bytes[offset_byte+1]&0xff)>>4) | ((bytes[offset_byte+2]&0x03)<<4) ;
		data[offset_data + 3] = ((bytes[offset_byte+2]&0xff)>>2);
	}

}

void SABER_pack10bit(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
	
	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
	
	offset_byte=0;
	for(i=0;i<SABER_K;i++){
		offset_byte1=i*(SABER_N*10)/8;
		for(j=0;j<SABER_N/4;j++){
			offset_byte=offset_byte1+5*j;
			offset_data=4*j;
			bytes[offset_byte + 0]= ( data[i][ offset_data + 0 ] & (0xff));

			bytes[offset_byte + 1]= ( (data[i][ offset_data + 0 ] >>8) & 0x03 ) | ((data[i][ offset_data + 1 ] & 0x3f) << 2);

			bytes[offset_byte + 2]= ( (data[i][ offset_data + 1 ] >>6) & 0x0f ) | ( (data[i][ offset_data + 2 ] &0x0f) << 4);

			bytes[offset_byte + 3]= ( (data[i][ offset_data + 2 ] >>4) & 0x3f ) | ((data[i][ offset_data + 3 ] & 0x03) << 6);

			bytes[offset_byte + 4]= ( (data[i][ offset_data + 3 ] >>2) & 0xff );
		}
	}
}



void POLVECp2BS(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){

	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
	
	offset_byte=0;
	for(i=0;i<SABER_K;i++){
		offset_byte1=i*(SABER_N*10)/8;
		for(j=0;j<SABER_N/4;j++){
			offset_byte=offset_byte1+5*j;
			offset_data=4*j;
			bytes[offset_byte + 0]= ( data[i][ offset_data + 0 ] & (0xff));

			bytes[offset_byte + 1]= ( (data[i][ offset_data + 0 ] >>8) & 0x03 ) | ((data[i][ offset_data + 1 ] & 0x3f) << 2);

			bytes[offset_byte + 2]= ( (data[i][ offset_data + 1 ] >>6) & 0x0f ) | ( (data[i][ offset_data + 2 ] &0x0f) << 4);

			bytes[offset_byte + 3]= ( (data[i][ offset_data + 2 ] >>4) & 0x3f ) | ((data[i][ offset_data + 3 ] & 0x03) << 6);

			bytes[offset_byte + 4]= ( (data[i][ offset_data + 3 ] >>2) & 0xff );
			
		}
	}
	
}

void POLVECp2BSX4(uint8_t *bytes0, uint8_t *bytes1, uint8_t *bytes2, uint8_t *bytes3, 
				uint16_t data0[SABER_K][SABER_N], uint16_t data1[SABER_K][SABER_N], 
				uint16_t data2[SABER_K][SABER_N], uint16_t data3[SABER_K][SABER_N]){
	uint16_t size = 960;
	/*--------------------------------------------------------*/
	/*------------------Load to avx_bytes---------------------*/
	/*--------------------------------------------------------*/
	
	__m256i avx_data[SABER_K*SABER_N/2];
	//num = (SABER_N*SABER_K)*(5/4)/2
	__m256i avx_bytes[480];
	
	
	const float * cfbs0 = (const float *)&data0[0];
	const float * cfbs1 = (const float *)&data1[0];
	const float * cfbs2 = (const float *)&data2[0];
	const float * cfbs3 = (const float *)&data3[0];
	
	const float * cfbs4 = (const float *)&data0[SABER_K/2][SABER_N/2];
	const float * cfbs5 = (const float *)&data1[SABER_K/2][SABER_N/2];
	const float * cfbs6 = (const float *)&data2[SABER_K/2][SABER_N/2];
	const float * cfbs7 = (const float *)&data3[SABER_K/2][SABER_N/2];
	
	avx_load_16bit_8bit(cfbs0, cfbs1, cfbs2, cfbs3, cfbs4, cfbs5, cfbs6, cfbs7, &avx_data[0]);
	
	/*--------------------------------------------------------*/
	/*---------------------Do the shifts----------------------*/
	/*--------------------------------------------------------*/
	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;
	
	offset_byte=0;
	for(i=0;i<SABER_K;++i){
		offset_byte1=i*(SABER_N*10)/8;
		for(j=0;j<SABER_N/(4*2);++j){
			offset_byte=offset_byte1/2+5*j;
			offset_data=4*j;
			avx_bytes[offset_byte + 0]= _mm256_and_si256(avx_data[SABER_N *i/2 + offset_data + 0 ],avx_epi32_ff);

			avx_bytes[offset_byte + 1]= _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_data[SABER_N *i/2 + offset_data + 0 ],8),avx_epi32_03),_mm256_slli_epi32(_mm256_and_si256(avx_data[SABER_N *i/2 + offset_data + 1 ],avx_epi32_3f),2));

			avx_bytes[offset_byte + 2]= _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_data[SABER_N *i/2 + offset_data + 1 ],6),avx_epi32_0f),_mm256_slli_epi32(_mm256_and_si256(avx_data[SABER_N *i/2 + offset_data + 2 ],avx_epi32_0f),4));

			avx_bytes[offset_byte + 3]= _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_data[SABER_N *i/2 + offset_data + 2 ],4),avx_epi32_3f),_mm256_slli_epi32(_mm256_and_si256(avx_data[SABER_N *i/2 + offset_data + 3 ],avx_epi32_03),6));

			avx_bytes[offset_byte + 4]= _mm256_and_si256(_mm256_srli_epi32(avx_data[SABER_N *i/2 + offset_data + 3 ],2),avx_epi32_ff);
		}
	}
	
	/*--------------------------------------------------------*/
	/*---------------------Store back-------------------------*/
	/*--------------------------------------------------------*/
	
	__m128i * bs0 = (__m128i *) bytes0;
	__m128i * bs1 = (__m128i *) bytes1;
	__m128i * bs2 = (__m128i *) bytes2;
	__m128i * bs3 = (__m128i *) bytes3;
	
	__m128i * bs4 = (__m128i *) (bytes0+960/2);
	__m128i * bs5 = (__m128i *) (bytes1+960/2);
	__m128i * bs6 = (__m128i *) (bytes2+960/2);
	__m128i * bs7 = (__m128i *) (bytes3+960/2);
	
	avx_store_8bit_bs(&avx_bytes[0], size/2, bs0, bs1, bs2, bs3, bs4, bs5, bs6, bs7);

}

void old_POLVECp2BSX4(uint8_t *bytes0, uint8_t *bytes1, uint8_t *bytes2, uint8_t *bytes3, 
				uint16_t data0[SABER_K][SABER_N], uint16_t data1[SABER_K][SABER_N], uint16_t data2[SABER_K][SABER_N], uint16_t data3[SABER_K][SABER_N]){
	
	__m256i avx_epi64_03, avx_epi64_0f, avx_epi64_3f, avx_epi64_ff;
	avx_epi64_03 = _mm256_set1_epi64x(0x03);
	avx_epi64_0f = _mm256_set1_epi64x(0x0f);
	avx_epi64_3f = _mm256_set1_epi64x(0x3f);
	avx_epi64_ff = _mm256_set1_epi64x(0xff);
	
	__m256i avx_data[SABER_K*SABER_N];
	uint32_t k,n,m = 0;
	for(k=0;k<SABER_K;++k){
		for(n=0;n<SABER_N;++n){
			avx_data[k*SABER_N+n] = _mm256_set_epi64x(data3[k][n], data2[k][n], data1[k][n], data0[k][n]);
		}
	}
	
	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;
	
	uint16_t para = (SABER_K-1)*((SABER_N*10)/8)+5*(SABER_N/4);
	__m256i avx_bytes[para];
	offset_byte=0;
	for(i=0;i<SABER_K;++i){
		offset_byte1=i*(SABER_N*10)/8;
		for(j=0;j<SABER_N/4;++j){
			offset_byte=offset_byte1+5*j;
			offset_data=4*j;
			avx_bytes[offset_byte + 0]= _mm256_and_si256(avx_data[SABER_N *i + offset_data + 0 ],avx_epi64_ff);

			avx_bytes[offset_byte + 1]= _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi64(avx_data[SABER_N *i + offset_data + 0 ],8),avx_epi64_03),_mm256_slli_epi64(_mm256_and_si256(avx_data[SABER_N *i + offset_data + 1 ],avx_epi64_3f),2));

			avx_bytes[offset_byte + 2]= _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi64(avx_data[SABER_N *i + offset_data + 1 ],6),avx_epi64_0f),_mm256_slli_epi64(_mm256_and_si256(avx_data[SABER_N *i + offset_data + 2 ],avx_epi64_0f),4));

			avx_bytes[offset_byte + 3]= _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi64(avx_data[SABER_N *i + offset_data + 2 ],4),avx_epi64_3f),_mm256_slli_epi64(_mm256_and_si256(avx_data[SABER_N *i + offset_data + 3 ],avx_epi64_03),6));

			avx_bytes[offset_byte + 4]= _mm256_and_si256(_mm256_srli_epi64(avx_data[SABER_N *i + offset_data + 3 ],2),avx_epi64_ff);
		}
	}
	
	__m256i *avx_bytes0_ptr = (__m256i*)bytes0;
	__m256i *avx_bytes1_ptr = (__m256i*)bytes1;
	__m256i *avx_bytes2_ptr = (__m256i*)bytes2;
	__m256i *avx_bytes3_ptr = (__m256i*)bytes3;

	uint16_t counter = ((SABER_N*10)/8*(SABER_K-1)+5*(SABER_N/4))/32;
	uint16_t offset_bytes;
	__m256i temp_byte0, temp_byte1, temp_byte2, temp_byte3;
	
	for(m=0;m<counter;++m){
		offset_bytes = (256/8)*m;

		temp_byte0 = _mm256_set_epi8(avx_bytes[offset_bytes + 31][0], avx_bytes[offset_bytes + 30][0], avx_bytes[offset_bytes + 29][0], avx_bytes[offset_bytes + 28][0],
						avx_bytes[offset_bytes + 27][0], avx_bytes[offset_bytes + 26][0], avx_bytes[offset_bytes + 25][0], avx_bytes[offset_bytes + 24][0],
						avx_bytes[offset_bytes + 23][0], avx_bytes[offset_bytes + 22][0], avx_bytes[offset_bytes + 21][0], avx_bytes[offset_bytes + 20][0],
						avx_bytes[offset_bytes + 19][0], avx_bytes[offset_bytes + 18][0], avx_bytes[offset_bytes + 17][0], avx_bytes[offset_bytes + 16][0],
						avx_bytes[offset_bytes + 15][0], avx_bytes[offset_bytes + 14][0], avx_bytes[offset_bytes + 13][0], avx_bytes[offset_bytes + 12][0],
						avx_bytes[offset_bytes + 11][0], avx_bytes[offset_bytes + 10][0], avx_bytes[offset_bytes + 9][0], avx_bytes[offset_bytes + 8][0],
						avx_bytes[offset_bytes + 7][0], avx_bytes[offset_bytes + 6][0], avx_bytes[offset_bytes + 5][0], avx_bytes[offset_bytes + 4][0],
						avx_bytes[offset_bytes + 3][0], avx_bytes[offset_bytes + 2][0], avx_bytes[offset_bytes + 1][0], avx_bytes[offset_bytes + 0][0]);
				_mm256_storeu_si256(avx_bytes0_ptr+m,temp_byte0);
				
				

		temp_byte1 = _mm256_set_epi8(avx_bytes[offset_bytes + 31][1], avx_bytes[offset_bytes + 30][1], avx_bytes[offset_bytes + 29][1], avx_bytes[offset_bytes + 28][1],
						avx_bytes[offset_bytes + 27][1], avx_bytes[offset_bytes + 26][1], avx_bytes[offset_bytes + 25][1], avx_bytes[offset_bytes + 24][1],
						avx_bytes[offset_bytes + 23][1], avx_bytes[offset_bytes + 22][1], avx_bytes[offset_bytes + 21][1], avx_bytes[offset_bytes + 20][1],
						avx_bytes[offset_bytes + 19][1], avx_bytes[offset_bytes + 18][1], avx_bytes[offset_bytes + 17][1], avx_bytes[offset_bytes + 16][1],
						avx_bytes[offset_bytes + 15][1], avx_bytes[offset_bytes + 14][1], avx_bytes[offset_bytes + 13][1], avx_bytes[offset_bytes + 12][1],
						avx_bytes[offset_bytes + 11][1], avx_bytes[offset_bytes + 10][1], avx_bytes[offset_bytes + 9][1], avx_bytes[offset_bytes + 8][1],
						avx_bytes[offset_bytes + 7][1], avx_bytes[offset_bytes + 6][1], avx_bytes[offset_bytes + 5][1], avx_bytes[offset_bytes + 4][1],
						avx_bytes[offset_bytes + 3][1], avx_bytes[offset_bytes + 2][1], avx_bytes[offset_bytes + 1][1], avx_bytes[offset_bytes + 0][1]);
				_mm256_storeu_si256(avx_bytes1_ptr+m,temp_byte1);
						

		temp_byte2 = _mm256_set_epi8(avx_bytes[offset_bytes + 31][2], avx_bytes[offset_bytes + 30][2], avx_bytes[offset_bytes + 29][2], avx_bytes[offset_bytes + 28][2],
						avx_bytes[offset_bytes + 27][2], avx_bytes[offset_bytes + 26][2], avx_bytes[offset_bytes + 25][2], avx_bytes[offset_bytes + 24][2],
						avx_bytes[offset_bytes + 23][2], avx_bytes[offset_bytes + 22][2], avx_bytes[offset_bytes + 21][2], avx_bytes[offset_bytes + 20][2],
						avx_bytes[offset_bytes + 19][2], avx_bytes[offset_bytes + 18][2], avx_bytes[offset_bytes + 17][2], avx_bytes[offset_bytes + 16][2],
						avx_bytes[offset_bytes + 15][2], avx_bytes[offset_bytes + 14][2], avx_bytes[offset_bytes + 13][2], avx_bytes[offset_bytes + 12][2],
						avx_bytes[offset_bytes + 11][2], avx_bytes[offset_bytes + 10][2], avx_bytes[offset_bytes + 9][2], avx_bytes[offset_bytes + 8][2],
						avx_bytes[offset_bytes + 7][2], avx_bytes[offset_bytes + 6][2], avx_bytes[offset_bytes + 5][2], avx_bytes[offset_bytes + 4][2],
						avx_bytes[offset_bytes + 3][2], avx_bytes[offset_bytes + 2][2], avx_bytes[offset_bytes + 1][2], avx_bytes[offset_bytes + 0][2]);
				_mm256_storeu_si256(avx_bytes2_ptr+m,temp_byte2);
						

		temp_byte3 = _mm256_set_epi8(avx_bytes[offset_bytes + 31][3], avx_bytes[offset_bytes + 30][3], avx_bytes[offset_bytes + 29][3], avx_bytes[offset_bytes + 28][3],
						avx_bytes[offset_bytes + 27][3], avx_bytes[offset_bytes + 26][3], avx_bytes[offset_bytes + 25][3], avx_bytes[offset_bytes + 24][3],
						avx_bytes[offset_bytes + 23][3], avx_bytes[offset_bytes + 22][3], avx_bytes[offset_bytes + 21][3], avx_bytes[offset_bytes + 20][3],
						avx_bytes[offset_bytes + 19][3], avx_bytes[offset_bytes + 18][3], avx_bytes[offset_bytes + 17][3], avx_bytes[offset_bytes + 16][3],
						avx_bytes[offset_bytes + 15][3], avx_bytes[offset_bytes + 14][3], avx_bytes[offset_bytes + 13][3], avx_bytes[offset_bytes + 12][3],
						avx_bytes[offset_bytes + 11][3], avx_bytes[offset_bytes + 10][3], avx_bytes[offset_bytes + 9][3], avx_bytes[offset_bytes + 8][3],
						avx_bytes[offset_bytes + 7][3], avx_bytes[offset_bytes + 6][3], avx_bytes[offset_bytes + 5][3], avx_bytes[offset_bytes + 4][3],
						avx_bytes[offset_bytes + 3][3], avx_bytes[offset_bytes + 2][3], avx_bytes[offset_bytes + 1][3], avx_bytes[offset_bytes + 0][3]);
				_mm256_storeu_si256(avx_bytes3_ptr+m,temp_byte3);

	}
}



void POLVECq2BS(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
	
	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
	
	offset_byte=0;
	for(i=0;i<SABER_K;i++){
		offset_byte1=i*(SABER_N*13)/8;
		for(j=0;j<SABER_N/8;j++){
			offset_byte=offset_byte1+13*j;
			offset_data=8*j;
			bytes[offset_byte + 0]= ( data[i][ offset_data + 0 ] & (0xff));

			bytes[offset_byte + 1]= ( (data[i][ offset_data + 0 ] >>8) & 0x1f ) | ((data[i][ offset_data + 1 ] & 0x07) << 5);

			bytes[offset_byte + 2]= ( (data[i][ offset_data + 1 ] >>3) & 0xff );

			bytes[offset_byte + 3]= ( (data[i][ offset_data + 1 ] >>11) & 0x03 ) | ((data[i][ offset_data + 2 ] & 0x3f) << 2);

			bytes[offset_byte + 4]= ( (data[i][ offset_data + 2 ] >>6) & 0x7f ) | ( (data[i][ offset_data + 3 ] & 0x01) << 7 );

			bytes[offset_byte + 5]= ( (data[i][ offset_data + 3 ] >>1) & 0xff );

			bytes[offset_byte + 6]= ( (data[i][ offset_data + 3 ] >>9) & 0x0f ) | ( (data[i][ offset_data + 4 ] & 0x0f) << 4 );

			bytes[offset_byte + 7]= ( (data[i][ offset_data + 4] >>4) & 0xff );

			bytes[offset_byte + 8]= ( (data[i][ offset_data + 4 ] >>12) & 0x01 ) | ( (data[i][ offset_data + 5 ] & 0x7f) << 1 );

			bytes[offset_byte + 9]= ( (data[i][ offset_data + 5 ] >>7) & 0x3f ) | ( (data[i][ offset_data + 6 ] & 0x03) << 6 );

			bytes[offset_byte + 10]= ( (data[i][ offset_data + 6 ] >>2) & 0xff );

			bytes[offset_byte + 11]= ( (data[i][ offset_data + 6 ] >>10) & 0x07 ) | ( (data[i][ offset_data + 7 ] & 0x1f) << 3 );

			bytes[offset_byte + 12]= ( (data[i][ offset_data + 7 ] >>5) & 0xff );

		}
	}


}

void POLVECq2BSX4(uint8_t *bytes0, uint8_t *bytes1, uint8_t *bytes2, uint8_t *bytes3, 
				uint16_t data0[SABER_K][SABER_N], uint16_t data1[SABER_K][SABER_N], 
				uint16_t data2[SABER_K][SABER_N], uint16_t data3[SABER_K][SABER_N]){
	uint16_t size = 1248;
	/*--------------------------------------------------------*/
	/*------------------Load to avx_bytes---------------------*/
	/*--------------------------------------------------------*/
	
	__m256i avx_data[SABER_K*SABER_N/2];
	//num = (SABER_N*SABER_K)*(13/8)/2
	__m256i avx_bytes[624];
	
	
	const float * cfbs0 = (const float *)&data0[0];
	const float * cfbs1 = (const float *)&data1[0];
	const float * cfbs2 = (const float *)&data2[0];
	const float * cfbs3 = (const float *)&data3[0];
	
	const float * cfbs4 = (const float *)&data0[SABER_K/2][SABER_N/2];
	const float * cfbs5 = (const float *)&data1[SABER_K/2][SABER_N/2];
	const float * cfbs6 = (const float *)&data2[SABER_K/2][SABER_N/2];
	const float * cfbs7 = (const float *)&data3[SABER_K/2][SABER_N/2];
	
	avx_load_16bit_8bit(cfbs0, cfbs1, cfbs2, cfbs3, cfbs4, cfbs5, cfbs6, cfbs7, &avx_data[0]);
	
	
	/*--------------------------------------------------------*/
	/*---------------------Do the shifts----------------------*/
	/*--------------------------------------------------------*/
	// clock_S11 = cpucycles();
	
	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
	
	offset_byte=0;
	for(i=0;i<SABER_K;++i){
		offset_byte1=i*(SABER_N*13)/8;//832+13*32=416*3=1248
		for(j=0;j<SABER_N/(8*2);++j){
			offset_byte=offset_byte1/2+13*j;
			offset_data=8*j;
			avx_bytes[offset_byte + 0]= _mm256_and_si256( avx_data[SABER_N *i/2 + offset_data + 0 ] , (avx_epi32_ff));

			avx_bytes[offset_byte + 1]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi32( avx_data[SABER_N *i/2 + offset_data + 0 ] ,8) , avx_epi32_1f ) , _mm256_slli_epi32( _mm256_and_si256( avx_data[SABER_N *i/2 + offset_data + 1 ] , avx_epi32_07) , 5));

			avx_bytes[offset_byte + 2]= _mm256_and_si256( _mm256_srli_epi32( avx_data[SABER_N *i/2 + offset_data + 1 ] ,3) , avx_epi32_ff );

			avx_bytes[offset_byte + 3]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi32( avx_data[SABER_N *i/2 + offset_data + 1 ] ,11) , avx_epi32_03 ) , _mm256_slli_epi32( _mm256_and_si256( avx_data[SABER_N *i/2 + offset_data + 2 ] , avx_epi32_3f) , 2));

			avx_bytes[offset_byte + 4]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi32( avx_data[SABER_N *i/2 + offset_data + 2 ] ,6) , avx_epi32_7f ) , _mm256_slli_epi32( _mm256_and_si256( avx_data[SABER_N *i/2 + offset_data + 3 ] , avx_epi32_01) , 7 ));

			avx_bytes[offset_byte + 5]= _mm256_and_si256( _mm256_srli_epi32( avx_data[SABER_N *i/2 + offset_data + 3 ] ,1) , avx_epi32_ff );

			avx_bytes[offset_byte + 6]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi32( avx_data[SABER_N *i/2 + offset_data + 3 ] ,9) , avx_epi32_0f ) , _mm256_slli_epi32( _mm256_and_si256( avx_data[SABER_N *i/2 + offset_data + 4 ] , avx_epi32_0f) , 4 ));

			avx_bytes[offset_byte + 7]= _mm256_and_si256( _mm256_srli_epi32( avx_data[SABER_N *i/2 + offset_data + 4] ,4) , avx_epi32_ff );

			avx_bytes[offset_byte + 8]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi32( avx_data[SABER_N *i/2 + offset_data + 4 ] ,12) , avx_epi32_01 ) , _mm256_slli_epi32( _mm256_and_si256( avx_data[SABER_N *i/2 + offset_data + 5 ] , avx_epi32_7f) , 1 ));

			avx_bytes[offset_byte + 9]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi32( avx_data[SABER_N *i/2 + offset_data + 5 ] ,7) , avx_epi32_3f ) , _mm256_slli_epi32( _mm256_and_si256( avx_data[SABER_N *i/2 + offset_data + 6 ] , avx_epi32_03) , 6 ));

			avx_bytes[offset_byte + 10]= _mm256_and_si256( _mm256_srli_epi32( avx_data[SABER_N *i/2 + offset_data + 6 ] ,2) , avx_epi32_ff );

			avx_bytes[offset_byte + 11]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi32( avx_data[SABER_N *i/2 + offset_data + 6 ] ,10) , avx_epi32_07 ) , _mm256_slli_epi32( _mm256_and_si256( avx_data[SABER_N *i/2 + offset_data + 7 ] , avx_epi32_1f) , 3 ));

			avx_bytes[offset_byte + 12]= _mm256_and_si256( _mm256_srli_epi32( avx_data[SABER_N *i/2 + offset_data + 7 ] ,5) , avx_epi32_ff );
		}
	}
	
	/*--------------------------------------------------------*/
	/*---------------------Store back-------------------------*/
	/*--------------------------------------------------------*/
	
	__m128i * bs0 = (__m128i *) bytes0;
	__m128i * bs1 = (__m128i *) bytes1;
	__m128i * bs2 = (__m128i *) bytes2;
	__m128i * bs3 = (__m128i *) bytes3;
	
	__m128i * bs4 = (__m128i *) (bytes0+size/2);
	__m128i * bs5 = (__m128i *) (bytes1+size/2);
	__m128i * bs6 = (__m128i *) (bytes2+size/2);
	__m128i * bs7 = (__m128i *) (bytes3+size/2);
	
	avx_store_8bit_bs(&avx_bytes[0], size/2, bs0, bs1, bs2, bs3, bs4, bs5, bs6, bs7);
	
}

void old_POLVECq2BSX4(uint8_t *bytes0, uint8_t *bytes1, uint8_t *bytes2, uint8_t *bytes3, 
				uint16_t data0[SABER_K][SABER_N], uint16_t data1[SABER_K][SABER_N], 
				uint16_t data2[SABER_K][SABER_N], uint16_t data3[SABER_K][SABER_N]){
	
	__m256i avx_epi64_01, avx_epi64_03, avx_epi64_07, avx_epi64_0f, avx_epi64_1f, avx_epi64_3f, avx_epi64_7f, avx_epi64_ff;
	avx_epi64_01 = _mm256_set1_epi64x(0x01);
	avx_epi64_03 = _mm256_set1_epi64x(0x03);
	avx_epi64_07 = _mm256_set1_epi64x(0x07);
	avx_epi64_0f = _mm256_set1_epi64x(0x0f);
	avx_epi64_1f = _mm256_set1_epi64x(0x1f);
	avx_epi64_3f = _mm256_set1_epi64x(0x3f);
	avx_epi64_7f = _mm256_set1_epi64x(0x7f);
	avx_epi64_ff = _mm256_set1_epi64x(0xff);
	
	__m256i avx_data[SABER_K*SABER_N];
	uint32_t k,n,m = 0;
	for(k=0;k<SABER_K;++k){
		for(n=0;n<SABER_N;++n){
			avx_data[k*SABER_N+n] = _mm256_set_epi64x(data3[k][n],data2[k][n],data1[k][n], data0[k][n]);
		}
	}
	
	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
	
	uint16_t para = (SABER_K-1)*((SABER_N*13)/8)+13*(SABER_N/8);
	__m256i avx_bytes[para];
	
	offset_byte=0;
	for(i=0;i<SABER_K;++i){
		offset_byte1=i*(SABER_N*13)/8;
		for(j=0;j<SABER_N/8;++j){
			offset_byte=offset_byte1+13*j;
			offset_data=8*j;
			avx_bytes[offset_byte + 0]= _mm256_and_si256(avx_data[SABER_N *i + offset_data + 0 ],(avx_epi64_ff));

			avx_bytes[offset_byte + 1]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi64(avx_data[SABER_N *i + 0 ],8),avx_epi64_1f ),_mm256_slli_epi64(_mm256_and_si256(avx_data[SABER_N *i + 1 ],avx_epi64_07),5));

			avx_bytes[offset_byte + 2]= (_mm256_and_si256( _mm256_srli_epi64(avx_data[SABER_N *i + 1 ],3),avx_epi64_ff ));

			avx_bytes[offset_byte + 3]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi64(avx_data[SABER_N *i + 1 ],11),avx_epi64_03 ),_mm256_slli_epi64(_mm256_and_si256(avx_data[SABER_N *i + 2 ],avx_epi64_3f),2));

			avx_bytes[offset_byte + 4]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi64(avx_data[SABER_N *i + 2 ],6),avx_epi64_7f ),_mm256_slli_epi64(_mm256_and_si256(avx_data[SABER_N *i + 3 ],avx_epi64_01),7));

			avx_bytes[offset_byte + 5]= (_mm256_and_si256( _mm256_srli_epi64(avx_data[SABER_N *i + 3 ],1),avx_epi64_ff ));

			avx_bytes[offset_byte + 6]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi64(avx_data[SABER_N *i + 3 ],9),avx_epi64_0f ),_mm256_slli_epi64(_mm256_and_si256(avx_data[SABER_N *i + 4 ],avx_epi64_0f),4));

			avx_bytes[offset_byte + 7]= (_mm256_and_si256( _mm256_srli_epi64(avx_data[SABER_N *i + 4],4),avx_epi64_ff ));

			avx_bytes[offset_byte + 8]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi64(avx_data[SABER_N *i + 4 ],12),avx_epi64_01 ),_mm256_slli_epi64(_mm256_and_si256(avx_data[SABER_N *i + 5 ],avx_epi64_7f),1));

			avx_bytes[offset_byte + 9]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi64(avx_data[SABER_N *i + 5 ],7),avx_epi64_3f ),_mm256_slli_epi64(_mm256_and_si256(avx_data[SABER_N *i + 6 ],avx_epi64_03),6));

			avx_bytes[offset_byte + 10]= (_mm256_and_si256( _mm256_srli_epi64(avx_data[SABER_N *i + 6 ],2),avx_epi64_ff ));

			avx_bytes[offset_byte + 11]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi64(avx_data[SABER_N *i + 6 ],10),avx_epi64_07 ),_mm256_slli_epi64(_mm256_and_si256(avx_data[SABER_N *i + 7 ],avx_epi64_1f),3));

			avx_bytes[offset_byte + 12]= (_mm256_and_si256( _mm256_srli_epi64(avx_data[SABER_N *i + 7 ],5),avx_epi64_ff));

		}
	}
	
	__m256i *avx_bytes0_ptr = (__m256i*)bytes0;
	__m256i *avx_bytes1_ptr = (__m256i*)bytes1;
	__m256i *avx_bytes2_ptr = (__m256i*)bytes2;
	__m256i *avx_bytes3_ptr = (__m256i*)bytes3;
	uint16_t counter = ((SABER_K-1)*((SABER_N*13)/8)+13*(SABER_N/8))/32;
	uint16_t offset_bytes;
	__m256i temp_byte0, temp_byte1, temp_byte2, temp_byte3;
	
	for(m=0;m<counter;++m){
		offset_bytes = (256/8)*m;

		temp_byte0 = _mm256_set_epi8(avx_bytes[offset_bytes + 31][0], avx_bytes[offset_bytes + 30][0], avx_bytes[offset_bytes + 29][0], avx_bytes[offset_bytes + 28][0],
						avx_bytes[offset_bytes + 27][0], avx_bytes[offset_bytes + 26][0], avx_bytes[offset_bytes + 25][0], avx_bytes[offset_bytes + 24][0],
						avx_bytes[offset_bytes + 23][0], avx_bytes[offset_bytes + 22][0], avx_bytes[offset_bytes + 21][0], avx_bytes[offset_bytes + 20][0],
						avx_bytes[offset_bytes + 19][0], avx_bytes[offset_bytes + 18][0], avx_bytes[offset_bytes + 17][0], avx_bytes[offset_bytes + 16][0],
						avx_bytes[offset_bytes + 15][0], avx_bytes[offset_bytes + 14][0], avx_bytes[offset_bytes + 13][0], avx_bytes[offset_bytes + 12][0],
						avx_bytes[offset_bytes + 11][0], avx_bytes[offset_bytes + 10][0], avx_bytes[offset_bytes + 9][0], avx_bytes[offset_bytes + 8][0],
						avx_bytes[offset_bytes + 7][0], avx_bytes[offset_bytes + 6][0], avx_bytes[offset_bytes + 5][0], avx_bytes[offset_bytes + 4][0],
						avx_bytes[offset_bytes + 3][0], avx_bytes[offset_bytes + 2][0], avx_bytes[offset_bytes + 1][0], avx_bytes[offset_bytes + 0][0]);
				_mm256_storeu_si256(avx_bytes0_ptr+m,temp_byte0);
				
				

		temp_byte1 = _mm256_set_epi8(avx_bytes[offset_bytes + 31][1], avx_bytes[offset_bytes + 30][1], avx_bytes[offset_bytes + 29][1], avx_bytes[offset_bytes + 28][1],
						avx_bytes[offset_bytes + 27][1], avx_bytes[offset_bytes + 26][1], avx_bytes[offset_bytes + 25][1], avx_bytes[offset_bytes + 24][1],
						avx_bytes[offset_bytes + 23][1], avx_bytes[offset_bytes + 22][1], avx_bytes[offset_bytes + 21][1], avx_bytes[offset_bytes + 20][1],
						avx_bytes[offset_bytes + 19][1], avx_bytes[offset_bytes + 18][1], avx_bytes[offset_bytes + 17][1], avx_bytes[offset_bytes + 16][1],
						avx_bytes[offset_bytes + 15][1], avx_bytes[offset_bytes + 14][1], avx_bytes[offset_bytes + 13][1], avx_bytes[offset_bytes + 12][1],
						avx_bytes[offset_bytes + 11][1], avx_bytes[offset_bytes + 10][1], avx_bytes[offset_bytes + 9][1], avx_bytes[offset_bytes + 8][1],
						avx_bytes[offset_bytes + 7][1], avx_bytes[offset_bytes + 6][1], avx_bytes[offset_bytes + 5][1], avx_bytes[offset_bytes + 4][1],
						avx_bytes[offset_bytes + 3][1], avx_bytes[offset_bytes + 2][1], avx_bytes[offset_bytes + 1][1], avx_bytes[offset_bytes + 0][1]);
				_mm256_storeu_si256(avx_bytes1_ptr+m,temp_byte1);
						

		temp_byte2 = _mm256_set_epi8(avx_bytes[offset_bytes + 31][2], avx_bytes[offset_bytes + 30][2], avx_bytes[offset_bytes + 29][2], avx_bytes[offset_bytes + 28][2],
						avx_bytes[offset_bytes + 27][2], avx_bytes[offset_bytes + 26][2], avx_bytes[offset_bytes + 25][2], avx_bytes[offset_bytes + 24][2],
						avx_bytes[offset_bytes + 23][2], avx_bytes[offset_bytes + 22][2], avx_bytes[offset_bytes + 21][2], avx_bytes[offset_bytes + 20][2],
						avx_bytes[offset_bytes + 19][2], avx_bytes[offset_bytes + 18][2], avx_bytes[offset_bytes + 17][2], avx_bytes[offset_bytes + 16][2],
						avx_bytes[offset_bytes + 15][2], avx_bytes[offset_bytes + 14][2], avx_bytes[offset_bytes + 13][2], avx_bytes[offset_bytes + 12][2],
						avx_bytes[offset_bytes + 11][2], avx_bytes[offset_bytes + 10][2], avx_bytes[offset_bytes + 9][2], avx_bytes[offset_bytes + 8][2],
						avx_bytes[offset_bytes + 7][2], avx_bytes[offset_bytes + 6][2], avx_bytes[offset_bytes + 5][2], avx_bytes[offset_bytes + 4][2],
						avx_bytes[offset_bytes + 3][2], avx_bytes[offset_bytes + 2][2], avx_bytes[offset_bytes + 1][2], avx_bytes[offset_bytes + 0][2]);
				_mm256_storeu_si256(avx_bytes2_ptr+m,temp_byte2);
						

		temp_byte3 = _mm256_set_epi8(avx_bytes[offset_bytes + 31][3], avx_bytes[offset_bytes + 30][3], avx_bytes[offset_bytes + 29][3], avx_bytes[offset_bytes + 28][3],
						avx_bytes[offset_bytes + 27][3], avx_bytes[offset_bytes + 26][3], avx_bytes[offset_bytes + 25][3], avx_bytes[offset_bytes + 24][3],
						avx_bytes[offset_bytes + 23][3], avx_bytes[offset_bytes + 22][3], avx_bytes[offset_bytes + 21][3], avx_bytes[offset_bytes + 20][3],
						avx_bytes[offset_bytes + 19][3], avx_bytes[offset_bytes + 18][3], avx_bytes[offset_bytes + 17][3], avx_bytes[offset_bytes + 16][3],
						avx_bytes[offset_bytes + 15][3], avx_bytes[offset_bytes + 14][3], avx_bytes[offset_bytes + 13][3], avx_bytes[offset_bytes + 12][3],
						avx_bytes[offset_bytes + 11][3], avx_bytes[offset_bytes + 10][3], avx_bytes[offset_bytes + 9][3], avx_bytes[offset_bytes + 8][3],
						avx_bytes[offset_bytes + 7][3], avx_bytes[offset_bytes + 6][3], avx_bytes[offset_bytes + 5][3], avx_bytes[offset_bytes + 4][3],
						avx_bytes[offset_bytes + 3][3], avx_bytes[offset_bytes + 2][3], avx_bytes[offset_bytes + 1][3], avx_bytes[offset_bytes + 0][3]);
				_mm256_storeu_si256(avx_bytes3_ptr+m,temp_byte3);

	}
	
}



void BS2POLVECp(const unsigned char *bytes, uint16_t data[SABER_K][SABER_N]){
	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
	
	offset_byte=0;
	for(i=0;i<SABER_K;i++){
		offset_byte1=i*(SABER_N*10)/8;
		for(j=0;j<SABER_N/4;j++){
			offset_byte=offset_byte1+5*j;
			offset_data=4*j;
			data[i][offset_data + 0]= ( bytes[ offset_byte + 0 ] & (0xff)) |  ((bytes[ offset_byte + 1 ] & 0x03)<<8);
			data[i][offset_data + 1]= ( (bytes[ offset_byte + 1 ]>>2) & (0x3f)) |  ((bytes[ offset_byte + 2 ] & 0x0f)<<6);		
			data[i][offset_data + 2]= ( (bytes[ offset_byte + 2 ]>>4) & (0x0f)) |  ((bytes[ offset_byte + 3 ] & 0x3f)<<4);
			data[i][offset_data + 3]= ( (bytes[ offset_byte + 3 ]>>6) & (0x03)) |  ((bytes[ offset_byte + 4 ] & 0xff)<<2);		

		}
	}
}

void BS2POLVECpX4(const unsigned char *bs0, const unsigned char *bs1, const unsigned char *bs2, const unsigned char *bs3, 
				__m256i data0[SABER_K][SABER_N/16], __m256i data1[SABER_K][SABER_N/16],
				__m256i data2[SABER_K][SABER_N/16], __m256i data3[SABER_K][SABER_N/16]){
	/*--------------------------------------------------------*/
	/*------------------Load to avx_bytes---------------------*/
	/*--------------------------------------------------------*/
	
	const float * cfbs0 = (const float *)bs0;
	const float * cfbs1 = (const float *)bs1;
	const float * cfbs2 = (const float *)bs2;
	const float * cfbs3 = (const float *)bs3;

	__m256i avx_bytes[960/2];
	
	__m256i avx_data[SABER_K*SABER_N/2];
	
	avx_load_8bit_16bit(cfbs0, cfbs1, cfbs2, cfbs3, &avx_bytes[0], 960);
	
	/*--------------------------------------------------------*/
	/*---------------------Do the shifts----------------------*/
	/*--------------------------------------------------------*/

	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;
	
	offset_byte=0;
	for(i=0;i<SABER_K;++i){
		offset_byte1=i*(SABER_N*10)/8;
		for(j=0;j<(SABER_N/4)/2;++j){
			offset_byte=offset_byte1/2+5*j;
			offset_data=4*j;
			avx_data[i*SABER_N/2+offset_data + 0] = _mm256_or_si256(_mm256_and_si256(avx_bytes[ offset_byte + 0 ],avx_epi32_ff), _mm256_slli_epi32(_mm256_and_si256(avx_bytes[ offset_byte + 1 ],avx_epi32_03),8));
			avx_data[i*SABER_N/2+offset_data + 1] = _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_bytes[ offset_byte + 1 ],2),(avx_epi32_3f)),_mm256_slli_epi32(_mm256_and_si256(avx_bytes[ offset_byte + 2 ],avx_epi32_0f),6));
			avx_data[i*SABER_N/2+offset_data + 2] = _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_bytes[ offset_byte + 2 ],4),(avx_epi32_0f)),_mm256_slli_epi32(_mm256_and_si256(avx_bytes[ offset_byte + 3 ],avx_epi32_3f),4));
			avx_data[i*SABER_N/2+offset_data + 3] = _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_bytes[ offset_byte + 3 ],6),(avx_epi32_03)),_mm256_slli_epi32(_mm256_and_si256(avx_bytes[ offset_byte + 4 ],avx_epi32_ff),2));
		}
	}
	
	
	/*--------------------------------------------------------*/
	/*---------------------Store back-------------------------*/
	/*--------------------------------------------------------*/
	avx_store_16bit_KN(&avx_data[0], &data0[0], &data1[0], &data2[0], &data3[0]);

}

void old_BS2POLVECpX4(const unsigned char *bytes0, const unsigned char *bytes1, const unsigned char *bytes2, const unsigned char *bytes3, 
__m256i data0[SABER_K][SABER_N/16], __m256i data1[SABER_K][SABER_N/16], __m256i data2[SABER_K][SABER_N/16], __m256i data3[SABER_K][SABER_N/16]){

	__m256i avx_epi64_03, avx_epi64_0f, avx_epi64_3f, avx_epi64_ff;
	avx_epi64_03 = _mm256_set1_epi64x(0x03);
	avx_epi64_0f = _mm256_set1_epi64x(0x0f);
	avx_epi64_3f = _mm256_set1_epi64x(0x3f);
	avx_epi64_ff = _mm256_set1_epi64x(0xff);
	
	uint32_t para = (SABER_K-1)*(SABER_N*10)/8+5*(SABER_N/4);
	
	__m256i avx_bytes[para];
	__m256i avx_data[SABER_K*SABER_N];
	uint32_t k;
	for(k=0;k<para;++k){
		avx_bytes[k] = _mm256_set_epi64x(bytes3[k], bytes2[k], bytes1[k], bytes0[k]);
	}


	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;
	
	offset_byte=0;
	for(i=0;i<SABER_K;++i){
		offset_byte1=i*(SABER_N*10)/8;
		for(j=0;j<SABER_N/4;++j){
			offset_byte=offset_byte1+5*j;
			offset_data=4*j;
			avx_data[i*SABER_N+offset_data + 0] = _mm256_or_si256(_mm256_and_si256(avx_bytes[ offset_byte + 0 ],avx_epi64_ff), _mm256_slli_epi64(_mm256_and_si256(avx_bytes[ offset_byte + 1 ],avx_epi64_03),8));
			avx_data[i*SABER_N+offset_data + 1] = _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi64(avx_bytes[ offset_byte + 1 ],2),(avx_epi64_3f)),_mm256_slli_epi64(_mm256_and_si256(avx_bytes[ offset_byte + 2 ],avx_epi64_0f),6));
			avx_data[i*SABER_N+offset_data + 2] = _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi64(avx_bytes[ offset_byte + 2 ],4),(avx_epi64_0f)),_mm256_slli_epi64(_mm256_and_si256(avx_bytes[ offset_byte + 3 ],avx_epi64_3f),4));
			avx_data[i*SABER_N+offset_data + 3] = _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi64(avx_bytes[ offset_byte + 3 ],6),(avx_epi64_03)),_mm256_slli_epi64(_mm256_and_si256(avx_bytes[ offset_byte + 4 ],avx_epi64_ff),2));

		}
	}


	uint32_t m,n;
	uint32_t offset_bytes;
	for(m=0;m<SABER_K;++m){
		for(n=0;n<(SABER_N/16);++n){
		offset_bytes = m*SABER_N+16*n;
		data0[m][n] = _mm256_set_epi16(avx_data[offset_bytes + 15][0], avx_data[offset_bytes + 14][0], avx_data[offset_bytes + 13][0], avx_data[offset_bytes + 12][0],
						avx_data[offset_bytes + 11][0], avx_data[offset_bytes + 10][0], avx_data[offset_bytes + 9][0], avx_data[offset_bytes + 8][0],
						avx_data[offset_bytes + 7][0], avx_data[offset_bytes + 6][0], avx_data[offset_bytes + 5][0], avx_data[offset_bytes + 4][0],
						avx_data[offset_bytes + 3][0], avx_data[offset_bytes + 2][0], avx_data[offset_bytes + 1][0], avx_data[offset_bytes + 0][0]);
				
				
		data1[m][n] = _mm256_set_epi16(avx_data[offset_bytes + 15][1], avx_data[offset_bytes + 14][1], avx_data[offset_bytes + 13][1], avx_data[offset_bytes + 12][1],
						avx_data[offset_bytes + 11][1], avx_data[offset_bytes + 10][1], avx_data[offset_bytes + 9][1], avx_data[offset_bytes + 8][1],
						avx_data[offset_bytes + 7][1], avx_data[offset_bytes + 6][1], avx_data[offset_bytes + 5][1], avx_data[offset_bytes + 4][1],
						avx_data[offset_bytes + 3][1], avx_data[offset_bytes + 2][1], avx_data[offset_bytes + 1][1], avx_data[offset_bytes + 0][1]);
						

		data2[m][n] = _mm256_set_epi16(avx_data[offset_bytes + 15][2], avx_data[offset_bytes + 14][2], avx_data[offset_bytes + 13][2], avx_data[offset_bytes + 12][2],
						avx_data[offset_bytes + 11][2], avx_data[offset_bytes + 10][2], avx_data[offset_bytes + 9][2], avx_data[offset_bytes + 8][2],
						avx_data[offset_bytes + 7][2], avx_data[offset_bytes + 6][2], avx_data[offset_bytes + 5][2], avx_data[offset_bytes + 4][2],
						avx_data[offset_bytes + 3][2], avx_data[offset_bytes + 2][2], avx_data[offset_bytes + 1][2], avx_data[offset_bytes + 0][2]);
						

		data3[m][n] = _mm256_set_epi16(avx_data[offset_bytes + 15][3], avx_data[offset_bytes + 14][3], avx_data[offset_bytes + 13][3], avx_data[offset_bytes + 12][3],
						avx_data[offset_bytes + 11][3], avx_data[offset_bytes + 10][3], avx_data[offset_bytes + 9][3], avx_data[offset_bytes + 8][3],
						avx_data[offset_bytes + 7][3], avx_data[offset_bytes + 6][3], avx_data[offset_bytes + 5][3], avx_data[offset_bytes + 4][3],
						avx_data[offset_bytes + 3][3], avx_data[offset_bytes + 2][3], avx_data[offset_bytes + 1][3], avx_data[offset_bytes + 0][3]);
		}
	}
	

}



void BS2POLVECq(const unsigned char *bytes, uint16_t data[SABER_K][SABER_N]){
	
	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
	
	offset_byte=0;
	for(i=0;i<SABER_K;i++){
		offset_byte1=i*(SABER_N*13)/8;
		for(j=0;j<SABER_N/8;j++){
			offset_byte=offset_byte1+13*j;
			offset_data=8*j;
			data[i][offset_data + 0]= ( bytes[ offset_byte + 0 ] & (0xff)) | ((bytes[offset_byte + 1] & 0x1f)<<8);
			data[i][offset_data + 1]= ( bytes[ offset_byte + 1 ]>>5 & (0x07)) | ((bytes[offset_byte + 2] & 0xff)<<3) | ((bytes[offset_byte + 3] & 0x03)<<11);
			data[i][offset_data + 2]= ( bytes[ offset_byte + 3 ]>>2 & (0x3f)) | ((bytes[offset_byte + 4] & 0x7f)<<6);
			data[i][offset_data + 3]= ( bytes[ offset_byte + 4 ]>>7 & (0x01)) | ((bytes[offset_byte + 5] & 0xff)<<1) | ((bytes[offset_byte + 6] & 0x0f)<<9);
			data[i][offset_data + 4]= ( bytes[ offset_byte + 6 ]>>4 & (0x0f)) | ((bytes[offset_byte + 7] & 0xff)<<4) | ((bytes[offset_byte + 8] & 0x01)<<12);
			data[i][offset_data + 5]= ( bytes[ offset_byte + 8]>>1 & (0x7f)) | ((bytes[offset_byte + 9] & 0x3f)<<7);
			data[i][offset_data + 6]= ( bytes[ offset_byte + 9]>>6 & (0x03)) | ((bytes[offset_byte + 10] & 0xff)<<2) | ((bytes[offset_byte + 11] & 0x07)<<10);
			data[i][offset_data + 7]= ( bytes[ offset_byte + 11]>>3 & (0x1f)) | ((bytes[offset_byte + 12] & 0xff)<<5);
		}
	}


}

void BS2POLVECqX4(const unsigned char *bs0, const unsigned char *bs1, const unsigned char *bs2, const unsigned char *bs3, 
				__m256i data0[SABER_K][SABER_N/16], __m256i data1[SABER_K][SABER_N/16], 
				__m256i data2[SABER_K][SABER_N/16], __m256i data3[SABER_K][SABER_N/16]){
	/*--------------------------------------------------------*/
	/*------------------Load to avx_bytes---------------------*/
	/*--------------------------------------------------------*/
	
	const float * cfbs0 = (const float *)bs0;
	const float * cfbs1 = (const float *)bs1;
	const float * cfbs2 = (const float *)bs2;
	const float * cfbs3 = (const float *)bs3;
	
	__m256i avx_bytes[1248/2];
	
	__m256i avx_data[SABER_K*SABER_N/2];
	
	avx_load_8bit_16bit(cfbs0, cfbs1, cfbs2, cfbs3, &avx_bytes[0], 1248);
	
	
	/*--------------------------------------------------------*/
	/*---------------------Do the shifts----------------------*/
	/*--------------------------------------------------------*/
	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
	for(i=0;i<SABER_K;++i){
		offset_byte1=i*(SABER_N*13)/8;
		for(j=0;j<SABER_N/(8*2);++j){
			offset_byte=offset_byte1/2+13*j;
			offset_data=8*j;
			avx_data[i*SABER_N/2 + offset_data + 0]= _mm256_or_si256(_mm256_and_si256(avx_bytes[ offset_byte + 0 ],(avx_epi32_ff)),_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte + 1],avx_epi32_1f),8));
			avx_data[i*SABER_N/2 + offset_data + 1]= _mm256_or_si256(_mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_bytes[ offset_byte + 1 ],5),(avx_epi32_07)),_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte + 2 ],avx_epi32_ff),3)),_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte + 3 ],avx_epi32_03),11));
			avx_data[i*SABER_N/2 + offset_data + 2]= _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_bytes[ offset_byte + 3 ],2),(avx_epi32_3f)),_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte + 4 ],avx_epi32_7f),6));
			avx_data[i*SABER_N/2 + offset_data + 3]= _mm256_or_si256(_mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_bytes[ offset_byte + 4 ],7),(avx_epi32_01)),_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte + 5 ],avx_epi32_ff),1)),_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte + 6 ],avx_epi32_0f),9 ));
			avx_data[i*SABER_N/2 + offset_data + 4]= _mm256_or_si256(_mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_bytes[ offset_byte + 6 ],4),(avx_epi32_0f)),_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte + 7 ],avx_epi32_ff),4)),_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte + 8 ],avx_epi32_01),12));
			avx_data[i*SABER_N/2 + offset_data + 5]= _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_bytes[ offset_byte + 8 ],1),(avx_epi32_7f)),_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte + 9 ],avx_epi32_3f),7));
			avx_data[i*SABER_N/2 + offset_data + 6]= _mm256_or_si256(_mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_bytes[ offset_byte + 9 ],6),(avx_epi32_03)),_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte + 10],avx_epi32_ff),2)),_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte + 11],avx_epi32_07),10));
			avx_data[i*SABER_N/2 + offset_data + 7]= _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi32(avx_bytes[ offset_byte + 11],3),(avx_epi32_1f)),_mm256_slli_epi32(_mm256_and_si256(avx_bytes[offset_byte + 12],avx_epi32_ff),5));
		}
	}
	
	
	/*--------------------------------------------------------*/
	/*---------------------Store back-------------------------*/
	/*--------------------------------------------------------*/
	avx_store_16bit_KN(&avx_data[0], &data0[0], &data1[0], &data2[0], &data3[0]);
	
}

void old_BS2POLVECqX4(const unsigned char *bytes0, const unsigned char *bytes1, const unsigned char *bytes2, const unsigned char *bytes3, 
				__m256i data0[SABER_K][SABER_N/16], __m256i data1[SABER_K][SABER_N/16], __m256i data2[SABER_K][SABER_N/16], __m256i data3[SABER_K][SABER_N/16]){
	
	uint32_t para = (SABER_K-1)*(SABER_N*13)/8+13*(SABER_N/8);
	__m256i avx_bytes[para];
	__m256i avx_data[SABER_K*SABER_N];
	uint32_t k;
	for(k=0;k<para;++k){
		avx_bytes[k] = _mm256_set_epi64x(bytes3[k], bytes2[k], bytes1[k], bytes0[k]);
	}
	
	
	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
	for(i=0;i<SABER_K;++i){
		offset_byte1=i*(SABER_N*13)/8;
		for(j=0;j<SABER_N/8;++j){
			offset_byte=offset_byte1+13*j;
			offset_data=8*j;
			avx_data[i*SABER_N + offset_data + 0]= _mm256_or_si256(_mm256_and_si256(avx_bytes[ offset_byte + 0 ],(avx_epi64_ff)),_mm256_slli_epi64(_mm256_and_si256(avx_bytes[offset_byte + 1],avx_epi64_1f),8));
			avx_data[i*SABER_N + offset_data + 1]= _mm256_or_si256(_mm256_or_si256(_mm256_and_si256(_mm256_srli_epi64(avx_bytes[ offset_byte + 1 ],5),(avx_epi64_07)),_mm256_slli_epi64(_mm256_and_si256(avx_bytes[offset_byte + 2 ],avx_epi64_ff),3)),_mm256_slli_epi64(_mm256_and_si256(avx_bytes[offset_byte + 3 ],avx_epi64_03),11));
			avx_data[i*SABER_N + offset_data + 2]= _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi64(avx_bytes[ offset_byte + 3 ],2),(avx_epi64_3f)),_mm256_slli_epi64(_mm256_and_si256(avx_bytes[offset_byte + 4 ],avx_epi64_7f),6));
			avx_data[i*SABER_N + offset_data + 3]= _mm256_or_si256(_mm256_or_si256(_mm256_and_si256(_mm256_srli_epi64(avx_bytes[ offset_byte + 4 ],7),(avx_epi64_01)),_mm256_slli_epi64(_mm256_and_si256(avx_bytes[offset_byte + 5 ],avx_epi64_ff),1)),_mm256_slli_epi64(_mm256_and_si256(avx_bytes[offset_byte + 6 ],avx_epi64_0f),9 ));
			avx_data[i*SABER_N + offset_data + 4]= _mm256_or_si256(_mm256_or_si256(_mm256_and_si256(_mm256_srli_epi64(avx_bytes[ offset_byte + 6 ],4),(avx_epi64_0f)),_mm256_slli_epi64(_mm256_and_si256(avx_bytes[offset_byte + 7 ],avx_epi64_ff),4)),_mm256_slli_epi64(_mm256_and_si256(avx_bytes[offset_byte + 8 ],avx_epi64_01),12));
			avx_data[i*SABER_N + offset_data + 5]= _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi64(avx_bytes[ offset_byte + 8 ],1),(avx_epi64_7f)),_mm256_slli_epi64(_mm256_and_si256(avx_bytes[offset_byte + 9 ],avx_epi64_3f),7));
			avx_data[i*SABER_N + offset_data + 6]= _mm256_or_si256(_mm256_or_si256(_mm256_and_si256(_mm256_srli_epi64(avx_bytes[ offset_byte + 9 ],6),(avx_epi64_03)),_mm256_slli_epi64(_mm256_and_si256(avx_bytes[offset_byte + 10],avx_epi64_ff),2)),_mm256_slli_epi64(_mm256_and_si256(avx_bytes[offset_byte + 11],avx_epi64_07),10));
			avx_data[i*SABER_N + offset_data + 7]= _mm256_or_si256(_mm256_and_si256(_mm256_srli_epi64(avx_bytes[ offset_byte + 11],3),(avx_epi64_1f)),_mm256_slli_epi64(_mm256_and_si256(avx_bytes[offset_byte + 12],avx_epi64_ff),5));
		}
	}
	
	uint32_t offset_bytes=0;
	uint32_t m,n;
	for(m=0;m<SABER_K;++m){
		for(n=0;n<(SABER_N/16);++n){
			offset_bytes = m*SABER_N+16*n;
			data0[m][n] = _mm256_set_epi16(avx_data[offset_bytes + 15][0], avx_data[offset_bytes + 14][0], avx_data[offset_bytes + 13][0], avx_data[offset_bytes + 12][0],
							avx_data[offset_bytes + 11][0], avx_data[offset_bytes + 10][0], avx_data[offset_bytes + 9][0], avx_data[offset_bytes + 8][0],
							avx_data[offset_bytes + 7][0], avx_data[offset_bytes + 6][0], avx_data[offset_bytes + 5][0], avx_data[offset_bytes + 4][0],
							avx_data[offset_bytes + 3][0], avx_data[offset_bytes + 2][0], avx_data[offset_bytes + 1][0], avx_data[offset_bytes + 0][0]);
			
			data1[m][n] = _mm256_set_epi16(avx_data[offset_bytes + 15][1], avx_data[offset_bytes + 14][1], avx_data[offset_bytes + 13][1], avx_data[offset_bytes + 12][1],
							avx_data[offset_bytes + 11][1], avx_data[offset_bytes + 10][1], avx_data[offset_bytes + 9][1], avx_data[offset_bytes + 8][1],
							avx_data[offset_bytes + 7][1], avx_data[offset_bytes + 6][1], avx_data[offset_bytes + 5][1], avx_data[offset_bytes + 4][1],
							avx_data[offset_bytes + 3][1], avx_data[offset_bytes + 2][1], avx_data[offset_bytes + 1][1], avx_data[offset_bytes + 0][1]);
						
			data2[m][n] = _mm256_set_epi16(avx_data[offset_bytes + 15][2], avx_data[offset_bytes + 14][2], avx_data[offset_bytes + 13][2], avx_data[offset_bytes + 12][2],
							avx_data[offset_bytes + 11][2], avx_data[offset_bytes + 10][2], avx_data[offset_bytes + 9][2], avx_data[offset_bytes + 8][2],
							avx_data[offset_bytes + 7][2], avx_data[offset_bytes + 6][2], avx_data[offset_bytes + 5][2], avx_data[offset_bytes + 4][2],
							avx_data[offset_bytes + 3][2], avx_data[offset_bytes + 2][2], avx_data[offset_bytes + 1][2], avx_data[offset_bytes + 0][2]);
						
			data3[m][n] = _mm256_set_epi16(avx_data[offset_bytes + 15][3], avx_data[offset_bytes + 14][3], avx_data[offset_bytes + 13][3], avx_data[offset_bytes + 12][3],
							avx_data[offset_bytes + 11][3], avx_data[offset_bytes + 10][3], avx_data[offset_bytes + 9][3], avx_data[offset_bytes + 8][3],
							avx_data[offset_bytes + 7][3], avx_data[offset_bytes + 6][3], avx_data[offset_bytes + 5][3], avx_data[offset_bytes + 4][3],
							avx_data[offset_bytes + 3][3], avx_data[offset_bytes + 2][3], avx_data[offset_bytes + 1][3], avx_data[offset_bytes + 0][3]);

		}
	}
}



void SABER_un_pack10bit(const unsigned char *bytes, uint16_t data[SABER_K][SABER_N]){
	
	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
	
	offset_byte=0;
	for(i=0;i<SABER_K;i++){
		offset_byte1=i*(SABER_N*10)/8;
		for(j=0;j<SABER_N/4;j++){
			offset_byte=offset_byte1+5*j;
			offset_data=4*j;
			data[i][offset_data + 0]= ( bytes[ offset_byte + 0 ] & (0xff)) |  ((bytes[ offset_byte + 1 ] & 0x03)<<8);
			data[i][offset_data + 1]= ( (bytes[ offset_byte + 1 ]>>2) & (0x3f)) |  ((bytes[ offset_byte + 2 ] & 0x0f)<<6);		
			data[i][offset_data + 2]= ( (bytes[ offset_byte + 2 ]>>4) & (0x0f)) |  ((bytes[ offset_byte + 3 ] & 0x3f)<<4);
			data[i][offset_data + 3]= ( (bytes[ offset_byte + 3 ]>>6) & (0x03)) |  ((bytes[ offset_byte + 4 ] & 0xff)<<2);		

		}
	}


}


void SABER_pack13bit(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
	
	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
	
	offset_byte=0;
	for(i=0;i<SABER_K;i++){
		offset_byte1=i*(SABER_N*13)/8;
		for(j=0;j<SABER_N/8;j++){
			offset_byte=offset_byte1+13*j;
			offset_data=8*j;
			bytes[offset_byte + 0]= ( data[i][ offset_data + 0 ] & (0xff));

			bytes[offset_byte + 1]= ( (data[i][ offset_data + 0 ] >>8) & 0x1f ) | ((data[i][ offset_data + 1 ] & 0x07) << 5);

			bytes[offset_byte + 2]= ( (data[i][ offset_data + 1 ] >>3) & 0xff );

			bytes[offset_byte + 3]= ( (data[i][ offset_data + 1 ] >>11) & 0x03 ) | ((data[i][ offset_data + 2 ] & 0x3f) << 2);

			bytes[offset_byte + 4]= ( (data[i][ offset_data + 2 ] >>6) & 0x7f ) | ( (data[i][ offset_data + 3 ] & 0x01) << 7 );

			bytes[offset_byte + 5]= ( (data[i][ offset_data + 3 ] >>1) & 0xff );

			bytes[offset_byte + 6]= ( (data[i][ offset_data + 3 ] >>9) & 0x0f ) | ( (data[i][ offset_data + 4 ] & 0x0f) << 4 );

			bytes[offset_byte + 7]= ( (data[i][ offset_data + 4] >>4) & 0xff );

			bytes[offset_byte + 8]= ( (data[i][ offset_data + 4 ] >>12) & 0x01 ) | ( (data[i][ offset_data + 5 ] & 0x7f) << 1 );

			bytes[offset_byte + 9]= ( (data[i][ offset_data + 5 ] >>7) & 0x3f ) | ( (data[i][ offset_data + 6 ] & 0x03) << 6 );

			bytes[offset_byte + 10]= ( (data[i][ offset_data + 6 ] >>2) & 0xff );

			bytes[offset_byte + 11]= ( (data[i][ offset_data + 6 ] >>10) & 0x07 ) | ( (data[i][ offset_data + 7 ] & 0x1f) << 3 );

			bytes[offset_byte + 12]= ( (data[i][ offset_data + 7 ] >>5) & 0xff );

		}
	}


}

void SABER_pack13bitX4(uint8_t *bytes0, uint8_t *bytes1, uint8_t *bytes2, uint8_t *bytes3, uint16_t data0[SABER_K][SABER_N], uint16_t data1[SABER_K][SABER_N], uint16_t data2[SABER_K][SABER_N], uint16_t data3[SABER_K][SABER_N]){
	__m256i avx_epi64_01, avx_epi64_03, avx_epi64_07, avx_epi64_0f, avx_epi64_1f, avx_epi64_3f, avx_epi64_7f, avx_epi64_ff;
	
	avx_epi64_01 = _mm256_set1_epi64x(0x01);
	avx_epi64_03 = _mm256_set1_epi64x(0x03);
	avx_epi64_07 = _mm256_set1_epi64x(0x07);
	avx_epi64_0f = _mm256_set1_epi64x(0x0f);
	avx_epi64_1f = _mm256_set1_epi64x(0x1f);
	avx_epi64_3f = _mm256_set1_epi64x(0x3f);
	avx_epi64_7f = _mm256_set1_epi64x(0x7f);
	avx_epi64_ff = _mm256_set1_epi64x(0xff);
	
	uint32_t i,j,m;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
	
	__m256i avx_data[SABER_K*SABER_N];
	for(i=0;i<SABER_K;++i){
		for(j=0;j<SABER_N;++j){
			avx_data[i*256+j] = _mm256_set_epi64x(data3[i][j], data2[i][j], data1[i][j], data0[i][j]);
		}
	}
	
	__m256i *avx_bytes0_ptr = (__m256i*)bytes0;
	__m256i *avx_bytes1_ptr = (__m256i*)bytes1;
	__m256i *avx_bytes2_ptr = (__m256i*)bytes2;
	__m256i *avx_bytes3_ptr = (__m256i*)bytes3;
	
	offset_byte=0;
	//para=1248
	uint16_t para = (SABER_K-1)*((SABER_N*13)/8)+13*(SABER_N/8);
	
	__m256i avx_bytes[para];
	
	for(i=0;i<SABER_K;i++){
		offset_byte1=i*(SABER_N*13)/8;
		for(j=0;j<SABER_N/8;j++){
			offset_byte=offset_byte1+13*j;
			offset_data=8*j;
			avx_bytes[offset_byte + 0 ]= _mm256_and_si256( avx_data[i*SABER_N + offset_data + 0 ],(avx_epi64_ff));

			avx_bytes[offset_byte + 1 ]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi64(avx_data[i*SABER_N + offset_data + 0 ] ,8 ),avx_epi64_1f ) , _mm256_slli_epi64(_mm256_and_si256(avx_data[i*SABER_N + offset_data + 1 ],avx_epi64_07) , 5));

			avx_bytes[offset_byte + 2 ]= _mm256_and_si256( _mm256_srli_epi64(avx_data[i*SABER_N + offset_data + 1 ] ,3 ),avx_epi64_ff );

			avx_bytes[offset_byte + 3 ]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi64(avx_data[i*SABER_N + offset_data + 1 ] ,11),avx_epi64_03 ) , _mm256_slli_epi64(_mm256_and_si256(avx_data[i*SABER_N + offset_data + 2 ],avx_epi64_3f) , 2));

			avx_bytes[offset_byte + 4 ]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi64(avx_data[i*SABER_N + offset_data + 2 ] ,6 ),avx_epi64_7f ) , _mm256_slli_epi64(_mm256_and_si256(avx_data[i*SABER_N + offset_data + 3 ],avx_epi64_01) , 7 ));

			avx_bytes[offset_byte + 5 ]= _mm256_and_si256( _mm256_srli_epi64(avx_data[i*SABER_N + offset_data + 3 ] ,1 ),avx_epi64_ff );

			avx_bytes[offset_byte + 6 ]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi64(avx_data[i*SABER_N + offset_data + 3 ] ,9 ),avx_epi64_0f ) , _mm256_slli_epi64(_mm256_and_si256(avx_data[i*SABER_N + offset_data + 4 ],avx_epi64_0f) , 4 ));

			avx_bytes[offset_byte + 7 ]= _mm256_and_si256( _mm256_srli_epi64(avx_data[i*SABER_N + offset_data + 4 ] ,4 ),avx_epi64_ff );

			avx_bytes[offset_byte + 8 ]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi64(avx_data[i*SABER_N + offset_data + 4 ] ,12),avx_epi64_01 ) , _mm256_slli_epi64(_mm256_and_si256(avx_data[i*SABER_N + offset_data + 5 ],avx_epi64_7f) , 1 ));

			avx_bytes[offset_byte + 9 ]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi64(avx_data[i*SABER_N + offset_data + 5 ] ,7 ),avx_epi64_3f ) , _mm256_slli_epi64(_mm256_and_si256(avx_data[i*SABER_N + offset_data + 6 ],avx_epi64_03) , 6 ));

			avx_bytes[offset_byte + 10]= _mm256_and_si256( _mm256_srli_epi64(avx_data[i*SABER_N + offset_data + 6 ] ,2 ),avx_epi64_ff );

			avx_bytes[offset_byte + 11]= _mm256_or_si256(_mm256_and_si256( _mm256_srli_epi64(avx_data[i*SABER_N + offset_data + 6 ] ,10),avx_epi64_07 ) , _mm256_slli_epi64(_mm256_and_si256(avx_data[i*SABER_N + offset_data + 7 ],avx_epi64_1f) , 3 ));

			avx_bytes[offset_byte + 12]= _mm256_and_si256( _mm256_srli_epi64(avx_data[i*SABER_N + offset_data + 7 ] ,5 ),avx_epi64_ff );

		}
	}
	
	__m256i temp_byte0, temp_byte1, temp_byte2, temp_byte3;
	uint16_t counter = para/32;
	uint16_t offset_bytes;
	for(m=0;m<counter;++m){
		offset_bytes = (256/8)*m;

		temp_byte0 = _mm256_set_epi8(avx_bytes[offset_bytes + 31][0], avx_bytes[offset_bytes + 30][0], avx_bytes[offset_bytes + 29][0], avx_bytes[offset_bytes + 28][0],
						avx_bytes[offset_bytes + 27][0], avx_bytes[offset_bytes + 26][0], avx_bytes[offset_bytes + 25][0], avx_bytes[offset_bytes + 24][0],
						avx_bytes[offset_bytes + 23][0], avx_bytes[offset_bytes + 22][0], avx_bytes[offset_bytes + 21][0], avx_bytes[offset_bytes + 20][0],
						avx_bytes[offset_bytes + 19][0], avx_bytes[offset_bytes + 18][0], avx_bytes[offset_bytes + 17][0], avx_bytes[offset_bytes + 16][0],
						avx_bytes[offset_bytes + 15][0], avx_bytes[offset_bytes + 14][0], avx_bytes[offset_bytes + 13][0], avx_bytes[offset_bytes + 12][0],
						avx_bytes[offset_bytes + 11][0], avx_bytes[offset_bytes + 10][0], avx_bytes[offset_bytes + 9][0], avx_bytes[offset_bytes + 8][0],
						avx_bytes[offset_bytes + 7][0], avx_bytes[offset_bytes + 6][0], avx_bytes[offset_bytes + 5][0], avx_bytes[offset_bytes + 4][0],
						avx_bytes[offset_bytes + 3][0], avx_bytes[offset_bytes + 2][0], avx_bytes[offset_bytes + 1][0], avx_bytes[offset_bytes + 0][0]);
				_mm256_storeu_si256(avx_bytes0_ptr+m,temp_byte0);
				
				

		temp_byte1 = _mm256_set_epi8(avx_bytes[offset_bytes + 31][1], avx_bytes[offset_bytes + 30][1], avx_bytes[offset_bytes + 29][1], avx_bytes[offset_bytes + 28][1],
						avx_bytes[offset_bytes + 27][1], avx_bytes[offset_bytes + 26][1], avx_bytes[offset_bytes + 25][1], avx_bytes[offset_bytes + 24][1],
						avx_bytes[offset_bytes + 23][1], avx_bytes[offset_bytes + 22][1], avx_bytes[offset_bytes + 21][1], avx_bytes[offset_bytes + 20][1],
						avx_bytes[offset_bytes + 19][1], avx_bytes[offset_bytes + 18][1], avx_bytes[offset_bytes + 17][1], avx_bytes[offset_bytes + 16][1],
						avx_bytes[offset_bytes + 15][1], avx_bytes[offset_bytes + 14][1], avx_bytes[offset_bytes + 13][1], avx_bytes[offset_bytes + 12][1],
						avx_bytes[offset_bytes + 11][1], avx_bytes[offset_bytes + 10][1], avx_bytes[offset_bytes + 9][1], avx_bytes[offset_bytes + 8][1],
						avx_bytes[offset_bytes + 7][1], avx_bytes[offset_bytes + 6][1], avx_bytes[offset_bytes + 5][1], avx_bytes[offset_bytes + 4][1],
						avx_bytes[offset_bytes + 3][1], avx_bytes[offset_bytes + 2][1], avx_bytes[offset_bytes + 1][1], avx_bytes[offset_bytes + 0][1]);
				_mm256_storeu_si256(avx_bytes1_ptr+m,temp_byte1);
						

		temp_byte2 = _mm256_set_epi8(avx_bytes[offset_bytes + 31][2], avx_bytes[offset_bytes + 30][2], avx_bytes[offset_bytes + 29][2], avx_bytes[offset_bytes + 28][2],
						avx_bytes[offset_bytes + 27][2], avx_bytes[offset_bytes + 26][2], avx_bytes[offset_bytes + 25][2], avx_bytes[offset_bytes + 24][2],
						avx_bytes[offset_bytes + 23][2], avx_bytes[offset_bytes + 22][2], avx_bytes[offset_bytes + 21][2], avx_bytes[offset_bytes + 20][2],
						avx_bytes[offset_bytes + 19][2], avx_bytes[offset_bytes + 18][2], avx_bytes[offset_bytes + 17][2], avx_bytes[offset_bytes + 16][2],
						avx_bytes[offset_bytes + 15][2], avx_bytes[offset_bytes + 14][2], avx_bytes[offset_bytes + 13][2], avx_bytes[offset_bytes + 12][2],
						avx_bytes[offset_bytes + 11][2], avx_bytes[offset_bytes + 10][2], avx_bytes[offset_bytes + 9][2], avx_bytes[offset_bytes + 8][2],
						avx_bytes[offset_bytes + 7][2], avx_bytes[offset_bytes + 6][2], avx_bytes[offset_bytes + 5][2], avx_bytes[offset_bytes + 4][2],
						avx_bytes[offset_bytes + 3][2], avx_bytes[offset_bytes + 2][2], avx_bytes[offset_bytes + 1][2], avx_bytes[offset_bytes + 0][2]);
				_mm256_storeu_si256(avx_bytes2_ptr+m,temp_byte2);
						

		temp_byte3 = _mm256_set_epi8(avx_bytes[offset_bytes + 31][3], avx_bytes[offset_bytes + 30][3], avx_bytes[offset_bytes + 29][3], avx_bytes[offset_bytes + 28][3],
						avx_bytes[offset_bytes + 27][3], avx_bytes[offset_bytes + 26][3], avx_bytes[offset_bytes + 25][3], avx_bytes[offset_bytes + 24][3],
						avx_bytes[offset_bytes + 23][3], avx_bytes[offset_bytes + 22][3], avx_bytes[offset_bytes + 21][3], avx_bytes[offset_bytes + 20][3],
						avx_bytes[offset_bytes + 19][3], avx_bytes[offset_bytes + 18][3], avx_bytes[offset_bytes + 17][3], avx_bytes[offset_bytes + 16][3],
						avx_bytes[offset_bytes + 15][3], avx_bytes[offset_bytes + 14][3], avx_bytes[offset_bytes + 13][3], avx_bytes[offset_bytes + 12][3],
						avx_bytes[offset_bytes + 11][3], avx_bytes[offset_bytes + 10][3], avx_bytes[offset_bytes + 9][3], avx_bytes[offset_bytes + 8][3],
						avx_bytes[offset_bytes + 7][3], avx_bytes[offset_bytes + 6][3], avx_bytes[offset_bytes + 5][3], avx_bytes[offset_bytes + 4][3],
						avx_bytes[offset_bytes + 3][3], avx_bytes[offset_bytes + 2][3], avx_bytes[offset_bytes + 1][3], avx_bytes[offset_bytes + 0][3]);
				_mm256_storeu_si256(avx_bytes3_ptr+m,temp_byte3);
	}
}



void SABER_un_pack13bit(const unsigned char *bytes, uint16_t data[SABER_K][SABER_N]){
	
	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
	
	offset_byte=0;
	for(i=0;i<SABER_K;i++){
		offset_byte1=i*(SABER_N*13)/8;
		for(j=0;j<SABER_N/8;j++){
			offset_byte=offset_byte1+13*j;
			offset_data=8*j;
			data[i][offset_data + 0]= ( bytes[ offset_byte + 0 ] & (0xff)) | ((bytes[offset_byte + 1] & 0x1f)<<8);
			data[i][offset_data + 1]= ( bytes[ offset_byte + 1 ]>>5 & (0x07)) | ((bytes[offset_byte + 2] & 0xff)<<3) | ((bytes[offset_byte + 3] & 0x03)<<11);
			data[i][offset_data + 2]= ( bytes[ offset_byte + 3 ]>>2 & (0x3f)) | ((bytes[offset_byte + 4] & 0x7f)<<6);
			data[i][offset_data + 3]= ( bytes[ offset_byte + 4 ]>>7 & (0x01)) | ((bytes[offset_byte + 5] & 0xff)<<1) | ((bytes[offset_byte + 6] & 0x0f)<<9);
			data[i][offset_data + 4]= ( bytes[ offset_byte + 6 ]>>4 & (0x0f)) | ((bytes[offset_byte + 7] & 0xff)<<4) | ((bytes[offset_byte + 8] & 0x01)<<12);
			data[i][offset_data + 5]= ( bytes[ offset_byte + 8]>>1 & (0x7f)) | ((bytes[offset_byte + 9] & 0x3f)<<7);
			data[i][offset_data + 6]= ( bytes[ offset_byte + 9]>>6 & (0x03)) | ((bytes[offset_byte + 10] & 0xff)<<2) | ((bytes[offset_byte + 11] & 0x07)<<10);
			data[i][offset_data + 7]= ( bytes[ offset_byte + 11]>>3 & (0x1f)) | ((bytes[offset_byte + 12] & 0xff)<<5);
		}
	}


}


void SABER_poly_un_pack13bit(const unsigned char *bytes, uint16_t data[SABER_N]){
	
	uint32_t j;
	uint32_t offset_data=0,offset_byte=0;	
	
	offset_byte=0;
	//for(i=0;i<SABER_K;i++){
		//i=0;
		//offset_byte1=i*(SABER_N*13)/8;
		for(j=0;j<SABER_N/8;j++){
			//offset_byte=offset_byte1+13*j;
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


void SABER_pack11bit(uint8_t *bytes,  uint16_t data[SABER_K][SABER_N]){
/*This function packs 11 bit data stream into 8 bits of data.
*/
	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
	
	offset_byte=0;
	for(i=0;i<SABER_K;i++){
		offset_byte1=i*(SABER_N*11)/8;
		for(j=0;j<SABER_N/8;j++){
			offset_byte=offset_byte1+11*j;
			offset_data=8*j;
			bytes[offset_byte + 0]= ( data[i][ offset_data + 0 ] & (0xff));

			bytes[offset_byte + 1]= ( (data[i][ offset_data + 0 ] >>8) & 0x07 ) | ((data[i][ offset_data + 1 ] & 0x1f) << 3);

			bytes[offset_byte + 2]= ( (data[i][ offset_data + 1 ] >>5) & 0x3f ) | ((data[i][ offset_data + 2 ] & 0x03) << 6);

			bytes[offset_byte + 3]= ( (data[i][ offset_data + 2 ] >>2) & 0xff );

			bytes[offset_byte + 4]= ( (data[i][ offset_data + 2 ] >>10) & 0x01 ) | ((data[i][ offset_data + 3 ] & 0x7f) << 1);

			bytes[offset_byte + 5]= ( (data[i][ offset_data + 3 ] >>7) & 0x0f ) | ((data[i][ offset_data + 4 ] & 0x0f) << 4);

			bytes[offset_byte + 6]= ( (data[i][ offset_data + 4 ] >>4) & 0x7f ) | ((data[i][ offset_data + 5 ] & 0x01) << 7);

			bytes[offset_byte + 7]= ( (data[i][ offset_data + 5 ] >>1) & 0xff );

			bytes[offset_byte + 8]= ( (data[i][ offset_data + 5 ] >>9) & 0x03 ) | ((data[i][ offset_data + 6 ] & 0x3f) << 2);

			bytes[offset_byte + 9]= ( (data[i][ offset_data + 6 ] >>6) & 0x1f ) | ((data[i][ offset_data + 7 ] & 0x07) << 5);

			bytes[offset_byte + 10]=( (data[i][ offset_data + 7 ] >>3) & 0xff );
			
		}
	}

}


void SABER_un_pack11bit(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
	
	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;


	for(i=0;i<SABER_K;i++){
		offset_byte1=i*(SABER_N*11)/8;
		for(j=0;j<SABER_N/8;j++){
			offset_byte=offset_byte1+11*j;
			offset_data=8*j;

			data[i][offset_data+ 0]=(bytes[offset_byte+0]) | ( (bytes[offset_byte + 1] & 0x07) << 8 );

			data[i][offset_data+ 1]= ( (bytes[offset_byte+1] >>3)&0x1f) | ( (bytes[offset_byte + 2] & 0x3f) << 5 );

			data[i][offset_data+ 2]= ( (bytes[offset_byte+2] >>6)&0x03) | ( (bytes[offset_byte + 3] & 0xff) << 2 ) | ( (bytes[offset_byte + 4] & 0x01) << 10 );

			data[i][offset_data+ 3]= ( (bytes[offset_byte+4] >>1)&0x7f) | ( (bytes[offset_byte + 5] & 0x0f) << 7 );

			data[i][offset_data+ 4]= ( (bytes[offset_byte+5] >>4)&0x0f) | ( (bytes[offset_byte + 6] & 0x7f) << 4 );

			data[i][offset_data+ 5]= ( (bytes[offset_byte+6] >>7)&0x01) | ( (bytes[offset_byte + 7] & 0xff) << 1 ) | ( (bytes[offset_byte + 8] & 0x03) << 9 );

			data[i][offset_data+ 6]= ( (bytes[offset_byte+8] >>2)&0x3f) | ( (bytes[offset_byte + 9] & 0x1f) << 6 );

			data[i][offset_data+ 7]= ( (bytes[offset_byte+9] >>5)&0x07) | ( (bytes[offset_byte + 10] & 0xff) << 3 );
		}
	}


}


void SABER_pack14bit(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
	
	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
	
	offset_byte=0;
	for(i=0;i<SABER_K;i++){
		offset_byte1=i*(SABER_N*14)/8;
		for(j=0;j<SABER_N/4;j++){
			offset_byte=offset_byte1+7*j;
			offset_data=4*j;
			bytes[offset_byte + 0]= ( data[i][ offset_data + 0 ] & (0xff));

			bytes[offset_byte + 1]= ( (data[i][ offset_data + 0 ] >>8) & 0x3f ) | ((data[i][ offset_data + 1 ] & 0x03) << 6);

			bytes[offset_byte + 2]= ( (data[i][ offset_data + 1 ] >>2) & 0xff );

			bytes[offset_byte + 3]= ( (data[i][ offset_data + 1 ] >>10) & 0x0f ) | ((data[i][ offset_data + 2 ] & 0x0f) << 4);

			bytes[offset_byte + 4]= ( (data[i][ offset_data + 2 ] >>4) & 0xff );

			bytes[offset_byte + 5]= ( (data[i][ offset_data + 2 ] >>12) & 0x03 ) | ((data[i][ offset_data + 3 ] & 0x3f) << 2);

			bytes[offset_byte + 6]= ( (data[i][ offset_data + 3 ] >>6) & 0xff );
		}
	}


}


void SABER_un_pack14bit(uint8_t *bytes, uint16_t data[SABER_K][SABER_N]){
	
	uint32_t i,j;
	uint32_t offset_data=0,offset_byte=0,offset_byte1=0;	
	
	offset_byte=0;
	for(i=0;i<SABER_K;i++){
		offset_byte1=i*(SABER_N*14)/8;
		for(j=0;j<SABER_N/4;j++){
			offset_byte=offset_byte1+7*j;
			offset_data=4*j;
			data[i][offset_data+ 0]=(bytes[offset_byte+0]&0xff) | ( (bytes[offset_byte + 1] & 0x3f) << 8 );

			data[i][offset_data+ 1]= ( (bytes[offset_byte+1] >>6)&0x03) | ((bytes[offset_byte+2]&0xff)<<2 ) | ( (bytes[offset_byte + 3] & 0x0f) << 10 );

			data[i][offset_data+ 2]= ( (bytes[offset_byte+3] >>4)&0x0f) | ( (bytes[offset_byte + 4] ) << 4 ) | ( (bytes[offset_byte + 5] & 0x03) << 12 );

			data[i][offset_data+ 3]= ( (bytes[offset_byte+5] >>2)&0x3f) | ( (bytes[offset_byte + 6] ) << 6 );
		}
	}


}



void POLVEC2BS(uint8_t *bytes, uint16_t data[SABER_K][SABER_N], uint16_t modulus){

	if(modulus==1024)
		POLVECp2BS(bytes, data);
	else if(modulus==8192)
		POLVECq2BS(bytes, data);
}

void POLVEC2BSX4(uint8_t *bytes0, uint8_t *bytes1, uint8_t *bytes2, uint8_t *bytes3, 
			uint16_t data0[SABER_K][SABER_N], uint16_t data1[SABER_K][SABER_N], 
			uint16_t data2[SABER_K][SABER_N], uint16_t data3[SABER_K][SABER_N], 
			uint16_t modulus){

	if(modulus==1024)
		POLVECp2BSX4(bytes0, bytes1, bytes2, bytes3, data0, data1, data2, data3);
	else if(modulus==8192)
		POLVECq2BSX4(bytes0, bytes1, bytes2, bytes3, data0, data1, data2, data3);
}



void BS2POLVEC(const unsigned char *bytes, uint16_t data[SABER_K][SABER_N], uint16_t modulus){

	if(modulus==1024)
		BS2POLVECp(bytes, data);
	else if(modulus==8192)
		BS2POLVECq(bytes, data);

}

void BS2POLVECX4(const unsigned char *bytes0, const unsigned char *bytes1, const unsigned char *bytes2, const unsigned char *bytes3,
		__m256i data0[SABER_K][SABER_N/16], __m256i data1[SABER_K][SABER_N/16], __m256i data2[SABER_K][SABER_N/16], __m256i data3[SABER_K][SABER_N/16],
		uint16_t modulus){

	if(modulus==1024)
		BS2POLVECpX4(bytes0, bytes1, bytes2, bytes3, data0, data1, data2, data3);
	else if(modulus==8192){
		BS2POLVECqX4(bytes0, bytes1, bytes2, bytes3, data0, data1, data2, data3);
	}

}





