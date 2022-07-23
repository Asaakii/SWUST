;----------------------------------------------------------------------------
;文件名:6-3-1.ASM
;功能:使用JMP指令实现任务切换实验（不反映不同特权级的情况）
;----------------------------------------------------------------------------
INCLUDE         386SCD.INC
;----------------------------------------------------------------------------
DSEG      	    SEGMENT PARA USE16              ;全局描述符表数据段(16位)
GDT             LABEL   BYTE            		;全局描述符表
DUMMY           DESC    <>                  	;空描述符
NORMAL			DESC	<0FFFFH,,,ATDW,,>		;规范段描述符
CODEM           DESC    <0FFFFH,,,ATCE,,>   	;主程序段描述符
LDTABLE1        DESC    <0FFFFH,,,ATLDT,,>      ;局部描述符表段的描述符
TSSTABLE0       DESC    <0FFFFH,,,,,>			;任务0状态段TSS描述符
TSSTABLE1       DESC    <0FFFFH,,,,,>			;任务1状态段TSS描述符
DSTACK0			DESC    <0FFFFH,,,ATDW,,>		;任务0的0级堆栈段描述符
DDATA0			DESC	<0FFFFH,,,ATDW,,>		;任务0的数据段描述符
;----------------------------------------------------------------------------
NORMAL_SEL		=		NORMAL-GDT				;规范段描述符选择子
CODEM_SEL       =       CODEM-GDT               ;主程序段选择子
LDT1_SEL        =       LDTABLE1-GDT            ;局部描述符表段选择子
TSS0_SEL		= 		TSSTABLE0-GDT			;任务0状态段选择子
TSS1_SEL		=		TSSTABLE1-GDT			;任务1状态段选择子
DSTACK0_SEL		=       DSTACK0-GDT				;任务0的堆栈段选择子
DDATA0_SEL      =       DDATA0-GDT              ;任务0的数据段描述符对应选择子
GDTLEN          =       $-GDT            	    ;全局描述符表长度
;----------------------------------------------------------------------------
VGDTR           PDESC   <GDTLEN-1,>             ;定义GDT的伪描述符VGDTR
SPVAR 			 DW  ?
SSVAR 			 DW  ?						    ;保存实模式下堆栈指针
;----------------------------------------------------------------------------
DSEG          ENDS                              ;全局描述符表段定义结束
;----------------------------------------------------------------------------
DSEG1 	     	SEGMENT PARA USE16               	;局部描述符表数据段(16位)
LDT1			LABEL   BYTE                      	;局部描述符表
DCODE1			DESC    <0FFFFH,,,ATCE,,>			;任务1的代码段描述符
DSTACK1			DESC	<0FFFFH,,,ATDW,,>			;任务1的堆栈段描述符
DDATAS          DESC    <0FFFFH,,,ATDW,,>  			;源数据段描述符
DDATAO          DESC    <0FFFFH,3000H,,ATDW,,> 		;目的数据段描述符
TOTASK0         GATE    <0,TSS0_SEL,,ATTASKGATE,>   ;指向任务0的调用门描述符
;----------------------------------------------------------------------------
DCODE1_SEL		=       DCODE1-LDT1+TIL		;任务1的代码描述符选择子
DSTACK1_SEL		=       DSTACK1-LDT1+TIL	;任务1的堆栈段描述符选择子
DDATAS_SEL		=       DDATAS-LDT1+TIL		;源数据段描述符选择子
DDATAO_SEL		=       DDATAO-LDT1+TIL		;目的数据段描述符选择子
TOTASK0_SEL		=		TOTASK0-LDT1+TIL	;任务门描述符选择子
LDT1LEN      	=       $-LDT1
DSEG1         ENDS                           ;局部描述符表段定义结束
;----------------------------------------------------------------------------
TSS0SEG    	  SEGMENT PARA USE16                ;任务状态段TSS0
TEMPTASK   	  TSS     <>
           	  DB      0FFH                      ;I/O许可位图结束标志
TSS0LEN    	  =       $
TSS0SEG     	 ENDS							;任务状态段TSS0结束
;----------------------------------------------------------------------------
TSS1SEG      SEGMENT PARA USE16                ;任务状态段TSS1
;----------------------------------------------------------------------------
                DD      0                         ;链接字
                DD      DSTACK1LEN                ;0级堆栈指针
                DD      DSTACK1_SEL               ;0级堆栈选择子
                DD      0                         ;1级堆栈指针(实例不使用)
                DD      0	               		  ;1级堆栈选择子(实例不使用)
                DD      0                         ;2级堆栈指针
                DD      0       	              ;2级堆栈选择子
                DD      0                         ;CR3
                DD      0		          		  ;EIP
                DD      200H                      ;EFLAGS
                DD      0FFFH                     ;EAX
                DD      0                         ;ECX
                DD      0                         ;EDX
                DD      0                         ;EBX
                DD      DSTACK1LEN	              ;ESP
                DD      0                         ;EBP
                DD      0                         ;ESI
                DD      0	                      ;EDI
                DW      DDATAS_SEL,0              ;ES
                DW      DCODE1_SEL,0              ;CS
                DW      DSTACK1_SEL,0             ;SS
                DW      DDATAS_SEL,0              ;DS
                DW      DDATAS_SEL,0              ;FS
                DW      DDATAS_SEL,0	          ;GS
                DW      LDT1_SEL,0              ;LDTR
                DW      0                       ;调试陷阱标志
                DW      $+2                     ;指向I/O许可位图
                DB      0FFH                    ;I/O许可位图结束标志
TSS1LEN      =       $
;----------------------------------------------------------------------------
TSS1SEG      ENDS                               ;任务状态段TSS1结束
;----------------------------------------------------------------------------
DSTACK0SEG   	SEGMENT PARA   USE16            ;任务0的堆栈段
DSTACK0LEN	=       512
                DB      DSTACK0LEN DUP(?)		;定义512个缓冲字节单元
DSTACK0SEG	ENDS                              	;任务0堆栈段结束
;----------------------------------------------------------------------------
DSTACK1SEG   	SEGMENT PARA   USE16            ;任务1的堆栈段
DSTACK1LEN	=       512
                DB      DSTACK1LEN DUP(?)		;定义512个缓冲字节单元
DSTACK1SEG	ENDS                              	;任务1堆栈段结束
;----------------------------------------------------------------------------
DDATA0SEG	SEGMENT	PARA USE16					;任务0的数据段
DDATA0LEN	=	128
		DB	DDATA0LEN DUP(?)
DDATA0SEG	ENDS
;----------------------------------------------------------------------------
DDATASSEG	SEGMENT	PARA USE16					;源数据段
DTEST		DB	11H,22H,33H,44H,55H,66H,77H,88H	;定义源数据段数据
DDATASLEN	=	$								;数据段的长度
DDATASSEG	ENDS								;源数据段定义结束
;----------------------------------------------------------------------------
CODEMSEG	SEGMENT PARA USE16					;主程序段
		ASSUME	CS:CODEMSEG
START		PROC
			ASSUME  DS:DSEG
            MOV     AX,DSEG
            MOV     DS,AX
            
			MOV     BX,16       		     ;准备要加载到GDTR的伪描述符
      		MUL     BX
			ADD     AX,OFFSET GDT            ;计算并设置GDT基地址
			ADC     DX,0
			MOV     WORD PTR VGDTR.BASE,AX
			MOV     WORD PTR VGDTR.BASE+2,DX
            
			MOV     AX,CODEMSEG
			MUL     BX
			MOV     WORD PTR CODEM.BASEL,AX  ;计算并设置主程序段基地址
			MOV     BYTE PTR CODEM.BASEM,DL
			MOV     BYTE PTR CODEM.BASEH,DH            

			MOV     AX,DSEG1
			MUL     BX
			MOV     WORD PTR LDTABLE1.BASEL,AX  ;计算并设置LDT表段基地址
			MOV     BYTE PTR LDTABLE1.BASEM,DL
			MOV     BYTE PTR LDTABLE1.BASEH,DH
               
			MOV		AX,TSS0SEG
			MUL		BX
			MOV		WORD PTR TSSTABLE0.BASEL,AX	;计算并设置任务段TSS0基地址
			MOV		BYTE PTR TSSTABLE0.BASEM,DL
			MOV		BYTE PTR TSSTABLE0.BASEH,DH		
			MOV		BYTE PTR TSSTABLE0.ATTRIBUTES,AT386TSS	;任务段TSS0的段属性
		
			MOV		AX,TSS1SEG
			MUL		BX
			MOV		WORD PTR TSSTABLE1.BASEL,AX	;计算并设置任务段TSS1基地址
			MOV		BYTE PTR TSSTABLE1.BASEM,DL
			MOV		BYTE PTR TSSTABLE1.BASEH,DH
			MOV		BYTE PTR TSSTABLE1.ATTRIBUTES,AT386TSS	;任务段TSS1的段属性
		
			MOV		AX,DSTACK0SEG
			MUL		BX
			MOV		WORD PTR DSTACK0.BASEL,AX	;计算并设置堆栈段基地址
			MOV		BYTE PTR DSTACK0.BASEM,DL
			MOV		BYTE PTR DSTACK0.BASEH,DH	
		
			MOV		AX,DDATA0SEG
			MUL		BX
			MOV		WORD PTR DDATA0.BASEL,AX	;计算并设置任务0数据段基地址
			MOV		BYTE PTR DDATA0.BASEM,DL
			MOV		BYTE PTR DDATA0.BASEH,DH
;-----------------------------------------------------------		

			ASSUME  DS:DSEG1
			MOV		  AX,DSEG1
			MOV		  DS,AX
			
			MOV		AX,DCODE1SEG
			MUL		BX
			MOV		WORD PTR DCODE1.BASEL,AX	;计算并设置任务1代码段基地址
			MOV		BYTE PTR DCODE1.BASEM,DL
			MOV		BYTE PTR DCODE1.BASEH,DH

			MOV		AX,DSTACK1SEG
			MUL		BX
			MOV		WORD PTR DSTACK1.BASEL,AX	;计算并设置任务1堆栈段基地址
			MOV		BYTE PTR DSTACK1.BASEM,DL
			MOV		BYTE PTR DSTACK1.BASEH,DH
	
			MOV		AX,DDATASSEG
			MUL		BX
			MOV		WORD PTR DDATAS.BASEL,AX	;计算并设置源数据段基地址
			MOV		BYTE PTR DDATAS.BASEM,DL
			MOV		BYTE PTR DDATAS.BASEH,DH
						
;---------------------------------------------------------------------------
			ASSUME  DS:DSEG
            MOV     AX,DSEG
            MOV     DS,AX
            
            MOV 	SSVAR,SS
            MOV 	SPVAR,SP				;保存实模式下堆栈指针
            
			LGDT    QWORD PTR VGDTR			;装载GDT表寄存器GDTR
            CLI                             ;关中断
            
            MOV     EAX,CR0         	    ;切换到保护方式
            OR      EAX,1
            MOV     CR0,EAX                
            
            JUMP16  <CODEM_SEL>,<OFFSET VIRTUAL>     ;清指令预取队列,并真正进入保护方式
               
VIRTUAL:    								;现在开始在保护方式下运行
			MOV		AX,TSS0_SEL				;装入任务0
			LTR		AX

			MOV		AX,DDATA0_SEL			;置数据段
			MOV		DS,AX
			MOV		ES,AX
			MOV		FS,AX
			MOV		GS,AX
			MOV 	ESP,DSTACK0LEN-1
			MOV		AX,DSTACK0_SEL			;置堆栈
			MOV		SS,AX
		
			JUMP16  TSS1_SEL,0				;跳转到任务1的0级代码段		
    
			MOV		AX,NORMAL_SEL			;把规范段描述符装入各数据段寄存器
			MOV		DS,AX
			MOV		ES,AX
			MOV		FS,AX
			MOV		GS,AX
			MOV		SS,AX
    
	        MOV     EAX,CR0					;切换到实模式
            AND     AL,11111110B
            MOV     CR0,EAX
            JUMP16  <SEG REAL>,<OFFSET REAL>;清指令预取队列,进入实方式

REAL:      									;现在又回到实方式
			MOV     AX,DSEG
            MOV     DS,AX
            LSS		SP,DWORD	PTR	SPVAR	;恢复实模式下的堆栈
            
            ASSUME	DS:TSS1SEG
			MOV     AX,TSS1SEG
            MOV     DS,AX

            CALL	INIT_TSS1				;恢复TSS1任务段表的初值,以备下次继续运行

            STI								;开中断
            
			MOV 	AX,4C00H
			INT 	21H						;程序终止

		
START		ENDP
CODEMLEN	= $
;----------------------------------------------------------------------------
INIT_TSS1	PROC	NEAR	;恢复TSS1任务段表的初值
		PUSH	DS
		MOV		AX,TSS1SEG
		MOV 	DS,AX

		MOV		SI,0		;链接字
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;0级堆栈指针
		MOV		AX,DSTACK1LEN
		MOV		[SI],AX
		
		ADD		SI,4		;0级堆栈选择子
		MOV		AX,DSTACK1_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;1级堆栈指针(实例不使用)
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;1级堆栈选择子(实例不使用)
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;2级堆栈指针
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;2级堆栈选择子
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;CR3
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;EIP
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;EFLAGS
		MOV		AX,200H
		MOV		[SI],AX
		
		ADD		SI,4		;EAX
		MOV		AX,0FFFH
		MOV		[SI],AX
		
		ADD		SI,4		;ECX
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;EDX
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;EBX
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;ESP
		MOV		AX,DSTACK1LEN
		MOV		[SI],AX
		
		ADD		SI,4		;EBP
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;ESI
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;EDI
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;ES
		MOV		AX,DDATAS_SEL
		MOV		[SI],AX
		
		ADD		SI,2		
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,2		;CS
		MOV		AX,DCODE1_SEL
		MOV		[SI],AX
		
		ADD		SI,2		
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,2		;SS
		MOV		AX,DSTACK1_SEL
		MOV		[SI],AX
		
		ADD		SI,2		
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,2		;DS
		MOV		AX,DDATAS_SEL
		MOV		[SI],AX
		
		ADD		SI,2
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,2		;FS
		MOV		AX,DDATAS_SEL
		MOV		[SI],AX
		
		ADD		SI,2
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,2		;GS
		MOV		AX,DDATAS_SEL
		MOV		[SI],AX
		
		ADD		SI,2
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,2		;LDTR
		MOV		AX,LDT1_SEL
		MOV		[SI],AX
		
		ADD		SI,2
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,2		;调试陷阱标志
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,2		;指向I/O许可位图
		MOV		AX,68H		;TSS有104个字节
		MOV		[SI],AX
		
		ADD		SI,2		;I/O许可位图结束标志
		MOV		AX,0FFH
		MOV		[SI],AX
		
		POP		DS

		RET
INIT_TSS1		ENDP

CODEMSEG	ENDS
;----------------------------------------------------------------------------
DCODE1SEG	SEGMENT PARA USE16                ;任务1代码段
                ASSUME  CS:DCODE1SEG
				MOV     AX, DDATAS_SEL
                MOV     DS,AX                  ;加载源数据段描述符
                MOV     AX, DDATAO_SEL
                MOV     ES,AX                  ;加载目标数据段描述符
                XOR     SI,SI
                XOR     DI,DI                  ;设置指针初值
                MOV     CX, 8		    	   ;设置传送长度
        M1:     MOVSB                  	       ;传送
                LOOP    M1

               	JUMP16	TOTASK0_SEL,0			;切换回任务0
DCODE1LEN	= $
DCODE1SEG	ENDS
;============================================================================

                END     START
