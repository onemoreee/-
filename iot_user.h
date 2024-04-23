#ifndef __ITO_USER_H
#define __ITO_USER_H
#include "sys.h"  //包含需要的头文件



//	u8 tempdata_hight=20;//空气温度上限变量
//u8 tempdata_low=5;//空气温度下限变量
//u8 humidata_hight=80;//空气湿度上限变量
//u8 humidata_low=50;//空气湿度下限变量
//u16 firedata_hight = 3000;
//u16 firedata_low = 80;
//u16 smokedata_hight = 500;
//u16 smokedata_low = 300;
//u16 codata_hight = 500;
//u16 codata_low = 300;






#define APP_tem_up   "tempdata_hight"//空气温度上限 
#define APP_tem_down   "tempdata_low"//空气温度下限
#define APP_humi_up   "humidata_hight"//空气湿度上限
#define APP_humi_down   "humidata_low"//空气湿度下限
#define APP_fire_up   "firedata_hight"//火焰上限
#define APP_fire_down   "firedata_low"//火焰下限
#define APP_smoke_up   "smokedata_hight"//烟雾限
#define APP_smoke_down   "smokedata_low"//烟雾下限
#define APP_co_up   "codata_hight"//CO上限
#define APP_co_down   "codata_low"//CO下限



//#define APP_soil_down   "soil_down"//土壤湿度下限
//#define APP_soil_up   "soil_up"//土壤湿度上限
/*-  bool型值*/
//#define APP_tem_alarm   "tem_alarm"//空气温度报警
//#define APP_hum_alarm   "hum_alarm"//空气湿度报警
//#define APP_soil_alarm  	"soil_alarm"//土壤湿度报警 bool型
////																					开 关
//#define APP_FAN  	"FAN"//风扇
//#define APP_WATER  	"WATER"//水泵
//#define APP_tem  	"tem"//空气温度
//#define APP_humi  	"humi"//空气湿度
//#define APP_soil  	"soil"//土壤湿度
//#define APP_auto_flag  	"auto_flag"//自动模式


//extern unsigned int SystemTimer,SystemTimer2,SystemTimer3,SystemTimer4,SystemTimer5,SystemTimer6;   //用于全局计时的变量           单位秒
//extern unsigned int TEHUTimer,TEHUTimer2,TEHUTimer3,TEHUTimer4,TEHUTimer5,TEHUTimer6 ;     //用于温湿度采集的计时的变量   单位秒







void LED_Sta(void);

void Timed_Data_UpLoad(void);//定时上传任务

void data_sta(void *str, int cmd);//发布开关的状态给服务器 

void data_init(void);

//extern int flagtime;
u32 Extract_digit(u8 *str);
void data_sta_str(void *str, int cmd);
void judge_data_sta(void *str, uint16_t GPIO_Pin);//发布判断开关的状态给服务器  
void Data_send_ito_now(void *str, int cmd);
#endif



