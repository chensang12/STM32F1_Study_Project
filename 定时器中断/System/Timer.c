#include "stm32f10x.h"                  // Device header
#include "OLED.h"
extern uint16_t Num;  //跨文件变量
void Timer_Init(void)
{
   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
   
   TIM_InternalClockConfig(TIM2);//IM_InternalClockConfig 设置 TIMx 内部时钟
   
   TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
   TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//分频数
   TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//计数方式
   TIM_TimeBaseInitStructure.TIM_Period = 65536-1;   //ARR   定时时间T=PSC/PSC+1/(ARR+1)
   TIM_TimeBaseInitStructure.TIM_Prescaler = 65536-1;  //PSC,进行7200分频
   TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//高级定时器配置
   TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
   
   TIM_ClearFlag(TIM2,TIM_FLAG_Update);       //清除 TIMx 的待处理标志位
   TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  //使能或者失能指定的 TIM 中断
   
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //优先级设置
   
   NVIC_InitTypeDef NVIC_InitStructure;
   NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
   NVIC_Init(&NVIC_InitStructure);
   
   TIM_Cmd(TIM2 ,ENABLE);   //使能或者失能 TIMx 外设

}

void TIM2_IRQHandler(void)
{
   if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)  //检查指定的 TIM 中断发生与否
   {
      Num++;
      
      TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
   }
}
