/*********************************************************************** 
*    Copyright(C)          
*   文件名：  main.c
*   作  者：  Terry
*   版  本：  
*   日  期：  2015/4/2
*   描  述：  
*   历  史：  无
*************************************************************************/ 
#include "hw_lib.h"
void sys_hw_init()
{
	//RCC_Configuration();
	system_delay.init();
	key_GPIO_Configuration();
	LED_init();
	Motor_init();
	timer2_init(1000);//second interrupt
	timer4_init();//millisecond interrupt
}
int main(void)			
{ 	
	sys_hw_init();
	while(1)
	{
		for(;;);
	}
	while(1)
	{		
//         Gokit_MessageHandle();
//         Gokit_P0CmdHandle();
//         KEY_Handle();
//         IR_Handle();
//         DHT11_Read_Data(&Device_ReadStruct.Temperature, &Device_ReadStruct.Humidity);
//         ReportDevStatusHandle(); 
	}
}
/*******************************************************************************
*                           配置RCC
*******************************************************************************/
ErrorStatus HSEStartUpStatus;
void RCC_Configuration(void)
{   
  RCC_DeInit();//复位RCC外部设备寄存器到默认值
	RCC_HSEConfig(RCC_HSE_ON);//打开外部高速晶振   
  HSEStartUpStatus = RCC_WaitForHSEStartUp();//等待外部高速时钟准备好
  if(HSEStartUpStatus == SUCCESS)//外部高速时钟已经准别好
  {								       
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);//开启FLASH的预取功能    
    FLASH_SetLatency(FLASH_Latency_2);//FLASH延迟2个周期 
    RCC_HCLKConfig(RCC_SYSCLK_Div1);//配置AHB(HCLK)时钟=SYSCLK     
    RCC_PCLK2Config(RCC_HCLK_Div1);//配置APB2(PCLK2)钟=AHB时钟   
    RCC_PCLK1Config(RCC_HCLK_Div2);//配置APB1(PCLK1)钟=AHB 1/2时钟    
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);//配置PLL时钟 == 外部高速晶体时钟*9  PLLCLK = 8MHz * 9 = 72 MHz    
    RCC_PLLCmd(ENABLE);//使能PLL时钟  
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);//等待PLL时钟就绪 
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//配置系统时钟 = PLL时钟   
    while(RCC_GetSYSCLKSource() != 0x08);//检查PLL时钟是否作为系统时钟
  }
}
