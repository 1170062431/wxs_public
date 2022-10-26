#include "sdk_cfg.h"
#include "led.h"
#include "timer.h"
#include "clock_api.h"
#include "common.h"
#include "board_init.h"
#include "bluetooth/bt_led.h"
#include "key.h"
#include "adc_api.h"
#include "audio/audio.h"
#include "audio/dac_api.h"
#include "task_bt.h"
#include "avctp_user.h"
#include "power.h"
#include "warning_tone.h"
#include "power_manage_api.h"
#include "music_player.h"
#include "msg.h"
#include "bt_tws.h"
#include "user_project.h"
#include "user_pwm.h"
#include "user_ad.h"

PRO AMQ;
u8 AMQ_state[AMQ_STA_END] = { 0 };

u8 vLevel;
u8 powerLevel;
u8 btStata;
u16 T_ledOn_s;
u8 F_powerOn,F_powerOff,F_lowPower,F_pause;
u8 C_powerOff_1s;

u16 T_idle_1s = 0;//运行15分钟关机,待机2分钟无操作关机

u8 F_isVin = 0;		//充电插入状态，0=无充电器插入,1=有充电器插入

void irq_global_disable(void);
void irq_sys_disable(void);

void user_io_init()
{
	static u8 F_init = 0;

	SET_ICTX_BTRX_in;
	IO_ICTX_BTRX_puOn;

	SET_ICRX_BTTX_out;
	IO_ICRX_BTTX_set;

	SET_DM_in;
	IO_DM_puOn;

	SET_isSTDBY_in;
	IO_isSTDBY_puOn;

	SET_DP_in;
	IO_DP_puOff;

	SET_PWM_BOOST_in;
	IO_PWM_BOOST_puOff;

	SET_MUTE_EN_out;
	IO_MUTE_EN_set;

	SET_PA3_in;
	IO_PA3_puOff;
//---------------------
//---------------------
	SET_433M_REC_in;
	IO_433M_REC_puOn;

	SET_isCHRG_in;
	IO_isCHRG_puOn;

	SET_AD_KEY_in;
//	IO_AD_KEY_puOff;
	IO_AD_KEY_puOn;

	AMQ.sta = STA_POWEROFF;
	AMQ.speedLevel = SPEEDLEVEL_OFF;
	AMQ.heatLevel = HEAT_LEVEL_OFF;
	AMQ.massage_type = 0;
	AMQ.C_timer_s = 900;
	AMQ.mute_en = 0;

	#if USER_TEST_EN
	btStata = BT_STATA_SCAN;
	#else
	btStata = BT_STATA_IDEL;
	#endif
	T_ledOn_s = 0;
	T_idle_1s = 0;
	powerLevel = POWER_LEVEL_L;
	vLevel = 0;
	F_powerOn = 0;
	F_powerOff = 0;
	F_lowPower = 0;
	F_pause = 0;
//	F_init = 1;

	C_powerOff_1s = SET_POWOFF_TIME_S;

	rtc_port_4s_reset_close();
}

void user_btStataScan()	//10ms
{
	static u8 T_btStataLedOn_10ms = 0;
	static u8 T_charge_10ms = 0, T_lowpower_10ms = 0;
	static u16 C_charged_10ms = 0;
	static u16 AD_Vbat_backup = 0,C_AD_Vbat_delay_10ms = 0;
	u16 stata = 0, temp = 0;
	u8 F_ble_updata = 0;

#if	BT_EN
	stata = get_bt_connect_status();
	switch(stata)
	{
	case BT_STATUS_INITING:          /*正在初始化*/
	case BT_STATUS_WAITINT_CONN:     /*等待连接*/
	case BT_STATUS_AUTO_CONNECTINT:  /*正在回连*/
	//	if(btStata == BT_STATA_IDEL)
	//		user_send_cmd_prepare(USER_CTRL_POWER_OFF, 0, NULL);
	//	else
			btStata = BT_STATA_SCAN;
		break;
	case BT_STATUS_TAKEING_PHONE:    /*正在电话*/
		break;
	case BT_STATUS_CONNECTING:       /*已连接，没有电话和音乐在活动*/
		btStata = BT_STATA_CONNECT;
		break;
	case BT_STATUS_PLAYING_MUSIC:    /*正在音乐*/
		btStata = BT_STATA_PLAY_MISIC;
		break;
	default:
		break;
	}
#endif
			
//##########################################################
//##########################################################
//同步BLE状态更新
	if(AMQ.sta == STA_RUNNING)
	{
		if(AMQ_state[AMQ_STA_START1_STOP0] != 1)
		{
			AMQ_state[AMQ_STA_START1_STOP0] = 1;
			F_ble_updata = 1;
		}
	}
	else if(AMQ_state[AMQ_STA_START1_STOP0])
	{
		AMQ_state[AMQ_STA_START1_STOP0] = 0;
		F_ble_updata = 1;
	}
	if(AMQ_state[AMQ_STA_HEAT_LEVEL] != AMQ.heatLevel)
	{
		AMQ_state[AMQ_STA_HEAT_LEVEL] = AMQ.heatLevel;
		F_ble_updata = 1;
	}
	if(AMQ_state[AMQ_STA_HEAT_LEVEL] != AMQ.heatLevel)
	{
		AMQ_state[AMQ_STA_HEAT_LEVEL] = AMQ.heatLevel;
		F_ble_updata = 1;
	}
	if(AMQ_state[AMQ_STA_MASSAGE_TYPE] != AMQ.massage_type)
	{
		AMQ_state[AMQ_STA_MASSAGE_TYPE] = AMQ.massage_type;
		F_ble_updata = 1;
	}
	if(AMQ_state[AMQ_STA_SPEED] != AMQ.speedLevel)
	{
		AMQ_state[AMQ_STA_SPEED] = AMQ.speedLevel;
		F_ble_updata = 1;
	}
	if(AMQ.C_timer_s % 60)
		temp = AMQ.C_timer_s/60 + 1;
	else
		temp = AMQ.C_timer_s/60;
	if(AMQ_state[AMQ_STA_TIME] != temp)
	{
		AMQ_state[AMQ_STA_TIME] = temp;
		F_ble_updata = 1;
	}
	if(AMQ_state[AMQ_STA_MODE] != AMQ.mode)
	{
		AMQ_state[AMQ_STA_MODE] = AMQ.mode;
		F_ble_updata = 1;
	}
	if(AMQ_state[AMQ_STA_MUTE_EN] != AMQ.mute_en)
	{
		AMQ_state[AMQ_STA_MUTE_EN] = AMQ.mute_en;
		F_ble_updata = 1;
	}
	
	//#######电量############
	temp = get_battery_level();
	if(AMQ.sta == STA_RUNNING)
		temp += SET_AD_V_LOWPOWER_FIX_RUN;
	if(AMQ.heatLevel != HEAT_LEVEL_OFF)
		temp += SET_AD_V_LOWPOWER_FIX_HEAT;
	//防止堵转异常电压
	if(AD_Vbat_backup == 0)
	{
		AD_Vbat_backup = temp;
	}
	if(AD_Vbat_backup > temp+12)
	{
		temp = AD_Vbat_backup;
		C_AD_Vbat_delay_10ms = 1500;
	}
	else if(C_AD_Vbat_delay_10ms)
	{
		C_AD_Vbat_delay_10ms--;
	}
	else
	{
		AD_Vbat_backup = temp;
	}
	//防止堵转异常电压end
	
	if(!AMQ_state[AMQ_STA_BAT_POWER])
	{
		if(temp <= 350)
			AMQ_state[AMQ_STA_BAT_POWER] = 0;
		else if(temp > 400)
			AMQ_state[AMQ_STA_BAT_POWER] = 100;
		else
			AMQ_state[AMQ_STA_BAT_POWER] = (temp-350)*2;
		F_ble_updata = 1;
	}
	if((AMQ.chargeStata == CHARGE_STATA_CHARGING)||(AMQ.chargeStata == CHARGE_STATA_FULL))		//充电状态电量才可以增加
	{
		if(AMQ_state[AMQ_STA_BAT_POWER] < (temp-350)*2)
		{
			if(AMQ_state[AMQ_STA_BAT_POWER] < 100)
			{
				AMQ_state[AMQ_STA_BAT_POWER]++;
				if(AMQ_state[AMQ_STA_BAT_POWER] % 20 == 0)
					F_ble_updata = 1;
			}
		}
	}
	if(AMQ_state[AMQ_STA_BAT_POWER] > (temp-350)*2)
	{
		if(AMQ_state[AMQ_STA_BAT_POWER])
		{
			AMQ_state[AMQ_STA_BAT_POWER]--;
			if(AMQ_state[AMQ_STA_BAT_POWER] % 20 == 0)
				F_ble_updata = 1;
			else if(AMQ_state[AMQ_STA_BAT_POWER] == 10)
				F_ble_updata = 1;
		}
	}

	if(F_ble_updata)
		task_post_msg(NULL, 1, MSG_BT_AMZ_DATA_UPDATE);
//##########################################################
//##########################################################

	if(!IO_isCHRG_in)
	{
		if(T_charge_10ms < 10)
			T_charge_10ms++;
		else
		{
			if(AMQ.chargeStata != CHARGE_STATA_CHARGING)
			{
				if(C_charged_10ms)		//充满停止检测8s
					C_charged_10ms--;
				else
					task_post_msg(NULL, 1, MSG_BT_AMQ_CHARGING);
					
				AMQ_state[AMQ_STA_IS_CHARGE] = 1;
			}
		#if	DISWORK_AT_CHRG_EN
			if(AMQ.sta != STA_POWEROFF)
			{
				AMQ.sta = STA_POWEROFF;
			}
		#endif
		}
	}
	else if(!IO_isSTDBY_in)
	{
		if(T_charge_10ms < 10)
			T_charge_10ms++;
		else
		{
			if(AMQ.chargeStata != CHARGE_STATA_FULL)
			{
				task_post_msg(NULL, 1, MSG_BT_AMQ_CHARGEND);
			}
			C_charged_10ms = 800;		//充满停止检测8s
		#if	DISWORK_AT_CHRG_EN
			if(AMQ.sta != STA_POWEROFF)
			{
				AMQ.sta = STA_POWEROFF;
			}
		#endif
		}
	}
	else
	{
		T_charge_10ms = 0;
		C_charged_10ms = 0;
		
		/*	//上面写了
		temp = get_battery_level();
		if(AMQ.mode == STA_RUNNING)
			temp += SET_AD_V_LOWPOWER_FIX_RUN;
		if(AMQ.heatLevel != HEAT_LEVEL_OFF)
			temp += SET_AD_V_LOWPOWER_FIX_HEAT;

		//防止堵转异常电压
		if(AD_Vbat_backup == 0)
		{
			AD_Vbat_backup = temp;
		}
		if(AD_Vbat_backup > temp+12)
		{
			temp = AD_Vbat_backup;
			C_AD_Vbat_delay_10ms = 1500;
		}
		else if(C_AD_Vbat_delay_10ms)
		{
			C_AD_Vbat_delay_10ms--;
		}
		else
		{
			AD_Vbat_backup = temp;
		}
		//防止堵转异常电压end
	//	*/
	
		AMQ_state[AMQ_STA_IS_CHARGE] = 0;

		if((temp>SET_AD_V_MIN)&&(temp<SET_AD_V_LOWPOWER)&&(AMQ.sta != STA_POWEROFF))		//V*100, EXP:3.6V = 360
		{
			if(T_lowpower_10ms < 100)
				T_lowpower_10ms++;
			else
			{
				if(AMQ.chargeStata != CHARGE_STATA_LOW_POWER)
					task_post_msg(NULL, 1, MSG_BT_AMQ_LOWPOWER);
					
				AMQ_state[AMQ_STA_IS_LOWPOWER] = 1;
			}
		}
		else if((AMQ.chargeStata != CHARGE_STATA_LOW_POWER)||(AMQ.sta == STA_POWEROFF))
		{
			AMQ.chargeStata = CHARGE_STATA_NULL;
			T_lowpower_10ms = 0;
			
			AMQ_state[AMQ_STA_IS_LOWPOWER] = 0;
		}
	}

#if 1
	temp = get_tone_status();
	if(((stata == BT_STATUS_PLAYING_MUSIC)||temp)&&(is_auto_mute()==0))
		IO_MUTE_EN_clr;
	else
		IO_MUTE_EN_set;
#else
		IO_MUTE_EN_clr;
#endif
}

void user_keyScan()		//20ms
{
	static u8 keyCode_ad = KEY_NON, keyCode_adBakup = KEY_NON;
	static u16 adBuf = 0;
	static u16 temp;
	static u8 T_keyDown_20ms = 0, T_keyNon_20ms = 0;
	static u8 key_last = KEY_NON, key_down_times = 0;
	static u8 F_keyDone = 0;
	static u8 C_tone_delay_20ms = 10;
	
//	adBuf = user_getAD(AD_CH_PB1);
	adBuf = adc_value[R_AD_CH_PR2];
//	log_printf("adBuf = %d",adBuf);

#if DISWORK_AT_CHRG_EN
	if((AMQ.chargeStata == CHARGE_STATA_CHARGING)||(AMQ.chargeStata == CHARGE_STATA_FULL))
		return;
#endif

	if(F_pause && (AMQ.sta == STA_RUNNING) && !get_tone_status())
	{
		if(C_tone_delay_20ms)
			C_tone_delay_20ms--;
		else
		{
			F_pause = 0;
			task_post_msg(NULL, 1, MSG_BT_AMQ_TONE_PLAY_HEAT);
		}
	}
	else
		C_tone_delay_20ms = 10;
		
#if LOWPOWER_EN	//0 = nomeal, 1 = lowpower
//	if(adBuf < SET_AD_KEY_NON+SET_AD_KEY_FIXED)
	if((adBuf < SET_AD_KEY_NON+SET_AD_KEY_FIXED)&&(IO_433M_REC_in))
	{
		if(keyCode_adBakup != KEY_NON)
		{
			keyCode_adBakup = KEY_NON;
			return;
		}
		keyCode_ad = KEY_NON;
		T_keyDown_20ms = 0;
		F_keyDone = 0;
		if(key_last != KEY_NON)
		{
			if(AMQ.sta == STA_POWEROFF)
				return;
		//	if(T_keyNon_20ms < 25)	//带双击功能
			if(T_keyNon_20ms < 2)	//不带双击功能
			{
				T_keyNon_20ms++;
			}
			else
			{
				T_keyNon_20ms = 0;
				switch(key_last)
				{
				case KEY_POW_MODE:
					if(key_down_times == 1)
					{
						task_post_msg(NULL, 1, MSG_BT_AMQ_SET_SPEED_LEVEL);	
						T_idle_1s = 0;
						AMQ.C_timer_s = 900;
					}
					/*	双击功能
					else if(key_down_times == 2)
					{
						if(get_call_status() == BT_CALL_INCOMING)
							task_post_msg(NULL, 1, MSG_BT_CALL_REJECT);
					}
				//	*/
				}
				key_last = KEY_NON;
				key_down_times = 0;
			}
		}
		else
			T_keyNon_20ms = 0;

	}
//	else if(adBuf < SET_AD_KEY_POW_MODE+SET_AD_KEY_FIXED)
	else if((adBuf < SET_AD_KEY_POW_MODE+SET_AD_KEY_FIXED)&&(IO_433M_REC_in))
	{
		if(keyCode_adBakup != KEY_POW_MODE)
		{
			keyCode_adBakup = KEY_POW_MODE;
			return;
		}

		if(keyCode_ad != KEY_POW_MODE)
		{
			keyCode_ad = KEY_POW_MODE;
			T_keyDown_20ms = 1;
		}
		else if(T_keyDown_20ms < 2)
		{
			T_keyDown_20ms++;
		}
		else if(T_keyDown_20ms == 2)
		{
			T_keyDown_20ms = 3;

			if(key_last != KEY_POW_MODE)
			{
				key_last = KEY_POW_MODE;
				key_down_times = 1;
			}
			/*	双击功能
			else
			{
				key_down_times++;
			}
		//	*/
		}
		else if(T_keyDown_20ms < 100)
		{
			T_keyDown_20ms++;
		}
		else if(T_keyDown_20ms == 100)
		{
			temp = get_tone_status();
			if(temp)
				return;

			T_keyDown_20ms = 110;
			key_down_times = 0;
			switch(AMQ.sta)
			{
			case STA_POWEROFF:
				if(F_lowPower)
					break;
				if(!F_keyDone)
					task_post_msg(NULL, 1, MSG_BT_AMQ_POWER_ON);
				F_keyDone = 1;
				break;
			case STA_IDLE:
			case STA_RUNNING:
				if(!F_keyDone)
					task_post_msg(NULL, 1, MSG_BT_AMQ_POWER_OFF);
				F_keyDone = 1;
				break;
			default:
				break;
			}
			T_idle_1s = 0;
			AMQ.C_timer_s = 900;
		}
	}
//	else if(adBuf < SET_AD_KEY_HEAT+SET_AD_KEY_FIXED)
	else if(!IO_433M_REC_in)	//改为加热键
	{
		if(keyCode_adBakup != KEY_HEAT)
		{
			keyCode_adBakup = KEY_HEAT;
			return;
		}

//		if(AMQ.mode != STA_RUNNING)
//			return;

		if(keyCode_ad != KEY_HEAT)
		{
			keyCode_ad = KEY_HEAT;
			T_keyDown_20ms = 1;
		}
		else if(T_keyDown_20ms < 2)
		{
			T_keyDown_20ms++;
		}
		else if(T_keyDown_20ms == 2)
		{
			T_keyDown_20ms = 3;
			if(!F_keyDone)
				task_post_msg(NULL, 1, MSG_BT_AMQ_SET_HEAT_LEVEL);
			F_keyDone = 1;
			T_idle_1s = 0;
			AMQ.C_timer_s = 900;
		}
		/*	连击
		else if(T_keyDown_20ms < 15)
			T_keyDown_20ms++;
		else
		{
			T_keyDown_20ms = 3;
		//	task_post_msg(NULL, 1, MSG_VOL_UP);
		}
	//	*/
	}
#else
	if(adBuf > SET_AD_KEY_NON-SET_AD_KEY_FIXED)
	{
		if(keyCode_adBakup != KEY_NON)
		{
			keyCode_adBakup = KEY_NON;
			return;
		}
		keyCode_ad = KEY_NON;
		T_keyDown_20ms = 0;
		F_keyDone = 0;
		if(key_last != KEY_NON)
		{
			if(AMQ.sta == STA_POWEROFF)
				return;
		//	if(T_keyNon_20ms < 25)	//带双击功能
			if(T_keyNon_20ms < 2)	//不带双击功能
			{
				T_keyNon_20ms++;
			}
			else
			{
				T_keyNon_20ms = 0;
				switch(key_last)
				{
				case KEY_POW_MODE:
					if(key_down_times == 1)
					{
						task_post_msg(NULL, 1, MSG_BT_AMQ_SET_SPEED_LEVEL);
					}
					/*	双击功能
					else if(key_down_times == 2)
					{
						if(get_call_status() == BT_CALL_INCOMING)
							task_post_msg(NULL, 1, MSG_BT_CALL_REJECT);
					}
				//	*/
				}
				key_last = KEY_NON;
				key_down_times = 0;
			}
		}
		else
			T_keyNon_20ms = 0;

	}
	else if(adBuf > SET_AD_KEY_HEAT-SET_AD_KEY_FIXED)
	{
		if(keyCode_adBakup != KEY_HEAT)
		{
			keyCode_adBakup = KEY_HEAT;
			return;
		}

		if(AMQ.sta != STA_RUNNING)
			return;

		if(keyCode_ad != KEY_HEAT)
		{
			keyCode_ad = KEY_HEAT;
			T_keyDown_20ms = 1;
		}
		else if(T_keyDown_20ms < 2)
		{
			T_keyDown_20ms++;
		}
		else if(T_keyDown_20ms == 2)
		{
			T_keyDown_20ms = 3;
			if(!F_keyDone)
				task_post_msg(NULL, 1, MSG_BT_AMQ_SET_HEAT_LEVEL);
			F_keyDone = 1;
		}
		/*	连击
		else if(T_keyDown_20ms < 15)
			T_keyDown_20ms++;
		else
		{
			T_keyDown_20ms = 3;
		//	task_post_msg(NULL, 1, MSG_VOL_UP);
		}
	//	*/
	}
	else if(adBuf < SET_AD_KEY_POW_MODE+SET_AD_KEY_FIXED)
	{
		if(keyCode_adBakup != KEY_POW_MODE)
		{
			keyCode_adBakup = KEY_POW_MODE;
			return;
		}

		if(keyCode_ad != KEY_POW_MODE)
		{
			keyCode_ad = KEY_POW_MODE;
			T_keyDown_20ms = 1;
		}
		else if(T_keyDown_20ms < 2)
		{
			T_keyDown_20ms++;
		}
		else if(T_keyDown_20ms == 2)
		{
			T_keyDown_20ms = 3;

			if(key_last != KEY_POW_MODE)
			{
				key_last = KEY_POW_MODE;
				key_down_times = 1;
			}
			/*	双击功能
			else
			{
				key_down_times++;
			}
		//	*/
		}
		else if(T_keyDown_20ms < 100)
		{
			T_keyDown_20ms++;
		}
		else if(T_keyDown_20ms == 100)
		{
			temp = get_tone_status();
			if(temp)
				return;
			if((AMQ.chargeStata == CHARGE_STATA_CHARGING)||(AMQ.chargeStata == CHARGE_STATA_FULL))
				return;

			T_keyDown_20ms = 110;
			key_down_times = 0;
			switch(AMQ.sta)
			{
			case STA_POWEROFF:
				if(F_lowPower)
					break;
				if(!F_keyDone)
					task_post_msg(NULL, 1, MSG_BT_AMQ_POWER_ON);
				F_keyDone = 1;
				break;
			case STA_IDLE:
			case STA_RUNNING:
				if(!F_keyDone)
					task_post_msg(NULL, 1, MSG_BT_AMQ_POWER_OFF);
				F_keyDone = 1;
				break;
			default:
				break;
			}
		}
	}
#endif
}

void user_sendTRX()
{
	u8 crc;

	if(C_powerOff_1s > 1)
	{
		crc = 0xAA+AMQ.sta+AMQ.speedLevel+AMQ.heatLevel+AMQ.chargeStata+AMQ.massage_type;
		user_putbyte(0xAA);
		user_putbyte(AMQ.sta);
		user_putbyte(AMQ.speedLevel);
		user_putbyte(AMQ.heatLevel);
		user_putbyte(AMQ.chargeStata);
		user_putbyte(AMQ.massage_type);
		user_putbyte(crc);
	}
}

LOOP_DETECT_REGISTER(user_sendTRX_detect) = {
//	.time = 50,		//100ms,如需更改需要调整函数内变量
	.time = 250,	//500ms,如需更改需要调整函数内变量
    .fun  = user_sendTRX,
};

#if 1	//test only
void user_dubugTest()			//2s
{
	u16 temp = 0;
	u16 adBuf,adNum,adSum = 0;

//	log_printf("歌词显示：bt_configs_user.c\n");
//	log_printf("ぁぃぅぇぉあいうえが\n");

//	user_send_cmd_prepare(USER_CTRL_AVCTP_OPID_GET_PLAY_TIME, 0, NULL);

//	adBuf = get_battery_level();	//V*100, EXP:3.6V = 360
//
//	user_putbyte(adBuf>>8);
//	user_putbyte(adBuf);

//	log_printf("电量=%d\n",adBuf);
//	log_printf("等级=%d\n",vLevel);

//	adBuf = adc_value[R_AD_CH_PB1];
	adBuf = adc_value[R_AD_CH_PR2];
//	log_printf("adBuf = %d",adBuf);
//	log_printf("按键=%d\n",adBuf);
	user_putbyte(adBuf>>8);
	user_putbyte(adBuf);

//	adBuf = adc_value[R_AD_CH_VBAT];
//	log_printf("VBAT=%d\n",adBuf);
//	adBuf = adc_value[R_AD_CH_BT];
//	log_printf("VBT=%d\n",adBuf);

//	adBuf = user_getAD(AD_CH_VBAT);
//	log_printf("user_getAD_VBAT�?d\n",adBuf);
//	temp = get_tone_status();
//	log_printf("!!!!!!!!!!!!!tone_status = %d\n",temp);

	log_printf("btStata = %d\n",btStata);

//	temp = get_bt_connect_status();
//	switch(temp)
//	{
//	case BT_STATUS_INITING:          /*正在初始�?/
//		log_printf("正在初始化\n");
//		break;
//	case BT_STATUS_WAITINT_CONN:     /*等待连接*/
//		log_printf("等待连接\n");
//		break;
//	case BT_STATUS_AUTO_CONNECTINT:  /*正在回连*/
//		log_printf("正在回连\n");
//		break;
//	case BT_STATUS_TAKEING_PHONE:    /*正在电话*/
//		log_printf("正在电话\n");
//		break;
//	case BT_STATUS_CONNECTING:       /*已连接，没有电话和音乐在活动*/
//		log_printf("已连接，没有电话和音乐在活动\n");
//		break;
//	case BT_STATUS_PLAYING_MUSIC:    /*正在音乐*/
//		log_printf("正在音乐\n");
//		break;
//	default:
//		break;
//	}
}
LOOP_DETECT_REGISTER(user_dubugTest_detect) = {
    .time = 1000,
    .fun  = user_dubugTest,
};
#endif

#if LOWPOWER_EN
void app_enter_sleep_mode_1()
{
	u16 adBuf;

	extern void set_sys_freq(u32 out_freq);

	if((AMQ.sta == STA_POWEROFF)&&(AMQ.chargeStata == CHARGE_STATA_NULL))
	{
		adBuf = adc_value[R_AD_CH_PR2];
		if(adBuf < SET_AD_KEY_NON+SET_AD_KEY_FIXED)
		{
			if(C_powerOff_1s)
			{
				C_powerOff_1s--;

				if(!C_powerOff_1s)
				{
				//	irq_global_disable();
				//	irq_sys_disable();
					#define IDLE_Hz 120000000L
					set_sys_freq(IDLE_Hz);
					enter_sys_soft_poweroff();
				}
			}
		}
		else
			C_powerOff_1s = SET_POWOFF_TIME_S;
	}
	else
		C_powerOff_1s = SET_POWOFF_TIME_S;
}
LOOP_DETECT_REGISTER(app_enter_sleep_mode_1_detect) = {
    .time = 500,
    .fun  = app_enter_sleep_mode_1,
};
#endif

void user_C_10ms()
{
	static u8 T_10ms = 0;
	static u8 T_1s = 0;
	u16 temp;

	//*
#if USER_PWM1_EN
	//PWM
#else
	if(AMQ.sta == STA_RUNNING)
		IO_PWM_BOOST_set;
	else
		IO_PWM_BOOST_clr;
#endif
//	*/

	if((AMQ.sta == STA_RUNNING)||((AMQ.sta == STA_IDLE)&&(AMQ.heatLevel != HEAT_LEVEL_OFF)))
	{
		if(T_idle_1s)
		{
			T_idle_1s = 0;
			T_10ms = 0;
			AMQ.C_timer_s = 900;
		}

		T_10ms++;
		if(T_10ms == 100)
		{
			T_10ms = 0;
			
			if(AMQ.C_timer_s)	//默认运行15分钟关机
			{
				AMQ.C_timer_s--;
				if(!AMQ.C_timer_s)
				{
					AMQ.C_timer_s = 900;
					task_post_msg(NULL, 1, MSG_BT_AMQ_POWER_OFF);
				}
			}
		}
	}
	else if(AMQ.sta == STA_IDLE)
	{
		if(!AMQ.C_timer_s)
		{
			AMQ.C_timer_s = 900;
			T_10ms = 0;
			T_idle_1s = 0;
		}

		T_10ms++;
		if(T_10ms == 100)
		{
			T_10ms = 0;
			T_idle_1s++;
			if(T_idle_1s == 120)	//待机2分钟无操作关机
			{
				T_idle_1s = 0;
				task_post_msg(NULL, 1, MSG_BT_AMQ_POWER_OFF);
			}
		}
		temp = adc_value[R_AD_CH_PR2];

	#if LOWPOWER_EN	//0 = nomeal, 1 = lowpower
		if(temp > SET_AD_KEY_NON+SET_AD_KEY_FIXED)	//有按键操作重新计时
			T_idle_1s = 0;
	#else
		if(temp < SET_AD_KEY_NON-SET_AD_KEY_FIXED)	//有按键操作重新计时
			T_idle_1s = 0;
	#endif
	}
}

LOOP_DETECT_REGISTER(user_C_10ms_detect) = {
    .time = 5,		//10ms,如需更改需要调整函数内变量
    .fun  = user_C_10ms,
};


#if 1
LOOP_DETECT_REGISTER(user_btStataScan_detect) = {
    .time = 5,		//10ms,如需更改需要调整函数内变量
    .fun  = user_btStataScan,
};

LOOP_DETECT_REGISTER(user_keyScan_detect) = {
    .time = 10,		//20ms,如需更改需要调整函数内变量
    .fun  = user_keyScan,
};
#endif
// */
