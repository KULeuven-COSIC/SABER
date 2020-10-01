#include <stddef.h>
#include <stdint.h>
#include "SABER_params.h"
#include "crypto_stream.h"
#include "symmetric.h"

void saber_aes256ctr_prf(unsigned char *output, unsigned long long outlen, const unsigned char *input)
{
	uint8_t ctr[16] = {0};
    crypto_stream_aes256ctr(output, (size_t)outlen, ctr, input);
}