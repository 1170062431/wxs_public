//Deviec:FT61F02X
//-----------------------Variable---------------------------------
		_stu_buzzer.setBuzzerOnTime_ms		EQU		20H
		_stu_buzzer.setBuzzerOffTime_ms		EQU		22H
		_stu_buzzer.C_buzzerOnTime_ms		EQU		24H
		_stu_buzzer.C_buzzerOffTime_ms		EQU		26H
		_stu_buzzer.buzzerTimes		EQU		28H
		_stu_buzzer		EQU		20H
		_SAFlag		EQU		7AH
		_VREGC		EQU		2EH
		_Time_FLAG.bit1		EQU		78H
		_Time_FLAG		EQU		78H
		_F_keyLJ		EQU		2DH
		_keyBuff		EQU		79H
		_keySta		EQU		31H
		_keyBackUp		EQU		2FH
		_keyCode		EQU		30H
		_mode		EQU		32H
		_C_sleep		EQU		2CH
//-----------------------Variable END---------------------------------
		ORG		0000H
		LJUMP 	0CH 			//0000 	380C
		ORG		0004H
		STR 	7EH 			//0004 	01FE
		SWAPR 	STATUS,0 		//0005 	0703
		STR 	70H 			//0006 	01F0
		LDR 	FSR,0 			//0007 	0804
		STR 	71H 			//0008 	01F1
		LDR 	PCLATH,0 		//0009 	080A
		STR 	72H 			//000A 	01F2
		LJUMP 	CFH 			//000B 	38CF
		ORG		000CH
		LJUMP 	185H 			//000C 	3985

		//;user_project.C: 104: POWER_INITIAL();
		LCALL 	6EH 			//000D 	306E

		//;user_project.C: 105: ADC_INITIAL();
		LCALL 	1B3H 			//000E 	31B3

		//;user_project.C: 108: F_feedDog = SET;
		LCALL 	17AH 			//000F 	317A
		LDWI 	1H 			//0010 	2A01

		//;user_project.C: 110: PA7 = 1;
		BCR 	STATUS,6 		//0011 	1303
		BSR 	5H,7 			//0012 	1B85

		//;user_project.C: 111: PA4 = 1;
		BSR 	5H,4 			//0013 	1A05
		ORG		0014H
		BSR 	5H,6 			//0014 	1B05

		//;user_project.C: 113: DelayS(1);
		LCALL 	146H 			//0015 	3146
		LDWI 	C8H 			//0016 	2AC8

		//;user_project.C: 114: PA7 = 0;
		BCR 	5H,7 			//0017 	1385

		//;user_project.C: 115: PA4 = 0;
		BCR 	5H,4 			//0018 	1205
		BCR 	5H,6 			//0019 	1305

		//;user_project.C: 117: buzzerOn(200, 200, 1);
		STR 	73H 			//001A 	01F3
		CLRR 	74H 			//001B 	0174
		ORG		001CH
		STR 	75H 			//001C 	01F5
		CLRR 	76H 			//001D 	0176
		CLRR 	77H 			//001E 	0177
		INCR	77H,1 			//001F 	09F7
		LCALL 	133H 			//0020 	3133

		//;user_project.C: 120: {
		//;user_project.C: 121: if(Time_FLAG.bit1)
		BTSS 	78H,0 			//0021 	1C78
		LJUMP 	5BH 			//0022 	385B

		//;user_project.C: 122: {
		//;user_project.C: 123: Time_FLAG.bit1 = RESET;
		BCR 	78H,0 			//0023 	1078
		ORG		0024H

		//;user_project.C: 124: keyScan();
		LCALL 	115H 			//0024 	3115

		//;user_project.C: 125: if(keyCode && !F_keyLJ)
		LDR 	30H,0 			//0025 	0830
		BTSC 	STATUS,2 		//0026 	1503
		LJUMP 	2CH 			//0027 	382C
		LDR 	2DH,1 			//0028 	08AD
		BTSS 	STATUS,2 		//0029 	1D03
		LJUMP 	2CH 			//002A 	382C

		//;user_project.C: 126: {
		//;user_project.C: 127: keyAction();
		LCALL 	158H 			//002B 	3158
		ORG		002CH

		//;user_project.C: 128: }
		//;user_project.C: 131: if(stu_buzzer.buzzerTimes)
		LDR 	28H,0 			//002C 	0828
		BTSC 	STATUS,2 		//002D 	1503
		LJUMP 	58H 			//002E 	3858

		//;user_project.C: 132: {
		//;user_project.C: 133: if(stu_buzzer.C_buzzerOnTime_ms)
		LDWI 	24H 			//002F 	2A24
		STR 	FSR 			//0030 	0184
		BCR 	STATUS,7 		//0031 	1383
		LDR 	INDF,0 			//0032 	0800
		INCR	FSR,1 			//0033 	0984
		ORG		0034H
		IORWR 	INDF,0 		//0034 	0300
		BTSC 	STATUS,2 		//0035 	1503
		LJUMP 	3EH 			//0036 	383E

		//;user_project.C: 134: {
		//;user_project.C: 135: stu_buzzer.C_buzzerOnTime_ms--;
		LDWI 	1H 			//0037 	2A01
		SUBWR 	24H,1 			//0038 	0CA4
		LDWI 	0H 			//0039 	2A00
		BTSS 	STATUS,0 		//003A 	1C03
		DECR 	25H,1 			//003B 	0DA5
		ORG		003CH
		SUBWR 	25H,1 			//003C 	0CA5

		//;user_project.C: 136: }
		LJUMP 	58H 			//003D 	3858

		//;user_project.C: 137: else if(stu_buzzer.C_buzzerOffTime_ms)
		LDWI 	6H 			//003E 	2A06
		ADDWI 	20H 			//003F 	2720
		STR 	FSR 			//0040 	0184
		LDR 	INDF,0 			//0041 	0800
		INCR	FSR,1 			//0042 	0984
		IORWR 	INDF,0 		//0043 	0300
		ORG		0044H
		BTSC 	STATUS,2 		//0044 	1503
		LJUMP 	4DH 			//0045 	384D

		//;user_project.C: 138: {
		//;user_project.C: 139: stu_buzzer.C_buzzerOffTime_ms--;
		LDWI 	1H 			//0046 	2A01
		SUBWR 	26H,1 			//0047 	0CA6
		LDWI 	0H 			//0048 	2A00
		BTSS 	STATUS,0 		//0049 	1C03
		DECR 	27H,1 			//004A 	0DA7
		SUBWR 	27H,1 			//004B 	0CA7
		ORG		004CH

		//;user_project.C: 140: }
		LJUMP 	58H 			//004C 	3858

		//;user_project.C: 141: else
		//;user_project.C: 142: {
		//;user_project.C: 143: stu_buzzer.buzzerTimes--;
		DECR 	28H,1 			//004D 	0DA8

		//;user_project.C: 144: if(stu_buzzer.buzzerTimes)
		BTSC 	STATUS,2 		//004E 	1503
		LJUMP 	58H 			//004F 	3858

		//;user_project.C: 145: {
		//;user_project.C: 146: stu_buzzer.C_buzzerOnTime_ms = stu_buzzer.setBuzzerOnTime_ms;
		LDR 	21H,0 			//0050 	0821
		STR 	25H 			//0051 	01A5
		LDR 	20H,0 			//0052 	0820
		STR 	24H 			//0053 	01A4
		ORG		0054H

		//;user_project.C: 147: stu_buzzer.C_buzzerOffTime_ms = stu_buzzer.setBuzzerOffTime_ms;
		LDR 	23H,0 			//0054 	0823
		STR 	27H 			//0055 	01A7
		LDR 	22H,0 			//0056 	0822
		STR 	26H 			//0057 	01A6

		//;user_project.C: 148: }
		//;user_project.C: 149: }
		//;user_project.C: 150: }
		//;user_project.C: 153: if(C_sleep)
		LDR 	2CH,0 			//0058 	082C
		BTSS 	STATUS,2 		//0059 	1D03

		//;user_project.C: 154: C_sleep--;
		DECR 	2CH,1 			//005A 	0DAC

		//;user_project.C: 156: }
		//;user_project.C: 158: if(mode == MODE_IDLE)
		BCR 	STATUS,5 		//005B 	1283
		ORG		005CH
		BCR 	STATUS,6 		//005C 	1303
		LDR 	32H,1 			//005D 	08B2
		BTSS 	STATUS,2 		//005E 	1D03
		LJUMP 	6BH 			//005F 	386B

		//;user_project.C: 159: {
		//;user_project.C: 160: if(!C_sleep)
		LDR 	2CH,1 			//0060 	08AC
		BTSS 	STATUS,2 		//0061 	1D03
		LJUMP 	21H 			//0062 	3821

		//;user_project.C: 161: {
		//;user_project.C: 162: C_sleep = 500;
		LDWI 	F4H 			//0063 	2AF4
		ORG		0064H
		STR 	2CH 			//0064 	01AC

		//;user_project.C: 163: PAIF =0;
		BCR 	INTCON,0 		//0065 	100B

		//;user_project.C: 164: IOCA2 =1;
		BSR 	STATUS,5 		//0066 	1A83
		BSR 	16H,2 			//0067 	1916

		//;user_project.C: 166: PAIE =1;
		//;user_project.C: 165: ReadAPin = PA2;
		BSR 	INTCON,3 		//0068 	198B
		SLEEP	 			//0069 	0002
		LJUMP 	21H 			//006A 	3821

		//;user_project.C: 170: else
		//;user_project.C: 171: {
		//;user_project.C: 172: C_sleep = 500;
		LDWI 	F4H 			//006B 	2AF4
		ORG		006CH
		STR 	2CH 			//006C 	01AC
		LJUMP 	21H 			//006D 	3821

		//;sys_init.c: 9: OSCCON = (OSCCON & 0x8F)|(7 << 4);
		BSR 	STATUS,5 		//006E 	1A83
		LDR 	FH,0 			//006F 	080F
		ANDWI 	8FH 			//0070 	248F
		IORWI 	70H 			//0071 	2570
		STR 	FH 			//0072 	018F

		//;sys_init.c: 11: INTCON = 0;
		CLRR 	INTCON 			//0073 	010B
		ORG		0074H

		//;sys_init.c: 12: PORTA = 0B00000000;
		BCR 	STATUS,5 		//0074 	1283
		CLRR 	5H 			//0075 	0105

		//;sys_init.c: 13: TRISA = 0B11111111;
		LDWI 	FFH 			//0076 	2AFF
		BSR 	STATUS,5 		//0077 	1A83
		STR 	5H 			//0078 	0185

		//;sys_init.c: 15: PORTC = 0B00000000;
		BCR 	STATUS,5 		//0079 	1283
		CLRR 	7H 			//007A 	0107

		//;sys_init.c: 16: TRISC = 0B11111111;
		BSR 	STATUS,5 		//007B 	1A83
		ORG		007CH
		STR 	7H 			//007C 	0187

		//;sys_init.c: 18: WPUA = 0B00000000;
		CLRR 	15H 			//007D 	0115

		//;sys_init.c: 19: WPUC = 0B00000000;
		CLRR 	8H 			//007E 	0108

		//;sys_init.c: 20: MSCKCON = 0B00000000;
		BCR 	STATUS,5 		//007F 	1283
		CLRR 	1BH 			//0080 	011B

		//;sys_init.c: 23: CMCON0 = 0B00000000;
		CLRR 	19H 			//0081 	0119

		//;sys_init.c: 24: ANSEL = 0B10101000;
		LDWI 	A8H 			//0082 	2AA8
		BSR 	STATUS,5 		//0083 	1A83
		ORG		0084H
		STR 	11H 			//0084 	0191

		//;sys_init.c: 26: TRISC1 = 1;
		BSR 	7H,1 			//0085 	1887

		//;sys_init.c: 27: WPUA3 = 0;
		BCR 	15H,3 			//0086 	1195

		//;sys_init.c: 29: TRISC1 = 1;
		BSR 	7H,1 			//0087 	1887

		//;sys_init.c: 30: WPUC1 = 0;
		BCR 	8H,1 			//0088 	1088

		//;sys_init.c: 32: TRISC3 = 0;
		BCR 	7H,3 			//0089 	1187

		//;sys_init.c: 33: PC3 = 0;
		BCR 	STATUS,5 		//008A 	1283
		BCR 	7H,3 			//008B 	1187
		ORG		008CH

		//;sys_init.c: 35: TRISC2= 0;
		BSR 	STATUS,5 		//008C 	1A83
		BCR 	7H,2 			//008D 	1107

		//;sys_init.c: 36: PC2 = 0;
		BCR 	STATUS,5 		//008E 	1283
		BCR 	7H,2 			//008F 	1107

		//;sys_init.c: 38: TRISA4 = 0;
		BSR 	STATUS,5 		//0090 	1A83
		BCR 	5H,4 			//0091 	1205

		//;sys_init.c: 39: PA4 = 0;
		BCR 	STATUS,5 		//0092 	1283
		BCR 	5H,4 			//0093 	1205
		ORG		0094H

		//;sys_init.c: 41: TRISC4 = 0;
		BSR 	STATUS,5 		//0094 	1A83
		BCR 	7H,4 			//0095 	1207

		//;sys_init.c: 42: PC4 = 0;
		BCR 	STATUS,5 		//0096 	1283
		BCR 	7H,4 			//0097 	1207

		//;sys_init.c: 44: TRISA2 = 1;
		BSR 	STATUS,5 		//0098 	1A83
		BSR 	5H,2 			//0099 	1905

		//;sys_init.c: 45: WPUA2 = 1;
		BSR 	15H,2 			//009A 	1915

		//;sys_init.c: 47: TRISA0 = 1;
		BSR 	5H,0 			//009B 	1805
		ORG		009CH

		//;sys_init.c: 48: WPUA0 = 1;
		BSR 	15H,0 			//009C 	1815

		//;sys_init.c: 49: TRISA1 = 1;
		BSR 	5H,1 			//009D 	1885

		//;sys_init.c: 50: WPUA1 = 1;
		BSR 	15H,1 			//009E 	1895

		//;sys_init.c: 51: TRISA5 = 1;
		BSR 	5H,5 			//009F 	1A85

		//;sys_init.c: 52: WPUA5 = 1;
		BSR 	15H,5 			//00A0 	1A95

		//;sys_init.c: 53: TRISC0 = 1;
		BSR 	7H,0 			//00A1 	1807

		//;sys_init.c: 54: WPUC0 = 1;
		BSR 	8H,0 			//00A2 	1808

		//;sys_init.c: 55: TRISC5 = 1;
		BSR 	7H,5 			//00A3 	1A87
		ORG		00A4H

		//;sys_init.c: 56: WPUC5 = 1;
		BSR 	8H,5 			//00A4 	1A88
		CLRWDT	 			//00A5 	0001

		//;sys_init.c: 63: WDTCON = (WDTCON &0xE1)|(10<<1);
		BCR 	STATUS,5 		//00A6 	1283
		BCR 	STATUS,6 		//00A7 	1303
		LDR 	18H,0 			//00A8 	0818
		ANDWI 	E1H 			//00A9 	24E1
		IORWI 	14H 			//00AA 	2514
		STR 	18H 			//00AB 	0198
		ORG		00ACH
		LDWI 	2H 			//00AC 	2A02

		//;sys_init.c: 65: SWDTEN = DISABLE;
		BCR 	18H,0 			//00AD 	1018

		//;sys_init.c: 74: OPTION = (0B00000000+2);
		BSR 	STATUS,5 		//00AE 	1A83
		STR 	1H 			//00AF 	0181

		//;sys_init.c: 79: TMR0 = 131;
		LDWI 	83H 			//00B0 	2A83
		BCR 	STATUS,5 		//00B1 	1283
		STR 	1H 			//00B2 	0181

		//;sys_init.c: 89: T1CON = 0B00000000;
		CLRR 	10H 			//00B3 	0110
		ORG		00B4H

		//;sys_init.c: 93: TMR1L = 0XBF;
		LDWI 	BFH 			//00B4 	2ABF
		STR 	EH 			//00B5 	018E

		//;sys_init.c: 94: TMR1H = 0XE0;
		LDWI 	E0H 			//00B6 	2AE0
		STR 	FH 			//00B7 	018F

		//;sys_init.c: 102: T2CON = (1<<3)|1;
		LDWI 	9H 			//00B8 	2A09
		STR 	12H 			//00B9 	0192

		//;sys_init.c: 103: PR2 = 13;
		LDWI 	DH 			//00BA 	2A0D
		BSR 	STATUS,5 		//00BB 	1A83
		ORG		00BCH
		STR 	12H 			//00BC 	0192

		//;sys_init.c: 115: GIE = ENABLE;
		BSR 	INTCON,7 		//00BD 	1B8B

		//;sys_init.c: 116: PEIE = ENABLE;
		BSR 	INTCON,6 		//00BE 	1B0B

		//;sys_init.c: 117: T0IF = RESET;
		BCR 	INTCON,2 		//00BF 	110B

		//;sys_init.c: 118: T0IE = ENABLE;
		BSR 	INTCON,5 		//00C0 	1A8B

		//;sys_init.c: 119: TMR1IF = RESET;
		BCR 	STATUS,5 		//00C1 	1283
		BCR 	CH,0 			//00C2 	100C

		//;sys_init.c: 120: TMR1IE = DISABLE;
		BSR 	STATUS,5 		//00C3 	1A83
		ORG		00C4H
		BCR 	CH,0 			//00C4 	100C

		//;sys_init.c: 121: TMR2IF = RESET;
		BCR 	STATUS,5 		//00C5 	1283
		BCR 	CH,1 			//00C6 	108C

		//;sys_init.c: 122: TMR2IE = DISABLE;
		BSR 	STATUS,5 		//00C7 	1A83
		BCR 	CH,1 			//00C8 	108C

		//;sys_init.c: 124: (T0IF = 0,T0IE = 1);
		BCR 	INTCON,2 		//00C9 	110B
		BSR 	INTCON,5 		//00CA 	1A8B

		//;sys_init.c: 125: (TMR1ON = 0);
		BCR 	STATUS,5 		//00CB 	1283
		ORG		00CCH
		BCR 	10H,0 			//00CC 	1010

		//;sys_init.c: 126: (TMR2ON = 0);
		BCR 	12H,2 			//00CD 	1112
		RET		 					//00CE 	0004

		//;test_61f02x_int.c: 33: if(T0IE && T0IF)
		BTSC 	INTCON,5 		//00CF 	168B
		BTSS 	INTCON,2 		//00D0 	1D0B
		LJUMP 	102H 			//00D1 	3902
		LDWI 	83H 			//00D2 	2A83

		//;test_61f02x_int.c: 34: {
		//;test_61f02x_int.c: 58: static u8 T_125us = 0;
		//;test_61f02x_int.c: 59: static u16 T_1ms = 0;
		//;test_61f02x_int.c: 60: T0IF = RESET;
		BCR 	INTCON,2 		//00D3 	110B
		ORG		00D4H

		//;test_61f02x_int.c: 61: TMR0 = 131;
		BCR 	STATUS,5 		//00D4 	1283
		BCR 	STATUS,6 		//00D5 	1303
		STR 	1H 			//00D6 	0181

		//;test_61f02x_int.c: 64: if(stu_buzzer.C_buzzerOnTime_ms)
		LDWI 	4H 			//00D7 	2A04
		ADDWI 	20H 			//00D8 	2720
		STR 	FSR 			//00D9 	0184
		BCR 	STATUS,7 		//00DA 	1383
		LDR 	INDF,0 			//00DB 	0800
		ORG		00DCH
		INCR	FSR,1 			//00DC 	0984
		IORWR 	INDF,0 		//00DD 	0300
		BTSC 	STATUS,2 		//00DE 	1503
		LJUMP 	ECH 			//00DF 	38EC

		//;test_61f02x_int.c: 65: {
		//;test_61f02x_int.c: 66: PC3 = PC2;
		BTSS 	7H,2 			//00E0 	1D07
		LJUMP 	E6H 			//00E1 	38E6
		BCR 	STATUS,5 		//00E2 	1283
		BCR 	STATUS,6 		//00E3 	1303
		ORG		00E4H
		BSR 	7H,3 			//00E4 	1987
		LJUMP 	E9H 			//00E5 	38E9
		BCR 	STATUS,5 		//00E6 	1283
		BCR 	STATUS,6 		//00E7 	1303
		BCR 	7H,3 			//00E8 	1187

		//;test_61f02x_int.c: 67: PC2 = !PC2;
		LDWI 	4H 			//00E9 	2A04
		XORWR 	7H,1 			//00EA 	0487

		//;test_61f02x_int.c: 68: }
		LJUMP 	EEH 			//00EB 	38EE
		ORG		00ECH

		//;test_61f02x_int.c: 69: else
		//;test_61f02x_int.c: 70: {
		//;test_61f02x_int.c: 71: PC3 = 0;
		BCR 	7H,3 			//00EC 	1187

		//;test_61f02x_int.c: 72: PC2 = 0;
		BCR 	7H,2 			//00ED 	1107

		//;test_61f02x_int.c: 73: }
		//;test_61f02x_int.c: 76: T_125us++;
		INCR	2BH,1 			//00EE 	09AB

		//;test_61f02x_int.c: 77: if(T_125us == 8)
		LDR 	2BH,0 			//00EF 	082B
		XORWI 	8H 			//00F0 	2608
		BTSS 	STATUS,2 		//00F1 	1D03
		LJUMP 	102H 			//00F2 	3902

		//;test_61f02x_int.c: 78: {
		//;test_61f02x_int.c: 79: T_125us = 0;
		CLRR 	2BH 			//00F3 	012B
		ORG		00F4H

		//;test_61f02x_int.c: 80: Time_FLAG.bit1 = SET;
		BSR 	78H,0 			//00F4 	1878

		//;test_61f02x_int.c: 81: T_1ms++;
		INCR	29H,1 			//00F5 	09A9
		BTSC 	STATUS,2 		//00F6 	1503
		INCR	2AH,1 			//00F7 	09AA

		//;test_61f02x_int.c: 82: if(T_1ms == 1000)
		LDR 	2AH,0 			//00F8 	082A
		XORWI 	3H 			//00F9 	2603
		LDWI 	E8H 			//00FA 	2AE8
		BTSC 	STATUS,2 		//00FB 	1503
		ORG		00FCH
		XORWR 	29H,0 			//00FC 	0429
		BTSS 	STATUS,2 		//00FD 	1D03
		LJUMP 	102H 			//00FE 	3902

		//;test_61f02x_int.c: 83: {
		//;test_61f02x_int.c: 84: T_1ms = 0;
		CLRR 	29H 			//00FF 	0129
		CLRR 	2AH 			//0100 	012A

		//;test_61f02x_int.c: 85: Time_FLAG.bit8 = SET;
		BSR 	78H,7 			//0101 	1BF8

		//;test_61f02x_int.c: 87: }
		//;test_61f02x_int.c: 88: }
		//;test_61f02x_int.c: 90: }
		//;test_61f02x_int.c: 116: if(PAIE && PAIF)
		BTSC 	INTCON,3 		//0102 	158B
		BTSS 	INTCON,0 		//0103 	1C0B
		ORG		0104H
		LJUMP 	10CH 			//0104 	390C

		//;test_61f02x_int.c: 117: {
		//;test_61f02x_int.c: 118: ReadAPin = PORTA;
		BCR 	STATUS,5 		//0105 	1283
		BCR 	STATUS,6 		//0106 	1303
		LDR 	5H,0 			//0107 	0805

		//;test_61f02x_int.c: 119: PAIF = 0;
		BCR 	INTCON,0 		//0108 	100B

		//;test_61f02x_int.c: 120: PAIE = 0;
		BCR 	INTCON,3 		//0109 	118B

		//;test_61f02x_int.c: 121: IOCA2 =0;
		BSR 	STATUS,5 		//010A 	1A83
		BCR 	16H,2 			//010B 	1116
		ORG		010CH
		LDR 	72H,0 			//010C 	0872
		STR 	PCLATH 			//010D 	018A
		LDR 	71H,0 			//010E 	0871
		STR 	FSR 			//010F 	0184
		SWAPR 	70H,0 			//0110 	0770
		STR 	STATUS 			//0111 	0183
		SWAPR 	7EH,1 			//0112 	07FE
		SWAPR 	7EH,0 			//0113 	077E
		ORG		0114H
		RETI		 			//0114 	0009

		//;user_project.C: 54: keyBuff = (keyBuff<<1)|PA2;
		BCR 	STATUS,0 		//0115 	1003
		BCR 	STATUS,5 		//0116 	1283
		BCR 	STATUS,6 		//0117 	1303
		BTSC 	5H,2 			//0118 	1505
		BSR 	STATUS,0 		//0119 	1803
		RLR 	79H,1 			//011A 	05F9

		//;user_project.C: 55: if(!(keyBuff&0x0F))
		LDR 	79H,0 			//011B 	0879
		ORG		011CH
		ANDWI 	FH 			//011C 	240F
		BTSS 	STATUS,2 		//011D 	1D03
		LJUMP 	129H 			//011E 	3929

		//;user_project.C: 56: {
		//;user_project.C: 57: keySta = 1;
		CLRR 	31H 			//011F 	0131
		INCR	31H,1 			//0120 	09B1

		//;user_project.C: 58: if(keySta != keyBackUp)
		DECR 	2FH,0 			//0121 	0D2F
		BTSC 	STATUS,2 		//0122 	1503
		RET		 					//0123 	0004
		ORG		0124H

		//;user_project.C: 59: {
		//;user_project.C: 60: keyCode = 1;
		CLRR 	30H 			//0124 	0130
		INCR	30H,1 			//0125 	09B0

		//;user_project.C: 61: keyBackUp = 1;
		CLRR 	2FH 			//0126 	012F
		INCR	2FH,1 			//0127 	09AF
		RET		 					//0128 	0004

		//;user_project.C: 64: else if((keyBuff&0x0F) == 0x0F)
		LDR 	79H,0 			//0129 	0879
		ANDWI 	FH 			//012A 	240F
		XORWI 	FH 			//012B 	260F
		ORG		012CH
		BTSS 	STATUS,2 		//012C 	1D03
		RET		 					//012D 	0004

		//;user_project.C: 65: {
		//;user_project.C: 66: keySta = 0;
		CLRR 	31H 			//012E 	0131

		//;user_project.C: 67: keyCode = 0;
		CLRR 	30H 			//012F 	0130

		//;user_project.C: 68: keyBackUp = 0;
		CLRR 	2FH 			//0130 	012F

		//;user_project.C: 69: F_keyLJ = RESET;
		CLRR 	2DH 			//0131 	012D
		RET		 					//0132 	0004

		//;buzzer.c: 12: stu_buzzer.setBuzzerOnTime_ms = bzOnTime_ms;
		LDR 	74H,0 			//0133 	0874
		ORG		0134H
		STR 	21H 			//0134 	01A1
		LDR 	73H,0 			//0135 	0873
		STR 	20H 			//0136 	01A0

		//;buzzer.c: 13: stu_buzzer.setBuzzerOffTime_ms = bzOffTime_ms;
		LDR 	76H,0 			//0137 	0876
		STR 	23H 			//0138 	01A3
		LDR 	75H,0 			//0139 	0875
		STR 	22H 			//013A 	01A2

		//;buzzer.c: 14: stu_buzzer.C_buzzerOnTime_ms = stu_buzzer.setBuzzerOnTime_ms;
		LDR 	21H,0 			//013B 	0821
		ORG		013CH
		STR 	25H 			//013C 	01A5
		LDR 	20H,0 			//013D 	0820
		STR 	24H 			//013E 	01A4

		//;buzzer.c: 15: stu_buzzer.C_buzzerOffTime_ms = stu_buzzer.setBuzzerOffTime_ms;
		LDR 	23H,0 			//013F 	0823
		STR 	27H 			//0140 	01A7
		LDR 	22H,0 			//0141 	0822
		STR 	26H 			//0142 	01A6

		//;buzzer.c: 16: stu_buzzer.buzzerTimes = bzTimes;
		LDR 	77H,0 			//0143 	0877
		ORG		0144H
		STR 	28H 			//0144 	01A8
		RET		 					//0145 	0004
		STR 	33H 			//0146 	01B3

		//;sys_init.c: 171: unsigned char a,b;
		//;sys_init.c: 172: for(a=0;a<Time;a++)
		CLRR 	34H 			//0147 	0134
		LDR 	33H,0 			//0148 	0833
		SUBWR 	34H,0 			//0149 	0C34
		BTSC 	STATUS,0 		//014A 	1403
		RET		 					//014B 	0004
		ORG		014CH

		//;sys_init.c: 173: {
		//;sys_init.c: 174: for(b=0;b<10;b++)
		CLRR 	35H 			//014C 	0135

		//;sys_init.c: 175: {
		//;sys_init.c: 176: DelayMs(100);
		LDWI 	64H 			//014D 	2A64
		LCALL 	16AH 			//014E 	316A
		LDWI 	AH 			//014F 	2A0A
		BCR 	STATUS,5 		//0150 	1283
		BCR 	STATUS,6 		//0151 	1303
		INCR	35H,1 			//0152 	09B5
		SUBWR 	35H,0 			//0153 	0C35
		ORG		0154H
		BTSS 	STATUS,0 		//0154 	1C03
		LJUMP 	14DH 			//0155 	394D
		INCR	34H,1 			//0156 	09B4
		LJUMP 	148H 			//0157 	3948

		//;user_project.C: 80: if(keyCode==1)
		DECRSZ 	30H,0 		//0158 	0E30
		LJUMP 	167H 			//0159 	3967
		LJUMP 	15FH 			//015A 	395F

		//;user_project.C: 85: turnToModeWork();
		LCALL 	18FH 			//015B 	318F
		ORG		015CH

		//;user_project.C: 86: break;
		LJUMP 	167H 			//015C 	3967

		//;user_project.C: 88: turnToModeIdle();
		LCALL 	199H 			//015D 	3199

		//;user_project.C: 89: break;
		LJUMP 	167H 			//015E 	3967
		LDR 	32H,0 			//015F 	0832
		XORWI 	0H 			//0160 	2600
		BTSC 	STATUS,2 		//0161 	1503
		LJUMP 	15BH 			//0162 	395B
		XORWI 	1H 			//0163 	2601
		ORG		0164H
		BTSC 	STATUS,2 		//0164 	1503
		LJUMP 	15DH 			//0165 	395D
		LJUMP 	167H 			//0166 	3967

		//;user_project.C: 92: }
		//;user_project.C: 93: F_keyLJ = SET;
		CLRR 	2DH 			//0167 	012D
		INCR	2DH,1 			//0168 	09AD
		RET		 					//0169 	0004
		STR 	75H 			//016A 	01F5

		//;sys_init.c: 153: unsigned char a,b;
		//;sys_init.c: 154: for(a=0;a<Time;a++)
		CLRR 	76H 			//016B 	0176
		ORG		016CH
		LDR 	75H,0 			//016C 	0875
		SUBWR 	76H,0 			//016D 	0C76
		BTSC 	STATUS,0 		//016E 	1403
		RET		 					//016F 	0004

		//;sys_init.c: 155: {
		//;sys_init.c: 156: for(b=0;b<5;b++)
		CLRR 	77H 			//0170 	0177

		//;sys_init.c: 157: {
		//;sys_init.c: 158: DelayUs(197);
		LDWI 	C5H 			//0171 	2AC5
		LCALL 	1A2H 			//0172 	31A2
		LDWI 	5H 			//0173 	2A05
		ORG		0174H
		INCR	77H,1 			//0174 	09F7
		SUBWR 	77H,0 			//0175 	0C77
		BTSS 	STATUS,0 		//0176 	1C03
		LJUMP 	171H 			//0177 	3971
		INCR	76H,1 			//0178 	09F6
		LJUMP 	16CH 			//0179 	396C

		//;TEST_61F02X_PWM.C: 138: PWM3CR0 = 0B00110010;
		LDWI 	32H 			//017A 	2A32
		BSR 	STATUS,6 		//017B 	1B03
		ORG		017CH
		STR 	FH 			//017C 	018F

		//;TEST_61F02X_PWM.C: 159: PWM3CR1 = 0B10000000;
		LDWI 	80H 			//017D 	2A80
		STR 	10H 			//017E 	0190

		//;TEST_61F02X_PWM.C: 164: TMR3H=0;
		CLRR 	DH 			//017F 	010D

		//;TEST_61F02X_PWM.C: 168: T3CKDIV = 30;
		LDWI 	1EH 			//0180 	2A1E
		STR 	11H 			//0181 	0191

		//;TEST_61F02X_PWM.C: 172: PR3L = 128;
		LDWI 	80H 			//0182 	2A80
		STR 	EH 			//0183 	018E
		ORG		0184H
		RET		 					//0184 	0004
		LDWI 	20H 			//0185 	2A20
		CLRR 	7AH 			//0186 	017A
		CLRR 	78H 			//0187 	0178
		CLRR 	79H 			//0188 	0179
		BCR 	STATUS,7 		//0189 	1383
		STR 	FSR 			//018A 	0184
		LDWI 	33H 			//018B 	2A33
		ORG		018CH
		LCALL 	1ABH 			//018C 	31AB
		CLRR 	STATUS 			//018D 	0103
		LJUMP 	0DH 			//018E 	380D
		LDWI 	C8H 			//018F 	2AC8

		//;user_project.C: 43: mode = MODE_WORK;
		CLRR 	32H 			//0190 	0132
		INCR	32H,1 			//0191 	09B2

		//;user_project.C: 44: buzzerOn(200, 200, 1);
		STR 	73H 			//0192 	01F3
		CLRR 	74H 			//0193 	0174
		ORG		0194H
		STR 	75H 			//0194 	01F5
		CLRR 	76H 			//0195 	0176
		CLRR 	77H 			//0196 	0177
		INCR	77H,1 			//0197 	09F7
		LJUMP 	133H 			//0198 	3933
		LDWI 	C8H 			//0199 	2AC8

		//;user_project.C: 32: mode = MODE_IDLE;
		CLRR 	32H 			//019A 	0132

		//;user_project.C: 33: buzzerOn(200, 200, 1);
		STR 	73H 			//019B 	01F3
		ORG		019CH
		CLRR 	74H 			//019C 	0174
		STR 	75H 			//019D 	01F5
		CLRR 	76H 			//019E 	0176
		CLRR 	77H 			//019F 	0177
		INCR	77H,1 			//01A0 	09F7
		LJUMP 	133H 			//01A1 	3933
		STR 	73H 			//01A2 	01F3

		//;sys_init.c: 138: unsigned char a;
		//;sys_init.c: 139: for(a=0;a<Time;a++)
		CLRR 	74H 			//01A3 	0174
		ORG		01A4H
		LDR 	73H,0 			//01A4 	0873
		SUBWR 	74H,0 			//01A5 	0C74
		BTSC 	STATUS,0 		//01A6 	1403
		RET		 					//01A7 	0004

		//;sys_init.c: 140: {
		//;sys_init.c: 141: _nop();
		NOP		 					//01A8 	0000
		INCR	74H,1 			//01A9 	09F4
		LJUMP 	1A4H 			//01AA 	39A4
		CLRWDT	 			//01AB 	0001
		ORG		01ACH
		CLRR 	INDF 			//01AC 	0100
		INCR	FSR,1 			//01AD 	0984
		XORWR 	FSR,0 			//01AE 	0404
		BTSC 	STATUS,2 		//01AF 	1503
		RETW 	0H 			//01B0 	2100
		XORWR 	FSR,0 			//01B1 	0404
		LJUMP 	1ACH 			//01B2 	39AC

		//;TEST_61F022_ADC.C: 33: ADCON1 = 0B01100000;
		LDWI 	60H 			//01B3 	2A60
		ORG		01B4H
		BSR 	STATUS,5 		//01B4 	1A83
		STR 	1FH 			//01B5 	019F

		//;TEST_61F022_ADC.C: 60: ADCON0 = 0B10111100;
		LDWI 	BCH 			//01B6 	2ABC
		BCR 	STATUS,5 		//01B7 	1283
		STR 	1FH 			//01B8 	019F
		RET		 					//01B9 	0004
			END
