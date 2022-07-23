#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char 
#define uint unsigned int
#define codport P0
#define sitport P2
 
code uchar ledcode[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F  };

uchar disbuf[6]={0,0,0,0,0,0} ;

uchar hou=12,min=59,sec,num;


void delay(xms)
{
	       uint i,j;
		   for(i=0;i<xms;i++)
		   {
		   	 for(j=0;j<10;j++)	;
		   }
}

void timer0() interrupt 1
{
	TL0=55536%256;
	TH0=55536/256;
	num=num+1;
	if (num>9)
	{
		num=0;
		sec=sec+1;
		if (sec>59)
		{
			sec=0;
			min=min+1;
			if (min>59)
			{
				min=0;
				hou=hou+1;
			}
		}
	}
	disbuf[0]=hou/10;
 	disbuf[1]=hou%10;
	disbuf[2]=min/10;
	disbuf[3]=min%10;
	disbuf[4]=sec/10;
	disbuf[5]=sec%10;
}

void display()
{
	uchar i;
	uchar scan=0x01;
	for (i=0;i<6;i++)
	{
		P0=0x00;
		P0=ledcode[disbuf[i]];
		P2=~scan;
		scan=(scan<<1);
		delay(10);
	}
}

void main()
{
    TMOD=0x01;
	TL0=55536%256;
	TH0=55536/256;
	ET0=1;
	EA=1;
	TR0=1;
	while(1)
	{
		display();
	}
}