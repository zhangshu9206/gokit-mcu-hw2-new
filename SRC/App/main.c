/*********************************************************************** 
*    Copyright(C)          
*   �ļ�����  main.c
*   ��  �ߣ�  Terry
*   ��  ����  
*   ��  �ڣ�  2015/4/2
*   ��  ����  
*   ��  ʷ��  ��
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
*                           ����RCC
*******************************************************************************/
ErrorStatus HSEStartUpStatus;
void RCC_Configuration(void)
{   
  RCC_DeInit();//��λRCC�ⲿ�豸�Ĵ�����Ĭ��ֵ
	RCC_HSEConfig(RCC_HSE_ON);//���ⲿ���پ���   
  HSEStartUpStatus = RCC_WaitForHSEStartUp();//�ȴ��ⲿ����ʱ��׼����
  if(HSEStartUpStatus == SUCCESS)//�ⲿ����ʱ���Ѿ�׼���
  {								       
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);//����FLASH��Ԥȡ����    
    FLASH_SetLatency(FLASH_Latency_2);//FLASH�ӳ�2������ 
    RCC_HCLKConfig(RCC_SYSCLK_Div1);//����AHB(HCLK)ʱ��=SYSCLK     
    RCC_PCLK2Config(RCC_HCLK_Div1);//����APB2(PCLK2)��=AHBʱ��   
    RCC_PCLK1Config(RCC_HCLK_Div2);//����APB1(PCLK1)��=AHB 1/2ʱ��    
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);//����PLLʱ�� == �ⲿ���پ���ʱ��*9  PLLCLK = 8MHz * 9 = 72 MHz    
    RCC_PLLCmd(ENABLE);//ʹ��PLLʱ��  
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);//�ȴ�PLLʱ�Ӿ��� 
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);//����ϵͳʱ�� = PLLʱ��   
    while(RCC_GetSYSCLKSource() != 0x08);//���PLLʱ���Ƿ���Ϊϵͳʱ��
  }
}
