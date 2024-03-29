#include "gpio.h"
/**
	****************************************************************************
	* @Warning 本程序未经作者许可，不得用于其它任何用途 
	* @File    gpio.c
	* @Author  xiaowine@cee0.com
	* @date    修改日期:
	* @version V1.0
	*************************************************
	* @brief   配置IO输入
	****************************************************************************
	* @attention 
	* Powered By Xiaowine
	* <h2><center>&copy;  Copyright(C) 小酒论坛 2015-2019</center></h2>
	* All rights reserved
	* 
**/


/**
************************************************************************************************************************
 * @Function 	:		void GPIO_init(void) 
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	配置IO输入
 * @param 		: 	
 * @Return  	:		None
 * @说	明  	:		
************************************************************************************************************************
*/
void GPIO_init(void) 
{
	GPIO_InitTypeDef  GPIO_InitStructure;
// 	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//禁用JTAG功能 使用PB3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|
												 RCC_APB2Periph_GPIOB|
												 RCC_APB2Periph_GPIOC, ENABLE);	 //使能PA,PB,PC,PD端口时钟
	/*****************PA0~7*******************************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
																GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC
	/*****************PB1~1*******************************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC
	/****************PC4~5********************************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC
	/**********************************************************/
}
/**
************************************************************************************************************************
 * @Function 	:		u16 IO_States(void)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	监测通道状态
 * @param 		: 	u16 *temp 各通道状态 位表示 d0位表示通道0
 * @Return  	:		None
 * @说	明  	:		
************************************************************************************************************************
*/
u16 IO_States(uFLAG *temp1)
{
	u16 temp;
	temp = GPIO_ReadInputData(GPIOA)&0xff;
	temp |= (GPIO_ReadInputData(GPIOC)&0x30)<<4;
	temp |= (GPIO_ReadInputData(GPIOB)&0x03)<<10;
	if(temp == 0)
		temp1->Bits.bit2 = 0;
	else temp1->Bits.bit2 = 1;
	return temp;
}
/**
************************************************************************************************************************
 * @Function 	:		void CRT_IO(void)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	
 * @param 		: 	
 * @Return  	:		None
 * @?�?�			:		
************************************************************************************************************************
*/
void CRT_IO(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
// 	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//禁用JTAG功能 使用PB3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PA,PB,PC,PD端口时钟
	/*****************PC15*******************************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 // 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //浮空输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC
	GPIO_SetBits(GPIOC,GPIO_Pin_15);						 //PB输出高
//	GPIO_ResetBits(GPIOC,GPIO_Pin_15);
}











