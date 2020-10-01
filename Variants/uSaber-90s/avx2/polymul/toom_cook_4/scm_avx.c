#define SCM_SIZE 16


unsigned short a0_array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
unsigned short a1_array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
unsigned short a2_array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
unsigned short a3_array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
unsigned short b0_array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
unsigned short b1_array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
unsigned short b2_array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
unsigned short b3_array[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};


unsigned short a_array[SCM_SIZE][16];
unsigned short b_array[SCM_SIZE][16];	

// Schoolbook internal variables
__m256i a0, a1, a2, a3, b0, b1, b2, b3;
__m256i c0, c1, c2, c3, c4, c5, c6;
__m256i temp;

__m256i c_avx[2*SCM_SIZE]; 
__m256i a[SCM_SIZE+2]; 
__m256i b[SCM_SIZE+2]; 
__m256i c_avx_extra[4];



void load_avx_input_new(uint16_t* aa, uint16_t* bb, int index)
{
	int i, i_plus1;

	for(i=0; i<SCM_SIZE; i=i+2)
	{
		a_array[i][index] = aa[i];		
		b_array[i][index] = bb[i];		
		
		i_plus1 = i+1;
		a_array[i_plus1][index] = aa[i_plus1];		
		b_array[i_plus1][index] = bb[i_plus1];		
	}
}



void schoolbook_avx_new1()
{

	// Unrolled first triangle
	c_avx[0] = _mm256_mullo_epi16 (a[0], b[0]);
	c_avx[1] = _mm256_mullo_epi16 (a[0], b[1]);
	temp = _mm256_mullo_epi16 (a[1], b[0]);
	c_avx[1] = _mm256_add_epi16(c_avx[1], temp);
	c_avx[2] = _mm256_mullo_epi16 (a[0], b[2]);
	temp = _mm256_mullo_epi16 (a[1], b[1]);
	c_avx[2] = _mm256_add_epi16(c_avx[2], temp);
	temp = _mm256_mullo_epi16 (a[2], b[0]);
	c_avx[2] = _mm256_add_epi16(c_avx[2], temp);
	c_avx[3] = _mm256_mullo_epi16 (a[0], b[3]);
	temp = _mm256_mullo_epi16 (a[1], b[2]);
	c_avx[3] = _mm256_add_epi16(c_avx[3], temp);
	temp = _mm256_mullo_epi16 (a[2], b[1]);
	c_avx[3] = _mm256_add_epi16(c_avx[3], temp);
	temp = _mm256_mullo_epi16 (a[3], b[0]);
	c_avx[3] = _mm256_add_epi16(c_avx[3], temp);
	c_avx[4] = _mm256_mullo_epi16 (a[0], b[4]);
	temp = _mm256_mullo_epi16 (a[1], b[3]);
	c_avx[4] = _mm256_add_epi16(c_avx[4], temp);
	temp = _mm256_mullo_epi16 (a[2], b[2]);
	c_avx[4] = _mm256_add_epi16(c_avx[4], temp);
	temp = _mm256_mullo_epi16 (a[3], b[1]);
	c_avx[4] = _mm256_add_epi16(c_avx[4], temp);
	temp = _mm256_mullo_epi16 (a[4], b[0]);
	c_avx[4] = _mm256_add_epi16(c_avx[4], temp);
	c_avx[5] = _mm256_mullo_epi16 (a[0], b[5]);
	temp = _mm256_mullo_epi16 (a[1], b[4]);
	c_avx[5] = _mm256_add_epi16(c_avx[5], temp);
	temp = _mm256_mullo_epi16 (a[2], b[3]);
	c_avx[5] = _mm256_add_epi16(c_avx[5], temp);
	temp = _mm256_mullo_epi16 (a[3], b[2]);
	c_avx[5] = _mm256_add_epi16(c_avx[5], temp);
	temp = _mm256_mullo_epi16 (a[4], b[1]);
	c_avx[5] = _mm256_add_epi16(c_avx[5], temp);
	temp = _mm256_mullo_epi16 (a[5], b[0]);
	c_avx[5] = _mm256_add_epi16(c_avx[5], temp);
	c_avx[6] = _mm256_mullo_epi16 (a[0], b[6]);
	temp = _mm256_mullo_epi16 (a[1], b[5]);
	c_avx[6] = _mm256_add_epi16(c_avx[6], temp);
	temp = _mm256_mullo_epi16 (a[2], b[4]);
	c_avx[6] = _mm256_add_epi16(c_avx[6], temp);
	temp = _mm256_mullo_epi16 (a[3], b[3]);
	c_avx[6] = _mm256_add_epi16(c_avx[6], temp);
	temp = _mm256_mullo_epi16 (a[4], b[2]);
	c_avx[6] = _mm256_add_epi16(c_avx[6], temp);
	temp = _mm256_mullo_epi16 (a[5], b[1]);
	c_avx[6] = _mm256_add_epi16(c_avx[6], temp);
	temp = _mm256_mullo_epi16 (a[6], b[0]);
	c_avx[6] = _mm256_add_epi16(c_avx[6], temp);
	c_avx[7] = _mm256_mullo_epi16 (a[0], b[7]);
	temp = _mm256_mullo_epi16 (a[1], b[6]);
	c_avx[7] = _mm256_add_epi16(c_avx[7], temp);
	temp = _mm256_mullo_epi16 (a[2], b[5]);
	c_avx[7] = _mm256_add_epi16(c_avx[7], temp);
	temp = _mm256_mullo_epi16 (a[3], b[4]);
	c_avx[7] = _mm256_add_epi16(c_avx[7], temp);
	temp = _mm256_mullo_epi16 (a[4], b[3]);
	c_avx[7] = _mm256_add_epi16(c_avx[7], temp);
	temp = _mm256_mullo_epi16 (a[5], b[2]);
	c_avx[7] = _mm256_add_epi16(c_avx[7], temp);
	temp = _mm256_mullo_epi16 (a[6], b[1]);
	c_avx[7] = _mm256_add_epi16(c_avx[7], temp);
	temp = _mm256_mullo_epi16 (a[7], b[0]);
	c_avx[7] = _mm256_add_epi16(c_avx[7], temp);
	c_avx[8] = _mm256_mullo_epi16 (a[0], b[8]);
	temp = _mm256_mullo_epi16 (a[1], b[7]);
	c_avx[8] = _mm256_add_epi16(c_avx[8], temp);
	temp = _mm256_mullo_epi16 (a[2], b[6]);
	c_avx[8] = _mm256_add_epi16(c_avx[8], temp);
	temp = _mm256_mullo_epi16 (a[3], b[5]);
	c_avx[8] = _mm256_add_epi16(c_avx[8], temp);
	temp = _mm256_mullo_epi16 (a[4], b[4]);
	c_avx[8] = _mm256_add_epi16(c_avx[8], temp);
	temp = _mm256_mullo_epi16 (a[5], b[3]);
	c_avx[8] = _mm256_add_epi16(c_avx[8], temp);
	temp = _mm256_mullo_epi16 (a[6], b[2]);
	c_avx[8] = _mm256_add_epi16(c_avx[8], temp);
	temp = _mm256_mullo_epi16 (a[7], b[1]);
	c_avx[8] = _mm256_add_epi16(c_avx[8], temp);
	temp = _mm256_mullo_epi16 (a[8], b[0]);
	c_avx[8] = _mm256_add_epi16(c_avx[8], temp);
	c_avx[9] = _mm256_mullo_epi16 (a[0], b[9]);
	temp = _mm256_mullo_epi16 (a[1], b[8]);
	c_avx[9] = _mm256_add_epi16(c_avx[9], temp);
	temp = _mm256_mullo_epi16 (a[2], b[7]);
	c_avx[9] = _mm256_add_epi16(c_avx[9], temp);
	temp = _mm256_mullo_epi16 (a[3], b[6]);
	c_avx[9] = _mm256_add_epi16(c_avx[9], temp);
	temp = _mm256_mullo_epi16 (a[4], b[5]);
	c_avx[9] = _mm256_add_epi16(c_avx[9], temp);
	temp = _mm256_mullo_epi16 (a[5], b[4]);
	c_avx[9] = _mm256_add_epi16(c_avx[9], temp);
	temp = _mm256_mullo_epi16 (a[6], b[3]);
	c_avx[9] = _mm256_add_epi16(c_avx[9], temp);
	temp = _mm256_mullo_epi16 (a[7], b[2]);
	c_avx[9] = _mm256_add_epi16(c_avx[9], temp);
	temp = _mm256_mullo_epi16 (a[8], b[1]);
	c_avx[9] = _mm256_add_epi16(c_avx[9], temp);
	temp = _mm256_mullo_epi16 (a[9], b[0]);
	c_avx[9] = _mm256_add_epi16(c_avx[9], temp);
	c_avx[10] = _mm256_mullo_epi16 (a[0], b[10]);
	temp = _mm256_mullo_epi16 (a[1], b[9]);
	c_avx[10] = _mm256_add_epi16(c_avx[10], temp);
	temp = _mm256_mullo_epi16 (a[2], b[8]);
	c_avx[10] = _mm256_add_epi16(c_avx[10], temp);
	temp = _mm256_mullo_epi16 (a[3], b[7]);
	c_avx[10] = _mm256_add_epi16(c_avx[10], temp);
	temp = _mm256_mullo_epi16 (a[4], b[6]);
	c_avx[10] = _mm256_add_epi16(c_avx[10], temp);
	temp = _mm256_mullo_epi16 (a[5], b[5]);
	c_avx[10] = _mm256_add_epi16(c_avx[10], temp);
	temp = _mm256_mullo_epi16 (a[6], b[4]);
	c_avx[10] = _mm256_add_epi16(c_avx[10], temp);
	temp = _mm256_mullo_epi16 (a[7], b[3]);
	c_avx[10] = _mm256_add_epi16(c_avx[10], temp);
	temp = _mm256_mullo_epi16 (a[8], b[2]);
	c_avx[10] = _mm256_add_epi16(c_avx[10], temp);
	temp = _mm256_mullo_epi16 (a[9], b[1]);
	c_avx[10] = _mm256_add_epi16(c_avx[10], temp);
	temp = _mm256_mullo_epi16 (a[10], b[0]);
	c_avx[10] = _mm256_add_epi16(c_avx[10], temp);
	c_avx[11] = _mm256_mullo_epi16 (a[0], b[11]);
	temp = _mm256_mullo_epi16 (a[1], b[10]);
	c_avx[11] = _mm256_add_epi16(c_avx[11], temp);
	temp = _mm256_mullo_epi16 (a[2], b[9]);
	c_avx[11] = _mm256_add_epi16(c_avx[11], temp);
	temp = _mm256_mullo_epi16 (a[3], b[8]);
	c_avx[11] = _mm256_add_epi16(c_avx[11], temp);
	temp = _mm256_mullo_epi16 (a[4], b[7]);
	c_avx[11] = _mm256_add_epi16(c_avx[11], temp);
	temp = _mm256_mullo_epi16 (a[5], b[6]);
	c_avx[11] = _mm256_add_epi16(c_avx[11], temp);
	temp = _mm256_mullo_epi16 (a[6], b[5]);
	c_avx[11] = _mm256_add_epi16(c_avx[11], temp);
	temp = _mm256_mullo_epi16 (a[7], b[4]);
	c_avx[11] = _mm256_add_epi16(c_avx[11], temp);
	temp = _mm256_mullo_epi16 (a[8], b[3]);
	c_avx[11] = _mm256_add_epi16(c_avx[11], temp);
	temp = _mm256_mullo_epi16 (a[9], b[2]);
	c_avx[11] = _mm256_add_epi16(c_avx[11], temp);
	temp = _mm256_mullo_epi16 (a[10], b[1]);
	c_avx[11] = _mm256_add_epi16(c_avx[11], temp);
	temp = _mm256_mullo_epi16 (a[11], b[0]);
	c_avx[11] = _mm256_add_epi16(c_avx[11], temp);
	c_avx[12] = _mm256_mullo_epi16 (a[0], b[12]);
	temp = _mm256_mullo_epi16 (a[1], b[11]);
	c_avx[12] = _mm256_add_epi16(c_avx[12], temp);
	temp = _mm256_mullo_epi16 (a[2], b[10]);
	c_avx[12] = _mm256_add_epi16(c_avx[12], temp);
	temp = _mm256_mullo_epi16 (a[3], b[9]);
	c_avx[12] = _mm256_add_epi16(c_avx[12], temp);
	temp = _mm256_mullo_epi16 (a[4], b[8]);
	c_avx[12] = _mm256_add_epi16(c_avx[12], temp);
	temp = _mm256_mullo_epi16 (a[5], b[7]);
	c_avx[12] = _mm256_add_epi16(c_avx[12], temp);
	temp = _mm256_mullo_epi16 (a[6], b[6]);
	c_avx[12] = _mm256_add_epi16(c_avx[12], temp);
	temp = _mm256_mullo_epi16 (a[7], b[5]);
	c_avx[12] = _mm256_add_epi16(c_avx[12], temp);
	temp = _mm256_mullo_epi16 (a[8], b[4]);
	c_avx[12] = _mm256_add_epi16(c_avx[12], temp);
	temp = _mm256_mullo_epi16 (a[9], b[3]);
	c_avx[12] = _mm256_add_epi16(c_avx[12], temp);
	temp = _mm256_mullo_epi16 (a[10], b[2]);
	c_avx[12] = _mm256_add_epi16(c_avx[12], temp);
	temp = _mm256_mullo_epi16 (a[11], b[1]);
	c_avx[12] = _mm256_add_epi16(c_avx[12], temp);
	temp = _mm256_mullo_epi16 (a[12], b[0]);
	c_avx[12] = _mm256_add_epi16(c_avx[12], temp);
	c_avx[13] = _mm256_mullo_epi16 (a[0], b[13]);
	temp = _mm256_mullo_epi16 (a[1], b[12]);
	c_avx[13] = _mm256_add_epi16(c_avx[13], temp);
	temp = _mm256_mullo_epi16 (a[2], b[11]);
	c_avx[13] = _mm256_add_epi16(c_avx[13], temp);
	temp = _mm256_mullo_epi16 (a[3], b[10]);
	c_avx[13] = _mm256_add_epi16(c_avx[13], temp);
	temp = _mm256_mullo_epi16 (a[4], b[9]);
	c_avx[13] = _mm256_add_epi16(c_avx[13], temp);
	temp = _mm256_mullo_epi16 (a[5], b[8]);
	c_avx[13] = _mm256_add_epi16(c_avx[13], temp);
	temp = _mm256_mullo_epi16 (a[6], b[7]);
	c_avx[13] = _mm256_add_epi16(c_avx[13], temp);
	temp = _mm256_mullo_epi16 (a[7], b[6]);
	c_avx[13] = _mm256_add_epi16(c_avx[13], temp);
	temp = _mm256_mullo_epi16 (a[8], b[5]);
	c_avx[13] = _mm256_add_epi16(c_avx[13], temp);
	temp = _mm256_mullo_epi16 (a[9], b[4]);
	c_avx[13] = _mm256_add_epi16(c_avx[13], temp);
	temp = _mm256_mullo_epi16 (a[10], b[3]);
	c_avx[13] = _mm256_add_epi16(c_avx[13], temp);
	temp = _mm256_mullo_epi16 (a[11], b[2]);
	c_avx[13] = _mm256_add_epi16(c_avx[13], temp);
	temp = _mm256_mullo_epi16 (a[12], b[1]);
	c_avx[13] = _mm256_add_epi16(c_avx[13], temp);
	temp = _mm256_mullo_epi16 (a[13], b[0]);
	c_avx[13] = _mm256_add_epi16(c_avx[13], temp);
	c_avx[14] = _mm256_mullo_epi16 (a[0], b[14]);
	temp = _mm256_mullo_epi16 (a[1], b[13]);
	c_avx[14] = _mm256_add_epi16(c_avx[14], temp);
	temp = _mm256_mullo_epi16 (a[2], b[12]);
	c_avx[14] = _mm256_add_epi16(c_avx[14], temp);
	temp = _mm256_mullo_epi16 (a[3], b[11]);
	c_avx[14] = _mm256_add_epi16(c_avx[14], temp);
	temp = _mm256_mullo_epi16 (a[4], b[10]);
	c_avx[14] = _mm256_add_epi16(c_avx[14], temp);
	temp = _mm256_mullo_epi16 (a[5], b[9]);
	c_avx[14] = _mm256_add_epi16(c_avx[14], temp);
	temp = _mm256_mullo_epi16 (a[6], b[8]);
	c_avx[14] = _mm256_add_epi16(c_avx[14], temp);
	temp = _mm256_mullo_epi16 (a[7], b[7]);
	c_avx[14] = _mm256_add_epi16(c_avx[14], temp);
	temp = _mm256_mullo_epi16 (a[8], b[6]);
	c_avx[14] = _mm256_add_epi16(c_avx[14], temp);
	temp = _mm256_mullo_epi16 (a[9], b[5]);
	c_avx[14] = _mm256_add_epi16(c_avx[14], temp);
	temp = _mm256_mullo_epi16 (a[10], b[4]);
	c_avx[14] = _mm256_add_epi16(c_avx[14], temp);
	temp = _mm256_mullo_epi16 (a[11], b[3]);
	c_avx[14] = _mm256_add_epi16(c_avx[14], temp);
	temp = _mm256_mullo_epi16 (a[12], b[2]);
	c_avx[14] = _mm256_add_epi16(c_avx[14], temp);
	temp = _mm256_mullo_epi16 (a[13], b[1]);
	c_avx[14] = _mm256_add_epi16(c_avx[14], temp);
	temp = _mm256_mullo_epi16 (a[14], b[0]);
	c_avx[14] = _mm256_add_epi16(c_avx[14], temp);
	c_avx[15] = _mm256_mullo_epi16 (a[0], b[15]);
	temp = _mm256_mullo_epi16 (a[1], b[14]);
	c_avx[15] = _mm256_add_epi16(c_avx[15], temp);
	temp = _mm256_mullo_epi16 (a[2], b[13]);
	c_avx[15] = _mm256_add_epi16(c_avx[15], temp);
	temp = _mm256_mullo_epi16 (a[3], b[12]);
	c_avx[15] = _mm256_add_epi16(c_avx[15], temp);
	temp = _mm256_mullo_epi16 (a[4], b[11]);
	c_avx[15] = _mm256_add_epi16(c_avx[15], temp);
	temp = _mm256_mullo_epi16 (a[5], b[10]);
	c_avx[15] = _mm256_add_epi16(c_avx[15], temp);
	temp = _mm256_mullo_epi16 (a[6], b[9]);
	c_avx[15] = _mm256_add_epi16(c_avx[15], temp);
	temp = _mm256_mullo_epi16 (a[7], b[8]);
	c_avx[15] = _mm256_add_epi16(c_avx[15], temp);
	temp = _mm256_mullo_epi16 (a[8], b[7]);
	c_avx[15] = _mm256_add_epi16(c_avx[15], temp);
	temp = _mm256_mullo_epi16 (a[9], b[6]);
	c_avx[15] = _mm256_add_epi16(c_avx[15], temp);
	temp = _mm256_mullo_epi16 (a[10], b[5]);
	c_avx[15] = _mm256_add_epi16(c_avx[15], temp);
	temp = _mm256_mullo_epi16 (a[11], b[4]);
	c_avx[15] = _mm256_add_epi16(c_avx[15], temp);
	temp = _mm256_mullo_epi16 (a[12], b[3]);
	c_avx[15] = _mm256_add_epi16(c_avx[15], temp);
	temp = _mm256_mullo_epi16 (a[13], b[2]);
	c_avx[15] = _mm256_add_epi16(c_avx[15], temp);
	temp = _mm256_mullo_epi16 (a[14], b[1]);
	c_avx[15] = _mm256_add_epi16(c_avx[15], temp);
	temp = _mm256_mullo_epi16 (a[15], b[0]);
	c_avx[15] = _mm256_add_epi16(c_avx[15], temp);

	// unrolled second triangle
	c_avx[16] = _mm256_mullo_epi16 (a[1], b[15]);
	temp = _mm256_mullo_epi16 (a[2], b[14]);
	c_avx[16] = _mm256_add_epi16(c_avx[16], temp);
	temp = _mm256_mullo_epi16 (a[3], b[13]);
	c_avx[16] = _mm256_add_epi16(c_avx[16], temp);
	temp = _mm256_mullo_epi16 (a[4], b[12]);
	c_avx[16] = _mm256_add_epi16(c_avx[16], temp);
	temp = _mm256_mullo_epi16 (a[5], b[11]);
	c_avx[16] = _mm256_add_epi16(c_avx[16], temp);
	temp = _mm256_mullo_epi16 (a[6], b[10]);
	c_avx[16] = _mm256_add_epi16(c_avx[16], temp);
	temp = _mm256_mullo_epi16 (a[7], b[9]);
	c_avx[16] = _mm256_add_epi16(c_avx[16], temp);
	temp = _mm256_mullo_epi16 (a[8], b[8]);
	c_avx[16] = _mm256_add_epi16(c_avx[16], temp);
	temp = _mm256_mullo_epi16 (a[9], b[7]);
	c_avx[16] = _mm256_add_epi16(c_avx[16], temp);
	temp = _mm256_mullo_epi16 (a[10], b[6]);
	c_avx[16] = _mm256_add_epi16(c_avx[16], temp);
	temp = _mm256_mullo_epi16 (a[11], b[5]);
	c_avx[16] = _mm256_add_epi16(c_avx[16], temp);
	temp = _mm256_mullo_epi16 (a[12], b[4]);
	c_avx[16] = _mm256_add_epi16(c_avx[16], temp);
	temp = _mm256_mullo_epi16 (a[13], b[3]);
	c_avx[16] = _mm256_add_epi16(c_avx[16], temp);
	temp = _mm256_mullo_epi16 (a[14], b[2]);
	c_avx[16] = _mm256_add_epi16(c_avx[16], temp);
	temp = _mm256_mullo_epi16 (a[15], b[1]);
	c_avx[16] = _mm256_add_epi16(c_avx[16], temp);
	c_avx[17] = _mm256_mullo_epi16 (a[2], b[15]);
	temp = _mm256_mullo_epi16 (a[3], b[14]);
	c_avx[17] = _mm256_add_epi16(c_avx[17], temp);
	temp = _mm256_mullo_epi16 (a[4], b[13]);
	c_avx[17] = _mm256_add_epi16(c_avx[17], temp);
	temp = _mm256_mullo_epi16 (a[5], b[12]);
	c_avx[17] = _mm256_add_epi16(c_avx[17], temp);
	temp = _mm256_mullo_epi16 (a[6], b[11]);
	c_avx[17] = _mm256_add_epi16(c_avx[17], temp);
	temp = _mm256_mullo_epi16 (a[7], b[10]);
	c_avx[17] = _mm256_add_epi16(c_avx[17], temp);
	temp = _mm256_mullo_epi16 (a[8], b[9]);
	c_avx[17] = _mm256_add_epi16(c_avx[17], temp);
	temp = _mm256_mullo_epi16 (a[9], b[8]);
	c_avx[17] = _mm256_add_epi16(c_avx[17], temp);
	temp = _mm256_mullo_epi16 (a[10], b[7]);
	c_avx[17] = _mm256_add_epi16(c_avx[17], temp);
	temp = _mm256_mullo_epi16 (a[11], b[6]);
	c_avx[17] = _mm256_add_epi16(c_avx[17], temp);
	temp = _mm256_mullo_epi16 (a[12], b[5]);
	c_avx[17] = _mm256_add_epi16(c_avx[17], temp);
	temp = _mm256_mullo_epi16 (a[13], b[4]);
	c_avx[17] = _mm256_add_epi16(c_avx[17], temp);
	temp = _mm256_mullo_epi16 (a[14], b[3]);
	c_avx[17] = _mm256_add_epi16(c_avx[17], temp);
	temp = _mm256_mullo_epi16 (a[15], b[2]);
	c_avx[17] = _mm256_add_epi16(c_avx[17], temp);
	c_avx[18] = _mm256_mullo_epi16 (a[3], b[15]);
	temp = _mm256_mullo_epi16 (a[4], b[14]);
	c_avx[18] = _mm256_add_epi16(c_avx[18], temp);
	temp = _mm256_mullo_epi16 (a[5], b[13]);
	c_avx[18] = _mm256_add_epi16(c_avx[18], temp);
	temp = _mm256_mullo_epi16 (a[6], b[12]);
	c_avx[18] = _mm256_add_epi16(c_avx[18], temp);
	temp = _mm256_mullo_epi16 (a[7], b[11]);
	c_avx[18] = _mm256_add_epi16(c_avx[18], temp);
	temp = _mm256_mullo_epi16 (a[8], b[10]);
	c_avx[18] = _mm256_add_epi16(c_avx[18], temp);
	temp = _mm256_mullo_epi16 (a[9], b[9]);
	c_avx[18] = _mm256_add_epi16(c_avx[18], temp);
	temp = _mm256_mullo_epi16 (a[10], b[8]);
	c_avx[18] = _mm256_add_epi16(c_avx[18], temp);
	temp = _mm256_mullo_epi16 (a[11], b[7]);
	c_avx[18] = _mm256_add_epi16(c_avx[18], temp);
	temp = _mm256_mullo_epi16 (a[12], b[6]);
	c_avx[18] = _mm256_add_epi16(c_avx[18], temp);
	temp = _mm256_mullo_epi16 (a[13], b[5]);
	c_avx[18] = _mm256_add_epi16(c_avx[18], temp);
	temp = _mm256_mullo_epi16 (a[14], b[4]);
	c_avx[18] = _mm256_add_epi16(c_avx[18], temp);
	temp = _mm256_mullo_epi16 (a[15], b[3]);
	c_avx[18] = _mm256_add_epi16(c_avx[18], temp);
	c_avx[19] = _mm256_mullo_epi16 (a[4], b[15]);
	temp = _mm256_mullo_epi16 (a[5], b[14]);
	c_avx[19] = _mm256_add_epi16(c_avx[19], temp);
	temp = _mm256_mullo_epi16 (a[6], b[13]);
	c_avx[19] = _mm256_add_epi16(c_avx[19], temp);
	temp = _mm256_mullo_epi16 (a[7], b[12]);
	c_avx[19] = _mm256_add_epi16(c_avx[19], temp);
	temp = _mm256_mullo_epi16 (a[8], b[11]);
	c_avx[19] = _mm256_add_epi16(c_avx[19], temp);
	temp = _mm256_mullo_epi16 (a[9], b[10]);
	c_avx[19] = _mm256_add_epi16(c_avx[19], temp);
	temp = _mm256_mullo_epi16 (a[10], b[9]);
	c_avx[19] = _mm256_add_epi16(c_avx[19], temp);
	temp = _mm256_mullo_epi16 (a[11], b[8]);
	c_avx[19] = _mm256_add_epi16(c_avx[19], temp);
	temp = _mm256_mullo_epi16 (a[12], b[7]);
	c_avx[19] = _mm256_add_epi16(c_avx[19], temp);
	temp = _mm256_mullo_epi16 (a[13], b[6]);
	c_avx[19] = _mm256_add_epi16(c_avx[19], temp);
	temp = _mm256_mullo_epi16 (a[14], b[5]);
	c_avx[19] = _mm256_add_epi16(c_avx[19], temp);
	temp = _mm256_mullo_epi16 (a[15], b[4]);
	c_avx[19] = _mm256_add_epi16(c_avx[19], temp);
	c_avx[20] = _mm256_mullo_epi16 (a[5], b[15]);
	temp = _mm256_mullo_epi16 (a[6], b[14]);
	c_avx[20] = _mm256_add_epi16(c_avx[20], temp);
	temp = _mm256_mullo_epi16 (a[7], b[13]);
	c_avx[20] = _mm256_add_epi16(c_avx[20], temp);
	temp = _mm256_mullo_epi16 (a[8], b[12]);
	c_avx[20] = _mm256_add_epi16(c_avx[20], temp);
	temp = _mm256_mullo_epi16 (a[9], b[11]);
	c_avx[20] = _mm256_add_epi16(c_avx[20], temp);
	temp = _mm256_mullo_epi16 (a[10], b[10]);
	c_avx[20] = _mm256_add_epi16(c_avx[20], temp);
	temp = _mm256_mullo_epi16 (a[11], b[9]);
	c_avx[20] = _mm256_add_epi16(c_avx[20], temp);
	temp = _mm256_mullo_epi16 (a[12], b[8]);
	c_avx[20] = _mm256_add_epi16(c_avx[20], temp);
	temp = _mm256_mullo_epi16 (a[13], b[7]);
	c_avx[20] = _mm256_add_epi16(c_avx[20], temp);
	temp = _mm256_mullo_epi16 (a[14], b[6]);
	c_avx[20] = _mm256_add_epi16(c_avx[20], temp);
	temp = _mm256_mullo_epi16 (a[15], b[5]);
	c_avx[20] = _mm256_add_epi16(c_avx[20], temp);
	c_avx[21] = _mm256_mullo_epi16 (a[6], b[15]);
	temp = _mm256_mullo_epi16 (a[7], b[14]);
	c_avx[21] = _mm256_add_epi16(c_avx[21], temp);
	temp = _mm256_mullo_epi16 (a[8], b[13]);
	c_avx[21] = _mm256_add_epi16(c_avx[21], temp);
	temp = _mm256_mullo_epi16 (a[9], b[12]);
	c_avx[21] = _mm256_add_epi16(c_avx[21], temp);
	temp = _mm256_mullo_epi16 (a[10], b[11]);
	c_avx[21] = _mm256_add_epi16(c_avx[21], temp);
	temp = _mm256_mullo_epi16 (a[11], b[10]);
	c_avx[21] = _mm256_add_epi16(c_avx[21], temp);
	temp = _mm256_mullo_epi16 (a[12], b[9]);
	c_avx[21] = _mm256_add_epi16(c_avx[21], temp);
	temp = _mm256_mullo_epi16 (a[13], b[8]);
	c_avx[21] = _mm256_add_epi16(c_avx[21], temp);
	temp = _mm256_mullo_epi16 (a[14], b[7]);
	c_avx[21] = _mm256_add_epi16(c_avx[21], temp);
	temp = _mm256_mullo_epi16 (a[15], b[6]);
	c_avx[21] = _mm256_add_epi16(c_avx[21], temp);
	c_avx[22] = _mm256_mullo_epi16 (a[7], b[15]);
	temp = _mm256_mullo_epi16 (a[8], b[14]);
	c_avx[22] = _mm256_add_epi16(c_avx[22], temp);
	temp = _mm256_mullo_epi16 (a[9], b[13]);
	c_avx[22] = _mm256_add_epi16(c_avx[22], temp);
	temp = _mm256_mullo_epi16 (a[10], b[12]);
	c_avx[22] = _mm256_add_epi16(c_avx[22], temp);
	temp = _mm256_mullo_epi16 (a[11], b[11]);
	c_avx[22] = _mm256_add_epi16(c_avx[22], temp);
	temp = _mm256_mullo_epi16 (a[12], b[10]);
	c_avx[22] = _mm256_add_epi16(c_avx[22], temp);
	temp = _mm256_mullo_epi16 (a[13], b[9]);
	c_avx[22] = _mm256_add_epi16(c_avx[22], temp);
	temp = _mm256_mullo_epi16 (a[14], b[8]);
	c_avx[22] = _mm256_add_epi16(c_avx[22], temp);
	temp = _mm256_mullo_epi16 (a[15], b[7]);
	c_avx[22] = _mm256_add_epi16(c_avx[22], temp);
	c_avx[23] = _mm256_mullo_epi16 (a[8], b[15]);
	temp = _mm256_mullo_epi16 (a[9], b[14]);
	c_avx[23] = _mm256_add_epi16(c_avx[23], temp);
	temp = _mm256_mullo_epi16 (a[10], b[13]);
	c_avx[23] = _mm256_add_epi16(c_avx[23], temp);
	temp = _mm256_mullo_epi16 (a[11], b[12]);
	c_avx[23] = _mm256_add_epi16(c_avx[23], temp);
	temp = _mm256_mullo_epi16 (a[12], b[11]);
	c_avx[23] = _mm256_add_epi16(c_avx[23], temp);
	temp = _mm256_mullo_epi16 (a[13], b[10]);
	c_avx[23] = _mm256_add_epi16(c_avx[23], temp);
	temp = _mm256_mullo_epi16 (a[14], b[9]);
	c_avx[23] = _mm256_add_epi16(c_avx[23], temp);
	temp = _mm256_mullo_epi16 (a[15], b[8]);
	c_avx[23] = _mm256_add_epi16(c_avx[23], temp);
	c_avx[24] = _mm256_mullo_epi16 (a[9], b[15]);
	temp = _mm256_mullo_epi16 (a[10], b[14]);
	c_avx[24] = _mm256_add_epi16(c_avx[24], temp);
	temp = _mm256_mullo_epi16 (a[11], b[13]);
	c_avx[24] = _mm256_add_epi16(c_avx[24], temp);
	temp = _mm256_mullo_epi16 (a[12], b[12]);
	c_avx[24] = _mm256_add_epi16(c_avx[24], temp);
	temp = _mm256_mullo_epi16 (a[13], b[11]);
	c_avx[24] = _mm256_add_epi16(c_avx[24], temp);
	temp = _mm256_mullo_epi16 (a[14], b[10]);
	c_avx[24] = _mm256_add_epi16(c_avx[24], temp);
	temp = _mm256_mullo_epi16 (a[15], b[9]);
	c_avx[24] = _mm256_add_epi16(c_avx[24], temp);
	c_avx[25] = _mm256_mullo_epi16 (a[10], b[15]);
	temp = _mm256_mullo_epi16 (a[11], b[14]);
	c_avx[25] = _mm256_add_epi16(c_avx[25], temp);
	temp = _mm256_mullo_epi16 (a[12], b[13]);
	c_avx[25] = _mm256_add_epi16(c_avx[25], temp);
	temp = _mm256_mullo_epi16 (a[13], b[12]);
	c_avx[25] = _mm256_add_epi16(c_avx[25], temp);
	temp = _mm256_mullo_epi16 (a[14], b[11]);
	c_avx[25] = _mm256_add_epi16(c_avx[25], temp);
	temp = _mm256_mullo_epi16 (a[15], b[10]);
	c_avx[25] = _mm256_add_epi16(c_avx[25], temp);
	c_avx[26] = _mm256_mullo_epi16 (a[11], b[15]);
	temp = _mm256_mullo_epi16 (a[12], b[14]);
	c_avx[26] = _mm256_add_epi16(c_avx[26], temp);
	temp = _mm256_mullo_epi16 (a[13], b[13]);
	c_avx[26] = _mm256_add_epi16(c_avx[26], temp);
	temp = _mm256_mullo_epi16 (a[14], b[12]);
	c_avx[26] = _mm256_add_epi16(c_avx[26], temp);
	temp = _mm256_mullo_epi16 (a[15], b[11]);
	c_avx[26] = _mm256_add_epi16(c_avx[26], temp);
	c_avx[27] = _mm256_mullo_epi16 (a[12], b[15]);
	temp = _mm256_mullo_epi16 (a[13], b[14]);
	c_avx[27] = _mm256_add_epi16(c_avx[27], temp);
	temp = _mm256_mullo_epi16 (a[14], b[13]);
	c_avx[27] = _mm256_add_epi16(c_avx[27], temp);
	temp = _mm256_mullo_epi16 (a[15], b[12]);
	c_avx[27] = _mm256_add_epi16(c_avx[27], temp);
	c_avx[28] = _mm256_mullo_epi16 (a[13], b[15]);
	temp = _mm256_mullo_epi16 (a[14], b[14]);
	c_avx[28] = _mm256_add_epi16(c_avx[28], temp);
	temp = _mm256_mullo_epi16 (a[15], b[13]);
	c_avx[28] = _mm256_add_epi16(c_avx[28], temp);
	c_avx[29] = _mm256_mullo_epi16 (a[14], b[15]);
	temp = _mm256_mullo_epi16 (a[15], b[14]);
	c_avx[29] = _mm256_add_epi16(c_avx[29], temp);
	c_avx[30] = _mm256_mullo_epi16 (a[15], b[15]);


	c_avx[2*SCM_SIZE-1] = _mm256_set_epi64x(0, 0, 0, 0);
}


// non unrolled code; not used though
void schoolbook_avx_new()
{
	int i, j;
	int scm_size_1, vv;

	
	for(i=0; i<SCM_SIZE; i=i+2)
	{
		a[i] = _mm256_loadu_si256 ((__m256i const *)a_array[i]);
		b[i] = _mm256_loadu_si256 ((__m256i const *)b_array[i]);	

		vv = i+1;
		a[vv] = _mm256_loadu_si256 ((__m256i const *)a_array[vv]);
		b[vv] = _mm256_loadu_si256 ((__m256i const *)b_array[vv]);	

	}
	

	// the first triangle
	for(i=0; i<SCM_SIZE; i++)
	{
		c_avx[i] = _mm256_mullo_epi16 (a[0], b[i]);	
		for(j=1; j<=i; j++)
		{
				temp = _mm256_mullo_epi16 (a[j], b[i-j]);
				c_avx[i] = _mm256_add_epi16(c_avx[i], temp);
		}
	}


	scm_size_1 = SCM_SIZE-1;
	

	// the second triangle
	for(i=1; i<SCM_SIZE; i++)
	{
		c_avx[scm_size_1+i] = _mm256_mullo_epi16 (a[i], b[scm_size_1]);	
		vv = scm_size_1+i;
		for(j=1; j<SCM_SIZE-i; j++)
		{
				temp = _mm256_mullo_epi16 (a[i+j], b[scm_size_1-j]);
				c_avx[vv] = _mm256_add_epi16(c_avx[vv], temp);
		}
	}
}
