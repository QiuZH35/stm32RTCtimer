/*

���߶��壺
		VCC--5V
		RXD--PB10
		TXD--PB11
		GND--GND
*/
#include "sys.h"
#include "delay.h"
#include "stdio.h"
#include "usart.h"
#include "syn6288.h"
#include "rtc.h"
#include "OLED_I2C.h"
#include "key.h"

extern _calendar_obj calendar;
char time[30]={0};
char date[20]={0};
void showWeek(u8 year,u8 month,u8 date);
void oledShow();

/**************оƬ��������*********************/
u8 SYN_StopCom[] = {0xFD, 0X00, 0X02, 0X02, 0XFD}; //ֹͣ�ϳ�
u8 SYN_SuspendCom[] = {0XFD, 0X00, 0X02, 0X03, 0XFC}; //��ͣ�ϳ�
u8 SYN_RecoverCom[] = {0XFD, 0X00, 0X02, 0X04, 0XFB}; //�ָ��ϳ�
u8 SYN_ChackCom[] = {0XFD, 0X00, 0X02, 0X21, 0XDE}; //״̬��ѯ
u8 SYN_PowerDownCom[] = {0XFD, 0X00, 0X02, 0X88, 0X77}; //����POWER DOWN ״̬����

int main(void)
{
	//uart_init(9600);
	u8 key = 0;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();
	USART3_Init(9600);
	RTC_Init();
	KEY_Init();

	I2C_Configuration();
	OLED_Init();
	OLED_CLS();
	eunm();

	while(1)
	{
		
		//��ͣ�ϳɣ���ʱû���õ�������չʾ�����÷�
		//YS_SYN_Set(SYN_SuspendCom);
		oledShow();
		SYN_FrameInfo(2, date);
		SYN_FrameInfo(2, time);
	}
}
void oledShow()
{
	
	sprintf(time,"%d-%d-%d",calendar.w_year,calendar.w_month,calendar.w_date);
		sprintf(date,"%d:%d:%d",calendar.hour,calendar.min,calendar.sec);
		if(calendar.sec<10)
		{
				sprintf(date,"%d:%d:0%d",calendar.hour,calendar.min,calendar.sec);
		}
		if(calendar.min<10)
		{
			sprintf(date,"%d:0%d:%d",calendar.hour,calendar.min,calendar.sec);
			if(calendar.sec<10)
			{
				sprintf(date,"%d:0%d:0%d",calendar.hour,calendar.min,calendar.sec);
			}
			
		}
		if(calendar.hour<10)
		{
			sprintf(date,"0%d:%d:%d",calendar.hour,calendar.min,calendar.sec);

			
			if(calendar.min<10)
			{
				sprintf(date,"0%d:0%d:%d",calendar.hour,calendar.min,calendar.sec);
				if(calendar.sec<10)
				{
					sprintf(date,"0%d:0%d:0%d",calendar.hour,calendar.min,calendar.sec);
				}
			}else
			if(calendar.sec<10)
				{
					sprintf(date,"0%d:%d:0%d",calendar.hour,calendar.min,calendar.sec);
				}
		}
		
		showWeek(calendar.w_year,calendar.w_month,calendar.w_date);
		OLED_ShowStr(30,2,time,1);
		OLED_ShowStr(30,4,date,1);
}

void showWeek(u8 year,u8 month,u8 date)
{
	switch ( RTC_Get_Week( year,month, date ) )
	{
		case 0:
		OLED_ShowStr(30,3,"Sunday",1);  
			break;
		case 1:
		
			OLED_ShowStr(30,3,"Monday",1);  
			break;
		case 2:
			
				OLED_ShowStr(30,3,"Tuesday",1);  
			break;
		case 3:
			
		OLED_ShowStr(30,3,"Wednesday",1);  
			break;
		case 4:
			
		OLED_ShowStr(30,3,"Thursday",1);  
			break;
		case 5:
		
		OLED_ShowStr(30,3,"Friday",1);  
			break;
		case 6:

		OLED_ShowStr(30,3,"Saturday",1);  
			break;
	}

	
	
}
