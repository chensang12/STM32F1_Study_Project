/*
 * @Author: Chen 2603148225@qq.com
 * @Date: 2023-03-23 22:04:22
 * @LastEditors: Chen 2603148225@qq.com
 * @LastEditTime: 2023-03-23 23:48:22
 * @FilePath: \软件I2C读取MPU6050\Hardware\MyI2C.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include "stm32f10x.h"
#include "Delay.h"


void MyI2C_W_SCL(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB,GPIO_Pin_10,(BitAction)BitValue);
    Delay_us(10);
}

void MyI2C_W_SDA(uint8_t BitValue)
{
    GPIO_WriteBit(GPIOB,GPIO_Pin_11,(BitAction)BitValue);
    Delay_us(10);
}

uint8_t MyI2C_R_SDA(void)
{
    uint8_t BitValue;
    BitValue = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11);
    Delay_us(10);
	return BitValue;
}

void MyI2C_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructrue;
    GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_Out_OD;
    GPIO_InitStructrue.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructrue);

    GPIO_SetBits(GPIOB,GPIO_Pin_10 | GPIO_Pin_11);
}

void MyI2C_Start(void)
{
    MyI2C_W_SDA(1);
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(0);
    MyI2C_W_SCL(0);
}

void MyI2C_Stop(void)
{
    MyI2C_W_SDA(0);
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t Byte)
{
    uint8_t i;
    for ( i = 0; i < 8; i++)
    {
        MyI2C_W_SDA(Byte  & (0X80 >> i));
        MyI2C_W_SCL(1);
        MyI2C_W_SCL(0);
    }

}

uint8_t MyI2C_ReceiveByte(void)
{
    uint8_t i;
    uint8_t Byte = 0X00;
    MyI2C_W_SDA(1);
    for (i = 0; i < 8; i++)
    {
        MyI2C_W_SCL(1);
        if(MyI2C_R_SDA()){Byte |= (0X80 >> i);}
        MyI2C_W_SCL(0);
    }
    return Byte;
}


void MyI2C_SendAckBit(uint8_t AckBit)
{
    MyI2C_W_SDA(AckBit);
    MyI2C_W_SCL(1);
    MyI2C_W_SCL(0);
}

uint8_t MyI2C_ReceiveAckBit(void)
{
    uint8_t AckBit;
    MyI2C_W_SDA(1);
    MyI2C_W_SCL(1);
    AckBit = MyI2C_R_SDA();
    MyI2C_W_SCL(0);
    return AckBit;
}

