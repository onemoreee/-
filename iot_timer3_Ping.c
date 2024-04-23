#include "iot_timer3_Ping.h"     //������Ҫ��ͷ�ļ�
#include "sys.h"
/*-------------------------------------------------*/
/*����������ʱ��3ʹ��30s��ʱ                       */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void TIM3_ENABLE_30S(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;            //����һ�����ö�ʱ���ı���
	NVIC_InitTypeDef NVIC_InitStructure;                          //����һ�������жϵı���
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);               //�����ж��������飺��2�� �������ȼ���0 1 2 3 �����ȼ���0 1 2 3		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);           //ʹ��TIM3ʱ��	
	TIM_DeInit(TIM3);                                             //��ʱ��3�Ĵ����ָ�Ĭ��ֵ	
	TIM_TimeBaseInitStructure.TIM_Period = 60000-1; 	          //�����Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=36000-1;              //���ö�ʱ��Ԥ��Ƶ��
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;     //1��Ƶ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);            //����TIM3
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);                    //�������жϱ�־λ
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                      //ʹ��TIM3����ж�    
	TIM_Cmd(TIM3,ENABLE);                                         //��TIM3                          
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;                 //����TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;       //��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;              //�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;                 //�ж�ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);                               //�����ж�
}
/*-------------------------------------------------*/
/*����������ʱ��3ʹ��2s��ʱ                        */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void TIM3_ENABLE_2S(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;            //����һ�����ö�ʱ���ı���
	NVIC_InitTypeDef NVIC_InitStructure;                          //����һ�������жϵı���
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);               //�����ж��������飺��2�� �������ȼ���0 1 2 3 �����ȼ���0 1 2 3		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);           //ʹ��TIM3ʱ��
	TIM_DeInit(TIM3);                                             //��ʱ��3�Ĵ����ָ�Ĭ��ֵ	
	TIM_TimeBaseInitStructure.TIM_Period = 20000-1; 	          //�����Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=7200-1;               //���ö�ʱ��Ԥ��Ƶ��
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;     //1��Ƶ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);            //����TIM3
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);                    //�������жϱ�־λ
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                      //ʹ��TIM3����ж�    
	TIM_Cmd(TIM3,ENABLE);                                         //��TIM3                          
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;                 //����TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;       //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0;              //�����ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;                 //�ж�ͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);                               //�����ж�
}
/*-------------------------------------------------*/
/*����������ʱ��3�жϷ�����                      */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{   //���TIM_IT_Update��λ����ʾTIM3����жϣ�����if	
		switch(Ping_flag)
		{                               //�ж�Ping_flag��״̬
			case 0:										 //���Ping_flag����0����ʾ����״̬������Ping����  
					Mqtt_PingMessage_To_Buff(); 					 //���Ping���ĵ����ͻ�����  
					break;
			case 1:										 //���Ping_flag����1��˵����һ�η��͵���ping���ģ�û���յ��������ظ�������1û�б����Ϊ0�������������쳣������Ҫ��������pingģʽ
			
					Mqtt_PingMessage_To_Buff();  					 //���Ping���ĵ����ͻ�����  
					break;
			case 2:			Mqtt_PingMessage_To_Buff();								break;	 //���Ping_flag����2��˵����û���յ��������ظ�
			case 3:			Mqtt_PingMessage_To_Buff();		            	break;             //���Ping_flag����3��˵����û���յ��������ظ�
			case 4:				TIM3_ENABLE_2S(); 					 //���ǽ���ʱ��6����Ϊ2s��ʱ,���ٷ���Ping����        //���Ping_flag����4��˵����û���յ��������ظ�	
					Mqtt_PingMessage_To_Buff();  					 //���Ping���ĵ����ͻ����� 
					break;
			case 5:										 //���Ping_flag����5��˵�����Ƿ����˶��ping�����޻ظ���Ӧ�������������⣬������������
					ConnectALi_flag = 0;                    //����״̬��0����ʾ�Ͽ���û���Ϸ�����
					TIM_Cmd(TIM3,DISABLE);               //��TIM3 				
					break;			
		}
		Ping_flag++;           		             		 //Ping_flag����1����ʾ�ַ�����һ��ping���ڴ��������Ļظ�
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);      //���TIM3����жϱ�־ 	
	}
}
