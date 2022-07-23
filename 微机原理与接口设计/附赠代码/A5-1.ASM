;======================================================
; 文件名:   A5-1.ASM
; 功能描述: 计算S=1+2×3+3×4+4×5+...+N(N+1),
;           直到N(N+1)项大于200为止。
;======================================================

SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK	ENDS

CODE	SEGMENT
		ASSUME CS:CODE

START:	MOV DX,0001H
		MOV BL,02H
A1:		MOV AL,BL
		INC BL
		MUL BL
		ADD DX,AX			;结果存于DX中
		CMP AX,00C8H		;判断N(N+1)与200的大小
		JNA A1
		MOV AX,4C00H
		INT 21H					;程序终止
CODE	ENDS
		END START

