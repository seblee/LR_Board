#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "wdg.h"
#include "dma.h"
#include "flash.h"
#include "board.h"
#include "adc.h"
#include "gpio.h"

/**
	****************************************************************************
	* @Warning 本程序未经作者许可，不得用于其它任何用途 
	* @File    main.c
	* @Author  xiaowine@cee0.com
	* @date    修改日期:
	* @version V1.1
	*************************************************
	* @brief   V1.1 输出采集改为AD采集
	****************************************************************************
	* @attention 
	* Powered By Xiaowine
	* <h2><center>&copy;  Copyright(C) 小酒论坛 2015-2019</center></h2>
	* All rights reserved
	* 
**/
const u8 TEXT_TO_SEND[] = {"DMA TEST小酒"};
#define TEXT_LENTH sizeof(USART_TX_BUF) //TEXT_TO_SEND字符串长度(不包含结束符)
uchar USART1_DAM_DONE = 1;

/*************	本地变量声明	**************/
uUINT16ARR address;
uchar address1 = 0x18;
uchar address2 = 0x1b;
/**
************************************************************************************************************************
 * @Function 	:		int main(void)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	
 * @param 		: 	
 * @Return  	:		None
 * @说	明  	:		
************************************************************************************************************************
*/
int main(void)
{
	delay_init();		  //延时函数初始化
	NVIC_Configuration(); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级

	//	uart2_init(19200);	 //串口初始化为19200
	/************串口1*****************************/
	uart1_init(9600); //串口初始化为9600

	// 	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)SendBuff,(TEXT_LENTH+3)*2);//DMA1通道4,外设为串口1,存储器为SendBuff,长(TEXT_LENTH+2)*100.
	// 	MYDMA_Config(DMA1_Channel4,(u32)&USART1->DR,(u32)USART_TX_BUF,TEXT_LENTH);//DMA1通道4,外设为串口1,存储器为SendBuff,长(TEXT_LENTH+2)*100.
	/********led******************/
	LED_Init();
	/*******继电器输出控制*******************/
	CRT_IO();
	/**************************************/
	Timerx_Init(99, 7199); //10Khz的计数频率，计数到100为10ms
	IWDG_Init(4, 1250);	//与分频数为64,重载值为1250,溢出时间为2s

	/******************************************/
	address.Byte[0] = address1;
	address.Byte[1] = address2;
	Board_init();
	SYS_CLK.SENDCLK = 200; //发送频率 ×10ms一次
	/**********************************************/
	while (1)
	{
		filter(); //得出AD平均值
		IWDG_Feed();
		if (SYS_Flag.SEND_flag == 1)
		{
			SYS_Flag.SEND_flag = 0;
		}
		//		if(SYS_Flag.SEND_flag == 1)
		//		{
		//			USART_DMACmd(USART1,USART_DMAReq_Tx,ENABLE); //使能串口1的DMA发送
		//			MYDMA_Enable(DMA1_Channel4);//开始一次DMA传输！
		//			USART1_DAM_DONE = 0;
		//			SYS_Flag.SEND_flag = 0;
		//		}
		//		if(DMA_GetFlagStatus(DMA1_FLAG_TC4)!=RESET)	//判断通道4传输完成
		//		{
		//			DMA_ClearFlag(DMA1_FLAG_TC4);//清除通道4传输完成标志
		//			USART1_DAM_DONE = 1;
		//		}
	}
}
