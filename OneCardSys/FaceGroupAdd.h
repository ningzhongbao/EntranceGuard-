#pragma once


// CFaceGroupAdd �Ի���

class CFaceGroupAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CFaceGroupAdd)

public:
	CFaceGroupAdd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFaceGroupAdd();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIA_ADDFACE };
#endif


public:

	CString GetAliasString();

	BOOL GetFaceGroupEnable();

	float GetSearchThreshold();

	UINT GetTopRank();



protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCreate();
	afx_msg void OnBnClickedBtncannel();
	CString m_edit_alias_string;
	int     m_edit_int_enable;
	CString m_edit_string_search_threshold;
	int m_edit_int_top_rank;
};
