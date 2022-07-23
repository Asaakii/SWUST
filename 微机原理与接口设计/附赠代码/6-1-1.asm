;----------------------------------------------------------------------------
;文件名:6-1-1.ASM
;功能:全局描述符及全局描述符表实验
;----------------------------------------------------------------------------
INCLUDE         386SCD.INC
;数据段==========================================================
DSEG            SEGMENT USE16                	 ;定义16位数据段
GDT             LABEL   BYTE                 	 ;全局描述符表
DUMMY           DESC    <>                   	 ;空描述符
CODEM           DESC    <0FFFFH,,,ATCE,,>    	 ;代码段描述符
DATAS           DESC    <0FFFFH,,,ATDW,,>   	 ;源数据段描述符
DATAD           DESC    <0FFFFH,3000H,,ATDW,,>   ;目标数据段描述符
VGDTR           PDESC   <GDTLEN-1,>				 ;伪描述符
GDTLEN          =       $-GDT           	      ;全局描述符表长度
CODEM_SEL       =       CODEM-GDT        	      ;代码段选择子
DATAS_SEL       =       DATAS-GDT       	      ;源数据段选择子
DATAD_SEL       =       DATAD-GDT       	      ;目标数据段选择子
DSEG            ENDS							  ;数据段定义结束
;==========================================================
DSEG1		SEGMENT PARA	USE16				  ;定义16位源数据段
TDATA           DW    1111H, 2222H, 3333H, 4444H  ;定义原数据段数据
                DW    5555H, 6666H, 7777H, 8888H
D1LEN		=$-TDATA							  ;数据段的长度
DSEG1		ENDS								  ;源数据段定义结束
;代码段=========================================================
CSEG		SEGMENT USE16							;16位代码段
                ASSUME CS:CSEG,DS:DSEG
START		PROC
                MOV     AX,DSEG
                MOV     DS,AX
                ;准备要加载到GDTR的伪描述符
                MOV		BX,16						;计算并设置GDT基地址
                MUL		BX							;数据段地址左移4位
                MOV		WORD PTR VGDTR.BASE,AX		;将得到的物理地址填入VGDTR描述符
                MOV		WORD PTR VGDTR.BASE+2,DX
               ;设置代码段描述符
				MOV		AX,CS						;计算并设置源数据段基址
				MUL		BX							;代码段地址左移4位
				MOV		WORD PTR CODEM.BASEL,AX		;代码段开始偏移为0
				MOV 	BYTE PTR CODEM.BASEM,DL		;将得到的物理地址填入CODEM描述符
				MOV 	BYTE PTR CODEM.BASEH,DH
				;设置源数据段描述符
				MOV 	AX,DSEG1					;计算并设置源数据段基址
				MUL		BX							;;源数据段地址左移4位
				ADD 	AX,OFFSET TDATA				;加上TDATA的偏移得到物理地址	
				ADC		DX,0
				MOV 	WORD PTR DATAS.BASEL,AX		;将得到的物理地址填入DATAS描述符
				MOV 	BYTE PTR DATAS.BASEM,DL
				MOV 	BYTE PTR DATAS.BASEH,DH
                ;加载GDTR
                LGDT    QWORD PTR VGDTR
                CLI                        		    ;关中断
                ;切换到保护方式
                MOV     EAX,CR0
                OR      EAX,1
                MOV     CR0,EAX
                ;清指令预取队列,并真正进入保护方式
                JUMP16  <CODEM_SEL>,<OFFSET VIRTUAL>
VIRTUAL:        ;现在开始在保护方式下运行
                MOV     AX,DATAS_SEL
                MOV     DS,AX                   ;加载源数据段描述符
                MOV		AX,DATAD_SEL
                MOV     ES,AX					;加载目标数据段描述符
                XOR		DI,DI					;DI清零
                XOR     SI,SI					;SI清零
                MOV     CX,D1LEN                ;设置数据长度

M1:				MOVSB							;通过串传送指令传数
				LOOP M1
                
                ;切换回实模式
                MOV     EAX,CR0
                AND     AL,11111110B
                MOV     CR0,EAX
                ;清指令预取队列,进入实方式
                JUMP16  <SEG REAL>,<OFFSET REAL>
REAL:           ;现在又回到实方式
                STI								;开中断

				MOV 	AX,4C00H
				INT 	21H						;程序终止

START		ENDP
CLEN		=$-1
CSEG		ENDS
		END		START
