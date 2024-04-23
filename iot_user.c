#include "iot_user.h"
#include "sys.h"


/*//下发数据的样式
命令:{"method":"thing.service.property.set","id":"1087087436","params":{"TempH":41},"version":"1.0.0"}
star_sp=params":{"TempH":41},"version":"1.0.0"}
star_sp+10=TempH":41},"version":"1.0.0"}  
end_sp=":41},"version":"1.0.0"}
*/
char *star_sp, *end_sp; //用于提取标识符
char identifier_temp[50];//用于存放标识符
int identifier_data;//用于存放下发的数据

/*-------------------------------------------------*/
/*功能：得到并处理下发的数据                       */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
void ITO_GetCmdData_Deal(void)
{
    u1_printf("命令:%s\r\n", &MQTT_CMDOutPtr[2]);                //串口输出信息
		star_sp =strstr((char *)MQTT_CMDOutPtr + 2, (char *)"params");
    if(star_sp == strstr((char *)MQTT_CMDOutPtr + 2, (char *)"params")) //app下发数据---定位得到标识符前面的字符 ，用于求出标识符有多大
    {		
        end_sp = strstr(star_sp + 10, "\":"); //定位得到标识符后面的字符 ，用于求出标识符有多大--加十是因为 params":{" 这一串字符长度为十
        memcpy(identifier_temp, star_sp + 10, (end_sp) - (star_sp + 10)); //将标识符提取
			
        identifier_data = Extract_digit((unsigned char *)end_sp + 2); //atoi（将字符串的数字变成整形的函数）得到下发的数据   +2是是因为 ":  这一串字符长度为十
					//data_sta(identifier_temp, identifier_data);
					//identifier_data云端下发的数据
					//identifier_temp云端下发的标识符
					//u1_printf("end_sp + 2:%s\r\n", end_sp + 2);                //串口输出信息
					//u1_printf("identifier_data + 2:%d\r\n", identifier_data );                //串口输出信息							

				//如果接收到了来自云端的数据 并且数据的标识为codata_hight 则将云端的数据赋值给程序中的存储数据的变量
				if(!(strcmp(identifier_temp, "fireup")))//CO上限   //如果
        {
            firedata_hight = identifier_data;
        }
				else if(!(strcmp(identifier_temp, "firedown")))//CO下限
        {
            firedata_low = identifier_data;
        }
				
        memset(identifier_temp, 0, 255);
    }


			if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"powerstate\":1}"))
			{	    //strstr函数是C语言中一个非常常用的字符串处理函数,它用于在一个字符串中查找另一个字符串的出现位置   	
				 LED1_On();//u1_printf("powerstate:1\r\n"); 
				 LED_Sta();
			}
			else if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"powerstate\":0}"))
			{   
				LED1_Off();//u1_printf("powerstate:0\r\n");
				LED_Sta();
			}
			
    MQTT_CMDOutPtr += CBUFF_UNIT;                             	 //指针下移
    if(MQTT_CMDOutPtr == MQTT_CMDEndPtr)           	           //如果指针到缓冲区尾部了
        MQTT_CMDOutPtr = MQTT_CMDBuf[0];          	             //指针归位到缓冲区开头
}
/*-------------------------------------------------*/
/*函数名：定时上传各种数据的任务                   */
/*参  数：无                                       */
/*返回值：无                                       */
/*-------------------------------------------------*/
//extern unsigned int SystemTimer ;


void Timed_Data_UpLoad(void)
{
	char temp[400];
	if((DHT11_flag == 0)&& (ConnectPack_flag == 1) && SystemTimer>100)
	{
		SystemTimer = 0;
		sprintf(temp,"{\"method\":\"thing.event.property.post\",\"id\":\"203302322\",\"params\":{\"firedata\":%d,\"fireup\":%d,\"firedown\":%d},\"version\":\"1.0.0\"}",AD_Value[0],firedata_hight,firedata_low);  //构建回复湿度温度数据
		Mqtt_PublishQs0Message_To_Buff(P_TOPIC_NAME,temp,strlen(temp));	
	}
}


/*--------------------------------------------*/
/*功能：立即发布灯的状态给服务器             */
/*参  数：需要提取的字符串                   */
/*返回值：提取出来的数字                     */
/*-------------------------------------------*/
void LED_Sta(void)
{
	char temp[400]; 
	if(strstr((char *)MQTT_CMDOutPtr+2,"\"params\":{\"powerstate\":1}"))//单片机 状态上报阿里云
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
/*功能：提取传入字符串的数字返回             */
/*参  数：需要提取的字符串                   */
/*返回值：提取出来的数字                     */
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
