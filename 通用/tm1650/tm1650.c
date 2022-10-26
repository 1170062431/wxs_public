
#include "tm1650.h"
#include "..\CTK_Library\BF7612CMXX\BF7612CMXX.h"
#include "..\Project\Project.h"
#include "..\CTK_Library\BF7612CMXX\BF7612CMXX_API.h"

/*
1、开始信号（START）/结束信号(STOP)
开始信号：保持 CLK 为“1”电平，DAT 从“1”跳“0”，认为是开始信号；
结束信号：保持 CLK 为“1”电平，DAT 从“0”跳“1”，认为是结束信号；
2、ACK 信号
 如果本次通讯正常，芯片在串行通讯的第 8 个时钟下降沿后，TM1650 主动把 DAT 拉低。直到检测到 CLK 来
了上升沿，DAT 释放为输入状态（对芯片而言）。 
3、 写“1”和写“0”
 写“1”：保持 DAT 为“1”电平，CLK 从“0”跳到“1”,再从“1”跳到“0”，则认为是写入“1”。
 写“0”：保持 DAT 为“0”电平，CLK 从“0”跳到“1”,再从“1”跳到“0”，则认为是写入“0”。
*/

//电平最小保持时间100ns，单片机12M单步时间83us，需要延时

#define SET_DIN()   SET_DAT_H	//DATAC |=  0x80
#define CLR_DIN()   SET_DAT_L	//DATAC &= ~0x80
#define SET_SCLK()  SET_CLK_H	//DATAC |=  0x40
#define CLR_SCLK()  SET_CLK_L	//DATAC &= ~0x40
#define IO_DIN	PC3
#define IO_SCLK	PC2

#define M_DISP_CTRL_SETTING(brightness,en) ((brightness<<4) + (CFG_SEG_MODE_8SEG<<3) + (CFG_WORK_MODE<<2) + en)


static void TM1650_Start(void);
static void TM1650_SendDat(unsigned char dat);
static void TM1650_Ask();
static void TM1650_End(void);

static void TM1650_Start()		//开始信号
{
    SET_SCLK(); 
    SET_DIN();
    Delay_Us(1);
	CLR_DIN();
}

static void TM1650_SendDat(unsigned char dat) //写一个字节高位在前，低位在后
{
    unsigned char i;
    CLR_SCLK();
    for (i = 0x80; i != 0x00; i >>= 1)
	{
        if (dat & i)
        	SET_DIN();
        else
			CLR_DIN();
        SET_SCLK();
		Delay_Us(1);
        CLR_SCLK();
    }
	TM1650_Ask();
}

static void TM1650_Ask()		 //ACK信号
{
    unsigned char timeout = 0;
	SET_DAT_IO_IN;
	SET_DAT_PU_ON;
    Delay_Us(1);
    SET_SCLK();
/*	while((IO_DIN)&&(timeout<=100))
	{
		timeout++;        
	}
*/
	SET_DAT_IO_OUT;
    CLR_SCLK();
    Delay_Us(1);
}

static void TM1650_End(void)	//停止信号
{
	SET_SCLK();
	CLR_DIN();
	Delay_Us(1);
	SET_DIN();
}

void TM1650_Init()
{
    // 数据命令设置（固定地址)
    TM1650_Start();
    TM1650_SendDat(CFG_SYS_CMD);
	TM1650_SendDat(M_DISP_CTRL_SETTING(CFG_BRIGHTNESS(7),OPEN));
    TM1650_SendAddrDat(0x68, 0x00);
    TM1650_SendAddrDat(0x6A, 0x00);
    TM1650_SendAddrDat(0x6C, 0x00);
    TM1650_SendAddrDat(0x6E, 0x00);
    TM1650_End();
}


void TM1650_Switch(unsigned char brightness,unsigned char en)
{
    TM1650_Start();
    TM1650_SendDat(CFG_SYS_CMD);
    TM1650_SendDat(M_DISP_CTRL_SETTING(brightness,en));
    TM1650_End();
}

void TM1650_SendAddrDat(unsigned char addr,unsigned char dat)
{
    TM1650_Start();
    TM1650_SendDat(addr);
    TM1650_SendDat(dat);
    TM1650_End();
}

static uchar TM1650_keyScan(void)          // 按键扫描
{
    uchar i;
    uchar rekey;
    TM1650_Start();
    TM1650_SendDat(CFG_READ_KEY_CMD);//读按键命令
    //DIO_H;
    for(i=0;i<8;i++)
    {
       SET_SCLK();
       rekey = rekey<<1;
       if(IO_DIN)
		{
			rekey++;
		} 
		Delay_Us(1);
		CLR_SCLK();        
	}
	TM1650_End();
	return(rekey);
}

