#ifndef _MAIN_H_
#define _MAIN_H_
/****************************************************************************************/
#include "user_io_cfg.h"
/*****************************************************************************************
******************************************************************************************/
#define LED_NUM				72		//2n
#define LED_BRIGHTNESS_MAX	50
#define LED_SPEED_MAX		5
#define T_LED_DAT1_H		13
#define T_LED_DAT0_H		5
#define T_LED_DAT			20

enum _RGB_DATA	//RGB 数据发送顺序
{
	DATA_R = 0,
	DATA_G,
	DATA_B,
};
enum _STA
{
	STA_POWEROFF = 0,
	STA_POWERON,
};

enum _MODE
{
	MODE_BEGIN = 0x00,
	MODE_qiCaiLiuShui,
	MODE_danSeChangLiang,
	MODE_danSeJianBian,
	MODE_huXi,
	MODE_sanSePaoMa,
	MODE_danSeJianGePaoMa,
	MODE_danSeQieHuan,
	MODE_shanSHuo,
	MODE_END,
};

typedef struct
{
	unsigned char sta;			//1--on;0--off
	unsigned char brightness;	//亮度,1-50
	unsigned char mode;			//模式
	unsigned int rgb;			//起始灯珠rgb值,0-254--R+G,255-509--G+B,510-764--B+R,765--W,886--OFF
	unsigned char num;			//连续亮灯数量
	unsigned char gap;			//亮灯间隔
	unsigned char step;			//亮灯步数,用于间隔位置定位
	unsigned char speed;		//切换速度,1-5
	unsigned char dir;			//方向,0--下到上,1--上到下,2--两边到中间,3--中间到两边
	unsigned char mic;			//咪头使能,0--除能,1--使能
	unsigned int mic_ad;		//咪头ad
}_LIGHT;
extern _LIGHT light;

void led_rgb_refreash();
void send_led_data();

#endif
