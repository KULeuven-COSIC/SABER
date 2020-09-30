/* Based on the public domain implementation in
 * crypto_hash/keccakc512/simple/ from http://bench.cr.yp.to/supercop.html
 * by Ronny Van Keer
 * and the public domain "TweetFips202" implementation
 * from https://twitter.com/tweetfips202
 * by Gilles Van Assche, Daniel J. Bernstein, and Peter Schwabe */

#include <stdint.h>
#include <string.h>
#include "fips202.h"
#include "keccakf1600.h"

#define NROUNDS 24
#define ROL(a, offset) ((a << offset) ^ (a >> (64-offset)))
#define MIN(a, b) ((a) < (b) ? (a) : (b))


#ifdef PROFILE_HASHING
#include "hal.h"
extern unsigned long long hash_cycles;
#endif


/*************************************************
 * Name:        keccak_absorb
 *
 * Description: Absorb step of Keccak;
 *              non-incremental, starts by zeroeing the state.
 *
 * Arguments:   - uint64_t *s:             pointer to (uninitialized) output Keccak state
 *              - unsigned int r:          rate in bytes (e.g., 168 for SHAKE128)
 *              - const unsigned char *m:  pointer to input to be absorbed into s
 *              - unsigned long long mlen: length of input in bytes
 *              - unsigned char p:         domain-separation byte for different Keccak-derived functions
 **************************************************/
static void keccak_absorb(uint64_t *s,
    unsigned int r,
    const unsigned char *m, unsigned long long int mlen,
    unsigned char p)
{
  unsigned long long i;
  unsigned char t[200];

  while (mlen >= r)
  {
    KeccakF1600_StateXORBytes(s, m, 0, r);
    KeccakF1600_StatePermute(s);
    mlen -= r;
    m += r;
  }

  for (i = 0; i < r; ++i)
    t[i] = 0;
  for (i = 0; i < mlen; ++i)
    t[i] = m[i];
  t[i] = p;
  t[r - 1] |= 128;

  KeccakF1600_StateXORBytes(s, t, 0, r);
}


/*************************************************
 * Name:        keccak_squeezeblocks
 *
 * Description: Squeeze step of Keccak. Squeezes full blocks of r bytes each.
 *              Modifies the state. Can be called multiple times to keep squeezing,
 *              i.e., is incremental.
 *
 * Arguments:   - unsigned char *h:               pointer to output blocks
 *              - unsigned long long int nblocks: number of blocks to be squeezed (written to h)
 *              - uint64_t *s:                    pointer to in/output Keccak state
 *              - unsigned int r:                 rate in bytes (e.g., 168 for SHAKE128)
 **************************************************/
static void keccak_squeezeblocks(unsigned char *h, unsigned long long int nblocks,
    uint64_t *s,
    unsigned int r)
{
  while(nblocks > 0)
  {
    KeccakF1600_StatePermute(s);
    KeccakF1600_StateExtractBytes(s, h, 0, r);
    h += r;
    nblocks--;
  }
}

/*************************************************
 * Name:        keccak_inc_init
 *
 * Description: Initializes the incremental Keccak state to zero.
 *
 * Arguments:   - uint64_t *s_inc: pointer to input/output incremental state
 *                First 25 values represent Keccak state.
 *                26th value represents either the number of absorbed bytes
 *                that have not been permuted, or not-yet-squeezed bytes.
 **************************************************/
static void keccak_inc_init(uint64_t *s_inc) {
    size_t i;

    for (i = 0; i < 25; ++i) {
        s_inc[i] = 0;
    }
    s_inc[25] = 0;
}
/*************************************************
 * Name:        keccak_inc_absorb
 *
 * Description: Incremental keccak absorb
 *              Preceded by keccak_inc_init, succeeded by keccak_inc_finalize
 *
 * Arguments:   - uint64_t *s_inc: pointer to input/output incremental state
 *                First 25 values represent Keccak state.
 *                26th value represents either the number of absorbed bytes
 *                that have not been permuted, or not-yet-squeezed bytes.
 *              - uint32_t r: rate in bytes (e.g., 168 for SHAKE128)
 *              - const uint8_t *m: pointer to input to be absorbed into s
 *              - size_t mlen: length of input in bytes
 **************************************************/
static void keccak_inc_absorb(uint64_t *s_inc, uint32_t r, const uint8_t *m,
                              size_t mlen) {
    /* Recall that s_inc[25] is the non-absorbed bytes xored into the state */
    while (mlen + s_inc[25] >= r) {

        KeccakF1600_StateXORBytes(s_inc, m, s_inc[25], r-s_inc[25]);
        mlen -= (size_t)(r - s_inc[25]);
        m += r - s_inc[25];
        s_inc[25] = 0;

        KeccakF1600_StatePermute(s_inc);
    }

    KeccakF1600_StateXORBytes(s_inc, m, s_inc[25], mlen);
    s_inc[25] += mlen;
}

/*************************************************
 * Name:        keccak_inc_finalize
 *
 * Description: Finalizes Keccak absorb phase, prepares for squeezing
 *
 * Arguments:   - uint64_t *s_inc: pointer to input/output incremental state
 *                First 25 values represent Keccak state.
 *                26th value represents either the number of absorbed bytes
 *                that have not been permuted, or not-yet-squeezed bytes.
 *              - uint32_t r: rate in bytes (e.g., 168 for SHAKE128)
 *              - uint8_t p: domain-separation byte for different
 *                                 Keccak-derived functions
 **************************************************/
static void keccak_inc_finalize(uint64_t *s_inc, uint32_t r, uint8_t p) {
    /* After keccak_inc_absorb, we are guaranteed that s_inc[25] < r,
       so we can always use one more byte for p in the current state. */
    size_t i;
    unsigned char t[200];
    for (i = 0; i < r; ++i)
      t[i] = 0;
    t[s_inc[25]] = p;
    t[r - 1] |= 128;

    KeccakF1600_StateXORBytes(s_inc, t, 0, r);
}

/*************************************************
 * Name:        keccak_inc_squeeze
 *
 * Description: Incremental Keccak squeeze; can be called on byte-level
 *
 * Arguments:   - uint8_t *h: pointer to output bytes
 *              - size_t outlen: number of bytes to be squeezed
 *              - uint64_t *s_inc: pointer to input/output incremental state
 *                First 25 values represent Keccak state.
 *                26th value represents either the number of absorbed bytes
 *                that have not been permuted, or not-yet-squeezed bytes.
 *              - uint32_t r: rate in bytes (e.g., 168 for SHAKE128)
 **************************************************/
static void keccak_inc_squeeze(uint8_t *h, size_t outlen,
                               uint64_t *s_inc, uint32_t r) {
    size_t len;
    if(outlen < s_inc[25])
    {
        len = outlen;
    }
    else
    {
        len = s_inc[25];
    }

    KeccakF1600_StateExtractBytes(s_inc, h, r-s_inc[25], len);
    h += len;
    outlen -= len;
    s_inc[25] -= len;

    /* Then squeeze the remaining necessary blocks */
    while (outlen > 0) {
        KeccakF1600_StatePermute(s_inc);

        if(outlen < r)
        {
            len = outlen;
        }
        else
        {
            len = r;
        }
        KeccakF1600_StateExtractBytes(s_inc, h, 0, len);
        h += len;
        outlen -= len;
        s_inc[25] = r - len;
    }
}

void shake128_inc_init(uint64_t *s_inc) {
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
    keccak_inc_init(s_inc);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

void shake128_inc_absorb(uint64_t *s_inc, const uint8_t *input, size_t inlen) {
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
    keccak_inc_absorb(s_inc, SHAKE128_RATE, input, inlen);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

void shake128_inc_finalize(uint64_t *s_inc) {
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
    keccak_inc_finalize(s_inc, SHAKE128_RATE, 0x1F);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

void shake128_inc_squeeze(uint8_t *output, size_t outlen, uint64_t *s_inc) {
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
    keccak_inc_squeeze(output, outlen, s_inc, SHAKE128_RATE);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

void shake256_inc_init(uint64_t *s_inc) {
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
    keccak_inc_init(s_inc);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

void shake256_inc_absorb(uint64_t *s_inc, const uint8_t *input, size_t inlen) {
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
    keccak_inc_absorb(s_inc, SHAKE256_RATE, input, inlen);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

void shake256_inc_finalize(uint64_t *s_inc) {
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
    keccak_inc_finalize(s_inc, SHAKE256_RATE, 0x1F);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

void shake256_inc_squeeze(uint8_t *output, size_t outlen, uint64_t *s_inc) {
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
    keccak_inc_squeeze(output, outlen, s_inc, SHAKE256_RATE);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

/********** cSHAKE128 ***********/

void cshake128_simple_absorb(uint64_t s[25], uint16_t cstm, const unsigned char *in, unsigned long long inlen)
{
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif


  unsigned char sep[8];
  unsigned int i;

  for (i = 0; i < 25; i++)
    s[i] = 0;

  /* Absorb customization (domain-separation) string */
  sep[0] = 0x01;
  sep[1] = 0xa8;
  sep[2] = 0x01;
  sep[3] = 0x00;
  sep[4] = 0x01;
  sep[5] = 16; // fixed bitlen of cstm
  sep[6] = cstm & 0xff;
  sep[7] = cstm >> 8;

  KeccakF1600_StateXORBytes(s, sep, 0, 8);
  KeccakF1600_StatePermute(s);

  /* Absorb input */
  keccak_absorb(s, SHAKE128_RATE, in, inlen, 0x04);

#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif

}


void cshake128_simple_squeezeblocks(unsigned char *output, unsigned long long nblocks, uint64_t *s)
{
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
  keccak_squeezeblocks(output, nblocks, s, SHAKE128_RATE);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}


void cshake128_simple(unsigned char *output, unsigned long long outlen, uint16_t cstm, const unsigned char *in, unsigned long long inlen)
{
  uint64_t s[25];
  unsigned char t[SHAKE128_RATE];
  unsigned int i;

  cshake128_simple_absorb(s, cstm, in, inlen);

#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif

  /* Squeeze output */
  keccak_squeezeblocks(output, outlen/SHAKE128_RATE, s, SHAKE128_RATE);
  output += (outlen/SHAKE128_RATE)*SHAKE128_RATE;

  if (outlen%SHAKE128_RATE)
  {
    keccak_squeezeblocks(t, 1, s, SHAKE128_RATE);
    for (i = 0; i < outlen%SHAKE128_RATE; i++)
      output[i] = t[i];
  }
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}



/*************************************************
 * Name:        shake128_absorb
 *
 * Description: Absorb step of the SHAKE128 XOF.
 *              non-incremental, starts by zeroeing the state.
 *
 * Arguments:   - uint64_t *s:                     pointer to (uninitialized) output Keccak state
 *              - const unsigned char *input:      pointer to input to be absorbed into s
 *              - unsigned long long inputByteLen: length of input in bytes
 **************************************************/
void shake128_absorb(uint64_t *s, const unsigned char *input, unsigned int inputByteLen)
{
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
  int i;
  for (i = 0; i < 25; i++)
    s[i] = 0;

  keccak_absorb(s, SHAKE128_RATE, input, inputByteLen, 0x1F);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

/*************************************************
 * Name:        shake128_squeezeblocks
 *
 * Description: Squeeze step of SHAKE128 XOF. Squeezes full blocks of SHAKE128_RATE bytes each.
 *              Modifies the state. Can be called multiple times to keep squeezing,
 *              i.e., is incremental.
 *
 * Arguments:   - unsigned char *output:      pointer to output blocks
 *              - unsigned long long nblocks: number of blocks to be squeezed (written to output)
 *              - uint64_t *s:                pointer to in/output Keccak state
 **************************************************/
void shake128_squeezeblocks(unsigned char *output, unsigned long long nblocks, uint64_t *s)
{
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
  keccak_squeezeblocks(output, nblocks, s, SHAKE128_RATE);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

void shake128(unsigned char *output, unsigned long long outlen, const unsigned char *input, unsigned long long inlen)
{
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
  uint64_t s[25] = {0};
  unsigned char t[SHAKE128_RATE];
  unsigned long long nblocks = outlen/SHAKE128_RATE;
  size_t i;

  /* Absorb input */
  keccak_absorb(s, SHAKE128_RATE, input, inlen, 0x1F);

  /* Squeeze output */
  keccak_squeezeblocks(output, nblocks, s, SHAKE128_RATE);

  output += nblocks*SHAKE128_RATE;
  outlen -= nblocks*SHAKE128_RATE;

  if (outlen)
  {
    keccak_squeezeblocks(t, 1, s, SHAKE128_RATE);
    for (i = 0; i < outlen; i++)
      output[i] = t[i];
  }
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}


void shake256_absorb(uint64_t *s, const unsigned char *input, unsigned int inputByteLen)
{
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
  int i;
  for (i = 0; i < 25; i++)
    s[i] = 0;

  keccak_absorb(s, SHAKE256_RATE, input, inputByteLen, 0x1F);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}


void shake256_squeezeblocks(unsigned char *output, unsigned long long nblocks, uint64_t *s)
{
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
  keccak_squeezeblocks(output, nblocks, s, SHAKE256_RATE);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

/*************************************************
 * Name:        shake256
 *
 * Description: SHAKE256 XOF with non-incremental API
 *
 * Arguments:   - unsigned char *output:      pointer to output
 *              - unsigned long long outlen:  requested output length in bytes
 - const unsigned char *input: pointer to input
 - unsigned long long inlen:   length of input in bytes
 **************************************************/
void shake256(unsigned char *output, unsigned long long outlen,
    const unsigned char *input, unsigned long long inlen)
{
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
  uint64_t s[25] = {0};
  unsigned char t[SHAKE256_RATE];
  unsigned long long nblocks = outlen/SHAKE256_RATE;
  size_t i;

  /* Absorb input */
  keccak_absorb(s, SHAKE256_RATE, input, inlen, 0x1F);

  /* Squeeze output */
  keccak_squeezeblocks(output, nblocks, s, SHAKE256_RATE);

  output+=nblocks*SHAKE256_RATE;
  outlen-=nblocks*SHAKE256_RATE;

  if(outlen)
  {
    keccak_squeezeblocks(t, 1, s, SHAKE256_RATE);
    for(i=0;i<outlen;i++)
      output[i] = t[i];
  }
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

/*************************************************
 * Name:        sha3_256
 *
 * Description: SHA3-256 with non-incremental API
 *
 * Arguments:   - unsigned char *output:      pointer to output
 *              - const unsigned char *input: pointer to input
 *              - unsigned long long inlen:   length of input in bytes
 **************************************************/
void sha3_256(unsigned char *output, const unsigned char *input, unsigned long long inlen)
{
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
  uint64_t s[25] = {0};
  unsigned char t[SHA3_256_RATE];
  size_t i;

  /* Absorb input */
  keccak_absorb(s, SHA3_256_RATE, input, inlen, 0x06);

  /* Squeeze output */
  keccak_squeezeblocks(t, 1, s, SHA3_256_RATE);

  for(i=0;i<32;i++)
    output[i] = t[i];
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}
void sha3_256_inc_init(uint64_t *s_inc) {
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
    keccak_inc_init(s_inc);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

void sha3_256_inc_absorb(uint64_t *s_inc, const uint8_t *input, size_t inlen) {
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
    keccak_inc_absorb(s_inc, SHA3_256_RATE, input, inlen);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

void sha3_256_inc_finalize(uint8_t *output, uint64_t *s_inc) {
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
    uint8_t t[SHA3_256_RATE];
    keccak_inc_finalize(s_inc, SHA3_256_RATE, 0x06);

    keccak_squeezeblocks(t, 1, s_inc, SHA3_256_RATE);

    for (size_t i = 0; i < 32; i++) {
        output[i] = t[i];
    }
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

/*************************************************
 * Name:        sha3_512
 *
 * Description: SHA3-512 with non-incremental API
 *
 * Arguments:   - unsigned char *output:      pointer to output
 *              - const unsigned char *input: pointer to input
 *              - unsigned long long inlen:   length of input in bytes
 **************************************************/
void sha3_512(unsigned char *output, const unsigned char *input, unsigned long long inlen)
{
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
  uint64_t s[25] = {0};
  unsigned char t[SHA3_512_RATE];
  size_t i;

  /* Absorb input */
  keccak_absorb(s, SHA3_512_RATE, input, inlen, 0x06);

  /* Squeeze output */
  keccak_squeezeblocks(t, 1, s, SHA3_512_RATE);

  for(i=0;i<64;i++)
    output[i] = t[i];
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}
void sha3_512_inc_init(uint64_t *s_inc) {
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
    keccak_inc_init(s_inc);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

void sha3_512_inc_absorb(uint64_t *s_inc, const uint8_t *input, size_t inlen) {
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
    keccak_inc_absorb(s_inc, SHA3_512_RATE, input, inlen);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

void sha3_512_inc_finalize(uint8_t *output, uint64_t *s_inc) {
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
    uint8_t t[SHA3_512_RATE];
    keccak_inc_finalize(s_inc, SHA3_512_RATE, 0x06);

    keccak_squeezeblocks(t, 1, s_inc, SHA3_512_RATE);

    for (size_t i = 0; i < 32; i++) {
        output[i] = t[i];
    }
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}

/********** cSHAKE256 ***********/

void cshake256_simple_absorb(uint64_t s[25], uint16_t cstm, const unsigned char *in, unsigned long long inlen)
{
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
  unsigned char sep[8];
  unsigned int i;

  for (i = 0; i < 25; i++)
    s[i] = 0;

  /* Absorb customization (domain-separation) string */
  sep[0] = 0x01;
  sep[1] = 0x88;
  sep[2] = 0x01;
  sep[3] = 0x00;
  sep[4] = 0x01;
  sep[5] = 16; // fixed bitlen of cstm
  sep[6] = cstm & 0xff;
  sep[7] = cstm >> 8;

  KeccakF1600_StateXORBytes(s, sep, 0, 8);
  KeccakF1600_StatePermute(s);

  /* Absorb input */
  keccak_absorb(s, SHAKE256_RATE, in, inlen, 0x04);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}


void cshake256_simple_squeezeblocks(unsigned char *output, unsigned long long nblocks, uint64_t *s)
{
#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif
  keccak_squeezeblocks(output, nblocks, s, SHAKE256_RATE);
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}


void cshake256_simple(unsigned char *output, unsigned long long outlen, uint16_t cstm, const unsigned char *in, unsigned long long inlen)
{
  uint64_t s[25];
  unsigned char t[SHAKE256_RATE];
  unsigned int i;

  cshake256_simple_absorb(s, cstm, in, inlen);

#ifdef PROFILE_HASHING
  uint64_t t0 = hal_get_time();
#endif

  /* Squeeze output */
  keccak_squeezeblocks(output, outlen/SHAKE256_RATE, s, SHAKE256_RATE);
  output += (outlen/SHAKE256_RATE)*SHAKE256_RATE;

  if(outlen%SHAKE256_RATE)
  {
    keccak_squeezeblocks(t, 1, s, SHAKE256_RATE);
    for (i = 0; i < outlen%SHAKE256_RATE; i++)
      output[i] = t[i];
  }
#ifdef PROFILE_HASHING
  uint64_t t1 = hal_get_time();
  hash_cycles += (t1-t0);
#endif
}
