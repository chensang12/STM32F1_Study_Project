#include "stm32f10x.h"
#include "OLED_Font.h"
#include "u8g2.h"
#include "Delay.h"



/*引脚配置*/
#define OLED_W_SCL(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_9, (BitAction)(x))
#define OLED_W_SDA(x)		GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)(x))



/*引脚初始化*/
void OLED_I2C_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

uint8_t u8x8_gpio_and_delay_template(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	switch(msg)
	{
		case U8X8_MSG_DELAY_100NANO:					//Delay	100ns
			__NOP();
			break;
		case U8X8_MSG_DELAY_10MICRO:                  	//Delay	10us 
				for(uint16_t i = 0; i < 320; i++)
				{
					__NOP();
				}
			
			break;
			
		case U8X8_MSG_DELAY_MILLI:						//Delay	1ms
				Delay_ms(1);
			break;
		
		case U8X8_MSG_DELAY_I2C:						//arg_int 是I2C的速度，单位100KHZ
				Delay_us(5);
			break;	
			
		case U8X8_MSG_GPIO_I2C_CLOCK:					//arg_int = 0 SCL = 0;
				if(arg_int == 1)
				{
					OLED_W_SCL(1);
				}
				else if(arg_int == 0)
				{
					OLED_W_SCL(0);
				}
			break;
			
		case U8X8_MSG_GPIO_I2C_DATA:
				if(arg_int == 1)
				{
					OLED_W_SDA(1);
				}
				else if(arg_int == 0)
				{
					OLED_W_SDA(0);
				}
			break;	
			
		case U8X8_MSG_GPIO_MENU_SELECT:
				u8x8_SetGPIOResult(u8x8,0);
			break;
			
		case U8X8_MSG_GPIO_MENU_NEXT:
				u8x8_SetGPIOResult(u8x8,0);
			break;

		case U8X8_MSG_GPIO_MENU_PREV:
				u8x8_SetGPIOResult(u8x8,0);
			break;

		case U8X8_MSG_GPIO_MENU_HOME:
				u8x8_SetGPIOResult(u8x8,0);
			break;	
				
		default:
			u8x8_SetGPIOResult(u8x8,1);
			break;
	}
	return 1;
}


void U8G2_Init(u8g2_t *u8g2)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	u8g2_Setup_ssd1306_i2c_128x64_noname_f(u8g2, U8G2_R0, u8x8_byte_sw_i2c, u8x8_gpio_and_delay_template);   //初始化u8g2结构体
	u8g2_InitDisplay(u8g2);		//根据所选驱动芯片进行初始化工作
	u8g2_SetPowerSave(u8g2,0);	//打开显示器
	u8g2_ClearBuffer(u8g2);
}




/*对接函数模板,u8g2 库将通过这个函数指针来调用这个函数，这个函数用来现延时，IO口的控制等等*/
///*uint8_t u8x8_gpio_and_delay_template(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
//{
//  switch(msg)
//  {
//    case U8X8_MSG_GPIO_AND_DELAY_INIT:	// called once during init phase of u8g2/u8x8
//      break;							// can be used to setup pins
//    case U8X8_MSG_DELAY_NANO:			// delay arg_int * 1 nano second
//      break;    
//    case U8X8_MSG_DELAY_100NANO:		// delay arg_int * 100 nano seconds
//      break;
//    case U8X8_MSG_DELAY_10MICRO:		// delay arg_int * 10 micro seconds
//      break;
//    case U8X8_MSG_DELAY_MILLI:			// delay arg_int * 1 milli second
//      break;
//    case U8X8_MSG_DELAY_I2C:				// arg_int is the I2C speed in 100KHz, e.g. 4 = 400 KHz
//      break;							// arg_int=1: delay by 5us, arg_int = 4: delay by 1.25us
//    case U8X8_MSG_GPIO_D0:				// D0 or SPI clock pin: Output level in arg_int
//    //case U8X8_MSG_GPIO_SPI_CLOCK:
//      break;
//    case U8X8_MSG_GPIO_D1:				// D1 or SPI data pin: Output level in arg_int
//    //case U8X8_MSG_GPIO_SPI_DATA:
//      break;
//    case U8X8_MSG_GPIO_D2:				// D2 pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_D3:				// D3 pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_D4:				// D4 pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_D5:				// D5 pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_D6:				// D6 pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_D7:				// D7 pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_E:				// E/WR pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_CS:				// CS (chip select) pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_DC:				// DC (data/cmd, A0, register select) pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_RESET:			// Reset pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_CS1:				// CS1 (chip select) pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_CS2:				// CS2 (chip select) pin: Output level in arg_int
//      break;
//    case U8X8_MSG_GPIO_I2C_CLOCK:		// arg_int=0: Output low at I2C clock pin
//      break;							// arg_int=1: Input dir with pullup high for I2C clock pin
//    case U8X8_MSG_GPIO_I2C_DATA:			// arg_int=0: Output low at I2C data pin
//      break;							// arg_int=1: Input dir with pullup high for I2C data pin
//    case U8X8_MSG_GPIO_MENU_SELECT:
//      u8x8_SetGPIOResult(u8x8, /* get menu select pin state */ 0);
//     break;
//    case U8X8_MSG_GPIO_MENU_NEXT:
//      u8x8_SetGPIOResult(u8x8, /* get menu next pin state */ 0);
//      break;
//    case U8X8_MSG_GPIO_MENU_PREV:
//      u8x8_SetGPIOResult(u8x8, /* get menu prev pin state */ 0);
//      break;
//    case U8X8_MSG_GPIO_MENU_HOME:
//      u8x8_SetGPIOResult(u8x8, /* get menu home pin state */ 0);
//      break;
//    default:
//      u8x8_SetGPIOResult(u8x8, 1);			// default return value
//      break;
//  }
//  return 1;
//}





/**
  * @brief  I2C开始
  * @param  无
  * @retval 无
  */
void OLED_I2C_Start(void)
{
	OLED_W_SDA(1);
	OLED_W_SCL(1);
	OLED_W_SDA(0);
	OLED_W_SCL(0);
}

/**
  * @brief  I2C停止
  * @param  无
  * @retval 无
  */
void OLED_I2C_Stop(void)
{
	OLED_W_SDA(0);
	OLED_W_SCL(1);
	OLED_W_SDA(1);
}

/**
  * @brief  I2C发送一个字节
  * @param  Byte 要发送的一个字节
  * @retval 无
  */
void OLED_I2C_SendByte(uint8_t Byte)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		OLED_W_SDA(Byte & (0x80 >> i));
		OLED_W_SCL(1);
		OLED_W_SCL(0);
	}
	OLED_W_SCL(1);	//额外的一个时钟，不处理应答信号
	OLED_W_SCL(0);
}

/**
  * @brief  OLED写命令
  * @param  Command 要写入的命令
  * @retval 无
  */
void OLED_WriteCommand(uint8_t Command)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x00);		//写命令
	OLED_I2C_SendByte(Command); 
	OLED_I2C_Stop();
}

/**
  * @brief  OLED写数据
  * @param  Data 要写入的数据
  * @retval 无
  */
void OLED_WriteData(uint8_t Data)
{
	OLED_I2C_Start();
	OLED_I2C_SendByte(0x78);		//从机地址
	OLED_I2C_SendByte(0x40);		//写数据
	OLED_I2C_SendByte(Data);
	OLED_I2C_Stop();
}

/**
  * @brief  OLED设置光标位置
  * @param  Y 以左上角为原点，向下方向的坐标，范围：0~7
  * @param  X 以左上角为原点，向右方向的坐标，范围：0~127
  * @retval 无
  */
void OLED_SetCursor(uint8_t Y, uint8_t X)
{
	OLED_WriteCommand(0xB0 | Y);					//设置Y位置
	OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));	//设置X位置低4位
	OLED_WriteCommand(0x00 | (X & 0x0F));			//设置X位置高4位
}

/**
  * @brief  OLED清屏
  * @param  无
  * @retval 无
  */
void OLED_Clear(void)
{  
	uint8_t i, j;
	for (j = 0; j < 8; j++)
	{
		OLED_SetCursor(j, 0);
		for(i = 0; i < 128; i++)
		{
			OLED_WriteData(0x00);
		}
	}
}

/**
  * @brief  OLED显示一个字符
  * @param  Line 行位置，范围：1~4
  * @param  Column 列位置，范围：1~16
  * @param  Char 要显示的一个字符，范围：ASCII可见字符
  * @retval 无
  */
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char)
{      	
	uint8_t i;
	OLED_SetCursor((Line - 1) * 2, (Column - 1) * 8);		//设置光标位置在上半部分
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i]);			//显示上半部分内容
	}
	OLED_SetCursor((Line - 1) * 2 + 1, (Column - 1) * 8);	//设置光标位置在下半部分
	for (i = 0; i < 8; i++)
	{
		OLED_WriteData(OLED_F8x16[Char - ' '][i + 8]);		//显示下半部分内容
	}
}

/**
  * @brief  OLED显示字符串
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  String 要显示的字符串，范围：ASCII可见字符
  * @retval 无
  */
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i++)
	{
		OLED_ShowChar(Line, Column + i, String[i]);
	}
}

/**
  * @brief  OLED次方函数
  * @retval 返回值等于X的Y次方
  */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)
	{
		Result *= X;
	}
	return Result;
}

/**
  * @brief  OLED显示数字（十进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~4294967295
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  OLED显示数字（十进制，带符号数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：-2147483648~2147483647
  * @param  Length 要显示数字的长度，范围：1~10
  * @retval 无
  */
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length)
{
	uint8_t i;
	uint32_t Number1;
	if (Number >= 0)
	{
		OLED_ShowChar(Line, Column, '+');
		Number1 = Number;
	}
	else
	{
		OLED_ShowChar(Line, Column, '-');
		Number1 = -Number;
	}
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i + 1, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0');
	}
}

/**
  * @brief  OLED显示数字（十六进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~0xFFFFFFFF
  * @param  Length 要显示数字的长度，范围：1~8
  * @retval 无
  */
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i, SingleNumber;
	for (i = 0; i < Length; i++)							
	{
		SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
		if (SingleNumber < 10)
		{
			OLED_ShowChar(Line, Column + i, SingleNumber + '0');
		}
		else
		{
			OLED_ShowChar(Line, Column + i, SingleNumber - 10 + 'A');
		}
	}
}

/**
  * @brief  OLED显示数字（二进制，正数）
  * @param  Line 起始行位置，范围：1~4
  * @param  Column 起始列位置，范围：1~16
  * @param  Number 要显示的数字，范围：0~1111 1111 1111 1111
  * @param  Length 要显示数字的长度，范围：1~16
  * @retval 无
  */
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length)
{
	uint8_t i;
	for (i = 0; i < Length; i++)							
	{
		OLED_ShowChar(Line, Column + i, Number / OLED_Pow(2, Length - i - 1) % 2 + '0');
	}
}

/**
  * @brief  OLED初始化
  * @param  无
  * @retval 无
  */
void OLED_Init(void)
{
	uint32_t i, j;
	
	for (i = 0; i < 1000; i++)			//上电延时
	{
		for (j = 0; j < 1000; j++);
	}
	
	OLED_I2C_Init();			//端口初始化
	
	OLED_WriteCommand(0xAE);	//关闭显示
	
	OLED_WriteCommand(0xD5);	//设置显示时钟分频比/振荡器频率
	OLED_WriteCommand(0x80);
	
	OLED_WriteCommand(0xA8);	//设置多路复用率
	OLED_WriteCommand(0x3F);
	
	OLED_WriteCommand(0xD3);	//设置显示偏移
	OLED_WriteCommand(0x00);
	
	OLED_WriteCommand(0x40);	//设置显示开始行
	
	OLED_WriteCommand(0xA1);	//设置左右方向，0xA1正常 0xA0左右反置
	
	OLED_WriteCommand(0xC8);	//设置上下方向，0xC8正常 0xC0上下反置

	OLED_WriteCommand(0xDA);	//设置COM引脚硬件配置
	OLED_WriteCommand(0x12);
	
	OLED_WriteCommand(0x81);	//设置对比度控制
	OLED_WriteCommand(0xFF);

	OLED_WriteCommand(0xD9);	//设置预充电周期
	OLED_WriteCommand(0xF1);

	OLED_WriteCommand(0xDB);	//设置VCOMH取消选择级别
	OLED_WriteCommand(0x30);

	OLED_WriteCommand(0xA4);	//设置整个显示打开/关闭

	OLED_WriteCommand(0xA6);	//设置正常/倒转显示

	OLED_WriteCommand(0x8D);	//设置充电泵
	OLED_WriteCommand(0x14);

	OLED_WriteCommand(0xAF);	//开启显示
		
	OLED_Clear();				//OLED清屏
}
