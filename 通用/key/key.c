#include"key.h"

#if KEY_433M_EN
uchar keyCodeBitNum_433M;
ulong keyCode_433M;
ulong keyAdr_433M;
#endif

#if KEYLJ_EN
uint timeKeyLJ_ms;
#endif

ulong keySta;
uchar keyCode;
uint keyDownTime_ms;
uchar F_keyDone;		//°´¼üÁ¬»÷ÓÃ

uchar keyStaBuff[KEY_NUM] = { 0x00 };

void keyScan()		//1ms
{
	static ulong keyStaBackup = 0;
	uchar i = 0;
	
	if(KEY0)
		keyStaBuff[0] = keyStaBuff[0]<<1|0;
	else
		keyStaBuff[0] = keyStaBuff[0]<<1|1;
	
	if(KEY1)
		keyStaBuff[1] = keyStaBuff[1]<<1|0;
	else
		keyStaBuff[1] = keyStaBuff[1]<<1|1;
	
	if(KEY2)
		keyStaBuff[2] = keyStaBuff[2]<<1|0;
	else
		keyStaBuff[2] = keyStaBuff[2]<<1|1;
	
	if(KEY3)
		keyStaBuff[3] = keyStaBuff[3]<<1|0;
	else
		keyStaBuff[3] = keyStaBuff[3]<<1|1;
	
	if(KEY4)
		keyStaBuff[4] = keyStaBuff[4]<<1|0;
	else
		keyStaBuff[4] = keyStaBuff[4]<<1|1;
	
	for(i=0;i<KEY_NUM;i++)
	{
		if((keyStaBuff[i]&KEY_MASK) == 0x00)
			keySta &= ~BIT(i);
		else if((keyStaBuff[i]&KEY_MASK) == KEY_MASK)	
			keySta |=  BIT(i);

	}
	if(keySta)
	{
		if(keySta == keyStaBackup)
			keyDownTime_ms++;
		else
			keyDownTime_ms = 0;
	}
	else
	{
		keyDownTime_ms = 0;
	}
	keyStaBackup = keySta;
}

void keyAction()
{
	if((light.sta == STA_POWEROFF) && (keyCode != KEY_POW))
		return;
	if(!F_keyDone)
	{
		switch(keyCode)
		{
		case KEY_POW:
			switch(light.sta)
			{
			case STA_POWEROFF:
				light.sta = STA_POWERON;
				break;
			case STA_POWERON:
			case STA_CONNECT:
				light.sta = STA_POWEROFF;
				C_poweroff_s = 0;
				break;
			}
		case KEY_RESET:
			switch(light.sta)
			{
			case STA_POWEROFF:
			case STA_CONNECT:
				break;
			case STA_POWERON:
				light.mode = MODE_ALL_ON;
				light.brightness = 100;
				light.colourFix = 60;
				F_eepWrite = 1;
				break;
			}
		case KEY_TIMER_30S:
			C_poweroff_s = 30;
			break;
		case KEY_BRIGHTNESS_ADD:
			if(light.brightness < LIGHT_BRIGHTNESS_MAX)
			{
				light.brightness++;
				F_eepWrite = 1;
			}
			timeKeyLJ_ms = SET_KEY_FIRST_LJYS_MS;
			break;
		case KEY_BRIGHTNESS_DEC:
			if(light.brightness > LIGHT_BRIGHTNESS_MIN)
			{
				light.brightness--;
				F_eepWrite = 1;
			}
			timeKeyLJ_ms = SET_KEY_FIRST_LJYS_MS;
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
			timeKeyLJ_ms = SET_KEY_FIRST_LJYS_MS;
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
			timeKeyLJ_ms = SET_KEY_FIRST_LJYS_MS;
			break;
		case KEY_NIGHT_LIGHT:
			light.mode = MODE_NINGHT_LIGHT;
			light.brightness = 10;
			light.colourFix = 100;
			F_eepWrite = 1;
			break;
		case KEY_LIGHT_R:
			light.mode = MODE_R;
			light.brightness = 100;
			F_eepWrite = 1;
			break;
		case KEY_LIGHT_G:
			light.mode = MODE_G;
			light.brightness = 100;
			F_eepWrite = 1;
			break;
		case KEY_LIGHT_B:
			light.mode = MODE_B;
			light.brightness = 100;
			F_eepWrite = 1;
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
			timeKeyLJ_ms = SET_KEY_FIRST_LJYS_MS;
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
			timeKeyLJ_ms = SET_KEY_FIRST_LJYS_MS;
			break;
		case KEY_LINGHT_RGB:
			light.mode = MODE_RGB_CHANGE;
			light.brightness = 100;
			light.RGBSwitchTime_150ms = LIGHT_RGB_SWITCH_TIME_DEFAULT_150MS;
			break;
		default:
			break;
		}
		F_keyDone = 1;
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
