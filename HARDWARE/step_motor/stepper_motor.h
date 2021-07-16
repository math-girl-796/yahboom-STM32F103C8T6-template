#ifndef  __STEPPER_MOTOR_H
#define  __STEPPER_MOTOR_H
#include "sys.h"

/* ���������ӵ�GPIO�˿�, �û�ֻ��Ҫ�޸�����Ĵ��뼴�ɸı���Ƶ�LED���� */
#define LA_GPIO_PORT    	GPIOA		                /* GPIO�˿� */
#define LA_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO�˿�ʱ�� */
#define LA_GPIO_PIN			  GPIO_Pin_4

#define LB_GPIO_PORT    	GPIOA
#define LB_GPIO_CLK 	    RCC_APB2Periph_GPIOA
#define LB_GPIO_PIN		    GPIO_Pin_5

#define LC_GPIO_PORT    	GPIOA
#define LC_GPIO_CLK 	    RCC_APB2Periph_GPIOA
#define LC_GPIO_PIN		    GPIO_Pin_6

#define LD_GPIO_PORT    	GPIOA
#define LD_GPIO_CLK 	    RCC_APB2Periph_GPIOA
#define LD_GPIO_PIN		    GPIO_Pin_7

#define CW 1
#define CCW 0

void stepper_motor_init(void);
//void Stepper_motor_Ctrl_Direction_Angle(int direction, int angle);  //��ĳһ������ת�̶��Ƕ�
//void Stepper_motorStop(void);//ֹͣ
//void Stepper_motorRccw(void); //��ʱ��
//void Stepper_motorRcw(void); //˳ʱ��

//direction ��ѡ���ΪCW/CCW���ֱ��ʾ˳ʱ�����ʱ��
//void OneStep4(u8 direction);
//void OneStep8(u8 direction);

//TΪתһȦ��ʱ��   ע�⣺T��СΪ6000��6000ʱ���п��ܳ��ֿ������
//void OneRound4(u8 direction, int T);

//TΪתһȦ��ʱ��
//void OneRound8(u8 direction, int T);


//��Ȼ�ƣ�������T=7000��Ϊ��������ʱ.
//����ĺ���������ע�͵��ˣ���Ϊ���������ǵ�������������Լ��õģ�����¶���û�

//angle��ת�Ƕȣ�  TΪתһȦ��ʱ�䣨��λ��ms��T��Ҫ����7000����
void stepper_motor_ctrl(u8 direction, int angle, int T);

#endif
