#ifndef __OLED_DATA_H
#define __OLED_DATA_H

#include <stdint.h>

/*中文字符字节宽度*/
#define OLED_CHN_CHAR_WIDTH			2		//UTF-8编码格式给3，GB2312编码格式给2

/*字模基本单元*/
typedef struct 
{
	char Index[OLED_CHN_CHAR_WIDTH + 1];	//汉字索引
	uint8_t Data[32];						//字模数据
} ChineseCell_t;

/*ASCII字模数据声明*/
extern const uint8_t OLED_F8x16[][16];
extern const uint8_t OLED_F6x8[][6];

/*汉字字模数据声明*/
extern const ChineseCell_t OLED_CF16x16[];

/*图像数据声明*/
extern const uint8_t Diode[];//二极管 
extern const uint8_t Signal_11x7[];//信号塔
extern const uint8_t Bat_16x8[];//电量
extern const uint8_t Menu_16x16[];///菜单
extern const uint8_t Lock_16x16[];//锁屏
extern const uint8_t wifi_16x16[]; //WIFI

extern const uint8_t Enter_16x16[];//确认
extern const uint8_t Back_16x16[];//返回
extern const uint8_t Right_16x16[];//右
extern const uint8_t Left_16x16[];//左


extern const uint8_t Info_48x48[];//关于信息
extern const uint8_t Setting_48x48[];//设置
extern const uint8_t Data_48x48[];//浏览器


/*按照上面的格式，在这个位置加入新的图像数据声明*/
//...

#endif


/*****************江协科技|版权所有****************/
/*****************jiangxiekeji.com*****************/
