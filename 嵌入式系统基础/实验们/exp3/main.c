#include "config.h"

#define SCK (0x01<<4)//SCK, P0.4
#define SI (0x01<<6) //SI. P0.6 13,12 位
#define RCK (0x01<<7)//RCK, P0.7

void __irq Timer0_IRQ(void);	

void GPIO_Init(void)
{
	PINSEL0 &= ~(0x03<<8);
	PINSEL0 &= ~(0x03<<12);
	PINSEL0 &= ~(0x03<<14);

	IO0DIR |= SI ;	// 方向为输出IO0DIR[6]=1
	IO0DIR |= SCK;
	IO0DIR |= RCK;

}

void Timer0_Init(uint16 time)
{
	T0TC = 0;	// TC清零
	T0PR = 0;	// 时钟不分频
	T0MCR = 0x03;	// T0MCR[2:0] = 011, 匹配后复位T0TC, 并中断
	T0MR0 = Fpclk;	// 匹配值是1s
	
	// 设置VIC
	VICIntSelect = VICIntSelect & (~(1<<4));	// 	VICIntEnable[4]=0，定时器0（通道#4）中断类型设为IRQ
	VICVectCntl0 = 0x20 | 4;	// 第6位为1是使能(0x20)，低5位设为4，其他位为0
	VICVectAddr0 = (unsigned int) Timer0_IRQ;	// 定时器0的中断服务程序地址
	VICIntEnable = (1<<4);	// Timer0在通道#4，VICIntEnable[4]=1, 让定时器0中断使能
	T0TCR = 0x01;	// 启动定时器0
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
void __irq Timer0_IRQ(void)	// T0的TC == T0的MR0时，中断
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

	// 退中断
	T0IR = 0x01;	// 清除定时器0的所有中断标志
	VICVectAddr = 0x00;	// 通知VIC中断处理结束
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