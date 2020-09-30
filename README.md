# SABER

SABER is a Mod-LWR based KEM finalist in the NIST Post-Quantum Cryptography Standardization Process.

## Folder structure

* `AVX_Implementation_KEM` : AVX2 optimized implementations of LightSaber, Saber, and FireSaber.
* `Cortex-M_Implementation_KEM` : Cortex-M optimized implementations of LightSaber, Saber, and FireSaber. Includes subdirectories `Cortex-M0` and `Cortex-M4`.
* `KAT` : Known Answer Tests for all possible conbinations of {uniform}-{Fire, Light}Saber-{90s}.
  * `PQCkemKAT*.req` : input for Known Answer Test
  * `PQCkemKAT*.rsp` : output for Known Answer Test
* `Reference_Implementation_KEM` : Reference implementations of LightSaber, Saber, and FireSaber.
* `Variants_Reference_Implementation_KEM` : Reference implementations of Saber variants. Includes macros to enable all possible conbinations of {uniform}-{Fire,Light}Saber-{90s}.


