#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Timer.h"
#include "Delay.h"
uint16_t Num;
uint16_t s=0;

int main(void)
{

   OLED_Init();
   Timer_Init();
   OLED_ShowString(1,1,"Num:");
   while(1)
   {
      OLED_ShowNum(1,5,Num,5); 
      OLED_ShowNum(2,5,TIM_GetCounter(TIM2),5);

   }
   

}
