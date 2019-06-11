#include "flash.h"
#include "usart.h"
#include "delay.h"
#include "board.h"
/**
	****************************************************************************
	* @Warning ������δ��������ɣ��������������κ���; 
	* @File    flash.c
	* @Author  xiaowine@cee0.com
	* @date    �޸�����:
	* @version V1.0
	*************************************************
	* @brief   
	****************************************************************************
	* @attention 
	* Powered By Xiaowine
	* <h2><center>&copy;  Copyright(C) С����̳ 2015-2019</center></h2>
	* All rights reserved
	* 
**/


/*************	���ر�������	**************/
u8	flag_flash					=	0;
u16	flag_flash_counter	=	0;

u8	REC_flag;
u16	REC_flag_counter;








/**
************************************************************************************************************************
 * @Function 	:		void LED_Init(void)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	flash IO��ʼ��
 * @param 		: 	
 * @Return  	:		None
 * @˵	��  	:		
************************************************************************************************************************
*/
void LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO, ENABLE);	 //ʹ��PA,PB,PC,PD�˿�ʱ��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//����JTAG���� ʹ��PB3
/*PB0 PB1 PB3-PB9 PB12-15  */ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC
	GPIO_SetBits(GPIOA,GPIO_Pin_15);	//���������
/*PA8 */ 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC
	GPIO_SetBits(GPIOC,GPIO_Pin_10);	//���������
}
/**
************************************************************************************************************************
 * @Function 	:		void Sign_flash(void)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	Sign_LED0״̬��ת
 * @param 		: 	
 * @Return  	:		None
 * @˵	��  	:		
************************************************************************************************************************
*/
void Sign_flash(void)
{
	static u8 LED_STATE	=	1;
	switch(LED_STATE)
	{
		case 1:Sign_LED0 = 0;LED_STATE = 2;break;
		case 2:Sign_LED0 = 1;LED_STATE = 1;break;
		default:LED_STATE = 1;break;
	}
}
/**
************************************************************************************************************************
 * @Function 	:		void REC_flash(void)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	RECE_LED1״̬��ת
 * @param 		: 	
 * @Return  	:		None
 * @˵	��  	:		
************************************************************************************************************************
*/
void REC_flash(void)
{
	static u8 REC_STATE	=	1;
	switch(REC_STATE)
	{
		case 1:RECE_LED1 = 0;REC_STATE = 2;break;
		case 2:RECE_LED1 = 1;REC_STATE = 1;break;
		default:REC_STATE = 1;break;
	}
}
/**
************************************************************************************************************************
 * @Function 	:		void Sign_flash_CTR(void)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	ɨ����Ƶ�
 * @param 		: 	
 * @Return  	:		None
 * @˵	��  	:		
************************************************************************************************************************
*/
void Sign_flash_CTR(void)
{
	if(REC_flag_counter == 0)
	{
		if(((BOARD_Flag.Bits.bit0 == 1)&&(BOARD_Flag.Bits.bit1 == 0))||
			 ((BOARD_Flag.Bits.bit0 == 0)&&(BOARD_Flag.Bits.bit2 == 1)) )
		{
			REC_flash(); 
			REC_flag_counter = REC_Q_speed;				//����
		}
		else if((BOARD_Flag.Bits.bit0 == 1)&&(BOARD_Flag.Bits.bit1 == 1))
		{
			REC_flash(); 
			REC_flag_counter = REC_S_speed;				//����
		}
		else 
			RECE_LED1 = 1;
	}else if(REC_flag_counter > 0)REC_flag_counter--;

	if(flag_flash_counter == 0)
	{
		if(flag_flash > 0)
		{
			Sign_flash(); 
			flag_flash--; 
			flag_flash_counter = flash_change_speed;
		}
		else 
		{
				Sign_flash(); 
				flag_flash_counter = flash_work_speed;
		}
	}else if(flag_flash_counter > 0)flag_flash_counter--;
	
}

