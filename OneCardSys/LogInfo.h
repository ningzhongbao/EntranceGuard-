#pragma once
#include "afxcmn.h"
#include "ATLComTime.h"
#include "stdafx.h"

// CLogInfo 对话框

class CLogInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CLogInfo)

public:
	CLogInfo(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLogInfo();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGLOGINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	void ReSize();
	POINT old;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CListCtrl m_listLogInfo;
	COleDateTime m_Begin_String;
	COleDateTime m_End_String;
	afx_msg void OnBnClickedBtnview();
	afx_msg void OnBnClickedBtnyl();
	afx_msg void OnBnClickedBtnvinit();
	afx_msg void OnBnClickedBtnckrz();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnexcel();
	afx_msg void OnLvnItemchangedListloginfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnPaint();
};
