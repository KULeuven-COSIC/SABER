
#include "xmc1100.h"
#include "prng.h"
#include "uart.h"

#define SUCCESS 0
#define ERROR 1

/**
 * PRNG Random Data Block Size
 */
typedef enum PRNG_BLOCK_SIZE {
	PRNG_RDBS_RESET = 0U, /**< Reset state (initialization must be done) */
	PRNG_RDBS_BYTE  = 1U, /**< BYTE (8-bit) */
	PRNG_RDBS_WORD  = 2U  /**< WORD (16-bit) */
} PRNG_BLOCK_SIZE;

typedef struct PRNG_INIT
{
	uint16_t key_words[5];      /**< Keywords */
	PRNG_BLOCK_SIZE block_size; /**< Block size */
} PRNG_INIT;

uint8_t PRNG_Init (PRNG_INIT * prng);

void rng_enable()
{
	// Hard-coded seed
	//SHA256(seed) = 0x19b25856e1c150ca834cffc8b59b23adbd0ec0389e58eb22b3b64768098d002b
	PRNG_INIT prng = {{0x19b2, 0x5856, 0xe1c1, 0x50ca, 0x834c}, PRNG_RDBS_WORD};
	if (PRNG_Init(&prng)) {
		UART_Write("PRNG ERROR\r\n", 13);
	}
}

void randombytes(unsigned char *x,unsigned long long xlen)
{
    union
    {
        uint16_t aschar[2];
        uint32_t asint;
    } random;

    while (xlen > 2)
    {
        random.asint = PRNG_WORD;
        *x++ = random.aschar[0];
        *x++ = random.aschar[1];
        xlen -= 2;
    }
    if (xlen > 0)
    {
        for (random.asint = PRNG_WORD; xlen > 0; --xlen)
        {
            *x++ = random.aschar[xlen - 1];
        }
    }
}

uint8_t
PRNG_Init (PRNG_INIT * prng)
{
	volatile uint16_t read_warm_up;
	uint16_t reg_val, i;

	/* Configure block size for key loading mode */
	PRNG_CTRL = (uint16_t)((PRNG_CTRL & ~(0x03UL << 1)) | (PRNG_RDBS_WORD << 1));

	/* Enable key loading mode */
	PRNG_CTRL |= BIT3;

	/* Load key words (80 bits) and wait till RDV is set */
	for (i = 0; i < 5; ++i) {
		PRNG_WORD = prng->key_words[i];
		while (!(PRNG_CHK & BIT0));
	}

	// Enable Streaming Mode
	PRNG_CTRL &= ~ BIT3;

	/* Warm up phase: Read and discard 64 bits */
	read_warm_up = PRNG_WORD;
	read_warm_up = PRNG_WORD;
	read_warm_up = PRNG_WORD;
	reg_val      = PRNG_WORD;
	read_warm_up &= reg_val;

	/* Configure block size either byte (8 bit) or word (16 bit) */
	PRNG_CTRL = (uint16_t)((PRNG_CTRL & ~(0x03UL << 1)) | (prng->block_size << 1));

	/*
	 * Checks for reset value for "random data block size". If reset,
	 * PRNG is not initialized
	 */
	if (!(PRNG_CTRL & (0x03UL << 1))) {
		return ERROR;
	}

	return SUCCESS;
}
