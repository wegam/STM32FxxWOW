#ifndef __Message_H
#define __Message_H


//----------ͨ��Ӧ��
typedef	enum	_GENERAL_ACK	
{
	APP_GENERAL_ACK	=	0xFF,		//�������¼�֮���ͨ��Ӧ��
	APP_GENERAL_PAK	=	0x55,		//�������¼�֮�����Ӧ��
	APP_GENERAL_NAK	=	0xAA		//�������¼�֮��ĸ�Ӧ��
}GeneralAck;
//----------������
typedef	enum	_APP_CMD
{
	APP_CMD_GETTANKINFO			=	0x01,		//�õ���λ��Ϣ
	APP_CMD_TANKINFOREP			=	0x81,		//��λ��Ϣ�ϱ�
	APP_CMD_DISPEN					=	0x02,		//��ҩ
	APP_CMD_DISPENREP				=	0x82,		//��ҩ����ϱ�
	APP_CMD_TIEONCARD				=	0x03,		//��
	APP_CMD_TIEONCARDREP		=	0x83,		//�󿨽���ϱ�
	APP_CMD_SENDBASKET			=	0x04,		//����
	APP_CMD_SENDBASKETREP		=	0x84,		//��������ϱ�
	APP_CMD_SEATREP					=	0x85,		//״̬���߱�����Ϣ�ϱ�
	APP_CMD_STARTEXTTRANS		=	0x86,		//�����ⲿ������
	APP_CMD_CABASBASKETREP	=	0x87,		//������ϱ��������Ӻ�
	APP_CMD_MAJ2MINSENDINFO	=	0x88,		//M����������򸨻���ܷ���������Ϣ
	APP_CMD_CacheData				=	0x30,		//������Ϣ
	APP_CMD_ACMotorCtl			=	0x31,		//�����ߵ��������Ϣ
	APP_CMD_GetMasterID			=	0x32,		//����������ַ
	APP_CMD_SendMasterID		=	0x33		//����������ַ
}AppCmd;
//----------�豸״̬��Ϣ����Ŵ�0x00��0x3F
typedef	enum	_MSG_STATUS	
{
	MSG_STATUS_OK							=	0x00,	//����״̬��������������ı�����
	MSG_STATUS_BUSY						=	0x01,	//æ���޷���������д���
	MSG_STATUS_CACHEFULL			=	0x02,	//����ṹ����
	MSG_STATUS_CACHENONEMPTY	=	0x03	//����ṹ����
}MsgStatus;
//----------������Ϣ����Ŵ�0x40��0x7F
typedef	enum	_MSG_ERROR	
{
	MSG_ERROR_CMD							=	0x40,	//������󣬽��յ��Ƿ�������
	MSG_ERROR_PARAMETER				=	0x41,	//�������󣬽��յ��Ƿ��Ĳ���
	MSG_ERROR_BASKETNONSELF		=	0x42	//�������������Ӵ��ں��뵱ǰλ�ò�ƥ��
}MsgError;
//----------������Ϣ����Ŵ�0x80��0xBF
typedef	enum	_MSG_ALARM	
{
	MSG_ALARM_DRUGSTUCK				=	0x80,		//ҩƷ����ס
	MSG_ALARM_LACKDRUG				=	0x81,		//ȱҩ
	MSG_ALARM_WAITRESOT				=	0x82,		//�ȴ���������ʱ
	MSG_ALARM_SEPARATEMOTOR		=	0x83,		//�����������
	MSG_ALARM_FALLMOTOR				=	0x84,		//�����������
	MSG_ALARM_EMPTYBASKET			=	0x85,		//�����ṹ����
	MSG_ALARM_LACKBASKET			=	0x86,		//�����ṹȱ��
	MSG_ALARM_STUCKBASKET_PB	=	0x87,		//�����ṹ����,���ڷ����������������
	MSG_ALARM_BASKETREMOVED		=	0x88,		//�����ṹ�����Ѿ���ȡ��
	MSG_ALARM_STUCKBASKET_TD	=	0x89,		//��ҩ�����¿���
	MSG_ALARM_STUCKBASKET_TC	=	0x8A,		//��ҩ�������ṹ����
	MSG_ALARM_STUCKBASKET_C1	=	0x8B,		//������������1����
	MSG_ALARM_STUCKBASKET_C2	=	0x8C,		//������������2����
	MSG_ALARM_READCARD_FAIL		=	0x8D,		//��IC��ʧ��
	MSG_ALARM_WRITECARD_FAIL	=	0x8E,		//дIC��ʧ��,����û��д�뿨��
	MSG_ALARM_WRITECARD_ERR		=	0x8F		//дIC������,д�뿨�е����ݲ���
}MsgAlarm;
//----------�豸�쳣��Ϣ����Ŵ�0xC0��0xFF
typedef	enum	_MSG_TROUBLE	
{
	MSG_TROUBLE_UNITCONTROL		=	0xC0,	/*��Ԫ�������ͨ���쳣*/
	MSG_TROUBLE_DISPENLAYER		=	0xC1,	/*��ҩ�������ͨ���쳣*/
	MSG_TROUBLE_TIEONCARDOT		=	0xC2,	/*�󿨳�ʱ,��ʱ������Ϣ����*/
	MSG_TROUBLE_SENDBASKETOT	=	0xC3,	/*������ʱ,��ʱ������Ϣ����*/
	MSG_TROUBLE_READERCOMM		=	0xC4,	/*������ͨ���쳣*/
	MSG_TROUBLE_READER				=	0xC5	/*�������쳣*/
}MsgTrouble;

//----------�������ݴ��
typedef struct	_SYS_INFO
{
	GeneralAck 	SYSACK;		//----------ͨ��Ӧ��
	AppCmd			SYSCMD;		//----------������
	MsgStatus		SYSMSG;		//----------�豸״̬��Ϣ����Ŵ�0x00��0x3F
	MsgAlarm		SYSALM;		//----------������Ϣ����Ŵ�0x80��0xBF
	MsgTrouble	SYSTRB;		//----------�豸�쳣��Ϣ����Ŵ�0xC0��0xFF
}SYS_INFO;







#endif
