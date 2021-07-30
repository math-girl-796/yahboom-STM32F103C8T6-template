#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "rocker.h"
#include <stdio.h>
#include <string.h>
#include "stepper_motor.h"
#include "motor.h"

void test_led(void);
void test_rocker(void);
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
	TIM3_Encoder_Init();
	led_init();
	uart1_init(115200);
	
	LeftMotor_Go();
	RightMotor_Go();
	LeftMotorPWM(1000);
	RightMotorPWM(1000);
	
	while(1)
	{
		led_switch();
		delay_ms(500);
		printf("%d\t", read_tim3_cnt());
		
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
		// uart3 ���յ����� ת����uart1
		if (uart3NewLineReceived) 
		{
			printf("%s\r\n", USART3_RX_BUF);
			memset(USART3_RX_BUF, 0, sizeof(USART3_RX_BUF));
			uart3NewLineReceived = 0;
		}
		
		// uart1 ���յ����� ת����uart3
		int len = uart1_buf_status();
		if (len != 0)
		{
			u8 buf[50];
			uart1_read_buf(buf, len);
			uart3_send_bytes(buf, len);
		}
	
		
		// ��Ϣ + ��ʾ����״̬
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
	
	// ��ʼ��mpu6050 dmp��
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
	
	
	// ��mpu6050 dmp�в��϶����ݣ������͵�����
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
				printf("�����޸ĳɹ�\t");
			}
			if (temp_cycle >= 7000)
			{
				cycle = temp_cycle;
				printf("�ٶ��޸ĳɹ�");
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();		//��ʱ��ʼ�� 
	
	uart1_init(115200);	//���ڳ�ʼ��������Ϊ115200
	
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


            


// �뽫PA1���ӵ�ҡ�˵�VRx����PA2���ӵ�ҡ�˵�VRy��PA3����ҡ�˵�SW��ҡ�˹��������ʹ��3V3
void test_rocker(void)
{
	int16_t adcx1 = 0;
	int16_t adcx2 = 0;
	u8 key = 0;
	char str[100];
	
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart1_init(115200);	 //���ڳ�ʼ��Ϊ115200
 	led_init();			     //LED�˿ڳ�ʼ��
 	
 	rocker_init();		  		//ADC��ʼ��

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
