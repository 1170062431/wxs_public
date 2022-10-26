
/*********************************************************************************************************************/
#include "timer0.h"
/*********************************************************************************************************************/
uchar F_1ms,F_1s;
uint T_1ms;

void TIMER0_ISR (void) interrupt 1 		 //ÿ1ms�����ж�
{
	static uchar F_IRRec_EN = 0;	//����ʱ=0����ʼλ�͵�ƽʱ=1����ʼλ�ߵ�ƽʱ=2
	static uchar IRKeyBitNum = 0;
	static uint IRHighTime = 0;
	static uchar IRLowTime = 0;
//------------------------------
//	/*����ʵ�ʰ�����Чλ������*/
//	static uchar IRRecBuff = 0;
//	static uint IRRecBuff = 0;
	static ulong IRRecBuff = 0;
//------------------------------
	static unsigned char T_125us = 0;
	
	TH0 = TH_VAL0;
	TL0 = TL_VAL0;

//	IO_LED_DAT = !IO_LED_DAT;

	T_125us++;
	if(T_125us == 8)
	{
		T_125us = 0;
	
		F_1ms = 1;
		T_1ms++;
		if(T_1ms == 1000)
		{
			T_1ms = 0;
			F_1s = 1;
		}

		if(keySta)
		{
			if(keySta == keyStaBackup)
				keyDownTime_ms++;
			else
				keyDownTime_ms = 0;
		}
		else if(keyDownTime_ms)
		{
			keyDownTime_ms = 0;
			if(++light.mode >= MODE_END)
				light.mode = MODE_BEGIN+1;
		}
	}
	
	if(light.mic)
	{
		if(!IO_MIC_AD)
		{
			if(light.mic_ad < LED_NUM)
				light.mic_ad++;
		}
	}
	else
		light.mic_ad = 0;
		
//	/*	
//	getIRKeyCode();
//	/*
	if(IO_IR_REC && IRHighTime<5000)	//���ߵ�ƽʱ��
	{
		IRHighTime++;
		if(IRHighTime > 2)
		{
			if (IRLowTime >= SET_IR_START_L_TIME_MIN_125US)
			{
				IRRecBuff = 0;
				IRKeyBitNum = 0;
				F_IRRec_EN = 1;
			}
			IRLowTime = 0;
		}
		if(IRHighTime > SET_IR_DATA2DATA_TIME_125US+20)
		{
			F_IRRec_EN = 0;
			keyCode = IRKEY_NON;
		}
		return;
	}
	
	else if(!IO_IR_REC && IRLowTime<200)
	{
		IRLowTime++;
		if(F_IRRec_EN)
		{
			if(IRLowTime == 2)	//ֻ���趨ִֵ��һ�Σ��ڷ�Χ��ֵԽ�󿹸���Խ��
			{
				if(F_IRRec_EN == 1)
				{
					if((SET_IR_START_H_TIME_MIN_125US<=IRHighTime) && (IRHighTime<=SET_IR_START_H_TIME_MAX_125US))	//������
					{
						F_IRRec_EN = 2;
						IRHighTime = 0;
						return;
					}
					else //if((SET_IR_LXM_H_TIME_MIN_125US<=IRHighTime) && (IRHighTime<=SET_IR_LXM_H_TIME_MAX_125US))	//������
					{
						IRHighTime = 0;
						return;
					}
				}
				else if(F_IRRec_EN == 2)
				{
					if(IRKeyBitNum < SET_IR_REC_BIT_MAX)
						IRKeyBitNum++;
					if(SET_IR_REC_DATA_START_BIT<=IRKeyBitNum && IRKeyBitNum<=SET_IR_REC_DATA_STOP_BIT)
					{
						if(SET_IR_DATA_0_H_TIME_MIN_125US<=IRHighTime && IRHighTime<=SET_IR_DATA_0_H_TIME_MAX_125US)
						{	
							IRRecBuff = IRRecBuff<<1;
							IRHighTime = 0;
						}
						else if(SET_IR_DATA_1_H_TIME_MIN_125US<=IRHighTime && IRHighTime<=SET_IR_DATA_1_H_TIME_MAX_125US)
						{
							IRRecBuff = (IRRecBuff<<1)|1;
							IRHighTime = 0;
						}
						else
						{
						//	IRRecBuff = 0;
						//	IRKeyBitNum = 0;
						//	F_IRRec_EN = 0;
							IRKeyBitNum--;
							return;
						}
						if(IRKeyBitNum == SET_IR_REC_DATA_STOP_BIT) 	//��������Чλ��
						{
							if((IRRecBuff>>16 == IRKEY_HEAD)&&((IRRecBuff+(IRRecBuff>>8))&0xFF == 0xFF))
							{
								IRRecBuff = userIrCodeChange((u16)IRRecBuff);
								keyCode = IRRecBuff&0xFF;
								/* //
								switch(IRRecBuff)
								{
								//YK_IR
								case IRKEY_light_add:
								case IRKEY_light_dec:
								case IRKEY_off:
								case IRKEY_on:
								case IRKEY_r:
								case IRKEY_g:
								case IRKEY_b:
								case IRKEY_w:
								case IRKEY_r_1:
								case IRKEY_g_1:
								case IRKEY_b_1:
								case IRKEY_flash:
								case IRKEY_r_2:
								case IRKEY_g_2:
								case IRKEY_b_2:
								case IRKEY_strobe:
								case IRKEY_r_3:
								case IRKEY_g_3:
								case IRKEY_b_3:
								case IRKEY_fade:
								case IRKEY_r_4:
								case IRKEY_g_4:
								case IRKEY_b_4:
								case IRKEY_smooth:
								//	keyCode = IRRecBuff;
									break;
								default:break;
								}
							//	*/
							}
					//	Uart0_PutChar(IRRecBuff);
						}
					}
					else
						IRHighTime = 0;
				}
			}
		}
		else
			IRHighTime = 0;
	}
//	*/
}
void timer0_init(void)
{	
	TMOD = (TMOD&0xFC)|0x00; 	//ģʽѡ��: ��ʱ��0��ģʽ0
	TH0 = TH_VAL0;    			//��8λװ��ֵ
	TL0 = TL_VAL0;    			//��8λװ��ֵ
	
	TR0 = 1;       //��ʱ��0ʹ��  
	ET0 = 1;       //��ʱ��0�ж�ʹ��
	PT0 = 0;       //���ö�ʱ��0�ж����ȼ�Ϊ�����ȼ�
}
