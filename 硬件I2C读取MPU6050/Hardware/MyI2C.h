/*
 * @Author: Chen 2603148225@qq.com
 * @Date: 2023-03-23 22:04:39
 * @LastEditors: Chen 2603148225@qq.com
 * @LastEditTime: 2023-03-23 23:44:12
 * @FilePath: \软件I2C读取MPU6050\Hardware\MyI2C.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __MYI2C_H
#define __MYI2C_Hs

void MyI2C_Init(void);
void MyI2C_Start(void);
void MyI2C_Stop(void);
void MyI2C_SendByte(uint8_t Byte);
uint8_t MyI2C_ReceiveByte(void);
void MyI2C_SendAckBit(uint8_t AckBit);
uint8_t MyI2C_ReceiveAckBit(void);

#endif
