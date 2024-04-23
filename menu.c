#include "sys.h"
#include "menu.h"
u8 wifipage_flag = 1;
static u8 func_index=0;//当前页面索引值
static u8 last_index=0;//上一个界面索引值
static void (*current_operation_func)(u8,u8);//定义一个函数指针
//索引表//加const存到flash中 节省SRAM内存
const Main_Menu table[30]=
{
	/*
		6个参数，分别为：
			- 第一个参数：当前界面的编号
			- 第二个参数：按下“上一页”按键执行的编号
			- 第三个参数：按下“下一页”按键执行的编号
			- 第四个参数：按下“确认“按键执行的编号
			- 第五个参数：按下“返回“按键执行的编号
			- 第六个参数：当前页面执行的函数（可以传递两个参数）
	*/	
	//锁屏界面
	{_Main_UI,_Main_UI,_Main_UI,_Wifi_Option,_OLED_Lock,Main_UI},

	//主菜单
	{_Wifi_Option,_Info_Option,_Setting_Option,_Wifi_Child,_Main_UI,Main_Menu_Func},//Wifi
	{_Setting_Option,_Wifi_Option,_Info_Option,_Setting_Child,_Main_UI,Main_Menu_Func},//设置
	{_Info_Option,_Setting_Option,_Wifi_Option,_Info_Child,_Main_UI,Main_Menu_Func},//关于信息
	
	//子菜单
	{_Wifi_Child,_Wifi_Child,_Wifi_Child,_Wifi_Child,_Wifi_Option,Wifi_Child},//Wifi子菜单
	{_Setting_Child,_Setting_Child,_Setting_Child,_Setting_Child,_Setting_Option,Setting_Child},//设置子菜单
	{_Info_Child,_Info_Child,_Info_Child,_Info_Child,_Info_Option,Info_Child},//关于信息子菜单
	
	{_OLED_Lock,_Main_UI,_Main_UI,_Main_UI,_Main_UI,OLED_Lock},//OLED熄屏
};




/*********************************************
* Function		:void Main_UI(u8 page_index,u8 key_val)
* Description	:显示锁屏界面
* Parameter		: void
* Return		: void
* Author		: firestaradmin
**********************************************/
void Main_UI(u8 page_index,u8 key_val)
{
	//首页的图片
	OLED_ShowImage(0,0,11,7,Signal_11x7);//左上信号塔
	OLED_ShowImage(112,0,16,8,Bat_16x8);//右上电池
	OLED_ShowImage(0,48,16,16,Menu_16x16);//左下菜单
	OLED_ShowImage(112,48,16,16,Lock_16x16);	//坐下锁屏
	//OLED_Update();
	//第一行汉字
//	OLED_ShowChinese(32,0,"确");
//	OLED_ShowChinese(48,0,"认");
//	OLED_ShowChinese(64,0,"解");
//	OLED_ShowChinese(80,0,"锁");
		OLED_ShowChinese(32,48,"确");
	OLED_ShowChinese(48,48,"认");
	OLED_ShowChinese(64,48,"解");
	OLED_ShowChinese(80,48,"锁");
	//OLED_Update();
	//第二行汉字
//	OLED_ShowChinese(0,16,"基");
//	OLED_ShowChinese(16,16,"于");
//	OLED_ShowString(32,16,"32",OLED_8X16);
//	OLED_ShowChinese(48,16,"和");
//	OLED_ShowString(64,16,"WIFI",OLED_8X16);
//	OLED_ShowChinese(96,16,"模");
//	OLED_ShowChinese(112,16,"块");
	OLED_ShowChinese(32,16,"欢");
	OLED_ShowChinese(48,16,"迎");
	OLED_ShowChinese(64,16,"使");
	OLED_ShowChinese(80,16,"用");
	//OLED_Update();
	//第三行汉字
	OLED_ShowChinese(0,32,"智");
	OLED_ShowChinese(16,32,"能");
	OLED_ShowChinese(32,32,"家");
	OLED_ShowChinese(48,32,"居");
	OLED_ShowChinese(64,32,"安");
	OLED_ShowChinese(80,32,"防");
	OLED_ShowChinese(96,32,"系");
	OLED_ShowChinese(112,32,"统");
	OLED_Update();
}

/*
函数功能：主菜单显示函数
参数：u8 page_index,u8 key_val
返回值：无
*/
void Main_Menu_Func(u8 page_index,u8 key_val)
{
	main_show_title(0);//显示智能植物养护系统
	OLED_ShowImage(16,28,16,16,Left_16x16);//显示左箭头
	OLED_ShowImage(96,28,16,16,Right_16x16);//显示右箭头
	OLED_ShowImage(0,48,16,16,Enter_16x16);//显示确定
	OLED_ShowImage(112,48,16,16,Back_16x16);//显示返回箭头
	OLED_Update();
	switch(page_index)
	{
		case _Wifi_Option:OLED_ShowImage(39,16,48,48,Data_48x48);OLED_Update();//显示数据浏览图标
						 break;
		case _Setting_Option:OLED_ShowImage(39,16,48,48,Setting_48x48);OLED_Update();//显示设置图标
						 break;
		case _Info_Option:OLED_ShowImage(39,16,48,48,Info_48x48);OLED_Update();//显示关于信息图标
						 break;
		default:break;
	}
}

void Wifi_Child(u8 page_index,u8 key_val)
{
	static u8 cur_pos=1;//记录按键当前位置
	
	if(last_index!=_Wifi_Option)//判断是否是第一次进入此界面
	{
		switch(key_val)
		{
			case KEY_PREVIOUS: /*wifipage_flag = 1;*/cur_pos==1?cur_pos=2:cur_pos--;//如果等于6 就重新=1 否则就--
					break;
			case KEY_ENTER: 
					break;									
			case KEY_NEXT:  /* wifipage_flag = 2;*/  cur_pos==2?cur_pos=1:cur_pos++;//如果等于6 就重新=1 否则就++
					break;
			default:break;
		}
	}
	else cur_pos=1;//第一次进入此界面,界面指针清零	
	//wifi = 1;
	//if(SubcribePack_flag == 1)
	//{
		if(cur_pos == 1)
		{	
			//显示连接WIIFI的图片
			wifi_show_title(0);//显示智能植物养护系统
			OLED_ShowImage(96,0,16,16,wifi_16x16);
			//第一页显示温度 温度
			OLED_ShowChinese(0,16,"温");
			OLED_ShowChinese(16,16,"度");
			OLED_ShowString(32,16,":     C",OLED_8X16);
			if(DHT11_flag == 0)
			{
				OLED_ShowFloatNum(40,16,temper_data,2,1,OLED_8X16);
			}
			OLED_ShowChinese(96,16,"正");
			OLED_ShowChinese(112,16,"常");
			OLED_ReverseArea(96,16,32,16);
			//第一页显示温度 湿度
			OLED_ShowChinese(0,32,"湿");
			OLED_ShowChinese(16,32,"度");
			OLED_ShowString(32,32,":     %",OLED_8X16);
			if(DHT11_flag == 0)
			{
				OLED_ShowFloatNum(40,32,humi_data,2,1,OLED_8X16);
			}
			OLED_ShowChinese(96,32,"正");
			OLED_ShowChinese(112,32,"常");
			OLED_ReverseArea(96,32,32,16);			
			//下一页
			OLED_ShowChinese(80,48,"下");
			OLED_ShowChinese(96,48,"一");
			OLED_ShowChinese(112,48,"页");
			OLED_DrawRectangle(80, 48, 48, 16, OLED_UNFILLED);
			OLED_Update();
			
		}else 
		{			
			//火焰AD_Value[0]
			OLED_ShowChinese(0,0,"火");
			OLED_ShowChinese(16,0,"焰");
			OLED_ShowString(32,0,":",OLED_8X16);		
			OLED_ShowNum(40,0,AD_Value[0],4,OLED_8X16);
			if(fire_alarmflag == 0)
			{
				OLED_ShowChinese(96,0,"正");
				OLED_ShowChinese(112,0,"常");
				Buzzer_Off();
			}else if(fire_alarmflag == 1)
			{
				OLED_ShowChinese(96,0,"过");
				OLED_ShowChinese(112,0,"高");	
				Buzzer_On();
			}else if(fire_alarmflag == 2)
			{
				OLED_ShowChinese(96,0,"过");
				OLED_ShowChinese(112,0,"低");
				Buzzer_On();
			}			
			OLED_ReverseArea(96,0,32,16);
			//烟雾AD_Value[1]
			OLED_ShowChinese(0,16,"烟");
			OLED_ShowChinese(16,16,"雾");
			OLED_ShowString(32,16,":",OLED_8X16);		
			OLED_ShowNum(40,16,AD_Value[1],4,OLED_8X16);
			OLED_ShowChinese(96,16,"正");
			OLED_ShowChinese(112,16,"常");
			OLED_ReverseArea(96,16,32,16);
			//气体AD_Value[2]
			OLED_ShowChinese(0,32,"气");
			OLED_ShowChinese(16,32,"体");
			OLED_ShowString(32,32,":",OLED_8X16);		
			OLED_ShowNum(40,32,AD_Value[2],4,OLED_8X16);
			OLED_ShowChinese(96,32,"过");
			OLED_ShowChinese(112,32,"高");
			OLED_ReverseArea(96,32,32,16);
			//上一页
			OLED_ShowChinese(80,48,"上");
			OLED_ShowChinese(96,48,"一");
			OLED_ShowChinese(112,48,"页");
			OLED_DrawRectangle(80, 48, 48, 16, OLED_UNFILLED);
			OLED_Update();		
		}	
//	}
}


u8 tempdata_hight=20;//空气温度上限变量
u8 tempdata_low=5;//空气温度下限变量
u8 humidata_hight=80;//空气湿度上限变量
u8 humidata_low=50;//空气湿度下限变量
u16 firedata_hight = 5000;
u16 firedata_low = 300;
u16 smokedata_hight = 500;
u16 smokedata_low = 300;
u16 codata_hight = 500;
u16 codata_low = 300;

u8 Mode = 1;
/*
函数功能：设置选项页
参数：u8 page_index,u8 key_val
返回值：无
*/
void Setting_Child(u8 page_index,u8 key_val)
{
	static u8 cur_pos=1;
	if(last_index!=_Setting_Option)//判断是否是第一次进入此界面
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
			//确定(设置)按键
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
	else cur_pos=1;//第一次进入此界面,界面指针清零
	if(cur_pos<=4)
	{	
		OLED_ShowChinese(0,0,"空");
		OLED_ShowChinese(16,0,"气");
		OLED_ShowChinese(32,0,"温");
		OLED_ShowChinese(48,0,"度");
		OLED_ShowChinese(64,0,"上");
		OLED_ShowChinese(80,0,"限");
		OLED_ShowString(96,0,":  C",OLED_8X16);
		OLED_ShowNum(104,0,tempdata_hight,2,OLED_8X16);
		
		OLED_ShowChinese(0,16,"空");
		OLED_ShowChinese(16,16,"气");
		OLED_ShowChinese(32,16,"温");
		OLED_ShowChinese(48,16,"度");
		OLED_ShowChinese(64,16,"下");
		OLED_ShowChinese(80,16,"限");
		OLED_ShowString(96,16,":  C",OLED_8X16);
		OLED_ShowNum(104,16,tempdata_low,2,OLED_8X16);
		
		OLED_ShowChinese(0,32,"空");
		OLED_ShowChinese(16,32,"气");
		OLED_ShowChinese(32,32,"湿");
		OLED_ShowChinese(48,32,"度");
		OLED_ShowChinese(64,32,"上");
		OLED_ShowChinese(80,32,"限");
		OLED_ShowString(96,32,":  %",OLED_8X16);
		OLED_ShowNum(104,32,humidata_hight,2,OLED_8X16);
		
		OLED_ShowChinese(0,48,"空");
		OLED_ShowChinese(16,48,"气");
		OLED_ShowChinese(32,48,"湿");
		OLED_ShowChinese(48,48,"度");
		OLED_ShowChinese(64,48,"下");
		OLED_ShowChinese(80,48,"限");
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
		OLED_ShowChinese(0,0,"火");
		OLED_ShowChinese(16,0,"焰");
		OLED_ShowChinese(32,0,"检");
		OLED_ShowChinese(48,0,"测");
		OLED_ShowChinese(64,0,"上");
		OLED_ShowChinese(80,0,"限");
		OLED_ShowNum(96,0,firedata_hight,4,OLED_8X16);

		
		OLED_ShowChinese(0,16,"火");
		OLED_ShowChinese(16,16,"焰");
		OLED_ShowChinese(32,16,"检");
		OLED_ShowChinese(48,16,"测");
		OLED_ShowChinese(64,16,"下");
		OLED_ShowChinese(80,16,"限");
		OLED_ShowNum(96,16,firedata_low,4,OLED_8X16);

		
		OLED_ShowChinese(0,32,"烟");
		OLED_ShowChinese(16,32,"雾");
		OLED_ShowChinese(32,32,"检");
		OLED_ShowChinese(48,32,"测");
		OLED_ShowChinese(64,32,"上");
		OLED_ShowChinese(80,32,"限");
		OLED_ShowNum(96,32,smokedata_hight,4,OLED_8X16);

		
		OLED_ShowChinese(0,48,"烟");
		OLED_ShowChinese(16,48,"雾");
		OLED_ShowChinese(32,48,"检");
		OLED_ShowChinese(48,48,"测");
		OLED_ShowChinese(64,48,"下");
		OLED_ShowChinese(80,48,"限");
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
		OLED_ShowChinese(0,0,"火");
		OLED_ShowChinese(16,0,"焰");
		OLED_ShowChinese(32,0,"检");
		OLED_ShowChinese(48,0,"测");
		OLED_ShowChinese(64,0,"上");
		OLED_ShowChinese(80,0,"限");
		OLED_ShowNum(96,0,codata_hight,4,OLED_8X16);
		
		OLED_ShowChinese(0,16,"火");
		OLED_ShowChinese(16,16,"焰");
		OLED_ShowChinese(32,16,"检");
		OLED_ShowChinese(48,16,"测");
		OLED_ShowChinese(64,16,"下");
		OLED_ShowChinese(80,16,"限");
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
	if(last_index!=_Info_Option)//判断是否是第一次进入此界面
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
	else cur_pos=1;//第一次进入此界面,界面指针清零
	
	if(cur_pos<=4)
	{
		wifi_show_title(0);//显示智能植物养护系统
		OLED_ShowImage(96,0,16,16,wifi_16x16);
		//WIFI 开关
		OLED_ShowChinese(0,16,"网");
		OLED_ShowChinese(16,16," ");
		OLED_ShowChinese(32,16,"络");
		OLED_ShowChinese(48,16,"状");
		OLED_ShowChinese(64,16,"态");
		OLED_ShowString(80,16,":",OLED_8X16);
		if(wifi_enter_flag == 2)
		{
			wifi = 1;
			OLED_ShowChinese(88,16,"开");
			OLED_ShowChinese(104,16,"启");			
		}else if(wifi_enter_flag == 1)
		{
			wifi = 0;
			OLED_ShowChinese(88,16,"关");
			OLED_ShowChinese(104,16,"闭");
		}
		OLED_ReverseArea(88,16,32,16);
		
		//LED 开关		
		OLED_ShowChinese(0,32,"警");
		OLED_ShowChinese(16,32,"示");
		OLED_ShowChinese(32,32,"灯");
		OLED_ShowChinese(48,32,"状");
		OLED_ShowChinese(64,32,"态");
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
			OLED_ShowChinese(88,32,"开");
			OLED_ShowChinese(104,32,"启");
		}else 
		{
			OLED_ShowChinese(88,32,"关");
			OLED_ShowChinese(104,32,"闭");	
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
函数功能：刷新界面
参数：无
返回值：无
*/
void GUI_Refresh(void)
{
	u8 key_val=KEY_Scan();//读取按键的键值
	if(key_val!=0)//只有按键按下才刷屏
	{
		last_index=func_index;//更新上一界面索引值
		switch(key_val)
		{
			case KEY_PREVIOUS: func_index=table[func_index].previous;//更新索引值
					break;
			case KEY_ENTER: func_index=table[func_index].enter;//更新索引值//按键enter按下后的索引号
					break;
			case KEY_NEXT:func_index=table[func_index].next;//更新索引值
					break;
			case KEY_BACK:func_index=table[func_index].back;//更新索引值
					break;
			default:break;
		}
		OLED_Clear();//清屏
		OLED_Update();
	}
	current_operation_func=table[func_index].current_operation;//执行当前索引号所对应的功能函数
	(*current_operation_func)(func_index,key_val);//执行当前索引对应的函数
}



/*  WIFI 调试OLED显示*/
void main_show_title(u8 line)//OLED显示:智能家居安防系统
{
	OLED_ShowChinese(0,line,"智");
	OLED_ShowChinese(16,line,"能");
	OLED_ShowChinese(32,line,"家");
	OLED_ShowChinese(48,line,"居");
	OLED_ShowChinese(64,line,"安");
	OLED_ShowChinese(80,line,"防");
	OLED_ShowChinese(96,line,"系");
	OLED_ShowChinese(112,line,"统");
	OLED_Update();
}

void wifi_show_title(u8 line)//OLED显示:数值显示
{

	OLED_ShowChinese(0,line,"智");
	OLED_ShowChinese(16,line,"能");
	OLED_ShowChinese(32,line,"家");
	OLED_ShowChinese(48,line,"居");
	OLED_Update();
}

