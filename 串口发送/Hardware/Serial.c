/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-12-15 00:34:44
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-12-16 01:55:00
 * @FilePath: \串口发送\Hardware\Serial.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "stm32f10x.h"
#include <stdio.h>
#include <stdarg.h>


void Serial_Init(void)
{
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

     GPIO_InitTypeDef GPIO_InitStructure;
     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
     GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOA,&GPIO_InitStructure);

     USART_InitTypeDef USART_InitStructure;
     USART_InitStructure.USART_BaudRate = 9600;
     USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //流控制CMD
     USART_InitStructure.USART_Mode = USART_Mode_Tx;
     USART_InitStructure.USART_Parity = USART_Parity_No; //校验位
     USART_InitStructure.USART_StopBits = USART_StopBits_1;
     USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位宽度
     USART_Init(USART1,&USART_InitStructure);

     USART_Cmd(USART1,ENABLE);


}
/**
  * @brief  串口发送一个字节
  * @param  Byte 发送的数据
  * @retval 无
  */

void Serial_SendByte(uint8_t Byte)
{
     USART_SendData(USART1,Byte);
     while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

/**
  * @brief  串口发送一个数组
  * @param  Array 数组名
  * @param  Length 数组长度
  * @retval 无
  */
void Serial_SendArray(uint8_t *Array, uint16_t Length)
{
     uint16_t i;
     for(i = 0; i < Length; i++)
     {
          Serial_SendByte(Array[i]);
     }
}
/**
  * @brief  串口发送一个字符串
  * @param  String 发送的字符串
  * @retval 无
  */
void Serial_SendString(uint8_t *String)  //可用\r\n换行
{
     uint16_t i;
     for (i = 0; String[i] != '\0'; i++)
	{
		Serial_SendByte(String[i]);
	}
}
/**
  * @brief  X的次方函数，方便对个十百千位取值
  * @param  X 次方的低数
  * @param  Y 幂次
  * @retval Result X的Y次
  */
uint32_t Serial_Pow(uint32_t X, uint32_t Y)
{
     uint32_t Result = 1;
     while(Y--)
     {
          Result *= X;
     }
     return Result;
}
/**
  * @brief  串口发送数字
  * @param  Number 数字大小
  * @param  Length 数字长度
  * @retval 无
  */
void Serial_SendNumber(uint32_t Number,uint8_t Length)
{
     uint8_t i;
     for(i = 0; i < Length; i++)
     {
          Serial_SendByte(Number / Serial_Pow(10,Length - i - 1) % 10 + 0X30);  //0X30是0的ASCII值，为数字偏移起始值
          //Serial_SendByte(Number / Serial_Pow(10,Length - i - 1) % 10 + '0'); //或者这一种方式
     }
     Serial_SendString("\r\n");
}

/**
  * @brief  printf函数重定向
  * @param  ch 
  * @param  *f 
  * @retval 无
  */

int fputc(int ch, FILE *f)  //printf的底层，重定向到串口
{
     Serial_SendByte(ch);
     return ch;
}

/**
  * @brief  多个printf函数重定向
  * @param   
  * @param   
  * @retval 无
  */

void Serial_Printf(char *format,...)
{
     char String[100];
     va_list arg;
     va_start(arg, format);
     vsprintf(String, format, arg);
     va_end(arg);
     Serial_SendString(String);
}













