#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��ucos,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos ʹ��	  
#endif


//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0){}//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 
/////////////////////////////////////////////////////////////////
 


/********************************************   uart 1   ***********************************************/
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART1_RX_BUF[USART1_REC_LEN];     //���ջ���
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART1_RX_STA=0;       //����״̬���	  
  
int uart1_buf_status(void)
{
	if (USART1_RX_STA & 0x8000) return USART1_RX_STA & 0x3fff;
	else return 0;
}

void uart1_read_buf(u8* buf, int len)
{
	int i = 0;
	for (i = 0; i< len; i++)
	{
		buf[i] = USART1_RX_BUF[i];
	}
	USART1_RX_STA=0;
}

void uart1_clear_buf(void)
{
	USART1_RX_STA=0;
}

void uart1_send_bytes(const u8* bytes, int len)
{
	int i = 0;
	for(i = 0; i < len; i++)
	{
		USART_SendData(USART1, bytes[i]);         //�򴮿�1��������
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
	}
}

void uart1_init(u32 bound){
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
#if EN_USART1_RX	
	NVIC_InitTypeDef NVIC_InitStructure;
#endif
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|UART1_GPIO_CLOCK, ENABLE);	
  
	//USART1_TX
	GPIO_InitStructure.GPIO_Pin = UART1_Pin_TX; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(UART1_GPIOx, &GPIO_InitStructure);
   
	//USART1_RX	 
	GPIO_InitStructure.GPIO_Pin = UART1_Pin_RX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(UART1_GPIOx, &GPIO_InitStructure);

#if EN_USART1_RX
	//Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
#endif
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART1, &USART_InitStructure); //��ʼ������1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}

void USART1_IRQHandler(void)                	//����1�жϷ������
	{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
		{
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		
		if((USART1_RX_STA&0x8000)==0)//����δ���
			{
			if(USART1_RX_STA&0x4000)//���յ���0x0d
				{
				if(Res!=0x0a)USART1_RX_STA=0;//���մ���,���¿�ʼ
				else USART1_RX_STA|=0x8000;	//��������� 
				}
			else //��û�յ�0X0D
				{	
				if(Res==0x0d)USART1_RX_STA|=0x4000;
				else
					{
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;
					USART1_RX_STA++;
					if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
					}		 
				}
			}   		 
     } 
#if SYSTEM_SUPPORT_OS 	//���SYSTEM_SUPPORT_OSΪ�棬����Ҫ֧��OS.
	OSIntExit();  											 
#endif
} 
#endif	

void uart1_send_string(char* str)
{
	int len = strlen(str);
	int i = 0;
	for (i = 0; i < len; i++) {
		USART_SendData(USART1, (uint16_t)str[i]);
		delay_us(100);	
	}
}




/*******************************************   uart3   **********************************************/
void uart3_init(u32 bound){
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
	//USART3_TX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOB, &GPIO_InitStructure);
   
	//USART3_RX	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//Usart3 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART3, &USART_InitStructure); //��ʼ������
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_Cmd(USART3, ENABLE);                    //ʹ�ܴ���

}


void uart3_send_bytes(const u8* bytes, int len)
{
	int i = 0;
	for(i = 0; i < len; i++)
	{
		USART_SendData(USART3, bytes[i]);         //�򴮿�3��������
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
	}
}



u8 uart3StartBit = 0;
int uart3PackNum = 0;

u8 USART3_RX_BUF[USART3_REC_LEN]; 
u16 USART3_RX_STA = 0;
u8 uart3NewLineReceived = 0;

void USART3_IRQHandler(void)
{
	u8 uartvalue = 0;

	if (USART_GetFlagStatus(USART3, USART_FLAG_ORE) != RESET)//ע�⣡����ʹ��if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)���ж�  
    {  
		USART_ClearFlag(USART3, USART_FLAG_ORE); //��SR��ʵ���������־
       	USART_ReceiveData(USART3);  		
    }
		
	if(USART_GetFlagStatus(USART3, USART_FLAG_RXNE)!=RESET)
	{
    	USART_ClearITPendingBit(USART3, USART_IT_RXNE);

		uartvalue = USART3->DR;
	    if(uartvalue == '$')
	    {
	      	uart3StartBit = 1;
		    USART3_RX_STA = 0;
	    }
	    if(uart3StartBit == 1)
	    {
	       	USART3_RX_BUF[USART3_RX_STA] = uartvalue;     
	    }  
	    if (uart3StartBit == 1 && uartvalue == '#') 
	    {
	    	
			uart3NewLineReceived = 1; 
			uart3StartBit = 0;
			uart3PackNum = USART3_RX_STA;	
		
	    }
		USART3_RX_STA++;
		if(USART3_RX_STA >= USART3_REC_LEN)
		{
			USART3_RX_STA = 0;
			uart3StartBit = 0;
			uart3NewLineReceived	= 0;
		}	 
	
	}

}












