/*
 * @Author: error: git config user.name && git config user.email & please set dead value or install git
 * @Date: 2023-01-20 11:39:14
 * @LastEditors: error: error: git config user.name & please set dead value or install git && error: git config user.email & please set dead value or install git & please set dead value or install git
 * @LastEditTime: 2023-02-07 19:29:37
 * @FilePath: \DHT11温湿度读取\User\main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "stm32f10x.h"    
#include "OLED.h"   
#include "DHT11.h" 
#include "Delay.h"    


u8 i;
int main(void)
{
   OLED_Init();
   Delay_s(1);
   while (1)
   {
      DHT11_ReceiveData();
      OLED_ShowNum(1,1,DHT11_DATA[0],3);
      OLED_ShowChar(1,4,'.');
      OLED_ShowNum(1,5,DHT11_DATA[1],3);
      OLED_ShowChar(2,4,'.');
      OLED_ShowNum(2,1,DHT11_DATA[2],3);
      OLED_ShowNum(2,5,DHT11_DATA[3],3);
      OLED_ShowNum(3,1,DHT11_DATA[4],3); 
      OLED_ShowNum(3,5,DHT11_Check(),1);     
      Delay_s(5);

   }

}
