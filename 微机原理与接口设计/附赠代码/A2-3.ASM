;=======================================================
; 文件名:   A2-3.ASM
; 功能描述: 将十六位二进制数转换为ASCII码表示的十进制数
;=======================================================

SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK	ENDS

CODE	SEGMENT
		ASSUME CS:CODE

START:	MOV SI,3500H		;源数据地址
		MOV DX,[SI]
		MOV SI,3515H		;目标数据地址
A1:		DEC SI
		MOV AX,DX
		MOV DX,0000H
		MOV CX,000AH		;除数10
		DIV CX				;得商送AX, 得余数送DX
		XCHG AX,DX
		ADD AL,30H			;得Di得ASCII码
		MOV [SI],AL			;存入目标地址
		CMP DX,0000H
		JNE A1				;判断转换结束否，未结束则转A1
A2:		CMP SI,3510H		;与目标地址得首地址比较
		JZ A3				;等于首地址则转A3，否则将剩余地址
		DEC SI				;中填30H
		MOV AL,30H
		MOV [SI],AL
        JMP A2
A3:    	MOV AX,4C00H
		INT 21H				;程序终止

CODE	ENDS
		END START