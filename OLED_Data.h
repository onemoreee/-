#ifndef __OLED_DATA_H
#define __OLED_DATA_H

#include <stdint.h>

/*�����ַ��ֽڿ��*/
#define OLED_CHN_CHAR_WIDTH			2		//UTF-8�����ʽ��3��GB2312�����ʽ��2

/*��ģ������Ԫ*/
typedef struct 
{
	char Index[OLED_CHN_CHAR_WIDTH + 1];	//��������
	uint8_t Data[32];						//��ģ����
} ChineseCell_t;

/*ASCII��ģ��������*/
extern const uint8_t OLED_F8x16[][16];
extern const uint8_t OLED_F6x8[][6];

/*������ģ��������*/
extern const ChineseCell_t OLED_CF16x16[];

/*ͼ����������*/
extern const uint8_t Diode[];//������ 
extern const uint8_t Signal_11x7[];//�ź���
extern const uint8_t Bat_16x8[];//����
extern const uint8_t Menu_16x16[];///�˵�
extern const uint8_t Lock_16x16[];//����
extern const uint8_t wifi_16x16[]; //WIFI

extern const uint8_t Enter_16x16[];//ȷ��
extern const uint8_t Back_16x16[];//����
extern const uint8_t Right_16x16[];//��
extern const uint8_t Left_16x16[];//��


extern const uint8_t Info_48x48[];//������Ϣ
extern const uint8_t Setting_48x48[];//����
extern const uint8_t Data_48x48[];//�����


/*��������ĸ�ʽ�������λ�ü����µ�ͼ����������*/
//...

#endif


/*****************��Э�Ƽ�|��Ȩ����****************/
/*****************jiangxiekeji.com*****************/
