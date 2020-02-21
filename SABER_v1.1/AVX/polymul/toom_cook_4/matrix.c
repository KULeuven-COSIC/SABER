/*
// Helper function to print avx vector
void print_avx2(__m256i a)
{
	uint16_t a_array[16];
	_mm256_maskstore_epi32(&a_array, mask, a);
	int16_t i;
	for(i=0; i<16; i++)
	printf("%u, ", a_array[i]);
	printf("\n");	
}
*/

void transpose(__m256i *M)
{
	int i;
	__m256i tL[8], tH[8];
	__m256i bL[4], bH[4], cL[4], cH[4];
	__m256i dL[2], dH[2], eL[2], eH[2], fL[2], fH[2], gL[2], gH[2];

	for(i=0; i<8; i=i+1)
	{
		tL[i] = _mm256_unpacklo_epi16(M[2*i], M[2*i+1]); 
		tH[i] = _mm256_unpackhi_epi16(M[2*i], M[2*i+1]); 
	}

	for(i=0; i<4; i=i+1)
	{
		bL[i] = _mm256_unpacklo_epi32(tL[2*i], tL[2*i+1]); 
		bH[i] = _mm256_unpackhi_epi32(tL[2*i], tL[2*i+1]); 
	}
	for(i=0; i<4; i=i+1)
	{
		cL[i] = _mm256_unpacklo_epi32(tH[2*i], tH[2*i+1]); 
		cH[i] = _mm256_unpackhi_epi32(tH[2*i], tH[2*i+1]); 
	}

	for(i=0; i<2; i=i+1)
	{
		dL[i] = _mm256_unpacklo_epi64(bL[2*i], bL[2*i+1]); 
		dH[i] = _mm256_unpackhi_epi64(bL[2*i], bL[2*i+1]); 
	}
	for(i=0; i<2; i=i+1)
	{
		eL[i] = _mm256_unpacklo_epi64(bH[2*i], bH[2*i+1]); 
		eH[i] = _mm256_unpackhi_epi64(bH[2*i], bH[2*i+1]); 
	}

	for(i=0; i<2; i=i+1)
	{
		fL[i] = _mm256_unpacklo_epi64(cL[2*i], cL[2*i+1]); 
		fH[i] = _mm256_unpackhi_epi64(cL[2*i], cL[2*i+1]); 
	}
	for(i=0; i<2; i=i+1)
	{
		gL[i] = _mm256_unpacklo_epi64(cH[2*i], cH[2*i+1]); 
		gH[i] = _mm256_unpackhi_epi64(cH[2*i], cH[2*i+1]); 
	}

	M[0] = _mm256_permute2f128_si256(dL[0], dL[1], 0x20);
	M[8] = _mm256_permute2f128_si256(dL[0], dL[1], 0x31);
	M[1] = _mm256_permute2f128_si256(dH[0], dH[1], 0x20);
	M[9] = _mm256_permute2f128_si256(dH[0], dH[1], 0x31);

	M[2] = _mm256_permute2f128_si256(eL[0], eL[1], 0x20);
	M[10] = _mm256_permute2f128_si256(eL[0], eL[1], 0x31);
	M[3] = _mm256_permute2f128_si256(eH[0], eH[1], 0x20);
	M[11] = _mm256_permute2f128_si256(eH[0], eH[1], 0x31);

	M[4] = _mm256_permute2f128_si256(fL[0], fL[1], 0x20);
	M[12] = _mm256_permute2f128_si256(fL[0], fL[1], 0x31);
	M[5] = _mm256_permute2f128_si256(fH[0], fH[1], 0x20);
	M[13] = _mm256_permute2f128_si256(fH[0], fH[1], 0x31);

	M[6] = _mm256_permute2f128_si256(gL[0], gL[1], 0x20);
	M[14] = _mm256_permute2f128_si256(gL[0], gL[1], 0x31);
	M[7] = _mm256_permute2f128_si256(gH[0], gH[1], 0x20);
	M[15] = _mm256_permute2f128_si256(gH[0], gH[1], 0x31);
}

