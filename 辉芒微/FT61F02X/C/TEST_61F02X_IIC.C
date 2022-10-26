//********************************************************* 
/*  文件名： TEST_61F02x_IIC.c
*	功能：  FT61F02x-IIC功能演示
*   IC:    FT61F023 SOP16
*   晶振：  16M/4T                    
*   说明：  此演示程序位61F02x_IIC的演示程序.
*		   该程序读取(24C02)0x12地址的值,取反后存入0x13地址
* 
*                  FT61F023  SOP16 
*                 ----------------
*  VDD-----------|1(VDD)   (VSS)16|-----------GND     
*  NC------------|2(PA7)   (PA0)15|------------NC 
*  NC------------|3(PA6)   (PA1)14|------------NC
*  NC------------|4(PA5)   (PA2)13|--------IIC_SDA
*  NC------------|5(PC3)   (PA3)12|------------NC
*  NC------------|6(PC2)   (PC0)11|------------NC
*  IIC_SCL-------|7(PA4)   (PC1)10|------------NC
*  NC------------|8(PC5)   (PC4)09|------------NC
*			      ----------------
*/

//*********************************************************
#include "SYSCFG.h"
#include "..\h\mcu_sel.h"
#include "..\h\user_project.h"
//*********************************************************

#ifdef IIC      
	/*-------------------------------------------------
	 *  函数名：IIC_Start
	 *	功能：  产生IIC起始信号
	 *  输入：  无
	 *  输出：  无
	 --------------------------------------------------*/
	void IIC_Start(void)
	{
		SDA_OUT;              //SDA线输出
		IIC_SDA=1;	  	  
		IIC_SCL=1;
		DelayUs(10);
	 	IIC_SDA=0;            //START:when CLK is high,DATA change form high to low 
		DelayUs(10);
		IIC_SCL=0;            //钳住I2C总线，准备发送或接收数据 
	    DelayUs(10);
	}	  
	/*-------------------------------------------------
	 *  函数名：IIC_Stop
	 *	功能：  产生IIC停止信号
	 *  输入：  无
	 *  输出：  无
	 --------------------------------------------------*/
	 void IIC_Stop(void)
	{
		SDA_OUT;              //SDA线输出
		IIC_SCL=0;
		IIC_SDA=0;            //STOP:when CLK is high DATA change form low to high
	 	DelayUs(10);
		IIC_SCL=1;
	    DelayUs(10); 
		IIC_SDA=1;            //发送I2C总线结束信号
		DelayUs(10);							   	
	}
	/*-------------------------------------------------
	 *  函数名：IIC_Wait_Ack
	 *	功能：  等待应答信号到来
	 *  输入：  无
	 *  输出：  返回值：1，接收应答失败
	 *               0，接收应答成功
	 --------------------------------------------------*/
	unsigned char IIC_Wait_Ack(void)
	{
		unsigned char ucErrTime=0;      
		SDA_IN;               //SDA设置为输入  
		IIC_SDA=1;
		DelayUs(5);	   
		IIC_SCL=1;
		DelayUs(5);	 
		while(IIC_SDA)
		{
			ucErrTime++;
			if(ucErrTime>250) //等待超时
			{
				IIC_Stop();
				return 1;
			}
		}
		IIC_SCL=0;            //时钟输出0 	   
		return 0;  
	} 
	/*-------------------------------------------------
	 *  函数名：IIC_Ack
	 *	功能：  产生ACK应答
	 *  输入：  无
	 *  输出：  无
	 --------------------------------------------------*/
	void IIC_Ack(void)
	{
		IIC_SCL=0;
		SDA_OUT;              //SDA线输出
		IIC_SDA=0;
		DelayUs(5);	
		IIC_SCL=1;
		DelayUs(5);	
		IIC_SCL=0;
	}
	/*-------------------------------------------------
	 *  函数名：IIC_NAck
	 *	功能：  不产生ACK应答
	 *  输入：  无
	 *  输出：  无
	 --------------------------------------------------*/	    
	void IIC_NAck(void)
	{
		IIC_SCL=0;
		SDA_OUT;              //SDA线输出
		IIC_SDA=1;
		DelayUs(5);	
		IIC_SCL=1;
		DelayUs(5);	
		IIC_SCL=0;
	}					 				     
	/*-------------------------------------------------
	 *  函数名：IIC_Send_Byte
	 *	功能：  IIC发送一个字节
	 *  输入：  写入要发送的一个人字节数据txd
	 *  输出：  无
	 --------------------------------------------------*/		  
	void IIC_Send_Byte(unsigned char txd)
	{                        
	    unsigned char t;   
		SDA_OUT;	          //SDA线输出   
	    IIC_SCL=0;            //拉低时钟开始数据传输
	    for(t=0;t<8;t++)
	    {              
			if((txd&0x80)>>7)
				IIC_SDA=1;
			else
				IIC_SDA=0;
			txd<<=1; 	  
			DelayUs(5);				  
			IIC_SCL=1;
			DelayUs(5);	
			IIC_SCL=0;	
			DelayUs(5);
	    }	 
	} 	    
	/*-------------------------------------------------
	 *  函数名：IIC_Read_Byte
	 *	功能：  IIC读一个字节
	 *  输入：  无
	 *  输出：  读出存储器里面的数据并返回receive
	 --------------------------------------------------*/
	 unsigned char IIC_Read_Byte(void)
	{
		unsigned char i,receive=0;
		SDA_IN;               //SDA设置为输入
	    for(i=0;i<8;i++ )
		{
	        IIC_SCL=0; 
	        DelayUs(5);	
	     	IIC_SCL=1;
	        receive<<=1;
	        if(IIC_SDA)receive++;   
			DelayUs(5);	
	    }					 
	    IIC_NAck();           //发送nACK
	  
	    return receive;
	}
	/*-------------------------------------------------
	 *  函数名：IIC_READ
	 *	功能：  IIC读出制定位置的数据
	 *  输入：  address
	 *  输出：  读出address存储器里面的数据iicdata
	 --------------------------------------------------*/
	 unsigned char IIC_READ(unsigned char address)
		{
		unsigned char iicdata = 0;
		IIC_READ_Begin:
			IIC_Start();
			IIC_Send_Byte(0xa0);
			if(IIC_Wait_Ack())goto IIC_READ_Begin;
			IIC_Send_Byte(address);				//填要读的数据地址
			if(IIC_Wait_Ack())goto IIC_READ_Begin; 
			IIC_Start();
			IIC_Send_Byte(0xa1);
			if(IIC_Wait_Ack())goto IIC_READ_Begin;
			iicdata=IIC_Read_Byte();
			IIC_Stop();		
			return iicdata;
		}
	 /*-------------------------------------------------
	 *  函数名：IIC_WRITE
	 *	功能：  IIC把数据data写入制定的位置address
	 *  输入：  address，data
	 *  输出：  无
	 --------------------------------------------------*/
	void IIC_WRITE(unsigned char address,unsigned char data)
		{
		IIC_WRITE_Begin:
			IIC_Start();
			IIC_Send_Byte(0xa0);
			if(IIC_Wait_Ack())goto IIC_WRITE_Begin;

			IIC_Send_Byte(address);
			if(IIC_Wait_Ack())goto IIC_WRITE_Begin;

			IIC_Send_Byte(data);
			if(IIC_Wait_Ack())goto IIC_WRITE_Begin;

			IIC_Stop();	
		}
#endif
