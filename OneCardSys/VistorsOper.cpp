// VistorsOper.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "VistorsOper.h"
#include "afxdialogex.h"
#include "SynPublic.h"

#include <atlconv.h>

#pragma  comment(lib, "SynIDCardAPI.lib")
bool g_bFlag = false;

CString Id_String = "";   //得到页面上的身份证号，抓图用
BOOL bFlage = TRUE;       //设置一个标志，防止死循环
CString  g_FilePath = ""; //全局文件名
CString g_pic_id = "";//照片id号

// CVistorsOper 对话框

IMPLEMENT_DYNAMIC(CVistorsOper, CDialogEx)

CVistorsOper::CVistorsOper(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLGVISITOPER, pParent)
	, m_Name_String(_T(""))
	, m_Sex_String(_T(""))
	, m_ID_String(_T(""))
	, m_FKAddr_String(_T(""))
	, m_BFZName_String(_T(""))
	, m_BFZAddr_String(_T(""))
	, m_Picture_Path(_T(""))
	, m_ShowInfoReg(_T(""))
	, m_SH_String(_T(""))
	, m_LH_String(_T(""))
	, m_PicId_String(_T(""))
	, m_Tel_String(_T(""))
	, m_FWJZTime(COleDateTime::GetCurrentTime())
{

}

CVistorsOper::~CVistorsOper()
{
	//LogOut();
}

void CVistorsOper::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VEDIT1, m_vEdit1);
	DDX_Control(pDX, IDC_VEDIT2, m_vEdit2);
	DDX_Control(pDX, IDC_VEDIT3, m_vEdit3);
	DDX_Control(pDX, IDC_VEDIT4, m_vEdit4);
	DDX_Control(pDX, IDC_VEDIT5, m_vEdit5);
	DDX_Control(pDX, IDC_VEDIT6, m_vEdit6);
	DDX_Control(pDX, IDC_VEDIT7, m_vEdit7);
	DDX_Control(pDX, IDC_VCOBXSEX, m_combxSex);
	DDX_Text(pDX, IDC_VEDIT2, m_Name_String);
	DDX_CBString(pDX, IDC_VCOBXSEX, m_Sex_String);
	DDX_Text(pDX, IDC_VEDIT3, m_ID_String);
	DDX_Text(pDX, IDC_VEDIT4, m_FKAddr_String);
	DDX_Text(pDX, IDC_VEDIT5, m_BFZName_String);
	DDX_Text(pDX, IDC_VEDIT6, m_BFZAddr_String);
	DDX_Text(pDX, IDC_VEDIT7, m_Picture_Path);
	DDX_Control(pDX, IDC_SVPERSHOW, m_Picture);
	DDX_Text(pDX, IDC_ShowInfo, m_ShowInfoReg);
	DDX_Text(pDX, IDC_EDIT_SH, m_SH_String);
	DDX_Text(pDX, IDC_EDIT_LH, m_LH_String);
	DDX_Text(pDX, IDC_Picture_ID, m_PicId_String);
	DDX_Control(pDX, IDC_Picture_ID, m_Edit_ID_Values);
	DDX_Text(pDX, IDC_EDITTel, m_Tel_String);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_FWJZTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_CTCTimeEd);
}


BEGIN_MESSAGE_MAP(CVistorsOper, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTNVINIT, &CVistorsOper::OnBnClickedBtnvinit)
	ON_BN_CLICKED(IDC_BTNVREAD, &CVistorsOper::OnBnClickedBtnvread)
	ON_BN_CLICKED(IDC_BTNVCLEAR, &CVistorsOper::OnBnClickedBtnvclear)
	ON_BN_CLICKED(IDC_BTNVREG, &CVistorsOper::OnBnClickedBtnvreg)
	ON_BN_CLICKED(IDC_BTNVLEAV, &CVistorsOper::OnBnClickedBtnvleav)
	ON_BN_CLICKED(IDC_BUTTON6, &CVistorsOper::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BtnSDSelectPicture, &CVistorsOper::OnBnClickedBtnsdselectpicture)
	ON_BN_CLICKED(IDC_BUTTON1, &CVistorsOper::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



//
//BOOL CVistorsOper::CheckLoginOk()
//{
//	if (0 < m_lLoginID)
//		return TRUE;
//	MessageBox(_T("还未登录！"), _T(""), MB_OK);
//	return FALSE;
//}

// CFaceOper 消息处理程序


/*****************************************************************************/

// CVistorsOper 消息处理程序
BOOL CVistorsOper::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

									// TODO: 在此添加额外的初始化代码
	
	m_playHandle = 0;  //截图句柄

	CRect rect1;
	GetClientRect(&rect1);     //取客户区大小  
	old.x = rect1.right - rect1.left;
	old.y = rect1.bottom - rect1.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);


	m_CTCTimeEd.SetFormat(_T("yyyy-MM-dd    HH:mm:ss"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CVistorsOper::OnPaint()
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
		CDialog::OnPaint();
	}
}

void CVistorsOper::OnBnClickedBtnvinit() //刷证初始化
{
	// TODO: 在此添加控件通知处理程序代码
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
	m_vEdit1.SetWindowText(sMsg);
}


void CVistorsOper::OnBnClickedBtnvread()  //读二代身份证信息
{
	// TODO: 在此添加控件通知处理程序代码
	OnBnClickedBtnvinit(); //刷证初始化

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
		m_vEdit1.SetWindowText(_T("请初始化后确认读卡器正常连接"));
		return;
	}

	CString csPath = _T("C:\\YTPicture");
	if (!PathIsDirectory(csPath))
	{
		CreateDirectory(csPath, 0);//不存在则创建
	}
	csPath = _T("C:\\YTPicture\\FKPicture");//每次把选择路径给cspath，防止cstring叠加，出错

	if (!PathIsDirectory(csPath))
	{
		CreateDirectory(csPath, 0);//不存在则创建	
	}

	char   szBuffer[_MAX_PATH] = "C:\\YTPicture\\FKPicture";
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
				m_vEdit1.SetWindowText(sMsg);
				sMsg.Format(_T("%s"), idcardData.Name);
				m_vEdit2.SetWindowText(sMsg);
				sMsg.Format(_T("%s"), idcardData.Sex);
				sprintf(szTemp, _T("%s"), idcardData.Sex);
				if (0 == strcmp(szTemp, _T("男")))
				{
					m_combxSex.SetCurSel(0);
				}
				else if (0 == strcmp(szTemp, _T("女")))
				{
					m_combxSex.SetCurSel(1);
				}


				//m_vEdit3.SetWindowText(sMsg);
				//sMsg.Format("民族:%s", idcardData.Nation);

				//sMsg.Format("出生:%s", idcardData.Born);

				sMsg.Format("%s", idcardData.Address);
				m_vEdit4.SetWindowText(sMsg);
				sMsg.Format("%s", idcardData.IDCardNo);
				m_vEdit3.SetWindowText(sMsg);
				//sMsg.Format("发证机关:%s", idcardData.GrantDept);
				//InsertDebugMes(sMsg);
				//sMsg.Format("有效期开始:%s", idcardData.UserLifeBegin);
				//InsertDebugMes(sMsg);
				//sMsg.Format("有效期结束:%s", idcardData.UserLifeEnd);
				//InsertDebugMes(sMsg);
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

					CString strTemp = _T("C:\\YTPicture\\FKPicture\\FK");
					
					sMsg = sMsg.Right(sMsg.GetLength() - 1 - sMsg.ReverseFind('\\')); //身份证号
					sMsg = strTimeFile + _T("E") + _T(".jpg");
					
					m_PicId_String =  _T("FK") + strTimeFile + _T("E");					
					m_Edit_ID_Values.SetWindowTextA(m_PicId_String);
					g_pic_id = m_PicId_String; // 把身份证id给上传id号

					sMsg = strTemp + sMsg;
					m_Picture_Path = sMsg;					
					strPath = sMsg;

					USES_CONVERSION;
					path = sMsg.GetBuffer(sMsg.GetLength() + 1);
			

					if (rename(szTempPath, path) == 0)
					{
						m_vEdit1.SetWindowText("保存照片成功！");
					}
					else
					{
						if (remove(szTempPath) == 0)
						{
							m_vEdit1.SetWindowText("保存照片成功！");
						}
						else
						{
							m_vEdit1.SetWindowText("保存照片失败！");
							AfxMessageBox(_T("保存照片失败"));
						}
					}
					
				}

				//InsertDebugMes(sMsg);
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

					CWnd *pWnd = GetDlgItem(IDC_SVPERSHOW);
					Graphics graphics(pWnd->GetDC()->m_hDC);
					GetDlgItem(IDC_SVPERSHOW)->GetClientRect(&rect);
					graphics.DrawImage(&image, 0, 0, rect.Width(), rect.Height());

				}
			}
			else
			{
				sMsg = "读取身份证信息错误!";
				m_vEdit1.SetWindowText(sMsg);
			}
		}
	}
	else
	{
		sMsg = "打开端口错误";
		m_vEdit1.SetWindowText(sMsg);
	}
	Syn_ClosePort(m_iPort);
}

void CVistorsOper::ClearDate()
{
	m_vEdit1.SetWindowText("");
	m_vEdit2.SetWindowText("");
	m_vEdit3.SetWindowText("");
	m_vEdit4.SetWindowText("");
	m_vEdit5.SetWindowText("");
	m_vEdit6.SetWindowText("");
	m_vEdit7.SetWindowText("");
	m_combxSex.SetCurSel(-1);

	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_SVPERSHOW);
	CRect lRect;
	pStatic->GetClientRect(&lRect);
	pStatic->GetDC()->FillSolidRect(lRect.left, lRect.top, lRect.Width(), lRect.Height(), RGB(240, 240, 240));

	m_ID_String = "";
	m_Picture_Path = "";
	Id_String = "";   //得到页面上的身份证号，抓图用
	bFlage = TRUE;       //设置一个标志，防止死循环
	g_FilePath = ""; //全局文件名
	m_Sex_String = "";
	m_FKAddr_String = "";
	m_BFZName_String = "";
	m_BFZAddr_String = "";
	m_Name_String = "";
	m_LH_String = "";
	m_SH_String = "";
	m_PicId_String = "";


	InvalidateRect(NULL, FALSE);
}

void CVistorsOper::OnBnClickedBtnvclear()  //清除数据
{
	// TODO: 在此添加控件通知处理程序代码
	CRect rect;
	
	CWnd *pWnd = GetDlgItem(IDC_SVPERSHOW);
	Graphics graphics(pWnd->GetDC()->m_hDC);
	GetDlgItem(IDC_SVPERSHOW)->GetClientRect(&rect);
	//graphics.DrawImage(&image, 0, 0, rect.Width(), rect.Height());
	Color color;
	graphics.Clear(color.LightGray);
	
	ClearDate();
	m_ShowInfoReg = "";
							  // CVistorsOper 对话框
	UpdateData(FALSE);
}

void CVistorsOper::OnBnClickedBtnvreg()      //登记，上传人脸；查看在数据据中是否有记录，有签离记录，直接改字段，上传人脸；没有记录，上传人脸，注册
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int upFaceFlage = 0; //照片上传成功置为1，如果写入数据库失败，且照片上传成功，就删除照片

	if (TRUE != CheckLoginOk())
		return;

	CString strTime;
	CTime   timTemp;
	timTemp = CTime::GetCurrentTime();
	strTime = timTemp.Format("%Y-%m-%d %H:%M:%S");   //登记时间
	CString IDNum = g_pic_id;
	CString HMD = _T("否");
	

	if (m_ID_String.IsEmpty())   //检查身份证是否为空
	{
		AfxMessageBox(_T("身份证为空，重新输入"));

		return;
	}
	int nLen = m_ID_String.GetLength();  //身份证
	for (int i = 0; i<nLen;i++)
	{
		if (!(m_ID_String.GetAt(i) >= '0' && m_ID_String.GetAt(i) <= '9' || m_ID_String.GetAt(i) >= 'A' && m_ID_String.GetAt(i) <= 'Z'))
		{
			MessageBox(_T("身份证格式错误"), _T("请重新输入"), 0);
			return;
		}
	}

	/************************************************************************/
	/* 人证核验                                                             */
	/************************************************************************/
	g_strPictureId = m_PicId_String;
	g_strFacePath = m_Picture_Path;

	CWintCheckVido m_cWintCheck;
	m_cWintCheck.DoModal();

	if (g_ReconPass != 1)
	{
		m_ShowInfoReg = _T("人证核验不通过，请重试!");
		return;
	}
	else
	{
		m_ShowInfoReg = g_strPictureId + _T("人证核验通过");
	}

	//// api实例指针
	//BaiduFaceApi *api = new BaiduFaceApi();
	//std::string res1 = api->match(m_Picture_Path, 2, "d:\\8.jpg", 2);


   /************************************************************************/
   /* 把照片转成二进制存入数据库                                           */
   /************************************************************************/
	m_varPictureToEJZ = PictureToEJZ(m_Picture_Path); 
	if (0 == m_varPictureToEJZ.iVal)
	{
		m_ShowInfoReg = _T("人脸图片转换成二进制失败，请重试");

		return;
	}
	m_nPictureLen = g_PictureLen; //获取照片的二进制数据大小
	

	/************************************************************************/
	/*  上传照片到摄像机                                                    */
	/************************************************************************/
	if (UpFacePicture(g_pic_id, m_lLoginID, m_Picture_Path) == TRUE)  //
	{
		upFaceFlage = 1;		
	}
	else
	{
		CWnd *pBtn1 = GetDlgItem(IDC_BUTTON1); //重新选取照片可用
		pBtn1->EnableWindow(TRUE);

		return;
	}


	/************************************************************************/
	/* 校验访客是否存在														*/
	/* 开始																    */
	/************************************************************************/ 
	try             	//首先查询数据库
	{
		CString ID_Tmp = "";   //id临时变量
		CString HMD_Tmp = "";  //黑名单临时变量

		CString Sql;
		Sql.Format("SELECT IDCardNum,HMD FROM [FaceContCen].[dbo].[FK_UserTabel] WHERE IDCardNum = '%s'", m_ID_String);

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);
		
		//被访者姓名
		ID_Tmp = m_pRecordSet->GetCollect(_variant_t(_T("IDCardNum")));  //用户不存在直接到catch
		if (!ID_Tmp.IsEmpty())
		{
			HMD_Tmp = m_pRecordSet->GetCollect(_variant_t(_T("HMD")));

			if (HMD_Tmp == "是")
			{
				MessageBox(_T("该访客为黑名单用户,请注意！"),_T("警告"),MB_OK|MB_ICONERROR);
				
				goto RegUse;
			}
			else   //用户存在也不是黑名单用户
			{
			RegUse:

				try
				{
					if (m_pRecordSet->State)
					{
						m_pRecordSet->Close();
					}

					CString Sql;
					Sql.Format("UPDATE [FaceContCen].[dbo].[FK_UserTabel] SET IDNum = '%s', BeginTime = '%s',SingnOff = '%s',BFZ_Name = '%s',BFZ_LH = '%s',BFZ_FH = '%s',QL_Time = '%s' WHERE IDCardNum = '%s'", IDNum.GetBuffer(0), strTime.GetBuffer(0), "否", m_BFZName_String.GetBuffer(0), m_LH_String.GetBuffer(0), m_SH_String.GetBuffer(0) , _T("未签离"), m_ID_String.GetBuffer(0));

					
					m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
						adLockOptimistic, adCmdText);

					m_ShowInfoReg = _T("ID:") + m_ID_String + _T("  姓名: ") + m_Name_String + _T(" 再次登记成功");	

					if (m_pRecordSet->State)   //关闭记录集
					{
						m_pRecordSet->Close();
					}

					goto FaceReg;
				}
				catch (_com_error e)
				{
					if (m_pRecordSet->State)
					{
						m_pRecordSet->Close();
					}
					CATCH_ERROR;
					if (1 == upFaceFlage) //
					{
						DropFacePicture(g_pic_id, m_lLoginID);	 //删除注册sql失败时，照片上传成功的照片
						upFaceFlage = 0;
					}
					MessageBox(_T("注册失败"), _T("注册"), MB_OK);

					return;
				}
			}
		}
		if (m_pRecordSet->State)		//关闭记录集
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

	/************************************************************************/
	/* 新用户注册                                                           */
	/************************************************************************/
	try    
	{
		CString strSql = _T("");
		strSql.Format(_T("Select * from [FaceContCen].[dbo].[FK_UserTabel]"));  //选择数据库表
		m_pRecordSet->Open(_bstr_t(strSql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);  //打开表
		m_pRecordSet->AddNew();  //首先添加一条记录
		m_pRecordSet->PutCollect("IDNum", IDNum.GetString());
		m_pRecordSet->PutCollect("Name", m_Name_String.GetString());
		m_pRecordSet->PutCollect("Sex", m_Sex_String.GetString());
		m_pRecordSet->PutCollect("IDCardNum", m_ID_String.GetString());
		m_pRecordSet->PutCollect("BFZ_Name", m_BFZName_String.GetString());
		m_pRecordSet->PutCollect("FK_Addr", m_FKAddr_String.GetString());
		m_pRecordSet->PutCollect("BFZ_LH", m_LH_String.GetString());
		m_pRecordSet->PutCollect("BFZ_FH", m_SH_String.GetString());
		m_pRecordSet->PutCollect("BeginTime", strTime.GetString());
		m_pRecordSet->PutCollect("HMD", HMD.GetString());
		m_pRecordSet->PutCollect("SingnOff", _T("否"));
		if (m_nPictureLen > 0)   //把图片存到sql
		{
			m_pRecordSet->PutCollect("PictureLength", m_nPictureLen);
			m_pRecordSet->GetFields()->GetItem("PictureDate")->AppendChunk(m_varPictureToEJZ);
		}

		m_pRecordSet->Update();  //记录更新到sql
		m_pRecordSet->Close();

		m_ShowInfoReg = _T(" ID: ") + m_ID_String + _T("\n 姓名: ") + m_Name_String + _T("登记成功");
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T(" ID: ") + m_ID_String + _T("\n 姓名: ") + m_Name_String + _T("\n 登记失败，请重新登记"));

		if (m_pRecordSet->State)
		{
			m_pRecordSet->CancelUpdate();  //关闭updae异常
			m_pRecordSet->Close();
		}
		CATCH_ERROR;
	}
	
FaceReg:
	g_Action = _T("访客登记");
	OperRZ(g_Action);          //日志
	
	/************************************************************************/
	/* 清屏                                                                  */
	/************************************************************************/
	ClearDate();
	UpdateData(FALSE);
}

void CVistorsOper::OperRZ(CString g_Action)
{
	////////////////////////日志////////////////////////////////////////////	
	CTime tmp_tm = CTime::GetCurrentTime();
	CString TimeEnd = tmp_tm.Format("%y-%m-%d %H:%M:%S");
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

void CVistorsOper::OnBnClickedBtnvleav()     //签离 改数据库字段，删除人脸
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (TRUE != CheckLoginOk())
	{
		return;
	}
	CString m_strIdTmp = "";//照片编号
	CString strTime;
	CTime   timTemp;
	timTemp = CTime::GetCurrentTime();
	strTime = timTemp.Format("%Y-%m-%d %H:%M:%S   ");   //签离时间
	try    //查看身份证是否在数据库中，不再说明输错或者已经签离或者未登记
	{
		CString Sql;
		Sql.Format("SELECT IDNum FROM [FaceContCen].[dbo].[FK_UserTabel] WHERE IDCardNum = '%s'", m_ID_String);

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);	
		
		_variant_t FP;	
		FP = m_pRecordSet->GetCollect(_variant_t(_T("IDNum")));
		if (FP.vt != VT_NULL)//如果不为空
		{
			m_strIdTmp = FP;
		}
		else
		{
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

		m_ID_String = "";
		AfxMessageBox("该用户未登记，请登记！");

		return;
	}

	if (m_ID_String.IsEmpty())
	{
		AfxMessageBox(_T("身份证为空，重新输入"));

		return;
	}
	//MessageBox(m_strIdTmp, "签离", 0);

	if (TRUE != DropFacePicture(m_strIdTmp, m_lLoginID))
	{
		m_ShowInfoReg = _T("摄像机照片删除失败,重试！");
		UpdateData(FALSE);

		return;
	}	

	try
	{	
		CString Sql;
		Sql.Format("UPDATE [FaceContCen].[dbo].[FK_UserTabel] SET QL_Time = '%s', SingnOff = '%s'  WHERE IDCardNum = '%s'", strTime.GetBuffer(0),_T("是"), m_ID_String.GetBuffer(0));

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		m_ShowInfoReg = _T(" ID: ") + m_ID_String + _T(" 姓名: ") + m_Name_String + _T(" 签离成功");

		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}
		ClearDate(); //清空屏幕
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}

		m_ShowInfoReg = (_T(" ID: ") + m_ID_String + _T("\n 姓名: ") + m_Name_String + _T("\n 签离失败，请重试一次"));
	}

	g_Action = m_Name_String + _T("  访客签离");     //日志
	OperRZ(g_Action);
	
	UpdateData(FALSE);
}


void CVistorsOper::OnBnClickedButton6()     //手动选取访客照片上传
{
	// TODO: 在此添加控件通知处理程序代码
}

int CALLBACK realload_callback1(LLONG lAnalyzerHandle,
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
		CString strJQ = _T("C:\\YTPicture");	//截取字符串，创建文件夹
		if (!PathIsDirectory(strJQ))
		{
			CreateDirectory(strJQ, 0);//不存在则创建 ,一级目录
		}
		strJQ = _T("C:\\YTPicture\\FKPicture");
		if (!PathIsDirectory(strJQ))
		{
			CreateDirectory(strJQ, 0);//不存在则创建，二级目录
		}
		//strJQ += _T("/FK") + Id_String + _T(".jpg");

		

		CString strTimeFile;
		CTime tm;          //获取系统时间
		tm = CTime::GetCurrentTime();
		strTimeFile = tm.Format("FK%y%m%d%H%M%S");

		strJQ += _T("\\") + strTimeFile + _T("E") + _T(".jpg");
		g_pic_id = strTimeFile + _T("E");
		FILE *pFilePath = fopen(strJQ, _T("w+b")); //效率低
		if (NULL != pFilePath)
		{
			fwrite(pBuffer, 1, dwBufSize, pFilePath);	//写入文件		
			g_FilePath = strJQ;
			
			fclose(pFilePath);
		}
		else
		{
			g_FilePath = _T("");
			MessageBox(NULL, _T("抓取失败，重试一次！"), NULL, MB_ICONERROR);
		}
	}

	return 0;
}


BOOL CVistorsOper::StartRealStream()
{
	// 图片数据处理在 realload_callback 回调中
	int nChannel = 0;

	m_playHandle = Net_RealLoadPicture(m_ZPLoginID, nChannel, EVENT_SP_FACE_SNAP_PART, 1,
		realload_callback1, NULL, NULL);
	if (0 >= m_playHandle)
	{
		MessageBox(_T("网络库错误，请重启截取人脸功能.\n"), NULL, MB_ICONERROR);
		Net_LogoutDevice(m_ZPLoginID);

		return FALSE;
	}

	return TRUE;
}

void CVistorsOper::OnBnClickedBtnsdselectpicture()
{
	// TODO: 在此添加控件通知处理程序代码	
}


void CVistorsOper::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	
	UpdateData(TRUE);

	Id_String = m_ID_String;

	if (Id_String.IsEmpty())
	{
		MessageBox(_T("身份证为空，请输入身份证号码"), NULL, MB_ICONERROR);

		return;
	}
	else
	{
		m_ShowInfoReg = _T("正在采集人脸数据，请稍后......");
	}

	if (StartRealStream())
	{
		UiTimer = SetTimer(1, 100, NULL);  //开启计时器，实时刷新界面

		CWnd *pBtn1 = GetDlgItem(IDC_BUTTON1);
		pBtn1->EnableWindow(FALSE);
	}

	UpdateData(FALSE);
}

void CVistorsOper::OnTimer(UINT_PTR nIDEvent)
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

BOOL  CVistorsOper::ExecuPicture()
{
	UpdateData(TRUE);
	CString strExt(".jpg");
	if (g_FilePath.IsEmpty() || -1 == g_FilePath.Find(strExt.GetBuffer(0)))
		return FALSE;

	CImage image;
	image.Load(g_FilePath);
	
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

	if (!g_FilePath.IsEmpty() && bFlage)
	{
		bFlage = FALSE;
		if (IDYES == MessageBox(_T("确实使用此人脸？"), _T("确认"), MB_YESNO | MB_ICONQUESTION))
		{
			if (0 >= m_playHandle)
			{
				MessageBox(_T("手动选取访客照片"), _T("Tip"), MB_ICONERROR);

				return FALSE;
			}
			bFlage = TRUE;

			m_Picture_Path = g_FilePath;  //界面edit路径
			Net_StopLoadPicture(m_playHandle); //停止网络数据拉流

			KillTimer(1);  //结束计时器

			CWnd *pBtn1 = GetDlgItem(IDC_BUTTON1);
			pBtn1->EnableWindow(TRUE);
			m_ShowInfoReg = _T("照片采集成功，请进行下一步操作。");
			m_PicId_String = g_pic_id;
			UpdateData(FALSE);

			return TRUE; 
		}
		else
		{
			g_FilePath = _T("");
			bFlage = TRUE;

			CStatic* pStatic = (CStatic*)GetDlgItem(IDC_SVPERSHOW);
			CRect lRect;
			pStatic->GetClientRect(&lRect);
			pStatic->GetDC()->FillSolidRect(lRect.left, lRect.top, lRect.Width(), lRect.Height(), RGB(240, 240, 240));

			CWnd *pBtn1 = GetDlgItem(IDC_BUTTON1);
			pBtn1->EnableWindow(TRUE);
		}
	}

	UpdateData(FALSE);
	return FALSE;
}

void CVistorsOper::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	//DestroyWindow();

	CDialogEx::OnCancel();
}


void CVistorsOper::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类
//	delete this;
	CDialogEx::PostNcDestroy();
}


void CVistorsOper::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	CDialogEx::OnClose();
}

void CVistorsOper::ReSize()
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

		if (woc == IDC_VCOBXSEX)
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

void CVistorsOper::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}
