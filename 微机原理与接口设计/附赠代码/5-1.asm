;----------------------------------------------------------------------------
;文件名:5-1.ASM
;功能:学习实模式和保护模式的切换
;----------------------------------------------------------------------------
;存储段描述符结构定义
DESC			STRUC
LIMITL		DW	0	;段界限(BIT0-15)
BASEL		DW	0	;段基地址(BIT0-15)
BASEM		DB	0	;段基地址(BIT16-23)
ATTRIBUTES	DB	0	;段属性
LIMITH		DB	0	;段界限(BIT16-19)(含段属性的高4位)
BASEH		DB	0	;段基地址(BIT24-31)
DESC			ENDS
;----------------------------------------------------------------------------
;常量定义
ATDW			EQU	92H	;存在的可读写数据段属性值
ATCE			EQU	98H	;存在的只执行代码段属性值
;----------------------------------------------------------------------------
;伪描述符结构类型定义
PDESC		STRUC
LIMIT		DW	0	;16位界限
BASE		DD	0	;32位基地址
PDESC		ENDS
;----------------------------------------------------------------------------
;16位偏移的段间直接转移指令的宏定义
JUMP16		MACRO	SELECTOR,OFFSET
DB			0EAH		;操作码
DW			OFFSET		;16位偏移量
DW			SELECTOR	;段值或段选择子
			ENDM
;----------------------------------------------------------------------------
.386P		; 386P伪指令
;----------------------------------------------------------------------------
DSEG		SEGMENT	PARA		USE16			;定义16位数据段
GDT			LABEL	BYTE						;全局描述符表
DUMMY		DESC		<>						;空描述符
CODEM		DESC		<0FFFFH,,,ATCE,,>		;代码段描述符
DATAS		DESC		<0FFFFH,,,ATDW,,>		;源数据段描述符
DATAD		DESC		<0FFFFH,,,ATDW,,>		;目标数据段描述符
VGDTR		PDESC		<GDTLEN-1,>				;伪描述符
GDTLEN		=			$-GDT					;全局描述符表长度
CODEM_SEL		=		CODEM-GDT				;代码段选择子
DATAS_SEL		=		DATAS-GDT				;源数据段选择子
DATAD_SEL		=		DATAD-GDT				;目标数据段选择子
DSEG			ENDS							;数据段定义结束
;----------------------------------------------------------------------------
DATA1		SEGMENT	PARA		USE16			;定义16位源数据段
MES1		DB 'This is tangdu speak!','$'		;$为字符串结束标志
ML			=	$-MES1							;字符串的长度
DATA1		ENDS								;源数据段定义结束
;----------------------------------------------------------------------------
DATA2		SEGMENT	PARA		USE16			;定义16位目标数据段
BUF			DB	64 DUP(?)						;定义64个缓冲区字节单元
DATA2		ENDS								;目标数据段定义结束
;----------------------------------------------------------------------------
CSEG		SEGMENT	USE16					;16位代码段
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
		;设置源代码段描述符
		MOV		AX,DATA1 
		MUL		BX							;源数据段地址左移4位
		MOV		WORD PTR DATAS.BASEL,AX		;源数据段开始偏移为0
		MOV		BYTE PTR DATAS.BASEM,DL		;将得到的物理地址填入DATAS描述符
		MOV		BYTE PTR DATAS.BASEH,DH
		;设置目标代码段描述符
		MOV		AX,DATA2 
		MUL		BX							;目标数据段地址左移4位
		MOV		WORD PTR DATAD.BASEL,AX		;目标数据段开始偏移为0
		MOV		BYTE PTR DATAD.BASEM,DL		;将得到的物理地址填入DATAD描述符
		MOV		BYTE PTR DATAD.BASEH,DH
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
		MOV		DS,AX					;加载源数据段描述符
		MOV		AX,DATAD_SEL
		MOV		ES,AX					;加载目标数据段描述符
		XOR		DI,DI					;DI清零
		XOR		SI,SI					;SI清零
		MOV		CX,ML					;设置数据长度
		REPZ	MOVSB					;通过串传送指令传数
		;切换回实模式
		MOV		EAX,CR0
		AND		AL,11111110B
		MOV		CR0,EAX
		;清指令预取队列,进入实方式
		JUMP16	<SEG REAL>,<OFFSET REAL>
REAL:	;现在又回到实方式
		STI								;开中断
		MOV		AX,DATA1
		MOV		DS,AX					;送源数据段
		MOV		DX,OFFSET MES1
		MOV		AH,09H
		INT		21H						;用INT 21H功能调用显示MES1数据段的内容
		
		MOV		AH,02H
		MOV 	DL,0DH
		INT 	21H						;回车
		MOV 	AH,02H
		MOV 	DL,0AH
		INT 	21H						;换行

		MOV		AX,DATA2
		MOV		DS,AX					;送目标数据段
		MOV		DX,OFFSET BUF
		MOV		AH,09H
		INT		21H						;用INT 21H功能调用显示BUF数据段的内容
		MOV 	AX,4C00H
		INT 	21H						;程序终止
START		ENDP
;----------------------------------------------------------------------------
CSEG			ENDS					;代码段定义结束
;----------------------------------------------------------------------------
		END     START
