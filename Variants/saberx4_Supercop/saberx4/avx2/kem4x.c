#include "randombytes.h"
#include "fips202x4.h"
#include "verify.h"
#include "SABER_indcpa.h"

int crypto_kem_keypair4x(
						unsigned char *pk0, unsigned char *sk0,
						unsigned char *pk1, unsigned char *sk1,
						unsigned char *pk2, unsigned char *sk2,
						unsigned char *pk3, unsigned char *sk3)
{
  int i;
 
  unsigned char seed_arr[4][SABER_SEEDBYTES];
  unsigned char noiseseed_arr[4][SABER_COINBYTES];
  unsigned char pseudorandom_key_arr[4][SABER_KEYBYTES];

  // Generate randomness in proper sequesce for the four key-pair generation operations
	for(i=0; i<4; i++)
	{
		randombytes(seed_arr[i], SABER_SEEDBYTES);
		randombytes(noiseseed_arr[i], SABER_COINBYTES);
		randombytes(pseudorandom_key_arr[i], SABER_KEYBYTES);
	}	

  indcpa_kem_keypair(pk0,sk0, pk1,sk1, pk2,sk2, pk3,sk3, seed_arr, noiseseed_arr);  // sk[0:SABER_INDCPA_SECRETKEYBYTES-1] <-- sk

  for(i=0;i<SABER_INDCPA_PUBLICKEYBYTES;i++)
	{
		// sk[SABER_INDCPA_SECRETKEYBYTES:SABER_INDCPA_SECRETKEYBYTES+SABER_INDCPA_SECRETKEYBYTES-1] <-- pk	
    sk0[i+SABER_INDCPA_SECRETKEYBYTES] = pk0[i]; 
    sk1[i+SABER_INDCPA_SECRETKEYBYTES] = pk1[i]; 
    sk2[i+SABER_INDCPA_SECRETKEYBYTES] = pk2[i]; 
    sk3[i+SABER_INDCPA_SECRETKEYBYTES] = pk3[i]; 
	}

  //sha3_256(sk+SABER_SECRETKEYBYTES-64, pk, SABER_INDCPA_PUBLICKEYBYTES);  // Then hash(pk) is appended.	
  sha3_256x4(sk0+SABER_SECRETKEYBYTES-64, sk1+SABER_SECRETKEYBYTES-64, 
						sk2+SABER_SECRETKEYBYTES-64, sk3+SABER_SECRETKEYBYTES-64,
						pk0, pk1, pk2, pk3,SABER_INDCPA_PUBLICKEYBYTES);  


	for(i=0; i<SABER_KEYBYTES; i++)
	{
		sk0[i+SABER_SECRETKEYBYTES-SABER_KEYBYTES] = pseudorandom_key_arr[0][i];
		sk1[i+SABER_SECRETKEYBYTES-SABER_KEYBYTES] = pseudorandom_key_arr[1][i];
		sk2[i+SABER_SECRETKEYBYTES-SABER_KEYBYTES] = pseudorandom_key_arr[2][i];
		sk3[i+SABER_SECRETKEYBYTES-SABER_KEYBYTES] = pseudorandom_key_arr[3][i];
	}


  return(0);	
}

int crypto_kem_enc4x(
					unsigned char *c0, unsigned char *k0, const unsigned char *pk0,
					unsigned char *c1, unsigned char *k1, const unsigned char *pk1,
					unsigned char *c2, unsigned char *k2, const unsigned char *pk2,
					unsigned char *c3, unsigned char *k3, const unsigned char *pk3)
{
  unsigned char kr0[64], kr1[64], kr2[64], kr3[64];          	  // Will contain key, coins
  unsigned char buf0[64], buf1[64], buf2[64], buf3[64];                          
  int i;
	
	randombytes(buf0, 32); 
	randombytes(buf1, 32); 
	randombytes(buf2, 32);
	randombytes(buf3, 32);

	//sha3_256(buf,buf,32);            			  // BUF[0:31] <-- random message (will be used as the key for client) 
	sha3_256x4(buf0,buf1,buf2,buf3, buf0,buf1,buf2,buf3, 32);

  //sha3_256(buf+32, pk, SABER_INDCPA_PUBLICKEYBYTES);    // BUF[32:63] <-- Hash(public key);  
	sha3_256x4(buf0+32,buf1+32,buf2+32,buf3+32,  pk0,pk1,pk2,pk3, SABER_INDCPA_PUBLICKEYBYTES);

  //sha3_512(kr, buf, 64);				// kr[0:63] <-- Hash(buf[0:63]);  	
							  								// K^ <-- kr[0:31]
							  								// noiseseed (r) <-- kr[32:63];	

	sha3_512x4(kr0,kr1,kr2,kr3, buf0,buf1,buf2,buf3, 64);

  //indcpa_kem_enc(buf, kr+32, pk,  c);	// buf[0:31] contains message; kr[32:63] contains randomness r;  		
	indcpa_kem_enc(buf0, buf1, buf2, buf3, 
								kr0+32, kr1+32, kr2+32, kr3+32, 
								pk0,c0, pk1,c1, pk2,c2, pk3,c3);


  //sha3_256(kr+32,c, SABER_BYTES_CCA_DEC); 
  sha3_256x4(kr0+32,kr1+32,kr2+32,kr3+32, c0,c1,c2,c3, SABER_BYTES_CCA_DEC);              


  //sha3_256(k, kr, 64);                          					// hash concatenation of pre-k and h(c) to k 
	sha3_256x4(k0,k1,k2,k3, kr0,kr1,kr2,kr3, 64);

  return(0);	
}


int crypto_kem_dec4x(
					unsigned char *k0, const unsigned char *c0, const unsigned char *sk0,
					unsigned char *k1, const unsigned char *c1, const unsigned char *sk1,
					unsigned char *k2, const unsigned char *c2, const unsigned char *sk2,
					unsigned char *k3, const unsigned char *c3, const unsigned char *sk3)
{
  	int i, fail0, fail1, fail2, fail3;
	unsigned char cmp0[SABER_BYTES_CCA_DEC], cmp1[SABER_BYTES_CCA_DEC];
	unsigned char cmp2[SABER_BYTES_CCA_DEC], cmp3[SABER_BYTES_CCA_DEC];
  	unsigned char buf0[64], buf1[64], buf2[64], buf3[64];
  	unsigned char kr0[64], kr1[64], kr2[64], kr3[64];                             // Will contain key, coins

  	//const unsigned char *pk = sk + SABER_INDCPA_SECRETKEYBYTES;
  	const unsigned char *pk0 = sk0 + SABER_INDCPA_SECRETKEYBYTES;
  	const unsigned char *pk1 = sk1 + SABER_INDCPA_SECRETKEYBYTES;
  	const unsigned char *pk2 = sk2 + SABER_INDCPA_SECRETKEYBYTES;
  	const unsigned char *pk3 = sk3 + SABER_INDCPA_SECRETKEYBYTES;

   //indcpa_kem_dec(sk, c, buf);			     // buf[0:31] <-- message
   indcpa_kem_dec(
									sk0, c0, buf0,
									sk1, c1, buf1,
									sk2, c2, buf2,
									sk3, c3, buf3);
	 
  // Multitarget countermeasure for coins + contributory KEM 
  for(i=0;i<32;i++)                                  // Save hash by storing h(pk) in sk 
	{
    //buf[32+i] = sk[SABER_SECRETKEYBYTES-64+i]; 
    buf0[32+i] = sk0[SABER_SECRETKEYBYTES-64+i]; 
    buf1[32+i] = sk1[SABER_SECRETKEYBYTES-64+i]; 
    buf2[32+i] = sk2[SABER_SECRETKEYBYTES-64+i]; 
    buf3[32+i] = sk3[SABER_SECRETKEYBYTES-64+i]; 
	}

  //sha3_512(kr, buf, 64);

	sha3_512x4(kr0,kr1,kr2,kr3, buf0,buf1,buf2,buf3, 64);

  //indcpa_kem_enc(buf, kr+32, pk, cmp);
	indcpa_kem_enc(buf0, buf1, buf2, buf3, 
								 kr0+32, kr1+32, kr2+32, kr3+32,
								 pk0,cmp0, pk1,cmp1, pk2,cmp2, pk3,cmp3);

  //fail = verify(c, cmp, SABER_BYTES_CCA_DEC);
  fail0 = verify(c0, cmp0, SABER_BYTES_CCA_DEC);
  fail1 = verify(c1, cmp1, SABER_BYTES_CCA_DEC);
  fail2 = verify(c2, cmp2, SABER_BYTES_CCA_DEC);
  fail3 = verify(c3, cmp3, SABER_BYTES_CCA_DEC);

  //sha3_256(kr+32, c, SABER_BYTES_CCA_DEC);        		      
	sha3_256x4(kr0+32,kr1+32,kr2+32,kr3+32, c0,c1,c2,c3, SABER_BYTES_CCA_DEC);

  //cmov(kr, sk+SABER_SECRETKEYBYTES-SABER_KEYBYTES, SABER_KEYBYTES, fail); 
  cmov(kr0, sk0+SABER_SECRETKEYBYTES-SABER_KEYBYTES, SABER_KEYBYTES, fail0); 
  cmov(kr1, sk1+SABER_SECRETKEYBYTES-SABER_KEYBYTES, SABER_KEYBYTES, fail1); 
  cmov(kr2, sk2+SABER_SECRETKEYBYTES-SABER_KEYBYTES, SABER_KEYBYTES, fail2); 
  cmov(kr3, sk3+SABER_SECRETKEYBYTES-SABER_KEYBYTES, SABER_KEYBYTES, fail3); 

  //sha3_256(k, kr, 64);                          	   	     
  sha3_256x4(k0,k1,k2,k3, kr0,kr1,kr2,kr3, 64);

  return(0);	
}
