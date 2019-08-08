#include "led.h"
#include "delay.h"
#include "key.h"
#include "usart.h"
#include "beep.h"
#include "exti.h"
#include "oled.h"
#include "timer.h"
#include "mpu6050.h"
#include "openmv.h"
#include "anjian.h"
//int main(void)
//{
//u8 t;
//u8 len; 
//u16 times=0;
//delay_init();  //??????? 
//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // ? ? NVIC ? ? ? ? 2
//uart_init(115200); //????????? 115200
//LED_Init();  //LED ?????
//KEY_Init(); //?????????????
//while(1)
//{
//if(USART_RX_STA&0x8000)
//{ len=USART_RX_STA&0x3f; //????????????
//printf("\r\n ???????:\r\n\r\n");
//for(t=0;t<len;t++)
//{ USART_SendData(USART1, USART_RX_BUF[t]); //??? 1 ????
//while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);
////??????
//}
//printf("\r\n\r\n"); //????
//USART_RX_STA=0;
//}else
//{ times++;
//if(times%5000==0)
//{ printf("\r\n ?? STM32 ??? ????\r\n");
//printf("????@ALIENTEK\r\n\r\n");
//}
//if(times%200==0)printf("?????,??????\n");
//if(times%30==0)LED0=!LED0; //?? LED,????????.
//delay_ms(10);
//}
//} 
//}
 
 void Oled_display(double MotorAngle)
 {
		OLED_ShowCHinese(0,0,8);
		OLED_ShowCHinese(16,0,9);    //剩余电量
		OLED_ShowCHinese(32,0,6);
		OLED_ShowCHinese(48,0,7);
	 
	  OLED_ShowCHinese(0,2,14);
		OLED_ShowCHinese(16,2,15);    //目标角度
		OLED_ShowCHinese(32,2,10);
		OLED_ShowCHinese(48,2,11);
		OLED_ShowNum(65,2,MotorAngle,3,16);
	 OLED_ShowNum(16,4,getDistnce(),3,16);
	 OLED_ShowNum(65,4,getAngle(),3,16);
	 
	 
 }
// u8 deal_with(u8 angle)  //角度转PWM
// {
//		u8 pwm;
//	 pwm=(0.73)*angle+49;
//	 return pwm;
// }
 int main(void)
 {
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 /*中断分组*/
	delay_init();	    	 //延时函数初始化
   UsartInit1();
	OLED_Init();
	OLED_Clear();
	TIM3_PWM_Init(1999,719);  //周期20ms
	while(1)
	{
//		TIM_SetCompare2(TIM3,100);
//		TIM_SetCompare4(TIM3,deal_with(90));    //增大是逆时针转    50-250之间   45度对应100/3
//		TIM_SetCompare3(TIM3,200);
		Oled_display(getMotorAngle());
	}
}
