#include "control.h"
#include "sys.h"

/*********************************************
* Function		:void control_alarm(void)
* Description	:判断各种传感器是否超过规定的阈值
* Parameter		: void
* Return		: void
* Author		: 
**********************************************/

void control_alarm(void)
{
	//超过火焰传感器阈值警报
		if((fire_data > firedata_low)&&(fire_data < firedata_hight)&&(beep_mode==0))
		{
			fire_alarmflag = 0;
		}else if((fire_data>firedata_hight)&&(beep_mode==0))
		{
			fire_alarmflag = 1;			

		}else if((fire_data<firedata_low)&&(beep_mode==0))
		{
			fire_alarmflag = 2;		
		}
		//超过烟雾传感器阈值警报...
	
		//超过温度传感器阈值警报...
		
		//超过CO传感器阈值警报...
}
