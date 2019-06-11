#ifndef __DOT_H
#define __DOT_H	 
#include "sys.h"
#include "config.h"
/*************行控制定义**************************/
#define ROW0_OUT	PAout(0)
#define ROW1_OUT	PAout(1)
#define ROW2_OUT	PAout(4)
/************定义按键***************************/
#define stop	PDin(2)

#define	key0	PCin(0)
#define	key1	PCin(1)
#define	key2	PCin(2)
#define	key3	PCin(3)
#define	key5	PCin(5)
#define	key6	PCin(6)
#define	key7	PCin(7)
#define	key8	PCin(8)
#define	key9	PCin(9)
#define	key10	PCin(10)
#define	key11	PCin(11)

/***************************************/
extern u8		MSIRowVal;
extern u16		MSILineValLast[3];
extern u16	MSILineValCurr;
extern u8		MSILineKeyVal[6];
extern uUINT16ARR address;
extern u8		hold;
/***************************************/

#define DATAIN   GPIO_ReadInputData(GPIOB)


void dot_init(void);
void dot_check(void);
u8 key_scan(u8 keydatain);
void keycheck(void);

/**
************************************************************************************************************************
 * @Function 	:		void judge_valid(void)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	检测有效性
 * @param 		: 	
 * @Return  	:		None
 * @说	明  	:		
************************************************************************************************************************
*/
void judge_valid(void);
/**
************************************************************************************************************************
 * @Function 	:		void send_data(u8 temp_num,u8 temp_val)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	数据发送
 * @param 		: 	temp_num 按键序号  temp_val键值 0按下 1放开
 * @Return  	:		None
 * @说	明  	:		
************************************************************************************************************************
*/
void send_data(u8 temp_num,u8 temp_val);
/**
************************************************************************************************************************
 * @Function 	:		void send_hold(u8 temp_hold)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	保持数据发送
 * @param 		: 	temp_num 按键序号  temp_val键值 0按下 1放开
 * @Return  	:		None
 * @说	明  	:		
************************************************************************************************************************
*/
void send_hold(u8 temp_hold);
/**
************************************************************************************************************************
 * @Function 	:		void send_AD(u8 temp_AD)
 * @author		: 	xiaowine@cee0.com
 * @brief 		: 	模拟量数据发送
 * @param 		: 	temp_AD 模拟量值(8位)
 * @Return  	:		None
 * @说	明  	:		
************************************************************************************************************************
*/
void send_AD(u8 temp_AD);































#endif














