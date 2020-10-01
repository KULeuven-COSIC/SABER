/*---------------------------------------------------------------------
This file has been adapted from the implementation 
(available at, Public Domain https://github.com/pq-crystals/kyber) 
of "CRYSTALS – Kyber: a CCA-secure module-lattice-based KEM"
by : Joppe Bos, Leo Ducas, Eike Kiltz, Tancrede Lepoint, 
Vadim Lyubashevsky, John M. Schanck, Peter Schwabe & Damien stehle
----------------------------------------------------------------------*/

#ifndef POLY_H
#define POLY_H

#include <stdint.h>
#include "SABER_params.h"

uint64_t clock_mul, clock_matrix, clock_secret, count_mul;

uint64_t clock_mv_vv_mul;

uint64_t count_enc;

typedef struct
{
  uint16_t coeffs[SABER_N];
} poly;

typedef struct{
  poly vec[SABER_K];
} polyvec;


#endif
