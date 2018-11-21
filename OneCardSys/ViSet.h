#pragma once
#include "stdafx.h"

// CViSet 对话框

class CViSet : public CDialogEx
{
	DECLARE_DYNAMIC(CViSet)

public:
	CViSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CViSet();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAVISET };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public: //变量
	CString m_ZPIP_String;
	int m_ZPPort_Int;
	CString m_ZPUser_String;
	CString m_ZPPWD_String;

	CString m_SBIP_String;
	int m_SBPort_Int;
	CString m_SBUSer_String;
	CString m_SBPWD_String;

public:	//函数
	void InitViParam();
	BOOL InitLoginParams(); //人脸上传相机初始化
	LLONG LogIn(CString strIp, INT nPort, CString strUser, CString strPwd);
	BOOL LogOut(LLONG lLoginHand);
	BOOL AllViLogin();//所有相机登陆函数
	void AllLogOut(); //所有设备登出函数


public:  //系统函数映射
	afx_msg void OnBnClickedSbbtnlogin();
	afx_msg void OnBnClickedZpbtnlogin();
	afx_msg void OnBnClickedZpbtnlogout();
	afx_msg void OnBnClickedSbbtnlogout();
};
