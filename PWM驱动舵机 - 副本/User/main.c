#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "Delay.h"
#include "Servo.h"

uint8_t i;
int main(void)
{

	PWM_Init();
	Servo_Init();
   while(1)
   {
       Servo_SetAngle(i);
       Delay_ms(1000);
       i = i + 45;
       if(i >= 180) i =0;
   }
}
