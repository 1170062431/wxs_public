#ifndef _UART_H_
#define _UART_H_

#include "typedef.h"

#define DEVICE_BLE_CONNECT_HEAD	0xAA

//产品信息，配对用,这里不能用enum或者16进制
#define PRO_SZJ		0	//甩脂机
#define PRO_FS		1	//风扇
#define PRO_JTJ		2	//脚踏机
#define PRO_JSQ		3	//加湿器
#define PRO_YKBL	4	//遥控伴侣
#define PRO_ZNSZ	5	//智能手杖
#define PRO_AMZ		6	//按摩枕
#define PRO_XXX		111	//未定义

#define PRO_DATA_LEN	4
#define PRO_TYPE		PRO_AMZ
#define PRO_NUM			1

extern u8 F_bleConnectRequest;
extern u8 bleConnectReceBuff[10];
extern u8 bleConnectSendBuff[10];
extern u32 deviceConnectValueA,deviceConnectValueB;

#if(PRO_TYPE == PRO_JTJ)
enum JTJ_STATE
{
	state_head = 0,	//0xAB
	state_length,	//11,state_type->state_sec
	state_type,		//0x14=query,0x15=update
	state_num,		//0
	state_powerOn,	//1=on,0=off
	
	state_Run,		//1=run,0=stop
	state_massage,	//1=on,0=off
	state_heat,		//1=on,0=off
	state_speed,	//0-20
	state_mode,		//0-5
	
	state_hour,		//0
	state_min,		//0-20
	state_sec,		//0-59
	state_err_code,	//指令返回写错误码，主动更新写state_crc
	state_crc
};
#endif

enum TRX_DATA
{
	TD_HEAD = 0,	//0xAA
	TD_MODE,
	TD_SPEED,
	TD_HEAT,
	TD_STATA,
	TD_CRC,
	TD_END
};
extern u8 user_uart_rxBuff[16];

enum userBleCmdType
{
	userBleCmdType_BEGIN,
#if (PRO_TYPE == PRO_JTJ)
	JTJ_POWER_ON_OFF_CTR = 0x0e,
	JTJ_ADD_FUNCTION_CTR,
	JTJ_START_STOP_CTR,
	JTJ_SPEED_CTR,
	JTJ_MODE_CTR,
	JTJ_TIME_CTR,
	JTJ_DATA_QUERY,
	JTJ_DATA_UPDATE,
#elif (PRO_TYPE == PRO_ZNSZ)
	ZNSZ_TIME_AND_WEATHER_REPORT = 0x0e,
	ZNSZ_BATTERY_VAL_REPORT,
	ZNSZ_ADDR_REPORT,
	ZNSZ_CALL,
	ZNSZ_SOS,
	ZNSZ_BATTERY_VAL_QUERY = 0x30,
#elif (PRO_TYPE == PRO_AMZ)
	AMZ_POWER_ON_OFF_CTR = 0x0e,
	AMZ_START_STOP_CTR,
	AMZ_HEAT_CTR,
	AMZ_MASSAGE_TYPE_CTR,
	AMZ_SPEED_CTR,
	AMZ_TIME_CTR,
	AMZ_USER_DEFINE,
	AMZ_SET_MODE,
	AMZ_MUTE_EN,
	AMZ_DATA_QUERY = 0x30,
	AMZ_DATA_UPDATE,
#endif
	userBleCmdType_END
};

enum userBleCmd
{
	USER_BLE_CMD_POWER_ON = 0x01,
	USER_BLE_CMD_POWER_OFF,
	USER_BLE_CMD_MASSAGE_ON,
	USER_BLE_CMD_MASSAGE_OFF,
	USER_BLE_CMD_HEAT_ON,
	USER_BLE_CMD_HEAT_OFF,
	USER_BLE_CMD_START,
	USER_BLE_CMD_STOP,
	USER_BLE_CMD_SET_SPEED,
	USER_BLE_CMD_ADD_SPEED,
	USER_BLE_CMD_DEC_SPEED,
	USER_BLE_CMD_SET_MODE,
	USER_BLE_CMD_SET_TIMER,
	USER_BLE_CMD_ADD_TIMER,
	USER_BLE_CMD_DEC_TIMER,
	USER_BLE_CMD_CLOSE_TIMER,
	USER_BLE_CMD_DATA_QUERY,
	USER_BLE_CMD_DATA_UPDATE,
	USER_BLE_CMD_NON
};

extern u8 user_ble_rxLen;
extern u8 user_ble_rxBuff[16];

extern u8 user_ble_txLen;
extern u8 user_ble_txBuff[16];

extern u8 user_uart_rxLen;
extern u8 user_uart_rxBuff[16];

extern u8 F_uart2_state_rec_start/*,F_uart0_cmdFb_rec_start*/;
extern u8 uart2_state_rec_num;

s32  uart_init(u32 baud);
void uart_module_init();
s32 uart_set_baud(u32 baud);

int puts(const char *out);
char getbyte();
char user_getbyte();
void putchar(char a);
void user_putchar(char a);
void user_putbyte(char a);
void put_buf(u8 *buf, u32 len);
void printf_buf(u8 *buf, u32 len);
void put_u8hex(u8 dat);
void put_u8hex0(u8 dat);
void put_u32hex(u32 dat);
void put_u32hex0(u32 dat);
void put_u16hex(u16 dat);
// s32 EQ_uart_init(u32 baud);

void uart_updata_io_ctrl(void **parm);
void uart_updata_receive_cmd();
extern void register_handle_printf_putchar(void (*handle)(char a));

void user_common_uart_isr(u8 uto_buf, void *p, u8 isr_flag);
u8 user_uart_isr_callback(u8 uto_buf);
s32 user_uart_init(u32 baud_rate);
void user_uart_write(char a);

#endif

