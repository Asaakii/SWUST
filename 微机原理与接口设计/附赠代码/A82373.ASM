;========================================================
; 文件名: A82373.ASM
; 功能描述: 8237DMA传送实验，存储器-IO
;========================================================

IOY0         EQU  0600H        	;IOY0起始地址
IOY1         EQU  0640H        	;IOY1起始地址
MY8237_0     EQU  IOY0+00H*2   	;通道0当前地址寄存器 
MY8237_1     EQU  IOY0+01H*2   	;通道0当前字节计数寄存器
MY8237_2     EQU  IOY0+02H*2   	;通道1当前地址寄存器
MY8237_3     EQU  IOY0+03H*2   	;通道1当前字节计数寄存器
MY8237_8     EQU  IOY0+08H*2   	;写命令寄存器/读状态寄存器
MY8237_9     EQU  IOY0+09H*2   	;请求寄存器
MY8237_B     EQU  IOY0+0BH*2   	;工作方式寄存器
MY8237_D     EQU  IOY0+0DH*2   	;写总清命令/读暂存寄存器
MY8237_F     EQU  IOY0+0FH*2   	;屏蔽位寄存器 
MY8255_A     EQU  IOY1+00H*2   	;8255的A口地址
MY8255_B     EQU  IOY1+01H*2   	;8255的B口地址
MY8255_C     EQU  IOY1+02H*2   	;8255的C口地址
MY8255_MODE  EQU  IOY1+03H*2   	;8255的控制寄存器地址

STACK1 	SEGMENT STACK
        DW 256 DUP(?)
STACK1 	ENDS
CODE 	SEGMENT
		ASSUME CS:CODE
START: 	MOV DX,MY8255_MODE
       	MOV AL,82H
       	OUT DX,AL
       	MOV DX,MY8237_D   		;写总清命令
       	OUT DX,AL
       	MOV DX,MY8237_0   		;写通道0当前地址寄存器
       	MOV AL,20H        		;总线地址是0320H*2=0640H
       	OUT DX,AL
       	MOV AL,03H
       	OUT DX,AL
       	MOV DX,MY8237_B   		;写通道0工作方式寄存器
       	MOV AL,48H        
       	OUT DX,AL
       	MOV DX,MY8237_8   		;写命令寄存器
       	MOV AL,80H        
      	OUT DX,AL
      	MOV DX,MY8237_F   		;写屏蔽位寄存器
       	MOV AL,00H          
      	OUT DX,AL
       	MOV DX,MY8237_9   		;写请求寄存器
       	MOV AL,04H        
       	OUT DX,AL
QUIT:  	MOV AX,4C00H      		;结束程序退出
       	INT 21H
CODE 	ENDS
     	END START
