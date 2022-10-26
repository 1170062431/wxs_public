	#include "..\H\timer.h"
	#include "USER_PROGRAM.H" 
	
	void timerInit()
	{
		TimerOff;
		SET_TIMER_OSC_Fsys;
		SET_TIMER_Prescale_8;
		_tmr = 205;				//¶¨Ê±50us,255-£¨8M/Prescale/10^6£©
		TIMER_INT_ENABLE;
		TimerOn;
	}