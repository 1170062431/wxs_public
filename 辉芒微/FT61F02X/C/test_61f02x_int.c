//********************************************************* 
/*  文件名: TEST_61F02x_INT.c
*	功能：  FT61F02x-INT功能演示
*   IC:    FT61F023 SOP16
*   晶振：  16M/2T                    
*   说明：  程序中DemoPortOut(PA3)输出100帧50HZ的占空比为50%的方波后, MCU
*          进入睡眠, 等待外部中断的发生；
*		   当外部中断触发后，重复以上流程;
*
*                  FT61F023  SOP16 
*                 ----------------
*  VDD-----------|1(VDD)   (VSS)16|-----------GND     
*  NC------------|2(PA7)   (PA0)15|------------NC 
*  NC------------|3(PA6)   (PA1)14|------------NC
*  NC------------|4(PA5)   (PA2)13|------------NC
*  NC------------|5(PC3)   (PA3)12|---DemoPortOut
*  NC------------|6(PC2)   (PC0)11|------------NC
*  NC------------|7(PA4)   (PC1)10|-----------INT<--中断IN
*  NC------------|8(PC5)   (PC4)09|------------NC
*			      ----------------
*/
//*********************************************************
#include "SYSCFG.h"
#include "..\h\config.h"
#include "..\h\mcu_sel.h"
#include "..\h\user_project.h"

//********************************************************
//**************中断处理**********************************
void interrupt ISR(void)
{ 
	//定时器的中断处理**********************
	if(TM0_E && TM0_F)
	{
		/*	100us
		static u8 T_100us = 0;
		static u16 T_1ms = 0;
		TM0_F = RESET;
		TMR0 = 156; 		//256-100，预分频8，定时100us
		T_100us++;
		if(T_100us == 10)
		{
			T_100us = 0;
			F_1ms = SET;
			T_1ms++;
			if(T_1ms == 1000)
			{
				T_1ms = 0;
				F_1s = SET;
		//		IO_LED = !IO_LED;
			}
			if(C_sleep)
				C_sleep--;
		}
	//	*/

	//	/*	125us
		static u8 T_125us = 0;
		static u16 T_1ms = 0;
		TM0_F = RESET;
		TMR0 = 131; 		//256-125，预分频8，定时125us
		
	#if BUZZER_EN	
		if(C_buzzerOnTime_ms)
		{
			IO_BZ_H = IO_BZ_L;
			IO_BZ_L = !IO_BZ_L;
		}
		else
		{
			IO_BZ_H_clr;
			IO_BZ_L_clr;
		}
	#endif	
	
		T_125us++;	
		if(T_125us == 8)
		{
			T_125us = 0;
			F_1ms = SET;
			T_1ms++;
			if(T_1ms == 1000)
			{
				T_1ms = 0;
				F_1s = SET;
			//	IO_LED = !IO_LED;
			}
		}
	//	*/
	} 
	
	//T1SYNC=16M/2T=8M=0.125US
	//定时500US=>TMR1=8000*0.125S=1ms，
	//初值=65536-8000=57535=>0XE0BF
/*	if(TMR1IE && TMR1IF)		//1ms中断一次
	{
		TMR1IF = 0;
		TMR1L = 0XBF;  			//需要在中断里重新赋初始值
		TMR1H = 0XE0;  			//需要在中断里重新赋初始值
	} 
*/	 
/*	if(TMR2IE && TMR2IF)        //100us中断一次
	{
		TMR2IF = 0;
	}  
*/	
/*	//比较器2的中断处理**********************
	if(C2IF)							
	{		 
		//Cbuff = CMCON0;  				//读CMCON0结束失配条件
		//C2IF = 0;						//清中断标志	
		//DemoPortOut = ~DemoPortOut; 	//翻转电平
	}
*/	
	//PA电平变化中断**********************
	if(PAIE && PAIF)		
    {
		ReadAPin = PORTA; 	//读取PORTA数据清PAIF标志
		PAIF = 0;  			//清PAIF标志位
		PAIE = 0;  			//暂先禁止PA2中断
		IOCA2 =0;  			//禁止PA2电平变化中断
    }
	 
/*	//PC1外部中断处理**********************
	if(INTE && INTF)		
	{                   	
		INTF = 0;  			//清PC1 INT 标志位
		INTE = 0;  			//暂先禁止INT中断
	}
*/

}
