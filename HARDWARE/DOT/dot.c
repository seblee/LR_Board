#include "dot.h"
#include "delay.h"
#include "flash.h"
#include "usart.h"
/*************** ���󰴼�����������*************************/
u8		MSIRowVal;
u16		MSILineValLast[3];
u16		MSILineValCurr;
u8		MSILineKeyVal[6];
u8		valid = 0;
u8		hold	= 0xff;
/***************************************/

void dot_init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE); 
//	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);//����JTAG���� ʹ��PB3
	/*PC0-3 PC5-11*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3 |
																GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7 |GPIO_Pin_8 |
																GPIO_Pin_9 |GPIO_Pin_10|GPIO_Pin_11;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOD, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC
	
	
/**********************************************************/
/**********************************************************/
}



void dot_check(void)
{
/****************��һ��******************************************/
	ROW0_OUT = 0;
	delay_us(10);
	MSILineValCurr = DATAIN;
	if(MSILineValCurr == MSILineValLast[0])
	{
		MSILineKeyVal[0] = (~MSILineValCurr)&0xff;
		MSILineKeyVal[1] = (~MSILineValCurr)>>8;
	}
	MSILineValLast[0] = MSILineValCurr;
	ROW0_OUT = 1;
	
/*****************�ڶ���*****************************************/
	ROW1_OUT = 0;
	delay_us(10);
	MSILineValCurr = DATAIN;
	if(MSILineValCurr == MSILineValLast[1])
	{
		MSILineKeyVal[2] = (~MSILineValCurr)&0xff;
		MSILineKeyVal[3] = (~MSILineValCurr)>>8;
	}
	MSILineValLast[1] = MSILineValCurr;
	ROW1_OUT = 1;
	
/******************������****************************************/
	ROW2_OUT = 0;
	delay_us(10);
	MSILineValCurr = DATAIN;
	if(MSILineValCurr == MSILineValLast[2])
	{
		MSILineKeyVal[4] = (~MSILineValCurr)&0xff;
		MSILineKeyVal[5] = (~MSILineValCurr)>>8;
	}
	MSILineValLast[2] = MSILineValCurr;
	ROW2_OUT = 1;
}

u8 key_scan(u8 keydatain)
{
	static u8 key_up=1;//
	if((key_up == 1)&&(keydatain != 0))
	{
		key_up = 0;
		if(keydatain == 1)
			return 1;
		else if(keydatain == 2)
			return 2;
		else if(keydatain == 4)
			return 3;
		else if(keydatain == 8)
			return 4;
		else if(keydatain == 0x10)
			return 5;
		else if(keydatain == 0x20)
			return 6;
		else if(keydatain == 0x40)
			return 7;
		else if(keydatain == 0x80)
			return 8;
		else return 0;
	}else if(keydatain == 0)key_up = 1;

	return 0;
}

void keycheck(void)
{
	if(key0 == 0)
		Led_D0 = 0;
	else Led_D0 = 1;
/**************************/
	if(key1 == 0)
		Led_D1 = 0;
	else Led_D1 = 1;
/**************************/
	if(key2 == 0)
		Led_D2 = 0;
	else Led_D2 = 1;
/**************************/
	if(key3 == 0)
	{	Led_D3 = 0;
		Led_D4 = 0;
	}
	else{
		Led_D3 = 1;
		Led_D4 = 1;
	}
/**************************/
	if(key5 == 0)
		Led_D5 = 0;
	else Led_D5 = 1;
/**************************/
	if(key6 == 0)
		Led_D6 = 0;
	else Led_D6 = 1;
/**************************/
	if(key7 == 0)
		Led_D7 = 0;
	else Led_D7 = 1;
/**************************/
	if(key8 == 0)
		Led_D8 = 0;
	else Led_D8 = 1;
/**************************/
	if(key9 == 0)
		Led_D9 = 0;
	else Led_D9 = 1;
/**************************/
	if(key10 == 0)
		Led_D10 = 0;
	else Led_D10 = 1;
/**************************/
	if(key11 == 0)
		Led_D11 = 0;
	else Led_D11 = 1;
/**************************/
}
/**
************************************************************************************************************************
 * @Function 	:		void judge_valid(void)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	�����Ч��
 * @param 		: 	
 * @Return  	:		None
 * @˵	��  	:		
************************************************************************************************************************
*/
void judge_valid(void)
{
	if((stop==0)&&(key0==1)&&(key1==1)&&(key2==1)&&(key3==1)&&(key5==1)&&(key6==1)&&(key7==1)&&(key8==1)&&(key9==1)&&(key10==1)&&(key11==1))  //�����ͣ���ϣ���������û�к��ϣ���Ч
		valid=1;
	else if(stop==1)
	{
		hold 	= 0xff;
		valid	=	0; //������Ч
	}
}

/*=============================================================================
�㶯���� ������ʱ���͡��Ͽ�ʱ��������
=============================================================================*/
/**
************************************************************************************************************************
 * @Function 	:		u8 dot_move(u8 key,u8 key_num,u8 temp)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	����
 * @param 		: 	
 * @Return  	:		None
 * @˵	��  	:		
************************************************************************************************************************
*/
u8 dot_move(u8 key,u8 key_num,u8 temp)
{
	if(key==0)
	{
		send_data(key_num,0);
		temp=0;
	}
	else if(temp<5)
	{
		send_data(key_num,1);
		temp=temp+1;
	}
	return(temp);
}
/**
************************************************************************************************************************
 * @Function 	:		void send_data(u8 temp_num,u8 temp_val)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	��ʱ�ź����ݷ���
 * @param 		: 	temp_num �������  temp_val��ֵ 0���� 1�ſ�
 * @Return  	:		None
 * @˵	��  	:		
************************************************************************************************************************
*/
void send_data(u8 temp_num,u8 temp_val)
{
	FM0DataToUART(address,0x54+temp_val,temp_num,USART_TX_BUF);
	USARTx_Send_buff(USART1,USART_TRA_LEN,USART_TX_BUF);
}
/**
************************************************************************************************************************
 * @Function 	:		void send_hold(u8 temp_hold)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	�������ݷ���
 * @param 		: 	temp_hold ���������ź�
 * @Return  	:		None
 * @˵	��  	:		
************************************************************************************************************************
*/
void send_hold(u8 temp_hold)
{
	FM0DataToUART(address,0x57,temp_hold,USART_TX_BUF);
	USARTx_Send_buff(USART1,USART_TRA_LEN,USART_TX_BUF);
}
/**
************************************************************************************************************************
 * @Function 	:		void send_AD(u8 temp_AD)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	ģ�������ݷ���
 * @param 		: 	temp_AD ģ����ֵ(8λ)
 * @Return  	:		None
 * @˵	��  	:		
************************************************************************************************************************
*/
void send_AD(u8 temp_AD)
{
	FM0DataToUART(address,0x56,temp_AD,USART_TX_BUF);
	USARTx_Send_buff(USART1,USART_TRA_LEN,USART_TX_BUF);
}





