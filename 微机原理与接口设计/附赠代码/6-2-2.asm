;----------------------------------------------------------------------------
;�ļ���:6-2-2.ASM
;����:ͨ��JMP��RETָ������������Ȩ���任��ת��
;----------------------------------------------------------------------------
INCLUDE         386SCD.INC
;���ݶ�==========================================================
DSEG            SEGMENT PARA USE16            ;16λ���ݶ�
GDT             LABEL   BYTE                  ;ȫ����������
DUMMY           DESC    <>                    ;��������
CODEM           DESC    <0FFFFH,,,ATCE,,>     ;�������������
LDTABLE         DESC    <0FFFFH,,,ATLDT,,>    ;�ֲ���������ε�������
VGDTR           PDESC   <GDTLEN-1,>           ;α������
GDTLEN          =       $-GDT                 ;ȫ������������
CODEM_SEL       =       0008H                 ;�������ѡ����
LDT_SEL         =       0010H             	  ;�ֲ����������ѡ����
DSEG            ENDS                          ;���ݶζ������
;=====================================================================
DSEG1			SEGMENT PARA USE16            	;16λ���ݶ�
LDT             LABEL   BYTE					;�ֲ���������
CODE1           DESC    <0FFFFH,,,ATCE,,>		;0�������1
CODE2           DESC    <0FFFFH,,,ATCE,,>    	;0�������2
DSTACK			DESC    <0FFFFH,,,ATDW,,>		;0����ջ��������
DATAS			DESC	<0FFFFH,,,ATDW,,>		;Դ���ݶ�������
DATAO			DESC	<0FFFFH,3000H,,ATDW,,>	;Ŀ�����ݶ�������
LDTLEN          =       $-LDT                   ;LDT����
CODE1_SEL       =       CODE1-LDT+TIL       	;�����1��ѡ����
CODE2_SEL       =       CODE2-LDT+TIL       	;�����2��ѡ����
DSTACK_SEL		=       DSTACK-LDT+TIL			;0����ջ������ѡ����
DATAS_SEL		=       DATAS-LDT+TIL			;Դ���ݶ�������ѡ����
DATAO_SEL		=       DATAO-LDT+TIL			;Ŀ�����ݶ�������ѡ����
DSEG1            ENDS                          	;���ݶζ������
;----------------------------------------------------------------------------
STACKSEG   	SEGMENT	PARA USE16				;����16λ��0����ջ��
STACKLEN		=       128
                DB      128 DUP(?)			;����128���������ֽڵ�Ԫ
STACKSEG	ENDS							;0����ջ�ν���
;-----------------------------------------------------------------------------
DATASSEG	SEGMENT	PARA USE16					;����16λ���ݶ�
TDATA		DB	11H,22H,33H,44H,55H,66H,77H,88H ;����Դ���ݶ�����
DATASLEN	=	$								;���ݶεĳ���
DATASSEG	ENDS								;Դ���ݶζ������
;�����=========================================================
CODE1SEG        SEGMENT PARA USE16					;��������1 
                ASSUME  CS:CODE1SEG

                CALL16	CODE2_SEL,0					;ת������2

                JUMP16  <CODEM_SEL>,<OFFSET REAL1>	;��ת���������

CODE1LEN	=	$
CODE1SEG        ENDS                           ;�����1�������
;----------------------------------------------------------------------------
CODE2SEG        SEGMENT PARA USE16				;��������2
                ASSUME  CS:CODE2SEG

                MOV     AX, DATAS_SEL
                MOV     DS,AX                  ;����Դ���ݶ�������
                MOV     AX, DATAO_SEL
                MOV     ES,AX                  ;����Ŀ�����ݶ�������
                XOR     SI,SI
                XOR     DI,DI                  ;����ָ���ֵ
                MOV     CX, 8		    	   ;���ô��ͳ���
        M1:     MOVSB                  	       ;����
                LOOP    M1

                RETF							;�μ䷵��
CODE2LEN        =       $
CODE2SEG        ENDS                           ;�����2�������
;�����=========================================================
CSEG		SEGMENT PARA USE16					;16λ�������
            ASSUME CS:CSEG
START		PROC
			ASSUME	DS:DSEG
            MOV     AX,DSEG
            MOV     DS,AX
            
            MOV		BX,16						;׼��Ҫ���ص�GDTR��α������
            MUL		BX							;���㲢����GDT����ַ
            MOV		WORD PTR VGDTR.BASE,AX
            MOV		WORD PTR VGDTR.BASE+2,DX

			MOV		AX,CSEG
			MUL		BX
			MOV		WORD PTR CODEM.BASEL,AX		;���㲢����������λ���ַ
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

			MOV		AX,CODE1SEG
			MUL		BX
			MOV		WORD PTR CODE1.BASEL,AX		;���㲢���ô����1����ַ
			MOV		BYTE PTR CODE1.BASEM,DL
			MOV		BYTE PTR CODE1.BASEH,DH

			MOV		AX,CODE2SEG
			MUL		BX
			MOV		WORD PTR CODE2.BASEL,AX		;���㲢���ô����2����ַ
			MOV		BYTE PTR CODE2.BASEM,DL
			MOV		BYTE PTR CODE2.BASEH,DH

			MOV		AX,STACKSEG
			MUL		BX
			MOV		WORD PTR DSTACK.BASEL,AX	;���㲢���ö�ջ�λ���ַ
			MOV		BYTE PTR DSTACK.BASEM,DL
			MOV		BYTE PTR DSTACK.BASEH,DH

			MOV		AX,DATASSEG
			MUL		BX
			MOV		WORD PTR DATAS.BASEL,AX		;���㲢����Դ���ݶλ���ַ
			MOV		BYTE PTR DATAS.BASEM,DL
			MOV		BYTE PTR DATAS.BASEH,DH

			ASSUME	DS:DSEG
            MOV     AX,DSEG
            MOV     DS,AX

			LGDT    QWORD PTR VGDTR				;װ��GDT��Ĵ���GDTR
            CLI                             	;���ж�

            MOV     EAX,CR0         	    	;�л���������ʽ
            OR      EAX,1
            MOV     CR0,EAX                
            								
            JUMP16  <CODEM_SEL>,<OFFSET VIRTUAL>;��ָ��Ԥȡ����,���������뱣����ʽ
                
VIRTUAL:    									;���ڿ�ʼ�ڱ�����ʽ������
   			MOV		AX,LDT_SEL
			LLDT	AX							;װ��LDT��Ĵ���LDTR
    			
            JUMP16  CODE1_SEL,0					;��ת����������1
     
REAL1:    					        			;�л���ʵģʽ
	        MOV     EAX,CR0
            AND     AL,11111110B
            MOV     CR0,EAX
            ;��ָ��Ԥȡ����,����ʵ��ʽ
            JUMP16  <SEG REAL>,<OFFSET REAL>
REAL:       ;�����ֻص�ʵ��ʽ
            STI									;���ж�
            
			MOV 	AX,4C00H
			INT 	21H							;������ֹ

START	        ENDP
;----------------------------------------------------------------------------
CSEG        ENDS
                END     START

