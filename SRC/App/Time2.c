#include "hw_lib.h"

//((1+TIM_Prescaler )/72M)*(1+TIM_Period )=((1+35999)/72M)*(1+2000)=1�롣
void TIM2_Init(uint32 counter_ms)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);/* TIM2 clock enable */ 
  /* ---------------------------------------------------------------
    TIM4 Configuration: Output Compare Timing Mode:
    TIM2CLK = 72 MHz, Prescaler = 7200, TIM2 counter clock = 7.2 MHz
  --------------------------------------------------------------- */
  /* Time base configuration */ 
  TIM_TimeBaseStructure.TIM_Period = (10*counter_ms - 1);//��������Զ�װ�صļ���ֵ�����ڼ����Ǵ�0��ʼ�ģ�����10000�κ�Ϊ9999 
	TIM_TimeBaseStructure.TIM_Prescaler = (7200 - 1);//�������Ԥ��Ƶϵ����������Ϊ0ʱ��ʾ����Ƶ����Ҫ��1
  //�߼�Ӧ�ñ��β��漰�������ڶ�ʱ��ʱ��(CK_INT)Ƶ���������˲���(ETR,TIx)
  //ʹ�õĲ���Ƶ��֮��ķ�Ƶ����
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* Clear TIM5 update pending flag[���TIM2����жϱ�־] */
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);  
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);/* TIM IT enable */ 
  TIM_Cmd(TIM2, ENABLE);/* TIM2 enable counter */
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures the used IRQ Channels and sets their priority.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void NVIC_Configuration(void)
{ 
  NVIC_InitTypeDef NVIC_InitStructure; 
  /* Set the Vector Table base address at 0x08000000 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);/////���ȼ���
  /* Enable the TIM5 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;/////��ռʽ���ȼ�
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;////��Ӧʽ���ȼ�
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);  
}
void timer2_init(uint32 counter_ms)
{
	TIM2_Init(counter_ms);
	NVIC_Configuration();	
}
void TIM2_IRQHandler()
{ 
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	
		LED1_reverse();
  }
}


