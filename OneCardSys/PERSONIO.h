#pragma once
#include "ATLComTime.h"
#include "afxwin.h"
#include "afxcmn.h"


// CPERSONIO 对话框

class CPERSONIO : public CDialogEx
{
	DECLARE_DYNAMIC(CPERSONIO)

public:
	CPERSONIO(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPERSONIO();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAIOSELECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


public:	 //自定函数和变量
	void ReSize();
	POINT old;
	CFont m_Font;
	CStatic m_static;

public:
	afx_msg void OnBnClickedBtnSelect();
	COleDateTime m_Begin_String;
	COleDateTime m_End_String;
	afx_msg void OnBnClickedBtnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnprint();	
	CListCtrl m_listLogInfo;
	afx_msg void OnLvnItemchangedListshow(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnprinttoa4();
};
