
#include "DMAH20160808.H"

//u32 *DMA_Buffer;
//u8	DMA_BufferSize=0;
/*******************************************************************************
*������		:DMA_Configuration
*��������	:��������
*����			:MemoryAddr--�ڴ��ַ,
					 BufferSize--�����С
*���			:��
*����ֵ		:��
*����			��
*******************************************************************************/
void DMA_Configuration(DMA_Channel_TypeDef* DMAy_Channelx,u32 *MemoryAddr,u32 BufferSize)	//USART1_DMA����
{
	DMA_InitTypeDef    DMA_Initstructure;
	NVIC_InitTypeDef   NVIC_Initstructure;
	
	/*����DMAʱ��*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);	
	
	/* Enable the DMA1 Interrupt */
	NVIC_Initstructure.NVIC_IRQChannel = DMA1_Channel4_IRQChannel;       		//ͨ������Ϊ����1�ж�
	NVIC_Initstructure.NVIC_IRQChannelSubPriority = 0;     									//�ж���Ӧ���ȼ�0
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;        									//���ж�
	NVIC_Init(&NVIC_Initstructure);

	/*DMA��������*/
	DMA_Initstructure.DMA_PeripheralBaseAddr =  (u32)(&USART1->DR);					//DMA����Դ��ַ
	DMA_Initstructure.DMA_MemoryBaseAddr     = (u32)MemoryAddr;							//DMA�����ڴ��ַ
	DMA_Initstructure.DMA_DIR = DMA_DIR_PeripheralDST;											//DMA_DIR_PeripheralDST��������ΪDMA��Ŀ�Ķˣ���DMA_DIR_PeripheralSRC��������Ϊ���ݴ������Դ��
	DMA_Initstructure.DMA_BufferSize = BufferSize; 													//ָ��DMAͨ����DMA����Ĵ�С
//	DMA_Initstructure.DMA_BufferSize = sizeof(MemoryAddr[0]); 													//ָ��DMAͨ����DMA����Ĵ�С
	DMA_Initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;				//DMA_PeripheralInc_Enable�������ַ�Ĵ�����������DMA_PeripheralInc_Disable�������ַ�Ĵ������䣩��
	DMA_Initstructure.DMA_MemoryInc =DMA_MemoryInc_Enable;									//DMA_MemoryInc_Enable���ڴ��ַ�Ĵ�����������DMA_MemoryInc_Disable���ڴ��ַ�Ĵ������䣩
	DMA_Initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//�������ݿ���--DMA_PeripheralDataSize_Byte�����ݿ���Ϊ8λ����DMA_PeripheralDataSize_HalfWord�����ݿ���Ϊ16λ����DMA_PeripheralDataSize_Word�����ݿ���Ϊ32λ��
	DMA_Initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;					//�ڴ����ݿ���--DMA_MemoryDataSize_Byte�����ݿ���Ϊ8λ����DMA_MemoryDataSize_HalfWord�����ݿ���Ϊ16λ����DMA_MemoryDataSize_Word �����ݿ���Ϊ32λ��
	DMA_Initstructure.DMA_Mode = DMA_Mode_Normal;														//DMA����ģʽ--DMA_Mode_Normal��ֻ����һ�Σ�, DMA_Mode_Circular ����ͣ�ش��ͣ�
	DMA_Initstructure.DMA_Priority = DMA_Priority_High; 										//DMAͨ����ת�����ȼ�--DMA_Priority_VeryHigh���ǳ��ߣ�DMA_Priority_High����)��DMA_Priority_Medium���У���DMA_Priority_Low���ͣ�
	DMA_Initstructure.DMA_M2M = DMA_M2M_Disable;														//DMAͨ�����ڴ浽�ڴ洫��--DMA_M2M_Enable(����Ϊ�ڴ浽�ڴ洫��)��DMA_M2M_Disable�����ڴ浽�ڴ洫�䣩
	DMA_Init(DMAy_Channelx,&DMA_Initstructure);															//��ʼ��DMA

	/* ���DMA1ͨ��4���б�־*/
	DMA_ClearFlag(DMA1_FLAG_GL4);                                 					// ���DMA���б�־
	/* �ر�DMA1ͨ��5*/
	DMA_Cmd(DMAy_Channelx,DISABLE);
	/* ʹ��DMA1ͨ��4��������ж� */
	DMA_ITConfig(DMAy_Channelx,DMA_IT_TC, ENABLE);


	/*DMA��������*/
	DMA_Initstructure.DMA_PeripheralBaseAddr =  (u32)(&USART1->DR);					//DMA����Դ��ַ
	DMA_Initstructure.DMA_MemoryBaseAddr     = 	(u32)MemoryAddr;						//DMA�����ڴ��ַ
	DMA_Initstructure.DMA_DIR = DMA_DIR_PeripheralSRC;											//DMA_DIR_PeripheralDST��������ΪDMA��Ŀ�Ķˣ���DMA_DIR_PeripheralSRC��������Ϊ���ݴ������Դ��
	DMA_Initstructure.DMA_BufferSize = BufferSize; 												//ָ��DMAͨ����DMA����Ĵ�С
//	DMA_Initstructure.DMA_BufferSize = sizeof(MemoryAddr); 									//ָ��DMAͨ����DMA����Ĵ�С
	DMA_Initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;				//DMA_PeripheralInc_Enable�������ַ�Ĵ�����������DMA_PeripheralInc_Disable�������ַ�Ĵ������䣩��
	DMA_Initstructure.DMA_MemoryInc =DMA_MemoryInc_Enable;									//DMA_MemoryInc_Enable���ڴ��ַ�Ĵ�����������DMA_MemoryInc_Disable���ڴ��ַ�Ĵ������䣩
	DMA_Initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//�������ݿ���--DMA_PeripheralDataSize_Byte�����ݿ���Ϊ8λ����DMA_PeripheralDataSize_HalfWord�����ݿ���Ϊ16λ����DMA_PeripheralDataSize_Word�����ݿ���Ϊ32λ��
	DMA_Initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;					//�ڴ����ݿ���--DMA_MemoryDataSize_Byte�����ݿ���Ϊ8λ����DMA_MemoryDataSize_HalfWord�����ݿ���Ϊ16λ����DMA_MemoryDataSize_Word �����ݿ���Ϊ32λ��
	DMA_Initstructure.DMA_Mode = DMA_Mode_Normal;														//DMA����ģʽ--DMA_Mode_Normal��ֻ����һ�Σ�, DMA_Mode_Circular ����ͣ�ش��ͣ�
	DMA_Initstructure.DMA_Priority = DMA_Priority_High; 										//DMAͨ����ת�����ȼ�--DMA_Priority_VeryHigh���ǳ��ߣ�DMA_Priority_High����)��DMA_Priority_Medium���У���DMA_Priority_Low���ͣ�
	DMA_Initstructure.DMA_M2M = DMA_M2M_Disable;														//DMAͨ�����ڴ浽�ڴ洫��--DMA_M2M_Enable(����Ϊ�ڴ浽�ڴ洫��)��DMA_M2M_Disable�����ڴ浽�ڴ洫�䣩
	DMA_Init(DMA1_Channel5,&DMA_Initstructure);															//��ʼ��DMA
	
	/* ���DMA1ͨ��5���б�־*/
	DMA_ClearFlag(DMA1_FLAG_GL5);                                 					// ���DMA���б�־
	/* ����DMA1ͨ��5*/
	DMA_Cmd(DMA1_Channel5,ENABLE);
}
/*******************************************************************************
*������		:USART_DMA_Configuration
*��������	:��������
*����			:MemoryAddr--�ڴ��ַ,
					 BufferSize--�����С
*���			:��
*����ֵ		:��
*����			��
*******************************************************************************/
void USART_DMA_Configuration(USART_TypeDef* USARTx,u32 *MemoryAddr,u32 BufferSize)	//USART_DMA����
{
	DMA_InitTypeDef    DMA_Initstructure;
	NVIC_InitTypeDef   NVIC_Initstructure;
	
	DMA_Channel_TypeDef* DMAx_Channeltx=0;
	DMA_Channel_TypeDef* DMAx_Channelrx=0;
	u8 DMAx_Channelx_IRQChannel=0;
	u32 DMAx_FLAG_GLtx=0;
	u32 DMAx_FLAG_GLrx=0;
	
	/*����DMAʱ��*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);	
	
	/*����*/
	if(USARTx==USART1)
	{
		DMAx_Channeltx=DMA1_Channel4;
		DMAx_Channelrx=DMA1_Channel5;
		DMAx_Channelx_IRQChannel=DMA1_Channel4_IRQChannel;
		DMAx_FLAG_GLtx=DMA1_FLAG_GL4;
		DMAx_FLAG_GLrx=DMA1_FLAG_GL5;
	}
	else if(USARTx==USART2)
	{
		DMAx_Channeltx=DMA1_Channel7;
		DMAx_Channelrx=DMA1_Channel6;
		DMAx_Channelx_IRQChannel=DMA1_Channel7_IRQChannel;
		DMAx_FLAG_GLtx=DMA1_FLAG_GL7;
		DMAx_FLAG_GLrx=DMA1_FLAG_GL6;
	}
	else if(USARTx==USART3)
	{
		DMAx_Channeltx=DMA1_Channel2;
		DMAx_Channelrx=DMA1_Channel3;
		DMAx_Channelx_IRQChannel=DMA1_Channel2_IRQChannel;
		DMAx_FLAG_GLtx=DMA1_FLAG_GL2;
		DMAx_FLAG_GLrx=DMA1_FLAG_GL3;
	}
	else if(USARTx==UART4)
	{
		DMAx_Channeltx=DMA2_Channel5;
		DMAx_Channelrx=DMA2_Channel3;
		DMAx_Channelx_IRQChannel=DMA2_Channel3_IRQChannel;
		DMAx_FLAG_GLtx=DMA2_FLAG_GL5;
		DMAx_FLAG_GLrx=DMA2_FLAG_GL3;
	}
	else if(USARTx==UART5)
	{
	}
	
	/* Enable the DMA1 Interrupt */
	NVIC_Initstructure.NVIC_IRQChannel = DMAx_Channelx_IRQChannel;       		//ͨ������Ϊ����1�ж�
	NVIC_Initstructure.NVIC_IRQChannelSubPriority = 1;     									//�ж���Ӧ���ȼ�0
	NVIC_Initstructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_Initstructure.NVIC_IRQChannelCmd = ENABLE;        									//���ж�
	NVIC_Init(&NVIC_Initstructure);

	/*DMA��������*/
	DMA_Initstructure.DMA_PeripheralBaseAddr =  (u32)(&USARTx->DR);					//DMA����Դ��ַ
	DMA_Initstructure.DMA_MemoryBaseAddr     = (u32)MemoryAddr;							//DMA�����ڴ��ַ
	DMA_Initstructure.DMA_DIR = DMA_DIR_PeripheralDST;											//DMA_DIR_PeripheralDST��������ΪDMA��Ŀ�Ķˣ���DMA_DIR_PeripheralSRC��������Ϊ���ݴ������Դ��
	DMA_Initstructure.DMA_BufferSize = BufferSize; 													//ָ��DMAͨ����DMA����Ĵ�С
//	DMA_Initstructure.DMA_BufferSize = sizeof(MemoryAddr[0]); 													//ָ��DMAͨ����DMA����Ĵ�С
	DMA_Initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;				//DMA_PeripheralInc_Enable�������ַ�Ĵ�����������DMA_PeripheralInc_Disable�������ַ�Ĵ������䣩��
	DMA_Initstructure.DMA_MemoryInc =DMA_MemoryInc_Enable;									//DMA_MemoryInc_Enable���ڴ��ַ�Ĵ�����������DMA_MemoryInc_Disable���ڴ��ַ�Ĵ������䣩
	DMA_Initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//�������ݿ���--DMA_PeripheralDataSize_Byte�����ݿ���Ϊ8λ����DMA_PeripheralDataSize_HalfWord�����ݿ���Ϊ16λ����DMA_PeripheralDataSize_Word�����ݿ���Ϊ32λ��
	DMA_Initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;					//�ڴ����ݿ���--DMA_MemoryDataSize_Byte�����ݿ���Ϊ8λ����DMA_MemoryDataSize_HalfWord�����ݿ���Ϊ16λ����DMA_MemoryDataSize_Word �����ݿ���Ϊ32λ��
	DMA_Initstructure.DMA_Mode = DMA_Mode_Normal;														//DMA����ģʽ--DMA_Mode_Normal��ֻ����һ�Σ�, DMA_Mode_Circular ����ͣ�ش��ͣ�
	DMA_Initstructure.DMA_Priority = DMA_Priority_High; 										//DMAͨ����ת�����ȼ�--DMA_Priority_VeryHigh���ǳ��ߣ�DMA_Priority_High����)��DMA_Priority_Medium���У���DMA_Priority_Low���ͣ�
	DMA_Initstructure.DMA_M2M = DMA_M2M_Disable;														//DMAͨ�����ڴ浽�ڴ洫��--DMA_M2M_Enable(����Ϊ�ڴ浽�ڴ洫��)��DMA_M2M_Disable�����ڴ浽�ڴ洫�䣩
	DMA_Init(DMAx_Channeltx,&DMA_Initstructure);															//��ʼ��DMA

	/* ���DMA1ͨ��4���б�־*/
	DMA_ClearFlag(DMAx_FLAG_GLtx);                                 					// ���DMA���б�־
	/* �ر�DMA1ͨ��5*/
	DMA_Cmd(DMAx_Channeltx,DISABLE);
	/* ʹ��DMA1ͨ��4��������ж� */
	DMA_ITConfig(DMAx_Channeltx,DMA_IT_TC, ENABLE);


	/*DMA��������*/
	DMA_Initstructure.DMA_PeripheralBaseAddr =  (u32)(&USARTx->DR);					//DMA����Դ��ַ
	DMA_Initstructure.DMA_MemoryBaseAddr     = 	(u32)MemoryAddr;						//DMA�����ڴ��ַ
	DMA_Initstructure.DMA_DIR = DMA_DIR_PeripheralSRC;											//DMA_DIR_PeripheralDST��������ΪDMA��Ŀ�Ķˣ���DMA_DIR_PeripheralSRC��������Ϊ���ݴ������Դ��
	DMA_Initstructure.DMA_BufferSize = BufferSize; 												//ָ��DMAͨ����DMA����Ĵ�С
//	DMA_Initstructure.DMA_BufferSize = sizeof(MemoryAddr); 									//ָ��DMAͨ����DMA����Ĵ�С
	DMA_Initstructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;				//DMA_PeripheralInc_Enable�������ַ�Ĵ�����������DMA_PeripheralInc_Disable�������ַ�Ĵ������䣩��
	DMA_Initstructure.DMA_MemoryInc =DMA_MemoryInc_Enable;									//DMA_MemoryInc_Enable���ڴ��ַ�Ĵ�����������DMA_MemoryInc_Disable���ڴ��ַ�Ĵ������䣩
	DMA_Initstructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//�������ݿ���--DMA_PeripheralDataSize_Byte�����ݿ���Ϊ8λ����DMA_PeripheralDataSize_HalfWord�����ݿ���Ϊ16λ����DMA_PeripheralDataSize_Word�����ݿ���Ϊ32λ��
	DMA_Initstructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;					//�ڴ����ݿ���--DMA_MemoryDataSize_Byte�����ݿ���Ϊ8λ����DMA_MemoryDataSize_HalfWord�����ݿ���Ϊ16λ����DMA_MemoryDataSize_Word �����ݿ���Ϊ32λ��
	DMA_Initstructure.DMA_Mode = DMA_Mode_Normal;														//DMA����ģʽ--DMA_Mode_Normal��ֻ����һ�Σ�, DMA_Mode_Circular ����ͣ�ش��ͣ�
	DMA_Initstructure.DMA_Priority = DMA_Priority_High; 										//DMAͨ����ת�����ȼ�--DMA_Priority_VeryHigh���ǳ��ߣ�DMA_Priority_High����)��DMA_Priority_Medium���У���DMA_Priority_Low���ͣ�
	DMA_Initstructure.DMA_M2M = DMA_M2M_Disable;														//DMAͨ�����ڴ浽�ڴ洫��--DMA_M2M_Enable(����Ϊ�ڴ浽�ڴ洫��)��DMA_M2M_Disable�����ڴ浽�ڴ洫�䣩
	DMA_Init(DMAx_Channelrx,&DMA_Initstructure);															//��ʼ��DMA
	
	/* ���DMA1ͨ��5���б�־*/
	DMA_ClearFlag(DMAx_FLAG_GLrx);                                 					// ���DMA���б�־
	/* ����DMA1ͨ��5*/
	DMA_Cmd(DMAx_Channelrx,ENABLE);	
}
/*******************************************************************************
*������		:DMA_Server
*��������	:DMA�жϷ�����
*����			: 
*���			:��
*����ֵ		:��
*����			��
*******************************************************************************/
void DMA_Server(void)
{ 
#ifdef	RS485_TO_USART_PRJ
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);	
#endif
#ifdef	PD002T20_PRJ
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);	
#endif
	/***USART1-TXD***/
	if(DMA_GetITStatus(DMA1_IT_TC4)== SET)
	{
		/*�����־λ*/
		DMA_ClearFlag(DMA1_FLAG_TC4); 
		/*�ر�DMA����*/ 
		DMA_Cmd(DMA1_Channel4,DISABLE);
	}
	/***USART2-TXD***/
	else if(DMA_GetITStatus(DMA1_IT_TC7)== SET)
	{
			/*�����־λ*/
		DMA_ClearFlag(DMA1_FLAG_TC7); 
		/*�ر�DMA����*/ 
		DMA_Cmd(DMA1_Channel7,DISABLE); 
	}
	/***USART3-TXD***/
	else if(DMA_GetITStatus(DMA1_IT_GL2)== SET)
	{
			/*�����־λ*/
		DMA_ClearFlag(DMA1_FLAG_TC2); 
		/*�ر�DMA����*/ 
		DMA_Cmd(DMA1_Channel2,DISABLE); 
	}
	/***USART4-TXD***/
	else if(DMA_GetITStatus(DMA2_IT_GL5)== SET)
	{
			/*�����־λ*/
		DMA_ClearFlag(DMA2_FLAG_TC5); 
		/*�ر�DMA����*/ 
		DMA_Cmd(DMA2_Channel5,DISABLE); 
	}
	/***ADC***/
	else if(DMA_GetITStatus(DMA1_IT_GL1)== SET)
	{
		DMA_Cmd(DMA1_Channel1,DISABLE);
		USER_Server();
			/*�����־λ*/
		DMA_ClearFlag(DMA1_FLAG_TC1); 
		/*�ر�DMA����*/ 
		DMA_Cmd(DMA1_Channel1,ENABLE);
			
	}
}