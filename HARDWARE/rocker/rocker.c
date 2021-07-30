#include "rocker.h"

// 初始化PA，占用PA1、PA2、PA3，需要PA1连接摇杆的VRx，PA2连接摇杆的VRy，PA3连接摇杆的sw，摇杆的5V输入处连接3v3电压
void rocker_init(void)
{
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;



	// 初始化PA1，用于ADC通道1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	// 初始化PA2，用于ADC通道2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	// 初始化PA3，用于摇杆按键
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//0 1 输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	// 初始化ADC1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
	ADC_DeInit(ADC1);  //复位ADC1 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	ADC_StartCalibration(ADC1);	 //开启AD校准
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
	
	// 初始化ADC2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2	, ENABLE );	  //使能ADC2通道时钟
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
	ADC_DeInit(ADC2);  //复位ADC2
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC2, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
	ADC_Cmd(ADC2, ENABLE);	//使能指定的ADC1
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	while(ADC_GetResetCalibrationStatus(ADC2));	//等待复位校准结束
	ADC_StartCalibration(ADC2);	 //开启AD校准
	while(ADC_GetCalibrationStatus(ADC2));	 //等待校准结束
}


// ch=1对应PA1，ch=2对应PA2
u16 get_adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}


// 获取摇杆x方向坐标，最左边为-2048，最右边为2047，中间是0
int16_t rocker_x(void)
{
	uint32_t temp_val=0;
	u8 t;
	for(t=0;t<ADC_MEAN_TIME;t++)
	{
		temp_val+=get_adc(1); // 获取PA1上的模拟信号
		delay_ms(5);
	}
	return temp_val/ADC_MEAN_TIME - 2048;
}


// 获取摇杆y方向坐标，最上边为-2048，最下边为2047，中间是0
int16_t rocker_y(void)
{
	uint32_t temp_val=0;
	u8 t;
	for(t=0;t<ADC_MEAN_TIME;t++)
	{
		temp_val+=get_adc(2); // 获取PA2上的模拟信号
		delay_ms(5);
	}
	return temp_val/ADC_MEAN_TIME - 2048;
}


// 获取摇杆按键状态，按下为1，松开为0
u8 rocker_sw(void)
{
	return !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3);
}
