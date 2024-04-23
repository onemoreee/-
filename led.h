#ifndef __LED_H__
#define __LED_H__

#include "sys.h"

#define LED_GPIO_PIN1   GPIO_Pin_13
#define LED_GPIO_PIN2   GPIO_Pin_8
#define LED_GPIO_PORT  GPIOC
#define LED_GPIO_CLK  RCC_APB2Periph_GPIOC

#define LED1_ON       GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN1)         
#define LED1_OFF      GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN1)           

#define LED2_ON       GPIO_ResetBits(LED_GPIO_PORT, LED_GPIO_PIN2)         
#define LED2_OFF      GPIO_SetBits(LED_GPIO_PORT, LED_GPIO_PIN2)           

void LED_AllOn(void);	
void LED_AllOff(void);
extern void LED1_On(void);
extern void LED1_Off(void);
void LED2_On(void);
void LED2_Off(void);
//void LED_Sta(void);

void LED_GPIO_Config(void);


#endif


