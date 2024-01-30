/*
 * @Author: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @Date: 2023-01-20 11:39:52
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2023-02-07 19:42:19
 * @FilePath: \DHT11温湿度读取\Hardware\DHT11.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */


#include "stm32f10x.h"  
#include "Delay.h" 

#define ONE_WIRE_PIN(x)		GPIO_WriteBit(GPIOA, GPIO_Pin_0, (BitAction)(x))


u8 DHT11_DATA[]={0X00,0X00,0X00,0X00,0X00};
u8 Check;
void DHT11_Init_out(void)
{
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
     GPIO_InitTypeDef GPIO_InitSturcture;
     GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_Out_PP;
     GPIO_InitSturcture.GPIO_Pin = GPIO_Pin_0;
     GPIO_InitSturcture.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOA,&GPIO_InitSturcture);
}

void DHT11_Init_in(void)
{
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
     GPIO_InitTypeDef GPIO_InitSturcture;
     GPIO_InitSturcture.GPIO_Mode = GPIO_Mode_IPU;
     GPIO_InitSturcture.GPIO_Pin = GPIO_Pin_0;
     GPIO_InitSturcture.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOA,&GPIO_InitSturcture);
}
void DHT11_Start(void)
{
     u8 Ack_Bit;
     DHT11_Init_out();
     ONE_WIRE_PIN(0);
     Delay_ms(20);
     ONE_WIRE_PIN(1);
     Delay_us(30);
     Ack_Bit = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
     while(Ack_Bit ==  1);
     Delay_us(80);
     while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == RESET);

}
u8 OneWire_ReceiveBit(void)
{
     u8 Bit = 0;
     u8 count = 0;
     while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1);
/*      while((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 1) && (count < 100))
     {
          Delay_us(100);
          count++;
     }
     count = 0;
     while((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0) && (count < 100))
     {
          Delay_us(100);
          count++;
     } */
     while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0) == 0);
     Delay_us(30);
     Bit = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
     return Bit;
     
}

void DHT11_ReceiveData(void)
{
     u8 i,j;
     DHT11_Start();
     DHT11_Init_in();

     for ( i = 0; i < 5; i++)
     {
          for ( j = 0; j < 8; j++)
          {
               if(OneWire_ReceiveBit()){ DHT11_DATA[i] |= 0X80 >> j;}
          }
     }
     
  
}

uint8_t DHT11_Check(void)
{
     u8 i ;
     i = DHT11_DATA[0] + DHT11_DATA[1] + DHT11_DATA[2] + DHT11_DATA[3];
     if (DHT11_DATA[4] == i)
     {
          return 1;
     }
     else
     {
          return 0;
     }    
}

