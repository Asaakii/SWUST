/****************************************Copyright (c)**************************************************/
/**                                
;**                                 西南科技大学计算机科学学院
;**                                   
;**                                http://www.cs.suswt.edu.cn
;**            
;**             日期：   2006.4.1
;**             描述：   led.c 西南科技大学计算机学院CS-II型实验板数码管工作程序，控制
;**                      数码管底层显示功能
;**
;**--------------led.c文件
;**------------------------------------------------------------------------------------------------------*/

/**------------------------------------------------------------------------------------------------------*/
#include "config.h"
#include "led.h"

#ifdef Led_Enable
const uint8 display_code[16]=
              {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示内容数组 

uint8 display_pit = 0x00;  //扫描时的指针
uint8 display_place;     //位选

uint8 display_buffer[8];  //缓存数组

/****************************************************************
  函数名:   void LedInit(void)
  功  能:   控制Led的端口初始化，设置端口方向
*****************************************************************/
void LedInit(void)
{
    PINSEL1 &= LedSmat;   //设置端口的功能
    IO0DIR |= Led_SCK;    //设置P0.17     
    IO0DIR |= Led_SI;     //    P0.18
    IO0DIR |= Led_RCK;    //    P0.20  为输出端口 
}
/****************************************************************
  函数名:   void LedSend(uint8 code, uint8 place)
  功  能:   向595端口传输二个字节数据,一个数据表示显示的代码，一个数据
            表示显示的位置将串行数据转化为并行数据。
*****************************************************************/
void LedSend(uint8 code, uint8 place)
{
    uint16 temp_send = 0x0000;
    uint8 temp; 
    temp_send = place ;
    temp_send = temp_send << 8;
    temp_send = temp_send | code;   //将code 和 place 组合成一个16数(temp_send)
    IO0CLR = Led_RCK;  //RCK = 0;
    for(temp = 0x00; temp < 16; temp ++)
    {
        IO0CLR = Led_SCK;  //SCK = 0;
        if((temp_send & 0x8000) == 0)
        {
            IO0CLR = Led_SI; //发送 0
        }
        else
        {
            IO0SET = Led_SI; //发送 1
        }
        IO0SET = Led_SCK;  //SCK = 1;
        temp_send = temp_send << 1;
    }  
    IO0SET = Led_RCK;  //RCK = 1; (发送完毕)
}

/****************************************************************
  函数名:   void LedPrint(uint32 data)
  功  能:   数码管显示,将显示的数据分解后存到缓存数组display_buffer中
*****************************************************************/
void LedPrint(uint32 data)
{
    uint8 temp, temp_code;
    for(temp = 0x00;temp < 0x08; temp ++)
    {
        temp_code = data & 0x0f; //分别取位(每四位取一次)
        display_buffer[temp] = display_code[temp_code];
        data = data >> 4;        
    }
}

/****************************************************************
  函数名:   void LedScan(void)
  功  能:   数码管扫描,稳定显示对应显存区数据.
*****************************************************************/
void LedScan(void)
{
    display_place = 0xff ^ (0x80 >> display_pit);  //控制位选
    LedSend(display_buffer[display_pit], display_place); //通过端口扩展实现显示
    display_pit ++;
    if(display_pit == 0x08)  //实现循环显示
    {
        display_pit = 0x00;
    }
}

#endif