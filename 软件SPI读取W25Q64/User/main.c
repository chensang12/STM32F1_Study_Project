#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "string.h"

float fff =1.234;
char buf[128];

int main(void)
{

    sprintf(buf,"%.3f\n\r",fff);//A
    while(1);

}
