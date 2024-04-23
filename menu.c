#include "sys.h"
#include "menu.h"
u8 wifipage_flag = 1;
static u8 func_index=0;//��ǰҳ������ֵ
static u8 last_index=0;//��һ����������ֵ
static void (*current_operation_func)(u8,u8);//����һ������ָ��
//������//��const�浽flash�� ��ʡSRAM�ڴ�
const Main_Menu table[30]=
{
	/*
		6���������ֱ�Ϊ��
			- ��һ����������ǰ����ı��
			- �ڶ������������¡���һҳ������ִ�еı��
			- ���������������¡���һҳ������ִ�еı��
			- ���ĸ����������¡�ȷ�ϡ�����ִ�еı��
			- ��������������¡����ء�����ִ�еı��
			- ��������������ǰҳ��ִ�еĺ��������Դ�������������
	*/	
	//��������
	{_Main_UI,_Main_UI,_Main_UI,_Wifi_Option,_OLED_Lock,Main_UI},

	//���˵�
	{_Wifi_Option,_Info_Option,_Setting_Option,_Wifi_Child,_Main_UI,Main_Menu_Func},//Wifi
	{_Setting_Option,_Wifi_Option,_Info_Option,_Setting_Child,_Main_UI,Main_Menu_Func},//����
	{_Info_Option,_Setting_Option,_Wifi_Option,_Info_Child,_Main_UI,Main_Menu_Func},//������Ϣ
	
	//�Ӳ˵�
	{_Wifi_Child,_Wifi_Child,_Wifi_Child,_Wifi_Child,_Wifi_Option,Wifi_Child},//Wifi�Ӳ˵�
	{_Setting_Child,_Setting_Child,_Setting_Child,_Setting_Child,_Setting_Option,Setting_Child},//�����Ӳ˵�
	{_Info_Child,_Info_Child,_Info_Child,_Info_Child,_Info_Option,Info_Child},//������Ϣ�Ӳ˵�
	
	{_OLED_Lock,_Main_UI,_Main_UI,_Main_UI,_Main_UI,OLED_Lock},//OLEDϨ��
};




/*********************************************
* Function		:void Main_UI(u8 page_index,u8 key_val)
* Description	:��ʾ��������
* Parameter		: void
* Return		: void
* Author		: firestaradmin
**********************************************/
void Main_UI(u8 page_index,u8 key_val)
{
	//��ҳ��ͼƬ
	OLED_ShowImage(0,0,11,7,Signal_11x7);//�����ź���
	OLED_ShowImage(112,0,16,8,Bat_16x8);//���ϵ��
	OLED_ShowImage(0,48,16,16,Menu_16x16);//���²˵�
	OLED_ShowImage(112,48,16,16,Lock_16x16);	//��������
	//OLED_Update();
	//��һ�к���
//	OLED_ShowChinese(32,0,"ȷ");
//	OLED_ShowChinese(48,0,"��");
//	OLED_ShowChinese(64,0,"��");
//	OLED_ShowChinese(80,0,"��");
		OLED_ShowChinese(32,48,"ȷ");
	OLED_ShowChinese(48,48,"��");
	OLED_ShowChinese(64,48,"��");
	OLED_ShowChinese(80,48,"��");
	//OLED_Update();
	//�ڶ��к���
//	OLED_ShowChinese(0,16,"��");
//	OLED_ShowChinese(16,16,"��");
//	OLED_ShowString(32,16,"32",OLED_8X16);
//	OLED_ShowChinese(48,16,"��");
//	OLED_ShowString(64,16,"WIFI",OLED_8X16);
//	OLED_ShowChinese(96,16,"ģ");
//	OLED_ShowChinese(112,16,"��");
	OLED_ShowChinese(32,16,"��");
	OLED_ShowChinese(48,16,"ӭ");
	OLED_ShowChinese(64,16,"ʹ");
	OLED_ShowChinese(80,16,"��");
	//OLED_Update();
	//�����к���
	OLED_ShowChinese(0,32,"��");
	OLED_ShowChinese(16,32,"��");
	OLED_ShowChinese(32,32,"��");
	OLED_ShowChinese(48,32,"��");
	OLED_ShowChinese(64,32,"��");
	OLED_ShowChinese(80,32,"��");
	OLED_ShowChinese(96,32,"ϵ");
	OLED_ShowChinese(112,32,"ͳ");
	OLED_Update();
}

/*
�������ܣ����˵���ʾ����
������u8 page_index,u8 key_val
����ֵ����
*/
void Main_Menu_Func(u8 page_index,u8 key_val)
{
	main_show_title(0);//��ʾ����ֲ������ϵͳ
	OLED_ShowImage(16,28,16,16,Left_16x16);//��ʾ���ͷ
	OLED_ShowImage(96,28,16,16,Right_16x16);//��ʾ�Ҽ�ͷ
	OLED_ShowImage(0,48,16,16,Enter_16x16);//��ʾȷ��
	OLED_ShowImage(112,48,16,16,Back_16x16);//��ʾ���ؼ�ͷ
	OLED_Update();
	switch(page_index)
	{
		case _Wifi_Option:OLED_ShowImage(39,16,48,48,Data_48x48);OLED_Update();//��ʾ�������ͼ��
						 break;
		case _Setting_Option:OLED_ShowImage(39,16,48,48,Setting_48x48);OLED_Update();//��ʾ����ͼ��
						 break;
		case _Info_Option:OLED_ShowImage(39,16,48,48,Info_48x48);OLED_Update();//��ʾ������Ϣͼ��
						 break;
		default:break;
	}
}

void Wifi_Child(u8 page_index,u8 key_val)
{
	static u8 cur_pos=1;//��¼������ǰλ��
	
	if(last_index!=_Wifi_Option)//�ж��Ƿ��ǵ�һ�ν���˽���
	{
		switch(key_val)
		{
			case KEY_PREVIOUS: /*wifipage_flag = 1;*/cur_pos==1?cur_pos=2:cur_pos--;//�������6 ������=1 �����--
					break;
			case KEY_ENTER: 
					break;									
			case KEY_NEXT:  /* wifipage_flag = 2;*/  cur_pos==2?cur_pos=1:cur_pos++;//�������6 ������=1 �����++
					break;
			default:break;
		}
	}
	else cur_pos=1;//��һ�ν���˽���,����ָ������	
	//wifi = 1;
	//if(SubcribePack_flag == 1)
	//{
		if(cur_pos == 1)
		{	
			//��ʾ����WIIFI��ͼƬ
			wifi_show_title(0);//��ʾ����ֲ������ϵͳ
			OLED_ShowImage(96,0,16,16,wifi_16x16);
			//��һҳ��ʾ�¶� �¶�
			OLED_ShowChinese(0,16,"��");
			OLED_ShowChinese(16,16,"��");
			OLED_ShowString(32,16,":     C",OLED_8X16);
			if(DHT11_flag == 0)
			{
				OLED_ShowFloatNum(40,16,temper_data,2,1,OLED_8X16);
			}
			OLED_ShowChinese(96,16,"��");
			OLED_ShowChinese(112,16,"��");
			OLED_ReverseArea(96,16,32,16);
			//��һҳ��ʾ�¶� ʪ��
			OLED_ShowChinese(0,32,"ʪ");
			OLED_ShowChinese(16,32,"��");
			OLED_ShowString(32,32,":     %",OLED_8X16);
			if(DHT11_flag == 0)
			{
				OLED_ShowFloatNum(40,32,humi_data,2,1,OLED_8X16);
			}
			OLED_ShowChinese(96,32,"��");
			OLED_ShowChinese(112,32,"��");
			OLED_ReverseArea(96,32,32,16);			
			//��һҳ
			OLED_ShowChinese(80,48,"��");
			OLED_ShowChinese(96,48,"һ");
			OLED_ShowChinese(112,48,"ҳ");
			OLED_DrawRectangle(80, 48, 48, 16, OLED_UNFILLED);
			OLED_Update();
			
		}else 
		{			
			//����AD_Value[0]
			OLED_ShowChinese(0,0,"��");
			OLED_ShowChinese(16,0,"��");
			OLED_ShowString(32,0,":",OLED_8X16);		
			OLED_ShowNum(40,0,AD_Value[0],4,OLED_8X16);
			if(fire_alarmflag == 0)
			{
				OLED_ShowChinese(96,0,"��");
				OLED_ShowChinese(112,0,"��");
				Buzzer_Off();
			}else if(fire_alarmflag == 1)
			{
				OLED_ShowChinese(96,0,"��");
				OLED_ShowChinese(112,0,"��");	
				Buzzer_On();
			}else if(fire_alarmflag == 2)
			{
				OLED_ShowChinese(96,0,"��");
				OLED_ShowChinese(112,0,"��");
				Buzzer_On();
			}			
			OLED_ReverseArea(96,0,32,16);
			//����AD_Value[1]
			OLED_ShowChinese(0,16,"��");
			OLED_ShowChinese(16,16,"��");
			OLED_ShowString(32,16,":",OLED_8X16);		
			OLED_ShowNum(40,16,AD_Value[1],4,OLED_8X16);
			OLED_ShowChinese(96,16,"��");
			OLED_ShowChinese(112,16,"��");
			OLED_ReverseArea(96,16,32,16);
			//����AD_Value[2]
			OLED_ShowChinese(0,32,"��");
			OLED_ShowChinese(16,32,"��");
			OLED_ShowString(32,32,":",OLED_8X16);		
			OLED_ShowNum(40,32,AD_Value[2],4,OLED_8X16);
			OLED_ShowChinese(96,32,"��");
			OLED_ShowChinese(112,32,"��");
			OLED_ReverseArea(96,32,32,16);
			//��һҳ
			OLED_ShowChinese(80,48,"��");
			OLED_ShowChinese(96,48,"һ");
			OLED_ShowChinese(112,48,"ҳ");
			OLED_DrawRectangle(80, 48, 48, 16, OLED_UNFILLED);
			OLED_Update();		
		}	
//	}
}


u8 tempdata_hight=20;//�����¶����ޱ���
u8 tempdata_low=5;//�����¶����ޱ���
u8 humidata_hight=80;//����ʪ�����ޱ���
u8 humidata_low=50;//����ʪ�����ޱ���
u16 firedata_hight = 5000;
u16 firedata_low = 300;
u16 smokedata_hight = 500;
u16 smokedata_low = 300;
u16 codata_hight = 500;
u16 codata_low = 300;

u8 Mode = 1;
/*
�������ܣ�����ѡ��ҳ
������u8 page_index,u8 key_val
����ֵ����
*/
void Setting_Child(u8 page_index,u8 key_val)
{
	static u8 cur_pos=1;
	if(last_index!=_Setting_Option)//�ж��Ƿ��ǵ�һ�ν���˽���
	{
		switch(key_val)
		{
			case KEY_PREVIOUS:
			{
				switch(cur_pos)
				{
					case 1:if(Mode==1) tempdata_hight==20?tempdata_hight=20:tempdata_hight++;
							break;
					case 2:if(Mode==1) tempdata_low==tempdata_hight?tempdata_low=tempdata_hight:tempdata_low++;
							break;
					case 3:if(Mode==1) humidata_hight==50?humidata_hight=50:humidata_hight++;
							break;
					case 4:if(Mode==1) humidata_low==humidata_hight?humidata_low=humidata_hight:humidata_low++;
							break;
					case 5:if(Mode==1) firedata_hight==3000?firedata_hight=3000:firedata_hight++;
							break;
					case 6:if(Mode==1) firedata_low==firedata_hight?firedata_low=firedata_hight:firedata_low++;
							break;
					case 7:if(Mode==1) smokedata_hight==500?smokedata_hight=500:smokedata_hight++;
							break;
					case 8:if(Mode==1) smokedata_low==smokedata_hight?smokedata_low=smokedata_hight:smokedata_low++;
							break;
					case 9:if(Mode==1) codata_hight==500?codata_hight=500:codata_hight++;
							break;
					case 10:if(Mode==1) codata_low==codata_hight?codata_low=codata_hight:codata_low++;
							break;					
					default:break;
				}
			}
			break;
			//ȷ��(����)����
			case KEY_ENTER:cur_pos==10?cur_pos=1:cur_pos++;
			break;
			case KEY_NEXT:
			{
				switch(cur_pos)
				{
					case 1:if(Mode==1) tempdata_hight==tempdata_low?tempdata_hight=tempdata_low:tempdata_hight--;
							break;
					case 2:if(Mode==1) tempdata_low==1?tempdata_low=1:tempdata_low--;
							break;
					case 3:if(Mode==1) humidata_hight==humidata_low?humidata_hight=humidata_low:humidata_hight--;
							break;
					case 4:if(Mode==1) humidata_low==1?humidata_low=1:humidata_low--;
							break;
					case 5:if(Mode==1) firedata_hight==firedata_low?firedata_hight=firedata_low:firedata_hight--;
							break;
					case 6:if(Mode==1) firedata_low==1?firedata_low=1:firedata_low--;
							break;					
					case 7:if(Mode==1) smokedata_hight==smokedata_low?smokedata_hight=smokedata_low:smokedata_hight--;
							break;
					case 8:if(Mode==1) smokedata_low==1?smokedata_low=1:smokedata_low--;
							break;	
					case 9:if(Mode==1) codata_hight==codata_low?codata_hight=codata_low:codata_hight--;
							break;
					case 10:if(Mode==1) codata_low==1?codata_low=1:codata_low--;
							break;							
					default:break;
				}
			}
			break;
			case KEY_BACK:
			break;
			default:break;
		}
	}
	else cur_pos=1;//��һ�ν���˽���,����ָ������
	if(cur_pos<=4)
	{	
		OLED_ShowChinese(0,0,"��");
		OLED_ShowChinese(16,0,"��");
		OLED_ShowChinese(32,0,"��");
		OLED_ShowChinese(48,0,"��");
		OLED_ShowChinese(64,0,"��");
		OLED_ShowChinese(80,0,"��");
		OLED_ShowString(96,0,":  C",OLED_8X16);
		OLED_ShowNum(104,0,tempdata_hight,2,OLED_8X16);
		
		OLED_ShowChinese(0,16,"��");
		OLED_ShowChinese(16,16,"��");
		OLED_ShowChinese(32,16,"��");
		OLED_ShowChinese(48,16,"��");
		OLED_ShowChinese(64,16,"��");
		OLED_ShowChinese(80,16,"��");
		OLED_ShowString(96,16,":  C",OLED_8X16);
		OLED_ShowNum(104,16,tempdata_low,2,OLED_8X16);
		
		OLED_ShowChinese(0,32,"��");
		OLED_ShowChinese(16,32,"��");
		OLED_ShowChinese(32,32,"ʪ");
		OLED_ShowChinese(48,32,"��");
		OLED_ShowChinese(64,32,"��");
		OLED_ShowChinese(80,32,"��");
		OLED_ShowString(96,32,":  %",OLED_8X16);
		OLED_ShowNum(104,32,humidata_hight,2,OLED_8X16);
		
		OLED_ShowChinese(0,48,"��");
		OLED_ShowChinese(16,48,"��");
		OLED_ShowChinese(32,48,"ʪ");
		OLED_ShowChinese(48,48,"��");
		OLED_ShowChinese(64,48,"��");
		OLED_ShowChinese(80,48,"��");
		OLED_ShowString(96,48,":  %",OLED_8X16);
		OLED_ShowNum(104,48,humidata_low,2,OLED_8X16);
		switch(cur_pos)
		{
			case 1: OLED_ReverseArea(0,0,96,16);break;
			case 2:	OLED_ReverseArea(0,16,96,16);break;
			case 3: OLED_ReverseArea(0,32,96,16);break;
			case 4:	OLED_ReverseArea(0,48,96,16);break;
			default:break;
		}
		OLED_Update();
	}
	else if(cur_pos<=8)
	{
		OLED_ShowChinese(0,0,"��");
		OLED_ShowChinese(16,0,"��");
		OLED_ShowChinese(32,0,"��");
		OLED_ShowChinese(48,0,"��");
		OLED_ShowChinese(64,0,"��");
		OLED_ShowChinese(80,0,"��");
		OLED_ShowNum(96,0,firedata_hight,4,OLED_8X16);

		
		OLED_ShowChinese(0,16,"��");
		OLED_ShowChinese(16,16,"��");
		OLED_ShowChinese(32,16,"��");
		OLED_ShowChinese(48,16,"��");
		OLED_ShowChinese(64,16,"��");
		OLED_ShowChinese(80,16,"��");
		OLED_ShowNum(96,16,firedata_low,4,OLED_8X16);

		
		OLED_ShowChinese(0,32,"��");
		OLED_ShowChinese(16,32,"��");
		OLED_ShowChinese(32,32,"��");
		OLED_ShowChinese(48,32,"��");
		OLED_ShowChinese(64,32,"��");
		OLED_ShowChinese(80,32,"��");
		OLED_ShowNum(96,32,smokedata_hight,4,OLED_8X16);

		
		OLED_ShowChinese(0,48,"��");
		OLED_ShowChinese(16,48,"��");
		OLED_ShowChinese(32,48,"��");
		OLED_ShowChinese(48,48,"��");
		OLED_ShowChinese(64,48,"��");
		OLED_ShowChinese(80,48,"��");
		OLED_ShowNum(96,48,smokedata_low,4,OLED_8X16);
		switch(cur_pos)
		{
			case 5: OLED_ReverseArea(0,0,96,16);break;
			case 6:	OLED_ReverseArea(0,16,96,16);break;
			case 7: OLED_ReverseArea(0,32,96,16);break;
			case 8:	OLED_ReverseArea(0,48,96,16);break;
			default:break;
		}
		OLED_Update();
	}else if(cur_pos<=10)
	{
		OLED_ShowChinese(0,0,"��");
		OLED_ShowChinese(16,0,"��");
		OLED_ShowChinese(32,0,"��");
		OLED_ShowChinese(48,0,"��");
		OLED_ShowChinese(64,0,"��");
		OLED_ShowChinese(80,0,"��");
		OLED_ShowNum(96,0,codata_hight,4,OLED_8X16);
		
		OLED_ShowChinese(0,16,"��");
		OLED_ShowChinese(16,16,"��");
		OLED_ShowChinese(32,16,"��");
		OLED_ShowChinese(48,16,"��");
		OLED_ShowChinese(64,16,"��");
		OLED_ShowChinese(80,16,"��");
		OLED_ShowNum(96,16,codata_low,4,OLED_8X16);
		switch(cur_pos)
		{
			case 9: OLED_ReverseArea(0,0,96,16);break;
			case 10:	OLED_ReverseArea(0,16,96,16);break;
			default:break;
		}
		OLED_Update();
	
	}

}


void Info_Child(u8 page_index,u8 key_val)
{
	static u8 cur_pos=1;
	static u8 led_enter_flag=1;
	static u8 wifi_enter_flag = 1;
	if(last_index!=_Info_Option)//�ж��Ƿ��ǵ�һ�ν���˽���
	{
		switch(key_val)
		{
			case KEY_PREVIOUS:cur_pos==1?cur_pos=4:cur_pos--;
					break;
			case KEY_ENTER: 
			{
				switch(cur_pos)
				{
					case 1:
						wifi_enter_flag == 2?wifi_enter_flag=1:wifi_enter_flag++;
					break;
					case 2:
						led_enter_flag == 2?led_enter_flag=1:led_enter_flag++;
					break;				
				}
				
				
			}
					break;									
			case KEY_NEXT:cur_pos==4?cur_pos=1:cur_pos++;
					break;
			default:break;
		}
	}
	else cur_pos=1;//��һ�ν���˽���,����ָ������
	
	if(cur_pos<=4)
	{
		wifi_show_title(0);//��ʾ����ֲ������ϵͳ
		OLED_ShowImage(96,0,16,16,wifi_16x16);
		//WIFI ����
		OLED_ShowChinese(0,16,"��");
		OLED_ShowChinese(16,16," ");
		OLED_ShowChinese(32,16,"��");
		OLED_ShowChinese(48,16,"״");
		OLED_ShowChinese(64,16,"̬");
		OLED_ShowString(80,16,":",OLED_8X16);
		if(wifi_enter_flag == 2)
		{
			wifi = 1;
			OLED_ShowChinese(88,16,"��");
			OLED_ShowChinese(104,16,"��");			
		}else if(wifi_enter_flag == 1)
		{
			wifi = 0;
			OLED_ShowChinese(88,16,"��");
			OLED_ShowChinese(104,16,"��");
		}
		OLED_ReverseArea(88,16,32,16);
		
		//LED ����		
		OLED_ShowChinese(0,32,"��");
		OLED_ShowChinese(16,32,"ʾ");
		OLED_ShowChinese(32,32,"��");
		OLED_ShowChinese(48,32,"״");
		OLED_ShowChinese(64,32,"̬");
		OLED_ShowString(80,32,":",OLED_8X16);
//		if(led_enter_flag == 2)
//		{
//			LED1_On();
//		}else if(led_enter_flag == 1)
//		{
//			LED1_Off();
//		}
		if(PCin(13) == 0)
		{
			OLED_ShowChinese(88,32,"��");
			OLED_ShowChinese(104,32,"��");
		}else 
		{
			OLED_ShowChinese(88,32,"��");
			OLED_ShowChinese(104,32,"��");	
		}
		OLED_ReverseArea(88,32,32,16);
		
		
		switch(cur_pos)
		{
			case 1: OLED_DrawRectangle(0, 16, 128, 16, OLED_UNFILLED);break;
			case 2:	OLED_DrawRectangle(0, 32, 128, 16, OLED_UNFILLED);break;
			default:break;
		}
		
		
		
		OLED_Update();	
	}	
}






void OLED_Lock(u8 page_index,u8 key_val)
{
	OLED_Clear();
}


/*
�������ܣ�ˢ�½���
��������
����ֵ����
*/
void GUI_Refresh(void)
{
	u8 key_val=KEY_Scan();//��ȡ�����ļ�ֵ
	if(key_val!=0)//ֻ�а������²�ˢ��
	{
		last_index=func_index;//������һ��������ֵ
		switch(key_val)
		{
			case KEY_PREVIOUS: func_index=table[func_index].previous;//��������ֵ
					break;
			case KEY_ENTER: func_index=table[func_index].enter;//��������ֵ//����enter���º��������
					break;
			case KEY_NEXT:func_index=table[func_index].next;//��������ֵ
					break;
			case KEY_BACK:func_index=table[func_index].back;//��������ֵ
					break;
			default:break;
		}
		OLED_Clear();//����
		OLED_Update();
	}
	current_operation_func=table[func_index].current_operation;//ִ�е�ǰ����������Ӧ�Ĺ��ܺ���
	(*current_operation_func)(func_index,key_val);//ִ�е�ǰ������Ӧ�ĺ���
}



/*  WIFI ����OLED��ʾ*/
void main_show_title(u8 line)//OLED��ʾ:���ܼҾӰ���ϵͳ
{
	OLED_ShowChinese(0,line,"��");
	OLED_ShowChinese(16,line,"��");
	OLED_ShowChinese(32,line,"��");
	OLED_ShowChinese(48,line,"��");
	OLED_ShowChinese(64,line,"��");
	OLED_ShowChinese(80,line,"��");
	OLED_ShowChinese(96,line,"ϵ");
	OLED_ShowChinese(112,line,"ͳ");
	OLED_Update();
}

void wifi_show_title(u8 line)//OLED��ʾ:��ֵ��ʾ
{

	OLED_ShowChinese(0,line,"��");
	OLED_ShowChinese(16,line,"��");
	OLED_ShowChinese(32,line,"��");
	OLED_ShowChinese(48,line,"��");
	OLED_Update();
}

