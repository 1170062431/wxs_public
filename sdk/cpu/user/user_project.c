#include "user_project.h"

u8 vLevel;
u8 powerLevel;
u8 mode,btStata;
u16 T_ledOn_s;

u8 F_isVin;		//充电插入状态,0=无充电器插入,1=充电器插入
	
static u32 usr_timer_1s_handle, usr_timer_10ms_handle;
static u32 usr_led_duty_reload_handle;
static u32 adch_time_sel, adch_key_pow;

PRO YK, *pYK;

int music_device_tone_play(char * logo);
extern void sys_enter_soft_poweroff(void *priv);
void power_set_soft_poweroff(void);

void user_io_init()
{
	user_debug("printf:user IO init start!!!\n");
//==================================================================================//
	SET_PA9_IO;
	SET_PA9_in;
	IO_PA9_puOn;

	SET_PA8_IO;
	SET_PA8_in;
	IO_PA8_puOn;

	SET_PA7_IO;
	SET_PA7_in;
	IO_PA7_puOn;

	SET_DM_IO;
	SET_DM_in;
	IO_DM_puOn;
	/*
	SET_DP_IO;
	SET_DP_in;
	IO_DP_puOn;
//	*/
	SET_PA2_IO;
	SET_PA2_in;
	IO_PA2_puOn;
	
	SET_K_PREV_IO;
	SET_K_PREV_in;
	IO_K_PREV_puOn;
	
	SET_K_VOLUP_IO;
	SET_K_VOLUP_in;
	IO_K_VOLUP_puOn;
	
	SET_K_POW_IO;
	SET_K_POW_in;
	IO_K_POW_puOn;
	
	SET_K_VOLDN_IO;
	SET_K_VOLDN_in;
	IO_K_VOLDN_puOn;
	
	SET_K_NEXT_IO;
	SET_K_NEXT_in;
	IO_K_NEXT_puOn;
	
	SET_LED_P_IO;
	SET_LED_P_out;
	IO_LED_P_puOn;
	
#if USER_TEST_EN
	user_debug("printf:user test: IO onit OK!!!\n");
#endif
//==================================================================================//
	adch_time_sel = 666;
	adch_key_pow = 666;
//==================================================================================//
	YK.set_led_onoff_times = 12;
	YK.F_init = 0;
	YK.F_keydown = 0;
	YK.F_lowPower = 0;
	YK.F_powerOff = 0;
	YK.C_poweroff_10ms = SET_POWEROFF_TIME_10MS;
//==================================================================================//
	usr_timer_10ms_handle = usr_timer_add(NULL, usr_timer_10ms_callback, 10, 0);
	user_debug("sys_timer_add,ID = %d\n",usr_timer_1s_handle);
//==================================================================================//
//	user_timer0_init();
//	user_timer1_init();
//	user_timer2_init();
//	user_timer3_init();
//	user_timer4_init();
//	user_timer5_init();
}
early_initcall(user_io_init);

void user_debug_fuc()
{
	u16  ret;
	void *dev;

	if(YK.mode == STA_POWEROFF)
		return;
	/*
	ret = adc_get_value(AD_CH_KEY_POW);
	adc_remove_sample_ch(adch_time_sel);
	if(APP_MUSIC_TASK != app_get_curr_task())
	{
	//	file_dec_repeat_set
		ret = music_player_get_fileindir_number();
		user_debug("music_player_get_fileindir_number:%d\n",ret);
		ret = music_player_get_file_cur();
		user_debug("music_player_get_file_cur:%d\n",ret);
	//	music_player_play_by_number(char * logo, u32 number);
		music_player_set_repeat_mode(FCYCLE_ONE);
		music_player_play_by_number("fat_nor", WNM.sound_index);
	//	music_player_play_by_path("fat_nor", USER_FLASH_PATH_WTN);
	//	usr_led_disp_1ms_handle = usr_timer_add(NULL, usr_led_disp_1ms_callback, 1, 0);
	//	usr_led_disp_1ms_handle = sys_usec_timer_add(NULL, usr_led_disp_1ms_callback, 100);
	}
	//	*/
}

void bt_key_pow_on_off()
{
	
}

void usr_timer_10ms_callback(void *priv)			//can't play music in this func,you can send msg
{
	static u8 T_10ms = 0, T_1s = 0;
	static u8 key = 0, key_backup = 0;
	u8 ret = 0;

	T_10ms++;
	if(T_10ms == 100)
	{
		T_10ms = 0;
		T_1s++;
		user_debug("usr_timer_10ms_callback, T_1s = %d\n",T_1s);
	}
	key = io_get_key_value;
	if(key != key_backup)
	{
		user_debug("io_get_key_value = %d\n",key);
		key_backup = key;
	}
	
	ret = get_bt_connect_status();
	switch(ret)
	{
	case BT_STATUS_INITING:          /*正在初始化*/
    case BT_STATUS_WAITINT_CONN:     /*等待连接*/
    case BT_STATUS_AUTO_CONNECTINT:  /*正在回连*/
		if(YK.set_led_onoff_times)
			break;

		if(!YK.F_powerOff)
		{
 			if(!YK.T_led_on_10ms && !YK.T_led_off_10ms)
			{
				YK.T_led_on_10ms = 20;
				YK.T_led_off_10ms = 30;
 			}
		}
		
		if(YK.C_poweroff_10ms)
			YK.C_poweroff_10ms--;
		else
		{
			YK.set_led_onoff_times = 0;
			YK.T_led_on_10ms = 0;
			YK.T_led_off_10ms = 0;
			IO_LED_P_clr;
			power_set_soft_poweroff();
		}
		break;
    case BT_STATUS_CONNECTING:       /*已连接，没有电话和音乐在活动*/
    case BT_STATUS_TAKEING_PHONE:    /*正在电话*/
    case BT_STATUS_PLAYING_MUSIC:    /*正在音乐*/
		if(!YK.F_init)
		{
			YK.F_init = 1;
			YK.set_led_onoff_times = 0;
			YK.T_led_on_10ms = 0;
			YK.T_led_off_10ms = 0;
		}
		
		YK.C_poweroff_10ms = SET_POWEROFF_TIME_10MS;
		break;
	}

	usr_led_disp();
}

void usr_led_disp()
{
	if(!IO_K_POW_in && YK.F_powerOff)
		return;
	
	if(YK.T_led_on_10ms)
	{
		YK.T_led_on_10ms--;
		IO_LED_P_set;
		return;
	}
	else if(YK.T_led_off_10ms)
	{
		YK.T_led_off_10ms--;
		IO_LED_P_clr;
		return;
	}
	else if(YK.set_led_onoff_times)
	{
		YK.set_led_onoff_times--;
		if(YK.F_powerOff)
		{
			YK.T_led_on_10ms = 20;
			YK.T_led_off_10ms = 20;
		}
		else
		{
			YK.T_led_on_10ms = 25;
			YK.T_led_off_10ms = 25;
		}
	}
	else
	{
		YK.F_keydown = 0;
		IO_LED_P_clr;
		if(YK.F_powerOff)
		{
			YK.F_powerOff = 0;
			power_set_soft_poweroff();
		}
	}
}

//struct timer_hdl {
//    u32 ticks;
//    int index;
//    int prd;
//    u32 fine_cnt;
//    void *power_ctrl;
//    struct list_head head;
//};
//
//static const u32 timer_div[] = {
//    /*0000*/    1,
//    /*0001*/    4,
//    /*0010*/    16,
//    /*0011*/    64,
//    /*0100*/    2,
//    /*0101*/    8,
//    /*0110*/    32,
//    /*0111*/    128,
//    /*1000*/    256,
//    /*1001*/    4 * 256,
//    /*1010*/    16 * 256,
//    /*1011*/    64 * 256,
//    /*1100*/    2 * 256,
//    /*1101*/    8 * 256,
//    /*1110*/    32 * 256,
//    /*1111*/    128 * 256,
//};
//
//#define APP_TIMER_CLK           clk_get("timer")
//#define MAX_TIME_CNT            0x7fff
//#define MIN_TIME_CNT            0x100
//
////====================================================================
////====================================================================
//
//#define TIMER0_UNIT_US           100		//15~???
//#define MAX_TIMER0_PERIOD_MS     (1000/TIMER_UNIT_MS)
//
//___interrupt
//static void user_timer0_isr()
//{
//    static u32 cnt = 0;
//    static u32 T_1s = 0;
//    static u32 led_cnt = 0;
//    JL_TIMER0->CON |= BIT(14);
//
////    cnt++;
////    if (cnt == 10000) {
////        cnt = 0;
////		T_1s++;
////		user_debug("user_timer0_isr:%d\n",T_1s);
////    }
//
////	usr_led_disp();
////======================================================//
//
////======================================================//
//}
//
//static int user_timer0_init()
//{
//#if 0
//    u32 prd_cnt;
//    u8 index;
//
//    for (index = 0; index < (sizeof(timer_div) / sizeof(timer_div[0])); index++) {
//        prd_cnt = TIMER0_UNIT_US * (APP_TIMER_CLK / 1000) / timer_div[index] / 1000;
//        if (prd_cnt > MIN_TIME_CNT && prd_cnt < MAX_TIME_CNT) {
//            break;
//        }
//    }
//
//	JL_TIMER0->CNT = 0;
//	JL_TIMER0->PRD = prd_cnt; //2ms
//	time_cnt[0] = prd_cnt;
////	request_irq(IRQ_TIME0_IDX, 0, user_timer0_isr, 0);
//	request_irq(IRQ_TIME0_IDX, 3, user_timer0_isr, 0);
//	JL_TIMER0->CON = (index << 4) | TIME0_MODE_SEL | BIT(3)|(TIME0_PWM_EN<<8)|(TIME0_PWM_INV_EN<<9);
//
////	user_debug("PRD : 0x%x / %d", JL_TIMER0->PRD, clk_get("timer"));
//
//    return 0;
//#endif
//}
//
////====================================================================
////====================================================================
//
//#define TIMER1_UNIT_US           LED_PWM_PRD_US		//15~???
//#define MAX_TIMER1_PERIOD_MS     (1000/TIMER_UNIT_MS)
//
//___interrupt
//static void user_timer1_isr()
//{
//    static u32 cnt = 0;
//    static u32 T_1s = 0;
//    static u32 led_cnt = 0;
//    JL_TIMER1->CON |= BIT(14);
//
////    cnt++;
////    if (cnt == 10000) {
////        cnt = 0;
////		T_1s++;
////		user_debug("user_timer1_isr:%d\n",T_1s);
////    }
//
////	usr_led_disp();
////======================================================//
//
////======================================================//
//}
//
//static int user_timer1_init()
//{
//#if TIME1_MODE_SEL
//    u32 prd_cnt;
//    u8 index;
//
//    for (index = 0; index < (sizeof(timer_div) / sizeof(timer_div[0])); index++) {
//	//	prd_cnt = TIMER1_UNIT_US * (APP_TIMER_CLK / 1000) / timer_div[index] / 1000;
//		prd_cnt = LED_PWM_PRD_CNT;
//        if (prd_cnt > MIN_TIME_CNT && prd_cnt < MAX_TIME_CNT) {
//            break;
//        }
//    }
//
//	JL_TIMER1->CNT = 0;
//	JL_TIMER1->PRD = prd_cnt;
//	JL_TIMER1->PWM = 0;
////	request_irq(IRQ_TIME1_IDX, 0, user_timer1_isr, 0);
//	request_irq(IRQ_TIME1_IDX, 3, user_timer1_isr, 0);
//	JL_TIMER1->CON = (index << 4) | TIME1_MODE_SEL | BIT(3)|(TIME1_PWM_EN<<8)|(TIME1_PWM_INV_EN<<9);
//
////	user_debug("PRD : 0x%x / %d", JL_TIMER1->PRD, clk_get("timer"));
//
//    return 0;
//#endif
//}
//
////====================================================================
////====================================================================
//
//static struct timer_hdl hdl;
//
//#define __this  (&hdl)
//
//#define TIMER2_UNIT_US           100		//15~???
//#define MAX_TIMER2_PERIOD_MS     (1000/TIMER_UNIT_MS)
//___interrupt
//static void user_timer2_isr()
//{
//    static u32 cnt = 0;
//    static u32 T_1s = 0;
//    static u32 led_cnt = 0;
//    JL_TIMER2->CON |= BIT(14);
//
////	cnt++;
////	if (cnt == 10000) {
////	    cnt = 0;
////		T_1s++;
////		user_debug("user_timer2_isr:%d\n",T_1s);
////	}
//
////======================================================//
////======================================================//
//}
//
//static int user_timer2_init()
//{
//#if 0
//    u32 prd_cnt;
//    u8 index;
//
//    for (index = 0; index < (sizeof(timer_div) / sizeof(timer_div[0])); index++) {
//        prd_cnt = TIMER2_UNIT_US * (APP_TIMER_CLK / 1000) / timer_div[index] / 1000;
//        if (prd_cnt > MIN_TIME_CNT && prd_cnt < MAX_TIME_CNT) {
//            break;
//        }
//    }
//	__this->index   = index;
//	__this->prd     = prd_cnt;
//
//	JL_TIMER2->CNT = 0;
//	JL_TIMER2->PRD = prd_cnt;
//	time_cnt[2] = prd_cnt;
////	request_irq(IRQ_TIME2_IDX, 0, user_timer2_isr, 0);
//	request_irq(IRQ_TIME2_IDX, 3, user_timer2_isr, 0);
//	JL_TIMER2->CON = (index << 4) | TIME2_MODE_SEL | BIT(3)|(TIME2_PWM_EN<<8)|(TIME2_PWM_INV_EN<<9);
////	JL_TIMER2->CON = (index << 4) | BIT(0) | BIT(3);
//
////	user_debug("PRD : 0x%x / %d", JL_TIMER2->PRD, clk_get("timer"));
//
//    return 0;
//#endif
//}
//
////====================================================================
////====================================================================
//
//#define TIMER3_UNIT_US           LED_PWM_PRD_US		//15~???
//#define MAX_TIMER3_PERIOD_MS     (1000/TIMER_UNIT_MS)
//
//___interrupt
//static void user_timer3_isr()
//{
//    static u32 cnt = 0;
//    static u32 T_1s = 0;
//    static u32 led_cnt = 0;
//    JL_TIMER3->CON |= BIT(14);
//
////	cnt++;
////	if (cnt == 10000) {
////	    cnt = 0;
////		T_1s++;
////		user_debug("user_timer3_isr:%d\n",T_1s);
////	}
//
////======================================================//
//
////======================================================//
//}
//
//static int user_timer3_init()
//{
//#if TIME3_MODE_SEL
//    u32 prd_cnt;
//    u8 index;
//
//    for (index = 0; index < (sizeof(timer_div) / sizeof(timer_div[0])); index++) {
//	//	prd_cnt = TIMER1_UNIT_US * (APP_TIMER_CLK / 1000) / timer_div[index] / 1000;
//		prd_cnt = LED_PWM_PRD_CNT;
//        if (prd_cnt > MIN_TIME_CNT && prd_cnt < MAX_TIME_CNT) {
//            break;
//        }
//    }
//
//	JL_TIMER3->CNT = 0;
//	JL_TIMER3->PRD = prd_cnt;
//	JL_TIMER3->PWM = 0;
////	request_irq(IRQ_TIME3_IDX, 0, user_timer3_isr, 0);
//	request_irq(IRQ_TIME3_IDX, 3, user_timer3_isr, 0);
//	JL_TIMER3->CON = (index << 4) | TIME3_MODE_SEL | BIT(3)|(TIME3_PWM_EN<<8)|(TIME3_PWM_INV_EN<<9);
//
////	user_debug("PRD : 0x%x / %d,JL_TIMER3->CON:0x%x", JL_TIMER3->PRD, clk_get("timer"),JL_TIMER3->CON);
//
//    return 0;
//#endif
//}
//
////====================================================================
////====================================================================
//
//#define TIMER4_UNIT_US           LED_PWM_PRD_US		//15~???
//#define MAX_TIMER4_PERIOD_MS     (1000/TIMER_UNIT_MS)
//
//___interrupt
//static void user_timer4_isr()
//{
//    static u32 cnt = 0;
//    static u32 T_1s = 0;
//    static u32 led_cnt = 0;
//    JL_TIMER4->CON |= BIT(14);
//
////    cnt++;
////    if (cnt == 10000) {
////        cnt = 0;
////		T_1s++;
////		user_debug("user_timer4_isr:%d\n",T_1s);
////    }
//
////	usr_led_disp();
////======================================================//
//
////======================================================//
//}
//
//static int user_timer4_init()
//{
//#if TIME4_MODE_SEL
//    u32 prd_cnt;
//    u8 index;
//
//    for (index = 0; index < (sizeof(timer_div) / sizeof(timer_div[0])); index++) {
//	//	prd_cnt = TIMER1_UNIT_US * (APP_TIMER_CLK / 1000) / timer_div[index] / 1000;
//		prd_cnt = LED_PWM_PRD_CNT;
//        if (prd_cnt > MIN_TIME_CNT && prd_cnt < MAX_TIME_CNT) {
//            break;
//        }
//    }
//
//	JL_TIMER4->CNT = 0;
//	JL_TIMER4->PRD = prd_cnt;
//	JL_TIMER4->PWM = 0;
////	request_irq(IRQ_TIME4_IDX, 0, user_timer4_isr, 0);
//	request_irq(IRQ_TIME4_IDX, 3, user_timer4_isr, 0);
//	JL_TIMER4->CON = (index << 4) | TIME4_MODE_SEL | BIT(3)|(TIME4_PWM_EN<<8)|(TIME4_PWM_INV_EN<<9);
//
////	user_debug("PRD : 0x%x / %d", JL_TIMER4->PRD, clk_get("timer"));
//
//    return 0;
//#endif
//}
//
////====================================================================
////====================================================================
//
//#define TIMER5_UNIT_US           LED_PWM_PRD_US		//15~???
//#define MAX_TIMER5_PERIOD_MS     (1000/TIMER_UNIT_MS)
//
//___interrupt
//static void user_timer5_isr()
//{
//    static u32 cnt = 0;
//    static u32 T_1s = 0;
//    static u32 led_cnt = 0;
//    JL_TIMER5->CON |= BIT(14);
//
////	cnt++;
////	if (cnt == 10000) {
////	    cnt = 0;
////		T_1s++;
////		user_debug("user_timer5_isr:%d\n",T_1s);
////	}
//
////======================================================//
//
////======================================================//
//}
//
//static int user_timer5_init()
//{
//#if TIME5_MODE_SEL
//    u32 prd_cnt;
//    u8 index;
//
//    for (index = 0; index < (sizeof(timer_div) / sizeof(timer_div[0])); index++) {
//	//	prd_cnt = TIMER1_UNIT_US * (APP_TIMER_CLK / 1000) / timer_div[index] / 1000;
//		prd_cnt = LED_PWM_PRD_CNT;
//        if (prd_cnt > MIN_TIME_CNT && prd_cnt < MAX_TIME_CNT) {
//            break;
//        }
//    }
//
//	JL_TIMER5->CNT = 0;
//	JL_TIMER5->PRD = prd_cnt;
//	JL_TIMER5->PWM = 0;
////	request_irq(IRQ_TIME5_IDX, 0, user_timer5_isr, 0);
//	request_irq(IRQ_TIME5_IDX, 3, user_timer5_isr, 0);
//	JL_TIMER5->CON = (index << 4) | TIME5_MODE_SEL | BIT(3)|(TIME5_PWM_EN<<8)|(TIME5_PWM_INV_EN<<9);
//
////	user_debug("PRD : 0x%x / %d", JL_TIMER5->PRD, clk_get("timer"));
//
//    return 0;
//#endif
//}

