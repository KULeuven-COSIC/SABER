CC 		  = /usr/bin/gcc
CFLAGS  = -Wall -Wextra -O3 -fomit-frame-pointer -msse2avx -mavx2 -march=native -lcrypto
CFLAGS2  = -Wno-unused-results -O3 -fomit-frame-pointer -msse2avx -mavx2 -march=native -std=c11 
CFLAGS3  = -Wall -Wextra -O3 -fomit-frame-pointer -msse2avx -mavx2 -march=native
CLANG   = clang -march=native -O3 -fomit-frame-pointer -lcrypto -fwrapv -Qunused-arguments -w
RM 		  = /bin/rm


all: test/PQCgenKAT_kem \
     test/test_kex \
     test/test_sample_matrix

SOURCES = pack_unpack.c verify.c fips202.o SABER_indcpa.c kem.c cbd.c rng.o
					

SOURCES2 = pack_unpack.c rng.o verify.c fips202.o SABER_indcpa.c kem.c cbd.c 
					

HEADERS = SABER_params.h pack_unpack.h verify.h cbd.h SABER_indcpa.h kem.h rng.h fips202.h api.h


test/test_kex: $(SOURCES) $(HEADERS) test/test_kex.c 
	$(CC) $(CFLAGS3) -o $@ $(SOURCES) test/test_kex.c -lcrypto

test/test_sample_matrix: $(SOURCES) $(HEADERS) test/sample_matrix_test.c 
	$(CC) $(CFLAGS3) -o $@ $(SOURCES) test/sample_matrix_test.c -lcrypto

test/PQCgenKAT_kem: $(SOURCES2) $(HEADERS) test/PQCgenKAT_kem.c 
	$(CC) $(CFLAGS3) -o $@ $(SOURCES2) test/PQCgenKAT_kem.c -lcrypto  

rng.o: rng.c
	$(CC) $(CFLAGS2) -c rng.c -lcrypto -o $@ 

# fips202.o: fips202.c
# 	$(CLANG) -c $^ -o $@

.PHONY: clean test

test:
	./test/test_kex
	./test/PQCgenKAT_kem


clean:
	-$(RM) -f *.o
	-$(RM) -rf test/test_sample_matrix
	-$(RM) -rf test/test_kex
	-$(RM) -rf test/PQCgenKAT_kem


