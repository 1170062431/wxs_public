//********************************************************* 
/*  文件名：TEST_61F02x_SPI.c
*	功能：  FT61F02x-SPI功能演示
*   IC:    FT61F023 SOP16
*   晶振：  16M/4T                    
*   说明：  此演示程序为61F23x_SPI的演示程序.
*		   该程序读取(25C64)0x12地址的值,取反后存入0x13地址 
*
*                  FT61F023  SOP16 
*                 ----------------
*  VDD-----------|1(VDD)   (VSS)16|-----------GND     
*  CS------------|2(PA7)   (PA0)15|------------NC 
*  SCK-----------|3(PA6)   (PA1)14|------------NC
*  NC------------|4(PA5)   (PA2)13|----------MOSI
*  NC------------|5(PC3)   (PA3)12|------------NC
*  NC------------|6(PC2)   (PC0)11|------------NC
*  MISO----------|7(PA4)   (PC1)10|------------NC
*  NC------------|8(PC5)   (PC4)09|------------NC
*			      ----------------
*/
//*********************************************************
#include "SYSCFG.h"
#include "..\h\mcu_sel.h"
#include "..\h\user_project.h"
//*********************************************************

#ifdef SPI
	/*-------------------------------------------------
	 *  函数名：init_25c64_io
	 *	功能：  25C64初始化
	 *  输入：  无
	 *  输出：  无
	 --------------------------------------------------*/	
	void init_25c64_io(void)
	{
	    SPI_CS = 1;
	 	SPI_SCK = 0;
	    SPI_MOSI = 0;
	}
	/*-------------------------------------------------
	 *  函数名：SPI_RW
	 *	功能：  主机输出以及输入一个字节
	 *  输入：  data
	 *  输出：  根据接收的data输出给从机一个字节
	 --------------------------------------------------*/		  
	unsigned char SPI_RW(unchar data)
	{
	   unsigned char i; 
	   for(i=0;i<8;i++)
	   {
	    if(data&0x80)
	      SPI_MOSI = 1;               //outpu 'uchar', MSB to MOSI
	    else
	      SPI_MOSI = 0;
	    NOP();
	    data<<=1;                 //shift next bit into MSB
	    SPI_SCK  =  1;                //Set SCK high...
		NOP();
	    if(SPI_MISO)
	      data  |= 0x01;
	    else
	      data  &= 0xFE;
		NOP();
	    SPI_SCK  =  0;
	   }
	   return data;
	 }
	/*-------------------------------------------------
	 *  函数名：WriteEnable
	 *	功能：  写允许（将WEN置位） 
	 --------------------------------------------------*/
	void WriteEnable(void)
	{
	    SPI_CS=0;
	    SPI_RW(0x06);  
	    SPI_CS=1;
	}
	/*-------------------------------------------------
	 *  函数名：WriteDisable
	 *	功能：  写禁止（将WEN复位） 
	 --------------------------------------------------*/
	 void WriteDisable (void)
	{
	    SPI_CS=0;
	    SPI_RW(0x04);  
	    SPI_CS=1;
	}
	/************************************************
	// 功能：读取25C64芯片的状态。
	// 返回值：状态寄存器数据字节
	// 注：25C64内部状态寄存器第0位=0表示空闲，0位=1表示忙。
	*************************************************/
	unsigned char SPI_ReadStatus(void)
	{
	    unsigned char status=0;
	    SPI_CS=0;
	    SPI_RW(0x05);                 //0x05读取状态的命令字
	    status = SPI_RW(0x00);        
	    SPI_CS=1;                         //关闭片选
	    return status;
	}  
	/************************************************
	*程序名：SPI_WriteStatus
	*功能:  写25C64芯片的状态寄存器。
	*      只有BP1、BP0 (bit7、3、2)可以写、
	*注：   25c64内部状态寄存器第0位=0表示空闲，0位=1表示忙。
	*************************************************/
	void SPI_WriteStatus(unsigned char Status)
	{
	    SPI_CS=0;
	    SPI_RW(0X01);  		          //0x01读取状态的命令字
	    SPI_RW(Status);               //写入一个字节
	    SPI_CS=1;                         //关闭片选
	}
	/*****************************************************************
	程序名：SPI_Read
	输入: 16位的地址
	返回: 读取的数据
	说明：从25c64指定的地址读取一个字节
	*****************************************************************/
	unsigned char SPI_Read(unsigned int addr)
	{
		unsigned char spidata;
	    while(SPI_ReadStatus()&0x01);       //判断是否忙
	    SPI_CS=0;                        	//使能器件   
	    SPI_RW(0x03);                       //发送读取命令   
	    SPI_RW((unsigned char)((addr)>>8));
	    SPI_RW((unsigned char)addr);
	  	spidata = SPI_RW(0x00);             //读出数据  
	    SPI_CS=1;  
	  	return spidata;            
	}
	/*****************************************************************
	程序名：SPI_Write
	输入: 地址，字节数据
	说明：将一个字节写入指定的地址
	*****************************************************************/
	void SPI_Write(unsigned int addr,unsigned char dat)
	{
	    while(SPI_ReadStatus()&0x01);  		//判断是否忙
	    WriteEnable();                      //SET WEL
	    SPI_CS=0;                          	//使能器件   
	    SPI_RW(0x02);   				    //发送写命令 
	    SPI_RW((unsigned char)((addr)>>8));
	    SPI_RW((unsigned char)addr);
	    
	    SPI_RW(dat);
		WriteDisable(); 
	    SPI_CS=1;                              //关闭片选
	    while(SPI_ReadStatus()&0x01); 
	}
	
#endif