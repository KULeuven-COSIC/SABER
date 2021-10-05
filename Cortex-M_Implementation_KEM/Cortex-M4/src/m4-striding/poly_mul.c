#include <stdint.h>
#include "poly_mul.h"
#include <string.h>

#define SABER_TC_INV3  43691
#define SABER_TC_INV9  36409
#define SABER_TC_INV15 61167


void toom_cook_4way_striding(uint16_t a[SABER_N], uint16_t b[SABER_N], uint16_t res[SABER_N]);

void poly_mul(uint16_t a[SABER_N], uint16_t b[SABER_N], uint16_t res[SABER_N])
{
	// uint32_t i;
	// uint16_t c[2*SABER_N - 1];

	// memset(c, 0, (2*SABER_N-1)*2);

	// polymul_asm(c, a, b);

	// for (i = SABER_N; i < 2*SABER_N-1; i++){
	//	 res[i - SABER_N] = (c[i - SABER_N] - c[i]);
	// }
	// res[SABER_N - 1] = c[SABER_N - 1];

	memset(res, 0, 2*SABER_N);
	//toom_cook_4way_mem_asm(a, b, res);
	toom_cook_4way_striding(a, b, res);
}

void poly_mul_acc(uint16_t a[SABER_N], uint16_t b[SABER_N], uint16_t res[SABER_N])
{
	// uint32_t i;
	// uint16_t c[2*SABER_N - 1];

	// polymul_asm(c, a, b);

	// for (i = SABER_N; i < 2*SABER_N-1; i++){
	//	 res[i - SABER_N] += (c[i - SABER_N] - c[i]);
	// }
	// res[SABER_N - 1] += c[SABER_N - 1];

	//toom_cook_4way_mem_asm(a, b, res);
	toom_cook_4way_striding(a, b, res);
}

void toom_cook_4way_striding(uint16_t a[SABER_N], uint16_t b[SABER_N], uint16_t res[SABER_N])
{
	//uint16_t aw1[64], aw2[64], aw3[64], aw4[64], aw5[64], aw6[64], aw7[64];
	//uint16_t bw2[64], bw3[64], bw4[64], bw5[64], bw6[64], bw7[64];
	uint16_t stack[13*64];

	uint16_t r0, r1, r2, r3, r4, r5, r6, r7, r8, r9;

	int i,j;

	//toom_cook_4way_striding_asm(a, b, res, stack);

// EVALUATION
	for (j = 0; j < 64; ++j) {
		r0 = a[4*j];
		r1 = a[4*j+1];
		r2 = a[4*j+2];
		r3 = a[4*j+3];
		r4 = r0 + r2;
		r5 = r1 + r3;
		r6 = r4 + r5; r7 = r4 - r5;
		stack[2*64+j] = r6;
		stack[3*64+j] = r7;
		r4 = ((r0 << 2)+r2) << 1;
		r5 = (r1 << 2) + r3;
		r6 = r4 + r5; r7 = r4 - r5;
		stack[4*64+j] = r6;
		stack[5*64+j] = r7;
		r4 = (r3 << 3) + (r2 << 2) + (r1 << 1) + r0;
		stack[64+j] = r4; stack[6*64+j] = r0;
		stack[j] = r3;
	}
	for (j = 0; j < 64; ++j) {
		r0 = b[4*j];
		r1 = b[4*j+1];
		r2 = b[4*j+2];
		r3 = b[4*j+3];
		r4 = r0 + r2;
		r5 = r1 + r3;
		r6 = r4 + r5; r7 = r4 - r5;
		stack[8*64+j] = r6;
		stack[9*64+j] = r7;
		r4 = ((r0 << 2)+r2) << 1;
		r5 = (r1 << 2) + r3;
		r6 = r4 + r5; r7 = r4 - r5;
		stack[10*64+j] = r6;
		stack[11*64+j] = r7;
		r4 = (r3 << 3) + (r2 << 2) + (r1 << 1) + r0;
		stack[7*64+j] = r4; stack[12*64+j] = r0;
		b[j] = r3;
	}

// MULTIPLICATION
	kara_strd_mem_asm(stack,b,&b[64], &b[128]);
	kara_strd_mem_asm(&stack[64],&stack[7*64],b   , &b[128]);
	kara_strd_mem_asm(&stack[2*64],&stack[8*64],&stack[7*64] , &b[128]);
	kara_strd_mem_asm(&stack[3*64],&stack[9*64],&stack[8*64] , &b[128]);
	kara_strd_mem_asm(&stack[4*64],&stack[10*64],&stack[9*64] , &b[128]);
	kara_strd_mem_asm(&stack[5*64],&stack[11*64],&stack[10*64] , &b[128]);
	kara_strd_mem_asm(&stack[6*64],&stack[12*64],&stack[11*64] , &b[128]);

// INTERPOLATION
	for (i = 0; i < 64; i++) {
		//save last round's r0, r1, r2
		r7=r0;
		r8=r1;
		r9=r2;

		r0 = b[64+i];
		r1 = b[i];
		r2 = stack[7*64+i];
		r3 = stack[8*64+i];
		r4 = stack[9*64+i];
		r5 = stack[10*64+i];
		r6 = stack[11*64+i];

		r1 = r1 + r4;
		r5 = r5 - r4;
		r3 = (r3-r2)>>1;
		r4 = r4 - r0;
		r4 = r4 - (r6 << 6);
		r4 = (r4 << 1) + r5;
		r2 = r2 + r3;
		r1 = r1 - (r2 << 6) - r2;
		r2 = r2 - r6;
		r2 = r2 - r0;
		r1 = r1 + 45*r2;
		r4 = (((r4 - (r2 << 3))*SABER_TC_INV3) >> 3);
		r5 = r5 + r1;
		r1 = (((r1 + (r3 << 4))*SABER_TC_INV9) >> 1);
		r3 = -(r3 + r1);
		r5 = ((30*r1 - r5)*SABER_TC_INV15>>2);
		r2 = r2 - r4;
		r1 = r1 - r5;

		res[3+4*i]	+= r3;
		if (i==0) {
			res[0+4*i]	+= r6;
			res[1+4*i]	+= r5;
			res[2+4*i]	+= r4;
		} else {
			res[0+4*i]	+= r6+r9;
			res[1+4*i]	+= r5+r8;
			res[2+4*i]	+= r4+r7;
		}
	}
	res[0]	-= r2;
	res[1]	-= r1;
	res[2]	-= r0;
}
