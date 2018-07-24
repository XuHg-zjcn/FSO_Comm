#include "Pins_init.h"
void LED_Init()
{
    GPIO_InitTypeDef s;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
    s.GPIO_Pin = GPIO_Pin_13;
    s.GPIO_Mode = GPIO_Mode_Out_PP;
    s.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &s);
}

void PA8_Clock_init()
{
	GPIO_InitTypeDef s;
	s.GPIO_Pin = GPIO_Pin_8;
	s.GPIO_Speed = GPIO_Speed_50MHz; 
	s.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOA, &s);
	RCC_MCOConfig(RCC_MCO_PLLCLK_Div2);
}
