
// MFCChatServerDlg.h : 头文件
//

#pragma once

#include <list>
using namespace std;

#include "Util.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "RichEditCtrlEx.h"
#include "BmpPicker.h"

#define WM_ACCEPT WM_USER+100
#define WM_RECIEVE WM_USER+101

#define MSG_MY_COLOR RGB(0,128,64)
#define MSG_USER_COLOR RGB(0,110,254)
#define MSG_SYSTEM_COLOR RGB(0,0,255)

// CMFCChatServerDlg 对话框
class CMFCChatServerDlg : public CDialogEx
{
// 构造
public:
	CMFCChatServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCCHATSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	bool m_bIsStart;
	SOCKET m_serverSocket;
	list<UserInfo> m_userInfoList;
	BOOL WinSockInit();
	void StopServer();

public:
	UINT m_port;
	DWORD m_ipAddress;
	CComboBox m_FontName;
	CComboBox m_FontSize;
	bool bIsBold;
	afx_msg void OnBtnStartServer();
	afx_msg void OnBtnSend();
	afx_msg void OnBtnClose();
	
	CRichEditCtrlEx m_RichLog;
	CRichEditCtrlEx m_RichEdit;

	static UINT __cdecl ThreadProc(LPVOID pParam);

protected:
	afx_msg LRESULT OnMsgRecv(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgAccept(WPARAM wParam, LPARAM lParam);
private:
	
public:
	void FindUserInfo(UserInfo &sClient);
	void SendMsgToAll(const UserMsg& uMsg);
	void SendMsgToPersonal(UserMsg& uMsg, CString srcUser);
	
	CBmpPicker m_BmpPicker;
};
