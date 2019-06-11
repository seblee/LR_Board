#include "gpio.h"
/**
	****************************************************************************
	* @Warning ������δ��������ɣ��������������κ���; 
	* @File    gpio.c
	* @Author  xiaowine@cee0.com
	* @date    �޸�����:
	* @version V1.0
	*************************************************
	* @brief   ����IO����
	****************************************************************************
	* @attention 
	* Powered By Xiaowine
	* <h2><center>&copy;  Copyright(C) С����̳ 2015-2019</center></h2>
	* All rights reserved
	* 
**/


/**
************************************************************************************************************************
 * @Function 	:		void GPIO_init(void) 
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	����IO����
 * @param 		: 	
 * @Return  	:		None
 * @˵	��  	:		
************************************************************************************************************************
*/
void GPIO_init(void) 
{
	GPIO_InitTypeDef  GPIO_InitStructure;
// 	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//����JTAG���� ʹ��PB3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|
												 RCC_APB2Periph_GPIOB|
												 RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA,PB,PC,PD�˿�ʱ��
	/*****************PA0~7*******************************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|
																GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC
	/*****************PB1~1*******************************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC
	/****************PC4~5********************************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC
	/**********************************************************/
}
/**
************************************************************************************************************************
 * @Function 	:		u16 IO_States(void)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	���ͨ��״̬
 * @param 		: 	u16 *temp ��ͨ��״̬ λ��ʾ d0λ��ʾͨ��0
 * @Return  	:		None
 * @˵	��  	:		
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
// 	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//����JTAG���� ʹ��PB3
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA,PB,PC,PD�˿�ʱ��
	/*****************PC15*******************************************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC
	GPIO_SetBits(GPIOC,GPIO_Pin_15);						 //PB�����
//	GPIO_ResetBits(GPIOC,GPIO_Pin_15);
}











