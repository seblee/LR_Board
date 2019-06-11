#ifndef __POWER_H
#define __POWER_H	 
#include "sys.h"

#define	Transmit_Power_Control	PAout(1)
#define	POWER_ON								1
#define	POWER_OFF								0
#define OVER_RUN_Limit					20
#define Electric_Current_Limit	200
extern unsigned int ad_value;



void POWER_CONTROL(void);
















#endif




















