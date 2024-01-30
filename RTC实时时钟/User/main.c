#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "My_RTC.h"
#include "OLED.h"
#include <time.h>


struct tm RTC_Time = {0};

int main(void)
{
	OLED_Init();
	My_RTC_Init();
	while(1)
	{
		My_RTC_ReadTime(&RTC_Time);
		OLED_ShowNum(1, 1, RTC_Time.tm_year + 1900, 4); OLED_ShowChar(1, 5, '.');
		OLED_ShowNum(1, 6, RTC_Time.tm_mon + 1, 2);		OLED_ShowChar(1, 8, '.');
		OLED_ShowNum(1, 9, RTC_Time.tm_mday, 3);
		
		
		OLED_ShowNum(2, 1, RTC_Time.tm_hour , 2);OLED_ShowChar(2, 3, ':');
		OLED_ShowNum(2, 4, RTC_Time.tm_min, 2);OLED_ShowChar(2, 6, ':');
		OLED_ShowNum(2, 7, RTC_Time.tm_sec, 2);
		
		
		OLED_ShowNum(4, 1, RTC_GetCounter(), 10);
	}
}
