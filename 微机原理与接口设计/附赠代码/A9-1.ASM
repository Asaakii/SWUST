;========================================================
; 文件名:   A9-1.ASM
; 功能描述: 使用INT 21H功能调用实现显示A--Z共26个字母
;========================================================

SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK	ENDS

CODE	SEGMENT
		ASSUME CS:CODE

START:	MOV CX,001AH
		MOV DL,41H
		MOV AL,DL
A1:		MOV AH,02H
		INT 21H				;功能调用
		INC DL
		PUSH CX
		MOV CX,0FFFFH
A2:		LOOP A2
		POP CX
		DEC CX
		JNZ A1
		MOV AX,4C00H
		INT 21H				;程序终止
CODE	ENDS
		END START