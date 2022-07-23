#include "config.h"
#include "led.h"

#define SIN 6
#define SCK 4
#define RCK 7

uint8 arr[16]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f,0xbf,0xdf,0xef,0xf7,0xfb,0xfd,0xfe,0xfb};
uint32 AD_number;

void Speaker(uint8 time)	
{
	uint16 temp;
	PINSEL1 &= (~(0x03<<24));
	IO0DIR |= 1<<23;
	IO0CLR |= 1<<23;		
	
	for(; time > 0; time--)
	{
		for(temp = 0;temp < 0x3fff; temp++)
		{
			;
		}
	} 
	
	IO0SET |= 1<<23;//涿魍Ｖ?
}
void DelayNS(uint32 dly)
{
	uint32 i,j;
	for (j=0;j<dly;j++)
		for (i=0;i<50000;i++);
}

void sendbyte(uint8 sdata)
{
	uint8 i;
	IO0CLR |= 1<<RCK;
	for (i=0;i<8;i++)
	{
		IO0CLR |=1<<SCK;
		if ((sdata&0x01)==0)
		{
			IO0CLR |=1<<SIN;
		}
		else
		{
			IO0SET |=1<<SIN;
		}
		IO0SET |=1<<SCK;
		sdata=sdata>>1;
	}
	IO0SET |=1<<RCK;
}

void __irq IRQ_Time0Interrupt(void)
{
    T0MR0=Fpclk/AD_number;
    LedScan();   //数码管显示扫描函数
    
    
    T0IR = 0x01; //复位MR0中断
    VICVectAddr=0x00;//清除地址
}

void Time0_InterruptSet(void)
{
    VICIntSelect &= 0xffffffef;  // 设置中断类型(定时器0中断为IRQ,其它为FIQ)
    VICVectCntl2 = 0x24;   //优先级分配(2).定时器0中断为4号中断,且使能定时器0中断
    VICVectAddr2 = (int)IRQ_Time0Interrupt; //传送中断服务程序的入口地址
    VICIntEnable = 0x00000010;  //允许定时器0中断源产生中断
}

void Time0Init(uint32 div, uint32 ovf)
{
    T0PR = div;   //分频值( 定时器计数时钟频率 = Fpclk/(div + 1) )
    T0MCR = 0x03;  //MR0与TC值的匹配将产生中断,并使TC复位
    T0MR0 = ovf;  //匹配值,可以认为是定时器的溢出值
    //T0TCR = 0x03; //TC0开始计数并复位.
    Time0_InterruptSet();
}


void Time0Start(void)
{
    T0TCR = 0x01;
}




void __irq IRQ_ADInterrupt(void)
{
	int i=0;
	uint8 j=0;
	AD_number = ADDR;  //读取ADDR中V/V(DDA)  [15:6] 的数据
	AD_number = AD_number >> 6;
	AD_number = AD_number & 0x000003ff;
	
	
	 //如果倒数第三位为0，则关闭风扇；否则开启
        if(AD_number<=0x0ff){ //判断是否有键按下 
			
			IO2SET |= 1<<23;
			IO0SET|=1<<24;
			DelayNS(AD_number*5);
			
			
			PINSEL0 &= ~(0x03<<8);
			PINSEL0 &=~(0x03<<12);
			PINSEL0 &=~(0x03<<14);
			
			IO0DIR |=1<<SIN;
			IO0DIR |=1<<SCK;
			IO0DIR |=1<<RCK;
			while(1)
			{
				sendbyte(arr[j]);
				sendbyte(arr[15-j]);
				DelayNS(AD_number);
				j++;
				if (j==16)
					j=0;
			}
			
		}
		else{
			IO2CLR|=1<<23;
			IO0CLR|=1<<24;
			DelayNS(AD_number);
			
		}
	
	
	
	LedPrint(AD_number);  //显示ADDR中V/V(DDA) 的数据
	
	VICVectAddr=0x00;//清除地址
}

void AD_InterruptInit(void)
{
	VICIntSelect &= 0xfffbffff;  // 设置中断类型(A/D转换器中断为IRQ,其它为FIQ)
    VICVectCntl3 = 0x32;   //优先级分配(3).A/D转换器中断为18号中断,且使能A/D转换器中断
    VICVectAddr3 = (int)IRQ_ADInterrupt; //传送中断服务程序的入口地址
    VICIntEnable = 0x00040000;  //允许A/D转换器中断源产生中断
}

void AD_Init(uint32 Fadclk)
{
	PINSEL1 |= 0x00400000;            //设置P0.27为AIN0功能
	ADCR = (1 << 0)                |  //SEL = 1,选择通道0
	       ((Fpclk / Fadclk) << 8) |  //CLKDIV = Fpclk/Fadclk - 1, 即转换时钟为Fadclk
	       (1 << 16)               |  //BURST = 1,A/D转换器以CLKS字段选择的速率重复执行转换
	       (2 << 17)               |  //CLKS = 2,使用9clock转换
	       (1 << 21)               |  //PDN = 1,正常工作模式(非掉电转换摸式)
	       (0 << 22)               |  //TEST[1:0] = 00,正常工作模式(非掉电转换摸式)
	       (1 << 24)               |  //START = 1,直接启动ADC转换
	       (0 << 27);                 //EDGE = 0(CAP/MAT引脚下降沿触发ADC转换)
	AD_InterruptInit();	  //AD中断初始化     
}






int main(void)
{
	PINSEL0&=~(0x03<<16);
	IO0DIR|=1<<24;
	IO0SET|=1<<24;
	PINSEL2&=(~(0x03<<14));
	IO2DIR|=1<<23;
	IO2CLR|=1<<23;
	LedInit();
	AD_Init(1000000);
	Time0Init(2, 5000);
	Time0Start();
	while(1)
	{}
	return (0);
}
