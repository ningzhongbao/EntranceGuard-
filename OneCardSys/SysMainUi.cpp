// SysMainUi.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "SysMainUi.h"
#include "afxdialogex.h"
#include "HttpPost.h"

// �ͷ�ָ���
#define RELEASE(x)                      {if(x != NULL ){delete x;x=NULL;}}

// CSysMainUi �Ի���

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
		RELEASE(m_ExportPicture) //�ͷŵ���ͼƬ�ڴ�ؼ�
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


void CSysMainUi::QXFun()  //Ȩ�޻���
{
	if (_T("����") == g_QX)
	{
		CWnd *IOSelect = GetDlgItem(IDC_Btn_IOSelect); //��Ա�������ѯ
		//pCan->EnableWindow(FALSE);
		IOSelect->ShowWindow(SW_HIDE);

		CWnd *BTNLOG = GetDlgItem(IDC_BTNLOG);  //��־��ѯ
		BTNLOG->ShowWindow(SW_HIDE);
		
		GetDlgItem(IDC_Btn_XFPermis)->ShowWindow(SW_HIDE); //�·�Ȩ��


		CWnd *BTNVRECORD = GetDlgItem(IDC_Btn_OutFacePicture); //��������ͼƬ
		BTNVRECORD->ShowWindow(SW_HIDE);

		CWnd *Btn_Oper_Per = GetDlgItem(IDC_Btn_Oper_Per);  //ס������
		Btn_Oper_Per->ShowWindow(SW_HIDE);

		CWnd *Register = GetDlgItem(IDC_Btn_Register);  //ס��ע��
		Register->ShowWindow(SW_HIDE);

		CWnd *GetPerInfo = GetDlgItem(IDC_GetPerInfo);  // �ɼ�������Ϣ									
		GetPerInfo->ShowWindow(SW_HIDE);

		CWnd *BtnFaceOper = GetDlgItem(IDC_BtnFaceOper);  // ���������
		BtnFaceOper->ShowWindow(SW_HIDE);
		//		
		//CWnd *Btn_Result = GetDlgItem(IDC_Btn_Result);  // ʱ��ͨ�в���
		//Btn_Result->ShowWindow(SW_HIDE);

		//RecvSysTime();//����ϵͳʱ��У��

	}
	else if (_T("��ҵ") == g_QX)
	{
		CWnd *IOSelect = GetDlgItem(IDC_Btn_IOSelect); //��Ա�������ѯ
		IOSelect->ShowWindow(SW_HIDE);

		CWnd *BTNLOG = GetDlgItem(IDC_BTNLOG);  //��־��ѯ
		BTNLOG->ShowWindow(SW_HIDE);

		CWnd *XFPermis = GetDlgItem(IDC_Btn_XFPermis); //�·�Ȩ��
		XFPermis->ShowWindow(SW_HIDE);
		
		//GetDlgItem(IDC_AddUser)->ShowWindow(SW_HIDE);   //����û�
		//GetDlgItem(IDC_DelUser)->ShowWindow(SW_HIDE); //ɾ���û�

		CWnd *OutFacePicture = GetDlgItem(IDC_Btn_OutFacePicture);  //����ҵ������
		OutFacePicture->ShowWindow(SW_HIDE);

		CWnd *GetPerInfo = GetDlgItem(IDC_GetPerInfo);  // �ɼ�������Ϣ
		GetPerInfo->ShowWindow(SW_HIDE);

		CWnd *tnFaceOper = GetDlgItem(IDC_BtnFaceOper);  // ���������
		tnFaceOper->ShowWindow(SW_HIDE);

		CWnd *Btn_Result = GetDlgItem(IDC_Btn_Result);  // ʱ��ͨ�в�
		Btn_Result->ShowWindow(SW_HIDE);

		CWnd *BUTTON1 = GetDlgItem(IDC_BUTTON1);  // ʱ��ͨ�в���
		BUTTON1->ShowWindow(SW_HIDE);
		
		CWnd *BTNVRECORD = GetDlgItem(IDC_BTNVRECORD);  // �ÿͼ�¼
		BTNVRECORD->ShowWindow(SW_HIDE);
	}
}

// CSysMainUi ��Ϣ�������
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
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		//dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDC *pDC;
		pDC = GetDC();
		CRect  rect;
		GetClientRect(&rect);   //��ȡ�ͻ�����С
		Graphics graphics(pDC->m_hDC);
		//Graphics graphics(dc.m_hDC);
		Image image(L"./res/BG_MainUI.jpg", FALSE);
		graphics.DrawImage(&image, 0, 0, rect.right, rect.bottom);  //���Ʊ���

		CDialogEx::OnPaint();
	}
}

BOOL CSysMainUi::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	ModifyStyleEx(0, WS_EX_APPWINDOW);//��ʾ������ͼ��

	m_Font.CreatePointFont(200, _T("Arial"), NULL);
	m_static1.SetFont(&m_Font, true);
	m_static2.SetFont(&m_Font, true);
	m_static3.SetFont(&m_Font, true);
	m_static4.SetFont(&m_Font, true);

	CRect rect;
	GetClientRect(&rect);     //ȡ�ͻ�����С  
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

	ViSet = new CViSet;    //���������
// 	ViSet->Create(IDD_DIAVISET, this);
// 	ViSet->ShowWindow(SW_HIDE);
// 	ViSet->AllViLogin(); //��ʼ�������ip

	//if (_T("����Ա") == g_QX)
	//{
	//	SendSysTime(); //����ϵͳʱ��
	//}

	m_ShowType_String = g_QX;  //���õ�½Ȩ��
	QXFun();      
	UpdateData(FALSE);

	//CMenu *pSysMenu = GetSystemMenu(FALSE);  //�رհ�ť
	//if (NULL != pSysMenu)
	//{
	//	pSysMenu->EnableMenuItem(SC_CLOSE, MF_GRAYED);
	//}	

	CDC *pDC;                                    //������ͼ
	pDC = GetDC();
	CRect  rect2;
	GetClientRect(&rect2);                       //��ȡ�ͻ�����С
	Graphics graphics(pDC->m_hDC);
	//Graphics graphics(dc.m_hDC);
	Image image(L"./res/BG_MainUI.jpg", FALSE);
	graphics.DrawImage(&image, 0, 0, rect2.right, rect2.bottom);  //���Ʊ���

	CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HttpUpdateHeart, (LPVOID)NULL, 0, 0));   //���������� HttpHeartBeat

	m_Menu.LoadMenu(IDR_MEMUSER);  //  IDR_MENU1//�˵���
	SetMenu(&m_Menu);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSysMainUi::OnBnClickedGetperinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*if (NULL == m_pPerDlg)
	{
		m_pPerDlg = new CGetInfoPer();
		m_pPerDlg->Create(IDD_GETPERSON, this);
	}
	m_pPerDlg->ShowWindow(SW_SHOW);	*/
	CGetInfoPer PerDlg; //��ȡ����ͼƬ
	if (IDOK == PerDlg.DoModal())
	{
		this->ShowWindow(SW_HIDE);
	}
}


void CSysMainUi::OnBnClickedBtnperinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL == m_pPicDlg)
	{
		m_pPicDlg = new CPicture1();
		m_pPicDlg->Create(IDD_PERSON_INFO, this);
	}
	m_pPicDlg->ShowWindow(SW_SHOW);
}


void CSysMainUi::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdateData(TRUE);

	ViSet->AllLogOut();
	if (m_pConnection->State)  //�ر����ݿ�����
	{
		m_pConnection->Close();
	}

	PostQuitMessage(0);	  //�˳���Ϣ��
	CDialogEx::OnClose();
}


void CSysMainUi::OnBnClickedGetoweinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL == m_OwenInfo)
	{
		m_OwenInfo = new CGetOwerInfo();
		m_OwenInfo->Create(IDD_GetOwerInfo, this);
	}
	m_OwenInfo->ShowWindow(SW_SHOW);
}


void CSysMainUi::OnBnClickedBtnsendowerinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}


void CSysMainUi::OnBnClickedBtnfaceoper()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//if (NULL == m_FaceOpen)
	//{
	//	m_FaceOpen = new CFaceOper();
	//	m_FaceOpen->Create(IDD_DIAUPFACEPICTURE, this);
	//}
	//m_FaceOpen->ShowWindow(SW_SHOW);
	CFaceOper   FaceOpen;//�����ϴ�2
	if (IDOK == FaceOpen.DoModal())
	{
		this->ShowWindow(SW_HIDE);
	}
}


void CSysMainUi::OnBnClickedBtnRegister()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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


void CSysMainUi::OnBnClickedButton1() //�ÿͲ���
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������   CVistorsOper  *m_VistorOPer;
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


void CSysMainUi::OnBnClickedBtnvrecord()  //�ÿͼ�¼
{
	// TODO: �ڴ���ӿؼ�֪ͨ���������� CVistorsRecord *m_VistorRecord;
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


void CSysMainUi::OnBnClickedBtnResult()  //�����Ա�ʶ����
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������  CPersComprResult *m_PersCompare;
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
void CSysMainUi::OnBnClickedBtnlog()   //��־��ѯ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL == m_LogInfo)
	{
		m_LogInfo = new CLogInfo();
		m_LogInfo->Create(IDD_DLGLOGINFO, this);
	}

	m_LogInfo->ShowWindow(SW_SHOW);
}


void CSysMainUi::OnBnClickedBtnzx()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (IDYES == MessageBox(_T("�Ƿ�ע����"), _T("ע��"), MB_YESNO | MB_ICONASTERISK))
	{
		ViSet->AllLogOut();//�ǳ����������
	
		////////////////////////��־////////////////////////////////////////////
		g_Action = _T("ע��");

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
		/////////////////////////////��־///////////////////////////////////////
		
		CDialogEx::OnOK();
	}
}


void CSysMainUi::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}

void CSysMainUi::ReSize()
{
	float fsp[2];
	POINT Newp; //��ȡ���ڶԻ���Ĵ�С
	CRect recta;
	GetClientRect(&recta);     //ȡ�ͻ�����С  
	Newp.x = recta.right - recta.left;
	Newp.y = recta.bottom - recta.top;
	fsp[0] = (float)Newp.x / old.x;
	fsp[1] = (float)Newp.y / old.y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint, TLPoint; //���Ͻ�
	CPoint OldBRPoint, BRPoint; //���½�
	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //�г����пؼ�  
	while (hwndChild)
	{
		woc = ::GetDlgCtrlID(hwndChild);//ȡ��ID
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CPERSONIO perIO;
	if (IDOK == perIO.DoModal())
	{
		this->ShowWindow(SW_HIDE);
	}
}


void CSysMainUi::OnBnClickedBtnOutfacepicture()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (NULL == m_ExportPicture)
	{
		m_ExportPicture = new CExportPicture();
		m_ExportPicture->Create(IDD_DIAEXPORT, this);
	}
	m_ExportPicture->ShowWindow(SW_SHOW);
	m_ExportPicture->ExportFun();
}

BOOL CSysMainUi::PreTranslateMessage(MSG* pMsg)   //����esc
{
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ���������������
	CAddUser addUser;
	addUser.DoModal();
}


void CSysMainUi::On32772()
{
	// TODO: �ڴ���������������
	CDeleUser delUser;
	delUser.DoModal();
}


void CSysMainUi::On32773()
{
	// TODO: �ڴ���������������
	OnBnClickedBtnzx();
}



void CSysMainUi::On32774()
{
	// TODO: �ڴ���������������	
	ViSet->DoModal();
}


void CSysMainUi::SendSysTime()  //����������ϵͳʱ��
{
	WSADATA wd;
	int err;
	int iResult;//�󶨽��

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
		::MessageBox(NULL, "����Уʱ������ʧ�ܣ�", NULL, 0);
		closesocket(sockClient);
		WSACleanup();
		return ;
	}
	
	/* ������Ӧ�߳���ͻ���ͨ�� */
	CloseHandle(CreateThread(NULL, 0, CSysMainUi::SendpondProc, ((LPVOID)sockClient), 0, 0));

}

DWORD WINAPI CSysMainUi::SendpondProc(LPVOID lpPar)
{
	SOCKET pClientSocket = (SOCKET)lpPar;
	MySysTime *mySysTime = new MySysTime;
	mySysTime->nEvent = 22; //Э��ͷ

	while (TRUE)
	{	
		Sleep(5000);	
		memset(&mySysTime->system_time, 0, sizeof(mySysTime->system_time));
 
		//GetLocalTime(&mySysTime->system_time);		//�Ȼ�ȡ����ʱ��

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ViSet->DoModal();
}
