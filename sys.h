#ifndef __SYS_H
#define __SYS_H	

#include "stm32f10x.h"

/*sys系统文件*/
#include "delay.h"																    
#include "my_usart1.h"
#include "stdio.h"      
#include "stdarg.h"		
#include "string.h"
#include "time2.h"

/*应用层文件*/
#include "dht11.h"	
#include "oled.h"
#include "OLED_Data.h"
#include "led.h"
#include "menu.h"
#include "key.h"
#include "lock.h"
#include "adc.h"
#include "buzzer.h"
#include "control.h"

/* ITO需要用的头文件 */
#include "utils_hmac.h"
#include "utils_md5.h"
#include "utils_sha1.h"

#include "iot_timer3_Ping.h"
#include "iot_usart2.h"
#include "iot_user.h"
#include "iot_wifi_mqtt.h"



extern u16 SystemTimer;

/*DHT11全局变量*/
extern u8 DHT11_flag;//全局变量 接收读取DHT11的返回值 DHT11读取成功返回0
extern float temper;//全局变量最终的温度
extern float humi;//全局变量最终的湿度

//extern u8 temper;//全局变量最终的温度
//extern u8 humi;//全局变量最终的湿度


extern u8 wifi;

//全局变量 定义最终数据名称
#define temper_data  temper
#define humi_data  humi
#define fire_data  AD_Value[0]
#define smoke_data  AD_Value[1]
#define co_data  AD_Value[2]
#define APP_fire_alarmflag   "fire_alarmflag"//空气温度下限
//全局变量 
extern u8 fire_alarmflag;//火焰警告标志位
extern u8 beep_mode;//报警模式是否启动


void NVIC_Config(void);
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//IO口操作,只对单一的IO口!

#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入


#endif
