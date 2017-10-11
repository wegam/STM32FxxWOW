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

#ifdef PD002V30				//�������̿�����

#include "PD002V30.H"
#include "CS5530.H"
#include "74HC595.H"

#include "STM32F10x_BitBand.H"
#include "STM32_GPIO.H"
#include "STM32_SYS.H"
#include "STM32_SYSTICK.H"
#include "STM32_WDG.H"
#include "STM32_USART.H"
#include "STM32_PWM.H"

#include "string.h"				//�����ڴ��������ͷ�ļ�
#include "stm32f10x_dma.h"

#define BufferSize	12
#define Command_ReadData	(unsigned char)0x05
#define Command_SendData	(unsigned char)0x06
//#define	USART_TO_RS485		//USARTת485��485תUSART����

//#define PD002V30TEST

unsigned long sysledcnt=0;			//ϵͳ����ָʾ��ɨ�����  0.5��

u8 txBuffer1[BufferSize]={0};			//USART1-TXBF
u8 rxBuffer1[BufferSize]={0};			//USART1-RXBF
u8 txBuffer_PD[BufferSize]={0};			//USART1-TXBF
u8 rxBuffer_PD[BufferSize]={0};			//USART1-RXBF


u8	txflg1=0;	//USART1���ͱ�־
u8	txflg3=0;	//485BUS���ͱ�־

u16	tx1_tcont=0;
u16	tx3_tcont=0;



u8 SwitchID=0;	//���뿪�ص�ַ

#define RS485_PD_RXEN		PA1=0				//rs485���ճ��ذ�ʹ��
#define RS485_PD_TXEN		PA1=1				//rs485���ͳ��ذ�ʹ��

u8	RS485_PD_txAddr=0;						//�������
u8	RS485_PD_rxAddr=0;						//�������


CS5530_Pindef CS5530_1,CS5530_2,CS5530_3;
u32 Value_AD1=0;
u32 Value_AD2=0;

u8 swid=0;
u16 RunTime=0;
HC595_Pindef HC595_Conf;

u8 dnum=0;

void TEMPdelay(u32 time);
/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void PD002V30_Configuration(void)
{
	SYS_Configuration();					//ϵͳ����---��ϵͳʱ�� STM32_SYS.H
	
	GPIO_DeInitAll();							//�����е�GPIO�ر�----V20170605	
	
	GPIO_Configuration_OPP2	(GPIOC,GPIO_Pin_1);			//BUZZER//��GPIO��Ӧ�ܽ�����ΪOD(��©)���ģʽ������ٶ�2MHz----V20170605
	
	GPIO_Configuration_IPU	(GPIOA,GPIO_Pin_4);			//S1//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
	GPIO_Configuration_IPU	(GPIOA,GPIO_Pin_5);			//S2//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
	GPIO_Configuration_IPU	(GPIOA,GPIO_Pin_6);			//S3//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
	GPIO_Configuration_IPU	(GPIOA,GPIO_Pin_7);			//S4//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
	
	Seg_Conf();
	
	SysTick_Configuration(1000);	//ϵͳ���ʱ������72MHz,��λΪuS
	
//	IWDG_Configuration(1000);			//�������Ź�����---������λms	
	
	PWM_OUT(TIM2,PWM_OUTChannel1,1,900);						//PWM�趨-20161127�汾
}
/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void PD002V30_Server(void)
{	

	IWDG_Feed();								//�������Ź�ι��
	
	RunTime++;
	if(RunTime>=1000)
	{
		dnum++;
		if(dnum>9)
			dnum=0;
		RunTime=0;
		TEMPdelay(0XFF);
		HC595_RCK_HIGH(&HC595_Conf);
		TEMPdelay(0XFF);
		HC595_WriteNumberN(&HC595_Conf,dnum);		//�����ź�д��
		TEMPdelay(0XFF);
		HC595_RCK_LOW(&HC595_Conf);
		
	}

}

/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void PD002V30_USART_Conf(void)
{


}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void PD002V30_USART1_Server(void)
{

}
/*******************************************************************************
* ������			:	function
* ��������		:	���ذ�
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void PD002V30_485_Server(void)
{

}
/*******************************************************************************
* ������			:	function
* ��������		: ��ȡ���뿪�ص�ַ
* ����			: void
* ����ֵ			: void
*******************************************************************************/
u8 PD002V30_GetSwitchID(void)
{
	u8 SwitchTemp=0;	

	SwitchTemp|=PA4in<<0;		//S1
	SwitchTemp|=PA5in<<1;		//S2
	SwitchTemp|=PA6in<<2;		//S3
	SwitchTemp|=PA7in<<3;		//S4
		
	SwitchTemp=~SwitchTemp;
	SwitchTemp=SwitchTemp&0x0F;
	
	return SwitchTemp;
}
/*******************************************************************************
* ������			:	PC001V21_GetBufferArray
* ��������		: ��ȡ4������8��ͨ����ADֵ��һ��һ�������ȡ
* ����			: void
* ����ֵ			: void
*******************************************************************************/
u8 PD002V30_GetBufferArray(void)
{
	return 0;
}
/*******************************************************************************
* ������			:	PC001V21_GetBufferArray
* ��������		: ��ȡ4������8��ͨ����ADֵ��һ��һ�������ȡ
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void cs5530init(void)
{
	CS5530_1.CS5530_CS_PORT=GPIOB;
	CS5530_1.CS5530_CS_Pin=GPIO_Pin_12;
	
	CS5530_1.CS5530_SDI_PORT=GPIOB;
	CS5530_1.CS5530_SDI_Pin=GPIO_Pin_15;
	
	CS5530_1.CS5530_SDO_PORT=GPIOB;
	CS5530_1.CS5530_SDO_Pin=GPIO_Pin_14;
	
	CS5530_1.CS5530_SCLK_PORT=GPIOB;
	CS5530_1.CS5530_SCLK_Pin=GPIO_Pin_13;
	
	
	
	CS5530_2.CS5530_CS_PORT=GPIOA;
	CS5530_2.CS5530_CS_Pin=GPIO_Pin_8;
	
	CS5530_2.CS5530_SDI_PORT=GPIOB;
	CS5530_2.CS5530_SDI_Pin=GPIO_Pin_15;
	
	CS5530_2.CS5530_SDO_PORT=GPIOB;
	CS5530_2.CS5530_SDO_Pin=GPIO_Pin_14;
	
	CS5530_2.CS5530_SCLK_PORT=GPIOB;
	CS5530_2.CS5530_SCLK_Pin=GPIO_Pin_13;
	
	CS5530_PinConf(&CS5530_1);
	CS5530_PinConf(&CS5530_2);
	
	CS5530_PowerUp(&CS5530_1);
	CS5530_PowerUp(&CS5530_2);
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void Seg_Conf(void)
{
	HC595_Conf.HC595_SDA_PORT=GPIOB;
	HC595_Conf.HC595_SDA_Pin=GPIO_Pin_5;
	
	HC595_Conf.HC595_SCK_PORT=GPIOB;
	HC595_Conf.HC595_SCK_Pin=GPIO_Pin_4;
	
	HC595_Conf.HC595_RCK_PORT=GPIOB;
	HC595_Conf.HC595_RCK_Pin=GPIO_Pin_3;
	HC595_PinConf(&HC595_Conf);
}
/*******************************************************************************
* ������			:	function
* ��������		:	��������˵�� 
* ����			: void
* ����ֵ			: void
*******************************************************************************/
void TEMPdelay(u32 time)
{
	while(time--);
}
#endif