;=========================================================
; 文件名: ZHILIU.ASM
; 功能描述: 直流电机闭环调速实验，通过专用图形显示界面
;           观察实验现象。
;           IOY0--8255, IOY3--8254
;=========================================================

SSTACK	SEGMENT STACK
		DW 64 DUP(?)
		TOP	LABEL WORD
SSTACK	ENDS
DATA	SEGMENT
TS		DB 14H						;采样周期
SPEC	DW 0030H					;给定电机转速30H为48转/秒
IBAND	DW 0060H					;PID算法中积分分离值
KPP		DW 1060H					;PID算法中比例项系数值
KII		DW 0010H					;PID算法中积分项系数值
KDD		DW 0020H					;PID算法中微分项系数值
CH1		DB ?						;专用图形显示的CH1通道
CH2		DB ?						;专用图形显示的CH2通道
CH3		DB ?						;专用图形显示的CH3通道
YK		DW ?						;电机转速反馈量
CK		DB ?						;电机转速控制量
VADD	DW ?
ZV		DB ?
ZVV		DB ?
TC		DB ?
FPWM	DB ?
CK_1	DB ?
EK_1	DW ?
AEK_1	DW ?
BEK		DW ?
AAAA	DB ?
VAA		DB ?
BBB		DB ?
VBB		DB ?
MARK	DB ?
R0		DW ?
R1		DW ?
R2		DW ?
R3		DW ?
R4		DW ?
R5		DW ?
R6		DW ?
R7		DB ?
R8		DW ?
DATA	ENDS

CODE	SEGMENT
		ASSUME  CS:CODE,DS:DATA
START:	MOV AX,DATA
		MOV DS,AX
MAIN:	CALL INIT					;初始化
		STI
M1:		MOV AL, TS				;判断 Ts=Tc ?
		SUB AL, TC
		JNC M1
		MOV TC, 00H				;得到 Yk
		MOV AL, ZVV
		MOV AH, 00H
		MOV YK, AX
		CALL PID				;调用PID计算控制量 CK
		MOV AL, CK				;根据 CK 产生 PWM 脉冲
		SUB AL, 80H         
		JC  IS0
		MOV AAAA, AL
		JMP COU
IS0:	MOV AL, 10H
		MOV AAAA, AL   
COU:	MOV AL, 7FH
		SUB AL, AAAA
		MOV BBB, AL
		MOV AX, SPEC			;将给定量 SPEC 存入 CH1
		MOV CH1, AL
		MOV AX, YK				;将反馈量 YK 存入 CH2
		MOV CH2, AL
		MOV AL, CK				;将控制量CK 存入 CH3
		MOV CH3, AL
		CALL PUT_COM			;调用PUT_COM显示给定、反馈与控制量的波形
		JMP M1         
PUT_COM:MOV DX, 03FDH
WAIT1:	IN	AL, DX
		TEST AL, 20H
		JZ	WAIT1
		MOV DX, 03F8H
		MOV AL,CH2
		OUT DX, AL
		MOV DX, 03FDH
WAIT2:	IN	AL, DX
		TEST AL, 20H
		JZ	WAIT2
		MOV DX, 03F8H
		MOV	AL, CH1
		OUT	DX, AL
		MOV DX, 03FDH
WAIT3:	IN	AL, DX
		TEST AL, 20H
		JZ	WAIT3
		MOV DX, 03F8H
		MOV	AL, CH3
		OUT	DX, AL
		RET
INIT:	CLI
		PUSH DS
		XOR AX, AX
		MOV DS, AX
		MOV AX, OFFSET IRQ6		;8259 IRQ6(T0:1ms)
		MOV SI, 0038H            
		MOV [SI], AX
		MOV AX, CS
		MOV SI, 003AH
		MOV [SI], AX
		MOV AX, OFFSET IRQ7		;8259 IRQ7(INT0:HR-OUT,COUNT-VVV)
		MOV SI, 003CH
		MOV [SI], AX
		MOV AX, CS
		MOV SI, 003EH
		MOV [SI], AX
		POP DS
		MOV AL, 2FH				;允许 IRQ6,IRQ7
		OUT 21H, AL
		MOV VADD, 0000H			;变量初始化
		MOV ZV, 00H              
		MOV ZVV, 00H
		MOV CK, 00H
		MOV YK, 0000H
		MOV CK_1, 00H
		MOV EK_1, 0000H
		MOV AEK_1, 0000H
		MOV BEK, 0000H
		MOV BBB, 00H
		MOV VBB, 00H
		MOV R0, 0000H
		MOV R1, 0000H
		MOV R2, 0000H
		MOV R3, 0000H
		MOV R4, 0000H
		MOV R5, 0000H
		MOV R6, 0000H
		MOV R7, 00H
		MOV	R8, 0000H
		MOV MARK, 00H
		MOV FPWM, 01H
		MOV AAAA, 7FH
		MOV VAA, 7FH
		MOV TC, 00H
		MOV DX, 606H
		MOV AL, 90H				;初始化 8255-B口
		OUT DX, AL
		MOV DX, 602H
		MOV AL, 00H
		OUT DX, AL
		MOV DX, 6C6H
		MOV AL, 36H				;8254计数器0的输出OUT0
		OUT DX, AL
		MOV DX, 6C0H            
		MOV AL, 0E8H				;定时1ms
		OUT DX, AL
		MOV AL, 03H
		OUT DX, AL
		RET 
IRQ7:	NOP							;7号中断程序，计算转速
		PUSH AX
		PUSH BX
		PUSH CX
		PUSH DX
		PUSHF
		MOV AL,MARK  
		CMP AL,01H
		JZ 	IN1
		MOV MARK,01H 
IN2:	NOP
		MOV AL,20H        			;中断返回，关闭 IRQ7
		OUT 20H,AL
		POPF
		POP DX
		POP CX 
		POP BX
		POP AX
		IRET
IN1:	MOV MARK, 00H
		CALL VV
		MOV AL, ZV
		MOV ZVV, AL
		JMP IN2
VV:		MOV DX, 0000H				;计算电机转速
		MOV AX, 03E8H
		MOV CX, VADD
		CMP CX, 0000H
		JZ  MM1     
		DIV CX
MM:		MOV ZV, AL
		MOV VADD, 0000H     
MM1:	RET
IRQ6:	PUSH AX
		PUSH DX
		PUSHF
		INC TC
		CALL KJ
		CLC
		CMP MARK, 01H
		JC 	TT1
		INC VADD
		CMP VADD, 0700H				;转速值溢出，赋极值
		JC 	TT1
		MOV VADD, 0700H
		MOV MARK, 00H
TT1:	NOP
		MOV AL, 20H          		;中断返回，关闭 IRQ6
		OUT 20H, AL       
		POPF
		POP DX
		POP AX
		IRET
KJ:		NOP  						;PWM发生子程序
		PUSH AX
		CMP FPWM, 01H				;FPWM为1，产生PWM的高电平
		JNZ TEST2
		CMP VAA, 00H
		JNZ ANOT0
		MOV FPWM, 02H
		MOV AL, BBB
		CLC
		RCR AL, 01H
		MOV VBB, AL
		JMP TEST2
ANOT0:	DEC VAA
		MOV DX, 0602H				;输出高电平
		MOV AL, 01H
		OUT DX, AL
TEST2:	CMP FPWM, 02H				;FPWM为2，产生PWM的低电平
		JNZ OUTT
		CMP VBB, 00H
		JNZ BNOT0
		MOV FPWM, 01H
		MOV AL, AAAA
		CLC
		RCR AL, 01H
		MOV VAA, AL
		JMP OUTT
BNOT0:	DEC VBB
		MOV DX, 0602H				;输出低电平
		MOV AL, 00H
		OUT DX, AL  
OUTT:	POP AX
		RET       
;==============================================
;PID算法子程序
;根据SPEC, KPP, KII, KDD及YK计算对应控制量CK
;==============================================       
PID:	MOV AX, SPEC				;求偏差EK
		SUB AX, YK
		MOV R0, AX
		MOV R1, AX					;求偏差的变化量AEK
		SUB AX, EK_1
		MOV R2, AX
		SUB AX, AEK_1				;求BEK
		MOV	BEK, AX
		MOV R8, AX
		MOV AX, R1
		MOV EK_1, AX
		MOV AX, R2
		MOV AEK_1, AX
		TEST R1, 8000H
		JZ 	EK1
		NEG R1  
EK1:	MOV AX, R1				;根据积分分离值，判是否积分
		SUB AX, IBAND
		JC 	II 
		MOV R3, 00H	
		JMP DDD
II:		MOV AL, TS				;计算积分项的值
		MOV AH, 00H
		MOV CX, R1
		MUL CX
		MOV CX, KII
		DIV CX
		MOV R3, AX
		TEST R0, 8000H
		JZ 	DDD
		NEG R3
DDD:	TEST BEK, 8000H			;计算微分项的值
		JZ 	DDD1
		NEG BEK
DDD1:	MOV AX, BEK
		MOV CX, KDD
		MUL	CX
		PUSH AX
		PUSH DX
		MOV AL, TS				
		MOV AH, 00H				;将微分项缩小8倍，防止溢出
		MOV CX, 0008H
		MUL CX
		MOV CX, AX
		POP DX
		POP AX
		DIV CX
		MOV R4, AX
		TEST R8, 8000H
		JZ 	DD1
		NEG R4
DD1:	MOV AX, R3				;积分项和微分项相加，判溢出
		ADD AX, R4
		MOV R5, AX
		JO 	L9
L2:		MOV AX, R5
		ADD AX, R2
		MOV R6, AX
		JO 	L3 
L5:		MOV AX, R6				;计算比例项
		MOV CX, KPP
		IMUL CX
		MOV CX, 1000H
		IDIV CX
		MOV	CX, AX
		RCL	AH, 01H				
		PUSHF
		RCR	AL, 01H
		POPF
		JC	LLL1					;判溢出，溢出赋极值
		CMP	CH, 00H
		JZ	LLL2
		MOV	AL, 7FH
		JMP	LLL2
LLL1:	CMP	CH, 0FFH
		JZ	LLL2
		MOV	AL, 80H
LLL2:	MOV	R7, AL      			;CK=CK+CK_1
		ADD AL, CK_1
		JO 	L8
L18:	MOV CK_1, AL
		ADD AL, 80H
		MOV CK, AL
		RET							;PID子程序返回
L8:		TEST R7, 80H				;溢出处理程序
		JNZ L17
		MOV AL, 7FH
		JMP L18
L17:	MOV AL, 80H
		JMP L18               	
L9:		TEST R3, 8000H
		JNZ L1
		MOV	R5, 7FFFH
		JMP L2
L1:		MOV R5, 8000H
		JMP L2
L3:		TEST R2, 8000H
		JNZ L4
		MOV R6, 7FFFH
		JMP L5
L4:		MOV R6, 8000H
		JMP L5
CODE	ENDS
		END START     
