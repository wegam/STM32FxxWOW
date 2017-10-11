/*********************************************
*�����������
*�ṹ�����������ʽ
*����ģʽ---��ʱ
*���⹦��:��ʱ,����
*������ȼ�:ֹͣ--�κ������,��ֹͣ����,����ִ��ֹͣ
*����:ɲ��
**********************************************/

#include "SWITCHID.H"

#include "STM32_GPIO.H"


//SW(1)_PORT
//SW(1)_Pin
//#define	SW_PORT(n)	SW##n##_PORT		//##ƴ�ӷ�
//#define	SW_Pin(n)		SW##n##_Pin
/****************************************************************
*������:
*����:
*
******************************************************************/
void SWITCHIDConf(SWITCHID_CONF *SWITCHIDx)
{
	unsigned char NumOfSW=SWITCHIDx->NumOfSW;			//����İ��뿪��λ��
	//���ݽ���İ��뿪��λ���ӵ�λ����λ����������������
	if(NumOfSW)	//SW1
	{
		GPIO_Configuration_IPU	(SWITCHIDx->SW1_PORT,	SWITCHIDx->SW1_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW2
	{
		GPIO_Configuration_IPU	(SWITCHIDx->SW2_PORT,	SWITCHIDx->SW2_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW3
	{
		GPIO_Configuration_IPU	(SWITCHIDx->SW3_PORT,	SWITCHIDx->SW3_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW4
	{
		GPIO_Configuration_IPU	(SWITCHIDx->SW4_PORT,	SWITCHIDx->SW4_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW5
	{
		GPIO_Configuration_IPU	(SWITCHIDx->SW5_PORT,	SWITCHIDx->SW5_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW6
	{
		GPIO_Configuration_IPU	(SWITCHIDx->SW6_PORT,	SWITCHIDx->SW6_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW7
	{
		GPIO_Configuration_IPU	(SWITCHIDx->SW7_PORT,	SWITCHIDx->SW7_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW8
	{
		GPIO_Configuration_IPU	(SWITCHIDx->SW8_PORT,	SWITCHIDx->SW8_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW9
	{
		GPIO_Configuration_IPU	(SWITCHIDx->SW9_PORT,	SWITCHIDx->SW9_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW10
	{
		GPIO_Configuration_IPU	(SWITCHIDx->SW10_PORT,	SWITCHIDx->SW10_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW11
	{
		GPIO_Configuration_IPU	(SWITCHIDx->SW11_PORT,	SWITCHIDx->SW11_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW12
	{
		GPIO_Configuration_IPU	(SWITCHIDx->SW12_PORT,	SWITCHIDx->SW12_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW13
	{
		GPIO_Configuration_IPU	(SWITCHIDx->SW13_PORT,	SWITCHIDx->SW13_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW14
	{
		GPIO_Configuration_IPU	(SWITCHIDx->SW14_PORT,	SWITCHIDx->SW14_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW15
	{
		GPIO_Configuration_IPU	(SWITCHIDx->SW15_PORT,	SWITCHIDx->SW15_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
		NumOfSW-=1;
	}
	if(NumOfSW)	//SW16
	{
		GPIO_Configuration_IPU	(SWITCHIDx->SW16_PORT,	SWITCHIDx->SW16_Pin);			//��GPIO��Ӧ�ܽ�����Ϊ��������ģʽ----V20170605
		NumOfSW-=1;
	}
}
/****************************************************************
*������:
*����:
*
******************************************************************/
unsigned long SWITCHIDRead(SWITCHID_CONF *SWITCHIDx)
{
	unsigned long	reValue=0;	
	unsigned long *P=(unsigned long*)&SWITCHIDx->sID_Data16.Data16;		//��ȡ���ݽṹ���ַ,�Ա㽫��ȡ�����ݱ���	
	unsigned char NumOfSW=SWITCHIDx->NumOfSW;		//����İ��뿪��λ��
	//���ݽ���İ��뿪��λ���ӵ�λ����λ���ж�ȡ
	if(NumOfSW)	//SW1
	{
		NumOfSW-=1;
		if(SWITCHIDx->SW1_PORT-> IDR	&SWITCHIDx->SW1_Pin)
			reValue|=0x0001<<0;
	}
	if(NumOfSW)	//SW2
	{
		NumOfSW-=1;
		if(SWITCHIDx->SW2_PORT-> IDR	&SWITCHIDx->SW2_Pin)
			reValue|=0x0001<<1;
	}
	if(NumOfSW)	//SW3
	{
		NumOfSW-=1;
		if(SWITCHIDx->SW3_PORT-> IDR	&SWITCHIDx->SW3_Pin)
			reValue|=0x0001<<2;
	}
	if(NumOfSW)	//SW4
	{
		NumOfSW-=1;
		if(SWITCHIDx->SW4_PORT-> IDR	&SWITCHIDx->SW4_Pin)
			reValue|=0x0001<<3;
	}
	if(NumOfSW)	//SW5
	{
		NumOfSW-=1;
		if(SWITCHIDx->SW5_PORT-> IDR	&SWITCHIDx->SW5_Pin)
			reValue|=0x0001<<4;
	}
	if(NumOfSW)	//SW6
	{
		NumOfSW-=1;
		if(SWITCHIDx->SW6_PORT-> IDR	&SWITCHIDx->SW6_Pin)
			reValue|=0x0001<<5;
	}
	if(NumOfSW)	//SW7
	{
		NumOfSW-=1;
		if(SWITCHIDx->SW7_PORT-> IDR	&SWITCHIDx->SW7_Pin)
			reValue|=0x0001<<6;
	}
	if(NumOfSW)	//SW8
	{
		NumOfSW-=1;
		if(SWITCHIDx->SW8_PORT-> IDR	&SWITCHIDx->SW8_Pin)
			reValue|=0x0001<<7;
	}
	if(NumOfSW)	//SW9
	{
		NumOfSW-=1;
		if(SWITCHIDx->SW9_PORT-> IDR	&SWITCHIDx->SW9_Pin)
			reValue|=0x0001<<8;
	}
	if(NumOfSW)	//SW10
	{
		NumOfSW-=1;
		if(SWITCHIDx->SW10_PORT-> IDR	&SWITCHIDx->SW10_Pin)
			reValue|=0x0001<<9;
	}
	if(NumOfSW)	//SW11
	{
		NumOfSW-=1;
		if(SWITCHIDx->SW11_PORT-> IDR	&SWITCHIDx->SW11_Pin)
			reValue|=0x0001<<10;
	}
	if(NumOfSW)	//SW12
	{
		NumOfSW-=1;
		if(SWITCHIDx->SW12_PORT-> IDR	&SWITCHIDx->SW12_Pin)
			reValue|=0x0001<<11;
	}
	if(NumOfSW)	//SW13
	{
		NumOfSW-=1;
		if(SWITCHIDx->SW13_PORT-> IDR	&SWITCHIDx->SW13_Pin)
			reValue|=0x0001<<12;
	}
	if(NumOfSW)	//SW14
	{
		NumOfSW-=1;
		if(SWITCHIDx->SW14_PORT-> IDR	&SWITCHIDx->SW14_Pin)
			reValue|=0x0001<<13;
	}
	if(NumOfSW)	//SW15
	{
		NumOfSW-=1;
		if(SWITCHIDx->SW15_PORT-> IDR	&SWITCHIDx->SW15_Pin)
			reValue|=0x0001<<14;
	}
	if(NumOfSW)	//SW16
	{
		NumOfSW-=1;
		if(SWITCHIDx->SW16_PORT-> IDR	&SWITCHIDx->SW16_Pin)
			reValue|=0x0001<<15;
	}
	reValue^=0xFFFF;		//���뿪�ص���Ч,��Ҫȡ��
	*P=reValue;
	SWITCHIDx->nID_Data16=reValue;
	return	reValue;	//�����ݷ���(�����Ҫֱ�ӻ�ȡ��ȡֵ����ʹ�÷���ֵ)
}
