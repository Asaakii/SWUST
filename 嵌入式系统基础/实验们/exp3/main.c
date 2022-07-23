#include "config.h"

#define SCK (0x01<<4)//SCK, P0.4
#define SI (0x01<<6) //SI. P0.6 13,12 λ
#define RCK (0x01<<7)//RCK, P0.7

void __irq Timer0_IRQ(void);	

void GPIO_Init(void)
{
	PINSEL0 &= ~(0x03<<8);
	PINSEL0 &= ~(0x03<<12);
	PINSEL0 &= ~(0x03<<14);

	IO0DIR |= SI ;	// ����Ϊ���IO0DIR[6]=1
	IO0DIR |= SCK;
	IO0DIR |= RCK;

}

void Timer0_Init(uint16 time)
{
	T0TC = 0;	// TC����
	T0PR = 0;	// ʱ�Ӳ���Ƶ
	T0MCR = 0x03;	// T0MCR[2:0] = 011, ƥ���λT0TC, ���ж�
	T0MR0 = Fpclk;	// ƥ��ֵ��1s
	
	// ����VIC
	VICIntSelect = VICIntSelect & (~(1<<4));	// 	VICIntEnable[4]=0����ʱ��0��ͨ��#4���ж�������ΪIRQ
	VICVectCntl0 = 0x20 | 4;	// ��6λΪ1��ʹ��(0x20)����5λ��Ϊ4������λΪ0
	VICVectAddr0 = (unsigned int) Timer0_IRQ;	// ��ʱ��0���жϷ�������ַ
	VICIntEnable = (1<<4);	// Timer0��ͨ��#4��VICIntEnable[4]=1, �ö�ʱ��0�ж�ʹ��
	T0TCR = 0x01;	// ������ʱ��0
}

void SendData(uint16 data)
{
	uint8 count;
	IO0CLR |= RCK;
	for(count = 0; count < 16; count++)
	{
		IO0CLR = SCK;
		if((data & 0x8000) == 0)
			IO0CLR = SI;
		else
			IO0SET = SI;
		
		IO0SET = SCK;
		data = data << 1;
	}
	
	IO0SET = RCK;
}

uint8 flag = 1;
void __irq Timer0_IRQ(void)	// T0��TC == T0��MR0ʱ���ж�
{
	
	
	if(flag)
		{
			SendData(0x5555);
			flag = 0;
		}
	else
		{
			SendData(0xAAAA);
			flag = 1;
		}

	// ���ж�
	T0IR = 0x01;	// �����ʱ��0�������жϱ�־
	VICVectAddr = 0x00;	// ֪ͨVIC�жϴ������
}

int main(void)
{
	GPIO_Init();
	//SendData(0x5555);
	Timer0_Init(1000);
	while(1)
	{
		// SendData(0x5555);
	}
	
	return 0;
}