#ifndef _TIMER_H_
#define _TIMER_H_

#include "stm32f10x.h"
#include "flash.h"

#define Led_On   GPIO_SetBits(GPIOC, GPIO_Pin_13)
#define Led_Off  GPIO_ResetBits(GPIOC, GPIO_Pin_13)
#define Led_FanZhuan GPIOC->ODR ^= GPIO_Pin_13
void systick_init(void);
void delay_ms(__IO uint32_t n);
void delay_nwhile(u32 n);

#endif
