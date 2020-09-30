#include "xmc1100.h"

extern int main(void);
void init(void);
void clock_init(void);
void default_handler(void);
extern void SysTick_Handler(void);//
// The following are 'declared' in the linker script
extern unsigned char  INIT_DATA_VALUES;
extern unsigned char  INIT_DATA_START;
extern unsigned char  INIT_DATA_END;
extern unsigned char  BSS_START;
extern unsigned char  BSS_END;
// The XMC1100 remaps interrupt vectors to RAM.  The boot loader
// looks for the program entry address at 0x10001004 and the
// initial stack pointer as 0x10001000.  These are defined in
// the "vectors" section below.  The section "vectors" is 
// placed at the beginning of flash by the linker script
// Another useful feature of this chip is that you can 
// pre-program startup considtions such as CPU speed and 
// which periperals.  This is done by writing values in to
// CLK_VAL1 and CLK_VAL2 below

const void * FlashVectors[] __attribute__((section(".vectors"))) ={
	(void *)0x20004000, 	/* Top of stack  @0x10001000 */ 
	init, 		 	  	    /* Reset Handler @0x10001004 */
	(void *)0,				/* @0x10001008 */
	(void *)0,				/* @0x1000100c */
	(void *)0xffffffff,		/* CLK_VAL1   @0x10001010 */
	(void *)0xffffffff		/* CLK_VAL2   @0x10001014 */
};
// The remaining interrupt vectors are relocated to RAM where a jump
// table should be placed to the actual interrupt handlers.  The jump 
// table takes the following form:
//	ldr R0,=handler_address
//  mov PC,R0
// This pair of instructions fits into 4 bytes which
// fits neatly into a jump table entry.

void JumpTable(void) __attribute__(( section(".remapped_vectors")));
void __attribute__((optimize("O0"))) JumpTable(void) 
{
	asm(" .long 0 "); // -15 reserved
	asm(" .long 0 "); // -14 reserved
	asm(" .long 0 "); // -13 HardFault
	asm(" .long 0 "); // -12 reserved
	asm(" .long 0 "); // -11 reserved
	asm(" .long 0 "); // -10 reserved
	asm(" .long 0 "); // -9 reserved
	asm(" .long 0 "); // -8 reserved
	asm(" .long 0 "); // -7 reserved
	asm(" .long 0 "); // -6 reserved
	asm(" .long 0 "); // -5 SVCall
	asm(" .long 0 "); // -4 reserved 
	asm(" .long 0 "); // -3 reserved 
	asm(" .long 0 "); // -2 PendSV
	//asm(" .long 0 "); // -1 Systick handler
	asm(" ldr R0,=SysTick_Handler "); // -1 Systick handler
	asm(" mov PC,R0 ");
	
	asm(" .long 0 "); // IRQ 0
	asm(" .long 0 "); // IRQ 1
	asm(" .long 0 "); // IRQ 2
	asm(" .long 0 "); // IRQ 3
	asm(" .long 0 "); // IRQ 4
	asm(" .long 0 "); // IRQ 5
	asm(" .long 0 "); // IRQ 6
	asm(" .long 0 "); // IRQ 7
	asm(" .long 0 "); // IRQ 8
	asm(" .long 0 "); // IRQ 9
	asm(" .long 0 "); // IRQ 10
	asm(" .long 0 "); // IRQ 11
	asm(" .long 0 "); // IRQ 12
	asm(" .long 0 "); // IRQ 13
	asm(" .long 0 "); // IRQ 14
	asm(" .long 0 "); // IRQ 15
	asm(" .long 0 "); // IRQ 16
	asm(" .long 0 "); // IRQ 17
	asm(" .long 0 "); // IRQ 18
	asm(" .long 0 "); // IRQ 19
	asm(" .long 0 "); // IRQ 20
	asm(" .long 0 "); // IRQ 21
	asm(" .long 0 "); // IRQ 22
	asm(" .long 0 "); // IRQ 23
	asm(" .long 0 "); // IRQ 24
	asm(" .long 0 "); // IRQ 25
	asm(" .long 0 "); // IRQ 26
	asm(" .long 0 "); // IRQ 27
	asm(" .long 0 "); // IRQ 28
	asm(" .long 0 "); // IRQ 29
	asm(" .long 0 "); // IRQ 30
	asm(" .long 0 "); // IRQ 31
	
};
void init()
{
// do global/static data initialization
// This is will also copy the jump table for remapped IRQ vectors
// to RAM.
	unsigned char *src;
	unsigned char *dest;
	unsigned len;
	src= &INIT_DATA_VALUES;
	dest= &INIT_DATA_START;
	len= &INIT_DATA_END-&INIT_DATA_START;
	while (len--)
		*dest++ = *src++;
// zero out the uninitialized global/static variables
	dest = &BSS_START;
	len = &BSS_END - &BSS_START;
	while (len--)
		*dest++=0;

	clock_init();
	main();
}

void clock_init()
{
	/* Setup system frequency */
	SCU_PASSWD = 0x000000C0UL; // disable bit protection
	SCU_CLKCR = 0x3FF00400UL; // MCLK = 8MHz, PCLK = 8MHz
	while((SCU_CLKCR & BIT30));
	SCU_PASSWD = 0x000000C3UL; // enable bit protection
}

void default_handler()
{
	while(1);
}
