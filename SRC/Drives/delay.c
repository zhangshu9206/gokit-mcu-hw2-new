/*********************************************************************** 
*    Copyright(C)          
*   
*   文件名：  delay.c
*   作  者：  LTY
*   版  本：  Ver1.0
*   日  期：  20130516
*   描  述：  不精确的延时与精确延时函数
*   历  史：  无
*************************************************************************/
#include "hw_lib.h"

static uint8  fac_us=0;//us延时倍乘数
static uint16 fac_ms=0;//ms延时倍乘数

#define SYSCLK 72
/*********************************************************************** 
* 函数名：  delay 
* 描  述：  不精确延时
* 调  用：  系统初始化时调用
* 被调用：  
* 输  入：  
* 输  出： 
* 其  他：  
***********************************************************************/
//static void delay(uint32 tick)
//{
	//while(tick--);
//}
/*********************************************************************** 
* 函数名：  delay_init 
* 描  述：  精确延时函数初始化
* 调  用：  系统初始化时调用
* 被调用：  
* 输  入：  
* 输  出： 
* 其  他：  
***********************************************************************/
static void delay_init()
{
	SysTick->CTRL&=0xfffffffb;//选择内部时钟 HCLK/8
	fac_us=SYSCLK/8;      
	fac_ms=(uint16)fac_us*1000;
}            

/*********************************************************************** 
* 函数名：  delay_ms 
* 描  述：  精确延时ms
* 调  用：  
* 被调用：  
* 输  入：  @ms：延时时间，取值范围 0~1864
* 输  出： 
* 其  他：  ms<=0xffffff*8/SYSCLK
***********************************************************************/
static void delay_ms(uint16 ms)
{         
	uint32 temp;  
	ms=(ms<=1864)?ms:1864;   
	SysTick->LOAD=(uint32)ms*fac_ms;//时间加载
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL=0x01 ;          //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器        
}   
/*********************************************************************** 
* 函数名：  delay_us 
* 描  述：  精确延时us
* 调  用：  
* 被调用：  
* 输  入：  @ns：延时时间
* 输  出： 
* 其  他：  
***********************************************************************/        
static void delay_us(uint32 us)
{  
	uint32 temp;       
	SysTick->LOAD=us*fac_us; //时间加载      
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL=0x01 ;      //开始倒数   
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器     
}  
 /*********************************************************************** 
* 函数名：  delay_seconds 
* 描  述：  精确延时s
* 调  用：  
* 被调用：  
* 输  入：  @s：延时时间
* 输  出： 
* 其  他：  
***********************************************************************/
static void delay_seconds(uint16 s)
{
	uint16 i=0;
	for(i=0;i<s;i++)
	{
		delay_ms(1000);
	}
}

system_delay_t system_delay=
{
	.init=delay_init,
	.usecond=delay_us,
	.msecond=delay_ms,
	.second=delay_seconds
};


