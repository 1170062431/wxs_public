opt subtitle "HI-TECH Software Omniscient Code Generator (PRO mode) build 10920"

opt pagewidth 120

	opt pm

	processor	16F685
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
	FNCALL	_main,_POWER_INITIAL
	FNCALL	_main,_ADC_INITIAL
	FNCALL	_main,_PWM_INITIAL
	FNCALL	_main,_DelayS
	FNCALL	_main,_buzzerOn
	FNCALL	_main,_keyScan
	FNCALL	_main,_keyAction
	FNCALL	_DelayS,_DelayMs
	FNCALL	_keyAction,_turnToModeWork
	FNCALL	_keyAction,_turnToModeIdle
	FNCALL	_DelayMs,_DelayUs
	FNCALL	_turnToModeWork,_buzzerOn
	FNCALL	_turnToModeIdle,_buzzerOn
	FNROOT	_main
	FNCALL	intlevel1,_ISR
	global	intlevel1
	FNROOT	intlevel1
	global	_stu_buzzer
	global	ISR@T_1ms
	global	ISR@T_125us
	global	_C_sleep
	global	_F_keyLJ
	global	_VREGC
	global	_keyBackUp
	global	_keyCode
	global	_keySta
	global	_mode
	global	_Time_FLAG
	global	_keyBuff
	global	_SAFlag
	global	_PSTRCON
psect	text367,local,class=CODE,delta=2
global __ptext367
__ptext367:
_PSTRCON	set	413
	DABS	1,413,1	;_PSTRCON

	global	_SRCON
_SRCON	set	414
	DABS	1,414,1	;_SRCON

	global	_C1SEN
_C1SEN	set	3317
	DABS	1,414,1	;_C1SEN

	global	_C2REN
_C2REN	set	3316
	DABS	1,414,1	;_C2REN

	global	_EEPGD
_EEPGD	set	3175
	DABS	1,396,1	;_EEPGD

	global	_PULSR
_PULSR	set	3314
	DABS	1,414,1	;_PULSR

	global	_PULSS
_PULSS	set	3315
	DABS	1,414,1	;_PULSS

	global	_SR0
_SR0	set	3318
	DABS	1,414,1	;_SR0

	global	_SR1
_SR1	set	3319
	DABS	1,414,1	;_SR1

	global	_STRA
_STRA	set	3304
	DABS	1,413,1	;_STRA

	global	_STRB
_STRB	set	3305
	DABS	1,413,1	;_STRB

	global	_STRC
_STRC	set	3306
	DABS	1,413,1	;_STRC

	global	_STRD
_STRD	set	3307
	DABS	1,413,1	;_STRD

	global	_STRSYNC
_STRSYNC	set	3308
	DABS	1,413,1	;_STRSYNC

	global	_WREN
_WREN	set	3170
	DABS	1,396,1	;_WREN

	global	_ADCON0
_ADCON0	set	31
	global	_CMCON0
_CMCON0	set	25
	global	_INTCON
_INTCON	set	11
	global	_MSCKCON
_MSCKCON	set	27
	global	_PORTA
_PORTA	set	5
	global	_PORTC
_PORTC	set	7
	global	_T1CON
_T1CON	set	16
	global	_T2CON
_T2CON	set	18
	global	_TMR0
_TMR0	set	1
	global	_TMR1H
_TMR1H	set	15
	global	_TMR1L
_TMR1L	set	14
	global	_WDTCON
_WDTCON	set	24
	global	_GIE
_GIE	set	95
	global	_PA2
_PA2	set	42
	global	_PA4
_PA4	set	44
	global	_PA6
_PA6	set	46
	global	_PA7
_PA7	set	47
	global	_PAIE
_PAIE	set	91
	global	_PAIF
_PAIF	set	88
	global	_PC2
_PC2	set	58
	global	_PC3
_PC3	set	59
	global	_PC4
_PC4	set	60
	global	_PEIE
_PEIE	set	94
	global	_SWDTEN
_SWDTEN	set	192
	global	_T0IE
_T0IE	set	93
	global	_T0IF
_T0IF	set	90
	global	_TMR1IF
_TMR1IF	set	96
	global	_TMR1ON
_TMR1ON	set	128
	global	_TMR2IF
_TMR2IF	set	97
	global	_TMR2ON
_TMR2ON	set	146
	global	_ADCON1
_ADCON1	set	159
	global	_ANSEL
_ANSEL	set	145
	global	_OPTION
_OPTION	set	129
	global	_OSCCON
_OSCCON	set	143
	global	_PR2
_PR2	set	146
	global	_TRISA
_TRISA	set	133
	global	_TRISC
_TRISC	set	135
	global	_WPUA
_WPUA	set	149
	global	_WPUC
_WPUC	set	136
	global	_IOCA2
_IOCA2	set	1202
	global	_TMR1IE
_TMR1IE	set	1120
	global	_TMR2IE
_TMR2IE	set	1121
	global	_TRISA0
_TRISA0	set	1064
	global	_TRISA1
_TRISA1	set	1065
	global	_TRISA2
_TRISA2	set	1066
	global	_TRISA4
_TRISA4	set	1068
	global	_TRISA5
_TRISA5	set	1069
	global	_TRISC0
_TRISC0	set	1080
	global	_TRISC1
_TRISC1	set	1081
	global	_TRISC2
_TRISC2	set	1082
	global	_TRISC3
_TRISC3	set	1083
	global	_TRISC4
_TRISC4	set	1084
	global	_TRISC5
_TRISC5	set	1085
	global	_WPUA0
_WPUA0	set	1192
	global	_WPUA1
_WPUA1	set	1193
	global	_WPUA2
_WPUA2	set	1194
	global	_WPUA3
_WPUA3	set	1195
	global	_WPUA5
_WPUA5	set	1197
	global	_WPUC0
_WPUC0	set	1088
	global	_WPUC1
_WPUC1	set	1089
	global	_WPUC5
_WPUC5	set	1093
	global	_PR3L
_PR3L	set	270
	global	_PWM3CR0
_PWM3CR0	set	271
	global	_PWM3CR1
_PWM3CR1	set	272
	global	_T3CKDIV
_T3CKDIV	set	273
	global	_TMR3H
_TMR3H	set	269
	file	"user_project.as"
	line	#
psect cinit,class=CODE,delta=2
global start_initialization
start_initialization:

psect	bitbssCOMMON,class=COMMON,bit,space=1
global __pbitbssCOMMON
__pbitbssCOMMON:
_SAFlag:
       ds      1

psect	bssCOMMON,class=COMMON,space=1
global __pbssCOMMON
__pbssCOMMON:
_Time_FLAG:
       ds      1

_keyBuff:
       ds      1

psect	bssBANK0,class=BANK0,space=1
global __pbssBANK0
__pbssBANK0:
_stu_buzzer:
       ds      9

ISR@T_1ms:
       ds      2

ISR@T_125us:
       ds      1

_C_sleep:
       ds      1

_F_keyLJ:
       ds      1

_VREGC:
       ds      1

_keyBackUp:
       ds      1

_keyCode:
       ds      1

_keySta:
       ds      1

_mode:
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

; Clear objects allocated to BITCOMMON
psect cinit,class=CODE,delta=2
	clrf	((__pbitbssCOMMON/8)+0)&07Fh
; Clear objects allocated to COMMON
psect cinit,class=CODE,delta=2
	clrf	((__pbssCOMMON)+0)&07Fh
	clrf	((__pbssCOMMON)+1)&07Fh
; Clear objects allocated to BANK0
psect cinit,class=CODE,delta=2
	bcf	status, 7	;select IRP bank0
	movlw	low(__pbssBANK0)
	movwf	fsr
	movlw	low((__pbssBANK0)+013h)
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
	global	?_POWER_INITIAL
?_POWER_INITIAL:	; 0 bytes @ 0x0
	global	?_DelayUs
?_DelayUs:	; 0 bytes @ 0x0
	global	?_DelayMs
?_DelayMs:	; 0 bytes @ 0x0
	global	?_DelayS
?_DelayS:	; 0 bytes @ 0x0
	global	?_ISR
?_ISR:	; 0 bytes @ 0x0
	global	??_ISR
??_ISR:	; 0 bytes @ 0x0
	global	?_PWM_INITIAL
?_PWM_INITIAL:	; 0 bytes @ 0x0
	global	?_ADC_INITIAL
?_ADC_INITIAL:	; 0 bytes @ 0x0
	global	?_turnToModeIdle
?_turnToModeIdle:	; 0 bytes @ 0x0
	global	?_turnToModeWork
?_turnToModeWork:	; 0 bytes @ 0x0
	global	?_keyScan
?_keyScan:	; 0 bytes @ 0x0
	global	?_keyAction
?_keyAction:	; 0 bytes @ 0x0
	global	?_main
?_main:	; 2 bytes @ 0x0
	ds	3
	global	?_buzzerOn
?_buzzerOn:	; 0 bytes @ 0x3
	global	??_POWER_INITIAL
??_POWER_INITIAL:	; 0 bytes @ 0x3
	global	??_DelayUs
??_DelayUs:	; 0 bytes @ 0x3
	global	??_PWM_INITIAL
??_PWM_INITIAL:	; 0 bytes @ 0x3
	global	??_ADC_INITIAL
??_ADC_INITIAL:	; 0 bytes @ 0x3
	global	??_keyScan
??_keyScan:	; 0 bytes @ 0x3
	global	DelayUs@Time
DelayUs@Time:	; 1 bytes @ 0x3
	global	buzzerOn@bzOnTime_ms
buzzerOn@bzOnTime_ms:	; 2 bytes @ 0x3
	ds	1
	global	DelayUs@a
DelayUs@a:	; 1 bytes @ 0x4
	ds	1
	global	??_DelayMs
??_DelayMs:	; 0 bytes @ 0x5
	global	DelayMs@Time
DelayMs@Time:	; 1 bytes @ 0x5
	global	buzzerOn@bzOffTime_ms
buzzerOn@bzOffTime_ms:	; 2 bytes @ 0x5
	ds	1
	global	DelayMs@a
DelayMs@a:	; 1 bytes @ 0x6
	ds	1
	global	DelayMs@b
DelayMs@b:	; 1 bytes @ 0x7
	global	buzzerOn@bzTimes
buzzerOn@bzTimes:	; 1 bytes @ 0x7
	ds	1
	global	??_buzzerOn
??_buzzerOn:	; 0 bytes @ 0x8
	global	??_DelayS
??_DelayS:	; 0 bytes @ 0x8
	global	??_turnToModeIdle
??_turnToModeIdle:	; 0 bytes @ 0x8
	global	??_turnToModeWork
??_turnToModeWork:	; 0 bytes @ 0x8
	global	??_keyAction
??_keyAction:	; 0 bytes @ 0x8
	global	??_main
??_main:	; 0 bytes @ 0x8
psect	cstackBANK0,class=BANK0,space=1
global __pcstackBANK0
__pcstackBANK0:
	global	DelayS@Time
DelayS@Time:	; 1 bytes @ 0x0
	ds	1
	global	DelayS@a
DelayS@a:	; 1 bytes @ 0x1
	ds	1
	global	DelayS@b
DelayS@b:	; 1 bytes @ 0x2
	ds	1
;;Data sizes: Strings 0, constant 0, data 0, bss 21, persistent 0 stack 0
;;Auto spaces:   Size  Autos    Used
;; COMMON          14      8      11
;; BANK0           80      3      22
;; BANK1           32      0       0

;;
;; Pointer list with targets:



;;
;; Critical Paths under _main in COMMON
;;
;;   _main->_buzzerOn
;;   _DelayS->_DelayMs
;;   _DelayMs->_DelayUs
;;   _turnToModeWork->_buzzerOn
;;   _turnToModeIdle->_buzzerOn
;;
;; Critical Paths under _ISR in COMMON
;;
;;   None.
;;
;; Critical Paths under _main in BANK0
;;
;;   _main->_DelayS
;;
;; Critical Paths under _ISR in BANK0
;;
;;   None.
;;
;; Critical Paths under _main in BANK1
;;
;;   None.
;;
;; Critical Paths under _ISR in BANK1
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
;; (0) _main                                                 0     0      0     538
;;                      _POWER_INITIAL
;;                        _ADC_INITIAL
;;                        _PWM_INITIAL
;;                             _DelayS
;;                           _buzzerOn
;;                            _keyScan
;;                          _keyAction
;; ---------------------------------------------------------------------------------
;; (1) _DelayS                                               3     3      0     340
;;                                              0 BANK0      3     3      0
;;                            _DelayMs
;; ---------------------------------------------------------------------------------
;; (1) _keyAction                                            0     0      0     132
;;                     _turnToModeWork
;;                     _turnToModeIdle
;; ---------------------------------------------------------------------------------
;; (2) _DelayMs                                              3     3      0     204
;;                                              5 COMMON     3     3      0
;;                            _DelayUs
;; ---------------------------------------------------------------------------------
;; (2) _turnToModeWork                                       0     0      0      66
;;                           _buzzerOn
;; ---------------------------------------------------------------------------------
;; (2) _turnToModeIdle                                       0     0      0      66
;;                           _buzzerOn
;; ---------------------------------------------------------------------------------
;; (3) _DelayUs                                              2     2      0      68
;;                                              3 COMMON     2     2      0
;; ---------------------------------------------------------------------------------
;; (1) _keyScan                                              0     0      0       0
;; ---------------------------------------------------------------------------------
;; (3) _buzzerOn                                             5     0      5      66
;;                                              3 COMMON     5     0      5
;; ---------------------------------------------------------------------------------
;; (1) _ADC_INITIAL                                          0     0      0       0
;; ---------------------------------------------------------------------------------
;; (1) _PWM_INITIAL                                          0     0      0       0
;; ---------------------------------------------------------------------------------
;; (1) _POWER_INITIAL                                        0     0      0       0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 3
;; ---------------------------------------------------------------------------------
;; (Depth) Function   	        Calls       Base Space   Used Autos Params    Refs
;; ---------------------------------------------------------------------------------
;; (4) _ISR                                                  3     3      0       0
;;                                              0 COMMON     3     3      0
;; ---------------------------------------------------------------------------------
;; Estimated maximum stack depth 4
;; ---------------------------------------------------------------------------------

;; Call Graph Graphs:

;; _main (ROOT)
;;   _POWER_INITIAL
;;   _ADC_INITIAL
;;   _PWM_INITIAL
;;   _DelayS
;;     _DelayMs
;;       _DelayUs
;;   _buzzerOn
;;   _keyScan
;;   _keyAction
;;     _turnToModeWork
;;       _buzzerOn
;;     _turnToModeIdle
;;       _buzzerOn
;;
;; _ISR (ROOT)
;;

;; Address spaces:

;;Name               Size   Autos  Total    Cost      Usage
;;BITCOMMON            E      0       1       0        7.1%
;;EEDATA             100      0       0       0        0.0%
;;NULL                 0      0       0       0        0.0%
;;CODE                 0      0       0       0        0.0%
;;COMMON               E      8       B       1       78.6%
;;BITSFR0              0      0       0       1        0.0%
;;SFR0                 0      0       0       1        0.0%
;;BITSFR1              0      0       0       2        0.0%
;;SFR1                 0      0       0       2        0.0%
;;STACK                0      0       3       2        0.0%
;;BITBANK0            50      0       0       3        0.0%
;;BANK0               50      3      16       4       27.5%
;;BITBANK1            20      0       0       5        0.0%
;;BITSFR2              0      0       0       5        0.0%
;;SFR2                 0      0       0       5        0.0%
;;BANK1               20      0       0       6        0.0%
;;ABS                  0      0      21       7        0.0%
;;DATA                 0      0      24       8        0.0%

	global	_main
psect	maintext,global,class=CODE,delta=2
global __pmaintext
__pmaintext:

;; *************** function _main *****************
;; Defined at:
;;		line 103 in file "user_project.C"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;                  2  10799[COMMON] int 
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 60/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels required when called:    4
;; This function calls:
;;		_POWER_INITIAL
;;		_ADC_INITIAL
;;		_PWM_INITIAL
;;		_DelayS
;;		_buzzerOn
;;		_keyScan
;;		_keyAction
;; This function is called by:
;;		Startup code after reset
;; This function uses a non-reentrant model
;;
psect	maintext
	file	"user_project.C"
	line	103
	global	__size_of_main
	__size_of_main	equ	__end_of_main-_main
	
_main:	
	opt	stack 4
; Regs used in _main: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	104
	
l12547:	
;user_project.C: 104: POWER_INITIAL();
	fcall	_POWER_INITIAL
	line	105
;user_project.C: 105: ADC_INITIAL();
	fcall	_ADC_INITIAL
	line	106
;user_project.C: 108: F_feedDog = SET;
	fcall	_PWM_INITIAL
	line	110
	
l12549:	
;user_project.C: 110: PA7 = 1;
	bcf	status, 6	;RP1=0, select bank0
	bsf	(47/8),(47)&7
	line	111
	
l12551:	
;user_project.C: 111: PA4 = 1;
	bsf	(44/8),(44)&7
	line	112
	
l12553:	
;user_project.C: 112: PA6 = 1;
	bsf	(46/8),(46)&7
	line	113
;user_project.C: 113: DelayS(1);
	movlw	(01h)
	fcall	_DelayS
	line	114
	
l12555:	
;user_project.C: 114: PA7 = 0;
	bcf	(47/8),(47)&7
	line	115
	
l12557:	
;user_project.C: 115: PA4 = 0;
	bcf	(44/8),(44)&7
	line	116
	
l12559:	
;user_project.C: 116: PA6 = 0;
	bcf	(46/8),(46)&7
	line	117
;user_project.C: 117: buzzerOn(200, 200, 1);
	movlw	0C8h
	movwf	(?_buzzerOn)
	clrf	(?_buzzerOn+1)
	movlw	0C8h
	movwf	0+(?_buzzerOn)+02h
	clrf	1+(?_buzzerOn)+02h
	clrf	0+(?_buzzerOn)+04h
	incf	0+(?_buzzerOn)+04h,f
	fcall	_buzzerOn
	line	121
	
l12561:	
;user_project.C: 120: {
;user_project.C: 121: if(Time_FLAG.bit1)
	btfss	(_Time_FLAG),0	;volatile
	goto	u621
	goto	u620
u621:
	goto	l10801
u620:
	line	123
	
l12563:	
;user_project.C: 122: {
;user_project.C: 123: Time_FLAG.bit1 = RESET;
	bcf	(_Time_FLAG),0	;volatile
	line	124
	
l12565:	
;user_project.C: 124: keyScan();
	fcall	_keyScan
	line	125
	
l12567:	
;user_project.C: 125: if(keyCode && !F_keyLJ)
	movf	(_keyCode),w
	skipz
	goto	u630
	goto	l12573
u630:
	
l12569:	
	movf	(_F_keyLJ),f
	skipz
	goto	u641
	goto	u640
u641:
	goto	l12573
u640:
	line	127
	
l12571:	
;user_project.C: 126: {
;user_project.C: 127: keyAction();
	fcall	_keyAction
	line	131
	
l12573:	
;user_project.C: 128: }
;user_project.C: 131: if(stu_buzzer.buzzerTimes)
	movf	0+(_stu_buzzer)+08h,w
	skipz
	goto	u650
	goto	l10803
u650:
	line	133
	
l12575:	
;user_project.C: 132: {
;user_project.C: 133: if(stu_buzzer.C_buzzerOnTime_ms)
	movlw	(04h)
	addlw	_stu_buzzer&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	incf	fsr0,f
	iorwf	indf,w
	skipnz
	goto	u661
	goto	u660
u661:
	goto	l12579
u660:
	line	135
	
l12577:	
;user_project.C: 134: {
;user_project.C: 135: stu_buzzer.C_buzzerOnTime_ms--;
	movlw	low(01h)
	subwf	0+(_stu_buzzer)+04h,f
	movlw	high(01h)
	skipc
	decf	1+(_stu_buzzer)+04h,f
	subwf	1+(_stu_buzzer)+04h,f
	line	136
;user_project.C: 136: }
	goto	l10803
	line	137
	
l12579:	
;user_project.C: 137: else if(stu_buzzer.C_buzzerOffTime_ms)
	movlw	(06h)
	addlw	_stu_buzzer&0ffh
	movwf	fsr0
	movf	indf,w
	incf	fsr0,f
	iorwf	indf,w
	skipnz
	goto	u671
	goto	u670
u671:
	goto	l12583
u670:
	line	139
	
l12581:	
;user_project.C: 138: {
;user_project.C: 139: stu_buzzer.C_buzzerOffTime_ms--;
	movlw	low(01h)
	subwf	0+(_stu_buzzer)+06h,f
	movlw	high(01h)
	skipc
	decf	1+(_stu_buzzer)+06h,f
	subwf	1+(_stu_buzzer)+06h,f
	line	140
;user_project.C: 140: }
	goto	l10803
	line	143
	
l12583:	
;user_project.C: 141: else
;user_project.C: 142: {
;user_project.C: 143: stu_buzzer.buzzerTimes--;
	decf	0+(_stu_buzzer)+08h,f
	line	144
	
l12585:	
;user_project.C: 144: if(stu_buzzer.buzzerTimes)
	movf	0+(_stu_buzzer)+08h,w
	skipz
	goto	u680
	goto	l10803
u680:
	line	146
	
l12587:	
;user_project.C: 145: {
;user_project.C: 146: stu_buzzer.C_buzzerOnTime_ms = stu_buzzer.setBuzzerOnTime_ms;
	movf	(_stu_buzzer+1),w
	movwf	1+(_stu_buzzer)+04h
	movf	(_stu_buzzer),w
	movwf	0+(_stu_buzzer)+04h
	line	147
;user_project.C: 147: stu_buzzer.C_buzzerOffTime_ms = stu_buzzer.setBuzzerOffTime_ms;
	movf	1+(_stu_buzzer)+02h,w
	movwf	1+(_stu_buzzer)+06h
	movf	0+(_stu_buzzer)+02h,w
	movwf	0+(_stu_buzzer)+06h
	line	150
	
l10803:	
	line	153
;user_project.C: 148: }
;user_project.C: 149: }
;user_project.C: 150: }
;user_project.C: 153: if(C_sleep)
	movf	(_C_sleep),w
	skipz
	goto	u690
	goto	l10801
u690:
	line	154
	
l12589:	
;user_project.C: 154: C_sleep--;
	decf	(_C_sleep),f
	line	156
	
l10801:	
	line	158
;user_project.C: 156: }
;user_project.C: 158: if(mode == MODE_IDLE)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(_mode),f
	skipz
	goto	u701
	goto	u700
u701:
	goto	l12605
u700:
	line	160
	
l12591:	
;user_project.C: 159: {
;user_project.C: 160: if(!C_sleep)
	movf	(_C_sleep),f
	skipz
	goto	u711
	goto	u710
u711:
	goto	l12561
u710:
	line	162
	
l12593:	
;user_project.C: 161: {
;user_project.C: 162: C_sleep = 500;
	movlw	(0F4h)
	movwf	(_C_sleep)
	line	163
	
l12595:	
;user_project.C: 163: PAIF =0;
	bcf	(88/8),(88)&7
	line	164
	
l12597:	
;user_project.C: 164: IOCA2 =1;
	bsf	status, 5	;RP0=1, select bank1
	bsf	(1202/8)^080h,(1202)&7
	line	165
	
l12599:	
;user_project.C: 165: ReadAPin = PA2;
	line	166
	
l12601:	
;user_project.C: 166: PAIE =1;
	bsf	(91/8),(91)&7
	line	167
	
l12603:	
# 167 "user_project.C"
sleep ;#
psect	maintext
	goto	l12561
	line	172
	
l12605:	
;user_project.C: 170: else
;user_project.C: 171: {
;user_project.C: 172: C_sleep = 500;
	movlw	(0F4h)
	movwf	(_C_sleep)
	goto	l12561
	global	start
	ljmp	start
	opt stack 0
psect	maintext
	line	175
GLOBAL	__end_of_main
	__end_of_main:
;; =============== function _main ends ============

	signat	_main,90
	global	_DelayS
psect	text368,local,class=CODE,delta=2
global __ptext368
__ptext368:

;; *************** function _DelayS *****************
;; Defined at:
;;		line 170 in file "sys_init.c"
;; Parameters:    Size  Location     Type
;;  Time            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  Time            1    0[BANK0 ] unsigned char 
;;  b               1    2[BANK0 ] unsigned char 
;;  a               1    1[BANK0 ] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 60/0
;;		On exit  : 60/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       3       0
;;      Temps:          0       0       0
;;      Totals:         0       3       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_DelayMs
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text368
	file	"sys_init.c"
	line	170
	global	__size_of_DelayS
	__size_of_DelayS	equ	__end_of_DelayS-_DelayS
	
_DelayS:	
	opt	stack 4
; Regs used in _DelayS: [wreg+status,2+status,0+pclath+cstack]
;DelayS@Time stored from wreg
	line	172
	movwf	(DelayS@Time)
	
l12529:	
;sys_init.c: 171: unsigned char a,b;
;sys_init.c: 172: for(a=0;a<Time;a++)
	clrf	(DelayS@a)
	goto	l12545
	line	174
	
l12531:	
;sys_init.c: 173: {
;sys_init.c: 174: for(b=0;b<10;b++)
	clrf	(DelayS@b)
	line	176
	
l12537:	
;sys_init.c: 175: {
;sys_init.c: 176: DelayMs(100);
	movlw	(064h)
	fcall	_DelayMs
	line	174
	
l12539:	
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	incf	(DelayS@b),f
	
l12541:	
	movlw	(0Ah)
	subwf	(DelayS@b),w
	skipc
	goto	u601
	goto	u600
u601:
	goto	l12537
u600:
	line	172
	
l12543:	
	incf	(DelayS@a),f
	
l12545:	
	movf	(DelayS@Time),w
	subwf	(DelayS@a),w
	skipc
	goto	u611
	goto	u610
u611:
	goto	l12531
u610:
	line	179
	
l1089:	
	return
	opt stack 0
GLOBAL	__end_of_DelayS
	__end_of_DelayS:
;; =============== function _DelayS ends ============

	signat	_DelayS,4216
	global	_keyAction
psect	text369,local,class=CODE,delta=2
global __ptext369
__ptext369:

;; *************** function _keyAction *****************
;; Defined at:
;;		line 79 in file "user_project.C"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, fsr0l, fsr0h, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 60/0
;;		On exit  : 60/0
;;		Unchanged: FFF9F/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    3
;; This function calls:
;;		_turnToModeWork
;;		_turnToModeIdle
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text369
	file	"user_project.C"
	line	79
	global	__size_of_keyAction
	__size_of_keyAction	equ	__end_of_keyAction-_keyAction
	
_keyAction:	
	opt	stack 4
; Regs used in _keyAction: [wreg-fsr0h+status,2+status,0+pclath+cstack]
	line	80
	
l12415:	
;user_project.C: 80: if(keyCode==1)
	decf	(_keyCode),w
	skipz
	goto	u441
	goto	u440
u441:
	goto	l10791
u440:
	goto	l12425
	line	85
	
l12419:	
;user_project.C: 85: turnToModeWork();
	fcall	_turnToModeWork
	line	86
;user_project.C: 86: break;
	goto	l10791
	line	88
	
l12421:	
;user_project.C: 88: turnToModeIdle();
	fcall	_turnToModeIdle
	line	89
;user_project.C: 89: break;
	goto	l10791
	line	82
	
l12425:	
	movf	(_mode),w
	; Switch size 1, requested type "space"
; Number of cases is 2, Range of values is 0 to 1
; switch strategies available:
; Name         Instructions Cycles
; simple_byte            7     4 (average)
; direct_byte            8     6 (fixed)
; jumptable            260     6 (fixed)
; rangetable             6     6 (fixed)
; spacedrange           10     9 (fixed)
; locatedrange           2     3 (fixed)
;	Chosen strategy is simple_byte

	opt asmopt_off
	xorlw	0^0	; case 0
	skipnz
	goto	l12419
	xorlw	1^0	; case 1
	skipnz
	goto	l12421
	goto	l10791
	opt asmopt_on

	line	92
	
l10791:	
	line	93
;user_project.C: 92: }
;user_project.C: 93: F_keyLJ = SET;
	clrf	(_F_keyLJ)
	incf	(_F_keyLJ),f
	line	94
	
l10797:	
	return
	opt stack 0
GLOBAL	__end_of_keyAction
	__end_of_keyAction:
;; =============== function _keyAction ends ============

	signat	_keyAction,88
	global	_DelayMs
psect	text370,local,class=CODE,delta=2
global __ptext370
__ptext370:

;; *************** function _DelayMs *****************
;; Defined at:
;;		line 152 in file "sys_init.c"
;; Parameters:    Size  Location     Type
;;  Time            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  Time            1    5[COMMON] unsigned char 
;;  b               1    7[COMMON] unsigned char 
;;  a               1    6[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 60/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         3       0       0
;;      Temps:          0       0       0
;;      Totals:         3       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_DelayUs
;; This function is called by:
;;		_DelayS
;; This function uses a non-reentrant model
;;
psect	text370
	file	"sys_init.c"
	line	152
	global	__size_of_DelayMs
	__size_of_DelayMs	equ	__end_of_DelayMs-_DelayMs
	
_DelayMs:	
	opt	stack 4
; Regs used in _DelayMs: [wreg+status,2+status,0+pclath+cstack]
;DelayMs@Time stored from wreg
	line	154
	movwf	(DelayMs@Time)
	
l12511:	
;sys_init.c: 153: unsigned char a,b;
;sys_init.c: 154: for(a=0;a<Time;a++)
	clrf	(DelayMs@a)
	goto	l12527
	line	156
	
l12513:	
;sys_init.c: 155: {
;sys_init.c: 156: for(b=0;b<5;b++)
	clrf	(DelayMs@b)
	line	158
	
l12519:	
;sys_init.c: 157: {
;sys_init.c: 158: DelayUs(197);
	movlw	(0C5h)
	fcall	_DelayUs
	line	156
	
l12521:	
	incf	(DelayMs@b),f
	
l12523:	
	movlw	(05h)
	subwf	(DelayMs@b),w
	skipc
	goto	u581
	goto	u580
u581:
	goto	l12519
u580:
	line	154
	
l12525:	
	incf	(DelayMs@a),f
	
l12527:	
	movf	(DelayMs@Time),w
	subwf	(DelayMs@a),w
	skipc
	goto	u591
	goto	u590
u591:
	goto	l12513
u590:
	line	161
	
l1081:	
	return
	opt stack 0
GLOBAL	__end_of_DelayMs
	__end_of_DelayMs:
;; =============== function _DelayMs ends ============

	signat	_DelayMs,4216
	global	_turnToModeWork
psect	text371,local,class=CODE,delta=2
global __ptext371
__ptext371:

;; *************** function _turnToModeWork *****************
;; Defined at:
;;		line 42 in file "user_project.C"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 60/0
;;		On exit  : 60/0
;;		Unchanged: FFF9F/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_buzzerOn
;; This function is called by:
;;		_keyAction
;; This function uses a non-reentrant model
;;
psect	text371
	file	"user_project.C"
	line	42
	global	__size_of_turnToModeWork
	__size_of_turnToModeWork	equ	__end_of_turnToModeWork-_turnToModeWork
	
_turnToModeWork:	
	opt	stack 4
; Regs used in _turnToModeWork: [wreg+status,2+status,0+pclath+cstack]
	line	43
	
l12393:	
;user_project.C: 43: mode = MODE_WORK;
	clrf	(_mode)
	incf	(_mode),f
	line	44
	
l12395:	
;user_project.C: 44: buzzerOn(200, 200, 1);
	movlw	0C8h
	movwf	(?_buzzerOn)
	clrf	(?_buzzerOn+1)
	movlw	0C8h
	movwf	0+(?_buzzerOn)+02h
	clrf	1+(?_buzzerOn)+02h
	clrf	0+(?_buzzerOn)+04h
	incf	0+(?_buzzerOn)+04h,f
	fcall	_buzzerOn
	line	45
	
l10781:	
	return
	opt stack 0
GLOBAL	__end_of_turnToModeWork
	__end_of_turnToModeWork:
;; =============== function _turnToModeWork ends ============

	signat	_turnToModeWork,88
	global	_turnToModeIdle
psect	text372,local,class=CODE,delta=2
global __ptext372
__ptext372:

;; *************** function _turnToModeIdle *****************
;; Defined at:
;;		line 31 in file "user_project.C"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0, pclath, cstack
;; Tracked objects:
;;		On entry : 60/0
;;		On exit  : 60/0
;;		Unchanged: FFF9F/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    2
;; This function calls:
;;		_buzzerOn
;; This function is called by:
;;		_keyAction
;; This function uses a non-reentrant model
;;
psect	text372
	file	"user_project.C"
	line	31
	global	__size_of_turnToModeIdle
	__size_of_turnToModeIdle	equ	__end_of_turnToModeIdle-_turnToModeIdle
	
_turnToModeIdle:	
	opt	stack 4
; Regs used in _turnToModeIdle: [wreg+status,2+status,0+pclath+cstack]
	line	32
	
l12389:	
;user_project.C: 32: mode = MODE_IDLE;
	clrf	(_mode)
	line	33
	
l12391:	
;user_project.C: 33: buzzerOn(200, 200, 1);
	movlw	0C8h
	movwf	(?_buzzerOn)
	clrf	(?_buzzerOn+1)
	movlw	0C8h
	movwf	0+(?_buzzerOn)+02h
	clrf	1+(?_buzzerOn)+02h
	clrf	0+(?_buzzerOn)+04h
	incf	0+(?_buzzerOn)+04h,f
	fcall	_buzzerOn
	line	34
	
l10778:	
	return
	opt stack 0
GLOBAL	__end_of_turnToModeIdle
	__end_of_turnToModeIdle:
;; =============== function _turnToModeIdle ends ============

	signat	_turnToModeIdle,88
	global	_DelayUs
psect	text373,local,class=CODE,delta=2
global __ptext373
__ptext373:

;; *************** function _DelayUs *****************
;; Defined at:
;;		line 137 in file "sys_init.c"
;; Parameters:    Size  Location     Type
;;  Time            1    wreg     unsigned char 
;; Auto vars:     Size  Location     Type
;;  Time            1    3[COMMON] unsigned char 
;;  a               1    4[COMMON] unsigned char 
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 0/0
;;		Unchanged: 0/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         2       0       0
;;      Temps:          0       0       0
;;      Totals:         2       0       0
;;Total ram usage:        2 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_DelayMs
;; This function uses a non-reentrant model
;;
psect	text373
	file	"sys_init.c"
	line	137
	global	__size_of_DelayUs
	__size_of_DelayUs	equ	__end_of_DelayUs-_DelayUs
	
_DelayUs:	
	opt	stack 4
; Regs used in _DelayUs: [wreg+status,2+status,0]
;DelayUs@Time stored from wreg
	line	139
	movwf	(DelayUs@Time)
	
l12505:	
;sys_init.c: 138: unsigned char a;
;sys_init.c: 139: for(a=0;a<Time;a++)
	clrf	(DelayUs@a)
	goto	l12509
	line	140
	
l1071:	
	line	141
;sys_init.c: 140: {
;sys_init.c: 141: _nop();
	nop
	line	139
	
l12507:	
	incf	(DelayUs@a),f
	
l12509:	
	movf	(DelayUs@Time),w
	subwf	(DelayUs@a),w
	skipc
	goto	u571
	goto	u570
u571:
	goto	l1071
u570:
	line	143
	
l1073:	
	return
	opt stack 0
GLOBAL	__end_of_DelayUs
	__end_of_DelayUs:
;; =============== function _DelayUs ends ============

	signat	_DelayUs,4216
	global	_keyScan
psect	text374,local,class=CODE,delta=2
global __ptext374
__ptext374:

;; *************** function _keyScan *****************
;; Defined at:
;;		line 53 in file "user_project.C"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2, status,0
;; Tracked objects:
;;		On entry : 0/0
;;		On exit  : 60/0
;;		Unchanged: FFF9F/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text374
	file	"user_project.C"
	line	53
	global	__size_of_keyScan
	__size_of_keyScan	equ	__end_of_keyScan-_keyScan
	
_keyScan:	
	opt	stack 6
; Regs used in _keyScan: [wreg+status,2+status,0]
	line	54
	
l12369:	
;user_project.C: 54: keyBuff = (keyBuff<<1)|PA2;
	clrc
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	btfsc	(42/8),(42)&7
	setc
	rlf	(_keyBuff),f
	line	55
	
l12371:	
;user_project.C: 55: if(!(keyBuff&0x0F))
	movf	(_keyBuff),w
	andlw	0Fh
	btfss	status,2
	goto	u381
	goto	u380
u381:
	goto	l12379
u380:
	line	57
	
l12373:	
;user_project.C: 56: {
;user_project.C: 57: keySta = 1;
	clrf	(_keySta)
	incf	(_keySta),f
	line	58
	
l12375:	
;user_project.C: 58: if(keySta != keyBackUp)
	decf	(_keyBackUp),w
	skipnz
	goto	u391
	goto	u390
u391:
	goto	l10788
u390:
	line	60
	
l12377:	
;user_project.C: 59: {
;user_project.C: 60: keyCode = 1;
	clrf	(_keyCode)
	incf	(_keyCode),f
	line	61
;user_project.C: 61: keyBackUp = 1;
	clrf	(_keyBackUp)
	incf	(_keyBackUp),f
	goto	l10788
	line	64
	
l12379:	
;user_project.C: 64: else if((keyBuff&0x0F) == 0x0F)
	movf	(_keyBuff),w
	andlw	0Fh
	xorlw	0Fh
	skipz
	goto	u401
	goto	u400
u401:
	goto	l10788
u400:
	line	66
	
l12381:	
;user_project.C: 65: {
;user_project.C: 66: keySta = 0;
	clrf	(_keySta)
	line	67
;user_project.C: 67: keyCode = 0;
	clrf	(_keyCode)
	line	68
;user_project.C: 68: keyBackUp = 0;
	clrf	(_keyBackUp)
	line	69
;user_project.C: 69: F_keyLJ = RESET;
	clrf	(_F_keyLJ)
	line	71
	
l10788:	
	return
	opt stack 0
GLOBAL	__end_of_keyScan
	__end_of_keyScan:
;; =============== function _keyScan ends ============

	signat	_keyScan,88
	global	_buzzerOn
psect	text375,local,class=CODE,delta=2
global __ptext375
__ptext375:

;; *************** function _buzzerOn *****************
;; Defined at:
;;		line 11 in file "buzzer.c"
;; Parameters:    Size  Location     Type
;;  bzOnTime_ms     2    3[COMMON] unsigned int 
;;  bzOffTime_ms    2    5[COMMON] unsigned int 
;;  bzTimes         1    7[COMMON] unsigned char 
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 60/0
;;		On exit  : 60/0
;;		Unchanged: FFF9F/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         5       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         5       0       0
;;Total ram usage:        5 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_turnToModeIdle
;;		_turnToModeWork
;;		_main
;; This function uses a non-reentrant model
;;
psect	text375
	file	"buzzer.c"
	line	11
	global	__size_of_buzzerOn
	__size_of_buzzerOn	equ	__end_of_buzzerOn-_buzzerOn
	
_buzzerOn:	
	opt	stack 4
; Regs used in _buzzerOn: [wreg]
	line	12
	
l12367:	
;buzzer.c: 12: stu_buzzer.setBuzzerOnTime_ms = bzOnTime_ms;
	movf	(buzzerOn@bzOnTime_ms+1),w
	movwf	(_stu_buzzer+1)
	movf	(buzzerOn@bzOnTime_ms),w
	movwf	(_stu_buzzer)
	line	13
;buzzer.c: 13: stu_buzzer.setBuzzerOffTime_ms = bzOffTime_ms;
	movf	(buzzerOn@bzOffTime_ms+1),w
	movwf	1+(_stu_buzzer)+02h
	movf	(buzzerOn@bzOffTime_ms),w
	movwf	0+(_stu_buzzer)+02h
	line	14
;buzzer.c: 14: stu_buzzer.C_buzzerOnTime_ms = stu_buzzer.setBuzzerOnTime_ms;
	movf	(_stu_buzzer+1),w
	movwf	1+(_stu_buzzer)+04h
	movf	(_stu_buzzer),w
	movwf	0+(_stu_buzzer)+04h
	line	15
;buzzer.c: 15: stu_buzzer.C_buzzerOffTime_ms = stu_buzzer.setBuzzerOffTime_ms;
	movf	1+(_stu_buzzer)+02h,w
	movwf	1+(_stu_buzzer)+06h
	movf	0+(_stu_buzzer)+02h,w
	movwf	0+(_stu_buzzer)+06h
	line	16
;buzzer.c: 16: stu_buzzer.buzzerTimes = bzTimes;
	movf	(buzzerOn@bzTimes),w
	movwf	0+(_stu_buzzer)+08h
	line	17
	
l10820:	
	return
	opt stack 0
GLOBAL	__end_of_buzzerOn
	__end_of_buzzerOn:
;; =============== function _buzzerOn ends ============

	signat	_buzzerOn,12408
	global	_ADC_INITIAL
psect	text376,local,class=CODE,delta=2
global __ptext376
__ptext376:

;; *************** function _ADC_INITIAL *****************
;; Defined at:
;;		line 31 in file "TEST_61F022_ADC.C"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg
;; Tracked objects:
;;		On entry : 60/0
;;		On exit  : 60/0
;;		Unchanged: FFF9F/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text376
	file	"TEST_61F022_ADC.C"
	line	31
	global	__size_of_ADC_INITIAL
	__size_of_ADC_INITIAL	equ	__end_of_ADC_INITIAL-_ADC_INITIAL
	
_ADC_INITIAL:	
	opt	stack 6
; Regs used in _ADC_INITIAL: [wreg]
	line	33
	
l12365:	
;TEST_61F022_ADC.C: 33: ADCON1 = 0B01100000;
	movlw	(060h)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(159)^080h	;volatile
	line	60
;TEST_61F022_ADC.C: 60: ADCON0 = 0B10111100;
	movlw	(0BCh)
	bcf	status, 5	;RP0=0, select bank0
	movwf	(31)	;volatile
	line	61
	
l9654:	
	return
	opt stack 0
GLOBAL	__end_of_ADC_INITIAL
	__end_of_ADC_INITIAL:
;; =============== function _ADC_INITIAL ends ============

	signat	_ADC_INITIAL,88
	global	_PWM_INITIAL
psect	text377,local,class=CODE,delta=2
global __ptext377
__ptext377:

;; *************** function _PWM_INITIAL *****************
;; Defined at:
;;		line 35 in file "TEST_61F02X_PWM.C"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 60/0
;;		On exit  : 60/40
;;		Unchanged: FFF9F/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text377
	file	"TEST_61F02X_PWM.C"
	line	35
	global	__size_of_PWM_INITIAL
	__size_of_PWM_INITIAL	equ	__end_of_PWM_INITIAL-_PWM_INITIAL
	
_PWM_INITIAL:	
	opt	stack 6
; Regs used in _PWM_INITIAL: [wreg+status,2]
	line	138
	
l12357:	
;TEST_61F02X_PWM.C: 138: PWM3CR0 = 0B00110010;
	movlw	(032h)
	bsf	status, 6	;RP1=1, select bank2
	movwf	(271)^0100h	;volatile
	line	159
;TEST_61F02X_PWM.C: 159: PWM3CR1 = 0B10000000;
	movlw	(080h)
	movwf	(272)^0100h	;volatile
	line	164
	
l12359:	
;TEST_61F02X_PWM.C: 164: TMR3H=0;
	clrf	(269)^0100h	;volatile
	line	168
	
l12361:	
;TEST_61F02X_PWM.C: 168: T3CKDIV = 30;
	movlw	(01Eh)
	movwf	(273)^0100h	;volatile
	line	172
	
l12363:	
;TEST_61F02X_PWM.C: 172: PR3L = 128;
	movlw	(080h)
	movwf	(270)^0100h	;volatile
	line	226
	
l6438:	
	return
	opt stack 0
GLOBAL	__end_of_PWM_INITIAL
	__end_of_PWM_INITIAL:
;; =============== function _PWM_INITIAL ends ============

	signat	_PWM_INITIAL,88
	global	_POWER_INITIAL
psect	text378,local,class=CODE,delta=2
global __ptext378
__ptext378:

;; *************** function _POWER_INITIAL *****************
;; Defined at:
;;		line 8 in file "sys_init.c"
;; Parameters:    Size  Location     Type
;;		None
;; Auto vars:     Size  Location     Type
;;		None
;; Return value:  Size  Location     Type
;;		None               void
;; Registers used:
;;		wreg, status,2
;; Tracked objects:
;;		On entry : 17F/0
;;		On exit  : 60/0
;;		Unchanged: FFE00/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          0       0       0
;;      Totals:         0       0       0
;;Total ram usage:        0 bytes
;; Hardware stack levels used:    1
;; Hardware stack levels required when called:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		_main
;; This function uses a non-reentrant model
;;
psect	text378
	file	"sys_init.c"
	line	8
	global	__size_of_POWER_INITIAL
	__size_of_POWER_INITIAL	equ	__end_of_POWER_INITIAL-_POWER_INITIAL
	
_POWER_INITIAL:	
	opt	stack 6
; Regs used in _POWER_INITIAL: [wreg+status,2]
	line	9
	
l12207:	
;sys_init.c: 9: OSCCON = (OSCCON & 0x8F)|(7 << 4);
	bsf	status, 5	;RP0=1, select bank1
	movf	(143)^080h,w
	andlw	08Fh
	iorlw	070h
	movwf	(143)^080h	;volatile
	line	11
	
l12209:	
;sys_init.c: 11: INTCON = 0;
	clrf	(11)	;volatile
	line	12
	
l12211:	
;sys_init.c: 12: PORTA = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(5)	;volatile
	line	13
	
l12213:	
;sys_init.c: 13: TRISA = 0B11111111;
	movlw	(0FFh)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(133)^080h	;volatile
	line	15
;sys_init.c: 15: PORTC = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(7)	;volatile
	line	16
	
l12215:	
;sys_init.c: 16: TRISC = 0B11111111;
	movlw	(0FFh)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(135)^080h	;volatile
	line	18
	
l12217:	
;sys_init.c: 18: WPUA = 0B00000000;
	clrf	(149)^080h	;volatile
	line	19
	
l12219:	
;sys_init.c: 19: WPUC = 0B00000000;
	clrf	(136)^080h	;volatile
	line	20
	
l12221:	
;sys_init.c: 20: MSCKCON = 0B00000000;
	bcf	status, 5	;RP0=0, select bank0
	clrf	(27)	;volatile
	line	23
	
l12223:	
;sys_init.c: 23: CMCON0 = 0B00000000;
	clrf	(25)	;volatile
	line	24
	
l12225:	
;sys_init.c: 24: ANSEL = 0B10101000;
	movlw	(0A8h)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(145)^080h	;volatile
	line	26
	
l12227:	
;sys_init.c: 26: TRISC1 = 1;
	bsf	(1081/8)^080h,(1081)&7
	line	27
	
l12229:	
;sys_init.c: 27: WPUA3 = 0;
	bcf	(1195/8)^080h,(1195)&7
	line	29
	
l12231:	
;sys_init.c: 29: TRISC1 = 1;
	bsf	(1081/8)^080h,(1081)&7
	line	30
	
l12233:	
;sys_init.c: 30: WPUC1 = 0;
	bcf	(1089/8)^080h,(1089)&7
	line	32
	
l12235:	
;sys_init.c: 32: TRISC3 = 0;
	bcf	(1083/8)^080h,(1083)&7
	line	33
	
l12237:	
;sys_init.c: 33: PC3 = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	(59/8),(59)&7
	line	35
	
l12239:	
;sys_init.c: 35: TRISC2= 0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	(1082/8)^080h,(1082)&7
	line	36
	
l12241:	
;sys_init.c: 36: PC2 = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	(58/8),(58)&7
	line	38
	
l12243:	
;sys_init.c: 38: TRISA4 = 0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	(1068/8)^080h,(1068)&7
	line	39
	
l12245:	
;sys_init.c: 39: PA4 = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	(44/8),(44)&7
	line	41
	
l12247:	
;sys_init.c: 41: TRISC4 = 0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	(1084/8)^080h,(1084)&7
	line	42
	
l12249:	
;sys_init.c: 42: PC4 = 0;
	bcf	status, 5	;RP0=0, select bank0
	bcf	(60/8),(60)&7
	line	44
	
l12251:	
;sys_init.c: 44: TRISA2 = 1;
	bsf	status, 5	;RP0=1, select bank1
	bsf	(1066/8)^080h,(1066)&7
	line	45
	
l12253:	
;sys_init.c: 45: WPUA2 = 1;
	bsf	(1194/8)^080h,(1194)&7
	line	47
	
l12255:	
;sys_init.c: 47: TRISA0 = 1;
	bsf	(1064/8)^080h,(1064)&7
	line	48
	
l12257:	
;sys_init.c: 48: WPUA0 = 1;
	bsf	(1192/8)^080h,(1192)&7
	line	49
	
l12259:	
;sys_init.c: 49: TRISA1 = 1;
	bsf	(1065/8)^080h,(1065)&7
	line	50
	
l12261:	
;sys_init.c: 50: WPUA1 = 1;
	bsf	(1193/8)^080h,(1193)&7
	line	51
	
l12263:	
;sys_init.c: 51: TRISA5 = 1;
	bsf	(1069/8)^080h,(1069)&7
	line	52
	
l12265:	
;sys_init.c: 52: WPUA5 = 1;
	bsf	(1197/8)^080h,(1197)&7
	line	53
	
l12267:	
;sys_init.c: 53: TRISC0 = 1;
	bsf	(1080/8)^080h,(1080)&7
	line	54
	
l12269:	
;sys_init.c: 54: WPUC0 = 1;
	bsf	(1088/8)^080h,(1088)&7
	line	55
	
l12271:	
;sys_init.c: 55: TRISC5 = 1;
	bsf	(1085/8)^080h,(1085)&7
	line	56
	
l12273:	
;sys_init.c: 56: WPUC5 = 1;
	bsf	(1093/8)^080h,(1093)&7
	line	62
	
l12275:	
# 62 "sys_init.c"
clrwdt ;#
psect	text378
	line	63
	
l12277:	
;sys_init.c: 63: WDTCON = (WDTCON &0xE1)|(10<<1);
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(24),w
	andlw	0E1h
	iorlw	014h
	movwf	(24)	;volatile
	line	65
	
l12279:	
;sys_init.c: 65: SWDTEN = DISABLE;
	bcf	(192/8),(192)&7
	line	74
;sys_init.c: 74: OPTION = (0B00000000+2);
	movlw	(02h)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(129)^080h	;volatile
	line	79
;sys_init.c: 79: TMR0 = 131;
	movlw	(083h)
	bcf	status, 5	;RP0=0, select bank0
	movwf	(1)	;volatile
	line	89
	
l12281:	
;sys_init.c: 89: T1CON = 0B00000000;
	clrf	(16)	;volatile
	line	93
	
l12283:	
;sys_init.c: 93: TMR1L = 0XBF;
	movlw	(0BFh)
	movwf	(14)	;volatile
	line	94
	
l12285:	
;sys_init.c: 94: TMR1H = 0XE0;
	movlw	(0E0h)
	movwf	(15)	;volatile
	line	102
	
l12287:	
;sys_init.c: 102: T2CON = (1<<3)|1;
	movlw	(09h)
	movwf	(18)	;volatile
	line	103
	
l12289:	
;sys_init.c: 103: PR2 = 13;
	movlw	(0Dh)
	bsf	status, 5	;RP0=1, select bank1
	movwf	(146)^080h	;volatile
	line	115
	
l12291:	
;sys_init.c: 115: GIE = ENABLE;
	bsf	(95/8),(95)&7
	line	116
	
l12293:	
;sys_init.c: 116: PEIE = ENABLE;
	bsf	(94/8),(94)&7
	line	117
	
l12295:	
;sys_init.c: 117: T0IF = RESET;
	bcf	(90/8),(90)&7
	line	118
	
l12297:	
;sys_init.c: 118: T0IE = ENABLE;
	bsf	(93/8),(93)&7
	line	119
	
l12299:	
;sys_init.c: 119: TMR1IF = RESET;
	bcf	status, 5	;RP0=0, select bank0
	bcf	(96/8),(96)&7
	line	120
	
l12301:	
;sys_init.c: 120: TMR1IE = DISABLE;
	bsf	status, 5	;RP0=1, select bank1
	bcf	(1120/8)^080h,(1120)&7
	line	121
	
l12303:	
;sys_init.c: 121: TMR2IF = RESET;
	bcf	status, 5	;RP0=0, select bank0
	bcf	(97/8),(97)&7
	line	122
	
l12305:	
;sys_init.c: 122: TMR2IE = DISABLE;
	bsf	status, 5	;RP0=1, select bank1
	bcf	(1121/8)^080h,(1121)&7
	line	124
	
l12307:	
;sys_init.c: 124: (T0IF = 0,T0IE = 1);
	bcf	(90/8),(90)&7
	
l12309:	
	bsf	(93/8),(93)&7
	line	125
	
l12311:	
;sys_init.c: 125: (TMR1ON = 0);
	bcf	status, 5	;RP0=0, select bank0
	bcf	(128/8),(128)&7
	line	126
	
l12313:	
;sys_init.c: 126: (TMR2ON = 0);
	bcf	(146/8),(146)&7
	line	128
	
l1067:	
	return
	opt stack 0
GLOBAL	__end_of_POWER_INITIAL
	__end_of_POWER_INITIAL:
;; =============== function _POWER_INITIAL ends ============

	signat	_POWER_INITIAL,88
	global	_ISR
psect	text379,local,class=CODE,delta=2
global __ptext379
__ptext379:

;; *************** function _ISR *****************
;; Defined at:
;;		line 31 in file "test_61f02x_int.c"
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
;;		Unchanged: FFE00/0
;; Data sizes:     COMMON   BANK0   BANK1
;;      Params:         0       0       0
;;      Locals:         0       0       0
;;      Temps:          3       0       0
;;      Totals:         3       0       0
;;Total ram usage:        3 bytes
;; Hardware stack levels used:    1
;; This function calls:
;;		Nothing
;; This function is called by:
;;		Interrupt level 1
;; This function uses a non-reentrant model
;;
psect	text379
	file	"test_61f02x_int.c"
	line	31
	global	__size_of_ISR
	__size_of_ISR	equ	__end_of_ISR-_ISR
	
_ISR:	
	opt	stack 4
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
psect	text379
	line	33
	
i1l12315:	
;test_61f02x_int.c: 33: if(T0IE && T0IF)
	btfss	(93/8),(93)&7
	goto	u29_21
	goto	u29_20
u29_21:
	goto	i1l12345
u29_20:
	
i1l12317:	
	btfss	(90/8),(90)&7
	goto	u30_21
	goto	u30_20
u30_21:
	goto	i1l12345
u30_20:
	line	60
	
i1l12319:	
;test_61f02x_int.c: 34: {
;test_61f02x_int.c: 58: static u8 T_125us = 0;
;test_61f02x_int.c: 59: static u16 T_1ms = 0;
;test_61f02x_int.c: 60: T0IF = RESET;
	bcf	(90/8),(90)&7
	line	61
	
i1l12321:	
;test_61f02x_int.c: 61: TMR0 = 131;
	movlw	(083h)
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movwf	(1)	;volatile
	line	64
	
i1l12323:	
;test_61f02x_int.c: 64: if(stu_buzzer.C_buzzerOnTime_ms)
	movlw	(04h)
	addlw	_stu_buzzer&0ffh
	movwf	fsr0
	bcf	status, 7	;select IRP bank0
	movf	indf,w
	incf	fsr0,f
	iorwf	indf,w
	skipnz
	goto	u31_21
	goto	u31_20
u31_21:
	goto	i1l5368
u31_20:
	line	66
	
i1l12325:	
;test_61f02x_int.c: 65: {
;test_61f02x_int.c: 66: PC3 = PC2;
	btfsc	(58/8),(58)&7
	goto	u32_21
	goto	u32_20
	
u32_21:
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bsf	(59/8),(59)&7
	goto	u33_24
u32_20:
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	bcf	(59/8),(59)&7
u33_24:
	line	67
	
i1l12327:	
;test_61f02x_int.c: 67: PC2 = !PC2;
	movlw	1<<((58)&7)
	xorwf	((58)/8),f
	line	68
;test_61f02x_int.c: 68: }
	goto	i1l12329
	line	69
	
i1l5368:	
	line	71
;test_61f02x_int.c: 69: else
;test_61f02x_int.c: 70: {
;test_61f02x_int.c: 71: PC3 = 0;
	bcf	(59/8),(59)&7
	line	72
;test_61f02x_int.c: 72: PC2 = 0;
	bcf	(58/8),(58)&7
	line	76
	
i1l12329:	
;test_61f02x_int.c: 73: }
;test_61f02x_int.c: 76: T_125us++;
	incf	(ISR@T_125us),f
	line	77
	
i1l12331:	
;test_61f02x_int.c: 77: if(T_125us == 8)
	movf	(ISR@T_125us),w
	xorlw	08h
	skipz
	goto	u34_21
	goto	u34_20
u34_21:
	goto	i1l12345
u34_20:
	line	79
	
i1l12333:	
;test_61f02x_int.c: 78: {
;test_61f02x_int.c: 79: T_125us = 0;
	clrf	(ISR@T_125us)
	line	80
	
i1l12335:	
;test_61f02x_int.c: 80: Time_FLAG.bit1 = SET;
	bsf	(_Time_FLAG),0	;volatile
	line	81
	
i1l12337:	
;test_61f02x_int.c: 81: T_1ms++;
	incf	(ISR@T_1ms),f
	skipnz
	incf	(ISR@T_1ms+1),f
	line	82
	
i1l12339:	
;test_61f02x_int.c: 82: if(T_1ms == 1000)
		movf	(ISR@T_1ms+1),w
	xorlw	3
	movlw	232
	skipnz
	xorwf	(ISR@T_1ms),w

	skipz
	goto	u35_21
	goto	u35_20
u35_21:
	goto	i1l12345
u35_20:
	line	84
	
i1l12341:	
;test_61f02x_int.c: 83: {
;test_61f02x_int.c: 84: T_1ms = 0;
	clrf	(ISR@T_1ms)
	clrf	(ISR@T_1ms+1)
	line	85
	
i1l12343:	
;test_61f02x_int.c: 85: Time_FLAG.bit8 = SET;
	bsf	(_Time_FLAG),7	;volatile
	line	116
	
i1l12345:	
;test_61f02x_int.c: 87: }
;test_61f02x_int.c: 88: }
;test_61f02x_int.c: 90: }
;test_61f02x_int.c: 116: if(PAIE && PAIF)
	btfss	(91/8),(91)&7
	goto	u36_21
	goto	u36_20
u36_21:
	goto	i1l5373
u36_20:
	
i1l12347:	
	btfss	(88/8),(88)&7
	goto	u37_21
	goto	u37_20
u37_21:
	goto	i1l5373
u37_20:
	line	118
	
i1l12349:	
;test_61f02x_int.c: 117: {
;test_61f02x_int.c: 118: ReadAPin = PORTA;
	bcf	status, 5	;RP0=0, select bank0
	bcf	status, 6	;RP1=0, select bank0
	movf	(5),w	;volatile
	line	119
	
i1l12351:	
;test_61f02x_int.c: 119: PAIF = 0;
	bcf	(88/8),(88)&7
	line	120
	
i1l12353:	
;test_61f02x_int.c: 120: PAIE = 0;
	bcf	(91/8),(91)&7
	line	121
	
i1l12355:	
;test_61f02x_int.c: 121: IOCA2 =0;
	bsf	status, 5	;RP0=1, select bank1
	bcf	(1202/8)^080h,(1202)&7
	line	132
	
i1l5373:	
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
psect	text380,local,class=CODE,delta=2
global __ptext380
__ptext380:
	global	btemp
	btemp set 07Eh

	DABS	1,126,2	;btemp
	global	wtemp0
	wtemp0 set btemp
	end
