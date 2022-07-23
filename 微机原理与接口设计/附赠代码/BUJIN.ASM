;=========================================================
; 文件名: BUJIN.ASM
; 功能描述: 步进电机控制实验
;=========================================================

IOY0         EQU   0600H          ;片选IOY0对应的端口始地址
MY8255_A     EQU   IOY0+00H*2     ;8255的A口地址
MY8255_B     EQU   IOY0+01H*2     ;8255的B口地址
MY8255_C     EQU   IOY0+02H*2     ;8255的C口地址
MY8255_MODE  EQU   IOY0+03H*2     ;8255的控制寄存器地址

SSTACK	SEGMENT STACK
		DW 256 DUP(?)
SSTACK	ENDS
DATA	SEGMENT
TABDT	DB 01H,03H,02H,06H,04H,0CH,08H,09H  
DATA	ENDS
CODE	SEGMENT
		ASSUME CS:CODE, DS:DATA
START:	MOV AX, DATA
		MOV DS, AX
MAIN:	MOV AL, 90H			; 控制B口工作于方式0，输出
		MOV DX, MY8255_MODE
		OUT DX, AL
A1:		MOV BX, OFFSET TABDT
		MOV CX, 0008H
A2:		MOV	AL,[BX]   
		MOV DX, MY8255_B	; 写B口 
		OUT	DX, AL
		CALL DALLY			; 控制步进电机的转速 
		INC	BX 
		LOOP A2
		JMP	A1
DALLY:	PUSH CX 
		MOV CX,8000H
A3:		PUSH AX
		POP	AX
		LOOP A3
		POP	CX
		RET	
CODE	ENDS
		END START
