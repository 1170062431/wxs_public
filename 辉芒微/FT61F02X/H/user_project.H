//输入AD检测分压电阻4.7K/1K，LED电流反馈AD检测电阻0.2R*2=0.1R

	#ifndef	_USER_PROJECT_H_
	#define	_USER_PROJECT_H_
	
	#include "..\H\config.h"
	#include "..\h\buzzer.h"
	
	#define DEBUG				1
	#define BUZZER_EN			1
	//AD_V_REF = 2V
	#define AD_8V_6_2V			557			//6.2V_1.088V-317，低于此值以干电池模式工作
	#define AD_8V_3_5V			314			//3.5V_0.614V-179,低于此值不工作
	#define AD_6W_50_MIN		6			//低电量时最小电流，小于此值停止工作
	#define AD_6W_100_MIN		10			//低电量时最小电流，小于此值停止工作
	#define AD_5W_100_MIN		10			//低电量时最小电流，小于此值停止工作
	
	#define SET_TIME2SLEEP		500			//ms
	
	#define SET_LEDON_DUTY_MIN	2
	#define SET_LEDON_DUTY_MAX	250
	
	#define SET_ADJ_ADREF_T		1			//设置AD参考值更新时间，单位s
	
	#define SET_ADJ_DUTY_T_MIN	2			//快速调整占空比时间间隔，单位ms
	#define SET_ADJ_DUTY_T_MID	1000		//中速调整占空比时间间隔，单位ms
	#define SET_ADJ_DUTY_T_MAX	5000		//慢速调整占空比时间间隔，单位ms
	
	#define SET_AD_LED_JC_NUM	128			//设置LED的AD检测次数
	#define SET_AD_INPUT_JC_NUM	64			//设置VIN的AD检测次数
	
	#define SET_AD_VIN_VAL_MAX	808			//设置AD最大有效值-VIN_9V
	#define SET_AD_VIN_VAL_MIN	296			//设置AD最小有效值-VIN_3.3V
	#define SET_AD_VLED_VAL_MAX	102			//设置AD最大有效值-VLED_2A_0.2V
	#define SET_AD_VLED_VAL_MIN	10			//设置AD最小有效值
	
	#define PWM_ON				1
	#define PWM_OFF				0
	
	#define PWM3_H2L_DUTY		PR3L	//0-255
	#define PWM4_H2L_DUTY		PR4L	//0-255
	
	#define PWM3_OUT			1		//PWM3输出有效电平1
	#define PWM4_OUT			0		//PWM4输出有效电平0	#define PWM5_OUT			1		//PWM5输出有效电平1
	
	#define K_NON				0
	#define K_MODE				1

	enum pro_mode
	{
		MODE_IDLE = 0,
		MODE_WORK
	};
	
	#define IO_RLED				PA7
	#define IO_RLED_out			TRISA7 = 0
	#define IO_RLED_int			TRISA7 = 1
	#define IO_RLED_pu_set		WPUA7 = 1
	#define IO_RLED_pu_clr		WPUA7 = 0
	#define IO_RLED_set			PA7 = 1
	#define IO_RLED_clr			PA7 = 0
	
#ifdef DEBUG	
	#define IO_YLED				PA6
	#define IO_YLED_out			TRISA6 = 0
	#define IO_YLED_int			TRISA6 = 1
	#define IO_YLED_pu_set		WPUA6 = 1
	#define IO_YLED_pu_clr		WPUA6 = 0
	#define IO_YLED_set			PA6 = 1
	#define IO_YLED_clr			PA6 = 0
#else	
	#define IO_YLED
	#define IO_YLED_out
	#define IO_YLED_int
	#define IO_YLED_pu_set
	#define IO_YLED_pu_clr
	#define IO_YLED_set
	#define IO_YLED_clr
#endif

	#define IO_GLED				PA4
	#define IO_GLED_out			TRISA4 = 0
	#define IO_GLED_int			TRISA4 = 1
	#define IO_GLED_pu_set		WPUA4 = 1
	#define IO_GLED_pu_clr		WPUA4 = 0
	#define IO_GLED_set			PA4 = 1
	#define IO_GLED_clr			PA4 = 0

	#define IO_BZ_H			PC3
	#define IO_BZ_H_out		TRISC3 = 0
	#define IO_BZ_H_int		TRISC3 = 1
	#define IO_BZ_H_pu_set	WPUC3 = 1
	#define IO_BZ_H_pu_clr	WPUC3 = 0
	#define IO_BZ_H_set		PC3 = 1
	#define IO_BZ_H_clr		PC3 = 0

	#define IO_BZ_L			PC2
	#define IO_BZ_L_out		TRISC2= 0
	#define IO_BZ_L_int		TRISC2 = 1
	#define IO_BZ_L_pu_set	WPUC2 = 1
	#define IO_BZ_L_pu_clr	WPUC2 = 0
	#define IO_BZ_L_set		PC2 = 1
	#define IO_BZ_L_clr		PC2 = 0

	#define IO_HEAT			PC4			//PWM3
	#define IO_HEAT_out		TRISC4 = 0
	#define IO_HEAT_int		TRISC4 = 1
	#define IO_HEAT_set		PC4 = 1
	#define IO_HEAT_clr		PC4 = 0

	#define AN_AD_Tsense			5			//AN5
	#define IO_AD_Tsense			PC1			//AN5
	#define IO_AD_Tsense_out		TRISC1 = 0
	#define IO_AD_Tsense_int		TRISC1 = 1
	#define IO_AD_Tsense_pu_set		WPUC1 = 1
	#define IO_AD_Tsense_pu_clr		WPUC1 = 0
//	#define IO_AD_Tsense_set		PC1 = 1
//	#define IO_AD_Tsense_clr		PC1 = 0

	#define IO_PC0				PC0
	#define IO_PC0_out			TRISC0 = 0
	#define IO_PC0_int			TRISC0 = 1
	#define IO_PC0_pu_set		WPUC0 = 1
	#define IO_PC0_pu_clr		WPUC0 = 0
	#define IO_PC0_set			PC0 = 1
	#define IO_PC0_clr			PC0 = 0

	#define AN_AD_Isense			3			//AN3
	#define IO_AD_Isense			PA3			//AN3
	#define IO_AD_Isense_out		TRISA3 = 0
	#define IO_AD_Isense_int		TRISA3 = 1
	#define IO_AD_Isense_pu_set		WPUA3 = 1
	#define IO_AD_Isense_pu_clr		WPUA3 = 0
//	#define IO_AD_Isense_set		PA3 = 1
//	#define IO_AD_Isense_clr		PA3 = 0
	
	#define IO_KEY				PA2
	#define IO_KEY_out			TRISA2= 0
	#define IO_KEY_int			TRISA2 = 1
	#define IO_KEY_pu_set		WPUA2 = 1
	#define IO_KEY_pu_clr		WPUA2 = 0
	#define IO_KEY_set			PA2 = 1
	#define IO_KEY_clr			PA2 = 0

	#define IO_PA1				PA1
	#define IO_PA1_out			TRISA1 = 0
	#define IO_PA1_int			TRISA1 = 1
	#define IO_PA1_pu_set		WPUA1 = 1
	#define IO_PA1_pu_clr		WPUA1 = 0
	#define IO_PA1_set			PA1 = 1
	#define IO_PA1_clr			PA1 = 0

	#define IO_PA0				PA0
	#define IO_PA0_out			TRISA0 = 0
	#define IO_PA0_int			TRISA0 = 1
	#define IO_PA0_pu_set		WPUA0 = 1
	#define IO_PA0_pu_clr		WPUA0 = 0
	#define IO_PA0_set			PA0 = 1
	#define IO_PA0_clr			PA0 = 0
	
	#define IO_PA5				PA5
	#define IO_PA5_out			TRISA5 = 0
	#define IO_PA5_int			TRISA5 = 1
	#define IO_PA5_pu_set		WPUA5 = 1
	#define IO_PA5_pu_clr		WPUA5 = 0
	#define IO_PA5_set			PA5 = 1
	#define IO_PA5_clr			PA5 = 0
	
	#define IO_PC5				PC5
	#define IO_PC5_out			TRISC5 = 0
	#define IO_PC5_int			TRISC5 = 1
	#define IO_PC5_pu_set		WPUC5 = 1
	#define IO_PC5_pu_clr		WPUC5 = 0
	#define IO_PC5_set			PC5 = 1
	#define IO_PC5_clr			PC5 = 0
	
	extern FLAG Time_FLAG;
	extern FlagStatus F_feedDog,F_keyLJ;
	extern u8 keyBuff,keySta,keyBackUp,keyCode;
	extern u8 mode,T_LedOn_10s;
	extern u8 ReadAPin,C_sleep;
	extern u8 AD_Tsense,AD_Isense;
    
	void POWER_INITIAL(void);
	void COMP_INITIAL();
	void DelayUs(unsigned char Time);
	void DelayMs(unsigned char Time);
	void DelayS(unsigned char Time);
	void ADC_INITIAL(void);
	unsigned int GET_ADC_DATA (unsigned char AN_CH);
	u16 GET_ADC_DATA_VER (u8 AN_CH,u8 AD_num,u16 AD_val_min,u16 AD_val_max);
	void PWM_INITIAL(void);
	void setPwm3(u8 pwm3_on,u16 pwm_fre,u16 pwm_d);
	unsigned char EEPROMread(unsigned char EEAddr);
	void EEPROMwrite(unsigned char EEAddr,unsigned char Data);

	void turnToModeIdle(void);
	void turnToModeWork(void);
	void keyScan(void);
	void keyAction(void);
	
	#endif