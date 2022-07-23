;=========================================================
; 文件名: A82592.ASM
; 功能描述: 8259中断优先级应用实验
;=========================================================

SSTACK	SEGMENT STACK
		DW 32 DUP(?)
SSTACK	ENDS

CODE   	SEGMENT
	   	ASSUME CS:CODE
START: 	PUSH DS
		MOV AX, 0000H
		MOV DS, AX
		MOV AX, OFFSET MIR7		;取中断入口地址
		MOV SI, 003CH			;中断矢量地址
		MOV [SI], AX			;填IRQ7的偏移矢量
		MOV AX, CS				;段地址
		MOV SI, 003EH
		MOV [SI], AX			;填IRQ7的段地址矢量
		MOV AX, OFFSET MIR6
		MOV SI, 0038H
		MOV [SI], AX
		MOV AX, CS
		MOV SI, 003AH
		MOV [SI], AX
		CLI
		POP DS
		;初始化主片8259
		MOV AL, 11H
		OUT 20H, AL				;ICW1
		MOV AL, 08H
		OUT 21H, AL				;ICW2
		MOV AL, 04H
		OUT 21H, AL				;ICW3
		MOV AL, 01H
		OUT 21H, AL				;ICW4
		MOV AL, 2FH
		OUT 21H, AL				;主8259 OCW1
		STI
AA1:	NOP
		JMP AA1
MIR7:	STI
		CALL DELAY
		MOV AX, 0137H
		INT 10H					;显示字符7
		MOV AX, 0120H
		INT 10H
		MOV AL, 20H
		OUT 20H, AL				;中断结束命令
		IRET
MIR6:	STI
		CALL DELAY
		MOV AX, 0136H
		INT 10H					;显示字符6
		MOV AX, 0120H
		INT 10H
		MOV AL, 20H
		OUT 20H, AL
		IRET
DELAY:	PUSH CX
		MOV CX, 0F000H
AA0:	PUSH AX
		POP  AX
		LOOP AA0
		POP CX
		RET
CODE	ENDS
		END  START
