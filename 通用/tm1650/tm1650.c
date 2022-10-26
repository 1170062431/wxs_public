
#include "tm1650.h"
#include "..\CTK_Library\BF7612CMXX\BF7612CMXX.h"
#include "..\Project\Project.h"
#include "..\CTK_Library\BF7612CMXX\BF7612CMXX_API.h"

/*
1����ʼ�źţ�START��/�����ź�(STOP)
��ʼ�źţ����� CLK Ϊ��1����ƽ��DAT �ӡ�1������0������Ϊ�ǿ�ʼ�źţ�
�����źţ����� CLK Ϊ��1����ƽ��DAT �ӡ�0������1������Ϊ�ǽ����źţ�
2��ACK �ź�
 �������ͨѶ������оƬ�ڴ���ͨѶ�ĵ� 8 ��ʱ���½��غ�TM1650 ������ DAT ���͡�ֱ����⵽ CLK ��
�������أ�DAT �ͷ�Ϊ����״̬����оƬ���ԣ��� 
3�� д��1����д��0��
 д��1�������� DAT Ϊ��1����ƽ��CLK �ӡ�0��������1��,�ٴӡ�1��������0��������Ϊ��д�롰1����
 д��0�������� DAT Ϊ��0����ƽ��CLK �ӡ�0��������1��,�ٴӡ�1��������0��������Ϊ��д�롰0����
*/

//��ƽ��С����ʱ��100ns����Ƭ��12M����ʱ��83us����Ҫ��ʱ

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

static void TM1650_Start()		//��ʼ�ź�
{
    SET_SCLK(); 
    SET_DIN();
    Delay_Us(1);
	CLR_DIN();
}

static void TM1650_SendDat(unsigned char dat) //дһ���ֽڸ�λ��ǰ����λ�ں�
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

static void TM1650_Ask()		 //ACK�ź�
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

static void TM1650_End(void)	//ֹͣ�ź�
{
	SET_SCLK();
	CLR_DIN();
	Delay_Us(1);
	SET_DIN();
}

void TM1650_Init()
{
    // �����������ã��̶���ַ)
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

static uchar TM1650_keyScan(void)          // ����ɨ��
{
    uchar i;
    uchar rekey;
    TM1650_Start();
    TM1650_SendDat(CFG_READ_KEY_CMD);//����������
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

