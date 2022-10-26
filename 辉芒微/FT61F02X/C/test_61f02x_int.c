//********************************************************* 
/*  �ļ���: TEST_61F02x_INT.c
*	���ܣ�  FT61F02x-INT������ʾ
*   IC:    FT61F023 SOP16
*   ����  16M/2T                    
*   ˵����  ������DemoPortOut(PA3)���100֡50HZ��ռ�ձ�Ϊ50%�ķ�����, MCU
*          ����˯��, �ȴ��ⲿ�жϵķ�����
*		   ���ⲿ�жϴ������ظ���������;
*
*                  FT61F023  SOP16 
*                 ----------------
*  VDD-----------|1(VDD)   (VSS)16|-----------GND     
*  NC------------|2(PA7)   (PA0)15|------------NC 
*  NC------------|3(PA6)   (PA1)14|------------NC
*  NC------------|4(PA5)   (PA2)13|------------NC
*  NC------------|5(PC3)   (PA3)12|---DemoPortOut
*  NC------------|6(PC2)   (PC0)11|------------NC
*  NC------------|7(PA4)   (PC1)10|-----------INT<--�ж�IN
*  NC------------|8(PC5)   (PC4)09|------------NC
*			      ----------------
*/
//*********************************************************
#include "SYSCFG.h"
#include "..\h\config.h"
#include "..\h\mcu_sel.h"
#include "..\h\user_project.h"

//********************************************************
//**************�жϴ���**********************************
void interrupt ISR(void)
{ 
	//��ʱ�����жϴ���**********************
	if(TM0_E && TM0_F)
	{
		/*	100us
		static u8 T_100us = 0;
		static u16 T_1ms = 0;
		TM0_F = RESET;
		TMR0 = 156; 		//256-100��Ԥ��Ƶ8����ʱ100us
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
		TMR0 = 131; 		//256-125��Ԥ��Ƶ8����ʱ125us
		
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
	//��ʱ500US=>TMR1=8000*0.125S=1ms��
	//��ֵ=65536-8000=57535=>0XE0BF
/*	if(TMR1IE && TMR1IF)		//1ms�ж�һ��
	{
		TMR1IF = 0;
		TMR1L = 0XBF;  			//��Ҫ���ж������¸���ʼֵ
		TMR1H = 0XE0;  			//��Ҫ���ж������¸���ʼֵ
	} 
*/	 
/*	if(TMR2IE && TMR2IF)        //100us�ж�һ��
	{
		TMR2IF = 0;
	}  
*/	
/*	//�Ƚ���2���жϴ���**********************
	if(C2IF)							
	{		 
		//Cbuff = CMCON0;  				//��CMCON0����ʧ������
		//C2IF = 0;						//���жϱ�־	
		//DemoPortOut = ~DemoPortOut; 	//��ת��ƽ
	}
*/	
	//PA��ƽ�仯�ж�**********************
	if(PAIE && PAIF)		
    {
		ReadAPin = PORTA; 	//��ȡPORTA������PAIF��־
		PAIF = 0;  			//��PAIF��־λ
		PAIE = 0;  			//���Ƚ�ֹPA2�ж�
		IOCA2 =0;  			//��ֹPA2��ƽ�仯�ж�
    }
	 
/*	//PC1�ⲿ�жϴ���**********************
	if(INTE && INTF)		
	{                   	
		INTF = 0;  			//��PC1 INT ��־λ
		INTE = 0;  			//���Ƚ�ֹINT�ж�
	}
*/

}
