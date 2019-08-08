#include"exti.h"
#include"key.h"
#include"delay.h"
#include"led.h"
#include"beep.h"
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitSStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	KEY_Init();				/*��ʼ��IO*/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);			/*����io����ʱ��*/
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource0);  /*����Io���ж��߹�ϵ*/
	
	EXTI_InitSStruct.EXTI_Line=EXTI_Line0;								/*��ʼ��key0�����ж�*/
	EXTI_InitSStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitSStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitSStruct.EXTI_Trigger=EXTI_Trigger_Falling;		
	EXTI_Init(&EXTI_InitSStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource1);
	EXTI_InitSStruct.EXTI_Line=EXTI_Line1;								/*��ʼ��key1�����ж�*/	
	EXTI_Init(&EXTI_InitSStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);
	EXTI_InitSStruct.EXTI_Line=EXTI_Line2;								/*��ʼ��key2�����ж�*/
	EXTI_InitSStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitSStruct.EXTI_Trigger=EXTI_Trigger_Falling;		
	EXTI_Init(&EXTI_InitSStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
	EXTI_InitSStruct.EXTI_Line=EXTI_Line3;								/*��ʼ��key3�����ж�*/
	EXTI_InitSStruct.EXTI_Trigger=EXTI_Trigger_Falling;		
	EXTI_Init(&EXTI_InitSStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
	EXTI_InitSStruct.EXTI_Line=EXTI_Line4;								/*��ʼ��key4�����ж�*/
	EXTI_InitSStruct.EXTI_Trigger=EXTI_Trigger_Falling;		
	EXTI_Init(&EXTI_InitSStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;					/*ʹ��key0�ж�*/
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI1_IRQn;					/*ʹ��key1�ж�*/
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI2_IRQn;					/*ʹ��key2�ж�*/
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI3_IRQn;					/*ʹ��KEY3�ж�*/
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI4_IRQn;					/*ʹ��KEY4�ж�*/
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);
}

//void EXTI4_IRQHandler()						/*��дkey0�жϷ�����*/
//{
//	delay_ms(10);
//	if(KEY0==0)
//	{
//		LED0=~LED0;
//	}
//	EXTI_ClearITPendingBit(EXTI_Line4);   
//}
//void EXTI3_IRQHandler()						/*��дkey1�жϷ�����*/
//{
//	delay_ms(10);
//	if(KEY1==0)
//	{
//		LED1=~LED1;
//	}
//	EXTI_ClearITPendingBit(EXTI_Line3);   
//}
//void EXTI2_IRQHandler()						/*��дkey2�жϷ�����*/
//{
//	delay_ms(10);
//	if(KEY2==0)
//	{
//		BEEP=~BEEP;
//	}
//	EXTI_ClearITPendingBit(EXTI_Line2);   
//}
//void EXTI0_IRQHandler()						/*��дwk_up�жϷ�����*/
//{
//	delay_ms(10);
//	if(WK_UP==1)
//	{
//		LED1=~LED1;
//		LED0=~LED0;
//	}
//	EXTI_ClearITPendingBit(EXTI_Line0);   
//}
