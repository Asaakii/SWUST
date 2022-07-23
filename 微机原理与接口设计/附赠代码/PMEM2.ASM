;----------------------------------------------------------------------------
;文件名:PMEM2.ASM
;功能：分页机制
;	为了简单化,只有一个任务,并且没有LDT和IDT,不允许中断,
;	不考虑发生异常,不使用堆栈.SRAM:00000000H--0001FFFFH
;	外部存储器MY0地址空间：00080000H--0009FFFFH
;----------------------------------------------------------------------------
INCLUDE         386SCD.INC     
;----------------------------------------------------------------------------
;PL			=	1		;页存在属性位P值
;RWR		=	0		;R/W属性位值,读/执行
;RWW		=	2		;R/W属性位值,读/写/执行
;USS		=	0		;U/S属性值,系统级
;USU		=	4		;U/S属性值,用户级
PDT_AD		=	00010000H	;页目录表所在所理页的地址
PT_AD		=	00012000H	;页表所在所理页的地址
XIANXIN_AD	=	00301028H	;线性地址XIANXIN_AD
WULI_AD		=	00080028H	;线性地址XIANXIN_AD对应的物理地址
;----------------------------------------------------------------------------
DSEG		SEGMENT	PARA		USE16				;定义16位数据段
GDT			LABEL	BYTE							;全局描述符表
DUMMY		DESC		<>							;空描述符
NORMAL		DESC	<0FFFFH,,,ATDW,,>				;规范段描述符
PDTABLE		DESC	<0FFFFH,PDT_AD AND 0FFFFH,PDT_AD SHR 16,ATDW,,>	;页目录表所在段描述符
PTABLE		DESC	<0FFFFH,PT_AD AND 0FFFFH,PT_AD SHR 16,ATDW,,>	;页表所在段描述符
CODEM		DESC	<0FFFFH,,,ATCE,,>				;主代码段描述符
PCODE		DESC	<0FFFFH,,,ATCE,,>				;分页机制代码段描述符
DDATA		DESC	<0FFFFH,,,ATDW,,>				;源数据段描述符
DATAO		DESC	<0FFFFH,XIANXIN_AD AND 0FFFFH,XIANXIN_AD SHR 16,ATDW,,>	;目标数据段描述符
NORMAL_SEL	=		NORMAL-GDT						;规范段描述符选择子
PDT_SEL		=		PDTABLE-GDT						;页目录表所在段描述符选择子
PT_SEL		=		PTABLE-GDT						;页表所在段描述符选择子
CODEM_SEL	=		CODEM-GDT						;主代码段选择子
PCODE_SEL	=		PCODE-GDT						;分页机制代码段描述符选择子
DDATA_SEL	=		DDATA-GDT						;源数据段描述符选择子
DATAO_SEL	=		DATAO-GDT						;目标数据段选择子

GDTLEN		=		$-GDT							;全局描述符表长度

VGDTR		PDESC	<GDTLEN-1,>						;伪描述符VGDTR
SPVAR 			 DW  ?
SSVAR 			 DW  ?								;保存实模式下堆栈指针

DSEG			ENDS								;数据段定义结束
;----------------------------------------------------------------------------
DDATASEG		SEGMENT	PARA		USE16			;定义16位源数据段
MESS		DB 'Page Is Successful!  ','$'			;字符$表示字符串结束
ML			=	$-MESS								;字符串的长度
DDATASEG		ENDS								;源数据段定义结束
;----------------------------------------------------------------------------
CSEG	SEGMENT	USE16					;16位主代码段
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
		MOV		WORD PTR VGDTR.BASE+2,DX
		;设置主代码段描述符
		MOV		AX,CS
		MUL		BX							;代码段地址左移4位
		MOV		WORD PTR CODEM.BASEL,AX		;代码段开始偏移为0
		MOV		BYTE PTR CODEM.BASEM,DL		;将得到的物理地址填入CODEM描述符
		MOV		BYTE PTR CODEM.BASEH,DH
		;设置分页机制代码段描述符
		MOV		AX,PCODESEG
		MUL		BX							;分页机制代码段地址左移4位
		MOV		WORD PTR PCODE.BASEL,AX		;代码段开始偏移为0
		MOV		BYTE PTR PCODE.BASEM,DL		;将得到的物理地址填入CODEM描述符
		MOV		BYTE PTR PCODE.BASEH,DH
		;设置源代码段描述符
		MOV		AX,DDATASEG 
		MUL		BX							;源数据段地址左移4位
		MOV		WORD PTR DDATA.BASEL,AX		;源数据段开始偏移为0
		MOV		BYTE PTR DDATA.BASEM,DL		;将得到的物理地址填入DATAS描述符
		MOV		BYTE PTR DDATA.BASEH,DH
;----------------------------------------------------------------------------
		MOV		SSVAR,SS
		MOV		SPVAR,SP					;保存实模式下堆栈指针
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

		JUMP16	<PCODE_SEL>,INIT_PDT

TOREAL:
		MOV		AX,NORMAL_SEL				;把规范段描述符装入各数据据段寄存器
		MOV		DS,AX
		MOV		ES,AX
		MOV		FS,AX
		MOV		GS,AX
		MOV		SS,AX
		;切换回实模式
		MOV		EAX,CR0
		AND		AL,11111110B
		MOV		CR0,EAX
		;清指令预取队列,进入实方式
		JUMP16	<SEG REAL>,<OFFSET REAL>
REAL:	;现在又回到实方式
		MOV     AX,DSEG
		MOV     DS,AX
		LSS		SP,DWORD	PTR	SPVAR		;恢复实模式下的堆栈

		MOV		AX,(WULI_AD SHR 16) SHL 12
		MOV		DS,AX						;送目标数据段
		MOV		DX,OFFSET (WULI_AD AND 0FFFFH)
		MOV		AH,09H
		INT		21H							;用INT 21H功能调用显示BUF数据段的内容

		STI									;开中断
		
		MOV 	AX,4C00H
		INT 	21H							;程序终止

START		ENDP
;----------------------------------------------------------------------------
PCODESEG		SEGMENT		PARA	USE16	;初始化页描述符,启动分页机制,16位代码段
			ASSUME	CS:PCODESEG
INIT_PDT:									;开始初始化页目录
		MOV		AX,PDT_SEL
		MOV		ES,AX
		XOR		DI,DI
		MOV		CX,1024
		XOR		EAX,EAX						;把页目录表PDT中全部表项置成无效
		REP		STOSD
											;置页目录表中表项PT
		MOV		DWORD PTR ES:[0],PT_AD OR (USS+RWW+PL);将页表的地址送到ES段的0偏移32位
		MOV		AX,PT_SEL					;初始化页表
		MOV		ES,AX
		XOR		DI,DI
		MOV		CX,1024
		XOR		EAX,EAX
		OR		EAX,USS+RWW+PL
PTLOOP:		STOSD
		ADD		EAX,1000H					;先全部置成直接对应等地址的物理页
		LOOP	PTLOOP						;再特别设置一项
		MOV		DI,(XIANXIN_AD SHR 12)*4	;将线性地址的中间10位(12-21)作为已指定页表的索引
		MOV		DWORD PTR ES:[DI],WULI_AD+USU+RWW+PL;将物理地址送到ES段的DI偏移32位
				
		MOV		EAX,PDT_AD					;页目录表的地址00010000H送给CR3
		MOV		CR3,EAX
		MOV		EAX,CR0						;控制寄存器CR0最高位置为1,使分页机制有效
		OR		EAX,80000000H
		MOV		CR0,EAX						;启动分页机制
		JMP		SHORT	PAGEE
PAGEE:

;----------------------------------------------------------------------------
		MOV		AX,DDATA_SEL				;送源数据段选择子
		MOV		DS,AX	
		MOV		AX,DATAO_SEL				;送目标数据段选择子
		MOV		ES,AX
		XOR		DI,DI						;DI清零
		XOR		SI,SI						;SI清零
		MOV		CX,ML						;设置数据长度
		REPZ	MOVSB						;通过串传送指令传数
;----------------------------------------------------------------------------
PTT:
		MOV		EAX,CR0						;关闭分页机制
		AND		EAX,7FFFFFFFH
		MOV		CR0,EAX

		JUMP16	<CODEM_SEL>,TOREAL			;转向主代码段,准备退出保护模式
				
PCODELEN	=	$
PCODESEG		ENDS
;----------------------------------------------------------------------------
CSEG			ENDS						;代码段定义结束
;----------------------------------------------------------------------------
		END     START




