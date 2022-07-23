;=========================================================
; 文件名: DA08322.ASM
; 功能描述: 利用DA0832产生方波，通过延时变化波形
;=========================================================

IOY0         EQU   0600H 
DA0832       EQU   IOY0+00H*2	

SSTACK	SEGMENT STACK
		DW 32 DUP(?)
SSTACK	ENDS
CODE	SEGMENT
		ASSUME CS:CODE
START:	MOV AX, 00H				; 产生方波
		MOV DX, DA0832
AA1:	MOV AL, 00H
		OUT DX, AL
		CALL DELAY
		MOV AL, 7FH
		OUT DX, AL
		CALL DELAY
		JMP AA1
DELAY:	PUSH CX
		MOV CX,0FF00H
AA2:	PUSH AX
		POP  AX
		LOOP AA2
		POP CX
		RET
CODE	ENDS
		END START
