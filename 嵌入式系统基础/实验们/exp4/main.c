//COM0 P0.0:[01] P0.1:[01]

#include "config.h"

#define UART_BPS 9600	//ͨ�Ų�����
#define BEEPPIN (1<<24)	//P0.24Ϊ���������͵�ƽ����

void Delay(uint32 dly)
{
	uint32 i;
	for(;dly>0;dly--)
		for(i=0;i<5000;i++);
}

void Beep_Init(void)
{
	PINSEL1 &= ~(0x3 << 16);	//16λΪ0
	//PINSEL1 &= ~(0x10000);	//17λΪ0
	
	IO0DIR |= BEEPPIN;	//24λΪ1�����
}

void Beep(void)
{
	while(1)
	{
		IO0SET |= BEEPPIN;
		Delay(10);
		IO0CLR |= BEEPPIN;
		Delay(10);
	}
}

void UART0_Init(void)
{
	uint16 Fdiv;
	//����I/O���ӵ�UART
	PINSEL0 |= 5;
	
	//���ô��ڲ�����
	U0LCR = 0x83;	//1000 0011������DLAB���շ��ֳ���Ϊ8λ��1�ֽڣ�
	Fdiv = (Fpclk / 16) / UART_BPS;	//���ò�����
	U0DLM = Fdiv / 256;
	U0DLL = Fdiv % 256;
	
	//���ô��ڹ���ģʽ
	U0LCR = 0x03;	//11����ֹ����DLAB
	U0FCR = 0x01;	//0000 0001��ʹ���շ�FIFO�������ý��ջ�������������Ϊ1�ֽ�
	
	//ʹ���շ��ж�
	U0IER = 0x1;	//11:ʹ����ȡ�ж�
	
}

//����
void UART0_SendByte(uint8 data)
{

	U0THR = data;	//���ݴ�������buffer����������
	while((U0LSR & 0x40) == 0);	//loop until UnLSR[6] == 1, �ȴ����ݷ���
	
}

//����
void __irq VIC_Service(void)
{
	uint8 rcv_data;
	
	switch(U0IIR & 0x0e)	//���һλ��Ҫ
	{
		case 0x04:	//����RDA�ж�
			rcv_data = U0RBR;	//�ӽ���FIFO�ж�ȡ���ݣ��յ������ݴ浽���ջ�����U0RBR�У��ǽ���FIFO�����յ����ַ��������ж��Զ����
			UART0_SendByte(rcv_data);
			if(rcv_data == 0x55)
				{
					Beep();
				}
			break;
		
		default:
			break;
	}
	
	// T0IR = 0x01;	//���жϱ�־
	VICVectAddr = 0;	//֪ͨVIC�жϴ������
}

//����ϵͳ�ж�
void VIC_Init(void)
{

	VICIntSelect |= 0x0;	//VICIntSelect[6] = 0,UART 0�жϷ���ΪIRQ�ж�
	VICVectCntl0 = 0x20 | 6;	//UART�жϷ���Ϊ slot0
	VICVectAddr0 = (unsigned int)VIC_Service;	//UART�жϷ�������ַ
	VICIntEnable |= 0x40;	//VICIntEnable[6] = 1��ͨ��6�ж�ʹ��
	
}


int main(void)
{

	Beep_Init();
	UART0_Init();
	VIC_Init();
	UART0_SendByte(0x55);
	while(1)
	{
		;
	}
	
	return 0;
}