#pragma once


// CDeleUser �Ի���

class CDeleUser : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleUser)

public:
	CDeleUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeleUser();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIADEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_User_String;
	afx_msg void OnBnClickedBtndel();
	afx_msg void OnBnClickedBtncanl();
};
