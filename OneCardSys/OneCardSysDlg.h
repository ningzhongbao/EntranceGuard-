
// OneCardSysDlg.h : 头文件
//

#pragma once
#include "SysMainUi.h"

// COneCardSysDlg 对话框
class COneCardSysDlg : public CDialogEx
{
// 构造
public:
	COneCardSysDlg(CWnd* pParent = NULL);	// 标准构造函数
	~COneCardSysDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ONECARDSYS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	CPropertySheet	m_sheet;	 // 属性页，用于容纳下面4个标签（页面）
	CPicture1       m_Picture;   //显示添加人脸信息属性页
	CFont m_Font;
	CStatic m_static;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

public:	//用户自定义变量
	CString m_strUser;
	CString m_strPwd;

	int  User; //用户id
	CString  Pwd; //密码
	_bstr_t        m_bstrConn;     //存储连接数据库的字符串
	_bstr_t        m_sqlCmd;       //存储sql语句

	
public:	//用户自定义函数
	BOOL ConnectionSql();  //连接数据库

	CString GetLocalHostIP();  //获取ip

	//
	//BOOL InitLoginParams();//人脸库操作初始化
	//BOOL LogIn();  //登陆
	//BOOL LogOut();  //登出
	void COneCardSysDlg::OperRZ(CString g_Action);//日志



public:
	afx_msg void OnBnClickedBtnlogin();
	afx_msg void OnBnClickedBtncannel();
	afx_msg void OnEnChangeEditUser();
	afx_msg void OnClose();
};
