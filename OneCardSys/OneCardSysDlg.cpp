
// OneCardSysDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "OneCardSysDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COneCardSysDlg 对话框



COneCardSysDlg::COneCardSysDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ONECARDSYS_DIALOG, pParent)
	, m_strUser(_T(""))
	, m_strPwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MAINLOGO);
}
COneCardSysDlg::~COneCardSysDlg()
{
	//LogOut();
}
void COneCardSysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUser);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
	DDX_Control(pDX, IDC_STHEME, m_static);
}

BEGIN_MESSAGE_MAP(COneCardSysDlg, CDialogEx)
	ON_WM_QUERYDRAGICON()	
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BtnLogin, &COneCardSysDlg::OnBnClickedBtnlogin)
	ON_BN_CLICKED(IDC_BtnCannel, &COneCardSysDlg::OnBnClickedBtncannel)
	ON_EN_CHANGE(IDC_EDIT_USER, &COneCardSysDlg::OnEnChangeEditUser)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


HBRUSH COneCardSysDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH   hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	return hBrush;
}



BOOL COneCardSysDlg::ConnectionSql()
{
	try
	{
		::CoInitialize(NULL);
		HRESULT hr = NULL;
		HRESULT hRes = NULL;
		hr = m_pConnection.CreateInstance("ADODB.Connection");

		//m_bstrConn = "Driver=SQL Server;Server=LAPTOP-E18QACSO;Database = FaceContCen"; //连接本机的数据库
		m_bstrConn = "Driver=SQL Server;Server=SHYT;Database = FaceContCen"; //局域网的数据库

		hRes = m_pConnection->Open(m_bstrConn, _T("sa"), _T("a1234"), adModeUnknown);		
		
		m_pRecordSet.CreateInstance(__uuidof(Recordset));
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("SQL数据库连接失败"));

		return FALSE;
	}

	return TRUE;
}

// COneCardSysDlg 消息处理程序

BOOL COneCardSysDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标	

	// TODO: 在此添加额外的初始化代码
	//if(TRUE != ConnectionSql()) //连接sql  
	//{ 
	//	PostQuitMessage(0);
	//	
	//	return FALSE;
	//}

	User = 0;  //登陆用户名
	Pwd = "";  //密码 
	UpdateData(TRUE);  //


	m_Font.CreatePointFont(230, "Arial", NULL);  //设置字体大小
	m_static.SetFont(&m_Font, true);

	m_strUser = "1";   
	m_strPwd = "1";

	//m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	UpdateData(FALSE); //更新到界面


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COneCardSysDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDC *pDC;
		pDC = GetDC();
		CRect  rect;
		GetClientRect(&rect);   //获取客户区大小
		Graphics graphics(pDC->m_hDC);
		//Graphics graphics(dc.m_hDC);
		Image image(L"./res/BG_Login.jpg", TRUE);
		graphics.DrawImage(&image, 0, 0, rect.right, rect.bottom);  //绘制背景

		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR COneCardSysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
} 


CString COneCardSysDlg::GetLocalHostIP()
{
	CString strIP("");
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	memset(name, '\0', 255);
	PHOSTENT hostinfo;
	wVersionRequested = MAKEWORD(2, 0);

	if (WSAStartup(wVersionRequested, &wsaData) == 0)
	{
		if (gethostname(name, sizeof(name)) == 0)
		{
			if ((hostinfo = gethostbyname(name)) != NULL)
			{
				strIP = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
			}
		}
		WSACleanup();
	}
	return strIP;
}

void COneCardSysDlg::OnBnClickedBtnlogin()
{
	// TODO: 在此添加控件通知处理程序代码	
	if (TRUE != ConnectionSql()) //连接sql  
	{
		//PostQuitMessage(0);
		return;
	}

	UpdateData(TRUE);

	if (User == 0)
	{
		try   //查询数据库获取用户名和密码
		{
			CString Sql;
			Sql.Format(_T("SELECT * FROM [FaceContCen].[dbo].[User] WHERE IdNum = %d"), atoi(m_strUser));

			m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
				adLockOptimistic, adCmdText);

			User = m_pRecordSet->GetCollect(_variant_t(_T("IdNum")));
			Pwd = m_pRecordSet->GetCollect(_variant_t(_T("PWD")));
			g_UseName = m_pRecordSet->GetCollect(_variant_t(_T("Name")));
			g_QX = m_pRecordSet->GetCollect(_variant_t(_T("Type")));
			g_IDNum = m_pRecordSet->GetCollect(_variant_t(_T("IDCard")));
			if (m_pRecordSet->State)
			{
				m_pRecordSet->Close();
			}
		}
		catch (_com_error e)
		{
			if (m_pRecordSet->State)
			{
				m_pRecordSet->Close();
			}
			//CATCH_ERROR;
		}
	}


	if (atoi(m_strUser) != User || m_strPwd != Pwd)  //登陆
	{
		MessageBox("用户ID或密码错误！\n 请重新输入！", "登录失败！", MB_OK | MB_ICONERROR);
	}
	else
	{
		this->ShowWindow(SW_HIDE);
		g_UserId = User;

		g_Action = "登陆";   //登陆日志记录
		OperRZ(g_Action);

		CSysMainUi m_SysUiMain;   //系统主界面
		if (m_SysUiMain.DoModal() == IDOK)
		{
			this->ShowWindow(SW_SHOW);
		
			User = 0;
			Pwd = "";
		}		
	}

}

void COneCardSysDlg::OperRZ(CString g_Action)
{
	g_Ip = GetLocalHostIP();

	CTime tmp_tm = CTime::GetCurrentTime();
	CString TimeEnd = tmp_tm.Format("%Y-%m-%d %H:%M:%S");
	try
	{
		CString Sql;
		Sql.Format("INSERT INTO [FaceContCen].[dbo].[SysRunLog](IdNum,Name,QX,BeginData,EndData,Action,Ip,SysRun) Values(%d,'%s','%s','%s','%s','%s','%s','%s')", g_UserId, g_UseName, g_QX, g_Time, TimeEnd, g_Action, g_Ip, g_SysRunRZ);

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}
		//CATCH_ERROR;
	}

	/////////////////////////////日志///////////////////////////////////////
}

void COneCardSysDlg::OnBnClickedBtncannel()
{
	// TODO: 在此添加控件通知处理程序代码
	PostQuitMessage(0);
}


void COneCardSysDlg::OnEnChangeEditUser()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
//
//static void CALLBACK disconnect_callback(LLONG lLoginID, char *lpszIP, LONG nPort, LDWORD dwUser)
//{ 
//	// TODO: 
//	//COneCardSysDlg* pDlg = (COneCardSysDlg*)dwUser;
//	m_lLoginID = 0;
//}
//
//
//BOOL COneCardSysDlg::InitLoginParams() //人脸上传相机初始化
//{
//	m_lLoginID = 0;
//	m_Str_Ip = "192.168.35.6";
//	m_int_port = 3000;
//	m_Str_User = "admin";
//	m_Str_Pwd = "admin123";
//
//	Net_Init(disconnect_callback, (LDWORD)(void*)this); //初始化sdk库
//
//	return TRUE;
//}
//
//BOOL COneCardSysDlg::LogIn()
//{
//	m_lLoginID = Net_LoginDevice(m_Str_Ip.GetBuffer(), m_int_port,
//		m_Str_User.GetBuffer(), m_Str_Pwd.GetBuffer(), NULL, &m_nError); //登陆
//
//	if (0 >= m_lLoginID)
//	{
//		MessageBox(_T("人脸模块启动失败，重启软件或检测设备是否在线"), _T("登录提示..."), MB_ICONHAND);
//
//		return FALSE;
//	}
//
//	return TRUE;
//}
//
//
//BOOL COneCardSysDlg::LogOut()
//{
//	if (m_lLoginID)
//	{
//		if (Net_LogoutDevice(m_lLoginID))
//		{
//			m_lLoginID = 0;
//			// 清理网络库资源
//			Net_Exit();
//
//			return TRUE;
//		}
//	}
//
//	return FALSE;
//}

void COneCardSysDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//LogOut();

	CDialogEx::OnClose();
}
