/*************************************************************
//文 件 名：TM1650.h
//文件描述：LED驱动芯片TM1650接口定义
//编 写 者：wxs
//创建日期：2020-10-26 9:20
//版 本 号：1.0
//修改纪录：
**************************************************************/
#ifndef _TM1650_H_
#define _TM1650_H_


#define CFG_SYS_CMD			0x48
#define CFG_READ_KEY_CMD	0x4F
#define CFG_BRIGHTNESS(N)	(N & 0x07)		//light level:1_001-2_002-...-7_007-8_000(DEFAULT)
#define CFG_SEG_MODE_8SEG	0				//(DEFAULT)
#define CFG_SEG_MODE_7SEG	1
#define CFG_WORK_MODE		0
#define CFG_WORK_IDLE		1
#define CFG_DISP_OFF		0
#define CFG_DISP_ON			1

#define CFG_DISP_CFG_BRIGHTNESS_NORMAL		7
#define CFG_DISP_CFG_BRIGHTNESS_LOWPOWER	1

void TM1650_Init     (void);
void TM1650_SendAddrDat (unsigned char addr,unsigned char dat);
void TM1650_Switch(unsigned char brightness,unsigned char en);
unsigned char TM1650_keyScan(void);

#endif