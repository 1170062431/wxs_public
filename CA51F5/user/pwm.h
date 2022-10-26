#ifndef _PWM_H_
#define _PWM_H_
/****************************************************************/
#include "user_io_cfg.h"
/****************************************************************
****************************************************************/
#define PWM_CH0		0
#define PWM_CH1		1
#define PWM_CH2		2
#define PWM_CH3		3
#define PWM_CH4		4
#define PWM_CH5		5
/**************************************************************/

//PWMxCON
#define PWMIE(N)			(N<<7)	  //N=0-1
#define PWMTOG(N)			(N<<6)	  //N=0-1
#define PWMMOD(N)			(N<<3)	  //N=0-7
#define PWMPOL(N)			(N<<2)	  //N=0-1
#define PWMCKS_SYS			0 
#define PWMCKS_IL			1	  
#define PWMCKS_IH			2	 


//PWMIF  
#define  PWM5IF	(1<<5)
#define  PWM4IF	(1<<4)
#define  PWM3IF	(1<<3)
#define  PWM2IF	(1<<2)
#define  PWM1IF	(1<<1)
#define  PWM0IF	(1<<0)	

//LEFLG
#define LEF1		(1<<7)
#define LEBSY1		(1<<6)
#define LEF0		(1<<3)
#define LEBSY0		(1<<2)

void pwm2_init();

#endif
