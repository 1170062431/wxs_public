#include "..\h\buzzer.h"

struct_buzzer stu_buzzer;

//===========================================================
//Funtion name：buzzerOn
//parameters：bzOnTime_ms-蜂鸣器开启时间ms，bzOffTime_ms-蜂鸣器关闭时间ms，bzTimes-蜂鸣次数
//returned value：无
//===========================================================
void buzzerOn(unsigned int bzOnTime_ms,unsigned int bzOffTime_ms,unsigned char bzTimes)
{
	setBuzzerOnTime_ms = bzOnTime_ms;
	setBuzzerOffTime_ms = bzOffTime_ms;
	C_buzzerOnTime_ms = setBuzzerOnTime_ms;
	C_buzzerOffTime_ms = setBuzzerOffTime_ms;
	buzzerTimes = bzTimes;
}

#if 0//BUZZER_EN	//执行间隔1ms,看情况选用合适中断时间控制蜂鸣器脚电平
	if(buzzerTimes)
	{
		if(C_buzzerOnTime_ms)
		{
			C_buzzerOnTime_ms--;
		}
		else if(C_buzzerOffTime_ms)
		{
			C_buzzerOffTime_ms--;
		}
		else 
		{
			buzzerTimes--;
			if(buzzerTimes)
			{
				C_buzzerOnTime_ms = setBuzzerOnTime_ms;
				C_buzzerOffTime_ms = setBuzzerOffTime_ms;
			}
		}
	}
#endif