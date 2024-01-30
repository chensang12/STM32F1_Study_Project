#include "stm32f10x.h"                  // Device header
#include "PWM.h"


void Servo_Init(void)
{
    PWM_Init();
}

/*
    舵机转动角度函数
    角度        高电平时间(ms)          
    0           500
    180         2500
    y/180  =  x
*/
void Servo_SetAngle(float Angle)
{
    PWM_SetCompare1(Angle/180 * 2000 + 500);
}
