#ifndef	_KEY_H_
#define	_KEY_H_

#include "user_io_cfg.h"

#define IRKEY_EN		1

#define KEY_433M_EN		0

#define KEY_MULTI_EN	0

#define KEYLJ_EN		0	//按键连击
	#if KEYLJ_EN
	#define SET_KEY_FIRST_LJYS_MS	500		//首次按键连击延时
	#define SET_KEY_LJYS_MS			150		//按键连击延时
	#endif

/*********************************************************/
/*********************************************************/
#define KEY_MASK		0x0F	//0x0F,按键后四位有效
/*********************************************************/
#define KEY0	IO_KEY_PWR
/*********************************************************/
#define NK 	0x000000
/*******以下为单按键**************************************/
#define K0 	0x000001
#define K1 	0x000002
#define K2 	0x000004
#define K3 	0x000008
#define K4 	0x000010
#define K5 	0x000020
#define K6 	0x000040
#define K7 	0x000080
#define K8 	0x000100
#define K9 	0x000200
#define K10 0x000400
#define K11 0x000800
#define K12 0x001000
#define K13 0x002000
#define K14 0x004000
#define K15	0x008000
#define K16	0x010000
#define K17	0x020000
#define K18	0x040000
#define K19	0x080000
/*******以下为复合键**************************************/
#define MK1	0x000003
#define MK2	0x080005
/*********************************************************/
#define KEY_NUM		1

#define T_POWER_ON_ms 	1200	//定时不太准

/*
enum KEY		//20bitadr=0xFCFFF +  4bitkey
{
	KEY_NON = 0xFF,
	KEY_POW = 0x09,
	KEY_RESET = 0x0B,
	KEY_TIMER_30S = 0x02,
	KEY_BRIGHTNESS_ADD = 0x07,
	KEY_BRIGHTNESS_DEC = 0x08,
	KEY_LIGHT_WARM = 0x0C,
	KEY_LIGHT_COLD = 0x03,		//数量值恒定为亮度100时的值，只计算百分比，和亮度无关
	KEY_NIGHT_LIGHT = 0x04,
	KEY_LIGHT_R = 0x0D,
	KEY_LIGHT_G = 0x05,
	KEY_LIGHT_B = 0x00,
	KEY_TIMER_DEC = 0x0E,
	KEY_TIMER_ADD = 0x01,
	KEY_LINGHT_RGB = 0x06,
	KEY_END
};
*/
enum IRKEY_24		//20bitadr=0xFCFFF +  4bitkey
{
	IRKEY_light_add = 0x00,
	IRKEY_light_dec,
	IRKEY_off,
	IRKEY_on,
	IRKEY_r,
	IRKEY_g,
	IRKEY_b,
	IRKEY_w,
	IRKEY_r_1,
	IRKEY_g_1,
	IRKEY_b_1,
	IRKEY_flash,
	IRKEY_r_2,
	IRKEY_g_2,
	IRKEY_b_2,
	IRKEY_strobe,
	IRKEY_r_3,
	IRKEY_g_3,
	IRKEY_b_3,
	IRKEY_fade,
	IRKEY_r_4,
	IRKEY_g_4,
	IRKEY_b_4,
	IRKEY_smooth,
	IRKEY_END,
	IRKEY_NON = 0xFF,
};
	
/*********************************************************/
#if IRKEY_EN	
/*********************************************************/	
#define IRKEY_HEAD  0x00F7	//0x00EF
#define IRCODE(n)	((n<<8)|(~n&0xff))
#define IRCODEF(n)	(n|(~n&0xff)<<8)
/*********************************************************/	
//extern uchar keyCodeBitNum_IR;
//extern ulong keyAdr_IR;
//extern uchar keyCode_IR;
/*********************************************************/
//IR接收设置
#define SET_IR_REC_BIT_MIN				8		//设置IR最小接收位数
#define SET_IR_REC_BIT_NOMAL			24
#define SET_IR_REC_BIT_MAX				32		//设置IR最大接收位数
#define SET_IR_REC_DATA_START_BIT		1		//设置IR接收数据起始位
#define SET_IR_REC_DATA_STOP_BIT		32		//设置IR接收数据结束位

#define SET_IR_START_L_TIME_MIN_125US		40	//起始位低电平时间9ms-72
#define SET_IR_START_L_TIME_MAX_125US		80

#define SET_IR_START_H_TIME_MIN_125US		20	//起始位高电平时间4.5ms-36
#define SET_IR_START_H_TIME_MAX_125US		46

#define SET_IR_DATA_0_L_TIME_MIN_125US		2	//起始位低电平时间600us-4.8
#define SET_IR_DATA_0_L_TIME_MAX_125US		6

#define SET_IR_DATA_0_H_TIME_MIN_125US		2	//起始位低电平时间600us-4.8
#define SET_IR_DATA_0_H_TIME_MAX_125US		6

#define SET_IR_DATA_1_L_TIME_MIN_125US		2	//起始位低电平时间600us-4.8
#define SET_IR_DATA_1_L_TIME_MAX_125US		6

#define SET_IR_DATA_1_H_TIME_MIN_125US		8	//数据1高电平时间1.6ms-12.8
#define SET_IR_DATA_1_H_TIME_MAX_125US		15
/*
#define SET_IR_LXM_H_TIME_MIN_125US 		14	//连续码高电平时间2.2ms-17.6
#define SET_IR_LXM_H_TIME_MAX_125US 		28
*/
#define SET_IR_DATA2DATA_TIME_125US 		768//1200	//数据间隔96ms-768,150ms-1200
/*********************************************************/
#endif
/*********************************************************/

#if KEYLJ_EN
extern uint timeKeyLJ_ms;
#endif

extern ulong keySta,keyStaBackup;
extern ulong keyCode;
extern uint keyDownTime_ms;
extern uchar F_keyDone;		//按键连击用

extern uchar keyStaBuff[KEY_NUM];
/*********************************************************/

void keyScan();
void keyAction();
u16 userIrCodeChange(u16 irCode);

#endif
