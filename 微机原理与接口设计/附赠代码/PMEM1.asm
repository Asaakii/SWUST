;----------------------------------------------------------------------------
;文件名:PMEM1.ASM
;实验内容：利用保护模式机制,实现外部存贮器扩展实验.
;	 此实验需要接线,把存储器的地址、数据、读写、字节使能及片选分别接到总线上。
;	 从00080000H的地址空间开始将一段数传至从00080028H开始的地址空间中,
;	 数据为30-39,41-5A   并将它的ASCII值在屏幕上显出来.
;----------------------------------------------------------------------------
XIANXIN_WULI_AD1	=	00080000H	;线性地址1(不分页时就是物理地址)
XIANXIN_WULI_AD2	=	00080028H	;线性地址2(不分页时就是物理地址)
;----------------------------------------------------------------------------
INCLUDE         386SCD.INC     
;----------------------------------------------------------------------------
DSEG		SEGMENT	PARA		USE16					;定义16位数据段
GDT			LABEL	BYTE								;全局描述符表
DUMMY		DESC		<>								;空描述符
CODEM		DESC		<0FFFFH,,,ATCE,,>				;代码段描述符
DATAS		DESC		<0FFFFH,XIANXIN_WULI_AD1 AND 0FFFFH,XIANXIN_WULI_AD1 SHR 16,ATDW,,>;源数据段描述符
DATAO		DESC		<0FFFFH,XIANXIN_WULI_AD2 AND 0FFFFH,XIANXIN_WULI_AD2 SHR 16,ATDW,,>;目标数据段描述符
VGDTR		PDESC		<GDTLEN-1,>						;伪描述符
GDTLEN		=			$-GDT							;全局描述符表长度
CODEM_SEL	=		CODEM-GDT							;代码段选择子
DATAS_SEL	=		DATAS-GDT							;源数据段选择子
DATAO_SEL	=		DATAO-GDT							;目标数据段选择子
DSEG			ENDS									;数据段定义结束
;----------------------------------------------------------------------------
CSEG	SEGMENT	USE16							;16位代码段
		ASSUME	CS:CSEG,DS:DSEG
START	PROC
		MOV		AX,DSEG
		MOV		DS,AX
		;准备要加载到GDTR的伪描述符
		MOV		BX,16
		MUL		BX							;数据段地址左移4位
		ADD		AX,OFFSET GDT				;加上GDT的偏移得到物理地址
		ADC		DX,0
		MOV		WORD PTR VGDTR.BASE,AX		;将得到的物理地址填入VGDTR描述符
		MOV		WORD PTR VGDTR.BASE+2,DX;
		;设置代码段描述符
		MOV		AX,CS
		MUL		BX							;代码段地址左移4位
		MOV		WORD PTR CODEM.BASEL,AX		;代码段开始偏移为0
		MOV		BYTE PTR CODEM.BASEM,DL		;将得到的物理地址填入CODEM描述符
		MOV		BYTE PTR CODEM.BASEH,DH
;----------------------------------------------------------------------------
		MOV		AX,(XIANXIN_WULI_AD1 SHR 16) SHL 12	;给地址从00080000H开始写数30-39
		MOV		DS,AX
		MOV		SI,(XIANXIN_WULI_AD1 AND 0FFFFH)	
		MOV		CX,10						;送10个数据
		MOV		AX,30H						;从30H开始
MEM1:	MOV		[SI],AX
		INC		SI
		ADD		AX,1
		LOOP	MEM1
			
		MOV		CX,26						;给地址从0008000AH开始写数41-5A
		MOV		AX,41H						;从A到Z总数26个数
MEM2:	MOV		[SI],AX
		INC		SI
		ADD		AX,1
		LOOP	MEM2
;----------------------------------------------------------------------------
		MOV		AX,DSEG
		MOV		DS,AX
		;加载GDTR
		LGDT		QWORD PTR VGDTR
		CLI									;关中断
		;切换到保护方式
		MOV		EAX,CR0
		OR		EAX,1
		MOV		CR0,EAX
		;清指令预取队列,并真正进入保护方式
		JUMP16	<CODEM_SEL>,<OFFSET VIRTUAL>
VIRTUAL:	;现在开始在保护方式下运行
		MOV		AX,DATAS_SEL
		MOV		DS,AX						;加载源数据段描述符
		MOV		AX,DATAO_SEL
		MOV		ES,AX						;加载目标数据段描述符
		XOR		DI,DI						;DI清零
		XOR		SI,SI						;SI清零
		MOV		CX,36						;设置数据长度
		REPZ	MOVSB						;通过串传送指令传数
		;切换回实模式
		MOV		EAX,CR0
		AND		AL,11111110B
		MOV		CR0,EAX
		;清指令预取队列,进入实方式
		JUMP16	<SEG REAL>,<OFFSET REAL>
REAL:	;现在又回到实方式
;----------------------------------------------------------------------------
		MOV		AX,(XIANXIN_WULI_AD2 SHR 16) SHL 12	;从地址00080028H开始输出数0-9
        MOV     DS,AX
        MOV		CX,0AH
        MOV     SI,(XIANXIN_WULI_AD2 AND 0FFFFH)	
MEMO1:  MOV		DL,[SI]
        MOV		AH,02H
        INT     21H						;用INT 21H功能调用输出字符
        ADD		SI,1
        LOOP	MEMO1
             
        MOV		CX,1AH					;从地址00080032H开始输出字母A-Z
MEMO2:  MOV     DL,[SI]
        MOV		AH,02H
        INT     21H						;用INT 21H功能调用输出字符
        ADD		SI,1
        LOOP	MEMO2
		STI								;开中断

		MOV 	AX,4C00H
		INT 	21H						;程序终止
			
START		ENDP
;----------------------------------------------------------------------------
CSEG			ENDS					;代码段定义结束
;----------------------------------------------------------------------------
		END     START
