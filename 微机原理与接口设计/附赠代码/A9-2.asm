;========================================================
; �ļ���:   A9-2.ASM
; ��������: INT 21H���ܵ���ʾ������
;========================================================
DATA1	SEGMENT
MES1	DB 'This is tangdu INT 21H !','$'
DATA1	ENDS					
;----------------------------------------------------------------------------
DATA2	SEGMENT
MES2	DB 0FFH DUP(?)
DATA2	ENDS					
;----------------------------------------------------------------------------
SSTACK	SEGMENT STACK
		DW 64 DUP(?)
SSTACK	ENDS
;----------------------------------------------------------------------------
CODE	SEGMENT
		ASSUME CS:CODE
;----------------------------------------------------------------------------
START:
		MOV AH,08H
		INT 21H			;���������뵽AL���޻���

		MOV AH,01H
		INT 21H			;���������뵽AL�в�����

		CALL ENTERR

		MOV CX,04H
		MOV DL,41H
AA:		MOV AH,02H
		INT 21H
		INC DL
		LOOP AA			;��DL�е�������ʾ����
	
		CALL ENTERR
	
		MOV AX,DATA1
		MOV DS,AX
		MOV DX,OFFSET MES1
		MOV AH,09H
		INT 21H			;��ʾ���ݶ�DATA1�е��ַ���

		CALL ENTERR

		MOV AX,DATA2
		MOV DS,AX
		MOV DX,OFFSET MES2
		MOV AH,0AH
		INT 21H			;�����ַ����ŵ����ݶ�DATA2��,�Իس�����
	
		ADD DX,02H
		MOV AH,09H
		INT 21H			;�����ݶ�DATA2�е��ַ�����ʾ����

		MOV AX,4C00H
		INT 21H			;������ֹ

ENTERR:
		MOV AH,02H
		MOV DL,0DH
		INT 21H			;�س�
		MOV AH,02H
		MOV DL,0AH
		INT 21H			;����
		RET
;----------------------------------------------------------------------------
CODE	ENDS
		END START