# SABER Variants
SABER is a Mod-LWR based KEM submitted to NIST Post-Quantum Cryptography Process

## Compilation instructions

* Select the desired security level and combination between uniform-Saber and Saber-90s by commenting/uncommenting the appropriate `#define` macros in the first lines of `SABER_params.h`
* Use `make clean` to clean executable files
* Use `make all` to compile the source codes 
* Use `./test/test_kex` to run KEM operations in loop for `repeat` number of iterations
* Use `./test/PQCgenKAT_kem` to generate KAT files

