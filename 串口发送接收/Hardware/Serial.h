/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-12-15 00:35:14
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-12-16 18:22:22
 * @FilePath: \串口发送\Hardware\Serial.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __SERVO_H
#define __SERVO_H
#include <stdio.h>

extern uint8_t Serial_Txpacket[4];
extern uint8_t Serial_Rxpacket[4];
extern char Serial_RxString[];
extern uint8_t Serial_RxFlag;

void Serial_Init(void);
void Serial_SendByte(uint8_t Byte);
void Serial_SendArray(uint8_t *Array, uint16_t Length);
void Serial_SendString(char *String);
uint32_t Serial_Pow(uint32_t X, uint32_t Y);
void Serial_SendNumber(uint32_t Number,uint8_t Length);
int fputc(int ch, FILE *f);
void Serial_Printf(char *format,...);

uint8_t Serial_GetRxData(void);
uint8_t Serial_GetFlag(void);
void Serial_SendPacket(void);


#endif



