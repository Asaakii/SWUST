;=========================================================
; 文件名: DA08321.ASM
; 功能描述: 利用DA0832产生锯齿波，通过延时变化波形
;=========================================================

IOY0         EQU   0600H 
DA0832       EQU   IOY0+00H*2	

SSTACK	SEGMENT STACK
		DW 32 DUP(?)
SSTACK	ENDS
CODE	SEGMENT
ASSUME	CS:CODE, SS:SSTACK
START:	MOV AX, 00H				; 产生锯齿波
		MOV DX, DA0832
		MOV AL, 00H
AA1:	OUT DX, AL
		CALL DELAY
		INC AL
		JMP AA1	   
DELAY:	PUSH CX
		MOV CX, 03FFH
AA2:	PUSH AX
		POP  AX
		LOOP AA2
		POP CX
		RET  
CODE	ENDS
		END START
