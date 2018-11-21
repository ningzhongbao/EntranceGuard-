#pragma once
#include "afxwin.h"


// CAddUser 对话框

class CAddUser : public CDialogEx
{
	DECLARE_DYNAMIC(CAddUser)

public:
	CAddUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddUser();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAADDUSER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
