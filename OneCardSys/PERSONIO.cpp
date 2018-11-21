// PERSONIO.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "PERSONIO.h"
#include "afxdialogex.h"


// CPERSONIO 对话框

IMPLEMENT_DYNAMIC(CPERSONIO, CDialogEx)

CPERSONIO::CPERSONIO(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIAIOSELECT, pParent)
	, m_Begin_String(COleDateTime::GetCurrentTime())
	, m_End_String(COleDateTime::GetCurrentTime())
{

}

CPERSONIO::~CPERSONIO()
{
}

void CPERSONIO::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATEBEGIN, m_Begin_String);
	DDX_DateTimeCtrl(pDX, IDC_DATEEND, m_End_String);

	DDX_Control(pDX, IDC_LISTSHOW, m_listLogInfo);
}


BEGIN_MESSAGE_MAP(CPERSONIO, CDialogEx)
	ON_BN_CLICKED(IDC_Btn_Select, &CPERSONIO::OnBnClickedBtnSelect)
	ON_BN_CLICKED(IDC_Btn_Close, &CPERSONIO::OnBnClickedBtnClose)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BtnPrint, &CPERSONIO::OnBnClickedBtnprint)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTSHOW, &CPERSONIO::OnLvnItemchangedListshow)
	ON_BN_CLICKED(IDC_BtnPrintToA4, &CPERSONIO::OnBnClickedBtnprinttoa4)
END_MESSAGE_MAP()


// CPERSONIO 消息处理程序


void CPERSONIO::OnBnClickedBtnSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	try
	{
		CString Sql;

		Sql.Format("SELECT * FROM [FaceContCen].[dbo].[ReconResult_T] WHERE DateTime BETWEEN '%d-%d-%d' and '%d-%d-%d'", m_Begin_String.GetYear(), m_Begin_String.GetMonth(), m_Begin_String.GetDay(), m_End_String.GetYear(), m_End_String.GetMonth(), m_End_String.GetDay());

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		CString strName;
		CString strSex;
		CString strReconMethod;
		CString strIDNum;
		CString strTel;
		CString strAddr; //行为
		CString strPerType;
		CString strSimilarity;
		_variant_t varTmp;

		m_listLogInfo.DeleteAllItems();

		for (int i = 0; !m_pRecordSet->adoEOF; i++)
		{
			varTmp = m_pRecordSet->GetCollect(_variant_t(_T("Name")));
			if (varTmp.vt != VT_NULL)
			{
				strName = varTmp;
			}
			varTmp = m_pRecordSet->GetCollect(_variant_t(_T("Sex")));
			if (varTmp.vt != VT_NULL)
			{
				strSex = varTmp;
			}
			else
			{
				strSex = "";
			}
			varTmp = m_pRecordSet->GetCollect(_variant_t(_T("ReconMothed")));
			if (varTmp.vt != VT_NULL)
			{
				strReconMethod = varTmp;
			}
			else
			{
				strReconMethod = "";
			}

			varTmp = m_pRecordSet->GetCollect(_variant_t(_T("IDNum")));
			if (varTmp.vt != VT_NULL)
			{
				strIDNum = varTmp;
			}
			else
			{
				strIDNum = "";
			}

			varTmp = m_pRecordSet->GetCollect(_variant_t(_T("Tel")));
			if (varTmp.vt != VT_NULL)
			{
				strTel = varTmp;
			}
			else
			{
				strTel = "";
			}

			varTmp = m_pRecordSet->GetCollect(_variant_t(_T("Addr")));
			if (varTmp.vt != VT_NULL)
			{
				strAddr = varTmp;
			}
			else
			{
				strAddr = "";
			}

			varTmp = m_pRecordSet->GetCollect(_variant_t(_T("PerType")));
			if (varTmp.vt != VT_NULL)
			{
				strPerType = varTmp;
			}
			else
			{
				strPerType = "";
			}

			varTmp = m_pRecordSet->GetCollect(_variant_t(_T("Similarity")));
			if (varTmp.vt != VT_NULL)
			{
				strSimilarity = varTmp;
			}
			else
			{
				strSimilarity = "";
			}

			CString tmpOutTime = "";   //离开时间
			varTmp = m_pRecordSet->GetCollect(_variant_t(_T("OutTime")));
			if (varTmp.vt != VT_NULL)
			{
				tmpOutTime = varTmp;
			}
			else
			{
				tmpOutTime = "";
			}
			m_listLogInfo.InsertItem(i,     strName.GetString());
			m_listLogInfo.SetItemText(i, 1, strSex.GetBuffer(0));
			m_listLogInfo.SetItemText(i, 2, strReconMethod.GetString());
			m_listLogInfo.SetItemText(i, 3, strIDNum.GetString());
			m_listLogInfo.SetItemText(i, 4, strTel.GetString());
			m_listLogInfo.SetItemText(i, 5, strAddr.GetString());
			m_listLogInfo.SetItemText(i, 6, strPerType.GetString());
			m_listLogInfo.SetItemText(i, 7, tmpOutTime.GetString());
			m_listLogInfo.SetItemText(i, 8, strSimilarity.GetString());

			m_pRecordSet->MoveNext();
		}
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

		CATCH_ERROR;
	}


	//////////////////////////日志////////////////////////////////////////////
	g_Action = "查看人员进出入信息";

	CTime tmp_tm = CTime::GetCurrentTime();
	CString TimeEnd = tmp_tm.Format("%Y-%m-%d %H:%M:%S");
	try
	{
		CString Sql;
		Sql.Format("INSERT INTO [FaceContCen].[dbo].[SysRunLog](IdNum,Name,QX,BeginData,EndData,Action,Ip,SysRun) Values(%d,'%s','%s','%s','%s','%s','%s','%s')", g_UserId, g_UseName, g_QX, g_Time, TimeEnd, g_Action, g_Ip, g_SysRunRZ);

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);
	}
	catch (_com_error e)
	{
		CATCH_ERROR;
	}
	if (m_pRecordSet->State)
	{
		m_pRecordSet->Close();
	}

	///////////////////////////////日志///////////////////////////////////////
	UpdateData(FALSE);

}


void CPERSONIO::OnBnClickedBtnClose()
{
	// TODO: 在此添加控件通知处理程序代码

	CDialogEx::OnCancel();
}


BOOL CPERSONIO::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	CRect rect1;              //窗口等比例放大缩小
	GetClientRect(&rect1);     //取客户区大小  
	old.x = rect1.right - rect1.left;
	old.y = rect1.bottom - rect1.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);

	m_Font.CreatePointFont(230, _T("Arial"), NULL);  //设置字体大小
	m_static.SetFont(&m_Font, true);

	CRect rect;
	m_listLogInfo.GetClientRect(&rect);
	m_listLogInfo.SetExtendedStyle(m_listLogInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listLogInfo.InsertColumn(0, _T("姓名"), LVCFMT_LEFT, rect.Width() / 7, 0);
	m_listLogInfo.InsertColumn(1, _T("性别"), LVCFMT_LEFT, rect.Width() / 7, 1);
	m_listLogInfo.InsertColumn(2, _T("识别方式"), LVCFMT_LEFT, rect.Width() / 7, 2);
	m_listLogInfo.InsertColumn(3, _T("身份证"), LVCFMT_LEFT, rect.Width() / 7, 3);
	m_listLogInfo.InsertColumn(4, _T("电话"), LVCFMT_LEFT, rect.Width() / 7, 4);
	m_listLogInfo.InsertColumn(5, _T("住址"), LVCFMT_LEFT, rect.Width() / 5, 5);
	m_listLogInfo.InsertColumn(6, _T("类型"), LVCFMT_LEFT, rect.Width() / 7, 6);
	m_listLogInfo.InsertColumn(7, _T("离开时间"), LVCFMT_LEFT, rect.Width() / 6, 7);
	m_listLogInfo.InsertColumn(8, _T("相似度"), LVCFMT_LEFT, rect.Width() / 8, 8);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPERSONIO::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnClose();
}


void CPERSONIO::OnPaint()
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
	//Image image(L"./res/RZ.jpg", TRUE);
	//graphics.DrawImage(&image, 0, 0, rect.right, rect.bottom);  //绘制背景
}


void CPERSONIO::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}


void CPERSONIO::OnBnClickedBtnprint()
{
	// TODO: 在此添加控件通知处理程序代码
	if (0 == m_listLogInfo.GetItemCount())
	{
		MessageBox(_T("没有数据"), NULL, MB_OK);
		return;
	}
	CString Name, Sex, RenconMoth, IdNum, Tel, Addr, Type, XSD,Time;

	CString strFileName = _T("人员进出入查询 V1.0");
	int i = 0;
	int j = 0;
	CString fileName = _T("c:\\") + strFileName + _T(".xls");//保存路径是d：盘根目录

	CFile file(fileName, CFile::modeCreate | CFile::modeWrite);

	CString header = _T("姓名\t 性别\t 识别方式\t 身份证\t 电话\t 住址\t 类型\t 相似度 \t时间\n");
	file.Write(header, header.GetLength());

	j = m_listLogInfo.GetItemCount();
	if (j > 0)
	{
		for (i = 0; i < j; i++)
		{
			Name = m_listLogInfo.GetItemText(i, 0);
			Sex = m_listLogInfo.GetItemText(i, 1);			
			RenconMoth = m_listLogInfo.GetItemText(i, 2);
			IdNum = m_listLogInfo.GetItemText(i, 3);
			Tel = m_listLogInfo.GetItemText(i, 4);
			Addr = m_listLogInfo.GetItemText(i, 5);
			Type = m_listLogInfo.GetItemText(i, 6);
			XSD = m_listLogInfo.GetItemText(i, 7);
			Time = m_listLogInfo.GetItemText(i, 8);

			CString msg;
			msg.Format(_T("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n"),  Name, Sex, RenconMoth, IdNum,Tel, Addr, Type, XSD, Time);

			file.Write(msg, msg.GetLength());
		}
	}
	file.Close();

	MessageBox(_T("导出到Excel成功"), _T("成功"), MB_OK);

	////////////////////////日志////////////////////////////////////////////
	g_Action = _T("人员进出入导出excel表");
	CTime tmp_tm = CTime::GetCurrentTime();
	CString TimeEnd = tmp_tm.Format("%Y-%m-%d %H:%M:%S");
	try
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}

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

	//	CATCH_ERROR;
	}	
	/////////////////////////////日志///////////////////////////////////////
}


//int sort_column; // 记录点击的列
//
//bool method; // 记录比较方法
//
// //?比较函数
//static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
//{
//
//	//?从参数中提取所需比较lc的两行数据
//
//	int row1 = (int)lParam1;
//	int row2 = (int)lParam2;
//
//	CListCtrl* lc = (CListCtrl*)lParamSort;
//
//	CString lp1 = lc->GetItemText(row1, sort_column);
//	CString lp2 = lc->GetItemText(row2, sort_column);
//
//
//	//?比较，对不同的列，不同比较，注意记录前一次排序方向，下一次要相反排序
//	if (sort_column < 2)
//	{
//		//int型比较
//		if (method)
//			return atoi(lp1) - atoi(lp2);
//		else
//			return atoi(lp1) - atoi(lp1);
//	}
//	else
//	{
//		//文字型比较
//		if (method)
//			return lp1.CompareNoCase(lp2);
//		else
//			return lp2.CompareNoCase(lp1);
//	}
//
//	return 0;
//}


void CPERSONIO::OnLvnItemchangedListshow(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	//sort_column = pNMLV->iSubItem;//点击的列

	//int count = m_listLogInfo.GetItemCount();


	////?每行的比较关键字，此处为列序号（点击的列号），可以设置为其他 比较函数的第一二个参数
	//for (int i = 0; i < count; i++)
	//{
	//	m_listLogInfo.SetItemData(i, i);
	//}

	//m_listLogInfo.SortItems(MyCompareProc, (DWORD_PTR)&m_listLogInfo);//排序 第二个参数是比较函数的第三个参数


	*pResult = 0;
}

void CPERSONIO::ReSize()
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

typedef struct tagColAtt
{
	int       nColIndex;
	CString   strColText;
	int       nPrintX;
	int       nSubItemIndex;
}COLATT;


void CPERSONIO::OnBnClickedBtnprinttoa4()   //打印
{
	// TODO: 在此添加控件通知处理程序代码
	PRINTDLG pd;
	pd.lStructSize = sizeof(PRINTDLG);
	pd.Flags = PD_RETURNDC;
	pd.hDC = NULL;
	pd.hwndOwner = NULL;
	pd.hInstance = NULL;
	pd.nMaxPage = 1;
	pd.nMinPage = 1;
	pd.nFromPage = 1;
	pd.nToPage = 1;
	pd.nCopies = 1;
	pd.hDevMode = NULL;
	pd.hDevNames = NULL;

	//显示打印对话框，由用户来设定纸张大小等。 
	if (!PrintDlg(&pd))
	{
		return;
	}
	ASSERT(pd.hDC != NULL);

	int nHorRes = GetDeviceCaps(pd.hDC, HORZRES);
	int nVerRes = GetDeviceCaps(pd.hDC, VERTRES);
	int nXMargin  = 2;
	int  nYMargin = 2;
	TEXTMETRIC tm;
	GetTextMetrics(pd.hDC, &tm);
	int nCharHeight = tm.tmHeight;
	int nCharWidth = tm.tmAveCharWidth;

	CHeaderCtrl* pHeader = m_listLogInfo.GetHeaderCtrl();

	//获得行，列的个数 
	int nColCount  = pHeader->GetItemCount();
	int nLineCount = m_listLogInfo.GetItemCount();
	int ColOrderArray[100];
	COLATT ca[100];
	m_listLogInfo.GetColumnOrderArray(ColOrderArray, nColCount);
	int nColX = nXMargin*nCharWidth;

	//检索各列的信息，确定列标题的内容长度。 
	for (int i = 0; i < nColCount; i++)
	{
		ca[i].nColIndex = ColOrderArray[i];
		LVCOLUMN lvc;
		TCHAR text[100];
		lvc.mask = LVCF_TEXT | LVCF_SUBITEM;
		lvc.pszText = text;
		lvc.cchTextMax = 100;
		m_listLogInfo.GetColumn(ca[i].nColIndex, &lvc);
		ca[i].strColText = lvc.pszText;
		ca[i].nSubItemIndex = lvc.iSubItem;
		ca[i].nPrintX = nColX;
		nColX += nCharWidth * strlen(ca[i].strColText);
		if (nColX > nHorRes)
		{
			DeleteDC(pd.hDC);
			AfxMessageBox(_T("字段太多，无法在一行内打印，请试用较大的纸，或横向打印。 "));
			return ;
		}
	}
	DOCINFO di;
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = _T("人员进出入信息");
	di.lpszOutput = (LPTSTR)NULL;
	di.lpszDatatype = (LPTSTR)NULL;
	di.fwType = 0;
	StartDoc(pd.hDC, &di);
	StartPage(pd.hDC);
	//TextOut(pd.hDC, nHorRes / 3, nYMargin, _T("人员进出入信息"), strlen(_T("人员进出入信息")));

	//调整各列的宽度，以使各列在后面的打印输出时更均匀的打印在纸上。 
	int space = (nHorRes - nXMargin*nCharWidth - nColX) / (nColCount - 1);
	for (int i = 1; i < nColCount; i++)
	{
		ca[i].nPrintX += i*space;
	}

	//输出列标题 
	for (int i = 0; i < nColCount; i++)
	{
		TextOut(pd.hDC, ca[i].nPrintX, nYMargin,ca[i].strColText, strlen(ca[i].strColText));
	}
		
	int nMaxLinePerPage = nVerRes / nCharHeight - 3;
	int nCurPage = 1;

	//输出各列的数据 
	for (int i = 0; i < nLineCount; i++)
	{
		for (int j = 0; j < nColCount; j++)
		{
			if (i + 1 - (nCurPage - 1)*nMaxLinePerPage > nMaxLinePerPage)
			{
				//新的一页 
				EndPage(pd.hDC);
				StartPage(pd.hDC);
				nCurPage++;
			}
			CString subitem = m_listLogInfo.GetItemText(i, ca[j].nSubItemIndex);
			TextOut(pd.hDC, ca[j].nPrintX, nYMargin + (i + 1 - (nCurPage - 1)*nMaxLinePerPage)*nCharHeight, subitem, strlen(subitem));
		}
	}

	EndPage(pd.hDC);
	EndDoc(pd.hDC);
	DeleteDC(pd.hDC);	//打印结束 

	AfxMessageBox(_T("打印成功"));

	return;
}
