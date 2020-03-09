#include <stdio.h>
#include "encode.h"

#define P_SIZE 10
#define SCALE_SIZE 3
#define P_1 P_SIZE-1

#define TWO_SCALE_MINUS1 ((1<<SCALE_SIZE)-1)
#define H2 ( (1<<(P_1-1)) - (1<<(P_1-SCALE_SIZE-1)) )

uint16_t floor_special(uint16_t a)
{

	int sign;
	uint16_t b;
	int16_t abs;
	int16_t sign2, temp;


	sign = (a>>15) & 0x01;
	
        abs = sign*(0-a) + (1-sign)*a;      // absolute value of a in constant time;

		
	//b = (abs>>9); 			   
	b = abs; 			    

	
	// when a is -ve, we need to do more computation (but in constant time)
	temp = abs & 0x01ff;	// least 9 bits of a;

	temp = -temp;		// if temp was 0, then result is 0; otherwise -ve. so the sign bit tells it.

	

	sign2 = (temp>>15) & 0x01;
	
	
	abs = abs + sign*sign2;

	b = sign*(0-abs) + (1-sign)*b;

	b = (b>>9) & 0x01;

	
	return(b);
}


// generates binary K2 from a and scale_data
void extract(uint16_t a, uint16_t scale_data, uint16_t *K2)
{
    uint16_t temp;

    temp = a - (scale_data<<(P_1-SCALE_SIZE)) + H2;	

    *K2 = floor_special(temp);

}

// generates ciphertext from input
void ciphertext_gen(uint16_t b, uint16_t *ciphertext)
{
 
    *ciphertext = (b >> 6);    // ciphertext = b>>6; hence 4 bits per coefficient
 
}

void GenCipherText(uint16_t *vprime, unsigned char *scl_c){


	uint16_t ciphertext_temp[SABER_N];
	int32_t i;

	for(i=0;i<SABER_N;i++)
		ciphertext_gen(vprime[i], ciphertext_temp+i);

	SABER_pack_4bit(scl_c, ciphertext_temp);



}

void ExtractKeyBits(uint16_t *scale_data,unsigned char *scale_ar,uint16_t *message_dec_unpacked){


	int32_t i;
	uint16_t op[SABER_N];	

	SABER_un_pack4bit(scale_ar, op);

	for(i=0;i<SABER_N;i++){
		    extract(scale_data[i], op[i], message_dec_unpacked+i);
	}


}

