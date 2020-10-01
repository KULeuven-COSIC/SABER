# SABER Variants
SABER is a Mod-LWR based KEM submitted to NIST Post-Quantum Cryptography Process

## Folder structure

* `SaberX4_avx2` : AVX2 optimized implementation of SaberX4 
* `uSaber-90s/ref` : Reference implementation of any combination of {uniform}-{Fire, Light}Saber-{90s}. 
* `uSaber-90s/avx2` : AVX2 optimized implementation of any combination of {Fire, Light}Saber-{90s}. AVX2 optimized implementations of uSaber are not available yet.

## Compilation instructions

* Select the desired security level and combination between uniform-Saber and Saber-90s by commenting/uncommenting the appropriate `#define` macros in the first lines of `SABER_params.h`
* Use `make clean` to clean executable files
* Use `make all` to compile the source codes 
* Use `./test/test_kex` to run KEM operations in loop for `repeat` number of iterations
* Use `./test/PQCgenKAT_kem` to generate KAT files

