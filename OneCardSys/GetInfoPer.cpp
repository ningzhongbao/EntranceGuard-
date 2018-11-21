// GetInfoPer.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "GetInfoPer.h"
#include "afxdialogex.h"

///////////////////////////全局变量/////////////////////////////////////
static int g_nCount = 0;     //全局变量设置图片名字
CString    g_strPictureShow; //ui_show路径名
DWORD      g_nPicSize = 0;   //图片大小
CString    filePathName;     //文件路径名
///////////////////////////////////////////////////////////////////////



// CGetInfoPer 对话框

IMPLEMENT_DYNAMIC(CGetInfoPer, CDialogEx)

CGetInfoPer::CGetInfoPer(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GETPERSON, pParent)
	, m_strPathName(_T(""))
{
	//InitLoginParams(); //初始化各项参数
	m_playHandle = 0;  //截图句柄
	//LogIn();//登录	

	CString strJQ = _T("C:\\YTPicture");	//截取字符串，创建文件夹
	if (!PathIsDirectory(strJQ))
	{
		CreateDirectory(strJQ, 0);//不存在则创建 ,一级目录
	}
	strJQ = _T("C:\\YTPicture\\ZPPictureFace");
	if (!PathIsDirectory(strJQ))
	{
		CreateDirectory(strJQ, 0);//不存在则创建，二级目录
	}
	m_strPathName = strJQ;
	filePathName = m_strPathName;
}

CGetInfoPer::~CGetInfoPer()
{
	//LogOut();
}

void CGetInfoPer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Picture_Show, m_ShowPicture);
	DDX_Text(pDX, IDC_EDIT1, m_strPathName);
	DDX_Control(pDX, IDC_EDIT1, m_Edit_Con);
}


BEGIN_MESSAGE_MAP(CGetInfoPer, CDialogEx)	
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BtnBegin, &CGetInfoPer::OnBnClickedBtnbegin)
	ON_BN_CLICKED(IDC_BtnStop, &CGetInfoPer::OnBnClickedBtnstop)
	ON_BN_CLICKED(IDC_BUTTON1, &CGetInfoPer::OnBnClickedButton1)	
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_Cannel, &CGetInfoPer::OnBnClickedCannel)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

HBRUSH CGetInfoPer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH   hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	return hBrush;
}


void CGetInfoPer::OnPaint()
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
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		/* CDC *pDC;
		pDC = GetDC();
		CRect  rect;
		GetClientRect(&rect);   //获取客户区大小
		Graphics graphics(pDC->m_hDC);
		//Graphics graphics(dc.m_hDC);
		Image image(L"./res/BG_BKALL.jpg", TRUE);
		graphics.DrawImage(&image, 0, 0, rect.right, rect.bottom);  *///绘制背景

		CDialogEx::OnPaint();
	}
}
//
//// CGetInfoPer 消息处理程序
//////////////////////////////////////////////////////////////////////////////////////////////
//static void CALLBACK disconnect_callback(LLONG lLoginID, char *lpszIP, LONG nPort, LDWORD dwUser)
//{
//	// TODO: 
//	CGetInfoPer* pDlg = (CGetInfoPer*)dwUser;
//	pDlg->m_lLoginID = 0;
//}
//
//BOOL CGetInfoPer::InitLoginParams()
//{
//	m_lLoginID = 0;
//	m_Str_Ip = "192.168.7.2";
//	m_int_port = 3000;
//	m_Str_User = "admin";
//	m_Str_Pwd = "admin123";
//	
//	Net_Init(disconnect_callback, (LDWORD)(void*)this); //初始化sdk库
//
//	return TRUE;
//}
//
//
//BOOL CGetInfoPer::LogIn()
//{						  
//	m_lLoginID = Net_LoginDevice(m_Str_Ip.GetBuffer(), m_int_port,
//		                         m_Str_User.GetBuffer(),m_Str_Pwd.GetBuffer(), NULL, &m_nError); //登陆
//
//	if (0 >= m_lLoginID)
//	{
//		MessageBox(_T("人脸识别功能登录失败，重启软件"), _T("登录提示..."), MB_ICONHAND);
//
//		return FALSE;
//	}
//
//	return TRUE;
//}
//
//BOOL CGetInfoPer::LogOut()
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

int CALLBACK realload_callback(LLONG lAnalyzerHandle,
								DWORD dwEventType,
								void* pEventInfo,
								BYTE *pBuffer,
								DWORD dwBufSize,
								LDWORD dwUser,
								int nSequence,
								void *reserved)
{	
	if (dwEventType == EVENT_SP_FACE_SNAP_PART)   // 人脸背景图
	{		
		STU_EVENT_FACE_SNAP_WHOLE stu = { 0 };
		memcpy(&stu, pEventInfo, sizeof(STU_EVENT_FACE_SNAP_WHOLE));
		g_strPictureShow = "";
		// pBuffer 是图片数据，dwBufSize 是图片数据大小			

		CString csPath;
		csPath = filePathName;  //每次把选择路径给cspath，防止cstring叠加，出错

		if (!PathIsDirectory(csPath))
		{
			CreateDirectory(csPath, 0);//不存在则创建
		}

		//文件已经存在
		CString filePath = "";

		CString strTime = "";   //获取系统时间
		SYSTEMTIME systime;
		GetLocalTime(&systime);//本地时间
		strTime.Format("ZH%2d%2d%2d%2d%2d%2d", systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds);

		csPath += _T("\\") + strTime + _T("E") + _T(".jpg");
		FILE *pFilePath = fopen(csPath, "wb+"); //效率低
		if (NULL != pFilePath)
		{
			fwrite(pBuffer, 2, dwBufSize, pFilePath);	//写入文件		
			g_strPictureShow = csPath;//获取文件名,为了在介面上显示，必须给定这个名字			
			fclose(pFilePath);
		}	
	}

	return 0;
}


BOOL CGetInfoPer::StartRealStream()
{
	// 图片数据处理在 realload_callback 回调中
	int nChannel = 0;

	m_playHandle = Net_RealLoadPicture( m_ZPLoginID, nChannel, EVENT_SP_FACE_SNAP_PART, 1,
									    realload_callback, NULL, NULL);
	if (0 >= m_playHandle)
	{
		MessageBox(_T("网络库错误，请重启截取人脸功能.\n"), NULL, MB_ICONERROR);

		Net_LogoutDevice(m_ZPLoginID);

		return FALSE;
	}

	return TRUE;
}

void CGetInfoPer::OnBnClickedBtnbegin()
{
	// TODO: 在此添加控件通知处理程序代码
	if (filePathName.IsEmpty())
	{
		MessageBox(_T("请先选择保存图片路径"), NULL, MB_ICONERROR);

		return ;
	}

	if (!StartRealStream())
	{
		MessageBox(_T("收集人脸失败"), NULL, MB_ICONERROR);
		
		return ;
	}
	else
	{		
		MessageBox(_T("正在采集人脸"), NULL, MB_OK);
		
		UiTimer = SetTimer(1, 100, NULL);  //开启计时器，实时刷新界面
	}
	
	CWnd *pBtn1 = GetDlgItem(IDC_BUTTON1);
	pBtn1->EnableWindow(FALSE);
	CWnd *pBegin = GetDlgItem(IDC_BtnBegin);//成功后设置开始按钮不可用
	pBegin->EnableWindow(FALSE);
	CWnd *pStop = GetDlgItem(IDC_BtnStop);
	pStop->EnableWindow(TRUE);
}


void CGetInfoPer::OnBnClickedBtnstop()
{
	// TODO: 在此添加控件通知处理程序代码
	//停止订阅
	if (0 >= m_playHandle)
	{
		MessageBox(_T("请先点击开始按钮"), _T("Tip"), MB_ICONERROR);
		return;
	}
	Net_StopLoadPicture(m_playHandle);

	KillTimer(1);  //结束计时器

	CWnd *pStop = GetDlgItem(IDC_BtnStop);
	pStop->EnableWindow(FALSE);
	CWnd *pBegin = GetDlgItem(IDC_BtnBegin);
	pBegin->EnableWindow(TRUE);
	CWnd *pBtn1 = GetDlgItem(IDC_BUTTON1);
	pBtn1->EnableWindow(TRUE);
}


void CGetInfoPer::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	TCHAR           szFolderPath[MAX_PATH] = { 0 };
	CString         strFolderPath = TEXT("");

	BROWSEINFO      sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot = 0;
	sInfo.lpszTitle = _T("请选择人脸图片存储路径");
	sInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_DONTGOBELOWDOMAIN;
	sInfo.lpfn = NULL;

	// 显示文件夹选择对话框  
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	if (lpidlBrowse != NULL)
	{
		// 取得文件夹名  
		if (::SHGetPathFromIDList(lpidlBrowse, szFolderPath))
		{
			strFolderPath = szFolderPath;
		}
	}
	if (lpidlBrowse != NULL)
	{
		::CoTaskMemFree(lpidlBrowse);
	}
	if ("" == strFolderPath)
	{
		MessageBox(_T("选取文件路径不正确，请重新选取"), NULL, MB_OK);

		return;
	}
	if (!strFolderPath.IsEmpty())
	{
		m_strPathName = strFolderPath;  //界面edit路径
	}

	filePathName = m_strPathName;   //文件夹路径
	
	CWnd *pStop = GetDlgItem(IDC_BtnBegin);
	pStop->EnableWindow(TRUE);

	UpdateData(FALSE);
}

void CGetInfoPer:: Ui_Show()
{
	CString strExt(".jpg");
	if (g_strPictureShow.IsEmpty() || -1 == g_strPictureShow.Find(strExt.GetBuffer(0)))
		return;
	
	m_strPathName = g_strPictureShow;  //界面edit路径

	CImage image;
	image.Load(g_strPictureShow);
	
	//以下两个矩形主要作用是，获取对话框上面的Picture Control的width和height，
	//并设置到图片矩形rectPicture，根据图片矩形rectPicture对图片进行处理，
	//最后绘制图片到对话框上Picture Control上面
	CRect rectControl;                        //控件矩形对象
	CRect rectPicture;                        //图片矩形对象

	int x = image.GetWidth();
	int y = image.GetHeight();
	(&m_ShowPicture)->GetClientRect(rectControl);

	CDC *pDc = (&m_ShowPicture)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(),
		CSize((int)rectControl.Width(),
		(int)rectControl.Height()));

	(&m_ShowPicture)->SetBitmap(NULL);

	//以下两种方法都可绘制图片
	image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); //将图片绘制到Picture控件表示的矩形区域

	image.Destroy();
	(&m_ShowPicture)->ReleaseDC(pDc);

	UpdateData(FALSE);
}

void CGetInfoPer::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
		case 1:
		   {
			 Ui_Show();//刷新界面人脸图片
		   }
		   break;
		default:
			break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CGetInfoPer::OnBnClickedCannel()
{
	// TODO: 在此添加控件通知处理程序代码
	//停止订阅
	if (m_playHandle > 0)
	{
		Net_StopLoadPicture(m_playHandle);
		KillTimer(1);  //结束计时器
	} 

	g_nCount = 0;     //全局变量设置图片名字
	g_strPictureShow = ""; //ui_show路径名
	g_nPicSize = 0;   //图片大小
	filePathName = "";     //文件路径名	
	m_strPathName = _T("文件路径");
	

	CWnd *pStop = GetDlgItem(IDC_BtnStop);
	pStop->EnableWindow(TRUE);
	CWnd *pBegin = GetDlgItem(IDC_BtnBegin);
	pBegin->EnableWindow(TRUE);
	CWnd *pBtn1 = GetDlgItem(IDC_BUTTON1);
	pBtn1->EnableWindow(TRUE);
	
	UpdateData(FALSE);

	CDialog::OnCancel();
}



void CGetInfoPer::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}

void CGetInfoPer::ReSize()
{
	float fsp[2];
	POINT Newp; //获取现在对话框的大小
	CRect recta;
	GetClientRect(&recta);     //取客户区大小  
	Newp.x = recta.right - recta.left;
	Newp.y = recta.bottom - recta.top;
	fsp[0] = (float)Newp.x / old.x;
	fsp[1] = (float)Newp.y / old.y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint, TLPoint; //左上角
	CPoint OldBRPoint, BRPoint; //右下角
	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //列出所有控件  
	while (hwndChild)
	{
		woc = ::GetDlgCtrlID(hwndChild);//取得ID
		GetDlgItem(woc)->GetWindowRect(Rect);
		ScreenToClient(Rect);
		OldTLPoint = Rect.TopLeft();
		TLPoint.x = long(OldTLPoint.x*fsp[0]);
		TLPoint.y = long(OldTLPoint.y*fsp[1]);
		OldBRPoint = Rect.BottomRight();
		BRPoint.x = long(OldBRPoint.x *fsp[0]);
		BRPoint.y = long(OldBRPoint.y *fsp[1]);
		Rect.SetRect(TLPoint, BRPoint);
		GetDlgItem(woc)->MoveWindow(Rect, TRUE);
		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}
	old = Newp;
}

BOOL CGetInfoPer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect1;
	GetClientRect(&rect1);     //取客户区大小  
	old.x = rect1.right - rect1.left;
	old.y = rect1.bottom - rect1.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);




	



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
