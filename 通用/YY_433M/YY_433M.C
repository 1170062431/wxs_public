//Project: yy_433M.prj
// Device: FT60F01X
// Memory: Flash 1KX14b, EEPROM 256X8b, SRAM 64X8b
// Author: 
//Company: 
//Version:
//   Date: 
//===========================================================
//===========================================================
	#include	"SYSCFG.h";
    
	#include "..\H\yy_433M.h"
//	#include "..\H\config.h"
	#include "..\H\mcu_sel.h"

//===========================================================
//Variable definition
//===========================================================	

#ifdef PRO_DY_CL
	u8 adr_yk_fixedCode;	//遥控地址确认码，与设定值相同时判定为地址已确定
	
	u16 adr_yk;		//遥控地址，确定后保持不变
	u16 adr_yk_ref;	//参考地址，实时更新
	FlagStatus F_buLian_EN,F_shaLian_EN;
	u16 TX_buLianCode,TX_shaLianCode,TX_connectCode;
#endif

	u8 eeReadData;
	u8 RX_data,RX_dataBit,RX_dataNum,TX_dataBit,TX_times;
    u16 RX_highTime,TX_highTime,TX_lowTime;
	FlagStatus F_feedDog,RX_EN;
    u8 T_1s;
    u16 T_100us;
	
	FLAG Time_FLAG;	
    
	u8 UART_RX_buff[SET_RX_DATA_NUM] = {0x00};

//===========================================================
//Funtion name：interrupt ISR
//parameters：无
//returned value：无
//===========================================================
	void interrupt ISR(void)
	{
		if(TM0_E && TM0_F)
		{
//			IO_RLED_N = !IO_RLED_N;		//时钟校准
			TM0_F = RESET;
//			TMR0 = 152;			//256-104，预分频4，定时104us,9600波特率
			TMR0 = 164;			//152+12,有误差,12为补偿值

			adr_yk_ref++;
			
			if(RX_EN)
			{
                if(IO_MRST)
					RX_data = (RX_data>>1)|0x80;
				else
					RX_data >>= 1;
                RX_dataBit--;
                if(!RX_dataBit)
                {
                    UART_RX_buff[0] = RX_data;
					RX_EN = DISABLE;
                }
				return;
            }
            else
            {
				T_100us++;
				if(T_100us == 9615)
				{
					T_100us = 0;
					T_1s++;
					if(T_1s == 15)
					{
						T_1s = 0;
                        IO_LED_clr;
                        IO_RLED_N_set;
					}
				}
            }
		}
        
		if(TM2_E && TM2_F)		//20us
		{
			IO_RLED_N = !IO_RLED_N;		//时钟校准
			TM2_F = RESET;
            if(TX_highTime)
            {
                TX_highTime--;
				IO_IR_TX_set;
                return;
            }
            else if(TX_lowTime)
            {
                TX_lowTime--;
                IO_IR_TX_clr;
                return;
            }
		}
//		F_feedDog = SET;
	}
//===========================================================
//Funtion name：main
//parameters：无
//returned value：无
//===========================================================
	main()
	{
		sys_init();
		F_buLian_EN = RESET;
		F_shaLian_EN = RESET;
        RX_EN = DISABLE;
//		TM0_OFF();
		adr_yk_fixedCode = EEPROMread(SET_ADR_FIXED_CODE_EEADR);
		if(adr_yk_fixedCode == SET_ADR_FIXED_CODE)
		{
			eeReadData = EEPROMread(SET_ADR_H_EEADR);
			adr_yk = eeReadData << 8;
			eeReadData = EEPROMread(SET_ADR_L_EEADR);
			adr_yk += eeReadData;
		}
		while(1)
		{
//			if(F_feedDog)
//				CLRWDT();
            
			RX_highTime	=	0;
			while(RX_highTime<5000)		//4000=1ms
			{
                if(IO_MRST)
					RX_highTime++;
				else
					RX_highTime = 0;
			}
            
            T_100us = 0;
            T_1s = 0;
			TM0_ON();
            while(IO_MRST)
            {
				CLRWDT();
//**************进入睡眠模式*******************          
//                if(IO_RLED_N == SET) 
//                {
//					TM0_OFF();
//					SWDTEN = DISABLE;
//					IOCA3 = SET;					//打开PA3电平变化中断
//					RAIE = SET;						//打开电平变化中断
//					SLEEP();
//					RAIE = RESET;					//关闭电平变化中断
//					IOCA3 = RESET;					//关闭PA3电平变化中断
//					SWDTEN = ENABLE;
//                }
//*******************************************
            }
			TM0_OFF();		//即将接收数据，参数初始化前关闭定时
/***********时钟校准*******************/	
			/*
			TM2_ON();
			while (1);
			*/
/**************************************/			
            RX_dataNum = 0;
			for(RX_dataNum = 0;RX_dataNum < SET_RX_DATA_NUM;RX_dataNum++)
			{
				while(IO_MRST);
				RX_EN = ENABLE;
				RX_dataBit = 8;
				TMR0 = 100;			//256-156，预分频4，首位加起始位延时156us,9600波特率
				TM0_ON();
				while(RX_EN);
				TM0_OFF();
				while(!IO_MRST);
			}
			RX_data = UART_RX_buff[0];
			IO_RLED_N = !IO_RLED_N;		//每次收到指令改变指示灯状态
			switch(RX_data)
			{
			case YY_WELCOME:			//你好小白（唤醒词）
				IO_LED_set;
				break;
			case YY_BULIAN_CONNECT:		//布帘对码
			case YY_SHALIAN_CONNECT:	//纱帘对码
			case YY_RESET:				//恢复出厂设置
				if((adr_yk_fixedCode != SET_ADR_FIXED_CODE)||(RX_data == YY_RESET))
				{
					adr_yk = adr_yk_ref;
					EEPROMwrite(SET_ADR_L_EEADR,(u8)adr_yk);
					EEPROMwrite(SET_ADR_L_EEADR,(u8)adr_yk);
					EEPROMwrite(SET_ADR_H_EEADR,(u8)(adr_yk>>8));
					EEPROMwrite(SET_ADR_H_EEADR,(u8)(adr_yk>>8));
					EEPROMwrite(SET_ADR_FIXED_CODE_EEADR,SET_ADR_FIXED_CODE);
					EEPROMwrite(SET_ADR_FIXED_CODE_EEADR,SET_ADR_FIXED_CODE);
					adr_yk_fixedCode = SET_ADR_FIXED_CODE;
				}
				TM2_ON();
				TX_times = SET_CONNECT_TIMES;
				while(TX_times)
				{
					TX_times--;
					yy_433m_TX_delay_8ms();
					if(TX_times == 3)		//最后四次延时一段较长时间当做第二次
						yy_433m_TX_delay_200ms();
					if(RX_data == YY_BULIAN_CONNECT)
					{
						TX_connectCode = CODE_BULIAN_CONNECT;
					}
					else if(RX_data == YY_SHALIAN_CONNECT)
					{
						TX_connectCode = CODE_SHALIAN_CONNECT;
					}
					yy_433m_sendCode(adr_yk_fixedCode, adr_yk,TX_connectCode);
				}
				TM2_OFF();
				if(RX_data == YY_BULIAN_CONNECT)
				{
					F_buLian_EN = SET;
					TX_buLianCode = CODE_BULIAN_OPEN;
				}
				else if(RX_data == YY_SHALIAN_CONNECT)
				{
					F_shaLian_EN = SET;
					TX_shaLianCode = CODE_SHALIAN_OPEN;
				}
				break;
			case YY_OPEN_CHUANGLIAN:	//打开窗帘
			case YY_CHUANGLIAN_OPEN_EX:	//窗帘全开
			case YY_OPEN_ALL:			//全部打开
				F_buLian_EN = SET;
				TX_buLianCode = CODE_BULIAN_OPEN;
				F_shaLian_EN = SET;
				TX_shaLianCode = CODE_SHALIAN_OPEN;
				break;
			case YY_CLOSE_CHUANGLIAN:	//关闭窗帘
			case YY_CHUANGLIAN_CLOSE_EX://窗帘全关
			case YY_CLOSE_ALL:			//全部关闭
				F_buLian_EN = SET;
				TX_buLianCode = CODE_BULIAN_CLOSE;
				F_shaLian_EN = SET;
				TX_shaLianCode = CODE_SHALIAN_CLOSE;
				break;
			case YY_OPEN_BULIAN:		//打开布帘
			case YY_OPEN_ZHEYANG:		//打开遮阳
				F_buLian_EN = SET;
				TX_buLianCode = CODE_BULIAN_OPEN;
				break;
			case YY_CLOSE_BULIAN:		//关闭布帘
			case YY_CLOSE_ZHEYANG:		//关闭遮阳
				F_buLian_EN = SET;
				TX_buLianCode = CODE_BULIAN_CLOSE;
				break;
			case YY_OPEN_SHALIAN:		//打开纱帘
			case YY_OPEN_ZHEGUANG:		//打开遮光
				F_shaLian_EN = SET;
				TX_shaLianCode = CODE_SHALIAN_OPEN;
				break;
			case YY_CLOSE_SHALIAN:		//关闭纱帘
			case YY_CLOSE_ZHEGUANG:		//关闭遮光
				F_shaLian_EN = SET;
				TX_shaLianCode = CODE_SHALIAN_CLOSE;
				break;
			case YY_CHUANGLIAN_STOP:	//窗帘停止
			case YY_STOP_CHUANGLIAN:	//停止窗帘
				F_buLian_EN = SET;
				TX_buLianCode = CODE_BULIAN_STOP;
				F_shaLian_EN = SET;
				TX_shaLianCode = CODE_SHALIAN_STOP;
				break;
			default:
				IO_RLED_N = !IO_RLED_N;
				break;
			}
			if (F_buLian_EN)
			{
				F_buLian_EN = RESET;
				TM2_ON();
				TX_times = SET_TX_TIMES;
				while(TX_times)
				{
					TX_times--;
					yy_433m_TX_delay_8ms();
					yy_433m_sendCode(adr_yk_fixedCode, adr_yk,TX_buLianCode);
				}
           		TM2_OFF();
			}
			if (F_shaLian_EN)
			{
				F_shaLian_EN = RESET;
				TM2_ON();
				TX_times = SET_TX_TIMES;
				while(TX_times)
				{
					TX_times--;
					yy_433m_TX_delay_8ms();
					yy_433m_sendCode(adr_yk_fixedCode, adr_yk,TX_shaLianCode);
				}
           		TM2_OFF();
			}
//			IO_IR_TX_clr;

/*
//$$$$$$$$$$$$-———-433M发送——————￥￥￥￥￥￥￥￥￥￥￥
			if(F_RX)
			{
                IO_RLED_N = !IO_RLED_N;
                TX_times = SET_TX_TIMES;
                while(TX_times)
                {
					TX_times--;
					TX_dataBit = SET_TX_DATA_BIT;
					TX_highTime = SET_HEAD_H_20US;
					TX_lowTime = SET_HEAD_L_20US;
					TM2_ON();
					TX_data = TX_data1;
					
					while(TX_dataBit)
					{
						if(TX_dataBit == SET_TX_DATA2_BIT)
						{
							TX_data = TX_data2;
						}
						if(!TX_lowTime)
						{
							if(TX_data & 0x80000000)
							{
								TX_highTime = SET_DATA_1_H_20US;
								TX_lowTime = SET_DATA_1_L_20US;
							}
							else
							{
								TX_highTime = SET_DATA_0_H_20US;
								TX_lowTime = SET_DATA_0_L_20US;
							}
							TX_data = TX_data<<1;
							TX_dataBit--;
						}
					}
					
					while(TX_lowTime);
					if(TX_times)
						TX_lowTime = SET_TX_DELAY_20US;
					while(TX_lowTime);
                }
			}
//			IO_IR_TX_clr;
            TM2_OFF();
			F_RX = RESET;
//===========================================================
*/

		}
	}

//===========================================================
//功能函数：yy_433m_send_head(void)
//输入参数：无
//===========================================================
void yy_433m_send_head(void)
{
	TX_highTime = SET_HEAD_H_20US;
	TX_lowTime = SET_HEAD_L_20US;
	while(TX_lowTime);
}

//===========================================================
//功能函数：yy_433m_send_8bit(u8 data)
//输入参数：data-发送8位数据
//===========================================================
void yy_433m_send_8bit(u8 data)
{
	u8 TX_data = 0;
	u8 TX_dataBit = 0;
	
	TX_data = data;
	TX_dataBit = 8;
	while(TX_dataBit)
	{
		if(!TX_lowTime)
		{
			if(TX_data & 0x80)
			{
				TX_highTime = SET_DATA_1_H_20US;
				TX_lowTime = SET_DATA_1_L_20US;
			}
			else
			{
				TX_highTime = SET_DATA_0_H_20US;
				TX_lowTime = SET_DATA_0_L_20US;
			}
			TX_data = TX_data<<1;
			TX_dataBit--;
		}
	}
	while(TX_lowTime);
}
//===========================================================
//功能函数：yy_433m_send_16bit(u16 data)
//输入参数：data-发送16位数据
//===========================================================
void yy_433m_send_16bit(u16 data)
{
	u16 TX_data = 0;
	u8 TX_dataBit = 0;
	
	TX_data = data;
	TX_dataBit = 16;
	while(TX_dataBit)
	{
		if(!TX_lowTime)
		{
			if(TX_data & 0x8000)
			{
				TX_highTime = SET_DATA_1_H_20US;
				TX_lowTime = SET_DATA_1_L_20US;
			}
			else
			{
				TX_highTime = SET_DATA_0_H_20US;
				TX_lowTime = SET_DATA_0_L_20US;
			}
			TX_data = TX_data<<1;
			TX_dataBit--;
		}
	}
	while(TX_lowTime);
}
//===========================================================
//功能函数：yy_433m_TX_delay_8ms，数据与数据之间发送间隔延迟
//输入参数：无
//===========================================================
void yy_433m_TX_delay_8ms()
{
	TX_lowTime = SET_TX_DELAY_20US;
	while(TX_lowTime);
}

//===========================================================
//功能函数：yy_433m_TX_delay_200ms，对码发送延迟
//输入参数：无
//===========================================================
void yy_433m_TX_delay_200ms(void)
{
	TX_lowTime = SET_CONNECT_DELAY_20US;
	while(TX_lowTime);
}

//===========================================================
//功能函数：yy_433m_sendCode(u8 adr_fixedCode,u16 adr,u16 code)
//输入参数：adr_fixedCode-地址确认码，adr-遥控地址码，code-执行码
//===========================================================
void yy_433m_sendCode(u8 adr_fixedCode,u16 adr,u16 code)
{
	yy_433m_send_head();
	yy_433m_send_8bit(adr_fixedCode);
	yy_433m_send_16bit(adr);
	yy_433m_send_16bit(code);
}

/*-------------------------------------------------
 * 	函数名称：EEPROMread
 * 	功能：   读EEPROM数据
 * 	输入参数：EEAddr 需读取数据的地址
 * 	返回参数；ReEEPROMread 对应地址读出的数据
 -------------------------------------------------*/
u8 EEPROMread(u8 EEAddr)
{
	u8 ReEEPROMread;
	EEADR = EEAddr;    
	RD = 1;
	ReEEPROMread = EEDAT;     			//EEPROM的读数据 ReEEPROMread = EEDATA;
	return ReEEPROMread;
}
/*-------------------------------------------------
 * 	函数名称：EEPROMwrite
 * 	功能：   写数据到EEPROM
 * 	输入参数：EEAddr 需要写入数据的地址
 *            Data 需要写入的数据
 * 	返回参数：无
 -------------------------------------------------*/
void EEPROMwrite(u8 EEAddr,u8 Data)
{							
	while(GIE)							//等待GIE为0
    {
		GIE=0;							//写数据必须关闭中?
    }		
	EEADR = EEAddr; 	 				//EEPROM的地址
	EEDAT = Data;		 				//EEPROM的写数据  EEDATA = Data;
	EEIF = 0;
	EECON1 |= 0x34;						//置位WREN1,WREN2,WREN3三个变量.
	WR = 1;								//置位WR启动编程
    NOP();
    NOP();
	while(WR);      					//等待EE写入完成
	GIE = 1;
}


