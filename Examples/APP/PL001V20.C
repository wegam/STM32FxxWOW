/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : PC001V21.c
* Author             : WOW
* Version            : V2.0.1
* Date               : 06/26/2017
* Description        : PC001V21����ư�.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

#ifdef PL001V20			//���ؿ��ư�--�����

#include "PL001V20.H"

#include "STM32_GPIO.H"
#include "CD4511.H"
#include "CD4511BM_TEST.H"
#include "STM32_PWM.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32F10x_BitBand.H"


#define	CD4511BM_DEBUG_TEST			//����ʱ����ܼ�����ʾ������ʹ��ʱӦ��ע�͵�


u16 Time=0;
u16 data=0;


CD4511_Pindef CD4511_Pin;


void PL001V20_DISPALY(u8 wei,u16 num);
/*******************************************************************************
*������		:	function
*��������	:	��������˵��
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void PL001V20_Configuration(void)
{
	SYS_Configuration();											//ϵͳ���� STM32_SYS.H	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,500);
	SysTick_Configuration(1000);							//ϵͳ���ʱ������72MHz,��λΪuS
	
	//λ
	GPIO_Configuration_OPP50	(GPIOB,		GPIO_Pin_5);			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOB,		GPIO_Pin_14);			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	GPIO_Configuration_OPP50	(GPIOB,		GPIO_Pin_15);			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�2MHz----V20170605
	
	//Pin
	CD4511_Pin.CD4511_A0_PORT=GPIOB;
	CD4511_Pin.CD4511_A0_Pin=GPIO_Pin_0;
	
	CD4511_Pin.CD4511_A1_PORT=GPIOB;
	CD4511_Pin.CD4511_A1_Pin=GPIO_Pin_1;
	
	CD4511_Pin.CD4511_A2_PORT=GPIOB;
	CD4511_Pin.CD4511_A2_Pin=GPIO_Pin_2;
	
	CD4511_Pin.CD4511_A3_PORT=GPIOB;
	CD4511_Pin.CD4511_A3_Pin=GPIO_Pin_3;
	
	CD4511_PinConf(&CD4511_Pin);
}

/*******************************************************************************
*������		:	function
*��������	:	��������˵��
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void PL001V20_Server(void)
{
	++Time;	
	if(Time>=50)
	{
		Time=0;	
		++data;		
	}
	if(data>999)
		data=0;
	PL001V20_DISPALY(Time%3,data);
}

/*******************************************************************************
*������		:	function
*��������	:	��������˵��
*����			: 
*���			:	��
*����ֵ		:	��
*����			:
*******************************************************************************/
void PL001V20_DISPALY(u8 wei,u16 num)
{
	if(wei==2)
	{
		if(num>100)
		{
			PB5=1;
			PB14=0;
			PB15=0;
			CD4511_WriteData(&CD4511_Pin,num/100);
		}
		else
		{
			PB5=0;
			PB14=0;
			PB15=0;
		}
	}
	else if(wei==1)
	{
		if(num>=10||num>=100)
		{
			PB5=0;
			PB14=1;
			PB15=0;
			if(num>=100)
			{
				num=num%100;
			}
			CD4511_WriteData(&CD4511_Pin,num/10);
		}
		else
		{
			PB5=0;
			PB14=0;
			PB15=0;
		}
	}
	else
	{
		PB5=0;
		PB14=0;
		PB15=1;
		CD4511_WriteData(&CD4511_Pin,num%10);
	}
}

#endif