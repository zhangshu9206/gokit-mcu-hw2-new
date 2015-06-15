/**************************************************************************************			  
* @file    LED.h 
* @author  LTY
* @version V1.0
* @date    04/08/2013
* @brief   GPIO ‰≥ˆ”¶”√
**************************************************************************************/
#ifndef LED__H__
#define LED__H__
#include "hw_lib.h"
void delay(uint32 us);
void LED_init(void);
void Led1_Turn_off(void);
void Led1_Turn_on(void);
void Led2_Turn_off(void);
void Led2_Turn_on(void);
void Motor_init(void);

void LED1_reverse(void);
void LED2_reverse(void);

#endif
