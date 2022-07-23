;----------------------------------------------------------------------------
;�ļ���:6-3-1.ASM
;����:ʹ��JMPָ��ʵ�������л�ʵ�飨����ӳ��ͬ��Ȩ���������
;----------------------------------------------------------------------------
INCLUDE         386SCD.INC
;----------------------------------------------------------------------------
DSEG      	    SEGMENT PARA USE16              ;ȫ�������������ݶ�(16λ)
GDT             LABEL   BYTE            		;ȫ����������
DUMMY           DESC    <>                  	;��������
NORMAL			DESC	<0FFFFH,,,ATDW,,>		;�淶��������
CODEM           DESC    <0FFFFH,,,ATCE,,>   	;�������������
LDTABLE1        DESC    <0FFFFH,,,ATLDT,,>      ;�ֲ���������ε�������
TSSTABLE0       DESC    <0FFFFH,,,,,>			;����0״̬��TSS������
TSSTABLE1       DESC    <0FFFFH,,,,,>			;����1״̬��TSS������
DSTACK0			DESC    <0FFFFH,,,ATDW,,>		;����0��0����ջ��������
DDATA0			DESC	<0FFFFH,,,ATDW,,>		;����0�����ݶ�������
;----------------------------------------------------------------------------
NORMAL_SEL		=		NORMAL-GDT				;�淶��������ѡ����
CODEM_SEL       =       CODEM-GDT               ;�������ѡ����
LDT1_SEL        =       LDTABLE1-GDT            ;�ֲ����������ѡ����
TSS0_SEL		= 		TSSTABLE0-GDT			;����0״̬��ѡ����
TSS1_SEL		=		TSSTABLE1-GDT			;����1״̬��ѡ����
DSTACK0_SEL		=       DSTACK0-GDT				;����0�Ķ�ջ��ѡ����
DDATA0_SEL      =       DDATA0-GDT              ;����0�����ݶ���������Ӧѡ����
GDTLEN          =       $-GDT            	    ;ȫ������������
;----------------------------------------------------------------------------
VGDTR           PDESC   <GDTLEN-1,>             ;����GDT��α������VGDTR
SPVAR 			 DW  ?
SSVAR 			 DW  ?						    ;����ʵģʽ�¶�ջָ��
;----------------------------------------------------------------------------
DSEG          ENDS                              ;ȫ����������ζ������
;----------------------------------------------------------------------------
DSEG1 	     	SEGMENT PARA USE16               	;�ֲ������������ݶ�(16λ)
LDT1			LABEL   BYTE                      	;�ֲ���������
DCODE1			DESC    <0FFFFH,,,ATCE,,>			;����1�Ĵ����������
DSTACK1			DESC	<0FFFFH,,,ATDW,,>			;����1�Ķ�ջ��������
DDATAS          DESC    <0FFFFH,,,ATDW,,>  			;Դ���ݶ�������
DDATAO          DESC    <0FFFFH,3000H,,ATDW,,> 		;Ŀ�����ݶ�������
TOTASK0         GATE    <0,TSS0_SEL,,ATTASKGATE,>   ;ָ������0�ĵ�����������
;----------------------------------------------------------------------------
DCODE1_SEL		=       DCODE1-LDT1+TIL		;����1�Ĵ���������ѡ����
DSTACK1_SEL		=       DSTACK1-LDT1+TIL	;����1�Ķ�ջ��������ѡ����
DDATAS_SEL		=       DDATAS-LDT1+TIL		;Դ���ݶ�������ѡ����
DDATAO_SEL		=       DDATAO-LDT1+TIL		;Ŀ�����ݶ�������ѡ����
TOTASK0_SEL		=		TOTASK0-LDT1+TIL	;������������ѡ����
LDT1LEN      	=       $-LDT1
DSEG1         ENDS                           ;�ֲ���������ζ������
;----------------------------------------------------------------------------
TSS0SEG    	  SEGMENT PARA USE16                ;����״̬��TSS0
TEMPTASK   	  TSS     <>
           	  DB      0FFH                      ;I/O���λͼ������־
TSS0LEN    	  =       $
TSS0SEG     	 ENDS							;����״̬��TSS0����
;----------------------------------------------------------------------------
TSS1SEG      SEGMENT PARA USE16                ;����״̬��TSS1
;----------------------------------------------------------------------------
                DD      0                         ;������
                DD      DSTACK1LEN                ;0����ջָ��
                DD      DSTACK1_SEL               ;0����ջѡ����
                DD      0                         ;1����ջָ��(ʵ����ʹ��)
                DD      0	               		  ;1����ջѡ����(ʵ����ʹ��)
                DD      0                         ;2����ջָ��
                DD      0       	              ;2����ջѡ����
                DD      0                         ;CR3
                DD      0		          		  ;EIP
                DD      200H                      ;EFLAGS
                DD      0FFFH                     ;EAX
                DD      0                         ;ECX
                DD      0                         ;EDX
                DD      0                         ;EBX
                DD      DSTACK1LEN	              ;ESP
                DD      0                         ;EBP
                DD      0                         ;ESI
                DD      0	                      ;EDI
                DW      DDATAS_SEL,0              ;ES
                DW      DCODE1_SEL,0              ;CS
                DW      DSTACK1_SEL,0             ;SS
                DW      DDATAS_SEL,0              ;DS
                DW      DDATAS_SEL,0              ;FS
                DW      DDATAS_SEL,0	          ;GS
                DW      LDT1_SEL,0              ;LDTR
                DW      0                       ;���������־
                DW      $+2                     ;ָ��I/O���λͼ
                DB      0FFH                    ;I/O���λͼ������־
TSS1LEN      =       $
;----------------------------------------------------------------------------
TSS1SEG      ENDS                               ;����״̬��TSS1����
;----------------------------------------------------------------------------
DSTACK0SEG   	SEGMENT PARA   USE16            ;����0�Ķ�ջ��
DSTACK0LEN	=       512
                DB      DSTACK0LEN DUP(?)		;����512�������ֽڵ�Ԫ
DSTACK0SEG	ENDS                              	;����0��ջ�ν���
;----------------------------------------------------------------------------
DSTACK1SEG   	SEGMENT PARA   USE16            ;����1�Ķ�ջ��
DSTACK1LEN	=       512
                DB      DSTACK1LEN DUP(?)		;����512�������ֽڵ�Ԫ
DSTACK1SEG	ENDS                              	;����1��ջ�ν���
;----------------------------------------------------------------------------
DDATA0SEG	SEGMENT	PARA USE16					;����0�����ݶ�
DDATA0LEN	=	128
		DB	DDATA0LEN DUP(?)
DDATA0SEG	ENDS
;----------------------------------------------------------------------------
DDATASSEG	SEGMENT	PARA USE16					;Դ���ݶ�
DTEST		DB	11H,22H,33H,44H,55H,66H,77H,88H	;����Դ���ݶ�����
DDATASLEN	=	$								;���ݶεĳ���
DDATASSEG	ENDS								;Դ���ݶζ������
;----------------------------------------------------------------------------
CODEMSEG	SEGMENT PARA USE16					;�������
		ASSUME	CS:CODEMSEG
START		PROC
			ASSUME  DS:DSEG
            MOV     AX,DSEG
            MOV     DS,AX
            
			MOV     BX,16       		     ;׼��Ҫ���ص�GDTR��α������
      		MUL     BX
			ADD     AX,OFFSET GDT            ;���㲢����GDT����ַ
			ADC     DX,0
			MOV     WORD PTR VGDTR.BASE,AX
			MOV     WORD PTR VGDTR.BASE+2,DX
            
			MOV     AX,CODEMSEG
			MUL     BX
			MOV     WORD PTR CODEM.BASEL,AX  ;���㲢����������λ���ַ
			MOV     BYTE PTR CODEM.BASEM,DL
			MOV     BYTE PTR CODEM.BASEH,DH            

			MOV     AX,DSEG1
			MUL     BX
			MOV     WORD PTR LDTABLE1.BASEL,AX  ;���㲢����LDT��λ���ַ
			MOV     BYTE PTR LDTABLE1.BASEM,DL
			MOV     BYTE PTR LDTABLE1.BASEH,DH
               
			MOV		AX,TSS0SEG
			MUL		BX
			MOV		WORD PTR TSSTABLE0.BASEL,AX	;���㲢���������TSS0����ַ
			MOV		BYTE PTR TSSTABLE0.BASEM,DL
			MOV		BYTE PTR TSSTABLE0.BASEH,DH		
			MOV		BYTE PTR TSSTABLE0.ATTRIBUTES,AT386TSS	;�����TSS0�Ķ�����
		
			MOV		AX,TSS1SEG
			MUL		BX
			MOV		WORD PTR TSSTABLE1.BASEL,AX	;���㲢���������TSS1����ַ
			MOV		BYTE PTR TSSTABLE1.BASEM,DL
			MOV		BYTE PTR TSSTABLE1.BASEH,DH
			MOV		BYTE PTR TSSTABLE1.ATTRIBUTES,AT386TSS	;�����TSS1�Ķ�����
		
			MOV		AX,DSTACK0SEG
			MUL		BX
			MOV		WORD PTR DSTACK0.BASEL,AX	;���㲢���ö�ջ�λ���ַ
			MOV		BYTE PTR DSTACK0.BASEM,DL
			MOV		BYTE PTR DSTACK0.BASEH,DH	
		
			MOV		AX,DDATA0SEG
			MUL		BX
			MOV		WORD PTR DDATA0.BASEL,AX	;���㲢��������0���ݶλ���ַ
			MOV		BYTE PTR DDATA0.BASEM,DL
			MOV		BYTE PTR DDATA0.BASEH,DH
;-----------------------------------------------------------		

			ASSUME  DS:DSEG1
			MOV		  AX,DSEG1
			MOV		  DS,AX
			
			MOV		AX,DCODE1SEG
			MUL		BX
			MOV		WORD PTR DCODE1.BASEL,AX	;���㲢��������1����λ���ַ
			MOV		BYTE PTR DCODE1.BASEM,DL
			MOV		BYTE PTR DCODE1.BASEH,DH

			MOV		AX,DSTACK1SEG
			MUL		BX
			MOV		WORD PTR DSTACK1.BASEL,AX	;���㲢��������1��ջ�λ���ַ
			MOV		BYTE PTR DSTACK1.BASEM,DL
			MOV		BYTE PTR DSTACK1.BASEH,DH
	
			MOV		AX,DDATASSEG
			MUL		BX
			MOV		WORD PTR DDATAS.BASEL,AX	;���㲢����Դ���ݶλ���ַ
			MOV		BYTE PTR DDATAS.BASEM,DL
			MOV		BYTE PTR DDATAS.BASEH,DH
						
;---------------------------------------------------------------------------
			ASSUME  DS:DSEG
            MOV     AX,DSEG
            MOV     DS,AX
            
            MOV 	SSVAR,SS
            MOV 	SPVAR,SP				;����ʵģʽ�¶�ջָ��
            
			LGDT    QWORD PTR VGDTR			;װ��GDT��Ĵ���GDTR
            CLI                             ;���ж�
            
            MOV     EAX,CR0         	    ;�л���������ʽ
            OR      EAX,1
            MOV     CR0,EAX                
            
            JUMP16  <CODEM_SEL>,<OFFSET VIRTUAL>     ;��ָ��Ԥȡ����,���������뱣����ʽ
               
VIRTUAL:    								;���ڿ�ʼ�ڱ�����ʽ������
			MOV		AX,TSS0_SEL				;װ������0
			LTR		AX

			MOV		AX,DDATA0_SEL			;�����ݶ�
			MOV		DS,AX
			MOV		ES,AX
			MOV		FS,AX
			MOV		GS,AX
			MOV 	ESP,DSTACK0LEN-1
			MOV		AX,DSTACK0_SEL			;�ö�ջ
			MOV		SS,AX
		
			JUMP16  TSS1_SEL,0				;��ת������1��0�������		
    
			MOV		AX,NORMAL_SEL			;�ѹ淶��������װ������ݶμĴ���
			MOV		DS,AX
			MOV		ES,AX
			MOV		FS,AX
			MOV		GS,AX
			MOV		SS,AX
    
	        MOV     EAX,CR0					;�л���ʵģʽ
            AND     AL,11111110B
            MOV     CR0,EAX
            JUMP16  <SEG REAL>,<OFFSET REAL>;��ָ��Ԥȡ����,����ʵ��ʽ

REAL:      									;�����ֻص�ʵ��ʽ
			MOV     AX,DSEG
            MOV     DS,AX
            LSS		SP,DWORD	PTR	SPVAR	;�ָ�ʵģʽ�µĶ�ջ
            
            ASSUME	DS:TSS1SEG
			MOV     AX,TSS1SEG
            MOV     DS,AX

            CALL	INIT_TSS1				;�ָ�TSS1����α�ĳ�ֵ,�Ա��´μ�������

            STI								;���ж�
            
			MOV 	AX,4C00H
			INT 	21H						;������ֹ

		
START		ENDP
CODEMLEN	= $
;----------------------------------------------------------------------------
INIT_TSS1	PROC	NEAR	;�ָ�TSS1����α�ĳ�ֵ
		PUSH	DS
		MOV		AX,TSS1SEG
		MOV 	DS,AX

		MOV		SI,0		;������
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;0����ջָ��
		MOV		AX,DSTACK1LEN
		MOV		[SI],AX
		
		ADD		SI,4		;0����ջѡ����
		MOV		AX,DSTACK1_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;1����ջָ��(ʵ����ʹ��)
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;1����ջѡ����(ʵ����ʹ��)
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;2����ջָ��
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;2����ջѡ����
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
		MOV		AX,DSTACK1LEN
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
		MOV		AX,DDATAS_SEL
		MOV		[SI],AX
		
		ADD		SI,2		
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,2		;CS
		MOV		AX,DCODE1_SEL
		MOV		[SI],AX
		
		ADD		SI,2		
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,2		;SS
		MOV		AX,DSTACK1_SEL
		MOV		[SI],AX
		
		ADD		SI,2		
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,2		;DS
		MOV		AX,DDATAS_SEL
		MOV		[SI],AX
		
		ADD		SI,2
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,2		;FS
		MOV		AX,DDATAS_SEL
		MOV		[SI],AX
		
		ADD		SI,2
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,2		;GS
		MOV		AX,DDATAS_SEL
		MOV		[SI],AX
		
		ADD		SI,2
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,2		;LDTR
		MOV		AX,LDT1_SEL
		MOV		[SI],AX
		
		ADD		SI,2
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,2		;���������־
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,2		;ָ��I/O���λͼ
		MOV		AX,68H		;TSS��104���ֽ�
		MOV		[SI],AX
		
		ADD		SI,2		;I/O���λͼ������־
		MOV		AX,0FFH
		MOV		[SI],AX
		
		POP		DS

		RET
INIT_TSS1		ENDP

CODEMSEG	ENDS
;----------------------------------------------------------------------------
DCODE1SEG	SEGMENT PARA USE16                ;����1�����
                ASSUME  CS:DCODE1SEG
				MOV     AX, DDATAS_SEL
                MOV     DS,AX                  ;����Դ���ݶ�������
                MOV     AX, DDATAO_SEL
                MOV     ES,AX                  ;����Ŀ�����ݶ�������
                XOR     SI,SI
                XOR     DI,DI                  ;����ָ���ֵ
                MOV     CX, 8		    	   ;���ô��ͳ���
        M1:     MOVSB                  	       ;����
                LOOP    M1

               	JUMP16	TOTASK0_SEL,0			;�л�������0
DCODE1LEN	= $
DCODE1SEG	ENDS
;============================================================================

                END     START
