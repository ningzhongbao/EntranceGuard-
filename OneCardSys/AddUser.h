#pragma once
#include "afxwin.h"


// CAddUser �Ի���

class CAddUser : public CDialogEx
{
	DECLARE_DYNAMIC(CAddUser)

public:
	CAddUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddUser();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAADDUSER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtncannel();
	afx_msg void OnBnClickedBtnok();
	void ClearDate();
	CString m_User;
	CString m_PWD;
	CString m_Name;
	CString m_Sex;
	CEdit m_Id;
	CString m_User_Type;
	CString m_Addr_String;
	CString m_ID_String;
};
