#pragma once
#include "afxwin.h"


// CExportPicture �Ի���

class CExportPicture : public CDialogEx
{
	DECLARE_DYNAMIC(CExportPicture)

public:
	CExportPicture(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CExportPicture();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_DIAEXPORT
};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	BOOL ExportFun();
	void Ui_Show(CString strPicture_Path, int myIDC);
	int m_Len;  //ͼƬ��С
	_variant_t varTmp; //����ָ��
	char *pBuf ; //��ʱָ�����
	char *m_pBMPBuffer;

public:
	CString m_ExportPath_string;
	CStatic m_ExportPicture;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditExcout();
};
