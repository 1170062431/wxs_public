#include "sdk_cfg.h"
#include "led.h"
#include "timer.h"
#include "clock_api.h"
#include "clock_interface.h"
#include "common.h"
#include "board_init.h"
#include "bluetooth/bt_led.h"
#include "key.h"
#include "adc_api.h"
#include "rtc/rtc_api.h"
#include "key_drv_ad.h"
#include "power.h"
#include "key_drv_ir.h"
#include "irq_api.h"
#include "uart.h"
#include "user_pwm.h"

u16 pwmBoostDuty,pwmLedRDuty,pwmLedWDuty;

#if USER_PWM1_EN
void timer1_isr_fun(void)
{
	USER_CLR_PWM1_PCLR;
//	log_printf("timer1_isr_fun!!!");
}

IRQ_REGISTER(IRQ_TIME1_IDX, timer1_isr_fun);

void timer1_init(void)
{
//	JL_TIMER1->CON = 0;
	JL_TIMER1->CON = (USER_SET_PWM1_PWM_INV<<9)|(USER_SET_PWM1_PSET3_0<<4)|(USER_SET_PWM1_SSEL1_0<<2)|USER_SET_PWM1_MODE1_0;

    IRQ_REQUEST(IRQ_TIME1_IDX, timer1_isr_fun);

    JL_TIMER1->CNT = 0;
	#if 1	//1
    USER_SET_PWM1_PRD(SET_USER_BOOST_DUTY);		//0x0030~0x07FF,48~2047,超过此范围需要分频
    USER_SET_PWM1_PWM(0);
	USER_SET_PWM1_ON;
	#else	//test
    USER_SET_PWM1_PRD(SET_USER_BOOST_DUTY);		//0x0030~0x07FF,48~2047,超过此范围需要分频
    USER_SET_PWM1_PWM(0);
	USER_SET_PWM1_ON;
	#endif
//	log_printf("timer1_init OK!!!");
}
#endif

