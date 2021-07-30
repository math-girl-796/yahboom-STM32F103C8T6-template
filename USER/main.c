#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "rocker.h"
#include "timer3.h"
#include <stdio.h>
#include <string.h>
#include "stepper_motor.h"

void test_led(void);
void test_rocker(void);
void test_timer3(void);
void test_pwm(void);
//void test_pwm_and_rocker(void);// 未通过测试
void test_steer(void);
void test_stepper_motor(void);
void test_uart_and_motor(void);
void test_uart1(void);
void test_printf(void);
void test_uart3(void);
void test_6050(void);
void test_motor(void);

int main(void)
{
	test_motor();
}

#include "motor.h"
void test_motor(void)
{
	motor_init();
	delay_init();
	led_init();
	
	LeftMotor_Go();
	RightMotor_Go();
	while(1)
	{
		led_on();
		LeftMotorPWM(3500);
		RightMotorPWM(3500);
		delay_ms(1000);
		led_off();
		LeftMotorPWM(7100);
		RightMotorPWM(7100);
		delay_ms(1000);
		
//		led_on();
//		LeftMotor_Go();
//		delay_ms(1000);
//		LeftMotor_Back();
//		delay_ms(1000);
//		LeftMotor_Stop();
//		delay_ms(1000);
//		
//		led_off();
//		RightMotor_Go();
//		delay_ms(1000);
//		RightMotor_Back();
//		delay_ms(1000);
//		RightMotor_Stop();
//		delay_ms(1000);
	}
}

void test_uart3(void)
{
	led_init();
	delay_init();
	uart1_init(115200);
	uart3_init(9600);
	
	while(1)
	{
		// uart3 接收到数据 转发到uart1
		if (uart3NewLineReceived) 
		{
			printf("%s\r\n", USART3_RX_BUF);
			memset(USART3_RX_BUF, 0, sizeof(USART3_RX_BUF));
			uart3NewLineReceived = 0;
		}
		
		// uart1 接收到数据 转发到uart3
		int len = uart1_buf_status();
		if (len != 0)
		{
			u8 buf[50];
			uart1_read_buf(buf, len);
			uart3_send_bytes(buf, len);
		}
	
		
		// 休息 + 显示工作状态
		delay_ms(200);
		led_switch();
	}
}


#include "inv_mpu.h"
#include "mpu6050.h"
void test_6050(void)
{
	uart1_init(115200);
	delay_init();
	led_init();
	MPU_Init();
	
	// 初始化mpu6050 dmp库
	while(1)
 	{
		u8 ret = mpu_dmp_init();
		delay_ms(400);
		led_switch();
		if (ret != 0)
		{
			printf("mpu_dmp_init error: %d  \r\n", ret);
		}
		else
		{
			printf("mpu_dmp_init ok  \r\n");
			break;
		}
	} 
	
	
	// 从mpu6050 dmp中不断读数据，并发送到串口
	float pitch, roll, yaw;
	while (1)
	{
		u8 ret = mpu_dmp_get_data(&pitch,&roll,&yaw);
		if (ret == 0)
		{
			printf("pitch: %f\t roll: %f\t yaw: %f\t   \r\n", pitch, roll, yaw);
		}
		else 
		{
//			printf("mpu_dmp_get_data error: %d  \r\n", ret);
		}
		delay_ms(200);
		led_switch();
	}
	
}

void test_printf(void)
{
	uart1_init(115200);
	delay_init();
	led_init();
	
	while(1)
	{
		led_switch();
		printf("hello\r\n");
		delay_ms(200);
	}
}


void test_uart_and_motor(void)
{
	u8 direction = CW;
	int cycle = 8000;
	int len = 0;
	u8 buf[5];
	
	delay_init();
	uart1_init(115200);
	stepper_motor_init();
	

	while(1)
	{
		if ((len = uart1_buf_status()) == 5)
		{
			u8 temp_direction;
			int temp_cycle;
			uart1_read_buf(buf, 5);
			temp_direction = buf[0];
			temp_cycle = buf[1] + (buf[2] << 8) + (buf[3] << 16) + (buf[4] << 24);
			printf("%d\t%d\t", temp_direction, temp_cycle);
			
			if (temp_direction == CW || temp_direction == CCW)
			{
				direction = temp_direction;
				printf("方向修改成功\t");
			}
			if (temp_cycle >= 7000)
			{
				cycle = temp_cycle;
				printf("速度修改成功");
			}
			printf("\r\n");
		}
		else if (len > 0)
		{
			uart1_clear_buf();
		}
		
		stepper_motor_ctrl_512(direction, 2, cycle);
	}
}

void test_uart1(void)
{
	u8 len;	
	u16 times=0;  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init();		//延时初始化 
	
	uart1_init(115200);	//串口初始化波特率为115200
	
	led_init();
	
	
	
	while(1)
	{
		if((len = uart1_buf_status()) != 0)
		{					   
			u8 str[20];
			
			uart1_read_buf(str, len);
			
			uart1_send_bytes(str, len);
			
			uart1_clear_buf();
			
		}else
		{
			times++;
			if(times%200==0)
			{
				static u8 a = 0;
				
				char str[10];
				
				sprintf(str, "%c%c\r\n", a+65, a+66);
				
				uart1_send_bytes((u8 *)str, 4);
				
				a ++;
				a = a % 26;
				
				led_switch();
			}
			delay_ms(10);   
		}
	}
}


void test_led(void)
{
	led_init();
	
	while(1)
	{
		led_blink3();
	}
}

void test_stepper_motor(void)
{
//	int i;
	
	led_init();
	stepper_motor_init();
	delay_init();
	
	while(1)
	{
		stepper_motor_ctrl(CW, 90, 8000);
		stepper_motor_ctrl(CCW, 90, 7000);
	}
}


// 连接PA6到9g舵机控制口
void test_steer(void)
{
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
// 下一步改进计划：把x映射到500-2500，然后用TIM_SetCompare设置舵机的角度
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
	uart1_init(115200);
	
	while (1)
	{
		x = rocker_x();
		duration = ((x + 2048.) / 4096  + 1) / 40;
		
		sprintf(str, "%f\r\n", duration);
		uart1_send_bytes((u8*)str, strlen(str));
		
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
		if (duration < 0.5) 
		{
			duration = 0;
			direct = 1;
		}
		if (duration > 1) 
		{
			duration = 1;
			direct = 0;
		}
		if (direct == 1) duration += 0.001;
		if (direct == 0) duration -= 0.001;
		
		TIM3_CH1_PWM_SetDuration(duration);
		TIM3_CH2_PWM_SetDuration(1.5 - duration);
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
	uart1_init(115200);	 //串口初始化为115200
 	led_init();			     //LED端口初始化
 	
 	rocker_init();		  		//ADC初始化

	strcpy(str, "hello\r\n");
	
	while(1)
	{
		
		adcx1=rocker_x();
		adcx2=rocker_y();
		key=rocker_sw();
		
		
		sprintf(str, "x:%d\ty:%d\tkey:%d\r\n", adcx1, adcx2, key);
		
		uart1_send_bytes((u8*)str, strlen(str));
		
//		led_switch();
		delay_ms(500);	
	}
}
