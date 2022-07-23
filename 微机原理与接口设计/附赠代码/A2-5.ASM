;========================================================
; 文件名:   A2-5.ASM
; 功能描述: BCD码转换为二进制数
;========================================================

SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK	ENDS

CODE	SEGMENT
		ASSUME CS:CODE

START:	XOR AX, AX
		MOV CX, 0004H
		MOV SI, 3500H
		MOV DI, 3510H
A1:		MOV AL, [SI]
		ADD AL, AL
		MOV BL, AL
		ADD AL, AL
		ADD AL, AL
		ADD AL, BL
		INC SI
		ADD AL, [SI]
		MOV [DI], AL
		INC SI
		INC DI
		LOOP A1
		MOV AX,4C00H
		INT 21H				;程序终止
CODE	ENDS
		END START