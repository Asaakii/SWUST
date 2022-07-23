;=========================================================
; 文件名: A82593.ASM
; 功能描述: 8259级联中断实验，中断源为主片8259的IR7，
;           从片8259的IR1。从片8259通过主片8259的IR2
;           进行级联。
;           主片每产生一次中断输出显示一个字符M7，从片
;           每产生一次中断输出显示一个字符S1。
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
		MOV AX, OFFSET SIR1
		MOV SI, 00C4H
		MOV [SI], AX
		MOV AX, CS
		MOV SI, 00C6H
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
		;初始化从片8259
		MOV AL, 11H
		OUT 0A0H, AL			;ICW1
		MOV AL, 30H
		OUT 0A1H, AL			;ICW2
		MOV AL, 02H				
		OUT 0A1H, AL			;ICW3
		MOV AL, 01H
		OUT 0A1H, AL			;ICW4
		MOV AL, 0FDH
		OUT 0A1H,AL				;OCW1 = 1111 1101		
		MOV AL, 6BH
		OUT 21H, AL				;主8259 OCW1
		STI
AA1:	NOP
		JMP AA1
MIR7:	STI
		CALL DELAY
		MOV AX, 014DH
		INT 10H					;显示字符M
		MOV AX, 0137H
		INT 10H					;显示字符7
		MOV AX, 0120H
		INT 10H
		MOV AL, 20H
		OUT 20H, AL				;中断结束命令
		IRET
SIR1:	STI
		CALL DELAY
		MOV AX, 0153H
		INT 10H					;显示字符S
		MOV AX, 0131H
		INT 10H					;显示字符1
		MOV AX, 0120H
		INT 10H
		MOV AL, 20H
		OUT 0A0H, AL
		OUT 20H, AL
		IRET
DELAY:	PUSH CX
		MOV CX, 0F00H
AA0:	PUSH AX
		POP  AX
		LOOP AA0
		POP CX
		RET
CODE	ENDS
		END  START
