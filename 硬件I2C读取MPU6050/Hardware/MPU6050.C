/*
 * @Author: Chen 2603148225@qq.com
 * @Date: 2023-03-23 23:37:03
 * @LastEditors: Chen 2603148225@qq.com
 * @LastEditTime: 2023-04-05 16:34:33
 * @FilePath: \软件I2C读取MPU6050\Hardware\MPU6050.C
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "stm32f10x.h"
#include "I2C.h"
#include "MPU6050_Reg.h"
#include "Delay.h"

#define MPU6050_ADDRESS     0XD0



void MPU6050_WriteReg(uint8_t RegAddress, uint8_t Data)
{
    I2C_GenerateSTART(I2C2, ENABLE);
    HardWareI2C_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
    HardWareI2C_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    I2C_SendData(I2C2, RegAddress);
    HardWareI2C_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    I2C_SendData(I2C2, Data);
    HardWareI2C_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    I2C_GenerateSTOP(I2C2, ENABLE);
}

uint8_t MPU6050_ReadReg(uint8_t ReaAddress)
{
    uint8_t Data;
    I2C_GenerateSTART(I2C2, ENABLE);
    HardWareI2C_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Transmitter);
    HardWareI2C_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    I2C_SendData(I2C2, ReaAddress);
    HardWareI2C_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED);

    I2C_GenerateSTART(I2C2, ENABLE);
    HardWareI2C_WaitEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2, MPU6050_ADDRESS, I2C_Direction_Receiver);
    HardWareI2C_WaitEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    I2C_AcknowledgeConfig(I2C2, DISABLE);
    I2C_GenerateSTOP(I2C2, ENABLE);

    HardWareI2C_WaitEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED);
    Data = I2C_ReceiveData(I2C2);

    return Data;
}

/* void MPU6050_ReadRegs(uint8_t ReaBaseAddress, uint8_t Count, int16_t *Data)
{
    uint8_t i;
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_ReceiveAckBit();
    MyI2C_SendByte(ReaBaseAddress);
    MyI2C_ReceiveAckBit();

    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS | 0X01);
    MyI2C_ReceiveAckBit();
    for ( i = 0; i < Count; i++)
    {
        *(Data + i) = MyI2C_ReceiveByte();
        if(i == (Count - 1)){MyI2C_SendAckBit(1);}    //应答位处理
		else{MyI2C_SendAckBit(0);}
		Delay_us(20);
    }

    MyI2C_Stop();
} */

uint8_t MPU6050_GetID(void)
{
    return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

void MPU6050_GetData(int16_t *ACCX,int16_t *ACCY,int16_t *ACCZ,
                     int16_t *GRYX,int16_t *GRYY,int16_t *GRYZ)
{
    uint8_t DataH, DataL;

    DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
    *ACCX = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
    *ACCY = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
    *ACCZ= (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
    *GRYX = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
    *GRYY = (DataH << 8) | DataL;

    DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
    *GRYZ= (DataH << 8) | DataL;
}
/* void MPU6050ACC_GetData(int16_t *ACCX,int16_t *ACCY,int16_t *ACCZ)
{
	int16_t Data[6];
	MPU6050_ReadRegs(MPU6050_ACCEL_XOUT_H,6,Data);
	*ACCX = (Data[0] << 8) | Data[1];
    *ACCY = (Data[2] << 8) | Data[3];
    *ACCZ = (Data[4] << 8) | Data[5];
}
void MPU6050GYRO_GetData(int16_t *GRYX,int16_t *GRYY,int16_t *GRYZ)
{
	int16_t Data[6];
	MPU6050_ReadRegs(MPU6050_GYRO_XOUT_H,6,Data);
	*GRYX = (Data[0] << 8) | Data[1];
    *GRYY = (Data[2] << 8) | Data[3];
    *GRYZ = (Data[4] << 8) | Data[5];

} */

void MPU6050_Init(void)
{
	HardWareI2C_Init();
	MPU6050_WriteReg(MPU6050_PWR_MGMT_1, 0x01);
	MPU6050_WriteReg(MPU6050_PWR_MGMT_2, 0x00);
	MPU6050_WriteReg(MPU6050_SMPLRT_DIV, 0x09);
	MPU6050_WriteReg(MPU6050_CONFIG, 0x06);
	MPU6050_WriteReg(MPU6050_GYRO_CONFIG, 0x18);
	MPU6050_WriteReg(MPU6050_ACCEL_CONFIG, 0x18);
}

