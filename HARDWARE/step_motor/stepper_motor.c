// ���Žӷ�
// IN4��PB6  d     
// IN3: PB7  c
// IN2: PB8  b
// IN1: PB9  a

#include "stdio.h"
#include "sys.h"
#include "delay.h"
#include "stepper_motor.h"



void stepper_motor_init(void)  //���ų�ʼ��PB6 7 8 9
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 ;
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB,&GPIO_InitStructure);
	 GPIO_ResetBits(GPIOB,GPIO_Pin_6 | GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9 );
}


void OneStep4(u8 direction)  
{
	static uint8_t step = 0;
	if (direction == CW)
	{
		switch(step)
		{

		case 0:
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
		case 1:
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
		case 2:
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_SetBits(GPIOB, GPIO_Pin_8);
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
		case 3:
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			GPIO_SetBits(GPIOB, GPIO_Pin_9);
			break;
		}
	}

	else if (direction == CCW)
	{
		switch(step)
		{
		case 0:
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			GPIO_SetBits(GPIOB, GPIO_Pin_9);
			break;
		case 1:
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_SetBits(GPIOB, GPIO_Pin_8);
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
		case 2:
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
		case 3:
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
	}
}
	step = (step + 1) % 4;
}
	
void OneStep8(u8 direction)
{
	static uint8_t step = 0;
	if (direction == CW)
	{

		switch(step)
		{
		case 0:
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
		case 1:
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
		case 2:
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
		case 3:
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
			GPIO_SetBits(GPIOB, GPIO_Pin_8);
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
		case 4:
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_SetBits(GPIOB, GPIO_Pin_8);
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
		case 5:
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_SetBits(GPIOB, GPIO_Pin_8);
			GPIO_SetBits(GPIOB, GPIO_Pin_9);
			break;
		case 6:
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			GPIO_SetBits(GPIOB, GPIO_Pin_9);
			break;
		case 7:
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			GPIO_SetBits(GPIOB, GPIO_Pin_9);
			break;
		}
	}

	else if (direction == CCW)
	{
		switch(step)
		{
		case 0:
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			GPIO_SetBits(GPIOB, GPIO_Pin_9);
			break;
		case 1:
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			GPIO_SetBits(GPIOB, GPIO_Pin_9);
			break;
		case 2:
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_SetBits(GPIOB, GPIO_Pin_8);
			GPIO_SetBits(GPIOB, GPIO_Pin_9);
			break;
		case 3:
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_SetBits(GPIOB, GPIO_Pin_8);
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
		case 4:
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
			GPIO_SetBits(GPIOB, GPIO_Pin_8);
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
		case 5:
			GPIO_ResetBits(GPIOB, GPIO_Pin_6);
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
		case 6:
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			GPIO_SetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
		case 7:
			GPIO_SetBits(GPIOB, GPIO_Pin_6);
			GPIO_ResetBits(GPIOB, GPIO_Pin_7);
			GPIO_ResetBits(GPIOB, GPIO_Pin_8);
			GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			break;
		}
	}
	step = (step + 1) % 8;
}
 
void Stepper_motorStop(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_6);
	GPIO_ResetBits(GPIOB, GPIO_Pin_7);
	GPIO_ResetBits(GPIOB, GPIO_Pin_8);
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);
}


void OneRound4(u8 direction, int T)  //0Ϊ��ʱ�룬1Ϊ˳ʱ�룻TתһȦ����ʱ�䣨ms����ѭ��512��תһȦ //��һ�֣�ת��ת45��
{
	u32 t;
	t=T*1000/(64*8);//t������һ���õ�ʱ��

	if(direction == CW)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_6);
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		GPIO_ResetBits(GPIOB, GPIO_Pin_9);
		delay_us(t/4);

		GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		GPIO_SetBits(GPIOB, GPIO_Pin_7);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		GPIO_ResetBits(GPIOB, GPIO_Pin_9);
		delay_us(t/4);

		GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		GPIO_SetBits(GPIOB, GPIO_Pin_8);
		GPIO_ResetBits(GPIOB, GPIO_Pin_9);
		delay_us(t/4);

		GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		GPIO_SetBits(GPIOB, GPIO_Pin_9);
		delay_us(t/4);
	}

	else if(direction == CCW)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		GPIO_SetBits(GPIOB, GPIO_Pin_9);
		delay_us(t/4);

		GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		GPIO_SetBits(GPIOB, GPIO_Pin_8);
		GPIO_ResetBits(GPIOB, GPIO_Pin_9);
		delay_us(t/4);

		GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		GPIO_SetBits(GPIOB, GPIO_Pin_7);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		GPIO_ResetBits(GPIOB, GPIO_Pin_9);
		delay_us(t/4);

		GPIO_SetBits(GPIOB, GPIO_Pin_6);
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);
		GPIO_ResetBits(GPIOB, GPIO_Pin_8);
		GPIO_ResetBits(GPIOB, GPIO_Pin_9);
		delay_us(t/4);
	}
	
}


void OneRound8(u8 direction, int T)  //0Ϊ��1Ϊ��TתһȦ����ʱ�䣨ms����ѭ��512��תһȦ //��һ�֣�ת��ת45��
{
	   u32 t;
	   t=T*1000/(64*8);//t������һ���õ�ʱ��
	
	   if(direction == CW)
		 {
          GPIO_SetBits(GPIOB, GPIO_Pin_6);
					GPIO_ResetBits(GPIOB, GPIO_Pin_7);
					GPIO_ResetBits(GPIOB, GPIO_Pin_8);
					GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			    delay_us(t/8);
			 
					GPIO_SetBits(GPIOB, GPIO_Pin_6);
					GPIO_SetBits(GPIOB, GPIO_Pin_7);
					GPIO_ResetBits(GPIOB, GPIO_Pin_8);
					GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			    delay_us(t/8);
			 
					GPIO_ResetBits(GPIOB, GPIO_Pin_6);
					GPIO_SetBits(GPIOB, GPIO_Pin_7);
					GPIO_ResetBits(GPIOB, GPIO_Pin_8);
					GPIO_ResetBits(GPIOB, GPIO_Pin_9);
				  delay_us(t/8);
			 
					GPIO_ResetBits(GPIOB, GPIO_Pin_6);
					GPIO_SetBits(GPIOB, GPIO_Pin_7);
					GPIO_SetBits(GPIOB, GPIO_Pin_8);
					GPIO_ResetBits(GPIOB, GPIO_Pin_9);
				  delay_us(t/8);
					
					GPIO_ResetBits(GPIOB, GPIO_Pin_6);
					GPIO_ResetBits(GPIOB, GPIO_Pin_7);
					GPIO_SetBits(GPIOB, GPIO_Pin_8);
					GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			    delay_us(t/8);
					
					GPIO_ResetBits(GPIOB, GPIO_Pin_6);
					GPIO_ResetBits(GPIOB, GPIO_Pin_7);
					GPIO_SetBits(GPIOB, GPIO_Pin_8);
					GPIO_SetBits(GPIOB, GPIO_Pin_9);
		      delay_us(t/8);
					
					GPIO_ResetBits(GPIOB, GPIO_Pin_6);
					GPIO_ResetBits(GPIOB, GPIO_Pin_7);
					GPIO_ResetBits(GPIOB, GPIO_Pin_8);
					GPIO_SetBits(GPIOB, GPIO_Pin_9);
			    delay_us(t/8);
					
					GPIO_SetBits(GPIOB, GPIO_Pin_6);
					GPIO_ResetBits(GPIOB, GPIO_Pin_7);
					GPIO_ResetBits(GPIOB, GPIO_Pin_8);
					GPIO_SetBits(GPIOB, GPIO_Pin_9);
					delay_us(t/8);
				}
		 
		 else if(direction == CCW)
		 {
					GPIO_SetBits(GPIOB, GPIO_Pin_6);
					GPIO_ResetBits(GPIOB, GPIO_Pin_7);
					GPIO_ResetBits(GPIOB, GPIO_Pin_8);
					GPIO_SetBits(GPIOB, GPIO_Pin_9);
				  delay_us(t/8);
			 
					GPIO_ResetBits(GPIOB, GPIO_Pin_6);
					GPIO_ResetBits(GPIOB, GPIO_Pin_7);
					GPIO_ResetBits(GPIOB, GPIO_Pin_8);
					GPIO_SetBits(GPIOB, GPIO_Pin_9);
				  delay_us(t/8);
			 
					GPIO_ResetBits(GPIOB, GPIO_Pin_6);
					GPIO_ResetBits(GPIOB, GPIO_Pin_7);
					GPIO_SetBits(GPIOB, GPIO_Pin_8);
					GPIO_SetBits(GPIOB, GPIO_Pin_9);
				  delay_us(t/8);
			 
					GPIO_ResetBits(GPIOB, GPIO_Pin_6);
					GPIO_ResetBits(GPIOB, GPIO_Pin_7);
					GPIO_SetBits(GPIOB, GPIO_Pin_8);
					GPIO_ResetBits(GPIOB, GPIO_Pin_9);
				  delay_us(t/8);
				
					GPIO_ResetBits(GPIOB, GPIO_Pin_6);
					GPIO_SetBits(GPIOB, GPIO_Pin_7);
					GPIO_SetBits(GPIOB, GPIO_Pin_8);
					GPIO_ResetBits(GPIOB, GPIO_Pin_9);
				  delay_us(t/8);
				
					GPIO_ResetBits(GPIOB, GPIO_Pin_6);
					GPIO_SetBits(GPIOB, GPIO_Pin_7);
					GPIO_ResetBits(GPIOB, GPIO_Pin_8);
					GPIO_ResetBits(GPIOB, GPIO_Pin_9);
				  delay_us(t/8);
				
					GPIO_SetBits(GPIOB, GPIO_Pin_6);
					GPIO_SetBits(GPIOB, GPIO_Pin_7);
					GPIO_ResetBits(GPIOB, GPIO_Pin_8);
					GPIO_ResetBits(GPIOB, GPIO_Pin_9);
			    delay_us(t/8);
			
					GPIO_SetBits(GPIOB, GPIO_Pin_6);
					GPIO_ResetBits(GPIOB, GPIO_Pin_7);
					GPIO_ResetBits(GPIOB, GPIO_Pin_8);
					GPIO_ResetBits(GPIOB, GPIO_Pin_9);
					delay_us(t/8);
		 }
	
}


void stepper_motor_ctrl(u8 direction, int angle, int T)
{
	int i;
	int round = angle / 360;
	int remain = angle % 360;
	
	int k = remain * 512 / 360;
	
	for(i=0;i<round;i++) // ����Ȧ��ת��
	{
		int j;
		for(j=0;j<512;j++)
		{
			OneRound8(direction,T);
		}
	}
	
	for(i=0;i<k;i++)     // תʣ�µĲ���һȦ��
	{
		 OneRound8(direction,T);
	}

}
