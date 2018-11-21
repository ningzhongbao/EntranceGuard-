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


// CSysMainUi 对话框




class CSysMainUi : public CDialogEx
{
	DECLARE_DYNAMIC(CSysMainUi)

public:
	CSysMainUi(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSysMainUi();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAMAINUI };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	// 实现
public:
	CGetInfoPer *m_pPerDlg; //截取人脸图片
	CPicture1   *m_pPicDlg; //人脸上传
	CGetOwerInfo*m_OwenInfo;//采集业主信息对话框
	CFaceOper   *m_FaceOpen;//人脸上传2
	CPerReg     *m_PerRegis;
	CPerModify  *m_PerModify;
    CVistorsOper  *m_VistorOPer;
	CVistorsRecord *m_VistorRecord;
	CPersComprResult *m_PersCompare;
	CLogInfo  *m_LogInfo;
	CExportPicture  *m_ExportPicture;
	CViSet          *ViSet; //摄像机ip配置登陆


	CFont m_Font;
	CStatic m_static1;
	CStatic m_static2;
	CStatic m_static3;
	CStatic m_static4;
	CString m_ShowType_String; //登陆权限设置

	void ReSize(); //窗口缩放
	POINT old;



	CMenu m_Menu; //菜单

	/************************************************************************/
	/* 系统校时服务器                                                        */
	/************************************************************************/
	void SendSysTime();  //服务器发送系统时间
	static DWORD WINAPI SendpondProc(LPVOID lpPar);

public:	//函数
	void QXFun();//登陆权限不同，界面显示不同
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
