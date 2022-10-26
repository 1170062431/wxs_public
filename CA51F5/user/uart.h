#ifndef _UART_H_
#define _UART_H_

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <absacc.h>

#include "user_io_cfg.h"

#define UART0_TX_BUF_SIZE		20
#define UART0_RX_BUF_SIZE		100

typedef struct
{
	unsigned char head;
	unsigned char tail;
}T_Buf_Info;

extern T_Buf_Info xdata	uart0_send;
extern T_Buf_Info xdata	uart0_rev;
extern unsigned char xdata uart0_tx_buf[UART0_TX_BUF_SIZE];
extern unsigned char xdata uart0_rx_buf[UART0_RX_BUF_SIZE];
extern bit uart0_tx_flag;	

#ifndef UART0_EN
	  #define Uart0_PutChar(n)
#else
void Uart0_PutChar(unsigned char bdat);
void Uart0_Initial(unsigned long int baudrate);
#endif	


#ifdef PRINT_EN
void uart_printf(char *fmt,...);
void user_printf(char *fmt,...);

#endif

#endif
