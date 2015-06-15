/**************************************************************************************			  
* @file    LED.c 
* @author  LTY
* @version V1.0
* @date    04/02/2015
* @brief   GPIOÊä³öÓ¦ÓÃ
**************************************************************************************/
#include "hw_lib.h"

void delay(uint32 us)
{
	while(us--);
}

#define RCC_LED1   RCC_APB2Periph_GPIOB
#define PORT_LED1  GPIOB
#define GPIO_LED1  GPIO_Pin_1

#define RCC_LED2   RCC_APB2Periph_GPIOB
#define PORT_LED2  GPIOB
#define GPIO_LED2 	GPIO_Pin_11

#define RCC_LED3   RCC_APB2Periph_GPIOB
#define PORT_LED3  GPIOB
#define GPIO_LED3  GPIO_Pin_14

#define RCC_LED4   RCC_APB2Periph_GPIOB
#define PORT_LED4  GPIOB
#define GPIO_LED4 	GPIO_Pin_15


void LED_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //RCC_APB2Periph_AFIO 
  GPIO_InitStructure.GPIO_Pin = GPIO_LED1|GPIO_LED2|GPIO_LED3|GPIO_LED4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void Motor_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //RCC_APB2Periph_AFIO 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  //GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	//GPIO_ResetBits(GPIOB, GPIO_Pin_4|GPIO_Pin_5);
}

void LED1_reverse(void)
{
  GPIOB->ODR ^= GPIO_Pin_1;
}

void LED2_reverse(void)
{
  GPIOB->ODR ^= GPIO_Pin_11;
}

void Led1_Turn_off(void)
{
   GPIO_SetBits(PORT_LED1, GPIO_LED1);
}
void Led1_Turn_on(void)
{
   GPIO_ResetBits(PORT_LED1, GPIO_LED1);
}
void Led2_Turn_off(void)
{
	GPIO_ResetBits(PORT_LED2, GPIO_LED2);
}
void Led2_Turn_on(void)
{
	GPIO_SetBits(PORT_LED2, GPIO_LED2);
}
