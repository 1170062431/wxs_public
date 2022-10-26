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

enum _RGB_DATA	//RGB ���ݷ���˳��
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
	unsigned char brightness;	//����,1-50
	unsigned char mode;			//ģʽ
	unsigned int rgb;			//��ʼ����rgbֵ,0-254--R+G,255-509--G+B,510-764--B+R,765--W,886--OFF
	unsigned char num;			//������������
	unsigned char gap;			//���Ƽ��
	unsigned char step;			//���Ʋ���,���ڼ��λ�ö�λ
	unsigned char speed;		//�л��ٶ�,1-5
	unsigned char dir;			//����,0--�µ���,1--�ϵ���,2--���ߵ��м�,3--�м䵽����
	unsigned char mic;			//��ͷʹ��,0--����,1--ʹ��
	unsigned int mic_ad;		//��ͷad
}_LIGHT;
extern _LIGHT light;

void led_rgb_refreash();
void send_led_data();

#endif
