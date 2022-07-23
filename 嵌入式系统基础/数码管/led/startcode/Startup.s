;/****************************************Copyright (c)**************************************************
;**                                
;**                                 西南科技大学计算机学院
;**                                   
;**                                 http://cs.swust.edu.cn
;**            
;**             日期：   2004.11.9
;**             描述：  startup.s文件，堆栈大小定义，操作模式定义，异常向量表的定义
;**
;**------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
;/********************************************************************************************************/

;各操作模式下堆栈大小定义
USR_STACK_LEGTH         EQU         256
SVC_STACK_LEGTH         EQU         0
FIQ_STACK_LEGTH         EQU         16
IRQ_STACK_LEGTH         EQU         256
ABT_STACK_LEGTH         EQU         0
UND_STACK_LEGTH         EQU         0

NoInt       EQU 0x80
;操作模式定义
USR32Mode   EQU 0x10
SVC32Mode   EQU 0x13
SYS32Mode   EQU 0x1f
IRQ32Mode   EQU 0x12
FIQ32Mode   EQU 0x11

PINSEL2     EQU 0xE002C014

BCFG0       EQU 0xFFE00000
BCFG1       EQU 0xFFE00004
BCFG2       EQU 0xFFE00008
BCFG3       EQU 0xFFE0000C


;引入的外部标号在这声明
    IMPORT  FIQ_Exception                   ;快速中断异常处理程序
    IMPORT  __main                          ;C语言主程序入口 
    IMPORT  TargetResetInit                 ;目标板基本初始化
    IMPORT  StackUsr
    IMPORT  bottom_of_heap

;给外部使用的标号在这声明
    EXPORT  Reset
    EXPORT __rt_div0
    EXPORT __user_initial_stackheap
    
;/*******************************************************************************
;** 中断向量表的定义，子程序名：vectors.存储器重定位时利用该名字实现重新映射
;**           平时用户主要使用的异常主要为非向量中断，向量中断，以及快速中断
;********************************************************************************/                 
    CODE32
    
    AREA    vectors,CODE,READONLY 
        ENTRY
Reset
        LDR     PC, ResetAddr
        LDR     PC, UndefinedAddr
        LDR     PC, SWI_Addr
        LDR     PC, PrefetchAddr
        LDR     PC, DataAbortAddr
        DCD     0xb9205f80
        LDR     PC, [PC, #-0xff0]
        LDR     PC, FIQ_Addr

ResetAddr           DCD     ResetInit
UndefinedAddr       DCD     Undefined
SWI_Addr            DCD     SoftwareInterrupt
PrefetchAddr        DCD     PrefetchAbort
DataAbortAddr       DCD     DataAbort
Nouse               DCD     0
IRQ_Addr            DCD     0
FIQ_Addr            DCD     FIQ_Handler

;未定义指令
Undefined
        B       Undefined

;软中断
SoftwareInterrupt
        B       SoftwareInterrupt

;取指令中止
PrefetchAbort
        B       PrefetchAbort

;取数据中止
DataAbort
        B       DataAbort

;快速中断
FIQ_Handler
        STMFD   SP!, {R0-R3, LR}
        BL      FIQ_Exception
        LDMFD   SP!, {R0-R3, LR}
        SUBS    PC,  LR,  #4

;/*********************************************************************************************************
;**    程序名称，InitStack,   用于初始化处理器各种模式下堆栈的大小以及堆栈指针，
;**                           每个工程模块必须做这样的操作，否则导致中断程序的
;**                           不能正常返回，或函数调用的返回失败。
;********************************************************************************************************/
InitStack    
        MOV     R0, LR

;设置管理模式堆栈
        MSR     CPSR_c, #0xd3
        LDR     SP, StackSvc
;设置中断模式堆栈
        MSR     CPSR_c, #0xd2
        LDR     SP, StackIrq
;设置快速中断模式堆栈
        MSR     CPSR_c, #0xd1
        LDR     SP, StackFiq
;设置中止模式堆栈
        MSR     CPSR_c, #0xd7
        LDR     SP, StackAbt
;设置未定义模式堆栈
        MSR     CPSR_c, #0xdb
        LDR     SP, StackUnd
;设置系统模式堆栈
        MSR     CPSR_c, #0x5f;//#0xdf
        LDR     SP, =StackUsr

        MOV     PC, R0

;/*********************************************************************************************************
;** 函数名称: ResetInit
;** 功能描述: 复位入口
;**------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
ResetInit
;初始化外部总线控制器，根据目标板决定配置

        LDR     R0, =PINSEL2
    IF :DEF: EN_CRP
        LDR     R1, =0x0f814910
    ELSE
        LDR     R1, =0x0f814914
    ENDIF
        STR     R1, [R0]

        LDR     R0, =BCFG0
        LDR     R1, =0x1000ffef
        STR     R1, [R0]

        LDR     R0, =BCFG1
        LDR     R1, =0x1000ffef
        STR     R1, [R0]

        LDR     R0, =BCFG2
        LDR     R1, =0x1000ffef
        STR     R1, [R0]

;        LDR     R0, =BCFG3
;        LDR     R1, =0x2000ffef
;        STR     R1, [R0]
        
        BL      InitStack               ;初始化堆栈
        BL      TargetResetInit         ;目标板基本初始化
                                        ;跳转到c语言入口
        B       __main
        
;/*********************************************************************************************************
;** 函数名称: __user_initial_stackheap 
;** 功能描述: 库函数初始化堆和栈，不能删除
;** 
;** 输　入: 参考库函数手册
;**
;** 输　出: 参考库函数手册
;**------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
__user_initial_stackheap    
    LDR   r0,=bottom_of_heap
    MOV   pc,lr


;/*********************************************************************************************************
;** 函数名称: __rt_div0
;** 功能描述: 整数除法除数为0错误处理函数，替代原始的__rt_div0减少目标代码大小
;** 
;** 输　入: 参考库函数手册
;**------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
__rt_div0

        B       __rt_div0

StackSvc           DCD     SvcStackSpace + (SVC_STACK_LEGTH - 1)* 4
StackIrq           DCD     IrqStackSpace + (IRQ_STACK_LEGTH - 1)* 4
StackFiq           DCD     FiqStackSpace + (FIQ_STACK_LEGTH - 1)* 4
StackAbt           DCD     AbtStackSpace + (ABT_STACK_LEGTH - 1)* 4
StackUnd           DCD     UndtStackSpace + (UND_STACK_LEGTH - 1)* 4

;/*********************************************************************************************************
;** 函数名称: CrpData
;** 功能描述: 支持芯片加密功能
;**------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
    IF :DEF: EN_CRP
        IF  . >= 0x1fc
        INFO    1,"\nThe data at 0x000001fc must be 0x87654321.\nPlease delete some source before this line."
        ENDIF
CrpData
    WHILE . < 0x1fc
    NOP
    WEND
CrpData1
    DCD     0x87654321          ;/* 当此数为0x87654321时，用户程序被保护 */
    ENDIF
;/* 分配堆栈空间 */
        AREA    MyStacks, DATA, NOINIT, ALIGN=2
SvcStackSpace      SPACE   SVC_STACK_LEGTH * 4  ;管理模式堆栈空间
IrqStackSpace      SPACE   IRQ_STACK_LEGTH * 4  ;中断模式堆栈空间
FiqStackSpace      SPACE   FIQ_STACK_LEGTH * 4  ;快速中断模式堆栈空间
AbtStackSpace      SPACE   ABT_STACK_LEGTH * 4  ;中止义模式堆栈空间
UndtStackSpace     SPACE   UND_STACK_LEGTH * 4  ;未定义模式堆栈
    END
;/*********************************************************************************************************
;**                            End Of File
;********************************************************************************************************/
