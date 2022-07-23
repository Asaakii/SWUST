;----------------------------------------------------------------------------
;文件名:6-1-2.ASM
;功能:局部描述符及局部描述符表实验
;----------------------------------------------------------------------------
INCLUDE         386SCD.INC
;数据段==========================================================
DSEG            SEGMENT USE16					;16位数据段
GDT             LABEL   BYTE					;全局描述符表
DUMMY           DESC    <>						;空描述符
CODEM           DESC    <0FFFFH,,,ATCE,,>		;代码段描述符
LDTABLE         DESC    <0FFFFH,,,ATLDT,,>		;局部描述符表段的描述符
VGDTR           PDESC   <GDTLEN-1,>           	;伪描述符

CODEM_SEL       =       CODEM-GDT           	;代码段选择子
LDT_SEL			=		LDTABLE-GDT        		;LDT表选择子
GDTLEN          =       $-GDT					;全局描述符表长度

DSEG            ENDS                            ;数据段定义结束
;--------------------------------------------------------------------
DSEG1			SEGMENT USE16					;16位数据段
LDT             LABEL   BYTE                  	;局部描述符表
LDATAS          DESC    <0FFFFH,,,ATDW,,>    	;源数据段描述符
LDATAD          DESC    <0FFFFH,3000H,,ATDW,,>  ;目标数据段描述符

LDTLEN          =       $-LDT 		            ;局部描述符表长度
LDATAS_SEL      =       LDATAS-LDT+TIL          ;源数据段选择子
LDATAD_SEL      =       LDATAD-LDT+TIL          ;目标数据段选择子
DSEG1           ENDS                          	;数据段定义结束
;-----------------------------------------------------------------------------
DATASSEG		SEGMENT	PARA USE16				  ;定义16位源数据段
TDATA			DB 11H,22H,33H,44H,55H,66H,77H,88H;定义源数据段数据
DATASLEN		=	$							  ;源数据段的长度
DATASSEG		ENDS							  ;源数据段定义结束
;代码段=========================================================
CSEG		SEGMENT USE16						;16位代码段
            ASSUME CS:CSEG
START		PROC
			ASSUME	DS:DSEG
            MOV     AX,DSEG
            MOV     DS,AX
            
            MOV		BX,16          	 			;准备要加载到GDTR的伪描述符
            MUL		BX							;计算并设置GDT基地址
            MOV		WORD PTR VGDTR.BASE,AX
            MOV		WORD PTR VGDTR.BASE+2,DX

			MOV		AX,CSEG
			MUL		BX
			MOV		WORD PTR CODEM.BASEL,AX		;计算并设置代码段基地址
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

			MOV		AX,DATASSEG
			MUL		BX
			MOV		WORD PTR LDATAS.BASEL,AX	;计算并设置源数据段基地址
			MOV		BYTE PTR LDATAS.BASEM,DL
			MOV		BYTE PTR LDATAS.BASEH,DH

			ASSUME	DS:DSEG
            MOV     AX,DSEG
            MOV     DS,AX

            LGDT    QWORD PTR VGDTR				;装载GDTR
            CLI                             	;关中断
            ;切换到保护方式
            MOV     EAX,CR0
            OR      EAX,1
            MOV     CR0,EAX                
            ;清指令预取队列,并真正进入保护方式
            JUMP16  <CODEM_SEL>,<OFFSET VIRTUAL>    
                
VIRTUAL:    ;现在开始在保护方式下运行
   			MOV		AX,LDT_SEL
			LLDT	AX							;装载LDT表寄存器LDTR
            MOV     AX,LDATAS_SEL      			;加载源数据段描述符
            MOV     DS,AX                  
            MOV		AX,LDATAD_SEL      			;加载目标数据段描述符
            MOV     ES,AX
            XOR		DI,DI
            XOR     SI,SI
            MOV     CX,8                		;设置数据长度
            REPZ    MOVSB              			;传数
            ;切换回实模式
            MOV     EAX,CR0
            AND     AL,11111110B
            MOV     CR0,EAX
            ;清指令预取队列,进入实方式
            JUMP16  <SEG REAL>,<OFFSET REAL>
REAL:       ;现在又回到实方式
            STI									;开中断

			MOV 	AX,4C00H
			INT 	21H							;程序终止

START       ENDP
;---------------------------------------------------------------------------
CSEG        ENDS                           ;代码段定义结束
;----------------------------------------------------------------------------
            END     START

