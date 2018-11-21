// LogInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "LogInfo.h"
#include "afxdialogex.h"


// CLogInfo �Ի���

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


// CLogInfo ��Ϣ�������
BOOL CLogInfo::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

									// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CRect rect1;
	GetClientRect(&rect1);     //ȡ�ͻ�����С  
	old.x = rect1.right - rect1.left;
	old.y = rect1.bottom - rect1.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);

	
	CRect rect;
	m_listLogInfo.GetClientRect(&rect);

	m_listLogInfo.SetExtendedStyle(m_listLogInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listLogInfo.InsertColumn(0, _T("ID"), LVCFMT_LEFT, rect.Width() / 7, 0);
	m_listLogInfo.InsertColumn(1, _T("����"), LVCFMT_LEFT, rect.Width() / 12, 1);
	m_listLogInfo.InsertColumn(2, _T("����"), LVCFMT_LEFT, rect.Width() / 6, 2);
	m_listLogInfo.InsertColumn(3, _T("��ʼʱ��"), LVCFMT_LEFT, rect.Width() / 8, 3);
	m_listLogInfo.InsertColumn(4, _T("����ʱ��"), LVCFMT_LEFT, rect.Width() / 8, 4);
	m_listLogInfo.InsertColumn(5, _T("��Ϊ"), LVCFMT_LEFT, rect.Width() / 3, 5);
	m_listLogInfo.InsertColumn(6, _T("IP��ַ"), LVCFMT_LEFT, rect.Width() / 6, 6);
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLogInfo::OnBnClickedButton2()   //�鿴��־
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CLogInfo::OnBnClickedButton3()   //����Excel��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CLogInfo::OnBnClickedBtnview()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}


void CLogInfo::OnBnClickedBtnyl()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CDialogEx::OnCancel();
}


void CLogInfo::OnBnClickedBtnvinit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CLogInfo::OnBnClickedBtnckrz()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		CString XW; //��Ϊ
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






	//////////////////////////��־////////////////////////////////////////////
	//g_Action = "�鿴��־";

	//CTime tmp_tm = CTime::GetCurrentTime();
	//CString TimeEnd = tmp_tm.Format("%y��%m��%d��%Hʱ%M��%S��");
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

	///////////////////////////////��־///////////////////////////////////////
	UpdateData(FALSE);
}


void CLogInfo::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}

void CLogInfo::ReSize()
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


void CLogInfo::OnBnClickedBtnexcel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (0 == m_listLogInfo.GetItemCount())
	{
		MessageBox("û������", NULL, MB_OK);
		return;
	}
	CString Ip[1024], Name[1024], Type[1024], BeginTime[1024], EndTime[1024], XW[1024], IpAddr[1024];

	CString strFileName = _T("������������ڿ���ϵͳ V1.0 ��־");
	int i = 0;
	int j = 0;
	CString fileName = "c:\\" + strFileName + ".xls";//����·����d���̸�Ŀ¼
	
	CFile file(fileName, CFile::modeCreate | CFile::modeReadWrite | CFile::shareExclusive);
	CString header = _T("ID\t ����\t ����\t ��ʼʱ��\t ����ʱ��\t ��Ϊ\t IP��ַ\n");
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

	MessageBox("������Excel�ɹ�", "�ɹ�", MB_OK);
	
	
	////////////////////////��־////////////////////////////////////////////
	g_Action = "��־����excel��";

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
	/////////////////////////////��־///////////////////////////////////////
}


void CLogInfo::OnLvnItemchangedListloginfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CLogInfo::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	//CDC *pDC;
	//pDC = GetDC();
	//CRect  rect;
	//GetClientRect(&rect);   //��ȡ�ͻ�����С
	//Graphics graphics(pDC->m_hDC);
	////Graphics graphics(dc.m_hDC);
	//Image image(L"./res/rz2.jpg", TRUE);
	//graphics.DrawImage(&image, 0, 0, rect.right, rect.bottom);  //���Ʊ���
}
