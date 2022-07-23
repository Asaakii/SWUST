;=========================================================
; 文件名: A82553.ASM
; 功能描述: 本实验使8255端口A工作在方式0并作为输出口，
;           端口B工作在方式1并作为输入口
;=========================================================

IOY0         EQU   0600H          ;片选IOY0对应的端口始地址
MY8255_A     EQU   IOY0+00H*2     ;8255的A口地址
MY8255_B     EQU   IOY0+01H*2     ;8255的B口地址
MY8255_C     EQU   IOY0+02H*2     ;8255的C口地址
MY8255_MODE  EQU   IOY0+03H*2     ;8255的控制寄存器地址

STACK1 	SEGMENT STACK
        DW 256 DUP(?)
STACK1 	ENDS
CODE 	SEGMENT
        ASSUME CS:CODE
START: 	MOV DX,MY8255_MODE         ;初始化8255工作方式
       	MOV AL,86H                 ;工作方式1，A口输出，B口输入
       	OUT DX,AL
       	MOV DX,MY8255_MODE         ;C口PC2置位
       	MOV AL,05H                 
       	OUT DX,AL
		PUSH DS
		MOV AX, 0000H
		MOV DS, AX
		MOV AX, OFFSET MIR7			;取中断入口地址
		MOV SI, 003CH				;中断矢量地址
		MOV [SI], AX				;填IRQ7的偏移矢量
		MOV AX, CS					;段地址
		MOV SI, 003EH
		MOV [SI], AX				;填IRQ7的段地址矢量
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
		MOV AL, 6FH				;OCW1
		OUT 21H, AL
		STI       
AA1:	NOP
		JMP AA1
MIR7:  	PUSH AX
       	MOV DX,MY8255_B            ;读B口
       	IN  AL,DX
       	MOV DX,MY8255_A            ;写A口
       	OUT DX,AL
	   	MOV AL,20H
       	OUT 20H,AL       
       	POP AX  
       	IRET  
DELAY:	PUSH CX
		MOV CX, 0F00H
AA0:	PUSH AX
		POP  AX
		LOOP AA0
		POP CX
		RET
CODE 	ENDS
     	END START
