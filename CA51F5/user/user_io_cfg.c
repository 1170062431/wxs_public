#include "user_io_cfg.h"

void io_init()
{	 
	SET_IO_CFG(IO_IR_REC_CFG,PU_OPEN,PD_CLOSE,OPR_CLOSE,INPUT);
	SET_IO_SEL(IO_IR_REC_SEL,SMIT_EN,PU_STRONG,PD_STRONG,DRV_LV3,SL_LV3);

	SET_IO_CFG(IO_KEY_PWR_CFG,PU_OPEN,PD_CLOSE,OPR_CLOSE,INPUT);
	SET_IO_SEL(IO_KEY_PWR_SEL,SMIT_EN,PU_STRONG,PD_STRONG,DRV_LV3,SL_LV3);

	SET_IO_CFG(IO_LED_DAT_CFG,PU_CLOSE,PD_CLOSE,OPR_CLOSE,P34_PWM2_SETTING);
	SET_IO_SEL(IO_LED_DAT_SEL,SMIT_EN,PU_STRONG,PD_STRONG,DRV_LV3,SL_LV3);
	IO_LED_DAT = 0;

	SET_IO_CFG(IO_MIC_AD_CFG,PU_OPEN,PD_CLOSE,OPR_CLOSE,INPUT);
	SET_IO_SEL(IO_MIC_AD_SEL,SMIT_EN,PU_WEEK,PD_WEEK,DRV_LV3,SL_LV3);

	keySta = 0;
	keyCode = IRKEY_NON;

	light.sta = STA_POWEROFF;
	light.brightness = LED_BRIGHTNESS_MAX;
	light.mode = MODE_qiCaiLiuShui;
 	light.rgb = 0;
	light.num = LED_NUM;
	light.gap = 0;
	light.speed = LED_SPEED_MAX;
	light.dir = 0;
	light.mic = 0;
}

