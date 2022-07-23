//COM0 P0.0:[01] P0.1:[01]

#include "config.h"

#define UART_BPS 9600	//通信波特率
#define BEEPPIN (1<<24)	//P0.24为蜂鸣器，低电平蜂鸣

void Delay(uint32 dly)
{
	uint32 i;
	for(;dly>0;dly--)
		for(i=0;i<5000;i++);
}

void Beep_Init(void)
{
	PINSEL1 &= ~(0x3 << 16);	//16位为0
	//PINSEL1 &= ~(0x10000);	//17位为0
	
	IO0DIR |= BEEPPIN;	//24位为1：输出
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
	//设置I/O连接到UART
	PINSEL0 |= 5;
	
	//设置串口波特率
	U0LCR = 0x83;	//1000 0011：访问DLAB，收发字长度为8位（1字节）
	Fdiv = (Fpclk / 16) / UART_BPS;	//设置波特率
	U0DLM = Fdiv / 256;
	U0DLL = Fdiv % 256;
	
	//设置串口工作模式
	U0LCR = 0x03;	//11：禁止访问DLAB
	U0FCR = 0x01;	//0000 0001，使能收发FIFO，并设置接收缓冲区触发点设为1字节
	
	//使能收发中断
	U0IER = 0x1;	//11:使能收取中断
	
}

//发送
void UART0_SendByte(uint8 data)
{

	U0THR = data;	//数据传给发送buffer，发送数据
	while((U0LSR & 0x40) == 0);	//loop until UnLSR[6] == 1, 等待数据发完
	
}

//接收
void __irq VIC_Service(void)
{
	uint8 rcv_data;
	
	switch(U0IIR & 0x0e)	//最后一位不要
	{
		case 0x04:	//发生RDA中断
			rcv_data = U0RBR;	//从接收FIFO中读取数据：收到的数据存到接收缓冲区U0RBR中，是接收FIFO最早收到的字符，读后中断自动清除
			UART0_SendByte(rcv_data);
			if(rcv_data == 0x55)
				{
					Beep();
				}
			break;
		
		default:
			break;
	}
	
	// T0IR = 0x01;	//清中断标志
	VICVectAddr = 0;	//通知VIC中断处理结束
}

//开放系统中断
void VIC_Init(void)
{

	VICIntSelect |= 0x0;	//VICIntSelect[6] = 0,UART 0中断分配为IRQ中断
	VICVectCntl0 = 0x20 | 6;	//UART中断分配为 slot0
	VICVectAddr0 = (unsigned int)VIC_Service;	//UART中断服务程序地址
	VICIntEnable |= 0x40;	//VICIntEnable[6] = 1，通道6中断使能
	
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