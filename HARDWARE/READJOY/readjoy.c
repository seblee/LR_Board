#include "readjoy.h"
#include "adc.h"
#include "dot.h"
#include "usart.h"
#include "24cxx.h" 
#include "myiic.h"
#include "adc.h"
#include "dot.h"

JOYSTICK JOY_data[8];
u8 par0[6]={0,0,0,0,0,0};
u8 par1[6]={0,0,0,0,0,0};
u8 par2[6]={0,0,0,0,0,0};
u8 par3[6]={0,0,0,0,0,0};
u8 par4[6]={0,0,0,0,0,0};
u8 par5[6]={0,0,0,0,0,0};


u8 Grade[8];
u8 Bak_Grade[8];
u8 GradeLast[8];
u8 Bak_GradeLast[8];
/**************/
void save_joy(void)
{
	u8 i,t = 0;
		printf("middle[%u]:%u\r\n",i,JOY_data[i].LCC_M);
	for(i = 0;i < JOY_NO;i++)
	{
		JOY_data[i].flag_bit_H = 0;
		JOY_data[i].flag_bit_M = 0;
		JOY_data[i].flag_bit_M1 = 0;
		JOY_data[i].flag_bit_L = 0;
	}
	while(1)
	{
//		if(EM_stop == 1)
//			printf("%u  \r\n",aftervalue[1]);
//		u16 joydata_tem[4];
		filter();
		t = key_scan(MSILineKeyVal[0]);
		delay_ms(100);
		if((EM_stop == 1)&&(t == 1))
		{
			for(i = 0;i < JOY_NO;i++)
			{
				if((JOY_data[i].flag_bit_M & (1<<i)) == 0)
				{
					JOY_data[i].LCC_M = aftervalue[i];
					printf("middle[%u]:%u\r\n",i,JOY_data[i].LCC_M);
					JOY_data[i].flag_bit_M |= 1<<i;
				}
			}
		}
		else if((EM_stop == 0)&&(t == 1))
		{
			for(i = 0;i < JOY_NO;i++)
			{
				if((aftervalue[i] > JOY_MAX_Limit)&&((JOY_data[i].flag_bit_H & (1<<i))==0))
				{
					JOY_data[i].LCC_H = aftervalue[i];
					printf("max[%u]:%u\r\n",i,JOY_data[i].LCC_H);
					JOY_data[i].flag_bit_H |= 1<<i;
				}
				if((aftervalue[i] < JOY_MIN_Limit)&&((JOY_data[i].flag_bit_L & (1<<i))==0))
				{
					JOY_data[i].LCC_L = aftervalue[i];
					printf("min[%u]:%u\r\n",i,JOY_data[i].LCC_L);
					JOY_data[i].flag_bit_L |= 1<<i;
				}
			}
		}
		else if(t == 2)
			AT24CXX_JOY_Write(JOYSTICKADD);
		else if(t == 3)
			read_read_joy();
	}
}



void read_read_joy(void)
{
	u8 i;
	printf("JOY_DATA Reading ......\r\n");
	AT24CXX_JOY_Read(JOYSTICKADD);
	printf("JOY_DATA Read Done\r\n");
	for(i = 0;i < JOY_NO;i++)
	{
		JOY_data[i].LCC_Fp_H = (float)128/(JOY_data[i].LCC_H - JOY_data[i].LCC_M);
		JOY_data[i].LCC_Fp_L = (float)128/(JOY_data[i].LCC_M - JOY_data[i].LCC_L);
	}
	/************初始化档位参数**************************/
	GET_para_int(0,par0);
	GET_para_int(1,par1);
	GET_para_int(2,par2);
	GET_para_int(3,par3);
	printf("1 %u  %u  %u  %u  %u  %u\r\n",par0[0],par0[1],par0[2],par0[3],par0[4],par0[5]);
	printf("2 %u  %u  %u  %u  %u  %u\r\n",par1[0],par1[1],par1[2],par1[3],par1[4],par1[5]);
	printf("3 %u  %u  %u  %u  %u  %u\r\n",par2[0],par2[1],par2[2],par2[3],par2[4],par2[5]);
	printf("4 %u  %u  %u  %u  %u  %u\r\n",par3[0],par3[1],par3[2],par3[3],par3[4],par3[5]);
}


void AT24CXX_JOY_Write(u16 WriteAddr)
{
	u8 i;
	printf("JOY_DATA Writing ......\r\n");
	for(i = 0;i < JOY_NO;i++)
	{
		AT24CXX_WriteOneByte(WriteAddr,(JOY_data[i].LCC_H>>8));
		AT24CXX_WriteOneByte(WriteAddr+1,(JOY_data[i].LCC_H&0xff));
		
		AT24CXX_WriteOneByte(WriteAddr+16,(JOY_data[i].LCC_M>>8));
		AT24CXX_WriteOneByte(WriteAddr+17,(JOY_data[i].LCC_M&0xff));
		
		AT24CXX_WriteOneByte(WriteAddr+32,(JOY_data[i].LCC_M1>>8));
		AT24CXX_WriteOneByte(WriteAddr+33,(JOY_data[i].LCC_M1&0xff));
		
		AT24CXX_WriteOneByte(WriteAddr+48,(JOY_data[i].LCC_L>>8));
		AT24CXX_WriteOneByte(WriteAddr+49,(JOY_data[i].LCC_L&0xff));
		
		WriteAddr += 2;
	}
	printf("JOY_DATA Writen Done\r\n");
}

void AT24CXX_JOY_Read(u16 WriteAddr)
{
	u8 temp_joy;
	u8 i;
	u16 temp;
	for(i = 0;i < JOY_NO;i++)
	{
		temp			=AT24CXX_ReadOneByte(WriteAddr);
		temp_joy	=AT24CXX_ReadOneByte(WriteAddr+1);
		
//		AT24CXX_Read(WriteAddr,temp_joy,2);
		JOY_data[i].LCC_H = ((temp<<8)|temp_joy);
		
		temp			=AT24CXX_ReadOneByte(WriteAddr+16);
		temp_joy	=AT24CXX_ReadOneByte(WriteAddr+17);
//		AT24CXX_Read(WriteAddr+16,temp_joy,2);
		JOY_data[i].LCC_M = ((temp<<8)|temp_joy);
		
		temp			=AT24CXX_ReadOneByte(WriteAddr+32);
		temp_joy	=AT24CXX_ReadOneByte(WriteAddr+33);
//		AT24CXX_Read(WriteAddr+32,temp_joy,2);
		JOY_data[i].LCC_M1 = ((temp<<8)|temp_joy);
		
		temp			=AT24CXX_ReadOneByte(WriteAddr+48);
		temp_joy	=AT24CXX_ReadOneByte(WriteAddr+49);
//		AT24CXX_Read(WriteAddr+48,temp_joy,2);
		JOY_data[i].LCC_L = ((temp<<8)|temp_joy);
		
		WriteAddr += 2;
		printf("LCC_H[%u] :%u\r\n",i,JOY_data[i].LCC_H);
		printf("LCC_M[%u] :%u\r\n",i,JOY_data[i].LCC_M);
		printf("LCC_M1[%u]:%u\r\n",i,JOY_data[i].LCC_M1);
		printf("LCC_L[%u] :%u\r\n",i,JOY_data[i].LCC_L);
		printf("\r\n");
	}
	
}
/*=============================================================================
	标准化摇杆输出值，0-255
=============================================================================*/
u8	AD_TO_BYTE(u8 ch)
{
	u8 grade;
	if(aftervalue[ch] < JOY_data[ch].LCC_L)
		grade = 0;
	else if(aftervalue[ch] < JOY_data[ch].LCC_M)
		grade = (aftervalue[ch] - JOY_data[ch].LCC_L) * (float)JOY_data[ch].LCC_Fp_L;
	else if(aftervalue[ch] <= JOY_data[ch].LCC_H)
		grade = 127 + (aftervalue[ch] - JOY_data[ch].LCC_M)*(float)JOY_data[ch].LCC_Fp_H;
	else if(aftervalue[ch] > JOY_data[ch].LCC_H)
		grade = 255;
	return grade;
}

/***************初始化摇杆挡位*****3档***********************************/

void GET_para_int(u8 ch,u8 *para)
{
	u8 temp;
	temp = 128 - 6*(float)JOY_data[ch].LCC_Fp_L*(JOY_data[ch].LCC_M - JOY_data[ch].LCC_L)/7;
	*para = temp;
	temp = 128 - 2*(float)JOY_data[ch].LCC_Fp_L*(JOY_data[ch].LCC_M - JOY_data[ch].LCC_L)/4;
	*(para+1) = temp;
	temp = 128 - (float)JOY_data[ch].LCC_Fp_L*(JOY_data[ch].LCC_M - JOY_data[ch].LCC_L)/4;
	*(para+2) = temp;
	temp = 127 +2*(float)JOY_data[ch].LCC_Fp_H*(JOY_data[ch].LCC_H - JOY_data[ch].LCC_M)/5; 
	*(para+3) = temp;
	temp = 127 +4*(float)JOY_data[ch].LCC_Fp_H*(JOY_data[ch].LCC_H - JOY_data[ch].LCC_M)/5; 
	*(para+4) = temp;
	temp = 127 +8*(float)JOY_data[ch].LCC_Fp_H*(JOY_data[ch].LCC_H - JOY_data[ch].LCC_M)/9;
	*(para+5) = temp;
	
	
//	*para 		= JOY_data[ch].LCC_M -2*(JOY_data[ch].LCC_M - JOY_data[ch].LCC_L)/3;
//	*(para+1) = JOY_data[ch].LCC_M -(JOY_data[ch].LCC_M - JOY_data[ch].LCC_L)/3;
//	*(para+2) = JOY_data[ch].LCC_M -(JOY_data[ch].LCC_M - JOY_data[ch].LCC_L)/4;
//	
//	*(para+3) = JOY_data[ch].LCC_M +(JOY_data[ch].LCC_H - JOY_data[ch].LCC_M)/4;
//	*(para+4) = JOY_data[ch].LCC_M +(JOY_data[ch].LCC_H - JOY_data[ch].LCC_M)/3;
//	*(para+5) = JOY_data[ch].LCC_M +2*(JOY_data[ch].LCC_H - JOY_data[ch].LCC_M)/3;
	
}

u8 AD_grade(u8 advall,u8 *para,u8 advall1,u8 *para1)
{
	u8 flag = 0;
	if(advall < *para)
		flag = 1;
	else if(advall < *(para+1))
		flag = 2;
	else if(advall < *(para+2))
		flag = 3;
	else if(advall < *(para+3))
		flag = 4;
	else if(advall < *(para+4))
		flag = 5;
	else if(advall <= *(para+5))
		flag = 6;
	else if(advall > *(para+5))
		flag = 7;
	else flag = 0;
	
	if(advall1 < *para1)
		flag |= 1<<4;
	else if(advall1 < *(para1+1))
		flag |= 2<<4;
	else if(advall1 < *(para1+2))
		flag |= 3<<4;
	else if(advall1 < *(para1+3))
		flag |= 4<<4;
	else if(advall1 < *(para1+4))
		flag |= 5<<4;
	else if(advall1 <= *(para1+5))
		flag |= 6<<4;
	else if(advall1 > *(para1+5))
		flag |= 7<<4;
	else flag |= 0<<4;
	return flag;
}


