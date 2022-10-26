#ifndef	_KEY_H_
#define	_KEY_H_

#ifndef uchar
#define uchar	unsigned char
#endif

#ifndef uint
#define uint	unsigned int
#endif

#ifndef ulong
#define ulong	unsigned long
#endif

#ifndef BIT(n)
#define BIT(n)	(1<<i)
#endif

#define KEY_433M_EN		1

#define KEY_MULTI_EN	1

#define KEYLJ_EN		1	//按键连击
	#if KEYLJ_EN
	#define SET_KEY_FIRST_LJYS_MS	500		//首次按键连击延时
	#define SET_KEY_LJYS_MS			150		//按键连击延时
	#endif

/*********************************************************/
/*********************************************************/
#define KEY_MASK		0x0F	//0x0F,按键后四位有效
/*********************************************************/
#define KEY0	IO_PA0_in
#define KEY1	IO_PA1_in
#define KEY2	IO_PA2_in
#define KEY3	IO_PA3_in
#define KEY4	IO_PA4_in
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
#define KEY_NUM		14
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
	
/*********************************************************/
/*********************************************************/
#if KEY_433M_EN		
extern uchar keyCodeBitNum_433M;
extern ulong keyAdr_433M;
extern uchar keyCode_433M;
/*********************************************************/
//433M接收设置
#define SET_433M_REC_BIT_MIN			8		//设置433M最小接收位数
#define SET_433M_REC_BIT_NOMAL			24
#define SET_433M_REC_BIT_MAX			24		//设置433M最大接收位数
#define SET_433M_REC_DATA_START_BIT		1		//设置433M接收数据起始位
#define SET_433M_REC_DATA_STOP_BIT		24		//设置433M接收数据结束位

#define SET_433M_START_L_TIME_MIN_125US		1	//起始位低电平时间(260us)-400us-3.2
#define SET_433M_START_L_TIME_MAX_125US		4

#define SET_433M_START_H_TIME_MIN_125US		54	//起始位高电平时间8ms-64
#define SET_433M_START_H_TIME_MAX_125US		74

#define SET_433M_DATA_0_L_TIME_MIN_125US	5	//数据0低电平时间780us-
#define SET_433M_DATA_0_L_TIME_MAX_125US	7

#define SET_433M_DATA_0_H_TIME_MIN_125US	1	//数据0高电平时间(260us)-400us-
#define SET_433M_DATA_0_H_TIME_MAX_125US	4

#define SET_433M_DATA_1_L_TIME_MIN_125US	1	//数据1低电平时间(260us)-320us-2.56
#define SET_433M_DATA_1_L_TIME_MAX_125US	4

#define SET_433M_DATA_1_H_TIME_MIN_125US	5	//数据1高电平时间720us-(780us)-5.76
#define SET_433M_DATA_1_H_TIME_MAX_125US	7
/*
#define SET_433M_LXM_H_TIME_MIN_125US 		14	//连续码高电平时间2.2ms-17.6
#define SET_433M_LXM_H_TIME_MAX_125US 		28
*/
#define SET_433M_DATA2DATA_TIME_125US 		500//1200	//数据间隔96ms-768,150ms-1200
#endif
/*********************************************************/
/*********************************************************/

#if KEYLJ_EN
extern uint timeKeyLJ_ms;
#endif
extern ulong keySta;
extern uchar keyCode;
extern uint keyDownTime_ms;
extern uchar F_keyDone;		//按键连击用

extern uchar keyStaBuff[KEY_NUM];
/*********************************************************/

void keyScan();
void keyAction();

#endif
