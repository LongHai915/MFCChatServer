/*
 *	�ļ����ƣ�RichEditCtrlEx.h
 *	��ǰ�汾��1.0 Unicode�汾
 *	���ã�CRichEditCtrl����չ�࣬��ת���ַ��ı���ͼƬ���Ҽ��˵���Ϣ���Զ���ⳬ���ӣ��Զ����У�RTF����
 *	���ߣ��޻�
 *	ԭ���ߣ������� (querw)
 *	������ڣ�2010��10��25��
 *	��ַ��http://blog.csdn.net/akof1314
 *	
 *	ʹ�ã�
 *	��CxxxApp::InitInstance()����ӣ� AfxInitRichEdit2();
 *	�ڶԻ������϶�һ��Rich Eidt 2.0�ؼ���������MultilineΪTrue��want return ΪTrue��Vertical ScrollΪTrue��
 *	Ϊ����ӱ�������������ΪCRichEditCtrlEx��֮���ٵ�������������ط�����
 *	����Ϊ�����¼���ʱ�򣬰�����༭����Ϊ������һ��TAB��˳��ؼ�
 */
#pragma once


#include <afxodlgs.h>
#include <afxpriv.h>
#include "oleimpl2.h"
#include "Richole.h"
#include "BmpPicker.h"
#define CHATMSG	1
#define CHATLOG	2
class CRichEditCtrlEx : public CRichEditCtrl
{
	DECLARE_DYNAMIC(CRichEditCtrlEx)

public:
	CRichEditCtrlEx();
	virtual ~CRichEditCtrlEx();

	static DWORD CALLBACK CStringFormatToRTF(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
	static DWORD CALLBACK RTFFormatToCString(DWORD dwCookie, LPBYTE pbBuff, LONG cb, LONG *pcb);
	void SetRTF(CString strRTF);
	CString GetRTF();
	void InsertBitmap(HBITMAP hBitmap,int index);
	void InsertBitmap(CString strFileName);
	void SetType(int type);	//��������༭�򣬻��������¼�򣨡����
	CString EncodeRichMessage();   //�����ת���ַ�
	void DecodeRichMessage(CString strText,CBmpPicker* m_BmpPicker);  //����ɱ���ͼƬ
	void AddMessageUser(CString strName,COLORREF crColor);
	void AddMessgaeText(CString strText,CString crFontName,UINT crFontSize,BOOL bIsBold,BOOL bIsItalic,BOOL bIsUnderline,COLORREF crColor,CBmpPicker* m_BmpPicker);
protected:
	DECLARE_MESSAGE_MAP()
	LPSTORAGE m_lpStorage;  // provides storage for m_lpObject
	LPLOCKBYTES m_lpLockBytes;  // part of implementation of m_lpStorage
	LPOLEOBJECT m_lpObject; // in case you want direct access to the OLE object
	LPVIEWOBJECT2 m_lpViewObject;// IViewObject for IOleObject above
	int m_type;

	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCopy() ;
	afx_msg void OnCut() { Cut(); }
	afx_msg void OnPaste();
	afx_msg void OnSelectall() { SetSel(0, -1); }
	afx_msg void OnUndo() { Undo(); }
	afx_msg void OnClear() { SetWindowText(_T("")); }
	afx_msg void OnSelectfont();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
public:
	afx_msg void OnEnLink(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
protected:
	virtual void PreSubclassWindow();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};


struct stFace
{
	long nPos;			//Ҫ�����λ��
	int nAtFace;		//�������Ĵ���
	CString strFace;		//Ҫ�����ͼ��ת���ַ�
	int nLength;		//ת���ַ�����ĳ���
};