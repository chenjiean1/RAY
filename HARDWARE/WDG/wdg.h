#ifndef __WDG_H
#define __WDG_H
#include "sys.h"

void IWDG_Init(u8 prer,u16 rlr);
void IWDG_Feed(void);

void WWDG_Init(u8 tr,u8 wr,u32 fprer);//��ʼ��WWDG
void WWDG_Set_Counter(u8 cnt);       //����WWDG�ļ�����

#endif