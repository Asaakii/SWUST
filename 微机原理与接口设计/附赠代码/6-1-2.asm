;----------------------------------------------------------------------------
;�ļ���:6-1-2.ASM
;����:�ֲ����������ֲ���������ʵ��
;----------------------------------------------------------------------------
INCLUDE         386SCD.INC
;���ݶ�==========================================================
DSEG            SEGMENT USE16					;16λ���ݶ�
GDT             LABEL   BYTE					;ȫ����������
DUMMY           DESC    <>						;��������
CODEM           DESC    <0FFFFH,,,ATCE,,>		;�����������
LDTABLE         DESC    <0FFFFH,,,ATLDT,,>		;�ֲ���������ε�������
VGDTR           PDESC   <GDTLEN-1,>           	;α������

CODEM_SEL       =       CODEM-GDT           	;�����ѡ����
LDT_SEL			=		LDTABLE-GDT        		;LDT��ѡ����
GDTLEN          =       $-GDT					;ȫ������������

DSEG            ENDS                            ;���ݶζ������
;--------------------------------------------------------------------
DSEG1			SEGMENT USE16					;16λ���ݶ�
LDT             LABEL   BYTE                  	;�ֲ���������
LDATAS          DESC    <0FFFFH,,,ATDW,,>    	;Դ���ݶ�������
LDATAD          DESC    <0FFFFH,3000H,,ATDW,,>  ;Ŀ�����ݶ�������

LDTLEN          =       $-LDT 		            ;�ֲ�����������
LDATAS_SEL      =       LDATAS-LDT+TIL          ;Դ���ݶ�ѡ����
LDATAD_SEL      =       LDATAD-LDT+TIL          ;Ŀ�����ݶ�ѡ����
DSEG1           ENDS                          	;���ݶζ������
;-----------------------------------------------------------------------------
DATASSEG		SEGMENT	PARA USE16				  ;����16λԴ���ݶ�
TDATA			DB 11H,22H,33H,44H,55H,66H,77H,88H;����Դ���ݶ�����
DATASLEN		=	$							  ;Դ���ݶεĳ���
DATASSEG		ENDS							  ;Դ���ݶζ������
;�����=========================================================
CSEG		SEGMENT USE16						;16λ�����
            ASSUME CS:CSEG
START		PROC
			ASSUME	DS:DSEG
            MOV     AX,DSEG
            MOV     DS,AX
            
            MOV		BX,16          	 			;׼��Ҫ���ص�GDTR��α������
            MUL		BX							;���㲢����GDT����ַ
            MOV		WORD PTR VGDTR.BASE,AX
            MOV		WORD PTR VGDTR.BASE+2,DX

			MOV		AX,CSEG
			MUL		BX
			MOV		WORD PTR CODEM.BASEL,AX		;���㲢���ô���λ���ַ
			MOV		BYTE PTR CODEM.BASEM,DL
			MOV		BYTE PTR CODEM.BASEH,DH

			MOV		AX,DSEG1
			MUL		BX
			MOV		WORD PTR LDTABLE.BASEL,AX	;���㲢����LDT��λ���ַ
			MOV		BYTE PTR LDTABLE.BASEM,DL
			MOV		BYTE PTR LDTABLE.BASEH,DH
			
			ASSUME	DS:DSEG1
            MOV     AX,DSEG1
            MOV     DS,AX

			MOV		AX,DATASSEG
			MUL		BX
			MOV		WORD PTR LDATAS.BASEL,AX	;���㲢����Դ���ݶλ���ַ
			MOV		BYTE PTR LDATAS.BASEM,DL
			MOV		BYTE PTR LDATAS.BASEH,DH

			ASSUME	DS:DSEG
            MOV     AX,DSEG
            MOV     DS,AX

            LGDT    QWORD PTR VGDTR				;װ��GDTR
            CLI                             	;���ж�
            ;�л���������ʽ
            MOV     EAX,CR0
            OR      EAX,1
            MOV     CR0,EAX                
            ;��ָ��Ԥȡ����,���������뱣����ʽ
            JUMP16  <CODEM_SEL>,<OFFSET VIRTUAL>    
                
VIRTUAL:    ;���ڿ�ʼ�ڱ�����ʽ������
   			MOV		AX,LDT_SEL
			LLDT	AX							;װ��LDT��Ĵ���LDTR
            MOV     AX,LDATAS_SEL      			;����Դ���ݶ�������
            MOV     DS,AX                  
            MOV		AX,LDATAD_SEL      			;����Ŀ�����ݶ�������
            MOV     ES,AX
            XOR		DI,DI
            XOR     SI,SI
            MOV     CX,8                		;�������ݳ���
            REPZ    MOVSB              			;����
            ;�л���ʵģʽ
            MOV     EAX,CR0
            AND     AL,11111110B
            MOV     CR0,EAX
            ;��ָ��Ԥȡ����,����ʵ��ʽ
            JUMP16  <SEG REAL>,<OFFSET REAL>
REAL:       ;�����ֻص�ʵ��ʽ
            STI									;���ж�

			MOV 	AX,4C00H
			INT 	21H							;������ֹ

START       ENDP
;---------------------------------------------------------------------------
CSEG        ENDS                           ;����ζ������
;----------------------------------------------------------------------------
            END     START

