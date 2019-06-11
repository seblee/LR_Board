#include "dpro.h"
#include "adc.h"
#include "dot.h"
#include "flash.h"
#include "usart.h"
u8       BatChaRat;   //
u8       BakBatChaRat;   //

u8 SwInVal[6];
u8 Bak_SwInVal[6];
u8 AdInval[8];
u8 AdinVallast[8];
u8 Bak_AdinVallast[8];
u8 Bak_AdInval[8];
u8 EmStopVal;
u8 Bak_EmStopVal;
u8 Uart0BuffSend[10];


void AD_SW_get(void)
{
	static u8 EEM_val = 0;
	u8 i;
	if((EM_stop == 1)||(EEM_val == 0))
	{
		for(i = 0;i < JOY_NO;i++)
			AdInval[i] = AD_TO_BYTE(i);
		for(i = 0;i < 6;i++)
			SwInVal[i] = MSILineKeyVal[i];
		GradeLast[0] = AD_grade(AdInval[0],par0,AdInval[1],par1);
		GradeLast[1] = AD_grade(AdInval[2],par2,AdInval[3],par3);
		GradeLast[2] = AD_grade(AdInval[4],par3,AdInval[5],par3);
		if( (SwInVal[0]==0)   &&
				(SwInVal[1]==0)   &&
				(SwInVal[2]==0)   &&
				(SwInVal[3]==0)   &&
				(SwInVal[4]==0)   &&
				(SwInVal[5]==0)   &&
				(GradeLast[0]==0x44)		 &&
				(GradeLast[1]==0x44)		 &&
				(GradeLast[2]==0x44)	)
		{EEM_val = 1;}
		else if(EM_stop == 1)
			EEM_val = 0;
		for(i = 0;i < JOY_NO;i++)
			AdInval[i] = 0x7f;
		for(i = 0;i < 6;i++)
			SwInVal[i] = 0;
		EmStopVal	 = 0x80;
		flag_flash = flash_times;
	}
	else if((EM_stop == 0)&&(EEM_val == 1))
	{
		for(i = 0;i < JOY_NO;i++)
		{
//			AdinVallast[i] = AD_TO_BYTE(i);
//			if(Bak_AdinVallast[i] == AdinVallast[i])
//				Bak_AdinVallast[i] = AdinVallast[i];
			AdInval[i] = AD_TO_BYTE(i);
		}
		for(i = 0;i < 6;i++)
			SwInVal[i] = MSILineKeyVal[i];
		EmStopVal = 0x00;
	}
	
	GradeLast[0] = AD_grade(AdInval[0],par0,AdInval[1],par1);
	GradeLast[1] = AD_grade(AdInval[2],par2,AdInval[3],par3);
	GradeLast[2] = AD_grade(AdInval[4],par3,AdInval[5],par3);
//	for(i = 0;i < 3;i++)
//	{
//		if(GradeLast[i] == Bak_GradeLast[i])
//			Grade[i] = GradeLast[i];
//		Bak_GradeLast[i] = GradeLast[i];
//	}
	Grade[0] = AD_grade(AdInval[0],par0,AdInval[1],par1);
	Grade[1] = AD_grade(AdInval[2],par2,AdInval[3],par3);
	Grade[2] = AD_grade(AdInval[4],par3,AdInval[5],par3);
//	printf("G[0]:%u  ad[0]:%u\r\n",Grade[0],aftervalue[0]);
	
	BatChaRat = CheckBatCha(aftervalue[8],FULLCHARGE,EMPTYCHARGE); //µçÁ¿
	
	if( (SwInVal[0]!=Bak_SwInVal[0])   ||
			(SwInVal[1]!=Bak_SwInVal[1])   ||
			(SwInVal[2]!=Bak_SwInVal[2])   ||
			(SwInVal[3]!=Bak_SwInVal[3])   ||
			(SwInVal[4]!=Bak_SwInVal[4])   ||
			(SwInVal[5]!=Bak_SwInVal[5])   ||
			(Grade[0]  !=Bak_Grade[0])		 ||
			(Grade[1]  !=Bak_Grade[1])		 ||
			(Grade[2]  !=Bak_Grade[2])		)
	{
		flag_flash = flash_times;
			
		for(i=0;i<6;i++)
			Bak_SwInVal[i] = SwInVal[i];
		for(i=0;i<3;i++)  
			Bak_Grade[i] = Grade[i];
	}
}

u8 CheckBatCha(u16 bat_value,u16 bat_H,u16 bat_L)
{
  u16 temp0;
  temp0 = (bat_H-bat_L)/4;
  if(bat_value>=(bat_H-temp0))return(0);
  else if(bat_value>=(bat_H-2*temp0))return(1);
  else if(bat_value>=(bat_H-3*temp0))return(2);
  else if(bat_value>=bat_L)return(3);
  else return(4);   
}



void NomOperSelfCheck(void)
{
	u8 EM_vale = 0;
	while(EM_vale == 0)
	{
		filter();
		AD_SW_get();	
		if( (SwInVal[0] == 0)&&
				(SwInVal[1] == 0)&&
				(SwInVal[2] == 0)&&
				(SwInVal[3] == 0)&&
				(SwInVal[4] == 0)&&
				(SwInVal[5] == 0)&&
				(Grade[0]== 0x44)&&
				(Grade[1]== 0x44)&&
				(Grade[2]== 0x44)&&/**/
				(EmStopVal ==0))
		{EM_vale = 1;}
		else flag_flash = flash_times;
//		printf("%u",Grade[0]);
	}		
}













