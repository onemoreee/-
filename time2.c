#include "sys.h"
/********************
①使能定时器时钟。
RCC_APB1PeriphClockCmd();
② 初始化定时器，配置ARR,PSC。
TIM_TimeBaseInit();
③定时器中断配置，同时配置NVIC。
void TIM_ITConfig();
NVIC_Init();
④使能定时器。
TIM_Cmd();
⑤编写中断服务函数。
TIMx_IRQHandler();
*****************/
int timer2_flag = 0;
void TIM2_Init(u32 arr,u32 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	TIM_DeInit(TIM2); 
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);                    //清除溢出中断标志位
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);                     //使能TIM2溢出中断    
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)//每过10ms进入一次中断
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  
	{		
		SystemTimer++;//全局计时的变量+1,表示过去了10ms=0.01s
		static u16 T2Count0,T2Count1;
		T2Count0++;
		T2Count1++;
//		if(T2Count0 >=100)
//		{
//			 T2Count0=0;
//			 //DHT11_flag  =   DHT11_Read_Data(&temper,&humi);
//		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update); 					
	}
}
