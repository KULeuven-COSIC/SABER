CC 		  = /usr/bin/gcc
CFLAGS  = -Wall -Wextra -O3 -fomit-frame-pointer -msse2avx -mavx2 -march=native -lcrypto
CFLAGS2  = -Wno-unused-results -O3 -fomit-frame-pointer -msse2avx -mavx2 -march=native -std=c11 
CFLAGS3  = -Wall -Wextra -O3 -fomit-frame-pointer -msse2avx -mavx2 -march=native
CLANG   = clang -march=native -O3 -fomit-frame-pointer -lcrypto -fwrapv -Qunused-arguments -w
RM 		  = /bin/rm


all: test/test_kex

SOURCES = pack_unpack.c verify.c fips202.c fips202x4.c SABER_indcpa.c kem.c cbd.c rng.o keccak4x/KeccakP-1600-times4-SIMD256.o

HEADERS = SABER_params.h pack_unpack.h poly.h verify.h cbd.h SABER_indcpa.h kem.h rng.h fips202.h fips202x4.h api.h 


test/test_kex: $(SOURCES) $(HEADERS) test/test_kex.c 
	$(CC) $(CFLAGS3) -o $@ $(SOURCES) test/test_kex.c -lcrypto


keccak4x/KeccakP-1600-times4-SIMD256.o: keccak4x/KeccakP-1600-times4-SIMD256.c \
					keccak4x/align.h \
					keccak4x/brg_endian.h \
					keccak4x/KeccakP-1600-times4-SIMD256.c \
					keccak4x/KeccakP-1600-times4-SnP.h \
					keccak4x/KeccakP-1600-unrolling.macros \
					keccak4x/SIMD256-config.h

	$(CC) $(CFLAGS) -c keccak4x/KeccakP-1600-times4-SIMD256.c -o $@

rng.o: rng.c
	$(CC) $(CFLAGS2) -c rng.c -lcrypto -o $@ 

# fips202.o: fips202.c
# 	$(CLANG) -c $^ -o $@

.PHONY: clean test

test:
	./test/test_kex


clean:
	-$(RM) -f *.o
	-$(RM) -rf test/test_kex
	-$(RM) -rf keccak4x/KeccakP-1600-times4-SIMD256.o


