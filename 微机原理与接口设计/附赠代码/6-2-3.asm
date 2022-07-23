;----------------------------------------------------------------------------
;�ļ���:6-2-3.ASM
;����:����������Ȩ���任��ת��
;----------------------------------------------------------------------------
INCLUDE         386SCD.INC
;----------------------------------------------------------------------------
TDATASEG          SEGMENT PARA USE16			;ȫ�������������ݶ�(16λ)
GDT             LABEL   BYTE	              	;ȫ����������
DUMMY           DESC    <>                  	;��������
NORMAL			DESC	<0FFFFH,,,ATDW,,>		;�淶��������
CODEM           DESC    <0FFFFH,,,ATCE,,>       ;�������������
LDTABLE         DESC    <0FFFFH,,,ATLDT,,>      ;�ֲ���������ε�������
TSSTABLE        DESC    <0FFFFH,,,AT386TSS,,>	;����״̬��TSS������
;----------------------------------------------------------------------------
GDTLEN          =       $-GDT                	 ;ȫ������������
NORMAL_SEL		=		NORMAL-GDT				 ;�淶��������ѡ����	
CODEM_SEL       =       CODEM-GDT                ;�������ѡ����
LDT_SEL         =       LDTABLE-GDT              ;�ֲ����������ѡ����
TSS_SEL			=		TSSTABLE-GDT			 ;����״̬��ѡ����
;----------------------------------------------------------------------------
VGDTR           PDESC   <GDTLEN-1,>          	 ;����GDT��α������VGDTR
SPVAR 			 DW  ?
SSVAR 			 DW  ?							 ;����ʵ��ʽ�µĶ�ջָ��
;----------------------------------------------------------------------------
TDATASEG          ENDS                           ;ȫ����������ζ������
;----------------------------------------------------------------------------
LDTSEG    		  SEGMENT USE16           		  ;�ֲ������������ݶ�(16λ)
LDT				LABEL   BYTE                      ;�ֲ���������
DCODE0          DESC    <0FFFFH,,,ATCE,D32,>      ;�����0������(32λ��,DPL=0)
DCODE3			DESC    <0FFFFH,,,ATCE+DPL3,,>	  ;�����3������(16λ��,DPL=3)
DSTACK0			DESC    <0FFFFH,,,ATDW,,>         ;0����ջ��������(DPL=0)
DSTACK3			DESC	<0FFFFH,,,ATDW+DPL3,,>    ;3����ջ��������(DPL=3)
DDATAS          DESC    <0FFFFH,,,ATDW+DPL3,,>    ;Դ���ݶ�������(DPL=3)
DDATAO          DESC    <0FFFFH,3000H,,ATDW+DPL3,,> ;Ŀ�����ݶ�������(DPL=3)
TOCODE0         GATE    <OFFSET PEND- OFFSET PSTART,DCODE0_SEL,,AT386CGATE+DPL3,>;ָ������0������������
;----------------------------------------------------------------------------
DCODE0_SEL		=       DCODE0 -LDT+TIL			;�����0������ѡ����(RPL=0)
DCODE3_SEL		=       DCODE3 -LDT+TIL+RPL3	;�����3������ѡ����(RPL=3)
DSTACK0_SEL     =       DSTACK0-LDT+TIL      	;0����ջ������ѡ����(RPL=0)
DSTACK3_SEL		=       DSTACK3-LDT+TIL+RPL3	;3����ջ������ѡ����(RPL=3)
DDATAS_SEL		=       DDATAS -LDT+TIL+RPL3	;Դ���ݶ�������ѡ����(RPL=3)
DDATAO_SEL		=       DDATAO -LDT+TIL+RPL3	;Ŀ�����ݶ�������ѡ����(RPL=3)
TOCODE0_SEL		=		(TOCODE0-LDT)+TIL		;������������ѡ����
LDTLEN			=       $-LDT
LDTSEG      	ENDS                            ;�ֲ���������ζ������
;----------------------------------------------------------------------------
TSSSEG      SEGMENT PARA USE16                  ;����״̬��TSS
                DD      0                       ;BACK
                DD      DSTACK0LEN              ;0����ջָ��
                DD      DSTACK0_SEL             ;��ʼ��
                DD      0						;1����ջָ��
                DD		0						;��ʼ��
                DD      0                       ;2����ջָ��
                DD      0                       ;δ��ʼ��
                DD      0                       ;CR3
                DD      0                       ;EIP
                DD      0                       ;EFLAGS
                DD      0                       ;EAX
                DD      0                       ;ECX
                DD      0                       ;EDX
                DD      0                       ;EBX
                DD      0                       ;ESP
                DD      0                       ;EBP
                DD      0                       ;ESI
                DD      0                       ;EDI
                DD      0                       ;ES
                DD      0                       ;CS
                DD      0                       ;SS
                DD      0                       ;DS
                DD      0                       ;FS
                DD      0                       ;GS
                DD      LDT_SEL					;LDT
                DW      0                       ;���������־
                DW      $+2                     ;ָ��I/O���λͼ
                DW      0FFFFH                  ;I/O���λͼ������־
TSSLEN     	 =       $
TSSSEG      ENDS                              ;����״̬��TSS����
;----------------------------------------------------------------------------
DSTACK0SEG   	SEGMENT	PARA USE16			;����16λ��0����ջ��
DSTACK0LEN		=       128
                DB      DSTACK0LEN DUP(?)	;����128���������ֽڵ�Ԫ
DSTACK0SEG	ENDS							;0����ջ�ν���
;----------------------------------------------------------------------------
DSTACK3SEG		SEGMENT PARA	USE16	         ;3����ջ��
DSTACK3LEN		=       128
				DB      DSTACK3LEN DUP(?)
DSTACK3SEG	ENDS       
;----------------------------------------------------------------------------
DDATASSEG	SEGMENT	PARA USE16					;����16λ���ݶ�
DTEST		DB	11H,22H,33H,44H,55H,66H,77H,88H ;����Դ���ݶ�����
DDATASLEN	=	$								;���ݶεĳ���
DDATASSEG	ENDS								;Դ���ݶζ������
;----------------------------------------------------------------------------
CODEMSEG        SEGMENT PARA USE16
                ASSUME  CS:CODEMSEG
START		PROC
			ASSUME   DS:TDATASEG
            MOV     AX,TDATASEG
            MOV     DS,AX
            
            MOV		BX,16               				;׼��Ҫ���ص�GDTR��α������
            MUL		BX			    					;���㲢����GDT����ַ
            MOV		WORD PTR VGDTR.BASE,AX
            MOV		WORD PTR VGDTR.BASE+2,DX

			MOV		AX,CODEMSEG
			MUL		BX
			MOV		WORD PTR CODEM.BASEL,AX	  		  	;���㲢����������λ���ַ
			MOV		BYTE PTR CODEM.BASEM,DL
			MOV		BYTE PTR CODEM.BASEH,DH

			MOV		AX,LDTSEG
			MUL		BX
			MOV		WORD PTR LDTABLE.BASEL,AX	    	;���㲢����LDT��λ���ַ
			MOV		BYTE PTR LDTABLE.BASEM,DL
			MOV		BYTE PTR LDTABLE.BASEH,DH

			MOV		AX,TSSSEG
			MUL		BX
			MOV		WORD PTR TSSTABLE.BASEL,AX	    	;���㲢���������TSS����ַ
			MOV		BYTE PTR TSSTABLE.BASEM,DL
			MOV		BYTE PTR TSSTABLE.BASEM,DL
			MOV		BYTE PTR TSSTABLE.ATTRIBUTES,AT386TSS;�����TSS�Ķ�����
;---------------------------------------------------------------------
			ASSUME   DS:LDTSEG
			MOV      AX,LDTSEG
			MOV		DS,AX
			
			MOV		AX,DCODE0SEG
			MUL		BX
			MOV		WORD PTR DCODE0.BASEL,AX	    	;���㲢���ô����0����ַ
			MOV		BYTE PTR DCODE0.BASEM,DL
			MOV		BYTE PTR DCODE0.BASEH,DH

			MOV		AX,DCODE3SEG
			MUL		BX
			MOV		WORD PTR DCODE3.BASEL,AX	    	;���㲢���ô����3����ַ
			MOV		BYTE PTR DCODE3.BASEM,DL
			MOV		BYTE PTR DCODE3.BASEH,DH

			MOV		AX,DSTACK0SEG
			MUL		BX
			MOV		WORD PTR DSTACK0.BASEL,AX	    	;���㲢���ö�ջ��0����ַ
			MOV		BYTE PTR DSTACK0.BASEM,DL
			MOV		BYTE PTR DSTACK0.BASEH,DH

			MOV		AX,DSTACK3SEG
			MUL		BX
			MOV		WORD PTR DSTACK3.BASEL,AX	    	;���㲢���ö�ջ��3����ַ
			MOV		BYTE PTR DSTACK3.BASEM,DL
			MOV		BYTE PTR DSTACK3.BASEH,DH
		
			MOV		AX,DDATASSEG
			MUL		BX
			MOV		WORD PTR DDATAS.BASEL,AX	    	;���㲢����Դ���ݶλ���ַ
			MOV		BYTE PTR DDATAS.BASEM,DL
			MOV		BYTE PTR DDATAS.BASEH,DH
;------------------------------------------------------		
			ASSUME   DS:TDATASEG
            MOV     AX,TDATASEG
            MOV     DS,AX
            
            MOV 	SSVAR,SS
            MOV 	SPVAR,SP						;����ʵ��ʽ�µĶ�ջָ��
            
			LGDT    QWORD PTR VGDTR					;װ��GDT��Ĵ���GDTR
            CLI                             		;���ж�
            MOV     EAX,CR0            				;�л���������ʽ
            OR      EAX,1
            MOV     CR0,EAX                
            JUMP16  <CODEM_SEL>,<OFFSET VIRTUAL>    ;��ָ��Ԥȡ����,���������뱣����ʽ
VIRTUAL:    										;���ڿ�ʼ�ڱ�����ʽ������
			MOV		AX,TSS_SEL						;װ��LDT��
			LTR		AX
			MOV		AX,LDT_SEL						;װ��TSS��
			LLDT	AX
			
			JUMP16  DCODE0_SEL,0            		;ת�Ƶ�0�������
REAL1:           							 		;�л���ʵģʽ
			MOV		AX,NORMAL_SEL					;�ѹ淶��������װ������ݶμĴ���
			MOV		DS,AX
			MOV		ES,AX
			MOV		FS,AX
			MOV		GS,AX
			MOV		SS,AX
			
	        MOV     EAX,CR0							;�л���ʵģʽ
            AND     AL,11111110B
            MOV     CR0,EAX
            
            JUMP16  <SEG REAL>,<OFFSET REAL>		;��ָ��Ԥȡ����,����ʵ��ʽ
REAL:       										;�����ֻص�ʵ��ʽ
			MOV     AX,TDATASEG
            MOV     DS,AX
            
			LSS 	SP,DWORD PTR SPVAR				;�ָ�ʵ��ʽ��ջָ��
			
            STI										;���ж�
            
			MOV 	AX,4C00H
			INT 	21H								;������ֹ
			
CODEMLEN        = $
START           ENDP
;-----------------------------------------------------------------
DCODE0SEG       SEGMENT PARA USE32					;0����32λ�����                
                ASSUME  CS:DCODE0SEG

PSTART:			MOV     AX,DSTACK0_SEL          	;����0����ջ
				MOV		SS,AX
				MOV     ESP,DSTACK0LEN-1
                PUSH    DWORD PTR DSTACK3_SEL
                PUSH    DWORD PTR DSTACK3LEN		;ѹ��3����ջָ��
                PUSH    DWORD PTR DCODE3_SEL
                PUSH    OFFSET 	0					;ѹ����ڵ�
                
                RETF								;��0�������ת�Ƶ�3�������
                
PEND:           JUMP32  <CODEM_SEL>,<OFFSET REAL1>	;��ת���������

DCODE0LEN	=       $
;----------------------------------------------------------------------------
DCODE0SEG	ENDS                              
;----------------------------------------------------------------------------
DCODE3SEG	SEGMENT PARA USE16                		;3����16λ�����
                ASSUME  CS:DCODE3SEG
                MOV     AX, DDATAS_SEL
                MOV     DS, AX                 		;����Դ���ݶ�������
                MOV     AX, DDATAO_SEL
                MOV     ES,AX                  		;����Ŀ�����ݶ�������
                XOR     SI,SI
                XOR     DI,DI                  		;����ָ���ֵ
                MOV     CX, 8		     	   		;���ô��ͳ���
        M1:     MOVSB                  	       		;����
                LOOP    M1
                
				CALL16  TOCODE0_SEL,0					;��3�������ת�Ƶ�0�������
				
DCODE3LEN	=	$
DCODE3SEG       ENDS  
;------------------------------------------------------------------
CODEMSEG        ENDS
                END     START

