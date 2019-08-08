#include "anjian.h"
#include "delay.h"
#include "key.h"
int StartInputFlag=0,EndInputDistanceFlag=0,EndInputAngleFlag=0;
int mode=0;//0为发挥
int distance=0,angle=0;
int distanceI=0,angleI=0;



void autoFire1();

void autoFire2();


void EXTI0_IRQHandler(){//???
    delay_ms(10);
    if(KEY0==0){
        if(!StartInputFlag)
            StartInputFlag=1;
        else {
            if(!EndInputDistanceFlag){
                distance+=distanceI;
                distance*=10;
            }
            else {
                if(!EndInputAngleFlag)
                {
                    angle+=angleI;
                    angle*=10;
                }
            }
        }
        
    }
    EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(){//取消
    delay_ms(10);
    if(KEY1==0){
        if(StartInputFlag){
            if(!EndInputDistanceFlag)
                if(!distance)
                    distance/=10;                                //是下拉为0  看程序要不要改
                else {
                    distanceI=0;
                }																						//else看有没错
            else if(!EndInputAngleFlag){
                if(!angle)                                 //??????????????????????
                    angle/=10;
                else {
                    angleI=0;
                    EndInputDistanceFlag=0;
                }
						}
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line1);
}

void EXTI2_IRQHandler(){//增量
    delay_ms(10);
    if(KEY2==0){
        if(StartInputFlag){
            if(!EndInputDistanceFlag)
                if(distanceI==9)distanceI=0;
                else distanceI+=1;
            else if(!EndInputAngleFlag){
                if(angleI==9)angleI=0;
                else angleI+=1;
						}
        }
    }
    EXTI_ClearITPendingBit(EXTI_Line2);
}

void EXTI3_IRQHandler(){//总确认
    delay_ms(10);
    if(KEY3==0){
        if(StartInputFlag){
            if(!EndInputDistanceFlag){
                EndInputDistanceFlag=1;
                distanceI=0;
            }
            else if(!EndInputAngleFlag){
                EndInputAngleFlag=1;
                angleI=0;
            }
            else Fire(distance,angle);
        }else if(!mode){
            autoFire1();
        }else if(mode){
            autoFire2();
        }

    }
    EXTI_ClearITPendingBit(EXTI_Line3);
}
void EXTI4_IRQHandler(){//模式选择
    delay_ms(10);
    if(KEY4==0){
        mode=!mode;
    }
		EXTI_ClearITPendingBit(EXTI_Line4);
}
double getDistnce(){return distance;}
double getAngle(){return angle;}
