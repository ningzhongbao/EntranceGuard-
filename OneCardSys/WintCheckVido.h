#pragma once
#include "PicUpFaceLib.h"

// CWintCheckVido �Ի���

class CWintCheckVido : public CDialogEx
{
	DECLARE_DYNAMIC(CWintCheckVido)

public:
	CWintCheckVido(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWintCheckVido();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAWITCHECKVIDO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	void OnShutVidoStream();
	void OnMyCloseWind();
	static DWORD PVCThread(LPVOID lpar);
	BOOL PerCardCheck();        //��֤����
	static DWORD GetRresult();
	void SetShow();
public:	
	afx_msg void OnStnClickedSvlc();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnDestroy();

	CString m_TipString;
	CString m_ScoreString;
	float m_FloatScore;
	CWinThread* pPlayerThread; //�����߳�
};
