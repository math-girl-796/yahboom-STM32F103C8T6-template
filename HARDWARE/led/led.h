#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

// 该器件初始化后会占用PC13管脚

void led_init(void);
u8 led_state(void);
void led_on(void);
void led_off(void);
void led_switch(void);


// 一些闪烁模式，内部自带延时，外部不需要再加延时
void led_blink1(void);
void led_blink2(void);
void led_blink3(void);
void led_blink4(void);
void led_blink5(void);


#endif
