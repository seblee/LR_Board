#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"
#include "delay.h"
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 

#define N 50 //ȡ50��ƽ��ֵ
#define M 12 //12·AD
extern u16 value[N][M];
extern u16 aftervalue[M];
extern float avalue[M];

void Adc_Init(void);
u16  Get_Adc(u8 ch); 
u16 Get_Adc_Average(u8 ch,u8 times); 
void filter(void);

#endif 





