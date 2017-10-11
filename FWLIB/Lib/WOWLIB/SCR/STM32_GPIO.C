/******************************** User_library *********************************
* �ļ��� 	: STM32_SDCard.H
* ����   	: wegam@sina.com
* �汾   	: V
* ����   	: 2016/01/01
* ˵��   	: 
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/


#include "STM32_GPIO.H"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_type.h"
#include "stm32f10x_conf.h"
#include "stm32f10x_map.h"

#include "STM32F10x_BitBand.H"
//#include "stm32f10x_gpio.h"
//#include "STM32F10x_BitBand.H"


/*******************************************************************************
* ������		:	GPIO_ClockCmd	
* ��������	:	�������GPIO�˿�ʱ��	 
* ����		:	GPIOx��GPIOA~GPIOG
						GPIO_Pin_x:GPIO_Pin_0~GPIO_Pin_15;GPIO_Pin_All---����IO��Ҫ�ض���ӿ�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_ClockConf(GPIO_TypeDef* GPIOx,						//GPIO�˿�			
										u16 GPIO_Pin_x									//GPIO����
										)		//�������GPIOʱ��	 
{
	assert_param(IS_GPIO_ALL_PERIPH(GPIOx)); 
	switch (*(u32*)&GPIOx)
	{
		//********************GPIOAʱ��ʹ��********************	
		case GPIOA_BASE:
//			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			if((GPIO_Pin_x==GPIO_Pin_13)||(GPIO_Pin_x==GPIO_Pin_14)||(GPIO_Pin_x==GPIO_Pin_15)||(GPIO_Pin_x==GPIO_Pin_All))
			{
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE);
				//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);			//�ر�SW����
				GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);		//�ر�JTAG,SW���ܿ���
			}
			else
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			break;
		//********************GPIOBʱ��ʹ��********************
		case GPIOB_BASE:
			if((GPIO_Pin_x&&GPIO_Pin_3==GPIO_Pin_3)||(GPIO_Pin_x&&GPIO_Pin_4==GPIO_Pin_4)||(GPIO_Pin_x==GPIO_Pin_All))
			{
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
				GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);				//�ر�JTAG
			}
			else
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
			break;
		//********************GPIOCʱ��ʹ��********************
		case GPIOC_BASE:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
			if((GPIO_Pin_x==GPIO_Pin_14)||(GPIO_Pin_x==GPIO_Pin_15))
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC |RCC_APB2Periph_AFIO, ENABLE);
			break;
		//********************GPIODʱ��ʹ��********************
		case GPIOD_BASE:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
			break;
		//********************GPIOEʱ��ʹ��********************
		case GPIOE_BASE:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
			break;
		//********************GPIOFʱ��ʹ��********************
		case GPIOF_BASE:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
			break;
		//********************GPIOGʱ��ʹ��********************
		case GPIOG_BASE:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);
			break;
		
		default: break;
		
	}

}

/*******************************************************************************
* ������		:	GPIO_DeInitAll
* ��������	:	�����е�GPIO�ر�----V20170605
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_DeInitAll(void)
{
	//1��GPIO�ṹ�嶨��
	GPIO_InitTypeDef	GPIO_InitStructure;
	//2����ʼ��GPIO�ṹ��
	GPIO_StructInit(&GPIO_InitStructure);			//GPIO_Pin_All��GPIO_Speed_2MHz��GPIO_Mode_IN_FLOATING
	//3����ʼ��GPIOΪĬ��״̬
	GPIO_Init(GPIOA,&GPIO_InitStructure);			//GPIOA
	GPIO_Init(GPIOB,&GPIO_InitStructure);			//GPIOB
	GPIO_Init(GPIOC,&GPIO_InitStructure);			//GPIOC
	GPIO_Init(GPIOD,&GPIO_InitStructure);			//GPIOD
	GPIO_Init(GPIOE,&GPIO_InitStructure);			//GPIOE
	GPIO_Init(GPIOF,&GPIO_InitStructure);			//GPIOF
	GPIO_Init(GPIOG,&GPIO_InitStructure);			//GPIOG
	//4���ر�GPIOʱ��
	GPIO_DeInit(GPIOA);												//GPIOA
	GPIO_DeInit(GPIOB);												//GPIOB
	GPIO_DeInit(GPIOC);												//GPIOC
	GPIO_DeInit(GPIOD);												//GPIOD
	GPIO_DeInit(GPIOE);												//GPIOE
	GPIO_DeInit(GPIOF);												//GPIOF
	GPIO_DeInit(GPIOG);												//GPIOG
	//4���ر�AFIO
	GPIO_AFIODeInit();												//AFIO�ر�	
}
/*******************************************************************************
* ������		:	GPIO_Configuration
* ��������	:	GPIO���� 
* ����		:	GPIOx��GPIOA~GPIOG
						GPIO_Pin_x:GPIO_Pin_0~GPIO_Pin_15;GPIO_Pin_All
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Configuration(GPIO_TypeDef* GPIOx,					//GPIO�˿�
												u16 GPIO_Pin_x,								//GPIO����
												GPIOMode_TypeDef GPIO_Mode,		//����ģʽ
												GPIOSpeed_TypeDef GPIO_Speed	//�����ٶ�
												)			//GPIO����	
{	
	switch(GPIO_Mode)
	{
		//����ģʽ
		case GPIO_Mode_AIN:					GPIO_Configuration_INA(GPIOx,GPIO_Pin_x);			//��GPIO��Ӧ�ܽ�����Ϊģ������ģʽ----V20170605
					break;
		case GPIO_Mode_IN_FLOATING:	GPIO_Configuration_INF(GPIOx,GPIO_Pin_x);			//��GPIO��Ӧ�ܽ�����Ϊģ������ģʽ----V20170605
					break;
		case GPIO_Mode_IPD:					GPIO_Configuration_IPD(GPIOx,GPIO_Pin_x);			//��GPIO��Ӧ�ܽ�����Ϊģ������ģʽ----V20170605
					break;
		case GPIO_Mode_IPU:					GPIO_Configuration_IPU(GPIOx,GPIO_Pin_x);			//��GPIO��Ӧ�ܽ�����Ϊģ������ģʽ----V20170605
					break;
		//���ģʽ
		case GPIO_Mode_Out_OD:	
					switch(GPIO_Speed)
					{
						case GPIO_Speed_10MHz:	GPIO_Configuration_OOD10	(GPIOx,GPIO_Pin_x);			//��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�2MHz----V20170605
									break;
						case GPIO_Speed_2MHz: 	GPIO_Configuration_OOD2		(GPIOx,GPIO_Pin_x);			//��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�2MHz----V20170605
									break;
						case GPIO_Speed_50MHz: 	GPIO_Configuration_OOD50	(GPIOx,GPIO_Pin_x);			//��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�2MHz----V20170605
									break;
						default : break;
					}
					break;
		case GPIO_Mode_Out_PP:
					switch(GPIO_Speed)
					{
						case GPIO_Speed_10MHz: 	GPIO_Configuration_OPP10	(GPIOx,GPIO_Pin_x);			//��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�2MHz----V20170605
									break;
						case GPIO_Speed_2MHz: 	GPIO_Configuration_OPP2		(GPIOx,GPIO_Pin_x);			//��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�2MHz----V20170605
									break;
						case GPIO_Speed_50MHz: 	GPIO_Configuration_OPP50	(GPIOx,GPIO_Pin_x);			//��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�2MHz----V20170605
									break;
						default : break;
					}
					break;
		case GPIO_Mode_AF_OD:
					switch(GPIO_Speed)
					{
						case GPIO_Speed_10MHz: 	GPIO_Configuration_AOD10	(GPIOx,GPIO_Pin_x);			//��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�2MHz----V20170605
									break;
						case GPIO_Speed_2MHz: 	GPIO_Configuration_AOD2		(GPIOx,GPIO_Pin_x);			//��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�2MHz----V20170605
									break;
						case GPIO_Speed_50MHz: 	GPIO_Configuration_AOD50	(GPIOx,GPIO_Pin_x);			//��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�2MHz----V20170605
									break;
						default : break;
					}
					break;
		case GPIO_Mode_AF_PP:
					switch(GPIO_Speed)
					{
						case GPIO_Speed_10MHz: 	GPIO_Configuration_APP10	(GPIOx,GPIO_Pin_x);			//��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�2MHz----V20170605
									break;
						case GPIO_Speed_2MHz: 	GPIO_Configuration_APP2		(GPIOx,GPIO_Pin_x);			//��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�2MHz----V20170605
									break;
						case GPIO_Speed_50MHz: 	GPIO_Configuration_APP50	(GPIOx,GPIO_Pin_x);			//��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�2MHz----V20170605
									break;
						default : break;
					}
					break;		
		default :	break;
	}
}
/*******************************************************************************
* ������		:	GPIO_InitStructure_INA
* ��������	:	��GPIO��Ӧ�ܽ�����Ϊģ������ģʽ----V20170605
* ����		:	GPIOx--GPIO�˿ڣ�GPIO_Pin_n--GPIO�ܽź�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Configuration_INA(
														GPIO_TypeDef* GPIOx,		//GPIO�˿�,x=A/B/C/D/E/F/G
														u16 GPIO_Pin_n					//GPIO�ܽź�n=0~15/All
														)
{
	//1��GPIO�ṹ�嶨��
	GPIO_InitTypeDef	GPIO_InitStructure;
	//2����ʼ��GPIO�ṹ��
  GPIO_InitStructure.GPIO_Pin  		= GPIO_Pin_n;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;		//����ģʽ��ʱ��������Ч
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_AIN;			//ģ������ģʽ
	//3)����GPIO�˿ڼ��ܽźſ����˿�ʱ�Ӽ�ȷ���Ƿ��AFIOʱ��
	GPIO_ClockConf(GPIOx,GPIO_Pin_n);
	//4����ʼ��GPIO
	GPIO_Init(GPIOx,&GPIO_InitStructure);			//GPIOA
}
/*******************************************************************************
* ������		:	GPIO_InitStructure_INF
* ��������	:	��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
* ����		:	GPIOx--GPIO�˿ڣ�GPIO_Pin_n--GPIO�ܽź�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Configuration_INF(
														GPIO_TypeDef* GPIOx,							//GPIO�˿�,x=A/B/C/D/E/F/G
														u16 GPIO_Pin_n										//GPIO�ܽź�n=0~15/All
														)
{
	//1��GPIO�ṹ�嶨��
	GPIO_InitTypeDef	GPIO_InitStructure;
	//2����ʼ��GPIO�ṹ��
	GPIO_InitStructure.GPIO_Pin  		= GPIO_Pin_n;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;					//����ģʽ��ʱ��������Ч
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_IN_FLOATING;		//��������ģʽ
	//3)����GPIO�˿ڼ��ܽźſ����˿�ʱ�Ӽ�ȷ���Ƿ��AFIOʱ��
	GPIO_ClockConf(GPIOx,GPIO_Pin_n);
	//3����ʼ��GPIO
	GPIO_Init(GPIOx,&GPIO_InitStructure);			//GPIOA	
}
/*******************************************************************************
* ������		:	GPIO_Configuration_IPD
* ��������	:	��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
* ����		:	GPIOx--GPIO�˿ڣ�GPIO_Pin_n--GPIO�ܽź�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Configuration_IPD(
														GPIO_TypeDef* GPIOx,							//GPIO�˿�,x=A/B/C/D/E/F/G
														u16 GPIO_Pin_n										//GPIO�ܽź�n=0~15/All
														)
{
	//1��GPIO�ṹ�嶨��
	GPIO_InitTypeDef	GPIO_InitStructure;
	//2����ʼ��GPIO�ṹ��
	GPIO_InitStructure.GPIO_Pin  		= GPIO_Pin_n;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;					//����ģʽ��ʱ��������Ч
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_IPD;						//��������ģʽ
	//3)����GPIO�˿ڼ��ܽźſ����˿�ʱ�Ӽ�ȷ���Ƿ��AFIOʱ��
	GPIO_ClockConf(GPIOx,GPIO_Pin_n);
	//3����ʼ��GPIO
	GPIO_Init(GPIOx,&GPIO_InitStructure);			//GPIOA	
}
/*******************************************************************************
* ������		:	GPIO_Configuration_IPU
* ��������	:	��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
* ����		:	GPIOx--GPIO�˿ڣ�GPIO_Pin_n--GPIO�ܽź�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Configuration_IPU(
														GPIO_TypeDef* GPIOx,							//GPIO�˿�,x=A/B/C/D/E/F/G
														u16 GPIO_Pin_n										//GPIO�ܽź�n=0~15/All
														)
{
	//1��GPIO�ṹ�嶨��
	GPIO_InitTypeDef	GPIO_InitStructure;
	//2����ʼ��GPIO�ṹ��
	GPIO_InitStructure.GPIO_Pin  		= GPIO_Pin_n;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;					//����ģʽ��ʱ��������Ч
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_IPU;						//��������ģʽ
	//3)����GPIO�˿ڼ��ܽźſ����˿�ʱ�Ӽ�ȷ���Ƿ��AFIOʱ��
	GPIO_ClockConf(GPIOx,GPIO_Pin_n);
	//3����ʼ��GPIO
	GPIO_Init(GPIOx,&GPIO_InitStructure);			//GPIOA	
}
/*******************************************************************************
* ������		:	GPIO_Configuration_OOD2
* ��������	:	��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�2MHz----V20170605
* ����		:	GPIOx--GPIO�˿ڣ�GPIO_Pin_n--GPIO�ܽź�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Configuration_OOD2(
														GPIO_TypeDef* GPIOx,							//GPIO�˿�,x=A/B/C/D/E/F/G
														u16 GPIO_Pin_n										//GPIO�ܽź�n=0~15/All
														)
{
	//1��GPIO�ṹ�嶨��
	GPIO_InitTypeDef	GPIO_InitStructure;
	//2����ʼ��GPIO�ṹ��
	GPIO_InitStructure.GPIO_Pin  		= GPIO_Pin_n;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;					//����ٶ�Ƶ��2MHz
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_Out_OD;					//OD(��©)���ģʽ
	//3)����GPIO�˿ڼ��ܽźſ����˿�ʱ�Ӽ�ȷ���Ƿ��AFIOʱ��
	GPIO_ClockConf(GPIOx,GPIO_Pin_n);
	//3����ʼ��GPIO
	GPIO_Init(GPIOx,&GPIO_InitStructure);			//GPIOA	
}
/*******************************************************************************
* ������		:	GPIO_Configuration_OOD2
* ��������	:	��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�10MHz----V20170605
* ����		:	GPIOx--GPIO�˿ڣ�GPIO_Pin_n--GPIO�ܽź�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Configuration_OOD10(
														GPIO_TypeDef* GPIOx,							//GPIO�˿�,x=A/B/C/D/E/F/G
														u16 GPIO_Pin_n										//GPIO�ܽź�n=0~15/All
														)
{
	//1��GPIO�ṹ�嶨��
	GPIO_InitTypeDef	GPIO_InitStructure;
	//2����ʼ��GPIO�ṹ��
	GPIO_InitStructure.GPIO_Pin  		= GPIO_Pin_n;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_10MHz;					//����ٶ�Ƶ��10MHz
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_Out_OD;					//OD(��©)���ģʽ
	//3)����GPIO�˿ڼ��ܽźſ����˿�ʱ�Ӽ�ȷ���Ƿ��AFIOʱ��
	GPIO_ClockConf(GPIOx,GPIO_Pin_n);
	//3����ʼ��GPIO
	GPIO_Init(GPIOx,&GPIO_InitStructure);			//GPIOA	
}
/*******************************************************************************
* ������		:	GPIO_Configuration_OOD50
* ��������	:	��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�50MHz----V20170605
* ����		:	GPIOx--GPIO�˿ڣ�GPIO_Pin_n--GPIO�ܽź�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Configuration_OOD50(
														GPIO_TypeDef* GPIOx,							//GPIO�˿�,x=A/B/C/D/E/F/G
														u16 GPIO_Pin_n										//GPIO�ܽź�n=0~15/All
														)
{
	//1��GPIO�ṹ�嶨��
	GPIO_InitTypeDef	GPIO_InitStructure;
	//2����ʼ��GPIO�ṹ��
	GPIO_InitStructure.GPIO_Pin  		= GPIO_Pin_n;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;					//����ٶ�Ƶ��50MHz
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_Out_OD;					//OD(��©)���ģʽ
	//3)����GPIO�˿ڼ��ܽźſ����˿�ʱ�Ӽ�ȷ���Ƿ��AFIOʱ��
	GPIO_ClockConf(GPIOx,GPIO_Pin_n);
	//3����ʼ��GPIO
	GPIO_Init(GPIOx,&GPIO_InitStructure);			//GPIOA	
}
/*******************************************************************************
* ������		:	GPIO_Configuration_OPP2
* ��������	:	��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
* ����		:	GPIOx--GPIO�˿ڣ�GPIO_Pin_n--GPIO�ܽź�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Configuration_OPP2(
														GPIO_TypeDef* GPIOx,							//GPIO�˿�,x=A/B/C/D/E/F/G
														u16 GPIO_Pin_n										//GPIO�ܽź�n=0~15/All
														)
{
	//1��GPIO�ṹ�嶨��
	GPIO_InitTypeDef	GPIO_InitStructure;
	//2����ʼ��GPIO�ṹ��
	GPIO_InitStructure.GPIO_Pin  		= GPIO_Pin_n;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;					//����ٶ�Ƶ��2MHz
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_Out_PP;					//PP(����)���ģʽ
	//3)����GPIO�˿ڼ��ܽźſ����˿�ʱ�Ӽ�ȷ���Ƿ��AFIOʱ��
	GPIO_ClockConf(GPIOx,GPIO_Pin_n);
	//3����ʼ��GPIO
	GPIO_Init(GPIOx,&GPIO_InitStructure);			//GPIOA	
}
/*******************************************************************************
* ������		:	GPIO_Configuration_OPP10
* ��������	:	��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�10MHz----V20170605
* ����		:	GPIOx--GPIO�˿ڣ�GPIO_Pin_n--GPIO�ܽź�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Configuration_OPP10(
														GPIO_TypeDef* GPIOx,							//GPIO�˿�,x=A/B/C/D/E/F/G
														u16 GPIO_Pin_n										//GPIO�ܽź�n=0~15/All
														)
{
	//1��GPIO�ṹ�嶨��
	GPIO_InitTypeDef	GPIO_InitStructure;
	//2����ʼ��GPIO�ṹ��
	GPIO_InitStructure.GPIO_Pin  		= GPIO_Pin_n;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_10MHz;					//����ٶ�Ƶ��10MHz
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_Out_PP;					//PP(����)���ģʽ
	//3)����GPIO�˿ڼ��ܽźſ����˿�ʱ�Ӽ�ȷ���Ƿ��AFIOʱ��
	GPIO_ClockConf(GPIOx,GPIO_Pin_n);
	//3����ʼ��GPIO
	GPIO_Init(GPIOx,&GPIO_InitStructure);			//GPIOA	
}
/*******************************************************************************
* ������		:	GPIO_Configuration_OPP50
* ��������	:	��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�10MHz----V20170605
* ����		:	GPIOx--GPIO�˿ڣ�GPIO_Pin_n--GPIO�ܽź�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Configuration_OPP50(
														GPIO_TypeDef* GPIOx,							//GPIO�˿�,x=A/B/C/D/E/F/G
														u16 GPIO_Pin_n										//GPIO�ܽź�n=0~15/All
														)
{
	//1��GPIO�ṹ�嶨��
	GPIO_InitTypeDef	GPIO_InitStructure;
	//2����ʼ��GPIO�ṹ��
	GPIO_InitStructure.GPIO_Pin  		= GPIO_Pin_n;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;					//����ٶ�Ƶ��50MHz
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_Out_PP;					//PP(����)���ģʽ
	//3)����GPIO�˿ڼ��ܽźſ����˿�ʱ�Ӽ�ȷ���Ƿ��AFIOʱ��
	GPIO_ClockConf(GPIOx,GPIO_Pin_n);
	//3����ʼ��GPIO
	GPIO_Init(GPIOx,&GPIO_InitStructure);			//GPIOA	
}
/*******************************************************************************
* ������		:	GPIO_Configuration_AOD2
* ��������	:	��GPIO��Ӧ�ܽ�����ΪAOD(���ÿ�©)���ģʽ������ٶ�2MHz----V20170605
* ����		:	GPIOx--GPIO�˿ڣ�GPIO_Pin_n--GPIO�ܽź�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Configuration_AOD2(
														GPIO_TypeDef* GPIOx,							//GPIO�˿�,x=A/B/C/D/E/F/G
														u16 GPIO_Pin_n										//GPIO�ܽź�n=0~15/All
														)
{
	//1��GPIO�ṹ�嶨��
	GPIO_InitTypeDef	GPIO_InitStructure;
	//2����ʼ��GPIO�ṹ��
	GPIO_InitStructure.GPIO_Pin  		= GPIO_Pin_n;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;					//����ٶ�Ƶ��2MHz
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_AF_OD;					//AOD(���ÿ�©)���ģʽ
	//3)����GPIO�˿ڼ��ܽźſ����˿�ʱ�Ӽ�ȷ���Ƿ��AFIOʱ��
	GPIO_ClockConf(GPIOx,GPIO_Pin_n);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);				//�򿪸���ʱ��
	//3����ʼ��GPIO
	GPIO_Init(GPIOx,&GPIO_InitStructure);			//GPIOA	
}
/*******************************************************************************
* ������		:	GPIO_Configuration_AOD10
* ��������	:	��GPIO��Ӧ�ܽ�����ΪAOD(���ÿ�©)���ģʽ������ٶ�10MHz----V20170605
* ����		:	GPIOx--GPIO�˿ڣ�GPIO_Pin_n--GPIO�ܽź�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Configuration_AOD10(
														GPIO_TypeDef* GPIOx,							//GPIO�˿�,x=A/B/C/D/E/F/G
														u16 GPIO_Pin_n										//GPIO�ܽź�n=0~15/All
														)
{
	//1��GPIO�ṹ�嶨��
	GPIO_InitTypeDef	GPIO_InitStructure;
	//2����ʼ��GPIO�ṹ��
	GPIO_InitStructure.GPIO_Pin  		= GPIO_Pin_n;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_10MHz;					//����ٶ�Ƶ��10MHz
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_AF_OD;					//AOD(���ÿ�©)���ģʽ
	//3)����GPIO�˿ڼ��ܽźſ����˿�ʱ�Ӽ�ȷ���Ƿ��AFIOʱ��
	GPIO_ClockConf(GPIOx,GPIO_Pin_n);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);				//�򿪸���ʱ��
	//3����ʼ��GPIO
	GPIO_Init(GPIOx,&GPIO_InitStructure);			//GPIOA	
}
/*******************************************************************************
* ������		:	GPIO_Configuration_AOD50
* ��������	:	��GPIO��Ӧ�ܽ�����ΪAOD(���ÿ�©)���ģʽ������ٶ�50MHz----V20170605
* ����		:	GPIOx--GPIO�˿ڣ�GPIO_Pin_n--GPIO�ܽź�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Configuration_AOD50(
														GPIO_TypeDef* GPIOx,							//GPIO�˿�,x=A/B/C/D/E/F/G
														u16 GPIO_Pin_n										//GPIO�ܽź�n=0~15/All
														)
{
	//1��GPIO�ṹ�嶨��
	GPIO_InitTypeDef	GPIO_InitStructure;
	//2����ʼ��GPIO�ṹ��
	GPIO_InitStructure.GPIO_Pin  		= GPIO_Pin_n;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;					//����ٶ�Ƶ��50MHz
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_AF_OD;					//AOD(���ÿ�©)���ģʽ
	//3)����GPIO�˿ڼ��ܽźſ����˿�ʱ�Ӽ�ȷ���Ƿ��AFIOʱ��
	GPIO_ClockConf(GPIOx,GPIO_Pin_n);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);				//�򿪸���ʱ��
	//3����ʼ��GPIO
	GPIO_Init(GPIOx,&GPIO_InitStructure);			//GPIOA	
}
/*******************************************************************************
* ������		:	GPIO_Configuration_APP2
* ��������	:	��GPIO��Ӧ�ܽ�����ΪAPP(��������)���ģʽ������ٶ�2MHz----V20170605
* ����		:	GPIOx--GPIO�˿ڣ�GPIO_Pin_n--GPIO�ܽź�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Configuration_APP2(
														GPIO_TypeDef* GPIOx,							//GPIO�˿�,x=A/B/C/D/E/F/G
														u16 GPIO_Pin_n										//GPIO�ܽź�n=0~15/All
														)
{
	//1��GPIO�ṹ�嶨��
	GPIO_InitTypeDef	GPIO_InitStructure;
	//2����ʼ��GPIO�ṹ��
	GPIO_InitStructure.GPIO_Pin  		= GPIO_Pin_n;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_2MHz;					//����ٶ�Ƶ��2MHz
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_AF_PP;					//APP(��������)���ģʽ
	//3)����GPIO�˿ڼ��ܽźſ����˿�ʱ�Ӽ�ȷ���Ƿ��AFIOʱ��
	GPIO_ClockConf(GPIOx,GPIO_Pin_n);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);				//�򿪸���ʱ��
	//3����ʼ��GPIO
	GPIO_Init(GPIOx,&GPIO_InitStructure);			//GPIOA	
}
/*******************************************************************************
* ������		:	GPIO_Configuration_APP10
* ��������	:	��GPIO��Ӧ�ܽ�����ΪAPP(��������)���ģʽ������ٶ�10MHz----V20170605
* ����		:	GPIOx--GPIO�˿ڣ�GPIO_Pin_n--GPIO�ܽź�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Configuration_APP10(
														GPIO_TypeDef* GPIOx,							//GPIO�˿�,x=A/B/C/D/E/F/G
														u16 GPIO_Pin_n										//GPIO�ܽź�n=0~15/All
														)
{
	//1��GPIO�ṹ�嶨��
	GPIO_InitTypeDef	GPIO_InitStructure;
	//2����ʼ��GPIO�ṹ��
	GPIO_InitStructure.GPIO_Pin  		= GPIO_Pin_n;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_10MHz;					//����ٶ�Ƶ��10MHz
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_AF_PP;					//APP(��������)���ģʽ
	//3)����GPIO�˿ڼ��ܽźſ����˿�ʱ�Ӽ�ȷ���Ƿ��AFIOʱ��
	GPIO_ClockConf(GPIOx,GPIO_Pin_n);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);				//�򿪸���ʱ��
	//3����ʼ��GPIO
	GPIO_Init(GPIOx,&GPIO_InitStructure);			//GPIOA	
}
/*******************************************************************************
* ������		:	GPIO_Configuration_APP50
* ��������	:	��GPIO��Ӧ�ܽ�����ΪAPP(��������)���ģʽ������ٶ�50MHz----V20170605
* ����		:	GPIOx--GPIO�˿ڣ�GPIO_Pin_n--GPIO�ܽź�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Configuration_APP50(
														GPIO_TypeDef* GPIOx,							//GPIO�˿�,x=A/B/C/D/E/F/G
														u16 GPIO_Pin_n										//GPIO�ܽź�n=0~15/All
														)
{
	//1��GPIO�ṹ�嶨��
	GPIO_InitTypeDef	GPIO_InitStructure;
	//2����ʼ��GPIO�ṹ��
	GPIO_InitStructure.GPIO_Pin  		= GPIO_Pin_n;
  GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;					//����ٶ�Ƶ��50MHz
  GPIO_InitStructure.GPIO_Mode 		= GPIO_Mode_AF_PP;					//APP(��������)���ģʽ
	//3)����GPIO�˿ڼ��ܽźſ����˿�ʱ�Ӽ�ȷ���Ƿ��AFIOʱ��
	GPIO_ClockConf(GPIOx,GPIO_Pin_n);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);				//�򿪸���ʱ��
	//3����ʼ��GPIO
	GPIO_Init(GPIOx,&GPIO_InitStructure);			//GPIOA	
}
/*******************************************************************************
* ������		:	GPIO_Configuration_APP50
* ��������	:	��GPIO��Ӧ�ܽ�����ΪAPP(��������)���ģʽ������ٶ�50MHz----V20170605
* ����		:	GPIOx--GPIO�˿ڣ�GPIO_Pin_n--GPIO�ܽź�
* ���		:
* ���� 		:
*******************************************************************************/
void GPIO_Toggle(
									GPIO_TypeDef* GPIOx,							//GPIO�˿�,x=A/B/C/D/E/F/G
									u16 GPIO_Pin_n										//GPIO�ܽź�n=0~15/All
									)
{
	//1��GPIO�ܽ�����ͣ�����Bit_RESET
	if ((GPIOx->ODR & GPIO_Pin_n) != (u32)Bit_RESET)
  {
    GPIOx->BRR = GPIO_Pin_n;
  }
  else
  {
		GPIOx->BSRR = GPIO_Pin_n;
  }
}



















//*****************************************************����Ϊ�ɳ���20170605********************
/*##############################################################################
################################################################################
# ģ����		:	STM32_GPIO	
# ��������	:	GPIO����ʹ��
# ʹ������	:	GPIO_Configuration(GPIOA,GPIO_Pin_All,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
						GPIO_Configuration(GPIOB,GPIO_Pin_1,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
################################################################################
###############################################################################*/
/*******************************************************************************
* ������		:	GPIO_Configuration
* ��������	:	GPIO���� 
* ����		:	GPIOx��GPIOA~GPIOG
						GPIO_Pin_x:GPIO_Pin_0~GPIO_Pin_15;GPIO_Pin_All
* ���		:
* ���� 		:
*******************************************************************************/
//void GPIO_Conf(	GPIO_TypeDef* GPIOX,						//GPIO�˿�
//								u16 GPIO_Pin_x,									//GPIO����
//								GPIOMode_TypeDef GPIO_Mode,			//����ģʽ
//								GPIOSpeed_TypeDef GPIO_Speed		//�����ٶ�
//								)			//GPIO����	
//{
//	GPIO_ClockConf(GPIOX,GPIO_Pin_x);														//�������GPIOʱ��	
//	GPIO_InitStructure(GPIOX,GPIO_Pin_x,GPIO_Mode,GPIO_Speed);	//GPIO��ʼ��
//}
/*******************************************************************************
* ������		:	GPIO_Configuration
* ��������	:	GPIO���� 
* ����		:	GPIOx��GPIOA~GPIOG
						GPIO_Pin_x:GPIO_Pin_0~GPIO_Pin_15;GPIO_Pin_All
* ���		:
* ���� 		:
*******************************************************************************/
//void GPIO_Configuration(GPIO_TypeDef* GPIOx,					//GPIO�˿�
//												u16 GPIO_Pin_x,								//GPIO����
//												GPIOMode_TypeDef GPIO_Mode,		//����ģʽ
//												GPIOSpeed_TypeDef GPIO_Speed	//�����ٶ�
//												)			//GPIO����	
//{	
//	GPIO_ClockConf(GPIOx,GPIO_Pin_x);														//�������GPIOʱ��	
//	GPIO_InitStructure(GPIOx,GPIO_Pin_x,GPIO_Mode,GPIO_Speed);	//GPIO��ʼ��
//}
/*******************************************************************************
* ������		:	GPIO_InitStructure
* ��������	:	GPIO��ʼ�� 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
//void GPIO_InitStructure(
//														GPIO_TypeDef* GPIOx,								//GPIO�˿�,x=A/B/C/D/E/F/G
//														GPIO_InitTypeDef* GPIO_InitStructure		//GPIO���ýṹ��
//														)
//{
//	//1)����GPIO�˿ڼ��ܽźſ����˿�ʱ�Ӽ�ȷ���Ƿ��AFIOʱ��
//	GPIO_ClockConf(GPIOx,GPIO_InitStructure->GPIO_Pin);
//	//2����ʼ��GPIO
//	GPIO_Init(GPIOx,GPIO_InitStructure);						//GPIO��ʼ��
//}