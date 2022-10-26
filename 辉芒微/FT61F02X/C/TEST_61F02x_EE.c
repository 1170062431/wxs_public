/*  文件名：TEST_61F02x_EE.C
*	功能：  FT61F02x-内部EE功能演示
*   IC:    FT61F023 SOP16
*   晶振：  16M /2T                    
*   说明： 	此演示程序为61F02x EERROM的演示程序.
*		  	该程序读取0x12地址的值,取反后存入0x13地址.

*               FT61F023  SOP16 
*               ---------------
*  VDD---------|1(VDD)  (VSS)16|--------GND     
*  NC----------|2(PA7)  (PA0)15|---------NC 
*  NC----------|3(PA6)  (PA1)14|---------NC
*  NC----------|4(PA5)  (PA2)13|---------NC
*  PWM4--------|5(PC3)  (PA3)12|---------NC
*  PWM5--------|6(PC2)  (PC0)11|---------NC
*  NC----------|7(PA4)  (PC1)10|---------NC
*  NC----------|8(PC5)  (PC4)09|-------PWM3
*			    ---------------
*/
//*********************************************************
#include "SYSCFG.h"

/*----------------------------------------------------
 *	函数名称：EEPROMread
 *	功能：   读EEPROM数据
 *	输入参数：EEAddr 需读取数据的地址
 *	返回参数；ReEEPROMread 对应地址读出的数据
 ----------------------------------------------------*/
unsigned char EEPROMread(unsigned char EEAddr)
{
	unsigned char ReEEPROMread;

	EEADR = EEAddr;    
	RD = 1;
	ReEEPROMread = EEDAT;     //EEPROM的读数据 ReEEPROMread = EEDATA;
	return ReEEPROMread;
}

/*---------------------------------------------------- 
 *	函数名称：EEPROMwrite
 *	功能：   写数据到EEPROM
 *	输入参数：EEAddr 需要写入数据的地址
 *	        Data 需要写入的数据
 *	返回参数：无
 ----------------------------------------------------*/
void EEPROMwrite(unsigned char EEAddr,unsigned char Data)
{
	
	while(GIE)			//等待GIE为0
		{GIE=0;}			//写数据必须关闭中断
	EEADR = EEAddr; 	 	//EEPROM的地址
	EEDAT = Data;		 	//EEPROM的写数据  EEDATA = Data;
	EEIF = 0;
	EECON1 |= 0x34;			//置位WREN1,WREN2,WREN3三个变量.
	WR = 1;					//置位WR启动编程
    NOP();
    NOP();
	while(WR);      		//等待EE写入完成
	GIE = 1;
}