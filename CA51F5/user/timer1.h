#ifndef _TIMER1_H_
#define _TIMER1_H_
/*********************************************************************************************************************/
#include "user_io_cfg.h"
/*********************************************************************************************************************/

#define INT_TIME1			1000			//定时时间，单位为us

#define	TH_VAL1				(unsigned char)((0x2000 - (INT_TIME1*(FOSC/1000))/12000)>>5)
#define	TL_VAL1				(unsigned char)(0x2000 - (INT_TIME1*(FOSC/1000))/12000)&0x1F

void timer1_init(void);

#endif

