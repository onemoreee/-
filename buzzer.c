#include "buzzer.h"
#include "sys.h"
void Buzzer_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef GPIOInitStruct;
	
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_11;
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIOInitStruct);
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,Bit_SET);
}
void Buzzer_On(void)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,Bit_RESET);
}

void Buzzer_Off(void)
{
	GPIO_WriteBit(GPIOB,GPIO_Pin_11,Bit_SET);
}




