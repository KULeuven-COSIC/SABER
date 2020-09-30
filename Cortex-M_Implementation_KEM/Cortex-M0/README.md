
Reference implementation of the CCA-secure module lattice-based key encapsulation Saber suitable for ARM Cortex-M0 processors.

## Setup

Configuration and main files are provided to demonstrate the cryptosystem on a XMC2Go Infineon board. It is enough to connect that board to the computer via USB and run the script `evaluate.py` in the corresponding directory to get all timing and memory results of that scheme.

#### Requirements

- The cross compiler for ARM Cortex-M series is required in order to build the executable. The toolchain can be found in https://launchpad.net/gcc-arm-embedded and the path to the libraries for the linker should be `/usr/arm-none-eabi/lib/armv6-m`. If you choose a custom location for your installation, the path to the libraries should be updated accordingly in the Makefiles.

- The JLink debugging software tool is required in order to flash the executable into the board. The package can be found in https://www.segger.com/downloads/jlink/ and it is necessary to update the path in the line 42 of the Makefiles to match your installation.

