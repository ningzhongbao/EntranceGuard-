#pragma once


// CDeleUser 对话框

class CDeleUser : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleUser)

public:
	CDeleUser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeleUser();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIADEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_User_String;
	afx_msg void OnBnClickedBtndel();
	afx_msg void OnBnClickedBtncanl();
};
