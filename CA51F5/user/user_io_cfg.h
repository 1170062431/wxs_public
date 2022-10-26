#ifndef _USER_IO_CFG_H_
#define _USER_IO_CFG_H_

#include "include/ca51f5_config.h"		
#include "include/ca51f5sfr.h"
#include "include/ca51f5xsfr.h"
#include "include/gpiodef_f5.h"
#include "include/system_clock.h"

#include "include/delay.h"
#include <intrins.h>

#include "uart.h"
#include "timer0.h"
#include "timer1.h"
#include "pwm.h"
#include "key.h"
#include "main.h"

// IO_CFG
#define IO_IR_REC		P35
#define IO_IR_REC_CFG	P35F
#define IO_IR_REC_SEL	P35C

#define IO_KEY_PWR		P32
#define IO_KEY_PWR_CFG	P32F
#define IO_KEY_PWR_SEL	P32C

#define IO_LED_DAT		P34
#define IO_LED_DAT_CFG	P34F
#define IO_LED_DAT_SEL	P34C

#define IO_MIC_AD		P01
#define IO_MIC_AD_CFG	P01F
#define IO_MIC_AD_SEL	P01C

//Pn
#define SET_IO_OUT(Pnx,a)		Pnx = a			//设置引脚输出,Pnx,1--Pnx output=1,Pnx,	0--Pnx output=0

//PnxF
enum PU_	//上拉
{
	PU_CLOSE = 0,
	PU_OPEN = 1,
};
enum PD_	//下拉
{
	PD_CLOSE = 0,
	PD_OPEN = 1,
};
enum OPR_	//开漏
{
	OPR_CLOSE = 0,
	OPR_OPEN = 1,
};
	
#define SET_IO_CFG(Pnx_CFG,PU,PD,OPR,FUNC_SEL)	Pnx_CFG = PU<<7|PD<<6|OPR<<5|FUNC_SEL	//设置引脚功能，上拉,下拉,开漏,输入输出等->2--output,1--input,0--high Z(高阻)

//PnxC
/*
*@SMIT_EN 		0--反相器模式 1--SMIT模式
*@PU_SEL/PD_SEL 0--弱上/下拉 1--强上/下拉
*@DRV			输出强度0~3
*@SR			电平转换速度0~3
*/
enum SMIT_SEL
{
	SMIT_DIS = 0,
	SMIT_EN = 1,
};
enum PU_SEL
{
	PU_WEEK = 0,
	PU_STRONG = 1,
};
enum PD_SEL
{
	PD_WEEK = 0,
	PD_STRONG = 1,
};
enum DRV_SEL
{
	DRV_LV1 = 0,
	DRV_LV2 = 1,
	DRV_LV3 = 2,
};
enum SL_SEL
{
	SL_LV1 = 0,
	SL_LV2 = 1,
	SL_LV3 = 2,
};

#define SET_IO_SEL(Pnx_SEL,SMIT_EN,PU_SEL,PD_SEL,DRV,SL)	Pnx_SEL = SMIT_EN<<6|PU_SEL<<5|PD_SEL<<4|DRV<<2|SL

void io_init();


#endif
