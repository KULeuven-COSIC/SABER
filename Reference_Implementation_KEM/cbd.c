/*---------------------------------------------------------------------
This file has been adapted from the implementation 
(available at, Public Domain https://github.com/pq-crystals/kyber) 
of "CRYSTALS – Kyber: a CCA-secure module-lattice-based KEM"
by : Joppe Bos, Leo Ducas, Eike Kiltz, Tancrede Lepoint, 
Vadim Lyubashevsky, John M. Schanck, Peter Schwabe & Damien stehle
----------------------------------------------------------------------*/

#include "SABER_params.h"
#include "api.h"
#include "cbd.h"
#include <stdint.h>

static uint64_t load_littleendian(const uint8_t *x, int bytes)
{
  int i;
  uint64_t r = x[0];
  for (i = 1; i < bytes; i++)
    r |= (uint64_t)x[i] << (8 * i);
  return r;
}

void cbd(uint16_t s[SABER_N], const uint8_t buf[SABER_POLYCOINBYTES])
{
#if SABER_MU == 6 || SABER_MU == 8
  uint32_t t, d, a[4], b[4], ab_mask, ab_shift, d_mask;
#elif SABER_MU == 10
  uint64_t t, d, a[4], b[4], ab_mask, ab_shift, d_mask;
#else
#error "Unsupported SABER parameter."
#endif

  int i, j, mu_div_2;

  mu_div_2 = SABER_MU / 2;

  d_mask = 1;
  for (i = 0; i < 7; i++)
    d_mask = (d_mask << mu_div_2) + 1;

  ab_mask = (1 << mu_div_2) - 1;

  for (i = 0; i < SABER_N / 4; i++)
  {
    t = load_littleendian(buf + mu_div_2 * i, mu_div_2);
    d = 0;
    for (j = 0; j < mu_div_2; j++)
      d += (t >> j) & d_mask;

    ab_shift = 0;
    for (j = 0; j < 4; j++) {
      a[j] = (d >> ab_shift) & ab_mask;
      ab_shift += mu_div_2;
 
      b[j] = (d >> ab_shift) & ab_mask;
      ab_shift += mu_div_2;
 
      s[4 * i + j] = (uint16_t) (a[j] - b[j]); 
    }
  }
}