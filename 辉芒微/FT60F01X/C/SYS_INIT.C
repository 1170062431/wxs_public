	#include	"SYSCFG.h";
    
	#include "..\H\yy_ir.h"
	#include "..\H\config.h"
	#include "..\H\mcu_sel.h"
    
	void sys_init()
	{
        OSCCON = (OSCCON &0x8F)|(SetFsys<<4);

		IO_RLED_N_out;
		IO_RLED_N_set;
		
		IO_LED_out;
		IO_LED_clr;
		
		IO_IR_TX_out;
		IO_IR_TX_clr;
        
//		WDTCON 寄存器
//			7:5.XXX
//         4:1.WDTPS<3:0>: 看门狗定时器周期选择
//			0.SWDTEN:软件打开/关闭看门狗定时器
		CLRWDT();
        WDTCON = (WDTCON &0xE1)|(SetWdtPrescaler<<1);
//		SWDTEN = ENABLE;
		SWDTEN = DISABLE;
        
//		OPTION 寄存器
//			7.PAPU: PORTA 上拉使能位
//			6.INTEDG:中断沿选择位		***1 = 在 INT 引脚的上升沿中断	***0 = 在 INT 引脚的下降沿中断
//			5.T0CS: Timer0 时钟源选择位	***1 = PA2/T0CKI 引脚的跳变	***0 = 内部指令周期(FOSC/4)
//			4.T0SE: Timer0 时钟源边沿选择位	***1 = 在 PA2/T0CKI 引脚的下降沿递增		***0 = 在 PA2/T0CKI 引脚的上升沿递增
//			3.PSA:预分频器分配位	***1 = 预分频器分配给 WDT		***0 = 预分频器分配给 Timer0 模块
//			2:0.PS<2:0>:预分频比选择位	0-7		***TIMER0分频比:2^1--2^8		***WDT分频比:2^0--2^7
        OPTION = (0B00000000+SetTm0Prescaler);
//		TMR0 = 56;		//256-200，预分频2，定时100us
//		TMR0 = 48;		//256-208，预分频2，定时104us,9600波特率
		TMR0 = 152;		//256-104，预分频4，定时104us,9600波特率

//	       T2CON 寄存器
//			7.XXX
//			6:3.TOUTPS<3:0>:定时器2输出后分频比选择
//			2.TMR2ON: 打开定时器2
//			1:0.T2CKPS<1:0>:定时器2驱动时钟预分频比选择
		T2CON &= (SetTm2Postscaler<<3);
        T2CON &= SetTm2Prescaler;
		TM2_CMP = 52;
        
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
        TM2_F = RESET;
        TM2_E = ENABLE;
		
	}