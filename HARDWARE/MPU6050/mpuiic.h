#ifndef __MPUIIC_H
#define __MPUIIC_H
#include "sys.h"
	   		   
//IO�������ã� �Ĺܽŵ�ʱ��Ҫ����SDA�õĽ��޸�GPIOx��CRx��(x * 4)
#define MPU_SDA_IN()  {GPIOA->CRL&=~(0xF << (5 * 4));GPIOA->CRL|=8<<(5 * 4);}
#define MPU_SDA_OUT() {GPIOA->CRL&=~(0xF << (5 * 4));GPIOA->CRL|=3<<(5 * 4);}

//IO��������	 
#define MPU_IIC_SCL    PAout(4) 		//SCL
#define MPU_IIC_SDA    PAout(5) 		//SDA	 
#define MPU_READ_SDA   PAin(5) 		//����SDA 

//IIC���в�������
void MPU_IIC_Delay(void);				//MPU IIC��ʱ����
void MPU_IIC_Init(void);                //��ʼ��IIC��IO��				 
void MPU_IIC_Start(void);				//����IIC��ʼ�ź�
void MPU_IIC_Stop(void);	  			//����IICֹͣ�ź�
void MPU_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 MPU_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 MPU_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void MPU_IIC_Ack(void);					//IIC����ACK�ź�
void MPU_IIC_NAck(void);				//IIC������ACK�ź�

void IMPU_IC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 MPU_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















