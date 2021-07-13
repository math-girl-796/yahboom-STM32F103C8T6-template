#include "led.h"


void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //使能 PB,PE 端口时钟
	
	
	/* 设置PC13(LED 默认对应的管脚) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //LED1-->PC.13 推挽输出
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //IO 口速度为 50MHz
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);  //初始化 GPIO
	
	GPIO_SetBits(GPIOC,GPIO_Pin_13); //PE.13 输出高，即默认为灭灯
}


/*
	返回值：1，灯正亮着；0，灯正灭着
*/
u8 led_state(void)
{
	u8 ret = GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13);
	return !ret;
}


/*
	将led设为点亮状态
*/
void led_on(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}


/*
	将led设为熄灭状态
*/
void led_off(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
}


/*
	将led状态改变：亮变灭，灭变亮
*/
void led_switch(void)
{
	if(led_state()) led_off();
	else led_on();
}


//延时一段较短的时间
void led_delay()
{
	u32 i=0;
	for(;i<1000000;i++);
}
// 一些闪烁模式，内部自带延时，外部不需要再加延时

// 均匀快闪
void led_blink1(void)
{
	led_on();
	led_delay();
	led_off();
	led_delay();
}


// 均匀慢闪
void led_blink2(void)
{
	led_on();
	led_delay();
	led_delay();
	led_off();
	led_delay();
	led_delay();
}


// 快慢交替
void led_blink3(void)
{
	static u8 speed = 1;
	if (speed == 1) 
	{
		led_on();
		led_delay();
		led_off();
		led_delay();
		speed = 2;
	}
	else
	{
		led_on();
		led_delay();
		led_delay();
		led_off();
		led_delay();
		led_delay();
		speed = 1;
	}
	

}


// 快快慢慢
void led_blink4(void)
{
	static u8 speed = 1;
	if (speed == 1) 
	{
		led_on();
		led_delay();
		led_off();
		led_delay();
		speed = 2;
	}
	else if (speed == 2)
	{
		led_on();
		led_delay();
		led_off();
		led_delay();
		speed = 3;
	}
	else if (speed == 3)
	{
		led_on();
		led_delay();
		led_delay();
		led_off();
		led_delay();
		led_delay();
		speed = 4;
	}
	else
	{
		led_on();
		led_delay();
		led_delay();
		led_off();
		led_delay();
		led_delay();
		speed = 1;
	}
}


// 快快快慢慢慢
void led_blink5(void)
{
	static u8 speed = 1;
	if (speed == 1) 
	{
		led_on();
		led_delay();
		led_off();
		led_delay();
		speed = 2;
	}
	else if (speed == 2)
	{
		led_on();
		led_delay();
		led_off();
		led_delay();
		speed = 3;
	}
	else if (speed == 3)
	{
		led_on();
		led_delay();
		led_off();
		led_delay();
		speed = 4;
	}
	else if (speed == 4)
	{
		led_on();
		led_delay();
		led_delay();
		led_off();
		led_delay();
		led_delay();
		speed = 5;
	}
	else if (speed == 5)
	{
		led_on();
		led_delay();
		led_delay();
		led_off();
		led_delay();
		led_delay();
		speed = 6;
	}
	else
	{
		led_on();
		led_delay();
		led_delay();
		led_off();
		led_delay();
		led_delay();
		speed = 1;
	}
}
