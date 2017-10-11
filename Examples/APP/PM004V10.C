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

#ifdef PM004V10			//С�Ƴ����ذ�

#include "PM004V10.H"

#include "STM32_USART.H"

#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"

#include "string.h"				//�����ڴ��������ͷ�ļ�
#include "stm32f10x_dma.h"

#define RxBufferSize	256

u8 RevBuffer[RxBufferSize]={0};
u8 RxdBuffer[RxBufferSize]={0};

u8 TevBuffer[RxBufferSize]={0};
u8 TxdBuffer[RxBufferSize]={0};

u8 strings[]="���ڿ���ģʽ�����ڽ��ջ���������������ݣ������ݿ�����RevBuffer,�����ؽ��յ������ݸ�����Ȼ�����½����ջ�������ַָ��RxdBuffer\n";

u16 RxNum=0;
u32	RuningTime=0;
u16 Tcnt=0;

/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void PM004V10_Configuration(void)
{
	SYS_Configuration();							//ϵͳ����---��ϵͳʱ�� STM32_SYS.H
	
	GPIO_DeInitAll();									//�����е�GPIO�ر�----V20170605
	
	USART_DMA_ConfigurationNR	(USART2,115200,(u32*)RxdBuffer,RxBufferSize);	//USART_DMA����--��ѯ��ʽ�������ж�
	
	SysTick_Configuration(100);				//ϵͳ���ʱ������72MHz,��λΪuS
	
	IWDG_Configuration(1000);					//�������Ź�����---������λms	
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,900);						//PWM�趨-20161127�汾--SYS-LED

}
/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void PM004V10_Server(void)
{	
	IWDG_Feed();								//�������Ź�ι��
	RuningTime++;
	if(RuningTime>=200)				//1��
	{
		RuningTime=0;
		Tcnt++;
		if(Tcnt>=1000)
			Tcnt=0;
		USART_DMAPrintf(USART2,"���ڿ���ģʽ�����ڽ��ջ���������������ݣ������ݿ�����RevBuffer,�����ؽ��յ������ݸ�����Ȼ�����½����ջ�������ַָ��RxdBuffer---%4d\n",Tcnt);					//�Զ���printf����DMA���ͳ���,��ߵ�ʡ�Ժž��ǿɱ����
//		USART_DMASend(USART2,(u32*)strings,strlen(strings));											//����DMA���ͳ���
	}
	RxNum=USART_ReadBufferIDLE(USART2,(u32*)RevBuffer,(u32*)RxdBuffer);	//���ڿ���ģʽ�����ڽ��ջ���������������ݣ������ݿ�����RevBuffer,�����ؽ��յ������ݸ�����Ȼ�����½����ջ�������ַָ��RxdBuffer
	if(RxNum)
	{
		USART_DMASend(USART2,(u32*)RevBuffer,RxNum);											//����DMA���ͳ���
	}
}











#endif