;----------------------------------------------------------------------------
;�ļ���:6-1-1.ASM
;����:ȫ����������ȫ����������ʵ��
;----------------------------------------------------------------------------
INCLUDE         386SCD.INC
;���ݶ�==========================================================
DSEG            SEGMENT USE16                	 ;����16λ���ݶ�
GDT             LABEL   BYTE                 	 ;ȫ����������
DUMMY           DESC    <>                   	 ;��������
CODEM           DESC    <0FFFFH,,,ATCE,,>    	 ;�����������
DATAS           DESC    <0FFFFH,,,ATDW,,>   	 ;Դ���ݶ�������
DATAD           DESC    <0FFFFH,3000H,,ATDW,,>   ;Ŀ�����ݶ�������
VGDTR           PDESC   <GDTLEN-1,>				 ;α������
GDTLEN          =       $-GDT           	      ;ȫ������������
CODEM_SEL       =       CODEM-GDT        	      ;�����ѡ����
DATAS_SEL       =       DATAS-GDT       	      ;Դ���ݶ�ѡ����
DATAD_SEL       =       DATAD-GDT       	      ;Ŀ�����ݶ�ѡ����
DSEG            ENDS							  ;���ݶζ������
;==========================================================
DSEG1		SEGMENT PARA	USE16				  ;����16λԴ���ݶ�
TDATA           DW    1111H, 2222H, 3333H, 4444H  ;����ԭ���ݶ�����
                DW    5555H, 6666H, 7777H, 8888H
D1LEN		=$-TDATA							  ;���ݶεĳ���
DSEG1		ENDS								  ;Դ���ݶζ������
;�����=========================================================
CSEG		SEGMENT USE16							;16λ�����
                ASSUME CS:CSEG,DS:DSEG
START		PROC
                MOV     AX,DSEG
                MOV     DS,AX
                ;׼��Ҫ���ص�GDTR��α������
                MOV		BX,16						;���㲢����GDT����ַ
                MUL		BX							;���ݶε�ַ����4λ
                MOV		WORD PTR VGDTR.BASE,AX		;���õ��������ַ����VGDTR������
                MOV		WORD PTR VGDTR.BASE+2,DX
               ;���ô����������
				MOV		AX,CS						;���㲢����Դ���ݶλ�ַ
				MUL		BX							;����ε�ַ����4λ
				MOV		WORD PTR CODEM.BASEL,AX		;����ο�ʼƫ��Ϊ0
				MOV 	BYTE PTR CODEM.BASEM,DL		;���õ��������ַ����CODEM������
				MOV 	BYTE PTR CODEM.BASEH,DH
				;����Դ���ݶ�������
				MOV 	AX,DSEG1					;���㲢����Դ���ݶλ�ַ
				MUL		BX							;;Դ���ݶε�ַ����4λ
				ADD 	AX,OFFSET TDATA				;����TDATA��ƫ�Ƶõ������ַ	
				ADC		DX,0
				MOV 	WORD PTR DATAS.BASEL,AX		;���õ��������ַ����DATAS������
				MOV 	BYTE PTR DATAS.BASEM,DL
				MOV 	BYTE PTR DATAS.BASEH,DH
                ;����GDTR
                LGDT    QWORD PTR VGDTR
                CLI                        		    ;���ж�
                ;�л���������ʽ
                MOV     EAX,CR0
                OR      EAX,1
                MOV     CR0,EAX
                ;��ָ��Ԥȡ����,���������뱣����ʽ
                JUMP16  <CODEM_SEL>,<OFFSET VIRTUAL>
VIRTUAL:        ;���ڿ�ʼ�ڱ�����ʽ������
                MOV     AX,DATAS_SEL
                MOV     DS,AX                   ;����Դ���ݶ�������
                MOV		AX,DATAD_SEL
                MOV     ES,AX					;����Ŀ�����ݶ�������
                XOR		DI,DI					;DI����
                XOR     SI,SI					;SI����
                MOV     CX,D1LEN                ;�������ݳ���

M1:				MOVSB							;ͨ��������ָ���
				LOOP M1
                
                ;�л���ʵģʽ
                MOV     EAX,CR0
                AND     AL,11111110B
                MOV     CR0,EAX
                ;��ָ��Ԥȡ����,����ʵ��ʽ
                JUMP16  <SEG REAL>,<OFFSET REAL>
REAL:           ;�����ֻص�ʵ��ʽ
                STI								;���ж�

				MOV 	AX,4C00H
				INT 	21H						;������ֹ

START		ENDP
CLEN		=$-1
CSEG		ENDS
		END		START
