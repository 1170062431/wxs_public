#ifndef _REC433_H_
#define _REC433_H_

/*********************************************************/
/********************************************************
		"1:1100us�ߵ�ƽ+400us�͵�ƽ
		0:400us�ߵ�ƽ+1100us�͵�ƽ
		������ʼλ10ms�͵�ƽ"					
		A	10101001 00001111 00101000 0			
		B	10101001 00001111 00100100 0			
		C	10101001 00001111 00100010 0			
		D	10101001 00001111 00100001 0			
/*********************************************************/
/*********************************************************/
//433M��������
#define SET_433M_REC_BIT_MAX		32		//����433M������λ��
#define SET_433M_REC_DATA_START_BIT	1		//����433M����������ʼλ
#define SET_433M_REC_DATA_STOP_BIT	32		//����433M�������ݽ���λ

#define SET_433M_START_L_TIME_MIN_125US		74	//��ʼλ�͵�ƽʱ��10ms-80
#define SET_433M_START_L_TIME_MAX_125US		86
/*
#define SET_433M_START_H_TIME_MIN_125US		30	//��ʼλ�ߵ�ƽʱ��4.5ms-36
#define SET_433M_START_H_TIME_MAX_125US		42
*/
#define SET_433M_DATA_0_L_TIME_MIN_125US	6	//����0�͵�ƽʱ��1100us-8.8
#define SET_433M_DATA_0_L_TIME_MAX_125US	11

#define SET_433M_DATA_0_H_TIME_MIN_125US	1	//����0�ߵ�ƽʱ��400us-3.2
#define SET_433M_DATA_0_H_TIME_MAX_125US	7

#define SET_433M_DATA_1_L_TIME_MIN_125US	1	//����1�͵�ƽʱ��400us-3.2
#define SET_433M_DATA_1_L_TIME_MAX_125US	7

#define SET_433M_DATA_1_H_TIME_MIN_125US	6	//����1�ߵ�ƽʱ��1100us-8.8
#define SET_433M_DATA_1_H_TIME_MAX_125US	11
/*
#define SET_433M_LXM_H_TIME_MIN_125US 		14	//������ߵ�ƽʱ��2.2ms-17.6
#define SET_433M_LXM_H_TIME_MAX_125US 		28
*/
#define SET_433M_DATA2DATA_TIME_125US 		888//1200	//���ݼ��96ms-768,150ms-1200

extern bit F_keyDone_433M;		//����������
extern unsigned long keyCode_433M;
/*********************************************************/
/*********************************************************/
void rec433M();

#endif