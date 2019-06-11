#include "pross.h"
#include "sys.h"
#define uchar unsigned char

u8 U1_num;
u8	USART1_array[5];
u16	U1_count;
u8	U1_rec_flag = 0;

void process_USART1(u8 ReC)
{
	USART_recieve_data(ReC,USART1_array,&U1_num);
	if(U1_num == 2)
	{
		U1_count = 0;
		U1_rec_flag = 0;
		U1_num = 0;
	}
}

void USART_recieve_data(u8 dat,u8 *array,u8 *number)
{
	if((*number == 0)&&((dat == 0x54)||(dat == 0x55)))
	{
		*array = dat;
		(*number)++;
	}
	else if(*number == 1)
	{
		*(array+1) = dat;
		(*number)++;
	}
	else *number = 0;
}



























