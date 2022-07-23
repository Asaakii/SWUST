#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char 
#define uint unsigned int 
code uchar SEG_CODE[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F  };
uchar disp_buff[3]={0,0,0} ;
sbit SW1=P3^0;
sbit CE=P2^0;
void delay(xms)
{
	       uint i,j;
		   for(i=0;i<xms;i++)
		   {
		   	 for(j=0;j<110;j++)	;
		   }
 }
void main()
{
     uchar i;
	 CE=0;
	 while(1)
 {
     if(SW1)
	 {
		 CE=1;
	  }
	  else 
	  	{
		  CE=0;
		  disp_buff[0]=P1/100;
		  disp_buff[1]=P1/10%10;
		  disp_buff[2]=P1%10;
		  for(i=0;i<3;i++)
		  {
		    P0=0x00;
			P2=(~(0x20<<i))&0xf0;
			P0=SEG_CODE[disp_buff[i]];
			delay(5)  ;
		  }
	  	}
 }   
}