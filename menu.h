#ifndef __MENU_H
#define __MENU_H
#include "sys.h"
typedef struct
{
	u8 Cur_Index;//当前索引项
	u8 previous;//上一页
	u8 next;//下一页
	u8 enter;//确认
	u8 back;//返回
	void (*current_operation)(u8,u8);//	当前索引执行的函数(界面)
}Main_Menu;

//各界面的索引值
enum
{
	_Main_UI=0,
	_Wifi_Option,
	_Setting_Option,
	_Info_Option,
	_Wifi_Child,
	_Setting_Child,
	_Info_Child,
	_OLED_Lock,
};
//按键索引值
enum
{
	KEY_PREVIOUS = 1,//上一个
	KEY_NEXT,				//下一个
	KEY_ENTER,			//确认
	KEY_BACK 				//返回
};



extern void Main_UI(u8 page_index,u8 key_val);//显示锁屏界面
extern void Main_Menu_Func(u8 page_index,u8 key_val);//显示主菜单
extern void Wifi_Child(u8 page_index,u8 key_val);//WIFI显示界面
extern void Setting_Child(u8 page_index,u8 key_val);//设置界面
extern void Info_Child(u8 page_index,u8 key_val);//控制警报信息状态
void OLED_Lock(u8 page_index,u8 key_val);//锁屏

extern void main_show_title(u8 line);//OLED显示:智能家居安防系统
extern void wifi_show_title(u8 line);//OLED显示:数值显示


extern void Data_Dispaly(u8 cur_pos);//WIFI 连接成功后 用来显示和数量数据
extern void GUI_Refresh(void);//按键刷新函数 主函数中调用

//extern u8 wifipage_flag;




extern u8 tempdata_hight;//空气温度上限变量
extern u8 tempdata_low;//空气温度下限变量
extern u8 humidata_hight;//空气湿度上限变量
extern u8 humidata_low;//空气湿度下限变量
extern u16 firedata_hight;//火焰传感器上限
extern u16 firedata_low;//火焰传感器下限
extern u16 smokedata_hight;//烟雾传感器上限
extern u16 smokedata_low;//烟雾传感器下限
extern u16 codata_hight;//CO传感器上限
extern u16 codata_low;//CO传感器下限








#endif


