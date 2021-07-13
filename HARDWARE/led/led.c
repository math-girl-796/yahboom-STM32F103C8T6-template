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
