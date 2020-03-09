#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <stdint.h>

void SysTick_Handler(void);

/* calibration of tick_count */
void setup_tick_count (void);

void start_tick_count (void);

/* return number of ticks since last start_tick_count() */
uint32_t end_tick_count (void);

#endif /* BENCHMARK_H */