#ifndef __FLASH_H
#define __FLASH_H	 
#include "sys.h"


#define	flash_times					5
#define	flash_work_speed		50
#define	flash_change_speed	5

#define	REC_Flash_times			5
#define	REC_S_speed					50
#define	REC_Q_speed					5


#define Sign_LED0 PAout(15)	
#define RECE_LED1 PCout(10)		




extern u8	flag_flash;
extern u16	flag_flash_counter;

extern u8	REC_flag;
extern u16	REC_flag_counter;

void LED_Init(void);//≥ı ºªØ	
void Sign_flash_CTR(void);
void Sign_flash(void);


#endif



