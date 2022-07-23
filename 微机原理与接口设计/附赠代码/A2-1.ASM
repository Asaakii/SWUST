;=========================================================
; 文件名:   A2-1.ASM
; 功能描述: 将ASCII码表示的十进制转换为二进制
;=========================================================
PUBLIC  SADD
SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK	ENDS

DATA	SEGMENT
SADD	DB  30H,30H,32H,35H,36H		;十进制数:00256
DATA	ENDS

CODE	SEGMENT
		ASSUME CS:CODE, DS:DATA

START:	MOV AX, DATA
		MOV DS, AX
		MOV AX, OFFSET SADD
		MOV SI, AX
		MOV BX, 000AH
		MOV CX, 0004H
		MOV AH, 00H
		MOV AL, [SI]
		SUB AL, 30H
A1:		IMUL BX
		MOV DX, [SI+01]
		AND DX, 00FFH
		ADC AX, DX
		SBB AX, 30H
		INC SI
		LOOP A1
A2:		JMP A2
CODE 	ENDS
     	END START