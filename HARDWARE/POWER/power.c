#include "power.h"
#include "adc.h"
#include "sys.h"
#define uchar unsigned char





void POWER_CONTROL()
{
	static uchar OVER_RUN_TIMES = 0;
	ad_value=Get_Adc(0);
	if(ad_value > Electric_Current_Limit)
	{
		OVER_RUN_TIMES++;
		if(OVER_RUN_TIMES > OVER_RUN_Limit)
			Transmit_Power_Control = POWER_OFF;
	}
	else
	{
		Transmit_Power_Control = POWER_ON;
		OVER_RUN_TIMES = 0;
	}
}































