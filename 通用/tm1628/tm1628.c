	#include "..\H\tm1628.h"
	#include "..\USER_PROGRAM\USER_PROGRAM.H"
	
//|	SEG1 SEG2 SEG3 SEG4 | SEG5 SEG6 SEG7 SEG8 | SEG9  SEG10   X  SEG12 | SEG13 SEG14  X   X	 |
//|		xxHL（低四位）  |	xxHU(高四位)	  |    	xxHL(低四位)       | 	xxHU（高四位）   |
//|	B0    B1   B2   B3  |   B4   B5   B6   B7 |    B0   B1    B2   B3  |   B4   B5    B6  B7 |
//|			00HL		|	   	  00HU		  |		 	  01HL		   |		  01HU 		 |	GRID1
//|			02HL 		|		  02HU 		  |			  03HL		   |	      03HU 		 |	GRID2 
//|			04HL 		|		  04HU 		  |			  05HL 		   |	 	  05HU 	 	 |	GRID3 
//|			06HL 		|		  06HU 		  |			  07HL 		   |		  07HU 		 |	GRID4
//|			08HL		|		  08HU 		  |			  09HL 		   |		  09HU 		 |	GRID5
//|			0AHL 		|		  0AHU 		  |			  0BHL 		   |		  0BHU 		 |	GRID6
//|			0CHL 		|		  0CHU 		  |			  0DHL 		   |	 	  0DHU 		 |	GRID7
		
	u8 LEDDispBuff[7] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00};
//	u8 LEDDispBuff[14] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	
	u8 KeyMap[5] = {0x00,0x00,0x00,0x00,0x00};		// 为存储按键值开辟的数组
	
	void tm1628Init()
	{
		command(Set_DispMode_7Grid10Seg);				//设置显示模式，7位10段模式 
		command(Set_Nomal_AutoAddADR_Write2Disp);		//设置数据命令,采用地址自动加1模式 
	}
	
//	向TM1628发送8位数据,从低位开始-------------------------------------
	void send_8bit(uint8 dat)
	{
		uint8 i;
		for(i=0;i<8;i++)
		{
			if(dat&0x01)
				IO_DIOSet;
			else
				IO_DIOClr;
			IO_CLKClr;
			IO_CLKSet;
			dat = dat>>1;
		}
	}
	
//	向TM1628发送命令--------------------------------------------------
	void command(uint8 com)
	{
		IO_STBSet;
		IO_STBClr;
		send_8bit(com);
	}
	
//	读取按键值并存入KEY[]数组，从低字节开始，从低位开始--------------------------------------------------
//	void read_key()
//	{
//		uint8 i,j;
//		command(Set_Nomal_ReadKeyMap);	//读键盘命令
//		IO_DIOSet;						//发送读按键命令后，需将DIO置高，才能读回正确的按键数据，否则读到的数据将全是“0”
//		for(j=0;j<5;j++)
//		{
//			for(i=0;i<8;i++)
//			{
//				KeyMap[j] = KeyMap[j]>>1;
//				IO_CLKClr;
//				IO_CLKSet;
//				if(IO_DIO)
//					KeyMap[j] = KeyMap[j]|0x80;
//			}
//		}
//		IO_STBSet;
//	}
		
//	显示函数--------------------------------------------------
	void displayLED()
	{
		uint8 i;
		command(Set_DispAdr_00H);			//设置显示地址，从00H开始 
		for(i=0;i<7;i++)					//发送显示数据
		{
			send_8bit(LEDDispBuff[i]);
			send_8bit(0x00);
		}
		command(Set_DispOn_LightLevel14); 	//显示控制命令，打开显示并设置为最亮 
//		read_key() ; 						//读按键值
		IO_STBSet;
	}
	
//	void displayLED()
//	{
//		uint8 i;
//		command(Set_DispAdr_00H);			//设置显示地址，从00H开始 
//		for(i=0;i<14;i++)					//发送显示数据
//		{
//			send_8bit(LEDDispBuff[i]);
//		}
//		command(Set_DispOn_LightLevel14); 	//显示控制命令，打开显示并设置为最亮 
////		read_key() ; 						//读按键值
//		IO_STBSet;
//	}
	
//	按键处理函数
//	void key_process()
//	{ 
//		// 由用户编写 
//	}