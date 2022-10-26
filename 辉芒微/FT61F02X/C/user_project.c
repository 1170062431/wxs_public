//Project: ZS-LED-4-1_2A.prj
// Device: FT61F02X
// Memory: Flash 2KX14b, EEPROM 256X8b, SRAM 128X8b
// Author: 
//Company: 
//Version:
//   Date: 
//===========================================================
//===========================================================
#include	"SYSCFG.h";
#include	"..\h\config.h"
#include	"..\h\user_project.H"
#include	"..\h\MCU_SEL.H"

//===========================================================
//Variable definition
//===========================================================
FLAG Time_FLAG;
FlagStatus F_feedDog,F_keyLJ;
u8 keyBuff,keySta,keyBackUp,keyCode;
u8 mode,T_LedOn_10s;
u8 ReadAPin,C_sleep;
u8 AD_Tsense,AD_Isense;

//===========================================================
//Funtion name:turnToModeIdle(void)
//parameters����
//returned value����
//===========================================================
void turnToModeIdle(void)
{
	mode = MODE_IDLE;
	buzzerOn(200, 200, 1);
}

//===========================================================
//Funtion name:void turnToModeWork(void)
//parameters����
//returned value����
//===========================================================
void turnToModeWork(void)
{
	mode = MODE_WORK;
	buzzerOn(200, 200, 1);
}

//===========================================================
//Funtion name:keyScan(void)
//parameters����
//returned value����
//===========================================================
void keyScan(void)
{
	keyBuff = (keyBuff<<1)|IO_KEY;
	if(!(keyBuff&0x0F))
	{
		keySta = K_MODE;
		if(keySta != keyBackUp)
		{
			keyCode = K_MODE;
			keyBackUp = K_MODE;
		}
	}
	else if((keyBuff&0x0F) == 0x0F)
	{
		keySta = K_NON;
		keyCode = K_NON;
		keyBackUp = K_NON;
		F_keyLJ = RESET;
	}
}

//===========================================================
//Funtion name:keyCL(void)
//parameters����
//returned value����
//===========================================================
void keyAction(void)
{
	if(keyCode==K_MODE)
	{
		switch(mode)
		{
			case MODE_IDLE:
				turnToModeWork();
				break;
			case MODE_WORK:
				turnToModeIdle();
				break;
			default:break;
		}
	}
	F_keyLJ = SET;
}

//===========================================================
//Funtion name��main
//parameters����
//returned value����
//===========================================================

main()
{
	POWER_INITIAL();		        //ϵͳ��ʼ��
	ADC_INITIAL();			        //ADC��ʼ��	
	PWM_INITIAL();
	
	F_feedDog = SET;
	
	IO_RLED_set;
	IO_GLED_set;
	IO_YLED_set;
	DelayS(1);
	IO_RLED_clr;
	IO_GLED_clr;
	IO_YLED_clr;
	buzzerOn(200, 200, 1);
	
	while(1)
	{
		if(F_1ms)
		{
			F_1ms = RESET;
			keyScan();
			if(keyCode && !F_keyLJ)
			{
				keyAction();
			}
			
		#if BUZZER_EN
			if(buzzerTimes)
			{
				if(C_buzzerOnTime_ms)	//Ҫ4KƵ��
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
		
			if(C_sleep)
				C_sleep--;
		
		}

		if(mode == MODE_IDLE)
		{
			if(!C_sleep)			//����˯��
			{
				C_sleep = SET_TIME2SLEEP;
				PAIF =0;   				//��PA INT�жϱ�־λ
				IOCA2 =1;  				//ʹ��PA2��ƽ�仯�ж�
				ReadAPin = IO_KEY;		//��PA��ƽ�仯�ж�
				PAIE =1;				//ʹ��PA INT�ж�
				SLEEP();
			}
		}
		else
		{
			C_sleep = SET_TIME2SLEEP;
		}
	}
} 
