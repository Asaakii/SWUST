#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
code uchar SEG_CODE[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
void delay(uint ms)
{
   uint t1,t2;
   for(t1=0;t1<ms;t1++)
      for(t2=0;t2<110;t2++);
}
void main()
{
   uchar i=0;
   while(1)
   {
      P0=SEG_CODE[i];
	  P1=SEG_CODE[i];
	  i++;
	  delay(1000);
	  if(i>15) i=0;
   }
}