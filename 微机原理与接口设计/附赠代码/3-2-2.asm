;========================================================
; �ļ���:3-2-2.asm
; ��������: 32λ�Ĵ�����32λָ��ʹ�õĻ����÷���
;			��һ��ASCII�ַ�ת����16�������룬������Ļ����ʾ������
;========================================================

.386P
TSTACK	SEGMENT	STACK	USE16 
	DB	64	DUP(?)
TSTACK	ENDS

DATA	SEGMENT	USE16
MES0	DB	'This is tangdu speaking!','$'
MES1	DB	'Show this sentence as hex:$'
;54,68,69,73,20,74,61,6E,67,64,75,20,73,70,65,61,6B,69,6E,67,21
BUF	DB	65	DUP(?)
DATA	ENDS

CODE	SEGMENT	USE16
		ASSUME	CS:CODE,DS:DATA
START:	MOV 	AX,DATA
		MOV		DS,AX
		MOV		DX,OFFSET MES0	;Show "This is tangdu speaking!"
		MOV		AH,09H
		INT 	21H
		CALL	KENTER			
		MOV		DX,OFFSET MES1	;Show Sentence as hex
		MOV		AH,09H
		INT 	21H
		CALL	KENTER	
		CALL	SAHEX
		MOV		DX,OFFSET BUF
		MOV		AH,09H
		INT 	21H
		CALL	KENTER			
		MOV 	AX,4C00H
		INT 	21H				;������ֹ
SAHEX	PROC	NEAR
CBYTE	=24	
		PUSHAD					;������32λ�Ĵ���ѹջ
		MOV		DI,OFFSET MES0
		MOVZX	EDI,DI			;����չָ��
		MOV		AX,DATA
		MOV		GS,AX			;ʹ��GS��
		MOV		SI,OFFSET BUF
		MOVZX	ESI,SI
		MOV		ECX,CBYTE
C1:		MOV		AL,DS:[EDI]
		AND		AL,0F0H			;ȡ��4λ
		SHR		AL,4
		CMP		AL,0AH			;�Ƿ���A���ϵ���
		JB		C2		
		ADD		AL,07H		
C2:		ADD		AL,30H		
		MOV		GS:[ESI],AL
		MOV		AL,DS:[EDI]
		AND		AL,0FH			;ȡ��4λ
		CMP		AL,0AH
		JB		C3
		ADD 	AL,07H
C3:		ADD		AL,30H
		MOV		GS:[ESI+1],AL
		MOV		BYTE PTR GS:[ESI+2],20H	;��ÿ���ַ������ո�
		ADD		ESI,3
		INC		EDI
		LOOP	C1
		
		MOV     AL,'$'
		MOV     GS:[ESI],AL
		
		POPAD					;�������мĴ���ֵ
		RET
SAHEX	ENDP

KENTER	PROC	NEAR
		MOV 	AH,02H
		MOV 	DL,0DH
		INT 	21H				;�س�
		MOV 	AH,02H
		MOV 	DL,0AH
		INT 	21H				;����
		RET
KENTER	ENDP
CODE	ENDS
		END		START