
This repository contains the ARM Cortex-M4 code for SABER.

## Setup

After cloning or downloading the repository, it is necessary to add the libraries to work with the microcontroller. In order to make it more straightforward for testing, as well as to keep the legacy version, we have added these required sources to the folder libopencm3. More information about this library can be found in https://github.com/libopencm3/libopencm3.

#### Requirements

- The cross compiler for ARM Cortex-M series is required in order to build the executable. The toolchain can be found in https://launchpad.net/gcc-arm-embedded.

- The stlink software tool is required in order to flash the executables into the board. The source code for this tool as well as installation instructions can be found in https://github.com/texane/stlink/blob/master/doc/compiling.md.

- `python3` as well as the module `pyserial` must be installed for the automation of the whole benchmark/testing process.

- The [STM32F4 Discovery board](https://www.st.com/en/evaluation-tools/stm32f4discovery.html) must be connected to the computer for UART communication via an USB-TTL converter. Such converter must wire the `TX`/`TXD` pin of the USB connector to the `PA3` pin on the board, and the `RX`/`RXD` pin of the USB connector to the `PA2` pin on the board. The ground (`GND`) pins can be connected anywhere available.

## Sources

* `tradeoff`: This code implements the best trade-off for Saber on embedded devices achieving high-speed while keeping the memory utilization rather low.

* `tba`:

## Benchmark

Our code is compatible with the [pqm4](https://github.com/mupq/pqm4) library. The folders containing the sources can be copied directly to `pqm4/crypto_kem/saber/` for a full test, benchmark and comparison to other schemes.

Building up the `pqm4` library can be time consuming since it will compile all versions of all KEMs and digital signatures available. To avoid this and for a quick benchmark of only Saber code we have created a lightweight version of such framework in `benchmark`. All scripts are taken directly from `pqm4` library, which is under the conditions of [CC0](https://creativecommons.org/publicdomain/zero/1.0/).

For a quick build and outputting the results in md format, the reader can execute the following commands:

```
python3 build_everything.py
```
```
[sudo] python3 benchmarks.py
```
```
python3 convert_benchmarks.py md
```

## Results

| scheme | implementation | key generation [cycles] | encapsulation [cycles] | decapsulation [cycles] |
| ------ | -------------- | ----------------------- | ---------------------- | ---------------------- |
| saber (1 executions) | m4-tradeoff | AVG: 853,726 <br /> MIN: 853,726 <br /> MAX: 853,726 | AVG: 1,108,537 <br /> MIN: 1,108,537 <br /> MAX: 1,108,537 | AVG: 1,124,982 <br /> MIN: 1,124,982 <br /> MAX: 1,124,982 |

| Scheme | Implementation | Key Generation [bytes] | Encapsulation [bytes] | Decapsulation [bytes] |
| ------ | -------------- | ---------------------- | --------------------- | --------------------- |
| saber | m4-tradeoff | 7,248 | 6,312 | 6,320 |
