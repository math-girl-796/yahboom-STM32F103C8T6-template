#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

void led_init(void);
u8 led_state(void);
void led_on(void);
void led_off(void);
void led_switch(void);


// һЩ��˸ģʽ���ڲ��Դ���ʱ���ⲿ����Ҫ�ټ���ʱ
void led_blink1(void);
void led_blink2(void);
void led_blink3(void);
void led_blink4(void);
void led_blink5(void);


#endif