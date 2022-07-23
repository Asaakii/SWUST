#include "config.h"
#include "A-D.h"
#include "led.h"

#ifdef AD_Enable
uint32 AD_number;
void __irq IRQ_ADInterrupt(void)
{
	int i=0;
	AD_number = ADDR;  //读取ADDR中V/V(DDA)  [15:6] 的数据
	AD_number = AD_number >> 6;
	AD_number = AD_number & 0x000003ff;
	
	
	 //如果倒数第三位为0，则关闭风扇；否则开启
        if(AD_number<=0x0ff){ //判断是否有键按下 
			IO2DIR|=1<<23;
			IO2SET|=1<<23;
		}
		else{
			IO2DIR|=1<<23;
			IO2CLR|=1<<23;
			
			//
			
			IO0CLR|=1<<24;
			
			for(i=0;i<1000;i++){}
			IO0SET|=1<<24;
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

#endif