#pragma once
#include "stdafx.h"
#include "afxwin.h"
#include <vector>
using namespace std;
#include "../OneCardSys/PicUpFaceLib.h"
#include "PictureToBinSys.h"   //�����ͼƬר�̶�����
#include "WintCheckVido.h"    //������֤����ͷ�ļ�
#include "ATLComTime.h"
#include "afxdtctl.h"


// CVistorsOper �Ի���

class CVistorsOper : public CDialogEx
{
	DECLARE_DYNAMIC(CVistorsOper)

public:
	CVistorsOper(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVistorsOper();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGVISITOPER};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	DECLARE_MESSAGE_MAP()

public:
	void ClearDate();   //��ձ���

	// ��������Ϣ
	//BOOL CheckLoginOk();  //У��������Ƿ��½
	BOOL StartRealStream();  //������ͼ
	BOOL  ExecuPicture();    //�ֶ�ѡ����Ƭ

	void  OperRZ(CString g_Action);//��־ģ��




public:	//�Զ�����
	void ReSize();  //���������С������
	POINT old;      //������󻯱���

	CString m_Name_String;
	CString m_Sex_String;
	CString m_ID_String;
	CString m_FKAddr_String;
	CString m_BFZName_String;
	CString m_BFZAddr_String;
	CString m_Picture_Path;
	CStatic m_Picture;
	CString m_ShowInfoReg;

	CEdit m_vEdit1;
	CEdit m_vEdit2;
	CEdit m_vEdit3;
	CEdit m_vEdit4;
	CEdit m_vEdit5;
	CEdit m_vEdit6;
	CEdit m_vEdit7;
	int m_iPort;      //���֤�������˿�

	//����
	LLONG    m_playHandle;//ץͼ���
	UINT     UiTimer;
	
	VARIANT  m_varPictureToEJZ;//�洢��Ƭ�Ķ���������
	DWORD    m_nPictureLen; //�����ƴ�С

public:
	afx_msg void OnBnClickedBtnvinit();
	afx_msg void OnBnClickedBtnvread();
	CComboBox m_combxSex;
	afx_msg void OnBnClickedBtnvclear();
	afx_msg void OnBnClickedBtnvreg();
	afx_msg void OnBnClickedBtnvleav();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedBtnsdselectpicture();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_SH_String;
	CString m_LH_String;
	CString m_PicId_String;
	CEdit m_Edit_ID_Values;
	CString m_Tel_String;
	COleDateTime m_FWJZTime;
	CDateTimeCtrl m_CTCTimeEd;
};
