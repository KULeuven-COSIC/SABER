# In order to use this makefile you must have an arm compiler on your
# system. You can get one here: https://launchpad.net/gcc-arm-embedded
# Your PATH environment variable should include the 'bin' folder in
# the arm compiler directory tree.
# One final thing.  You must edit the LIBSPEC variable below to make
# it point at your arm compiler.
# A particular version of the compiler is mentioned in the LIBSPEC 
# line below.  Find out what the equivalent is for your system and change
# it accordingly.
# Tell the linker where to find the libraries -> important: use thumb versions
#LIBSPEC=-L /usr/lib/arm-none-eabi/newlib/armv6-m
LIBSPEC=-L /usr/arm-none-eabi/lib/armv6-m

IDIR =./include
SDIR =./src
ODIR=obj

# Specify the compiler to use
CC=arm-none-eabi-gcc
# Specify the assembler to use
AS=arm-none-eabi-as
# Size program to use
SIZE:= arm-none-eabi-size
# Specity the linker to use
#LD=arm-none-eabi-ld
LDLIBS= -lgcc
# Specify architecture
CCFLAGS= -mthumb -mcpu=cortex-m0
CCFLAGS += -O3
CCFLAGS+= -g -Wall -Wextra -Wno-unused-parameter
CCFLAGS+= -Wimplicit-function-declaration -Wredundant-decls
CCFLAGS+= -Wmissing-prototypes -Wstrict-prototypes -Wundef -Wshadow -I$(IDIR)

# Disassembler
OBJDUMP = arm-none-eabi-objdump
OBJDUMP_FLAGS += --disassemble --source --disassembler-options=force-thumb

# Linker script
LDSCRIPT := linker_script.ld

# Flasher
JLINKEXE = ~/Documents/JLink_Linux_V510q_x86_64/JLinkExe
#JLINKOPT = -SelectEmuBySN 000591033379
#JLINKOPT += -device xmc1100-64 -if SWD -speed 400
JLINKOPT = -device xmc1100-64 -if SWD -speed 400
########################
define SEGGER_FLASH_SOFTDEVICE_CMD
r
loadbin main.bin 0x10001000
r
g
exit
endef

########################
export SEGGER_FLASH_SOFTDEVICE_CMD

# Specify program name, output directory and sources
SABER_SRC := cbd.c kem.c pack_unpack.c poly.c poly_mul.c encode.c SABER_indcpa.c verify.c \
			 fips202.c asm_KeccakF-1600.S
#keccakf1600.S
SABER_OBJS := cbd.o kem.o pack_unpack.o poly.o poly_mul.o encode.o SABER_indcpa.o verify.o \
			  fips202.o asm_KeccakF-1600.o
#keccakf1600.o
PROG   := main
SRC    := $(SDIR)/init.c \
		  $(SDIR)/prng.c \
		  $(SDIR)/uart.c \
		  $(SDIR)/benchmark.c \
  		  $(SDIR)/main.c

OBJS   := $(patsubst $(SDIR)/%.c, $(SDIR)/$(ODIR)/%.o, $(SRC))
OBJS += $(patsubst %.o, $(SDIR)/$(ODIR)/%.o, $(SABER_OBJS))

# Generate disassebly list file
$(PROG).lst: $(PROG).elf
	$(OBJDUMP) $(OBJDUMP_FLAGS) $< > $@

# The default 'target' (output) is main.elf and it depends on the object files being there.
# These object files are linked together to create main.elf
$(PROG).elf : $(OBJS)
	$(CC) $(CCFLAGS) -o $(PROG).elf $(OBJS) $(LIBSPEC) -Wl,-T,$(LDSCRIPT) -Wl,-Map=$(PROG).map -nostartfiles $(LDLIBS)
	arm-none-eabi-objcopy -O binary $(PROG).elf $(PROG).bin
	objcopy -O ihex $(PROG).elf $(PROG).hex
	@echo "done!"
	@echo "--------------------------------------------------"
	$(SIZE) $@
	@echo "--------------------------------------------------"

# Compile C source code and generate object files
$(SDIR)/$(ODIR)/%.o: $(SDIR)/%.c
	@ mkdir -p $(SDIR)/$(ODIR)
	$(CC) -c $(CCFLAGS) $< -o $@

# Compile assembly source code and generate object files
$(SDIR)/$(ODIR)/%.o: $(SDIR)/%.S
	@ mkdir -p $(SDIR)/$(ODIR)
	$(CC) -c $(CCFLAGS) $< -o $@

flash: $(PROG).elf
	@echo "$$SEGGER_FLASH_SOFTDEVICE_CMD" | $(JLINKEXE) $(JLINKOPT)

.PHONY: clean

clean:
	rm -f $(SDIR)/*~ $(IDIR)/*~ $(SDIR)/$(ODIR)/*.o
	rm -f *.elf *.map *.bin *.hex *.lst
