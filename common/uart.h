/*
 * uart.h
 *
 *  Created on: 2017-3-29
 *      Author: Administrator
 */

#ifndef UART_H_
#define UART_H_

#define UART_BASE_ADDR	0x400400
#define RBR	*((int *)(UART_BASE_ADDR+0))
#define THR	*((int *)(UART_BASE_ADDR+0))
#define IER	*((int *)(UART_BASE_ADDR+1))
#define IIR	*((int *)(UART_BASE_ADDR+2))
#define FCR	*((int *)(UART_BASE_ADDR+2))
#define LCR	*((int *)(UART_BASE_ADDR+3))
#define MCR	*((int *)(UART_BASE_ADDR+4))
#define LSR	*((int *)(UART_BASE_ADDR+5))
#define MSR	*((int *)(UART_BASE_ADDR+6))
#define SCR	*((int *)(UART_BASE_ADDR+7))
#define DLL	*((int *)(UART_BASE_ADDR+0))
#define DLM	*((int *)(UART_BASE_ADDR+1))

void TMCR_reset( void );
void EMIF_init(void);
void wait(int nWait);



#endif /* UART_H_ */
