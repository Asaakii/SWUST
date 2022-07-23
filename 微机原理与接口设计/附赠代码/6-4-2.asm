;----------------------------------------------------------------------------
;�ļ���:6-4-2.ASM
;����:ͨ��������ת�Ƶ��ж�/�쳣����
;----------------------------------------------------------------------------
INCLUDE         386SCD.INC     
;----------------------------------------------------------------------------
GDTSEG          SEGMENT PARA USE16          ;ȫ�������������ݶ�(16λ)
;----------------------------------------------------------------------------
GDT             LABEL   BYTE                ;ȫ����������
DUMMY           DESC    <>                  ;��������
NORMAL			DESC	<0FFFFH,,,ATDW,,>	;�淶��������

CODEM           DESC    <0FFFFH,CODEMSEG,,ATCE,,>   ;�������������

TSSTABLE1       DESC    <0FFFFH,TSS1SEG,,,,>	;����1״̬��TSS������
TSSTABLE2       DESC    <0FFFFH,TSS2SEG,,,,>	;����2״̬��TSS������
TSSTABLE3       DESC    <0FFFFH,TSS3SEG,,,,>	;����3״̬��TSS������

DCODE2			DESC    <0FFFFH,DCODE2SEG,,ATCE,,>		;����2��0�������������
DCODE3			DESC    <0FFFFH,DCODE3SEG,,ATCE+DPL3,,>	;����3��3�������������(DPL=3)

DSTACK1			DESC    <0FFFFH,DSTACK1SEG,,ATDW,,>			;����1��0����ջ��������
DSTACK2			DESC	<0FFFFH,DSTACK2SEG,,ATDW,,>			;����2��0����ջ��������
DSTACK3			DESC	<0FFFFH,DSTACK3SEG,,ATDW+DPL3,,>	;����3��3����ջ��������(DPL=3)

DDATA1			DESC	<0FFFFH,DDATA1SEG,,ATDW,,>		;����1�����ݶ�������
DDATA2			DESC	<0FFFFH,DDATA2SEG,,ATDW,,>		;����2�����ݶ�������
DDATAS          DESC    <0FFFFH,DDATASSEG,,ATDW+DPL3,,>		;Դ���ݶ�������(DPL=3)
DDATAO          DESC    <0FFFFH,4000H,,ATDW+DPL3,,>    		;Ŀ�����ݶ�������(DPL=3)
;----------------------------------------------------------------------------
NORMAL_SEL		=		NORMAL-GDT			;�淶��������ѡ����
CODEM_SEL       =       CODEM-GDT           ;�������ѡ����
TSS1_SEL		= 		TSSTABLE1-GDT		;����1״̬��ѡ����
TSS2_SEL		=		TSSTABLE2-GDT		;����2״̬��ѡ����
TSS3_SEL		=		TSSTABLE3-GDT		;����3״̬��ѡ����
DCODE2_SEL		=       DCODE2-GDT			;����2�����������ѡ����
DCODE3_SEL		=       DCODE3-GDT+RPL3		;����3�����������ѡ����(RPL=3)
DSTACK1_SEL		=       DSTACK1-GDT			;0����ջ��1������ѡ����
DSTACK2_SEL		=       DSTACK2-GDT			;0����ջ��2������ѡ����
DSTACK3_SEL		=       DSTACK3-GDT+RPL3	;3����ջ��3������ѡ����(RPL=3)
DDATA1_SEL		=       DDATA1-GDT			;����1�����ݶ���������Ӧѡ����
DDATA2_SEL		=       DDATA2-GDT			;����2�����ݶ���������Ӧѡ����
DDATAS_SEL      =       DDATAS-GDT+RPL3     ;Դ���ݶ�ѡ����(RPL=3)
DDATAO_SEL      =       DDATAO-GDT+RPL3     ;Ŀ�����ݶ�ѡ����(RPL=3)
GDTLEN          =       $-GDT               ;ȫ������������
GDTSEG          ENDS                        ;ȫ����������ζ������
;----------------------------------------------------------------------------
IDTSEG		SEGMENT		PARA	USE16			;16λ�ж�/�쳣��������
IDT			LABEL		BYTE					;�����ж���������IDT
			REPT	32							;��00H---1FH��32���ж���������
			GATE	<,,,AT386IGATE,>
			ENDM
			
INT20		GATE    <0,TSS3_SEL,,ATTASKGATE,>	;��Ӧ20H���쳣/�жϴ������ε�������������

			REPT	256-33						;��21H---FFH��223���ж���������
			GATE	<,,,AT386IGATE,>
			ENDM
			
IDTLEN		=	$-IDT							;�ж�����������
IDTSEG		ENDS								;16λ�ж�/�쳣�������ν���
;----------------------------------------------------------------------------
TSS1SEG      SEGMENT PARA USE16                ;����1������״̬��TSS
TEMPTASK     TSS     <>
             DB      0FFH                      ;I/O���λͼ������־
TSS1LEN      =       $
TSS1SEG      ENDS								;����1״̬��TSS����
;----------------------------------------------------------------------------
TSS2SEG      SEGMENT PARA USE16                 ;����״̬��TSS2
                DD      0                       ;������
                DD      DSTACK2LEN              ;0����ջָ��
                DD      DSTACK2_SEL				;0����ջѡ����
                DD      0                       ;1����ջָ��(ʵ����ʹ��)
                DD      0	                    ;1����ջѡ����(ʵ����ʹ��)
                DD      0                       ;2����ջָ��
                DD      0	                    ;2����ջѡ����
                DD      0                       ;CR3
                DD      0		                ;EIP
                DD      200H                    ;EFLAGS
                DD      0FFFH                   ;EAX
                DD      0                       ;ECX
                DD      0                       ;EDX
                DD      0                       ;EBX
                DD      DSTACK2LEN              ;ESP
                DD      0                       ;EBP
                DD      0                       ;ESI
                DD      0	                    ;EDI
                DD      DDATA2_SEL              ;ES
                DD      DCODE2_SEL              ;CS
                DD      DSTACK2_SEL             ;SS
                DD      DDATA2_SEL              ;DS
                DD      DDATA2_SEL              ;FS
                DD      DDATA2_SEL	        	;GS
                DD      0                       ;LDTR
                DW      0                       ;���������־
                DW      $+2                     ;ָ��I/O���λͼ
                DB      0FFH                    ;I/O���λͼ������־
TSS2LEN      =       $
TSS2SEG      ENDS                               ;����״̬��TSS����
;----------------------------------------------------------------------------
TSS3SEG      SEGMENT PARA USE16                 ;����״̬��TSS3
                DD      0                       ;������
                DD      0        			    ;0����ջָ��
                DD      0	     		        ;0����ջѡ����
                DD      0                       ;1����ջָ��(ʵ����ʹ��)
                DD      0                       ;1����ջѡ����(ʵ����ʹ��)
                DD      0                       ;2����ջָ��
                DD      0                       ;2����ջѡ����
                DD      0                         ;CR3
                DD      0                         ;EIP
                DD      200H                      ;EFLAGS
                DD      0FFFH                     ;EAX
                DD      0                         ;ECX
                DD      0                         ;EDX
                DD      0                         ;EBX
                DD      DSTACK3LEN                ;ESP
                DD      0                         ;EBP
                DD      0                         ;ESI
                DD      0	                      ;EDI
                DD      DDATAO_SEL                ;ES
                DD      DCODE3_SEL                ;CS
                DD      DSTACK3_SEL               ;SS
                DD      DDATAS_SEL                ;DS
                DD      DDATAS_SEL                ;FS
                DD      DDATAS_SEL                ;GS
                DD      0                         ;LDTR
                DW      0                         ;���������־
                DW      $+2                       ;ָ��I/O���λͼ
                DB      0FFH                      ;I/O���λͼ������־
TSS3LEN      =       $
TSS3SEG      ENDS                              ;����״̬��TSS����
;----------------------------------------------------------------------------
DSTACK1SEG   	SEGMENT PARA   USE16            ;����1��0����ջ��
DSTACK1LEN	=       512
                DB      DSTACK1LEN DUP(0)		;����512�������ֽڵ�Ԫ
DSTACK1SEG	ENDS                              	 ;����1��ջ�ν���
;----------------------------------------------------------------------------
DSTACK2SEG	SEGMENT PARA	USE16	         	;����2��0����ջ��
DSTACK2LEN	=       512
		DB      DSTACK2LEN DUP(?)
DSTACK2SEG	ENDS       
;----------------------------------------------------------------------------
DSTACK3SEG	SEGMENT PARA	USE16	         	;����3��3����ջ��
DSTACK3LEN	=       512
		DB      DSTACK3LEN DUP(?)
DSTACK3SEG	ENDS       
;----------------------------------------------------------------------------
DDATA1SEG	SEGMENT	PARA USE16		;����1�����ݶ�
DDATA1LEN	=	128
		DB	DDATA1LEN DUP(?)	
DDATA1SEG	ENDS
;----------------------------------------------------------------------------
DDATA2SEG	SEGMENT	PARA USE16		;����2�����ݶ�
DDATA2LEN	=	128
		DB	DDATA2LEN DUP(?)
DDATA2SEG	ENDS
;----------------------------------------------------------------------------
DDATASSEG	SEGMENT	PARA USE16					;Դ���ݶ�
DTEST		DB	11H,22H,33H,44H,55H,66H,77H,88H	;����Դ���ݶ�����
DDATASLEN	=	$								;���ݶεĳ���
DDATASSEG	ENDS								;Դ���ݶζ������
;----------------------------------------------------------------------------
RDATASEG		SEGMENT		PARA	USE16		;ʵģʽ�µ����ݶ�
VGDTR           PDESC   <GDTLEN-1,>          	;GDTα������
VIDTR			PDESC	<IDTLEN-1,>				;IDTα������
NORVIDTR		PDESC	<3FFH,0>				;���ڱ���ԭIDTRֵ
SPVAR			DW  ?
SSVAR			DW  ?							;���ڱ���ʵģʽ�µĶ�ջָ��
REGV		DB	?								;���ڱ���ԭ�ж����μĴ���ֵ
RDATASEG		ENDS
;----------------------------------------------------------------------------
CODEMSEG	SEGMENT PARA USE16					;�������
		ASSUME	CS:CODEMSEG
START		PROC
            
			ASSUME  DS:GDTSEG
            MOV     AX,GDTSEG
            MOV     DS,AX
            
			MOV		BX,16
			MOV     AX,CODEMSEG
			MUL     BX
			MOV     WORD PTR CODEM.BASEL,AX		;���㲢����������λ���ַ
			MOV     BYTE PTR CODEM.BASEM,DL
			MOV     BYTE PTR CODEM.BASEH,DH            

			MOV     AX,TSS1SEG
			MUL     BX
			MOV     WORD PTR TSSTABLE1.BASEL,AX  ;���㲢��������1����ַ
			MOV     BYTE PTR TSSTABLE1.BASEM,DL
			MOV     BYTE PTR TSSTABLE1.BASEH,DH            
			MOV		BYTE PTR TSSTABLE1.ATTRIBUTES,AT386TSS	;�����TSS1�Ķ�����

			MOV     AX,TSS2SEG
			MUL     BX
			MOV     WORD PTR TSSTABLE2.BASEL,AX  ;���㲢��������2����ַ
			MOV     BYTE PTR TSSTABLE2.BASEM,DL
			MOV     BYTE PTR TSSTABLE2.BASEH,DH            
			MOV		BYTE PTR TSSTABLE2.ATTRIBUTES,AT386TSS	;�����TSS2�Ķ�����

			MOV     AX,TSS3SEG
			MUL     BX
			MOV     WORD PTR TSSTABLE3.BASEL,AX  ;���㲢��������3����ַ
			MOV     BYTE PTR TSSTABLE3.BASEM,DL
			MOV     BYTE PTR TSSTABLE3.BASEH,DH            
			MOV		BYTE PTR TSSTABLE3.ATTRIBUTES,AT386TSS	;�����TSS3�Ķ�����

			MOV     AX,DCODE2SEG
			MUL     BX
			MOV     WORD PTR DCODE2.BASEL,AX  ;���㲢���ô����2����ַ
			MOV     BYTE PTR DCODE2.BASEM,DL
			MOV     BYTE PTR DCODE2.BASEH,DH            

			MOV     AX,DCODE3SEG
			MUL     BX
			MOV     WORD PTR DCODE3.BASEL,AX  ;���㲢���ô����3����ַ
			MOV     BYTE PTR DCODE3.BASEM,DL
			MOV     BYTE PTR DCODE3.BASEH,DH            

			MOV     AX,DSTACK1SEG
			MUL     BX
			MOV     WORD PTR DSTACK1.BASEL,AX  ;���㲢���ö�ջ��1����ַ
			MOV     BYTE PTR DSTACK1.BASEM,DL
			MOV     BYTE PTR DSTACK1.BASEH,DH            

			MOV     AX,DSTACK2SEG
			MUL     BX
			MOV     WORD PTR DSTACK2.BASEL,AX  ;���㲢���ö�ջ��2����ַ
			MOV     BYTE PTR DSTACK2.BASEM,DL
			MOV     BYTE PTR DSTACK2.BASEH,DH            

			MOV     AX,DSTACK3SEG
			MUL     BX
			MOV     WORD PTR DSTACK3.BASEL,AX  ;���㲢���ö�ջ��3����ַ
			MOV     BYTE PTR DSTACK3.BASEM,DL
			MOV     BYTE PTR DSTACK3.BASEH,DH            

			MOV     AX,DDATA1SEG
			MUL     BX
			MOV     WORD PTR DDATA1.BASEL,AX  ;���㲢�������ݶ�1����ַ
			MOV     BYTE PTR DDATA1.BASEM,DL 
			MOV     BYTE PTR DDATA1.BASEH,DH            

			MOV     AX,DDATA2SEG
			MUL     BX
			MOV     WORD PTR DDATA2.BASEL,AX  ;���㲢�������ݶ�2����ַ
			MOV     BYTE PTR DDATA2.BASEM,DL
			MOV     BYTE PTR DDATA2.BASEH,DH            

			MOV     AX,DDATASSEG
			MUL     BX
			MOV     WORD PTR DDATAS.BASEL,AX  ;���㲢�������ݶ�3����ַ
			MOV     BYTE PTR DDATAS.BASEM,DL
			MOV     BYTE PTR DDATAS.BASEH,DH            
;----------------------------------------------------------------------------
			ASSUME	DS:RDATASEG
			MOV		AX,RDATASEG
			MOV		DS,AX
			
			MOV		AX,GDTSEG
			MOV     BX,16      			    ;׼��Ҫ���ص�GDTR��α������
      		MUL     BX
			ADD     AX,OFFSET GDT           ;���㲢����GDT����ַ
			ADC     DX,0 
			MOV     WORD PTR VGDTR.BASE,AX
			MOV     WORD PTR VGDTR.BASE+2,DX
            
			MOV		AX,IDTSEG
      		MUL     BX
			ADD     AX,OFFSET IDT           ;���㲢����IDT����ַ
			ADC     DX,0          
			MOV     WORD PTR VIDTR.BASE,AX
			MOV     WORD PTR VIDTR.BASE+2,DX
			
            MOV 	SSVAR,SS
            MOV 	SPVAR,SP				;����ʵģʽ�¶�ջָ��
            
            IN		AL,21H					;�ж������ּĴ����˿ڵ�ַ
            MOV		REGV,AL					;�����ж������ֽ�
            
			LGDT    QWORD PTR VGDTR			;װ��GDTR
            SIDT	NORVIDTR				;����IDTRֵ
            CLI                             ;���ж�
            
			LIDT	QWORD	PTR	VIDTR		;��IDTR

            MOV     EAX,CR0					;�л���������ʽ
            OR      EAX,1
            MOV     CR0,EAX                
            JUMP16  <CODEM_SEL>,<OFFSET VIRTUAL>;��ָ��Ԥȡ����,���������뱣����ʽ    
                
VIRTUAL:    								;���ڿ�ʼ�ڱ�����ʽ������
			MOV		AX,TSS1_SEL					;װ������1
			LTR		AX
			MOV		AX,DDATA1_SEL				;�����ݶ�
			MOV		DS,AX
			MOV		ES,AX
			MOV		FS,AX
			MOV		GS,AX
			MOV		ESP,DSTACK1LEN-1
			MOV		AX,DSTACK1_SEL				;�ö�ջ
			MOV		SS,AX
			
			CALL16  TSS2_SEL,0              ;��ת������2��0�������
			
			MOV		AX,NORMAL_SEL			;�ѹ淶��������װ������ݾݶμĴ���
			MOV		DS,AX
			MOV		ES,AX
			MOV		FS,AX
			MOV		GS,AX
			MOV		SS,AX
    
	        MOV     EAX,CR0					   ;�л���ʵģʽ
            AND     AL,11111110B
            MOV     CR0,EAX
            JUMP16  <SEG REAL>,<OFFSET REAL>   ;��ָ��Ԥȡ����,����ʵ��ʽ

REAL:   	  								;�����ֻص�ʵ��ʽ

			MOV     AX,RDATASEG
            MOV     DS,AX
            
            LSS		SP,DWORD	PTR	SPVAR	;�ָ�ʵģʽ�µĶ�ջ
            LIDT	NORVIDTR				;�ָ�IDTR
            
            MOV		AL,REGV					;�ָ��ж������ֽ�
            OUT		21H,AL
            

            ASSUME	DS:TSS2SEG
			MOV     AX,TSS2SEG
            MOV     DS,AX
            CALL	INIT_TSS2				;�ָ�TSS2����α�ĳ�ֵ,�Ա��´μ�������

            ASSUME	DS:TSS3SEG
			MOV     AX,TSS3SEG
            MOV     DS,AX
            CALL	INIT_TSS3				;�ָ�TSS3����α�ĳ�ֵ,�Ա��´μ�������
            
            STI								;���ж�

			MOV 	AX,4C00H
			INT 	21H						;������ֹ

START		ENDP
CODEMLEN	= $
;----------------------------------------------------------------------------
INIT_TSS2	PROC	NEAR	;�ָ�TSS2�����ĳ�ֵ
		PUSH	DS
		MOV		AX,TSS2SEG
		MOV 	DS,AX

		MOV		SI,0		;������
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;0����ջָ��
		MOV		AX,DSTACK2LEN
		MOV		[SI],AX
		
		ADD		SI,4		;0����ջѡ����
		MOV		AX,DSTACK2_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;1����ջָ��
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;1����ջѡ����
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
		MOV		AX,DSTACK2LEN
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
		MOV		AX,DDATA2_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;CS
		MOV		AX,DCODE2_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;SS
		MOV		AX,DSTACK2_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;DS
		MOV		AX,DDATA2_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;FS
		MOV		AX,DDATA2_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;GS
		MOV		AX,DDATA2_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;LDTR
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;���������־
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
INIT_TSS2		ENDP
;----------------------------------------------------------------------------
INIT_TSS3	PROC	NEAR	;�ָ�TSS3�����ĳ�ֵ
		PUSH	DS
		MOV		AX,TSS3SEG
		MOV 	DS,AX

		MOV		SI,0		;������
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;0����ջָ��
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;0����ջѡ����
		MOV		AX,0
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
		MOV		AX,DSTACK3LEN
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
		MOV		AX,DDATAO_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;CS
		MOV		AX,DCODE3_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;SS
		MOV		AX,DSTACK3_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;DS
		MOV		AX,DDATAS_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;FS
		MOV		AX,DDATAS_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;GS
		MOV		AX,DDATAS_SEL
		MOV		[SI],AX
		
		ADD		SI,4		;LDTR
		MOV		AX,0
		MOV		[SI],AX
		
		ADD		SI,4		;���������־
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
INIT_TSS3		ENDP
;----------------------------------------------------------------------------
DCODE2SEG	SEGMENT PARA USE16                ;����2��0�������
                ASSUME  CS:DCODE2SEG	

				INT		20H					  ;��INTָ�����һ���ж�/�쳣�����������������

                IRETD						  ;�жϷ���
                                                                                        
DCODE2LEN	= $
DCODE2SEG	ENDS                         
;----------------------------------------------------------------------------
DCODE3SEG	SEGMENT PARA USE16               	;����3��3�������
                ASSUME  CS:DCODE3SEG
				
                MOV     AX, DDATAS_SEL
                MOV     DS,AX                   ;����Դ���ݶ�������
                MOV     AX, DDATAO_SEL
                MOV     ES,AX                   ;����Ŀ�����ݶ�������
                XOR     SI,SI
                XOR     DI,DI                   ;����ָ���ֵ
                MOV     CX, 8		   		    ;���ô��ͳ���
        M1:     MOVSB                  	        ;����
                LOOP    M1                      
                
               	IRETD							;�μ䷵��

DCODE3LEN	= $
DCODE3SEG	ENDS
;----------------------------------------------------------------------------
CODEMSEG	ENDS
;============================================================================
                END     START
