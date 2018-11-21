// GetInfoPer.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "GetInfoPer.h"
#include "afxdialogex.h"

///////////////////////////ȫ�ֱ���/////////////////////////////////////
static int g_nCount = 0;     //ȫ�ֱ�������ͼƬ����
CString    g_strPictureShow; //ui_show·����
DWORD      g_nPicSize = 0;   //ͼƬ��С
CString    filePathName;     //�ļ�·����
///////////////////////////////////////////////////////////////////////



// CGetInfoPer �Ի���

IMPLEMENT_DYNAMIC(CGetInfoPer, CDialogEx)

CGetInfoPer::CGetInfoPer(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GETPERSON, pParent)
	, m_strPathName(_T(""))
{
	//InitLoginParams(); //��ʼ���������
	m_playHandle = 0;  //��ͼ���
	//LogIn();//��¼	

	CString strJQ = _T("C:\\YTPicture");	//��ȡ�ַ����������ļ���
	if (!PathIsDirectory(strJQ))
	{
		CreateDirectory(strJQ, 0);//�������򴴽� ,һ��Ŀ¼
	}
	strJQ = _T("C:\\YTPicture\\ZPPictureFace");
	if (!PathIsDirectory(strJQ))
	{
		CreateDirectory(strJQ, 0);//�������򴴽�������Ŀ¼
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
		/* CDC *pDC;
		pDC = GetDC();
		CRect  rect;
		GetClientRect(&rect);   //��ȡ�ͻ�����С
		Graphics graphics(pDC->m_hDC);
		//Graphics graphics(dc.m_hDC);
		Image image(L"./res/BG_BKALL.jpg", TRUE);
		graphics.DrawImage(&image, 0, 0, rect.right, rect.bottom);  *///���Ʊ���

		CDialogEx::OnPaint();
	}
}
//
//// CGetInfoPer ��Ϣ�������
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
//	Net_Init(disconnect_callback, (LDWORD)(void*)this); //��ʼ��sdk��
//
//	return TRUE;
//}
//
//
//BOOL CGetInfoPer::LogIn()
//{						  
//	m_lLoginID = Net_LoginDevice(m_Str_Ip.GetBuffer(), m_int_port,
//		                         m_Str_User.GetBuffer(),m_Str_Pwd.GetBuffer(), NULL, &m_nError); //��½
//
//	if (0 >= m_lLoginID)
//	{
//		MessageBox(_T("����ʶ���ܵ�¼ʧ�ܣ��������"), _T("��¼��ʾ..."), MB_ICONHAND);
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
//			// �����������Դ
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
	if (dwEventType == EVENT_SP_FACE_SNAP_PART)   // ��������ͼ
	{		
		STU_EVENT_FACE_SNAP_WHOLE stu = { 0 };
		memcpy(&stu, pEventInfo, sizeof(STU_EVENT_FACE_SNAP_WHOLE));
		g_strPictureShow = "";
		// pBuffer ��ͼƬ���ݣ�dwBufSize ��ͼƬ���ݴ�С			

		CString csPath;
		csPath = filePathName;  //ÿ�ΰ�ѡ��·����cspath����ֹcstring���ӣ�����

		if (!PathIsDirectory(csPath))
		{
			CreateDirectory(csPath, 0);//�������򴴽�
		}

		//�ļ��Ѿ�����
		CString filePath = "";

		CString strTime = "";   //��ȡϵͳʱ��
		SYSTEMTIME systime;
		GetLocalTime(&systime);//����ʱ��
		strTime.Format("ZH%2d%2d%2d%2d%2d%2d", systime.wMonth, systime.wDay, systime.wHour, systime.wMinute, systime.wSecond, systime.wMilliseconds);

		csPath += _T("\\") + strTime + _T("E") + _T(".jpg");
		FILE *pFilePath = fopen(csPath, "wb+"); //Ч�ʵ�
		if (NULL != pFilePath)
		{
			fwrite(pBuffer, 2, dwBufSize, pFilePath);	//д���ļ�		
			g_strPictureShow = csPath;//��ȡ�ļ���,Ϊ���ڽ�������ʾ����������������			
			fclose(pFilePath);
		}	
	}

	return 0;
}


BOOL CGetInfoPer::StartRealStream()
{
	// ͼƬ���ݴ����� realload_callback �ص���
	int nChannel = 0;

	m_playHandle = Net_RealLoadPicture( m_ZPLoginID, nChannel, EVENT_SP_FACE_SNAP_PART, 1,
									    realload_callback, NULL, NULL);
	if (0 >= m_playHandle)
	{
		MessageBox(_T("����������������ȡ��������.\n"), NULL, MB_ICONERROR);

		Net_LogoutDevice(m_ZPLoginID);

		return FALSE;
	}

	return TRUE;
}

void CGetInfoPer::OnBnClickedBtnbegin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (filePathName.IsEmpty())
	{
		MessageBox(_T("����ѡ�񱣴�ͼƬ·��"), NULL, MB_ICONERROR);

		return ;
	}

	if (!StartRealStream())
	{
		MessageBox(_T("�ռ�����ʧ��"), NULL, MB_ICONERROR);
		
		return ;
	}
	else
	{		
		MessageBox(_T("���ڲɼ�����"), NULL, MB_OK);
		
		UiTimer = SetTimer(1, 100, NULL);  //������ʱ����ʵʱˢ�½���
	}
	
	CWnd *pBtn1 = GetDlgItem(IDC_BUTTON1);
	pBtn1->EnableWindow(FALSE);
	CWnd *pBegin = GetDlgItem(IDC_BtnBegin);//�ɹ������ÿ�ʼ��ť������
	pBegin->EnableWindow(FALSE);
	CWnd *pStop = GetDlgItem(IDC_BtnStop);
	pStop->EnableWindow(TRUE);
}


void CGetInfoPer::OnBnClickedBtnstop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ֹͣ����
	if (0 >= m_playHandle)
	{
		MessageBox(_T("���ȵ����ʼ��ť"), _T("Tip"), MB_ICONERROR);
		return;
	}
	Net_StopLoadPicture(m_playHandle);

	KillTimer(1);  //������ʱ��

	CWnd *pStop = GetDlgItem(IDC_BtnStop);
	pStop->EnableWindow(FALSE);
	CWnd *pBegin = GetDlgItem(IDC_BtnBegin);
	pBegin->EnableWindow(TRUE);
	CWnd *pBtn1 = GetDlgItem(IDC_BUTTON1);
	pBtn1->EnableWindow(TRUE);
}


void CGetInfoPer::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	TCHAR           szFolderPath[MAX_PATH] = { 0 };
	CString         strFolderPath = TEXT("");

	BROWSEINFO      sInfo;
	::ZeroMemory(&sInfo, sizeof(BROWSEINFO));
	sInfo.pidlRoot = 0;
	sInfo.lpszTitle = _T("��ѡ������ͼƬ�洢·��");
	sInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_DONTGOBELOWDOMAIN;
	sInfo.lpfn = NULL;

	// ��ʾ�ļ���ѡ��Ի���  
	LPITEMIDLIST lpidlBrowse = ::SHBrowseForFolder(&sInfo);
	if (lpidlBrowse != NULL)
	{
		// ȡ���ļ�����  
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
		MessageBox(_T("ѡȡ�ļ�·������ȷ��������ѡȡ"), NULL, MB_OK);

		return;
	}
	if (!strFolderPath.IsEmpty())
	{
		m_strPathName = strFolderPath;  //����edit·��
	}

	filePathName = m_strPathName;   //�ļ���·��
	
	CWnd *pStop = GetDlgItem(IDC_BtnBegin);
	pStop->EnableWindow(TRUE);

	UpdateData(FALSE);
}

void CGetInfoPer:: Ui_Show()
{
	CString strExt(".jpg");
	if (g_strPictureShow.IsEmpty() || -1 == g_strPictureShow.Find(strExt.GetBuffer(0)))
		return;
	
	m_strPathName = g_strPictureShow;  //����edit·��

	CImage image;
	image.Load(g_strPictureShow);
	
	//��������������Ҫ�����ǣ���ȡ�Ի��������Picture Control��width��height��
	//�����õ�ͼƬ����rectPicture������ͼƬ����rectPicture��ͼƬ���д���
	//������ͼƬ���Ի�����Picture Control����
	CRect rectControl;                        //�ؼ����ζ���
	CRect rectPicture;                        //ͼƬ���ζ���

	int x = image.GetWidth();
	int y = image.GetHeight();
	(&m_ShowPicture)->GetClientRect(rectControl);

	CDC *pDc = (&m_ShowPicture)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(),
		CSize((int)rectControl.Width(),
		(int)rectControl.Height()));

	(&m_ShowPicture)->SetBitmap(NULL);

	//�������ַ������ɻ���ͼƬ
	image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); //��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������

	image.Destroy();
	(&m_ShowPicture)->ReleaseDC(pDc);

	UpdateData(FALSE);
}

void CGetInfoPer::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
		case 1:
		   {
			 Ui_Show();//ˢ�½�������ͼƬ
		   }
		   break;
		default:
			break;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CGetInfoPer::OnBnClickedCannel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ֹͣ����
	if (m_playHandle > 0)
	{
		Net_StopLoadPicture(m_playHandle);
		KillTimer(1);  //������ʱ��
	} 

	g_nCount = 0;     //ȫ�ֱ�������ͼƬ����
	g_strPictureShow = ""; //ui_show·����
	g_nPicSize = 0;   //ͼƬ��С
	filePathName = "";     //�ļ�·����	
	m_strPathName = _T("�ļ�·��");
	

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

	// TODO: �ڴ˴������Ϣ����������

	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}

void CGetInfoPer::ReSize()
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

BOOL CGetInfoPer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect1;
	GetClientRect(&rect1);     //ȡ�ͻ�����С  
	old.x = rect1.right - rect1.left;
	old.y = rect1.bottom - rect1.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);




	



	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
