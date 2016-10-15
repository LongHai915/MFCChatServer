
// MFCChatServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCChatServerDlg �Ի���



CMFCChatServerDlg::CMFCChatServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCChatServerDlg::IDD, pParent)
	, m_port(0)
	, m_ipAddress(0)
	, bIsBold(false)
	, m_bIsStart(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PORT, m_port);
	DDX_IPAddress(pDX, IDC_IPADDRESS_IP, m_ipAddress);
	DDX_Control(pDX, IDC_CB_FONTNAME, m_FontName);
	DDX_Control(pDX, IDC_CB_FONTSIZE, m_FontSize);
	DDX_Control(pDX, IDC_RICHEDIT_MSG1, m_RichLog);
	DDX_Control(pDX, IDC_RICHEDIT_MSG2, m_RichEdit);
	DDX_Control(pDX, IDC_BTN_FACE, m_BmpPicker);
}

BEGIN_MESSAGE_MAP(CMFCChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START_SERVER, &CMFCChatServerDlg::OnBtnStartServer)
	ON_BN_CLICKED(IDC_BTN_SEND, &CMFCChatServerDlg::OnBtnSend)
	ON_BN_CLICKED(IDC_BTN_CLOSE, &CMFCChatServerDlg::OnBtnClose)
	ON_MESSAGE(WM_ACCEPT, &CMFCChatServerDlg::OnMsgAccept)
	ON_MESSAGE(WM_RECIEVE, &CMFCChatServerDlg::OnMsgRecv)
END_MESSAGE_MAP()


// CMFCChatServerDlg ��Ϣ�������

BOOL CMFCChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	char sHostName[100];
	gethostname(sHostName, sizeof(sHostName));
	struct hostent FAR * lpHostEnt = gethostbyname(sHostName);
	if (lpHostEnt == NULL)
	{
		MessageBox(_T("error"));
	}
	//��ȡIP
	LPSTR lpAddr = lpHostEnt->h_addr_list[0];
	if (lpAddr)
	{
		struct in_addr inAddr;
		memmove(&inAddr, lpAddr, 4);
		DWORD  dw1 = inet_addr(inet_ntoa(inAddr));
		m_ipAddress = htonl(dw1); //�������ֽ�˳���Ϊ�����ֽ�˳��
		//UpdateData(FALSE);
	}
	CEdit *ce = (CEdit*)GetDlgItem(IDC_EDIT_PORT);
	CRect rect;
	ce->GetClientRect(&rect); //hwndEditΪ�༭��Ķ���
	//�������ݵ�,��߾����ϱ߾�
	::OffsetRect(&rect, 0, 4);
	::SendMessage(ce->m_hWnd, EM_SETRECT, 0, (LPARAM)&rect);
	m_port = 5566;
	UpdateData(FALSE);
		//WORD  wd1 = LOWORD(dw1);//ȡ��ʮ��λ
		//WORD  wd2 = HIWORD(dw1);//ȡ��ʮ��λ
		//BYTE  bte1 = LOBYTE(wd1);
		//BYTE  bte2 = HIBYTE(wd1);
		//BYTE  bte3 = LOBYTE(wd2);
		//BYTE  bte4 = HIBYTE(wd2);
		//m_ipAddress.SetAddress(bte1, bte2, bte3, bte4);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCChatServerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/************************************************************************/
/* ��ʼ���׽ӿ�                                                          */
/************************************************************************/
BOOL CMFCChatServerDlg::WinSockInit()
{
	WSADATA wsaData = { 0 };
	WORD wRequestVersion = MAKEWORD(2, 2);
	if (WSAStartup(wRequestVersion, &wsaData))
	{
		MessageBox(_T("wsa loads failed."), _T("Error"), MB_OK | MB_ICONERROR);
		return false;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		MessageBox(_T("wsa version error."), _T("Error"), MB_OK | MB_ICONERROR);
		WSACleanup();
		return false;
	}
	return true;
}
/************************************************************************/
/* �ر��׽���                                                           */
/************************************************************************/
void CMFCChatServerDlg::StopServer()
{
	
	if (INVALID_SOCKET == m_serverSocket)
		closesocket(m_serverSocket);
	WSACleanup();
	m_RichLog.AddMessageUser(_T("system info: server is stopped."), RGB(255,0,0));
	/*POSITION pos = m_userInfoList.GetHeadPosition();
	UserInfo *uInfo = NULL;
	while (pos)
	{
		uInfo = (UserInfo *)m_userInfoList.GetNext(pos);
		if (SOCKET_ERROR == closesocket(uInfo->socket))
			TRACE(_T("system info: close client socket failed: %d"), WSAGetLastError());
	}*/
	m_userInfoList.clear();
}
/************************************************************************/
/* ���������߳�                                                          */
/************************************************************************/
UINT CMFCChatServerDlg::ThreadProc(LPVOID pParam)
{
	VERIFY(pParam);
	CMFCChatServerDlg *pThis = (CMFCChatServerDlg*)pParam;
	CString sIP;
	pThis->WinSockInit();
	pThis->m_serverSocket = INVALID_SOCKET;
	pThis->m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	BOOL bReuseaddr = TRUE;
	setsockopt(pThis->m_serverSocket, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (const char*)&bReuseaddr, sizeof(BOOL));
	if (INVALID_SOCKET == pThis->m_serverSocket)
	{
		TRACE(_T("system info: create socket failed: %d\n"), WSAGetLastError());
		//pThis->m_RichLog.AddMessageUser(_T("system info: create socket failed..."), MSG_SYSTEM_COLOR);
		//((CEdit*)pThis->GetDlgItem(IDC_BTN_START_SERVER))->ShowBalloonTip(_T("Error"), _T("create socket failed."), TTI_ERROR_LARGE);
		goto _Error_End;
		/*closesocket(pThis->m_serverSocket);
		WSACleanup();
		return -1;*/
	}
	TRACE(_T("system info: create socket success...\n"));
	//pThis->m_RichLog.AddMessageUser(_T("system info: create socket success..."), MSG_SYSTEM_COLOR);
	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.S_un.S_addr = htonl(pThis->m_ipAddress);
	serverAddr.sin_port = htons(pThis->m_port);
	if (bind(pThis->m_serverSocket, (sockaddr *)&serverAddr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		TRACE(_T("system info: binding failed, please check ip or port: %d\n"), WSAGetLastError());
		//pThis->m_RichLog.AddMessageUser(_T("system info: binding failed, please check ip or port..."), MSG_SYSTEM_COLOR);
		//((CEdit*)pThis->GetDlgItem(IDC_BTN_START_SERVER))->ShowBalloonTip(_T("Error"), _T("failed, please check ip or port."), TTI_ERROR_LARGE);
		goto _Error_End;
		/*closesocket(pThis->m_serverSocket);
		WSACleanup();
		return -1;*/
	}
	TRACE(_T("system info: binding success...\n"));
	//pThis->m_RichLog.AddMessageUser(_T("system info: binding success..."), MSG_SYSTEM_COLOR);
	if (listen(pThis->m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		TRACE(_T("system info: listen socket failed: %d\n"), WSAGetLastError());
		//pThis->m_RichLog.AddMessageUser(_T("system info: listen socket failed..."), MSG_SYSTEM_COLOR);
		//((CEdit*)pThis->GetDlgItem(IDC_BTN_START_SERVER))->ShowBalloonTip(_T("Error"), _T("listen socket failed."), TTI_ERROR_LARGE);
		goto _Error_End;
		/*closesocket(pThis->m_serverSocket);
		WSACleanup();
		return -1;*/
	}
	WSAAsyncSelect(pThis->m_serverSocket, pThis->m_hWnd, WM_ACCEPT, FD_ACCEPT);
	TRACE(_T("system info: listen socket success...\n"));
	pThis->m_bIsStart = true;
	pThis->m_RichLog.AddMessageUser(_T("system info: the server is running..."), MSG_SYSTEM_COLOR);
	return 1;

_Error_End:
	if (pThis->m_serverSocket != INVALID_SOCKET)
		closesocket(pThis->m_serverSocket);
	WSACleanup();
	return 0;
}
/************************************************************************/
/* ���տͻ��˵�����                                                      */
/************************************************************************/
LRESULT CMFCChatServerDlg::OnMsgAccept(WPARAM wParam, LPARAM lParam)
{
	UserInfo uInfo;
	SOCKET client;
	SOCKADDR_IN clientAddr;
	int iLen = sizeof(SOCKADDR_IN);
	CString msg = _T("");

	if (WSAGETSELECTERROR(lParam))
	{
		closesocket(m_serverSocket);
		TRACE(_T("Listening runs failed: %d"), WSAGetLastError());
		return -1;
	}

	switch (WSAGETSELECTEVENT(lParam))
	{
	case FD_ACCEPT:
		client = accept(m_serverSocket, (sockaddr*)&clientAddr, &iLen);
		if (INVALID_SOCKET == client)
			return 1;
		uInfo.socket = client;
		uInfo.IP = inet_ntoa(clientAddr.sin_addr); 
		m_userInfoList.push_back(uInfo);
		msg = _T("system info: ") + uInfo.IP;
		msg += _T(" comes in the room.");
		m_RichLog.AddMessageUser(msg, MSG_SYSTEM_COLOR);
		WSAAsyncSelect(uInfo.socket, m_hWnd, WM_RECIEVE, FD_READ | FD_CLOSE);
		break;
	default:
		ASSERT(0);
		break;
	}
	return 0;
}
/************************************************************************/
/* ����ͻ��˵�����                                                      */
/************************************************************************/
afx_msg LRESULT CMFCChatServerDlg::OnMsgRecv(WPARAM wParam, LPARAM lParam)
{
	UserInfo sClient = {0};
	UserMsg uMsg = {0};
	memset(&uMsg, 0, sizeof(UserMsg));
	//ZeroMemory(&uMsg, sizeof(uMsg));
	int errMsg;
	CString str;
	if (WSAGETSELECTEVENT(lParam) == FD_READ)
	{
		/*pos = FindUserInfo((SOCKET)wParam);
		ASSERT(m_userInfoList.GetPrev(pos));
		UserInfo *uInfo = (UserInfo*)m_userInfoList.GetPrev(pos);*/
		//sSender = uInfo->UserName;
		sClient.socket = (SOCKET)wParam;
		errMsg = recv(sClient.socket, (char*)&uMsg, sizeof(UserMsg), 0);
		TRACE(uMsg.UserName);
		TRACE(sClient.UserName);
		sClient.UserName = uMsg.UserName;
		FindUserInfo(sClient);
		if (errMsg == SOCKET_ERROR)
		{
			m_userInfoList.remove(sClient);
			return 1;
		}
		//uInfo->UserName = uMsg.UserName;
		//sSender = ((UserInfo*)m_userInfoList.GetAt(pos))->UserName;
		switch (uMsg.Protocol)
		{
		case USER_LOAD:
			break;
		case USER_MSGTOALL:
			uMsg.Protocol = USER_MSGTOALL;
			//_tcscpy_s(uMsg.UserName, sSender);
			str.Format(_T("%s"), uMsg.Msg);
			//FilterString(str);
			_tcscpy_s(uMsg.Msg, str);
			SendMsgToAll(uMsg);
			str.Format(_T("��%s�� sends to All:"), sClient.UserName);
			m_RichLog.AddMessageUser(str, MSG_USER_COLOR);
			m_RichLog.AddMessgaeText(uMsg.Msg, uMsg.m_FontName, uMsg.m_FontSize, uMsg.bIsBold, uMsg.bIsItalic, uMsg.bIsUnderline, uMsg.crColor, &m_BmpPicker);
			break;
		case USER_MSGTOPERSONAL:
			uMsg.Protocol = USER_MSGTOPERSONAL;
			//_tcscpy_s(uMsg.UserName, sSender);
			str.Format(_T("%s"), uMsg.Msg);
			//FilterString(str);
			_tcscpy_s(uMsg.Msg, str);
			SendMsgToPersonal(uMsg, sClient.UserName);
			str.Format(_T("��%s��sends to ��%s��:"), sClient.UserName, uMsg.UserName);
			m_RichLog.AddMessageUser(str, MSG_USER_COLOR);
			m_RichLog.AddMessgaeText(uMsg.Msg, uMsg.m_FontName, uMsg.m_FontSize, uMsg.bIsBold, uMsg.bIsItalic, uMsg.bIsUnderline, uMsg.crColor, &m_BmpPicker);
			break;
		default:
			break;
		}
	}
	else if (WSAGETSELECTEVENT(lParam) == FD_CLOSE)
	{
		if (WSAGETSELECTERROR(lParam) == 0)
		{
			//���ݹرա�  
		}
		else if (WSAGETSELECTERROR(lParam) == WSAECONNREFUSED)
		{
			//Ӳ�رա�  
		}
	}
	return 0;
}
/************************************************************************/
/* ����������                                                            */
/************************************************************************/
void CMFCChatServerDlg::OnBtnStartServer()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_port > 65535 || m_port < 1024)
	{
		CEdit* ce = (CEdit *)GetDlgItem(IDC_EDIT_PORT);
		ce->ShowBalloonTip(_T("Port"), _T("Port is only from 1024 to 65535"), TTI_WARNING);
		ce->SetWindowText(_T("65535"));
		return;
	}
	CString strNow;
	if (m_bIsStart == FALSE)
	{
		AfxBeginThread(/*(AFX_THREADPROC)*/ThreadProc, this, THREAD_PRIORITY_NORMAL);
		SetDlgItemText(IDC_BTN_START_SERVER, _T("Stop Server"));
	}
	else
	{
		if (IDOK == MessageBox(_T("Server is running, closing it will close all connections!\n\nAre you sure to close it?"), _T("warnning"), MB_OKCANCEL | MB_ICONQUESTION))
		{
			this->StopServer();
			m_bIsStart = false;
			SetDlgItemText(IDC_BTN_START_SERVER, _T("Start Server"));
			SetDlgItemText(IDC_STATIC_STATUS, _T("Server is stopped."));
		}
	}
}
/************************************************************************/
/* ������Ϣ                                                             */
/************************************************************************/
void CMFCChatServerDlg::OnBtnSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (m_bIsStart == FALSE)
	{
		m_RichLog.AddMessageUser(_T("Because of server is closed, you could not send message to all."), MSG_SYSTEM_COLOR);
		return;
	}
	CString strEdit = m_RichEdit.EncodeRichMessage();
	if (strEdit.IsEmpty())
	{
		((CEdit*)GetDlgItem(IDC_RICHEDIT_MSG2))->ShowBalloonTip(_T("Warning"), _T("Message can not be empty, please input."), TTI_INFO_LARGE);
		return;
	}
	UpdateData(TRUE);
	CString strFontName, strFontSize;
	/*m_FontName.GetWindowText(strFontName);
	m_FontSize.GetWindowText(strFontSize);
	COLORREF color = m_ColorPicker.GetColor();
	if (color == -1)
	{
	color = m_ColorPicker.GetAutomaticColor();
	}

	CString strTemp;
	m_UserChat.GetLBText(m_UserChat.GetCurSel(), strTemp);*/
	UserMsg msgTemp;
	msgTemp.Protocol = USER_MSGTOALL;
	_tcscpy_s(msgTemp.Msg, strEdit.GetBuffer(0));
	strEdit.ReleaseBuffer();
	_tcscpy_s(msgTemp.m_FontName, strFontName);
	msgTemp.m_FontSize = _ttoi(strFontSize);
	_tcscpy_s(msgTemp.UserName, _T("Admin"));
	//msgTemp.bIsBold = bIsBold;
	//msgTemp.bIsItalic = bIsItalic;
	//msgTemp.bIsUnderline = bIsUnderline;
	//msgTemp.crColor = color;
	SendMsgToAll(msgTemp);
	m_RichLog.AddMessageUser(_T("admin sends message to all"), MSG_SYSTEM_COLOR);
	m_RichEdit.SetWindowText(_T(""));
	m_RichEdit.SetFocus();

}
/************************************************************************/
/* �رճ���                                                             */
/************************************************************************/
void CMFCChatServerDlg::OnBtnClose()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
/************************************************************************/
/* ���ҿͻ�����Ϣ                                                        */
/************************************************************************/
void CMFCChatServerDlg::FindUserInfo(UserInfo &sClient)
{
	//POSITION pos = m_userInfoList.GetHeadPosition();
	//UserInfo *uInfo = NULL;
	//while (pos)
	//{
	//	VERIFY(m_userInfoList.GetAt(pos));
	//	// ȡ����ֵ
	//	uInfo = (UserInfo *)m_userInfoList.GetAt(pos);
	//	uInfo = (UserInfo *)m_userInfoList.GetNext(pos);
	//	if (uInfo->socket == socket)
	//		return pos;
	//}
	//return POSITION();

	/*sClient.IP.Empty();
	sClient.socket = 0;
	sClient.UserName.Empty();
	ZeroMemory(&sClient, sizeof(UserInfo));*/
	list<UserInfo>::iterator ibegin;
	ibegin = m_userInfoList.begin();
	while (ibegin != m_userInfoList.end())
	{
		if (ibegin->socket == sClient.socket)
		{
			ibegin->UserName = sClient.UserName;
			sClient.IP = ibegin->IP;
			break;
		}		
		ibegin++;
	}
	return;
}
/************************************************************************/
/* ������Ϣ��������                                                      */
/************************************************************************/
void CMFCChatServerDlg::SendMsgToAll(const UserMsg& uMsg)
{
	/*POSITION pos = m_userInfoList.GetHeadPosition();
	UserInfo *uInfo = NULL;
	while (pos)
	{
	uInfo = (UserInfo*)m_userInfoList.GetNext(pos);
	if (INVALID_SOCKET != uInfo->socket)
	send(uInfo->socket, (char *)&uMsg, sizeof(uMsg), 0);
	}*/

	list<UserInfo>::iterator ibegin;
	ibegin = m_userInfoList.begin();
	while (ibegin != m_userInfoList.end())
	{
		if (INVALID_SOCKET != ibegin->socket)
			send(ibegin->socket, (char*)&uMsg, sizeof(uMsg), 0);
		ibegin++;
	}
}
/************************************************************************/
/* ������Ϣ��ָ���ͻ�                                                    */
/************************************************************************/
void CMFCChatServerDlg::SendMsgToPersonal(UserMsg& uMsg, CString srcUser)
{
	/*POSITION pos = m_userInfoList.GetHeadPosition();
	UserInfo *uInfo=NULL;
	while (pos)
	{
		uInfo = (UserInfo *)m_userInfoList.GetNext(pos);
		if (uInfo->UserName.Compare(uMsg.UserName) == 0)
		{
			_tcscpy_s(uMsg.UserName, srcUser);
			break;
		}
	}
	if (uInfo!=NULL && uInfo->socket!=INVALID_SOCKET)
		send(uInfo->socket, (char*)&uMsg, sizeof(uMsg), 0);*/

	/*list<UserInfo>::iterator ibegin;
	ibegin = m_userInfoList.begin();
	while (ibegin != m_userInfoList.end())
	{
		if (INVALID_SOCKET != ibegin->socket)
			send(ibegin->socket, (char*)&uMsg, sizeof(uMsg), 0);
		ibegin++;
	}*/
}
