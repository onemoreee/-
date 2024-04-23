#include "lock.h"
#include "sys.h"

//int lock_index = 0;//索引值 输入的位数
//char user_pwd[]="1144";	
//char pwd_Ram[4] = "----";	

//char Lock_judge(void)
//{
//		char key;
//		//char lock_flag = 4;
//		key = KEY_Scan();		
//		if(key)
//		{
//			pwd_Ram[lock_index] = key;						
//			OLED_ShowString(32+lock_index*8,32,"*",OLED_8X16);
//			OLED_Update();			
//			lock_index++;
//			if(lock_index>=4)
//			{			
//				for(lock_index = 0; lock_index <4 ;lock_index++)
//				{
//					if(pwd_Ram[lock_index] != user_pwd[lock_index])
//					{
//						//密码错误
//						OLED_Clear();
//						OLED_Update();
//						OLED_ShowString(0,0,"PIN ERROR     ",OLED_8X16);
//						OLED_Update();
//						delay_ms(3000);
//						return 1;
//					}
//				}
//				//密码正确
//				OLED_Clear();
//				OLED_Update();
//				//OLED_ShowString(0,0,"PIN RIGHT      ",OLED_8X16);
//				//OLED_Update();
//				//delay_ms(5000);		
//				return  0;				
//			}
//		}
//		return 2;
//		
//}


/*main*/
//loop:
//	for(lock_index = 0;lock_index<4;lock_index++) 
//	{
//		pwd_Ram[lock_index] = '-';	
//	}
//	lock_index = 0;
//	
//	OLED_ShowString(0,0,"Please enter",OLED_8X16);
//	OLED_ShowString(32,32,"----",OLED_8X16);
//	OLED_Update();

/*while*/

//		if(Lock_judge() ==1 )//密码错误就重输入
//		{
//			goto loop;
//		}
//		if(Lock_judge() ==0)//密码正确就显示
//		{
//			delay_ms(10);
//			menu2 = menu1();
//			if(menu2==1) menu2_1();      //二级菜单 - 手势识别
//			if(menu2==2) menu2_2();
//			if(menu2==3) goto loop;
//		}
	
