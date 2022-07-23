;=========================================================
; 文件名: AD0809.ASM
; 功能说明: 进行AD采样，将结果显示。 片选为IOY0
;=========================================================

IOY0         EQU   0600H 
AD0809       EQU   IOY0+00H*2		;AD0809的端口地址

SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK	ENDS
PUBLIC	VALUE				;设置全局变量以便变量监视
DATA	SEGMENT
VALUE	DB ?				;AD转换结果
DATA	ENDS
CODE	SEGMENT
		ASSUME CS:CODE, DS:DATA
START:	MOV AX, DATA
		MOV DS, AX
		MOV DX, AD0809		;启动AD采样
		OUT DX, AL
		CALL DALLY
		IN  AL, DX			;读AD采样结果
		MOV VALUE, AL		;将结果送变量
		JMP START			;在此处设置断点, 观察变量窗口中的VALUE值
DALLY:	PUSH CX				;延时程序
		PUSH AX
		MOV CX, 100H
A5:		MOV AX, 0800H
A6:		DEC AX
		JNZ A6
		LOOP A5
		POP AX
		POP CX
		RET	
CODE	ENDS
		END START

