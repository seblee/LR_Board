#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "config.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//ͨ�ö�ʱ�� ��������			   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/12/03
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

extern u16 Timct10ms;
extern SYSclkint SYS_CLK;
extern SYSFlagint 	SYS_Flag;





















void Timerx_Init(u16 arr,u16 psc);
#endif























