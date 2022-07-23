;============================================================
; 文件名称: LED16.ASM 
; 功能描述: 
;     行: CS1(600H), CS2(640H)  列: CS3(680H), CS4(6C0H)
;============================================================
ROW1		EQU 0600H			;端口定义IOY0
ROW2		EQU 0640H			;端口定义IOY1
COL1		EQU 0680H			;端口定义IOY2
COL2		EQU 06C0H			;端口定义IOY3
STACK1	SEGMENT STACK
		DW 256 DUP(?)
STACK1	ENDS
;定义为数据段
INCLUDE HZDOTht.ASM			;数据字段为汉字点阵库, 在HZDOTht.ASM文件中		
CODE	SEGMENT
		ASSUME	CS:CODE, DS:DATA
START:	MOV AX, DATA
		MOV DS, AX
		MOV DX, ROW1
		MOV AL, 00H
		OUT DX, AL
		MOV DX, ROW2
		OUT DX, AL
		MOV AL, 0ffH
		MOV DX, COL1
		OUT DX, AL
		MOV DX, COL2
		OUT DX, AL

BG0:	MOV AX, 160
		MOV SI, OFFSET HZDOTht
BG1:	CALL DISP
		ADD SI, 2
		DEC AX
		JZ BG0
		JMP BG1
;======显示汉字子程序======
;入口参数: SI = 存放汉字起始地址	
DISP:	MOV CX, 000FH
		PUSH AX		
ML0:	PUSH CX
		MOV BL, 01H
		MOV CX, 0008H
ML1:	MOV DX, ROW1			;控制0--7行
		MOV AL, 00H
		OUT DX, AL
		MOV AL, [SI]
		NOT AL
		MOV DX, COL1			;0--7列
		OUT DX, AL
		INC SI
		MOV AL, [SI]
		NOT AL
		MOV DX, COL2			;8--15列
		OUT DX, AL
		INC SI
		MOV DX, ROW1			;控制0--7行
		MOV AL, BL
		OUT DX, AL
		ROL BL, 1
		
		CALL DELAY
		LOOP ML1
		MOV DX, ROW1
		MOV AL, 00H
		OUT DX, AL
		MOV CX, 0008H
ML2:	MOV DX, ROW2			;控制8--15行
		MOV AL, 00H
		OUT DX, AL
		MOV AL, [SI]
		NOT AL
		MOV DX, COL1			;0--7列
		OUT DX, AL
		INC SI
		MOV AL, [SI]
		NOT AL
		MOV DX, COL2			;8--15列
		OUT DX, AL
		INC SI
		MOV DX, ROW2			;控制8--15行
		MOV AL, BL
		OUT DX, AL
		ROL BL, 1
		CALL DELAY
		LOOP ML2
		MOV DX, ROW2
		MOV AL, 00H
		OUT DX, AL
		SUB SI, 32
		POP CX
		LOOP ML0
		POP AX
		RET	
DELAY:	PUSH CX				;延时子程序
		MOV CX, 0100H
DL1:	PUSH AX
		POP AX
		LOOP DL1
		POP CX
		RET		
		
CODE	ENDS
		END START

