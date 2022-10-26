#include "pwm.h"

#if(PWM1A_EN|PWM1B_EN|PWM2A_EN|PWM2B_EN)
//-------------------------------------------------------------------
//函数名：pwmInit()
//参数：无
//输出：无
//-------------------------------------------------------------------
void pwmInit()
{
#if(PWM1A_EN|PWM1B_EN)
	TIM1_ARRH = 100/256; 	// 配置TIMER1计数器计数周期100us 
	TIM1_ARRL = 100%256;
	
	#if PWM1A_EN
	PT1_GOE |= PWM_CH_TM1_A;
	
	TIM1_GCMARH = 0/256;	// TIM1_CHA输出比0%
	TIM1_GCMARL = 0%256;
	
	TIM1_PCONRA = 0x10;  	// 比较输出初始值为0，打开比较模式，计数值小于比较值为 1，大于为 0
//	TIM1_PCONRA = 0x50;  	// 比较输出初始值为0，打开比较模式，比较值相等的时候将输出取反
//	TIM1_PCONRA = 0xd0;  	// 比较输出初始值为1，打开比较模式，比较值相等的时候将输出取反
//	TIM1_PCONRA = 0xd0;  	// 比较输出初始值为1，打开比较模式，比较值相等的时候将输出取反
	#endif

	#if PWM1B_EN
	PT1_GOE |= PWM_CH_TM1_B;
	
	TIM1_GCMBRH = 0/256;	// TIM1_CHA输出比0%
	TIM1_GCMBRL = 0%256;
	
	TIM1_PCONRB = 0x10;  	// 比较输出初始值为0，打开比较模式，计数值小于比较值为 1，大于为 0
//	TIM1_PCONRB = 0x50;  	// 比较输出初始值为0，打开比较模式，比较值相等的时候将输出取反
//	TIM1_PCONRB = 0xd0;  	// 比较输出初始值为1，打开比较模式，比较值相等的时候将输出取反
//	TIM1_PCONRB = 0xd0;  	// 比较输出初始值为1，打开比较模式，比较值相等的时候将输出取反
	#endif
	
	TIM1_CR = 0x01; 		// 配置TIMER1向上计数，锯齿波计数模式
//	TIM1_CR = 0x02; 		// 配置TIMER1向上计数，三角波模式A

	TIM1_FCONR = 0x0f;		// 配置TIMER1时钟源来自SYSCLK，预分频16分频
	
	TIM1_DTUA = 0;			// 设置死区为0个TIMER1计数周期， 0死区
//	TIM1_DTUA = 5;			// 设置死区为5个TIMER1计数周期， 5us死区

	TIM1_DTR = 0x00;		// 硬件互补输出关闭
//	TIM1_DTR = 0x14;		// 硬件互补输出打开，使能TIM1_CHB死区输出，死区输出有IO1_DR[7]决定
	

	TIM1_IE = 0x00;  		// 使能TIM1_CHA和TIM1_CHB比较中断
//	TIM1_IE = 0x0c;  		// 使能TIM1_CHA和TIM1_CHB比较中断

	TIM1_CR = TIM1_CR|0x01;	// 使能定时器1
#endif

#if(PWM2A_EN|PWM2B_EN)
	TIM2_ARRH = 100/256; 	// 配置TIMER1计数器计数周期100us 
	TIM2_ARRL = 100%256;
	
	#if PWM2A_EN
	PT2_GOE |= PWM_CH_TM2_A;
	
	TIM2_GCMARH = 0/256;	// TIM2_CHA输出比0%
	TIM2_GCMARL = 0%256;
	
	TIM2_PCONRA = 0x10;  	// 比较输出初始值为0，打开比较模式，计数值小于比较值为 1，大于为 0
//	TIM2_PCONRA = 0x50;  	// 比较输出初始值为0，打开比较模式，比较值相等的时候将输出取反
//	TIM2_PCONRA = 0xd0;  	// 比较输出初始值为1，打开比较模式，比较值相等的时候将输出取反
//	TIM2_PCONRA = 0xd0;  	// 比较输出初始值为1，打开比较模式，比较值相等的时候将输出取反
	#endif

	#if PWM2B_EN
	PT2_GOE |= PWM_CH_TM2_B;
	
	TIM2_GCMBRH = 0/256;	// TIM2_CHA输出比0%
	TIM2_GCMBRL = 0%256;
	
	TIM2_PCONRB = 0x10;  	// 比较输出初始值为0，打开比较模式，计数值小于比较值为 1，大于为 0
//	TIM2_PCONRB = 0x50;  	// 比较输出初始值为0，打开比较模式，比较值相等的时候将输出取反
//	TIM2_PCONRB = 0xd0;  	// 比较输出初始值为1，打开比较模式，比较值相等的时候将输出取反
//	TIM2_PCONRB = 0xd0;  	// 比较输出初始值为1，打开比较模式，比较值相等的时候将输出取反
	#endif
	
	TIM2_CR = 0x01; 		// 配置TIMER1向上计数，锯齿波计数模式
//	TIM2_CR = 0x02; 		// 配置TIMER1向上计数，三角波模式A
	
	TIM2_FCONR = 0x0f;		// 配置TIMER1时钟源来自SYSCLK，预分频16分频
	
	TIM2_DTUA = 0;			// 设置死区为0个TIMER1计数周期， 0死区
//	TIM2_DTUA = 5;			// 设置死区为5个TIMER1计数周期， 5us死区

	TIM2_DTR = 0x00;		// 硬件互补输出关闭
//	TIM2_DTR = 0x14;		// 硬件互补输出打开，使能TIM2_CHB死区输出，死区输出有IO1_DR[7]决定

	TIM1_IE = 0x00; 		// 使能TIM1_CHA和TIM1_CHB比较中断
//	TIM1_IE = 0x0c; 		// 使能TIM1_CHA和TIM1_CHB比较中断

	TIM2_CR = TIM2_CR|0x01;	// 使能定时器1
#endif
}

//---------------------------------------------------------------------------------------
//函数名：setPwm(uchar chanel,uint pwm_p,uchar pwm_d)
//参数：chanel-pwm通道（PWM_CH_TMx_x），pwm_p-周期100us~10000us，对应频率10K~100，pwm_d-占空比0~pwm_p
//输出：无
//---------------------------------------------------------------------------------------
void setPwm(uchar chanel,uint pwm_p,uchar pwm_d)
{
	switch(chanel)
	{
	case PWM_CH_TM1_A:
		TIM1_ARRH = pwm_p>>8; // 配置TIMER1计数器计数周期100us 
		TIM1_ARRL = pwm_p;			//pwm_p%256
		TIM1_GCMARH = pwm_d>>8;		// TIM1_CHA输出比50%
		TIM1_GCMARL = pwm_d;		//pwm_d%256
		break;
	case PWM_CH_TM1_B:
		TIM1_ARRH = pwm_p>>8; // 配置TIMER1计数器计数周期100us 
		TIM1_ARRL = pwm_p;			//pwm_p%256
		TIM1_GCMBRH = pwm_d>>8;		// TIM1_CHA输出比50%
		TIM1_GCMBRL = pwm_d;		//pwm_d%256
		break;
	case PWM_CH_TM2_A:
		TIM2_ARRH = pwm_p>>8; // 配置TIMER1计数器计数周期100us 
		TIM2_ARRL = pwm_p;			//pwm_p%256
		TIM2_GCMARH = pwm_d>>8;		// TIM1_CHA输出比50%
		TIM2_GCMARL = pwm_d;		//pwm_d%256
		break;
	case PWM_CH_TM2_B:
		TIM2_ARRH = pwm_p>>8; // 配置TIMER1计数器计数周期100us 
		TIM2_ARRL = pwm_p;			//pwm_p%256
		TIM2_GCMBRH = pwm_d>>8;		// TIM1_CHA输出比50%
		TIM2_GCMBRL = pwm_d;		//pwm_d%256
		break;
	default:
		break;
	}
}

#endif
