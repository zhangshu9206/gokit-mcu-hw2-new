#include "hw_lib.h"
void NVIC_Configuration(void);

/*7200/72M*10=1/1000s=1ms*/
void TIM4_Configuration(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);/* TIM4 clock enable */  
  /* ---------------------------------------------------------------
    TIM4 Configuration: Output Compare Timing Mode:
    TIM2CLK = 36 MHz, Prescaler = 7200, TIM2 counter clock = 7.2 MHz
  --------------------------------------------------------------- */
  /* Time base configuration */
  //��������Զ�װ�صļ���ֵ�����ڼ����Ǵ�0��ʼ�ģ�����10000�κ�Ϊ9999
  TIM_TimeBaseStructure.TIM_Period = (10-1);	 //��ֵ��ʾ1Ms�ж�һ��
  // �������Ԥ��Ƶϵ����������Ϊ0ʱ��ʾ����Ƶ����Ҫ��1
  TIM_TimeBaseStructure.TIM_Prescaler = (7200 - 1);	  //10KHz
  // �߼�Ӧ�ñ��β��漰�������ڶ�ʱ��ʱ��(CK_INT)Ƶ���������˲���(ETR,TIx)
  // ʹ�õĲ���Ƶ��֮��ķ�Ƶ����
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  TIM_ClearITPendingBit(TIM4, TIM_IT_Update);/* Clear TIM5 update pending flag[���TIM5����жϱ�־] */
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); /* TIM IT enable */ //������ж�  
  TIM_Cmd(TIM4, DISABLE);  //������ʧ�ܣ���ʼ����/* TIM5 enable counter */
}

void NVIC_Configuration(void)
{ 
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Set the Vector Table base address at 0x08000000 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  /* Enable the TIM5 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure); 
}
void timer4_init()
{
	TIM4_Configuration();
	NVIC_Configuration();
}
extern unsigned int lngcounter;
void TIM4_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
  {
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    lngcounter++;
  }
}
