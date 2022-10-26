#ifndef _CONFIG_H_
#define _CONFIG_H_

#define YES	1
#define NO	0

/* 数据类型定义 */
typedef unsigned char uchar;	// 8 位无符号整型数
typedef unsigned int uint;	//16 位无符号整型数
typedef unsigned long ulong;	//32 位无符号整型数

typedef signed char int8;	// 8 位有符号整型数
typedef signed int int16;	//16 位有符号整型数
typedef signed long int32;	//32 位有符号整型数
typedef unsigned char uint8;	// 8 位无符号整型数
typedef unsigned int uint16;	//16 位无符号整型数
typedef unsigned long uint32;	//32 位无符号整型数

typedef signed char* int8_p;	// 8 位有符号整型数
typedef signed int* int16_p;	//16 位有符号整型数
typedef signed long* int32_p;	//32 位有符号整型数
typedef unsigned char* uint8_p;	// 8 位无符号整型数
typedef unsigned int* uint16_p;	//16 位无符号整型数
typedef unsigned long* uint32_p;	//32 位无符号整型数

typedef signed long  					s32;
typedef signed short 					s16;
typedef signed char  					s8;

typedef signed long  const 				sc32;  /* Read Only */
typedef signed short const 				sc16;  /* Read Only */
typedef signed char  const 				sc8;   /* Read Only */

typedef volatile signed long  			vs32;
typedef volatile signed short 			vs16;
typedef volatile signed char  			vs8;

typedef volatile signed long  const 	vsc32;  /* Read Only */
typedef volatile signed short const 	vsc16;  /* Read Only */
typedef volatile signed char  const 	vsc8;   /* Read Only */

typedef unsigned long  					u32;
typedef unsigned short 					u16;
typedef unsigned char  					u8;

typedef unsigned long  const 			uc32;  /* Read Only */
typedef unsigned short const 			uc16;  /* Read Only */
typedef unsigned char  const 			uc8;   /* Read Only */

typedef volatile unsigned long  		vu32;
typedef volatile unsigned short 		vu16;
typedef volatile unsigned char  		vu8;

typedef volatile unsigned long  const 	vuc32;  /* Read Only */
typedef volatile unsigned short const 	vuc16;  /* Read Only */
typedef volatile unsigned char  const 	vuc8;   /* Read Only */

#define U8_MAX     ((u8)255)
#define S8_MAX     ((s8)127)
#define S8_MIN     ((s8)-128)
#define U16_MAX    ((u16)65535u)
#define S16_MAX    ((s16)32767)
#define S16_MIN    ((s16)-32768)
#define U32_MAX    ((u32)4294967295uL)
#define S32_MAX    ((s32)2147483647)
#define S32_MIN    ((s32)-2147483648)

#define BIT(n)	(u32)(0x01<<(n))

typedef enum
{
  FALSE = 0,
  TRUE = !FALSE
}bool;

typedef enum 
{
  RESET = 0,
  SET = !RESET
}FlagStatus, ITStatus, BitStatus;

typedef enum 
{
  DISABLE = 0,
  ENABLE = !DISABLE
}FunctionalState;

typedef enum 
{
  ERROR = 0,
  SUCCESS = !ERROR
}ErrorStatus;

typedef struct
{
	volatile u8 bit1 : 1;
	volatile u8 bit2 : 1;
	volatile u8 bit3 : 1;
	volatile u8 bit4 : 1;
	volatile u8 bit5 : 1;
	volatile u8 bit6 : 1;
	volatile u8 bit7 : 1;
	volatile u8 bit8 : 1;
}FLAG;
extern FLAG Time_FLAG;	
#define F_1ms	Time_FLAG.bit1
#define F_2ms	Time_FLAG.bit2
#define F_10ms	Time_FLAG.bit3
#define F_50ms	Time_FLAG.bit4
#define F_100ms	Time_FLAG.bit5
#define F_250ms	Time_FLAG.bit6
#define F_500ms	Time_FLAG.bit7
#define F_1s	Time_FLAG.bit8

#endif