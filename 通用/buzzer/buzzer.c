#include "..\h\buzzer.h"

struct_buzzer stu_buzzer;

//===========================================================
//Funtion name��buzzerOn
//parameters��bzOnTime_ms-����������ʱ��ms��bzOffTime_ms-�������ر�ʱ��ms��bzTimes-��������
//returned value����
//===========================================================
void buzzerOn(unsigned int bzOnTime_ms,unsigned int bzOffTime_ms,unsigned char bzTimes)
{
	setBuzzerOnTime_ms = bzOnTime_ms;
	setBuzzerOffTime_ms = bzOffTime_ms;
	C_buzzerOnTime_ms = setBuzzerOnTime_ms;
	C_buzzerOffTime_ms = setBuzzerOffTime_ms;
	buzzerTimes = bzTimes;
}

#if 0//BUZZER_EN	//ִ�м��1ms,�����ѡ�ú����ж�ʱ����Ʒ������ŵ�ƽ
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