#include "pwm.h"

#if(PWM1A_EN|PWM1B_EN|PWM2A_EN|PWM2B_EN)
//-------------------------------------------------------------------
//��������pwmInit()
//��������
//�������
//-------------------------------------------------------------------
void pwmInit()
{
#if(PWM1A_EN|PWM1B_EN)
	TIM1_ARRH = 100/256; 	// ����TIMER1��������������100us 
	TIM1_ARRL = 100%256;
	
	#if PWM1A_EN
	PT1_GOE |= PWM_CH_TM1_A;
	
	TIM1_GCMARH = 0/256;	// TIM1_CHA�����0%
	TIM1_GCMARL = 0%256;
	
	TIM1_PCONRA = 0x10;  	// �Ƚ������ʼֵΪ0���򿪱Ƚ�ģʽ������ֵС�ڱȽ�ֵΪ 1������Ϊ 0
//	TIM1_PCONRA = 0x50;  	// �Ƚ������ʼֵΪ0���򿪱Ƚ�ģʽ���Ƚ�ֵ��ȵ�ʱ�����ȡ��
//	TIM1_PCONRA = 0xd0;  	// �Ƚ������ʼֵΪ1���򿪱Ƚ�ģʽ���Ƚ�ֵ��ȵ�ʱ�����ȡ��
//	TIM1_PCONRA = 0xd0;  	// �Ƚ������ʼֵΪ1���򿪱Ƚ�ģʽ���Ƚ�ֵ��ȵ�ʱ�����ȡ��
	#endif

	#if PWM1B_EN
	PT1_GOE |= PWM_CH_TM1_B;
	
	TIM1_GCMBRH = 0/256;	// TIM1_CHA�����0%
	TIM1_GCMBRL = 0%256;
	
	TIM1_PCONRB = 0x10;  	// �Ƚ������ʼֵΪ0���򿪱Ƚ�ģʽ������ֵС�ڱȽ�ֵΪ 1������Ϊ 0
//	TIM1_PCONRB = 0x50;  	// �Ƚ������ʼֵΪ0���򿪱Ƚ�ģʽ���Ƚ�ֵ��ȵ�ʱ�����ȡ��
//	TIM1_PCONRB = 0xd0;  	// �Ƚ������ʼֵΪ1���򿪱Ƚ�ģʽ���Ƚ�ֵ��ȵ�ʱ�����ȡ��
//	TIM1_PCONRB = 0xd0;  	// �Ƚ������ʼֵΪ1���򿪱Ƚ�ģʽ���Ƚ�ֵ��ȵ�ʱ�����ȡ��
	#endif
	
	TIM1_CR = 0x01; 		// ����TIMER1���ϼ�������ݲ�����ģʽ
//	TIM1_CR = 0x02; 		// ����TIMER1���ϼ��������ǲ�ģʽA

	TIM1_FCONR = 0x0f;		// ����TIMER1ʱ��Դ����SYSCLK��Ԥ��Ƶ16��Ƶ
	
	TIM1_DTUA = 0;			// ��������Ϊ0��TIMER1�������ڣ� 0����
//	TIM1_DTUA = 5;			// ��������Ϊ5��TIMER1�������ڣ� 5us����

	TIM1_DTR = 0x00;		// Ӳ����������ر�
//	TIM1_DTR = 0x14;		// Ӳ����������򿪣�ʹ��TIM1_CHB������������������IO1_DR[7]����
	

	TIM1_IE = 0x00;  		// ʹ��TIM1_CHA��TIM1_CHB�Ƚ��ж�
//	TIM1_IE = 0x0c;  		// ʹ��TIM1_CHA��TIM1_CHB�Ƚ��ж�

	TIM1_CR = TIM1_CR|0x01;	// ʹ�ܶ�ʱ��1
#endif

#if(PWM2A_EN|PWM2B_EN)
	TIM2_ARRH = 100/256; 	// ����TIMER1��������������100us 
	TIM2_ARRL = 100%256;
	
	#if PWM2A_EN
	PT2_GOE |= PWM_CH_TM2_A;
	
	TIM2_GCMARH = 0/256;	// TIM2_CHA�����0%
	TIM2_GCMARL = 0%256;
	
	TIM2_PCONRA = 0x10;  	// �Ƚ������ʼֵΪ0���򿪱Ƚ�ģʽ������ֵС�ڱȽ�ֵΪ 1������Ϊ 0
//	TIM2_PCONRA = 0x50;  	// �Ƚ������ʼֵΪ0���򿪱Ƚ�ģʽ���Ƚ�ֵ��ȵ�ʱ�����ȡ��
//	TIM2_PCONRA = 0xd0;  	// �Ƚ������ʼֵΪ1���򿪱Ƚ�ģʽ���Ƚ�ֵ��ȵ�ʱ�����ȡ��
//	TIM2_PCONRA = 0xd0;  	// �Ƚ������ʼֵΪ1���򿪱Ƚ�ģʽ���Ƚ�ֵ��ȵ�ʱ�����ȡ��
	#endif

	#if PWM2B_EN
	PT2_GOE |= PWM_CH_TM2_B;
	
	TIM2_GCMBRH = 0/256;	// TIM2_CHA�����0%
	TIM2_GCMBRL = 0%256;
	
	TIM2_PCONRB = 0x10;  	// �Ƚ������ʼֵΪ0���򿪱Ƚ�ģʽ������ֵС�ڱȽ�ֵΪ 1������Ϊ 0
//	TIM2_PCONRB = 0x50;  	// �Ƚ������ʼֵΪ0���򿪱Ƚ�ģʽ���Ƚ�ֵ��ȵ�ʱ�����ȡ��
//	TIM2_PCONRB = 0xd0;  	// �Ƚ������ʼֵΪ1���򿪱Ƚ�ģʽ���Ƚ�ֵ��ȵ�ʱ�����ȡ��
//	TIM2_PCONRB = 0xd0;  	// �Ƚ������ʼֵΪ1���򿪱Ƚ�ģʽ���Ƚ�ֵ��ȵ�ʱ�����ȡ��
	#endif
	
	TIM2_CR = 0x01; 		// ����TIMER1���ϼ�������ݲ�����ģʽ
//	TIM2_CR = 0x02; 		// ����TIMER1���ϼ��������ǲ�ģʽA
	
	TIM2_FCONR = 0x0f;		// ����TIMER1ʱ��Դ����SYSCLK��Ԥ��Ƶ16��Ƶ
	
	TIM2_DTUA = 0;			// ��������Ϊ0��TIMER1�������ڣ� 0����
//	TIM2_DTUA = 5;			// ��������Ϊ5��TIMER1�������ڣ� 5us����

	TIM2_DTR = 0x00;		// Ӳ����������ر�
//	TIM2_DTR = 0x14;		// Ӳ����������򿪣�ʹ��TIM2_CHB������������������IO1_DR[7]����

	TIM1_IE = 0x00; 		// ʹ��TIM1_CHA��TIM1_CHB�Ƚ��ж�
//	TIM1_IE = 0x0c; 		// ʹ��TIM1_CHA��TIM1_CHB�Ƚ��ж�

	TIM2_CR = TIM2_CR|0x01;	// ʹ�ܶ�ʱ��1
#endif
}

//---------------------------------------------------------------------------------------
//��������setPwm(uchar chanel,uint pwm_p,uchar pwm_d)
//������chanel-pwmͨ����PWM_CH_TMx_x����pwm_p-����100us~10000us����ӦƵ��10K~100��pwm_d-ռ�ձ�0~pwm_p
//�������
//---------------------------------------------------------------------------------------
void setPwm(uchar chanel,uint pwm_p,uchar pwm_d)
{
	switch(chanel)
	{
	case PWM_CH_TM1_A:
		TIM1_ARRH = pwm_p>>8; // ����TIMER1��������������100us 
		TIM1_ARRL = pwm_p;			//pwm_p%256
		TIM1_GCMARH = pwm_d>>8;		// TIM1_CHA�����50%
		TIM1_GCMARL = pwm_d;		//pwm_d%256
		break;
	case PWM_CH_TM1_B:
		TIM1_ARRH = pwm_p>>8; // ����TIMER1��������������100us 
		TIM1_ARRL = pwm_p;			//pwm_p%256
		TIM1_GCMBRH = pwm_d>>8;		// TIM1_CHA�����50%
		TIM1_GCMBRL = pwm_d;		//pwm_d%256
		break;
	case PWM_CH_TM2_A:
		TIM2_ARRH = pwm_p>>8; // ����TIMER1��������������100us 
		TIM2_ARRL = pwm_p;			//pwm_p%256
		TIM2_GCMARH = pwm_d>>8;		// TIM1_CHA�����50%
		TIM2_GCMARL = pwm_d;		//pwm_d%256
		break;
	case PWM_CH_TM2_B:
		TIM2_ARRH = pwm_p>>8; // ����TIMER1��������������100us 
		TIM2_ARRL = pwm_p;			//pwm_p%256
		TIM2_GCMBRH = pwm_d>>8;		// TIM1_CHA�����50%
		TIM2_GCMBRL = pwm_d;		//pwm_d%256
		break;
	default:
		break;
	}
}

#endif
