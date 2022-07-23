;=====================================================
; 文件名:   A7-1.asm
; 功能描述: 子程序实验，利用子程序求一组数中的最大
;           值和最小值
;=====================================================
; 实验方法:
;   使用E0000:3000命令，改变连续8个地址单元的值，然后
;   运行程序，再点击停止，查看AX寄存器中的内容，AH中
;   为最大值，AL中为最小值。
;=====================================================

SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK	ENDS

CODE	SEGMENT
		ASSUME CS:CODE

START:	MOV AX, 0000H
		MOV DS, AX
		MOV SI, 3000H		; 数据区首址
		MOV CX, 0008H
		CALL BRANCH			; 调用子程序
HERE:	JMP HERE
;======================================================
; 子程序，出口参数在AX中
;======================================================
BRANCH	PROC NEAR
		JCXZ A4
		PUSH SI
		PUSH CX
		PUSH BX
		MOV BH, [SI]
		MOV BL, BH
		CLD
A1:		LODSB
		CMP AL, BH
		JBE A2
		MOV BH, AL
		JMP A3
A2:		CMP AL, BL
		JAE A3
		MOV BL, AL
A3:		LOOP A1
		MOV AX, BX
		POP BX
		POP CX
		POP SI
A4:		RET
BRANCH	ENDP
CODE 	ENDS
		END START