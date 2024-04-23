#ifndef __key_H__
#define __key_H__

#include "sys.h"

//#define KEY_GPIO_PIN   GPIO_Pin_15
//#define KEY_GPIO_PORT  GPIOB
//#define KEY_GPIO_CLK  RCC_APB2Periph_GPIOB

//void KEY_GPIO_Config(void);
//void KEY_Scan(void);
//extern u8 flag;



/*菜单按键定义*/
/*
key1 -- PB12
key2 -- PB13
key3 -- PB14
key4 -- PB15
*/
#define key1 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//--
#define key2 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)//++
#define key3 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//确认
#define key4 GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//选择


char KEY_Scan(void);
void KEY_GPIO_Init(void);


#endif


