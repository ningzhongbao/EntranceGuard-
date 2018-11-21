// ViSet.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "ViSet.h"
#include "afxdialogex.h"


// CViSet 对话框

IMPLEMENT_DYNAMIC(CViSet, CDialogEx)

CViSet::CViSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIAVISET, pParent)
	, m_ZPIP_String(_T(""))
	, m_ZPPort_Int(0)
	, m_ZPUser_String(_T(""))
	, m_ZPPWD_String(_T(""))
	, m_SBIP_String(_T(""))
	, m_SBPort_Int(0)
	, m_SBUSer_String(_T(""))
	, m_SBPWD_String(_T(""))
{
	InitViParam();//初始化摄像机ip	
}

CViSet::~CViSet()
{
}

void CViSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ZPIP, m_ZPIP_String);
	DDX_Text(pDX, IDC_ZPPort, m_ZPPort_Int);
	DDX_Text(pDX, IDC_ZPUser, m_ZPUser_String);
	DDX_Text(pDX, IDC_ZPPWD, m_ZPPWD_String);
	DDX_Text(pDX, IDC_SBIP, m_SBIP_String);
	DDX_Text(pDX, IDC_SBPort, m_SBPort_Int);
	DDX_Text(pDX, IDC_SBUser, m_SBUSer_String);
	DDX_Text(pDX, IDC_SBPWD, m_SBPWD_String);
}


BEGIN_MESSAGE_MAP(CViSet, CDialogEx)
	ON_BN_CLICKED(IDC_SBBtnLogin, &CViSet::OnBnClickedSbbtnlogin)
	ON_BN_CLICKED(IDC_ZPBtnLogin, &CViSet::OnBnClickedZpbtnlogin)
	ON_BN_CLICKED(IDC_ZPBtnLogOut, &CViSet::OnBnClickedZpbtnlogout)
	ON_BN_CLICKED(IDC_SBBtnLogOut, &CViSet::OnBnClickedSbbtnlogout)
END_MESSAGE_MAP()


// CViSet 消息处理程序


void CViSet::InitViParam()
{
	//UpdateData(TRUE);
	//抓拍机ip设置
	m_ZPIP_String = "192.168.35.8";
	m_ZPPort_Int = 3000;
	m_ZPUser_String = "admin";
	m_ZPPWD_String = "admin123";

	//识别机ip设置
	m_SBIP_String = "192.168.35.6";
	m_SBPort_Int = 3000;
	m_SBUSer_String = "admin";
	m_SBPWD_String = "admin123";
	
//	this->UpdateData(FALSE);
}

void CViSet::OnBnClickedSbbtnlogin()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	InitLoginParams();  //初始化摄像机库
	m_lLoginID = LogIn(m_SBIP_String, m_SBPort_Int, m_SBUSer_String, m_SBPWD_String); //识别机句柄赋值

	if (0 >= m_lLoginID)
	{
		MessageBox(_T("门口人脸识别机登陆失败，请检测设备是否在线！"), _T("识别机登陆提示"), MB_ICONHAND);

		return;
	}
	else
	{
		MessageBox(_T("门口人脸识别机登陆成功！"), _T("识别机登陆提示"), MB_OK);
	}

}


static void CALLBACK disconnect_callback(LLONG lLoginID, char *lpszIP, LONG nPort, LDWORD dwUser)
{
	// TODO: 
	m_lLoginID = 0;
	m_ZPLoginID = 0;
}


BOOL CViSet::InitLoginParams() //人脸上传相机初始化
{
	Net_Init(disconnect_callback, (LDWORD)(void*)this); //初始化sdk库

	return TRUE;
}

LLONG CViSet::LogIn(CString strIp, INT nPort, CString strUser, CString strPwd)
{
	LLONG llogin = 0;
	llogin = Net_LoginDevice(strIp.GetBuffer(), nPort,
		strUser.GetBuffer(), strPwd.GetBuffer(), NULL, &m_nError); //登陆

	return llogin;
}


BOOL CViSet::LogOut(LLONG lLoginHand)
{
	if (lLoginHand)
	{
		if (Net_LogoutDevice(lLoginHand))
		{
			lLoginHand = 0;
			// 清理网络库资源
			Net_Exit();

			return TRUE;
		}
	}

	return FALSE;
}

void CViSet::OnBnClickedZpbtnlogin()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	InitLoginParams();  //初始化摄像机库

	m_ZPLoginID = LogIn(m_ZPIP_String, m_ZPPort_Int, m_ZPUser_String, m_ZPPWD_String); //抓拍机句柄赋值

	if (0 >= m_ZPLoginID)
	{
		MessageBox(_T("抓拍机登陆失败，请检测设备是否在线！"), _T("抓拍机登陆"), MB_ICONHAND);

		return ;
	}
	else
	{
		MessageBox(_T("抓拍机登陆成功！"), _T("抓拍机登陆"), 0);
	}
}


//BOOL CViSet::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//
//	// TODO:  在此添加额外的初始化
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//				  // 异常: OCX 属性页应返回 FALSE
//}


void CViSet::OnBnClickedZpbtnlogout()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!LogOut(m_ZPLoginID))
	{
		MessageBox("抓拍机登出失败", "登出提示 ", MB_ICONHAND);
	}
	else
	{
		MessageBox(_T("抓拍机登出成功！"), _T("登出提示"), 0);
	}
}

BOOL CViSet::AllViLogin()
{
	OnBnClickedZpbtnlogin();
	OnBnClickedSbbtnlogin();

	return TRUE;
}


void CViSet::OnBnClickedSbbtnlogout()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!LogOut(m_lLoginID))
	{
		MessageBox("识别机登出失败", "登出提示 ", MB_ICONHAND);
	}
	else
	{
		MessageBox("识别机登出成功", "登出提示", MB_OK);
	}
}

void CViSet::AllLogOut()
{
	OnBnClickedSbbtnlogout();
	OnBnClickedZpbtnlogout();
}
