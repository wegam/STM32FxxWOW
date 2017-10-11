#ifndef __TM1618_H
#define __TM1618_H
#include "stm32f10x_gpio.h"



typedef enum
{
	TM1618_Cathode	=	0,			//���������
	TM1618_Anode							//���������
}SegPolarity_TypeDef;				//����ܼ���


typedef struct	_TM1618_Pin
{
	//DIO
	GPIO_TypeDef* 	TM1618_DIO_PORT;				//GPIOX
	unsigned short 	TM1618_DIO_Pin;				//GPIO_Pin_x
	
	//CLK
	GPIO_TypeDef* 	TM1618_CLK_PORT;				//GPIOX
	unsigned short 	TM1618_CLK_Pin;				//GPIO_Pin_x
	
	//STB
	GPIO_TypeDef* 	TM1618_STB_PORT;				//GPIOX
	unsigned short 	TM1618_STB_Pin;				//GPIO_Pin_x


}TM1618_Pindef;


void TM1618_PinConf(TM1618_Pindef *Pinfo);
void TM1618_WriteData(TM1618_Pindef *Pinfo,u16 Data);
void TM1618_WriteDataN(TM1618_Pindef *Pinfo,u16 Data);		//�����ź�д��


#endif
