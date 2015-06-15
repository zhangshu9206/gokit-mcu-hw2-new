/**************************************************************************************			  
* @file   key.h 
* @author  
* @version V1.0
* @date    04/08/2013
* @brief  
**************************************************************************************/
#ifndef KEY__H__
#define KEY__H__
#include "hw_lib.h"

#define  Infrared  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)

extern uint8 cancellAlarmFlag;

void key_GPIO_Configuration(void);
void infrared_detection(void);


#endif

