#pragma once


// CGetOwerInfo �Ի���

class CGetOwerInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CGetOwerInfo)

public:
	CGetOwerInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGetOwerInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_GETYZINFO
};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeEditXqeditNum();
};
