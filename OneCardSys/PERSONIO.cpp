// PERSONIO.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "PERSONIO.h"
#include "afxdialogex.h"


// CPERSONIO �Ի���

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


// CPERSONIO ��Ϣ�������


void CPERSONIO::OnBnClickedBtnSelect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
		CString strAddr; //��Ϊ
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

			CString tmpOutTime = "";   //�뿪ʱ��
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


	//////////////////////////��־////////////////////////////////////////////
	g_Action = "�鿴��Ա��������Ϣ";

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

	///////////////////////////////��־///////////////////////////////////////
	UpdateData(FALSE);

}


void CPERSONIO::OnBnClickedBtnClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CDialogEx::OnCancel();
}


BOOL CPERSONIO::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	
	CRect rect1;              //���ڵȱ����Ŵ���С
	GetClientRect(&rect1);     //ȡ�ͻ�����С  
	old.x = rect1.right - rect1.left;
	old.y = rect1.bottom - rect1.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);

	m_Font.CreatePointFont(230, _T("Arial"), NULL);  //���������С
	m_static.SetFont(&m_Font, true);

	CRect rect;
	m_listLogInfo.GetClientRect(&rect);
	m_listLogInfo.SetExtendedStyle(m_listLogInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listLogInfo.InsertColumn(0, _T("����"), LVCFMT_LEFT, rect.Width() / 7, 0);
	m_listLogInfo.InsertColumn(1, _T("�Ա�"), LVCFMT_LEFT, rect.Width() / 7, 1);
	m_listLogInfo.InsertColumn(2, _T("ʶ��ʽ"), LVCFMT_LEFT, rect.Width() / 7, 2);
	m_listLogInfo.InsertColumn(3, _T("���֤"), LVCFMT_LEFT, rect.Width() / 7, 3);
	m_listLogInfo.InsertColumn(4, _T("�绰"), LVCFMT_LEFT, rect.Width() / 7, 4);
	m_listLogInfo.InsertColumn(5, _T("סַ"), LVCFMT_LEFT, rect.Width() / 5, 5);
	m_listLogInfo.InsertColumn(6, _T("����"), LVCFMT_LEFT, rect.Width() / 7, 6);
	m_listLogInfo.InsertColumn(7, _T("�뿪ʱ��"), LVCFMT_LEFT, rect.Width() / 6, 7);
	m_listLogInfo.InsertColumn(8, _T("���ƶ�"), LVCFMT_LEFT, rect.Width() / 8, 8);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CPERSONIO::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnClose();
}


void CPERSONIO::OnPaint()
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
	//Image image(L"./res/RZ.jpg", TRUE);
	//graphics.DrawImage(&image, 0, 0, rect.right, rect.bottom);  //���Ʊ���
}


void CPERSONIO::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}


void CPERSONIO::OnBnClickedBtnprint()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (0 == m_listLogInfo.GetItemCount())
	{
		MessageBox(_T("û������"), NULL, MB_OK);
		return;
	}
	CString Name, Sex, RenconMoth, IdNum, Tel, Addr, Type, XSD,Time;

	CString strFileName = _T("��Ա�������ѯ V1.0");
	int i = 0;
	int j = 0;
	CString fileName = _T("c:\\") + strFileName + _T(".xls");//����·����d���̸�Ŀ¼

	CFile file(fileName, CFile::modeCreate | CFile::modeWrite);

	CString header = _T("����\t �Ա�\t ʶ��ʽ\t ���֤\t �绰\t סַ\t ����\t ���ƶ� \tʱ��\n");
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

	MessageBox(_T("������Excel�ɹ�"), _T("�ɹ�"), MB_OK);

	////////////////////////��־////////////////////////////////////////////
	g_Action = _T("��Ա�����뵼��excel��");
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
	/////////////////////////////��־///////////////////////////////////////
}


//int sort_column; // ��¼�������
//
//bool method; // ��¼�ȽϷ���
//
// //?�ȽϺ���
//static int CALLBACK MyCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
//{
//
//	//?�Ӳ�������ȡ����Ƚ�lc����������
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
//	//?�Ƚϣ��Բ�ͬ���У���ͬ�Ƚϣ�ע���¼ǰһ����������һ��Ҫ�෴����
//	if (sort_column < 2)
//	{
//		//int�ͱȽ�
//		if (method)
//			return atoi(lp1) - atoi(lp2);
//		else
//			return atoi(lp1) - atoi(lp1);
//	}
//	else
//	{
//		//�����ͱȽ�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//sort_column = pNMLV->iSubItem;//�������

	//int count = m_listLogInfo.GetItemCount();


	////?ÿ�еıȽϹؼ��֣��˴�Ϊ����ţ�������кţ�����������Ϊ���� �ȽϺ����ĵ�һ��������
	//for (int i = 0; i < count; i++)
	//{
	//	m_listLogInfo.SetItemData(i, i);
	//}

	//m_listLogInfo.SortItems(MyCompareProc, (DWORD_PTR)&m_listLogInfo);//���� �ڶ��������ǱȽϺ����ĵ���������


	*pResult = 0;
}

void CPERSONIO::ReSize()
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

typedef struct tagColAtt
{
	int       nColIndex;
	CString   strColText;
	int       nPrintX;
	int       nSubItemIndex;
}COLATT;


void CPERSONIO::OnBnClickedBtnprinttoa4()   //��ӡ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	//��ʾ��ӡ�Ի������û����趨ֽ�Ŵ�С�ȡ� 
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

	//����У��еĸ��� 
	int nColCount  = pHeader->GetItemCount();
	int nLineCount = m_listLogInfo.GetItemCount();
	int ColOrderArray[100];
	COLATT ca[100];
	m_listLogInfo.GetColumnOrderArray(ColOrderArray, nColCount);
	int nColX = nXMargin*nCharWidth;

	//�������е���Ϣ��ȷ���б�������ݳ��ȡ� 
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
			AfxMessageBox(_T("�ֶ�̫�࣬�޷���һ���ڴ�ӡ�������ýϴ��ֽ��������ӡ�� "));
			return ;
		}
	}
	DOCINFO di;
	di.cbSize = sizeof(DOCINFO);
	di.lpszDocName = _T("��Ա��������Ϣ");
	di.lpszOutput = (LPTSTR)NULL;
	di.lpszDatatype = (LPTSTR)NULL;
	di.fwType = 0;
	StartDoc(pd.hDC, &di);
	StartPage(pd.hDC);
	//TextOut(pd.hDC, nHorRes / 3, nYMargin, _T("��Ա��������Ϣ"), strlen(_T("��Ա��������Ϣ")));

	//�������еĿ�ȣ���ʹ�����ں���Ĵ�ӡ���ʱ�����ȵĴ�ӡ��ֽ�ϡ� 
	int space = (nHorRes - nXMargin*nCharWidth - nColX) / (nColCount - 1);
	for (int i = 1; i < nColCount; i++)
	{
		ca[i].nPrintX += i*space;
	}

	//����б��� 
	for (int i = 0; i < nColCount; i++)
	{
		TextOut(pd.hDC, ca[i].nPrintX, nYMargin,ca[i].strColText, strlen(ca[i].strColText));
	}
		
	int nMaxLinePerPage = nVerRes / nCharHeight - 3;
	int nCurPage = 1;

	//������е����� 
	for (int i = 0; i < nLineCount; i++)
	{
		for (int j = 0; j < nColCount; j++)
		{
			if (i + 1 - (nCurPage - 1)*nMaxLinePerPage > nMaxLinePerPage)
			{
				//�µ�һҳ 
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
	DeleteDC(pd.hDC);	//��ӡ���� 

	AfxMessageBox(_T("��ӡ�ɹ�"));

	return;
}
