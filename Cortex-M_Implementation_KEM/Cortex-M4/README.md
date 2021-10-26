
This repository contains the ARM Cortex-M4 code for SABER.

## Setup

After cloning or downloading the repository, it is necessary to add the libraries to work with the microcontroller. In order to make it more straightforward for testing, as well as to keep the legacy version, we have added these required sources to the folder libopencm3. More information about this library can be found in https://github.com/libopencm3/libopencm3.

#### Requirements

- The cross compiler for ARM Cortex-M series is required in order to build the executable. The toolchain can be found in https://launchpad.net/gcc-arm-embedded.

- The stlink software tool is required in order to flash the executables into the board. The source code for this tool as well as installation instructions can be found in https://github.com/texane/stlink/blob/master/doc/compiling.md.

- `python3` as well as the module `pyserial` must be installed for the automation of the whole benchmark/testing process.

- The [STM32F4 Discovery board](https://www.st.com/en/evaluation-tools/stm32f4discovery.html) must be connected to the computer for UART communication via an USB-TTL converter. Such converter must wire the `TX`/`TXD` pin of the USB connector to the `PA3` pin on the board, and the `RX`/`RXD` pin of the USB connector to the `PA2` pin on the board. The ground (`GND`) pins can be connected anywhere available.

## Sources

* `m4-tc4kara`: This code implements a polynomial multiplication based on Toom-Cook 4-way and Karatsuba achieving high-speed while keeping the memory utilization rather low for Saber on embedded devices.

* `m4-striding`: This code implements a polynomial multiplication based on the striding version of Toom-Cook 4-way and Karatsuba to achieve a significant memory reduction with respect to the classical version of such algorithms, while not suffering a penalization on performance / marginally improving performance numbers.

* `tba`:

## Benchmark

For a quick build and outputting the results in md format, the reader can go to benchmark folder and execute the following commands:

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
| saber (1 executions) | m4-tc4kara | AVG: 851,958 <br /> MIN: 851,958 <br /> MAX: 851,958 | AVG: 1,106,900 <br /> MIN: 1,106,900 <br /> MAX: 1,106,900 | AVG: 1,124,292 <br /> MIN: 1,124,292 <br /> MAX: 1,124,292 |

| Scheme | Implementation | Key Generation [bytes] | Encapsulation [bytes] | Decapsulation [bytes] |
| ------ | -------------- | ---------------------- | --------------------- | --------------------- |
| saber | m4-tc4kara | 7,256 | 6,328 | 6,336 |
