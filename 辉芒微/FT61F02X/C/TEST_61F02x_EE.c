/*  �ļ�����TEST_61F02x_EE.C
*	���ܣ�  FT61F02x-�ڲ�EE������ʾ
*   IC:    FT61F023 SOP16
*   ����  16M /2T                    
*   ˵���� 	����ʾ����Ϊ61F02x EERROM����ʾ����.
*		  	�ó����ȡ0x12��ַ��ֵ,ȡ�������0x13��ַ.

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
 *	�������ƣ�EEPROMread
 *	���ܣ�   ��EEPROM����
 *	���������EEAddr ���ȡ���ݵĵ�ַ
 *	���ز�����ReEEPROMread ��Ӧ��ַ����������
 ----------------------------------------------------*/
unsigned char EEPROMread(unsigned char EEAddr)
{
	unsigned char ReEEPROMread;

	EEADR = EEAddr;    
	RD = 1;
	ReEEPROMread = EEDAT;     //EEPROM�Ķ����� ReEEPROMread = EEDATA;
	return ReEEPROMread;
}

/*---------------------------------------------------- 
 *	�������ƣ�EEPROMwrite
 *	���ܣ�   д���ݵ�EEPROM
 *	���������EEAddr ��Ҫд�����ݵĵ�ַ
 *	        Data ��Ҫд�������
 *	���ز�������
 ----------------------------------------------------*/
void EEPROMwrite(unsigned char EEAddr,unsigned char Data)
{
	
	while(GIE)			//�ȴ�GIEΪ0
		{GIE=0;}			//д���ݱ���ر��ж�
	EEADR = EEAddr; 	 	//EEPROM�ĵ�ַ
	EEDAT = Data;		 	//EEPROM��д����  EEDATA = Data;
	EEIF = 0;
	EECON1 |= 0x34;			//��λWREN1,WREN2,WREN3��������.
	WR = 1;					//��λWR�������
    NOP();
    NOP();
	while(WR);      		//�ȴ�EEд�����
	GIE = 1;
}