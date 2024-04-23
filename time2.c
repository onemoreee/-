#include "sys.h"
/********************
��ʹ�ܶ�ʱ��ʱ�ӡ�
RCC_APB1PeriphClockCmd();
�� ��ʼ����ʱ��������ARR,PSC��
TIM_TimeBaseInit();
�۶�ʱ���ж����ã�ͬʱ����NVIC��
void TIM_ITConfig();
NVIC_Init();
��ʹ�ܶ�ʱ����
TIM_Cmd();
�ݱ�д�жϷ�������
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
	
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);                    //�������жϱ�־λ
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);                     //ʹ��TIM2����ж�    
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;	
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_Cmd(TIM2, ENABLE);
}

void TIM2_IRQHandler(void)//ÿ��10ms����һ���ж�
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)  
	{		
		SystemTimer++;//ȫ�ּ�ʱ�ı���+1,��ʾ��ȥ��10ms=0.01s
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
