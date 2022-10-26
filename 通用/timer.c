#include "timer.h"
#include "basic_include.h"

void timer0Init()
{
	/* 配置定时器0 */
	TIM0_CR  = 0x06;			// 选择系统时钟16MHz/4分频
	TIM0_ARR = 250;				// 自动重装周期250，定时125us
	TIM0_IE  = 0x01;			// 打开TIMER0中断
	TIM0_CR  = TIM0_CR | 0x01;	// 使能TIMER0
}

void timer1Init()
{
	/* 配置定时器1 */
	TIM1_CR      = 0x00;                // 定时器1向上计数，锯齿波模式
	TIM1_FCONR   = 0x0f;                // TIMER1时钟源选择系统时钟，预分频16分频

	TIM1_PCONRA    = 0x03;             	// 使能TIMER1 TIM1_CHA通道捕捉，上升沿捕捉
	TIM1_PCONRB    = 0x03;             	// 使能TIMER1 TIM1_CHB通道捕捉，上升沿捕捉
	TIM1_IE        = 0x0c;             	// 使能TIMER1 捕捉和比较中断

	TIM1_ARRH    = 10000/256;           // 计数溢出值10ms
	TIM1_ARRL    = 10000%256;
	TIM1_IE      = 0x01;                // 使能上溢中断
	TIM1_CR      = TIM1_CR|0x01;        // 使能TIMER1
}

