#ifndef __LED_H
#define __LED_H	 
#include "sys.h"
#include "config.h"
/**
	****************************************************************************
	* @Warning 本程序未经作者许可，不得用于其它任何用途 
	* @File    board.h
	* @Author  xiaowine@cee0.com
	* @date    修改日期:
	* @version V1.0
	*************************************************
	* @brief   -->>board.c
	****************************************************************************
	* @attention 
	* Powered By Xiaowine
	* <h2><center>&copy;  Copyright(C) 小酒论坛 2015-2019</center></h2>
	* All rights reserved
	* 
**/

#define flash_speed	60

#define AD_min_Limit	700

/*************	本地变量声明	**************/
extern uFLAG BOARD_Flag;
extern u16 Count_Board;
/*************	本地函数声明	**************/
/**
************************************************************************************************************************
 * @Function 	:		
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	
 * @param 		: 	
 * @Return  	:		None
 * @说	明  	:		
************************************************************************************************************************
*/
void Process_Para(u8 temp);
/**
************************************************************************************************************************
 * @Function 	:		void PWM_CHK_REC(PWM_CHK_STR *temp,u8 temp1)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	
 * @param 		: 	
 * @Return  	:		None
 * @说	明  	:		接收数据
************************************************************************************************************************
*/
void PARA_REC(PWM_CHK_STR *temp,u8 temp1);
/**
************************************************************************************************************************
 * @Function 	:		void Board_init(void)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	
 * @param 		: 	
 * @Return  	:		None
 * @说	明  	:		
************************************************************************************************************************
*/
void Board_init(void);
/**
************************************************************************************************************************
 * @Function 	:		void Para_PWM(USART_TypeDef* USARTx,u16 ch)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	
 * @param 		: 	
 * @Return  	:		None
 * @说	明  	:		
************************************************************************************************************************
*/
void Para_Board(USART_TypeDef* USARTx,u16 temp);
/**
************************************************************************************************************************
 * @Function 	:		u16 AD_States()
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	
 * @param 		: 	
 * @Return  	:		None
 * @说	明  	:		
************************************************************************************************************************
*/
u16 AD_States(uFLAG *temp1);

#endif

















