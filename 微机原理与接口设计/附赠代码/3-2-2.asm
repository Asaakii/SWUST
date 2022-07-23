;========================================================
; 文件名:3-2-2.asm
; 功能描述: 32位寄存器和32位指令使用的基本用法，
;			将一组ASCII字符转换成16进制数码，并在屏幕上显示出来。
;========================================================

.386P
TSTACK	SEGMENT	STACK	USE16 
	DB	64	DUP(?)
TSTACK	ENDS

DATA	SEGMENT	USE16
MES0	DB	'This is tangdu speaking!','$'
MES1	DB	'Show this sentence as hex:$'
;54,68,69,73,20,74,61,6E,67,64,75,20,73,70,65,61,6B,69,6E,67,21
BUF	DB	65	DUP(?)
DATA	ENDS

CODE	SEGMENT	USE16
		ASSUME	CS:CODE,DS:DATA
START:	MOV 	AX,DATA
		MOV		DS,AX
		MOV		DX,OFFSET MES0	;Show "This is tangdu speaking!"
		MOV		AH,09H
		INT 	21H
		CALL	KENTER			
		MOV		DX,OFFSET MES1	;Show Sentence as hex
		MOV		AH,09H
		INT 	21H
		CALL	KENTER	
		CALL	SAHEX
		MOV		DX,OFFSET BUF
		MOV		AH,09H
		INT 	21H
		CALL	KENTER			
		MOV 	AX,4C00H
		INT 	21H				;程序终止
SAHEX	PROC	NEAR
CBYTE	=24	
		PUSHAD					;将所有32位寄存器压栈
		MOV		DI,OFFSET MES0
		MOVZX	EDI,DI			;零扩展指令
		MOV		AX,DATA
		MOV		GS,AX			;使用GS段
		MOV		SI,OFFSET BUF
		MOVZX	ESI,SI
		MOV		ECX,CBYTE
C1:		MOV		AL,DS:[EDI]
		AND		AL,0F0H			;取高4位
		SHR		AL,4
		CMP		AL,0AH			;是否是A以上的数
		JB		C2		
		ADD		AL,07H		
C2:		ADD		AL,30H		
		MOV		GS:[ESI],AL
		MOV		AL,DS:[EDI]
		AND		AL,0FH			;取低4位
		CMP		AL,0AH
		JB		C3
		ADD 	AL,07H
C3:		ADD		AL,30H
		MOV		GS:[ESI+1],AL
		MOV		BYTE PTR GS:[ESI+2],20H	;在每个字符间加入空格
		ADD		ESI,3
		INC		EDI
		LOOP	C1
		
		MOV     AL,'$'
		MOV     GS:[ESI],AL
		
		POPAD					;弹出所有寄存器值
		RET
SAHEX	ENDP

KENTER	PROC	NEAR
		MOV 	AH,02H
		MOV 	DL,0DH
		INT 	21H				;回车
		MOV 	AH,02H
		MOV 	DL,0AH
		INT 	21H				;换行
		RET
KENTER	ENDP
CODE	ENDS
		END		START