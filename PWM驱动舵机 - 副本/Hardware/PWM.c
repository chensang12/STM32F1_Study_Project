#include "stm32f10x.h"                  // Device header


void PWM_Init(void)
{
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//把端口控制权利给片上外设TIM2
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOA,&GPIO_InitStructure);
   
   TIM_InternalClockConfig(TIM2);
   
   TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
   TIM_TimeBaseInitStructure .TIM_ClockDivision = TIM_CKD_DIV1;
   TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
   TIM_TimeBaseInitStructure.TIM_Period = 20000-1;    //周期ARR
   TIM_TimeBaseInitStructure.TIM_Prescaler = 72-1;  //预分频器PSC
   TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
   TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
   
   TIM_OCInitTypeDef TIM_OCInitStructure;
   TIM_OCStructInit(&TIM_OCInitStructure); //默认一步到位
   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1 ;  //输出模式
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCNPolarity_High;//输出极性
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable ;  //输出使能
   TIM_OCInitStructure.TIM_Pulse = 0;  //设置CCR
   
   TIM_OC1Init(TIM2,&TIM_OCInitStructure);
   
   TIM_Cmd(TIM2,ENABLE);//打开定时器
   
}

void PWM_SetCompare2(uint16_t Compare)
{
   TIM_SetCompare1(TIM2,Compare);//更改CCR值
}
