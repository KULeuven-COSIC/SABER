#include "scm_avx.c"
#include "matrix.c"
#include "../../SABER_params.h"
#include "../../SABER_indcpa.h"


__m256i a_extra[2], b_extra[2];

void karatsuba32_fork_avx_new(__m256i* a1, __m256i* b1, uint8_t position)
{
		

	a[position] = a1[0];
	b[position] = b1[0];

	if((position+1)>15)
	{ 
		a_extra[0] = a1[1];
		b_extra[0] = b1[1];	

		a_extra[1] = _mm256_add_epi16(a1[0], a1[1]);
		b_extra[1] = _mm256_add_epi16(b1[0], b1[1]);
	}
	else
	{
		a[position+1] = a1[1];
		b[position+1] = b1[1];

		a[position+2] = _mm256_add_epi16(a1[0], a1[1]);
		b[position+2] = _mm256_add_epi16(b1[0], b1[1]);
	}
}

void karatsuba32_fork_avx_partial(__m256i* a1, __m256i* b1, uint8_t position)
{
		

		a[position] = a1[1];
		b[position] = b1[1];

		a[position+1] = _mm256_add_epi16(a1[0], a1[1]);
		b[position+1] = _mm256_add_epi16(b1[0], b1[1]);
}

void karatsuba32_fork_avx_partial1(__m256i* a1, __m256i* b1, uint8_t position)
{
		

		a[position] = _mm256_add_epi16(a1[0], a1[1]);
		b[position] = _mm256_add_epi16(b1[0], b1[1]);
}

void karatsuba32_join_avx_new(__m256i* result_final, uint8_t position)
{
	

		result_final[0] = c_avx[position];   
		result_final[3] = c_avx[position+1+16];

		// b[0] = resultd0[n-1:n/2] + resultd01[n/2-1:0]
		b[0] = _mm256_add_epi16(c_avx[position+16], c_avx[position+2]);

		// b[1] = resultd01[n-1:n/2] + resultd1[n/2-1:0]
		b[1] = _mm256_add_epi16(c_avx[position+2+16], c_avx[position+1]);
		
		// b[0] = b[0] - a[0] - a[2]		
		b[2] = _mm256_sub_epi16(b[0], result_final[0]);
		result_final[1] = _mm256_sub_epi16(b[2], c_avx[position+1]);

		// b[1] = b[1] - a[1] - a[3]		
		b[2] = _mm256_sub_epi16(b[1], c_avx[position+16]);
		result_final[2] = _mm256_sub_epi16(b[2], result_final[3]);

}



void karatsuba32_join_avx_partial(__m256i* result_final, uint8_t position)
{
	

		// c_avx[position] --> c_avx_extra[0]
		// c_avx[position+16] --> c_avx_extra[1]
		// c_avx[position+1] --> c_avx[position]
		// c_avx[position+1+16] --> c_avx[position+16]
		// c_avx[position+2] --> c_avx[position+1]

		result_final[0] = c_avx_extra[0];   
		result_final[3] = c_avx[position+16];

		// b[0] = resultd0[n-1:n/2] + resultd01[n/2-1:0]
		b[0] = _mm256_add_epi16(c_avx_extra[1], c_avx[position+1]);

		// b[1] = resultd01[n-1:n/2] + resultd1[n/2-1:0]
		b[1] = _mm256_add_epi16(c_avx[position+1+16], c_avx[position]);
		
		// b[0] = b[0] - a[0] - a[2]		
		b[2] = _mm256_sub_epi16(b[0], result_final[0]);
		result_final[1] = _mm256_sub_epi16(b[2], c_avx[position]);

		// b[1] = b[1] - a[1] - a[3]		
		b[2] = _mm256_sub_epi16(b[1], c_avx_extra[1]);
		result_final[2] = _mm256_sub_epi16(b[2], result_final[3]);

}

void karatsuba32_join_avx_partial1(__m256i* result_final, uint8_t position)
{
		

		result_final[0] = c_avx_extra[0];   
		result_final[3] = c_avx[position+16];

		// b[0] = resultd0[n-1:n/2] + resultd01[n/2-1:0]
		b[0] = _mm256_add_epi16(c_avx_extra[1], c_avx[position+1]);

		// b[1] = resultd01[n-1:n/2] + resultd1[n/2-1:0]
		b[1] = _mm256_add_epi16(c_avx[position+1+16], c_avx[position]);
		
		// b[0] = b[0] - a[0] - a[2]		
		b[2] = _mm256_sub_epi16(b[0], result_final[0]);
		result_final[1] = _mm256_sub_epi16(b[2], c_avx[position]);

		// b[1] = b[1] - a[1] - a[3]		
		b[2] = _mm256_sub_epi16(b[1], c_avx_extra[1]);
		result_final[2] = _mm256_sub_epi16(b[2], result_final[3]);

}

void karatsuba32_join_avx_partial2(__m256i* result_final, uint8_t position)
{
	

		// c_avx[position] --> c_avx_extra[0]
		// c_avx[position+16] --> c_avx_extra[1]
		// c_avx[position+1] --> c_avx_extra[2]
		// c_avx[position+1+16] --> c_avx_extra[3]
		// c_avx[position+2] --> c_avx[position]
		// c_avx[position+2+16] --> c_avx[position+16]

		result_final[0] = c_avx_extra[0];   
		result_final[3] = c_avx_extra[3];

		// b[0] = resultd0[n-1:n/2] + resultd01[n/2-1:0]
		b[0] = _mm256_add_epi16(c_avx_extra[1], c_avx[position]);

		// b[1] = resultd01[n-1:n/2] + resultd1[n/2-1:0]
		b[1] = _mm256_add_epi16(c_avx[position+16], c_avx_extra[2]);
		
		// b[0] = b[0] - a[0] - a[2]		
		b[2] = _mm256_sub_epi16(b[0], result_final[0]);
		result_final[1] = _mm256_sub_epi16(b[2], c_avx_extra[2]);

		// b[1] = b[1] - a[1] - a[3]		
		b[2] = _mm256_sub_epi16(b[1], c_avx_extra[1]);
		result_final[2] = _mm256_sub_epi16(b[2], result_final[3]);

}


void join_32coefficient_results(__m256i result_d0[], __m256i result_d1[], __m256i result_d01[], __m256i result_64ks[])
{

		// {b[5],b[4]} = resultd0[63:32] + resultd01[31:0]
		b[4] = _mm256_add_epi16(result_d0[2], result_d01[0]);
		b[5] = _mm256_add_epi16(result_d0[3], result_d01[1]);

		// {b[7],b[6]} = resultd01[63:32] + resultd1[31:0]
		b[6] = _mm256_add_epi16(result_d01[2], result_d1[0]);
		b[7] = _mm256_add_epi16(result_d01[3], result_d1[1]);


		// {b[7],b[6],b[5],b[4]} <-- {b[7],b[6],b[5],b[4]} - {a[3],a[2],a[1],a[0]} - {a[7],a[6],a[5],a[4]}	
		result_64ks[2] = _mm256_sub_epi16(b[4], result_d0[0]);
		result_64ks[2] = _mm256_sub_epi16(result_64ks[2], result_d1[0]);
		result_64ks[3] = _mm256_sub_epi16(b[5], result_d0[1]);
		result_64ks[3] = _mm256_sub_epi16(result_64ks[3], result_d1[1]);
		result_64ks[4] = _mm256_sub_epi16(b[6], result_d0[2]);
		result_64ks[4] = _mm256_sub_epi16(result_64ks[4], result_d1[2]);
		result_64ks[5] = _mm256_sub_epi16(b[7], result_d0[3]);
		result_64ks[5] = _mm256_sub_epi16(result_64ks[5], result_d1[3]);

		result_64ks[0] = result_d0[0];
		result_64ks[1] = result_d0[1];
		result_64ks[6] = result_d1[2];
		result_64ks[7] = result_d1[3];
}

void batch_64coefficient_multiplications(
				 __m256i* a0, __m256i* b0, __m256i* result_final0, 
				 __m256i* a1, __m256i* b1, __m256i* result_final1,
				 __m256i* a2, __m256i* b2, __m256i* result_final2,
				 __m256i* a3, __m256i* b3, __m256i* result_final3,
				 __m256i* a4, __m256i* b4, __m256i* result_final4,
				 __m256i* a5, __m256i* b5, __m256i* result_final5,
				 __m256i* a6, __m256i* b6, __m256i* result_final6)
{

	__m256i a_lu_temp[2], b_lu_temp[2];
	__m256i result_d0[16], result_d1[16], result_d01[16];
	
	uint16_t i;
	
	
		// KS splitting of 1st 64-coeff multiplication
		for(i=0; i<2; i++)
		{
			a_lu_temp[i] = _mm256_add_epi16(a0[i], a0[2+i]);		
			b_lu_temp[i] = _mm256_add_epi16(b0[i], b0[2+i]);
		}
		karatsuba32_fork_avx_new(&a0[0], &b0[0], 0);	
		karatsuba32_fork_avx_new(&a0[2], &b0[2], 3);
		karatsuba32_fork_avx_new(a_lu_temp, b_lu_temp, 6);

		// KS splitting of 2nd 64-coeff multiplication
		for(i=0; i<2; i++)
		{
			a_lu_temp[i] = _mm256_add_epi16(a1[i], a1[2+i]);		
			b_lu_temp[i] = _mm256_add_epi16(b1[i], b1[2+i]);
		}
		karatsuba32_fork_avx_new(&a1[0], &b1[0], 9);    
		karatsuba32_fork_avx_new(&a1[2], &b1[2], 12);  
		karatsuba32_fork_avx_new(a_lu_temp, b_lu_temp, 15);	// Partial: loads only one of the three elements in the bucket

		// Compute 16 school-book multiplications in a batch.
		transpose(a);
		transpose(b);
		schoolbook_avx_new1();
		transpose(&c_avx[0]);
		transpose(&c_avx[16]);
		
		// store the partial multiplication result.
		c_avx_extra[0] = c_avx[15];
		c_avx_extra[1] = c_avx[15+16];

		karatsuba32_join_avx_new(result_d0, 0);
		karatsuba32_join_avx_new(result_d1, 3);
		karatsuba32_join_avx_new(result_d01, 6);
		
		// Final result of 1st 64-coeff multiplication
		join_32coefficient_results(result_d0, result_d1, result_d01, result_final0);



		karatsuba32_join_avx_new(result_d0, 9);
		karatsuba32_join_avx_new(result_d1, 12);


		// Fork 2 parts of previous operands
		karatsuba32_fork_avx_partial(a_lu_temp, b_lu_temp, 0);    	 

		// Fork multiplication of a2*b2
		for(i=0; i<2; i++)
		{
			a_lu_temp[i] = _mm256_add_epi16(a2[i], a2[2+i]);		
			b_lu_temp[i] = _mm256_add_epi16(b2[i], b2[2+i]);
		}
		karatsuba32_fork_avx_new(&a2[0], &b2[0], 2);   	
		karatsuba32_fork_avx_new(&a2[2], &b2[2], 5);
		karatsuba32_fork_avx_new(a_lu_temp, b_lu_temp, 8);

		// Fork multiplication of a3*b3
		for(i=0; i<2; i++)
		{
			a_lu_temp[i] = _mm256_add_epi16(a3[i], a3[2+i]);		
			b_lu_temp[i] = _mm256_add_epi16(b3[i], b3[2+i]);
		}
		karatsuba32_fork_avx_new(&a3[0], &b3[0], 11);   	
		karatsuba32_fork_avx_new(&a3[2], &b3[2], 14);		// Partial: loads only two of the three elements in the bucket

		transpose(a);
		transpose(b);   	 
		schoolbook_avx_new1();

		transpose(&c_avx[0]);
		transpose(&c_avx[16]);

		karatsuba32_join_avx_partial(result_d01, 0);	// Combine results of this computation with previous computation
		// Final result of 2nd 64-coeff multiplication
		join_32coefficient_results(result_d0, result_d1, result_d01, result_final1);

		// store the partial multiplication result. they will be combined after next batch multiplication
		c_avx_extra[0] = c_avx[14];
		c_avx_extra[1] = c_avx[14+16];
		c_avx_extra[2] = c_avx[15];
		c_avx_extra[3] = c_avx[15+16];




		karatsuba32_join_avx_new(result_d0, 2);
		karatsuba32_join_avx_new(result_d1, 5);
		karatsuba32_join_avx_new(result_d01, 8);
		
		// Final result of 3rd 64-coeff multiplication
		join_32coefficient_results(result_d0, result_d1, result_d01, result_final2);

		// Join d0 of 4th 64-coeff multiplication
		karatsuba32_join_avx_new(result_d0, 11);



		// Fork 1 part of previous operands
		karatsuba32_fork_avx_partial1(&a3[2], &b3[2], 0);    	 
		karatsuba32_fork_avx_new(a_lu_temp, b_lu_temp, 1);

		// Fork multiplication of a4*b4
		for(i=0; i<2; i++)
		{
			a_lu_temp[i] = _mm256_add_epi16(a4[i], a4[2+i]);		
			b_lu_temp[i] = _mm256_add_epi16(b4[i], b4[2+i]);
		}
		karatsuba32_fork_avx_new(&a4[0], &b4[0], 4);   	
		karatsuba32_fork_avx_new(&a4[2], &b4[2], 7);
		karatsuba32_fork_avx_new(a_lu_temp, b_lu_temp, 10);

		// Fork multiplication of a5*b5
		for(i=0; i<2; i++)
		{
			a_lu_temp[i] = _mm256_add_epi16(a5[i], a5[2+i]);		
			b_lu_temp[i] = _mm256_add_epi16(b5[i], b5[2+i]);
		}
		karatsuba32_fork_avx_new(&a5[0], &b5[0], 13);   	

		transpose(a);
		transpose(b);   	 
		schoolbook_avx_new1();

		transpose(&c_avx[0]);
		transpose(&c_avx[16]);

		karatsuba32_join_avx_partial2(result_d1, 0);
		karatsuba32_join_avx_new(result_d01, 1);

		// Final result of 4th 64-coeff multiplication
		join_32coefficient_results(result_d0, result_d1, result_d01, result_final3);




		karatsuba32_join_avx_new(result_d0, 4);
		karatsuba32_join_avx_new(result_d1, 7);
		karatsuba32_join_avx_new(result_d01, 10);

		// Final result of 5th 64-coeff multiplication
		join_32coefficient_results(result_d0, result_d1, result_d01, result_final4);

		karatsuba32_join_avx_new(result_d0, 13);
	


		// Fork remaining 2 parts of a5*b5
		karatsuba32_fork_avx_new(&a5[2], &b5[2], 0);
		karatsuba32_fork_avx_new(a_lu_temp, b_lu_temp, 3);
		
		// Fork multiplication of a6*b6
		for(i=0; i<2; i++)
		{
			a_lu_temp[i] = _mm256_add_epi16(a6[i], a6[2+i]);		
			b_lu_temp[i] = _mm256_add_epi16(b6[i], b6[2+i]);
		}

		karatsuba32_fork_avx_new(&a6[0], &b6[0], 6);   	
		karatsuba32_fork_avx_new(&a6[2], &b6[2], 9);
		karatsuba32_fork_avx_new(a_lu_temp, b_lu_temp, 12);

		transpose(a);
		transpose(b);   	 
		schoolbook_avx_new1();

		transpose(&c_avx[0]);
		transpose(&c_avx[16]);


		karatsuba32_join_avx_new(result_d1, 0);
		karatsuba32_join_avx_new(result_d01, 3);

		// Final result of 6th 64-coeff multiplication
		join_32coefficient_results(result_d0, result_d1, result_d01, result_final5);

		karatsuba32_join_avx_new(result_d0, 6);
		karatsuba32_join_avx_new(result_d1, 9);
		karatsuba32_join_avx_new(result_d01, 12);

		// Final result of 6th 64-coeff multiplication
		join_32coefficient_results(result_d0, result_d1, result_d01, result_final6);


}


void toom_cook_4way_avx(__m256i* a1_avx,__m256i* b1_avx, uint64_t p_mod, __m256i* res_avx_output){

	int16_t AVX_N = SABER_N/16;
	int16_t i;
	
	int16_t small_len_avx=AVX_N/4;

	//-----AVX data declaration-----------------
	__m256i res_avx[2*AVX_N];
	__m256i a_avx[small_len_avx],b_avx[small_len_avx];
	__m256i th_a_avx[small_len_avx],t_h_a_avx[small_len_avx];
	__m256i th_b_avx[small_len_avx],t_h_b_avx[small_len_avx];

	__m256i w1_avx[2*small_len_avx],w2_avx[2*small_len_avx],w3_avx[2*small_len_avx],w4_avx[2*small_len_avx],w5_avx[2*small_len_avx],w6_avx[2*small_len_avx],w7_avx[2*small_len_avx];


	__m256i temp1_avx[2*small_len_avx];

	//--------------------these data are created for place holding---------

	__m256i a1_ph_avx[small_len_avx],b1_ph_avx[small_len_avx];
	__m256i a2_ph_avx[small_len_avx],b2_ph_avx[small_len_avx];
	__m256i a3_ph_avx[small_len_avx],b3_ph_avx[small_len_avx];
	__m256i a4_ph_avx[small_len_avx],b4_ph_avx[small_len_avx];
	__m256i a5_ph_avx[small_len_avx],b5_ph_avx[small_len_avx];
	__m256i a6_ph_avx[small_len_avx],b6_ph_avx[small_len_avx];

	//--------------------these data are created for place holding ends---------

	//-----AVX data declaration ends------------

	

	
	p_mod=p_mod*8;


	//do the partial products
	
	//-------------------t0--------------------

	//create a(0)*b(0)

	for(i=0;i<small_len_avx;i++){
		_mm256_store_si256 (a1_ph_avx+i, a1_avx[0+i]);
		_mm256_store_si256 (b1_ph_avx+i, b1_avx[0+i]);
	}


	//-------------------t0 ends------------------
	
	//-------------------th and t_h. th <-a(1/2)*b(1/2). t_h <- a(-1/2)*b(-1/2) ---------------------
	//create partial sum for th and t_h
	
	for(i=0;i<small_len_avx;i++){//th_x_avx contains 4*x[0]
		th_a_avx[i]= _mm256_slli_epi16(a1_ph_avx[i],2);
		th_b_avx[i]= _mm256_slli_epi16(b1_ph_avx[i],2);
	
	//th_x_avx contains 4*x[0]+x[2]
		th_a_avx[i]= _mm256_add_epi16(th_a_avx[i],a1_avx[small_len_avx*2+i]);
		th_b_avx[i]= _mm256_add_epi16(th_b_avx[i],b1_avx[small_len_avx*2+i]);
	
	//th_x_avx contains 8*x[0]+2*x[2]
		th_a_avx[i]= _mm256_slli_epi16(th_a_avx[i],1);
		th_b_avx[i]= _mm256_slli_epi16(th_b_avx[i],1);
	
	//t_h_x_avx contains x[1]
		_mm256_store_si256 (t_h_a_avx+i, a1_avx[small_len_avx*1+i]);
		_mm256_store_si256 (t_h_b_avx+i, b1_avx[small_len_avx*1+i]);
	
	//t_h_x_avx contains 4*x[1]
		t_h_a_avx[i]= _mm256_slli_epi16(t_h_a_avx[i],2);
		t_h_b_avx[i]= _mm256_slli_epi16(t_h_b_avx[i],2);

	//th_x_avx contains 4*x[1]+x[3]
		t_h_a_avx[i]= _mm256_add_epi16(t_h_a_avx[i],a1_avx[small_len_avx*3+i]);
		t_h_b_avx[i]= _mm256_add_epi16(t_h_b_avx[i],b1_avx[small_len_avx*3+i]);
	}

	//create th

	for(i=0;i<small_len_avx;i++){
		a2_ph_avx[i]= _mm256_add_epi16(th_a_avx[i],t_h_a_avx[i]);
		b2_ph_avx[i]= _mm256_add_epi16(th_b_avx[i],t_h_b_avx[i]);
	}

	//create t_h

	for(i=0;i<small_len_avx;i++){
		a3_ph_avx[i]= _mm256_sub_epi16(th_a_avx[i],t_h_a_avx[i]);
		b3_ph_avx[i]= _mm256_sub_epi16(th_b_avx[i],t_h_b_avx[i]);
	}


	//-------------------t1 and t_1. t1 <-a(1)*b(1). t_1 <- a(-1)*b(-1) ---------------------

	//create partial sum for t_1 and t1
	
	for(i=0;i<small_len_avx;i++){//th_x_avx contains x[2]+x[0]
		th_a_avx[i]= _mm256_add_epi16(a1_avx[small_len_avx*2+i],a1_avx[small_len_avx*0+i]);
		th_b_avx[i]= _mm256_add_epi16(b1_avx[small_len_avx*2+i],b1_avx[small_len_avx*0+i]);
		
		//th_x_avx contains x[3]+x[1]
		t_h_a_avx[i]= _mm256_add_epi16(a1_avx[small_len_avx*3+i],a1_avx[small_len_avx*1+i]);
		t_h_b_avx[i]= _mm256_add_epi16(b1_avx[small_len_avx*3+i],b1_avx[small_len_avx*1+i]);
	}	
	

	//create t1
	for(i=0;i<small_len_avx;i++){// x[0]+x[1]+x[2]+x[3]
		a4_ph_avx[i]= _mm256_add_epi16(th_a_avx[i],t_h_a_avx[i]);
		b4_ph_avx[i]= _mm256_add_epi16(th_b_avx[i],t_h_b_avx[i]);
	}

	//create t_1
	for(i=0;i<small_len_avx;i++){//-x[3]+x[2]-x[1]+x[0]
		a5_ph_avx[i]= _mm256_sub_epi16(th_a_avx[i],t_h_a_avx[i]);
		b5_ph_avx[i]= _mm256_sub_epi16(th_b_avx[i],t_h_b_avx[i]);
	}


	//------------------t_inf------------------------------	
	//create t_inf

	for(i=0;i<small_len_avx;i++){//x_avx contains x[3]
		_mm256_store_si256 (a6_ph_avx+i, a1_avx[small_len_avx*3+i]);
		_mm256_store_si256 (b6_ph_avx+i, b1_avx[small_len_avx*3+i]);
	}	


	//-------------------t_inf ends----------------------
	
	//-------------------t2-------------------------
	for(i=0;i<small_len_avx;i++){// 2*x[3]
		a_avx[i]= _mm256_add_epi16(a6_ph_avx[i],a1_avx[small_len_avx*3+i]);
		b_avx[i]= _mm256_add_epi16(b6_ph_avx[i],b1_avx[small_len_avx*3+i]);

		// 2*x[3]+x[2]
		a_avx[i]= _mm256_add_epi16(a_avx[i],a1_avx[small_len_avx*2+i]);
		b_avx[i]= _mm256_add_epi16(b_avx[i],b1_avx[small_len_avx*2+i]);
		
		// 4*x[3]+2*x[2]
		a_avx[i]= _mm256_slli_epi16(a_avx[i],1);
		b_avx[i]= _mm256_slli_epi16(b_avx[i],1);
		
		// 4*x[3]+2*x[2]+x[1]
		a_avx[i]= _mm256_add_epi16(a_avx[i],a1_avx[small_len_avx*1+i]);
		b_avx[i]= _mm256_add_epi16(b_avx[i],b1_avx[small_len_avx*1+i]);
		
		// 8*x[3]+4*x[2]+2*x[1]
		a_avx[i]= _mm256_slli_epi16(a_avx[i],1);
		b_avx[i]= _mm256_slli_epi16(b_avx[i],1);
		
		// 8*x[3]+8*x[2]+2*x[1]+x[0]
		a_avx[i]= _mm256_add_epi16(a_avx[i],a1_avx[small_len_avx*0+i]);
		b_avx[i]= _mm256_add_epi16(b_avx[i],b1_avx[small_len_avx*0+i]);
	}
	

	batch_64coefficient_multiplications(
				 a1_ph_avx, b1_ph_avx, w7_avx, 
				 a2_ph_avx, b2_ph_avx, w5_avx,
				 a3_ph_avx, b3_ph_avx, w6_avx,
				 a4_ph_avx, b4_ph_avx, w3_avx,
				 a5_ph_avx, b5_ph_avx, w4_avx,
				 a6_ph_avx, b6_ph_avx, w1_avx,
				 a_avx, b_avx, w2_avx);
	


	/*	--------------------------------------------
		---------------Solution starts--------------
		--------------------------------------------

	*/
	

	for(i=0;i<2*small_len_avx;i++){
			
		w2_avx[i]= _mm256_add_epi16(w2_avx[i],w5_avx[i]);//w2 <- w2+w5
		w6_avx[i]= _mm256_sub_epi16(w6_avx[i],w5_avx[i]);// w6 <- w6-w5
		w4_avx[i]= _mm256_sub_epi16(w4_avx[i],w3_avx[i]);// w4 <- w4-w3
		
		w5_avx[i]= _mm256_sub_epi16(w5_avx[i],w1_avx[i]);// w5 <- w5-w1
		temp1_avx[i] = _mm256_slli_epi16(w7_avx[i],6); //temp <- 64*w7
		w5_avx[i]= _mm256_sub_epi16(w5_avx[i],temp1_avx[i]);// w5 <- w5-64*w7

		w4_avx[i] = _mm256_srli_epi16(w4_avx[i],1); //w4 <- w4/2
		w3_avx[i]= _mm256_add_epi16(w3_avx[i],w4_avx[i]);//w3 <- w3+w4

		temp1_avx[i] = _mm256_slli_epi16(w5_avx[i],1); //temp <- 2*w5
		w5_avx[i]= _mm256_add_epi16(w6_avx[i],temp1_avx[i]);//w5 <- 2*w5+w6

		temp1_avx[i] = _mm256_slli_epi16(w3_avx[i],6); //temp <- 64*w3
		temp1_avx[i] = _mm256_add_epi16(w3_avx[i],temp1_avx[i]); //temp <- 65*w3
		w2_avx[i]= _mm256_sub_epi16(w2_avx[i],temp1_avx[i]);// w2 <- w2-65*w3

		w3_avx[i]= _mm256_sub_epi16(w3_avx[i],w7_avx[i]);// w3 <- w3-w7
		w3_avx[i]= _mm256_sub_epi16(w3_avx[i],w1_avx[i]);// w3 <- w3-w1

		temp1_avx[i] = _mm256_mullo_epi16 (w3_avx[i],int45_avx); //temp <- 45*w3
		w2_avx[i] = _mm256_add_epi16(w2_avx[i],temp1_avx[i]); //w2 <- w2+45*w3

		temp1_avx[i] = _mm256_slli_epi16(w3_avx[i],3); //temp <- 8*w3
		w5_avx[i]= _mm256_sub_epi16(w5_avx[i],temp1_avx[i]);//w5 <- w5-8*w3

		w5_avx[i] = _mm256_mullo_epi16 (w5_avx[i],inv3_avx); //w5 <- w5*1/3
		w5_avx[i] = _mm256_srli_epi16 (w5_avx[i],3); //w5 <- w5*1/8 ---> w5=w5/24

		w6_avx[i] = _mm256_add_epi16(w2_avx[i],w6_avx[i]); //w6 <- w6+w2
		temp1_avx[i] = _mm256_slli_epi16(w4_avx[i],4); //temp <- 16*w4
		w2_avx[i] = _mm256_add_epi16(w2_avx[i],temp1_avx[i]); //w2 <- w2+16*w4

		w2_avx[i] = _mm256_mullo_epi16 (w2_avx[i],inv9_avx); //w2 <- w2*1/9
		w2_avx[i] = _mm256_srli_epi16 (w2_avx[i],1); //w2 <- w2*1/2 ---> w2=w2/18

		w3_avx[i]= _mm256_sub_epi16(w3_avx[i],w5_avx[i]);//w3 <- w3-w5
		
		w4_avx[i] = _mm256_add_epi16(w4_avx[i],w2_avx[i]); //w4 <- w4+w2

		w4_avx[i] = _mm256_sub_epi16(int0_avx,w4_avx[i]); //w4 <- -(w4+w2)

		temp1_avx[i] = _mm256_mullo_epi16 (w2_avx[i],int30_avx); //temp <- w2*30
		w6_avx[i]= _mm256_sub_epi16(temp1_avx[i],w6_avx[i]);//w6 <- 30*w2-w6

		w6_avx[i] = _mm256_mullo_epi16 (w6_avx[i],inv15_avx); //w6 <- w6*1/15
		w6_avx[i] = _mm256_srli_epi16 (w6_avx[i],2); //w6 <- w6*1/4 ---> w6=w6/60

		w2_avx[i]= _mm256_sub_epi16(w2_avx[i],w6_avx[i]);//w2 <- w2-w6

	}

	for(i=0; i<2*AVX_N; i++){
		res_avx[i]=_mm256_xor_si256 (res_avx[i], res_avx[i]);
	}	

	for(i=0;i<2*small_len_avx;i++){	
		res_avx[0*small_len_avx+i]=_mm256_add_epi16 (res_avx[0*small_len_avx+i], w7_avx[i]);
		res_avx[1*small_len_avx+i]=_mm256_add_epi16 (res_avx[1*small_len_avx+i], w6_avx[i]);
		res_avx[2*small_len_avx+i]=_mm256_add_epi16 (res_avx[2*small_len_avx+i], w5_avx[i]);
		res_avx[3*small_len_avx+i]=_mm256_add_epi16 (res_avx[3*small_len_avx+i], w4_avx[i]);
		res_avx[4*small_len_avx+i]=_mm256_add_epi16 (res_avx[4*small_len_avx+i], w3_avx[i]);
		res_avx[5*small_len_avx+i]=_mm256_add_epi16 (res_avx[5*small_len_avx+i], w2_avx[i]);
		res_avx[6*small_len_avx+i]=_mm256_add_epi16 (res_avx[6*small_len_avx+i], w1_avx[i]);
	}	


	// Reduction by X^256 + 1
	for(i=0; i<16; i++)
	res_avx_output[i] = _mm256_sub_epi16(res_avx[i], res_avx[i+16]);

}




