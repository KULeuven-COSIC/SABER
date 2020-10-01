/*---------------------------------------------------------------------
This file has been adapted from the implementation 
(available at, Public Domain https://github.com/pq-crystals/kyber) 
of "CRYSTALS – Kyber: a CCA-secure module-lattice-based KEM"
by : Joppe Bos, Leo Ducas, Eike Kiltz, Tancrede Lepoint, 
Vadim Lyubashevsky, John M. Schanck, Peter Schwabe & Damien stehle
----------------------------------------------------------------------*/

#include <stdio.h>
#include "apiorig.h"
#include "poly.h"
#include "cbd.h"
#include "fips202.h"
#include "fips202x4.h"

void poly_getnoise(uint16_t *r,const unsigned char *seed, unsigned char nonce)
{
  unsigned char buf[SABER_N];

  cshake128_simple(buf,SABER_N,nonce,seed,SABER_NOISESEEDBYTES);

  cbd( r, buf);
}

/*
void poly_getnoise4x(uint16_t *r0, uint16_t *r1, uint16_t *r2, const unsigned char *seed, unsigned char nonce0, unsigned char nonce1, unsigned char nonce2, unsigned char nonce3)
{
  uint16_t nblocks=2;
  unsigned char buf0[SHAKE128_RATE*nblocks];
  unsigned char buf1[SHAKE128_RATE*nblocks];
  unsigned char buf2[SHAKE128_RATE*nblocks];
  unsigned char buf3[SHAKE128_RATE*nblocks];

  cshake128_simple4x(buf0,buf1,buf2,buf3,SHAKE128_RATE*nblocks,nonce0,nonce1,nonce2,nonce3,seed,SABER_NOISESEEDBYTES);

  	
  cbd( r0, buf0);
  cbd( r1, buf1);
  cbd( r2, buf2);
}


*/
