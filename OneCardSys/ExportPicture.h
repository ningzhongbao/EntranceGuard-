#pragma once
#include "afxwin.h"


// CExportPicture 对话框

class CExportPicture : public CDialogEx
{
	DECLARE_DYNAMIC(CExportPicture)

public:
	CExportPicture(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExportPicture();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_DIAEXPORT
};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	BOOL ExportFun();
	void Ui_Show(CString strPicture_Path, int myIDC);
	int m_Len;  //图片大小
	_variant_t varTmp; //万能指针
	char *pBuf ; //临时指针变量
	char *m_pBMPBuffer;

public:
	CString m_ExportPath_string;
	CStatic m_ExportPicture;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditExcout();
};
