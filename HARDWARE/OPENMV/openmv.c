#include "openmv.h"
#include "stm32f10x.h"
#include "anjian.h"



int cx,cy,lm;
int AfterTurnFlag=0,i=0,lmSum=0,CountTOFlag=0,AfterFindFlag=0;
int autoFireFlag=0,autoMode=1;
const int QVGA_CX=320/2,QVGA_CY=240/2,lmCountTims=20;
int lmAvg=0;


void UsartInit()
	{
    USART_TypeDef * usart=USART1;
    //uint8_t usartIrq=USART1_IRQn;
    uint16_t gpioIn=GPIO_Pin_10;
    uint16_t gpioOut=GPIO_Pin_9;

    GPIO_InitTypeDef gpioInit;
    USART_InitTypeDef usartInit;
    //NVIC_InitTypeDef nvicInit;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//???
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    gpioInit.GPIO_Speed=GPIO_Speed_50MHz;
    gpioInit.GPIO_Mode=GPIO_Mode_AF_PP;
    gpioInit.GPIO_Pin=gpioOut;
    GPIO_Init(GPIOA,&gpioInit);
    gpioInit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    gpioInit.GPIO_Pin=gpioIn;
    GPIO_Init(GPIOA,&gpioInit);

    usartInit.USART_BaudRate=115200;
    usartInit.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    usartInit.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
    usartInit.USART_Parity=USART_Parity_No;
    usartInit.USART_StopBits=USART_StopBits_1;
    usartInit.USART_WordLength=USART_WordLength_8b;
    USART_Init(usart,&usartInit);
    
    // nvicInit.NVIC_IRQChannel=usartIrq;
    // nvicInit.NVIC_IRQChannelCmd=ENABLE;
    // nvicInit.NVIC_IRQChannelPreemptionPriority=1;
    // nvicInit.NVIC_IRQChannelSubPriority=2;
    // NVIC_Init(&nvicInit);
    // USART_ITConfig(usart,USART_IT_RXNE,ENABLE);//????????
    USART_Cmd(usart,ENABLE);
}
void UsartInit1()
	{
    USART_TypeDef * usart=USART1;
    uint8_t usartIrq=USART1_IRQn;
    uint16_t gpioIn=GPIO_Pin_10;
    uint16_t gpioOut=GPIO_Pin_9;

    GPIO_InitTypeDef gpioInit;
    USART_InitTypeDef usartInit;
    NVIC_InitTypeDef nvicInit;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    gpioInit.GPIO_Speed=GPIO_Speed_50MHz;
    gpioInit.GPIO_Mode=GPIO_Mode_AF_PP;
    gpioInit.GPIO_Pin=gpioOut;
    GPIO_Init(GPIOA,&gpioInit);
    gpioInit.GPIO_Mode=GPIO_Mode_IN_FLOATING;
    gpioInit.GPIO_Pin=gpioIn;
    GPIO_Init(GPIOA,&gpioInit);

    usartInit.USART_BaudRate=115200;
    usartInit.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    usartInit.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
    usartInit.USART_Parity=USART_Parity_No;
    usartInit.USART_StopBits=USART_StopBits_1;
    usartInit.USART_WordLength=USART_WordLength_8b;
    USART_Init(usart,&usartInit);
    
    nvicInit.NVIC_IRQChannel=usartIrq;
    nvicInit.NVIC_IRQChannelCmd=ENABLE;
    nvicInit.NVIC_IRQChannelPreemptionPriority=2;
    nvicInit.NVIC_IRQChannelSubPriority=2;
    NVIC_Init(&nvicInit);
    USART_ITConfig(usart,USART_IT_RXNE,ENABLE);//????????
    USART_Cmd(usart,ENABLE);
	}

 double deal_with(double angle)  //角度转PWM
 {
		double pwm;
	 pwm=(0.73)*angle+49;
	 return pwm;
 }
 
const double angleDealt=0.1;
const double startAngle=1;   //修改为  角度-30 ---  30
const double endAngle=90;
double MotorAngle=startAngle;

void turnLeft()                //如果angle>0&&<30
{
	MotorAngle+=angleDealt;
	if(MotorAngle>endAngle)MotorAngle=startAngle;
	TIM_SetCompare2(TIM3,deal_with(MotorAngle));   //规定这是控制摄像头左右转					//角度应有结构体？？？？
//	TIM_SetCompare3(TIM3,deal_with(MotorAngle));		//控制云台水平转
//	TIM_SetCompare4(TIM3,deal_with(MotorAngle));			//控制云台俯仰
}
void turnRight()                //如果angle>30&&<60
{
	MotorAngle-=angleDealt;
	if(MotorAngle<startAngle)MotorAngle=endAngle;	
	TIM_SetCompare2(TIM3,deal_with(MotorAngle));   //规定这是控制摄像头左右转	
//	TIM_SetCompare3(TIM3,deal_with(MotorAngle));		//控制云台水平转
//	TIM_SetCompare4(TIM3,deal_with(MotorAngle));			//控制云台俯仰
}

double CalcAngleWithDistance(double distance){
	double angle;
	
	return angle;
}

void Fire(double distance,double angle){
	TIM_SetCompare3(TIM3,deal_with(angle));//控制云台水平转
	TIM_SetCompare4(TIM3,deal_with(CalcAngleWithDistance(MotorAngle)));//控制云台俯仰
}

void autoFire1()
{
	   autoMode=0;
    autoFireFlag=1;
    AfterTurnFlag=0,i=0,lmSum=0,CountTOFlag=0;
    lmAvg=0;
    while(!AfterFindFlag);
    Fire(MotorAngle,lmAvg);
}
void autoFire2()
{
	    autoMode=0;
    autoFireFlag=1;
    AfterTurnFlag=0,i=0,lmSum=0,CountTOFlag=0;
    lmAvg=0;
    while(!AfterFindFlag);
    Fire(MotorAngle,lmAvg);
}
int length;
int getOLED(){
	return cx;
}

int readNum(){
	int num=0;
	int i=0;
	int nums[3];
	length=USART_ReceiveData(USART1)-'0';
	for(i=0;i<length;i++)
		nums[i]=USART_ReceiveData(USART1)-'0';
	for(i=0;i<length;i++){
		num+=nums[i];
		num=num*10;
	}
	num=num/10;
	return num;
}

void USART1_IRQHandler(){
    if(autoFireFlag){
        if(!autoMode){
            cx=readNum();
            cy=readNum();
            lm=readNum();
            if(!AfterTurnFlag){
                if(cx>QVGA_CX)turnRight();
                else if(cx<QVGA_CX)turnLeft();
                else AfterTurnFlag=1;
            }
            if(AfterTurnFlag&&!CountTOFlag){
                ++i;
                lmSum+=lm;
                if(i==lmCountTims)CountTOFlag=1;
            }
            if(CountTOFlag){
                lmAvg=lmSum/lmCountTims;
                AfterFindFlag=1;
                autoFireFlag=0;
            }
            // USART_SendData(USART1,cx);
            // USART_SendData(USART1,cy);
            // USART_SendData(USART1,lm);
        }else{
            //cx=readNum();
            //cy=readNum();
            //lm=readNum();
					cx=USART_ReceiveData(USART1);
					cy=USART_ReceiveData(USART1);
					lm=USART_ReceiveData(USART1);
					  USART_SendData(USART1,cx);
            USART_SendData(USART1,cy);
            USART_SendData(USART1,lm);
            if(!AfterTurnFlag){
                if(cx>QVGA_CX)turnRight();
                else if(cx<QVGA_CX)turnLeft();
                else AfterTurnFlag=1;
            }
            if(AfterTurnFlag){
                lmAvg=250;
                AfterFindFlag=1;
                autoFireFlag=0;
            }
        }
    }
}

double getMotorAngle(void){
	return MotorAngle;
}

