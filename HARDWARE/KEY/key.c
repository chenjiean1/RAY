#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"

//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_4;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

//	//��ʼ�� WK_UP-->GPIOA.0	  ��������
//	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0

}

u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(KEY3==0)return KEY3_PRES;
		else if(KEY4==0)return KEY4_PRES;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)key_up=1; 	    
 	return 0;// �ް�������
}
