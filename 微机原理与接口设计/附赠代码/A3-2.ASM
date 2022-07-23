;=====================================================
; 文件名:   A3-2.ASM
; 功能描述: 十进制的BCD码减法运算
;=====================================================

SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK	ENDS

PUBLIC	X, Y, Z
DATA	SEGMENT
X		DW ?
Y		DW ?
Z		DW ?
DATA	ENDS

CODE	SEGMENT
		ASSUME CS:CODE, DS:DATA

START:	MOV AX, DATA
		MOV DS, AX
        MOV AH, 00H
		SAHF
		MOV CX, 0002H
		MOV SI, OFFSET X
		MOV DI, OFFSET Z
A1:     MOV AL, [SI]
        SBB AL, [SI+02H]
		DAS
		PUSHF
		AND AL, 0FH
		POPF
		MOV [DI], AL
		INC DI
		INC SI
		LOOP A1
		JMP START
CODE 	ENDS
		END START