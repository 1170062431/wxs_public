//Deviec:FT60F01X
//-----------------------Variable---------------------------------
		_RX_data		EQU		5DH
		_RX_dataBit		EQU		5EH
		_RX_dataNum		EQU		5FH
		_TX_dataBit		EQU		60H
		_RX_highTime		EQU		65H
		_TX_highTime		EQU		57H
		_TX_lowTime		EQU		59H
		_TX_data		EQU		4FH
		_TX_data1		EQU		53H
		_F_RX		EQU		5BH
		_RX_EN		EQU		5CH
		_Time_FLAG		EQU		61H
		_UART_RX_buff		EQU		40H
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	0CH 			//0000 	380C
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	62H 			//0006 	01E2
		LDR 	FSR,0 			//0007 	0804
		STR 	63H 			//0008 	01E3
		LDR 	PCLATH,0 		//0009 	080A
		STR 	64H 			//000A 	01E4
		LJUMP 	B4H 			//000B 	38B4
		ORG		000CH
		LJUMP 	136H 			//000C 	3936

		//;yy_ir.C: 95: sys_init();
		LCALL 	F5H 			//000D 	30F5

		//;yy_ir.C: 96: F_RX = RESET;
		CLRR 	5BH 			//000E 	015B

		//;yy_ir.C: 97: RX_EN = DISABLE;
		CLRR 	5CH 			//000F 	015C

		//;yy_ir.C: 98: (T0IE = 0,T0IF = 0);
		BCR 	INTCON,5 		//0010 	128B
		BCR 	INTCON,2 		//0011 	110B

		//;yy_ir.C: 100: {
		//;yy_ir.C: 104: RX_highTime = 0;
		CLRR 	65H 			//0012 	0165
		CLRR 	66H 			//0013 	0166
		ORG		0014H

		//;yy_ir.C: 105: while(RX_highTime<5000)
		LDWI 	13H 			//0014 	2A13
		SUBWR 	66H,0 			//0015 	0C66
		LDWI 	88H 			//0016 	2A88
		BTSC 	STATUS,2 		//0017 	1503
		SUBWR 	65H,0 			//0018 	0C65

		//;yy_ir.C: 106: {
		//;yy_ir.C: 107: if(PA3)
		BCR 	STATUS,5 		//0019 	1283
		BTSC 	STATUS,0 		//001A 	1403
		LJUMP 	24H 			//001B 	3824
		ORG		001CH
		BTSS 	5H,3 			//001C 	1D85
		LJUMP 	12H 			//001D 	3812

		//;yy_ir.C: 108: RX_highTime++;
		INCR	65H,1 			//001E 	09E5
		BTSC 	STATUS,2 		//001F 	1503
		INCR	66H,1 			//0020 	09E6
		LJUMP 	14H 			//0021 	3814
		CLRWDT	 			//0022 	0001
		BCR 	STATUS,5 		//0023 	1283
		ORG		0024H
		BTSC 	5H,3 			//0024 	1585
		LJUMP 	22H 			//0025 	3822

		//;yy_ir.C: 115: }
		//;yy_ir.C: 116: RX_dataNum = 0;
		CLRR 	5FH 			//0026 	015F

		//;yy_ir.C: 117: for(RX_dataNum = 0;RX_dataNum < 8;RX_dataNum++)
		CLRR 	5FH 			//0027 	015F
		LDWI 	8H 			//0028 	2A08
		SUBWR 	5FH,0 			//0029 	0C5F
		BTSC 	STATUS,0 		//002A 	1403
		LJUMP 	3FH 			//002B 	383F
		ORG		002CH
		BTSC 	5H,3 			//002C 	1585
		LJUMP 	2CH 			//002D 	382C
		LDWI 	8H 			//002E 	2A08

		//;yy_ir.C: 120: RX_EN = ENABLE;
		CLRR 	5CH 			//002F 	015C
		INCR	5CH,1 			//0030 	09DC

		//;yy_ir.C: 121: RX_dataBit = 8;
		STR 	5EH 			//0031 	01DE

		//;yy_ir.C: 122: TMR0 = 100;
		LDWI 	64H 			//0032 	2A64
		STR 	1H 			//0033 	0181
		ORG		0034H

		//;yy_ir.C: 123: (T0IF = 0,T0IE = 1);
		BCR 	INTCON,2 		//0034 	110B
		BSR 	INTCON,5 		//0035 	1A8B

		//;yy_ir.C: 124: while(RX_EN);
		LDR 	5CH,1 			//0036 	08DC
		BTSS 	STATUS,2 		//0037 	1D03
		LJUMP 	36H 			//0038 	3836

		//;yy_ir.C: 125: (T0IE = 0,T0IF = 0);
		BCR 	INTCON,5 		//0039 	128B
		BCR 	INTCON,2 		//003A 	110B

		//;yy_ir.C: 126: while(!PA3);
		BTSS 	5H,3 			//003B 	1D85
		ORG		003CH
		LJUMP 	3BH 			//003C 	383B
		INCR	5FH,1 			//003D 	09DF
		LJUMP 	28H 			//003E 	3828

		//;yy_ir.C: 127: }
		//;yy_ir.C: 128: RX_data = UART_RX_buff[7];
		LDR 	47H,0 			//003F 	0847
		STR 	5DH 			//0040 	01DD

		//;yy_ir.C: 129: switch(RX_data)
		LJUMP 	6BH 			//0041 	386B
		LDWI 	4H 			//0042 	2A04
		XORWR 	5H,1 			//0043 	0485
		ORG		0044H
		LJUMP 	76H 			//0044 	3876
		LDWI 	FFH 			//0045 	2AFF
		CLRR 	56H 			//0046 	0156
		STR 	55H 			//0047 	01D5
		LDWI 	A2H 			//0048 	2AA2
		STR 	54H 			//0049 	01D4
		LDWI 	5DH 			//004A 	2A5D
		STR 	53H 			//004B 	01D3
		ORG		004CH
		CLRR 	5BH 			//004C 	015B
		INCR	5BH,1 			//004D 	09DB
		LJUMP 	76H 			//004E 	3876
		LDWI 	FFH 			//004F 	2AFF
		CLRR 	56H 			//0050 	0156
		STR 	55H 			//0051 	01D5
		LDWI 	E2H 			//0052 	2AE2
		STR 	54H 			//0053 	01D4
		ORG		0054H
		LDWI 	1DH 			//0054 	2A1D
		LJUMP 	4BH 			//0055 	384B
		LDWI 	FFH 			//0056 	2AFF
		CLRR 	56H 			//0057 	0156
		STR 	55H 			//0058 	01D5
		LDWI 	38H 			//0059 	2A38
		STR 	54H 			//005A 	01D4
		LDWI 	C7H 			//005B 	2AC7
		ORG		005CH
		LJUMP 	4BH 			//005C 	384B
		LDWI 	FFH 			//005D 	2AFF
		CLRR 	56H 			//005E 	0156
		STR 	55H 			//005F 	01D5
		LDWI 	98H 			//0060 	2A98
		STR 	54H 			//0061 	01D4
		LDWI 	67H 			//0062 	2A67
		LJUMP 	4BH 			//0063 	384B
		ORG		0064H
		LDWI 	FFH 			//0064 	2AFF
		CLRR 	56H 			//0065 	0156
		STR 	55H 			//0066 	01D5
		LDWI 	2H 			//0067 	2A02
		STR 	54H 			//0068 	01D4
		LDWI 	FDH 			//0069 	2AFD
		LJUMP 	4BH 			//006A 	384B
		LDR 	5DH,0 			//006B 	085D
		ORG		006CH
		STR 	FSR 			//006C 	0184
		LDWI 	DH 			//006D 	2A0D
		SUBWR 	FSR,0 			//006E 	0C04
		BTSC 	STATUS,0 		//006F 	1403
		LJUMP 	76H 			//0070 	3876
		LDWI 	1H 			//0071 	2A01
		STR 	PCLATH 			//0072 	018A
		LDWI 	21H 			//0073 	2A21
		ORG		0074H
		ADDWR 	FSR,0 			//0074 	0B04
		STR 	PCL 			//0075 	0182

		//;yy_ir.C: 151: if(F_RX)
		LDR 	5BH,0 			//0076 	085B
		BTSC 	STATUS,2 		//0077 	1503
		LJUMP 	B2H 			//0078 	38B2

		//;yy_ir.C: 152: {
		//;yy_ir.C: 153: TX_dataBit = 32;
		LDWI 	20H 			//0079 	2A20
		STR 	60H 			//007A 	01E0

		//;yy_ir.C: 154: TX_highTime = 692;
		LDWI 	B4H 			//007B 	2AB4
		ORG		007CH
		STR 	57H 			//007C 	01D7
		LDWI 	2H 			//007D 	2A02
		STR 	58H 			//007E 	01D8

		//;yy_ir.C: 156: TX_lowTime = 346;
		LDWI 	5AH 			//007F 	2A5A
		STR 	59H 			//0080 	01D9
		LDWI 	1H 			//0081 	2A01
		STR 	5AH 			//0082 	01DA

		//;yy_ir.C: 157: (TMR2ON = 1);
		BSR 	12H,2 			//0083 	1912
		ORG		0084H

		//;yy_ir.C: 158: TX_data = TX_data1;
		LDR 	56H,0 			//0084 	0856
		STR 	52H 			//0085 	01D2
		LDR 	55H,0 			//0086 	0855
		STR 	51H 			//0087 	01D1
		LDR 	54H,0 			//0088 	0854
		STR 	50H 			//0089 	01D0
		LDR 	53H,0 			//008A 	0853
		STR 	4FH 			//008B 	01CF
		ORG		008CH

		//;yy_ir.C: 159: while(TX_dataBit)
		LDR 	60H,1 			//008C 	08E0
		BTSC 	STATUS,2 		//008D 	1503
		LJUMP 	A5H 			//008E 	38A5

		//;yy_ir.C: 160: {
		//;yy_ir.C: 165: if(!TX_lowTime)
		LDR 	5AH,0 			//008F 	085A
		IORWR 	59H,0 			//0090 	0359
		BTSS 	STATUS,2 		//0091 	1D03
		LJUMP 	8CH 			//0092 	388C

		//;yy_ir.C: 166: {
		//;yy_ir.C: 167: if(TX_data & 0x80000000)
		BTSS 	52H,7 			//0093 	1FD2
		ORG		0094H
		LJUMP 	99H 			//0094 	3899

		//;yy_ir.C: 168: {
		//;yy_ir.C: 169: TX_highTime = 43;
		LDWI 	2BH 			//0095 	2A2B
		STR 	57H 			//0096 	01D7
		LDWI 	81H 			//0097 	2A81
		LJUMP 	9BH 			//0098 	389B

		//;yy_ir.C: 171: }
		//;yy_ir.C: 170: TX_lowTime = 129;
		//;yy_ir.C: 172: else
		//;yy_ir.C: 173: {
		//;yy_ir.C: 174: TX_highTime = 43;
		LDWI 	2BH 			//0099 	2A2B
		STR 	57H 			//009A 	01D7
		CLRR 	58H 			//009B 	0158
		ORG		009CH

		//;yy_ir.C: 175: TX_lowTime = 43;
		STR 	59H 			//009C 	01D9
		CLRR 	5AH 			//009D 	015A

		//;yy_ir.C: 176: }
		//;yy_ir.C: 177: TX_data = TX_data<<1;
		BCR 	STATUS,0 		//009E 	1003
		RLR 	4FH,1 			//009F 	05CF
		RLR 	50H,1 			//00A0 	05D0
		RLR 	51H,1 			//00A1 	05D1
		RLR 	52H,1 			//00A2 	05D2

		//;yy_ir.C: 178: TX_dataBit--;
		DECR 	60H,1 			//00A3 	0DE0
		ORG		00A4H
		LJUMP 	8CH 			//00A4 	388C
		LDR 	5AH,0 			//00A5 	085A
		IORWR 	59H,0 			//00A6 	0359
		BTSS 	STATUS,2 		//00A7 	1D03
		LJUMP 	A5H 			//00A8 	38A5

		//;yy_ir.C: 182: TX_highTime = 43;
		LDWI 	2BH 			//00A9 	2A2B
		STR 	57H 			//00AA 	01D7
		CLRR 	58H 			//00AB 	0158
		ORG		00ACH

		//;yy_ir.C: 183: while(TX_highTime);
		LDR 	58H,0 			//00AC 	0858
		IORWR 	57H,0 			//00AD 	0357
		BTSS 	STATUS,2 		//00AE 	1D03
		LJUMP 	ACH 			//00AF 	38AC

		//;yy_ir.C: 184: PA4 = 0;
		BCR 	5H,4 			//00B0 	1205

		//;yy_ir.C: 185: (TMR2ON = 0);
		BCR 	12H,2 			//00B1 	1112

		//;yy_ir.C: 186: }
		//;yy_ir.C: 188: F_RX = RESET;
		CLRR 	5BH 			//00B2 	015B
		LJUMP 	12H 			//00B3 	3812
		ORG		00B4H

		//;yy_ir.C: 36: if(T0IE && T0IF)
		BTSC 	INTCON,5 		//00B4 	168B
		BTSS 	INTCON,2 		//00B5 	1D0B
		LJUMP 	CDH 			//00B6 	38CD
		LDWI 	98H 			//00B7 	2A98

		//;yy_ir.C: 37: {
		//;yy_ir.C: 38: static u8 T_100us = 0;
		//;yy_ir.C: 39: static u16 T_1ms = 0;
		//;yy_ir.C: 40: T0IF = RESET;
		BCR 	INTCON,2 		//00B8 	110B

		//;yy_ir.C: 41: TMR0 = 152;
		BCR 	STATUS,5 		//00B9 	1283
		STR 	1H 			//00BA 	0181

		//;yy_ir.C: 54: if(RX_EN)
		LDR 	5CH,0 			//00BB 	085C
		ORG		00BCH
		BTSC 	STATUS,2 		//00BC 	1503
		LJUMP 	CDH 			//00BD 	38CD

		//;yy_ir.C: 55: {
		//;yy_ir.C: 56: if(PA3)
		BTSS 	5H,3 			//00BE 	1D85
		LJUMP 	C2H 			//00BF 	38C2

		//;yy_ir.C: 57: RX_data = (RX_data>>1)|0x80;
		BSR 	STATUS,0 		//00C0 	1803
		LJUMP 	C3H 			//00C1 	38C3

		//;yy_ir.C: 58: else
		//;yy_ir.C: 59: RX_data >>= 1;
		BCR 	STATUS,0 		//00C2 	1003
		RRR	5DH,1 			//00C3 	06DD
		ORG		00C4H

		//;yy_ir.C: 60: RX_dataBit--;
		DECRSZ 	5EH,1 		//00C4 	0EDE

		//;yy_ir.C: 61: if(!RX_dataBit)
		LJUMP 	ECH 			//00C5 	38EC

		//;yy_ir.C: 62: {
		//;yy_ir.C: 63: UART_RX_buff[RX_dataNum] = RX_data;
		LDR 	5FH,0 			//00C6 	085F
		ADDWI 	40H 			//00C7 	2740
		STR 	FSR 			//00C8 	0184
		LDR 	5DH,0 			//00C9 	085D
		STR 	INDF 			//00CA 	0180

		//;yy_ir.C: 64: RX_EN = DISABLE;
		CLRR 	5CH 			//00CB 	015C
		ORG		00CCH
		LJUMP 	ECH 			//00CC 	38EC

		//;yy_ir.C: 67: }
		//;yy_ir.C: 68: }
		//;yy_ir.C: 70: if(TMR2IE && TMR2IF)
		BSR 	STATUS,5 		//00CD 	1A83
		BTSS 	CH,1 			//00CE 	1C8C
		LJUMP 	ECH 			//00CF 	38EC
		BCR 	STATUS,5 		//00D0 	1283
		BTSS 	CH,1 			//00D1 	1C8C
		LJUMP 	ECH 			//00D2 	38EC

		//;yy_ir.C: 71: {
		//;yy_ir.C: 72: TMR2IF = RESET;
		BCR 	CH,1 			//00D3 	108C
		ORG		00D4H

		//;yy_ir.C: 73: if(TX_highTime)
		LDR 	58H,0 			//00D4 	0858
		IORWR 	57H,0 			//00D5 	0357
		BTSC 	STATUS,2 		//00D6 	1503
		LJUMP 	E1H 			//00D7 	38E1

		//;yy_ir.C: 74: {
		//;yy_ir.C: 75: TX_highTime--;
		LDWI 	1H 			//00D8 	2A01
		SUBWR 	57H,1 			//00D9 	0CD7
		LDWI 	0H 			//00DA 	2A00
		BTSS 	STATUS,0 		//00DB 	1C03
		ORG		00DCH
		DECR 	58H,1 			//00DC 	0DD8
		SUBWR 	58H,1 			//00DD 	0CD8

		//;yy_ir.C: 76: PA4 = ~PA4;
		LDWI 	10H 			//00DE 	2A10
		XORWR 	5H,1 			//00DF 	0485
		LJUMP 	ECH 			//00E0 	38EC

		//;yy_ir.C: 79: else if(TX_lowTime)
		LDR 	5AH,0 			//00E1 	085A
		IORWR 	59H,0 			//00E2 	0359
		BTSC 	STATUS,2 		//00E3 	1503
		ORG		00E4H
		LJUMP 	ECH 			//00E4 	38EC

		//;yy_ir.C: 80: {
		//;yy_ir.C: 81: TX_lowTime--;
		LDWI 	1H 			//00E5 	2A01
		SUBWR 	59H,1 			//00E6 	0CD9
		LDWI 	0H 			//00E7 	2A00
		BTSS 	STATUS,0 		//00E8 	1C03
		DECR 	5AH,1 			//00E9 	0DDA
		SUBWR 	5AH,1 			//00EA 	0CDA

		//;yy_ir.C: 82: PA4 = 0;
		BCR 	5H,4 			//00EB 	1205
		ORG		00ECH
		LDR 	64H,0 			//00EC 	0864
		STR 	PCLATH 			//00ED 	018A
		LDR 	63H,0 			//00EE 	0863
		STR 	FSR 			//00EF 	0184
		SWAPR 	62H,0 			//00F0 	0762
		STR 	STATUS 			//00F1 	0183
		SWAPR 	7EH,1 			//00F2 	07FE
		SWAPR 	7EH,0 			//00F3 	077E
		ORG		00F4H
		RETI		 			//00F4 	0009

		//;SYS_INIT.C: 9: OSCCON = (OSCCON &0x8F)|(7<<4);
		BSR 	STATUS,5 		//00F5 	1A83
		LDR 	FH,0 			//00F6 	080F
		ANDWI 	8FH 			//00F7 	248F
		IORWI 	70H 			//00F8 	2570
		STR 	FH 			//00F9 	018F

		//;SYS_INIT.C: 11: TRISA2 = 0;
		BCR 	5H,2 			//00FA 	1105

		//;SYS_INIT.C: 12: PA2 = 1;
		BCR 	STATUS,5 		//00FB 	1283
		ORG		00FCH
		BSR 	5H,2 			//00FC 	1905

		//;SYS_INIT.C: 14: TRISA5 = 0;
		BSR 	STATUS,5 		//00FD 	1A83
		BCR 	5H,5 			//00FE 	1285

		//;SYS_INIT.C: 15: PA5 = 0;
		BCR 	STATUS,5 		//00FF 	1283
		BCR 	5H,5 			//0100 	1285

		//;SYS_INIT.C: 17: TRISA4 = 0;
		BSR 	STATUS,5 		//0101 	1A83
		BCR 	5H,4 			//0102 	1205

		//;SYS_INIT.C: 18: PA4 = 0;
		BCR 	STATUS,5 		//0103 	1283
		ORG		0104H
		BCR 	5H,4 			//0104 	1205
		CLRWDT	 			//0105 	0001

		//;SYS_INIT.C: 25: WDTCON = (WDTCON &0xE1)|(10<<1);
		BCR 	STATUS,5 		//0106 	1283
		LDR 	18H,0 			//0107 	0818
		ANDWI 	E1H 			//0108 	24E1
		IORWI 	14H 			//0109 	2514
		STR 	18H 			//010A 	0198
		LDWI 	1H 			//010B 	2A01
		ORG		010CH

		//;SYS_INIT.C: 27: SWDTEN = DISABLE;
		BCR 	18H,0 			//010C 	1018

		//;SYS_INIT.C: 36: OPTION = (0B00000000+1);
		BSR 	STATUS,5 		//010D 	1A83
		STR 	1H 			//010E 	0181

		//;SYS_INIT.C: 39: TMR0 = 152;
		LDWI 	98H 			//010F 	2A98
		BCR 	STATUS,5 		//0110 	1283
		STR 	1H 			//0111 	0181

		//;SYS_INIT.C: 46: T2CON &= (0<<3);
		CLRR 	12H 			//0112 	0112

		//;SYS_INIT.C: 47: T2CON &= 1;
		LDWI 	1H 			//0113 	2A01
		ORG		0114H
		ANDWR 	12H,1 			//0114 	0292

		//;SYS_INIT.C: 48: PR2 = 52;
		LDWI 	34H 			//0115 	2A34
		BSR 	STATUS,5 		//0116 	1A83
		STR 	12H 			//0117 	0192

		//;SYS_INIT.C: 59: GIE = ENABLE;
		BSR 	INTCON,7 		//0118 	1B8B

		//;SYS_INIT.C: 60: PEIE = ENABLE;
		BSR 	INTCON,6 		//0119 	1B0B

		//;SYS_INIT.C: 61: T0IF = RESET;
		BCR 	INTCON,2 		//011A 	110B

		//;SYS_INIT.C: 62: T0IE = ENABLE;
		BSR 	INTCON,5 		//011B 	1A8B
		ORG		011CH

		//;SYS_INIT.C: 63: TMR2IF = RESET;
		BCR 	STATUS,5 		//011C 	1283
		BCR 	CH,1 			//011D 	108C

		//;SYS_INIT.C: 64: TMR2IE = ENABLE;
		BSR 	STATUS,5 		//011E 	1A83
		BSR 	CH,1 			//011F 	188C
		RET		 					//0120 	0004
		LJUMP 	42H 			//0121 	3842
		LJUMP 	42H 			//0122 	3842
		LJUMP 	76H 			//0123 	3876
		ORG		0124H
		LJUMP 	45H 			//0124 	3845
		LJUMP 	4FH 			//0125 	384F
		LJUMP 	56H 			//0126 	3856
		LJUMP 	56H 			//0127 	3856
		LJUMP 	45H 			//0128 	3845
		LJUMP 	76H 			//0129 	3876
		LJUMP 	5DH 			//012A 	385D
		LJUMP 	76H 			//012B 	3876
		ORG		012CH
		LJUMP 	76H 			//012C 	3876
		LJUMP 	64H 			//012D 	3864
		CLRWDT	 			//012E 	0001
		CLRR 	INDF 			//012F 	0100
		INCR	FSR,1 			//0130 	0984
		XORWR 	FSR,0 			//0131 	0404
		BTSC 	STATUS,2 		//0132 	1503
		RETW 	0H 			//0133 	2100
		ORG		0134H
		XORWR 	FSR,0 			//0134 	0404
		LJUMP 	12FH 			//0135 	392F
		LDWI 	40H 			//0136 	2A40
		STR 	FSR 			//0137 	0184
		LDWI 	62H 			//0138 	2A62
		LCALL 	12EH 			//0139 	312E
		CLRR 	STATUS 			//013A 	0103
		LJUMP 	0DH 			//013B 	380D
			END
