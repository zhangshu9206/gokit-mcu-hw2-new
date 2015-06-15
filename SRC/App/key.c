#include "hw_lib.h"

unsigned int lngcounter=0; //按键按下时间测量
/**********************************************************************
* 名    称：
* 功    能：配置输入输出
* 入口参数： 
* 出口参数：
-----------------------------------------------------------------------
* 说明：使用库函数，配置IO口
***********************************************************************/
void key_GPIO_Configuration(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //RCC_APB2Periph_AFIO 
  /*设置PB7为输入*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//最大输入50MHZ
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//GPIO_Mode_IPU;内部上拉为高电平
  GPIO_Init(GPIOB,&GPIO_InitStructure);
}
/***********************
** 函数名称: 
** 功能描述: 检测到一次红外电平变化
** 输　 入: 按键信号
** 输 出: 0:无按键 1:一次单击 2：一次长按
** 全局变量: lngcounter
** 调用模块: 
** 说明： lngcounter是在中断时间为一毫秒的定时器里自加一的
** 注意：
********************/
uint8 infraredKEY(void)
{
	if(Infrared==0)
	{ 
		system_delay.msecond(10);
		if(Infrared==0)
		{	
			TIM_Cmd(TIM4,ENABLE);
			while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)==0);
			TIM_Cmd(TIM4,DISABLE);			
			if(lngcounter>200)//如果按键时间超过200ms则视为是长按并返回2
			{
				lngcounter=0;
				return 2;
			}
			else //非长按，仅为一次普通单击
			{
				lngcounter=0;
				return 1; //返回一
			}
		}
		else
		{	
		   lngcounter=0;
	    	return 0; //延时后低电平消失视为无按键按下，返回0
		}
	}
	else
	return 0; //没有按键信号直接返回
}

void infrared_detection(void)
{
	uint8 infraredKey=infraredKEY();
	if(2==infraredKey)
	{	
			LED2_reverse();
	}
}


