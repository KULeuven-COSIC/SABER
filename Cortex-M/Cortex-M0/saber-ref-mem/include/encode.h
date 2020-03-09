#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include "SABER_params.h"
#include "pack_unpack.h"

void mask_gen(uint16_t b_avx, uint16_t *K1, uint16_t *mask_data);

void extract(uint16_t a, uint16_t mask_data, uint16_t *K2);

void ciphertext_gen(uint16_t b_avx, uint16_t *ciphertext);

void GenCipherText(uint16_t *vprime, unsigned char *msk_c);

void ExtractKeyBits(uint16_t *mask_data,unsigned char *mask_ar,uint16_t *message_dec_unpacked);
