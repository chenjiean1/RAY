#ifndef _OLED_H
#define _OLED_H
#include "sys.h"



#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	


#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//IO��������
 
#define OLED_SDA_IN()  {GPIOC->CRH&=0XFFF0FFFF;GPIOC->CRH|=(u32)8<<16;}
#define OLED_SDA_OUT() {GPIOC->CRH&=0XFFF0FFFF;GPIOC->CRH|=(u32)3<<16;}

//IO��������	 
#define OLED_IIC_SCL    PCout(10) //SCL
#define OLED_IIC_SDA    PCout(12) //SDA	 
#define OLED_READ_SDA   PCin(12)  //����SDA 

//IIC���в�������
void OLED_IIC_Init(void);                //��ʼ��IIC��IO��				 
void OLED_IIC_Start(void);				//����IIC��ʼ�ź�
void OLED_IIC_Stop(void);	  			//����IICֹͣ�ź�
void OLED_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 OLED_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 OLED_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void OLED_IIC_Ack(void);					//IIC����ACK�ź�
void OLED_IIC_NAck(void);				//IIC������ACK�ź�

void OLED_IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 OLED_IIC_Read_One_Byte(u8 daddr,u8 addr);	

void OLED_Init(void);
void OLED_WR_Byte(unsigned dat,unsigned cmd); 
void Write_OLED_Command(unsigned char IIC_Command);
void Write_OLED_Data(unsigned char IIC_Data);
void fill_picture(unsigned char fill_Data);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Clear(void);
void OLED_On(void);
u32 oled_pow(u8 m,u8 n);
void OLED_Refresh_Gram(void);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2);
void OLED_ShowString(u8 x,u8 y,u8 chr[],u8 Char_Size);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);

#endif
