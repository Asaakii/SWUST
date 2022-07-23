#include "config.h"
#include "A-D.h"
#include "led.h"

#ifdef AD_Enable
uint32 AD_number;
void __irq IRQ_ADInterrupt(void)
{
	int i=0;
	AD_number = ADDR;  //��ȡADDR��V/V(DDA)  [15:6] ������
	AD_number = AD_number >> 6;
	AD_number = AD_number & 0x000003ff;
	
	
	 //�����������λΪ0����رշ��ȣ�������
        if(AD_number<=0x0ff){ //�ж��Ƿ��м����� 
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

#endif