
	#include "SYSCFG.h";
	#include "..\H\user_project.h"
	#include "..\H\config.h"
	#include "..\H\mcu_sel.h"
    
	void POWER_INITIAL (void)
	{
        OSCCON = (OSCCON & 0x8F)|(SetFsys << 4);
		
		INTCON = 0;  			//暂禁止所有中断
		PORTA = 0B00000000; 
		TRISA = 0B11111111;		//PA全部输入 
		
		PORTC = 0B00000000; 
		TRISC = 0B11111111;		//PC全部输入
		
        WPUA = 0B00000000;    	//禁止所有PA口上拉
		WPUC = 0B00000000;    	//禁止所有PC口上拉
		MSCKCON = 0B00000000;	//Bit6->0,禁止PA4，PC5稳压输出
					  			//Bit5->0,TIMER2时钟为Fosc
					  			//Bit4->0,禁止LVR          
		CMCON0 = 0B00000000; 	//关闭比较器，CxIN为数字IO口
		ANSEL = 0B10101000; 	//AN0~7,1 = 模拟输入，0 = 数字 IO

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
		
//		WDTCON 寄存器
//			7:5.XXX
//      	4:1.WDTPS<3:0>: 看门狗定时器周期选择
//			0.SWDTEN:软件打开/关闭看门狗定时器
		CLRWDT();
        WDTCON = (WDTCON &0xE1)|(SetWdtPrescaler<<1);
//		SWDTEN = ENABLE;
		SWDTEN = DISABLE;
        
//		OPTION 寄存器（Timer0）
//			7.PAPU: PORTA 上拉使能位
//			6.INTEDG:中断沿选择位		***1 = 在 INT 引脚的上升沿中断	***0 = 在 INT 引脚的下降沿中断
//			5.T0CS: Timer0 时钟源选择位	***1 = PA2/T0CKI 引脚的跳变	***0 = 内部指令周期(FOSC/4)
//			4.T0SE: Timer0 时钟源边沿选择位	***1 = 在 PA2/T0CKI 引脚的下降沿递增		***0 = 在 PA2/T0CKI 引脚的上升沿递增
//			3.PSA:预分频器分配位	***1 = 预分频器分配给 WDT		***0 = 预分频器分配给 Timer0 模块
//			2:0.PS<2:0>:预分频比选择位	0-7		***TIMER0分频比:2^1--2^8		***WDT分频比:2^0--2^7
        OPTION = (0B00000000+SetTm0Prescaler);
//		TMR0 = 56;		//256-200，4T预分频2，定时100us
//		TMR0 = 48;		//256-208，4T预分频2，定时104us,9600波特率
//		TMR0 = 156;		//256-100，2T预分频8，定时100us
//		TMR0 = 152;		//256-104，2T预分频8，定时104us,9600波特率
		TMR0 = 131;		//256-125，2T预分频8，定时125us,drive 4K buzzer

//		T1CON 寄存器（Timer1）
//			7.T1GINV:TIMER1 门控翻转位***1 = Timer1 门控为高电平有效（门控为高电平时 Timer1 计数）***0 = Timer1 门控为低电平有效（门控为低电平时 Timer1 计数）
//			6.TMR1GE:Timer1 门控使能位(2),TMR1ON = 0：此位被忽略,TMR1ON = 1：***1 = Timer1 在 Timer1 门控不活动时打开***0 = Timer1 打开
//			5:4.T1CKPS[1:0]:Timer1 输入时钟预分频比选择位	***11=8分频，10=4分频，01=2分频，00=1分频
//			3.T1OSCEN:LP 振荡器使能控制位，如果无 CLKOUT 振荡器的 INTOSC 处于激活状态：		***1 = LP 振荡器被使能用于 Timer1 时钟***0 = LP 振荡器关闭
//			2.T1SYNC:Timer1 外部时钟输入同步控制位，TMR1CS = 1:***1 = 不同步外部时钟输入	***0 = 同步外部时钟输入,TMR1CS = 0:此位被忽略。Timer1 使用内部时钟
//			1.TMR1CS:Timer1 时钟源选择位***1 = T1CK1 引脚（上升沿）的外部时钟	***0 = 内部时钟（指令时钟）
//			0.TMR1ON:Timer1 使能位
		T1CON = 0B00000000; 
//		T1SYNC=16M/2T=8M=0.125US
//		定时500US=>TMR1=8000*0.125S=1ms，
//		初值=65536-8000=57535=>0XE0BF
		TMR1L = 0XBF;  			//需要在中断里重新赋初始值
		TMR1H = 0XE0;  			//需要在中断里重新赋初始值
		
		#ifndef	PWM1
//	    T2CON 寄存器(Timer2)
//			7.XXX
//			6:3.TOUTPS<3:0>:定时器2输出后分频比选择
//			2.TMR2ON: 打开定时器2
//			1:0.T2CKPS<1:0>:定时器2驱动时钟预分频比选择
		T2CON = (SetTm2Postscaler<<3)|SetTm2Prescaler;
		TM2_CMP = 13;		//定时13us，时钟源16M，2T模式，4预分频，2后分频
		#endif

//		INTCON:中断控制
//			7.GIE:全局中断
//			6.PEIE:外设中断
//			5.T0IE:定时器0溢出中断
//			4.INTE:外部中断
//			3.PAIE: PORTA电平中断
//			2.T0IF:定时器0溢出中断标志位
//			1.INTF: PA2/INT外部中断标志位
//			0.PAIF: PORTA 电平变化中断标志位
		GIE = ENABLE;
        PEIE = ENABLE;		//这个必须要开，不然TM2中断无效
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
 *	函数名称：DelayUs
 *	功能：   短延时函数 --16M-2T--大概快1%左右.
 *	输入参数：Time 延时时间长度 延时时长Time Us
 *	返回参数：无 
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
 *	函数名称：DelayMs
 *	功能：   短延时函数
 *	输入参数：Time 延时时间长度 延时时长Time ms
 *	返回参数：无 
 ----------------------------------------------------*/
void DelayMs(unsigned char Time)
{
	unsigned char a,b;
	for(a=0;a<Time;a++)
	{
		for(b=0;b<5;b++)
		{
		 	DelayUs(197);     //快1%
		}
	}
}

/*----------------------------------------------------
 *	函数名称：DelayS
 *	功能：   短延时函数
 *	输入参数：Time 延时时间长度 延时时长Time S
 *	返回参数：无 
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