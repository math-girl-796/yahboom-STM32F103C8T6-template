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


// ����PA6��9g������ƿ�
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
		TIM_SetCompare1(TIM3,1500); // ���Է���9g�����19999��71��pwm��compare������ΧΪ500-2500
	}

}


// �������ʹ��������
// PA6����9g������������ϣ����߷��ߵ�PC13Ҳ��
void test_pwm_and_rocker(void)
{
	float duration = 0;
	int16_t x = 0;
	char str[100];
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	

	// ԭʱ��Ϊ72,000,000hz
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

// PA6��PA7�е�һ�����߳������PC13�Ǹ�������
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


// ���ý���
void test_timer3(void)
{
	TIM3_Ms_Init(1000);
	led_init();
	while(1){;}
}


// �뽫PA1���ӵ�ҡ�˵�VRx����PA2���ӵ�ҡ�˵�VRy��PA3����ҡ�˵�SW��ҡ�˹��������ʹ��3V3
void test_rocker(void)
{
	int16_t adcx1 = 0;
	int16_t adcx2 = 0;
	u8 key = 0;
	char str[100];
	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	led_init();			     //LED�˿ڳ�ʼ��
 	
 	rocker_init();		  		//ADC��ʼ��

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
