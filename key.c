#include "key.h"
#include "sys.h"
#include "delay.h"


u8 key_value = 0;

void KEY_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIOInitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOB, &GPIOInitStruct);	
}


/*菜单按键定义*/
/*
key1 -- PB12
key2 -- PB13
key3 -- PB14
key4 -- PB15
*/

char KEY_Scan(void)
{
	u8 key_value = 0;
	if(PBin(12) == 0)
	{
		delay_ms(5);
		if(PBin(12) == 0)
		{
			key_value = 1;
		}
		while(!PBin(12));

	}
	if(PBin(13) == 0)
	{
		delay_ms(5);
		if(PBin(13) == 0)
		{
			key_value = 2;
		}
		while(!PBin(13));

	}
	if(PBin(14) == 0)
	{
		delay_ms(5);
		if(PBin(14) == 0)
		{
			key_value = 3;
		}
		while(!PBin(14));
	}	
	if(PBin(15) == 0)
	{
		delay_ms(5);
		if(PBin(15) == 0)
		{
			key_value =4;
		}
		while(!PBin(15));
	}
	return key_value;
}




////void EXTI3_IRQHandler(void)//选择按键
////{
////    Delay_Ms(10);//消抖
////    if(!KEY0_IN_STA)
////    {
////        switch(screen_num)
////        {
////        case 0://主界面
////            screen_choose++;
////            screen_choose %= 3;
////            break;
////        case 2://限值选择界面
////            switch(admin_screen_page)
////            {
////            case 1://第一个界面
////                if(admin_choose < 4)
////                    admin_choose++;
////                else admin_choose = 0;
////                break;
////            case 2://第二个界面
////                if(admin_choose < 8)
////                    admin_choose++;
////                else admin_choose = 5;
////                break;
////            }
////            break;
////        case 3://开关控制界面
////            pwr_choose++;
////            pwr_choose %= 3;
////            break;
////        case 5://报警界面
////            choose_fan_admin = !choose_fan_admin;
////            break;
////        }
////    }
////    EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE5上的中断标志位
////}
