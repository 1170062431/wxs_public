opt subtitle "HI-TECH Software Omniscient Code Generator (PRO mode) build 10920"

opt pagewidth 120

	opt pm

	processor	16F684
clrc	macro
	bcf	3,0
	endm
clrz	macro
	bcf	3,2
	endm
setc	macro
	bsf	3,0
	endm
setz	macro
	bsf	3,2
	endm
skipc	macro
	btfss	3,0
	endm
skipz	macro
	btfss	3,2
	endm
skipnc	macro
	btfsc	3,0
	endm
skipnz	macro
	btfsc	3,2
	endm
indf	equ	0
indf0	equ	0
pc	equ	2
pcl	equ	2
status	equ	3
fsr	equ	4
fsr0	equ	4
c	equ	1
z	equ	0
pclath	equ	10
	FNCALL	_main,_sys_init
	FNROOT	_main
	FNCALL	intlevel1,_ISR
	global	intlevel1
	FNROOT	intlevel1
	global	_UART_RX_buff
	global	_TX_data
	global	_TX_data1
	global	_TX_highTime
	global	_TX_lowTime
	global	_F_RX
	global	_RX_EN
	global	_RX_data
	global	_RX_dataBit
	global	_RX_dataNum
	global	_TX_dataBit
	global	_Time_FLAG
	global	_FSR
psect	text44,local,class=CODE,delta=2
global __ptext44
__ptext44:
_FSR	set	4
	DABS	1,4,1	;_FSR

	global	_INDF
_INDF	set	0
	DABS	1,0,1	;_INDF

	global	_PCL
_PCL	set	2
	DABS	1,2,1	;_PCL

	global	_PCLATH
_PCLATH	set	10
	DABS	1,10,1	;_PCLATH

	global	_PORTA
_PORTA	set	5
	DABS	1,5,1	;_PORTA

	global	_SFR06
_SFR06	set	6
	DABS	1,6,1	;_SFR06

	global	_SFR07
_SFR07	set	7
	DABS	1,7,1	;_SFR07

	global	_SFR08
_SFR08	set	8
	DABS	1,8,1	;_SFR08

	global	_SFR09
_SFR09	set	9
	DABS	1,9,1	;_SFR09

	global	_STATUS
_STATUS	set	3
	DABS	1,3,1	;_STATUS

	global	_TMR0
_TMR0	set	1
	DABS	1,1,1	;_TMR0

	global	_CCPR1
_CCPR1	set	19
	DABS	1,19,2	;_CCPR1

	global	_TMR1
_TMR1	set	14
	DABS	1,14,2	;_TMR1

	global	_ADCON0
_ADCON0	set	31
	DABS	1,31,1	;_ADCON0

	global	_ADRESH
_ADRESH	set	30
	DABS	1,30,1	;_ADRESH

	global	_CCP1CON
_CCP1CON	set	21
	DABS	1,21,1	;_CCP1CON

	global	_CCPR1H
_CCPR1H	set	20
	DABS	1,20,1	;_CCPR1H

	global	_CCPR1L
_CCPR1L	set	19
	DABS	1,19,1	;_CCPR1L

	global	_CMCON0
_CMCON0	set	25
	DABS	1,25,1	;_CMCON0

	global	_CMCON1
_CMCON1	set	26
	DABS	1,26,1	;_CMCON1

	global	_ECCPAS
_ECCPAS	set	23
	DABS	1,23,1	;_ECCPAS

	global	_INTCONbits
_INTCONbits	set	11
	DABS	1,11,1	;_INTCONbits

	global	_MSCKCONbits
_MSCKCONbits	set	27
	DABS	1,27,1	;_MSCKCONbits

	global	_PCLATHbits
_PCLATHbits	set	10
	DABS	1,10,1	;_PCLATHbits

	global	_PIR1bits
_PIR1bits	set	12
	DABS	1,12,1	;_PIR1bits

	global	_PORTAbits
_PORTAbits	set	5
	DABS	1,5,1	;_PORTAbits

	global	_PORTC
_PORTC	set	7
	DABS	1,7,1	;_PORTC

	global	_PWM1CON
_PWM1CON	set	22
	DABS	1,22,1	;_PWM1CON

	global	_SFR00
_SFR00	set	0
	DABS	1,0,1	;_SFR00

	global	_SFR01
_SFR01	set	1
	DABS	1,1,1	;_SFR01

	global	_SFR02
_SFR02	set	2
	DABS	1,2,1	;_SFR02

	global	_SFR03
_SFR03	set	3
	DABS	1,3,1	;_SFR03

	global	_SFR04
_SFR04	set	4
	DABS	1,4,1	;_SFR04

	global	_SFR05
_SFR05	set	5
	DABS	1,5,1	;_SFR05

	global	_SFR0A
_SFR0A	set	10
	DABS	1,10,1	;_SFR0A

	global	_SFR0B
_SFR0B	set	11
	DABS	1,11,1	;_SFR0B

	global	_SFR0C
_SFR0C	set	12
	DABS	1,12,1	;_SFR0C

	global	_SFR11
_SFR11	set	17
	DABS	1,17,1	;_SFR11

	global	_SFR12
_SFR12	set	18
	DABS	1,18,1	;_SFR12

	global	_SFR18
_SFR18	set	24
	DABS	1,24,1	;_SFR18

	global	_SFR1B
_SFR1B	set	27
	DABS	1,27,1	;_SFR1B

	global	_SFR1C
_SFR1C	set	28
	DABS	1,28,1	;_SFR1C

	global	_SFR1D
_SFR1D	set	29
	DABS	1,29,1	;_SFR1D

	global	_SOSCPRHbits
_SOSCPRHbits	set	29
	DABS	1,29,1	;_SOSCPRHbits

	global	_STATUSbits
_STATUSbits	set	3
	DABS	1,3,1	;_STATUSbits

	global	_T1CON
_T1CON	set	16
	DABS	1,16,1	;_T1CON

	global	_T2CONbits
_T2CONbits	set	18
	DABS	1,18,1	;_T2CONbits

	global	_TMR1H
_TMR1H	set	15
	DABS	1,15,1	;_TMR1H

	global	_TMR1L
_TMR1L	set	14
	DABS	1,14,1	;_TMR1L

	global	_WDTCONbits
_WDTCONbits	set	24
	DABS	1,24,1	;_WDTCONbits

	global	_ADFM
_ADFM	set	255
	DABS	1,31,1	;_ADFM

	global	_ADIF
_ADIF	set	102
	DABS	1,12,1	;_ADIF

	global	_ADON
_ADON	set	248
	DABS	1,31,1	;_ADON

	global	_C
_C	set	24
	DABS	1,3,1	;_C

	global	_C1IF
_C1IF	set	99
	DABS	1,12,1	;_C1IF

	global	_C1INV
_C1INV	set	204
	DABS	1,25,1	;_C1INV

	global	_C1OUT
_C1OUT	set	206
	DABS	1,25,1	;_C1OUT

	global	_C2IF
_C2IF	set	100
	DABS	1,12,1	;_C2IF

	global	_C2INV
_C2INV	set	205
	DABS	1,25,1	;_C2INV

	global	_C2OUT
_C2OUT	set	207
	DABS	1,25,1	;_C2OUT

	global	_C2SYNC
_C2SYNC	set	208
	DABS	1,26,1	;_C2SYNC

	global	_CARRY
_CARRY	set	24
	DABS	1,3,1	;_CARRY

	global	_CCP1IF
_CCP1IF	set	101
	DABS	1,12,1	;_CCP1IF

	global	_CCP1M0
_CCP1M0	set	168
	DABS	1,21,1	;_CCP1M0

	global	_CCP1M1
_CCP1M1	set	169
	DABS	1,21,1	;_CCP1M1

	global	_CCP1M2
_CCP1M2	set	170
	DABS	1,21,1	;_CCP1M2

	global	_CCP1M3
_CCP1M3	set	171
	DABS	1,21,1	;_CCP1M3

	global	_CHS0
_CHS0	set	250
	DABS	1,31,1	;_CHS0

	global	_CHS1
_CHS1	set	251
	DABS	1,31,1	;_CHS1

	global	_CHS2
_CHS2	set	252
	DABS	1,31,1	;_CHS2

	global	_CIS
_CIS	set	203
	DABS	1,25,1	;_CIS

	global	_CKCNTI
_CKCNTI	set	217
	DABS	1,27,1	;_CKCNTI

	global	_CKMAVG
_CKMAVG	set	218
	DABS	1,27,1	;_CKMAVG

	global	_CKMEAIF
_CKMEAIF	set	102
	DABS	1,12,1	;_CKMEAIF

	global	_CM0
_CM0	set	200
	DABS	1,25,1	;_CM0

	global	_CM1
_CM1	set	201
	DABS	1,25,1	;_CM1

	global	_CM2
_CM2	set	202
	DABS	1,25,1	;_CM2

	global	_DC
_DC	set	25
	DABS	1,3,1	;_DC

	global	_DC1B0
_DC1B0	set	172
	DABS	1,21,1	;_DC1B0

	global	_DC1B1
_DC1B1	set	173
	DABS	1,21,1	;_DC1B1

	global	_ECCPAS0
_ECCPAS0	set	188
	DABS	1,23,1	;_ECCPAS0

	global	_ECCPAS1
_ECCPAS1	set	189
	DABS	1,23,1	;_ECCPAS1

	global	_ECCPAS2
_ECCPAS2	set	190
	DABS	1,23,1	;_ECCPAS2

	global	_ECCPASE
_ECCPASE	set	191
	DABS	1,23,1	;_ECCPASE

	global	_ECCPIF
_ECCPIF	set	101
	DABS	1,12,1	;_ECCPIF

	global	_EEIF
_EEIF	set	103
	DABS	1,12,1	;_EEIF

	global	_GIE
_GIE	set	95
	DABS	1,11,1	;_GIE

	global	_GO
_GO	set	249
	DABS	1,31,1	;_GO

	global	_GO_DONE
_GO_DONE	set	249
	DABS	1,31,1	;_GO_DONE

	global	_GO_nDONE
_GO_nDONE	set	249
	DABS	1,31,1	;_GO_nDONE

	global	_HC
_HC	set	25
	DABS	1,3,1	;_HC

	global	_INTE
_INTE	set	92
	DABS	1,11,1	;_INTE

	global	_INTF
_INTF	set	89
	DABS	1,11,1	;_INTF

	global	_IRP
_IRP	set	31
	DABS	1,3,1	;_IRP

	global	_OSFIF
_OSFIF	set	98
	DABS	1,12,1	;_OSFIF

	global	_P1M0
_P1M0	set	174
	DABS	1,21,1	;_P1M0

	global	_P1M1
_P1M1	set	175
	DABS	1,21,1	;_P1M1

	global	_PA0
_PA0	set	40
	DABS	1,5,1	;_PA0

	global	_PA1
_PA1	set	41
	DABS	1,5,1	;_PA1

	global	_PA2
_PA2	set	42
	DABS	1,5,1	;_PA2

	global	_PA3
_PA3	set	43
	DABS	1,5,1	;_PA3

	global	_PA4
_PA4	set	44
	DABS	1,5,1	;_PA4

	global	_PA5
_PA5	set	45
	DABS	1,5,1	;_PA5

	global	_PAGE
_PAGE	set	29
	DABS	1,3,1	;_PAGE

	global	_PAIE
_PAIE	set	91
	DABS	1,11,1	;_PAIE

	global	_PAIF
_PAIF	set	88
	DABS	1,11,1	;_PAIF

	global	_PDC0
_PDC0	set	176
	DABS	1,22,1	;_PDC0

	global	_PDC1
_PDC1	set	177
	DABS	1,22,1	;_PDC1

	global	_PDC2
_PDC2	set	178
	DABS	1,22,1	;_PDC2

	global	_PDC3
_PDC3	set	179
	DABS	1,22,1	;_PDC3

	global	_PDC4
_PDC4	set	180
	DABS	1,22,1	;_PDC4

	global	_PDC5
_PDC5	set	181
	DABS	1,22,1	;_PDC5

	global	_PDC6
_PDC6	set	182
	DABS	1,22,1	;_PDC6

	global	_PEIE
_PEIE	set	94
	DABS	1,11,1	;_PEIE

	global	_PRSEN
_PRSEN	set	183
	DABS	1,22,1	;_PRSEN

	global	_PSSAC0
_PSSAC0	set	186
	DABS	1,23,1	;_PSSAC0

	global	_PSSAC1
_PSSAC1	set	187
	DABS	1,23,1	;_PSSAC1

	global	_PSSBD0
_PSSBD0	set	184
	DABS	1,23,1	;_PSSBD0

	global	_PSSBD1
_PSSBD1	set	185
	DABS	1,23,1	;_PSSBD1

	global	_RA0
_RA0	set	40
	DABS	1,5,1	;_RA0

	global	_RA1
_RA1	set	41
	DABS	1,5,1	;_RA1

	global	_RA2
_RA2	set	42
	DABS	1,5,1	;_RA2

	global	_RA3
_RA3	set	43
	DABS	1,5,1	;_RA3

	global	_RA4
_RA4	set	44
	DABS	1,5,1	;_RA4

	global	_RA5
_RA5	set	45
	DABS	1,5,1	;_RA5

	global	_RAIE
_RAIE	set	91
	DABS	1,11,1	;_RAIE

	global	_RAIF
_RAIF	set	88
	DABS	1,11,1	;_RAIF

	global	_RC0
_RC0	set	56
	DABS	1,7,1	;_RC0

	global	_RC1
_RC1	set	57
	DABS	1,7,1	;_RC1

	global	_RC2
_RC2	set	58
	DABS	1,7,1	;_RC2

	global	_RC3
_RC3	set	59
	DABS	1,7,1	;_RC3

	global	_RC4
_RC4	set	60
	DABS	1,7,1	;_RC4

	global	_RC5
_RC5	set	61
	DABS	1,7,1	;_RC5

	global	_RP
_RP	set	29
	DABS	1,3,1	;_RP

	global	_RP0
_RP0	set	29
	DABS	1,3,1	;_RP0

	global	_RP1
_RP1	set	30
	DABS	1,3,1	;_RP1

	global	_SLVREN
_SLVREN	set	220
	DABS	1,27,1	;_SLVREN

	global	_SWDTEN
_SWDTEN	set	192
	DABS	1,24,1	;_SWDTEN

	global	_T0IE
_T0IE	set	93
	DABS	1,11,1	;_T0IE

	global	_T0IF
_T0IF	set	90
	DABS	1,11,1	;_T0IF

	global	_T1CKPS0
_T1CKPS0	set	132
	DABS	1,16,1	;_T1CKPS0

	global	_T1CKPS1
_T1CKPS1	set	133
	DABS	1,16,1	;_T1CKPS1

	global	_T1GINV
_T1GINV	set	135
	DABS	1,16,1	;_T1GINV

	global	_T1GSS
_T1GSS	set	209
	DABS	1,26,1	;_T1GSS

	global	_T1IF
_T1IF	set	96
	DABS	1,12,1	;_T1IF

	global	_T1OSCEN
_T1OSCEN	set	131
	DABS	1,16,1	;_T1OSCEN

	global	_T2CKPS0
_T2CKPS0	set	144
	DABS	1,18,1	;_T2CKPS0

	global	_T2CKPS1
_T2CKPS1	set	145
	DABS	1,18,1	;_T2CKPS1

	global	_T2IF
_T2IF	set	97
	DABS	1,12,1	;_T2IF

	global	_TMR0IE
_TMR0IE	set	93
	DABS	1,11,1	;_TMR0IE

	global	_TMR0IF
_TMR0IF	set	90
	DABS	1,11,1	;_TMR0IF

	global	_TMR1CS
_TMR1CS	set	129
	DABS	1,16,1	;_TMR1CS

	global	_TMR1GE
_TMR1GE	set	134
	DABS	1,16,1	;_TMR1GE

	global	_TMR1IF
_TMR1IF	set	96
	DABS	1,12,1	;_TMR1IF

	global	_TMR1ON
_TMR1ON	set	128
	DABS	1,16,1	;_TMR1ON

	global	_TMR2IF
_TMR2IF	set	97
	DABS	1,12,1	;_TMR2IF

	global	_TMR2ON
_TMR2ON	set	146
	DABS	1,18,1	;_TMR2ON

	global	_TOUTPS0
_TOUTPS0	set	147
	DABS	1,18,1	;_TOUTPS0

	global	_TOUTPS1
_TOUTPS1	set	148
	DABS	1,18,1	;_TOUTPS1

	global	_TOUTPS2
_TOUTPS2	set	149
	DABS	1,18,1	;_TOUTPS2

	global	_TOUTPS3
_TOUTPS3	set	150
	DABS	1,18,1	;_TOUTPS3

	global	_VCFG
_VCFG	set	254
	DABS	1,31,1	;_VCFG

	global	_WDTPS0
_WDTPS0	set	193
	DABS	1,24,1	;_WDTPS0

	global	_WDTPS1
_WDTPS1	set	194
	DABS	1,24,1	;_WDTPS1

	global	_WDTPS2
_WDTPS2	set	195
	DABS	1,24,1	;_WDTPS2

	global	_WDTPS3
_WDTPS3	set	196
	DABS	1,24,1	;_WDTPS3

	global	_Z
_Z	set	26
	DABS	1,3,1	;_Z

	global	_ZERO
_ZERO	set	26
	DABS	1,3,1	;_ZERO

	global	_nDONE
_nDONE	set	249
	DABS	1,31,1	;_nDONE

	global	_nPD
_nPD	set	27
	DABS	1,3,1	;_nPD

	global	_nPF
_nPF	set	27
	DABS	1,3,1	;_nPF

	global	_nT1SYNC
_nT1SYNC	set	130
	DABS	1,16,1	;_nT1SYNC

	global	_nTF
_nTF	set	28
	DABS	1,3,1	;_nTF

	global	_nTO
_nTO	set	28
	DABS	1,3,1	;_nTO

	global	_RX_highTime
psect	nvCOMMON,class=COMMON,space=1
global __pnvCOMMON
__pnvCOMMON:
_RX_highTime:
       ds      2

	global	_OPTION
_OPTION	set	129
	DABS	1,129,1	;_OPTION

	global	_SFR80
_SFR80	set	128
	DABS	1,128,1	;_SFR80

	global	_ADCON1
_ADCON1	set	159
	DABS	1,159,1	;_ADCON1

	global	_ADRESL
_ADRESL	set	158
	DABS	1,158,1	;_ADRESL

	global	_ANSEL
_ANSEL	set	145
	DABS	1,145,1	;_ANSEL

	global	_EECON1bits
_EECON1bits	set	156
	DABS	1,156,1	;_EECON1bits

	global	_EECON2bits
_EECON2bits	set	157
	DABS	1,157,1	;_EECON2bits

	global	_EEDATA
_EEDATA	set	154
	DABS	1,154,1	;_EEDATA

	global	_IOC
_IOC	set	150
	DABS	1,150,1	;_IOC

	global	_IOCAbits
_IOCAbits	set	150
	DABS	1,150,1	;_IOCAbits

	global	_OPTION_REG
_OPTION_REG	set	129
	DABS	1,129,1	;_OPTION_REG

	global	_OPTIONbits
_OPTIONbits	set	129
	DABS	1,129,1	;_OPTIONbits

	global	_OSCCONbits
_OSCCONbits	set	143
	DABS	1,143,1	;_OSCCONbits

	global	_OSCTUNE
_OSCTUNE	set	144
	DABS	1,144,1	;_OSCTUNE

	global	_PCONbits
_PCONbits	set	142
	DABS	1,142,1	;_PCONbits

	global	_PIE1bits
_PIE1bits	set	140
	DABS	1,140,1	;_PIE1bits

	global	_SFR81
_SFR81	set	129
	DABS	1,129,1	;_SFR81

	global	_SFR85
_SFR85	set	133
	DABS	1,133,1	;_SFR85

	global	_SFR8C
_SFR8C	set	140
	DABS	1,140,1	;_SFR8C

	global	_SFR8E
_SFR8E	set	142
	DABS	1,142,1	;_SFR8E

	global	_SFR8F
_SFR8F	set	143
	DABS	1,143,1	;_SFR8F

	global	_SFR92
_SFR92	set	146
	DABS	1,146,1	;_SFR92

	global	_SFR95
_SFR95	set	149
	DABS	1,149,1	;_SFR95

	global	_SFR96
_SFR96	set	150
	DABS	1,150,1	;_SFR96

	global	_SFR9A
_SFR9A	set	154
	DABS	1,154,1	;_SFR9A

	global	_SFR9B
_SFR9B	set	155
	DABS	1,155,1	;_SFR9B

	global	_SFR9C
_SFR9C	set	156
	DABS	1,156,1	;_SFR9C

	global	_SFR9D
_SFR9D	set	157
	DABS	1,157,1	;_SFR9D

	global	_TRISAbits
_TRISAbits	set	133
	DABS	1,133,1	;_TRISAbits

	global	_TRISC
_TRISC	set	135
	DABS	1,135,1	;_TRISC

	global	_VRCON
_VRCON	set	153
	DABS	1,153,1	;_VRCON

	global	_WPU
_WPU	set	149
	DABS	1,149,1	;_WPU

	global	_WPUAbits
_WPUAbits	set	149
	DABS	1,149,1	;_WPUAbits

	global	_ADCS0
_ADCS0	set	1276
	DABS	1,159,1	;_ADCS0

	global	_ADCS1
_ADCS1	set	1277
	DABS	1,159,1	;_ADCS1

	global	_ADCS2
_ADCS2	set	1278
	DABS	1,159,1	;_ADCS2

	global	_ADIE
_ADIE	set	1126
	DABS	1,140,1	;_ADIE

	global	_ANS0
_ANS0	set	1160
	DABS	1,145,1	;_ANS0

	global	_ANS1
_ANS1	set	1161
	DABS	1,145,1	;_ANS1

	global	_ANS2
_ANS2	set	1162
	DABS	1,145,1	;_ANS2

	global	_ANS3
_ANS3	set	1163
	DABS	1,145,1	;_ANS3

	global	_ANS4
_ANS4	set	1164
	DABS	1,145,1	;_ANS4

	global	_ANS5
_ANS5	set	1165
	DABS	1,145,1	;_ANS5

	global	_ANS6
_ANS6	set	1166
	DABS	1,145,1	;_ANS6

	global	_ANS7
_ANS7	set	1167
	DABS	1,145,1	;_ANS7

	global	_C1IE
_C1IE	set	1123
	DABS	1,140,1	;_C1IE

	global	_C2IE
_C2IE	set	1124
	DABS	1,140,1	;_C2IE

	global	_CCP1IE
_CCP1IE	set	1125
	DABS	1,140,1	;_CCP1IE

	global	_CKMEAIE
_CKMEAIE	set	1126
	DABS	1,140,1	;_CKMEAIE

	global	_ECCPIE
_ECCPIE	set	1125
	DABS	1,140,1	;_ECCPIE

	global	_EEIE
_EEIE	set	1127
	DABS	1,140,1	;_EEIE

	global	_HFIOFR
_HFIOFR	set	1146
	DABS	1,143,1	;_HFIOFR

	global	_HTS
_HTS	set	1146
	DABS	1,143,1	;_HTS

	global	_INTEDG
_INTEDG	set	1038
	DABS	1,129,1	;_INTEDG

	global	_IOC0
_IOC0	set	1200
	DABS	1,150,1	;_IOC0

	global	_IOC1
_IOC1	set	1201
	DABS	1,150,1	;_IOC1

	global	_IOC2
_IOC2	set	1202
	DABS	1,150,1	;_IOC2

	global	_IOC3
_IOC3	set	1203
	DABS	1,150,1	;_IOC3

	global	_IOC4
_IOC4	set	1204
	DABS	1,150,1	;_IOC4

	global	_IOC5
_IOC5	set	1205
	DABS	1,150,1	;_IOC5

	global	_IOCA0
_IOCA0	set	1200
	DABS	1,150,1	;_IOCA0

	global	_IOCA1
_IOCA1	set	1201
	DABS	1,150,1	;_IOCA1

	global	_IOCA2
_IOCA2	set	1202
	DABS	1,150,1	;_IOCA2

	global	_IOCA3
_IOCA3	set	1203
	DABS	1,150,1	;_IOCA3

	global	_IOCA4
_IOCA4	set	1204
	DABS	1,150,1	;_IOCA4

	global	_IOCA5
_IOCA5	set	1205
	DABS	1,150,1	;_IOCA5

	global	_IRCF0
_IRCF0	set	1148
	DABS	1,143,1	;_IRCF0

	global	_IRCF1
_IRCF1	set	1149
	DABS	1,143,1	;_IRCF1

	global	_IRCF2
_IRCF2	set	1150
	DABS	1,143,1	;_IRCF2

	global	_LFIOFR
_LFIOFR	set	1145
	DABS	1,143,1	;_LFIOFR

	global	_LFMOD
_LFMOD	set	1151
	DABS	1,143,1	;_LFMOD

	global	_LTS
_LTS	set	1145
	DABS	1,143,1	;_LTS

	global	_OSFIE
_OSFIE	set	1122
	DABS	1,140,1	;_OSFIE

	global	_OSTS
_OSTS	set	1147
	DABS	1,143,1	;_OSTS

	global	_PS0
_PS0	set	1032
	DABS	1,129,1	;_PS0

	global	_PS1
_PS1	set	1033
	DABS	1,129,1	;_PS1

	global	_PS2
_PS2	set	1034
	DABS	1,129,1	;_PS2

	global	_PSA
_PSA	set	1035
	DABS	1,129,1	;_PSA

	global	_RD
_RD	set	1248
	DABS	1,156,1	;_RD

	global	_SBODEN
_SBODEN	set	1140
	DABS	1,142,1	;_SBODEN

	global	_SBOREN
_SBOREN	set	1140
	DABS	1,142,1	;_SBOREN

	global	_SCS
_SCS	set	1144
	DABS	1,143,1	;_SCS

	global	_T0CS
_T0CS	set	1037
	DABS	1,129,1	;_T0CS

	global	_T0SE
_T0SE	set	1036
	DABS	1,129,1	;_T0SE

	global	_T1IE
_T1IE	set	1120
	DABS	1,140,1	;_T1IE

	global	_T2IE
_T2IE	set	1121
	DABS	1,140,1	;_T2IE

	global	_TMR1IE
_TMR1IE	set	1120
	DABS	1,140,1	;_TMR1IE

	global	_TMR2IE
_TMR2IE	set	1121
	DABS	1,140,1	;_TMR2IE

	global	_TRISA0
_TRISA0	set	1064
	DABS	1,133,1	;_TRISA0

	global	_TRISA1
_TRISA1	set	1065
	DABS	1,133,1	;_TRISA1

	global	_TRISA2
_TRISA2	set	1066
	DABS	1,133,1	;_TRISA2

	global	_TRISA3
_TRISA3	set	1067
	DABS	1,133,1	;_TRISA3

	global	_TRISA4
_TRISA4	set	1068
	DABS	1,133,1	;_TRISA4

	global	_TRISA5
_TRISA5	set	1069
	DABS	1,133,1	;_TRISA5

	global	_TRISC0
_TRISC0	set	1080
	DABS	1,135,1	;_TRISC0

	global	_TRISC1
_TRISC1	set	1081
	DABS	1,135,1	;_TRISC1

	global	_TRISC2
_TRISC2	set	1082
	DABS	1,135,1	;_TRISC2

	global	_TRISC3
_TRISC3	set	1083
	DABS	1,135,1	;_TRISC3

	global	_TRISC4
_TRISC4	set	1084
	DABS	1,135,1	;_TRISC4

	global	_TRISC5
_TRISC5	set	1085
	DABS	1,135,1	;_TRISC5

	global	_TUN0
_TUN0	set	1152
	DABS	1,144,1	;_TUN0

	global	_TUN1
_TUN1	set	1153
	DABS	1,144,1	;_TUN1

	global	_TUN2
_TUN2	set	1154
	DABS	1,144,1	;_TUN2

	global	_TUN3
_TUN3	set	1155
	DABS	1,144,1	;_TUN3

	global	_TUN4
_TUN4	set	1156
	DABS	1,144,1	;_TUN4

	global	_ULPWUE
_ULPWUE	set	1141
	DABS	1,142,1	;_ULPWUE

	global	_VR0
_VR0	set	1224
	DABS	1,153,1	;_VR0

	global	_VR1
_VR1	set	1225
	DABS	1,153,1	;_VR1

	global	_VR2
_VR2	set	1226
	DABS	1,153,1	;_VR2

	global	_VR3
_VR3	set	1227
	DABS	1,153,1	;_VR3

	global	_VREN
_VREN	set	1231
	DABS	1,153,1	;_VREN

	global	_VRR
_VRR	set	1229
	DABS	1,153,1	;_VRR

	global	_WPU0
_WPU0	set	1192
	DABS	1,149,1	;_WPU0

	global	_WPU1
_WPU1	set	1193
	DABS	1,149,1	;_WPU1

	global	_WPU2
_WPU2	set	1194
	DABS	1,149,1	;_WPU2

	global	_WPU4
_WPU4	set	1196
	DABS	1,149,1	;_WPU4

	global	_WPU5
_WPU5	set	1197
	DABS	1,149,1	;_WPU5

	global	_WPUA0
_WPUA0	set	1192
	DABS	1,149,1	;_WPUA0

	global	_WPUA1
_WPUA1	set	1193
	DABS	1,149,1	;_WPUA1

	global	_WPUA2
_WPUA2	set	1194
	DABS	1,149,1	;_WPUA2

	global	_WPUA4
_WPUA4	set	1196
	DABS	1,149,1	;_WPUA4

	global	_WPUA5
_WPUA5	set	1197
	DABS	1,149,1	;_WPUA5

	global	_WR
_WR	set	1256
	DABS	1,157,1	;_WR

	global	_WREN
_WREN	set	1250
	DABS	1,156,1	;_WREN

	global	_WREN1
_WREN1	set	1250
	DABS	1,156,1	;_WREN1

	global	_WREN2
_WREN2	set	1252
	DABS	1,156,1	;_WREN2

	global	_WREN3
_WREN3	set	1253
	DABS	1,156,1	;_WREN3

	global	_WRERR
_WRERR	set	1251
	DABS	1,156,1	;_WRERR

	global	_nBOD
_nBOD	set	1136
	DABS	1,142,1	;_nBOD

	global	_nBOR
_nBOR	set	1136
	DABS	1,142,1	;_nBOR

	global	_nPAPU
_nPAPU	set	1039
	DABS	1,129,1	;_nPAPU

	global	_nPOR
_nPOR	set	1137
	DABS	1,142,1	;_nPOR

	global	_nRAPU
_nRAPU	set	1039
	DABS	1,129,1	;_nRAPU

	global	_INTCON
_INTCON	set	11
	DABS	1,11,1	;_INTCON

	global	_PIR1
_PIR1	set	12
	DABS	1,12,1	;_PIR1

	global	_SFR0D
_SFR0D	set	13
	DABS	1,13,1	;_SFR0D

	global	_SFR0E
_SFR0E	set	14
	DABS	1,14,1	;_SFR0E

	global	_SFR0F
_SFR0F	set	15
	DABS	1,15,1	;_SFR0F

	global	_SFR10
_SFR10	set	16
	DABS	1,16,1	;_SFR10

	global	_TMR2
_TMR2	set	17
	DABS	1,17,1	;_TMR2

	global	_SFR13
_SFR13	set	19
	DABS	1,19,1	;_SFR13

	global	_SFR14
_SFR14	set	20
	DABS	1,20,1	;_SFR14

	global	_SFR15
_SFR15	set	21
	DABS	1,21,1	;_SFR15

	global	_SFR16
_SFR16	set	22
	DABS	1,22,1	;_SFR16

	global	_SFR17
_SFR17	set	23
	DABS	1,23,1	;_SFR17

	global	_T2CON
_T2CON	set	18
	DABS	1,18,1	;_T2CON

	global	_WDTCON
_WDTCON	set	24
	DABS	1,24,1	;_WDTCON

	global	_MSCKCON
_MSCKCON	set	27
	DABS	1,27,1	;_MSCKCON

	global	_SFR19
_SFR19	set	25
	DABS	1,25,1	;_SFR19

	global	_SFR1A
_SFR1A	set	26
	DABS	1,26,1	;_SFR1A

	global	_SFR1E
_SFR1E	set	30
	DABS	1,30,1	;_SFR1E

	global	_SFR1F
_SFR1F	set	31
	DABS	1,31,1	;_SFR1F

	global	_SOSCPRH
_SOSCPRH	set	29
	DABS	1,29,1	;_SOSCPRH

	global	_SOSCPRL
_SOSCPRL	set	28
	DABS	1,28,1	;_SOSCPRL

	global	_SFR82
_SFR82	set	130
	DABS	1,130,1	;_SFR82

	global	_SFR83
_SFR83	set	131
	DABS	1,131,1	;_SFR83

	global	_SFR84
_SFR84	set	132
	DABS	1,132,1	;_SFR84

	global	_TRISA
_TRISA	set	133
	DABS	1,133,1	;_TRISA

	global	_PIE1
_PIE1	set	140
	DABS	1,140,1	;_PIE1

	global	_SFR86
_SFR86	set	134
	DABS	1,134,1	;_SFR86

	global	_SFR87
_SFR87	set	135
	DABS	1,135,1	;_SFR87

	global	_SFR88
_SFR88	set	136
	DABS	1,136,1	;_SFR88

	global	_SFR89
_SFR89	set	137
	DABS	1,137,1	;_SFR89

	global	_SFR8A
_SFR8A	set	138
	DABS	1,138,1	;_SFR8A

	global	_SFR8B
_SFR8B	set	139
	DABS	1,139,1	;_SFR8B

	global	_PCON
_PCON	set	142
	DABS	1,142,1	;_PCON

	global	_SFR8D
_SFR8D	set	141
	DABS	1,141,1	;_SFR8D

	global	_OSCCON
_OSCCON	set	143
	DABS	1,143,1	;_OSCCON

	global	_PR2
_PR2	set	146
	DABS	1,146,1	;_PR2

	global	_SFR90
_SFR90	set	144
	DABS	1,144,1	;_SFR90

	global	_SFR91
_SFR91	set	145
	DABS	1,145,1	;_SFR91

	global	_SFR93
_SFR93	set	147
	DABS	1,147,1	;_SFR93

	global	_SFR94
_SFR94	set	148
	DABS	1,148,1	;_SFR94

	global	_WPUA
_WPUA	set	149
	DABS	1,149,1	;_WPUA

	global	_EEDAT
_EEDAT	set	154
	DABS	1,154,1	;_EEDAT

	global	_IOCA
_IOCA	set	150
	DABS	1,150,1	;_IOCA

	global	_SFR97
_SFR97	set	151
	DABS	1,151,1	;_SFR97

	global	_SFR98
_SFR98	set	152
	DABS	1,152,1	;_SFR98

	global	_SFR99
_SFR99	set	153
	DABS	1,153,1	;_SFR99

	global	_EEADR
_EEADR	set	155
	DABS	1,155,1	;_EEADR

	global	_EECON1
_EECON1	set	156
	DABS	1,156,1	;_EECON1

	global	_EECON2
_EECON2	set	157
	DABS	1,157,1	;_EECON2

	global	_SFR9E
_SFR9E	set	158
	DABS	1,158,1	;_SFR9E

	global	_SFR9F
_SFR9F	set	159
	DABS	1,159,1	;_SFR9F

	file	"yy_ir.as"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

psect	bssCOMMON,class=COMMON,space=1
global __pbssCOMMON
__pbssCOMMON:
_UART_RX_buff:
       ds      15

_TX_data:
       ds      4

_TX_data1:
       ds      4

_TX_highTime:
       ds      2

_TX_lowTime:
       ds      2

_F_RX:
       ds      1

_RX_EN:
       ds      1

_RX_data:
       ds      1

_RX_dataBit:
       ds      1

_RX_dataNum:
       ds      1

_TX_dataBit:
       ds      1

_Time_FLAG:
       ds      1

psect clrtext,class=CODE,delta=2
global clear_ram
;	Called with FSR containing the base address, and
;	W with the last address+1
clear_ram:
	clrwdt			;clear the watchdog before getting into this loop
clrloop:
	clrf	indf		;clear RAM location pointed to by FSR
	incf	fsr,f		;increment pointer
	xorwf	fsr,w		;XOR with final address
	btfsc	status,2	;have we reached the end yet?
	retlw	0		;all done for this memory range, return
	xorwf	fsr,w		;XOR again to restore value
	goto	clrloop		;do the next byte

; Clear objects allocated to COMMON
psect cinit,class=CODE,delta=2
	movlw	low(__pbssCOMMON)
	movwf	fsr
	movlw	low((__pbssCOMMON)+022h)
	fcall	clear_ram
psect cinit,class=CODE,delta=2
global end_of_initialization

;End of C runtime variable initialization code

end_of_initialization:
clrf status
ljmp _main	;jump to C main() function
psect	cstackCOMMON,class=COMMON,space=1
global __pcstackCOMMON
__pcstackCOMMON:
	global	?_sys_init
?_sys_init:	; 0 bytes @ 0x0
	global	?_ISR
?_ISR:	; 0 bytes @ 0x0
	global	??_ISR
??_ISR:	; 0 bytes @ 0x0
	global	?_main
?_main:	; 2 bytes @ 0x0
	ds	3
	global	??_sys_init
??_sys_init:	; 0 bytes @ 0x3
	global	??_main
??_main:	; 0 bytes @ 0x3
;;Data sizes: Strings 0, constant 0, data 0, bss 34, persistent 2 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          62      3      39

;;
;; Pointer list with targets:



;;
;; Critical Paths under _main in COMMON
;;
;;   None.
;;
;; Critical Paths under _ISR in COMMON
;;
;;   None.

;;
;;Main: autosize = 0, tempsize = 0, incstack = 0, save=0
;;

;;
;;Call Graph Tables:
;;
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (0) _main                                                 0     0      0       0
;;                           _sys_init
;; ---------------------------------------------------------------------------------
;; (1) _sys_init                                             0     0      0       0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 1
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (2) _ISR                                                  3     3      0       0
;;                                              0 COMMON     3     3      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 2
;; ---------------------------------------------------------------------------------

;; Call Graph Graphs:

;; _main (ROOT)
;;   _sys_init
;;
;; _ISR (ROOT)
;;

;; Address spaces:

;;Name               Size   Autos  Total    Cost      Usage
;;BITCOMMON           3E      0       0       0        0.0%
;;EEDATA             100      0       0       0        0.0%
;;NULL                 0      0       0       0        0.0%
;;CODE                 0      0       0       0        0.0%
;;COMMON              3E      3      27       1       62.9%
;;BITSFR0              0      0       0       1        0.0%
;;SFR0                 0      0       0       1        0.0%
;;BITSFR1              0      0       0       2        0.0%
;;SFR1                 0      0       0       2        0.0%
;;STACK                0      0       1       2        0.0%
;;ABS                  0      0      27       3        0.0%
;;DATA                 0      0      28       4        0.0%

	global	_main
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:

;; *************** function _main *****************
;; Defined at:
;;		line 94 in file "yy_ir.C"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  2  909[COMMON] int 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 20/0
;;		Unchanged: FFE00/0
;; Data sizes:     COMMON
;;      Params:         0
;;      Locals:         0
;;      Temps:          0
;;      Totals:         0
;;Total ram usage:        0 bytes
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_sys_init
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"yy_ir.C"
	line	94
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 6
; Regs used in _main: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	95
	
l1962:	
;yy_ir.C: 95: sys_init();
	fcall	_sys_init
	line	96
	
l1964:	
;yy_ir.C: 96: F_RX = RESET;
	clrf	(_F_RX)
	line	97
	
l1966:	
;yy_ir.C: 97: RX_EN = DISABLE;
	clrf	(_RX_EN)
	line	98
	
l1968:	
;yy_ir.C: 98: (T0IE = 0,T0IF = 0);
	bcf	(93/8),(93)&7
	
l1970:	
	bcf	(90/8),(90)&7
	line	104
	
l1972:	
;yy_ir.C: 100: {
;yy_ir.C: 104: RX_highTime = 0;
	clrf	(_RX_highTime)
	clrf	(_RX_highTime+1)
	line	105
;yy_ir.C: 105: while(RX_highTime<5000)
	goto	l1978
	
l912:	
	line	107
;yy_ir.C: 106: {
;yy_ir.C: 107: if(PA3)
	bcf	status, 5	;RP0=0, select bank0
	btfss	(43/8),(43)&7
	goto	u101
	goto	u100
u101:
	goto	l1972
u100:
	line	108
	
l1974:	
;yy_ir.C: 108: RX_highTime++;
	incf	(_RX_highTime),f
	skipnz
	incf	(_RX_highTime+1),f
	line	105
	
l1978:	
	movlw	high(01388h)
	subwf	(_RX_highTime+1),w
	movlw	low(01388h)
	skipnz
	subwf	(_RX_highTime),w
	skipc
	goto	u111
	goto	u110
u111:
	goto	l912
u110:
	goto	l916
	line	112
	
l917:	
	line	114
# 114 "yy_ir.C"
clrwdt ;#
psect	maintext
	line	115
	
l916:	
	line	112
	bcf	status, 5	;RP0=0, select bank0
	btfsc	(43/8),(43)&7
	goto	u121
	goto	u120
u121:
	goto	l917
u120:
	line	116
	
l1980:	
;yy_ir.C: 115: }
;yy_ir.C: 116: RX_dataNum = 0;
	clrf	(_RX_dataNum)
	line	117
;yy_ir.C: 117: for(RX_dataNum = 0;RX_dataNum < 8;RX_dataNum++)
	clrf	(_RX_dataNum)
	
l1982:	
	movlw	(08h)
	subwf	(_RX_dataNum),w
	skipc
	goto	u131
	goto	u130
u131:
	goto	l921
u130:
	goto	l1998
	line	119
	
l921:	
	btfsc	(43/8),(43)&7
	goto	u141
	goto	u140
u141:
	goto	l921
u140:
	
l923:	
	line	120
;yy_ir.C: 120: RX_EN = ENABLE;
	clrf	(_RX_EN)
	incf	(_RX_EN),f
	line	121
	
l1986:	
;yy_ir.C: 121: RX_dataBit = 8;
	movlw	(08h)
	movwf	(_RX_dataBit)
	line	122
;yy_ir.C: 122: TMR0 = 100;
	movlw	(064h)
	movwf	(1)	;volatile
	line	123
	
l1988:	
;yy_ir.C: 123: (T0IF = 0,T0IE = 1);
	bcf	(90/8),(90)&7
	
l1990:	
	bsf	(93/8),(93)&7
	line	124
;yy_ir.C: 124: while(RX_EN);
	
l1992:	
	movf	(_RX_EN),f
	skipz
	goto	u151
	goto	u150
u151:
	goto	l1992
u150:
	
l926:	
	line	125
;yy_ir.C: 125: (T0IE = 0,T0IF = 0);
	bcf	(93/8),(93)&7
	bcf	(90/8),(90)&7
	line	126
;yy_ir.C: 126: while(!PA3);
	
l927:	
	btfss	(43/8),(43)&7
	goto	u161
	goto	u160
u161:
	goto	l927
u160:
	line	117
	
l1994:	
	incf	(_RX_dataNum),f
	goto	l1982
	line	128
	
l1998:	
;yy_ir.C: 127: }
;yy_ir.C: 128: RX_data = UART_RX_buff[7];
	movf	0+(_UART_RX_buff)+07h,w
	movwf	(_RX_data)
	line	129
;yy_ir.C: 129: switch(RX_data)
	goto	l2034
	line	131
	
l2000:	
	movlw	1<<((42)&7)
	xorwf	((42)/8),f
	goto	l2036
	line	134
	
l2004:	
	movlw	0
	movwf	(_TX_data1+3)
	movlw	0FFh
	movwf	(_TX_data1+2)
	movlw	0A2h
	movwf	(_TX_data1+1)
	movlw	05Dh
	movwf	(_TX_data1)

	
l2006:	
	clrf	(_F_RX)
	incf	(_F_RX),f
	goto	l2036
	line	135
	
l2008:	
	movlw	0
	movwf	(_TX_data1+3)
	movlw	0FFh
	movwf	(_TX_data1+2)
	movlw	0E2h
	movwf	(_TX_data1+1)
	movlw	01Dh
	movwf	(_TX_data1)

	goto	l2006
	line	136
	
l2012:	
	movlw	0
	movwf	(_TX_data1+3)
	movlw	0FFh
	movwf	(_TX_data1+2)
	movlw	038h
	movwf	(_TX_data1+1)
	movlw	0C7h
	movwf	(_TX_data1)

	goto	l2006
	line	140
	
l2024:	
	movlw	0
	movwf	(_TX_data1+3)
	movlw	0FFh
	movwf	(_TX_data1+2)
	movlw	098h
	movwf	(_TX_data1+1)
	movlw	067h
	movwf	(_TX_data1)

	goto	l2006
	line	143
	
l2028:	
	movlw	0
	movwf	(_TX_data1+3)
	movlw	0FFh
	movwf	(_TX_data1+2)
	movlw	02h
	movwf	(_TX_data1+1)
	movlw	0FDh
	movwf	(_TX_data1)

	goto	l2006
	line	129
	
l2034:	
	movf	(_RX_data),w
	; Switch size 1, requested type "space"
; Number of cases is 9, Range of values is 0 to 12
; switch strategies available:
; Name         Instructions Cycles
; direct_byte           19     6 (fixed)
; simple_byte           28    15 (average)
; jumptable            260     6 (fixed)
; rangetable            17     6 (fixed)
; spacedrange           32     9 (fixed)
; locatedrange          13     3 (fixed)
;	Chosen strategy is direct_byte

	movwf fsr
	movlw	13
	subwf	fsr,w
skipnc
goto l2036
movlw high(S2104)
movwf pclath
	movlw low(S2104)
	addwf fsr,w
	movwf pc
psect	swtext1,local,class=CONST,delta=2
global __pswtext1
__pswtext1:
S2104:
	ljmp	l2000
	ljmp	l2000
	ljmp	l2036
	ljmp	l2004
	ljmp	l2008
	ljmp	l2012
	ljmp	l2012
	ljmp	l2004
	ljmp	l2036
	ljmp	l2024
	ljmp	l2036
	ljmp	l2036
	ljmp	l2028
psect	maintext

	line	151
	
l2036:	
;yy_ir.C: 151: if(F_RX)
	movf	(_F_RX),w
	skipz
	goto	u170
	goto	l2062
u170:
	line	153
	
l2038:	
;yy_ir.C: 152: {
;yy_ir.C: 153: TX_dataBit = 32;
	movlw	(020h)
	movwf	(_TX_dataBit)
	line	154
;yy_ir.C: 154: TX_highTime = 692;
	movlw	low(02B4h)
	movwf	(_TX_highTime)
	movlw	high(02B4h)
	movwf	((_TX_highTime))+1
	line	156
;yy_ir.C: 156: TX_lowTime = 346;
	movlw	low(015Ah)
	movwf	(_TX_lowTime)
	movlw	high(015Ah)
	movwf	((_TX_lowTime))+1
	line	157
	
l2040:	
;yy_ir.C: 157: (TMR2ON = 1);
	bsf	(146/8),(146)&7
	line	158
;yy_ir.C: 158: TX_data = TX_data1;
	movf	(_TX_data1+3),w
	movwf	(_TX_data+3)
	movf	(_TX_data1+2),w
	movwf	(_TX_data+2)
	movf	(_TX_data1+1),w
	movwf	(_TX_data+1)
	movf	(_TX_data1),w
	movwf	(_TX_data)

	line	159
;yy_ir.C: 159: while(TX_dataBit)
	goto	l2054
	line	165
	
l2042:	
;yy_ir.C: 160: {
;yy_ir.C: 165: if(!TX_lowTime)
	movf	((_TX_lowTime+1)),w
	iorwf	((_TX_lowTime)),w
	skipz
	goto	u181
	goto	u180
u181:
	goto	l2054
u180:
	line	167
	
l2044:	
;yy_ir.C: 166: {
;yy_ir.C: 167: if(TX_data & 0x80000000)
	btfss	(_TX_data+3),(31)&7
	goto	u191
	goto	u190
u191:
	goto	l2048
u190:
	line	169
	
l2046:	
;yy_ir.C: 168: {
;yy_ir.C: 169: TX_highTime = 43;
	movlw	02Bh
	movwf	(_TX_highTime)
	clrf	(_TX_highTime+1)
	line	170
;yy_ir.C: 170: TX_lowTime = 129;
	movlw	081h
	movwf	(_TX_lowTime)
	clrf	(_TX_lowTime+1)
	line	171
;yy_ir.C: 171: }
	goto	l2050
	line	174
	
l2048:	
;yy_ir.C: 172: else
;yy_ir.C: 173: {
;yy_ir.C: 174: TX_highTime = 43;
	movlw	02Bh
	movwf	(_TX_highTime)
	clrf	(_TX_highTime+1)
	line	175
;yy_ir.C: 175: TX_lowTime = 43;
	movlw	02Bh
	movwf	(_TX_lowTime)
	clrf	(_TX_lowTime+1)
	line	177
	
l2050:	
;yy_ir.C: 176: }
;yy_ir.C: 177: TX_data = TX_data<<1;
	clrc
	rlf	(_TX_data),f
	rlf	(_TX_data+1),f
	rlf	(_TX_data+2),f
	rlf	(_TX_data+3),f
	line	178
	
l2052:	
;yy_ir.C: 178: TX_dataBit--;
	decf	(_TX_dataBit),f
	line	159
	
l2054:	
	movf	(_TX_dataBit),f
	skipz
	goto	u201
	goto	u200
u201:
	goto	l2042
u200:
	line	181
	
l2056:	
	movf	((_TX_lowTime+1)),w
	iorwf	((_TX_lowTime)),w
	skipz
	goto	u211
	goto	u210
u211:
	goto	l2056
u210:
	line	182
	
l2058:	
;yy_ir.C: 182: TX_highTime = 43;
	movlw	02Bh
	movwf	(_TX_highTime)
	clrf	(_TX_highTime+1)
	line	183
;yy_ir.C: 183: while(TX_highTime);
	
l2060:	
	movf	((_TX_highTime+1)),w
	iorwf	((_TX_highTime)),w
	skipz
	goto	u221
	goto	u220
u221:
	goto	l2060
u220:
	
l954:	
	line	184
;yy_ir.C: 184: PA4 = 0;
	bcf	(44/8),(44)&7
	line	185
;yy_ir.C: 185: (TMR2ON = 0);
	bcf	(146/8),(146)&7
	line	188
	
l2062:	
;yy_ir.C: 186: }
;yy_ir.C: 188: F_RX = RESET;
	clrf	(_F_RX)
	goto	l1972
	global	start
	ljmp	start
	opt stack 0
psect	maintext
	line	190
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,90
	global	_sys_init
psect	text45,local,class=CODE,delta=2
global __ptext45
__ptext45:

;; *************** function _sys_init *****************
;; Defined at:
;;		line 8 in file "SYS_INIT.C"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 20/20
;;		Unchanged: FFE00/0
;; Data sizes:     COMMON
;;      Params:         0
;;      Locals:         0
;;      Temps:          0
;;      Totals:         0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text45
	file	"SYS_INIT.C"
	line	8
	global	__size_of_sys_init
	__size_of_sys_init	equ	__end_of_sys_init-_sys_init
	
_sys_init:	
	opt	stack 6
; Regs used in _sys_init: [wreg+status,2+status,0]
	line	9
	
l1882:	
;SYS_INIT.C: 9: OSCCON = (OSCCON &0x8F)|(7<<4);
	bsf	status, 5	;RP0=1, select bank1
	movf	(143)^080h,w
	andlw	08Fh
	iorlw	070h
	movwf	(143)^080h	;volatile
	line	11
	
l1884:	
;SYS_INIT.C: 11: TRISA2 = 0;
	bcf	(1066/8)^080h,(1066)&7
	line	12
	
l1886:	
;SYS_INIT.C: 12: PA2 = 1;
	bcf	status, 5	;RP0=0, select bank0
	bsf	(42/8),(42)&7
	line	14
	
l1888:	
;SYS_INIT.C: 14: TRISA5 = 0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	(1069/8)^080h,(1069)&7
	line	15
	
l1890:	
;SYS_INIT.C: 15: PA5 = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	(45/8),(45)&7
	line	17
	
l1892:	
;SYS_INIT.C: 17: TRISA4 = 0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	(1068/8)^080h,(1068)&7
	line	18
	
l1894:	
;SYS_INIT.C: 18: PA4 = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	(44/8),(44)&7
	line	24
	
l1896:	
# 24 "SYS_INIT.C"
clrwdt ;#
psect	text45
	line	25
;SYS_INIT.C: 25: WDTCON = (WDTCON &0xE1)|(10<<1);
	bcf	status, 5	;RP0=0, select bank0
	movf	(24),w
	andlw	0E1h
	iorlw	014h
	movwf	(24)	;volatile
	line	27
	
l1898:	
;SYS_INIT.C: 27: SWDTEN = DISABLE;
	bcf	(192/8),(192)&7
	line	36
	
l1900:	
;SYS_INIT.C: 36: OPTION = (0B00000000+1);
	movlw	(01h)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(129)^080h	;volatile
	line	39
	
l1902:	
;SYS_INIT.C: 39: TMR0 = 152;
	movlw	(098h)
	bcf	status, 5	;RP0=0, select bank0
	movwf	(1)	;volatile
	line	46
	
l1904:	
;SYS_INIT.C: 46: T2CON &= (0<<3);
	clrf	(18)	;volatile
	line	47
	
l1906:	
;SYS_INIT.C: 47: T2CON &= 1;
	movlw	(01h)
	andwf	(18),f	;volatile
	line	48
	
l1908:	
;SYS_INIT.C: 48: PR2 = 52;
	movlw	(034h)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(146)^080h	;volatile
	line	59
	
l1910:	
;SYS_INIT.C: 59: GIE = ENABLE;
	bsf	(95/8),(95)&7
	line	60
	
l1912:	
;SYS_INIT.C: 60: PEIE = ENABLE;
	bsf	(94/8),(94)&7
	line	61
	
l1914:	
;SYS_INIT.C: 61: T0IF = RESET;
	bcf	(90/8),(90)&7
	line	62
	
l1916:	
;SYS_INIT.C: 62: T0IE = ENABLE;
	bsf	(93/8),(93)&7
	line	63
	
l1918:	
;SYS_INIT.C: 63: TMR2IF = RESET;
	bcf	status, 5	;RP0=0, select bank0
	bcf	(97/8),(97)&7
	line	64
	
l1920:	
;SYS_INIT.C: 64: TMR2IE = ENABLE;
	bsf	status, 5	;RP0=1, select bank1
	bsf	(1121/8)^080h,(1121)&7
	line	66
	
l431:	
	return
	opt stack 0
GLOBAL	__end_of_sys_init
	__end_of_sys_init:
;; =============== function _sys_init ends ============

	signat	_sys_init,88
	global	_ISR
psect	text46,local,class=CODE,delta=2
global __ptext46
__ptext46:

;; *************** function _ISR *****************
;; Defined at:
;;		line 35 in file "yy_ir.C"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: FFFDF/0
;; Data sizes:     COMMON
;;      Params:         0
;;      Locals:         0
;;      Temps:          3
;;      Totals:         3
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		Interrupt level 1
;; This function uses a non-reentrant model
;;
psect	text46
	file	"yy_ir.C"
	line	35
	global	__size_of_ISR
	__size_of_ISR	equ	__end_of_ISR-_ISR
	
_ISR:	
	opt	stack 6
; Regs used in _ISR: [wreg-fsr0h+status,2+status,0]
psect	intentry,class=CODE,delta=2
global __pintentry
__pintentry:
global interrupt_function
interrupt_function:
	global saved_w
	saved_w	set	btemp+0
	movwf	saved_w
	swapf	status,w
	movwf	(??_ISR+0)
	movf	fsr0,w
	movwf	(??_ISR+1)
	movf	pclath,w
	movwf	(??_ISR+2)
	ljmp	_ISR
psect	text46
	line	36
	
i1l1922:	
;yy_ir.C: 36: if(T0IE && T0IF)
	btfss	(93/8),(93)&7
	goto	u1_21
	goto	u1_20
u1_21:
	goto	i1l894
u1_20:
	
i1l1924:	
	btfss	(90/8),(90)&7
	goto	u2_21
	goto	u2_20
u2_21:
	goto	i1l894
u2_20:
	line	40
	
i1l1926:	
;yy_ir.C: 37: {
;yy_ir.C: 38: static u8 T_100us = 0;
;yy_ir.C: 39: static u16 T_1ms = 0;
;yy_ir.C: 40: T0IF = RESET;
	bcf	(90/8),(90)&7
	line	41
	
i1l1928:	
;yy_ir.C: 41: TMR0 = 152;
	movlw	(098h)
	bcf	status, 5	;RP0=0, select bank0
	movwf	(1)	;volatile
	line	54
;yy_ir.C: 54: if(RX_EN)
	movf	(_RX_EN),w
	skipz
	goto	u3_20
	goto	i1l894
u3_20:
	line	56
	
i1l1930:	
;yy_ir.C: 55: {
;yy_ir.C: 56: if(PA3)
	btfss	(43/8),(43)&7
	goto	u4_21
	goto	u4_20
u4_21:
	goto	i1l900
u4_20:
	line	57
	
i1l1932:	
;yy_ir.C: 57: RX_data = (RX_data>>1)|0x80;
	setc
	rrf	(_RX_data),f
	goto	i1l1934
	line	58
	
i1l900:	
	line	59
;yy_ir.C: 58: else
;yy_ir.C: 59: RX_data >>= 1;
	clrc
	rrf	(_RX_data),f
	line	60
	
i1l1934:	
;yy_ir.C: 60: RX_dataBit--;
	decf	(_RX_dataBit),f
	line	61
;yy_ir.C: 61: if(!RX_dataBit)
	movf	(_RX_dataBit),f
	skipz
	goto	u5_21
	goto	u5_20
u5_21:
	goto	i1l903
u5_20:
	line	63
	
i1l1936:	
;yy_ir.C: 62: {
;yy_ir.C: 63: UART_RX_buff[RX_dataNum] = RX_data;
	movf	(_RX_dataNum),w
	addlw	_UART_RX_buff&0ffh
	movwf	fsr0
	movf	(_RX_data),w
	movwf	indf
	line	64
	
i1l1938:	
;yy_ir.C: 64: RX_EN = DISABLE;
	clrf	(_RX_EN)
	goto	i1l903
	line	68
	
i1l894:	
	line	70
;yy_ir.C: 67: }
;yy_ir.C: 68: }
;yy_ir.C: 70: if(TMR2IE && TMR2IF)
	bsf	status, 5	;RP0=1, select bank1
	btfss	(1121/8)^080h,(1121)&7
	goto	u6_21
	goto	u6_20
u6_21:
	goto	i1l903
u6_20:
	
i1l1942:	
	bcf	status, 5	;RP0=0, select bank0
	btfss	(97/8),(97)&7
	goto	u7_21
	goto	u7_20
u7_21:
	goto	i1l903
u7_20:
	line	72
	
i1l1944:	
;yy_ir.C: 71: {
;yy_ir.C: 72: TMR2IF = RESET;
	bcf	(97/8),(97)&7
	line	73
	
i1l1946:	
;yy_ir.C: 73: if(TX_highTime)
	movf	(_TX_highTime+1),w
	iorwf	(_TX_highTime),w
	skipnz
	goto	u8_21
	goto	u8_20
u8_21:
	goto	i1l1954
u8_20:
	line	75
	
i1l1948:	
;yy_ir.C: 74: {
;yy_ir.C: 75: TX_highTime--;
	movlw	low(01h)
	subwf	(_TX_highTime),f
	movlw	high(01h)
	skipc
	decf	(_TX_highTime+1),f
	subwf	(_TX_highTime+1),f
	line	76
;yy_ir.C: 76: PA4 = ~PA4;
	movlw	1<<((44)&7)
	xorwf	((44)/8),f
	goto	i1l903
	line	79
	
i1l1954:	
;yy_ir.C: 79: else if(TX_lowTime)
	movf	(_TX_lowTime+1),w
	iorwf	(_TX_lowTime),w
	skipnz
	goto	u9_21
	goto	u9_20
u9_21:
	goto	i1l903
u9_20:
	line	81
	
i1l1956:	
;yy_ir.C: 80: {
;yy_ir.C: 81: TX_lowTime--;
	movlw	low(01h)
	subwf	(_TX_lowTime),f
	movlw	high(01h)
	skipc
	decf	(_TX_lowTime+1),f
	subwf	(_TX_lowTime+1),f
	line	82
	
i1l1958:	
;yy_ir.C: 82: PA4 = 0;
	bcf	(44/8),(44)&7
	line	87
	
i1l903:	
	movf	(??_ISR+2),w
	movwf	pclath
	movf	(??_ISR+1),w
	movwf	fsr0
	swapf	(??_ISR+0)^0FFFFFF80h,w
	movwf	status
	swapf	saved_w,f
	swapf	saved_w,w
	retfie
	opt stack 0
GLOBAL	__end_of_ISR
	__end_of_ISR:
;; =============== function _ISR ends ============

	signat	_ISR,88
psect	text47,local,class=CODE,delta=2
global __ptext47
__ptext47:
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
