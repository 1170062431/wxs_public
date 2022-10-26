#include "sdk_cfg.h"
#include "led.h"
#include "timer.h"
#include "clock_api.h"
#include "common.h"
#include "board_init.h"
#include "bluetooth/bt_led.h"
#include "key.h"
#include "user_ad.h"
#include "adc_api.h"

#ifdef SUPPORT_MS_EXTENSIONS
#pragma bss_seg(	".system_bss")
#pragma data_seg(	".system_data")
#pragma const_seg(	".system_const")
#pragma code_seg(	".system_code")
#endif

u16 user_getAD(u32 channel)
{
	static u16 adBuf = 0;
	u16 adc_con_tmp = 0;

	while (!(BIT(7) & JL_ADC->CON)); 	 //wait pending
	adBuf = JL_ADC->RES;

	adc_con_tmp = JL_ADC->CON & (~0x0F00);
	JL_ADC->CON = adc_con_tmp | (channel & 0xFFFF);		//channel; //AD channel select
	if((channel & 0xFFFF) == AD_CH_RTC)
	{
		adc_mux_ch_set((channel & 0xFFFF0000) >> 16);
	}
	else if((channel & 0xFFFF) == AD_CH_PMU)
	{
		adc_ldo_ch_sel((channel & 0xFFFF0000) >> 16);
	}
	else if((channel & 0xFFFF) == AD_CH_BT)
	{
		WLA_CON0 |= ((0x1 & 0X1) << 0) | \
				   ((0x0 & 0X1) << 1) | \
				   ((0x1 & 0X3) << 2) | \
				   ((0x08 & 0X1f) << 6) | \
				   ((0x2 & 0x3) << 11) | \
				   ((0x8 & 0xf) << 13);
	}
	JL_ADC->CON |=  BIT(6);					//AD start
	JL_ADC->CON &= ~BIT(7);
	while (!(JL_ADC->CON & BIT(7)));		//wait pending
	
	adBuf = JL_ADC->RES;
//	adBuf = adc_res_api(channel);

	return adBuf;
}

#if	0
LOOP_UI_REGISTER(user_getAD_detect) = {
    .time = 500,
    .fun  = user_getAD,
};
#endif


