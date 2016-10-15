#ifndef _UTIL_H_
#define _UTIL_H_

#include <afxwin.h>

enum //�Զ���Э��
{
	USER_LOAD = 0,              //�û���½
	USER_LOAD_SUCCEED,          //��¼�ɹ�
	USER_LOAD_LOSS_HAS_USER,	//��¼ʧ��(�û��ѵ�¼)
	USER_LOAD_LOSS_NO_USER,     //��¼ʧ��(�û���������)
	USER_LOAD_LOSS_ERROR_PSW,	//��¼ʧ��(�������)

	USER_REGISTER,              //�û�ע��
	USER_REGISTER_SUCCEED,      //ע��ɹ�
	USER_REGISTER_LOSS_HAS_USER,//ע��ʧ��(�û����Ѵ���)
	USER_REGISTER_LOSS_ERROR,	//ע��ʧ��(δ֪ԭ��)
	USER_REGISTER_STOP,			//ע�ᱻ��ֹ

	USER_UPDATE_PWD,            //�û������޸�
	USER_UPDATE_PWD_SUCCEED,    //��������ɹ�
	USER_UPDATE_PWD_ERROR,		//�������루���������
	USER_UPDATE_PWD_LOSS,       //��������ʧ��

	USER_UPDATE_NOTICE,         //�û��������
	USER_UPDATE_NOTICE_SUCCEED, //���¹���ɹ�
	USER_UPDATE_NOTICE_LOSS,    //���¹���ʧ��

	USER_MSGTOALL,              //������Ϣ�����е���
	USER_MSGTOPERSONAL,         //������Ϣ��˽��
	USER_STOP_MSG,				//�����û�

	USER_OUT_USER,				//�߳��û�
	USER_DELETE_USER,			//ɾ���û�

	USER_USERNAMELIST,          //�û��б�
	USER_SYSTEMNOTICE,			//ϵͳ����
	USER_PERSONNOTICE,			//�����û���������
	USER_NOTICELIST,            //�û������б�

	USER_EXIT,
};

struct UserMsg
{
	int Protocol;              //Э�� 	
	TCHAR UserName[20];        //�û���	
	TCHAR UserPwd[20];         //����	
	TCHAR m_FontName[20];
	int m_FontSize;
	BOOL bIsBold;	//����
	BOOL bIsItalic;	//б��
	BOOL bIsUnderline;//�»���
	COLORREF crColor;
	TCHAR UserNotice[300];     //����
	TCHAR Msg[5000];            //���յ���Ϣ
};

struct UserInfo
{
	CString UserName;          //�û��ǳ�
	CString IP;                //�û�IP
	SOCKET socket;             //�û����׽���
	bool operator==(const UserInfo &uInfo) const
	{
		if (socket == uInfo.socket)
			return true;
		return false;
	}
};

#endif