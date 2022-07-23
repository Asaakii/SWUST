;=================================================
; 文件名:   A8-1.ASM
; 功能描述: 通过查表的方法实现十六进制到BCD码
;           的转换
;=================================================
; 实验方法:
;   程序下载完成后，首先查看寄存器CS的值，根据CS的
;   值使用反汇编U命令查看DS的值，然后更改DS段3000H
;   处的值，即需转换的十六进制数，转换结果存放在
;   3001H(高4位)和3002H(低4位)中。
;=================================================

SSTACK	SEGMENT STACK
		DW 32 DUP(?)
SSTACK	ENDS

;=================================================
; 十六进制数0～9与A,B,C,D,E,F对应ASC码表
;=================================================
PUBLIC	ASCH, ASCL, HEX
DATA	SEGMENT
TAB		DB 30H,31H,32H,33H,34H,35H,36H,37H,38H,39H
		DB 41H,42H,43H,44H,45H,46H
HEX		DB ?
ASCH	DB ?
ASCL	DB ?
DATA	ENDS

CODE	SEGMENT
		ASSUME CS:CODE, DS:DATA
START:	PUSH DS
		XOR AX, AX
		MOV AX, DATA
		MOV DS, AX
AA1:	MOV AL, HEX			;需转换的十六进制数
		MOV AH, AL
		AND AL, 0F0H
		MOV CL, 04H
		SHR AL, CL
		MOV BX, OFFSET TAB		;表首地址存放于BX中
		XLAT
		MOV ASCH, AL			;存放十六进制数高4位的BCD码
		MOV AL, AH
		AND AL, 0FH
		XLAT
		MOV ASCL, AL			;存放十六进制数低4位的BCD码
		NOP
		JMP AA1
CODE	ENDS
		END START