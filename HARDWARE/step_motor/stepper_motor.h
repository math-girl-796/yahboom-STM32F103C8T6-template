#ifndef  __STEPPER_MOTOR_H
#define  __STEPPER_MOTOR_H
#include "sys.h"
#include "stdio.h"
#include "sys.h"
#include "delay.h"

/* ���������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�LED���� */
#define LA_GPIO_PORT    	GPIOB		                /* GPIO�˿� */
#define LA_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO�˿�ʱ�� */
#define LA_GPIO_PIN			GPIO_Pin_6

#define LB_GPIO_PORT    	GPIOB
#define LB_GPIO_CLK 	    RCC_APB2Periph_GPIOB
#define LB_GPIO_PIN		    GPIO_Pin_7

#define LC_GPIO_PORT    	GPIOB
#define LC_GPIO_CLK 	    RCC_APB2Periph_GPIOB
#define LC_GPIO_PIN		    GPIO_Pin_8

#define LD_GPIO_PORT    	GPIOB
#define LD_GPIO_CLK 	    RCC_APB2Periph_GPIOB
#define LD_GPIO_PIN		    GPIO_Pin_9

#define CW 1
#define CCW 0

void stepper_motor_init(void);

//void Stepper_motorStop(void);//ֹͣ

//direction ��ѡ���ΪCW/CCW���ֱ��ʾ˳ʱ�����ʱ��
//void OneStep4(u8 direction);
//void OneStep8(u8 direction);

//TΪתһȦ��ʱ��   ע�⣺T��СΪ6000��6000ʱ���п��ܳ��ֿ������
//void OneRound4(u8 direction, int T);

//TΪתһȦ��ʱ��
//void OneRound8(u8 direction, int T);


//��Ȼ�ƣ�������T=7000��Ϊ��������ʱ.

//angle��ת�Ƕȣ�  TΪתһȦ��ʱ�䣨��λ��ms��T��Ҫ����7000����
//����ʹ����������ʵ�֣��Ƕ�ԽС�����Խ��
//С�Ƕ�ʱ��ʹ��stepper_motor_ctrl_512����
void stepper_motor_ctrl(u8 direction, int angle, int T);

//���ڶ���������stepper_motor_ctrl��ͬ
//factorΪ512ʱתһȦ��factorÿ��һ����ת0.703125�Ƕ�
void stepper_motor_ctrl_512(u8 direction, int factor, int T);

#endif
