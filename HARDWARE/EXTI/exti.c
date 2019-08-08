#include"exti.h"
#include"key.h"
#include"delay.h"
#include"led.h"
#include"beep.h"
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitSStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	KEY_Init();				/*初始化IO*/
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);			/*开启io复用时钟*/
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource0);  /*设置Io与中断线关系*/
	
	EXTI_InitSStruct.EXTI_Line=EXTI_Line0;								/*初始化key0线上中断*/
	EXTI_InitSStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitSStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitSStruct.EXTI_Trigger=EXTI_Trigger_Falling;		
	EXTI_Init(&EXTI_InitSStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource1);
	EXTI_InitSStruct.EXTI_Line=EXTI_Line1;								/*初始化key1线上中断*/	
	EXTI_Init(&EXTI_InitSStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource2);
	EXTI_InitSStruct.EXTI_Line=EXTI_Line2;								/*初始化key2线上中断*/
	EXTI_InitSStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitSStruct.EXTI_Trigger=EXTI_Trigger_Falling;		
	EXTI_Init(&EXTI_InitSStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
	EXTI_InitSStruct.EXTI_Line=EXTI_Line3;								/*初始化key3线上中断*/
	EXTI_InitSStruct.EXTI_Trigger=EXTI_Trigger_Falling;		
	EXTI_Init(&EXTI_InitSStruct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
	EXTI_InitSStruct.EXTI_Line=EXTI_Line4;								/*初始化key4线上中断*/
	EXTI_InitSStruct.EXTI_Trigger=EXTI_Trigger_Falling;		
	EXTI_Init(&EXTI_InitSStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;					/*使能key0中断*/
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI1_IRQn;					/*使能key1中断*/
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI2_IRQn;					/*使能key2中断*/
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI3_IRQn;					/*使能KEY3中断*/
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=EXTI4_IRQn;					/*使能KEY4中断*/
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);
}

//void EXTI4_IRQHandler()						/*编写key0中断服务函数*/
//{
//	delay_ms(10);
//	if(KEY0==0)
//	{
//		LED0=~LED0;
//	}
//	EXTI_ClearITPendingBit(EXTI_Line4);   
//}
//void EXTI3_IRQHandler()						/*编写key1中断服务函数*/
//{
//	delay_ms(10);
//	if(KEY1==0)
//	{
//		LED1=~LED1;
//	}
//	EXTI_ClearITPendingBit(EXTI_Line3);   
//}
//void EXTI2_IRQHandler()						/*编写key2中断服务函数*/
//{
//	delay_ms(10);
//	if(KEY2==0)
//	{
//		BEEP=~BEEP;
//	}
//	EXTI_ClearITPendingBit(EXTI_Line2);   
//}
//void EXTI0_IRQHandler()						/*编写wk_up中断服务函数*/
//{
//	delay_ms(10);
//	if(WK_UP==1)
//	{
//		LED1=~LED1;
//		LED0=~LED0;
//	}
//	EXTI_ClearITPendingBit(EXTI_Line0);   
//}
