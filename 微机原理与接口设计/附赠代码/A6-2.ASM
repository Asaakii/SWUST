;========================================================
; 文件名:   A6-2.ASM
; 功能描述: 实现学生成绩名次表
;========================================================

SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK		ENDS

CODE	SEGMENT
		ASSUME CS:CODE

START:	MOV AX,0000H
		MOV DS,AX
		MOV ES,AX
		MOV SI,3000H		;存放学生成绩
		MOV CX,000AH		;共10个成绩
		MOV DI,3100H		;名次表首地址
A1:		CALL BRANCH			;调用子程序
		MOV AL,0AH
		SUB AL,CL
		INC AL
		MOV BX,DX
		MOV [BX+DI],AL
		LOOP A1
		MOV AX,4C00H
		INT 21H					;程序终止

;===扫描成绩表，得到最高成绩者的学号===
BRANCH: PUSH CX
		MOV CX,000AH
		MOV AL,00H
		MOV BX,3000H
		MOV SI,BX
A2:		CMP AL,[SI]
		JAE A3
		MOV AL,[SI]
		MOV DX,SI
		SUB DX,BX
A3:		INC SI
		LOOP A2
		ADD BX,DX
		MOV AL,00H
		MOV [BX],AL
		POP CX
		RET	
CODE	ENDS
		END START
