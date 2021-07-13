#include "stm32f10x.h"
#include "led.h"


void Delay(u32 count)
{
	u32 i=0;
	for(;i<count;i++);
}

int main(void)
{
	led_init();
	
	led_on();
	
	while(1)
	{
//		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
//		Delay(3000000);
//		GPIO_SetBits(GPIOB,GPIO_Pin_13);
//		Delay(3000000);
	}
}
