#ifdef OLED096_TEST
#include "OLED096_TEST.H"

#include "STM32_SYS.H"
#include "STM32_PWM.H"

//#include "delay.h"
//#include "sys.h"
//#include "STM32_096OLED.h"
//#include "bmp.h"


#define STATUS_STALL			0			//δ����
#define STATUS_RUN				1			//��������
#define STATUS_CHARGE			2			//���/�ػ�
#define STATUS_FULLPOWER	3			//������


u32 running_time=0;
u32 led_time=0;
u32 cun_time=0;
u32 time_H=0;
u32 time_S=0;
u32 time_M=0;
u8 Status_run=0;

/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void OLED096_TEST_Configuration(void)
{
	u8 t;
	SYS_Configuration();				//ϵͳ����
	PWM_Configuration(TIM2,7200,10000,50);
	
	Status_run=STATUS_STALL;			//δ����
	OLED_Init();								//��ʼ��OLED 
	OLED_POWER_ON;
	Status_run=STATUS_RUN;		//��������
	OLED_Clear(); 
		t=' ';
		running_time=0;
		OLED_ShowNum(0,0,time_H,6,16);//��ʾASCII�ַ�����ֵ	cun_time
		OLED_ShowString(57,0,"-");
		OLED_ShowNum(65,0,time_M,2,16);//��ʾASCII�ַ�����ֵ	cun_time
		OLED_ShowString(81,0,"-");
		OLED_ShowNum(89,0,time_S,2,16);//��ʾASCII�ַ�����ֵ	cun_time
		
//	while(1) 
//	{		
//		if(running_time++>0x02)
//		{
//			led_time=0;
//			while(led_time++<=1000000)
//			{
//				if(led_time%2==0)
//				{
//					time_S++;
//					if(time_S>=60)
//					{
//						time_S=0;
//						time_M++;
//						if(time_M>=60)
//						{
//							time_M=0;
//							time_H++;
//							OLED_ShowNum(0,0,time_H,6,16);//��ʾASCII�ַ�����ֵ	cun_time
//						}
//						OLED_ShowNum(65,0,time_M,2,16);//��ʾASCII�ַ�����ֵ	cun_time
//					}
//					OLED_ShowNum(89,0,time_S,2,16);//��ʾASCII�ַ�����ֵ	cun_time
//				}
//				
//				
//				if(led_time%100<50)
//				{
//					OLED_LED_ON;					
////					OLED_ShowNum(60,0,led_time,6,16);//��ʾASCII�ַ�����ֵ	cun_time
//					OLED_ShowNum(60,2,led_time,6,16);//��ʾASCII�ַ�����ֵ
//					OLED_ShowNum(60,4,led_time,6,16);//��ʾASCII�ַ�����ֵ
//					OLED_ShowNum(60,6,led_time,6,16);//��ʾASCII�ַ�����ֵ
//				}
//				else
//					OLED_LED_OFF;
//				OLED_delayms(5);
////				OLED_ShowString(63,6,led_time);
//				OLED_ShowNum(0,6,led_time,6,16);//��ʾASCII�ַ�����ֵ
//			}
////			OLED_POWER_OFF;
//			OLED_Clear();
//			running_time=0;			
//		}
////		OLED_Clear();
////		OLED_LED_ON;
////		OLED_ShowCHinese(0,0,0);//��
////		OLED_ShowCHinese(18,0,1);//��
////		OLED_ShowCHinese(36,0,2);//԰
////		OLED_ShowCHinese(54,0,3);//��
////		OLED_ShowCHinese(72,0,4);//��
////		OLED_ShowCHinese(90,0,5);//��
////		OLED_ShowCHinese(108,0,6);//��
////		OLED_ShowString(0,3,"1.3' OLED TEST");
////		//OLED_ShowString(8,2,"ZHONGJINGYUAN");
////	 //	OLED_ShowString(20,4,"2014/05/01");
////		OLED_ShowString(0,6,"ASCII:");
//////		OLED_ShowString(63,6,"CODE:");
////		OLED_ShowString(63,6,"99%:");
////		OLED_ShowChar(48,6,t);//��ʾASCII�ַ�
////		t++;
////		if(t>'~')t=' ';
////		OLED_ShowNum(103,6,t,3,16);//��ʾASCII�ַ�����ֵ
//////		OLED_ShowNum(103,6,t,3,16);//��ʾASCII�ַ�����ֵ
////			
////	
////		OLED_delayms(1000);
////		OLED_Clear();
////		OLED_delayms(1000);
//////		LED_OFF;
////		OLED_DrawBMP(0,0,128,8,BMP1);  //ͼƬ��ʾ(ͼƬ��ʾ���ã����ɵ��ֱ��ϴ󣬻�ռ�ý϶�ռ䣬FLASH�ռ�8K��������)
////		OLED_delayms(1000);
////		OLED_DrawBMP(0,0,128,8,BMP2);
////		OLED_delayms(1000);
//	}
	
	
	
	
	
	
	
	
	
	
	
//	TIM_Configuration(TIM3,7200,10000);	//��ʱʱ���趨
//	PWM_Configuration(TIM2,7200,200,10);
//	USART_DMA_Configuration(USART1,115200,1,1,(u32*)ADC_TEST_BUFFER,(u32*)ADC_TEST_BUFFER,ADC_TEST_BUFFERSIZE);	//USART_DMA����
	
	
//	ADC1_DiscConfiguration((u32*)&ADCD,1,ADC_Channel_16,1,1,ADC_SampleTime_239Cycles5);				//ADC1����ͨ��������
	
//	ADC_TempSensorVrefintCmd(ENABLE);
//	ADC1_Cmd(ENABLE);					//����ADC1ת��
//	DAC_Configuration();
//	DAC_DMA_Configuration((u32*)&DACD);
//	ADC1_Cmd(ENABLE);					//����ADC1ת��
	
//	ADC_TempSensorConfiguration((u32*)&ADCD);		//STM32�ڲ��¶ȴ���������
	
//		ADC1_Init();
//	GPIO_Configuration(GPIOE,GPIO_Pin_All,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
//	GPIO_Configuration(GPIOA,GPIO_Pin_3,GPIO_Mode_Out_PP,GPIO_Speed_50MHz);
//	SysTick_Configuration(10000);	//ϵͳ���ʱ������72MHz,��λΪuS
	
}
/*******************************************************************************
* ������		:	
* ��������	:	 
* ����		:	
* ���		:
* ���� 		:
*******************************************************************************/
void OLED096_TEST_Server(void)
{
	
//	u8 t;
//	Status_run=STATUS_STALL;			//δ����
//	delay_init();	    	 				//��ʱ������ʼ��	  
//	NVIC_Configuration(); 	 		//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 	LED_Init();			     //LED�˿ڳ�ʼ��
//	OLED_Init();								//��ʼ��OLED 
//	POWER_ON;
//	Status_run=STATUS_RUN;		//��������
//	OLED_Clear(); 
//		/*
//		 OLED_ShowString(30,0,"OLED TEST");
//		OLED_ShowString(8,2,"ZHONGJINGYUAN");  
//		OLED_ShowString(20,4,"2014/05/01");  
//		OLED_ShowString(0,6,"ASCII:");  
//		OLED_ShowString(63,6,"CODE:");  
//		t=' '; 
//		OLED_ShowCHinese(0,0,0);//��
//		OLED_ShowCHinese(18,0,1);//��
//		OLED_ShowCHinese(36,0,2);//԰
//		OLED_ShowCHinese(54,0,3);//��
//		OLED_ShowCHinese(72,0,4);//��
//		OLED_ShowCHinese(90,0,5);//��
//		OLED_ShowCHinese(108,0,6);//��
//		*/	
//		t=' ';
//		running_time=0;
//		OLED_ShowNum(0,0,time_H,6,16);//��ʾASCII�ַ�����ֵ	cun_time
//		OLED_ShowString(57,0,"-");
//		OLED_ShowNum(65,0,time_M,2,16);//��ʾASCII�ַ�����ֵ	cun_time
//		OLED_ShowString(81,0,"-");
//		OLED_ShowNum(89,0,time_S,2,16);//��ʾASCII�ַ�����ֵ	cun_time
//		
//	while(1) 
//	{		
//		if(running_time++>0x02)
//		{
//			led_time=0;
//			while(led_time++<=1000000)
//			{
//				if(led_time%2==0)
//				{
//					time_S++;
//					if(time_S>=60)
//					{
//						time_S=0;
//						time_M++;
//						if(time_M>=60)
//						{
//							time_M=0;
//							time_H++;
//							OLED_ShowNum(0,0,time_H,6,16);//��ʾASCII�ַ�����ֵ	cun_time
//						}
//						OLED_ShowNum(65,0,time_M,2,16);//��ʾASCII�ַ�����ֵ	cun_time
//					}
//					OLED_ShowNum(89,0,time_S,2,16);//��ʾASCII�ַ�����ֵ	cun_time
//				}
//				
//				
//				if(led_time%100<50)
//				{
//					LED_ON;					
////					OLED_ShowNum(60,0,led_time,6,16);//��ʾASCII�ַ�����ֵ	cun_time
//					OLED_ShowNum(60,2,led_time,6,16);//��ʾASCII�ַ�����ֵ
//					OLED_ShowNum(60,4,led_time,6,16);//��ʾASCII�ַ�����ֵ
//					OLED_ShowNum(60,6,led_time,6,16);//��ʾASCII�ַ�����ֵ
//				}
//				else
//					LED_OFF;
//				delay_ms(5);
////				OLED_ShowString(63,6,led_time);
//				OLED_ShowNum(0,6,led_time,6,16);//��ʾASCII�ַ�����ֵ
//			}
////			POWER_OFF;
//			OLED_Clear();
//			running_time=0;			
//		}
//	}

}





#endif