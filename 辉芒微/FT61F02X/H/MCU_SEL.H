	#ifndef	_MCU_SEL_H_		//FT61F02X
	#define	_MCU_SEL_H_

//	#define PWM1	1		//仅 FT61F023  SOP16 有效
	#define PWM3	1
//	#define PWM4	1
//	#define PWM5	1
//	#define SPI		1
//	#define IIC		1

//  以下为2T模式，4T模式频率减半
//	7 =16 MHz
//	6 =8 MHz 
//	5 =4 MHz(default)
//	4 =2 MHz
//	3 =1 MHz
//	2 =500 kHz
//	1 =250 kHz
//	0 =32 kHz (LFINTOSC)
	#define SetFsys				7		//设定内部振荡器频率
 
//TM0定时100us，接收串口数据（波特率9600），TM2定时13us，生成38K载波及对红外数据的定时
//TM0有一个和看门狗共用的预分频，TM2有单独的预分频和后分频
//假如需要定时 X us ，定时器时钟源为 Y M ，则初始寄存器赋值为 XY ,数大了就分频
	#define SetTm0Prescaler			2		//设置Tm0预分频，范围0-7，对应分频比:2^1--2^8
    
//	#define Set_TM0_Timing_100us()		(TMR0 = 56)		//100us*4M/2分频=200,256-200

	#define SetTm2Postscaler		1		//设置Tm2后分频，范围0-15(1-16分频)
    
//	#define SetTm2Prescaler			0		//设定Tm2预分频1
	#define SetTm2Prescaler			1		//设定Tm2预分频4
//	#define SetTm2Prescaler			2		//设定Tm2预分频16

//	#define Set_TM2_Timing_13us()		(PR2 = 52)		//13us*4M/1后分频/1预分频=52

	#define SetWdtPrescaler			10	//看门狗定时器周期选择,范围0-15(32-65535),10的时候约为1s
    
	#define TM0_E		T0IE
	#define TM0_F		T0IF
    #define TM0_CNT		TMR0
    
	#define TM0_ON()	(T0IF = 0,T0IE = 1)
    #define TM0_OFF()	(T0IE = 0,T0IF = 0)
	
	#define TM1_E		TMR1IE
	#define TM1_F		TMR1IF
    
 	#define TM1_ON()	(TMR1ON = 1)
    #define TM1_OFF()	(TMR1ON = 0)

	#define TM2_E		TMR2IE
	#define TM2_F		TMR2IF
    #define TM2_CMP		PR2
    
	#define TM2_ON()	(TMR2ON = 1)
    #define TM2_OFF()	(TMR2ON = 0)

	#endif