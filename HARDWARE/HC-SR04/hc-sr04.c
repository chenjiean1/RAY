#include "hc-sr04.h"
#include "timer.h"
#include "delay.h"
#include "oled.h"

u8 gFlag=0;
u16 time=0;
void StartModule()
{
	gTrig=1;
	delay_us(11);
	gTrig=0;
}

static void MeasureDistance()
{

	unsigned long dCm=0;
	dCm=(time*1.7)/100;
	if((dCm>700)||(gTrig==1))
	{
		gFlag=0;
		OLED_ShowNum(0,2,000,3,16);
	}
	else
	{
		OLED_ShowNum(0,4,dCm,5,16);
	}
	time=0;
}

void HCSR04_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);	
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
 GPIO_Init(GPIOB, &GPIO_InitStructure);				
 GPIO_SetBits(GPIOC,GPIO_Pin_10);						

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	 
 GPIO_Init(GPIOC, &GPIO_InitStructure);	  	
 GPIO_SetBits(GPIOC,GPIO_Pin_5); 						 
}
void HCSR04Test()
{
	TIME3_Init(9,71);
	TIM_Cmd(TIM3,DISABLE);
	HCSR04_Init();
	while(1)
	{
		StartModule();
		while(!gEcho);
		TIM_Cmd(TIM4,ENABLE);	
		while(gEcho);
		TIM_Cmd(TIM3,DISABLE);
		MeasureDistance();
		delay_ms(10);
	}
}
void TIM3_IRQHandler()
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{	
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
		time++;
		if(time>65000)
		{
			gFlag=1;
		}
	}
}
