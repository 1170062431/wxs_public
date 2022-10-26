#include "..\h\led.h"

#if LED_EN

struct_led stu_led;
//===========================================================
//Funtion name:ledFlash
//parameters:onTime_ms-LED����ʱ��ms,offTime_ms-LED�ر�ʱ��ms,flashTimes-��˸����
//returned value:��
//===========================================================
void ledFlash(uint onTime_ms,uint offTime_ms,uchar flashTimes)
{
	setLedOnTime_ms = onTime_ms;
	setLedOffTime_ms = offTime_ms;
	C_ledOnTime_ms = setLedOnTime_ms;
	C_ledOnTime_ms = setLedOffTime_ms;
	ledFlashTimes = flashTimes;
}

#if 0//LED_EN	//ִ�м��1ms
	if(ledFlashTimes )
	{
		if(C_ledOnTime_ms)
		{
			C_ledOnTime_ms--;
		}
		else if(C_ledOffTime_ms)
		{
			C_ledOffTime_ms--;
		}
		else 
		{
			ledFlashTimes--;
			if(ledFlashTimes)
			{
				C_ledOnTime_ms = setledOnTime_ms;
				C_ledOffTime_ms = setledOffTime_ms;
			}
		}
	}
#endif

#endif


#if RGB_EN

struct_rgb stu_rgb;
//===========================================================
//Funtion name:rgbChange
//parameters:switchTime_ms-�л�ʱ��ms,dutr_R/G/B-ռ�ձ�R/G/B
//returned value:�л���ɷ���0�����򷵻�1
//===========================================================
uchar rgbChange(uchar switchTime_ms,uchar dutr_R,uchar dutr_G,uchar dutr_B)
{
	static uchar switchTime = 0;
	
//	stu_rgb.switchTime_ms = switchTime_ms;
	if(switchTime_ms)
	{
		if(switchTime)
		{
			switchTime--;
			return 1;
		}
		else
		{
			if(stu_rgb.dutyR > dutr_R)
				stu_rgb.dutyR--;
			else if(stu_rgb.dutyR < dutr_R)
				stu_rgb.dutyR++;
			
			if(stu_rgb.dutyG > dutr_G)
				stu_rgb.dutyG--;
			else if(stu_rgb.dutyG < dutr_G)
				stu_rgb.dutyG++;
			
			if(stu_rgb.dutyB > dutr_B)
				stu_rgb.dutyB--;
			else if(stu_rgb.dutyB < dutr_B)
				stu_rgb.dutyB++;
		}
			
		if((stu_rgb.dutyR != dutr_R)||(stu_rgb.dutyG != dutr_G)||(stu_rgb.dutyB != dutr_B))
		{
			switchTime = switchTime_ms;
			return 1;
		}
	}
	else
	{
		stu_rgb.dutyR = dutr_R;
		stu_rgb.dutyG = dutr_G;
		stu_rgb.dutyB = dutr_B;
	}
	return 0;
}

#endif