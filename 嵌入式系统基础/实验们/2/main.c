#include "config.h"
#define SCK (0x01<<4) //P0.4
#define SI (0x01<<6) //P0.6
#define RCK (0x01<<7) //P0.7

void DelayNS(uint32 dly)
{
	uint32 i;
	for(;dly>0;dly--)
		for(i=0;i<5000;i++);

}
// GPIO output
void GPIO_Init(void)
{
	PINSEL0 &= ~(0x03<<8);	// 8,9位为0 1100000000 0011111111
	PINSEL0 &= ~(0x03<<12);
	PINSEL0 &= ~(0x03<<14);
	//3个引脚输出
	IO0DIR |= SCK;
	IO0DIR |= SI;
	IO0DIR |= RCK;
	
}

void SendByte(uint16 data)
{
	uint8 i = 0;
	IO0CLR |= RCK;
	for(i = 0; i < 16; i++)
	{
		IO0CLR |= SCK;
		if(0 == (data & 0x8000))	//先发高位
		{
			IO0CLR |= SI;
		}
		else
		{
			IO0SET |= SI;
		}
			
		IO0SET |= SCK;	//发完1位，移位
		
		data = (data << 1);	//发送下一位
	}
	
	IO0SET |= RCK;
}

int main()
{
	GPIO_Init();
	
	while(1)
	{
	
		SendByte(0xAAAA); //1不亮
		DelayNS(1000);
		SendByte(0x5555);
		DelayNS(1000);
	}
	
	return 0;
}