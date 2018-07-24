#include "stm32f10x_gpio.h"

void GpioConfigurationLed(void)
{
     GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* Enable the GPIO_LED Clock */
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB 
	                       |RCC_APB2Periph_GPIOC
						   |RCC_APB2Periph_GPIOD, ENABLE);
	
	/* Configure the GPIO_LED pin */
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	 GPIO_Init(GPIOA, &GPIO_InitStructure);

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	 GPIO_Init(GPIOB, &GPIO_InitStructure);

	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All ;
	 GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void LED_Init()
{
    GPIO_InitTypeDef s;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    s.GPIO_Pin = GPIO_Pin_13;
    s.GPIO_Mode = GPIO_Mode_Out_PP;
    s.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &s);
}
