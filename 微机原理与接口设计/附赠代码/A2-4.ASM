;=========================================================
; 文件名:   A2-4.ASM
; 功能描述: 十六进制数转换为ASCII码
;=========================================================

SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK	ENDS

CODE	SEGMENT
		ASSUME CS:CODE

START:	MOV CX,0004H		
		MOV DI,3500H		;十六进制数源地址
		MOV DX,[DI]	
A1:		MOV AX,DX
		AND AX,000FH		;取低4位
		CMP AL,0AH
		JB A2				;小于0AH则转A2
		ADD AL,07H			;在A～FH之间，需多加上7H
A2:		ADD AL,30H			;转换为相应ASCII码
		MOV [DI+0DH],AL		;结果存入目标地址
		DEC DI
		PUSH CX
		MOV CL,04H
		SHR DX,CL			;将十六进制数右移4位
		POP CX
		LOOP A1
		MOV AX,4C00H
		INT 21H				;程序终止
CODE	ENDS
		END START