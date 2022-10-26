	#ifndef	_YY_433M_H_
	#define	_YY_433M_H_
	
	#include "..\H\config.h"

//TM0定时104us，接收串口数据（波特率9600），TM2定时20us

//产品选型
	#define PRO_DY_CL				1		//杜亚窗帘

#ifdef PRO_DY_CL
//对码步骤：电机端长按设置键约3s第一次亮灯时放手，然后按遥控器对码键1~2次(通常是2次)，最后按窗帘打开键，对码完成。
//为保证地址的独立性，在地址确认前，设置一个地址变量实时更新
//地址确认后设立8位固定码，与地址一起存入EEPROM（8位固定码+16位地址码+8位左右电机区别码+8位操作码）
	#define YY_WELCOME				0x00
	#define YY_BULIAN_CONNECT		0x51
	#define YY_SHALIAN_CONNECT		0x52
	#define YY_RESET				0x53
	#define YY_OPEN_CHUANGLIAN		0x01
	#define YY_CLOSE_CHUANGLIAN		0x02
	#define YY_OPEN_BULIAN			0x03
	#define YY_CLOSE_BULIAN			0x04
	#define YY_OPEN_SHALIAN			0x05
	#define YY_CLOSE_SHALIAN		0x06
	#define YY_OPEN_ZHEGUANG		0x07
	#define YY_CLOSE_ZHEGUANG		0x08
	#define YY_OPEN_ZHEYANG			0x09
	#define YY_CLOSE_ZHEYANG		0x0A
	#define YY_CHUANGLIAN_STOP		0x0B
	#define YY_STOP_CHUANGLIAN		0x0C
	#define YY_CHUANGLIAN_OPEN_EX	0x0D	//窗帘全开
	#define YY_CHUANGLIAN_CLOSE_EX	0x0E
	#define YY_OPEN_ALL				0x0F	//全部打开
	#define YY_CLOSE_ALL			0x10

	#define SET_ADR_FIXED_CODE			0x12	//设置地址固定码
	#define SET_ADR_FIXED_CODE_EEADR	0x22	//设置地址固定码内存地址
	#define SET_ADR_H_EEADR				0x32	//设置地址固定码高位内存地址
	#define SET_ADR_L_EEADR				0x33	//设置地址固定码低位内存地址
	
//	#define SET_ADR_BULIAN			0x02	//左右电机区别码_布帘
//	#define SET_ADR_SHALIAN			0x01	//左右电机区别码_纱帘
	
	#define CODE_BULIAN_OPEN		0x0211
	#define CODE_BULIAN_STOP		0x0255
	#define CODE_BULIAN_CLOSE		0x0233
	#define CODE_BULIAN_CONNECT		0x02CC	//对码
	
	#define CODE_SHALIAN_OPEN		0x0111
	#define CODE_SHALIAN_STOP		0x0155
	#define CODE_SHALIAN_CLOSE		0x0133
	#define CODE_SHALIAN_CONNECT	0x01CC	//对码
	
//初始低电平，起始位4.8ms高电平+1.5ms低电平
	#define SET_HEAD_H_20US			240
	#define SET_HEAD_L_20US			75
//数据“1”：720us高电平+360us低电平
	#define SET_DATA_1_H_20US		36
	#define SET_DATA_1_L_20US		18
//数据“0”：360us高电平+720us低电平
	#define SET_DATA_0_H_20US		18
	#define SET_DATA_0_L_20US		36
//数据发送间隔8000us
	#define SET_TX_DELAY_20US		400
//对码发送次数：4
	#define SET_CONNECT_TIMES		8
//对码发送间隔200ms
	#define SET_CONNECT_DELAY_20US	10000
//数据发送次数：4
	#define SET_TX_TIMES			4

	#define SET_RX_DATA_NUM			1			//设置接收数据个数,每个8位
    #define SET_TX_DATA_BIT			40			//设置发送数据总位数
    #define SET_TX_DATA2_BIT		32			//设置发送数据data2位数（总位数-32）  
#endif
    
	#define IO_RLED_N		PA2
	#define IO_RLED_N_out	TRISA2 = 0
	#define IO_RLED_N_int	TRISA2 = 1
	#define IO_RLED_N_set	PA2 = 1
	#define IO_RLED_N_clr	PA2 = 0

	#define IO_MRST			PA3				//PA3只能做为输入
//	#define IO_MRST_out		TRISA3= 0
//	#define IO_MRST_int		TRISA3 = 1
//	#define IO_MRST_set		PA3 = 1
//	#define IO_MRST_clr		PA3 = 0

	#define IO_LED			PA5
	#define IO_LED_out		TRISA5 = 0
	#define IO_LED_int		TRISA5 = 1
	#define IO_LED_set		PA5 = 1
	#define IO_LED_clr		PA5 = 0

	#define IO_IR_TX		PA4
	#define IO_IR_TX_out	TRISA4 = 0
	#define IO_IR_TX_int	TRISA4 = 1
	#define IO_IR_TX_set	PA4 = 1
	#define IO_IR_TX_clr	PA4 = 0

#ifdef PRO_DY_CL
	extern u8 adr_yk_fixedCode;	//遥控地址确认码，与设定值相同时判定为地址已确定
	
	extern u16 adr_yk;		//遥控地址，确定后保持不变
	extern u16 adr_yk_ref;	//参考地址，实时更新
	extern FlagStatus F_buLian_EN,F_shaLian_EN;
	extern u16 TX_buLianCode,TX_shaLianCode,TX_connectCode;
#endif 

	extern u8 eeReadData;
	extern u8 RX_data,RX_dataBit,RX_dataNum,TX_dataBit,TX_times;
    extern u16 RX_highTime,TX_highTime,TX_lowTime;

	extern FlagStatus F_feedDog,RX_EN;
    
	void sys_init();

	void yy_433m_send_head(void);
	void yy_433m_send_8bit(u8 data);
	void yy_433m_send_16bit(u16 data);
	void yy_433m_TX_delay_8ms(void);
	void yy_433m_TX_delay_200ms(void);
	void yy_433m_sendCode(u8 adr_fixedCode,u16 adr,u16 code);
	u8 EEPROMread(u8 EEAddr);
	void EEPROMwrite(u8 EEAddr,u8 Data);

	#endif