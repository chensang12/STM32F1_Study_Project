#ifndef __I2C_H

void HardWareI2C_Init(void);
void HardWareI2C_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT);

#endif




