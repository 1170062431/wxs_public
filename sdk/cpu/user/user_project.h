
#ifndef _USER_PROJECT_H_
#define _USER_PROJECT_H_

#include "system/includes.h"
#include "device/key_driver.h"
#include "asm/chargestore.h"
#include "asm/charge.h"
#include "asm/power/p33.h"
#include "rtc_alarm.h"
#include "asm/pwm_led.h"
#include "user_cfg.h"
#include "usb/otg.h"
#include "norflash.h"
#include "btstack\avctp_user.h"

#define USER_TEST_EN		0

#define USER_DEBUG_EN		1
#if USER_DEBUG_EN
#define	user_debug			printf
#else
#define	user_debug(...)
#endif

#define SEL_MUTE_EN				1	//高电平静音，功放芯片使能脚电平不同
#define SEL_IC_AC6323A			1
/*
#define TMODE_CLOSE				0
#define TMODE_TIMER				1	//timer/counter
#define TMODE_CAPTURE_RISEING	2
#define TMODE_CAPTURE_FALLING	3

//定时器功能选择
#define TIME0_MODE_SEL		0
#define TIME1_MODE_SEL		1
#define TIME2_MODE_SEL		0
#define TIME3_MODE_SEL		1
#define TIME4_MODE_SEL		1
#define TIME5_MODE_SEL		1

//PWM使能
#define TIME0_PWM_EN		0	//6965E不支持
#define TIME1_PWM_EN		1	//跟切歌有冲突？？？
#define TIME2_PWM_EN		0	//6965E不支持
#define TIME3_PWM_EN		1
#define TIME4_PWM_EN		1
#define TIME5_PWM_EN		1	//两个输出，对应引脚设为输出后同步输出波形

//PWM反向使能
#define TIME0_PWM_INV_EN	0	//6965E不支持
#define TIME1_PWM_INV_EN	0
#define TIME2_PWM_INV_EN	0	//6965E不支持
#define TIME3_PWM_INV_EN	0
#define TIME4_PWM_INV_EN	0
#define TIME5_PWM_INV_EN	0
//	*/
#if SEL_IC_AC6323A
//PA
#define IO_PA9_in			gpio_in(IO_PORTA_09)
#define SET_PA9_in			gpio_set_direction(IO_PORTA_09, 1)
#define SET_PA9_out			gpio_set_direction(IO_PORTA_09, 0)
#define SET_PA9_IO			gpio_set_die(IO_PORTA_09, 1)
#define SET_PA9_AN			gpio_set_die(IO_PORTA_09, 0)
#define IO_PA9_set			gpio_write(IO_PORTA_09, 1)
#define IO_PA9_clr			gpio_write(IO_PORTA_09, 0)
#define IO_PA9_puOn			gpio_set_pull_up(IO_PORTA_09, 1)
#define IO_PA9_puOff		gpio_set_pull_up(IO_PORTA_09, 0)
#define IO_PA9_pdOn			gpio_set_pull_down(IO_PORTA_09, 1)
#define IO_PA9_pdOff		gpio_set_pull_down(IO_PORTA_09, 0)

#define IO_PA8_in			gpio_in(IO_PORTA_08)
#define SET_PA8_in			gpio_set_direction(IO_PORTA_08, 1)
#define SET_PA8_out			gpio_set_direction(IO_PORTA_08, 0)
#define SET_PA8_IO			gpio_set_die(IO_PORTA_08, 1)
#define SET_PA8_AN			gpio_set_die(IO_PORTA_08, 0)
#define IO_PA8_set			gpio_write(IO_PORTA_08, 1)
#define IO_PA8_clr			gpio_write(IO_PORTA_08, 0)
#define IO_PA8_puOn			gpio_set_pull_up(IO_PORTA_08, 1)
#define IO_PA8_puOff		gpio_set_pull_up(IO_PORTA_08, 0)
#define IO_PA8_pdOn			gpio_set_pull_down(IO_PORTA_08, 1)
#define IO_PA8_pdOff		gpio_set_pull_down(IO_PORTA_08, 0)

#define IO_PA7_in			gpio_in(IO_PORTA_07)
#define SET_PA7_in			gpio_set_direction(IO_PORTA_07, 1)
#define SET_PA7_out			gpio_set_direction(IO_PORTA_07, 0)
#define SET_PA7_IO			gpio_set_die(IO_PORTA_07, 1)
#define SET_PA7_AN			gpio_set_die(IO_PORTA_07, 0)
#define IO_PA7_set			gpio_write(IO_PORTA_07, 1)
#define IO_PA7_clr			gpio_write(IO_PORTA_07, 0)
#define IO_PA7_puOn			gpio_set_pull_up(IO_PORTA_07, 1)
#define IO_PA7_puOff		gpio_set_pull_up(IO_PORTA_07, 0)
#define IO_PA7_pdOn			gpio_set_pull_down(IO_PORTA_07, 1)
#define IO_PA7_pdOff		gpio_set_pull_down(IO_PORTA_07, 0)

//usb
#define IO_DM_in			gpio_in(IO_PORT_DM)
#define SET_DM_in			gpio_set_direction(IO_PORT_DM, 1)
#define SET_DM_out			gpio_set_direction(IO_PORT_DM, 0)
#define SET_DM_IO			gpio_set_die(IO_PORT_DM, 1)
#define SET_DM_AN			gpio_set_die(IO_PORT_DM, 0)
#define IO_DM_set			gpio_write(IO_PORT_DM, 1)
#define IO_DM_clr			gpio_write(IO_PORT_DM, 0)
#define IO_DM_puOn			gpio_set_pull_up(IO_PORT_DM, 1)
#define IO_DM_puOff			gpio_set_pull_up(IO_PORT_DM, 0)
#define IO_DM_pdOn			gpio_set_pull_down(IO_PORT_DM, 1)
#define IO_DM_pdOff			gpio_set_pull_down(IO_PORT_DM, 0)

#define IO_DP_in			gpio_in(IO_PORT_DP)
#define SET_DP_in			gpio_set_direction(IO_PORT_DP, 1)
#define SET_DP_out			gpio_set_direction(IO_PORT_DP, 0)
#define SET_DP_IO			gpio_set_die(IO_PORT_DP, 1)
#define SET_DP_AN			gpio_set_die(IO_PORT_DP, 0)
#define IO_DP_set			gpio_write(IO_PORT_DP, 1)
#define IO_DP_clr			gpio_write(IO_PORT_DP, 0)
#define IO_DP_puOn			gpio_set_pull_up(IO_PORT_DP, 1)
#define IO_DP_puOff			gpio_set_pull_up(IO_PORT_DP, 0)
#define IO_DP_pdOn			gpio_set_pull_down(IO_PORT_DP, 1)
#define IO_DP_pdOff			gpio_set_pull_down(IO_PORT_DP, 0)
//-------------------------------------------------------------------------------
//PA
#define IO_PA2_in			gpio_in(IO_PORTA_02)
#define SET_PA2_in			gpio_set_direction(IO_PORTA_02, 1)
#define SET_PA2_out			gpio_set_direction(IO_PORTA_02, 0)
#define SET_PA2_IO			gpio_set_die(IO_PORTA_02, 1)
#define SET_PA2_AN			gpio_set_die(IO_PORTA_02, 0)
#define IO_PA2_set			gpio_write(IO_PORTA_02, 1)
#define IO_PA2_clr			gpio_write(IO_PORTA_02, 0)
#define IO_PA2_puOn			gpio_set_pull_up(IO_PORTA_02, 1)
#define IO_PA2_puOff		gpio_set_pull_up(IO_PORTA_02, 0)
#define IO_PA2_pdOn			gpio_set_pull_down(IO_PORTA_02, 1)
#define IO_PA2_pdOff		gpio_set_pull_down(IO_PORTA_02, 0)

#define IO_K_PREV_in			gpio_in(IO_PORTA_01)
#define SET_K_PREV_in			gpio_set_direction(IO_PORTA_01, 1)
#define SET_K_PREV_out			gpio_set_direction(IO_PORTA_01, 0)
#define SET_K_PREV_IO			gpio_set_die(IO_PORTA_01, 1)
#define SET_K_PREV_AN			gpio_set_die(IO_PORTA_01, 0)
#define IO_K_PREV_set			gpio_write(IO_PORTA_01, 1)
#define IO_K_PREV_clr			gpio_write(IO_PORTA_01, 0)
#define IO_K_PREV_puOn			gpio_set_pull_up(IO_PORTA_01, 1)
#define IO_K_PREV_puOff			gpio_set_pull_up(IO_PORTA_01, 0)
#define IO_K_PREV_pdOn			gpio_set_pull_down(IO_PORTA_01, 1)
#define IO_K_PREV_pdOff			gpio_set_pull_down(IO_PORTA_01, 0)

#define IO_K_VOLUP_in			gpio_in(IO_PORTA_00)
#define SET_K_VOLUP_in			gpio_set_direction(IO_PORTA_00, 1)
#define SET_K_VOLUP_out			gpio_set_direction(IO_PORTA_00, 0)
#define SET_K_VOLUP_IO			gpio_set_die(IO_PORTA_00, 1)
#define SET_K_VOLUP_AN			gpio_set_die(IO_PORTA_00, 0)
#define IO_K_VOLUP_set			gpio_write(IO_PORTA_00, 1)
#define IO_K_VOLUP_clr			gpio_write(IO_PORTA_00, 0)
#define IO_K_VOLUP_puOn			gpio_set_pull_up(IO_PORTA_00, 1)
#define IO_K_VOLUP_puOff`		gpio_set_pull_up(IO_PORTA_00, 0)
#define IO_K_VOLUP_pdOn			gpio_set_pull_down(IO_PORTA_00, 1)
#define IO_K_VOLUP_pdOff		gpio_set_pull_down(IO_PORTA_00, 0)
//-------------------------------------------------------------------------------
//PB
#define IO_K_POW_in				gpio_in(IO_PORTB_07)
#define SET_K_POW_in			gpio_set_direction(IO_PORTB_07, 1)
#define SET_K_POW_out			gpio_set_direction(IO_PORTB_07, 0)
#define SET_K_POW_IO			gpio_set_die(IO_PORTB_07, 1)
#define SET_K_POW_AN			gpio_set_die(IO_PORTB_07, 0)
#define IO_K_POW_set			gpio_write(IO_PORTB_07, 1)
#define IO_K_POW_clr			gpio_write(IO_PORTB_07, 0)
#define IO_K_POW_puOn			gpio_set_pull_up(IO_PORTB_07, 1)
#define IO_K_POW_puOff			gpio_set_pull_up(IO_PORTB_07, 0)
#define IO_K_POW_pdOn			gpio_set_pull_down(IO_PORTB_07, 1)
#define IO_K_POW_pdOff			gpio_set_pull_down(IO_PORTB_07, 0)

#define IO_K_VOLDN_in			gpio_in(IO_PORTB_06)
#define SET_K_VOLDN_in			gpio_set_direction(IO_PORTB_06, 1)
#define SET_K_VOLDN_out			gpio_set_direction(IO_PORTB_06, 0)
#define SET_K_VOLDN_IO			gpio_set_die(IO_PORTB_06, 1)
#define SET_K_VOLDN_AN			gpio_set_die(IO_PORTB_06, 0)
#define IO_K_VOLDN_set			gpio_write(IO_PORTB_06, 1)
#define IO_K_VOLDN_clr			gpio_write(IO_PORTB_06, 0)
#define IO_K_VOLDN_puOn			gpio_set_pull_up(IO_PORTB_06, 1)
#define IO_K_VOLDN_puOff		gpio_set_pull_up(IO_PORTB_06, 0)
#define IO_K_VOLDN_pdOn			gpio_set_pull_down(IO_PORTB_06, 1)
#define IO_K_VOLDN_pdOff		gpio_set_pull_down(IO_PORTB_06, 0)

#define IO_K_NEXT_in			gpio_in(IO_PORTB_05)
#define SET_K_NEXT_in			gpio_set_direction(IO_PORTB_05, 1)
#define SET_K_NEXT_out			gpio_set_direction(IO_PORTB_05, 0)
#define SET_K_NEXT_IO			gpio_set_die(IO_PORTB_05, 1)
#define SET_K_NEXT_AN			gpio_set_die(IO_PORTB_05, 0)
#define IO_K_NEXT_set			gpio_write(IO_PORTB_05, 1)
#define IO_K_NEXT_clr			gpio_write(IO_PORTB_05, 0)
#define IO_K_NEXT_puOn			gpio_set_pull_up(IO_PORTB_05, 1)
#define IO_K_NEXT_puOff			gpio_set_pull_up(IO_PORTB_05, 0)
#define IO_K_NEXT_pdOn			gpio_set_pull_down(IO_PORTB_05, 1)
#define IO_K_NEXT_pdOff			gpio_set_pull_down(IO_PORTB_05, 0)

#define IO_LED_P_in				gpio_in(IO_PORTB_04)
#define SET_LED_P_in			gpio_set_direction(IO_PORTB_04, 1)
#define SET_LED_P_out			gpio_set_direction(IO_PORTB_04, 0)
#define SET_LED_P_IO			gpio_set_die(IO_PORTB_04, 1)
#define SET_LED_P_AN			gpio_set_die(IO_PORTB_04, 0)
#define IO_LED_P_set			gpio_write(IO_PORTB_04, 1)
#define IO_LED_P_clr			gpio_write(IO_PORTB_04, 0)
#define IO_LED_P_puOn			gpio_set_pull_up(IO_PORTB_04, 1)
#define IO_LED_P_puOff			gpio_set_pull_up(IO_PORTB_04, 0)
#define IO_LED_P_pdOn			gpio_set_pull_down(IO_PORTB_04, 1)
#define IO_LED_P_pdOff			gpio_set_pull_down(IO_PORTB_04, 0)
//-------------------------------------------------------------------------------
#endif	//#if SEL_IC_AC6323A

enum PRO_STA
{
	STA_POWEROFF = 0,
	STA_POWERON,
	STA_END
};
	
enum PRO_MODE
{
	P_MODE_BEGIN = 0,
	MODE_BT,
	MODE_FAN,
	MODE_EVI,
	MODE_WTN,
	P_MODE_END
};

enum LED_MODE
{
	MODE_OFF = 0,
	MODE_RGB,		//七彩渐变:红橙黄绿蓝紫粉
	MODE_RGB_SET,	//选择颜色,七彩固定
	MODE_BREATH,	//呼吸灯（蓝色，强弱一直变化）
	MODE_WARM,		//暖光灯（长按可以调亮度）
	L_MODE_END
};

#define LED_PWM_PRD_US		30	//24
#define LED_PWM_PRD_CNT		1920	//240*8

#define LED_DUTY_MAX		250	//24
#define LED_LIGHT_MIN		25
#define LED_LIGHT_MAX		250

#define SET_POWEROFF_TIME_10MS		200		//因为会休眠，定时器不准，根据实际时间调整

typedef struct
{
	u8 sta;		//0 = poweroff, 1 = poweron
	u8 mode;
	u8 F_init;
	u8 F_keydown;
	u8 F_lowPower;
	u8 F_powerOff;
	u8 set_led_onoff_times;
	u16 T_led_on_10ms;
	u16 T_led_off_10ms;
	u16 C_poweroff_10ms;
}PRO;
extern PRO YK, *pYK;

#define SET_BATTERY_LEVEL_3V9	390
#define SET_BATTERY_LEVEL_3V7	370

#define POWER_LEVEL_H	3
#define POWER_LEVEL_M	2
#define POWER_LEVEL_L	1

#define SET_VBAT_POWEROFF		265
#define SET_VBAT_LOWPOWER		320

#define SET_VBAT_COMP_TIME		250		//1s=500

extern u8 F_powerOn,F_powerOff,F_lowPower;

extern u8 F_isVin;		//充电插入状态,0=无充电器插入 ，2=充电器插入

void user_io_init();

void bt_key_pow_on_off();

void usr_led_disp();
void usr_timer_10ms_callback(void *priv);

extern u8 io_get_key_value(void);

#endif

