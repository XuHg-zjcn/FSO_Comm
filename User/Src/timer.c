#include "timer.h"

__IO uint32_t gTimingDelay;
/* SystemCoreClock / 1000    --> 1ms */
/* SystemCoreClock / 10000   --> 100us */
/* SystemCoreClock / 100000  --> 10us */
/* SystemCoreClock / 1000000 --> 1us */
void systick_init()
{
    while (SysTick_Config(8000000*9/1000) == 1);
}

void SysTick_Handler(void)
{
	if (gTimingDelay != 0x0)
	{
		gTimingDelay--;
	}
}

void delay_ms(uint32_t n)
{
    gTimingDelay = n;
    while(gTimingDelay != 0);
}


void delay_nwhile(uint32_t n) //SYSCLK_Cycs = 6n+9
{ while(n--);
}
