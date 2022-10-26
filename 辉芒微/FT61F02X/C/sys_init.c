
	#include "SYSCFG.h";
	#include "..\H\user_project.h"
	#include "..\H\config.h"
	#include "..\H\mcu_sel.h"
    
	void POWER_INITIAL (void)
	{
        OSCCON = (OSCCON & 0x8F)|(SetFsys << 4);
		
		INTCON = 0;  			//�ݽ�ֹ�����ж�
		PORTA = 0B00000000; 
		TRISA = 0B11111111;		//PAȫ������ 
		
		PORTC = 0B00000000; 
		TRISC = 0B11111111;		//PCȫ������
		
        WPUA = 0B00000000;    	//��ֹ����PA������
		WPUC = 0B00000000;    	//��ֹ����PC������
		MSCKCON = 0B00000000;	//Bit6->0,��ֹPA4��PC5��ѹ���
					  			//Bit5->0,TIMER2ʱ��ΪFosc
					  			//Bit4->0,��ֹLVR          
		CMCON0 = 0B00000000; 	//�رձȽ�����CxINΪ����IO��
		ANSEL = 0B10101000; 	//AN0~7,1 = ģ�����룬0 = ���� IO

		IO_AD_Tsense_int;
		IO_AD_Isense_pu_clr;

		IO_AD_Tsense_int;
		IO_AD_Tsense_pu_clr;

		IO_BZ_H_out;
		IO_BZ_H_clr;
		
		IO_BZ_L_out;
		IO_BZ_L_clr;
		
		IO_GLED_out;
		IO_GLED_clr;
		
		IO_HEAT_out;
		IO_HEAT_clr;

		IO_KEY_int;
		IO_KEY_pu_set;

		IO_PA0_int;
		IO_PA0_pu_set;
		IO_PA1_int;
		IO_PA1_pu_set;
		IO_PA5_int;
		IO_PA5_pu_set;
		IO_PC0_int;
		IO_PC0_pu_set;
		IO_PC5_int;
		IO_PC5_pu_set;
		
//		WDTCON �Ĵ���
//			7:5.XXX
//      	4:1.WDTPS<3:0>: ���Ź���ʱ������ѡ��
//			0.SWDTEN:�����/�رտ��Ź���ʱ��
		CLRWDT();
        WDTCON = (WDTCON &0xE1)|(SetWdtPrescaler<<1);
//		SWDTEN = ENABLE;
		SWDTEN = DISABLE;
        
//		OPTION �Ĵ�����Timer0��
//			7.PAPU: PORTA ����ʹ��λ
//			6.INTEDG:�ж���ѡ��λ		***1 = �� INT ���ŵ��������ж�	***0 = �� INT ���ŵ��½����ж�
//			5.T0CS: Timer0 ʱ��Դѡ��λ	***1 = PA2/T0CKI ���ŵ�����	***0 = �ڲ�ָ������(FOSC/4)
//			4.T0SE: Timer0 ʱ��Դ����ѡ��λ	***1 = �� PA2/T0CKI ���ŵ��½��ص���		***0 = �� PA2/T0CKI ���ŵ������ص���
//			3.PSA:Ԥ��Ƶ������λ	***1 = Ԥ��Ƶ������� WDT		***0 = Ԥ��Ƶ������� Timer0 ģ��
//			2:0.PS<2:0>:Ԥ��Ƶ��ѡ��λ	0-7		***TIMER0��Ƶ��:2^1--2^8		***WDT��Ƶ��:2^0--2^7
        OPTION = (0B00000000+SetTm0Prescaler);
//		TMR0 = 56;		//256-200��4TԤ��Ƶ2����ʱ100us
//		TMR0 = 48;		//256-208��4TԤ��Ƶ2����ʱ104us,9600������
//		TMR0 = 156;		//256-100��2TԤ��Ƶ8����ʱ100us
//		TMR0 = 152;		//256-104��2TԤ��Ƶ8����ʱ104us,9600������
		TMR0 = 131;		//256-125��2TԤ��Ƶ8����ʱ125us,drive 4K buzzer

//		T1CON �Ĵ�����Timer1��
//			7.T1GINV:TIMER1 �ſط�תλ***1 = Timer1 �ſ�Ϊ�ߵ�ƽ��Ч���ſ�Ϊ�ߵ�ƽʱ Timer1 ������***0 = Timer1 �ſ�Ϊ�͵�ƽ��Ч���ſ�Ϊ�͵�ƽʱ Timer1 ������
//			6.TMR1GE:Timer1 �ſ�ʹ��λ(2),TMR1ON = 0����λ������,TMR1ON = 1��***1 = Timer1 �� Timer1 �ſز��ʱ��***0 = Timer1 ��
//			5:4.T1CKPS[1:0]:Timer1 ����ʱ��Ԥ��Ƶ��ѡ��λ	***11=8��Ƶ��10=4��Ƶ��01=2��Ƶ��00=1��Ƶ
//			3.T1OSCEN:LP ����ʹ�ܿ���λ������� CLKOUT ������ INTOSC ���ڼ���״̬��		***1 = LP ������ʹ������ Timer1 ʱ��***0 = LP �����ر�
//			2.T1SYNC:Timer1 �ⲿʱ������ͬ������λ��TMR1CS = 1:***1 = ��ͬ���ⲿʱ������	***0 = ͬ���ⲿʱ������,TMR1CS = 0:��λ�����ԡ�Timer1 ʹ���ڲ�ʱ��
//			1.TMR1CS:Timer1 ʱ��Դѡ��λ***1 = T1CK1 ���ţ������أ����ⲿʱ��	***0 = �ڲ�ʱ�ӣ�ָ��ʱ�ӣ�
//			0.TMR1ON:Timer1 ʹ��λ
		T1CON = 0B00000000; 
//		T1SYNC=16M/2T=8M=0.125US
//		��ʱ500US=>TMR1=8000*0.125S=1ms��
//		��ֵ=65536-8000=57535=>0XE0BF
		TMR1L = 0XBF;  			//��Ҫ���ж������¸���ʼֵ
		TMR1H = 0XE0;  			//��Ҫ���ж������¸���ʼֵ
		
		#ifndef	PWM1
//	    T2CON �Ĵ���(Timer2)
//			7.XXX
//			6:3.TOUTPS<3:0>:��ʱ��2������Ƶ��ѡ��
//			2.TMR2ON: �򿪶�ʱ��2
//			1:0.T2CKPS<1:0>:��ʱ��2����ʱ��Ԥ��Ƶ��ѡ��
		T2CON = (SetTm2Postscaler<<3)|SetTm2Prescaler;
		TM2_CMP = 13;		//��ʱ13us��ʱ��Դ16M��2Tģʽ��4Ԥ��Ƶ��2���Ƶ
		#endif

//		INTCON:�жϿ���
//			7.GIE:ȫ���ж�
//			6.PEIE:�����ж�
//			5.T0IE:��ʱ��0����ж�
//			4.INTE:�ⲿ�ж�
//			3.PAIE: PORTA��ƽ�ж�
//			2.T0IF:��ʱ��0����жϱ�־λ
//			1.INTF: PA2/INT�ⲿ�жϱ�־λ
//			0.PAIF: PORTA ��ƽ�仯�жϱ�־λ
		GIE = ENABLE;
        PEIE = ENABLE;		//�������Ҫ������ȻTM2�ж���Ч
        TM0_F = RESET;
        TM0_E = ENABLE;
        TM1_F = RESET;
        TM1_E = DISABLE;
        TM2_F = RESET;
        TM2_E = DISABLE;

		TM0_ON();
		TM1_OFF();
		TM2_OFF();
		
	}
	
	/*----------------------------------------------------
 *	�������ƣ�DelayUs
 *	���ܣ�   ����ʱ���� --16M-2T--��ſ�1%����.
 *	���������Time ��ʱʱ�䳤�� ��ʱʱ��Time Us
 *	���ز������� 
 ----------------------------------------------------*/
void DelayUs(unsigned char Time)
{
	unsigned char a;
	for(a=0;a<Time;a++)
	{
		NOP();
	}
} 

/*----------------------------------------------------
 *	�������ƣ�DelayMs
 *	���ܣ�   ����ʱ����
 *	���������Time ��ʱʱ�䳤�� ��ʱʱ��Time ms
 *	���ز������� 
 ----------------------------------------------------*/
void DelayMs(unsigned char Time)
{
	unsigned char a,b;
	for(a=0;a<Time;a++)
	{
		for(b=0;b<5;b++)
		{
		 	DelayUs(197);     //��1%
		}
	}
}

/*----------------------------------------------------
 *	�������ƣ�DelayS
 *	���ܣ�   ����ʱ����
 *	���������Time ��ʱʱ�䳤�� ��ʱʱ��Time S
 *	���ز������� 
 ----------------------------------------------------*/
void DelayS(unsigned char Time)
{
	unsigned char a,b;
	for(a=0;a<Time;a++)
	{
		for(b=0;b<10;b++)
		{
		 	DelayMs(100); 
		}
	}
}