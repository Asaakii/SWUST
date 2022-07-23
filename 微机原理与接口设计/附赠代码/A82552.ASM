;=========================================================
; 文件名: A82552.ASM
; 功能描述: A口为输出，B口为输出，流水灯显示
;=========================================================

IOY0         EQU   0600H          ;片选IOY0对应的端口始地址
MY8255_A     EQU   IOY0+00H*2     ;8255的A口地址
MY8255_B     EQU   IOY0+01H*2     ;8255的B口地址
MY8255_C     EQU   IOY0+02H*2     ;8255的C口地址
MY8255_MODE  EQU   IOY0+03H*2     ;8255的控制寄存器地址

SSTACK	SEGMENT STACK
		DW 32 DUP(?)
SSTACK	ENDS
CODE	SEGMENT
		ASSUME CS:CODE
START:	MOV DX, MY8255_MODE
		MOV AL, 80H
		OUT DX, AL
		MOV BX, 8001H
AA1:	MOV DX, MY8255_A
		MOV AL, BH
		OUT DX, AL
		ROR BH, 1
		MOV DX, MY8255_B
		MOV AL, BL
		OUT DX, AL
		ROL BL, 1	
		CALL DELAY
		CALL DELAY
		JMP AA1
DELAY:	PUSH CX
		MOV CX, 0F000H
AA2:	PUSH AX
		POP  AX
		LOOP AA2
		POP  CX
		RET
CODE	ENDS
		END  START
