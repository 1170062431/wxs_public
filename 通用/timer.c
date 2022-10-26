#include "timer.h"
#include "basic_include.h"

void timer0Init()
{
	/* ���ö�ʱ��0 */
	TIM0_CR  = 0x06;			// ѡ��ϵͳʱ��16MHz/4��Ƶ
	TIM0_ARR = 250;				// �Զ���װ����250����ʱ125us
	TIM0_IE  = 0x01;			// ��TIMER0�ж�
	TIM0_CR  = TIM0_CR | 0x01;	// ʹ��TIMER0
}

void timer1Init()
{
	/* ���ö�ʱ��1 */
	TIM1_CR      = 0x00;                // ��ʱ��1���ϼ�������ݲ�ģʽ
	TIM1_FCONR   = 0x0f;                // TIMER1ʱ��Դѡ��ϵͳʱ�ӣ�Ԥ��Ƶ16��Ƶ

	TIM1_PCONRA    = 0x03;             	// ʹ��TIMER1 TIM1_CHAͨ����׽�������ز�׽
	TIM1_PCONRB    = 0x03;             	// ʹ��TIMER1 TIM1_CHBͨ����׽�������ز�׽
	TIM1_IE        = 0x0c;             	// ʹ��TIMER1 ��׽�ͱȽ��ж�

	TIM1_ARRH    = 10000/256;           // �������ֵ10ms
	TIM1_ARRL    = 10000%256;
	TIM1_IE      = 0x01;                // ʹ�������ж�
	TIM1_CR      = TIM1_CR|0x01;        // ʹ��TIMER1
}

