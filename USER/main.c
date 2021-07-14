#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "rocker.h"
#include "timer3.h"
#include <stdio.h>
#include <string.h>

void test_rocker(void);
void test_timer3(void);
void test_pwm(void);
//void test_pwm_and_rocker(void);
void test_steer(void);


int main(void)
{
	test_steer();
}


// 连接PA6到9g舵机控制口
void test_steer(void)
{
	
	int pos = 0;
	
	delay_init();
	
	TIM3_CH1_PWM_Init(19999, 71);
	while(1)
	{
		delay_ms(1000);
		TIM_SetCompare1(TIM3,500);
		delay_ms(1000);
		TIM_SetCompare1(TIM3,1500);
		delay_ms(1000);
		TIM_SetCompare1(TIM3,2500);
		delay_ms(1000);
		TIM_SetCompare1(TIM3,1500); // 尝试发现9g舵机在19999，71的pwm下compare工作范围为500-2500
	}

}


// 这个不好使，舵机疯狂抖
// PA6连在9g舵机控制输入上，或者飞线到PC13也行
void test_pwm_and_rocker(void)
{
	float duration = 0;
	int16_t x = 0;
	char str[100];
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	

	// 原时钟为72,000,000hz
	TIM3_CH1_PWM_Init(19999, 71); 
	delay_init();
	led_init();
	rocker_init();
	uart_init(115200);
	
	while (1)
	{
		x = rocker_x();
		duration = ((x + 2048.) / 4096  + 1) / 40;
		
		sprintf(str, "%f\r\n", duration);
		uart_send_string(str);
		
		TIM3_CH1_PWM_SetDuration(duration);
		
		delay_ms(1000);                           
	}
}                

// PA6和PA7中的一个飞线出来怼在PC13那个焊点上
void test_pwm(void)
{
	float duration = 0;
	u8 direct = 0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	

	TIM3_CH1_PWM_Init(899,0);
	TIM3_CH2_PWM_Init(899,0);
	delay_init();
	
	while (1)
	{
		if (duration < 0) 
		{
			duration = 0;
			direct = 1;
		}
		if (duration > 0.1) 
		{
			duration = 0.1;
			direct = 0;
		}
		if (direct == 1) duration += 0.001;
		if (direct == 0) duration -= 0.001;
		
		TIM3_CH1_PWM_SetDuration(duration);
		TIM3_CH2_PWM_SetDuration(0.1 - duration);
		delay_ms(10);
	}
}


// 不用接线
void test_timer3(void)
{
	TIM3_Ms_Init(1000);
	led_init();
	while(1){;}
}


// 请将PA1连接到摇杆的VRx，将PA2连接到摇杆的VRy，PA3连接摇杆的SW。摇杆供电请务必使用3V3
void test_rocker(void)
{
	int16_t adcx1 = 0;
	int16_t adcx2 = 0;
	u8 key = 0;
	char str[100];
	
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
 	led_init();			     //LED端口初始化
 	
 	rocker_init();		  		//ADC初始化

	strcpy(str, "hello\r\n");
	
	while(1)
	{
		
		adcx1=rocker_x();
		adcx2=rocker_y();
		key=rocker_sw();
		
		
		sprintf(str, "x:%d\ty:%d\tkey:%d\r\n", adcx1, adcx2, key);
		
		uart_send_string(str);
		
//		led_switch();
		delay_ms(500);	
	}
}
