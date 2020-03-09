#include "api.h"
#include "xmc1100.h"
#include "uart.h"
#include "prng.h"
#include "benchmark.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

//#define MEMSIZE
//#define SPEED
#define SPEED

// NOTE: seed for the random number generator is hardcoded in prng.c:rng_enable()

void initPorts(void);//to avoid stupid warning
void initPorts(void)
{
	// LED's are on P1.0 and P1.1
	// So make these push-pull outputs
	P1_IOCR0 = BIT15 + BIT7;
	P1_OUT = BIT0 + BIT1;
	P0_IOCR4 = BIT15;
	P0_OUT = BIT5;
}

#if !defined(MEMSIZE) && !defined(SPEED)
// test program for peripherals
int main(void)
{
	initPorts();
	UART_Init();
	rng_enable();
	setup_tick_count();

	unsigned char seed[16];
	uint32_t time;
	int i;
	while(1) {
		start_tick_count();
		P1_OUT ^= 0x01;
		for (i = 0; i < 1000000; ++i) {
		}
		P1_OUT ^= 0x02;
		randombytes(seed,16);
		UART_SendTrace((char*)seed,16,0);
		time = end_tick_count();
		UART_SendTrace("test time = ", 12, time);
	}

}
#endif

#ifdef SPEED

int main(void)
{
	unsigned char ss[CRYPTO_BYTES];
	unsigned char sk[CRYPTO_SECRETKEYBYTES];
	unsigned char pk[CRYPTO_PUBLICKEYBYTES];
	unsigned char ct[CRYPTO_CIPHERTEXTBYTES];
	//unsigned int t0, t1;
	uint32_t time;

	initPorts();
	UART_Init();
	setup_tick_count();
	rng_enable();

	// Key-pair generation
	// t0 = DWT_CYCCNT;
	start_tick_count();
	crypto_kem_keypair(pk, sk);
	// t1 = DWT_CYCCNT;
	// printcycles("keypair cycles:", t1-t0);
	time = end_tick_count();
	UART_SendTrace("keygen time= ", 13, time);

	// Encapsulation
	// t0 = DWT_CYCCNT;
	start_tick_count();
	crypto_kem_enc(ct, ss, pk);
	// t1 = DWT_CYCCNT;
	// printcycles("encaps cycles: ", t1-t0);
	time = end_tick_count();
	UART_SendTrace("encaps time= ", 13, time);

	// Decapsulation
	// t0 = DWT_CYCCNT;
	start_tick_count();
	crypto_kem_dec(ss, ct, sk);
	// t1 = DWT_CYCCNT;
	// printcycles("decaps cycles: ", t1-t0);
	time = end_tick_count();
	UART_SendTrace("decaps time= ", 13, time);

	return 0;
}

#endif

#ifdef MEMSIZE

#define MAXSTACK 0x2880
unsigned char key_a[CRYPTO_BYTES], key_b[CRYPTO_BYTES];
unsigned char pk[CRYPTO_PUBLICKEYBYTES];
unsigned char sendb[CRYPTO_CIPHERTEXTBYTES];
unsigned char sk_a[CRYPTO_SECRETKEYBYTES];
  
unsigned int ctr;
unsigned char canary;
volatile unsigned char *p;
extern unsigned char _end; 

static unsigned int stack_count(unsigned char canaryv,volatile unsigned char *a)
{
  //volatile unsigned char *p = (a-MAXSTACK);
  p = (a-MAXSTACK);
  unsigned int c = 0;
  while(*p == canaryv && p < a)
  {
    p++;
    c++;
  }
  return c;
} 

#define WRITE_CANARY(X) {p=X;while(p>= (X-MAXSTACK)) *(p--) = canary;}
 
int main(void)
{
	initPorts();
	UART_Init();
	rng_enable();


	volatile unsigned char a; /* Mark the beginning of the stack */
	//int i;
	//poly sk;
	canary = 42;

	WRITE_CANARY(&a);
	crypto_kem_keypair(pk, sk_a);
	ctr = MAXSTACK - stack_count(canary,&a);
	// sprintf((char *)output, "RAM usage of keygen: %d",ctr);
	//   send_USART_str(output);
	UART_SendTrace("RAM keygen", 10, ctr);

	WRITE_CANARY(&a);
	crypto_kem_enc(sendb, key_b, pk);
	ctr = MAXSTACK - stack_count(canary,&a);
	// sprintf((char *)output, "RAM usage of sharedb: %d",ctr);
	//   send_USART_str(output);
	UART_SendTrace("RAM encaps", 10, ctr);

	WRITE_CANARY(&a);   
	crypto_kem_dec(key_a, sendb, sk_a);
	ctr = MAXSTACK - stack_count(canary,&a);
	// sprintf((char *)output, "RAM usage of shareda: %d",ctr);
	//   send_USART_str(output);
	UART_SendTrace("RAM decaps", 10, ctr);

	WRITE_CANARY(&a);
	crypto_kem_keypair(pk, sk_a);
	crypto_kem_enc(sendb, key_b, pk);
	crypto_kem_dec(key_a, sendb, sk_a);
	ctr = MAXSTACK - stack_count(canary,&a);
	// sprintf((char *)output, "RAM usage of KEM: %d",ctr);
	//   send_USART_str(output);
	UART_SendTrace("RAM total", 9, ctr);

	return 0;
}

#endif
