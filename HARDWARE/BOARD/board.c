#include "board.h"
#include "stm32f10x.h"
#include "sys.h" 
#include "usart.h"
#include "gpio.h"
#include "timer.h"
#include "config.h"
#include "adc.h"
#include "dma.h"
/**
	****************************************************************************
	* @Warning ������δ��������ɣ��������������κ���; 
	* @File    board.c
	* @Author  xiaowine@cee0.com
	* @date    �޸�����:
	* @version V1.0
	*************************************************
	* @brief   ���IO״̬ ���մ�������
	****************************************************************************
	* @attention 
	* Powered By Xiaowine
	* <h2><center>&copy;  Copyright(C) С����̳ 2015-2019</center></h2>
	* All rights reserved
	* 
**/

/*************	���ر�������	**************/
PWM_CHK_STR Para_Da;
void (*Para_FUN)(PWM_CHK_STR *,u8);
uFLAG BOARD_Flag = {0x00};
u16 Count_Board = 0;
/**
************************************************************************************************************************
 * @Function 	:		void Board_init(void)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	
 * @param 		: 	
 * @Return  	:		None
 * @˵	��  	:		
************************************************************************************************************************
*/
void Board_init(void)
{
	/**************************************/
	GPIO_init();
/********adcģ����******************/
	Adc_Init();
	MYDMA_CH1_Config(DMA1_Channel1,(u32)&ADC1->DR,(u32)&value,M*N);
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);
	DMA_Cmd(DMA1_Channel1, ENABLE);	
/********adcģ����******************/
	Para_FUN = PARA_REC;
	Proce_U1 = Process_Para;
}
/**
************************************************************************************************************************
 * @Function 	:		void Board_Scan(void)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	board ɨ��
 * @param 		: 	
 * @Return  	:		None
 * @˵	��  	:		
************************************************************************************************************************
*/
void Board_Scan(void)
{
	u16 temp1,temp2;
	if(Para_Da.number == 3)
	{
		Count_Board = 0;
		BOARD_Flag.Bits.bit0 = 1;
		Dead_MCU_CTR_ON; 
		temp1 = ((Para_Da.RData1<<8)|Para_Da.RData2)&0X0FFF;
		SYS_Flag.SEND_flag = 1;
//		temp2 = IO_States(&BOARD_Flag)&0X0FFF;
		temp2 = AD_States(&BOARD_Flag)&0X0FFF;
		if(temp1 == temp2)
			BOARD_Flag.Bits.bit1 = 1;
		else 
			BOARD_Flag.Bits.bit1 = 0;
		Para_Da.number = 0;
		Para_Board(USART1,temp2);
	}
}
/**
************************************************************************************************************************
 * @Function 	:		u16 AD_States()
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	
 * @param 		: 	
 * @Return  	:		None
 * @˵	��  	:		
************************************************************************************************************************
*/
u16 AD_States(uFLAG *temp1)
{
	u16 temp = 0;
	u8 i;
	for(i = 0;i < 12;i++)
	{
		if(aftervalue[i] > AD_min_Limit)
			temp |= 1<<i;
	}
	if(temp == 0)
		temp1->Bits.bit2 = 0;
	else temp1->Bits.bit2 = 1;
	return temp;
}



/**
************************************************************************************************************************
 * @Function 	:		void Process_Para(u8 temp)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	
 * @param 		: 	
 * @Return  	:		None
 * @˵	��  	:		
************************************************************************************************************************
*/
void Process_Para(u8 temp)
{
	(*Para_FUN)(&Para_Da,temp);
}

/**
************************************************************************************************************************
 * @Function 	:		void PWM_CHK_REC(PWM_CHK_STR *temp,u8 temp1)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	
 * @param 		: 	
 * @Return  	:		None
 * @˵	��  	:		�������� 57 DH	DL
************************************************************************************************************************
*/
void PARA_REC(PWM_CHK_STR *temp,u8 temp1)
{
	if((temp->number == 0)&&(temp1 == 0x57))
	{
		temp->number++;
		temp->RData0 = temp1;
	}
	else if(temp->number == 1)
	{
		temp->number++;
		temp->RData1 = temp1;
	}
	else if(temp->number == 2)
	{
		temp->number++;
		temp->RData2 = temp1;
	}
	else temp->number = 0;
	Board_Scan();
}
/**
************************************************************************************************************************
 * @Function 	:		void Para_PWM(USART_TypeDef* USARTx,u16 ch)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	
 * @param 		: 	
 * @Return  	:		None
 * @˵	��  	:		
************************************************************************************************************************
*/
void Para_Board(USART_TypeDef* USARTx,u16 temp)
{
	/*	��������������λ(�ȶ�USART_SR��Ȼ��д��USART_DR)��
	���ܹ���֤�׸����ݷ���ʱ�������ָ��ǵ����
	http://www.openedv.com/posts/list/14573.htm
	����ִ������һ������
	*/
	USART_ClearFlag(USARTx,USART_FLAG_TC);
//	USART_GetFlagStatus(USART1, USART_FLAG_TC);
	/**************************/
	USART_SendData(USARTx, 0x7a);//�򴮿�x��������
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
	USART_SendData(USARTx, (u8)(temp>>8));//�򴮿�x��������
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
	USART_SendData(USARTx,(u8)(temp&0xff));//�򴮿�x��������
	while(USART_GetFlagStatus(USARTx,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
}









