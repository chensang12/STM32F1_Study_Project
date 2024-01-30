/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2022-12-15 00:34:11
 * @LastEditors: error: git config user.name && git config user.email & please set dead value or install git
 * @LastEditTime: 2022-12-16 01:53:10
 * @FilePath: \串口发送\User\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "stm32f10x.h"                  
#include "OLED.h"
#include "Serial.h"
#include "Delay.h"

int main(void)
{
    Serial_Init();
    while (1)
    {
        //printf("Num = %d\r\n",666);
        Serial_Printf("Num = %d\r\n",656);
        Delay_s(1);
    }    
    
}



