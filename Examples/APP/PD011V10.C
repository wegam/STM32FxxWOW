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

#ifdef PD011V10			//8·������ư�

#include "PD011V10.H"

#include "STM32_USART.H"
#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_PWM.H"

#include "string.h"				//�����ڴ��������ͷ�ļ�
#include "stm32f10x_dma.h"

#define RxBufferSize	5

u8 RevBuffer1[RxBufferSize]={0};
u8 RxdBuffer1[RxBufferSize]={0};
u8 TxdBuffer1[RxBufferSize]={0};

u8 RevBuffer4[RxBufferSize]={0};
u8 RxdBuffer4[RxBufferSize]={0};
u8 TxdBuffer4[RxBufferSize]={0};

u8 RevBuffer2[RxBufferSize]={0};
u8 RxdBuffer2[RxBufferSize]={0};
u8 TxdBuffer2[RxBufferSize]={0};

u8 RevBuffer3[RxBufferSize]={0};
u8 RxdBuffer3[RxBufferSize]={0};
u8 TxdBuffer3[RxBufferSize]={0};

u16	SYSTime=0;							//ѭ����ʱ����
u16	DelayTime=0;
u8 testFlg=0;

RS485_TypeDef RS485_1,RS485_4;

/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void PD011V10_Configuration(void)
{
	SYS_Configuration();					//ϵͳ����---��ϵͳʱ�� STM32_SYS.H
	
	GPIO_DeInitAll();							//�����е�GPIO�ر�----V20170605
	
	PD011V10_PinSet();
	
	RS485_DMA_ConfigurationNR	(&RS485_1,9600,(u32*)RxdBuffer1,RxBufferSize);	//USART_DMA����--��ѯ��ʽ�������ж�,������Ĭ��Ϊ����״̬
	RS485_DMA_ConfigurationNR	(&RS485_4,9600,(u32*)RxdBuffer4,RxBufferSize);	//USART_DMA����--��ѯ��ʽ�������ж�,������Ĭ��Ϊ����״̬
	
	USART_DMA_ConfigurationNR	(USART2,9600,(u32*)RxdBuffer2,RxBufferSize);	//USART_DMA����--��ѯ��ʽ�������ж�
	USART_DMA_ConfigurationNR	(USART3,9600,(u32*)RxdBuffer3,RxBufferSize);	//USART_DMA����--��ѯ��ʽ�������ж�
	
//	RS485_RX_EN(&RS485_4);
	
	SysTick_Configuration(1000);	//ϵͳ���ʱ������72MHz,��λΪuS
	
	IWDG_Configuration(1000);			//�������Ź�����---������λms	
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,900);						//PWM�趨-20161127�汾
}
/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void PD011V10_Server(void)
{
	u8 RxNum=0;
	
	IWDG_Feed();								//�������Ź�ι��
	SYSTime++;
	if(SYSTime>=1000)
	{
		SYSTime=0;							//ѭ����ʱ����
		GPIO_Toggle(GPIOB,	GPIO_Pin_13);
	}
	if(SYSTime==0)
	{
		TxdBuffer1[0]++;
		if(TxdBuffer1[0]>=255)
			TxdBuffer1[0]=0;
		RS485_DMASend(&RS485_1,(u32*)TxdBuffer1,RxBufferSize);	//RS485-DMA���ͳ���
	}
	RxNum=RS485_ReadBufferIDLE(&RS485_4,(u32*)RevBuffer4,(u32*)RxdBuffer4);	//���ڿ���ģʽ�����ڽ��ջ���������������ݣ������ݿ�����RevBuffer,�����ؽ��յ������ݸ�����Ȼ�����½����ջ�������ַָ��RxdBuffer
	if(RxNum)
	{
		PWM_OUT(TIM2,PWM_OUTChannel1,RevBuffer4[0],500);						//PWM�趨-20161127�汾
	}
	
	if(SYSTime==0)
	{
		TxdBuffer2[0]++;
		if(TxdBuffer2[0]>=255)
			TxdBuffer2[0]=0;
		USART_DMASend(USART2,(u32*)TxdBuffer2,RxBufferSize);	//RS485-DMA���ͳ���
	}
	RxNum=USART_ReadBufferIDLE(USART3,(u32*)RevBuffer3,(u32*)RxdBuffer3);	//���ڿ���ģʽ�����ڽ��ջ���������������ݣ������ݿ�����RevBuffer,�����ؽ��յ������ݸ�����Ȼ�����½����ջ�������ַָ��RxdBuffer
	if(RxNum)
	{
		PWM_OUT(TIM2,PWM_OUTChannel1,RevBuffer3[0],500);						//PWM�趨-20161127�汾
	}
}

/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void PD011V10_PinSet(void)
{	
	GPIO_Configuration_OPP50	(GPIOD,	GPIO_Pin_4);			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�50MHz----V20170605
	PD4=0;
	
	RS485_1.USARTx=USART1;
	RS485_1.RS485_CTL_PORT=GPIOA;
	RS485_1.RS485_CTL_Pin=GPIO_Pin_10;
	
	RS485_4.USARTx=UART4;
	RS485_4.RS485_CTL_PORT=GPIOA;
	RS485_4.RS485_CTL_Pin=GPIO_Pin_15;
	
	//����������
	GPIO_Configuration_OPP50	(GPIOB,	GPIO_Pin_13);			//��GPIO��Ӧ�ܽ�����ΪPP(����)���ģʽ������ٶ�50MHz----V20170605
}
#endif