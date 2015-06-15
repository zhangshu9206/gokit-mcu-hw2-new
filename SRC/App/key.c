#include "hw_lib.h"

unsigned int lngcounter=0; //��������ʱ�����
/**********************************************************************
* ��    �ƣ�
* ��    �ܣ������������
* ��ڲ����� 
* ���ڲ�����
-----------------------------------------------------------------------
* ˵����ʹ�ÿ⺯��������IO��
***********************************************************************/
void key_GPIO_Configuration(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //RCC_APB2Periph_AFIO 
  /*����PB7Ϊ����*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //| GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�������50MHZ
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//GPIO_Mode_IPU;�ڲ�����Ϊ�ߵ�ƽ
  GPIO_Init(GPIOB,&GPIO_InitStructure);
}
/***********************
** ��������: 
** ��������: ��⵽һ�κ����ƽ�仯
** �䡡 ��: �����ź�
** �� ��: 0:�ް��� 1:һ�ε��� 2��һ�γ���
** ȫ�ֱ���: lngcounter
** ����ģ��: 
** ˵���� lngcounter�����ж�ʱ��Ϊһ����Ķ�ʱ�����Լ�һ��
** ע�⣺
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
			if(lngcounter>200)//�������ʱ�䳬��200ms����Ϊ�ǳ���������2
			{
				lngcounter=0;
				return 2;
			}
			else //�ǳ�������Ϊһ����ͨ����
			{
				lngcounter=0;
				return 1; //����һ
			}
		}
		else
		{	
		   lngcounter=0;
	    	return 0; //��ʱ��͵�ƽ��ʧ��Ϊ�ް������£�����0
		}
	}
	else
	return 0; //û�а����ź�ֱ�ӷ���
}

void infrared_detection(void)
{
	uint8 infraredKey=infraredKEY();
	if(2==infraredKey)
	{	
			LED2_reverse();
	}
}


