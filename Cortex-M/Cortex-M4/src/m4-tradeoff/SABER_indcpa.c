#include <string.h>
#include <stdint.h>
#include "SABER_indcpa.h"
#include "poly.h"
#include "pack_unpack.h"
#include "poly_mul.h"
#include "fips202.h"
#include "SABER_params.h"
#include "randombytes.h"



/*-----------------------------------------------------------------------------------
	This routine generates a=[Matrix K x K] of 256-coefficient polynomials
-------------------------------------------------------------------------------------*/

#define h1 4 //2^(EQ-EP-1)

#define h2 ( (1<<(SABER_EP-2)) - (1<<(SABER_EP-SABER_ET-1)) + (1<<(SABER_EQ-SABER_EP-1)) )


void InnerProd(uint16_t pkcl[SABER_K][SABER_N],uint16_t skpv[SABER_K][SABER_N],uint16_t mod,uint16_t res[SABER_N]);
void MatrixVectorMul(polyvec *a, uint16_t skpv[SABER_K][SABER_N], uint16_t res[SABER_K][SABER_N], uint16_t mod, int16_t transpose);

void MatrixVectorMul_keypair(const unsigned char *seed, uint16_t skpv[SABER_K][SABER_N], uint16_t res[SABER_K][SABER_N], uint16_t mod);
void MatrixVectorMul_encryption(const unsigned char *seed, uint16_t skpv[SABER_K][SABER_N], unsigned char *ciphertext, uint16_t mod);

void VectorMul(const unsigned char *seed, uint16_t skpv[SABER_K][SABER_N],uint16_t res[SABER_N]);

void POL2MSG(uint16_t *message_dec_unpacked, unsigned char *message_dec);

void byte_bank2pol_part(unsigned char *bytes, uint16_t pol_part[], uint16_t pol_part_start_index, uint16_t num_8coeff)
{
	uint32_t j;
	uint32_t offset_data=0, offset_byte=0;	
	
	offset_byte=0;

	for(j=0;j<num_8coeff;j++)
	{
		offset_byte=13*j;
		offset_data=pol_part_start_index+8*j;
		pol_part[offset_data + 0]= ( bytes[ offset_byte + 0 ] & (0xff)) | ((bytes[offset_byte + 1] & 0x1f)<<8);
		pol_part[offset_data + 1]= ( bytes[ offset_byte + 1 ]>>5 & (0x07)) | ((bytes[offset_byte + 2] & 0xff)<<3) | ((bytes[offset_byte + 3] & 0x03)<<11);
		pol_part[offset_data + 2]= ( bytes[ offset_byte + 3 ]>>2 & (0x3f)) | ((bytes[offset_byte + 4] & 0x7f)<<6);
		pol_part[offset_data + 3]= ( bytes[ offset_byte + 4 ]>>7 & (0x01)) | ((bytes[offset_byte + 5] & 0xff)<<1) | ((bytes[offset_byte + 6] & 0x0f)<<9);
		pol_part[offset_data + 4]= ( bytes[ offset_byte + 6 ]>>4 & (0x0f)) | ((bytes[offset_byte + 7] & 0xff)<<4) | ((bytes[offset_byte + 8] & 0x01)<<12);
		pol_part[offset_data + 5]= ( bytes[ offset_byte + 8]>>1 & (0x7f)) | ((bytes[offset_byte + 9] & 0x3f)<<7);
		pol_part[offset_data + 6]= ( bytes[ offset_byte + 9]>>6 & (0x03)) | ((bytes[offset_byte + 10] & 0xff)<<2) | ((bytes[offset_byte + 11] & 0x07)<<10);
		pol_part[offset_data + 7]= ( bytes[ offset_byte + 11]>>3 & (0x1f)) | ((bytes[offset_byte + 12] & 0xff)<<5);
	}
}

void GenMatrix(polyvec *a, const unsigned char *seed) 
{
#if Saber_type == 3
	unsigned char shake_op_buf[SHAKE128_RATE+144];
#else	
	unsigned char shake_op_buf[SHAKE128_RATE+112];	// there can be at most 112 bytes left over from previous shake call
#endif
	uint16_t temp_ar[SABER_N];

  int i,j,k;

  uint64_t s[25];
  
  uint16_t pol_part_start_index, num_8coeff, num_8coeff_final, left_over_bytes, total_bytes;
  uint16_t row, column, num_polynomial;

  for (i = 0; i < 25; ++i)
    s[i] = 0;
  
  
  keccak_absorb(s, SHAKE128_RATE, seed, SABER_SEEDBYTES, 0x1F);

  pol_part_start_index=0; num_8coeff=0; left_over_bytes=0; total_bytes=0;
  num_polynomial=0;	

  while(num_polynomial!=9)
  {	

	keccak_squeezeblocks(shake_op_buf+left_over_bytes, 1, s, SHAKE128_RATE);

  	total_bytes = left_over_bytes + SHAKE128_RATE;

  	num_8coeff = total_bytes/13;

	if((num_8coeff*8+pol_part_start_index)>255)
		num_8coeff_final=32-pol_part_start_index/8;
	else 
		num_8coeff_final=num_8coeff;

	
  	byte_bank2pol_part(shake_op_buf, temp_ar, pol_part_start_index, num_8coeff_final);

  	left_over_bytes = total_bytes - num_8coeff_final*13;	


  	for(j=0; j<left_over_bytes; j++)	// bring the leftover in the begining of the buffer.
  		shake_op_buf[j] = shake_op_buf[num_8coeff_final*13+j];	

  	pol_part_start_index = pol_part_start_index + num_8coeff_final*8;	// this will be >256 when the polynomial is complete.

  	if(pol_part_start_index>255) 
  	{	 
		pol_part_start_index=0;

		if(num_polynomial>5) row=2;
		else if(num_polynomial>2) row=1;
        	else row = 0;
   
        	column = num_polynomial%3;
        	for(k=0;k<SABER_N;k++)
        	{
		   a[row].vec[column].coeffs[k] = temp_ar[k];
		}

		num_polynomial++;
	}
  }
}

void GenMatrix_poly(uint16_t temp_ar[], const unsigned char *seed, uint16_t poly_number) 
{
#if Saber_type == 3
  static unsigned char shake_op_buf[SHAKE128_RATE+144];	// there can be at most 112 bytes left over from previous shake call	
#else
  static unsigned char shake_op_buf[SHAKE128_RATE+112];	// there can be at most 112 bytes left over from previous shake call
#endif

  static int i,j;

  static uint64_t s[25];
  
  static uint16_t pol_part_start_index, num_8coeff, num_8coeff_final, left_over_bytes, total_bytes;
  static uint16_t poly_complete;


	// Init state when poly_number=0;

	if(poly_number==0)
	{
		for (i = 0; i < 25; ++i)
    		s[i] = 0;
  
  		keccak_absorb(s, SHAKE128_RATE, seed, SABER_SEEDBYTES, 0x1F);

  		pol_part_start_index=0; num_8coeff=0; left_over_bytes=0; total_bytes=0; 
	}


  poly_complete=0;

  while(poly_complete!=1)
  {	

	keccak_squeezeblocks(shake_op_buf+left_over_bytes, 1, s, SHAKE128_RATE);

  	total_bytes = left_over_bytes + SHAKE128_RATE;

  	num_8coeff = total_bytes/13;

	if((num_8coeff*8+pol_part_start_index)>255)
		num_8coeff_final=32-pol_part_start_index/8;
	else 
		num_8coeff_final=num_8coeff;

	
  	byte_bank2pol_part(shake_op_buf, temp_ar, pol_part_start_index, num_8coeff_final);

  	left_over_bytes = total_bytes - num_8coeff_final*13;	


  	for(j=0; j<left_over_bytes; j++)	// bring the leftover in the begining of the buffer.
  		shake_op_buf[j] = shake_op_buf[num_8coeff_final*13+j];	

  	pol_part_start_index = pol_part_start_index + num_8coeff_final*8;	// this will be >256 when the polynomial is complete.

  	if(pol_part_start_index>255) 
  	{	 
		pol_part_start_index=0;
		poly_complete++;
	}
  }

}

void indcpa_kem_keypair(unsigned char *pk, unsigned char *sk)
{
  // polyvec a[SABER_K];// skpv;

  uint16_t skpv[SABER_K][SABER_N];

  // unsigned char seed[SABER_SEEDBYTES];
  unsigned char noiseseed[SABER_COINBYTES];
  int32_t i,j;


  uint16_t res[SABER_K][SABER_N];

  // randombytes(seed, SABER_SEEDBYTES);
  randombytes(&pk[SABER_POLYVECCOMPRESSEDBYTES], SABER_SEEDBYTES);
  // shake128(seed, SABER_SEEDBYTES, seed, SABER_SEEDBYTES); // for not revealing system RNG state
  shake128(&pk[SABER_POLYVECCOMPRESSEDBYTES], SABER_SEEDBYTES, &pk[SABER_POLYVECCOMPRESSEDBYTES], SABER_SEEDBYTES); // for not revealing system RNG state
  randombytes(noiseseed, SABER_COINBYTES);

  // GenMatrix(a, seed);	//sample matrix A
  // GenMatrix(a, &pk[SABER_POLYVECCOMPRESSEDBYTES]);

  GenSecret(skpv,noiseseed);//generate secret from constant-time binomial distribution

  //------------------------do the matrix vector multiplication and rounding------------

	for(i=0;i<SABER_K;i++){
		for(j=0;j<SABER_N;j++){
			res[i][j]=0;
		}
	}

	// MatrixVectorMul(a,skpv,res,SABER_Q-1,1);
	// MatrixVectorMul_mem(&pk[SABER_POLYVECCOMPRESSEDBYTES],skpv,res,1);
	MatrixVectorMul_keypair(&pk[SABER_POLYVECCOMPRESSEDBYTES],skpv,res,SABER_Q-1);
	//MatrixVectorMul_keypair(seed,skpv,res,SABER_Q-1);

	  //-----now rounding

	for(i=0;i<SABER_K;i++){ //shift right 3 bits
		for(j=0;j<SABER_N;j++){
			res[i][j]=res[i][j] + h1;
			res[i][j]=(res[i][j]>>(SABER_EQ-SABER_EP));
		}
	}



	//------------------unload and pack sk=3 x (256 coefficients of 14 bits)-------

	// POLVEC2BS(sk, skpv, SABER_Q);
	POLVECq2BS(sk, skpv);

	//------------------unload and pack pk=256 bits seed and 3 x (256 coefficients of 11 bits)-------


	//POLVEC2BS(pk, res, SABER_P); // load the public-key coefficients
	POLVECp2BS(pk, res); // load the public-key coefficients



	// for(i=0;i<SABER_SEEDBYTES;i++){ // now load the seedbytes in PK. Easy since seed bytes are kept in byte format.
	// 	pk[SABER_POLYVECCOMPRESSEDBYTES + i]=seed[i];
	// }

}


void indcpa_kem_enc(unsigned char *message_received, unsigned char *noiseseed, const unsigned char *pk, unsigned char *ciphertext)
{
	uint32_t i,j;
	// polyvec a[SABER_K];		// skpv;
	// unsigned char seed[SABER_SEEDBYTES];
	// uint16_t pkcl[SABER_K][SABER_N]; 	//public key of received by the client

	uint16_t skpv1[SABER_K][SABER_N];

	// uint16_t message[SABER_KEYBYTES*8];
	uint16_t message_bit;

	// uint16_t res[SABER_K][SABER_N];
	//uint16_t acc[SABER_N];
	//uint16_t mod=SABER_Q-1;

	uint16_t vprime[SABER_N];

	//uint16_t ciphertext_temp[SABER_N];


	// unsigned char msk_c[SABER_SCALEBYTES_KEM];

	// for(i=0;i<SABER_SEEDBYTES;i++){ // extract the seedbytes from Public Key.
	// 	seed[i]=pk[ SABER_POLYVECCOMPRESSEDBYTES + i];
	// }


	// GenMatrix(a, seed);
	// GenMatrix(a, &pk[SABER_POLYVECCOMPRESSEDBYTES]);

	GenSecret(skpv1,noiseseed);//generate secret from constant-time binomial distribution
	//-----------------matrix-vector multiplication and rounding

	// for(i=0;i<SABER_K;i++){
	// 	for(j=0;j<SABER_N;j++){
	// 		res[i][j]=0;
	// 	}
	// }

	// MatrixVectorMul(a,skpv1,res,SABER_Q-1,0);

	//   //-----now rounding

	// for(i=0;i<SABER_K;i++){ //shift right 3 bits
	// 	for(j=0;j<SABER_N;j++){
	// 		res[i][j]=res[i][j]+ h1;
	// 		res[i][j]=(res[i][j]>> (SABER_EQ-SABER_EP));
	// 	}
	// }

	// //POLVEC2BS(ciphertext, res, SABER_P);
	// POLVECp2BS(ciphertext, res);

	MatrixVectorMul_encryption(&pk[SABER_POLYVECCOMPRESSEDBYTES], skpv1, ciphertext, SABER_Q-1);

//*******************************************************************client matrix-vector multiplication ends************************************

	//------now calculate the v'

	//-------unpack the public_key

	//BS2POLVEC(pk,pkcl,SABER_P);  //pkcl is the b in the protocol
	// BS2POLVECp(pk,pkcl);  //pkcl is the b in the protocol


	for(i=0;i<SABER_N;i++)
		vprime[i]=0;

	// for(i=0;i<SABER_K;i++){
	// 	for(j=0;j<SABER_N;j++){
	// 		skpv1[i][j]=skpv1[i][j] & ((SABER_P-1));
	// 	}
	// }

	// vector-vector scalar multiplication with mod p
	// InnerProd(pkcl,skpv1,(SABER_P-1),vprime);
	VectorMul(pk, skpv1, vprime);

	//addition of h1 to vprime
	// for(i=0;i<SABER_N;i++)
	// 	vprime[i]=vprime[i]+h1;


	for(j=0; j<SABER_KEYBYTES; j++)
	{
		for(i=0; i<8; i++)
		{
			message_bit = ((message_received[j]>>i) & 0x01);
			message_bit = (message_bit<<9);
			vprime[j*8+i]=vprime[j*8+i]- message_bit;
			//res[0][j*8+i]=res[0][j*8+i]+ message_bit;
		}
	}

	// // unpack message_received;
	// for(j=0; j<SABER_KEYBYTES; j++)
	// {
	// 	for(i=0; i<8; i++)
	// 	{
	// 		message[8*j+i] = ((message_received[j]>>i) & 0x01);
	// 	}
	// }

	// // message encoding
	// for(i=0; i<SABER_N; i++)
	// {
	// 	message[i] = (message[i]<<(SABER_EP-1));
	// }

	// for(i=0;i<SABER_N;i++)
	// {
	// 	vprime[i]=( (vprime[i] - message[i]) & (SABER_P-1) );

	// }


	for(i=0;i<SABER_N;i++)
	{

		vprime[i]=(vprime[i]+h1)>>(SABER_EP-SABER_ET);
	}

	#if Saber_type == 1
		// SABER_pack_3bit(msk_c, vprime);
		SABER_pack_3bit(&ciphertext[SABER_POLYVECCOMPRESSEDBYTES], vprime);
	#elif Saber_type == 2
		// SABER_pack_4bit(msk_c, vprime);
		SABER_pack_4bit(&ciphertext[SABER_POLYVECCOMPRESSEDBYTES], vprime);
	#elif Saber_type == 3
		// SABER_pack_6bit(msk_c, vprime);
		SABER_pack_6bit(&ciphertext[SABER_POLYVECCOMPRESSEDBYTES], vprime);
	#endif


	// for(j=0;j<SABER_SCALEBYTES_KEM;j++){
	// 	ciphertext[SABER_POLYVECCOMPRESSEDBYTES + j] = msk_c[j];
	// }

}


void indcpa_kem_dec(const unsigned char *sk, const unsigned char *ciphertext, unsigned char message_dec[])
{

	uint32_t i,j;


	uint16_t sksv[SABER_K][SABER_N]; //secret key of the server


	// uint16_t pksv[SABER_K][SABER_N];

	// uint8_t scale_ar[SABER_SCALEBYTES_KEM];
	// uint16_t message_dec_unpacked[SABER_KEYBYTES*8];	// one element containes on decrypted bit;


	//uint16_t acc[SABER_N];

	uint16_t v[SABER_N];

	// uint16_t op[SABER_N];

	BS2POLVECq(sk, sksv); //sksv is the secret-key
	// BS2POLVECp(ciphertext, pksv); //pksv is the ciphertext

	// BS2POLVEC(sk, sksv, SABER_Q); //sksv is the secret-key
	// BS2POLVEC(ciphertext, pksv, SABER_P); //pksv is the ciphertext


	// vector-vector scalar multiplication with mod p
	// for(i=0;i<SABER_N;i++)
	// 	v[i]=0;

	#if Saber_type == 1
		// SABER_un_pack3bit(scale_ar, op);
		SABER_un_pack3bit(&ciphertext[SABER_POLYVECCOMPRESSEDBYTES], v);
	#elif Saber_type == 2
		// SABER_un_pack4bit(scale_ar, op);
		SABER_un_pack4bit(&ciphertext[SABER_POLYVECCOMPRESSEDBYTES], v);
	#elif Saber_type == 3
		// SABER_un_pack6bit(scale_ar, op);
		SABER_un_pack6bit(&ciphertext[SABER_POLYVECCOMPRESSEDBYTES], v);
	#endif

	for (i = 0; i < SABER_N; ++i) {
		v[i] = h2 - (v[i] << (SABER_EP-SABER_ET));
	}

	// for(i=0;i<SABER_K;i++){
	// 	for(j=0;j<SABER_N;j++){
	// 		sksv[i][j]=sksv[i][j] & ((SABER_P-1));
	// 	}
	// }

	// InnerProd(pksv,sksv,(SABER_P-1),v);
	VectorMul(ciphertext, sksv, v);

	//Extraction
	// for(i=0;i<SABER_SCALEBYTES_KEM;i++){
	// 	scale_ar[i]=ciphertext[SABER_POLYVECCOMPRESSEDBYTES+i];
	// }

	// #if Saber_type == 1
	// 	// SABER_un_pack3bit(scale_ar, op);
	// 	SABER_un_pack3bit(&ciphertext[SABER_POLYVECCOMPRESSEDBYTES], op);
	// #elif Saber_type == 2
	// 	// SABER_un_pack4bit(scale_ar, op);
	// 	SABER_un_pack4bit(&ciphertext[SABER_POLYVECCOMPRESSEDBYTES], op);
	// #elif Saber_type == 3
	// 	// SABER_un_pack6bit(scale_ar, op);
	// 	SABER_un_pack6bit(&ciphertext[SABER_POLYVECCOMPRESSEDBYTES], op);
	// #endif


	// //addition of h1
	// for(i=0;i<SABER_N;i++){
	// 	v[i]= ( ( v[i] + h2 - (op[i]<<(SABER_EP-SABER_ET)) ) & (SABER_P-1) ) >> (SABER_EP-1);
	// }
	for (i = 0; i < SABER_N; ++i) {
		v[i] = (v[i] & (SABER_P-1)) >> (SABER_EP-1);
	}

	// pack decrypted message
	POL2MSG(v, message_dec);
}

void MatrixVectorMul(polyvec *a, uint16_t skpv[SABER_K][SABER_N], uint16_t res[SABER_K][SABER_N], uint16_t mod, int16_t transpose){

	//uint16_t acc[SABER_N];
	int32_t i,j;
	//int32_t k;

	if(transpose==1){
		for(i=0;i<SABER_K;i++){
			for(j=0;j<SABER_K;j++){
				//toom_cook_4way_mem((uint16_t *)&a[j].vec[i], skpv[j], acc);
				toom_cook_4way_mem((uint16_t *)&a[j].vec[i], skpv[j], res[i]);

				/*for(k=0;k<SABER_N;k++){
					res[i][k]=res[i][k]+acc[k];
					res[i][k]=(res[i][k]&mod); //reduction mod p
					acc[k]=0; //clear the accumulator
				}*/

			}
		}
	}
	else{

		for(i=0;i<SABER_K;i++){
			for(j=0;j<SABER_K;j++){
				//toom_cook_4way_mem((uint16_t *)&a[i].vec[j], skpv[j], acc);
				toom_cook_4way_mem((uint16_t *)&a[i].vec[j], skpv[j], res[i]);
				/*for(k=0;k<SABER_N;k++){
					res[i][k]=res[i][k]+acc[k];
					res[i][k]=res[i][k]&mod; //reduction
					acc[k]=0; //clear the accumulator
				}*/

			}
		}
	}


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


void InnerProd(uint16_t pkcl[SABER_K][SABER_N],uint16_t skpv[SABER_K][SABER_N],uint16_t mod,uint16_t res[SABER_N])
{
	uint32_t j;
	//int32_t k;
	//uint16_t acc[SABER_N];

	// vector-vector scalar multiplication with mod p
	for(j=0;j<SABER_K;j++){
		//pol_mul(pkcl[j], skpv[j], acc , SABER_P, SABER_N);
		//toom_cook_4way_mem(pkcl[j], skpv[j], acc );
		toom_cook_4way_mem(pkcl[j], skpv[j], res );

			/**
			for(k=0;k<SABER_N;k++){
				res[k]=res[k]+acc[k];
				res[k]=res[k]&mod; //reduction
				acc[k]=0; //clear the accumulator
			}/**/
	}
}

void MatrixVectorMul_keypair(const unsigned char *seed, uint16_t skpv[SABER_K][SABER_N], uint16_t res[SABER_K][SABER_N], uint16_t mod)
{
	int32_t i,j,k;
	uint16_t temp_ar[SABER_N];

	for(i=0;i<SABER_K;i++){
		for(j=0;j<SABER_K;j++){
			GenMatrix_poly(temp_ar, seed, i+j);			
			toom_cook_4way_mem(temp_ar, skpv[i], res[j]);
		}
	}
}

void MatrixVectorMul_encryption(const unsigned char *seed, uint16_t skpv[SABER_K][SABER_N], unsigned char *ciphertext, uint16_t mod)
{
	uint16_t acc[SABER_N]; 
	int32_t i,j,k;
	uint16_t res[SABER_N];

	for(i=0;i<SABER_K;i++) {
		for(j=0;j<SABER_N;j++) {
			res[j]=0; acc[j]=0;
		}
		for(j=0;j<SABER_K;j++) {
			GenMatrix_poly(acc, seed, i+j);
			//toom_cook_4way(acc, skpv[j], acc, SABER_Q, SABER_N);
			//pol_mul(acc, skpv[j], acc, SABER_Q, SABER_N);	
			toom_cook_4way_mem(acc, skpv[j], res);
		}
		
		// Now one polynomial of the output vector is ready.
		// Rounding: perform bit manipulation before packing into ciphertext 
		for(k=0;k<SABER_N;k++) {
			res[k]=res[k]+4;
			res[k]=(res[k]>>3);
		}
		
		POLp2BS(ciphertext, res, i);
	}

}

void VectorMul(const unsigned char *byte_array, uint16_t skpv[SABER_K][SABER_N],uint16_t res[SABER_N]){

	uint32_t j;
	uint16_t pkcl[SABER_N];

	// vector-vector scalar multiplication with mod p
	for(j=0;j<SABER_K;j++){
		BS2POLp(j, byte_array, pkcl);
		toom_cook_4way_mem(pkcl, skpv[j], res);
	}
	// for(j=0;j<SABER_N;j++)
	// 	res[j]=res[j]&(SABER_P-1);
}

unsigned char MatrixVectorMul_encryption_cmp(const unsigned char *seed, uint16_t skpv[SABER_K][SABER_N], unsigned char *ciphertext, uint16_t mod)
{
	unsigned char fail = 0;
	uint16_t acc[SABER_N]; 
	int32_t i,j,k;
	uint16_t res[SABER_N];

	for(i=0;i<SABER_K;i++) {
		for(j=0;j<SABER_N;j++) {
			res[j]=0; acc[j]=0;
		}
		for(j=0;j<SABER_K;j++) {
			GenMatrix_poly(acc, seed, i+j);
			//toom_cook_4way(acc, skpv[j], acc, SABER_Q, SABER_N);
			toom_cook_4way_mem(acc, skpv[j], res);
		}
		// Now one polynomial of the output vector is ready.
		// Rounding: perform bit manipulation before packing into ciphertext 
		for(k=0;k<SABER_N;k++) {
			res[k]=res[k]+4;
			res[k]=(res[k]>>3);
		}
		
		fail |= POLp2BS_cmp(ciphertext, res, i);
	}
	return fail;
}

unsigned char indcpa_kem_enc_cmp(unsigned char *message_received, unsigned char *noiseseed, const unsigned char *pk, unsigned char *ciphertext)
{
	unsigned char fail = 0;

	uint32_t i,j;
	uint16_t skpv1[SABER_K][SABER_N];
	uint16_t message_bit;
	uint16_t vprime[SABER_N];

	GenSecret(skpv1,noiseseed);//generate secret from constant-time binomial distribution

	fail |= MatrixVectorMul_encryption_cmp(&pk[SABER_POLYVECCOMPRESSEDBYTES], skpv1, ciphertext, SABER_Q-1);

//********************client matrix-vector multiplication ends************************************

	for(i=0;i<SABER_N;i++)
		vprime[i]=0;

	VectorMul(pk, skpv1, vprime);

	for(j=0; j<SABER_KEYBYTES; j++) {
		for(i=0; i<8; i++) {
			message_bit = ((message_received[j]>>i) & 0x01);
			message_bit = (message_bit<<9);
			vprime[j*8+i]=vprime[j*8+i]- message_bit;
		}
	}

	for(i=0;i<SABER_N;i++) {
		vprime[i]=(vprime[i]+h1)>>(SABER_EP-SABER_ET);
	}

	#if Saber_type == 1
		fail |= SABER_pack_3bit_cmp(&ciphertext[SABER_POLYVECCOMPRESSEDBYTES], vprime);
	#elif Saber_type == 2
		fail |= SABER_pack_4bit_cmp(&ciphertext[SABER_POLYVECCOMPRESSEDBYTES], vprime);
	#elif Saber_type == 3
		fail |= SABER_pack_6bit_cmp(&ciphertext[SABER_POLYVECCOMPRESSEDBYTES], vprime);
	#endif

	fail = ~fail + 1;
	fail >>= 63;

	return (unsigned char)fail;
}
