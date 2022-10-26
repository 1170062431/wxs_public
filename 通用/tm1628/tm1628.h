	#ifndef _TM1628_H_
	#define _TM1628_H_
	#include "config.h"
	
//	显示模式设置	
	#define Set_DispMode_4Grid13Seg		0x00
	#define Set_DispMode_5Grid12Seg		0x01
	#define Set_DispMode_6Grid11Seg		0x02
	#define Set_DispMode_7Grid10Seg		0x03
	
//	数据读写设置	
	#define Set_Nomal_AutoAddADR_Write2Disp		0x40
	#define Set_Nomal_FixedADR_Write2Disp		0x44
	#define Set_Nomal_ReadKeyMap				0x42
		
	#define Set_Test_AutoAddADR_Write2Disp		0x48
	#define Set_Test_FixedADR_Write2Disp		0x4C
	#define Set_Test_ReadKeyMap					0x4A
	
//	显示控制设置
	#define Set_DispOff							0x80
	#define Set_DispOn_LightLevel1				0x88
	#define Set_DispOn_LightLevel2				0x89
	#define Set_DispOn_LightLevel4				0x8A
	#define Set_DispOn_LightLevel10				0x8B
	#define Set_DispOn_LightLevel11				0x8C
	#define Set_DispOn_LightLevel12				0x8D
	#define Set_DispOn_LightLevel13				0x8E
	#define Set_DispOn_LightLevel14				0x8F
	
//	显示寄存器地址设置
	#define Set_DispAdr_00H						0xC0
	#define Set_DispAdr_01H						0xC1
	#define Set_DispAdr_02H						0xC2
	#define Set_DispAdr_03H						0xC3
	#define Set_DispAdr_04H						0xC4
	#define Set_DispAdr_05H						0xC5
	#define Set_DispAdr_06H						0xC6
	#define Set_DispAdr_07H						0xC7
	#define Set_DispAdr_08H						0xC8
	#define Set_DispAdr_09H						0xC9
	#define Set_DispAdr_0AH						0xCA
	#define Set_DispAdr_0BH						0xCB
	#define Set_DispAdr_0CH						0xCC
	#define Set_DispAdr_0DH						0xCD

	extern unsigned char LEDDispBuff[7];
//	extern unsigned char LEDDispBuff[14];
	
	void tm1628Init();
	void send_8bit(uint8 dat);
	void command(uint8 com);
	void read_key();
	void displayLED();
//	void key_process();
	
	#endif