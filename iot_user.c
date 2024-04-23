#include "iot_user.h"
#include "sys.h"


/*//�·����ݵ���ʽ
����:{"method":"thing.service.property.set","id":"1087087436","params":{"TempH":41},"version":"1.0.0"}
star_sp=params":{"TempH":41},"version":"1.0.0"}
star_sp+10=TempH":41},"version":"1.0.0"}  
end_sp=":41},"version":"1.0.0"}
*/
char *star_sp, *end_sp; //������ȡ��ʶ��
char identifier_temp[50];//���ڴ�ű�ʶ��
int identifier_data;//���ڴ���·�������

/*-------------------------------------------------*/
/*���ܣ��õ��������·�������                       */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
void ITO_GetCmdData_Deal(void)
{
    u1_printf("����:%s\r\n", &MQTT_CMDOutPtr[2]);                //���������Ϣ
		star_sp =strstr((char *)MQTT_CMDOutPtr + 2, (char *)"params");
    if(star_sp == strstr((char *)MQTT_CMDOutPtr + 2, (char *)"params")) //app�·�����---��λ�õ���ʶ��ǰ����ַ� �����������ʶ���ж��
    {		
        end_sp = strstr(star_sp + 10, "\":"); //��λ�õ���ʶ��������ַ� �����������ʶ���ж��--��ʮ����Ϊ params":{" ��һ���ַ�����Ϊʮ
        memcpy(identifier_temp, star_sp + 10, (end_sp) - (star_sp + 10)); //����ʶ����ȡ
			
        identifier_data = Extract_digit((unsigned char *)end_sp + 2); //atoi�����ַ��������ֱ�����εĺ������õ��·�������   +2������Ϊ ":  ��һ���ַ�����Ϊʮ
					//data_sta(identifier_temp, identifier_data);
					//identifier_data�ƶ��·�������
					//identifier_temp�ƶ��·��ı�ʶ��
					//u1_printf("end_sp + 2:%s\r\n", end_sp + 2);                //���������Ϣ
					//u1_printf("identifier_data + 2:%d\r\n", identifier_data );                //���������Ϣ							

				//������յ��������ƶ˵����� �������ݵı�ʶΪcodata_hight ���ƶ˵����ݸ�ֵ�������еĴ洢���ݵı���
				if(!(strcmp(identifier_temp, "fireup")))//CO����   //���
        {
            firedata_hight = identifier_data;
        }
				else if(!(strcmp(identifier_temp, "firedown")))//CO����
        {
            firedata_low = identifier_data;
        }
				
        memset(identifier_temp, 0, 255);
    }


			if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"powerstate\":1}"))
			{	    //strstr������C������һ���ǳ����õ��ַ���������,��������һ���ַ����в�����һ���ַ����ĳ���λ��   	
				 LED1_On();//u1_printf("powerstate:1\r\n"); 
				 LED_Sta();
			}
			else if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"powerstate\":0}"))
			{   
				LED1_Off();//u1_printf("powerstate:0\r\n");
				LED_Sta();
			}
			
    MQTT_CMDOutPtr += CBUFF_UNIT;                             	 //ָ������
    if(MQTT_CMDOutPtr == MQTT_CMDEndPtr)           	           //���ָ�뵽������β����
        MQTT_CMDOutPtr = MQTT_CMDBuf[0];          	             //ָ���λ����������ͷ
}
/*-------------------------------------------------*/
/*����������ʱ�ϴ��������ݵ�����                   */
/*��  ������                                       */
/*����ֵ����                                       */
/*-------------------------------------------------*/
//extern unsigned int SystemTimer ;


void Timed_Data_UpLoad(void)
{
	char temp[400];
	if((DHT11_flag == 0)&& (ConnectPack_flag == 1) && SystemTimer>100)
	{
		SystemTimer = 0;
		sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"firedata\":%d,\"fireup\":%d,\"firedown\":%d},\"version\":\"1.0.0\"}",AD_Value[0],firedata_hight,firedata_low);  //�����ظ�ʪ���¶�����
		Mqtt_PublishQs0Message_To_Buff(P_TOPIC_NAME,temp,strlen(temp));	
	}
}


/*--------------------------------------------*/
/*���ܣ����������Ƶ�״̬��������             */
/*��  ������Ҫ��ȡ���ַ���                   */
/*����ֵ����ȡ����������                     */
/*-------------------------------------------*/
void LED_Sta(void)
{
	char temp[400]; 
	if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"powerstate\":1}"))//��Ƭ�� ״̬�ϱ�������
	{
		sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"powerstate\":1},\"version\":\"1.0.0\"}"); 	
	}
	else if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"powerstate\":0}")) 
	{		
		sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"powerstate\":0},\"version\":\"1.0.0\"}");  
	}
		Mqtt_PublishQs0Message_To_Buff(P_TOPIC_NAME,temp,strlen(temp)); 
}


/*--------------------------------------------*/
/*���ܣ���ȡ�����ַ��������ַ���             */
/*��  ������Ҫ��ȡ���ַ���                   */
/*����ֵ����ȡ����������                     */
/*-------------------------------------------*/
u32 Extract_digit(u8 *str)
{
	u32 num=0;
	while(*str>='0'&&*str<='9')
	{
		num+=(*str)-48;
		*str++;
		num*=10;

	}
	return num/10;
}
