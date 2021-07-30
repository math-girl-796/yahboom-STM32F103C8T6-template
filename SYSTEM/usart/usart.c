#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用ucos,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//ucos 使用	  
#endif


//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0){}//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 
/////////////////////////////////////////////////////////////////
 


/********************************************   uart 1   ***********************************************/
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART1_RX_BUF[USART1_REC_LEN];     //接收缓冲
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART1_RX_STA=0;       //接收状态标记	  
  
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
		USART_SendData(USART1, bytes[i]);         //向串口1发送数据
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
	}
}

void uart1_init(u32 bound){
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
#if EN_USART1_RX	
	NVIC_InitTypeDef NVIC_InitStructure;
#endif
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|UART1_GPIO_CLOCK, ENABLE);	
  
	//USART1_TX
	GPIO_InitStructure.GPIO_Pin = UART1_Pin_TX; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(UART1_GPIOx, &GPIO_InitStructure);
   
	//USART1_RX	 
	GPIO_InitStructure.GPIO_Pin = UART1_Pin_RX;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(UART1_GPIOx, &GPIO_InitStructure);

#if EN_USART1_RX
	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
#endif
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART1, &USART_InitStructure); //初始化串口1
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(USART1, ENABLE);                    //使能串口1 

}

void USART1_IRQHandler(void)                	//串口1中断服务程序
	{
	u8 Res;
#if SYSTEM_SUPPORT_OS 		//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
	OSIntEnter();    
#endif
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
		{
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
		
		if((USART1_RX_STA&0x8000)==0)//接收未完成
			{
			if(USART1_RX_STA&0x4000)//接收到了0x0d
				{
				if(Res!=0x0a)USART1_RX_STA=0;//接收错误,重新开始
				else USART1_RX_STA|=0x8000;	//接收完成了 
				}
			else //还没收到0X0D
				{	
				if(Res==0x0d)USART1_RX_STA|=0x4000;
				else
					{
					USART1_RX_BUF[USART1_RX_STA&0X3FFF]=Res ;
					USART1_RX_STA++;
					if(USART1_RX_STA>(USART1_REC_LEN-1))USART1_RX_STA=0;//接收数据错误,重新开始接收	  
					}		 
				}
			}   		 
     } 
#if SYSTEM_SUPPORT_OS 	//如果SYSTEM_SUPPORT_OS为真，则需要支持OS.
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
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
	//USART3_TX
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOB, &GPIO_InitStructure);
   
	//USART3_RX	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	//Usart3 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

	USART_Init(USART3, &USART_InitStructure); //初始化串口
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//开启串口接受中断
	USART_Cmd(USART3, ENABLE);                    //使能串口

}


void uart3_send_bytes(const u8* bytes, int len)
{
	int i = 0;
	for(i = 0; i < len; i++)
	{
		USART_SendData(USART3, bytes[i]);         //向串口3发送数据
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
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

	if (USART_GetFlagStatus(USART3, USART_FLAG_ORE) != RESET)//注意！不能使用if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)来判断  
    {  
		USART_ClearFlag(USART3, USART_FLAG_ORE); //读SR其实就是清除标志
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












