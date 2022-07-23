;========================================================
; 文件名:   Wmd861.Asm
; 功能描述: 初始化内存3000H地址单元开始的16个字节，内容
;           为0～15共16个数据。
;========================================================
; 实验目的: 本实验为系统认识实验，目的在于通过该实验来
;           学习实验系统的使用。
;========================================================

SSTACK	SEGMENT STACK				;定义堆栈段
		DW 32 DUP(?)
SSTACK	ENDS

CODE	SEGMENT
		ASSUME CS:CODE, SS:SSTACK
START:	PUSH DS
		XOR AX, AX
		MOV DS, AX
		MOV SI, 3000H				;建立数据起始地址
		MOV CX, 16					;循环次数
AA1:	MOV [SI], AL
		INC SI						;地址自加1
		INC AL						;数据自加1
		LOOP AA1
		MOV AX,4C00H
		INT 21H						;程序终止
CODE	ENDS
		END START
	