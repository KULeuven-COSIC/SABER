
# ARM Cortex-M4

This repository contains ARM Cortex-M4 code for SABER.

## Requirements

The code in this repository includes the [pqm4](https://github.com/mupq/pqm4) framework for testing and benchmarking on the [STM32F4 Discovery board](https://www.st.com/en/evaluation-tools/stm32f4discovery.html). We refer to the documentation of [pqm4](https://github.com/mupq/pqm4) for the required prerequisites.

## Setup

After cloning or downloading this repository, it is necessary to initialize pqm4:

```bash
git submodule update --init --recursive
```

## Sources

[pqm4](https://github.com/mupq/pqm4) contains optimized implementations of Saber. In addition to the implementations present there, we also include:

* [m4-tc4kara](./src/saber/m4-tc4kara): This code implements a polynomial multiplication based on Toom-Cook 4-way and Karatsuba achieving high-speed while keeping the memory utilization rather low for Saber on embedded devices.

* [m4-striding](./src/saber/m4-striding): This code implements a polynomial multiplication based on the striding version of Toom-Cook 4-way and Karatsuba to achieve a significant memory reduction with respect to the classical version of such algorithms, while not suffering a penalization on performance / marginally improving performance numbers.

## Running Benchmarks and Tests

Before proceeding with the benchmarks and tests, the implementations in [m4-tc4kara](./src/saber/m4-tc4kara) and [m4-striding](./src/saber/m4-striding) should be added to [pqm4](https://github.com/mupq/pqm4):

```bash
ln -rs ./src/lightsaber/* ./pqm4/crypto_kem/lightsaber/
ln -rs ./src/saber/* ./pqm4/crypto_kem/saber/
ln -rs ./src/firesaber/* ./pqm4/crypto_kem/firesaber/
```

All Saber tests tests can be run using:

```bash
cd pqm4
[sudo] python3 test.py lightsaber saber firesaber
[sudo] python3 testvectors.py lightsaber saber firesaber
```

Similarly, all Saber benchmarks can be run using:

```bash
cd pqm4
[sudo] python3 benchmarks.py lightsaber saber firesaber
```

To output the results in md format:

```bash
python3 convert_benchmarks.py md > ../benchmarks.md
```

## Results

Benchmarks can be found in [benchmarks.md](./benchmarks.md).
