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
  //这个就是自动装载的计数值，由于计数是从0开始的，计数10000次后为9999
  TIM_TimeBaseStructure.TIM_Period = (10-1);	 //该值表示1Ms中断一次
  // 这个就是预分频系数，当由于为0时表示不分频所以要减1
  TIM_TimeBaseStructure.TIM_Prescaler = (7200 - 1);	  //10KHz
  // 高级应用本次不涉及。定义在定时器时钟(CK_INT)频率与数字滤波器(ETR,TIx)
  // 使用的采样频率之间的分频比例
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
  TIM_ClearITPendingBit(TIM4, TIM_IT_Update);/* Clear TIM5 update pending flag[清除TIM5溢出中断标志] */
  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); /* TIM IT enable */ //打开溢出中断  
  TIM_Cmd(TIM4, DISABLE);  //计数器失能，开始工作/* TIM5 enable counter */
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
