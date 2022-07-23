;----------------------------------------------------------------------------
;�ļ���:6-4-1.ASM
;����:ͨ���ж��Ż�������ת�Ƶ��ж�/�쳣����
;----------------------------------------------------------------------------
INCLUDE         386SCD.INC
;----------------------------------------------------------------------------
GDTSEG          SEGMENT PARA USE16                  ;ȫ�������������ݶ�(16λ)
;----------------------------------------------------------------------------
GDT             LABEL   BYTE						;ȫ����������
DUMMY           DESC    <>                   		;��������
NORMAL			DESC	<0FFFFH,,,ATDW,,>			;�淶��������
CODEM           DESC    <0FFFFH,CODEMSEG,,ATCE,,>    	;�������������
DCODE			DESC    <0FFFFH,DCODESEG,,ATCE,,>		;DCODESEG�����������
ICODE			DESC    <0FFFFH,ICODESEG,,ATCE,,>		;�쳣/�жϴ�������������
DSTACK0			DESC    <0FFFFH,DSTACK0SEG,,ATDW,,>		;0����ջ��������
DDATAS			DESC	<0FFFFH,DDATASSEG,,ATDW,,>		;Դ���ݶ�������
DDATAO			DESC	<0FFFFH,3000H,,ATDW,,>			;Ŀ�����ݶ�������
;----------------------------------------------------------------------------
NORMAL_SEL		=		NORMAL-GDT					;�淶��������ѡ����
CODEM_SEL       =       CODEM-GDT                   ;�������ѡ����
DCODE_SEL       =       DCODE-GDT                   ;DCODESEG�����ѡ����
ICODE_SEL       =       ICODE-GDT                   ;�쳣/�жϴ�������ѡ����
DSTACK0_SEL		=		DSTACK0-GDT					;0����ջ��ѡ����
DDATAS_SEL		=		DDATAS-GDT					;Դ���ݶ�ѡ����
DDATAO_SEL		=		DDATAO-GDT					;Ŀ�����ݶ�ѡ����
GDTLEN          =       $-GDT            	        ;ȫ������������
GDTSEG          ENDS                                ;ȫ����������ζ������
;----------------------------------------------------------------------------
IDTSEG		SEGMENT		PARA	USE16			;16λ�ж�/�쳣��������
IDT			LABEL		BYTE					;�����ж���������IDT
			REPT	32							;��00H---1FH��32�����ж���������
			GATE	<,,,AT386IGATE,>
			ENDM
			
INT20		GATE    <0,ICODE_SEL,,AT386IGATE,>	;��Ӧ20H���쳣/�жϴ������ε��ж���������

			REPT	256-33						;��21H---FFH��223�����ж���������
			GATE	<,,,AT386IGATE,>
			ENDM
			
IDTLEN		=	$-IDT							;�ж�����������
IDTSEG		ENDS								;16λ�ж�/�쳣�������ν���
;----------------------------------------------------------------------------
DSTACK0SEG   	SEGMENT PARA   USE16              ;0����ջ��(16λ��)
DSTACK0LEN	=       1024
                DB      DSTACK0LEN DUP(0)		  ;����1024�������ֽڵ�Ԫ
DSTACK0SEG	ENDS                              	  ;0����ջ�ν���
;----------------------------------------------------------------------------
DDATASSEG	SEGMENT	PARA USE16					;Դ���ݶ�
DTEST		DB	11H,22H,33H,44H,55H,66H,77H,88H	;����Դ���ݶ�����
DDATASLEN	=	$								;���ݶεĳ���
DDATASSEG	ENDS								;Դ���ݶζ������
;========================================================================
RDATASEG		SEGMENT		PARA	USE16		;ʵģʽ�µ����ݶ�
VGDTR           PDESC   <GDTLEN-1,>             ;GDTα������
VIDTR			PDESC	<IDTLEN-1,>				;IDTα������
NORVIDTR		PDESC	<3FFH,0>				;���ڱ���ԭIDTRֵ
SPVAR			DW  ?
SSVAR			DW  ?							;����ʵģʽ�µĶ�ջָ��
REGV			DB	?							;���ڱ���ԭ�ж����μĴ���ֵ
RDATASEG		ENDS
;----------------------------------------------------------------------------
CODEMSEG	SEGMENT PARA USE16
			ASSUME	CS:CODEMSEG
START		PROC
			ASSUME  DS:GDTSEG
            MOV     AX,GDTSEG
            MOV     DS,AX
            
			MOV     BX,16 
			MOV     AX,CODEMSEG
			MUL     BX
			MOV     WORD PTR CODEM.BASEL,AX  ;���㲢����������λ���ַ
			MOV     BYTE PTR CODEM.BASEM,DL
			MOV     BYTE PTR CODEM.BASEH,DH            
			
			MOV     AX,DCODESEG
			MUL     BX
			MOV     WORD PTR DCODE.BASEL,AX  ;���㲢����DCODESEG����λ���ַ
			MOV     BYTE PTR DCODE.BASEM,DL
			MOV     BYTE PTR DCODE.BASEH,DH            
			
			MOV     AX,ICODESEG
			MUL     BX
			MOV     WORD PTR ICODE.BASEL,AX  ;���㲢�����жϴ���λ���ַ
			MOV     BYTE PTR ICODE.BASEM,DL
			MOV     BYTE PTR ICODE.BASEH,DH            
			
			MOV     AX,DSTACK0SEG
			MUL     BX
			MOV     WORD PTR DSTACK0.BASEL,AX  ;���㲢���ö�ջ��0����ַ
			MOV     BYTE PTR DSTACK0.BASEM,DL
			MOV     BYTE PTR DSTACK0.BASEH,DH            
			
			MOV     AX,DDATASSEG
			MUL     BX
			MOV     WORD PTR DDATAS.BASEL,AX  ;���㲢����Դ���ݻ���ַ
			MOV     BYTE PTR DDATAS.BASEM,DL
			MOV     BYTE PTR DDATAS.BASEH,DH            
;-----------------------------------------------------------		
			ASSUME	DS:RDATASEG
			MOV		AX,RDATASEG
			MOV		DS,AX
			
			MOV		AX,GDTSEG
			MOV     BX,16
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
			
;-----------------------------------------------------------		
            MOV 	SSVAR,SS
            MOV 	SPVAR,SP			;����ʵģʽ�µĶ�ջָ��
            
            IN		AL,21H				;�ж������ּĴ����˿ڵ�ַ
            MOV		REGV,AL				;�����ж������ֽ�
            
			LGDT    QWORD PTR VGDTR		;װ��GDTR
            SIDT	NORVIDTR			;����IDTRֵ
            CLI                         ;���ж�
            
            LIDT	QWORD	PTR	VIDTR	;��IDTR
            
            MOV     EAX,CR0             ;�л���������ʽ
            OR      EAX,1
            MOV     CR0,EAX                
            
            JUMP16  <CODEM_SEL>,<OFFSET VIRTUAL>     ;��ָ��Ԥȡ����,���������뱣����ʽ
;-----------------------------------------------------------		
VIRTUAL:    						;���ڿ�ʼ�ڱ�����ʽ������
			CALL16  DCODE_SEL,0		;��ת����DCODESEG�����				
			
			MOV		AX,NORMAL_SEL	;׼������ʵģʽ
			MOV		DS,AX			;�ѹ淶��������װ������ݶμĴ���
			MOV		ES,AX
			MOV		FS,AX
			MOV		GS,AX
			MOV		SS,AX
    
	        MOV     EAX,CR0					   ;�л���ʵģʽ
            AND     AL,11111110B
            MOV     CR0,EAX
            JUMP16  <SEG REAL>,<OFFSET REAL>   ;��ָ��Ԥȡ����,����ʵ��ʽ

REAL:   										;�����ֻص�ʵ��ʽ
			MOV     AX,RDATASEG
            MOV     DS,AX
            LSS		SP,DWORD	PTR	SPVAR		;�ָ�ʵģʽ�µĶ�ջָ��
            LIDT	NORVIDTR					;�ָ�IDTR
            
            MOV		AL,REGV						;�ָ��ж������ֽ�
            OUT		21H,AL
                        
            STI									;���ж�

			MOV 	AX,4C00H
			INT 	21H							;������ֹ
		
		
START		ENDP
CODEMLEN	= $
CODEMSEG	ENDS
;----------------------------------------------------------------------------
DCODESEG   SEGMENT PARA USE16        ;DCODESEG��16λ�����
           ASSUME  CS:DCODESEG
           MOV     AX, DDATAS_SEL
           MOV     DS,AX             ;����Դ���ݶ�������
           MOV     AX, DDATAO_SEL
           MOV     ES,AX             ;����Ŀ�����ݶ�������
           XOR     SI,SI
           XOR     DI,DI			;����ָ���ֵ
           MOV     CX, 8			;���ô��ͳ���
  		   INT		20H				;��INTָ�����һ���ж�/�쳣�����������������
		   RETF				    	;�жϷ���
DCODELEN	= $
DCODESEG	ENDS                    ;DCODESEG��16λ����ν���
;----------------------------------------------------------------------------
ICODESEG   SEGMENT PARA USE16           ;�쳣/�жϴ�������
           ASSUME  CS:ICODESEG
                
		  PUSHAD						;�����ֳ�
				
  M1:     MOVSB                  	    ;����
          LOOP    M1
                 
   		  POPAD							;�ָ��ֳ�
				
		  IRETD							;�μ䷵��      
				          
ICODELEN	=$

ICODESEG     	ENDS
;============================================================================
                END     START

