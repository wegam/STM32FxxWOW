#ifndef __PC001V21_H
#define __PC001V21_H



void PC001V21_Configuration(void);
void PC001V21_Server(void);
void PC001V21_PinSet(void);
void PC001V21_USART_Conf(void);
void PC001V21_USART1_Server(void);
void PC001V21_4851_Server(void);
void PC001V21_4852_Server(void);
unsigned char PC001V21_GetSwitchID(void);				//��ȡ���뿪�ص�ַ
unsigned char PC001V21_GetBufferArray(void);		//��ȡ�������ADֵ
void DR_LOCK_OUT(unsigned char dr);	//����������
void DR_LOCK_Check(void);						//������״̬���
#endif
