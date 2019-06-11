#ifndef __CONFIG_H
#define __CONFIG_H	 
#include "sys.h"
/**
	****************************************************************************
	* @Warning ������δ��������ɣ��������������κ���; 
	* @File    ϵͳ�����ļ�
	* @Author  xiaowine@cee0.com
	* @date    �޸�����:2015��3��14��14:53:30
	* @version V1.0
	*************************************************
	* @brief   -->>include struct files
	****************************************************************************
	* @attention 
	* Powered By Xiaowine
	* <h2><center>&copy;  Copyright(C) С����̳ 2015-2019</center></h2>
	* All rights reserved
	* 
**/

#define AddrID	((u16)0xa297)





/********���� EEPROM��ַ******************/
#define Current_Save_flag	0				//���ݸ��� 4��Chennel_NUM �ֽ�
#define Current_ADDR			1				//���ݸ��� 4��Chennel_NUM �ֽ�
#define Chennel_NUM				16

#define AddrID_ADDR				68			//4��Chennel_NUM+4 
/********ҡ�����ݽṹ��********************/
typedef struct
{
  uint16_t LCC_H;
  uint16_t LCC_M;
  uint16_t LCC_M1;
  uint16_t LCC_L;
	u8			 flag_bit_H;
	u8			 flag_bit_M;
	u8			 flag_bit_M1;
	u8			 flag_bit_L;
	float		 LCC_Fp_H;
	float		 LCC_Fp_L;
	u8			 LCC_BYTE_DATA;
}JOYSTICK;


/**********uint16���ַ����鹲����***************/
typedef	union _UINT16ARR_
{
  u16 HalfWord;
  u8  Byte[2];
}uUINT16ARR,*P_uUINT16ARR;

/************ϵͳʱ�ӽṹ��***************************/
typedef struct
{
	u16 Halfword;
	u16 SENDCLK;
	u16 RECclk;
}SYSclkint;
/************ϵͳʱ�ӱ�־λ�ṹ��***************************/
typedef struct
{
	u16 uClk;
	u16 uFLAG;
}ClkFg;

/*****ʱ�ӱ�־λ**********************************/
typedef struct
{
	u8 Halfword;
	u8 SEND_flag;
	u8 REC_flag;
}SYSFlagint;

/********PWM ���������ṹ��******************/
typedef struct	
{
//	u16 PWM_PPA;
	u8	Hight_Current;
	u8	Low_Current;
	u8	Start_Current;
	u8	Rang;
	u8	Medium_H;
	u8	Medium_L;
	float Coe_SpeedH;
	float Coe_SpeedL;

}PWM_Para;

/********LED �����ṹ��******************/
typedef struct	
{
	u16 flash_flag;
	u16	flash_counter;
}LED_Para;


//�����־λ
typedef	union _fullflag_
{
  u8  BYTE_flag;
  struct
  {
    u8 bit0:1;
    u8 bit1:1;
    u8 bit2:1;
    u8 bit3:1;
    u8 bit4:1;
    u8 bit5:1;
    u8 bit6:1;
    u8 bit7:1;
  }Bits;
}uFLAG,*P_uFLAG;



/********MODE adjustment�ṹ��******************/
typedef struct
{
	u8 	Parameter_Mode;
	u8 	Mode_IN_Flag;
	u16	Current_CH;
	u8	times_10ms;
	struct
	{
		u8 	Clk_flag:1;
		u8	speed_flag:1;
		u8  change_flag:1;
		u8  bit3:1;
		u8  bit4:1;
		u8  bit5:1;
		u8  bit6:1;
		u8  bit7:1;
	}bits;
}Mode_stu;
/********�������ݼĴ���******************/
typedef struct
{
	u8 RFnumber;
	u8 RData0;
	u8 RData1;
	u8 RData2;
	u8 RData3;
	u8 RData4;
	u8 RData5;
	u8 RData6;
	u8 RData7;
	u8 RData8;
	u8 RData9;
	u8 RData10;
	u8 RData11;
}Rec_Str;
/********PWM_CHK REC_data******************/
typedef struct
{
	u8 times;
	u8 number;
	u8 OKSTA;
	u8 RData0;
	u8 RData1;
	u8 RData2;
	u8 RData3;
}PWM_CHK_STR;
/**********ָ�� PWMֵ��ָ��****************/
typedef struct
{
	u8	*Pwm_out;
}Point_P;













#endif














