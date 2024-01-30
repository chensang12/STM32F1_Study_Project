#include "stm32f10x.h"                  // Device header
#include <time.h>

struct tm Read_Time = {0};

void My_RTC_Init(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
	
	PWR_BackupAccessCmd(ENABLE);
	
	RCC_LSICmd(ENABLE);
	//RCC_LSEConfig(RCC_LSE_ON);
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == SET);
	
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
	RCC_RTCCLKCmd(ENABLE);
	
	RTC_WaitForSynchro();
	RTC_WaitForLastTask();
	
	RTC_SetPrescaler(40000 - 1);
	RTC_WaitForLastTask();
	
	if(BKP_ReadBackupRegister(BKP_DR1) != 0X5A5A)
	{
		BKP_WriteBackupRegister(BKP_DR1, 0X5A5A);
		RTC_SetCounter(1692283570);
		RTC_WaitForLastTask();
	}
	//PWR_BackupAccessCmd(DISABLE);
}


void My_RTC_ReadTime(struct tm *Time)
{
	uint32_t RTC_Count;
	RTC_Count = RTC_GetCounter() + 8 * 60 *60;
	struct tm *time = localtime(&RTC_Count);
	*Time = *time;
}


