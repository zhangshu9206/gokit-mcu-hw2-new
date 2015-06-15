#include "hw_lib.h"

//((1+TIM_Prescaler )/72M)*(1+TIM_Period )=((1+35999)/72M)*(1+2000)=1秒。
void TIM2_Init(uint32 counter_ms)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure; 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);/* TIM2 clock enable */ 
  /* ---------------------------------------------------------------
    TIM4 Configuration: Output Compare Timing Mode:
    TIM2CLK = 72 MHz, Prescaler = 7200, TIM2 counter clock = 7.2 MHz
  --------------------------------------------------------------- */
  /* Time base configuration */ 
  TIM_TimeBaseStructure.TIM_Period = (10*counter_ms - 1);//这个就是自动装载的计数值，由于计数是从0开始的，计数10000次后为9999 
	TIM_TimeBaseStructure.TIM_Prescaler = (7200 - 1);//这个就是预分频系数，当由于为0时表示不分频所以要减1
  //高级应用本次不涉及。定义在定时器时钟(CK_INT)频率与数字滤波器(ETR,TIx)
  //使用的采样频率之间的分频比例
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  /* Clear TIM5 update pending flag[清除TIM2溢出中断标志] */
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
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);/////优先级组
  /* Enable the TIM5 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;/////抢占式优先级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;////响应式优先级
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


