;=========================================================
; 文件名:   A5-2.ASM
; 功能描述: 求某数据区内负数的个数
;=========================================================

SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK	ENDS

CODE	SEGMENT
		ASSUME CS:CODE

START:	MOV DI, 3000H			;数据区首地址
		MOV CL, [DI]			;取数据个数
		XOR CH, CH
		MOV BL, CH
		INC DI					;指向第一个数据
A1:		MOV AL, [DI]
		TEST AL, 80H			;检查数据首位是否为1
		JE A2
		INC BL					;负数个数加1
A2:		INC DI
		LOOP A1
		MOV [DI], BL			;保存结果
		MOV AX,4C00H
		INT 21H					;程序终止
CODE	ENDS
		END START
