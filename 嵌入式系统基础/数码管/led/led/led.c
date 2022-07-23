/****************************************Copyright (c)**************************************************/
/**                                
;**                                 ���ϿƼ���ѧ�������ѧѧԺ
;**                                   
;**                                http://www.cs.suswt.edu.cn
;**            
;**             ���ڣ�   2006.4.1
;**             ������   led.c ���ϿƼ���ѧ�����ѧԺCS-II��ʵ�������ܹ������򣬿���
;**                      ����ܵײ���ʾ����
;**
;**--------------led.c�ļ�
;**------------------------------------------------------------------------------------------------------*/

/**------------------------------------------------------------------------------------------------------*/
#include "config.h"
#include "led.h"

#ifdef Led_Enable
const uint8 display_code[16]=
              {0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
                0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//��ʾ�������� 

uint8 display_pit = 0x00;  //ɨ��ʱ��ָ��
uint8 display_place;     //λѡ

uint8 display_buffer[8];  //��������

/****************************************************************
  ������:   void LedInit(void)
  ��  ��:   ����Led�Ķ˿ڳ�ʼ�������ö˿ڷ���
*****************************************************************/
void LedInit(void)
{
    PINSEL1 &= LedSmat;   //���ö˿ڵĹ���
    IO0DIR |= Led_SCK;    //����P0.17     
    IO0DIR |= Led_SI;     //    P0.18
    IO0DIR |= Led_RCK;    //    P0.20  Ϊ����˿� 
}
/****************************************************************
  ������:   void LedSend(uint8 code, uint8 place)
  ��  ��:   ��595�˿ڴ�������ֽ�����,һ�����ݱ�ʾ��ʾ�Ĵ��룬һ������
            ��ʾ��ʾ��λ�ý���������ת��Ϊ�������ݡ�
*****************************************************************/
void LedSend(uint8 code, uint8 place)
{
    uint16 temp_send = 0x0000;
    uint8 temp; 
    temp_send = place ;
    temp_send = temp_send << 8;
    temp_send = temp_send | code;   //��code �� place ��ϳ�һ��16��(temp_send)
    IO0CLR = Led_RCK;  //RCK = 0;
    for(temp = 0x00; temp < 16; temp ++)
    {
        IO0CLR = Led_SCK;  //SCK = 0;
        if((temp_send & 0x8000) == 0)
        {
            IO0CLR = Led_SI; //���� 0
        }
        else
        {
            IO0SET = Led_SI; //���� 1
        }
        IO0SET = Led_SCK;  //SCK = 1;
        temp_send = temp_send << 1;
    }  
    IO0SET = Led_RCK;  //RCK = 1; (�������)
}

/****************************************************************
  ������:   void LedPrint(uint32 data)
  ��  ��:   �������ʾ,����ʾ�����ݷֽ��浽��������display_buffer��
*****************************************************************/
void LedPrint(uint32 data)
{
    uint8 temp, temp_code;
    for(temp = 0x00;temp < 0x08; temp ++)
    {
        temp_code = data & 0x0f; //�ֱ�ȡλ(ÿ��λȡһ��)
        display_buffer[temp] = display_code[temp_code];
        data = data >> 4;        
    }
}

/****************************************************************
  ������:   void LedScan(void)
  ��  ��:   �����ɨ��,�ȶ���ʾ��Ӧ�Դ�������.
*****************************************************************/
void LedScan(void)
{
    display_place = 0xff ^ (0x80 >> display_pit);  //����λѡ
    LedSend(display_buffer[display_pit], display_place); //ͨ���˿���չʵ����ʾ
    display_pit ++;
    if(display_pit == 0x08)  //ʵ��ѭ����ʾ
    {
        display_pit = 0x00;
    }
}

#endif