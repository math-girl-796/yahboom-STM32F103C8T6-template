#ifndef __ROCKER_H
#define __ROCKER_H
#include "stm32f10x.h"
#include "delay.h"

#define ADC_MEAN_TIME 10 // adc转换精度：取 ADC_MEAN_TIME 次转换的平均值

// 使用时会占用PA1、PA2和PA，请将PA1连接到摇杆的VRx，将PA2连接到摇杆的VRy，PA3连接摇杆的SW。摇杆供电请务必使用3V3

void rocker_init(void);
int16_t rocker_x(void);
int16_t rocker_y(void);
u8 rocker_sw(void);


#endif
