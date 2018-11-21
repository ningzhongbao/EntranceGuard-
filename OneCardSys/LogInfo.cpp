// LogInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "LogInfo.h"
#include "afxdialogex.h"


// CLogInfo 对话框

IMPLEMENT_DYNAMIC(CLogInfo, CDialogEx)

CLogInfo::CLogInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLGLOGINFO, pParent)
	, m_Begin_String(COleDateTime::GetCurrentTime())
	, m_End_String(COleDateTime::GetCurrentTime())
{

}

CLogInfo::~CLogInfo()
{
}

void CLogInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTLOGINFO, m_listLogInfo);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Begin_String);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_End_String);
}


BEGIN_MESSAGE_MAP(CLogInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CLogInfo::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CLogInfo::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BtnView, &CLogInfo::OnBnClickedBtnview)
	ON_BN_CLICKED(IDC_BtnYL, &CLogInfo::OnBnClickedBtnyl)
	ON_BN_CLICKED(IDC_BTNVINIT, &CLogInfo::OnBnClickedBtnvinit)
	ON_BN_CLICKED(IDC_BtnCKRZ, &CLogInfo::OnBnClickedBtnckrz)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BtnExcel, &CLogInfo::OnBnClickedBtnexcel)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTLOGINFO, &CLogInfo::OnLvnItemchangedListloginfo)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CLogInfo 消息处理程序
BOOL CLogInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

									// TODO: 在此添加额外的初始化代码
	CRect rect1;
	GetClientRect(&rect1);     //取客户区大小  
	old.x = rect1.right - rect1.left;
	old.y = rect1.bottom - rect1.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);

	
	CRect rect;
	m_listLogInfo.GetClientRect(&rect);

	m_listLogInfo.SetExtendedStyle(m_listLogInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listLogInfo.InsertColumn(0, _T("ID"), LVCFMT_LEFT, rect.Width() / 7, 0);
	m_listLogInfo.InsertColumn(1, _T("姓名"), LVCFMT_LEFT, rect.Width() / 12, 1);
	m_listLogInfo.InsertColumn(2, _T("类型"), LVCFMT_LEFT, rect.Width() / 6, 2);
	m_listLogInfo.InsertColumn(3, _T("开始时间"), LVCFMT_LEFT, rect.Width() / 8, 3);
	m_listLogInfo.InsertColumn(4, _T("结束时间"), LVCFMT_LEFT, rect.Width() / 8, 4);
	m_listLogInfo.InsertColumn(5, _T("行为"), LVCFMT_LEFT, rect.Width() / 3, 5);
	m_listLogInfo.InsertColumn(6, _T("IP地址"), LVCFMT_LEFT, rect.Width() / 6, 6);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLogInfo::OnBnClickedButton2()   //查看日志
{
	// TODO: 在此添加控件通知处理程序代码
}


void CLogInfo::OnBnClickedButton3()   //导出Excel表
{
	// TODO: 在此添加控件通知处理程序代码
}


void CLogInfo::OnBnClickedBtnview()
{
	// TODO: 在此添加控件通知处理程序代码
	
}


void CLogInfo::OnBnClickedBtnyl()
{
	// TODO: 在此添加控件通知处理程序代码

	CDialogEx::OnCancel();
}


void CLogInfo::OnBnClickedBtnvinit()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CLogInfo::OnBnClickedBtnckrz()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	try
	{	
		CString Sql;

		Sql.Format(_T("SELECT * FROM [FaceContCen].[dbo].[SysRunLog] WHERE RZDate BETWEEN '%d-%d-%d' and '%d-%d-%d'"), m_Begin_String.GetYear(), m_Begin_String.GetMonth(), m_Begin_String.GetDay(),m_End_String.GetYear(), m_End_String.GetMonth(), m_End_String.GetDay());
		
		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		CString ID;
		CString Name;
		CString Type;
		CString BeginTime;
		CString EndTime;
		CString XW; //行为
		CString IPAddr = "";
		_variant_t varTmp;
		m_listLogInfo.DeleteAllItems();

		for (int i = 0; !m_pRecordSet->adoEOF; i++)
		{
			varTmp = m_pRecordSet->GetCollect(_variant_t(_T("IdNum")));
			if (varTmp.vt != VT_NULL)
			{
				ID = varTmp;
			}
			varTmp = m_pRecordSet->GetCollect(_variant_t(_T("Name")));
			if (varTmp.vt != VT_NULL)
			{
				Name = varTmp;
			}
			varTmp = m_pRecordSet->GetCollect(_variant_t(_T("QX")));
			if (varTmp.vt != VT_NULL)
			{
				Type = varTmp;
			}
			else
			{
				Type = "";
			}
			varTmp = m_pRecordSet->GetCollect(_variant_t(_T("BeginData")));
			if (varTmp.vt != VT_NULL)
			{
				BeginTime = varTmp;
			}
			varTmp = m_pRecordSet->GetCollect(_variant_t(_T("EndData")));
			if (varTmp.vt != VT_NULL)
			{
				EndTime = varTmp;
			}
			varTmp = m_pRecordSet->GetCollect(_variant_t(_T("Action")));
			if (varTmp.vt != VT_NULL)
			{
				XW = varTmp;
			}
			varTmp = m_pRecordSet->GetCollect(_variant_t(_T("Ip")));
			if (varTmp.vt != VT_NULL)
			{
				IPAddr = varTmp;
			}


			m_listLogInfo.InsertItem(i, ID.GetString());
			m_listLogInfo.SetItemText(i, 1, Name.GetBuffer(0));
			m_listLogInfo.SetItemText(i, 2, Type.GetString());
			m_listLogInfo.SetItemText(i, 3, BeginTime.GetString());
			m_listLogInfo.SetItemText(i, 4, EndTime.GetString());
			m_listLogInfo.SetItemText(i, 5, XW.GetString());
			m_listLogInfo.SetItemText(i, 6, IPAddr.GetString());

			m_pRecordSet->MoveNext();
		}

	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}

		CATCH_ERROR;
	}
	if (m_pRecordSet->State)
	{
		m_pRecordSet->Close();
	}






	//////////////////////////日志////////////////////////////////////////////
	//g_Action = "查看日志";

	//CTime tmp_tm = CTime::GetCurrentTime();
	//CString TimeEnd = tmp_tm.Format("%y年%m月%d日%H时%M分%S秒");
	//try
	//{
	//	CString Sql;
	//	Sql.Format("INSERT INTO [FaceContCen].[dbo].[SysRunLog](IdNum,Name,QX,BeginData,EndData,Action,Ip,SysRun) Values(%d,'%s','%s','%s','%s','%s','%s','%s')", g_UserId, g_UseName, g_QX, g_Time, TimeEnd, g_Action, g_Ip, g_SysRunRZ);

	//	m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
	//		adLockOptimistic, adCmdText);

	//}
	//catch (_com_error e)
	//{
	//	CATCH_ERROR;
	//}
	//if (m_pRecordSet->State)
	//{
	//	m_pRecordSet->Close();
	//}

	///////////////////////////////日志///////////////////////////////////////
	UpdateData(FALSE);
}


void CLogInfo::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}

void CLogInfo::ReSize()
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


void CLogInfo::OnBnClickedBtnexcel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (0 == m_listLogInfo.GetItemCount())
	{
		MessageBox("没有数据", NULL, MB_OK);
		return;
	}
	CString Ip[1024], Name[1024], Type[1024], BeginTime[1024], EndTime[1024], XW[1024], IpAddr[1024];

	CString strFileName = _T("智能人脸出入口控制系统 V1.0 日志");
	int i = 0;
	int j = 0;
	CString fileName = "c:\\" + strFileName + ".xls";//保存路径是d：盘根目录
	
	CFile file(fileName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive);
	CString header = _T("ID\t 姓名\t 类型\t 开始时间\t 结束时间\t 行为\t IP地址\n");
	file.Write(header, header.GetLength());

	j = m_listLogInfo.GetItemCount();
	if (j > 0)
	{
		for (i = 0; i < j; i++)
		{
			Ip[i] = m_listLogInfo.GetItemText(i, 0);
			Name[i] = m_listLogInfo.GetItemText(i, 1);
			Type[i] = m_listLogInfo.GetItemText(i, 2);
			BeginTime[i] = m_listLogInfo.GetItemText(i, 3);
			EndTime[i] = m_listLogInfo.GetItemText(i, 4);
			XW[i] = m_listLogInfo.GetItemText(i, 5);
			IpAddr[i] = m_listLogInfo.GetItemText(i, 6);


			CString msg;
			msg.Format(_T("%s\t%s\t%s\t%s\t%s\t%s\t%s\n"), Ip[i], Name[i], Type[i], BeginTime[i], EndTime[i], XW[i], IpAddr[i]);

			file.Write(msg, msg.GetLength());      
		}
	}	
	file.Close();	

	MessageBox("导出到Excel成功", "成功", MB_OK);
	
	
	////////////////////////日志////////////////////////////////////////////
	g_Action = "日志导出excel表";

	CTime tmp_tm = CTime::GetCurrentTime();
	CString TimeEnd = tmp_tm.Format("%Y-%m-%d %H:%M:%S");
	try
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}

		CString Sql;
		Sql.Format(_T("INSERT INTO [FaceContCen].[dbo].[SysRunLog](IdNum,Name,QX,BeginData,EndData,Action,Ip,SysRun) Values(%d,'%s','%s','%s','%s','%s','%s','%s')"), g_UserId, g_UseName, g_QX, g_Time, TimeEnd, g_Action, g_Ip, g_SysRunRZ);

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}

		CATCH_ERROR;
	}
	if (m_pRecordSet->State)
	{
		m_pRecordSet->Close();
	}
	/////////////////////////////日志///////////////////////////////////////
}


void CLogInfo::OnLvnItemchangedListloginfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CLogInfo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	//CDC *pDC;
	//pDC = GetDC();
	//CRect  rect;
	//GetClientRect(&rect);   //获取客户区大小
	//Graphics graphics(pDC->m_hDC);
	////Graphics graphics(dc.m_hDC);
	//Image image(L"./res/rz2.jpg", TRUE);
	//graphics.DrawImage(&image, 0, 0, rect.right, rect.bottom);  //绘制背景
}
