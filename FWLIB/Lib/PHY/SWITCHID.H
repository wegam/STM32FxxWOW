
#ifndef __SWITCHID_H
#define __SWITCHID_H

#include "stm32f10x_gpio.h"

//HC165_CONF	HC165x_TEST;			//����ṹ�����



typedef struct _SWITCHID_DATA
{
	struct
	{
		unsigned long D0:1;
		unsigned long D1:1;
		unsigned long D2:1;
		unsigned long D3:1;
		unsigned long D4:1;
		unsigned long D5:1;
		unsigned long D6:1;
		unsigned long D7:1;
		unsigned long D8:1;
		unsigned long D9:1;
		unsigned long D10:1;
		unsigned long D11:1;
		unsigned long D12:1;
		unsigned long D13:1;
		unsigned long D14:1;
		unsigned long D15:1;
	}Data16;
	
}SWITCHID_DATA;			//���������ʱ����ز������������������в���ֵ

typedef struct _SWITCHID_CONF
{
	unsigned char	NumOfSW;											//�ӵİ��뿪��λ��,���16λ:����ʱ��Ҫ�������ӵİ��뿪��λ��
	//____________SW1
	GPIO_TypeDef* 	SW1_PORT;					//GPIOX
	unsigned short 	SW1_Pin;					//GPIO_Pin_x
	
	//____________SW2
	GPIO_TypeDef* 	SW2_PORT;					//GPIOX
	unsigned short 	SW2_Pin;					//GPIO_Pin_x
	
	//____________SW3
	GPIO_TypeDef* 	SW3_PORT;					//GPIOX
	unsigned short 	SW3_Pin;					//GPIO_Pin_x
	
	//____________SW4
	GPIO_TypeDef* 	SW4_PORT;					//GPIOX
	unsigned short 	SW4_Pin;					//GPIO_Pin_x
	
	//____________SW5
	GPIO_TypeDef* 	SW5_PORT;					//GPIOX
	unsigned short 	SW5_Pin;					//GPIO_Pin_x
	
	//____________SW6
	GPIO_TypeDef* 	SW6_PORT;					//GPIOX
	unsigned short 	SW6_Pin;					//GPIO_Pin_x
	
	//____________SW7
	GPIO_TypeDef* 	SW7_PORT;					//GPIOX
	unsigned short 	SW7_Pin;					//GPIO_Pin_x
	
	//____________SW8
	GPIO_TypeDef* 	SW8_PORT;					//GPIOX
	unsigned short 	SW8_Pin;					//GPIO_Pin_x
	
	//____________SW9
	GPIO_TypeDef* 	SW9_PORT;					//GPIOX
	unsigned short 	SW9_Pin;					//GPIO_Pin_x
	
	//____________SW10
	GPIO_TypeDef* 	SW10_PORT;					//GPIOX
	unsigned short 	SW10_Pin;					//GPIO_Pin_x
	
	//____________SW11
	GPIO_TypeDef* 	SW11_PORT;					//GPIOX
	unsigned short 	SW11_Pin;					//GPIO_Pin_x
	
	//____________SW12
	GPIO_TypeDef* 	SW12_PORT;					//GPIOX
	unsigned short 	SW12_Pin;					//GPIO_Pin_x
	
	//____________SW13
	GPIO_TypeDef* 	SW13_PORT;					//GPIOX
	unsigned short 	SW13_Pin;					//GPIO_Pin_x
	
	//____________SW14
	GPIO_TypeDef* 	SW14_PORT;					//GPIOX
	unsigned short 	SW14_Pin;					//GPIO_Pin_x
	
	//____________SW15
	GPIO_TypeDef* 	SW15_PORT;					//GPIOX
	unsigned short 	SW15_Pin;					//GPIO_Pin_x
	
	//____________SW16
	GPIO_TypeDef* 	SW16_PORT;					//GPIOX
	unsigned short 	SW16_Pin;					//GPIO_Pin_x
	
	SWITCHID_DATA		sID_Data16;				//�ṹ��λ��ʽ:��ȡ�İ��뿪��ֵ---����Ҫ����
	unsigned short	nID_Data16;				//������ֵ��ʽ:��ȡ�İ��뿪��ֵ---����Ҫ����
}SWITCHID_CONF;




void SWITCHIDConf(SWITCHID_CONF *SWITCHIDx);		//
unsigned long SWITCHIDRead(SWITCHID_CONF *SWITCHIDx);		//


#endif

