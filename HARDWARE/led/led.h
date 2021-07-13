#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

void led_init(void);
u8 led_state(void);
void led_on(void);
void led_off(void);
void led_switch(void);


#endif
