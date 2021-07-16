#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
#include <string.h>
#include "delay.h"


/*************************************************************** uart1:TX-PA9，RX-PA10 ************************************************************************/

/* 说明：从机可向本机不停地发送数据，每发送一个字节，本机会中断一次，并将这个字节积累到缓存中，直到本机接收到连续的 0D 0A 为止 */
/* 若本机收到了 0D 0A，缓冲区会停止对外界数据的接收(但仍会中断，中断后不对新接收到的数据进行处理，直接丢弃)，直到使用uart1_read_buf或uart1_clear_buf清空缓冲区为止 */
/* 本机若想实时获得从机数据，需要不断地用uart1_buf_status查看是否有新数据传来，一旦传来，需尽快读走。 */

/* 改进策略：当本机接收到0D 0A时，触发另一个自定义中断，该中断更新一个全局变量，维护最新传来的数据 */
#define USART1_REC_LEN  		200  	//定义最大接收字节数。如果一次收到的数据总量超过此数，缓冲区将被清空
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

#define UART1_GPIOx			GPIOA
#define UART1_Pin_TX		GPIO_Pin_9
#define UART1_Pin_RX		GPIO_Pin_10
#define UART1_GPIO_CLOCK	RCC_APB2Periph_GPIOA

void uart1_init(u32 bound);							// 初始化串口
void uart1_send_bytes(const u8* bytes, int len);	// bytes: 字节数字；len：字节数组长度
int uart1_buf_status(void);							// 检查接收缓冲区中是否有数据，如果有，返回数据长度，如果没有，返回0
void uart1_read_buf(u8* buf, int len);				// 将串口接收寄存器内的内容前len个字节读入到buf中，然后清空串口接收缓冲区
void uart1_clear_buf(void);							// 清空串口接收缓冲区

/*************************************************************************************************************************************************************/


#endif


