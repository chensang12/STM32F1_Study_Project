/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2023-01-20 11:43:31
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2023-01-20 12:29:48
 * @FilePath: \DHT11温湿度读取\Hardware\OneWire.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "stm32f10x.h"  
/*引脚配置*/
#define  DHT11_DATA(X)       GPIO_WriteBit(GPIOA,GPIO_Pin_0,(BitAction)(X))

void DHT11