#include "config.h"
#define BEEPCON 0x1000000	//P0.24为蜂鸣器，低电平蜂鸣

void DelayNS(uint32 dly)
{
	uint32 i;
	for(;dly>0;dly--)
		for(i=0;i<5000;i++);
}

int main()
{
	uint32 i;
	!(PINSEL1 &= 0x8000);	//16位为0
	!(PINSEL1 &= 0x10000);	//17位为0
	
	IO0DIR &= BEEPCON;	//25位为1，为输出
	
	while(1)
	{
		IO0SET &= BEEPCON;
		DelayNS(10);
		IO0CLR &= BEEPCON;
		DelayNS(10);
	}
	
	return 0;
}