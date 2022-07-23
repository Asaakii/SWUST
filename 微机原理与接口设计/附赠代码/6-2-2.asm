;----------------------------------------------------------------------------
;文件名:6-2-2.ASM
;功能:通过JMP，RET指令任务内无特权级变换的转移
;----------------------------------------------------------------------------
INCLUDE         386SCD.INC
;数据段==========================================================
DSEG            SEGMENT PARA USE16            ;16位数据段
GDT             LABEL   BYTE                  ;全局描述符表
DUMMY           DESC    <>                    ;空描述符
CODEM           DESC    <0FFFFH,,,ATCE,,>     ;主程序段描述符
LDTABLE         DESC    <0FFFFH,,,ATLDT,,>    ;局部描述符表段的描述符
VGDTR           PDESC   <GDTLEN-1,>           ;伪描述符
GDTLEN          =       $-GDT                 ;全局描述符表长度
CODEM_SEL       =       0008H                 ;主程序段选择子
LDT_SEL         =       0010H             	  ;局部描述符表段选择子
DSEG            ENDS                          ;数据段定义结束
;=====================================================================
DSEG1			SEGMENT PARA USE16            	;16位数据段
LDT             LABEL   BYTE					;局部描述符表
CODE1           DESC    <0FFFFH,,,ATCE,,>		;0级代码段1
CODE2           DESC    <0FFFFH,,,ATCE,,>    	;0级代码段2
DSTACK			DESC    <0FFFFH,,,ATDW,,>		;0级堆栈段描述符
DATAS			DESC	<0FFFFH,,,ATDW,,>		;源数据段描述符
DATAO			DESC	<0FFFFH,3000H,,ATDW,,>	;目的数据段描述符
LDTLEN          =       $-LDT                   ;LDT表长度
CODE1_SEL       =       CODE1-LDT+TIL       	;代码段1的选择子
CODE2_SEL       =       CODE2-LDT+TIL       	;代码段2的选择子
DSTACK_SEL		=       DSTACK-LDT+TIL			;0级堆栈描述符选择子
DATAS_SEL		=       DATAS-LDT+TIL			;源数据段描述符选择子
DATAO_SEL		=       DATAO-LDT+TIL			;目的数据段描述符选择子
DSEG1            ENDS                          	;数据段定义结束
;----------------------------------------------------------------------------
STACKSEG   	SEGMENT	PARA USE16				;定义16位的0级堆栈段
STACKLEN		=       128
                DB      128 DUP(?)			;定义128个缓冲区字节单元
STACKSEG	ENDS							;0级堆栈段结束
;-----------------------------------------------------------------------------
DATASSEG	SEGMENT	PARA USE16					;定义16位数据段
TDATA		DB	11H,22H,33H,44H,55H,66H,77H,88H ;定义源数据段数据
DATASLEN	=	$								;数据段的长度
DATASSEG	ENDS								;源数据段定义结束
;代码段=========================================================
CODE1SEG        SEGMENT PARA USE16					;任务代码段1 
                ASSUME  CS:CODE1SEG

                CALL16	CODE2_SEL,0					;转向代码段2

                JUMP16  <CODEM_SEL>,<OFFSET REAL1>	;跳转至主代码段

CODE1LEN	=	$
CODE1SEG        ENDS                           ;代码段1定义结束
;----------------------------------------------------------------------------
CODE2SEG        SEGMENT PARA USE16				;任务代码段2
                ASSUME  CS:CODE2SEG

                MOV     AX, DATAS_SEL
                MOV     DS,AX                  ;加载源数据段描述符
                MOV     AX, DATAO_SEL
                MOV     ES,AX                  ;加载目标数据段描述符
                XOR     SI,SI
                XOR     DI,DI                  ;设置指针初值
                MOV     CX, 8		    	   ;设置传送长度
        M1:     MOVSB                  	       ;传送
                LOOP    M1

                RETF							;段间返回
CODE2LEN        =       $
CODE2SEG        ENDS                           ;代码段2定义结束
;代码段=========================================================
CSEG		SEGMENT PARA USE16					;16位主代码段
            ASSUME CS:CSEG
START		PROC
			ASSUME	DS:DSEG
            MOV     AX,DSEG
            MOV     DS,AX
            
            MOV		BX,16						;准备要加载到GDTR的伪描述符
            MUL		BX							;计算并设置GDT基地址
            MOV		WORD PTR VGDTR.BASE,AX
            MOV		WORD PTR VGDTR.BASE+2,DX

			MOV		AX,CSEG
			MUL		BX
			MOV		WORD PTR CODEM.BASEL,AX		;计算并设置主代码段基地址
			MOV		BYTE PTR CODEM.BASEM,DL
			MOV		BYTE PTR CODEM.BASEH,DH

			MOV		AX,DSEG1
			MUL		BX
			MOV		WORD PTR LDTABLE.BASEL,AX	;计算并设置LDT表段基地址
			MOV		BYTE PTR LDTABLE.BASEM,DL
			MOV		BYTE PTR LDTABLE.BASEH,DH
			
			ASSUME	DS:DSEG1
            MOV     AX,DSEG1
            MOV     DS,AX

			MOV		AX,CODE1SEG
			MUL		BX
			MOV		WORD PTR CODE1.BASEL,AX		;计算并设置代码段1基地址
			MOV		BYTE PTR CODE1.BASEM,DL
			MOV		BYTE PTR CODE1.BASEH,DH

			MOV		AX,CODE2SEG
			MUL		BX
			MOV		WORD PTR CODE2.BASEL,AX		;计算并设置代码段2基地址
			MOV		BYTE PTR CODE2.BASEM,DL
			MOV		BYTE PTR CODE2.BASEH,DH

			MOV		AX,STACKSEG
			MUL		BX
			MOV		WORD PTR DSTACK.BASEL,AX	;计算并设置堆栈段基地址
			MOV		BYTE PTR DSTACK.BASEM,DL
			MOV		BYTE PTR DSTACK.BASEH,DH

			MOV		AX,DATASSEG
			MUL		BX
			MOV		WORD PTR DATAS.BASEL,AX		;计算并设置源数据段基地址
			MOV		BYTE PTR DATAS.BASEM,DL
			MOV		BYTE PTR DATAS.BASEH,DH

			ASSUME	DS:DSEG
            MOV     AX,DSEG
            MOV     DS,AX

			LGDT    QWORD PTR VGDTR				;装载GDT表寄存器GDTR
            CLI                             	;关中断

            MOV     EAX,CR0         	    	;切换到保护方式
            OR      EAX,1
            MOV     CR0,EAX                
            								
            JUMP16  <CODEM_SEL>,<OFFSET VIRTUAL>;清指令预取队列,并真正进入保护方式
                
VIRTUAL:    									;现在开始在保护方式下运行
   			MOV		AX,LDT_SEL
			LLDT	AX							;装载LDT表寄存器LDTR
    			
            JUMP16  CODE1_SEL,0					;跳转到任务代码段1
     
REAL1:    					        			;切换回实模式
	        MOV     EAX,CR0
            AND     AL,11111110B
            MOV     CR0,EAX
            ;清指令预取队列,进入实方式
            JUMP16  <SEG REAL>,<OFFSET REAL>
REAL:       ;现在又回到实方式
            STI									;关中断
            
			MOV 	AX,4C00H
			INT 	21H							;程序终止

START	        ENDP
;----------------------------------------------------------------------------
CSEG        ENDS
                END     START

