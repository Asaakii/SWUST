;========================================================
; 文件名: A82371.ASM
; 功能描述: 8237DMA传送实验，源地址为1000H，目标地址为
;     0000H，通过E命令改变8000:2000连续10个存储单元的值，
;     运行程序后，通过D8000:0000查看传送结果。
;========================================================

IOY0         EQU  0600H        ;IOY0起始地址
MY8237_0     EQU  IOY0+00H*2   ;通道0当前地址寄存器 
MY8237_1     EQU  IOY0+01H*2   ;通道0当前字节计数寄存器
MY8237_2     EQU  IOY0+02H*2   ;通道1当前地址寄存器
MY8237_3     EQU  IOY0+03H*2   ;通道1当前字节计数寄存器
MY8237_8     EQU  IOY0+08H*2   ;写命令寄存器/读状态寄存器
MY8237_9     EQU  IOY0+09H*2   ;请求寄存器
MY8237_B     EQU  IOY0+0BH*2   ;工作方式寄存器
MY8237_D     EQU  IOY0+0DH*2   ;写总清命令/读暂存寄存器
MY8237_F     EQU  IOY0+0FH*2   ;屏蔽位寄存器 

STACK	SEGMENT STACK
	DW 64 DUP(?)
STACK	ENDS
CODE	SEGMENT
		ASSUME CS:CODE
START:	MOV AL, 00
		MOV DX, MY8237_D	
		OUT DX, AL				;写总清命令
AA1:	MOV AL, 00H
		MOV DX, MY8237_0		;写通道0当前地址寄存器
		OUT DX,AL
		MOV AL,10H
		OUT DX,AL
		MOV AL,00H	
		MOV DX, MY8237_2		;写通道1当前地址寄存器
		OUT DX,AL
		MOV AL,00H
		OUT DX,AL
		MOV AL,0AH
		MOV DX, MY8237_1		;写通道0当前字节计数寄存器
		OUT DX,AL
		MOV AL,00H
		OUT DX,AL
		MOV AL,0AH
		MOV DX, MY8237_3		;写通道1当前字节计数寄存器
		OUT DX,AL
		MOV AL,00H
		OUT DX,AL
		MOV AL,88H
		MOV DX, MY8237_B		;写通道0工作方式寄存器
		OUT DX,AL
		MOV AL,85H				;写通道1工作方式寄存器   
		OUT DX,AL
		MOV AL,81H
		MOV DX, MY8237_8		;写命令寄存器
		OUT DX,AL
		MOV AL,04H
		MOV DX, MY8237_9		;写请求寄存器
		OUT DX,AL
		MOV AL,00H
		MOV DX, MY8237_F		;写屏蔽位寄存器
		OUT DX,AL
		MOV AX,4C00H
		INT 21H					;程序终止
CODE 	ENDS
     	END START
