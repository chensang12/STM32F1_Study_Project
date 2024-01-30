#include "stm32f10x.h"                  // Device header

#define MPU6050_ADDRESS     0XD0

/**
 * @brief STM32硬件I2C初始化
 * @param 无
 */
void HardWareI2C_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);

	I2C_InitTypeDef I2C_InitStructure;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_ClockSpeed = 50000;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_OwnAddress1 = 0;
	I2C_Init(I2C2,&I2C_InitStructure);

	I2C_Cmd(I2C2,ENABLE);
}



/**
 * @brief 硬件I2C事件读取判断
 * @param I2Cx 使用的I2C
 * @param I2C_EVENT 需要判断的事件
 */
void HardWareI2C_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT)
{
	uint32_t TimeOut;
	TimeOut = 10000;
	while (I2C_CheckEvent(I2Cx, I2C_EVENT) != SUCCESS)
	{
		TimeOut--;
		if (TimeOut == 0)
		{
			break;
		}
	}
}
