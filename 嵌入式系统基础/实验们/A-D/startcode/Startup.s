;/****************************************Copyright (c)**************************************************
;**                                
;**                                 ���ϿƼ���ѧ�����ѧԺ
;**                                   
;**                                 http://cs.swust.edu.cn
;**            
;**             ���ڣ�   2004.11.9
;**             ������  startup.s�ļ�����ջ��С���壬����ģʽ���壬�쳣������Ķ���
;**
;**------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
;/********************************************************************************************************/

;������ģʽ�¶�ջ��С����
USR_STACK_LEGTH         EQU         256
SVC_STACK_LEGTH         EQU         0
FIQ_STACK_LEGTH         EQU         16
IRQ_STACK_LEGTH         EQU         256
ABT_STACK_LEGTH         EQU         0
UND_STACK_LEGTH         EQU         0

NoInt       EQU 0x80
;����ģʽ����
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


;������ⲿ�����������
    IMPORT  FIQ_Exception                   ;�����ж��쳣�������
    IMPORT  __main                          ;C������������� 
    IMPORT  TargetResetInit                 ;Ŀ��������ʼ��
    IMPORT  StackUsr
    IMPORT  bottom_of_heap

;���ⲿʹ�õı����������
    EXPORT  Reset
    EXPORT __rt_div0
    EXPORT __user_initial_stackheap
    
;/*******************************************************************************
;** �ж�������Ķ��壬�ӳ�������vectors.�洢���ض�λʱ���ø�����ʵ������ӳ��
;**           ƽʱ�û���Ҫʹ�õ��쳣��ҪΪ�������жϣ������жϣ��Լ������ж�
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

;δ����ָ��
Undefined
        B       Undefined

;���ж�
SoftwareInterrupt
        B       SoftwareInterrupt

;ȡָ����ֹ
PrefetchAbort
        B       PrefetchAbort

;ȡ������ֹ
DataAbort
        B       DataAbort

;�����ж�
FIQ_Handler
        STMFD   SP!, {R0-R3, LR}
        BL      FIQ_Exception
        LDMFD   SP!, {R0-R3, LR}
        SUBS    PC,  LR,  #4

;/*********************************************************************************************************
;**    �������ƣ�InitStack,   ���ڳ�ʼ������������ģʽ�¶�ջ�Ĵ�С�Լ���ջָ�룬
;**                           ÿ������ģ������������Ĳ������������жϳ����
;**                           �����������أ��������õķ���ʧ�ܡ�
;********************************************************************************************************/
InitStack    
        MOV     R0, LR

;���ù���ģʽ��ջ
        MSR     CPSR_c, #0xd3
        LDR     SP, StackSvc
;�����ж�ģʽ��ջ
        MSR     CPSR_c, #0xd2
        LDR     SP, StackIrq
;���ÿ����ж�ģʽ��ջ
        MSR     CPSR_c, #0xd1
        LDR     SP, StackFiq
;������ֹģʽ��ջ
        MSR     CPSR_c, #0xd7
        LDR     SP, StackAbt
;����δ����ģʽ��ջ
        MSR     CPSR_c, #0xdb
        LDR     SP, StackUnd
;����ϵͳģʽ��ջ
        MSR     CPSR_c, #0x5f;//#0xdf
        LDR     SP, =StackUsr

        MOV     PC, R0

;/*********************************************************************************************************
;** ��������: ResetInit
;** ��������: ��λ���
;**------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
ResetInit
;��ʼ���ⲿ���߿�����������Ŀ����������

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
        
        BL      InitStack               ;��ʼ����ջ
        BL      TargetResetInit         ;Ŀ��������ʼ��
                                        ;��ת��c�������
        B       __main
        
;/*********************************************************************************************************
;** ��������: __user_initial_stackheap 
;** ��������: �⺯����ʼ���Ѻ�ջ������ɾ��
;** 
;** �䡡��: �ο��⺯���ֲ�
;**
;** �䡡��: �ο��⺯���ֲ�
;**------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
__user_initial_stackheap    
    LDR   r0,=bottom_of_heap
    MOV   pc,lr


;/*********************************************************************************************************
;** ��������: __rt_div0
;** ��������: ������������Ϊ0�������������ԭʼ��__rt_div0����Ŀ������С
;** 
;** �䡡��: �ο��⺯���ֲ�
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
;** ��������: CrpData
;** ��������: ֧��оƬ���ܹ���
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
    DCD     0x87654321          ;/* ������Ϊ0x87654321ʱ���û����򱻱��� */
    ENDIF
;/* �����ջ�ռ� */
        AREA    MyStacks, DATA, NOINIT, ALIGN=2
SvcStackSpace      SPACE   SVC_STACK_LEGTH * 4  ;����ģʽ��ջ�ռ�
IrqStackSpace      SPACE   IRQ_STACK_LEGTH * 4  ;�ж�ģʽ��ջ�ռ�
FiqStackSpace      SPACE   FIQ_STACK_LEGTH * 4  ;�����ж�ģʽ��ջ�ռ�
AbtStackSpace      SPACE   ABT_STACK_LEGTH * 4  ;��ֹ��ģʽ��ջ�ռ�
UndtStackSpace     SPACE   UND_STACK_LEGTH * 4  ;δ����ģʽ��ջ
    END
;/*********************************************************************************************************
;**                            End Of File
;********************************************************************************************************/
