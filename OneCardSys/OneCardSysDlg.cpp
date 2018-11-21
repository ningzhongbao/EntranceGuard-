
// OneCardSysDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "OneCardSysDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COneCardSysDlg �Ի���



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

		//m_bstrConn = "Driver=SQL Server;Server=LAPTOP-E18QACSO;Database = FaceContCen"; //���ӱ��������ݿ�
		m_bstrConn = "Driver=SQL Server;Server=SHYT;Database = FaceContCen"; //�����������ݿ�

		hRes = m_pConnection->Open(m_bstrConn, _T("sa"), _T("a1234"), adModeUnknown);		
		
		m_pRecordSet.CreateInstance(__uuidof(Recordset));
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("SQL���ݿ�����ʧ��"));

		return FALSE;
	}

	return TRUE;
}

// COneCardSysDlg ��Ϣ�������

BOOL COneCardSysDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��	

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//if(TRUE != ConnectionSql()) //����sql  
	//{ 
	//	PostQuitMessage(0);
	//	
	//	return FALSE;
	//}

	User = 0;  //��½�û���
	Pwd = "";  //���� 
	UpdateData(TRUE);  //


	m_Font.CreatePointFont(230, "Arial", NULL);  //���������С
	m_static.SetFont(&m_Font, true);

	m_strUser = "1";   
	m_strPwd = "1";

	//m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	UpdateData(FALSE); //���µ�����


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void COneCardSysDlg::OnPaint()
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
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDC *pDC;
		pDC = GetDC();
		CRect  rect;
		GetClientRect(&rect);   //��ȡ�ͻ�����С
		Graphics graphics(pDC->m_hDC);
		//Graphics graphics(dc.m_hDC);
		Image image(L"./res/BG_Login.jpg", TRUE);
		graphics.DrawImage(&image, 0, 0, rect.right, rect.bottom);  //���Ʊ���

		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	if (TRUE != ConnectionSql()) //����sql  
	{
		//PostQuitMessage(0);
		return;
	}

	UpdateData(TRUE);

	if (User == 0)
	{
		try   //��ѯ���ݿ��ȡ�û���������
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


	if (atoi(m_strUser) != User || m_strPwd != Pwd)  //��½
	{
		MessageBox("�û�ID���������\n ���������룡", "��¼ʧ�ܣ�", MB_OK | MB_ICONERROR);
	}
	else
	{
		this->ShowWindow(SW_HIDE);
		g_UserId = User;

		g_Action = "��½";   //��½��־��¼
		OperRZ(g_Action);

		CSysMainUi m_SysUiMain;   //ϵͳ������
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

	/////////////////////////////��־///////////////////////////////////////
}

void COneCardSysDlg::OnBnClickedBtncannel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	PostQuitMessage(0);
}


void COneCardSysDlg::OnEnChangeEditUser()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
//BOOL COneCardSysDlg::InitLoginParams() //�����ϴ������ʼ��
//{
//	m_lLoginID = 0;
//	m_Str_Ip = "192.168.35.6";
//	m_int_port = 3000;
//	m_Str_User = "admin";
//	m_Str_Pwd = "admin123";
//
//	Net_Init(disconnect_callback, (LDWORD)(void*)this); //��ʼ��sdk��
//
//	return TRUE;
//}
//
//BOOL COneCardSysDlg::LogIn()
//{
//	m_lLoginID = Net_LoginDevice(m_Str_Ip.GetBuffer(), m_int_port,
//		m_Str_User.GetBuffer(), m_Str_Pwd.GetBuffer(), NULL, &m_nError); //��½
//
//	if (0 >= m_lLoginID)
//	{
//		MessageBox(_T("����ģ������ʧ�ܣ�������������豸�Ƿ�����"), _T("��¼��ʾ..."), MB_ICONHAND);
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
//			// �����������Դ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//LogOut();

	CDialogEx::OnClose();
}
