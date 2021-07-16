#ifndef __TIMER3_H
#define __TIMER3_H
#include "sys.h"
#include "usart.h"
#include <string.h>
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//��ʱ�� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   

static u16 TIM3_CH1_PWM_ARR;
static u16 TIM3_CH2_PWM_ARR;

void TIM3_Ms_Init(u16 ms);

void TIM3_Int_Init(u16 arr,u16 psc);

void TIM3_CH1_PWM_Init(u16 arr, u16 psc); // PA6

void TIM3_CH1_PWM_SetDuration(float duration);

void TIM3_CH2_PWM_Init(u16 arr, u16 psc); // PA7

void TIM3_CH2_PWM_SetDuration(float duration);

#endif
