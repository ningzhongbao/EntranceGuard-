#pragma once

//#include "D:\\cProjcet\\OneCardSys\\OneCardSys\\NetManager\\netmanager.h"

#include "afxwin.h"
#include <gdiplus.h>
using namespace Gdiplus;
#include "stdafx.h"
//#pragma comment(lib, "netmanager.lib")

// CGetInfoPer �Ի���

class CGetInfoPer : public CDialogEx
{
	DECLARE_DYNAMIC(CGetInfoPer)

public:
	CGetInfoPer(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGetInfoPer();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GETPERSON };
#endif

public:
	//BOOL InitLoginParams();//��ʼ����¼����
	//BOOL LogIn();  //��¼
	//BOOL LogOut();
	BOOL StartRealStream();
	static void CALLBACK OnRealDataCallBack(LLONG lRealHandle, DWORD dwDataType, BYTE *pBuffer, DWORD dwBufSize, LDWORD dwUser);
	void Ui_Show();

public:
	//LLONG m_lLoginID;
	//int	m_nError;

	//CString     m_Str_Ip  ; //ip
	//INT 	    m_int_port; //�˿�
	//CString 	m_Str_User; //�û���
	//CString 	m_Str_Pwd ; //����

	//ʵʱ���ž��
	LLONG    m_playHandle;
	void     *m_parserHandle;
	FILE     *m_streamFp;
	UINT     UiTimer;
	void ReSize();
	POINT old;

	//CFont m_Font;
	//CStatic m_static;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnbegin();
	afx_msg void OnBnClickedBtnstop();
	afx_msg void OnBnClickedButton1();
	
	CStatic m_ShowPicture;
	static CStatic m_ShowPicture1;
	CString m_strPathName;
	CEdit m_Edit_Con;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCannel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	
};
