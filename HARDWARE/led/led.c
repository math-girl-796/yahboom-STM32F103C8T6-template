#include "led.h"


void led_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE); //ʹ�� PB,PE �˿�ʱ��
	
	
	/* ����PC13(LED Ĭ�϶�Ӧ�Ĺܽ�) */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //LED1-->PC.13 �������
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  //IO ���ٶ�Ϊ 50MHz
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);  //��ʼ�� GPIO
	
	GPIO_SetBits(GPIOC,GPIO_Pin_13); //PE.13 ����ߣ���Ĭ��Ϊ���
}


/*
	����ֵ��1���������ţ�0����������
*/
u8 led_state(void)
{
	u8 ret = GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13);
	return !ret;
}


/*
	��led��Ϊ����״̬
*/
void led_on(void)
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}


/*
	��led��ΪϨ��״̬
*/
void led_off(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
}


/*
	��led״̬�ı䣺�����������
*/
void led_switch(void)
{
	if(led_state()) led_off();
	else led_on();
}


//��ʱһ�ν϶̵�ʱ��
void led_delay()
{
	u32 i=0;
	for(;i<1000000;i++);
}
// һЩ��˸ģʽ���ڲ��Դ���ʱ���ⲿ����Ҫ�ټ���ʱ

// ���ȿ���
void led_blink1(void)
{
	led_on();
	led_delay();
	led_off();
	led_delay();
}


// ��������
void led_blink2(void)
{
	led_on();
	led_delay();
	led_delay();
	led_off();
	led_delay();
	led_delay();
}


// ��������
void led_blink3(void)
{
	static u8 speed = 1;
	if (speed == 1) 
	{
		led_on();
		led_delay();
		led_off();
		led_delay();
		speed = 2;
	}
	else
	{
		led_on();
		led_delay();
		led_delay();
		led_off();
		led_delay();
		led_delay();
		speed = 1;
	}
	

}


// �������
void led_blink4(void)
{
	static u8 speed = 1;
	if (speed == 1) 
	{
		led_on();
		led_delay();
		led_off();
		led_delay();
		speed = 2;
	}
	else if (speed == 2)
	{
		led_on();
		led_delay();
		led_off();
		led_delay();
		speed = 3;
	}
	else if (speed == 3)
	{
		led_on();
		led_delay();
		led_delay();
		led_off();
		led_delay();
		led_delay();
		speed = 4;
	}
	else
	{
		led_on();
		led_delay();
		led_delay();
		led_off();
		led_delay();
		led_delay();
		speed = 1;
	}
}


// ����������
void led_blink5(void)
{
	static u8 speed = 1;
	if (speed == 1) 
	{
		led_on();
		led_delay();
		led_off();
		led_delay();
		speed = 2;
	}
	else if (speed == 2)
	{
		led_on();
		led_delay();
		led_off();
		led_delay();
		speed = 3;
	}
	else if (speed == 3)
	{
		led_on();
		led_delay();
		led_off();
		led_delay();
		speed = 4;
	}
	else if (speed == 4)
	{
		led_on();
		led_delay();
		led_delay();
		led_off();
		led_delay();
		led_delay();
		speed = 5;
	}
	else if (speed == 5)
	{
		led_on();
		led_delay();
		led_delay();
		led_off();
		led_delay();
		led_delay();
		speed = 6;
	}
	else
	{
		led_on();
		led_delay();
		led_delay();
		led_off();
		led_delay();
		led_delay();
		speed = 1;
	}
}
