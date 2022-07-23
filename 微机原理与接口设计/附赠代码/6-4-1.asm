;----------------------------------------------------------------------------
;文件名:6-4-1.ASM
;功能:通过中断门或陷阱门转移的中断/异常处理
;----------------------------------------------------------------------------
INCLUDE         386SCD.INC
;----------------------------------------------------------------------------
GDTSEG          SEGMENT PARA USE16                  ;全局描述符表数据段(16位)
;----------------------------------------------------------------------------
GDT             LABEL   BYTE						;全局描述符表
DUMMY           DESC    <>                   		;空描述符
NORMAL			DESC	<0FFFFH,,,ATDW,,>			;规范段描述符
CODEM           DESC    <0FFFFH,CODEMSEG,,ATCE,,>    	;主程序段描述符
DCODE			DESC    <0FFFFH,DCODESEG,,ATCE,,>		;DCODESEG代码段描述符
ICODE			DESC    <0FFFFH,ICODESEG,,ATCE,,>		;异常/中断处理代码段描述符
DSTACK0			DESC    <0FFFFH,DSTACK0SEG,,ATDW,,>		;0级堆栈段描述符
DDATAS			DESC	<0FFFFH,DDATASSEG,,ATDW,,>		;源数据段描述符
DDATAO			DESC	<0FFFFH,3000H,,ATDW,,>			;目的数据段描述符
;----------------------------------------------------------------------------
NORMAL_SEL		=		NORMAL-GDT					;规范段描述符选择子
CODEM_SEL       =       CODEM-GDT                   ;主程序段选择子
DCODE_SEL       =       DCODE-GDT                   ;DCODESEG代码段选择子
ICODE_SEL       =       ICODE-GDT                   ;异常/中断处理代码段选择子
DSTACK0_SEL		=		DSTACK0-GDT					;0级堆栈段选择子
DDATAS_SEL		=		DDATAS-GDT					;源数据段选择子
DDATAO_SEL		=		DDATAO-GDT					;目的数据段选择子
GDTLEN          =       $-GDT            	        ;全局描述符表长度
GDTSEG          ENDS                                ;全局描述符表段定义结束
;----------------------------------------------------------------------------
IDTSEG		SEGMENT		PARA	USE16			;16位中断/异常处理程序段
IDT			LABEL		BYTE					;定义中断描述符表IDT
			REPT	32							;从00H---1FH的32个空中断门描述符
			GATE	<,,,AT386IGATE,>
			ENDM
			
INT20		GATE    <0,ICODE_SEL,,AT386IGATE,>	;对应20H号异常/中断处理程序段的中断门描述符

			REPT	256-33						;从21H---FFH的223个空中断门描述符
			GATE	<,,,AT386IGATE,>
			ENDM
			
IDTLEN		=	$-IDT							;中断描述符表长度
IDTSEG		ENDS								;16位中断/异常处理程序段结束
;----------------------------------------------------------------------------
DSTACK0SEG   	SEGMENT PARA   USE16              ;0级堆栈段(16位段)
DSTACK0LEN	=       1024
                DB      DSTACK0LEN DUP(0)		  ;定义1024个缓冲字节单元
DSTACK0SEG	ENDS                              	  ;0级堆栈段结束
;----------------------------------------------------------------------------
DDATASSEG	SEGMENT	PARA USE16					;源数据段
DTEST		DB	11H,22H,33H,44H,55H,66H,77H,88H	;定义源数据段数据
DDATASLEN	=	$								;数据段的长度
DDATASSEG	ENDS								;源数据段定义结束
;========================================================================
RDATASEG		SEGMENT		PARA	USE16		;实模式下的数据段
VGDTR           PDESC   <GDTLEN-1,>             ;GDT伪描述符
VIDTR			PDESC	<IDTLEN-1,>				;IDT伪描述符
NORVIDTR		PDESC	<3FFH,0>				;用于保存原IDTR值
SPVAR			DW  ?
SSVAR			DW  ?							;保存实模式下的堆栈指针
REGV			DB	?							;用于保存原中断屏蔽寄存器值
RDATASEG		ENDS
;----------------------------------------------------------------------------
CODEMSEG	SEGMENT PARA USE16
			ASSUME	CS:CODEMSEG
START		PROC
			ASSUME  DS:GDTSEG
            MOV     AX,GDTSEG
            MOV     DS,AX
            
			MOV     BX,16 
			MOV     AX,CODEMSEG
			MUL     BX
			MOV     WORD PTR CODEM.BASEL,AX  ;计算并设置主程序段基地址
			MOV     BYTE PTR CODEM.BASEM,DL
			MOV     BYTE PTR CODEM.BASEH,DH            
			
			MOV     AX,DCODESEG
			MUL     BX
			MOV     WORD PTR DCODE.BASEL,AX  ;计算并设置DCODESEG代码段基地址
			MOV     BYTE PTR DCODE.BASEM,DL
			MOV     BYTE PTR DCODE.BASEH,DH            
			
			MOV     AX,ICODESEG
			MUL     BX
			MOV     WORD PTR ICODE.BASEL,AX  ;计算并设置中断代码段基地址
			MOV     BYTE PTR ICODE.BASEM,DL
			MOV     BYTE PTR ICODE.BASEH,DH            
			
			MOV     AX,DSTACK0SEG
			MUL     BX
			MOV     WORD PTR DSTACK0.BASEL,AX  ;计算并设置堆栈段0基地址
			MOV     BYTE PTR DSTACK0.BASEM,DL
			MOV     BYTE PTR DSTACK0.BASEH,DH            
			
			MOV     AX,DDATASSEG
			MUL     BX
			MOV     WORD PTR DDATAS.BASEL,AX  ;计算并设置源数据基地址
			MOV     BYTE PTR DDATAS.BASEM,DL
			MOV     BYTE PTR DDATAS.BASEH,DH            
;-----------------------------------------------------------		
			ASSUME	DS:RDATASEG
			MOV		AX,RDATASEG
			MOV		DS,AX
			
			MOV		AX,GDTSEG
			MOV     BX,16
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
			
;-----------------------------------------------------------		
            MOV 	SSVAR,SS
            MOV 	SPVAR,SP			;保存实模式下的堆栈指针
            
            IN		AL,21H				;中断屏蔽字寄存器端口地址
            MOV		REGV,AL				;保存中断屏蔽字节
            
			LGDT    QWORD PTR VGDTR		;装载GDTR
            SIDT	NORVIDTR			;保存IDTR值
            CLI                         ;关中断
            
            LIDT	QWORD	PTR	VIDTR	;置IDTR
            
            MOV     EAX,CR0             ;切换到保护方式
            OR      EAX,1
            MOV     CR0,EAX                
            
            JUMP16  <CODEM_SEL>,<OFFSET VIRTUAL>     ;清指令预取队列,并真正进入保护方式
;-----------------------------------------------------------		
VIRTUAL:    						;现在开始在保护方式下运行
			CALL16  DCODE_SEL,0		;跳转到到DCODESEG代码段				
			
			MOV		AX,NORMAL_SEL	;准备返回实模式
			MOV		DS,AX			;把规范段描述符装入各数据段寄存器
			MOV		ES,AX
			MOV		FS,AX
			MOV		GS,AX
			MOV		SS,AX
    
	        MOV     EAX,CR0					   ;切换到实模式
            AND     AL,11111110B
            MOV     CR0,EAX
            JUMP16  <SEG REAL>,<OFFSET REAL>   ;清指令预取队列,进入实方式

REAL:   										;现在又回到实方式
			MOV     AX,RDATASEG
            MOV     DS,AX
            LSS		SP,DWORD	PTR	SPVAR		;恢复实模式下的堆栈指针
            LIDT	NORVIDTR					;恢复IDTR
            
            MOV		AL,REGV						;恢复中断屏蔽字节
            OUT		21H,AL
                        
            STI									;开中断

			MOV 	AX,4C00H
			INT 	21H							;程序终止
		
		
START		ENDP
CODEMLEN	= $
CODEMSEG	ENDS
;----------------------------------------------------------------------------
DCODESEG   SEGMENT PARA USE16        ;DCODESEG的16位代码段
           ASSUME  CS:DCODESEG
           MOV     AX, DDATAS_SEL
           MOV     DS,AX             ;加载源数据段描述符
           MOV     AX, DDATAO_SEL
           MOV     ES,AX             ;加载目标数据段描述符
           XOR     SI,SI
           XOR     DI,DI			;设置指针初值
           MOV     CX, 8			;设置传送长度
  		   INT		20H				;用INT指令调用一个中断/异常处理程序来传送数据
		   RETF				    	;中断返回
DCODELEN	= $
DCODESEG	ENDS                    ;DCODESEG的16位代码段结束
;----------------------------------------------------------------------------
ICODESEG   SEGMENT PARA USE16           ;异常/中断处理代码段
           ASSUME  CS:ICODESEG
                
		  PUSHAD						;保护现场
				
  M1:     MOVSB                  	    ;传送
          LOOP    M1
                 
   		  POPAD							;恢复现场
				
		  IRETD							;段间返回      
				          
ICODELEN	=$

ICODESEG     	ENDS
;============================================================================
                END     START

