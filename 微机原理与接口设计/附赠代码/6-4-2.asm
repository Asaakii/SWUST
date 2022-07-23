;----------------------------------------------------------------------------
;文件名:6-4-2.ASM
;功能:通过任务门转移的中断/异常处理
;----------------------------------------------------------------------------
INCLUDE         386SCD.INC     
;----------------------------------------------------------------------------
GDTSEG          SEGMENT PARA USE16          ;全局描述符表数据段(16位)
;----------------------------------------------------------------------------
GDT             LABEL   BYTE                ;全局描述符表
DUMMY           DESC    <>                  ;空描述符
NORMAL			DESC	<0FFFFH,,,ATDW,,>	;规范段描述符

CODEM           DESC    <0FFFFH,CODEMSEG,,ATCE,,>   ;主程序段描述符

TSSTABLE1       DESC    <0FFFFH,TSS1SEG,,,,>	;任务1状态段TSS描述符
TSSTABLE2       DESC    <0FFFFH,TSS2SEG,,,,>	;任务2状态段TSS描述符
TSSTABLE3       DESC    <0FFFFH,TSS3SEG,,,,>	;任务3状态段TSS描述符

DCODE2			DESC    <0FFFFH,DCODE2SEG,,ATCE,,>		;任务2的0级代码段描述符
DCODE3			DESC    <0FFFFH,DCODE3SEG,,ATCE+DPL3,,>	;任务3的3级代码段描述符(DPL=3)

DSTACK1			DESC    <0FFFFH,DSTACK1SEG,,ATDW,,>			;任务1的0级堆栈段描述符
DSTACK2			DESC	<0FFFFH,DSTACK2SEG,,ATDW,,>			;任务2的0级堆栈段描述符
DSTACK3			DESC	<0FFFFH,DSTACK3SEG,,ATDW+DPL3,,>	;任务3的3级堆栈段描述符(DPL=3)

DDATA1			DESC	<0FFFFH,DDATA1SEG,,ATDW,,>		;任务1的数据段描述符
DDATA2			DESC	<0FFFFH,DDATA2SEG,,ATDW,,>		;任务2的数据段描述符
DDATAS          DESC    <0FFFFH,DDATASSEG,,ATDW+DPL3,,>		;源数据段描述符(DPL=3)
DDATAO          DESC    <0FFFFH,4000H,,ATDW+DPL3,,>    		;目的数据段描述符(DPL=3)
;----------------------------------------------------------------------------
NORMAL_SEL		=		NORMAL-GDT			;规范段描述符选择子
CODEM_SEL       =       CODEM-GDT           ;主程序段选择子
TSS1_SEL		= 		TSSTABLE1-GDT		;任务1状态段选择子
TSS2_SEL		=		TSSTABLE2-GDT		;任务2状态段选择子
TSS3_SEL		=		TSSTABLE3-GDT		;任务3状态段选择子
DCODE2_SEL		=       DCODE2-GDT			;任务2代码段描述符选择子
DCODE3_SEL		=       DCODE3-GDT+RPL3		;任务3代码段描述符选择子(RPL=3)
DSTACK1_SEL		=       DSTACK1-GDT			;0级堆栈段1描述符选择子
DSTACK2_SEL		=       DSTACK2-GDT			;0级堆栈段2描述符选择子
DSTACK3_SEL		=       DSTACK3-GDT+RPL3	;3级堆栈段3描述符选择子(RPL=3)
DDATA1_SEL		=       DDATA1-GDT			;任务1的数据段描述符对应选择子
DDATA2_SEL		=       DDATA2-GDT			;任务2的数据段描述符对应选择子
DDATAS_SEL      =       DDATAS-GDT+RPL3     ;源数据段选择子(RPL=3)
DDATAO_SEL      =       DDATAO-GDT+RPL3     ;目的数据段选择子(RPL=3)
GDTLEN          =       $-GDT               ;全局描述符表长度
GDTSEG          ENDS                        ;全局描述符表段定义结束
;----------------------------------------------------------------------------
IDTSEG		SEGMENT		PARA	USE16			;16位中断/异常处理程序段
IDT			LABEL		BYTE					;定义中断描述符表IDT
			REPT	32							;从00H---1FH的32个中断门描述符
			GATE	<,,,AT386IGATE,>
			ENDM
			
INT20		GATE    <0,TSS3_SEL,,ATTASKGATE,>	;对应20H号异常/中断处理程序段的任务门描述符

			REPT	256-33						;从21H---FFH的223个中断门描述符
			GATE	<,,,AT386IGATE,>
			ENDM
			
IDTLEN		=	$-IDT							;中断描述符表长度
IDTSEG		ENDS								;16位中断/异常处理程序段结束
;----------------------------------------------------------------------------
TSS1SEG      SEGMENT PARA USE16                ;任务1的任务状态段TSS
TEMPTASK     TSS     <>
             DB      0FFH                      ;I/O许可位图结束标志
TSS1LEN      =       $
TSS1SEG      ENDS								;任务1状态段TSS结束
;----------------------------------------------------------------------------
TSS2SEG      SEGMENT PARA USE16                 ;任务状态段TSS2
                DD      0                       ;链接字
                DD      DSTACK2LEN              ;0级堆栈指针
                DD      DSTACK2_SEL				;0级堆栈选择子
                DD      0                       ;1级堆栈指针(实例不使用)
                DD      0	                    ;1级堆栈选择子(实例不使用)
                DD      0                       ;2级堆栈指针
                DD      0	                    ;2级堆栈选择子
                DD      0                       ;CR3
                DD      0		                ;EIP
                DD      200H                    ;EFLAGS
                DD      0FFFH                   ;EAX
                DD      0                       ;ECX
                DD      0                       ;EDX
                DD      0                       ;EBX
                DD      DSTACK2LEN              ;ESP
                DD      0                       ;EBP
                DD      0                       ;ESI
                DD      0	                    ;EDI
                DD      DDATA2_SEL              ;ES
                DD      DCODE2_SEL              ;CS
                DD      DSTACK2_SEL             ;SS
                DD      DDATA2_SEL              ;DS
                DD      DDATA2_SEL              ;FS
                DD      DDATA2_SEL	        	;GS
                DD      0                       ;LDTR
                DW      0                       ;调试陷阱标志
                DW      $+2                     ;指向I/O许可位图
                DB      0FFH                    ;I/O许可位图结束标志
TSS2LEN      =       $
TSS2SEG      ENDS                               ;任务状态段TSS结束
;----------------------------------------------------------------------------
TSS3SEG      SEGMENT PARA USE16                 ;任务状态段TSS3
                DD      0                       ;链接字
                DD      0        			    ;0级堆栈指针
                DD      0	     		        ;0级堆栈选择子
                DD      0                       ;1级堆栈指针(实例不使用)
                DD      0                       ;1级堆栈选择子(实例不使用)
                DD      0                       ;2级堆栈指针
                DD      0                       ;2级堆栈选择子
                DD      0                         ;CR3
                DD      0                         ;EIP
                DD      200H                      ;EFLAGS
                DD      0FFFH                     ;EAX
                DD      0                         ;ECX
                DD      0                         ;EDX
                DD      0                         ;EBX
                DD      DSTACK3LEN                ;ESP
                DD      0                         ;EBP
                DD      0                         ;ESI
                DD      0	                      ;EDI
                DD      DDATAO_SEL                ;ES
                DD      DCODE3_SEL                ;CS
                DD      DSTACK3_SEL               ;SS
                DD      DDATAS_SEL                ;DS
                DD      DDATAS_SEL                ;FS
                DD      DDATAS_SEL                ;GS
                DD      0                         ;LDTR
                DW      0                         ;调试陷阱标志
                DW      $+2                       ;指向I/O许可位图
                DB      0FFH                      ;I/O许可位图结束标志
TSS3LEN      =       $
TSS3SEG      ENDS                              ;任务状态段TSS结束
;----------------------------------------------------------------------------
DSTACK1SEG   	SEGMENT PARA   USE16            ;任务1的0级堆栈段
DSTACK1LEN	=       512
                DB      DSTACK1LEN DUP(0)		;定义512个缓冲字节单元
DSTACK1SEG	ENDS                              	 ;任务1堆栈段结束
;----------------------------------------------------------------------------
DSTACK2SEG	SEGMENT PARA	USE16	         	;任务2的0级堆栈段
DSTACK2LEN	=       512
		DB      DSTACK2LEN DUP(?)
DSTACK2SEG	ENDS       
;----------------------------------------------------------------------------
DSTACK3SEG	SEGMENT PARA	USE16	         	;任务3的3级堆栈段
DSTACK3LEN	=       512
		DB      DSTACK3LEN DUP(?)
DSTACK3SEG	ENDS       
;----------------------------------------------------------------------------
DDATA1SEG	SEGMENT	PARA USE16		;任务1的数据段
DDATA1LEN	=	128
		DB	DDATA1LEN DUP(?)	
DDATA1SEG	ENDS
;----------------------------------------------------------------------------
DDATA2SEG	SEGMENT	PARA USE16		;任务2的数据段
DDATA2LEN	=	128
		DB	DDATA2LEN DUP(?)
DDATA2SEG	ENDS
;----------------------------------------------------------------------------
DDATASSEG	SEGMENT	PARA USE16					;源数据段
DTEST		DB	11H,22H,33H,44H,55H,66H,77H,88H	;定义源数据段数据
DDATASLEN	=	$								;数据段的长度
DDATASSEG	ENDS								;源数据段定义结束
;----------------------------------------------------------------------------
RDATASEG		SEGMENT		PARA	USE16		;实模式下的数据段
VGDTR           PDESC   <GDTLEN-1,>          	;GDT伪描述符
VIDTR			PDESC	<IDTLEN-1,>				;IDT伪描述符
NORVIDTR		PDESC	<3FFH,0>				;用于保存原IDTR值
SPVAR			DW  ?
SSVAR			DW  ?							;用于保存实模式下的堆栈指针
REGV		DB	?								;用于保存原中断屏蔽寄存器值
RDATASEG		ENDS
;----------------------------------------------------------------------------
CODEMSEG	SEGMENT PARA USE16					;主程序段
		ASSUME	CS:CODEMSEG
START		PROC
            
			ASSUME  DS:GDTSEG
            MOV     AX,GDTSEG
            MOV     DS,AX
            
			MOV		BX,16
			MOV     AX,CODEMSEG
			MUL     BX
			MOV     WORD PTR CODEM.BASEL,AX		;计算并设置主程序段基地址
			MOV     BYTE PTR CODEM.BASEM,DL
			MOV     BYTE PTR CODEM.BASEH,DH            

			MOV     AX,TSS1SEG
			MUL     BX
			MOV     WORD PTR TSSTABLE1.BASEL,AX  ;计算并设置任务1基地址
			MOV     BYTE PTR TSSTABLE1.BASEM,DL
			MOV     BYTE PTR TSSTABLE1.BASEH,DH            
			MOV		BYTE PTR TSSTABLE1.ATTRIBUTES,AT386TSS	;任务段TSS1的段属性

			MOV     AX,TSS2SEG
			MUL     BX
			MOV     WORD PTR TSSTABLE2.BASEL,AX  ;计算并设置任务2基地址
			MOV     BYTE PTR TSSTABLE2.BASEM,DL
			MOV     BYTE PTR TSSTABLE2.BASEH,DH            
			MOV		BYTE PTR TSSTABLE2.ATTRIBUTES,AT386TSS	;任务段TSS2的段属性

			MOV     AX,TSS3SEG
			MUL     BX
			MOV     WORD PTR TSSTABLE3.BASEL,AX  ;计算并设置任务3基地址
			MOV     BYTE PTR TSSTABLE3.BASEM,DL
			MOV     BYTE PTR TSSTABLE3.BASEH,DH            
			MOV		BYTE PTR TSSTABLE3.ATTRIBUTES,AT386TSS	;任务段TSS3的段属性

			MOV     AX,DCODE2SEG
			MUL     BX
			MOV     WORD PTR DCODE2.BASEL,AX  ;计算并设置代码段2基地址
			MOV     BYTE PTR DCODE2.BASEM,DL
			MOV     BYTE PTR DCODE2.BASEH,DH            

			MOV     AX,DCODE3SEG
			MUL     BX
			MOV     WORD PTR DCODE3.BASEL,AX  ;计算并设置代码段3基地址
			MOV     BYTE PTR DCODE3.BASEM,DL
			MOV     BYTE PTR DCODE3.BASEH,DH            

			MOV     AX,DSTACK1SEG
			MUL     BX
			MOV     WORD PTR DSTACK1.BASEL,AX  ;计算并设置堆栈段1基地址
			MOV     BYTE PTR DSTACK1.BASEM,DL
			MOV     BYTE PTR DSTACK1.BASEH,DH            

			MOV     AX,DSTACK2SEG
			MUL     BX
			MOV     WORD PTR DSTACK2.BASEL,AX  ;计算并设置堆栈段2基地址
			MOV     BYTE PTR DSTACK2.BASEM,DL
			MOV     BYTE PTR DSTACK2.BASEH,DH            

			MOV     AX,DSTACK3SEG
			MUL     BX
			MOV     WORD PTR DSTACK3.BASEL,AX  ;计算并设置堆栈段3基地址
			MOV     BYTE PTR DSTACK3.BASEM,DL
			MOV     BYTE PTR DSTACK3.BASEH,DH            

			MOV     AX,DDATA1SEG
			MUL     BX
			MOV     WORD PTR DDATA1.BASEL,AX  ;计算并设置数据段1基地址
			MOV     BYTE PTR DDATA1.BASEM,DL 
			MOV     BYTE PTR DDATA1.BASEH,DH            

			MOV     AX,DDATA2SEG
			MUL     BX
			MOV     WORD PTR DDATA2.BASEL,AX  ;计算并设置数据段2基地址
			MOV     BYTE PTR DDATA2.BASEM,DL
			MOV     BYTE PTR DDATA2.BASEH,DH            

			MOV     AX,DDATASSEG
			MUL     BX
			MOV     WORD PTR DDATAS.BASEL,AX  ;计算并设置数据段3基地址
			MOV     BYTE PTR DDATAS.BASEM,DL
			MOV     BYTE PTR DDATAS.BASEH,DH            
;----------------------------------------------------------------------------
			ASSUME	DS:RDATASEG
			MOV		AX,RDATASEG
			MOV		DS,AX
			
			MOV		AX,GDTSEG
			MOV     BX,16      			    ;准备要加载到GDTR的伪描述符
      		MUL     BX
			ADD     AX,OFFSET GDT           ;计算并设置GDT基地址
			ADC     DX,0 
			MOV     WORD PTR VGDTR.BASE,AX
			MOV     WORD PTR VGDTR.BASE+2,DX
            
			MOV		AX,IDTSEG
      		MUL     BX
			ADD     AX,OFFSET IDT           ;计算并设置IDT基地址
			ADC     DX,0          
			MOV     WORD PTR VIDTR.BASE,AX
			MOV     WORD PTR VIDTR.BASE+2,DX
			
            MOV 	SSVAR,SS
            MOV 	SPVAR,SP				;保存实模式下堆栈指针
            
            IN		AL,21H					;中断屏蔽字寄存器端口地址
            MOV		REGV,AL					;保存中断屏蔽字节
            
			LGDT    QWORD PTR VGDTR			;装载GDTR
            SIDT	NORVIDTR				;保存IDTR值
            CLI                             ;关中断
            
			LIDT	QWORD	PTR	VIDTR		;置IDTR

            MOV     EAX,CR0					;切换到保护方式
            OR      EAX,1
            MOV     CR0,EAX                
            JUMP16  <CODEM_SEL>,<OFFSET VIRTUAL>;清指令预取队列,并真正进入保护方式    
                
VIRTUAL:    								;现在开始在保护方式下运行
			MOV		AX,TSS1_SEL					;装入任务1
			LTR		AX
			MOV		AX,DDATA1_SEL				;置数据段
			MOV		DS,AX
			MOV		ES,AX
			MOV		FS,AX
			MOV		GS,AX
			MOV		ESP,DSTACK1LEN-1
			MOV		AX,DSTACK1_SEL				;置堆栈
			MOV		SS,AX
			
			CALL16  TSS2_SEL,0              ;跳转到任务2的0级代码段
			
			MOV		AX,NORMAL_SEL			;把规范段描述符装入各数据据段寄存器
			MOV		DS,AX
			MOV		ES,AX
			MOV		FS,AX
			MOV		GS,AX
			MOV		SS,AX
    
	        MOV     EAX,CR0					   ;切换到实模式
            AND     AL,11111110B
            MOV     CR0,EAX
            JUMP16  <SEG REAL>,<OFFSET REAL>   ;清指令预取队列,进入实方式

REAL:   	  								;现在又回到实方式

			MOV     AX,RDATASEG
            MOV     DS,AX
            
            LSS		SP,DWORD	PTR	SPVAR	;恢复实模式下的堆栈
            LIDT	NORVIDTR				;恢复IDTR
            
            MOV		AL,REGV					;恢复中断屏蔽字节
            OUT		21H,AL
            

            ASSUME	DS:TSS2SEG
			MOV     AX,TSS2SEG
            MOV     DS,AX
            CALL	INIT_TSS2				;恢复TSS2任务段表的初值,以备下次继续运行

            ASSUME	DS:TSS3SEG
			MOV     AX,TSS3SEG
            MOV     DS,AX
            CALL	INIT_TSS3				;恢复TSS3任务段表的初值,以备下次继续运行
            
            STI								;开中断

			MOV 	AX,4C00H
			INT 	21H						;程序终止

START		ENDP
CODEMLEN	= $
;----------------------------------------------------------------------------
INIT_TSS2	PROC	NEAR	;恢复TSS2任务表的初值
		PUSH	DS
		MOV		AX,TSS2SEG
		MOV 	DS,AX

		MOV		SI,0		;链接字
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;0级堆栈指针
		MOV		AX,DSTACK2LEN
		MOV		[SI],AX
		
		ADD		SI,4		;0级堆栈选择子
		MOV		AX,DSTACK2_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;1级堆栈指针
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;1级堆栈选择子
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
		MOV		AX,DSTACK2LEN
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
		MOV		AX,DDATA2_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;CS
		MOV		AX,DCODE2_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;SS
		MOV		AX,DSTACK2_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;DS
		MOV		AX,DDATA2_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;FS
		MOV		AX,DDATA2_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;GS
		MOV		AX,DDATA2_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;LDTR
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;调试陷阱标志
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
INIT_TSS2		ENDP
;----------------------------------------------------------------------------
INIT_TSS3	PROC	NEAR	;恢复TSS3任务表的初值
		PUSH	DS
		MOV		AX,TSS3SEG
		MOV 	DS,AX

		MOV		SI,0		;链接字
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;0级堆栈指针
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;0级堆栈选择子
		MOV		AX,0
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
		MOV		AX,DSTACK3LEN
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
		MOV		AX,DDATAO_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;CS
		MOV		AX,DCODE3_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;SS
		MOV		AX,DSTACK3_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;DS
		MOV		AX,DDATAS_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;FS
		MOV		AX,DDATAS_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;GS
		MOV		AX,DDATAS_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;LDTR
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;调试陷阱标志
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
INIT_TSS3		ENDP
;----------------------------------------------------------------------------
DCODE2SEG	SEGMENT PARA USE16                ;任务2的0级代码段
                ASSUME  CS:DCODE2SEG	

				INT		20H					  ;用INT指令调用一个中断/异常处理程序来传送数据

                IRETD						  ;中断返回
                                                                                        
DCODE2LEN	= $
DCODE2SEG	ENDS                         
;----------------------------------------------------------------------------
DCODE3SEG	SEGMENT PARA USE16               	;任务3的3级代码段
                ASSUME  CS:DCODE3SEG
				
                MOV     AX, DDATAS_SEL
                MOV     DS,AX                   ;加载源数据段描述符
                MOV     AX, DDATAO_SEL
                MOV     ES,AX                   ;加载目标数据段描述符
                XOR     SI,SI
                XOR     DI,DI                   ;设置指针初值
                MOV     CX, 8		   		    ;设置传送长度
        M1:     MOVSB                  	        ;传送
                LOOP    M1                      
                
               	IRETD							;段间返回

DCODE3LEN	= $
DCODE3SEG	ENDS
;----------------------------------------------------------------------------
CODEMSEG	ENDS
;============================================================================
                END     START
