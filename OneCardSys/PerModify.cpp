// PerModify.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "PerModify.h"
#include "afxdialogex.h"


// CPerModify �Ի���

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

// CPerModify ��Ϣ�������


void CPerModify::OnBnClickedBtnselect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	InitData();	//clear();

	if (m_ID_String.IsEmpty() && m_ID_String == "" && m_Name_String.IsEmpty() && m_Name_String == "")
	{
		m_ShowTip = _T("��ѯ��������Ϊ�գ�");
		UpdateData(FALSE);

		return;
	}

	/************************************************************************/
	/* ��ѯ����                                                                     */
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
		m_Names = m_pRecordSet->GetCollect(_variant_t(_T("Name"))); //����
		m_XB = m_pRecordSet->GetCollect(_variant_t(_T("Sex")));
		m_Tel = m_pRecordSet->GetCollect(_variant_t(_T("Tel")));
		m_Type_string = m_pRecordSet->GetCollect(_variant_t(_T("RegType")));
		m_RegDateTime = m_pRecordSet->GetCollect(_variant_t(_T("RegDateTime"))); //�Ǽ�ʱ��
		m_LD = m_pRecordSet->GetCollect(_variant_t(_T("LD")));
		m_FH_String = m_pRecordSet->GetCollect(_variant_t(_T("FH")));
		m_UseLogOut_String = m_pRecordSet->GetCollect(_variant_t(_T("LogOut")));
		m_PicLen = m_pRecordSet->GetCollect(_variant_t("PictureLength"));  //ͼƬ��С
		varPicDate = m_pRecordSet->GetFields()->GetItem("PictureDate")->GetChunk(m_PicLen);//��ͼƬ����
		if (m_pRecordSet->State)  //������ݿ��¼�򿪾͹رռ�¼��
		{
			m_pRecordSet->Close(); //�رռ�¼�� 
		}

		/************************************************************************/
		/*  //�����ļ���                                                         */
		/************************************************************************/
		m_strPath = _T("C:\\YTPicture");  
		if (!PathIsDirectory(m_strPath))
		{
			CreateDirectory(m_strPath, 0);//�������򴴽�
		}
		m_strPath = _T("C:\\YTPicture\\ZHPictureReg");//ÿ�ΰ�ѡ��·����cspath����ֹcstring���ӣ�����
		if (!PathIsDirectory(m_strPath))
		{
			CreateDirectory(m_strPath, 0);//�������򴴽�	}��
		}
		m_strPath += _T("\\") + m_IDs + _T(".jpg");  //��Ƭ·��
		
		/************************************************************************/
		/* EJZToPicture()�����ݿ��еĶ�������Ƭ���ݴ浽����c��                  */
		/************************************************************************/
		if (EJZToPicture(m_strPath, m_PicLen, varPicDate) != TRUE)
		{
			m_ShowTip = _T("������Ƭ����ʧ�ܣ�");
		}		
		
		
		Ui_Show(m_strPath);  //��ʾ��Ƭ
		Sql.ReleaseBuffer();  //�ͷŻ���
		m_ShowTip =_T("����:  ") + m_Names + _T("     ���֤:  ") + m_Type_string + _T("    �Ǽ�ʱ��:  ") + m_RegDateTime;
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}

		m_ShowTip = _T(" ID: ") + m_ID_String + _T("\n ����: ") + m_Name_String + _T("\n ��ѯʧ�ܣ������²�ѯ");
	}

	////////////////////////��־////////////////////////////////////////////
	g_Action = _T("��ѯ�û�");
	OperRZ(g_Action); 
	////////////////////////��־///////////////////////////////////////

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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (m_IDs.IsEmpty())
	{
		m_ShowTip = _T("���֤Ϊ�գ��޸�ʧ��");
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
		m_ShowTip = _T(" ID: ") + m_ID_String + _T("\n  ����: ") + m_Name_String + _T("\n  �޸ĳɹ�");
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //�رռ�¼�� 
		}
	}
	catch (_com_error e)
	{
		m_ShowTip = _T(" ID: ") + m_ID_String + _T("\n ����: ") + m_Name_String + _T("\n �޸�ʧ�ܣ��������޸�");
		CATCH_ERROR;
	}	

	////////////////////////��־////////////////////////////////////////////
	g_Action = "�޸��û�";
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

	if (TRUE != Net_PreFindFaceInfo(lFaceLoginId))   //ɾ���������������ͼƬ
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
		m_ShowTip = _T("û���ҵ������֤��Ӧ������");

		UpdateData(FALSE);
		return FALSE;
	}

	if (TRUE != DeletePersonInfo(lFaceLoginId, (&pOutParam)->stPersonInfo.nPersonID))
	{
		m_ShowTip = _T("ɾ������ʧ�ܣ�������һ��");

		UpdateData(FALSE);
		return FALSE;
	}
	Net_CloseFindFaceInfo(lFaceLoginId);

	return TRUE;
}

void CPerModify::OnBnClickedBtnDele()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	CString m_strIdTmp = "";
	if (m_IDs.IsEmpty())
	{
		m_ShowTip = _T("���֤Ϊ�գ�ɾ��ʧ��");
		UpdateData(FALSE);

		return;
	}	
	try    //�鿴���֤�Ƿ������ݿ��У�����˵���������Ѿ�ǩ�����δ�Ǽ�
	{
		CString Sql;
		Sql.Format("SELECT ID FROM [FaceContCen].[dbo].[PersonInfo] WHERE RegType = '%s'", m_ID_String);
		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);
		_variant_t FP;
		FP = m_pRecordSet->GetCollect(_variant_t(_T("ID")));
		if (FP.vt != VT_NULL)//�����Ϊ��
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
		AfxMessageBox(_T("���֤����,����������"));

		return;
	}

	if (DropFacePicture(m_strIdTmp, m_lLoginID) != TRUE) //ɾ���������Ƭ
	{
		//return;
	}

	try    //ɾ�����ݿ⻧������
	{
		CString Sql;
		Sql.Format("DELETE  FROM [FaceContCen].[dbo].[PersonInfo] WHERE ID = '%s'", m_IDs);

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		Sql.ReleaseBuffer();
		m_ShowTip = _T(" ID: ") + m_ID_String + _T("\n  ����: ") + m_Name_String + _T("\n  ɾ���ɹ�");

		InitData();

		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //�رռ�¼�� 
		}
	}
	catch (_com_error e)
	{
		m_ShowTip = _T(" ID: ") + m_ID_String + _T("\n ����: ") + m_Name_String + _T("\n ɾ��ʧ�ܣ�������ɾ��");
		CATCH_ERROR;
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}
	}

	
	g_Action = "ɾ���û�";  //��־
	OperRZ(g_Action);
	
	OnBnClickedBtnseleall();   //����ȫѡˢ��
	InvalidateRect(NULL, FALSE);
	UpdateData(FALSE);
}


BOOL CPerModify::DeletePersonInfo(LONG lFaceLoginId, unsigned int nPersonID)   //ɾ�������ͼƬ
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_ListShowInfo.GetClientRect(&rect);

	m_ListShowInfo.SetExtendedStyle(m_ListShowInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListShowInfo.InsertColumn(0, _T("���֤��"), LVCFMT_LEFT, rect.Width() / 3, 6);
	m_ListShowInfo.InsertColumn(1, _T("����"), LVCFMT_LEFT, rect.Width() / 8, 1);
	m_ListShowInfo.InsertColumn(2, _T("�Ա�"), LVCFMT_LEFT, rect.Width() / 8, 2);
	m_ListShowInfo.InsertColumn(3, _T("�绰"), LVCFMT_LEFT, rect.Width() / 5, 3);
	m_ListShowInfo.InsertColumn(4, _T("¥����"), LVCFMT_LEFT, rect.Width() / 10, 4);
	m_ListShowInfo.InsertColumn(5, _T("�����"), LVCFMT_LEFT, rect.Width() / 10, 5);
	m_ListShowInfo.InsertColumn(6, _T("ID"), LVCFMT_LEFT, rect.Width() / 4, 0);

	m_ListShowInfo.SetBkColor((DWORD)RGB(255, 255, 255));   //ListCtrl����ɫ(��ɫ)
	m_ListShowInfo.SetTextColor((DWORD)RGB(255, 0, 130));      //ÿһ�е�������ɫ(��ɫ)

	
	CRect rect1;
	GetClientRect(&rect1);     //ȡ�ͻ�����С  
	old.x = rect1.right - rect1.left;
	old.y = rect1.bottom - rect1.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);

	// �쳣: OCX ����ҳӦ���� FALSE;  
	m_person_certificate_type = _T("���֤");	

	return TRUE; // unless you set the focus to a control
}

void CPerModify::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	Ui_Show(m_strPath);	
}


void CPerModify::OnBnClickedBtnseleall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //�رռ�¼�� 
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
			m_pRecordSet->Close(); //�رռ�¼�� 
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

	////////////////////////��־////////////////////////////////////////////
	g_Action = _T("��ѯ�����û�");
	OperRZ(g_Action);
	/////////////////////////////��־///////////////////////////////////////
}


void CPerModify::OnLvnItemchangedListshowinfo(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	m_ID_String = "";
	m_Name_String = "";
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;
	if (-1 != pNMListView->iItem)        // ���iItem����-1����˵�����б��ѡ��   
	{
		// ��ȡ��ѡ���б����һ��������ı�   
		m_ID_String = m_ListShowInfo.GetItemText(pNMListView->iItem, 0);
		m_Name_String = m_ListShowInfo.GetItemText(pNMListView->iItem, 1);

		UpdateData(FALSE);
		OnBnClickedBtnselect();
	}
}

void CPerModify::ReSize()
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

	// TODO: �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}


void CPerModify::OnBnClickedBtnzhperlogout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	CString m_strIdTmp = "";
	if (m_IDs.IsEmpty())
	{
		m_ShowTip = _T("���֤Ϊ�գ�ɾ��ʧ��");
		UpdateData(FALSE);

		return;
	}
	try    //�鿴���֤�Ƿ������ݿ��У�����˵���������Ѿ�ǩ�����δ�Ǽ�
	{
		CString Sql;
		Sql.Format("SELECT ID FROM [FaceContCen].[dbo].[PersonInfo] WHERE RegType = '%s'", m_ID_String);
		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);
		_variant_t FP;
		FP = m_pRecordSet->GetCollect(_variant_t(_T("ID")));
		if (FP.vt != VT_NULL)//�����Ϊ��
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
		AfxMessageBox(_T("���֤����,����������"));

		return;
	}

	if (DropFacePicture(m_strIdTmp, m_lLoginID) == TRUE) //ɾ���������Ƭ
	{
		m_ShowTip = _T("ɾ���������Ƭ�ɹ�");

		UpdateData(FALSE);
	}

	try
	{
		CString Sql = "";
		Sql.Format("UPDATE [FaceContCen].[dbo].[PersonInfo] SET LogOut = '%s' WHERE ID = '%s'", _T("��ס����ע��"), m_strIdTmp);
		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		m_ShowTip = _T("ס��ע���ɹ�");
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
		m_ShowTip = _T("ס��ע��ʧ��");

		return;
	}

	g_Action = "ס��ע��";  //��־
	OperRZ(g_Action);

	UpdateData(FALSE);
}
