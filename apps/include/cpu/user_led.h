
#ifndef _USER_LED_H_
#define _USER_LED_H_

#include "user_project.h"

#define user_ledOn()	do{PORTR_DIR(1, 0); PORTR_OUT(1, 1);}while(0)
#define user_ledOff()	do{PORTR_DIR(1, 0); PORTR_OUT(1, 0);}while(0)
//#define user_ledOn()	do{JL_PORTA->DIR &= ~BIT(2); JL_PORTA->OUT |=  BIT(2);}while(0)
//#define user_ledOff()	do{JL_PORTA->DIR &= ~BIT(2); JL_PORTA->OUT &= ~BIT(2);}while(0)

void user_led_scan();

#endif

