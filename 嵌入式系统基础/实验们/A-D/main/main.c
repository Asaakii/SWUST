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
	
	IO0SET |= 1<<23;//�����ͣ�?
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
    LedScan();   //�������ʾɨ�躯��
    
    
    T0IR = 0x01; //��λMR0�ж�
    VICVectAddr=0x00;//�����ַ
}

void Time0_InterruptSet(void)
{
    VICIntSelect &= 0xffffffef;  // �����ж�����(��ʱ��0�ж�ΪIRQ,����ΪFIQ)
    VICVectCntl2 = 0x24;   //���ȼ�����(2).��ʱ��0�ж�Ϊ4���ж�,��ʹ�ܶ�ʱ��0�ж�
    VICVectAddr2 = (int)IRQ_Time0Interrupt; //�����жϷ���������ڵ�ַ
    VICIntEnable = 0x00000010;  //����ʱ��0�ж�Դ�����ж�
}

void Time0Init(uint32 div, uint32 ovf)
{
    T0PR = div;   //��Ƶֵ( ��ʱ������ʱ��Ƶ�� = Fpclk/(div + 1) )
    T0MCR = 0x03;  //MR0��TCֵ��ƥ�佫�����ж�,��ʹTC��λ
    T0MR0 = ovf;  //ƥ��ֵ,������Ϊ�Ƕ�ʱ�������ֵ
    //T0TCR = 0x03; //TC0��ʼ��������λ.
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
	AD_number = ADDR;  //��ȡADDR��V/V(DDA)  [15:6] ������
	AD_number = AD_number >> 6;
	AD_number = AD_number & 0x000003ff;
	
	
	 //�����������λΪ0����رշ��ȣ�������
        if(AD_number<=0x0ff){ //�ж��Ƿ��м����� 
			
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
	
	
	
	LedPrint(AD_number);  //��ʾADDR��V/V(DDA) ������
	
	VICVectAddr=0x00;//�����ַ
}

void AD_InterruptInit(void)
{
	VICIntSelect &= 0xfffbffff;  // �����ж�����(A/Dת�����ж�ΪIRQ,����ΪFIQ)
    VICVectCntl3 = 0x32;   //���ȼ�����(3).A/Dת�����ж�Ϊ18���ж�,��ʹ��A/Dת�����ж�
    VICVectAddr3 = (int)IRQ_ADInterrupt; //�����жϷ���������ڵ�ַ
    VICIntEnable = 0x00040000;  //����A/Dת�����ж�Դ�����ж�
}

void AD_Init(uint32 Fadclk)
{
	PINSEL1 |= 0x00400000;            //����P0.27ΪAIN0����
	ADCR = (1 << 0)                |  //SEL = 1,ѡ��ͨ��0
	       ((Fpclk / Fadclk) << 8) |  //CLKDIV = Fpclk/Fadclk - 1, ��ת��ʱ��ΪFadclk
	       (1 << 16)               |  //BURST = 1,A/Dת������CLKS�ֶ�ѡ��������ظ�ִ��ת��
	       (2 << 17)               |  //CLKS = 2,ʹ��9clockת��
	       (1 << 21)               |  //PDN = 1,��������ģʽ(�ǵ���ת����ʽ)
	       (0 << 22)               |  //TEST[1:0] = 00,��������ģʽ(�ǵ���ת����ʽ)
	       (1 << 24)               |  //START = 1,ֱ������ADCת��
	       (0 << 27);                 //EDGE = 0(CAP/MAT�����½��ش���ADCת��)
	AD_InterruptInit();	  //AD�жϳ�ʼ��     
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
