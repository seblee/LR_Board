#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
#include "config.h"
/**
	****************************************************************************
	* @Warning ������δ��������ɣ��������������κ���; 
	* @File    usart.h
	* @Author  xiaowine@cee0.com
	* @date    �޸�����:
	* @version V2.0
	*************************************************
	* @brief   -->>usart.c
	*				   V1.3�޸�˵�� 
	*					 ֧����Ӧ��ͬƵ���µĴ��ڲ���������.
	*					 �����˶�printf��֧��
	*					 �����˴��ڽ��������.
	*					 ������printf��һ���ַ���ʧ��bug
	*					 V1.4�޸�˵��
	*					 1,�޸Ĵ��ڳ�ʼ��IO��bug
	*					 2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
	*					 3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
	*					 4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
	****************************************************************************
	* @attention 
	* Powered By Xiaowine
	* <h2><center>&copy;  Copyright(C) С����̳ 2015-2019</center></h2>
	* All rights reserved
	* 
**/

////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define USART_TRA_LEN				3
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
#define EN_USART2_RX 			1		//ʹ�ܣ�1��/��ֹ��0������2����
#define EN_USART3_RX 			1		//ʹ�ܣ�1��/��ֹ��0������3����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u8  USART_TX_BUF[USART_TRA_LEN];
extern u16 USART_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart1_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);

void USARTx_Send_buff(USART_TypeDef* USARTx,u32 len,u8 *buf);
void FM0DataToUART(uUINT16ARR add,u8 cmd,u8 temp,u8 *p_uartsendbuf);
/**
************************************************************************************************************************
 * @Function 	:		void Prece_REC(u8 temp)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	���մ�����
 * @param 		: 	u8 temp ���յ����ֽ�
 * @Return  	:		None
 * @˵	��  	:		
************************************************************************************************************************
*/
void Prece_REC(u8 temp);
extern void (*Proce_U1)(u8);
#endif


