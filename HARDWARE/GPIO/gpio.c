#include "gpio.h"
/**
	****************************************************************************
	* @Warning ±æ≥Ã–ÚŒ¥æ≠◊˜’ﬂ–Ìø…£¨≤ªµ√”√”⁄∆‰À¸»Œ∫Œ”√Õæ 
	* @File    gpio.c
	* @Author  xiaowine@cee0.com
	* @date    –ﬁ∏ƒ»’∆⁄:
	* @version V1.0
	*************************************************
	* @brief   ≈‰÷√IO ‰»Î
	****************************************************************************
	* @attention 
	* Powered By Xiaowine
	* <h2><center>&copy;  Copyright(C) –°æ∆¬€Ã≥ 2015-2019</center></h2>
	* All rights reserved
	* 
**/


/**
************************************************************************************************************************
 * @Function 	:		void GPIO_init(void) 
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	≈‰÷√IO ‰»Î
 * @param 		: 	
 * @Return  	:		None
 * @Àµ	√˜  	:		
************************************************************************************************************************
*/
void GPIO_init(void) 
{
	GPIO_InitTypeDef  GPIO_InitStructure;
// 	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//Ω˚”√JTAGπ¶ƒ‹  π”√PB3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|
												 RCC_APB2Periph_GPIOB|
												 RCC_APB2Periph_GPIOC, ENABLE);	 // πƒ‹PA,PB,PC,PD∂Àø⁄ ±÷”
	/*****************PA0~7*******************************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
																GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				 // ∂Àø⁄≈‰÷√
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //∏°ø’ ‰»Î
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IOø⁄ÀŸ∂»Œ™50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //∏˘æ›…Ë∂®≤Œ ˝≥ı ºªØGPIOC
	/*****************PB1~1*******************************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;				 // ∂Àø⁄≈‰÷√
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //∏°ø’ ‰»Î
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IOø⁄ÀŸ∂»Œ™50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //∏˘æ›…Ë∂®≤Œ ˝≥ı ºªØGPIOC
	/****************PC4~5********************************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;				 // ∂Àø⁄≈‰÷√
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //∏°ø’ ‰»Î
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IOø⁄ÀŸ∂»Œ™50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //∏˘æ›…Ë∂®≤Œ ˝≥ı ºªØGPIOC
	/**********************************************************/
}
/**
************************************************************************************************************************
 * @Function 	:		u16 IO_States(void)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	º‡≤‚Õ®µ¿◊¥Ã¨
 * @param 		: 	u16 *temp ∏˜Õ®µ¿◊¥Ã¨ Œª±Ì æ d0Œª±Ì æÕ®µ¿0
 * @Return  	:		None
 * @Àµ	√˜  	:		
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
 * @?µ?˜			:		
************************************************************************************************************************
*/
void CRT_IO(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
// 	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//Ω˚”√JTAGπ¶ƒ‹  π”√PB3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 // πƒ‹PA,PB,PC,PD∂Àø⁄ ±÷”
	/*****************PC15*******************************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 // ∂Àø⁄≈‰÷√
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //∏°ø’ ‰»Î
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IOø⁄ÀŸ∂»Œ™50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //∏˘æ›…Ë∂®≤Œ ˝≥ı ºªØGPIOC
	GPIO_SetBits(GPIOC,GPIO_Pin_15);						 //PB ‰≥ˆ∏ﬂ
//	GPIO_ResetBits(GPIOC,GPIO_Pin_15);
}











