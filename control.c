#include "control.h"
#include "sys.h"

/*********************************************
* Function		:void control_alarm(void)
* Description	:�жϸ��ִ������Ƿ񳬹��涨����ֵ
* Parameter		: void
* Return		: void
* Author		: 
**********************************************/

void control_alarm(void)
{
	//�������洫������ֵ����
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
		//��������������ֵ����...
	
		//�����¶ȴ�������ֵ����...
		
		//����CO��������ֵ����...
}
