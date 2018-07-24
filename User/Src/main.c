#include "stm32f10x.h"
#include "timer.h"
#include "Pins_init.h"
#include "NVIC.h"
#include <stdio.h>
#include "flash.h"
//PC13 on my board is a LED
#define Led_On   GPIO_SetBits(GPIOC, GPIO_Pin_13)
#define Led_Off GPIO_ResetBits(GPIOC, GPIO_Pin_13)
#define Led_FanZhuan GPIOC->ODR ^= GPIO_Pin_13
void RCC_PLL_Config(uint32_t RCC_PLLSource, uint32_t RCC_PLLMul) //RCC_PLLSource_HSE_Divx,RCC_PLLMul_x
{
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	RCC_WaitForHSEStartUp();
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_PLLConfig(RCC_PLLSource,RCC_PLLMul);
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while(RCC_GetSYSCLKSource() != 0x08);
}
void RCC_HSI_Config(uint8_t HSICalibrationValue)//RCC_SYSCLKSource_HSI or RCC_SYSCLKSource_HSE
{
	RCC_DeInit();
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div2);
	RCC_AdjustHSICalibrationValue(HSICalibrationValue); //0x11 8.012MHz
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
}
void ADC_Setup(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 2;
	ADC_Init(ADC1, &ADC_InitStructure);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_2,1,ADC_SampleTime_28Cycles5);
	ADC_RegularChannelConfig(ADC1,ADC_Channel_3,2,ADC_SampleTime_28Cycles5);
	
}
int main()
{
  SystemInit();
	RCC_PLL_Config(RCC_PLLSource_HSE_Div1, RCC_PLLMul_15);
	LED_Init();
	systick_init();
	Led_On;
  while(1)
  {

  }
}
