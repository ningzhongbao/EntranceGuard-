#pragma once
#include "stdafx.h"

// CViSet �Ի���

class CViSet : public CDialogEx
{
	DECLARE_DYNAMIC(CViSet)

public:
	CViSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CViSet();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAVISET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public: //����
	CString m_ZPIP_String;
	int m_ZPPort_Int;
	CString m_ZPUser_String;
	CString m_ZPPWD_String;

	CString m_SBIP_String;
	int m_SBPort_Int;
	CString m_SBUSer_String;
	CString m_SBPWD_String;

public:	//����
	void InitViParam();
	BOOL InitLoginParams(); //�����ϴ������ʼ��
	LLONG LogIn(CString strIp, INT nPort, CString strUser, CString strPwd);
	BOOL LogOut(LLONG lLoginHand);
	BOOL AllViLogin();//���������½����
	void AllLogOut(); //�����豸�ǳ�����


public:  //ϵͳ����ӳ��
	afx_msg void OnBnClickedSbbtnlogin();
	afx_msg void OnBnClickedZpbtnlogin();
	afx_msg void OnBnClickedZpbtnlogout();
	afx_msg void OnBnClickedSbbtnlogout();
};
