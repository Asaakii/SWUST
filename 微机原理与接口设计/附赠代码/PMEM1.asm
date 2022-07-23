;----------------------------------------------------------------------------
;�ļ���:PMEM1.ASM
;ʵ�����ݣ����ñ���ģʽ����,ʵ���ⲿ��������չʵ��.
;	 ��ʵ����Ҫ����,�Ѵ洢���ĵ�ַ�����ݡ���д���ֽ�ʹ�ܼ�Ƭѡ�ֱ�ӵ������ϡ�
;	 ��00080000H�ĵ�ַ�ռ俪ʼ��һ����������00080028H��ʼ�ĵ�ַ�ռ���,
;	 ����Ϊ30-39,41-5A   ��������ASCIIֵ����Ļ���Գ���.
;----------------------------------------------------------------------------
XIANXIN_WULI_AD1	=	00080000H	;���Ե�ַ1(����ҳʱ���������ַ)
XIANXIN_WULI_AD2	=	00080028H	;���Ե�ַ2(����ҳʱ���������ַ)
;----------------------------------------------------------------------------
INCLUDE         386SCD.INC     
;----------------------------------------------------------------------------
DSEG		SEGMENT	PARA		USE16					;����16λ���ݶ�
GDT			LABEL	BYTE								;ȫ����������
DUMMY		DESC		<>								;��������
CODEM		DESC		<0FFFFH,,,ATCE,,>				;�����������
DATAS		DESC		<0FFFFH,XIANXIN_WULI_AD1 AND 0FFFFH,XIANXIN_WULI_AD1 SHR 16,ATDW,,>;Դ���ݶ�������
DATAO		DESC		<0FFFFH,XIANXIN_WULI_AD2 AND 0FFFFH,XIANXIN_WULI_AD2 SHR 16,ATDW,,>;Ŀ�����ݶ�������
VGDTR		PDESC		<GDTLEN-1,>						;α������
GDTLEN		=			$-GDT							;ȫ������������
CODEM_SEL	=		CODEM-GDT							;�����ѡ����
DATAS_SEL	=		DATAS-GDT							;Դ���ݶ�ѡ����
DATAO_SEL	=		DATAO-GDT							;Ŀ�����ݶ�ѡ����
DSEG			ENDS									;���ݶζ������
;----------------------------------------------------------------------------
CSEG	SEGMENT	USE16							;16λ�����
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
;----------------------------------------------------------------------------
		MOV		AX,(XIANXIN_WULI_AD1 SHR 16) SHL 12	;����ַ��00080000H��ʼд��30-39
		MOV		DS,AX
		MOV		SI,(XIANXIN_WULI_AD1 AND 0FFFFH)	
		MOV		CX,10						;��10������
		MOV		AX,30H						;��30H��ʼ
MEM1:	MOV		[SI],AX
		INC		SI
		ADD		AX,1
		LOOP	MEM1
			
		MOV		CX,26						;����ַ��0008000AH��ʼд��41-5A
		MOV		AX,41H						;��A��Z����26����
MEM2:	MOV		[SI],AX
		INC		SI
		ADD		AX,1
		LOOP	MEM2
;----------------------------------------------------------------------------
		MOV		AX,DSEG
		MOV		DS,AX
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
		MOV		DS,AX						;����Դ���ݶ�������
		MOV		AX,DATAO_SEL
		MOV		ES,AX						;����Ŀ�����ݶ�������
		XOR		DI,DI						;DI����
		XOR		SI,SI						;SI����
		MOV		CX,36						;�������ݳ���
		REPZ	MOVSB						;ͨ��������ָ���
		;�л���ʵģʽ
		MOV		EAX,CR0
		AND		AL,11111110B
		MOV		CR0,EAX
		;��ָ��Ԥȡ����,����ʵ��ʽ
		JUMP16	<SEG REAL>,<OFFSET REAL>
REAL:	;�����ֻص�ʵ��ʽ
;----------------------------------------------------------------------------
		MOV		AX,(XIANXIN_WULI_AD2 SHR 16) SHL 12	;�ӵ�ַ00080028H��ʼ�����0-9
        MOV     DS,AX
        MOV		CX,0AH
        MOV     SI,(XIANXIN_WULI_AD2 AND 0FFFFH)	
MEMO1:  MOV		DL,[SI]
        MOV		AH,02H
        INT     21H						;��INT 21H���ܵ�������ַ�
        ADD		SI,1
        LOOP	MEMO1
             
        MOV		CX,1AH					;�ӵ�ַ00080032H��ʼ�����ĸA-Z
MEMO2:  MOV     DL,[SI]
        MOV		AH,02H
        INT     21H						;��INT 21H���ܵ�������ַ�
        ADD		SI,1
        LOOP	MEMO2
		STI								;���ж�

		MOV 	AX,4C00H
		INT 	21H						;������ֹ
			
START		ENDP
;----------------------------------------------------------------------------
CSEG			ENDS					;����ζ������
;----------------------------------------------------------------------------
		END     START
