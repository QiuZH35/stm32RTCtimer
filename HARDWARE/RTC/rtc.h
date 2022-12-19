#ifndef __RTC_H
#define __RTC_H	    
#include "sys.h"
#include "delay.h"
#include "OLED_I2C.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_rtc.h"

//ʱ��ṹ��
typedef struct 
{
	char hour;
	char min;
	char sec;			
	//������������
	short w_year;
	char  w_month;
	char w_date;
	char  week;		 
}_calendar_obj;					 
extern _calendar_obj calendar;	//�����ṹ��

extern u8 const mon_table[12];	//�·��������ݱ�
void Disp_Time(u8 x,u8 y,u8 size);//���ƶ�λ�ÿ�ʼ��ʾʱ��
void Disp_Week(u8 x,u8 y,u8 size,u8 lang);//��ָ��λ����ʾ����
u8 RTC_Init(void);        //��ʼ��RTC,����0,ʧ��;1,�ɹ�;
u8 Is_Leap_Year(u16 year);//ƽ��,�����ж�
u8 RTC_Alarm_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);
u8 RTC_Get(void);         //����ʱ��   
u8 RTC_Get_Week(u16 year,u8 month,u8 day);
u8 RTC_Set(u16 syear,u8 smon,u8 sday,u8 hour,u8 min,u8 sec);//����ʱ��
void eunm();
void show();
#endif

