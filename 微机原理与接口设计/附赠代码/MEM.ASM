;=========================================================
; 文件名: MEM.ASM
; 功能描述: 扩展存储器实验，访问16位存储器，将16个数写入
;           从8000:0000H开始的连续地址单元，然后使用D命令查看
;           数据是否被正确写入
;=========================================================

SSTACK	SEGMENT STACK
		DW 32 DUP(?)
SSTACK	ENDS
CODE	SEGMENT
START	PROC FAR
		ASSUME CS:CODE	  
		MOV AX, 8000H		; 存储器扩展空间段地址
		MOV DS, AX
AA0:	MOV SI, 0000H		; 数据首地址
		MOV CX, 0010H
		MOV AX, 0000H
AA1:	MOV [SI], AX
		INC AX
		INC SI
		INC SI
		LOOP AA1
		MOV AX,4C00H
		INT 21H			;程序终止
START	ENDP
CODE	ENDS
		END START
