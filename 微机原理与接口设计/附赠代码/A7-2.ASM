;========================================================
; 文件名:   A7-2.ASM
; 功能描述: 求N!
;========================================================

SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK	ENDS

PUBLIC	N, RESULT		;设置全局变量
DATA	SEGMENT
N		DB ?			;N的范围在1～8之间
RESULT	DW ?			;N!的结果存于该变量中
DATA	ENDS

CODE	SEGMENT
		ASSUME CS:CODE, DS:DATA

START:	MOV AX, DATA
		MOV DS, AX
		MOV AX, OFFSET RESULT
		PUSH AX
		MOV AL, N
		MOV AH, 00H
		PUSH AX
		MOV DI, 0000H
		CALL branch
		JMP START			;在此处设置断点，观察变量
;===子程序===
branch:	PUSH BP
		MOV BP,SP
		PUSH BX
		PUSH AX
		MOV BX,[BP+DI+06H]
		MOV AX,[BP+DI+04H]
		CMP AX,0000H
		JZ A1
		PUSH BX
		DEC AX
		PUSH AX
		CALL branch				;递归调用
		MOV BX,[BP+DI+06H]
		MOV AX,[BX]
		PUSH BX
		MOV BX,[BP+DI+04H]
		MUL BX
		POP BX
		JMP A2
A1:		MOV AX, 0001H
A2:		MOV RESULT, AX
		POP AX
		POP BX	 
		POP BP
		RET 0004H
CODE	ENDS
		END START