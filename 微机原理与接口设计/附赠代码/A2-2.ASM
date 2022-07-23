;====================================================
; 文件名:   A2-2.ASM
; 功能描述: 将十进制数的ASCII码转换为BCD码
;====================================================

SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK	ENDS

CODE	SEGMENT
		ASSUME CS:CODE

START:	MOV CX, 0005H			;转换位数
		MOV DI, 3500H			;ASCII码首地址
A1:		MOV BL, 0FFH			;将错误标志存入BL
		MOV AL, [DI]
		CMP AL, 3AH
	 	JNB A2					;不低于3AH则转A2
		SUB AL, 30H
		JB  A2					;低于30H则转A2
		MOV BL, AL
A2:		MOV AL, BL				;结果或错误标志送入AL
		MOV [DI+0AH],AL			;结果存入目标地址
		INC DI
		LOOP A1
		MOV AX,4C00H
		INT 21H					;程序终止
CODE	ENDS
		END START