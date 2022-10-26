#include "key.h"

#if KEY_433M_EN
uchar keyCodeBitNum_433M;
ulong keyCode_433M;
ulong keyAdr_433M;
#endif

#if KEYLJ_EN
uint timeKeyLJ_ms;
#endif

ulong keySta,keyStaBackup;
ulong keyCode;
uint keyDownTime_ms;
uchar F_keyDone;		//°´¼üÁ¬»÷ÓÃ

uchar keyStaBuff[KEY_NUM] = { 0x00 };

void keyScan()		//1ms
{
	uchar i = 0;
	
	if(IO_KEY_PWR)
		keyStaBuff[0] = keyStaBuff[0]<<1|0;
	else
		keyStaBuff[0] = keyStaBuff[0]<<1|1;
	
	for(i=0;i<KEY_NUM;i++)
	{
		if((keyStaBuff[i]&KEY_MASK) == 0x00)
			keySta &= ~BIT(i);
		else if((keyStaBuff[i]&KEY_MASK) == KEY_MASK)
			keySta |=  BIT(i);
	}
	/* //
	if(keySta)
	{
		if(keySta == keyStaBackup)
			keyDownTime_ms++;
		else
			keyDownTime_ms = 0;
	}
	else if(keyDownTime_ms)
	{
		keyDownTime_ms = 0;
		if(light.rgb < 765)
			light.rgb += 30;
		else
		{
			light.rgb = 0;
			if(++light.mode >= MODE_END)
				light.mode = MODE_BEGIN+1;
		}
	}
//	*/
	keyStaBackup = keySta;
}

void keyAction()
{
	if(!F_keyDone)
	{
		if(keyDownTime_ms >= T_POWER_ON_ms)
		{
			if(light.sta == STA_POWEROFF)
				light.sta = STA_POWERON;
			else if(light.sta == STA_POWERON)
				light.sta = STA_POWEROFF;
			
			F_keyDone = 1;
		}
		
		if((light.sta == STA_POWEROFF) && (keyCode != IRKEY_on))
			return;
		
		switch(keyCode)
		{
		case IRKEY_light_add:
			if(light.brightness <= LED_BRIGHTNESS_MAX-10)
				light.brightness += 10;
			else
				light.brightness = LED_BRIGHTNESS_MAX;
			F_keyDone = 1;
			break;
		case IRKEY_light_dec:
			if(light.brightness >= 20)
				light.brightness -= 10;
			else
				light.brightness = 10;
			F_keyDone = 1;
			break;
		case IRKEY_off:
			light.sta = STA_POWEROFF;
			F_keyDone = 1;
			break;
		case IRKEY_on:
			if(light.sta != STA_POWERON)
				light.sta = STA_POWERON;
			else
				light.mic = !light.mic;
			F_keyDone = 1;
			break;
		case IRKEY_r:
			light.rgb = 0;
			if(light.mode == MODE_qiCaiLiuShui)
				light.mode = MODE_danSeChangLiang;
			F_keyDone = 1;
			break;
		case IRKEY_g:
			light.rgb = 255;
			if(light.mode == MODE_qiCaiLiuShui)
				light.mode = MODE_danSeChangLiang;
			F_keyDone = 1;
			break;
		case IRKEY_b:
			light.rgb = 510;
			if(light.mode == MODE_qiCaiLiuShui)
				light.mode = MODE_danSeChangLiang;
			F_keyDone = 1;
			break;
		case IRKEY_w:
			light.rgb = 765;
			if(light.mode == MODE_qiCaiLiuShui)
				light.mode = MODE_danSeChangLiang;
			F_keyDone = 1;
			break;
		case IRKEY_r_1:
			light.rgb = 30;
			if(light.mode == MODE_qiCaiLiuShui)
				light.mode = MODE_danSeChangLiang;
			F_keyDone = 1;
			break;
		case IRKEY_g_1:
			light.rgb = 285;
			if(light.mode == MODE_qiCaiLiuShui)
				light.mode = MODE_danSeChangLiang;
			F_keyDone = 1;
			break;
		case IRKEY_b_1:
			light.rgb = 540;
			if(light.mode == MODE_qiCaiLiuShui)
				light.mode = MODE_danSeChangLiang;
			F_keyDone = 1;
			break;
		case IRKEY_flash:
			if(light.mode != MODE_shanSHuo)
			{
				light.mode = MODE_shanSHuo;
			}
			else if(++light.gap > 1)
			{
				light.gap = 0;
			}
			F_keyDone = 1;
			break;
		case IRKEY_r_2:
			light.rgb = 60;
			if(light.mode == MODE_qiCaiLiuShui)
				light.mode = MODE_danSeChangLiang;
			F_keyDone = 1;
			break;
		case IRKEY_g_2:
			light.rgb = 315;
			if(light.mode == MODE_qiCaiLiuShui)
				light.mode = MODE_danSeChangLiang;
			F_keyDone = 1;
			break;
		case IRKEY_b_2:
			light.rgb = 570;
			if(light.mode == MODE_qiCaiLiuShui)
				light.mode = MODE_danSeChangLiang;
			F_keyDone = 1;
			break;
		case IRKEY_strobe:
			if(light.mode != MODE_huXi)
			{
				light.mode = MODE_huXi;
			}
			else if(++light.gap > 1)
			{
				light.gap = 0;
			}
			F_keyDone = 1;
			break;
		case IRKEY_r_3:
			light.rgb = 90;
			if(light.mode == MODE_qiCaiLiuShui)
				light.mode = MODE_danSeChangLiang;
			F_keyDone = 1;
			break;
		case IRKEY_g_3:
			light.rgb = 345;
			if(light.mode == MODE_qiCaiLiuShui)
				light.mode = MODE_danSeChangLiang;
			F_keyDone = 1;
			break;
		case IRKEY_b_3:
			light.rgb = 600;
			if(light.mode == MODE_qiCaiLiuShui)
				light.mode = MODE_danSeChangLiang;
			F_keyDone = 1;
			break;
		case IRKEY_fade:
			if(light.mode != MODE_sanSePaoMa)
			{
				light.mode = MODE_sanSePaoMa;
			}
			else if(++light.dir > 3)
			{
				light.dir = 0;
			}
			F_keyDone = 1;
			break;
		case IRKEY_r_4:
			light.rgb = 127;
			if(light.mode == MODE_qiCaiLiuShui)
				light.mode = MODE_danSeChangLiang;
			F_keyDone = 1;
			break;
		case IRKEY_g_4:
			light.rgb = 382;
			if(light.mode == MODE_qiCaiLiuShui)
				light.mode = MODE_danSeChangLiang;
			F_keyDone = 1;
			break;
		case IRKEY_b_4:
			light.rgb = 637;
			if(light.mode == MODE_qiCaiLiuShui)
				light.mode = MODE_danSeChangLiang;
			F_keyDone = 1;
			break;
		case IRKEY_smooth:
			if(light.mic)
			{
				if(light.mode != MODE_qiCaiLiuShui)
				{
					light.mode = MODE_qiCaiLiuShui;
				}
				else if(++light.dir > 3)
				{
					light.dir = 0;
				}
			}
			else
			{
				if(light.mode != MODE_qiCaiLiuShui)
				{
					light.mode = MODE_qiCaiLiuShui;
				}
				else if(++light.dir > 1)
				{
					light.dir = 0;
					light.mode = MODE_danSeJianBian;
				}
			}
			F_keyDone = 1;
			break;
		default:
			break;
		}
	}
#if KEYLJ_EN
	else if(F_keyDone && !timeKeyLJ_ms)
	{
		switch(keyCode)
		{
		case KEY_POW:
		case KEY_RESET:
		case KEY_TIMER_30S:
			break;
		case KEY_BRIGHTNESS_ADD:
			if(light.brightness < LIGHT_BRIGHTNESS_MAX)
			{
				light.brightness++;
				F_eepWrite = 1;
			}
			timeKeyLJ_ms = SET_KEY_LJYS_MS/3;
			break;
		case KEY_BRIGHTNESS_DEC:
			if(light.brightness > LIGHT_BRIGHTNESS_MIN)
			{
				light.brightness--;
				F_eepWrite = 1;
			}
			timeKeyLJ_ms = SET_KEY_LJYS_MS/3;
			break;
		case KEY_LIGHT_WARM:
			if((light.mode == MODE_WHITE)||(light.mode == MODE_YELLOW)||(light.mode == MODE_NINGHT_LIGHT))
			{
				if(light.colourFix < LIGHT_BRIGHTNESS_MAX)
				{
					light.colourFix++;
					F_eepWrite = 1;
				}
			}
			timeKeyLJ_ms = SET_KEY_LJYS_MS/3;
			break;
		case KEY_LIGHT_COLD:
			if((light.mode == MODE_WHITE)||(light.mode == MODE_YELLOW)||(light.mode == MODE_NINGHT_LIGHT))
			{
				if(light.colourFix)
				{
					light.colourFix--;
					F_eepWrite = 1;
				}
			}
			timeKeyLJ_ms = SET_KEY_LJYS_MS/3;
			break;
		case KEY_NIGHT_LIGHT:
		case KEY_LIGHT_R:
		case KEY_LIGHT_G:
		case KEY_LIGHT_B:
			break;
		case KEY_TIMER_DEC:
			if(light.mode == MODE_RGB_CHANGE)
			{
				if(light.RGBSwitchTime_150ms > LIGHT_RGB_SWITCH_TIME_MIN_150MS)
				{
					light.RGBSwitchTime_150ms--;
					F_eepWrite = 1;
				}
			}
			timeKeyLJ_ms = SET_KEY_LJYS_MS;
			break;
		case KEY_TIMER_ADD:
			if(light.mode == MODE_RGB_CHANGE)
			{
				if(light.RGBSwitchTime_150ms < LIGHT_RGB_SWITCH_TIME_MAX_150MS)
				{
					light.RGBSwitchTime_150ms++;
					F_eepWrite = 1;
				}
			}
			timeKeyLJ_ms = SET_KEY_LJYS_MS;
			break;
		case KEY_LINGHT_RGB:
			break;
		default:
			break;
		}
		F_keyDone = 1;
		
	}
#endif
}

u16 userIrCodeChange(u16 irCode)
{
	u16 temp = 0, i = 0;

	for(i=0;i<16;i++)
	{
		if(irCode & BIT(i))
			temp |= BIT(15-i);
	}
	return temp;
}
