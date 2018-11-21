#pragma once
#include "stdafx.h"
#include "afxwin.h"
#include <vector>
using namespace std;
#include "../OneCardSys/PicUpFaceLib.h"
#include "PictureToBinSys.h"   //引入把图片专程二进制
#include "WintCheckVido.h"    //引入人证核验头文件
#include "ATLComTime.h"
#include "afxdtctl.h"


// CVistorsOper 对话框

class CVistorsOper : public CDialogEx
{
	DECLARE_DYNAMIC(CVistorsOper)

public:
	CVistorsOper(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVistorsOper();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGVISITOPER};
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	DECLARE_MESSAGE_MAP()

public:
	void ClearDate();   //清空变量

	// 人脸库信息
	//BOOL CheckLoginOk();  //校验摄像机是否登陆
	BOOL StartRealStream();  //启动截图
	BOOL  ExecuPicture();    //手动选择照片

	void  OperRZ(CString g_Action);//日志模块




public:	//自定变量
	void ReSize();  //窗口最大化最小化函数
	POINT old;      //窗口最大化变量

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
	int m_iPort;      //身份证读卡器端口

	//人脸
	LLONG    m_playHandle;//抓图句柄
	UINT     UiTimer;
	
	VARIANT  m_varPictureToEJZ;//存储照片的二进制数据
	DWORD    m_nPictureLen; //二进制大小

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
