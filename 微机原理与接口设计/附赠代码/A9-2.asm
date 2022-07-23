;========================================================
; 文件名:   A9-2.ASM
; 功能描述: INT 21H功能调用示例程序
;========================================================
DATA1	SEGMENT
MES1	DB 'This is tangdu INT 21H !','$'
DATA1	ENDS					
;----------------------------------------------------------------------------
DATA2	SEGMENT
MES2	DB 0FFH DUP(?)
DATA2	ENDS					
;----------------------------------------------------------------------------
SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK	ENDS
;----------------------------------------------------------------------------
CODE	SEGMENT
		ASSUME CS:CODE
;----------------------------------------------------------------------------
START:
		MOV AH,08H
		INT 21H			;读键盘输入到AL中无回显

		MOV AH,01H
		INT 21H			;读键盘输入到AL中并回显

		CALL ENTERR

		MOV CX,04H
		MOV DL,41H
AA:		MOV AH,02H
		INT 21H
		INC DL
		LOOP AA			;将DL中的数据显示出来
	
		CALL ENTERR
	
		MOV AX,DATA1
		MOV DS,AX
		MOV DX,OFFSET MES1
		MOV AH,09H
		INT 21H			;显示数据段DATA1中的字符串

		CALL ENTERR

		MOV AX,DATA2
		MOV DS,AX
		MOV DX,OFFSET MES2
		MOV AH,0AH
		INT 21H			;读入字符串放到数据段DATA2中,以回车结束
	
		ADD DX,02H
		MOV AH,09H
		INT 21H			;将数据段DATA2中的字符串显示出来

		MOV AX,4C00H
		INT 21H			;程序终止

ENTERR:
		MOV AH,02H
		MOV DL,0DH
		INT 21H			;回车
		MOV AH,02H
		MOV DL,0AH
		INT 21H			;换行
		RET
;----------------------------------------------------------------------------
CODE	ENDS
		END START