#include "rocker.h"

// ��ʼ��PA��ռ��PA1��PA2��PA3����ҪPA1����ҡ�˵�VRx��PA2����ҡ�˵�VRy��PA3����ҡ�˵�sw��ҡ�˵�5V���봦����3v3��ѹ
void rocker_init(void)
{
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;



	// ��ʼ��PA1������ADCͨ��1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	// ��ʼ��PA2������ADCͨ��2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	// ��ʼ��PA3������ҡ�˰���
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//0 1 ����
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	// ��ʼ��ADC1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
	ADC_DeInit(ADC1);  //��λADC1 
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	ADC_StartCalibration(ADC1);	 //����ADУ׼
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
	
	// ��ʼ��ADC2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2	, ENABLE );	  //ʹ��ADC2ͨ��ʱ��
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
	ADC_DeInit(ADC2);  //��λADC2
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC2, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
	ADC_Cmd(ADC2, ENABLE);	//ʹ��ָ����ADC1
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	while(ADC_GetResetCalibrationStatus(ADC2));	//�ȴ���λУ׼����
	ADC_StartCalibration(ADC2);	 //����ADУ׼
	while(ADC_GetCalibrationStatus(ADC2));	 //�ȴ�У׼����
}


// ch=1��ӦPA1��ch=2��ӦPA2
u16 get_adc(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}


// ��ȡҡ��x�������꣬�����Ϊ-2048�����ұ�Ϊ2047���м���0
int16_t rocker_x(void)
{
	uint32_t temp_val=0;
	u8 t;
	for(t=0;t<ADC_MEAN_TIME;t++)
	{
		temp_val+=get_adc(1); // ��ȡPA1�ϵ�ģ���ź�
		delay_ms(5);
	}
	return temp_val/ADC_MEAN_TIME - 2048;
}


// ��ȡҡ��y�������꣬���ϱ�Ϊ-2048�����±�Ϊ2047���м���0
int16_t rocker_y(void)
{
	uint32_t temp_val=0;
	u8 t;
	for(t=0;t<ADC_MEAN_TIME;t++)
	{
		temp_val+=get_adc(2); // ��ȡPA2�ϵ�ģ���ź�
		delay_ms(5);
	}
	return temp_val/ADC_MEAN_TIME - 2048;
}


// ��ȡҡ�˰���״̬������Ϊ1���ɿ�Ϊ0
u8 rocker_sw(void)
{
	return !GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3);
}
