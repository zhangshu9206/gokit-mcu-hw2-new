/**************************************************************************************			  
* @file    qneacs_hw_lib.h 
* @author  LTY
* @version V1.0
* @date    04/08/2013
* @brief   全局配置，所有应用C文件只需要包含此头文件即可。
**************************************************************************************/
#ifndef QNEACS_HW_LIB__H__
#define QNEACS_HW_LIB__H__

#ifndef STM32F10X_MD
#define STM32F10X_MD
#endif

#include "stm32f10x.h"
#include "stdio.h"
#include "string.h"
#define USE_FULL_ASSERT
#include <stdio.h>
#include <stdarg.h>

#include <stdlib.h>

#define uint8 unsigned char
#define sint8 signed char
#define uint16 unsigned short
#define sint16 signed short 
#define uint32 unsigned int
#define sint32 signed int

#define NULL 0

#define DBG_EN  0
#define DBG_WATCH 1
 


#include "delay.h"
#include "stm32f10x_it.h"
#include "LED.h"
#include "Time2.h"
#include "Time4.h"
#include "key.h"

#include <stdio.h>
#include <stdlib.h>

#endif

