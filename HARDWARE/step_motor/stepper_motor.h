#ifndef  __STEPPER_MOTOR_H
#define  __STEPPER_MOTOR_H
#include "sys.h"

/* 定义电机连接的GPIO端口, 用户只需要修改下面的代码即可改变控制的LED引脚 */
#define LA_GPIO_PORT    	GPIOA		                /* GPIO端口 */
#define LA_GPIO_CLK 	    RCC_APB2Periph_GPIOA		/* GPIO端口时钟 */
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
//void Stepper_motor_Ctrl_Direction_Angle(int direction, int angle);  //按某一方向旋转固定角度
//void Stepper_motorStop(void);//停止
//void Stepper_motorRccw(void); //逆时针
//void Stepper_motorRcw(void); //顺时针

//direction 可选项均为CW/CCW，分别表示顺时针和逆时针
//void OneStep4(u8 direction);
//void OneStep8(u8 direction);

//T为转一圈的时间   注意：T最小为6000，6000时还有可能出现卡顿情况
//void OneRound4(u8 direction, int T);

//T为转一圈的时间
//void OneRound8(u8 direction, int T);


//段然云：建议以T=7000作为电机最低延时.
//上面的函数声明被注释掉了，因为它们是咱们电机驱动开发者自己用的，不暴露给用户

//angle旋转角度；  T为转一圈的时间（单位：ms；T需要大于7000）；
void stepper_motor_ctrl(u8 direction, int angle, int T);

#endif
