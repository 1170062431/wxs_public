//Project: yy_ir.prj
// Device: FT60F01X
// Memory: Flash 1KX14b, EEPROM 256X8b, SRAM 64X8b
// Author: 
//Company: 
//Version:
//   Date: 
//===========================================================
//===========================================================
	#include	"SYSCFG.h";
    
	#include "..\H\yy_ir.h"
//	#include "..\H\config.h"
	#include "..\H\mcu_sel.h"
	#include "..\H\ir_keyckde.h"
	
//===========================================================
//Variable definition
//===========================================================
	u8 RX_data,RX_dataBit,RX_dataNum,TX_dataBit;
    u16 RX_highTime,TX_highTime,TX_lowTime;
    u32 TX_data,TX_data1,TX_data2;
	FlagStatus F_feedDog,F_RX,RX_EN;
    
	FLAG Time_FLAG;	
    
	u8 UART_RX_buff[15]	= {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

//===========================================================
//Funtion name：interrupt ISR
//parameters：无
//returned value：无
//===========================================================
	void interrupt ISR(void)
	{
		if(TM0_E && TM0_F)
		{
			static u8 T_100us = 0;
			static u16 T_1ms = 0;
			TM0_F = RESET;
			TMR0 = 152;			//256-104，预分频4，定时104us,9600波特率
//			T_100us++;
//			if(T_100us == 10)
//			{
//                T_100us = 0;
//				T_1ms++;
//				if(T_1ms == 1000)
//                {
//                    T_1ms	= 0;
//                   IO_IR_TX = ~IO_IR_TX;
//                }
//			}
			
			if(RX_EN)
			{
                if(IO_MRST)
					RX_data = (RX_data>>1)|0x80;
				else
					RX_data >>= 1;
                RX_dataBit--;
                if(!RX_dataBit)
                {
                    UART_RX_buff[RX_dataNum] = RX_data;
					RX_EN = DISABLE;
                }
				return;
            }
		}
        
		if(TM2_E && TM2_F)		//13us
		{
			TM2_F = RESET;
            if(TX_highTime)
            {
                TX_highTime--;
				IO_IR_TX = ~IO_IR_TX;
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
        F_RX = RESET;
        RX_EN = DISABLE;
        TM0_OFF();
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
            while(IO_MRST)
            {
				CLRWDT();
            }	
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
			RX_data = UART_RX_buff[7];
			switch(RX_data)
			{
				case	0x00:IO_RLED_N = !IO_RLED_N; break;
    			case	0x01:IO_RLED_N = !IO_RLED_N; break;
//				case	0x02:TX_data1 = 0x0ff00ff0;		TX_data2 = 0x00000000;	F_RX = SET;	break;
				case	0x03:TX_data1 = IR_KEYCODE_power;		F_RX = SET;	break;		//原取暖一档
				case	0x04:TX_data1 = IR_KEYCODE_windSpd;		F_RX = SET;	break;		//原取暖二档
				case	0x05:TX_data1 = IR_KEYCODE_swing;			F_RX = SET;	break;		//摆风 原开启摇头
				case	0x06:TX_data1 = IR_KEYCODE_swing;			F_RX = SET; break;		//摆风 原关闭摇头
				case	0x07:TX_data1 = IR_KEYCODE_power;		F_RX = SET; break;		//原关闭取暖器
//				case	0x08:TX_data1 = 0x0ff00ff0;						F_RX = SET; break;
				case	0x09:TX_data1 = IR_KEYCODE_timer;			F_RX = SET; break;		//原打开定时
//				case	0x0a:TX_data1 = 0x0ff00ff0;						F_RX = SET; break;
//				case	0x0b:TX_data1 = 0x0ff00ff0;						F_RX = SET; break;
				case	0x0c:TX_data1 = IR_KEYCODE_windTyp;		F_RX = SET; break;		//原关闭定时
//				case	0x0d:TX_data1 = 0x0ff00ff0;						F_RX = SET; break;
//				case	0x0e:TX_data1 = 0x0ff00ff0;						F_RX = SET; break;
//				case	0x0f:TX_data1 = 0x0ff00ff0;						F_RX = SET; break;
				default:break;
			}
            
//$$$$$$$$$$$$-———-红外发送——————￥￥￥￥￥￥￥￥￥￥￥
			if(F_RX)
			{
				TX_dataBit = 32;
				TX_highTime = 692;
//				TX_highTime = 346;		//空调高低起始位相同
				TX_lowTime = 346;
				TM2_ON();
                TX_data = TX_data1;
				while(TX_dataBit)
                {
//					if(TX_dataBit == 16)
//					{
//						TX_data = TX_data2;
//					}
					if(!TX_lowTime)
					{
						if(TX_data & 0x80000000)
						{
							TX_highTime = 43;		//560us/13us
							TX_lowTime = 129;		//1680us/13us
						}
						else
						{
							TX_highTime = 43;
							TX_lowTime = 43;
						}
						TX_data = TX_data<<1;
						TX_dataBit--;
					}
                }
				while(TX_lowTime);
				TX_highTime = 43;			//560us结束码
				while(TX_highTime);
                IO_IR_TX_clr;
				TM2_OFF();
			}
            
			F_RX = RESET;
		}
	}
//===========================================================
