#ifndef __PROSS_H
#define __PROSS_H	 
#include "sys.h"






void process_USART1(u8 ReC);
void USART_recieve_data(u8 dat,u8 *array,u8 *number);

extern u8 U1_num;
extern u8	USART1_array[5];
extern u16	U1_count;
extern u8	U1_rec_flag;













#endif




















