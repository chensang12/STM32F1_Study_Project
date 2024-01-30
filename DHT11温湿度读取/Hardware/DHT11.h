/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2023-01-20 11:40:01
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2023-02-06 21:55:10
 * @FilePath: \DHT11温湿度读取\DHT11.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __DHT11_H
#define __DHT11_H

//extern uint8_t RH,RL,TH,TL;
extern u8 DHT11_DATA[];
extern u8 Check;
void DHT11_Init(void);
void DHT11_Start(void);
u8 OneWire_ReceiveBit(void);
void DHT11_ReceiveData(void);
#endif



