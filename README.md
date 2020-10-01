# SABER

SABER is a Mod-LWR based KEM finalist in the NIST Post-Quantum Cryptography Standardization Process.

## Folder structure

* `AVX_Implementation_KEM` : AVX2 optimized implementations of LightSaber, Saber, and FireSaber.
* `Cortex-M_Implementation_KEM` : Cortex-M optimized implementations of LightSaber, Saber, and FireSaber. Includes subdirectories `Cortex-M0` and `Cortex-M4`.
* `KAT` : Known Answer Tests for all possible conbinations of {uniform}-{Fire, Light}Saber-{90s}.
  * `PQCkemKAT*.req` : input for Known Answer Test
  * `PQCkemKAT*.rsp` : output for Known Answer Test
* `Reference_Implementation_KEM` : Reference implementations of LightSaber, Saber, and FireSaber.
* `Variants` : Implementations of Saber variants: uSaber, Saber-90s, and SaberX4

## Compilation instructions

* Select the desired algorithm in `SABER_params.h`. This can be done by commenting/uncommenting the appropriate line with `#define` in the code.   
* Use `make clean` to clean executable files
* Use `make all` to compile the source codes 
* Use `./test/test_kex` to run KEM operations in loop for `repeat` number of iterations
* Use `./test/PQCgenKAT_kem` to generate KAT files



