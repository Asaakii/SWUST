;----------------------------------------------------------------------------
;�ļ���:5-1.ASM
;����:ѧϰʵģʽ�ͱ���ģʽ���л�
;----------------------------------------------------------------------------
;�洢���������ṹ����
DESC			STRUC
LIMITL		DW	0	;�ν���(BIT0-15)
BASEL		DW	0	;�λ���ַ(BIT0-15)
BASEM		DB	0	;�λ���ַ(BIT16-23)
ATTRIBUTES	DB	0	;������
LIMITH		DB	0	;�ν���(BIT16-19)(�������Եĸ�4λ)
BASEH		DB	0	;�λ���ַ(BIT24-31)
DESC			ENDS
;----------------------------------------------------------------------------
;��������
ATDW			EQU	92H	;���ڵĿɶ�д���ݶ�����ֵ
ATCE			EQU	98H	;���ڵ�ִֻ�д��������ֵ
;----------------------------------------------------------------------------
;α�������ṹ���Ͷ���
PDESC		STRUC
LIMIT		DW	0	;16λ����
BASE		DD	0	;32λ����ַ
PDESC		ENDS
;----------------------------------------------------------------------------
;16λƫ�ƵĶμ�ֱ��ת��ָ��ĺ궨��
JUMP16		MACRO	SELECTOR,OFFSET
DB			0EAH		;������
DW			OFFSET		;16λƫ����
DW			SELECTOR	;��ֵ���ѡ����
			ENDM
;----------------------------------------------------------------------------
.386P		; 386Pαָ��
;----------------------------------------------------------------------------
DSEG		SEGMENT	PARA		USE16			;����16λ���ݶ�
GDT			LABEL	BYTE						;ȫ����������
DUMMY		DESC		<>						;��������
CODEM		DESC		<0FFFFH,,,ATCE,,>		;�����������
DATAS		DESC		<0FFFFH,,,ATDW,,>		;Դ���ݶ�������
DATAD		DESC		<0FFFFH,,,ATDW,,>		;Ŀ�����ݶ�������
VGDTR		PDESC		<GDTLEN-1,>				;α������
GDTLEN		=			$-GDT					;ȫ������������
CODEM_SEL		=		CODEM-GDT				;�����ѡ����
DATAS_SEL		=		DATAS-GDT				;Դ���ݶ�ѡ����
DATAD_SEL		=		DATAD-GDT				;Ŀ�����ݶ�ѡ����
DSEG			ENDS							;���ݶζ������
;----------------------------------------------------------------------------
DATA1		SEGMENT	PARA		USE16			;����16λԴ���ݶ�
MES1		DB 'This is tangdu speak!','$'		;$Ϊ�ַ���������־
ML			=	$-MES1							;�ַ����ĳ���
DATA1		ENDS								;Դ���ݶζ������
;----------------------------------------------------------------------------
DATA2		SEGMENT	PARA		USE16			;����16λĿ�����ݶ�
BUF			DB	64 DUP(?)						;����64���������ֽڵ�Ԫ
DATA2		ENDS								;Ŀ�����ݶζ������
;----------------------------------------------------------------------------
CSEG		SEGMENT	USE16					;16λ�����
		ASSUME	CS:CSEG,DS:DSEG
START	PROC
		MOV		AX,DSEG
		MOV		DS,AX
		;׼��Ҫ���ص�GDTR��α������
		MOV		BX,16
		MUL		BX							;���ݶε�ַ����4λ
		ADD		AX,OFFSET GDT				;����GDT��ƫ�Ƶõ������ַ
		ADC		DX,0
		MOV		WORD PTR VGDTR.BASE,AX		;���õ��������ַ����VGDTR������
		MOV		WORD PTR VGDTR.BASE+2,DX;
		;���ô����������
		MOV		AX,CS
		MUL		BX							;����ε�ַ����4λ
		MOV		WORD PTR CODEM.BASEL,AX		;����ο�ʼƫ��Ϊ0
		MOV		BYTE PTR CODEM.BASEM,DL		;���õ��������ַ����CODEM������
		MOV		BYTE PTR CODEM.BASEH,DH
		;����Դ�����������
		MOV		AX,DATA1 
		MUL		BX							;Դ���ݶε�ַ����4λ
		MOV		WORD PTR DATAS.BASEL,AX		;Դ���ݶο�ʼƫ��Ϊ0
		MOV		BYTE PTR DATAS.BASEM,DL		;���õ��������ַ����DATAS������
		MOV		BYTE PTR DATAS.BASEH,DH
		;����Ŀ������������
		MOV		AX,DATA2 
		MUL		BX							;Ŀ�����ݶε�ַ����4λ
		MOV		WORD PTR DATAD.BASEL,AX		;Ŀ�����ݶο�ʼƫ��Ϊ0
		MOV		BYTE PTR DATAD.BASEM,DL		;���õ��������ַ����DATAD������
		MOV		BYTE PTR DATAD.BASEH,DH
		;����GDTR
		LGDT		QWORD PTR VGDTR
		CLI									;���ж�
		;�л���������ʽ
		MOV		EAX,CR0
		OR		EAX,1
		MOV		CR0,EAX
		;��ָ��Ԥȡ����,���������뱣����ʽ
		JUMP16	<CODEM_SEL>,<OFFSET VIRTUAL>
VIRTUAL:	;���ڿ�ʼ�ڱ�����ʽ������
		MOV		AX,DATAS_SEL
		MOV		DS,AX					;����Դ���ݶ�������
		MOV		AX,DATAD_SEL
		MOV		ES,AX					;����Ŀ�����ݶ�������
		XOR		DI,DI					;DI����
		XOR		SI,SI					;SI����
		MOV		CX,ML					;�������ݳ���
		REPZ	MOVSB					;ͨ��������ָ���
		;�л���ʵģʽ
		MOV		EAX,CR0
		AND		AL,11111110B
		MOV		CR0,EAX
		;��ָ��Ԥȡ����,����ʵ��ʽ
		JUMP16	<SEG REAL>,<OFFSET REAL>
REAL:	;�����ֻص�ʵ��ʽ
		STI								;���ж�
		MOV		AX,DATA1
		MOV		DS,AX					;��Դ���ݶ�
		MOV		DX,OFFSET MES1
		MOV		AH,09H
		INT		21H						;��INT 21H���ܵ�����ʾMES1���ݶε�����
		
		MOV		AH,02H
		MOV 	DL,0DH
		INT 	21H						;�س�
		MOV 	AH,02H
		MOV 	DL,0AH
		INT 	21H						;����

		MOV		AX,DATA2
		MOV		DS,AX					;��Ŀ�����ݶ�
		MOV		DX,OFFSET BUF
		MOV		AH,09H
		INT		21H						;��INT 21H���ܵ�����ʾBUF���ݶε�����
		MOV 	AX,4C00H
		INT 	21H						;������ֹ
START		ENDP
;----------------------------------------------------------------------------
CSEG			ENDS					;����ζ������
;----------------------------------------------------------------------------
		END     START
