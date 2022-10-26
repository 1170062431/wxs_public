
#ifndef _USER_PROJECT_H_
#define _USER_PROJECT_H_

#include "audio/ladc_api.h"

#define LOWPOWER_EN			1	//低功耗使能mm，板子硬件不同
#define SET_POWOFF_TIME_S	3	//低功耗时间

#define DISWORK_AT_CHRG_EN	0	//充电禁止工作使能
#define BT_EN				1	//蓝牙使能

#define USER_TEST_EN		0
#define USER_LRC_LYRICS_EN	0	//LRC歌词显示

#define USER_PRO_EN			1

#define SEL_IC_AC6928B		1

#if SEL_IC_AC6928B
//PC
#define IO_ICTX_BTRX_in			(JL_PORTC->IN & BIT(5))
#define SET_ICTX_BTRX_in		JL_PORTC->DIR |=  BIT(5)
#define SET_ICTX_BTRX_out		JL_PORTC->DIR &= ~BIT(5)
#define IO_ICTX_BTRX_set		JL_PORTC->OUT |=  BIT(5)
#define IO_ICTX_BTRX_clr		JL_PORTC->OUT &= ~BIT(5)
#define IO_ICTX_BTRX_puOn		{JL_PORTC->PU  |=  BIT(5);JL_PORTC->DIE  |=  BIT(5);}
#define IO_ICTX_BTRX_puOff		{JL_PORTC->PU  &= ~BIT(5);JL_PORTC->DIE  &= ~BIT(5);}
#define IO_ICTX_BTRX_pdOn		{JL_PORTC->PD  |=  BIT(5);JL_PORTC->DIE  |=  BIT(5);}
#define IO_ICTX_BTRX_pdOff		{JL_PORTC->PD  &= ~BIT(5);JL_PORTC->DIE  &= ~BIT(5);}

#define IO_ICRX_BTTX_in			(JL_PORTC->IN & BIT(4))
#define SET_ICRX_BTTX_in		JL_PORTC->DIR |=  BIT(4)
#define SET_ICRX_BTTX_out		JL_PORTC->DIR &= ~BIT(4)
#define IO_ICRX_BTTX_set		JL_PORTC->OUT |=  BIT(4)
#define IO_ICRX_BTTX_clr		JL_PORTC->OUT &= ~BIT(4)
#define IO_ICRX_BTTX_puOn		{JL_PORTC->PU  |=  BIT(4);JL_PORTC->DIE  |=  BIT(4);}
#define IO_ICRX_BTTX_puOff		{JL_PORTC->PU  &= ~BIT(4);JL_PORTC->DIE  &= ~BIT(4);}
#define IO_ICRX_BTTX_pdOn		{JL_PORTC->PD  |=  BIT(4);JL_PORTC->DIE  |=  BIT(4);}
#define IO_ICRX_BTTX_pdOff		{JL_PORTC->PD  &= ~BIT(4);JL_PORTC->DIE  &= ~BIT(4);}

#define IO_isSTDBY_in			(JL_PORTC->IN & BIT(3))
#define SET_isSTDBY_in			JL_PORTC->DIR |=  BIT(3)
#define SET_isSTDBY_out			JL_PORTC->DIR &= ~BIT(3)
#define IO_isSTDBY_set			JL_PORTC->OUT |=  BIT(3)
#define IO_isSTDBY_clr			JL_PORTC->OUT &= ~BIT(3)
#define IO_isSTDBY_puOn			{JL_PORTC->PU  |=  BIT(3);JL_PORTC->DIE  |=  BIT(3);}
#define IO_isSTDBY_puOff		{JL_PORTC->PU  &= ~BIT(3);JL_PORTC->DIE  &= ~BIT(3);}
//usb
#define IO_DM_in			USB_DM_IN
#define SET_DM_in			USB_DM_DIR(1)
#define SET_DM_out			USB_DM_DIR(0)
#define IO_DM_set			USB_DM_OUT(1)
#define IO_DM_clr			USB_DM_OUT(0)
#define IO_DM_puOn			{USB_DM_PU(1);USB_DM_DIE(1);}
#define IO_DM_puOff			{USB_DM_PU(0);USB_DM_DIE(0);}

#define IO_DP_in			USB_DP_IN
#define SET_DP_in			USB_DP_DIR(1)
#define SET_DP_out			USB_DP_DIR(0)
#define IO_DP_set			USB_DP_OUT(1)
#define IO_DP_clr			USB_DP_OUT(0)
#define IO_DP_puOn			{USB_DP_PU(1);USB_DP_DIE(1);}
#define IO_DP_puOff			{USB_DP_PU(0);USB_DP_DIE(0);}
//-------------------------------------------------------------------------------
//PA
#define IO_PWM_BOOST_in			(JL_PORTA->IN & BIT(4))
#define SET_PWM_BOOST_in		(JL_PORTA->DIR |=  BIT(4))
#define SET_PWM_BOOST_out		(JL_PORTA->DIR &= ~BIT(4))
#define IO_PWM_BOOST_set		(JL_PORTA->OUT |=  BIT(4))
#define IO_PWM_BOOST_clr		(JL_PORTA->OUT &= ~BIT(4))
#define IO_PWM_BOOST_puOn		{JL_PORTA->PU  |=  BIT(4);JL_PORTA->DIE  |=  BIT(4);}
#define IO_PWM_BOOST_puOff		{JL_PORTA->PU  &= ~BIT(4);JL_PORTA->DIE  &= ~BIT(4);}
//-------------------------------------------------------------------------------
#define IO_MUTE_EN_in		(JL_PORTA->IN & BIT(0))
#define SET_MUTE_EN_in		(JL_PORTA->DIR |=  BIT(0))
#define SET_MUTE_EN_out		(JL_PORTA->DIR &= ~BIT(0))
#define IO_MUTE_EN_set		(JL_PORTA->OUT |=  BIT(0))
#define IO_MUTE_EN_clr		(JL_PORTA->OUT &= ~BIT(0))
#define IO_MUTE_EN_puOn		{JL_PORTA->PU  |=  BIT(0);JL_PORTA->DIE  |=  BIT(0);}
#define IO_MUTE_EN_puOff	{JL_PORTA->PU  &= ~BIT(0);JL_PORTA->DIE  &= ~BIT(0);}
//-------------------------------------------------------------------------------
#define IO_PA3_in			(JL_PORTA->IN & BIT(3))
#define SET_PA3_in			JL_PORTA->DIR |=  BIT(3)
#define SET_PA3_out			JL_PORTA->DIR &= ~BIT(3)
#define IO_PA3_set			JL_PORTA->OUT |=  BIT(3)
#define IO_PA3_clr			JL_PORTA->OUT &= ~BIT(3)
#define IO_PA3_puOn			{JL_PORTA->PU  |=  BIT(3);JL_PORTA->DIE  |=  BIT(3);}
#define IO_PA3_puOff		{JL_PORTA->PU  &= ~BIT(3);JL_PORTA->DIE  &= ~BIT(3);}
//-------------------------------------------------------------------------------
//PB
	/*
#define IO_poweronEn_in		(JL_PORTB->IN & BIT(0))
#define SET_poweronEn_in	JL_PORTB->DIR |=  BIT(0)
#define SET_poweronEn_out	JL_PORTB->DIR &= ~BIT(0)
#define IO_poweronEn_set	JL_PORTB->OUT |=  BIT(0)
#define IO_poweronEn_clr	JL_PORTB->OUT &= ~BIT(0)
#define IO_poweronEn_puOn	{JL_PORTB->PU  |=  BIT(0);JL_PORTB->DIE  |=  BIT(0);}
#define IO_poweronEn_puOff	{JL_PORTB->PU  &= ~BIT(0);JL_PORTB->DIE  &= ~BIT(0);}

#define IO_adKey_in			(JL_PORTB->IN & BIT(1))
#define SET_adKey_in		JL_PORTB->DIR |=  BIT(1)
#define SET_adKey_out		JL_PORTB->DIR &= ~BIT(1)
#define IO_adKey_set		JL_PORTB->OUT |=  BIT(1)
#define IO_adKey_clr		JL_PORTB->OUT &= ~BIT(1)
#define IO_adKey_puOn		{JL_PORTB->PU  |=  BIT(1);JL_PORTB->DIE  |=  BIT(1);}
#define IO_adKey_puOff		{JL_PORTB->PU  &= ~BIT(1);JL_PORTB->DIE  &= ~BIT(1);}
#define IO_adKey_pdOn		{JL_PORTB->PD  |=  BIT(1);JL_PORTB->DIE  |=  BIT(1);}
#define IO_adKey_pdOff		{JL_PORTB->PD  &= ~BIT(1);JL_PORTB->DIE  &= ~BIT(1);}

#define IO_pwmLedR_in		(JL_PORTB->IN & BIT(3))
#define SET_pwmLedR_in		JL_PORTB->DIR |=  BIT(3)
#define SET_pwmLedR_out		JL_PORTB->DIR &= ~BIT(3)
#define IO_pwmLedR_set		JL_PORTB->OUT |=  BIT(3)
#define IO_pwmLedR_clr		JL_PORTB->OUT &= ~BIT(3)
#define IO_pwmLedR_puOn		{JL_PORTB->PU  |=  BIT(3);JL_PORTB->DIE  |=  BIT(3);}
#define IO_pwmLedR_puOff	{JL_PORTB->PU  &= ~BIT(3);JL_PORTB->DIE  &= ~BIT(3);}

#define IO_pwmLedW_in		(JL_PORTB->IN & BIT(4))
#define SET_pwmLedW_in		JL_PORTB->DIR |=  BIT(4)
#define SET_pwmLedW_out		JL_PORTB->DIR &= ~BIT(4)
#define IO_pwmLedW_set		JL_PORTB->OUT |=  BIT(4)
#define IO_pwmLedW_clr		JL_PORTB->OUT &= ~BIT(4)
#define IO_pwmLedW_puOn		{JL_PORTB->PU  |=  BIT(4);JL_PORTB->DIE  |=  BIT(4);}
#define IO_pwmLedW_puOff	{JL_PORTB->PU  &= ~BIT(4);JL_PORTB->DIE  &= ~BIT(4);}
//	*/
#define IO_433M_REC_in		(JL_PORTB->IN & BIT(5))
#define SET_433M_REC_in		JL_PORTB->DIR |=  BIT(5)
#define SET_433M_REC_out	JL_PORTB->DIR &= ~BIT(5)
#define IO_433M_REC_set		JL_PORTB->OUT |=  BIT(5)
#define IO_433M_REC_clr		JL_PORTB->OUT &= ~BIT(5)
#define IO_433M_REC_puOn	{JL_PORTB->PU  |=  BIT(5);JL_PORTB->DIE  |=  BIT(5);}
#define IO_433M_REC_puOff	{JL_PORTB->PU  &= ~BIT(5);JL_PORTB->DIE  &= ~BIT(5);}
//PR
#define IO_isCHRG_in		PORTR_IN(1)
#define SET_isCHRG_in		PORTR_DIR(1, 1)
#define SET_isCHRG_out		PORTR_DIR(1, 0)
#define IO_isCHRG_set		PORTR_OUT(1, 1)
#define IO_isCHRG_clr		PORTR_OUT(1, 0)
#define IO_isCHRG_puOn		{PORTR_PU(1, 1);PORTR_DIE(1, 1);}
#define IO_isCHRG_puOff		{PORTR_PU(1, 0);PORTR_DIE(1, 0);}
//-------------------------------------------------------------------------------
#define IO_AD_KEY_in		PORTR_IN(2)
#define SET_AD_KEY_in		PORTR_DIR(2, 1)
#define SET_AD_KEY_out		PORTR_DIR(2, 0)
#define IO_AD_KEY_set		PORTR_OUT(2, 1)
#define IO_AD_KEY_clr		PORTR_OUT(2, 0)
#define IO_AD_KEY_puOn		{PORTR_PU(2, 1);PORTR_DIE(2, 0);}
#define IO_AD_KEY_puOff		{PORTR_PU(2, 0);PORTR_DIE(2, 0);}
//-------------------------------------------------------------------------------
#endif	//#if SEL_IC_AC6928B

#if LOWPOWER_EN	//0 = nomeal, 1 = lowpower
#define SET_AD_KEY_FIXED		25
#define SET_AD_KEY_MAX			1023
#define SET_AD_KEY_HEAT			280		//240-293,Vin:2.7V-4.3V
#define SET_AD_KEY_POW_MODE		213		//204-233
#define SET_AD_KEY_NON			180//160		//172-177
#else
#define SET_AD_KEY_FIXED		200
#define SET_AD_KEY_MAX			1023
#define SET_AD_KEY_POW_MODE		0		//1023 / 2.2K * 0
#define SET_AD_KEY_HEAT			511		//1023 / 4.4K * 2.2K
#define SET_AD_KEY_NON			1023
#endif

#define SET_AD_V_MIN			200		//小于 2.0V 视为数据错误
#define SET_AD_V_LOWPOWER		356		//设置低压报警,3.6V = 360
#define SET_AD_V_LOWPOWER_FIX_RUN	10	//设置低压报警补偿,仅电机运行
#define SET_AD_V_LOWPOWER_FIX_HEAT	12	//设置低压报警补偿,带加热(在电机运行的补偿基础上加)

enum KEY
{
	KEY_BEGIN = 0,
	KEY_NON,
	KEY_POW_MODE,
	KEY_HEAT,
	KEY_END,
};

enum AMQ_STA
{
	STA_BEGIN = 0,
	STA_POWEROFF,
	STA_IDLE,
	STA_RUNNING,
	STA_END,
};
	
enum BT_STATA
{
	BT_STATA_BEGIN = 0,
	BT_STATA_IDEL,
	BT_STATA_SCAN,
	BT_STATA_CONNECT,
	BT_STATA_PLAY_MISIC,
	BT_STATA_END,
};

enum CHARGE_STATA
{
	CHARGE_STATA_BEGIN = 0,
	CHARGE_STATA_NULL,		//没有充电
	CHARGE_STATA_CHARGING,	//正在充电
	CHARGE_STATA_FULL,		//电量充满
	CHARGE_STATA_LOW_POWER,	//电量低且未充电
	CHARGE_STATA_END,
};

#define SPEEDLEVEL_OFF		0
#define SPEEDLEVEL_SLOW		1
#define SPEEDLEVEL_MID		2
#define SPEEDLEVEL_FAST		3
#define HEAT_LEVEL_OFF		0
#define HEAT_LEVEL_LOW		1
#define HEAT_LEVEL_MID		2
#define HEAT_LEVEL_HIGH		3

typedef struct{
	u8 sta;
	u8 speedLevel;
	u8 heatLevel;
	u8 chargeStata;		//CHARGE_STATA_NULL,CHARGE_STATA_CHARGING,CHARGE_STATA_FULL,CHARGE_STATA_LOW_POWER
	u8 massage_type;	//按摩类型，0 = 顺时针逆时针交替， 1 = 顺时针， 2 = 逆时针
	u16 C_timer_s;		//APP定时使用，无APP时默认定时15分钟
	//APP
	u8 mode;
	u8 mute_en;
}PRO;
extern PRO AMQ;

enum AMQ_STATE_INDEX
{
	AMQ_STA_START1_STOP0,
	AMQ_STA_HEAT_LEVEL,
	AMQ_STA_MASSAGE_TYPE,
	AMQ_STA_SPEED,
	AMQ_STA_TIME,
	AMQ_STA_BAT_POWER,
	AMQ_STA_IS_CHARGE,
	AMQ_STA_IS_LOWPOWER,
	AMQ_STA_MODE,
	AMQ_STA_MUTE_EN,
	AMQ_STA_END,
};
extern u8 AMQ_state[AMQ_STA_END];

#define SET_BATTERY_LEVEL_3V9	390
#define SET_BATTERY_LEVEL_3V7	370

#define POWER_LEVEL_H	3
#define POWER_LEVEL_M	2
#define POWER_LEVEL_L	1

#define SET_VBAT_POWEROFF		265
#define SET_VBAT_LOWPOWER		320
#define SET_VBAT_LEVEL1_5		340
#define SET_VBAT_LEVEL2_25		355
#define SET_VBAT_LEVEL3_50		365
#define SET_VBAT_LEVEL4_75		375
#define SET_VBAT_LEVEL5_100		395

#define SET_VBAT_COMP_TIME		250		//1s=500

extern u8 vLevel;
extern u8 powerLevel;
extern u8 btStata;
extern u16 T_ledOn_s;
extern u8 F_powerOn,F_powerOff,F_lowPower,F_pause;

extern u16 T_idle_1s;//运行15分钟关机,待机2分钟无操作关机

extern u8 F_isVin;		//充电插入状态,0=无充电器插入 ，2=充电器插入

void user_io_init();
void user_keyScan();
void user_sendTRX();


#endif

