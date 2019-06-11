#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
#include "config.h"
/**
	****************************************************************************
	* @Warning 本程序未经作者许可，不得用于其它任何用途 
	* @File    usart.h
	* @Author  xiaowine@cee0.com
	* @date    修改日期:
	* @version V2.0
	*************************************************
	* @brief   -->>usart.c
	*				   V1.3修改说明 
	*					 支持适应不同频率下的串口波特率设置.
	*					 加入了对printf的支持
	*					 增加了串口接收命令功能.
	*					 修正了printf第一个字符丢失的bug
	*					 V1.4修改说明
	*					 1,修改串口初始化IO的bug
	*					 2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
	*					 3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
	*					 4,修改了EN_USART1_RX的使能方式
	****************************************************************************
	* @attention 
	* Powered By Xiaowine
	* <h2><center>&copy;  Copyright(C) 小酒论坛 2015-2019</center></h2>
	* All rights reserved
	* 
**/

////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define USART_TRA_LEN				3
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
#define EN_USART2_RX 			1		//使能（1）/禁止（0）串口2接收
#define EN_USART3_RX 			1		//使能（1）/禁止（0）串口3接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u8  USART_TX_BUF[USART_TRA_LEN];
extern u16 USART_RX_STA;         		//接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义
void uart1_init(u32 bound);
void uart2_init(u32 bound);
void uart3_init(u32 bound);

void USARTx_Send_buff(USART_TypeDef* USARTx,u32 len,u8 *buf);
void FM0DataToUART(uUINT16ARR add,u8 cmd,u8 temp,u8 *p_uartsendbuf);
/**
************************************************************************************************************************
 * @Function 	:		void Prece_REC(u8 temp)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	接收处理函数
 * @param 		: 	u8 temp 接收到的字节
 * @Return  	:		None
 * @说	明  	:		
************************************************************************************************************************
*/
void Prece_REC(u8 temp);
extern void (*Proce_U1)(u8);
#endif


