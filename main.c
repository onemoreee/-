#include "sys.h"

u16 SystemTimer=0;//变量声明全局时间变量

/*DHT11全局变量*/
u8 DHT11_flag;//全局变量 接收读取DHT11的返回值 DHT11读取成功返回0
float temper;//全局变量最终的温度
float humi;//全局变量最终的湿度

//
//警报显示全局变量
u8 fire_alarmflag = 0;
u8 beep_mode = 0;

//开启WIFI标志
u8 wifi = 0;
int main(void)
{
	delay_init();						//延时函数初始化
	//调试交互相关
	My_USART1_Init();				//调试串口初始化	
	LED_GPIO_Config();			//开发板上LED灯
	KEY_GPIO_Init();				//按键初始化
	OLED_Init();						//OLED显示屏幕初始化
	//火焰、CO、烟雾传感器相关
  MY_ADC_Init();					//ADC初始化
	delay_ms(10);						//延时
	//上传云端相关
	WiFi_ResetIO_Init(); 		//WIFI复位引脚初始化
	AliIoT_Parameter_Init();//阿里云参数初始化
	while(1)			
	{		
		GUI_Refresh();//OLED显示刷新函数
		if(wifi == 1)
		{
			Connect_server();
		}	
		control_alarm();//判断传感器数值是否超过上下限
	}	
}

/*Stm32+Esp01s（MQTT）连接阿里云教程*/
//1.没有原理，只包含实际应用（想了解原理的，我觉得海创电子讲的挺好，可以去了解）
//2.包含：（视频演示）
//	上传数据到阿里云（将CO传感器采集的数据上传到云平台
//  接收阿里云下发的数据（通过阿里云平台设置火焰传感器上下限的值）
//  阿里云自带手机APP的制作

//前提：
//1.本代码已经获得了火焰传感器的数据存在AD_Value[0]变量里
//2.设置了火焰传感器上下限的值存在了firedata_low和firedata_hight变量里
//3.在control_alarm()函数中进行了是否超过限制的判断，如果超过上限fire_alarmflag这个标志位为1，不超过上下限fire_alarmflag标为位为0

//1.连接阿里云平台并创建手机APP

//2.将火焰传感器数据，火焰传感器上限数据，火焰传感器下限数据上传到阿里云并通过APP显示
/*
	阿里云是个浩瀚的空间，我们定义这个空间中，有存储火焰传感器数值的地方、有存储火焰上下限数据的地方，我们将这些地方定义标识名称，以方便我们能精准的找到
	上传数据的流程：
				上传到哪个地方（告诉阿里云标识名称）
				上传的数据是什么（将单片机中读取和设置的变量值上传）
*/

//3.能够接收来自APP的数据控制火焰传感器上下限的数值
/*
	下发数据：从阿里云平台收到数据，并解析是哪个标识的数据，并切将云端的值，赋值给单片机中的变量值
*/

