#ifndef _PWM_H_
#define _PWM_H_

#include "basic_include.h"

#define PWM1A_EN		0
#define PWM1B_EN		0
#define PWM2A_EN		1
#define PWM2B_EN		1

#define PWM_CH_LED_W	PWM_CH_TM2_B
#define PWM_CH_LED_WR	PWM_CH_TM2_A

#define PWM_CH_TM1_A	0x40
#define PWM_CH_TM1_B	0x80
#define PWM_CH_TM2_A	0x01
#define PWM_CH_TM2_B	0x02

void pwmInit();
void setPwm(uchar chanel,uint pwm_p,uchar pwm_d);

#endif