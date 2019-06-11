#ifndef __READJOY_H
#define __READJOY_H	 
#include "sys.h"
#include "config.h"






extern JOYSTICK JOY_data[8];
extern u8 par0[6];
extern u8 par1[6];
extern u8 par2[6];
extern u8 par3[6];
extern u8 par4[6];
extern u8 par5[6];
extern u8 Grade[8];
extern u8 Bak_Grade[8];
extern u8 GradeLast[8];
extern u8 Bak_GradeLast[8];






void save_joy(void);
void read_read_joy(void);
void AT24CXX_JOY_Write(u16 WriteAddr);
void AT24CXX_JOY_Read(u16 WriteAddr);
u8	AD_TO_BYTE(u8 ch);
void GET_para_int(u8 ch,u8 *para);
u8 AD_grade(u8 advall,u8 *par0,u8 advall1,u8 *par1);




































#endif














