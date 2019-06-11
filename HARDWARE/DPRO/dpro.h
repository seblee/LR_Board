#ifndef __DPRO_H
#define __DPRO_H	 

#include "sys.h"
#include "config.h"
#include "readjoy.h"


extern u8 SwInVal[6];
extern u8 AdInval[8];
extern u8 AdinVallast[8];
extern u8 Bak_AdinVallast[8];
extern u8 Bak_AdInval[8];
extern u8 EmStopVal;
extern u8 Uart0BuffSend[10];



u8 CheckBatCha(u16 bat_value,u16 bat_H,u16 bat_L);
void AD_SW_get(void);
void NomOperSelfCheck(void);

#endif
