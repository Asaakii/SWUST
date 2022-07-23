;----------------------------------------------------------------------------
;文件名:6-2-3.ASM
;功能:任务内有特权级变换的转移
;----------------------------------------------------------------------------
INCLUDE         386SCD.INC
;----------------------------------------------------------------------------
TDATASEG          SEGMENT PARA USE16			;全局描述符表数据段(16位)
GDT             LABEL   BYTE	              	;全局描述符表
DUMMY           DESC    <>                  	;空描述符
NORMAL			DESC	<0FFFFH,,,ATDW,,>		;规范段描述符
CODEM           DESC    <0FFFFH,,,ATCE,,>       ;主程序段描述符
LDTABLE         DESC    <0FFFFH,,,ATLDT,,>      ;局部描述符表段的描述符
TSSTABLE        DESC    <0FFFFH,,,AT386TSS,,>	;任务状态段TSS描述符
;----------------------------------------------------------------------------
GDTLEN          =       $-GDT                	 ;全局描述符表长度
NORMAL_SEL		=		NORMAL-GDT				 ;规范段描述符选择子	
CODEM_SEL       =       CODEM-GDT                ;主程序段选择子
LDT_SEL         =       LDTABLE-GDT              ;局部描述符表段选择子
TSS_SEL			=		TSSTABLE-GDT			 ;任务状态段选择子
;----------------------------------------------------------------------------
VGDTR           PDESC   <GDTLEN-1,>          	 ;定义GDT的伪描述符VGDTR
SPVAR 			 DW  ?
SSVAR 			 DW  ?							 ;定义实方式下的堆栈指针
;----------------------------------------------------------------------------
TDATASEG          ENDS                           ;全局描述符表段定义结束
;----------------------------------------------------------------------------
LDTSEG    		  SEGMENT USE16           		  ;局部描述符表数据段(16位)
LDT				LABEL   BYTE                      ;局部描述符表
DCODE0          DESC    <0FFFFH,,,ATCE,D32,>      ;代码段0描述符(32位段,DPL=0)
DCODE3			DESC    <0FFFFH,,,ATCE+DPL3,,>	  ;代码段3描述符(16位段,DPL=3)
DSTACK0			DESC    <0FFFFH,,,ATDW,,>         ;0级堆栈段描述符(DPL=0)
DSTACK3			DESC	<0FFFFH,,,ATDW+DPL3,,>    ;3级堆栈段描述符(DPL=3)
DDATAS          DESC    <0FFFFH,,,ATDW+DPL3,,>    ;源数据段描述符(DPL=3)
DDATAO          DESC    <0FFFFH,3000H,,ATDW+DPL3,,> ;目的数据段描述符(DPL=3)
TOCODE0         GATE    <OFFSET PEND- OFFSET PSTART,DCODE0_SEL,,AT386CGATE+DPL3,>;指向代码段0的任务描述符
;----------------------------------------------------------------------------
DCODE0_SEL		=       DCODE0 -LDT+TIL			;代码段0描述符选择子(RPL=0)
DCODE3_SEL		=       DCODE3 -LDT+TIL+RPL3	;代码段3描述符选择子(RPL=3)
DSTACK0_SEL     =       DSTACK0-LDT+TIL      	;0级堆栈描述符选择子(RPL=0)
DSTACK3_SEL		=       DSTACK3-LDT+TIL+RPL3	;3级堆栈描述符选择子(RPL=3)
DDATAS_SEL		=       DDATAS -LDT+TIL+RPL3	;源数据段描述符选择子(RPL=3)
DDATAO_SEL		=       DDATAO -LDT+TIL+RPL3	;目标数据段描述符选择子(RPL=3)
TOCODE0_SEL		=		(TOCODE0-LDT)+TIL		;调用门描述符选择子
LDTLEN			=       $-LDT
LDTSEG      	ENDS                            ;局部描述符表段定义结束
;----------------------------------------------------------------------------
TSSSEG      SEGMENT PARA USE16                  ;任务状态段TSS
                DD      0                       ;BACK
                DD      DSTACK0LEN              ;0级堆栈指针
                DD      DSTACK0_SEL             ;初始化
                DD      0						;1级堆栈指针
                DD		0						;初始化
                DD      0                       ;2级堆栈指针
                DD      0                       ;未初始化
                DD      0                       ;CR3
                DD      0                       ;EIP
                DD      0                       ;EFLAGS
                DD      0                       ;EAX
                DD      0                       ;ECX
                DD      0                       ;EDX
                DD      0                       ;EBX
                DD      0                       ;ESP
                DD      0                       ;EBP
                DD      0                       ;ESI
                DD      0                       ;EDI
                DD      0                       ;ES
                DD      0                       ;CS
                DD      0                       ;SS
                DD      0                       ;DS
                DD      0                       ;FS
                DD      0                       ;GS
                DD      LDT_SEL					;LDT
                DW      0                       ;调试陷阱标志
                DW      $+2                     ;指向I/O许可位图
                DW      0FFFFH                  ;I/O许可位图结束标志
TSSLEN     	 =       $
TSSSEG      ENDS                              ;任务状态段TSS结束
;----------------------------------------------------------------------------
DSTACK0SEG   	SEGMENT	PARA USE16			;定义16位的0级堆栈段
DSTACK0LEN		=       128
                DB      DSTACK0LEN DUP(?)	;定义128个缓冲区字节单元
DSTACK0SEG	ENDS							;0级堆栈段结束
;----------------------------------------------------------------------------
DSTACK3SEG		SEGMENT PARA	USE16	         ;3级堆栈段
DSTACK3LEN		=       128
				DB      DSTACK3LEN DUP(?)
DSTACK3SEG	ENDS       
;----------------------------------------------------------------------------
DDATASSEG	SEGMENT	PARA USE16					;定义16位数据段
DTEST		DB	11H,22H,33H,44H,55H,66H,77H,88H ;定义源数据段数据
DDATASLEN	=	$								;数据段的长度
DDATASSEG	ENDS								;源数据段定义结束
;----------------------------------------------------------------------------
CODEMSEG        SEGMENT PARA USE16
                ASSUME  CS:CODEMSEG
START		PROC
			ASSUME   DS:TDATASEG
            MOV     AX,TDATASEG
            MOV     DS,AX
            
            MOV		BX,16               				;准备要加载到GDTR的伪描述符
            MUL		BX			    					;计算并设置GDT基地址
            MOV		WORD PTR VGDTR.BASE,AX
            MOV		WORD PTR VGDTR.BASE+2,DX

			MOV		AX,CODEMSEG
			MUL		BX
			MOV		WORD PTR CODEM.BASEL,AX	  		  	;计算并设置主程序段基地址
			MOV		BYTE PTR CODEM.BASEM,DL
			MOV		BYTE PTR CODEM.BASEH,DH

			MOV		AX,LDTSEG
			MUL		BX
			MOV		WORD PTR LDTABLE.BASEL,AX	    	;计算并设置LDT表段基地址
			MOV		BYTE PTR LDTABLE.BASEM,DL
			MOV		BYTE PTR LDTABLE.BASEH,DH

			MOV		AX,TSSSEG
			MUL		BX
			MOV		WORD PTR TSSTABLE.BASEL,AX	    	;计算并设置任务段TSS基地址
			MOV		BYTE PTR TSSTABLE.BASEM,DL
			MOV		BYTE PTR TSSTABLE.BASEM,DL
			MOV		BYTE PTR TSSTABLE.ATTRIBUTES,AT386TSS;任务段TSS的段属性
;---------------------------------------------------------------------
			ASSUME   DS:LDTSEG
			MOV      AX,LDTSEG
			MOV		DS,AX
			
			MOV		AX,DCODE0SEG
			MUL		BX
			MOV		WORD PTR DCODE0.BASEL,AX	    	;计算并设置代码段0基地址
			MOV		BYTE PTR DCODE0.BASEM,DL
			MOV		BYTE PTR DCODE0.BASEH,DH

			MOV		AX,DCODE3SEG
			MUL		BX
			MOV		WORD PTR DCODE3.BASEL,AX	    	;计算并设置代码段3基地址
			MOV		BYTE PTR DCODE3.BASEM,DL
			MOV		BYTE PTR DCODE3.BASEH,DH

			MOV		AX,DSTACK0SEG
			MUL		BX
			MOV		WORD PTR DSTACK0.BASEL,AX	    	;计算并设置堆栈段0基地址
			MOV		BYTE PTR DSTACK0.BASEM,DL
			MOV		BYTE PTR DSTACK0.BASEH,DH

			MOV		AX,DSTACK3SEG
			MUL		BX
			MOV		WORD PTR DSTACK3.BASEL,AX	    	;计算并设置堆栈段3基地址
			MOV		BYTE PTR DSTACK3.BASEM,DL
			MOV		BYTE PTR DSTACK3.BASEH,DH
		
			MOV		AX,DDATASSEG
			MUL		BX
			MOV		WORD PTR DDATAS.BASEL,AX	    	;计算并设置源数据段基地址
			MOV		BYTE PTR DDATAS.BASEM,DL
			MOV		BYTE PTR DDATAS.BASEH,DH
;------------------------------------------------------		
			ASSUME   DS:TDATASEG
            MOV     AX,TDATASEG
            MOV     DS,AX
            
            MOV 	SSVAR,SS
            MOV 	SPVAR,SP						;保存实方式下的堆栈指针
            
			LGDT    QWORD PTR VGDTR					;装载GDT表寄存器GDTR
            CLI                             		;关中断
            MOV     EAX,CR0            				;切换到保护方式
            OR      EAX,1
            MOV     CR0,EAX                
            JUMP16  <CODEM_SEL>,<OFFSET VIRTUAL>    ;清指令预取队列,并真正进入保护方式
VIRTUAL:    										;现在开始在保护方式下运行
			MOV		AX,TSS_SEL						;装载LDT表
			LTR		AX
			MOV		AX,LDT_SEL						;装载TSS表
			LLDT	AX
			
			JUMP16  DCODE0_SEL,0            		;转移到0级程序段
REAL1:           							 		;切换回实模式
			MOV		AX,NORMAL_SEL					;把规范段描述符装入各数据段寄存器
			MOV		DS,AX
			MOV		ES,AX
			MOV		FS,AX
			MOV		GS,AX
			MOV		SS,AX
			
	        MOV     EAX,CR0							;切换到实模式
            AND     AL,11111110B
            MOV     CR0,EAX
            
            JUMP16  <SEG REAL>,<OFFSET REAL>		;清指令预取队列,进入实方式
REAL:       										;现在又回到实方式
			MOV     AX,TDATASEG
            MOV     DS,AX
            
			LSS 	SP,DWORD PTR SPVAR				;恢复实方式堆栈指针
			
            STI										;开中断
            
			MOV 	AX,4C00H
			INT 	21H								;程序终止
			
CODEMLEN        = $
START           ENDP
;-----------------------------------------------------------------
DCODE0SEG       SEGMENT PARA USE32					;0级的32位代码段                
                ASSUME  CS:DCODE0SEG

PSTART:			MOV     AX,DSTACK0_SEL          	;建立0级堆栈
				MOV		SS,AX
				MOV     ESP,DSTACK0LEN-1
                PUSH    DWORD PTR DSTACK3_SEL
                PUSH    DWORD PTR DSTACK3LEN		;压入3级堆栈指针
                PUSH    DWORD PTR DCODE3_SEL
                PUSH    OFFSET 	0					;压入入口点
                
                RETF								;由0级程序段转移到3级程序段
                
PEND:           JUMP32  <CODEM_SEL>,<OFFSET REAL1>	;跳转到主程序段

DCODE0LEN	=       $
;----------------------------------------------------------------------------
DCODE0SEG	ENDS                              
;----------------------------------------------------------------------------
DCODE3SEG	SEGMENT PARA USE16                		;3级的16位代码段
                ASSUME  CS:DCODE3SEG
                MOV     AX, DDATAS_SEL
                MOV     DS, AX                 		;加载源数据段描述符
                MOV     AX, DDATAO_SEL
                MOV     ES,AX                  		;加载目标数据段描述符
                XOR     SI,SI
                XOR     DI,DI                  		;设置指针初值
                MOV     CX, 8		     	   		;设置传送长度
        M1:     MOVSB                  	       		;传送
                LOOP    M1
                
				CALL16  TOCODE0_SEL,0					;由3级程序段转移到0级程序段
				
DCODE3LEN	=	$
DCODE3SEG       ENDS  
;------------------------------------------------------------------
CODEMSEG        ENDS
                END     START

