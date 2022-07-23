;=========================================================
; 文件名:   A6-1.ASM
; 功能描述: 气泡法排序
;=========================================================

SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK	ENDS

CODE	SEGMENT
		ASSUME CS:CODE

START:	MOV CX, 000AH
		MOV SI, 300AH
		MOV BL, 0FFH
A1:		CMP BL, 0FFH
		JNZ A4
		MOV BL, 00H
		DEC CX
		JZ A4
		PUSH SI
		PUSH CX
A2:		DEC SI
		MOV AL, [SI]
		DEC SI
		CMP AL, [SI]
		JA A3
		XCHG AL, [SI]
		MOV [SI+01H], AL
		MOV BL, 0FFH
A3:		INC SI
		LOOP A2
		POP CX
		POP SI
		JMP A1
A4:		MOV AX,4C00H
		INT 21H					;程序终止
CODE	ENDS
		END START
