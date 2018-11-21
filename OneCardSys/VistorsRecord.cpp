// VistorsRecord.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "VistorsRecord.h"
#include "afxdialogex.h"


// CVistorsRecord 对话框

IMPLEMENT_DYNAMIC(CVistorsRecord, CDialogEx)

CVistorsRecord::CVistorsRecord(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLGVISTRECORD, pParent)
	, m_SelectName(_T(""))
	, m_SelectId(_T(""))
	, m_Name_String(_T(""))
	, m_Sex_String(_T(""))
	, m_ID_String(_T(""))
	, m_RG_Stri(_T(""))	
	, m_BFZ_String(_T(""))
	, m_FK_String(_T(""))
	, m_BFZ_FH_String(_T(""))
	, m_BFZ_LH_String(_T(""))
	, m_BFZ_Addr_String(_T(""))
	, m_Picture_Path(_T(""))
	, m_YL_String(_T(""))
	, m_BeginTime_String(_T(""))
	, m_EndTime_Str(_T(""))
	, m_HMD_String(_T(""))
	, m_strLH(_T(""))
	, m_strFH(_T(""))
	, m_Begin_String(COleDateTime::GetCurrentTime())
	, m_EndTime_String(COleDateTime::GetCurrentTime())
	, m_PicId_string(_T(""))
	, m_Tel_String(_T(""))
{

}

CVistorsRecord::~CVistorsRecord()
{
}

void CVistorsRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBVRFSEX, m_vrCobxSex);
	DDX_Control(pDX, IDC_LISTVRECORD, m_listRcfInfo);
	DDX_Text(pDX, IDC_EVRFNAME, m_SelectName);
	DDX_Text(pDX, IDC_EVRFID, m_SelectId);
	DDX_Text(pDX, IDC_EDIT4, m_Name_String);
	DDX_CBString(pDX, IDC_COMBVRFSEX, m_Sex_String);
	DDX_Text(pDX, IDC_EDIT5, m_ID_String);
	DDX_Text(pDX, IDC_EDIT7, m_RG_Stri);
	DDX_Text(pDX, IDC_EDIT8, m_BFZ_String);
	DDX_Text(pDX, IDC_EDIT9, m_FK_String);
	DDX_Text(pDX, IDC_EDIT10, m_Picture_Path);
	DDX_Control(pDX, IDC_SVRCDSHOW, m_Picture);
	DDX_Text(pDX, IDC_EDSHOW, m_YL_String);
	DDX_Text(pDX, IDC_EDIT_BeginTime, m_BeginTime_String);
	DDX_Text(pDX, IDC_EDIT_EndTime, m_EndTime_Str);
	DDX_Text(pDX, IDC_EDITHMD, m_HMD_String);
	DDX_Text(pDX, IDC_EDIT_LH, m_strLH);
	DDX_Text(pDX, IDC_EDIT_FH, m_strFH);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_datetimebegin);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_datetimeend);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Begin_String);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_EndTime_String);
	DDX_Text(pDX, IDC_PicID, m_PicId_string);
	DDX_Text(pDX, IDC_EDITEL, m_Tel_String);
}


BEGIN_MESSAGE_MAP(CVistorsRecord, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CVistorsRecord::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CVistorsRecord::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CVistorsRecord::OnBnClickedButton1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTVRECORD, &CVistorsRecord::OnLvnItemchangedListvrecord)
	ON_BN_CLICKED(IDC_BtnSelectAll, &CVistorsRecord::OnBnClickedBtnselectall)
	ON_BN_CLICKED(IDC_BtnSelect, &CVistorsRecord::OnBnClickedBtnselect)
	ON_EN_CHANGE(IDC_EVRFNAME, &CVistorsRecord::OnEnChangeEvrfname)
	ON_BN_CLICKED(IDC_BtnJionBT, &CVistorsRecord::OnBnClickedBtnjionbt)
	ON_EN_CHANGE(IDC_EVRFID, &CVistorsRecord::OnEnChangeEvrfid)
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_EDIT11, &CVistorsRecord::OnEnChangeEdit11)
	ON_STN_CLICKED(IDC_STATICPT, &CVistorsRecord::OnStnClickedStaticpt)
	ON_BN_CLICKED(IDC_BtnDelete, &CVistorsRecord::OnBnClickedBtndelete)
	ON_WM_PAINT()	
	ON_CBN_DROPDOWN(IDC_COMBVRFSEX, &CVistorsRecord::OnCbnDropdownCombvrfsex)
	ON_BN_CLICKED(IDC_BtnSelectAll_HMD, &CVistorsRecord::OnBnClickedBtnselectallHmd)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CVistorsRecord::OnDtnDatetimechangeDatetimepicker1)
	ON_BN_CLICKED(IDC_BtnSelectTime, &CVistorsRecord::OnBnClickedBtnselecttime)
	ON_BN_CLICKED(IDC_BtnDelete2, &CVistorsRecord::OnBnClickedBtndelete2)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////////
//static void CALLBACK disconnect_callback(LLONG lLoginID, char *lpszIP, LONG nPort, LDWORD dwUser)
//{
//	// TODO: 
//	CVistorsRecord* pDlg = (CVistorsRecord*)dwUser;
//	pDlg->m_lLoginID = 0;
//}
//
//BOOL CVistorsRecord::InitLoginParams()
//{
//	m_lLoginID = 0;
//	m_Str_Ip = "192.168.7.2";
//	m_int_port = 3000;
//	m_Str_User = "admin";
//	m_Str_Pwd = "admin123";
//
//
//	Net_Init(disconnect_callback, (LDWORD)(void*)this); //初始化sdk库
//
//	return TRUE;
//}
//
//BOOL CVistorsRecord::LogIn()
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
//BOOL CVistorsRecord::LogOut()
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

BOOL CVistorsRecord::CheckLoginOk()
{
	if (0 < m_lLoginID)
		return TRUE;
	MessageBox(_T("还未登录！"), "", MB_OK);
	return FALSE;
}
///////////////////////////////////////////////////////////////////////////////////

// CVistorsRecord 消息处理程序
BOOL CVistorsRecord::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

   // TODO: 在此添加额外的初始化代码
	m_datetimebegin.SetFormat(_T("yyyy-MM-dd    HH:mm:ss"));
	m_datetimeend.SetFormat(_T("yyyy-MM-dd    HH:mm:ss"));

	CRect rect;
	m_listRcfInfo.GetClientRect(&rect);

	m_listRcfInfo.SetExtendedStyle(m_listRcfInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listRcfInfo.InsertColumn(0, _T("姓名"), LVCFMT_LEFT, rect.Width() / 10, 0);
	m_listRcfInfo.InsertColumn(1, _T("性别"), LVCFMT_LEFT, rect.Width() / 12, 1);
	m_listRcfInfo.InsertColumn(2, _T("身份证号"), LVCFMT_LEFT, rect.Width() / 7, 2);
	m_listRcfInfo.InsertColumn(3, _T("登记时间"), LVCFMT_LEFT, rect.Width() / 7, 3);
	m_listRcfInfo.InsertColumn(4, _T("签离时间"), LVCFMT_LEFT, rect.Width() / 7, 4);
	m_listRcfInfo.InsertColumn(5, _T("被访者姓名"), LVCFMT_LEFT, rect.Width() / 8, 5);
	m_listRcfInfo.InsertColumn(6, _T("访客住址"), LVCFMT_LEFT, rect.Width() / 3, 6);
	m_listRcfInfo.InsertColumn(7, _T("被访者住址"), LVCFMT_LEFT, rect.Width() / 3, 7);
	m_listRcfInfo.InsertColumn(8, _T("是否黑名单"), LVCFMT_LEFT, rect.Width() / 7, 8);
	m_listRcfInfo.InsertColumn(9, _T("是否签离"), LVCFMT_LEFT, rect.Width() / 7, 9);


	CRect rect1;
	GetClientRect(&rect1);     //取客户区大小  
	old.x = rect1.right - rect1.left;
	old.y = rect1.bottom - rect1.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);
	m_ShowPath = "";

	/**************************人脸上传 开始************************************/
	//InitLoginParams(); //初始化各项参数

	
	/*if (!LogIn())
	{
		return FALSE;
	}*/
	/**************************人脸上传 结束**************************************/


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}



void CVistorsRecord::OnBnClickedButton3()  //加入黑名单
{
	// TODO: 在此添加控件通知处理程序代码
}


void CVistorsRecord::OnBnClickedButton2() //条件查询
{
	// TODO: 在此添加控件通知处理程序代码
}


void CVistorsRecord::OnBnClickedButton1()  //全部查询
{
	// TODO: 在此添加控件通知处理程序代码
}


void CVistorsRecord::OnLvnItemchangedListvrecord(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	UpdateData(TRUE);
	m_SelectId = "";
	m_SelectName = "";
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;
	if (-1 != pNMListView->iItem)        // 如果iItem不是-1，就说明有列表项被选择   
	{
		// 获取被选择列表项第一个子项的文本   
		m_SelectId = m_listRcfInfo.GetItemText(pNMListView->iItem, 2);
		m_SelectName = m_listRcfInfo.GetItemText(pNMListView->iItem, 0);

		UpdateData(FALSE);
		OnBnClickedBtnselect();
	}
}


void CVistorsRecord::OnBnClickedBtnselectall()
{
	// TODO: 在此添加控件通知处理程序代码
	try
	{
		m_listRcfInfo.DeleteAllItems();

		m_pRecordSet->Open("SELECT * FROM [FaceContCen].[dbo].[FK_UserTabel]", m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		CString BFZName = _T(""); 
		CString Name = _T("");
		CString Sex = _T("");
		CString BFZAddr = _T("");
		CString BeginTime = _T("");
		CString EndTime = _T("");
		CString FZAddr = _T("");
		CString QL = _T("");
		CString SFHMD = _T("");
		CString ID = _T("");

		for (int i = 0; !m_pRecordSet->adoEOF; i++)
		{			
			Name = m_pRecordSet->GetCollect(_variant_t(_T("Name")));
			Sex = m_pRecordSet->GetCollect(_variant_t(_T("Sex")));
			BFZName = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_Name")));
			FZAddr = m_pRecordSet->GetCollect(_variant_t(_T("FK_Addr")));		
			ID = m_pRecordSet->GetCollect(_variant_t(_T("IDCardNum")));//人脸id号，唯一
			m_BFZ_FH_String = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_FH")));
			m_BFZ_LH_String = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_LH")));
			BFZAddr = _T("楼号：") + m_BFZ_FH_String + _T("   房号：") + m_BFZ_LH_String;
			SFHMD = m_pRecordSet->GetCollect(_variant_t(_T("HMD")));
			BeginTime = m_pRecordSet->GetCollect(_variant_t(_T("BeginTime")));

			
			_variant_t varSFQL;			//是否签离
			varSFQL = m_pRecordSet->GetCollect(_variant_t(_T("SingnOff")));
			if (varSFQL.vt != VT_NULL)   //如果不为空
			{
				QL = varSFQL;
			}			
			_variant_t varEndTime;//签离时间			
			varEndTime = m_pRecordSet->GetCollect(_variant_t(_T("QL_Time")));
			if (varEndTime.vt != VT_NULL)//如果不为空
			{
				EndTime = varEndTime;
			}


			m_listRcfInfo.InsertItem(i, Name.GetString());
			m_listRcfInfo.SetItemText(i, 1, Sex.GetBuffer(0));
			m_listRcfInfo.SetItemText(i, 2, ID.GetString());
			m_listRcfInfo.SetItemText(i, 3, BeginTime.GetString());
			m_listRcfInfo.SetItemText(i, 4, EndTime.GetString());
			m_listRcfInfo.SetItemText(i, 5, BFZName.GetString());
			m_listRcfInfo.SetItemText(i, 6, FZAddr.GetString());
			m_listRcfInfo.SetItemText(i, 7, BFZAddr.GetString());
			m_listRcfInfo.SetItemText(i, 8, SFHMD.GetString());
			m_listRcfInfo.SetItemText(i, 9, QL.GetString());
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
			m_pRecordSet->Close(); //关闭记录集 
		}
		CATCH_ERROR;
	}
	

	////////////////////////日志////////////////////////////////////////////
	g_Action = _T("查询所有访客用户");

	CTime tmp_tm = CTime::GetCurrentTime();
	CString TimeEnd = tmp_tm.Format("%Y-%m-%d %H:%M:%S");
	try
	{
		CString Sql;
		Sql.Format(_T("INSERT INTO [FaceContCen].[dbo].[SysRunLog](IdNum,Name,QX,BeginData,EndData,Action,Ip,SysRun) Values(%d,'%s','%s','%s','%s','%s','%s','%s')"), g_UserId, g_UseName, g_QX, g_Time, TimeEnd, g_Action, g_Ip, g_SysRunRZ);
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


}


void CVistorsRecord::OnBnClickedBtnselect()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_SelectId.IsEmpty() && m_SelectId == "" && m_SelectName.IsEmpty() && m_SelectName == "")
	{
		MessageBox( _T("查询条件不能为空！"),_T("警告"),MB_OK|MB_ICONERROR);
		UpdateData(FALSE);

		return;
	}
	try
	{
		CString Sql = _T("");  //
		Sql.Format(_T("SELECT * FROM [FaceContCen].[dbo].[FK_UserTabel] WHERE IDCardNum = '%s' OR Name = '%s'"), m_SelectId.GetBuffer(0), m_SelectName.GetBuffer(0));

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		_variant_t varName;		 //姓名
		varName = m_pRecordSet->GetCollect(_variant_t(_T("Name")));
		if (VT_NULL != varName.vt){
			m_Name_String = varName;
		}else{
			m_Name_String = "";
		}

		_variant_t varId;		 //照片编号
		varId = m_pRecordSet->GetCollect(_variant_t(_T("IDNum")));
		if (VT_NULL != varId.vt){
			m_PicId_string = varId;
		}else{
			m_PicId_string = "";
		}

		_variant_t varSex;  //性别
		varSex = m_pRecordSet->GetCollect(_variant_t(_T("Sex")));
		if (VT_NULL != varSex.vt)		{
			m_Sex_String = varSex;	
		}		else		{
			m_Sex_String = "";
		}

		_variant_t varBeginTime;  //进入时间
		varBeginTime = m_pRecordSet->GetCollect(_variant_t(_T("BeginTime")));
		if (VT_NULL != varBeginTime.vt)		{
			m_BeginTime_String = varBeginTime;
		}		else		{
			m_BeginTime_String = "";
		}

		_variant_t varFKAddr;  //访客住址
		varFKAddr = m_pRecordSet->GetCollect(_variant_t(_T("FK_Addr")));
		if (VT_NULL != varFKAddr.vt)		{
			m_FK_String = varFKAddr;
		}		else		{
			m_FK_String = "";
		}

		_variant_t varFH;  //被访者的房间号
		varFH = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_FH")));
		if (VT_NULL != varFH.vt)		{
			m_strFH = varFH;
		}
		else		{
			m_strFH = "";
		}

		_variant_t varLH;   //被访者的楼层号
		varLH = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_LH")));
		if (VT_NULL != varLH.vt){
			m_strLH = varLH;
		}else{
			m_strLH = "";
		}

		_variant_t varPicturePath;   //照片的路径
		varPicturePath = m_pRecordSet->GetCollect(_variant_t(_T("PicturePath")));
		if (VT_NULL != varPicturePath.vt){
			m_Picture_Path = varPicturePath;
		}else{
			m_Picture_Path = "";
		}

		_variant_t varHMD;  //是否黑名单
		varHMD = m_pRecordSet->GetCollect(_variant_t(_T("HMD")));
		if (VT_NULL != varHMD.vt){
			m_HMD_String = varHMD;
		}else{
			m_HMD_String = "";
		}

		_variant_t FP; //唯一人脸id号
		FP = m_pRecordSet->GetCollect(_variant_t(_T("IDCardNum"))); //id
		if (VT_NULL != FP.vt){
			m_ID_String = FP;
		}else		{
			m_ID_String = "";
		} 

		_variant_t varEndTime; //签离时间
		varEndTime = m_pRecordSet->GetCollect(_variant_t(_T("QL_Time")));
		if (varEndTime.vt != VT_NULL){
			m_EndTime_Str = varEndTime;
		}else{
			m_EndTime_Str = "";
		}
		
		_variant_t varBFZName;//被访者姓名
		varBFZName = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_Name")));
		if (varBFZName.vt != VT_NULL){
			m_BFZ_String = varBFZName;
		}else{
			m_BFZ_String = "";
		}		
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
		m_strPath = _T("C:\\YTPicture\\FKPicture");//每次把选择路径给cspath，防止cstring叠加，出错
		if (!PathIsDirectory(m_strPath))
		{
			CreateDirectory(m_strPath, 0);//不存在则创建	}　
		}
		m_strPath += _T("\\") + m_PicId_string + _T(".jpg");  //照片路径

	    /************************************************************************/
	    /*  EJZToPicture()将数据库中的二进制照片数据存到本地c盘                 */
	    /************************************************************************/
		if (EJZToPicture(m_strPath, m_PicLen, varPicDate) != TRUE)
		{
			m_YL_String = _T("人脸照片加载失败！");
		}

		Sql.ReleaseBuffer();
	}
	catch (_com_error e)
	{

		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //关闭记录集 
		}
		CATCH_ERROR;
	}
	Ui_Show();

	UpdateData(FALSE);
}


void CVistorsRecord::OnEnChangeEvrfname()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CVistorsRecord::OnBnClickedBtnjionbt()  //直接删除摄像机人脸并更改sql字段为黑名单
{
	// TODO: 在此添加控件通知处理程序代码
	if (TRUE != CheckLoginOk())
		return;

	/*if (UpFacePicture(m_PicId_string, m_lLoginID, m_Picture_Path) != TRUE){
		return;
	}*/

	if (DropFacePicture(m_PicId_string, m_lLoginID) == TRUE) 
	{
		m_YL_String = _T("照片加入黑名单成功！");
	}

	try
	{		
		CString Sql;
		Sql.Format(_T("UPDATE [FaceContCen].[dbo].[FK_UserTabel] SET HMD = '%s' WHERE IDCardNum = '%s'"),_T("是"), m_ID_String);

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}

		m_YL_String = m_ID_String + _T("\n  姓名: ") + m_Name_String + _T("\n  加入黑名单成功");
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}
		m_YL_String = _T("加入黑名单失败,再试一次");
		CATCH_ERROR;	
	}

	UpdateData(FALSE);
}


void CVistorsRecord::OnEnChangeEvrfid()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CVistorsRecord::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}

	
}


void CVistorsRecord::ReSize()
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
		
		if (woc == IDC_COMBVRFSEX)
		{
			OldTLPoint = Rect.TopLeft();
			TLPoint.x = float(OldTLPoint.x*fsp[0]) + 0.5;
			TLPoint.y = float(OldTLPoint.y*fsp[1]) + 0.5;
			BRPoint.x = TLPoint.x + Rect.Width();
			BRPoint.y = TLPoint.y + Rect.Height();
			Rect.SetRect(TLPoint, BRPoint);
			GetDlgItem(woc)->MoveWindow(Rect, TRUE);
			//hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
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
			//hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
		}
		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}
	old = Newp;
}


void CVistorsRecord::OnEnChangeEdit11()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CVistorsRecord::OnStnClickedStaticpt()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CVistorsRecord::Ui_Show()
{

	CString g_strPictureShow;
	g_strPictureShow = m_strPath;

	CString strExt(".jpg");
	if (g_strPictureShow.IsEmpty() || -1 == g_strPictureShow.Find(strExt.GetBuffer(0)))
	{
		return;
	}

	CImage image;
	if (image.Load(g_strPictureShow))
	{
		return;
	}	

	CRect rectControl;                        //控件矩形对象
	CRect rectPicture;                        //图片矩形对象

	int x = image.GetWidth();
	int y = image.GetHeight();
	(&m_Picture)->GetClientRect(rectControl);

	CDC *pDc = (&m_Picture)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(),
		CSize((int)rectControl.Width(),
		(int)rectControl.Height()));

	(&m_Picture)->SetBitmap(NULL);

	//以下两种方法都可绘制图片
	image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); //将图片绘制到Picture控件表示的矩形区域

	image.Destroy();
	(&m_Picture)->ReleaseDC(pDc);
	UpdateData(FALSE);
}


void CVistorsRecord::OnBnClickedBtndelete()
{
	// TODO: 在此添加控件通知处理程序代码
	/************************签离删除人脸***开始*********************************************/
	if (TRUE != CheckLoginOk())
		return;

	/*if (DropFacePicture(m_PicId_string, m_lLoginID) != TRUE){
		return;
	}*/

	try
	{
		CString Sql;
		Sql.Format(_T("UPDATE [FaceContCen].[dbo].[FK_UserTabel] SET  HMD = '%s'  WHERE IDCardNum = '%s'"), "否",m_ID_String.GetBuffer(0));

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		m_YL_String = _T(" ID: ") + m_ID_String + _T(" 姓名: ") + m_Name_String + _T(" 删除黑名单成功");

	}
	catch (_com_error e)
	{
		AfxMessageBox(_T(" ID: ") + m_ID_String + _T("\n 姓名: ") + m_Name_String + _T("\n 删除黑名单失败，请重试一次"));

		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}
	}
	if (m_pRecordSet->State)
	{
		m_pRecordSet->Close();
	}

	UpdateData(FALSE);
}



void CVistorsRecord::OnPaint()
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
	//Image image(L"./res/BG_BKALL.jpg", TRUE);
	//graphics.DrawImage(&image, 0, 0, rect.right, rect.bottom);  //绘制背景
}



void CVistorsRecord::OnCbnDropdownCombvrfsex()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CVistorsRecord::OnBnClickedBtnselectallHmd()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	try
	{
		m_listRcfInfo.DeleteAllItems();

		m_pRecordSet->Open("SELECT * FROM [FaceContCen].[dbo].[FK_UserTabel] WHERE HMD = '是'", m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		CString BFZName = _T("");
		CString Name = _T("");
		CString Sex = _T("");
		CString BFZAddr = _T("");
		CString BeginTime = _T("");
		CString EndTime = _T("");
		CString FZAddr = _T("");
		CString QL = _T("");
		CString SFHMD = _T("");
		CString ID = _T("");

		for (int i = 0; !m_pRecordSet->adoEOF; i++)
		{
			Name = m_pRecordSet->GetCollect(_variant_t(_T("Name")));
			Sex = m_pRecordSet->GetCollect(_variant_t(_T("Sex")));
			BFZName = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_Name")));
			FZAddr = m_pRecordSet->GetCollect(_variant_t(_T("FK_Addr")));
			ID = m_pRecordSet->GetCollect(_variant_t(_T("IDCardNum")));//人脸id号，唯一
			m_BFZ_FH_String = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_FH")));
			m_BFZ_LH_String = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_LH")));
			BFZAddr = _T("楼号：") + m_BFZ_FH_String + _T("   房号：") + m_BFZ_LH_String;
			SFHMD = m_pRecordSet->GetCollect(_variant_t(_T("HMD")));
			BeginTime = m_pRecordSet->GetCollect(_variant_t(_T("BeginTime")));


			_variant_t varSFQL;			//是否签离
			varSFQL = m_pRecordSet->GetCollect(_variant_t(_T("SingnOff")));
			if (varSFQL.vt != VT_NULL)   //如果不为空
			{
				QL = varSFQL;
			}
			_variant_t varEndTime;//签离时间			
			varEndTime = m_pRecordSet->GetCollect(_variant_t(_T("QL_Time")));
			if (varEndTime.vt != VT_NULL)//如果不为空
			{
				EndTime = varEndTime;
			}


			m_listRcfInfo.InsertItem(i, Name.GetString()); //设置list数据
			m_listRcfInfo.SetItemText(i, 1, Sex.GetBuffer(0));
			m_listRcfInfo.SetItemText(i, 2, ID.GetString());
			m_listRcfInfo.SetItemText(i, 3, BeginTime.GetString());
			m_listRcfInfo.SetItemText(i, 4, EndTime.GetString());
			m_listRcfInfo.SetItemText(i, 5, BFZName.GetString());
			m_listRcfInfo.SetItemText(i, 6, FZAddr.GetString());
			m_listRcfInfo.SetItemText(i, 7, BFZAddr.GetString());
			m_listRcfInfo.SetItemText(i, 8, SFHMD.GetString());
			m_listRcfInfo.SetItemText(i, 9, QL.GetString());
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
			m_pRecordSet->Close(); //关闭记录集 
		}
		CATCH_ERROR;
	}

	UpdateData(FALSE);
}


void CVistorsRecord::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


void CVistorsRecord::OnBnClickedBtnselecttime()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_listRcfInfo.DeleteAllItems();
	try
	{
		CString Sql;

		Sql.Format("SELECT * FROM [FaceContCen].[dbo].[FK_UserTabel] WHERE AutoTime BETWEEN '%d-%d-%d %d:%d:%d' and '%d-%d-%d %d:%d:%d'", m_Begin_String.GetYear(), m_Begin_String.GetMonth(), m_Begin_String.GetDay(), m_Begin_String.GetHour(), m_Begin_String.GetMinute(), m_Begin_String.GetSecond(), m_EndTime_String.GetYear(), m_EndTime_String.GetMonth(), m_EndTime_String.GetDay(), m_EndTime_String.GetHour(), m_EndTime_String.GetMinute(), m_EndTime_String.GetSecond());

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);
		CString BFZName = _T("");
		CString Name = _T("");
		CString Sex = _T("");
		CString BFZAddr = _T("");
		CString BeginTime = _T("");
		CString EndTime = _T("");
		CString FZAddr = _T("");
		CString QL = _T("");
		CString SFHMD = _T("");
		CString ID = _T("");

		for (int i = 0; !m_pRecordSet->adoEOF; i++)
		{
			Name = m_pRecordSet->GetCollect(_variant_t(_T("Name")));
			Sex = m_pRecordSet->GetCollect(_variant_t(_T("Sex")));
			BFZName = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_Name")));
			FZAddr = m_pRecordSet->GetCollect(_variant_t(_T("FK_Addr")));
			ID = m_pRecordSet->GetCollect(_variant_t(_T("IDCardNum")));//人脸id号，唯一
			m_BFZ_FH_String = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_FH")));
			m_BFZ_LH_String = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_LH")));
			BFZAddr = _T("楼号：") + m_BFZ_FH_String + _T("   房号：") + m_BFZ_LH_String;
			SFHMD = m_pRecordSet->GetCollect(_variant_t(_T("HMD")));
			BeginTime = m_pRecordSet->GetCollect(_variant_t(_T("BeginTime")));


			_variant_t varSFQL;			//是否签离
			varSFQL = m_pRecordSet->GetCollect(_variant_t(_T("SingnOff")));
			if (varSFQL.vt != VT_NULL)   //如果不为空
			{
				QL = varSFQL;
			}
			_variant_t varEndTime;//签离时间			
			varEndTime = m_pRecordSet->GetCollect(_variant_t(_T("QL_Time")));
			if (varEndTime.vt != VT_NULL)//如果不为空
			{
				EndTime = varEndTime;
			}


			m_listRcfInfo.InsertItem(i, Name.GetString()); //设置list数据
			m_listRcfInfo.SetItemText(i, 1, Sex.GetBuffer(0));
			m_listRcfInfo.SetItemText(i, 2, ID.GetString());
			m_listRcfInfo.SetItemText(i, 3, BeginTime.GetString());
			m_listRcfInfo.SetItemText(i, 4, EndTime.GetString());
			m_listRcfInfo.SetItemText(i, 5, BFZName.GetString());
			m_listRcfInfo.SetItemText(i, 6, FZAddr.GetString());
			m_listRcfInfo.SetItemText(i, 7, BFZAddr.GetString());
			m_listRcfInfo.SetItemText(i, 8, SFHMD.GetString());
			m_listRcfInfo.SetItemText(i, 9, QL.GetString());
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
			m_pRecordSet->Close(); //关闭记录集 
		}
		CATCH_ERROR;
	}

	UpdateData(FALSE);
}


void CVistorsRecord::OnBnClickedBtndelete2() //先人脸库的人脸，在删除信息
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (m_PicId_string.IsEmpty())
	{
		m_YL_String = _T("照片id为空，删除失败");
		UpdateData(FALSE);

		return;
	}

	if (DropFacePicture(m_PicId_string, m_lLoginID) == TRUE)
	{
		//m_YL_String = _T("照片加入黑名单成功！");
	}

	try    //删除数据库户主数据
	{
		CString Sql;
		Sql.Format("DELETE  FROM [FaceContCen].[dbo].[FK_UserTabel] WHERE IDNum = '%s'", m_PicId_string);

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //关闭记录集 
		}

		Sql.ReleaseBuffer();
		m_YL_String = _T(" ID: ") + m_PicId_string + _T("\n  姓名: ") + m_Name_String + _T("\n  删除成功");
	
	}
	catch (_com_error e)
	{
		m_YL_String = _T(" ID: ") + m_PicId_string + _T("\n 姓名: ") + m_Name_String + _T("\n 删除失败，请重新删除");

		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}
	}

	InvalidateRect(NULL, FALSE);

	UpdateData(FALSE);
}
