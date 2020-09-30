
#include "benchmark.h"

#include "xmc1100.h"

static uint32_t calibration_value = 0;
static uint32_t timer_overflow = 0;

void SysTick_Handler()
{
	timer_overflow++;
	SYST_CVR = 0x00FFFFFF;
}

void
setup_tick_count (void)
{
	calibration_value = 0;
	SYST_RVR = 0x00FFFFFF;
	SYST_CVR = 0x00FFFFFF;
	SYST_CSR &= ~(BIT0+BIT1+BIT2+BIT16);
	SYST_CSR |= (BIT1+BIT2);
	//enable_interrupts();
	start_tick_count();
	calibration_value = end_tick_count();
	//disable_interrupts();
}

void
__attribute__ ((noinline))
start_tick_count (void)
{
	disable_interrupts();
	timer_overflow = 0;
	SYST_CVR = 0x00FFFFFF;
	enable_interrupts();
	SYST_CSR ^= BIT0;
}

uint32_t
__attribute__ ((noinline))
end_tick_count (void)
{
	uint32_t ticks;
	SYST_CSR ^= BIT0;
	disable_interrupts();
	ticks = 0x00FFFFFF - SYST_CVR;
	while (timer_overflow--) {
		ticks += 0x00FFFFFF;
	}
	//enable_interrupts();
	return ticks - calibration_value;
}
