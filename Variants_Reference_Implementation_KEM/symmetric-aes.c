#include <stddef.h>
#include <stdint.h>
#include "SABER_params.h"
#include "aes256ctr.h"
#include "symmetric.h"

void saber_aes256ctr_prf(unsigned char *output, unsigned long long outlen, const unsigned char *input)
{
	uint8_t expnonce[12] = {0};
	aes256ctr_prf(output, (size_t)outlen, input, expnonce);
}
