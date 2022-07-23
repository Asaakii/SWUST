;数据块间搬移程序


SSTACK	SEGMENT STACK
		DW 64 DUP(?)	;字
SSTACK	ENDS

CODE	SEGMENT
		ASSUME CS:CODE

START:	MOV CX, 0010H	;搬移字节数CX=10H
		MOV SI, 1234H	;源数据块首地址SI=3100H
		MOV DI, 4321H	;目的块首地址DI=3200H
		CMP SI, DI	;SI-DI
		JA A2	;源数据块首地址SI>目的块首地址DI,到A2
				;源数据块首地址SI<目的块首地址DI,往下
		
		ADD SI, CX	;SI=3100H+10H=3110H
		ADD DI, CX	;DI=3200H+10H=3110H
		DEC SI	;
		DEC DI	;
		
A1:		MOV AL, [SI]
		MOV [DI], AL	;SI的内容给DI
		DEC SI
		DEC DI	;下一字节
		DEC CX
		JNE A1	;没完继续A1
		JMP A3	;否则去A3
		
A2:		MOV AL, [SI]
		MOV [DI], AL	;SI的内容给DI
		INC SI
		INC DI	;下一字节
		DEC CX
		JNE A2	;没完继续A2，否则往下走
		
A3:		MOV AX,4C00H
		INT 21H					;程序终止
CODE	ENDS
		END START