
#include "sys.h"
void LED_AllOff(void);
void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);
	GPIO_InitStruct.GPIO_Pin = LED_GPIO_PIN1 | LED_GPIO_PIN2;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);	
	LED_AllOff();
}

void LED_AllOn(void)
{
	LED1_ON;
	LED2_ON;
}

void LED_AllOff(void)
{
	LED1_OFF;
	LED2_OFF;
}

void LED1_On(void)
{
	LED1_ON;
}

void LED1_Off(void)
{
	LED1_OFF;	
}

void LED2_On(void)
{
	LED2_ON;
}

void LED2_Off(void)
{
	LED2_OFF;	
}

//void LED_Sta(void)
//{
//	char temp[400]; 
//	if(strstr((char *)mqtt_CMDOutPtr+2,"\"params\":{\"powerstate\":1}"))
//	{
//		//单片机 状态上报阿里云
//		sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"powerstate\":1},\"version\":\"1.0.0\"}"); 	
//	}
//	else if(strstr((char *)mqtt_CMDOutPtr+2,"\"params\":{\"powerstate\":0}"))            
//		sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"powerstate\":0},\"version\":\"1.0.0\"}");  
//	Mqtt_PublishQs0Message_To_Buff(PUBLISH_TOPIC,temp,strlen(temp)); 
//}


