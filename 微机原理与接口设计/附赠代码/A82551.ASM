;=========================================================
; 文件名: A82551.ASM
; 功能描述: A口为输入，B口为输出，将读入的数据输出显示
;           IOY0
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
		MOV AL, 82H
		OUT DX, AL
AA1:	MOV DX, MY8255_B
		IN  AL, DX
		CALL DELAY
		MOV DX, MY8255_A
		OUT DX, AL
		JMP AA1
DELAY:	PUSH CX
		MOV CX, 0F00H
AA2:	PUSH AX
		POP  AX
		LOOP AA2
		POP  CX
		RET
CODE	ENDS
		END  START
