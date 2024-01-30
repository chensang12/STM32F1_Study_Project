#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "u8g2.h"
#include "Delay.h"

int main(void)
{

	u8g2_t u8g2;
	U8G2_Init(&u8g2);  // init u8g2 structure
	
	u8g2_InitDisplay(&u8g2); // send init sequence to the display, display is in sleep mode after this,
	u8g2_SetPowerSave(&u8g2, 0); // wake up display

	

	while(1)
	{
		u8g2_ClearBuffer(&u8g2);
		u8g2_SendBuffer(&u8g2);//清屏
		
		u8g2_SetFont(&u8g2,u8g2_font_DigitalDiscoThin_tf);
		u8g2_DrawStr(&u8g2,30,50,"Test_code");
		u8g2_SendBuffer(&u8g2);
		u8g2_DrawCircle(&u8g2,64,32,32,U8G2_DRAW_ALL);//在屏幕中间画个圆
		u8g2_SendBuffer(&u8g2);
		u8g2_SetPowerSave(&u8g2, 0);
		Delay_s(5);u8g2_SetPowerSave(&u8g2, 1);
		Delay_s(5);
		
	}
}
