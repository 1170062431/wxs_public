/***********************************Jieli tech************************************************
  File : timer.c
  By   : Juntham
  date : 2014-07-04 11:21
********************************************************************************************/
#include "sdk_cfg.h"
#include "timer.h"
#include "clock_api.h"
#include "irq_api.h"
#include "clock.h"
#include "dac.h"
#include "msg.h"
#include "common/sys_timer.h"
#include "common/common.h"
#include "..\include_lib\rtc\rtc_api.h"
#include "user_project.h"
#include "user_pwm.h"

#ifdef SUPPORT_MS_EXTENSIONS
#pragma bss_seg(	".timer_app_bss")
#pragma data_seg(	".timer_app_data")
#pragma const_seg(	".timer_app_const")
#pragma code_seg(	".timer_app_code")
#endif

#define SOURCE_CLK	1	//0:LSB		1:OSC
#define MAX_TIME_CNT 0x7fff
#define MIN_TIME_CNT 0x0100
#define MIN_TIME_CNT1 0x0010
#if SOURCE_CLK
#define TIMER_CLK        IOSC_CLK
#else
#define TIMER_CLK        LSB_CLK
#endif

void (*timer2_caback_fun)() = NULL;

static const u16 timer_div[] = {
    /*0000*/    1,
    /*0001*/    4,
    /*0010*/    16,
    /*0011*/    64,
    /*0100*/    2,
    /*0101*/    8,
    /*0110*/    32,
    /*0111*/    128,
    /*1000*/    256,
    /*1001*/    4 * 256,
    /*1010*/    16 * 256,
    /*1011*/    64 * 256,
    /*1100*/    2 * 256,
    /*1101*/    8 * 256,
    /*1110*/    32 * 256,
    /*1111*/    128 * 256,
};

u32 os_time_get(void)
{
    return get_jiffies(0, 0);
}
/*----------------------------------------------------------------------------*/
/**@brief  get halfsec flag
   @param
   @return
   @note

 */
/*----------------------------------------------------------------------------*/
u8 get_sys_halfsec(void)
{
    return sys_global_value.sys_halfsec;
}

/*----------------------------------------------------------------------------*/
/**@brief  get 2ms's count
   @param
   @return counkt
   @note

 */
/*----------------------------------------------------------------------------*/
static void timer0_isr_fun(void)
{
    struct loop_detect_handler *detect;
    JL_TIMER0->CON |= BIT(14);

    sys_global_value.t0_cnt1++;
	if(sys_global_value.t0_cnt1 == 60000)
		sys_global_value.t0_cnt1 = 0;
	
    list_for_each_loop_detect(detect) {
        if ((sys_global_value.t0_cnt1 %  detect->time) == 0) {
            if (detect->fun) {
                detect->fun();
            }
        }
    }
}
IRQ_REGISTER(IRQ_TIME0_IDX, timer0_isr_fun);

static void timer0_init(void)
{
    u32 prd_cnt, clk, tmp_tick;
    u8 index;
    u8 clk_src;
    u8 catch_flag = 0;

    //resrt_sfr
    JL_TIMER0->CON = 0;

    clk = TIMER_CLK;
    clk /= 1000;
    clk *= 2; //2ms
    for (index = 0; index < (sizeof(timer_div) / sizeof(timer_div[0])); index++) {
        prd_cnt = clk / timer_div[index];
        if (prd_cnt > MIN_TIME_CNT && prd_cnt < MAX_TIME_CNT) {
            catch_flag = 1;
            break;
        }
    }

#if SOURCE_CLK
    clk_src = TIMER_CLK_SRC_OSC;
#else
    clk_src = TIMER_CLK_SRC_SYSCLK;
#endif

    if (catch_flag == 0) {
        puts("warning:timer_err\n");
        return;
    }

    IRQ_REQUEST(IRQ_TIME0_IDX, timer0_isr_fun);

    JL_TIMER0->CNT = 0;
    JL_TIMER0->PRD = prd_cnt - 1;
    JL_TIMER0->CON = BIT(0) | (clk_src << 2) | (index << 4);

    /* log_printf("JL_TIMER0->CNT = 0x%x\n", JL_TIMER0->CNT); */
    /* log_printf("JL_TIMER0->PRD = 0x%x\n", JL_TIMER0->PRD); */
    /* log_printf("JL_TIMER0->CON = 0x%x\n", JL_TIMER0->CON); */
}
void timer2_isr_fun(void)
{
    struct loop_detect_handler *detect;
    JL_TIMER2->CON |= BIT(14);
    sys_global_value.t2_cnt1++;
    IRQ_RELEASE(IRQ_TIME2_IDX);
    if (timer2_caback_fun) {
        timer2_caback_fun();
        timer2_caback_fun = NULL;
    }
    /* puts("timer2_isr_fun\n"); */
#if 0
    list_for_each_tws_detect(detect) {
        /* putchar('@'); */
        if ((sys_global_value.t2_cnt1 %  detect->time) == 0) {
            if (detect->fun) {
                detect->fun();
            }
        }
    }
#endif
}

IRQ_REGISTER(IRQ_TIME2_IDX, timer2_isr_fun);
void tws_sync_set_timer2_us(u32 time_us, void (*fun)())
{
    u32 tem_tick = time_us;
    u32 tem_tick1;
    s32 timer_num;
    u32 prd_cnt, clk, tmp_tick;
    u8 index;
    u8 clk_src;
    u8 catch_flag = 0;
    if (tem_tick == 0) {
        IRQ_RELEASE(IRQ_TIME2_IDX);
        timer2_caback_fun = NULL;
    }
    if (tem_tick < 4) {
        tem_tick = 4;
    }
    //resrt_sfr
    JL_TIMER2->CON = 0;

    clk = TIMER_CLK;
    clk /= 1000;
    tem_tick1 = (tem_tick * 100) / 100;
    clk = clk * tem_tick1 / 1000;
    for (index = 0; index < (sizeof(timer_div) / sizeof(timer_div[0])); index++) {
        prd_cnt = clk / timer_div[index];
        /* printf("----prd_cnt=0x%x\n",prd_cnt ); */
        if (prd_cnt > MIN_TIME_CNT1 && prd_cnt < MAX_TIME_CNT) {
            catch_flag = 1;
            break;
        }
    }

#if SOURCE_CLK
    clk_src = TIMER_CLK_SRC_OSC;
#else
    clk_src = TIMER_CLK_SRC_SYSCLK;
#endif

    if (catch_flag == 0) {
        puts("warning:timer_err\n");
        return;
    }

    timer2_caback_fun = fun;
    IRQ_REQUEST(IRQ_TIME2_IDX, timer2_isr_fun);

    JL_TIMER2->CNT = 0;
    JL_TIMER2->PRD = prd_cnt - 1;
    JL_TIMER2->CON = BIT(0) | (clk_src << 2) | (index << 4);

    /* log_printf("JL_TIMER0->CNT = 0x%x\n", JL_TIMER0->CNT); */
    /* log_printf("JL_TIMER0->PRD = 0x%x\n", JL_TIMER0->PRD); */
    /* log_printf("JL_TIMER0->CON = 0x%x\n", JL_TIMER0->CON); */
}

#if USER_PWM3_EN
/*********************************************************/
/********************************************************
		"1:1100us高电平+400us低电平
		0:400us高电平+1100us低电平
		数据起始位10ms低电平"					
		A	10101001 00001111 00101000 0			
		B	10101001 00001111 00100100 0			
		C	10101001 00001111 00100010 0			
		D	10101001 00001111 00100001 0			
/*********************************************************/
/*********************************************************/
#define KEY_433M_ADDR	0xA55A
#define KEY_433M_PAUSE	0x01FE
#define KEY_433M_MODE	0x02FD
#define KEY_433M_HEAT	0x04FB
//433M接收设置
#define SET_433M_REC_BIT_MAX		32		//设置433M最大接收位数
#define SET_433M_REC_DATA_START_BIT	1		//设置433M接收数据起始位
#define SET_433M_REC_DATA_STOP_BIT	32		//设置433M接收数据结束位

#define SET_433M_START_L_TIME_MIN_125US		64	//起始位低电平时间9ms-72
#define SET_433M_START_L_TIME_MAX_125US		95
//*
#define SET_433M_START_H_TIME_MIN_125US		30	//起始位高电平时间4.5ms-36
#define SET_433M_START_H_TIME_MAX_125US		50
//	*/
#define SET_433M_DATA_0_L_TIME_MIN_125US	6	//数据0低电平时间1100us-8.8
#define SET_433M_DATA_0_L_TIME_MAX_125US	15

#define SET_433M_DATA_0_H_TIME_MIN_125US	1	//数据0高电平时间400us-3.2
#define SET_433M_DATA_0_H_TIME_MAX_125US	7

#define SET_433M_DATA_1_L_TIME_MIN_125US	1	//数据1低电平时间400us-3.2
#define SET_433M_DATA_1_L_TIME_MAX_125US	7

#define SET_433M_DATA_1_H_TIME_MIN_125US	6	//数据1高电平时间1100us-8.8
#define SET_433M_DATA_1_H_TIME_MAX_125US	15
/*
#define SET_433M_LXM_H_TIME_MIN_125US 		14	//连续码高电平时间2.2ms-17.6
#define SET_433M_LXM_H_TIME_MAX_125US 		28
*/
#define SET_433M_DATA2DATA_TIME_125US 		1200//1200	//数据间隔96ms-768,150ms-1200
/*********************************************************/
/*********************************************************/
static void timer3_isr_fun(void)		//src=24M,4分频x750,125us中断
{  
//	static u16 pwm_P = 0;
	static u8 T_125us = 0;
	static u16 T_1ms = 0;
//------------------------------------------------------------------------------------------------------------
	static unsigned long keyCode_433M;
	static unsigned char F_rec433M_EN = 0;	//待机时=0，起始位低电平时=1，起始位高电平时=2?
	static unsigned char F_keysend = 0;
	static unsigned char rec433MBitNum = 0;
	static unsigned char rec433MHighTime = 0;
	static unsigned char rec433MLowTime = 0;
	static unsigned int rec433MIdleTime = 0;	//空闲时间超过 SET_433M_DATA2DATA_TIME_125US 清空键值
//------------------------------------------------------------------------------------------------------------
//	/*根据实际按键有效位数调整*/
	static unsigned long rec433MBuff = 0;
	static unsigned long rec433MBuffBackup = 0;
//------------------------------------------------------------------------------------------------------------
	
	USER_CLR_PWM3_PCLR;

//	T_125us++;
//	
//	//*	timer test
//	if(T_125us%2)
//		IO_pwmBoost_clr;
//	else
//		IO_pwmBoost_set;
//	//	*/
//	
//	if(T_125us == 8)
//	{
//		T_125us = 0;
//		T_1ms++;
//		if(T_1ms == 1000)
//		{
//			T_1ms = 0;
//		}
//	}
	
	if(AMQ.sta == STA_POWEROFF)
		return;
//	/*
	rec433MIdleTime++;
	if(rec433MIdleTime > SET_433M_DATA2DATA_TIME_125US+20)
	{
		F_rec433M_EN = 0;
		F_keysend = 0;
		keyCode_433M = KEY_NON;
	}
	if(IO_433M_REC_in && rec433MHighTime<200)	//读高电平时间
	{
		rec433MHighTime++;
		if(rec433MHighTime > 2)
		{
			if((rec433MLowTime >= SET_433M_START_L_TIME_MIN_125US)&&(rec433MLowTime <= SET_433M_START_L_TIME_MAX_125US))
			{
				rec433MBuff = 0;
				rec433MBitNum = 0;
				if(!F_rec433M_EN)
					rec433MIdleTime = 0;
				F_rec433M_EN = 1;
			}
			rec433MLowTime = 0;
		}
		return;
	}
	else if(!IO_433M_REC_in && rec433MLowTime<200)
	{
		rec433MLowTime++;
		if(F_rec433M_EN)
		{
			if(rec433MLowTime == 2)	//只在设定值执行一次，在范围内值越大抗干扰越好
			{
				if(F_rec433M_EN == 1)
				//*	
				{
					if((SET_433M_START_H_TIME_MIN_125US<=rec433MHighTime) && (rec433MHighTime<=SET_433M_START_H_TIME_MAX_125US))	//正常码
					{
						F_rec433M_EN = 2;
						rec433MHighTime = 0;
						return;
					}
					else //if((SET_433M_LXM_H_TIME_MIN_125US<=rec433MHighTime) && (rec433MHighTime<=SET_433M_LXM_H_TIME_MAX_125US))	//连续码
					{
						rec433MHighTime = 0;
						return;
					}
				}
				else if(F_rec433M_EN == 2)
			//	*/
				{
					if(rec433MBitNum < SET_433M_REC_BIT_MAX)
						rec433MBitNum++;
					if(SET_433M_REC_DATA_START_BIT<=rec433MBitNum && rec433MBitNum<=SET_433M_REC_DATA_STOP_BIT)
					{
						if(SET_433M_DATA_0_H_TIME_MIN_125US<=rec433MHighTime && rec433MHighTime<=SET_433M_DATA_0_H_TIME_MAX_125US)
						{	
							rec433MBuff = rec433MBuff<<1;
							rec433MHighTime = 0;
						}
						else if(SET_433M_DATA_1_H_TIME_MIN_125US<=rec433MHighTime && rec433MHighTime<=SET_433M_DATA_1_H_TIME_MAX_125US)
						{
							rec433MBuff = (rec433MBuff<<1)|1;
							rec433MHighTime = 0;
						}
						else
						{
							rec433MBuff = 0;
							rec433MBitNum = 0;
							F_rec433M_EN = 0;
						//	rec433MBitNum--;
							return;
						}
						//*
						if(rec433MBitNum == SET_433M_REC_DATA_STOP_BIT) 	//接收完有效位数
						{
							if(rec433MBuff>>16 == KEY_433M_ADDR)
							{
								rec433MIdleTime = 0;
								switch(rec433MBuff & 0x0000FFFF)
								{
								//YK_433M
								case KEY_433M_PAUSE:
									if(F_keysend)
										return;
									task_post_msg(NULL, 1, MSG_BT_AMQ_PAUSE);
									break;
								case KEY_433M_MODE:
									if(F_keysend)
										return;
									task_post_msg(NULL, 1, MSG_BT_AMQ_SET_SPEED_LEVEL);
									break;
								case KEY_433M_HEAT:
									if(F_keysend)
										return;
									if(AMQ.sta == STA_RUNNING)
										task_post_msg(NULL, 1, MSG_BT_AMQ_SET_HEAT_LEVEL);
									break;
								default:break;
								}
								F_keysend = 1;
							}
						}
					//	*/
					}
					else
						rec433MHighTime = 0;
				}
			}
			else if(rec433MLowTime == SET_433M_START_L_TIME_MIN_125US)	//到下个起始位，接收完成
			{
				rec433MIdleTime = 0;
				if(rec433MBuff == rec433MBuffBackup)
 				{
 					keyCode_433M = rec433MBuff;
					rec433MBuff = 0;
					rec433MBuffBackup = 0;
					/*
					if(keyCode_433M>>16 == KEY_433M_ADDR)
					{
						switch(keyCode_433M & 0x0000FFFF)
						{
						//YK_433M
						case KEY_433M_PAUSE:
							if(F_keysend)
								break;
							task_post_msg(NULL, 1, MSG_BT_AMQ_PAUSE);
							break;
						case KEY_433M_MODE:
							if(F_keysend)
								break;
							task_post_msg(NULL, 1, MSG_BT_AMQ_SET_SPEED_LEVEL);
							break;
						case KEY_433M_HEAT:
							if(F_keysend)
								break;
							if(AMQ.mode == STA_RUNNING)
								task_post_msg(NULL, 1, MSG_BT_AMQ_SET_HEAT_LEVEL);
							break;
						default:break;
						}
						F_keysend = 1;
					}
				//	*/
				}
				else
				{
					rec433MBuffBackup = rec433MBuff;
					rec433MBuff = 0;
				}
			}
		}
		else
			rec433MHighTime = 0;
	}
//	*/

//	return;
	/*
	pwm_P++;
	if(pwm_P == SET_USER_PWM_DUTY_R)
		pwm_P = 0;
	
	#if 0
	if(pwmBoostDuty > pwm_P)
		IO_pwmBoost_set;
	else
		IO_pwmBoost_clr;
	#endif

	#if 0
	if(pwmLedWDuty > pwm_P)
		IO_pwmLedW_set;
	else
		IO_pwmLedW_clr;
	#endif
	
	#if 1
	if(pwmLedRDuty > pwm_P)
		IO_pwmLedR_set;
	else
		IO_pwmLedR_clr;
	#endif
	*/
}

IRQ_REGISTER(IRQ_TIME3_IDX, timer3_isr_fun);

static void timer3_init(void)
{
    u32 prd_cnt, clk, tmp_tick;
    u8 index;
    u8 clk_src;
    u8 catch_flag = 0;

    //resrt_sfr
//	JL_TIMER3->CON = 0;
	JL_TIMER3->CON = (USER_SET_PWM3_PWM_INV<<9)|(USER_SET_PWM3_PSET3_0<<4)|(USER_SET_PWM3_SSEL1_0<<2)|USER_SET_PWM3_MODE1_0;

    IRQ_REQUEST(IRQ_TIME3_IDX, timer3_isr_fun);

    JL_TIMER3->CNT = 0;
	#if 1	//1
    USER_SET_PWM3_PRD(SET_USER_PWM_DUTY_W);		//0x0030~0x07FF,48~2047,超过此范围需要分频
    USER_SET_PWM3_PWM(0);
	USER_SET_PWM3_ON;
	#else	//test
    USER_SET_PWM3_PRD(125);		//0x0030~0x07FF,48~2047,超过此范围需要分频
    USER_SET_PWM3_PWM(0);
	USER_SET_PWM3_ON;
	#endif

	#if 0
    clk = TIMER_CLK;
//	clk /= 8000;	//125us,4K
//	clk /= 76000;	//13us,38K
	clk /= SET_USER_PWM_FRE;
	clk /= SET_USER_PWM_DUTY_W;
	
	#if USER_TIME3_DIV_EN
    for (index = 0; index < (sizeof(timer_div) / sizeof(timer_div[0])); index++) {
        prd_cnt = clk / timer_div[index];
    	if (prd_cnt > MIN_TIME_CNT && prd_cnt < MAX_TIME_CNT) {
            catch_flag = 1;
            break;
        }
    }
	#else
	index = 0;
	prd_cnt = clk / timer_div[index];
	catch_flag = 1;
	#endif
	
#if SOURCE_CLK
    clk_src = TIMER_CLK_SRC_OSC;
#else
    clk_src = TIMER_CLK_SRC_SYSCLK;
#endif

    if (catch_flag == 0) {
        puts("warning:timer_err\n");
        return;
    }

    IRQ_REQUEST(IRQ_TIME3_IDX, timer3_isr_fun);

    JL_TIMER3->CNT = 0;
    JL_TIMER3->PRD = prd_cnt - 1;
    JL_TIMER3->CON = BIT(0) | (clk_src << 2) | (index << 4);
	#endif
}
#endif //#if	USER_PWM3_EN

void timer_init(void (*isr_fun)(void))
{
    sys_timer_var_init();  //major use in bluetooth
    timer0_init();
	
	#if USER_PWM1_EN
	timer1_init();
	#endif
	
	#if USER_PWM3_EN
	timer3_init();
	#endif
}

#if 0 // UI display
/****为了处理闪屏问题。默认独立使用timer3设置成最高优先级使用。
 *   如果有其他调度要认真考虑能不能放在最高优先级里面
 * ****/
static void timer3_isr_fun(void)
{
    struct loop_detect_handler *detect;
    JL_TIMER3->CON |= BIT(14);

    sys_global_value.t3_cnt1++;

    list_for_each_loop_ui(detect) {
        if ((sys_global_value.t3_cnt1 %  detect->time) == 0) {
            if (detect->fun) {
                detect->fun();
            }
        }
    }
    if (0 == (sys_global_value.t3_cnt1 % 250)) {
        sys_global_value.sys_halfsec = !sys_global_value.sys_halfsec;//led7 driver
    }
}
IRQ_REGISTER(IRQ_TIME3_IDX, timer3_isr_fun);

static void timer3_init(void)
{
    u32 prd_cnt, clk, tmp_tick;
    u8 index;
    u8 clk_src;
    u8 catch_flag = 0;

    //resrt_sfr
    JL_TIMER3->CON = 0;

    clk = TIMER_CLK;
    clk /= 1000;
    clk *= 2; //2ms
    for (index = 0; index < (sizeof(timer_div) / sizeof(timer_div[0])); index++) {
        prd_cnt = clk / timer_div[index];
        if (prd_cnt > MIN_TIME_CNT && prd_cnt < MAX_TIME_CNT) {
            catch_flag = 1;
            break;
        }
    }

#if SOURCE_CLK
    clk_src = TIMER_CLK_SRC_OSC;
#else
    clk_src = TIMER_CLK_SRC_SYSCLK;
#endif

    if (catch_flag == 0) {
        puts("warning:timer_err\n");
        return;
    }

    IRQ_REQUEST(IRQ_TIME3_IDX, timer3_isr_fun);

    JL_TIMER3->CNT = 0;
    JL_TIMER3->PRD = prd_cnt - 1;
    JL_TIMER3->CON = BIT(0) | (clk_src << 2) | (index << 4);

    /* log_printf("JL_TIMER3->CNT = 0x%x\n", JL_TIMER3->CNT); * /
    /* log_printf("JL_TIMER3->PRD = 0x%x\n", JL_TIMER3->PRD); * /
    /* log_printf("JL_TIMER3->CON = 0x%x\n", JL_TIMER3->CON); */
}
#endif 	//UI display

#if 0	//IR send
static u8 IRSendDataLen = 2;
static u8 IRsendBuff[] = {0x55,0x8e,0x8e,0x8e,0x8e,0x8e,0x8e,0xAA};
static u8 IRSendDataTimes = 0;
static u16 sendHeadHighTime_13us = 692;
static u16 sendHeadLowTime_13us = 346;
static u16 sendData2DataTime_13us = 10000;
static void timer3_isr_fun(void)
{
	static u8 sendDataNum = 0;
	static u8 sendBitNum = 8;
	static u8 sendData = 0;
	static u16 sendDataHighTime_13us = 0;
	static u16 sendDataLowTime_13us = 0;
    JL_TIMER3->CON |= BIT(14);
	if(!IRSendDataLen)
		return;
	if(sendHeadHighTime_13us)
	{
		sendHeadHighTime_13us--;
		return;
		sendData = !sendData;
	}
	else if(sendHeadLowTime_13us)
	{
		sendHeadLowTime_13us--;
		return;
		sendData = 0;
	}
	else if(sendDataHighTime_13us)
	{
		sendDataHighTime_13us--;
		sendData = !sendData;
	}
	else if(sendDataLowTime_13us)
	{
		sendDataLowTime_13us--;
		sendData = 0;
	}
	else
	{
		if(!sendBitNum)
		{
			sendBitNum = 8;
			sendDataNum++;
			if(sendDataNum == IRSendDataLen)
			{
				sendDataNum = 0;
				IRSendDataLen = 0;
				sendHeadHighTime_13us = 692;
				sendHeadLowTime_13us = 346;
				PORTR_OUT(PORTR1, 0);
				return;
			}
		}
		if(IRsendBuff[sendDataNum] & BIT(sendBitNum))
		{
			sendDataHighTime_13us = 43;
			sendDataLowTime_13us = 129;
		}
		else
		{
			sendDataHighTime_13us = 43;
			sendDataLowTime_13us = 43;
		}
		sendBitNum--;
	}
	PORTR_OUT(PORTR1, sendData);
}
IRQ_REGISTER(IRQ_TIME3_IDX, timer3_isr_fun);

static void timer3_init(void)
{
    u32 prd_cnt, clk, tmp_tick;
    u8 index;
    u8 clk_src;
    u8 catch_flag = 0;

    //resrt_sfr
    JL_TIMER3->CON = 0;

    clk = TIMER_CLK;
//	clk /= 8000;	//125us,4K
	clk /= 76000;	//13us,38K
    for (index = 0; index < (sizeof(timer_div) / sizeof(timer_div[0])); index++) {
        prd_cnt = clk / timer_div[index];
        if (prd_cnt > MIN_TIME_CNT && prd_cnt < MAX_TIME_CNT) {
            catch_flag = 1;
            break;
        }
    }

#if SOURCE_CLK
    clk_src = TIMER_CLK_SRC_OSC;
#else
    clk_src = TIMER_CLK_SRC_SYSCLK;
#endif

    if (catch_flag == 0) {
        puts("warning:timer_err\n");
        return;
    }

    IRQ_REQUEST(IRQ_TIME3_IDX, timer3_isr_fun);

    JL_TIMER3->CNT = 0;
    JL_TIMER3->PRD = prd_cnt - 1;
    JL_TIMER3->CON = BIT(0) | (clk_src << 2) | (index << 4);

	PORTR_DIR(PORTR1, 0);
	PORTR_OUT(PORTR1, 0);
}
#endif	//IR send

