#ifndef __MOTOR_H
#define __MOTOR_H

#include "stm32f10x.h"

#define Motor_RCC_LEFT		 RCC_APB2Periph_GPIOA
#define Motor_Port_LEFT		 GPIOA
#define Left_MotoA_Pin 	 GPIO_Pin_6
#define Left_MotoB_Pin 	 GPIO_Pin_7

#define Motor_RCC_RIGHT		 RCC_APB2Periph_GPIOB
#define Motor_Port_RIGHT		 GPIOB
#define Right_MotoA_Pin	 GPIO_Pin_0
#define Right_MotoB_Pin  GPIO_Pin_1

#define  LeftMotor_Go()			{GPIO_SetBits(Motor_Port_LEFT, Left_MotoA_Pin); GPIO_ResetBits(Motor_Port_LEFT, Left_MotoB_Pin);}
#define  LeftMotor_Back()		{GPIO_ResetBits(Motor_Port_LEFT, Left_MotoA_Pin); GPIO_SetBits(Motor_Port_LEFT, Left_MotoB_Pin);}
#define  LeftMotor_Stop()		{GPIO_ResetBits(Motor_Port_LEFT, Left_MotoA_Pin); GPIO_ResetBits(Motor_Port_LEFT, Left_MotoB_Pin);}

#define  RightMotor_Go()		{GPIO_SetBits(Motor_Port_RIGHT, Right_MotoA_Pin); GPIO_ResetBits(Motor_Port_RIGHT, Right_MotoB_Pin);}
#define  RightMotor_Back()		{GPIO_ResetBits(Motor_Port_RIGHT, Right_MotoA_Pin); GPIO_SetBits(Motor_Port_RIGHT, Right_MotoB_Pin);}
#define  RightMotor_Stop()		{GPIO_ResetBits(Motor_Port_RIGHT, Right_MotoA_Pin); GPIO_ResetBits(Motor_Port_RIGHT, Right_MotoB_Pin);}

#define  LeftMotorPWM(Speed)	TIM_SetCompare1(TIM4, Speed);
#define  RightMotorPWM(Speed)	TIM_SetCompare2(TIM4, Speed);

void motor_init(void);
void MOTOR_GPIO_Init(void);
void Motor_PWM_Init(u16 arr, u16 psc, u16 arr2, u16 psc2 );






























#endif
