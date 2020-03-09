
#include "uart.h"
#include "xmc1100.h"

void
UART_Init (void)
{
	// Disable clock gating to USIC0
	SCU_PASSWD = 0x000000C0UL; // disable bit protection
	SCU_CGATCLR0 |= BIT3;
	SCU_PASSWD = 0x000000C3UL; // enable bit protection

	/* Enable the module kernel clock and the module functionality */
	USIC0_CH0_KSCFG |= BIT0 | BIT1;

	/* fFD = fPB */
	/* FDR.DM = 02b (Fractional divider mode) */
	USIC0_CH0_FDR &= ~(0x03UL << 14 | 0x000003ffUL << 0);// DM STEP
	USIC0_CH0_FDR |= (0x02UL << 14) | (FDR_STEP << 0);

	/* Configure baud rate generator */
	/* BAUDRATE = fCTQIN/(BRG.PCTQ x BRG.DCTQ) */
	/* CLKSEL = 0 (fPIN = fFD), CTQSEL = 00b (fCTQIN = fPDIV), PPPEN = 0 (fPPP=fPIN) */
	USIC0_CH0_BRG &= ~(0x03UL << 8 | 0x1fUL << 10 | 0x000003ffUL << 16 | 0x03UL << 0 | 0x01UL << 4);// PCTQ DCTQ PDIV CLKSEL PPPEN
	USIC0_CH0_BRG |= (BRG_PCTQ << 8) | (BRG_DCTQ << 10) | (BRG_PDIV << 16);

	/* Configuration of USIC Shift Control */
	/* SCTR.FLE = 8 (Frame Length) */
	/* SCTR.WLE = 8 (Word Length) */
	/* SCTR.TRM = 1 (Transmission Mode) */
	/* SCTR.PDL = 1 (This bit defines the output level at the shift data output signal when no data is available for transmission) */
	USIC0_CH0_SCTR &= ~(0x03UL << 8 | 0x3fUL << 16 | 0x0fUL << 24);
	USIC0_CH0_SCTR |= (0x01UL << 1) | (0x01UL << 8) | (0x07UL << 16) | (0x07UL << 24);// PDL TRM FLE WLE

	/* Configuration of USIC Transmit Control/Status Register */
	/* TBUF.TDEN = 1 (TBUF Data Enable: A transmission of the data word in TBUF can be started if TDV = 1 */
	/* TBUF.TDSSM = 1 (Data Single Shot Mode: allow word-by-word data transmission which avoid sending the same data several times*/
	USIC0_CH0_TCSR &= ~(0x03UL << 10);
	USIC0_CH0_TCSR |= (0x01UL << 8) | (0x01UL << 10);// TDSSM TDEN

	/* Configuration of Protocol Control Register */
	/* PCR.SMD = 1 (Sample Mode based on majority) */
	/* PCR.STPB = 0 (1x Stop bit) */
	/* PCR.SP = 5 (Sample Point) */
	/* PCR.PL = 0 (Pulse Length is equal to the bit length) */
	USIC0_CH0_PCR &= ~((0x01UL << 1) | (0x1fUL << 8) | (0x07UL << 13));// ASCMode: STPB SP PL
	USIC0_CH0_PCR |= (0x01UL << 0) | (9 << 8);// ASCMode: SMD SP

	/* Configure Transmit Buffer */
	/* Standard transmit buffer event is enabled */
	/* Define start entry of Transmit Data FIFO buffer DPTR = 0*/
	USIC0_CH0_TBCTR &= ~((0x07UL << 24) | (0x3fUL << 0));// SIZE DPTR
	/* Set Transmit Data Buffer to 32 and set data pointer to position 0*/
	USIC0_CH0_TBCTR |= ((0x05 << 24)|(0x00 << 0));

	/* Configure Receive Buffer */
	/* Standard Receive buffer event is enabled */
	/* Define start entry of Receive Data FIFO buffer DPTR = 32*/
	USIC0_CH0_RBCTR &= ~((0x07UL << 24) | (0x3fUL << 0));// SIZE DPTR
	/* Set Receive Data Buffer Size to 32 and set data pointer to position 32*/
	USIC0_CH0_RBCTR |= ((0x05UL << 24)|(32 << 0));

	/* Initialize UART_TX (DOUT)*/
	/* P2.1 as output controlled by ALT6 = U0C0.DOUT0 */
	P2_IOCR0 &= ~0x0000f800UL;
	P2_IOCR0 |= (0xB0U << 8);

	/* Configuration of Channel Control Register */
	/* CCR.PM = 00 ( Disable parity generation) */
	/* CCR.MODE = 2 (ASC mode enabled. Note: 0 (USIC channel is disabled)) */
	USIC0_CH0_CCR &= ~((0x03UL << 8) | 0x0fUL << 0);// PM MODE
	USIC0_CH0_CCR |= (0x02UL << 0);

	/* Initialize UART_RX (DX0)*/
	/* P2.2 as input */
	P2_IOCR0 &= ~0x00f80000UL;//INPUT = 0x00 << 16

	/* Select P2.2 as input for USIC DX3 -> UCIC DX0 */
	USIC0_CH0_DX3CR &= ~(0x07UL);// DSEL

	/* Route USIC DX3 input signal to USIC DX0 (DSEL=DX0G) */
	USIC0_CH0_DX0CR &= ~(0x07UL);// DSEL
	USIC0_CH0_DX0CR |= (6 << 0);

	// Switch analog pin to digital
	P2_PDISC &= ~0x00000002UL;
	P2_PDISC &= ~0x00000004UL;

	// empty RX-Buffer
	uint8_t dummy, n;
	for (n = 0 ; n < 100 ; n++) {
		if ((USIC0_CH0_TRBSR & 0x00000008) == 0) { // if there is anything in the RX-Buffer
			dummy = (USIC0_CH0_OUTR & 0x0000FFFF);
			USIC0_CH0_IN[0] = dummy; // send
		}
	}
}

void
UART_Write (char * str, uint8_t len)
{
	uint8_t i;
	for (i = 0 ; i < len ; i++) {//&& str[i] != '\0' ; i++) {
		USIC0_CH0_IN[0] = str[i];
	}
}

uint8_t
UART_Read (char * str)
{
	uint8_t i = 0;
	while ((USIC0_CH0_TRBSR & 0x00000008) == 0) {
		str[i] = (USIC0_CH0_OUTR & 0x0000FFFF);
		i++;
	}
	return i;
}

void
UART_SendAddr (uint32_t ui)
{
	int8_t i;
	char j;
	USIC0_CH0_IN[0] = '0';
	USIC0_CH0_IN[0] = 'x';
	for (i = 7; i >= 0; i--) {
		j = (char)((ui >> (4*i)) & 0x0F);
		if (j < 10) {
			USIC0_CH0_IN[0] = '0'+j;
		} else {
			USIC0_CH0_IN[0] = 'A'+j-10;
		}
	}
	USIC0_CH0_IN[0] = '\r';
	USIC0_CH0_IN[0] = '\n';
}

void
UART_SendTrace (char * str, uint8_t len, uint32_t ui)
{
	while ((USIC0_CH0_TRBSR & BIT11) == 0);
	UART_Write(str, len);
	UART_SendAddr(ui);
}

void
UART_SendWord (uint16_t w)
{
	while ((USIC0_CH0_TRBSR & BIT11) == 0);
	int8_t i;
	char j;
	USIC0_CH0_IN[0] = '0';
	USIC0_CH0_IN[0] = 'x';
	for (i = 3; i >= 0; i--) {
		j = (char)((w >> (4*i)) & 0x0F);
		if (j < 10) {
			USIC0_CH0_IN[0] = '0'+j;
		} else {
			USIC0_CH0_IN[0] = 'A'+j-10;
		}
	}
	USIC0_CH0_IN[0] = '\r';
	USIC0_CH0_IN[0] = '\n';
}
