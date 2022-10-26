#ifndef _TIMER0_H_
#define _TIMER0_H_
/*********************************************************************************************************************/
#include "user_io_cfg.h"
/*********************************************************************************************************************/

#define INT_TIME0			(125-1)			//¶¨Ê±125us,+Êý×Ö²¹³¥

#define	TH_VAL0				(unsigned char)((0x2000 - (INT_TIME0*(FOSC/1000))/12000)>>5)
#define	TL_VAL0				(unsigned char)(0x2000 - (INT_TIME0*(FOSC/1000))/12000)&0x1F

extern unsigned char F_1ms,F_1s;
extern unsigned int T_1ms;

void timer0_init(void);

#endif