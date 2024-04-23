#ifndef __MENU_H
#define __MENU_H
#include "sys.h"
typedef struct
{
	u8 Cur_Index;//��ǰ������
	u8 previous;//��һҳ
	u8 next;//��һҳ
	u8 enter;//ȷ��
	u8 back;//����
	void (*current_operation)(u8,u8);//	��ǰ����ִ�еĺ���(����)
}Main_Menu;

//�����������ֵ
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
//��������ֵ
enum
{
	KEY_PREVIOUS = 1,//��һ��
	KEY_NEXT,				//��һ��
	KEY_ENTER,			//ȷ��
	KEY_BACK 				//����
};



extern void Main_UI(u8 page_index,u8 key_val);//��ʾ��������
extern void Main_Menu_Func(u8 page_index,u8 key_val);//��ʾ���˵�
extern void Wifi_Child(u8 page_index,u8 key_val);//WIFI��ʾ����
extern void Setting_Child(u8 page_index,u8 key_val);//���ý���
extern void Info_Child(u8 page_index,u8 key_val);//���ƾ�����Ϣ״̬
void OLED_Lock(u8 page_index,u8 key_val);//����

extern void main_show_title(u8 line);//OLED��ʾ:���ܼҾӰ���ϵͳ
extern void wifi_show_title(u8 line);//OLED��ʾ:��ֵ��ʾ


extern void Data_Dispaly(u8 cur_pos);//WIFI ���ӳɹ��� ������ʾ����������
extern void GUI_Refresh(void);//����ˢ�º��� �������е���

//extern u8 wifipage_flag;




extern u8 tempdata_hight;//�����¶����ޱ���
extern u8 tempdata_low;//�����¶����ޱ���
extern u8 humidata_hight;//����ʪ�����ޱ���
extern u8 humidata_low;//����ʪ�����ޱ���
extern u16 firedata_hight;//���洫��������
extern u16 firedata_low;//���洫��������
extern u16 smokedata_hight;//������������
extern u16 smokedata_low;//������������
extern u16 codata_hight;//CO����������
extern u16 codata_low;//CO����������








#endif


