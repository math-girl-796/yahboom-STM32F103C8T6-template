#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "ADC.h"
#include "rocker.h"
#include <stdio.h>
#include <string.h>


int main(void)
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
