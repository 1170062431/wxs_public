	#include "SYSCFG.h"
	#include "..\h\config.h"
	#include "..\h\mcu_sel.h"
	#include "..\h\user_project.h"

	#ifdef PWM1
	/*-------------------------------------------------
	 *  函数名：pwm_duty_count
	 *	功能：  将十位pwm_d的值赋值给CCPR1L:CCP1CON<5:4>
	 *  输入：  无
	 *  输出：  无
	 --------------------------------------------------*/	
	void pwm_duty_count (void)  
	{    
		unsigned int  lsb22;  
		unsigned char lsb23;            	     	   
		lsb22 = (unsigned char) pwm_d & 0B00000011;
		CCP1CON =  CCP1CON & 0B11001111;
		lsb22 <<= 4;
		lsb23 = (unsigned char)lsb22; 
		CCP1CON =  CCP1CON | lsb23; //赋值10Bit PWM脉冲宽度的低2位LSB
		lsb22 = pwm_d >> 2; 		//赋值10Bit PWM脉冲宽度的高8位MSB
		lsb23 = (unsigned char)lsb22; 
		CCPR1L = lsb23;  
	}
	#endif
	
	/*-------------------------------------------------
	 *  函数名：PWM_INITIAL
	 *	功能：  PWM初始化
	 *  输入：  无
	 *  输出：  无
	 --------------------------------------------------*/
	void PWM_INITIAL (void) 
	{
		//PWM1
		/*   说明：  芯片工作在PWM增强模式下,P1A(PC5) 
		*			引脚均输出20KHZ占空比渐增渐减的波形
		*			P1B,P1C,P1D,PWM引脚为普通I/O口
		*
		*              FT61F023  SOP16 
		*              ---------------
		*  VDD---------|1(VDD)  (VSS)16|--------GND     
		*  NC----------|2(PA7)  (PA0)15|---------NC 
		*  NC----------|3(PA6)  (PA1)14|---------NC
		*  NC----------|4(PA5)  (PA2)13|---------NC
		*  P1C---------|5(PC3)  (PA3)12|---------NC
		*  PID---------|6(PC2)  (PC0)11|---------NC
		*  NC----------|7(PA4)  (PC1)10|---------NC
		*  P1A---------|8(PC5)  (PC4)09|--------P1B
		*			   ---------------
		*/
		
		#ifdef PWM1
		//输入：  SET_PR2:周期
		//PWM周期 = (SET_PR2+1)*2*(1/Fosc)*T2分频比值
		
		MSCKCON = 0B00000000; 		//Bit6->0,禁止PA4，PC5稳压输出
		                            //Bit5->0为TIMER2时钟为Fosc ; 1为TIMER2时钟为32MHZ
						   			//Bit4->0,禁止LVR  
		T2CON = 0B00000000;   		//Bit(1:0)=00;T2分频比为1:1
		/*
		//MSCKCON->5Bit=1时使用如下计算公式***************************
		PR2 = 15; 					//设置PWM的周期 = (PR2+1)*4*(1/Fosc*2)*T2分频比值
				                    //Tpwm = (15+1)*2*(1/16000000*2)*1 = 8us = 125KHZ
		*/
		//MSCKCON->5Bit=0时使用如下计算公式***************************
		PR2 = SET_PR2; //31			//设置PWM的周期 = (PR2+1)*2*(1/Fosc)*T2分频比值
				                    //Tpwm = (199+1)*2*(1/16000000)*1 = 50us = 20KHZ
		//CCP1CON = 0B10001100; 	//Bit(7:6)=10;P1A,P1B半桥输出带死区
						   			//Bit(5:4)=00;10Bit PWM占空比低2位
						   			//Bit(3:0)=1100;PWM模式，P1A和P1B为高电平有效
		CCP1CON = 0B10001101; 		//Bit(7:6)=00;P1A单输出,P1B,P1C,P1D位普通I/O口
						   			//Bit(5:4)=00;10Bit PWM占空比低2位
						   			//Bit(3:0)=1101;PWM模式，P1A高电平有效,P1B低电平有效

		pwm_duty_count();      		//PWM占空比计算 占空比pwm_d/((PR2+1)*4)

		PWM1CON = 0B10000001; 		//Bit7=1,自动关闭时PWM自动重启
						   			//死区时间=Bit<6:0>*(1/Fosc)*2
						   			//=1*(1/16000000)*2=0.125ns
		ECCPAS = 0B00001111;  		//Bit(6:4)=000,禁止自动关闭
						   			//Bit(3:2)=11,P1A,P1C关闭时为三态
						   			//Bit(1:0)=11,P1B,P1D关闭时为三态
		//PWM1AUX = 0B10000011; 	//Bit7=1,使能PWM辅助功能
						   			//Bit6=0,使能PWM连续输出
						   			//Bit5:2=0000,P1C,P1D,P1E,P1F引脚为IO
						   			//Bit1:0=11,P1A,P1B为半桥PWM输出
		PWM1AUX = 0B10000000; 		//Bit7=1,使能PWM辅助功能
						   			//Bit6=0,使能PWM连续输出
						   			//Bit5:2=0011,P1C,P1D为半桥PWM输出
						   			//Bit1:0=11,P1A,P1B,P1E,P1F引脚为IO
		TMR2IF = 0;           		//清T2中断标志位  
		//TMR2ON = 1;           	//使能开启T2 		
		#endif
		
	//PWM345
	/*               FT61F023  SOP16 
	*               ---------------
	*  VDD---------|1(VDD)  (VSS)16|--------GND     
	*  NC----------|2(PA7)  (PA0)15|---------NC 
	*  NC----------|3(PA6)  (PA1)14|---------NC
	*  NC----------|4(PA5)  (PA2)13|---------NC
	*  PWM4--------|5(PC3)  (PA3)12|---------NC
	*  PWM5--------|6(PC2)  (PC0)11|---------NC
	*  NC----------|7(PA4)  (PC1)10|---------NC
	*  NC----------|8(PC5)  (PC4)09|-------PWM3
	*			    ---------------
	*/
	
		#ifdef PWM3
	//	PWM3CR0 寄存器
	//	7.P3INTS:PWM3 中断选择位
	//		***1 = TMR3 计数值和 PR3 匹配时产生中断
	//		***0 = TMR3 计数值溢出时产生中断
	//	6:4.P3PER[2:0]:PWM3 周期位选择位
	//		***000-4位
	//		***001-5位
	//		***010-6位
	//		***011-8位
	//		***100-9位
	//		***101-10位
	//		***110-11位
	//		***111-12位
	//	3:1.P3CKSRC[2:0]:TIMER3/PWM3 时钟选择位
	//		***000-系统时钟SYSCLK/(T3CKDIV+1)
	//		***001-内部RC快时钟/(T3CKDIV+1)
	//		***010-T0CK/(T3CKDIV+1)
	//		***011-T1CK/(T3CKDIV+1)
	//		***100-内部RC快时钟/(T3CKDIV+1),同时 PWM3 输出低电平
	//		***101-内部RC快时钟/(T3CKDIV+1),同时 PWM3 输出高电平
	//		***110-内部RC快时钟/(T3CKDIV+1),同时 PWM3 根据高脉冲调制P3CK
	//		***111-内部RC快时钟/(T3CKDIV+1),同时 PWM3 根据低脉冲调制P3CK
	//	0.P3BZR:PWM/BUZZER 选择
	//		***1 = BUZZER
	//		***0 = PWM
	
		PWM3CR0 = 0B00110010;
	
	//	PWM3CR1 寄存器
	//	7.P3EN:TMR3/PWM3 工作模式
	//		***1 = TMR3 为 PWM/BUZZER 模式
	//		***0 = TMR3 为定时器模式
	//	6.P3POL:PWM3 输出极性选择
	//		***1 = PWM3 为低电平有效
	//		***0 = PWM3 为高电平有效
	//	5:3.TMR3PS[2:0]:PWM3 预分频比设置位
	//		***000-1:1
	//		***001-1:2
	//		***010-1:4
	//		***011-1:8
	//		***100-1:16
	//		***101-1:32
	//		***110-1:64
	//		***111-1:128
	//	2.TMR3ON:定时器 3 使能位
	//	1.TMR3IE:定时器 3 中断使能位
	//	0.TMR3IF:定时器 3 中断标志位
		PWM3CR1 = 0B10000000;
	
	//	TMR3H 寄存器	
	//	7:4.TMR3H[7:0]:TIMER3 计数结果高 4 位
	//	3:0.PR3H[3:0]:PWM3 匹配寄存器 PR3 高 4 位
		TMR3H=0;

	//	T3CKDIV 寄存器
	//	7:0.T3CKDIV[7:0]:TMR3 时钟频率为 FT3CK/(T3CKDIV+1)
		T3CKDIV = 30; 			//周期 = 预分频2^0*八位周期2^8*[(T3CKDIV+1)/16000000] =(T3CKDIV+1)*16us
				  				//31*16us = 0.496ms ≈ 2KHz
	//	PR3L 寄存器	
	//	7:0.PR3L[7:0]:PWM3 匹配寄存器 PR3 低 8 位
		PR3L = 128;
		//-------------------------------
		#endif

		#ifdef PWM4
		PWM4CR0 = 0B00110010; 	//Bit7 禁止中断
								//Bit6:4 周期位选择011:8位
								//Bit3:1 时钟选择001:内部RC快时钟/(T3CKDIV+1)
								//Bit0	PWM 输出	
	#if	PWM4_OUT					
	    //PWM4CR1 = 0;
		PWM4CR1 = 0B10000000;
	#else
		PWM4CR1 = 0B11000000;
	                   			//Bit7 =1，TMR4为PWM/BUZZER模式
		               			//Bit6 =0，PWM4为高电平有效
		               			//Bit5:3 =000，PWM4预分频比设置为1:1
		               			//Bit2 =0,暂关TMR4
		               			//Bit1 =0,禁止TMR4中断
		               			//Bit0 =0，TMR3中断标志位只读
	#endif
	    TMR4H=0;
		
		T4CKDIV = 62;			//周期 = 2^0*2^8*[(T4CKDIV+1)/16000000] =(T4CKDIV+1)*16us
					 			//63*16us = 1.008ms ≈ 1KHz
		PR4L = 128;
		//-------------------------------
		#endif

		#ifdef PWM5
		PWM5CR0 = 0B00110010; 	/*Bit7	禁止中断
					 			  Bit6:4 周期位选择011:8位
								  Bit3:1 时钟选择001:内部RC快时钟/(T3CKDIV+1)
								  Bit0	PWM 输出
								*/	
	#if	PWM5_OUT
	    //PWM5CR1 = 0;
		PWM5CR1 = 0B10000000;
	#else
		PWM5CR1 = 0B11000000;
	                  		 	/*Bit7 =1，TMR5为PWM/BUZZER模式
		              		 	  Bit6 =0，PWM5为高电平有效
		              		 	  Bit5:3 =000，PWM5预分频比设置为1:1
		              		 	  Bit2 =0,暂关TMR5
		              		 	  Bit1 =0,禁止TMR5中断
		              		 	  Bit0 =0，TMR5中断标志位只读
		              		 	*/
	#endif
	    TMR5H=0;
		T5CKDIV = 124;			//周期 = 2^0*2^8*[(T3CKDIV+1)/16000000] =(T3CKDIV+1)*16us
					  			// 125*16us = 2ms = 500Hz
		PR5L = 128;
		//-------------------------------
		#endif
	}

	//pwm_p:周期，pwm_fre:频率-(244-31250),pwm_d:占空比-(0-100)
	void setPwm3(u8 pwm3_on,u16 pwm_fre,u16 pwm_d)
	{
		if(pwm3_on == PWM_ON)
		{
			T3CKDIV = (u8)(62500/pwm_fre-1);
			PR3L = (u8)(pwm_d*255/100);
			TMR3ON = 1;
			TRISC4 = 0;		//PC4
		}
		else if(pwm3_on == PWM_OFF)
		{
			PR3L = 0;
		#if	PWM4_OUT
			while(PC4);
		#else
			while(!PC4);
		#endif
			TMR3ON = 0;
		}
	}
	
	//pwm_p:周期，pwm_fre:频率-(244-31250),pwm_d:占空比-(0-100)
	void setPwm4(u8 pwm4_on,u16 pwm_fre,u16 pwm_d)
	{
		if(pwm4_on == PWM_ON)
		{
			T4CKDIV = (u8)(62500/pwm_fre-1);
			PR4L = (u8)(pwm_d*255/100);
			TMR4ON = 1;
			TRISC3 = 0;		//PC3
		}
		else if(pwm4_on == PWM_OFF)
		{
			PR4L = 0;
		#if	PWM4_OUT
			while(PC3);
		#else
			while(!PC3);
		#endif
			TMR4ON = 0;
		}
	}