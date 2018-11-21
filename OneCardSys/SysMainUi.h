#pragma once
#include "Picture1.h"
#include "GetInfoPer.h"
#include "GetOwerInfo.h"
#include "FaceOper.h"
#include "PerReg.h"
#include "PerModify.h"
#include "VistorsOper.h"
#include "VistorsRecord.h"
#include  "PersComprResult.h"
#include "LogInfo.h"
#include "PERSONIO.h"
#include "ExportPicture.h"
#include "AddUser.h"
#include "DeleUser.h"
#include "ViSet.h"


// CSysMainUi �Ի���




class CSysMainUi : public CDialogEx
{
	DECLARE_DYNAMIC(CSysMainUi)

public:
	CSysMainUi(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSysMainUi();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAMAINUI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

	// ʵ��
public:
	CGetInfoPer *m_pPerDlg; //��ȡ����ͼƬ
	CPicture1   *m_pPicDlg; //�����ϴ�
	CGetOwerInfo*m_OwenInfo;//�ɼ�ҵ����Ϣ�Ի���
	CFaceOper   *m_FaceOpen;//�����ϴ�2
	CPerReg     *m_PerRegis;
	CPerModify  *m_PerModify;
    CVistorsOper  *m_VistorOPer;
	CVistorsRecord *m_VistorRecord;
	CPersComprResult *m_PersCompare;
	CLogInfo  *m_LogInfo;
	CExportPicture  *m_ExportPicture;
	CViSet          *ViSet; //�����ip���õ�½


	CFont m_Font;
	CStatic m_static1;
	CStatic m_static2;
	CStatic m_static3;
	CStatic m_static4;
	CString m_ShowType_String; //��½Ȩ������

	void ReSize(); //��������
	POINT old;



	CMenu m_Menu; //�˵�

	/************************************************************************/
	/* ϵͳУʱ������                                                        */
	/************************************************************************/
	void SendSysTime();  //����������ϵͳʱ��
	static DWORD WINAPI SendpondProc(LPVOID lpPar);

public:	//����
	void QXFun();//��½Ȩ�޲�ͬ��������ʾ��ͬ
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedGetperinfo();
	afx_msg void OnBnClickedBtnperinfo();
	afx_msg void OnClose();
	afx_msg void OnBnClickedGetoweinfo();
	afx_msg void OnBnClickedBtnsendowerinfo();
	afx_msg void OnBnClickedBtnfaceoper();
	afx_msg void OnBnClickedBtnRegister();
	afx_msg void OnBnClickedBtnOperPer();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnvrecord();
	afx_msg void OnBnClickedBtnResult();
	afx_msg void OnBnClickedBtnlog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();	
	afx_msg void OnBnClickedBtnzx();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnIoselect();
	afx_msg void OnBnClickedBtnOutfacepicture();
	afx_msg void On32771();
	afx_msg void On32772();
	afx_msg void On32773();
	afx_msg void On32774();
	afx_msg void OnBnClickedBtnipset();
};
