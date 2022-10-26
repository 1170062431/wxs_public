#include "rec433.h"

bit F_keyDone_433M;		//按键连击用
unsigned long keyCode_433M;

void rec433M()		//125us中断
{
//------------------------------------------------------------------------------------------------------------
	static unsigned char F_rec433M_EN = 0;	//待机时=0，起始位低电平时=1，起始位高电平时=2?
	static unsigned char rec433MBitNum = 0;
	static unsigned char rec433MHighTime = 0;
	static unsigned char rec433MLowTime = 0;
	static unsigned int rec433MIdleTime = 0;	//空闲时间超过 SET_433M_DATA2DATA_TIME_125US 清空键值
//------------------------------------------------------------------------------------------------------------
//	/*根据实际按键有效位数调整*/
	static unsigned long rec433MBuff = 0;
	static unsigned long rec433MBuffBackup = 0;
//------------------------------------------------------------------------------------------------------------
//	/*
	rec433MIdleTime++;
	if(rec433MIdleTime > SET_433M_DATA2DATA_TIME_125US+20)
	{
		F_rec433M_EN = 0;
		keyCode_433M = IRKEY_NON;
	}
	if(IO_433M_REC && rec433MHighTime<200)	//读高电平时间
	{
		rec433MHighTime++;
		if(rec433MHighTime > 2)
		{
			if((rec433MLowTime >= SET_433M_START_L_TIME_MIN_125US)&&(rec433MLowTime <= SET_433M_START_L_TIME_MAX_125US))
			{
				rec433MBuff = 0;
				rec433MBitNum = 0;
				rec433MIdleTime = 0;
				F_rec433M_EN = 1;
			}
			rec433MLowTime = 0;
		}
		return;
	}
	
	else if(!IO_433M_REC && rec433MLowTime<200)
	{
		rec433MLowTime++;
		if(F_rec433M_EN)
		{
			if(rec433MLowTime == 2)	//只在设定值执行一次，在范围内值越大抗干扰越好
			{
				if(F_rec433M_EN == 1)
				/*	
				{
					if((SET_433M_START_H_TIME_MIN_125US<=rec433MHighTime) && (rec433MHighTime<=SET_433M_START_H_TIME_MAX_125US))	//正常码
					{
						F_rec433M_EN = 2;
						rec433MHighTime = 0;
						return;
					}
					else //if((SET_433M_LXM_H_TIME_MIN_125US<=rec433MHighTime) && (rec433MHighTime<=SET_433M_LXM_H_TIME_MAX_125US))	//连续码
					{
						rec433MHighTime = 0;
						return;
					}
				}
				else if(F_rec433M_EN == 2)
			//	*/
				{
					if(rec433MBitNum < SET_433M_REC_BIT_MAX)
						rec433MBitNum++;
					if(SET_433M_REC_DATA_START_BIT<=rec433MBitNum && rec433MBitNum<=SET_433M_REC_DATA_STOP_BIT)
					{
						if(SET_433M_DATA_0_H_TIME_MIN_125US<=rec433MHighTime && rec433MHighTime<=SET_433M_DATA_0_H_TIME_MAX_125US)
						{	
							rec433MBuff = rec433MBuff<<1;
							rec433MHighTime = 0;
						}
						else if(SET_433M_DATA_1_H_TIME_MIN_125US<=rec433MHighTime && rec433MHighTime<=SET_433M_DATA_1_H_TIME_MAX_125US)
						{
							rec433MBuff = (rec433MBuff<<1)|1;
							rec433MHighTime = 0;
						}
						else
						{
							rec433MBuff = 0;
							rec433MBitNum = 0;
							F_rec433M_EN = 0;
						//	rec433MBitNum--;
							return;
						}
						/*
						if(rec433MBitNum == SET_433M_REC_DATA_STOP_BIT) 	//接收完有效位数
						{
							switch(rec433MBuff)
							{
								//YK_IR
								case IRKEY_POW:
								case IRKEY_TURN:
								case IRKEY_SPADD:
								case IRKEY_SPDEC:
								case IRKEY_TMADD:
								case IRKEY_TMDEC:
								case IRKEY_START_STOP:
								case IRKEY_P1:
								case IRKEY_P3:
								case IRKEY_P2:
								case IRKEY_P4_P5:
								case IRKEY_HEAT: keyCode_433M = rec433MBuff;break;
								default:break;
							}
						}
					//	*/
					}
					else
						rec433MHighTime = 0;
				}
			}
			else if(rec433MLowTime == SET_433M_START_L_TIME_MIN_125US)	//到下个起始位，接收完成
			{
				if(rec433MBuff == rec433MBuffBackup)
 				{
 					keyCode_433M = rec433MBuff;
					rec433MBuff = 0;
					rec433MBuffBackup = 0;
				}
				else
				{
					rec433MBuffBackup = rec433MBuff;
					rec433MBuff = 0;
				}
			}
		}
		else
			rec433MHighTime = 0;
	}
//	*/
}