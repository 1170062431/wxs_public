#include "sdk_cfg.h"
#include "led.h"
#include "timer.h"
#include "clock_api.h"
#include "common.h"
#include "board_init.h"
#include "bluetooth/bt_led.h"
#include "key.h"
#include "user_led.h"
#include "adc_api.h"
#include "rtc/rtc_api.h"
#include "key_drv_ad.h"
#include "power.h"

#ifdef SUPPORT_MS_EXTENSIONS
#pragma bss_seg(	".system_bss")
#pragma data_seg(	".system_data")
#pragma const_seg(	".system_const")
#pragma code_seg(	".system_code")
#endif

void user_led_scan()
{
    static bool F_LED = 0;
	F_LED = !F_LED;
	if(F_LED)
	{
		user_ledOn();
//		log_printf("USER_LED_ON\n");
	}
	else
	{
		user_ledOff();
//		log_printf("USER_LED_OFF\n");
	}
}

/*
LOOP_DETECT_REGISTER(user_led_scan_detect) = {
//LOOP_UI_REGISTER(user_led_scan_detect) = {
//TWS_DETECT_REGISTER(user_led_scan_detect) = {
//USLOOP_DETECT_REGISTER(user_led_scan_detec) = {
    .time = 250,
    .fun  = user_led_scan,
};
*/



