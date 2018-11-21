// PerReg.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "PerReg.h"
#include "afxdialogex.h"

BOOL bFlageReg = TRUE;       //设置一个标志，防止死循环
CString  g_FilePathReg = ""; //全局文件名
INT g_DynamicUp = 0;          //动态上传全局标志
CPerReg *g_cPerReg = NULL;
int g_B = 0;
// CPerReg 对话框

IMPLEMENT_DYNAMIC(CPerReg, CDialogEx)

CPerReg::CPerReg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIAREGISTER, pParent)
	, m_ID_String(_T(""))
	, m_Name_String(_T(""))
	, m_Tel_String(_T(""))
	, m_LD_String(_T(""))
	, m_FH_String(_T(""))
	, m_Path_String(_T(""))
	, m_COM_XB_String(_T(""))
	, m_RegTip(_T(""))
	, m_IdCard_String(_T(""))
{
	g_cPerReg = this;
}

CPerReg::~CPerReg()
{
}

void CPerReg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ID, m_ID_String);
	DDX_Text(pDX, IDC_EDIT_Name, m_Name_String);
	DDX_Text(pDX, IDC_EDIT_Tel, m_Tel_String);
	DDX_Text(pDX, IDC_EDIT_LD, m_LD_String);
	DDX_Text(pDX, IDC_EDIT_FH, m_FH_String);
	DDX_Text(pDX, IDC_EDIT_ShowPath, m_Path_String);
	DDX_Control(pDX, IDC_Picture_Show, m_Picture);
	DDX_CBString(pDX, IDC_COM_XB, m_COM_XB_String);
	DDX_Text(pDX, IDC_EDIT_ShowTip, m_RegTip);
	DDX_Text(pDX, IDC_EDIT_IdCard, m_IdCard_String);
	DDX_Control(pDX, IDC_EDIT_ShowTip, m_StatVal);
	DDX_Control(pDX, IDC_COM_XB, m_ComBoxSex);
	DDX_Control(pDX, IDC_EDIT_IdCard, m_EditIDNo);
	DDX_Control(pDX, IDC_EDIT_ID, m_Edit_ID_Values);
	DDX_Control(pDX, IDC_EDIT_ShowPath, m_vEdit7);
	DDX_Control(pDX, IDC_EDIT_Name, m_EditName);
}


BEGIN_MESSAGE_MAP(CPerReg, CDialogEx)
	ON_BN_CLICKED(IDC_Btn_Open, &CPerReg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_Btn_Reg, &CPerReg::OnBnClickedBtnReg)
	ON_BN_CLICKED(IDC_Btn_Cannel, &CPerReg::OnBnClickedBtnCannel)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_Btn_STReg, &CPerReg::OnBnClickedBtnStreg)
	ON_BN_CLICKED(IDC_BtnTwoCard, &CPerReg::OnBnClickedBtntwocard)
END_MESSAGE_MAP()


void CPerReg::ClearScreen()
{
	m_ID_String = (_T(""));
	m_Name_String = (_T(""));
	m_Tel_String = (_T(""));
	m_LD_String = (_T("00"));
	m_FH_String = (_T("11"));
	m_Path_String = (_T(""));
	m_COM_XB_String = _T("男");
	g_FilePathReg = "";
	m_IdCard_String = (_T(""));

	/*CStatic* pStatic = (CStatic*)GetDlgItem(IDC_Picture_Show);
	CRect lRect;
	pStatic->GetClientRect(&lRect);
	pStatic->GetDC()->FillSolidRect(lRect.left, lRect.top, lRect.Width(), lRect.Height(), RGB(240, 240, 240));

	InvalidateRect(nullptr, FALSE);*/
}

// CPerReg 消息处理程序

BOOL CPerReg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_COM_XB_String = _T("男");
	m_LD_String = "00";
	m_FH_String = "11";
	m_playHandle = 0;  //截图句柄

	CRect rect1;
	GetClientRect(&rect1);     //取客户区大小  
	old.x = rect1.right - rect1.left;
	old.y = rect1.bottom - rect1.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

BOOL CPerReg::CheckLoginOk()
{
	if (0 < m_lLoginID)
		return TRUE;
	MessageBox(_T("还未登录！"), "", MB_OK);
	return FALSE;
}

int CALLBACK realload_callbackReg(LLONG lAnalyzerHandle,
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

		// pBuffer 是图片数据，dwBufSize 是图片数据大小		 	
		CString csPath = _T("C:\\YTPicture");
		if (!PathIsDirectory(csPath))
		{
			CreateDirectory(csPath, 0);//不存在则创建
		}
		csPath = _T("C:\\YTPicture\\ZHPictureReg");//每次把选择路径给cspath，防止cstring叠加，出错

		if (!PathIsDirectory(csPath))
		{
			CreateDirectory(csPath, 0);//不存在则创建	}　
		}
		CString strTimeFile;
		CTime tm;          //获取系统时间
		tm = CTime::GetCurrentTime();
		strTimeFile = tm.Format("FZ%y%m%d%H%M%S");

		csPath += _T("\\") + strTimeFile + _T("E") + _T(".jpg");

		FILE *pFilePath = fopen(csPath, _T("w+b")); //效率低
		if (NULL != pFilePath)
		{
			fwrite(pBuffer, 1, dwBufSize, pFilePath);	//写入文件		
			fclose(pFilePath);

			g_FilePathReg = csPath;
		}
		else
		{
			g_FilePathReg = "";
			//MessageBox(NULL, _T("抓取失败，重试一次！"), NULL, MB_ICONERROR);
		}	
	}
	
	return 0;
}


BOOL CPerReg::StartRealStream()
{
	// 图片数据处理在 realload_callback 回调中
	if (m_ZPLoginID <= 0)
	{
		MessageBox("未登录", "提示", MB_ICONERROR);

		return FALSE;
	}

	int nChannel = 0;
	m_playHandle = Net_RealLoadPicture(m_ZPLoginID, nChannel, EVENT_SP_FACE_SNAP_PART, 1,
		realload_callbackReg, NULL, NULL);
	if (0 >= m_playHandle)
	{
		MessageBox(_T("网络库错误，请重启截取人脸功能.\n"), NULL, MB_ICONERROR);

		Net_LogoutDevice(m_ZPLoginID);

		return FALSE;
	}

	return TRUE;
}


void CPerReg::OnBnClickedBtnOpen()
{
	// TODO: 在此添加控件通知处理程序代码

	if (!StartRealStream())
	{
		m_RegTip = _T("收集人脸失败。");

		return;
	}
	else
	{
		m_RegTip = _T("正在采集人脸...");

		UiTimer = SetTimer(1, 100, NULL);  //开启计时器，实时刷新界面

		CWnd *pBtn1 = GetDlgItem(IDC_Btn_Open);
		pBtn1->EnableWindow(FALSE);
		CWnd *STReg = GetDlgItem(IDC_Btn_STReg);
		STReg->EnableWindow(FALSE);
		
		//g_DynamicUp = 1;   //动态采集置为1
	}
	
	UpdateData(FALSE);
}

void CPerReg::Ui_Show(CString strPicture_Path, int myIDC_Picture)
{
	WCHAR buf[1024];
	CRect rect;
	USES_CONVERSION;
	wcscpy(buf, A2W((LPCSTR)strPicture_Path));  //CString -> wchar_t

	Image image(buf, TRUE);
	CWnd *pWnd = GetDlgItem(myIDC_Picture);
	Graphics graphics(pWnd->GetDC()->m_hDC);
	GetDlgItem(myIDC_Picture)->GetClientRect(&rect);
	graphics.DrawImage(&image, 0, 0, rect.Width(), rect.Height());
}


void CPerReg::OnBnClickedBtnReg()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (TRUE != CheckLoginOk())    //检查是否登陆摄像机
		return;
	
	if (m_IdCard_String == "" || m_IdCard_String.IsEmpty())
	{
		m_RegTip = _T("请输入身份证。");

		UpdateData(FALSE);
		return ;
	}
	
	int nLen = m_IdCard_String.GetLength();
	for (int i = 0; i < nLen; i++)
	{
		if (!(m_IdCard_String.GetAt(i) >= '0' && m_IdCard_String.GetAt(i) <= '9' || m_IdCard_String.GetAt(i) >= 'A' && m_IdCard_String.GetAt(i) <= 'Z'))
		{
			MessageBox(_T("身份证格式错误"), _T("请重新输入"), 0);
			return;
		}
	}
	if (m_Name_String == "" || m_Name_String.IsEmpty())
	{
		m_RegTip = _T("姓名为空。");

		UpdateData(FALSE);
		return ;
	}
	if (m_COM_XB_String == "" || m_COM_XB_String.IsEmpty())
	{
		m_RegTip = _T("请输入性别。");

		UpdateData(FALSE);
		return ;
	}

	/************************************************************************/
	/*                            人证核验                                   */
	/************************************************************************/
	/*g_strPictureId = m_ID_String;
	g_strFacePath = m_csFileName;

	CWintCheckVido m_cWintCheck;
	m_cWintCheck.DoModal();

	if (g_ReconPass != 1)
	{
		m_RegTip = _T("人证核验不通过，请重试!");
		UpdateData(FALSE);

		return;
	}
	else
	{
		m_RegTip = g_strPictureId +  _T("人证核验通过");
	}*/

	/************************************************************************/
	/*                            把人脸图片转换成二进制                    */
	/************************************************************************/
	varBLOB = PictureToEJZ(m_csFileName); 
	if (0 == varBLOB.iVal && g_PictureLen > 0)
	{
		m_RegTip = _T("人脸图片转换成二进制失败，请重试");
		return;
	}
	m_nFileLen = g_PictureLen; //获取照片的二进制数据大小


	/************************************************************************/
	/*                           人脸上传摄像机                             */
	/************************************************************************/
	//if (g_DynamicUp != 1)  //等于1，动态上传
	//{
	//
	//}
	if (!UpFacePicture(m_ID_String, m_lLoginID, m_csFileName))   
	{
		return;
	}

	/************************************************************************/
	/*                       sql操作                                        */
	/************************************************************************/
	try   
	{
		CTime tm1 = CTime::GetCurrentTime();
		CString RegTime = tm1.Format("%Y-%m-%d %H:%M:%S");

		CString strSql = _T("");
		strSql.Format(_T("Select * from [FaceContCen].[dbo].[PersonInfo]"));
		m_pRecordSet->Open(_bstr_t(strSql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		m_pRecordSet->AddNew();
		m_pRecordSet->PutCollect("ID", m_ID_String.GetBuffer(0));
		m_pRecordSet->PutCollect("Name", m_Name_String.GetBuffer(0));
		m_pRecordSet->PutCollect("Sex", m_COM_XB_String.GetBuffer(0));
		m_pRecordSet->PutCollect("Tel", m_Tel_String.GetBuffer(0));
		m_pRecordSet->PutCollect("LD", m_LD_String.GetBuffer(0));
		m_pRecordSet->PutCollect("FH", m_FH_String.GetBuffer(0));
		m_pRecordSet->PutCollect("RegDateTime", RegTime.GetBuffer(0));
		m_pRecordSet->PutCollect("RegType", m_IdCard_String.GetBuffer(0));
		m_pRecordSet->PutCollect("LogOut",_T("住户正常"));
		if (m_nFileLen > 0)   //把图片存到sql
		{
			m_pRecordSet->PutCollect("PictureLength", m_nFileLen);
			m_pRecordSet->GetFields()->GetItem("PictureDate")->AppendChunk(varBLOB);
		}

		m_pRecordSet->Update();  //记录更新到sql
		m_pRecordSet->Close();

		m_RegTip = _T(" ID: ") + m_ID_String + _T("\n ;  姓名: ") + m_Name_String + _T("\n ;  注册成功");

		ClearScreen();  //清屏
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->CancelUpdate();  //关闭updae异常
			m_pRecordSet->Close();     //关闭记录集
		}
		m_RegTip = _T(" ID: ") + m_ID_String + _T("\n 姓名: ") + m_Name_String + _T("\n 注册失败，请重新注册");
		CATCH_ERROR;
	}
	
	/************************************************************************/
	/* 日志                                                                  */
	/************************************************************************/
	g_Action = "注册用户";    //日志
	OperRZ(g_Action);

	/************************************************************************/
	/* 按钮可用                                                                     */
	/************************************************************************/
	CWnd *STReg = GetDlgItem(IDC_Btn_STReg);  //静态采集可用
	STReg->EnableWindow(TRUE);
	CWnd *pBtn1 = GetDlgItem(IDC_Btn_Open);
	pBtn1->EnableWindow(TRUE);

	UpdateData(FALSE);	
}


void CPerReg::OperRZ(CString g_Action)
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

void CPerReg::OnBnClickedBtnCannel()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pRecordSet->State)
	{
		m_pRecordSet->Close(); //关闭记录集 
	}

	CDialog::OnCancel();
}




void CPerReg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}

void CPerReg::ReSize()
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



void CPerReg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
	case 1:
	{
		ExecuPicture();//刷新界面人脸图片++	
	}
	break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


BOOL  CPerReg::ExecuPicture()
{
	CString strExt(".jpg");
	if (g_FilePathReg.IsEmpty() || -1 == g_FilePathReg.Find(strExt.GetBuffer(0)))
		return FALSE;
	
	WCHAR buf[1024];
	CRect rect;
	USES_CONVERSION;
	wcscpy(buf, A2W((LPCSTR)g_FilePathReg));  //CString -> wchar_t

	Image image(buf, TRUE);
	CWnd *pWnd = GetDlgItem(IDC_Picture_Show);
	Graphics graphics(pWnd->GetDC()->m_hDC);
	GetDlgItem(IDC_Picture_Show)->GetClientRect(&rect);
	graphics.DrawImage(&image, 0, 0, rect.Width(), rect.Height());

	if (!g_FilePathReg.IsEmpty() && bFlageReg)
	{
		bFlageReg = FALSE;
		if (IDYES == MessageBox(_T("确实使用此人脸？"), _T("确认"), MB_YESNO | MB_ICONQUESTION))
		{
			if (0 >= m_playHandle)
			{
				MessageBox(_T("未登录！"), _T("Tip"), MB_ICONERROR);

				return FALSE;
			}
			bFlageReg = TRUE;

			m_Path_String = g_FilePathReg;  //界面edit路径
			Net_StopLoadPicture(m_playHandle); //停止网络数据拉流
			m_csFileName = g_FilePathReg;
			KillTimer(1);  //结束计时器

			
			m_RegTip = _T("照片采集成功，请输入基本信息后点击下方注册按钮注册");

			int iEndPos = 0;
			ID = m_csFileName.Mid(m_csFileName.ReverseFind('\\') + 1);
			iEndPos = ID.ReverseFind('.');
			ID = ID.Left(iEndPos);
			m_ID_String = ID;


			CWnd *pBtn1 = GetDlgItem(IDC_Btn_Open);  //动态采集可用
			pBtn1->EnableWindow(TRUE);



			UpdateData(FALSE);

			return TRUE;
		}
		else
		{
			g_FilePathReg = "";
			bFlageReg = TRUE;

			CStatic* pStatic = (CStatic*)GetDlgItem(IDC_Picture_Show);
			CRect lRect;
			pStatic->GetClientRect(&lRect);
			pStatic->GetDC()->FillSolidRect(lRect.left, lRect.top, lRect.Width(), lRect.Height(), RGB(240, 240, 240));

			/*CWnd *pBtn1 = GetDlgItem(IDC_Btn_Open);
			pBtn1->EnableWindow(TRUE);*/

			m_RegTip = _T("请重新选取人脸图片");
		}
	}

	UpdateData(FALSE);
	return FALSE;
}


void CPerReg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	CDC *pDC;
	pDC = GetDC();
	CRect  rect;
	GetClientRect(&rect);   //获取客户区大小
	Graphics graphics(pDC->m_hDC);
	//Graphics graphics(dc.m_hDC);
	Image image(L"./res/BG_BKALL.jpg", TRUE);
	graphics.DrawImage(&image, 0, 0, rect.right, rect.bottom);  //绘制背景
}


void CPerReg::OnBnClickedBtnStreg()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog dlg(TRUE);           ///TRUE为OPEN对话框，FALSE为SAVE AS对话框  
	if (dlg.DoModal() == IDOK)
		m_csFileName = dlg.GetPathName();
	else
		m_csFileName.Empty();

	CString strExt(_T(".jpg"));
	if (m_csFileName.IsEmpty() || -1 == m_csFileName.Find(strExt.GetBuffer(0)))
	{
		AfxMessageBox(_T("不是jpg类型图片"));
		return;
	}
	int iEndPos = 0;
	ID = m_csFileName.Mid(m_csFileName.ReverseFind('\\') + 1);
	iEndPos = ID.ReverseFind('.');
	CString strFileName = ID.Left(iEndPos);
	int nLen = strFileName.GetLength();
	if (15 == nLen && 'F' == strFileName[0] && 'Z' == strFileName[1] && 'E' == strFileName[14] || 'P' == strFileName[1])
	{
		ID = strFileName;
		goto Label;
	}

	if (12 <= nLen)
	{
		MessageBox("文件名长度必须小于等于12位数", _T("提示"), MB_ICONERROR);
		return;
	}
	if ('F' == strFileName[0] && 'Z' == strFileName[1] || 'P' == strFileName[1])
	{
		ID = strFileName + _T("E");
	}
	else
	{

		for (int i = 0; i < 12 - nLen; i++)
		{		
			strFileName += _T("E");
		}

		ID = _T("FP") + strFileName + _T("E");       //自动加上协议头fz，不管有么有协议头
	}
Label:
	m_ID_String += ID;
	m_Path_String = m_csFileName;  //把图片本地路径给界面的edit
	Ui_Show(m_Path_String, IDC_Picture_Show);

	CWnd *pBtn1 = GetDlgItem(IDC_Btn_Open);
	pBtn1->EnableWindow(FALSE);

	CWnd *STReg = GetDlgItem(IDC_Btn_STReg);
	STReg->EnableWindow(FALSE);

	g_DynamicUp = 0;
	UpdateData(FALSE);
}

//CWintCheckVido tmpWC;
//
//BOOL CPerReg::PerCardCheck()        //人证核验
//{
//	// 1. 上传比对人脸库
//	if (!UpFacePicture(m_ID_String, m_ZPLoginID, m_csFileName))
//	{
//		return FALSE;
//	}
//
//
//	// 2. 开启视频检测
//	tmpWC.Create(IDD_DIAWITCHECKVIDO, this);
//	tmpWC.ShowWindow(SW_SHOW);
//
//
//	// 3. 获取对比结果
//	if (WintnesCheck())
//	{
//		CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE(GetRresult)), (LPVOID)NULL, 0, NULL));	
//	}	
//
//	return TRUE;
//}
//
//DWORD CPerReg::GetRresult()
//{
//
//	while (TRUE)
//	{
//		if (g_cPerReg->m_ID_String == g_ReconBackId)  //id相等且分数大于70分
//		{
//			// 4. 关闭视频，删除人脸库人脸，获取结果
//			::MessageBox(g_cPerReg->m_hWnd, g_ReconBackId, NULL, 0);
//			DropFacePicture(g_cPerReg->m_ID_String, m_ZPLoginID);
//			tmpWC.OnShutVidoStream();
//			WintCheckStop();
//			g_B = 2;
//
//			return 1;
//		}
//	}
//
//	return 0;
//}

BOOL g_bFlag = false;  //身份证阅读器初始化

void CPerReg::IDCardInit()
{
	CString sMsg, sMsg2;
	unsigned int uiCurrBaud;
	int nRet, nRet2;
	m_iPort = 0;
	nRet = Syn_FindUSBReader();
	if (nRet == 0)
	{
		sMsg = "没有找到读卡器";
		g_bFlag = false;
	}
	else
	{
		m_iPort = nRet;
		Beep(4000, 200);
		if (nRet > 1000)
		{
			sMsg.Format("读卡器连接在USB端口 %d", nRet);
		}
		else
		{
			Sleep(200);
			nRet2 = Syn_GetCOMBaud(nRet, &uiCurrBaud);
			sMsg2.Format("%u", uiCurrBaud);
			sMsg.Format("读卡器连接在串口 %d,当前SAM波特率为 %u", nRet, uiCurrBaud);
		}
		g_bFlag = true;
	}
	m_StatVal.SetWindowText(sMsg);
}

void CPerReg::OnBnClickedBtntwocard()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	IDCardInit(); //身份证阅读器初始化
	
	int nRet;
	CString sMsg;
	CString sText;
	unsigned char pucIIN[4];
	unsigned char pucSN[8];
	IDCardData idcardData;
	int iPhototype;
	WCHAR buf[1024];
	char szTemp[10] = "";
	char szTempPath[200] = "";
	char szNewPath[200] = "";
	char *path = NULL;
	CString strPath = NULL;

	if (g_bFlag == false)
	{
		m_StatVal.SetWindowText(_T("请初始化后确认读卡器正常连接"));
		return;
	}

	CString csPath = _T("C:\\YTPicture");
	if (!PathIsDirectory(csPath))
	{
		CreateDirectory(csPath, 0);//不存在则创建
	}
	csPath = _T("C:\\YTPicture\\ZHPicture");//每次把选择路径给cspath，防止cstring叠加，出错
	if (!PathIsDirectory(csPath))
	{
		CreateDirectory(csPath, 0);//不存在则创建	
	}

	char   szBuffer[_MAX_PATH] = "C:\\YTPicture\\ZHPicture";
	Syn_SetPhotoPath(2, szBuffer);	//设置照片路径	iOption 路径选项	0=C:	1=当前路径	2=指定路径
									//cPhotoPath	绝对路径,仅在iOption=2时有效
	iPhototype = 1;
	Syn_SetPhotoType(1); //0 = bmp ,1 = Jpg , 2 = base64 , 3 = WLT ,4 = 不生成
	Syn_SetPhotoName(2); // 生成照片文件名 0=tmp 1=姓名 2=身份证号 3=姓名_身份证号 

	Syn_SetSexType(1);	// 0=卡中存储的数据	1=解释之后的数据,男、女、未知
	Syn_SetNationType(1);// 0=卡中存储的数据	1=解释之后的数据 2=解释之后加"族"
	Syn_SetBornType(3);			// 0=YYYYMMDD,1=YYYY年MM月DD日,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD
	Syn_SetUserLifeBType(1);	// 0=YYYYMMDD,1=YYYY年MM月DD日,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD
	Syn_SetUserLifeEType(1, 1);	// 0=YYYYMMDD(不转换),1=YYYY年MM月DD日,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD,
								// 0=长期 不转换,	1=长期转换为 有效期开始+50年
	nRet = Syn_OpenPort(m_iPort);
	if (nRet == 0)
	{
		if (Syn_SetMaxRFByte(m_iPort, 80, 0) == 0)
		{
			nRet = Syn_StartFindIDCard(m_iPort, pucIIN, 0);
			nRet = Syn_SelectIDCard(m_iPort, pucSN, 0);
			nRet = Syn_ReadMsg(m_iPort, 0, &idcardData);
			if (nRet == 0 || nRet == 1)
			{
				sMsg = _T("读取身份证信息成功!");
				m_StatVal.SetWindowText(sMsg);
				sMsg.Format(_T("%s"), idcardData.Name); //name
				m_EditName.SetWindowText(sMsg);
				sMsg.Format(_T("%s"), idcardData.Sex); //sex
				sprintf(szTemp, _T("%s"), idcardData.Sex);
				if (0 == strcmp(szTemp, _T("男")))
				{
					m_ComBoxSex.SetCurSel(0);
				}
				else if (0 == strcmp(szTemp, _T("女")))
				{
					m_ComBoxSex.SetCurSel(1);
				}

				//sMsg.Format("%s", idcardData.Address);
				//m_vEdit4.SetWindowText(sMsg);
				sMsg.Format("%s", idcardData.IDCardNo);
				m_EditIDNo.SetWindowText(sMsg);
		
				if (nRet == 1)
				{
					sMsg = _T("解码照片失败");
				}
				else
				{
					CString strTimeFile;    //照片的文件命名用的时间命名
					CTime tm;          //获取系统时间
					tm = CTime::GetCurrentTime();
					strTimeFile = tm.Format("%y%m%d%H%M%S");

					sMsg.Format(_T("%s"), idcardData.PhotoFileName);
					sprintf(szTempPath, _T("%s"), idcardData.PhotoFileName);  //old name XXX.Jpg
					sMsg = sMsg.Left(sMsg.Find('.'));
					CString strTemp = _T("C:\\YTPicture\\ZHPicture\\FZ");

					sMsg = sMsg.Right(sMsg.GetLength() - 1 - sMsg.ReverseFind('\\')); //身份证号
					sMsg = strTimeFile + _T("E") + _T(".jpg");

					m_ID_String = _T("FZ") + strTimeFile + _T("E");
					m_Edit_ID_Values.SetWindowTextA(m_ID_String);	 //id号				

					sMsg = strTemp + sMsg;
					m_csFileName = sMsg; //路径
					strPath = sMsg;

					USES_CONVERSION;
					path = sMsg.GetBuffer(sMsg.GetLength() + 1);


					if (rename(szTempPath, path) == 0)
					{
						m_StatVal.SetWindowText("保存照片成功！");
					}
					else
					{
						if (remove(szTempPath) == 0)
						{
							m_StatVal.SetWindowText("保存照片成功！");
						}
						else
						{
							m_StatVal.SetWindowText("保存照片失败！");
						}
					}

				}

				m_vEdit7.SetWindowText(sMsg);
				sMsg.ReleaseBuffer();
				if (iPhototype == 0 && nRet == 0)
				{
					HBITMAP hBitmap;
					CStatic *pStatic = (CStatic *)GetDlgItem(IDC_SVPERSHOW);
					sText.Format("%s", idcardData.PhotoFileName);
					hBitmap = (HBITMAP) ::LoadImage(NULL, sText, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
					pStatic->ModifyStyle(0XF, SS_BITMAP);
					pStatic->SetBitmap(hBitmap);
				}
				else if (iPhototype == 1 && nRet == 0)
				{
					CRect rect;
					USES_CONVERSION;
					wcscpy(buf, A2W((LPCSTR)strPath));  //CString -> wchar_t
														//Image image(L"C:\\temp1", TRUE);  
					Image image(buf, TRUE);

					CWnd *pWnd = GetDlgItem(IDC_Picture_Show);
					Graphics graphics(pWnd->GetDC()->m_hDC);
					GetDlgItem(IDC_Picture_Show)->GetClientRect(&rect);
					graphics.DrawImage(&image, 0, 0, rect.Width(), rect.Height());

				}
			}
			else
			{
				sMsg = "读取身份证信息错误!";
				m_StatVal.SetWindowText(sMsg);
			}
		}
	}
	else
	{
		sMsg = "打开端口错误";
		m_StatVal.SetWindowText(sMsg);
	}
	Syn_ClosePort(m_iPort);
}
