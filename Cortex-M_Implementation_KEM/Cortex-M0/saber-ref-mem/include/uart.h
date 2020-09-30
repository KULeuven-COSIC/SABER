
#ifndef UART_H
#define UART_H

#include <stdint.h>

// UART baud rate constants for 115.2kbps @ MCLK=8MHz
#define FDR_STEP 590UL
#define BRG_PDIV 3UL
#define BRG_DCTQ 9UL
#define BRG_PCTQ 0UL


void UART_Init (void);
void UART_Write (char * str, uint8_t len);
uint8_t UART_Read (char * str);
void UART_SendAddr (uint32_t ui);
void UART_SendTrace (char * str, uint8_t len, uint32_t ui);
void UART_SendWord (uint16_t w);

#endif /* UART_H */
