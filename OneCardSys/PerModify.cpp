// PerModify.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "PerModify.h"
#include "afxdialogex.h"


// CPerModify 对话框

IMPLEMENT_DYNAMIC(CPerModify, CDialogEx)

CPerModify::CPerModify(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIAMODIFY, pParent)
	, m_ID_String(_T(""))
	, m_Name_String(_T(""))
	, m_ShowTip(_T(""))
	, m_IDs(_T(""))
	, m_Names(_T(""))
	, m_XB(_T(""))
	, m_Tel(_T(""))
	, m_ShowPath(_T(""))
	, m_LD(_T(""))
	, m_Type_string(_T(""))
	, m_FH_String(_T(""))	
	, m_UseLogOut_String(_T(""))
{

}

CPerModify::~CPerModify()
{
}

void CPerModify::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_ID_String);
	DDX_Text(pDX, IDC_EDIT_Name, m_Name_String);
	DDX_Control(pDX, IDC_Picture, m_Picture);
	DDX_Text(pDX, IDC_EDIT_ShowTip, m_ShowTip);
	DDX_Text(pDX, IDC_EDIT_IDs, m_IDs);
	DDX_Text(pDX, IDC_EDIT_Names, m_Names);
	DDX_CBString(pDX, IDC_COM_XB, m_XB);
	DDX_Text(pDX, IDC_EDIT_Tel, m_Tel);
	DDX_Text(pDX, IDC_EDIT_Path, m_ShowPath);
	DDX_Text(pDX, IDC_EDIT_RegType, m_Type_string);
	DDX_Text(pDX, IDC_EDIT_FH, m_FH_String);
	DDX_Text(pDX, IDC_EDIT_LDS, m_LD);
	DDX_Control(pDX, IDC_LISTSHOWINFO, m_ListShowInfo);
	DDX_Text(pDX, IDC_SLogOut, m_UseLogOut_String);
}


BEGIN_MESSAGE_MAP(CPerModify, CDialogEx)
	ON_BN_CLICKED(IDC_BtnSelect, &CPerModify::OnBnClickedBtnselect)
	ON_BN_CLICKED(IDC_Btn_Modify, &CPerModify::OnBnClickedBtnModify)
	ON_BN_CLICKED(IDC_Btn_Dele, &CPerModify::OnBnClickedBtnDele)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BtnSeleAll, &CPerModify::OnBnClickedBtnseleall)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTSHOWINFO, &CPerModify::OnLvnItemchangedListshowinfo)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BtnZHPerLogOut, &CPerModify::OnBnClickedBtnzhperlogout)
END_MESSAGE_MAP()


void CPerModify::InitData()
{
	m_IDs = "";
	m_Names = "";
	m_XB = "";
	m_Tel = "";
	m_ShowPath = "";
	m_LD = "";
	m_FH_String = "";
	m_Type_string = "";

	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_Picture);
	CRect lRect;
	pStatic->GetClientRect(&lRect);
	pStatic->GetDC()->FillSolidRect(lRect.left, lRect.top, lRect.Width(), lRect.Height(), RGB(240, 240, 240));
	InvalidateRect(NULL, FALSE);
}

// CPerModify 消息处理程序


void CPerModify::OnBnClickedBtnselect()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	InitData();	//clear();

	if (m_ID_String.IsEmpty() && m_ID_String == "" && m_Name_String.IsEmpty() && m_Name_String == "")
	{
		m_ShowTip = _T("查询条件不能为空！");
		UpdateData(FALSE);

		return;
	}

	/************************************************************************/
	/* 查询数据                                                                     */
	/************************************************************************/
	try
	{
		CString Sql;
		Sql.Format("SELECT * FROM [FaceContCen].[dbo].[PersonInfo] WHERE RegType = '%s' OR Name = '%s'", m_ID_String, m_Name_String);
		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		_variant_t FP;
		FP = m_pRecordSet->GetCollect(_variant_t(_T("ID"))); //id
		m_IDs = FP.bstrVal;
		m_Names = m_pRecordSet->GetCollect(_variant_t(_T("Name"))); //姓名
		m_XB = m_pRecordSet->GetCollect(_variant_t(_T("Sex")));
		m_Tel = m_pRecordSet->GetCollect(_variant_t(_T("Tel")));
		m_Type_string = m_pRecordSet->GetCollect(_variant_t(_T("RegType")));
		m_RegDateTime = m_pRecordSet->GetCollect(_variant_t(_T("RegDateTime"))); //登记时间
		m_LD = m_pRecordSet->GetCollect(_variant_t(_T("LD")));
		m_FH_String = m_pRecordSet->GetCollect(_variant_t(_T("FH")));
		m_UseLogOut_String = m_pRecordSet->GetCollect(_variant_t(_T("LogOut")));
		m_PicLen = m_pRecordSet->GetCollect(_variant_t("PictureLength"));  //图片大小
		varPicDate = m_pRecordSet->GetFields()->GetItem("PictureDate")->GetChunk(m_PicLen);//读图片数据
		if (m_pRecordSet->State)  //如果数据库记录打开就关闭记录集
		{
			m_pRecordSet->Close(); //关闭记录集 
		}

		/************************************************************************/
		/*  //创建文件夹                                                         */
		/************************************************************************/
		m_strPath = _T("C:\\YTPicture");  
		if (!PathIsDirectory(m_strPath))
		{
			CreateDirectory(m_strPath, 0);//不存在则创建
		}
		m_strPath = _T("C:\\YTPicture\\ZHPictureReg");//每次把选择路径给cspath，防止cstring叠加，出错
		if (!PathIsDirectory(m_strPath))
		{
			CreateDirectory(m_strPath, 0);//不存在则创建	}　
		}
		m_strPath += _T("\\") + m_IDs + _T(".jpg");  //照片路径
		
		/************************************************************************/
		/* EJZToPicture()将数据库中的二进制照片数据存到本地c盘                  */
		/************************************************************************/
		if (EJZToPicture(m_strPath, m_PicLen, varPicDate) != TRUE)
		{
			m_ShowTip = _T("人脸照片加载失败！");
		}		
		
		
		Ui_Show(m_strPath);  //显示照片
		Sql.ReleaseBuffer();  //释放缓冲
		m_ShowTip =_T("姓名:  ") + m_Names + _T("     身份证:  ") + m_Type_string + _T("    登记时间:  ") + m_RegDateTime;
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}

		m_ShowTip = _T(" ID: ") + m_ID_String + _T("\n 姓名: ") + m_Name_String + _T("\n 查询失败，请重新查询");
	}

	////////////////////////日志////////////////////////////////////////////
	g_Action = _T("查询用户");
	OperRZ(g_Action); 
	////////////////////////日志///////////////////////////////////////

	UpdateData(FALSE);
}



void CPerModify::Ui_Show(CString strPicture_Path)
{
	WCHAR buf[1024];
	CRect rect;
	USES_CONVERSION;
	wcscpy(buf, A2W((LPCSTR)strPicture_Path));  //CString -> wchar_t

	Image image(buf, TRUE);
	CWnd *pWnd = GetDlgItem(IDC_Picture);
	Graphics graphics(pWnd->GetDC()->m_hDC);
	GetDlgItem(IDC_Picture)->GetClientRect(&rect);
	graphics.DrawImage(&image, 0, 0, rect.Width(), rect.Height());
}

void CPerModify::OnBnClickedBtnModify()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_IDs.IsEmpty())
	{
		m_ShowTip = _T("身份证为空，修改失败");
		UpdateData(FALSE);

		return;
	}
	try
	{
		CString Sql;
		Sql.Format("UPDATE  [FaceContCen].[dbo].[PersonInfo] SET Name = '%s', Sex = '%s', Tel='%s',LD = '%s',FH='%s',RegType = '%s' WHERE ID = '%s'", m_Names, m_XB, m_Tel, m_LD, m_FH_String, m_Type_string, m_IDs);

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		Sql.ReleaseBuffer();
		m_ShowTip = _T(" ID: ") + m_ID_String + _T("\n  姓名: ") + m_Name_String + _T("\n  修改成功");
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //关闭记录集 
		}
	}
	catch (_com_error e)
	{
		m_ShowTip = _T(" ID: ") + m_ID_String + _T("\n 姓名: ") + m_Name_String + _T("\n 修改失败，请重新修改");
		CATCH_ERROR;
	}	

	////////////////////////日志////////////////////////////////////////////
	g_Action = "修改用户";
	OperRZ(g_Action);

	InvalidateRect(NULL, FALSE);
	UpdateData(FALSE);
}


void CPerModify::OperRZ(CString g_Action)
{
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
		//	CATCH_ERROR;
	}
}

BOOL CPerModify::DropApointFace(LONG lFaceLoginId)
{

	if (TRUE != Net_PreFindFaceInfo(lFaceLoginId))   //删除摄像机户主人脸图片
	{
		Net_CloseFindFaceInfo(lFaceLoginId);
		return FALSE;
	}

	STU_PERSON_INFO_GET_BYID_IN_PARAM pInParam = { 0 };
	STU_PERSON_INFO_GET_BYID_OUT_PARAM pOutParam = { 0 };

	memcpy(pInParam.szCertificateType, m_person_certificate_type.GetBuffer(0), m_person_certificate_type.GetLength());
	m_person_certificate_type.ReleaseBuffer();

	memcpy(pInParam.szID, m_IDs.GetBuffer(0), m_IDs.GetLength());
	m_IDs.ReleaseBuffer();

	if (TRUE != Net_GetPersonInfoByID(lFaceLoginId, &pInParam, &pOutParam))
	{
		m_ShowTip = _T("没有找到该身份证对应的人脸");

		UpdateData(FALSE);
		return FALSE;
	}

	if (TRUE != DeletePersonInfo(lFaceLoginId, (&pOutParam)->stPersonInfo.nPersonID))
	{
		m_ShowTip = _T("删除人脸失败，请再试一次");

		UpdateData(FALSE);
		return FALSE;
	}
	Net_CloseFindFaceInfo(lFaceLoginId);

	return TRUE;
}

void CPerModify::OnBnClickedBtnDele()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CString m_strIdTmp = "";
	if (m_IDs.IsEmpty())
	{
		m_ShowTip = _T("身份证为空，删除失败");
		UpdateData(FALSE);

		return;
	}	
	try    //查看身份证是否在数据库中，不再说明输错或者已经签离或者未登记
	{
		CString Sql;
		Sql.Format("SELECT ID FROM [FaceContCen].[dbo].[PersonInfo] WHERE RegType = '%s'", m_ID_String);
		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);
		_variant_t FP;
		FP = m_pRecordSet->GetCollect(_variant_t(_T("ID")));
		if (FP.vt != VT_NULL)//如果不为空
		{
			m_strIdTmp = FP;
		}else{
			m_strIdTmp = "";
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
		AfxMessageBox(_T("身份证错误,请重新输入"));

		return;
	}

	if (DropFacePicture(m_strIdTmp, m_lLoginID) != TRUE) //删除摄像机照片
	{
		//return;
	}

	try    //删除数据库户主数据
	{
		CString Sql;
		Sql.Format("DELETE  FROM [FaceContCen].[dbo].[PersonInfo] WHERE ID = '%s'", m_IDs);

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		Sql.ReleaseBuffer();
		m_ShowTip = _T(" ID: ") + m_ID_String + _T("\n  姓名: ") + m_Name_String + _T("\n  删除成功");

		InitData();

		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //关闭记录集 
		}
	}
	catch (_com_error e)
	{
		m_ShowTip = _T(" ID: ") + m_ID_String + _T("\n 姓名: ") + m_Name_String + _T("\n 删除失败，请重新删除");
		CATCH_ERROR;
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}
	}

	
	g_Action = "删除用户";  //日志
	OperRZ(g_Action);
	
	OnBnClickedBtnseleall();   //调用全选刷新
	InvalidateRect(NULL, FALSE);
	UpdateData(FALSE);
}


BOOL CPerModify::DeletePersonInfo(LONG lFaceLoginId, unsigned int nPersonID)   //删除摄像机图片
{
	if (TRUE != Net_DeletePersonInfo(lFaceLoginId, nPersonID))
	{
		return FALSE;
	}

	return TRUE;
}



BOOL CPerModify::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_ListShowInfo.GetClientRect(&rect);

	m_ListShowInfo.SetExtendedStyle(m_ListShowInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListShowInfo.InsertColumn(0, _T("身份证号"), LVCFMT_LEFT, rect.Width() / 3, 6);
	m_ListShowInfo.InsertColumn(1, _T("姓名"), LVCFMT_LEFT, rect.Width() / 8, 1);
	m_ListShowInfo.InsertColumn(2, _T("性别"), LVCFMT_LEFT, rect.Width() / 8, 2);
	m_ListShowInfo.InsertColumn(3, _T("电话"), LVCFMT_LEFT, rect.Width() / 5, 3);
	m_ListShowInfo.InsertColumn(4, _T("楼栋号"), LVCFMT_LEFT, rect.Width() / 10, 4);
	m_ListShowInfo.InsertColumn(5, _T("房间号"), LVCFMT_LEFT, rect.Width() / 10, 5);
	m_ListShowInfo.InsertColumn(6, _T("ID"), LVCFMT_LEFT, rect.Width() / 4, 0);

	m_ListShowInfo.SetBkColor((DWORD)RGB(255, 255, 255));   //ListCtrl背景色(白色)
	m_ListShowInfo.SetTextColor((DWORD)RGB(255, 0, 130));      //每一行的文字颜色(红色)

	
	CRect rect1;
	GetClientRect(&rect1);     //取客户区大小  
	old.x = rect1.right - rect1.left;
	old.y = rect1.bottom - rect1.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);

	// 异常: OCX 属性页应返回 FALSE;  
	m_person_certificate_type = _T("身份证");	

	return TRUE; // unless you set the focus to a control
}

void CPerModify::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	Ui_Show(m_strPath);	
}


void CPerModify::OnBnClickedBtnseleall()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //关闭记录集 
		}

		m_ListShowInfo.DeleteAllItems();

		m_pRecordSet->Open("SELECT * FROM [FaceContCen].[dbo].[PersonInfo]", m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		CString ID;
		CString Name;
		CString Sex;
		CString Tel;
		CString LD;
		CString FH;
		//CString Path;
		CString Type;


		for (int i = 0; !m_pRecordSet->adoEOF; i++)
		{
			ID = m_pRecordSet->GetCollect(_variant_t(_T("ID")));
			Name = m_pRecordSet->GetCollect(_variant_t(_T("Name")));
			Sex = m_pRecordSet->GetCollect(_variant_t(_T("Sex")));
			Tel = m_pRecordSet->GetCollect(_variant_t(_T("Tel")));
			LD = m_pRecordSet->GetCollect(_variant_t(_T("LD")));
			FH = m_pRecordSet->GetCollect(_variant_t(_T("FH")));
			//Path = m_pRecordSet->GetCollect(_variant_t(_T("PicturePath")));
			Type = m_pRecordSet->GetCollect(_variant_t(_T("RegType")));



			m_ListShowInfo.InsertItem(i, Type.GetString());
			m_ListShowInfo.SetItemText(i, 1, Name.GetBuffer(0));
			m_ListShowInfo.SetItemText(i, 2, Sex.GetString());
			m_ListShowInfo.SetItemText(i, 3, Tel.GetString());
			m_ListShowInfo.SetItemText(i, 4, LD.GetString());
			m_ListShowInfo.SetItemText(i, 5, FH.GetString());
			m_ListShowInfo.SetItemText(i, 6, ID.GetString());

			m_pRecordSet->MoveNext();
		}
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //关闭记录集 
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

	////////////////////////日志////////////////////////////////////////////
	g_Action = _T("查询所有用户");
	OperRZ(g_Action);
	/////////////////////////////日志///////////////////////////////////////
}


void CPerModify::OnLvnItemchangedListshowinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	m_ID_String = "";
	m_Name_String = "";
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;
	if (-1 != pNMListView->iItem)        // 如果iItem不是-1，就说明有列表项被选择   
	{
		// 获取被选择列表项第一个子项的文本   
		m_ID_String = m_ListShowInfo.GetItemText(pNMListView->iItem, 0);
		m_Name_String = m_ListShowInfo.GetItemText(pNMListView->iItem, 1);

		UpdateData(FALSE);
		OnBnClickedBtnselect();
	}
}

void CPerModify::ReSize()
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

		if (woc == IDC_COM_XB)
		{
			OldTLPoint = Rect.TopLeft();
			TLPoint.x = float(OldTLPoint.x*fsp[0]) + 0.5;
			TLPoint.y = float(OldTLPoint.y*fsp[1]) + 0.5;
			BRPoint.x = TLPoint.x + Rect.Width();
			BRPoint.y = TLPoint.y + Rect.Height();
			Rect.SetRect(TLPoint, BRPoint);
			GetDlgItem(woc)->MoveWindow(Rect, TRUE);
			hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
		}
		else
		{
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
	}
	old = Newp;
}

void CPerModify::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}


void CPerModify::OnBnClickedBtnzhperlogout()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	CString m_strIdTmp = "";
	if (m_IDs.IsEmpty())
	{
		m_ShowTip = _T("身份证为空，删除失败");
		UpdateData(FALSE);

		return;
	}
	try    //查看身份证是否在数据库中，不再说明输错或者已经签离或者未登记
	{
		CString Sql;
		Sql.Format("SELECT ID FROM [FaceContCen].[dbo].[PersonInfo] WHERE RegType = '%s'", m_ID_String);
		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);
		_variant_t FP;
		FP = m_pRecordSet->GetCollect(_variant_t(_T("ID")));
		if (FP.vt != VT_NULL)//如果不为空
		{
			m_strIdTmp = FP;
		}
		else {
			m_strIdTmp = "";
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
		AfxMessageBox(_T("身份证错误,请重新输入"));

		return;
	}

	if (DropFacePicture(m_strIdTmp, m_lLoginID) == TRUE) //删除摄像机照片
	{
		m_ShowTip = _T("删除摄像机照片成功");

		UpdateData(FALSE);
	}

	try
	{
		CString Sql = "";
		Sql.Format("UPDATE [FaceContCen].[dbo].[PersonInfo] SET LogOut = '%s' WHERE ID = '%s'", _T("该住户已注销"), m_strIdTmp);
		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		m_ShowTip = _T("住户注销成功");
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
		m_ShowTip = _T("住户注销失败");

		return;
	}

	g_Action = "住户注销";  //日志
	OperRZ(g_Action);

	UpdateData(FALSE);
}
