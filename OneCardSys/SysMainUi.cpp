// SysMainUi.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "SysMainUi.h"
#include "afxdialogex.h"
#include "HttpPost.h"

// 释放指针宏
#define RELEASE(x)                      {if(x != NULL ){delete x;x=NULL;}}

// CSysMainUi 对话框

IMPLEMENT_DYNAMIC(CSysMainUi, CDialogEx)

CSysMainUi::CSysMainUi(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIAMAINUI, pParent)	
	, m_ShowType_String(_T(""))
{	
}

CSysMainUi::~CSysMainUi()
{
	RELEASE(m_pPicDlg)
		RELEASE(m_OwenInfo)
		RELEASE(m_FaceOpen)
		RELEASE(m_PerRegis)
		RELEASE(m_PerModify)
		RELEASE(m_VistorOPer)
		RELEASE(m_VistorRecord)
		RELEASE(m_PersCompare)
		RELEASE(m_LogInfo)
		RELEASE(m_ExportPicture) //释放导出图片内存控件
		RELEASE(ViSet)
}

void CSysMainUi::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STFACEOPR, m_static1);
	DDX_Control(pDX, IDC_STUSERINFO, m_static2);
	DDX_Control(pDX, IDC_STVISTINFO, m_static3);
	DDX_Control(pDX, IDC_STOWNERINFO, m_static4);
	DDX_Text(pDX, IDC_ShotType, m_ShowType_String);  //	
}


BEGIN_MESSAGE_MAP(CSysMainUi, CDialogEx)
	ON_BN_CLICKED(IDC_GetPerInfo, &CSysMainUi::OnBnClickedGetperinfo)
	ON_BN_CLICKED(IDC_BtnPerInfo, &CSysMainUi::OnBnClickedBtnperinfo)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_GetOweInfo, &CSysMainUi::OnBnClickedGetoweinfo)
	ON_BN_CLICKED(IDC_BtnSendOwerInfo, &CSysMainUi::OnBnClickedBtnsendowerinfo)
	ON_BN_CLICKED(IDC_BtnFaceOper, &CSysMainUi::OnBnClickedBtnfaceoper)
	ON_BN_CLICKED(IDC_Btn_Register, &CSysMainUi::OnBnClickedBtnRegister)
	ON_BN_CLICKED(IDC_Btn_Oper_Per, &CSysMainUi::OnBnClickedBtnOperPer)
	ON_BN_CLICKED(IDC_BUTTON1, &CSysMainUi::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTNVRECORD, &CSysMainUi::OnBnClickedBtnvrecord)
	ON_BN_CLICKED(IDC_Btn_Result, &CSysMainUi::OnBnClickedBtnResult)
	ON_BN_CLICKED(IDC_BTNLOG, &CSysMainUi::OnBnClickedBtnlog)
	ON_BN_CLICKED(IDC_BtnZX, &CSysMainUi::OnBnClickedBtnzx)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_Btn_IOSelect, &CSysMainUi::OnBnClickedBtnIoselect)
	ON_BN_CLICKED(IDC_Btn_OutFacePicture, &CSysMainUi::OnBnClickedBtnOutfacepicture)
	ON_COMMAND(ID_32771, &CSysMainUi::On32771)
	ON_COMMAND(ID_32772, &CSysMainUi::On32772)
	ON_COMMAND(ID_32773, &CSysMainUi::On32773)
	ON_COMMAND(ID_32774, &CSysMainUi::On32774)
	ON_BN_CLICKED(IDC_BtnIPSet, &CSysMainUi::OnBnClickedBtnipset)
END_MESSAGE_MAP()


void CSysMainUi::QXFun()  //权限机制
{
	if (_T("保安") == g_QX)
	{
		CWnd *IOSelect = GetDlgItem(IDC_Btn_IOSelect); //人员进出入查询
		//pCan->EnableWindow(FALSE);
		IOSelect->ShowWindow(SW_HIDE);

		CWnd *BTNLOG = GetDlgItem(IDC_BTNLOG);  //日志查询
		BTNLOG->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_Btn_XFPermis)->ShowWindow(SW_HIDE); //下放权限


		CWnd *BTNVRECORD = GetDlgItem(IDC_Btn_OutFacePicture); //导出所有图片
		BTNVRECORD->ShowWindow(SW_HIDE);

		CWnd *Btn_Oper_Per = GetDlgItem(IDC_Btn_Oper_Per);  //住户操作
		Btn_Oper_Per->ShowWindow(SW_HIDE);

		CWnd *Register = GetDlgItem(IDC_Btn_Register);  //住户注册
		Register->ShowWindow(SW_HIDE);

		CWnd *GetPerInfo = GetDlgItem(IDC_GetPerInfo);  // 采集人脸信息									
		GetPerInfo->ShowWindow(SW_HIDE);

		CWnd *BtnFaceOper = GetDlgItem(IDC_BtnFaceOper);  // 人脸库操作
		BtnFaceOper->ShowWindow(SW_HIDE);
		//		
		//CWnd *Btn_Result = GetDlgItem(IDC_Btn_Result);  // 时事通行操作
		//Btn_Result->ShowWindow(SW_HIDE);

		//RecvSysTime();//启动系统时间校验

	}
	else if (_T("物业") == g_QX)
	{
		CWnd *IOSelect = GetDlgItem(IDC_Btn_IOSelect); //人员进出入查询
		IOSelect->ShowWindow(SW_HIDE);

		CWnd *BTNLOG = GetDlgItem(IDC_BTNLOG);  //日志查询
		BTNLOG->ShowWindow(SW_HIDE);

		CWnd *XFPermis = GetDlgItem(IDC_Btn_XFPermis); //下放权限
		XFPermis->ShowWindow(SW_HIDE);
		
		//GetDlgItem(IDC_AddUser)->ShowWindow(SW_HIDE);   //添加用户
		//GetDlgItem(IDC_DelUser)->ShowWindow(SW_HIDE); //删除用户

		CWnd *OutFacePicture = GetDlgItem(IDC_Btn_OutFacePicture);  //下载业主人脸
		OutFacePicture->ShowWindow(SW_HIDE);

		CWnd *GetPerInfo = GetDlgItem(IDC_GetPerInfo);  // 采集人脸信息
		GetPerInfo->ShowWindow(SW_HIDE);

		CWnd *tnFaceOper = GetDlgItem(IDC_BtnFaceOper);  // 人脸库操作
		tnFaceOper->ShowWindow(SW_HIDE);

		CWnd *Btn_Result = GetDlgItem(IDC_Btn_Result);  // 时事通行操
		Btn_Result->ShowWindow(SW_HIDE);

		CWnd *BUTTON1 = GetDlgItem(IDC_BUTTON1);  // 时事通行操作
		BUTTON1->ShowWindow(SW_HIDE);
		
		CWnd *BTNVRECORD = GetDlgItem(IDC_BTNVRECORD);  // 访客记录
		BTNVRECORD->ShowWindow(SW_HIDE);
	}
}

// CSysMainUi 消息处理程序
HBRUSH CSysMainUi::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH   hBrush = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkMode(TRANSPARENT);
		return   (HBRUSH)::GetStockObject(NULL_BRUSH);
	}
	return hBrush;
}



void CSysMainUi::OnPaint()
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
		CDC *pDC;
		pDC = GetDC();
		CRect  rect;
		GetClientRect(&rect);   //获取客户区大小
		Graphics graphics(pDC->m_hDC);
		//Graphics graphics(dc.m_hDC);
		Image image(L"./res/BG_MainUI.jpg", FALSE);
		graphics.DrawImage(&image, 0, 0, rect.right, rect.bottom);  //绘制背景

		CDialogEx::OnPaint();
	}
}

BOOL CSysMainUi::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO: 在此添加额外的初始化代码
	ModifyStyleEx(0, WS_EX_APPWINDOW);//显示任务栏图标

	m_Font.CreatePointFont(200, _T("Arial"), NULL);
	m_static1.SetFont(&m_Font, true);
	m_static2.SetFont(&m_Font, true);
	m_static3.SetFont(&m_Font, true);
	m_static4.SetFont(&m_Font, true);

	CRect rect;
	GetClientRect(&rect);     //取客户区大小  
	old.x = rect.right - rect.left;
	old.y = rect.bottom - rect.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);

	m_pPicDlg = NULL;
	m_pPerDlg = NULL;
	m_OwenInfo = NULL;
	m_FaceOpen = NULL;
	m_PerRegis = NULL;
	m_PerModify = NULL;
	m_VistorOPer = NULL;
	m_VistorRecord = NULL;  
	m_PersCompare = NULL; 
	m_LogInfo = NULL;
	m_ExportPicture = NULL;

	ViSet = new CViSet;    //摄像机配置
// 	ViSet->Create(IDD_DIAVISET, this);
// 	ViSet->ShowWindow(SW_HIDE);
// 	ViSet->AllViLogin(); //初始化摄像机ip

	//if (_T("管理员") == g_QX)
	//{
	//	SendSysTime(); //发送系统时间
	//}

	m_ShowType_String = g_QX;  //设置登陆权限
	QXFun();      
	UpdateData(FALSE);

	//CMenu *pSysMenu = GetSystemMenu(FALSE);  //关闭按钮
	//if (NULL != pSysMenu)
	//{
	//	pSysMenu->EnableMenuItem(SC_CLOSE, MF_GRAYED);
	//}	

	CDC *pDC;                                    //背景贴图
	pDC = GetDC();
	CRect  rect2;
	GetClientRect(&rect2);                       //获取客户区大小
	Graphics graphics(pDC->m_hDC);
	//Graphics graphics(dc.m_hDC);
	Image image(L"./res/BG_MainUI.jpg", FALSE);
	graphics.DrawImage(&image, 0, 0, rect2.right, rect2.bottom);  //绘制背景

	CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HttpUpdateHeart, (LPVOID)NULL, 0, 0));   //发送心跳包 HttpHeartBeat

	m_Menu.LoadMenu(IDR_MEMUSER);  //  IDR_MENU1//菜单项
	SetMenu(&m_Menu);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSysMainUi::OnBnClickedGetperinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	/*if (NULL == m_pPerDlg)
	{
		m_pPerDlg = new CGetInfoPer();
		m_pPerDlg->Create(IDD_GETPERSON, this);
	}
	m_pPerDlg->ShowWindow(SW_SHOW);	*/
	CGetInfoPer PerDlg; //截取人脸图片
	if (IDOK == PerDlg.DoModal())
	{
		this->ShowWindow(SW_HIDE);
	}
}


void CSysMainUi::OnBnClickedBtnperinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == m_pPicDlg)
	{
		m_pPicDlg = new CPicture1();
		m_pPicDlg->Create(IDD_PERSON_INFO, this);
	}
	m_pPicDlg->ShowWindow(SW_SHOW);
}


void CSysMainUi::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdateData(TRUE);

	ViSet->AllLogOut();
	if (m_pConnection->State)  //关闭数据库连接
	{
		m_pConnection->Close();
	}

	PostQuitMessage(0);	  //退出消息环
	CDialogEx::OnClose();
}


void CSysMainUi::OnBnClickedGetoweinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == m_OwenInfo)
	{
		m_OwenInfo = new CGetOwerInfo();
		m_OwenInfo->Create(IDD_GetOwerInfo, this);
	}
	m_OwenInfo->ShowWindow(SW_SHOW);
}


void CSysMainUi::OnBnClickedBtnsendowerinfo()
{
	// TODO: 在此添加控件通知处理程序代码

}


void CSysMainUi::OnBnClickedBtnfaceoper()
{
	// TODO: 在此添加控件通知处理程序代码

	//if (NULL == m_FaceOpen)
	//{
	//	m_FaceOpen = new CFaceOper();
	//	m_FaceOpen->Create(IDD_DIAUPFACEPICTURE, this);
	//}
	//m_FaceOpen->ShowWindow(SW_SHOW);
	CFaceOper   FaceOpen;//人脸上传2
	if (IDOK == FaceOpen.DoModal())
	{
		this->ShowWindow(SW_HIDE);
	}
}


void CSysMainUi::OnBnClickedBtnRegister()
{
	// TODO: 在此添加控件通知处理程序代码

	/*if (NULL == m_PerRegis)
	{
		m_PerRegis = new CPerReg();
		m_PerRegis->Create(IDD_DIAREGISTER, this);
	}
	m_PerRegis->ShowWindow(SW_SHOW);*/

	CPerReg perReg;
	if (IDOK == perReg.DoModal())
	{
		this->ShowWindow(SW_HIDE);
	}
	
}


void CSysMainUi::OnBnClickedBtnOperPer()
{
	// TODO: 在此添加控件通知处理程序代码
	//if (NULL == m_PerModify)
	//{
	//	m_PerModify = new CPerModify();
	//	m_PerModify->Create(IDD_DIAMODIFY, this);
	//}

	//m_PerModify->ShowWindow(SW_SHOW);

	CPerModify perYZModify;
	if (IDOK == perYZModify.DoModal())
	{
		this->ShowWindow(SW_HIDE);
	}
}


void CSysMainUi::OnBnClickedButton1() //访客操作
{
	// TODO: 在此添加控件通知处理程序代码   CVistorsOper  *m_VistorOPer;
	//if (NULL == m_VistorOPer)
	//{
	//	m_VistorOPer = new CVistorsOper();
	//	m_VistorOPer->Create(IDD_DLGVISITOPER, this);
	//}
	//

	//m_VistorOPer->ShowWindow(SW_SHOW);

	CVistorsOper  VistorOPer;
	if (IDOK == VistorOPer.DoModal())
	{
		this->ShowWindow(SW_HIDE);
	}
}


void CSysMainUi::OnBnClickedBtnvrecord()  //访客记录
{
	// TODO: 在此添加控件通知处理程序代码 CVistorsRecord *m_VistorRecord;
	/*if (NULL == m_VistorRecord)
	{
		m_VistorRecord = new CVistorsRecord();
		m_VistorRecord->Create(IDD_DLGVISTRECORD, this);
	}

	m_VistorRecord->ShowWindow(SW_SHOW);*/

	CVistorsRecord VistorRecord;
	if (IDOK == VistorRecord.DoModal())
	{
		this->ShowWindow(SW_HIDE);
	}
}


void CSysMainUi::OnBnClickedBtnResult()  //人脸对比识别结果
{
	// TODO: 在此添加控件通知处理程序代码  CPersComprResult *m_PersCompare;
	if (NULL == m_PersCompare)
	{
		m_PersCompare = new CPersComprResult();
		m_PersCompare->Create(IDD_DLGPERSCOMRELT, this);
	}

	m_PersCompare->ShowWindow(SW_SHOW);

	//m_PersCompare = new CPersComprResult();
	//m_PersCompare->DoModal();
}

//CLogInfo  *m_LogInfo;
void CSysMainUi::OnBnClickedBtnlog()   //日志查询
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == m_LogInfo)
	{
		m_LogInfo = new CLogInfo();
		m_LogInfo->Create(IDD_DLGLOGINFO, this);
	}

	m_LogInfo->ShowWindow(SW_SHOW);
}


void CSysMainUi::OnBnClickedBtnzx()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IDYES == MessageBox(_T("是否注销？"), _T("注销"), MB_YESNO | MB_ICONASTERISK))
	{
		ViSet->AllLogOut();//登出所有摄像机
	
		////////////////////////日志////////////////////////////////////////////
		g_Action = _T("注销");

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

		}
		/////////////////////////////日志///////////////////////////////////////
		
		CDialogEx::OnOK();
	}
}


void CSysMainUi::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}

void CSysMainUi::ReSize()
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


void CSysMainUi::OnBnClickedBtnIoselect()
{
	// TODO: 在此添加控件通知处理程序代码

	CPERSONIO perIO;
	if (IDOK == perIO.DoModal())
	{
		this->ShowWindow(SW_HIDE);
	}
}


void CSysMainUi::OnBnClickedBtnOutfacepicture()
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL == m_ExportPicture)
	{
		m_ExportPicture = new CExportPicture();
		m_ExportPicture->Create(IDD_DIAEXPORT, this);
	}
	m_ExportPicture->ShowWindow(SW_SHOW);
	m_ExportPicture->ExportFun();
}

BOOL CSysMainUi::PreTranslateMessage(MSG* pMsg)   //禁用esc
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE) 
	{
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		return TRUE;
	}
	else
	{
		return CDialogEx::PreTranslateMessage(pMsg);
	} 	
}



void CSysMainUi::On32771()
{
	// TODO: 在此添加命令处理程序代码
	CAddUser addUser;
	addUser.DoModal();
}


void CSysMainUi::On32772()
{
	// TODO: 在此添加命令处理程序代码
	CDeleUser delUser;
	delUser.DoModal();
}


void CSysMainUi::On32773()
{
	// TODO: 在此添加命令处理程序代码
	OnBnClickedBtnzx();
}



void CSysMainUi::On32774()
{
	// TODO: 在此添加命令处理程序代码	
	ViSet->DoModal();
}


void CSysMainUi::SendSysTime()  //服务器发送系统时间
{
	WSADATA wd;
	int err;
	int iResult;//绑定结果

	err = WSAStartup(MAKEWORD(2, 2), &wd);
	if (0 != err)
	{
		WSACleanup();
		return;
	}

	SOCKET sockClient = NULL;
	sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (SOCKET_ERROR == sockClient)
	{
		closesocket(sockClient);
		return;
	}

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("192.168.35.61");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(5050);

	iResult = connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	if (iResult == SOCKET_ERROR) {	
		::MessageBox(NULL, "连接校时服务器失败！", NULL, 0);
		closesocket(sockClient);
		WSACleanup();
		return ;
	}
	
	/* 启动相应线程与客户端通信 */
	CloseHandle(CreateThread(NULL, 0, CSysMainUi::SendpondProc, ((LPVOID)sockClient), 0, 0));

}

DWORD WINAPI CSysMainUi::SendpondProc(LPVOID lpPar)
{
	SOCKET pClientSocket = (SOCKET)lpPar;
	MySysTime *mySysTime = new MySysTime;
	mySysTime->nEvent = 22; //协议头

	while (TRUE)
	{	
		Sleep(5000);	
		memset(&mySysTime->system_time, 0, sizeof(mySysTime->system_time));
 
		//GetLocalTime(&mySysTime->system_time);		//先获取本地时间

		CTime cCurrTim = CTime::GetCurrentTime();
		char szBuf[100] = "";
		CString g_TimeEnd = cCurrTim.Format("%Y%m%d%H%M%S");
		
		strcpy(szBuf, g_TimeEnd);
		int nSendLen = sizeof(mySysTime);
		int res = ::send(pClientSocket, (char *)szBuf, sizeof(szBuf), 0);
	}

	return 0;
}

void CSysMainUi::OnBnClickedBtnipset()
{
	// TODO: 在此添加控件通知处理程序代码
	ViSet->DoModal();
}
