#include "stm32f10x.h"
#include "led.h"
#include "delay.h"


void Delay(u32 count)
{
	u32 i=0;
	for(;i<count;i++);
}

int main(void)
{
	led_init();
	delay_init();
	
	
	led_off();
	
	while(1)
	{
		led_blink5();
	}
}
