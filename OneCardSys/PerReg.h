#pragma once
#include "afxwin.h"
#include "stdafx.h"
#include <vector>
using namespace std;
#include  "../OneCardSys/PicUpFaceLib.h"
#include  "PictureToBinSys.h"
#include "WintCheckVido.h" //人证核验实时视频流
#include "WintnessCheck.h"  //人证核验实现功能


#include "SynPublic.h"
#pragma  comment(lib, "SynIDCardAPI.lib")



// CPerReg 对话框

class CPerReg : public CDialogEx
{
	DECLARE_DYNAMIC(CPerReg)

public:
	CPerReg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPerReg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_DIAREGISTER
};
#endif

public://自定函数
	void Ui_Show(CString strPicture_Path, int myIDC_Picture);
	BOOL StartRealStream();
	BOOL  ExecuPicture();
	//BOOL PictureToEJZ();        //将图片数据转换成二进制存到万能变量中
	void OperRZ(CString g_Action);//日志
		
	BOOL CheckLoginOk();         //判断是否登录摄像机摄像机

	void ClearScreen();          //清空屏幕

	BOOL PerCardCheck();        //人证核验
	static DWORD GetRresult();  


	/************************************************************************/
	/* 刷身份证                                                       */
	/************************************************************************/
	void IDCardInit();  //刷身份证初始化
	int m_iPort;      //身份证读卡器端口


public://自定变量
	CString m_csFileName;  //文件名
	CString ID;            //照片的ip号
	void ReSize();         //窗口最大化最小化函数
	POINT old;             //窗口最大化变量

	VARIANT      varBLOB;  //存储图片的二进制流文件到sql
	DWORD        m_nFileLen;


	CString m_IdCard_String; //身份证
	CString m_RegTip;        //提示
	CString m_ID_String;     //界面id编号映射
	CString m_Name_String;   //界面名字映射
	CString m_Tel_String;    //电话
	CString m_LD_String;     //楼栋
	CString m_FH_String;     //房间号
	CString m_Path_String;   //界面图片路径
	CStatic m_Picture;       //照片变量映射
	CString m_COM_XB_String; //性别
	LLONG    m_playHandle;   //抓图句柄
	UINT     UiTimer;         //计时器
	
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnReg();
	afx_msg void OnBnClickedBtnCannel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnStreg();
	afx_msg void OnBnClickedBtntwocard();
	CEdit m_StatVal;
	CComboBox m_ComBoxSex;
	CEdit m_EditIDNo;
	CEdit m_Edit_ID_Values;
	CEdit m_vEdit7;
	CEdit m_EditName;
};
