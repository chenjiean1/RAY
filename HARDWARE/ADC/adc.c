#include"sys.h"
#include"adc.h"
#include"delay.h"
void Adc_Init(void)	
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	ADC_InitTypeDef   ADC_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);		/*开启PA1时钟,初始化PA1*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;				
	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AIN; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);				
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);		/*设置ADC1分频因子*/
	ADC_DeInit(ADC1);										/*复位ADC1*/
	
	ADC_InitStruct.ADC_ContinuousConvMode=DISABLE;						/*初始化ADC1*/
	ADC_InitStruct.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStruct.ADC_NbrOfChannel=1;          
	ADC_InitStruct.ADC_ScanConvMode=DISABLE;
	ADC_Init(ADC1,&ADC_InitStruct);
	
	ADC_Cmd(ADC1,ENABLE);										/*使能ADC1*/
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
}

u16  Get_Adc(u8 ch)
{
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_239Cycles5);			/*配置规则通道参数*/
	
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);		/*开启软件转换*/
	
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	
	return ADC_GetConversionValue(ADC1);				/*读取ADC1值*/
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
