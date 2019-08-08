#include"sys.h"
#include"adc.h"
#include"delay.h"
void Adc_Init(void)	
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	ADC_InitTypeDef   ADC_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		/*����PA1ʱ��,��ʼ��PA1*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AIN; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);				
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);		/*����ADC1��Ƶ����*/
	ADC_DeInit(ADC1);										/*��λADC1*/
	
	ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;						/*��ʼ��ADC1*/
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStruct.ADC_NbrOfChannel=1;          
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;
	ADC_Init(ADC1,&ADC_InitStruct);
	
	ADC_Cmd(ADC1,ENABLE);										/*ʹ��ADC1*/
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
}

u16  Get_Adc(u8 ch)
{
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_239Cycles5);			/*���ù���ͨ������*/
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);		/*�������ת��*/
	
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	
	return ADC_GetConversionValue(ADC1);				/*��ȡADC1ֵ*/
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
}
