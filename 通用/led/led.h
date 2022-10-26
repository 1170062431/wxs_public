
#ifndef _LED_H_
#define _LED_H_

#ifndef uchar
#define uchar	unsigned char
#endif

#ifndef uint
#define uint	unsigned int
#endif

//***LED***===============================================================================
#define LED_EN	1

#if LED_EN
typedef struct
{
	uint setLedOnTime_ms;
	uint setLedOffTime_ms;
	uint C_ledOnTime_ms;
	uint C_ledOffTime_ms;
	uchar ledFlashTimes;
}struct_led;
extern struct_led stu_led;

#define setLedOnTime_ms		stu_led.setLedOnTime_ms
#define setLedOffTime_ms	stu_led.setLedOffTime_ms
#define C_ledOnTime_ms		stu_led.C_ledOnTime_ms
#define C_ledOffTime_ms		stu_led.C_ledOffTime_ms
#define ledFlashTimes		stu_led.ledFlashTimes

void ledFlash(uint onTime_ms,uint offTime_ms,uchar flashTimes);
#endif

//***RGB***===============================================================================
#define RGB_EN	1

#if RGB_EN
enum COLOR
{
	COLOR_BEGIN = 0,//	R	G	B
	COLOR_RED,		//	255	0	0
	COLOR_GREEN,	//	0	255	0
	COLOR_BLUE,		//	0	0	255

	COLOR_END
};

typedef struct
{
	uint mode;			//模式
	uint switchTime_ms;	//颜色切换时间,0=立即切换
	uchar dutyR;		//占空比
	uchar dutyG;
	uchar dutyB;
}struct_rgb;
extern struct_rgb stu_rgb;

uchar rgbChange(uchar switchTime_ms,uchar dutr_R,uchar dutr_G,uchar dutr_B);
#endif

#endif
