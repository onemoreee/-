#ifndef __ITO_USER_H
#define __ITO_USER_H
#include "sys.h"  //������Ҫ��ͷ�ļ�



//	u8 tempdata_hight=20;//�����¶����ޱ���
//u8 tempdata_low=5;//�����¶����ޱ���
//u8 humidata_hight=80;//����ʪ�����ޱ���
//u8 humidata_low=50;//����ʪ�����ޱ���
//u16 firedata_hight = 3000;
//u16 firedata_low = 80;
//u16 smokedata_hight = 500;
//u16 smokedata_low = 300;
//u16 codata_hight = 500;
//u16 codata_low = 300;






#define APP_tem_up   "tempdata_hight"//�����¶����� 
#define APP_tem_down   "tempdata_low"//�����¶�����
#define APP_humi_up   "humidata_hight"//����ʪ������
#define APP_humi_down   "humidata_low"//����ʪ������
#define APP_fire_up   "firedata_hight"//��������
#define APP_fire_down   "firedata_low"//��������
#define APP_smoke_up   "smokedata_hight"//������
#define APP_smoke_down   "smokedata_low"//��������
#define APP_co_up   "codata_hight"//CO����
#define APP_co_down   "codata_low"//CO����



//#define APP_soil_down   "soil_down"//����ʪ������
//#define APP_soil_up   "soil_up"//����ʪ������
/*-  bool��ֵ*/
//#define APP_tem_alarm   "tem_alarm"//�����¶ȱ���
//#define APP_hum_alarm   "hum_alarm"//����ʪ�ȱ���
//#define APP_soil_alarm  	"soil_alarm"//����ʪ�ȱ��� bool��
////																					�� ��
//#define APP_FAN  	"FAN"//����
//#define APP_WATER  	"WATER"//ˮ��
//#define APP_tem  	"tem"//�����¶�
//#define APP_humi  	"humi"//����ʪ��
//#define APP_soil  	"soil"//����ʪ��
//#define APP_auto_flag  	"auto_flag"//�Զ�ģʽ


//extern unsigned int SystemTimer,SystemTimer2,SystemTimer3,SystemTimer4,SystemTimer5,SystemTimer6;   //����ȫ�ּ�ʱ�ı���           ��λ��
//extern unsigned int TEHUTimer,TEHUTimer2,TEHUTimer3,TEHUTimer4,TEHUTimer5,TEHUTimer6 ;     //������ʪ�Ȳɼ��ļ�ʱ�ı���   ��λ��







void LED_Sta(void);

void Timed_Data_UpLoad(void);//��ʱ�ϴ�����

void data_sta(void *str, int cmd);//�������ص�״̬�������� 

void data_init(void);

//extern int flagtime;
u32 Extract_digit(u8 *str);
void data_sta_str(void *str, int cmd);
void judge_data_sta(void *str, uint16_t GPIO_Pin);//�����жϿ��ص�״̬��������  
void Data_send_ito_now(void *str, int cmd);
#endif



