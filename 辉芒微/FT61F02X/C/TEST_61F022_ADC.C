/*  文件名：TEST_61F02x_ADC.C
*	功能：  FT61F02x-ADC功能演示
*   IC:    FT61F023 SOP16
*   晶振：  16M/2T                    
*   说明：  程序根据AN2(PA2)口的电压来调节PWM3P(PC4)的占空比
*			AN2脚电压越高(0-VDD)PWM3P(PC2)占空比越大(2K,0-99%)	
*
*               FT61F023  SOP16 
*               ---------------
*  VDD---------|1(VDD)  (VSS)16|--------GND     
*  NC----------|2(PA7)  (PA0)15|---------NC 
*  NC----------|3(PA6)  (PA1)14|---------NC
*  NC----------|4(PA5)  (PA2)13|--------AN2
*  NC----------|5(PC3)  (PA3)12|---------NC
*  NC----------|6(PC2)  (PC0)11|---------NC
*  NC----------|7(PA4)  (PC1)10|---------NC
*  NC----------|8(PC5)  (PC4)09|-------PWM3
*			    ---------------
*/
#include "SYSCFG.h"
#include "..\h\config.h"
#include "..\h\user_project.h"

/*-------------------------------------------------
 *  函数名:  ADC_INITIAL
 *	功能：  ADC初始化
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
void ADC_INITIAL (void) 
{
	//ADC 时钟频率 <= 250K
	ADCON1 = 0B01100000; 	//DIVS=0,时钟选FOSC
					   		//ADCS[2:0]=110,分频FOSC/64

	//ADCON0 寄存器						
	//7.ADFM:A/D 转换结果格式选择位
	//	v	***1 = 右对齐
	//		***0 = 左对齐           
	//6:5.VCFG[1:0]:参考电压选择位
	//		***11 = VREF 引脚
	//		***10 = 内部 3V 电压
	//	v	***01 = 内部 2V 电压
	//		***00 = VDD
	//4:2.CHS[2:0]:模拟通道选择位
	//		***000 = AN0
	//		***001 = AN1
	//		***010 = AN2
	//		***011 = AN3
	//		***100 = AN4
	//		***101 = AN5
	//		***110 = AN6
	//		***111 =内部 1/4 VDD
	//1.GO/DONE:A/D 转换状态位
	//		***1 = A/D 转换正在进行。将本位置 1 启动一次 A/D 转换。A/D 转换完成时此位由硬件自动清零
	//		***0 = A/D 转换完成/不在进行中
	//0.ADON:ADC 使能位
	//		***1 = 使能 ADC
	//		***0 = 禁止 ADC，不消耗工作电流
	ADCON0 = 0B10111100;
}                      
/*-------------------------------------------------
 *  函数名: GET_ADC_DATA
 *	功能：  读取通道ADC值
 *  输入：  AN_CN 通道序号
 *  输出：  INT类型 10bit AD值(单次采样无滤波)
 --------------------------------------------------*/
unsigned int GET_ADC_DATA (unsigned char AN_CH) 
{ 
	unsigned char ADCON0Buff; 
	unsigned int  tBuffer = 0;
	unsigned int  ADC_DATA=0;
	
	ADON = ENABLE;
	ADCON0Buff = ADCON0 & 0B11100011; 	//清空通道值

	AN_CH <<=2;              
	ADCON0Buff |= AN_CH;   				//(BIT4-BIT2)CHS=010,选择AN2通道      

	ADCON0 = ADCON0Buff; 				//重新加载通道值
    DelayUs(20); 
	GO_DONE = 1;             			//启动ADC 
	while( GO_DONE==1 );    			//等待ADC转换完成

	ADC_DATA =  ADRESH;
	ADC_DATA <<=8;
	ADC_DATA |= ADRESL;      			//10Bit ADC值整合
	tBuffer =  ADC_DATA;
	ADON = DISABLE;
	return  tBuffer;
}

/*-------------------------------------------------
 *  函数名: GET_ADC_DATA
 *	功能：  读取通道ADC值，采样（AD_num+2）次，减去最大最小值取平均,检测异常时返回0
 *  输入：  AN_CN 通道序号，AD_num AD采样次数,AD_val_min AD数值最小有效值,AD_val_max AD数值最大有效值
 *  输出：  INT类型 10bit AD值(单次采样带滤波)
 --------------------------------------------------*/
u16 GET_ADC_DATA_VER (u8 AN_CH,u8 AD_num,u16 AD_val_min,u16 AD_val_max) 
{ 
	u8 i;
	u8 ADCON0Buff; 
	u16 tBuffer = 0;
	u16 ADC_DATA=0;
	u16 AD_ILed_sum = 0;
	u16 AD_ILed_min = 1024;
	u16 AD_ILed_max = 0;
	u8 err_cnt = 0; 

	ADON = ENABLE;
	
	ADCON0Buff = ADCON0 & 0B11100011; 	//清空通道值

	AN_CH <<=2;              
	ADCON0Buff |= AN_CH;   				//选择通道      

	ADCON0 = ADCON0Buff; 				//重新加载通道值
    DelayUs(20); 
	
	for(i=AD_num+2;i>0;i--)
	{
		GO_DONE = 1;             		//启动ADC 
		while(GO_DONE == 1);    		//等待ADC转换完成
	
		ADC_DATA =  ADRESH;
		ADC_DATA <<=8;
		ADC_DATA |= ADRESL;      		//10Bit ADC值整合

		if(ADC_DATA>AD_val_max || ADC_DATA<AD_val_min)
		{
			i++;
			err_cnt++;
			if(err_cnt > 20)
				return 0;
			continue;
		}
		
		if(ADC_DATA < AD_ILed_min)
			AD_ILed_min = ADC_DATA;
		if(ADC_DATA > AD_ILed_max)
			AD_ILed_max = ADC_DATA;
		AD_ILed_sum += ADC_DATA;
	}
	ADC_DATA = (AD_ILed_sum-AD_ILed_min-AD_ILed_max)/AD_num;
	
	tBuffer =  ADC_DATA;
	ADON = DISABLE;
	return  tBuffer;
}
