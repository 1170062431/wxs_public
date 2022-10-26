#ifndef _MAIN_C_
#define _MAIN_C_
/****************************************************************************************/
#include "main.h"
/*****************************************************************************************
******************************************************************************************/
_LIGHT light;
	
unsigned int LED_DAT[LED_NUM] = { 0 };	//LED 数据表,0-254--R+G,255-509--G+B,510-764--B+R,765--W,886--OFF
	/* //
unsigned char LED_DAT[LED_NUM][3] = {	//LED 数据表	
	{0x00,0x00,0x00},		//led1++
	{0x00,0x00,0x00},		//led2++
	{0x00,0x00,0x00},		//led3++
	{0x00,0x00,0x00},		//led4++
	{0x00,0x00,0x00},		//led5++
	{0x00,0x00,0x00},		//led6++
};
//	*/
void main(void)
{
	io_init();
	timer0_init();
	pwm2_init();
	
#ifdef UART0_EN
	Uart0_Initial(UART0_BAUTRATE);	//初始化UART0
#endif

	EA = 1;													//开全局中断

#ifdef PRINT_EN
	uart_printf("CA51F551S1 Demo Code\n");
#endif

	F_1ms = 0;
	F_1s = 0;
	T_1ms = 0;
	
	while(1)
	{
		if(F_1ms)
		{
			F_1ms = 0;
			keyScan();
			if(keySta || (keyCode != IRKEY_NON))
			{
			/* //
				if(!F_keyDone)
				{
					user_printf("IR keyCode = 0x%08lx ",keyCode);
					user_printf("keySta = 0x%08lx ",keySta);
					user_printf("keyDownTime_ms = %d ",keyDownTime_ms);
					user_printf("\n");
				}
			//	*/
				keyAction();
			}
			else
				F_keyDone = 0;
			if(T_1ms%20 == 0)
			{
				led_rgb_refreash();
				send_led_data();
			}
		}
		if(F_1s)
		{
			F_1s = 0;
		#ifdef PRINT_EN
			uart_printf("1s\n");
		#endif
		}
	}

}

void led_rgb_refreash()		//>=10ms
{
	static u16 temp_rgb;
	static u8 F_huXi = 0;
	u8 led_index,led_on_num;
	u8 gap,num;
	
	if(light.sta == STA_POWEROFF)
	{
		for(led_index=0;led_index<LED_NUM;led_index++)
		{
			LED_DAT[led_index] = 886;
		}
		return;
	}
	
	temp_rgb = light.rgb;
	
	if(light.mic)
		led_on_num = light.mic_ad;
	else
		led_on_num = LED_NUM;
	
	switch (light.mode)
	{
	case MODE_qiCaiLiuShui:
		if(light.dir == 0)
		{
			for(led_index=0;led_index<led_on_num;led_index++)
			{
				LED_DAT[led_index] = temp_rgb;
				temp_rgb = (temp_rgb+11)%765;
			}
			for(led_index=led_on_num;led_index<LED_NUM;led_index++)
			{
				LED_DAT[led_index] = 886;
			}
		}
		else if(light.dir == 1)
		{
			for(led_index=LED_NUM;led_index>LED_NUM-led_on_num;led_index--)
			{
				LED_DAT[led_index-1] = temp_rgb;
				temp_rgb = (temp_rgb+11)%765;
			}
			for(led_index=LED_NUM-led_on_num;led_index>0;led_index--)
			{
				LED_DAT[led_index-1] = 886;
			}
		}
		else if(light.dir == 2)		//mic enable
		{
			for(led_index=0;led_index<LED_NUM;led_index++)
			{
				LED_DAT[led_index] = temp_rgb;
				temp_rgb = (temp_rgb+11)%765;
			}
			for(led_index=led_on_num/2;led_index<LED_NUM-led_on_num/2;led_index++)
			{
				LED_DAT[led_index] = 886;
			}
		}
		else if(light.dir == 3)		//mic enable
		{
			for(led_index=LED_NUM;led_index>0;led_index--)
			{
				LED_DAT[led_index-1] = temp_rgb;
				temp_rgb = (temp_rgb+11)%765;
			}
			for(led_index=0;led_index<(LED_NUM-led_on_num)/2;led_index++)
			{
				LED_DAT[led_index] = 886;
			}
			for(led_index=LED_NUM;led_index>(LED_NUM+led_on_num)/2;led_index--)
			{
				LED_DAT[led_index-1] = 886;
			}
		}
		
		if(T_1ms%40 <= 3)
		{
			if(light.rgb < 11)
				light.rgb += (765-11);
			else
				light.rgb -= 11;
		}
		
		if(light.mic_ad)
			light.mic_ad --;
		break;
	case MODE_danSeChangLiang:
		for(led_index=0;led_index<led_on_num;led_index++)
		{
			LED_DAT[led_index] = temp_rgb;
		}
		if(light.dir == 0)
		{
			for(led_index=led_on_num;led_index<LED_NUM;led_index++)
			{
				LED_DAT[led_index] = 886;
			}
		}
		else if(light.dir == 1)
		{
			for(led_index=LED_NUM-led_on_num;led_index>0;led_index--)
			{
				LED_DAT[led_index-1] = 886;
			}
		}
		else if(light.dir == 2)		//mic enable
		{
			for(led_index=led_on_num/2;led_index<LED_NUM-led_on_num/2;led_index++)
			{
				LED_DAT[led_index] = 886;
			}
		}
		else if(light.dir == 3)		//mic enable
		{
			for(led_index=0;led_index<(LED_NUM-led_on_num)/2;led_index++)
			{
				LED_DAT[led_index] = 886;
			}
			for(led_index=LED_NUM;led_index>(LED_NUM+led_on_num)/2;led_index--)
			{
				LED_DAT[led_index-1] = 886;
			}
		}
		if(light.mic_ad)
			light.mic_ad --;
		break;
	case MODE_sanSePaoMa:
		for(led_index=0;led_index<LED_NUM;led_index++)
		{
			LED_DAT[led_index] = temp_rgb;
			temp_rgb = (temp_rgb+255)%765;
		}
		if(!light.mic)
		{
			if(T_1ms%200 <= 3)
			{
				if(light.rgb < 255)
					light.rgb += (765-255);
				else
					light.rgb -= 255;
			}
		}
		else if(light.mic_ad)
		{
			if(T_1ms%100 <= 3)
			{
				if(light.rgb < 255)
					light.rgb += (765-255);
				else
					light.rgb -= 255;
			}
			light.mic_ad = 0;
		}
		
		/*
		if(light.mic_ad)
		{
			light.mic_ad --;
			if(light.rgb < 255)
				light.rgb++;
			else
				light.rgb = 0;
		}
	//	*/
		break;
	case MODE_danSeJianBian:
		for(led_index=0;led_index<LED_NUM;led_index++)
		{
			LED_DAT[led_index] = temp_rgb;
		}
		if(!light.mic)
		{
			if(T_1ms%40 <= 3)
				light.rgb = (light.rgb+3)%765;
		}
		else if(light.mic_ad)
		{
			if(T_1ms%40 <= 3)
				light.rgb = (light.rgb+6)%765;
			light.mic_ad = 0;
		}
		
		break;
	case MODE_danSeJianGePaoMa:
	//	if(light.gap == 0)
		{
			light.gap = 3;
			light.num = 3;
	//		light.step = 0;
		}
	//	else
		{
			if(T_1ms%200 <= 10)
				light.step++;
			if(light.step >= light.gap+light.num)
			{
				light.step = 0;
			}
			if(light.step <= light.gap)
			{
				gap = light.step;
				num = 3;
			}
			else
			{
				gap = 0;
				num = light.step-light.gap;
			}
		}
		if(light.mic && !light.mic_ad)
			break;
		for(led_index=0;led_index<LED_NUM;led_index++)
		{
			while(gap)
			{
				gap--;
				LED_DAT[led_index] = 886;
				led_index++;
				if(led_index == LED_NUM)
					return;
			}
			while(num)
			{
				num--;
				LED_DAT[led_index] = temp_rgb;
				led_index++;
				if(led_index == LED_NUM)
					return;
			}
			gap = light.gap;
			num = light.num;
		}
		light.mic_ad = 0;
		break;
	case MODE_danSeQieHuan:
		if(T_1ms%20 <= 3)
			light.step++;
		if(light.step > LED_NUM)
		{
			light.step = 1;
			light.rgb = (light.rgb+230)%765;
			temp_rgb = light.rgb;
		}
		for(led_index=0;led_index<light.step;led_index++)
		{
			LED_DAT[led_index] = temp_rgb;
		}
		break;
	case MODE_shanSHuo:
		if((T_1ms < 500)&&(light.mic_ad == 0))
		{
			for(led_index=0;led_index<LED_NUM;led_index++)
			{
				LED_DAT[led_index] = 886;
			}
		}
		else if(!light.mic || light.mic_ad)
		{
			for(led_index=0;led_index<LED_NUM;led_index++)
			{
				LED_DAT[led_index] = temp_rgb;
			}
		}
		light.mic_ad = 0;
		break;
	case MODE_huXi:
		for(led_index=0;led_index<LED_NUM;led_index++)
		{
			LED_DAT[led_index] = temp_rgb;
		}
		if(T_1ms%40 <= 3)
		{
			if(F_huXi)
			{
				if(light.brightness)
					light.brightness--;
				else
					F_huXi = 0;
			}
			else
			{
				if(light.brightness < LED_BRIGHTNESS_MAX)
					light.brightness++;
				else
					F_huXi = 1;
			}
		}
	default:
		break;
	}
}

void send_led_data()
{
//	/*	
	unsigned char led_data_temp[3] = { 0x00,0x00,0x00 };		//LED 数据表
//	*/
	unsigned char led_index = 0,color_index = 0;
	unsigned int temp;
	
	for(led_index=0;led_index<LED_NUM;led_index++) 		//每级 RGB LED 为 3 个字节数据
	{
		temp = LED_DAT[led_index];
		if(temp < 255)
		{
			led_data_temp[DATA_R] = (255-temp)*light.brightness/LED_BRIGHTNESS_MAX;
			led_data_temp[DATA_G] = (temp)*light.brightness/LED_BRIGHTNESS_MAX;
			led_data_temp[DATA_B] = 0;
		}
		else if(temp < 510)
		{
			led_data_temp[DATA_R] = 0;
			led_data_temp[DATA_G] = (510-temp)*light.brightness/LED_BRIGHTNESS_MAX;
			led_data_temp[DATA_B] = (temp-255)*light.brightness/LED_BRIGHTNESS_MAX;
		}
		else if(temp < 765)
		{
			led_data_temp[DATA_R] = (temp-510)*light.brightness/LED_BRIGHTNESS_MAX;
			led_data_temp[DATA_G] = 0;
			led_data_temp[DATA_B] = (765-temp)*light.brightness/LED_BRIGHTNESS_MAX;
		}
		else if(temp == 765)
		{
			led_data_temp[DATA_R] = 125*light.brightness/LED_BRIGHTNESS_MAX;
			led_data_temp[DATA_G] = 125*light.brightness/LED_BRIGHTNESS_MAX;
			led_data_temp[DATA_B] = 125*light.brightness/LED_BRIGHTNESS_MAX;
		}
		else if(temp == 886)
		{
			led_data_temp[DATA_R] = 0;
			led_data_temp[DATA_G] = 0;
			led_data_temp[DATA_B] = 0;
		}
		for(color_index=0;color_index<3;color_index++)
		{
		//	while(LEFLG & LEBSY1); 		//等待数据全部发送,这个没用
			while(LEFLG & LEF1); 		//等待数据全部发送
			LEDAT1 = led_data_temp[color_index%3]; //写入 LED 数据到 LEDAT 寄存器
		}
	}
}


#endif
