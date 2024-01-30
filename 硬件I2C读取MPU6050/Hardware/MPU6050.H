/*
 * @Author: Chen 2603148225@qq.com
 * @Date: 2023-03-23 23:37:12
 * @LastEditors: Chen 2603148225@qq.com
 * @LastEditTime: 2023-03-23 23:37:44
 * @FilePath: \软件I2C读取MPU6050\Hardware\MPU6050.H
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __MPU6050_H
#define __MPU6050_H

void MPU6050_Init(void);
void MPU6050_WriteReg(uint8_t ReaAddress, uint8_t Data);
uint8_t MyI2C_ReceiveByte(void);
uint8_t MPU6050_ReadReg(uint8_t ReaAddress);
uint8_t MPU6050_GetID(void);
void MPU6050_GetData(int16_t *ACCX,int16_t *ACCY,int16_t *ACCZ,
                     int16_t *GRYX,int16_t *GRYY,int16_t *GRYZ);

void MPU6050_ReadRegs(uint8_t ReaBaseAddress, uint8_t Count, int16_t *Data);
void MPU6050_GetDatas(int16_t *ACCX,int16_t *ACCY,int16_t *ACCZ,
                     int16_t *GRYX,int16_t *GRYY,int16_t *GRYZ);

void MPU6050GYRO_GetData(int16_t *GRYX,int16_t *GRYY,int16_t *GRYZ);
void MPU6050ACC_GetData(int16_t *ACCX,int16_t *ACCY,int16_t *ACCZ);

#endif
