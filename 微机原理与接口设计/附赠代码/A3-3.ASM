;=====================================================
; 文件名:   A3-3.ASM
; 功能描述: 乘法运算
;=====================================================

SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK	ENDS

DATA	SEGMENT
DATA1 	DB 5 DUP(?)			;被乘数
DATA2 	DB ?				;乘数
RESULT 	DB 6 DUP(?)			;计算结果
DATA	ENDS
	
CODE	SEGMENT
		ASSUME CS:CODE,DS:DATA

START:  MOV AX,DATA
		MOV DS,AX
		CALL INIT				;初始化目标地址单元为0
		MOV SI,OFFSET DATA2
		MOV BL,[SI]
		AND BL,0FH				;得到乘数
		CMP BL,09H
		JNC ERROR
		MOV SI,OFFSET DATA1
		MOV DI,OFFSET RESULT
		MOV CX,0005H
A1:		MOV AL,[SI+04H]
		AND AL,0FH
		CMP AL,09H
		JNC ERROR
		DEC SI
		MUL BL
		AAM						;乘法调整指令
		ADD AL,[DI+05H]
		AAA
		MOV [DI+05H],AL
		DEC DI
		MOV [DI+05H],AH	
		LOOP A1
A2:		MOV AX,4C00H
		INT 21H					;程序终止

;===将RESULT所指内存单元清零===
INIT:	MOV SI,OFFSET RESULT
		MOV CX,0003H
		MOV AX,0000H
A3:		MOV [SI],AX
		INC SI
		INC SI
		LOOP A3
		RET 

;===错误处理===
ERROR:  MOV SI,OFFSET RESULT	;若输入数据不符合要求
		MOV CX,0003H			;则RESULT所指向内存单
		MOV AX,0EEEEH			;元全部写入E
A4:		MOV [SI],AX
		INC SI
		INC SI
		LOOP A4
		JMP A2
CODE 	ENDS
		END	START		