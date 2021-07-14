#ifndef __ROCKER_H
#define __ROCKER_H
#include "stm32f10x.h"
#include "delay.h"

#define ADC_MEAN_TIME 10 // adcת�����ȣ�ȡ ADC_MEAN_TIME ��ת����ƽ��ֵ

// ʹ��ʱ��ռ��PA1��PA2��PA���뽫PA1���ӵ�ҡ�˵�VRx����PA2���ӵ�ҡ�˵�VRy��PA3����ҡ�˵�SW��ҡ�˹��������ʹ��3V3

void rocker_init(void);
int16_t rocker_x(void);
int16_t rocker_y(void);
u8 rocker_sw(void);


#endif
