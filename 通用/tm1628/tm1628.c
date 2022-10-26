	#include "..\H\tm1628.h"
	#include "..\USER_PROGRAM\USER_PROGRAM.H"
	
//|	SEG1 SEG2 SEG3 SEG4 | SEG5 SEG6 SEG7 SEG8 | SEG9  SEG10   X  SEG12 | SEG13 SEG14  X   X	 |
//|		xxHL������λ��  |	xxHU(����λ)	  |    	xxHL(����λ)       | 	xxHU������λ��   |
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
	
	u8 KeyMap[5] = {0x00,0x00,0x00,0x00,0x00};		// Ϊ�洢����ֵ���ٵ�����
	
	void tm1628Init()
	{
		command(Set_DispMode_7Grid10Seg);				//������ʾģʽ��7λ10��ģʽ 
		command(Set_Nomal_AutoAddADR_Write2Disp);		//������������,���õ�ַ�Զ���1ģʽ 
	}
	
//	��TM1628����8λ����,�ӵ�λ��ʼ-------------------------------------
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
	
//	��TM1628��������--------------------------------------------------
	void command(uint8 com)
	{
		IO_STBSet;
		IO_STBClr;
		send_8bit(com);
	}
	
//	��ȡ����ֵ������KEY[]���飬�ӵ��ֽڿ�ʼ���ӵ�λ��ʼ--------------------------------------------------
//	void read_key()
//	{
//		uint8 i,j;
//		command(Set_Nomal_ReadKeyMap);	//����������
//		IO_DIOSet;						//���Ͷ�����������轫DIO�øߣ����ܶ�����ȷ�İ������ݣ�������������ݽ�ȫ�ǡ�0��
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
		
//	��ʾ����--------------------------------------------------
	void displayLED()
	{
		uint8 i;
		command(Set_DispAdr_00H);			//������ʾ��ַ����00H��ʼ 
		for(i=0;i<7;i++)					//������ʾ����
		{
			send_8bit(LEDDispBuff[i]);
			send_8bit(0x00);
		}
		command(Set_DispOn_LightLevel14); 	//��ʾ�����������ʾ������Ϊ���� 
//		read_key() ; 						//������ֵ
		IO_STBSet;
	}
	
//	void displayLED()
//	{
//		uint8 i;
//		command(Set_DispAdr_00H);			//������ʾ��ַ����00H��ʼ 
//		for(i=0;i<14;i++)					//������ʾ����
//		{
//			send_8bit(LEDDispBuff[i]);
//		}
//		command(Set_DispOn_LightLevel14); 	//��ʾ�����������ʾ������Ϊ���� 
////		read_key() ; 						//������ֵ
//		IO_STBSet;
//	}
	
//	����������
//	void key_process()
//	{ 
//		// ���û���д 
//	}