#pragma once
#include "afxcmn.h"
#include "ATLComTime.h"
#include "stdafx.h"

// CLogInfo �Ի���

class CLogInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CLogInfo)

public:
	CLogInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGLOGINFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
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
