;=========================================================
; 文件名: A82542.ASM
; 功能描述: 产生1s方波，输入时钟为1MHz，使用计数器0和1
;           计数初值均为03E8H
;=========================================================

IOY0	 EQU  0600H        		;IOY0起始地址
A8254    EQU  IOY0+00H*2
B8254    EQU  IOY0+01H*2
C8254    EQU  IOY0+02H*2
CON8254  EQU  IOY0+03H*2

SSTACK	SEGMENT STACK
		DW 32 DUP(?)
SSTACK	ENDS

CODE	SEGMENT
		ASSUME CS:CODE
START:	MOV DX, CON8254			;8254
		MOV AL, 36H				;计数器0，方式3
		OUT DX, AL
		MOV DX, A8254
		MOV AL, 0E8H
		OUT DX, AL
		MOV AL, 03H
		OUT DX, AL
		MOV DX, CON8254			;8254
		MOV AL, 76H				;计数器1，方式3
		OUT DX, AL
		MOV DX, B8254
		MOV AL, 0E8H
		OUT DX, AL
		MOV AL, 03H
		OUT DX, AL
AA1:	JMP AA1
CODE	ENDS
		END  START
