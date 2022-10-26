	#ifndef _TIMER_H_
	#define _TIMER_H_
	#include	"BS83B16A-3.h"
	
//	时钟源选择
	#define SET_TIMER_OSC_Fsys		(_ts = 0)
	#define SET_TIMER_OSC_Fsub		(_ts = 1)

//	预分频选择
	#define SET_TIMER_Prescale_1	(_tpsc2=0,_tpsc1=0,_tpsc0=0)
	#define SET_TIMER_Prescale_2	(_tpsc2=0,_tpsc1=0,_tpsc0=1)
	#define SET_TIMER_Prescale_4	(_tpsc2=0,_tpsc1=1,_tpsc0=0)
	#define SET_TIMER_Prescale_8	(_tpsc2=0,_tpsc1=1,_tpsc0=1)
	#define SET_TIMER_Prescale_16	(_tpsc2=1,_tpsc1=0,_tpsc0=0)
	#define SET_TIMER_Prescale_32	(_tpsc2=1,_tpsc1=0,_tpsc0=1)
	#define SET_TIMER_Prescale_64	(_tpsc2=1,_tpsc1=1,_tpsc0=0)
	#define SET_TIMER_Prescale_128	(_tpsc2=1,_tpsc1=1,_tpsc0=1)
	
	#define TIMER_INT_ENABLE		(_tf = 0,_te = 1,_emi = 1)
	#define TIMER_INT_UNABLE		(_tf = 0,_te = 0,_emi = 0)
	
	#define TimerOn		(_ton = 1)
	#define TimerOff	(_ton = 0)
	
	extern void timerInit();
	
	#endif