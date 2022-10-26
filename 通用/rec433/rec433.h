#ifndef _REC433_H_
#define _REC433_H_

/*********************************************************/
/********************************************************
		"1:1100us高电平+400us低电平
		0:400us高电平+1100us低电平
		数据起始位10ms低电平"					
		A	10101001 00001111 00101000 0			
		B	10101001 00001111 00100100 0			
		C	10101001 00001111 00100010 0			
		D	10101001 00001111 00100001 0			
/*********************************************************/
/*********************************************************/
//433M接收设置
#define SET_433M_REC_BIT_MAX		32		//设置433M最大接收位数
#define SET_433M_REC_DATA_START_BIT	1		//设置433M接收数据起始位
#define SET_433M_REC_DATA_STOP_BIT	32		//设置433M接收数据结束位

#define SET_433M_START_L_TIME_MIN_125US		74	//起始位低电平时间10ms-80
#define SET_433M_START_L_TIME_MAX_125US		86
/*
#define SET_433M_START_H_TIME_MIN_125US		30	//起始位高电平时间4.5ms-36
#define SET_433M_START_H_TIME_MAX_125US		42
*/
#define SET_433M_DATA_0_L_TIME_MIN_125US	6	//数据0低电平时间1100us-8.8
#define SET_433M_DATA_0_L_TIME_MAX_125US	11

#define SET_433M_DATA_0_H_TIME_MIN_125US	1	//数据0高电平时间400us-3.2
#define SET_433M_DATA_0_H_TIME_MAX_125US	7

#define SET_433M_DATA_1_L_TIME_MIN_125US	1	//数据1低电平时间400us-3.2
#define SET_433M_DATA_1_L_TIME_MAX_125US	7

#define SET_433M_DATA_1_H_TIME_MIN_125US	6	//数据1高电平时间1100us-8.8
#define SET_433M_DATA_1_H_TIME_MAX_125US	11
/*
#define SET_433M_LXM_H_TIME_MIN_125US 		14	//连续码高电平时间2.2ms-17.6
#define SET_433M_LXM_H_TIME_MAX_125US 		28
*/
#define SET_433M_DATA2DATA_TIME_125US 		888//1200	//数据间隔96ms-768,150ms-1200

extern bit F_keyDone_433M;		//按键连击用
extern unsigned long keyCode_433M;
/*********************************************************/
/*********************************************************/
void rec433M();

#endif