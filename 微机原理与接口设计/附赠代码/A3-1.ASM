;=====================================================
; 文件名:   A3-1.ASM
; 功能描述: 二进制双精度加法运算
;=====================================================

SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK	ENDS

PUBLIC	XH, XL, YH, YL
PUBLIC	ZH, ZL
DATA	SEGMENT
XL		DW ?			;X低位
XH		DW ?			;X高位
YL		DW ?			;Y低位
YH		DW ?			;Y高位
ZL		DW ?			;Z低位
ZH		DW ?			;Z高位
DATA	ENDS

CODE	SEGMENT
		ASSUME CS:CODE, DS:DATA

START:	MOV AX, DATA
		MOV DS, AX
		MOV AX, XL
		ADD AX, YL		;X低位加Y低位
		MOV ZL, AX		;低位和存到Z的低位
		MOV AX, XH
		ADC AX, YH		;高位带进位加
		MOV ZH, AX		;存高位结果
		JMP START
CODE	ENDS
		END START