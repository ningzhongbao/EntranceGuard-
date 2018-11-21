// PerReg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "PerReg.h"
#include "afxdialogex.h"

BOOL bFlageReg = TRUE;       //����һ����־����ֹ��ѭ��
CString  g_FilePathReg = ""; //ȫ���ļ���
INT g_DynamicUp = 0;          //��̬�ϴ�ȫ�ֱ�־
CPerReg *g_cPerReg = NULL;
int g_B = 0;
// CPerReg �Ի���

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
	m_COM_XB_String = _T("��");
	g_FilePathReg = "";
	m_IdCard_String = (_T(""));

	/*CStatic* pStatic = (CStatic*)GetDlgItem(IDC_Picture_Show);
	CRect lRect;
	pStatic->GetClientRect(&lRect);
	pStatic->GetDC()->FillSolidRect(lRect.left, lRect.top, lRect.Width(), lRect.Height(), RGB(240, 240, 240));

	InvalidateRect(nullptr, FALSE);*/
}

// CPerReg ��Ϣ�������

BOOL CPerReg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_COM_XB_String = _T("��");
	m_LD_String = "00";
	m_FH_String = "11";
	m_playHandle = 0;  //��ͼ���

	CRect rect1;
	GetClientRect(&rect1);     //ȡ�ͻ�����С  
	old.x = rect1.right - rect1.left;
	old.y = rect1.bottom - rect1.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}

BOOL CPerReg::CheckLoginOk()
{
	if (0 < m_lLoginID)
		return TRUE;
	MessageBox(_T("��δ��¼��"), "", MB_OK);
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
	if (dwEventType == EVENT_SP_FACE_SNAP_PART)   // ��������ͼ
	{
		STU_EVENT_FACE_SNAP_WHOLE stu = { 0 };
		memcpy(&stu, pEventInfo, sizeof(STU_EVENT_FACE_SNAP_WHOLE));

		// pBuffer ��ͼƬ���ݣ�dwBufSize ��ͼƬ���ݴ�С		 	
		CString csPath = _T("C:\\YTPicture");
		if (!PathIsDirectory(csPath))
		{
			CreateDirectory(csPath, 0);//�������򴴽�
		}
		csPath = _T("C:\\YTPicture\\ZHPictureReg");//ÿ�ΰ�ѡ��·����cspath����ֹcstring���ӣ�����

		if (!PathIsDirectory(csPath))
		{
			CreateDirectory(csPath, 0);//�������򴴽�	}��
		}
		CString strTimeFile;
		CTime tm;          //��ȡϵͳʱ��
		tm = CTime::GetCurrentTime();
		strTimeFile = tm.Format("FZ%y%m%d%H%M%S");

		csPath += _T("\\") + strTimeFile + _T("E") + _T(".jpg");

		FILE *pFilePath = fopen(csPath, _T("w+b")); //Ч�ʵ�
		if (NULL != pFilePath)
		{
			fwrite(pBuffer, 1, dwBufSize, pFilePath);	//д���ļ�		
			fclose(pFilePath);

			g_FilePathReg = csPath;
		}
		else
		{
			g_FilePathReg = "";
			//MessageBox(NULL, _T("ץȡʧ�ܣ�����һ�Σ�"), NULL, MB_ICONERROR);
		}	
	}
	
	return 0;
}


BOOL CPerReg::StartRealStream()
{
	// ͼƬ���ݴ����� realload_callback �ص���
	if (m_ZPLoginID <= 0)
	{
		MessageBox("δ��¼", "��ʾ", MB_ICONERROR);

		return FALSE;
	}

	int nChannel = 0;
	m_playHandle = Net_RealLoadPicture(m_ZPLoginID, nChannel, EVENT_SP_FACE_SNAP_PART, 1,
		realload_callbackReg, NULL, NULL);
	if (0 >= m_playHandle)
	{
		MessageBox(_T("����������������ȡ��������.\n"), NULL, MB_ICONERROR);

		Net_LogoutDevice(m_ZPLoginID);

		return FALSE;
	}

	return TRUE;
}


void CPerReg::OnBnClickedBtnOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	if (!StartRealStream())
	{
		m_RegTip = _T("�ռ�����ʧ�ܡ�");

		return;
	}
	else
	{
		m_RegTip = _T("���ڲɼ�����...");

		UiTimer = SetTimer(1, 100, NULL);  //������ʱ����ʵʱˢ�½���

		CWnd *pBtn1 = GetDlgItem(IDC_Btn_Open);
		pBtn1->EnableWindow(FALSE);
		CWnd *STReg = GetDlgItem(IDC_Btn_STReg);
		STReg->EnableWindow(FALSE);
		
		//g_DynamicUp = 1;   //��̬�ɼ���Ϊ1
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (TRUE != CheckLoginOk())    //����Ƿ��½�����
		return;
	
	if (m_IdCard_String == "" || m_IdCard_String.IsEmpty())
	{
		m_RegTip = _T("���������֤��");

		UpdateData(FALSE);
		return ;
	}
	
	int nLen = m_IdCard_String.GetLength();
	for (int i = 0; i < nLen; i++)
	{
		if (!(m_IdCard_String.GetAt(i) >= '0' && m_IdCard_String.GetAt(i) <= '9' || m_IdCard_String.GetAt(i) >= 'A' && m_IdCard_String.GetAt(i) <= 'Z'))
		{
			MessageBox(_T("���֤��ʽ����"), _T("����������"), 0);
			return;
		}
	}
	if (m_Name_String == "" || m_Name_String.IsEmpty())
	{
		m_RegTip = _T("����Ϊ�ա�");

		UpdateData(FALSE);
		return ;
	}
	if (m_COM_XB_String == "" || m_COM_XB_String.IsEmpty())
	{
		m_RegTip = _T("�������Ա�");

		UpdateData(FALSE);
		return ;
	}

	/************************************************************************/
	/*                            ��֤����                                   */
	/************************************************************************/
	/*g_strPictureId = m_ID_String;
	g_strFacePath = m_csFileName;

	CWintCheckVido m_cWintCheck;
	m_cWintCheck.DoModal();

	if (g_ReconPass != 1)
	{
		m_RegTip = _T("��֤���鲻ͨ����������!");
		UpdateData(FALSE);

		return;
	}
	else
	{
		m_RegTip = g_strPictureId +  _T("��֤����ͨ��");
	}*/

	/************************************************************************/
	/*                            ������ͼƬת���ɶ�����                    */
	/************************************************************************/
	varBLOB = PictureToEJZ(m_csFileName); 
	if (0 == varBLOB.iVal && g_PictureLen > 0)
	{
		m_RegTip = _T("����ͼƬת���ɶ�����ʧ�ܣ�������");
		return;
	}
	m_nFileLen = g_PictureLen; //��ȡ��Ƭ�Ķ��������ݴ�С


	/************************************************************************/
	/*                           �����ϴ������                             */
	/************************************************************************/
	//if (g_DynamicUp != 1)  //����1����̬�ϴ�
	//{
	//
	//}
	if (!UpFacePicture(m_ID_String, m_lLoginID, m_csFileName))   
	{
		return;
	}

	/************************************************************************/
	/*                       sql����                                        */
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
		m_pRecordSet->PutCollect("LogOut",_T("ס������"));
		if (m_nFileLen > 0)   //��ͼƬ�浽sql
		{
			m_pRecordSet->PutCollect("PictureLength", m_nFileLen);
			m_pRecordSet->GetFields()->GetItem("PictureDate")->AppendChunk(varBLOB);
		}

		m_pRecordSet->Update();  //��¼���µ�sql
		m_pRecordSet->Close();

		m_RegTip = _T(" ID: ") + m_ID_String + _T("\n ;  ����: ") + m_Name_String + _T("\n ;  ע��ɹ�");

		ClearScreen();  //����
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->CancelUpdate();  //�ر�updae�쳣
			m_pRecordSet->Close();     //�رռ�¼��
		}
		m_RegTip = _T(" ID: ") + m_ID_String + _T("\n ����: ") + m_Name_String + _T("\n ע��ʧ�ܣ�������ע��");
		CATCH_ERROR;
	}
	
	/************************************************************************/
	/* ��־                                                                  */
	/************************************************************************/
	g_Action = "ע���û�";    //��־
	OperRZ(g_Action);

	/************************************************************************/
	/* ��ť����                                                                     */
	/************************************************************************/
	CWnd *STReg = GetDlgItem(IDC_Btn_STReg);  //��̬�ɼ�����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pRecordSet->State)
	{
		m_pRecordSet->Close(); //�رռ�¼�� 
	}

	CDialog::OnCancel();
}




void CPerReg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}

void CPerReg::ReSize()
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



void CPerReg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
	{
		ExecuPicture();//ˢ�½�������ͼƬ++	
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
		if (IDYES == MessageBox(_T("ȷʵʹ�ô�������"), _T("ȷ��"), MB_YESNO | MB_ICONQUESTION))
		{
			if (0 >= m_playHandle)
			{
				MessageBox(_T("δ��¼��"), _T("Tip"), MB_ICONERROR);

				return FALSE;
			}
			bFlageReg = TRUE;

			m_Path_String = g_FilePathReg;  //����edit·��
			Net_StopLoadPicture(m_playHandle); //ֹͣ������������
			m_csFileName = g_FilePathReg;
			KillTimer(1);  //������ʱ��

			
			m_RegTip = _T("��Ƭ�ɼ��ɹ��������������Ϣ�����·�ע�ᰴťע��");

			int iEndPos = 0;
			ID = m_csFileName.Mid(m_csFileName.ReverseFind('\\') + 1);
			iEndPos = ID.ReverseFind('.');
			ID = ID.Left(iEndPos);
			m_ID_String = ID;


			CWnd *pBtn1 = GetDlgItem(IDC_Btn_Open);  //��̬�ɼ�����
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

			m_RegTip = _T("������ѡȡ����ͼƬ");
		}
	}

	UpdateData(FALSE);
	return FALSE;
}


void CPerReg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CDC *pDC;
	pDC = GetDC();
	CRect  rect;
	GetClientRect(&rect);   //��ȡ�ͻ�����С
	Graphics graphics(pDC->m_hDC);
	//Graphics graphics(dc.m_hDC);
	Image image(L"./res/BG_BKALL.jpg", TRUE);
	graphics.DrawImage(&image, 0, 0, rect.right, rect.bottom);  //���Ʊ���
}


void CPerReg::OnBnClickedBtnStreg()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog dlg(TRUE);           ///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���  
	if (dlg.DoModal() == IDOK)
		m_csFileName = dlg.GetPathName();
	else
		m_csFileName.Empty();

	CString strExt(_T(".jpg"));
	if (m_csFileName.IsEmpty() || -1 == m_csFileName.Find(strExt.GetBuffer(0)))
	{
		AfxMessageBox(_T("����jpg����ͼƬ"));
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
		MessageBox("�ļ������ȱ���С�ڵ���12λ��", _T("��ʾ"), MB_ICONERROR);
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

		ID = _T("FP") + strFileName + _T("E");       //�Զ�����Э��ͷfz��������ô��Э��ͷ
	}
Label:
	m_ID_String += ID;
	m_Path_String = m_csFileName;  //��ͼƬ����·���������edit
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
//BOOL CPerReg::PerCardCheck()        //��֤����
//{
//	// 1. �ϴ��ȶ�������
//	if (!UpFacePicture(m_ID_String, m_ZPLoginID, m_csFileName))
//	{
//		return FALSE;
//	}
//
//
//	// 2. ������Ƶ���
//	tmpWC.Create(IDD_DIAWITCHECKVIDO, this);
//	tmpWC.ShowWindow(SW_SHOW);
//
//
//	// 3. ��ȡ�ԱȽ��
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
//		if (g_cPerReg->m_ID_String == g_ReconBackId)  //id����ҷ�������70��
//		{
//			// 4. �ر���Ƶ��ɾ����������������ȡ���
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

BOOL g_bFlag = false;  //���֤�Ķ�����ʼ��

void CPerReg::IDCardInit()
{
	CString sMsg, sMsg2;
	unsigned int uiCurrBaud;
	int nRet, nRet2;
	m_iPort = 0;
	nRet = Syn_FindUSBReader();
	if (nRet == 0)
	{
		sMsg = "û���ҵ�������";
		g_bFlag = false;
	}
	else
	{
		m_iPort = nRet;
		Beep(4000, 200);
		if (nRet > 1000)
		{
			sMsg.Format("������������USB�˿� %d", nRet);
		}
		else
		{
			Sleep(200);
			nRet2 = Syn_GetCOMBaud(nRet, &uiCurrBaud);
			sMsg2.Format("%u", uiCurrBaud);
			sMsg.Format("�����������ڴ��� %d,��ǰSAM������Ϊ %u", nRet, uiCurrBaud);
		}
		g_bFlag = true;
	}
	m_StatVal.SetWindowText(sMsg);
}

void CPerReg::OnBnClickedBtntwocard()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	IDCardInit(); //���֤�Ķ�����ʼ��
	
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
		m_StatVal.SetWindowText(_T("���ʼ����ȷ�϶�������������"));
		return;
	}

	CString csPath = _T("C:\\YTPicture");
	if (!PathIsDirectory(csPath))
	{
		CreateDirectory(csPath, 0);//�������򴴽�
	}
	csPath = _T("C:\\YTPicture\\ZHPicture");//ÿ�ΰ�ѡ��·����cspath����ֹcstring���ӣ�����
	if (!PathIsDirectory(csPath))
	{
		CreateDirectory(csPath, 0);//�������򴴽�	
	}

	char   szBuffer[_MAX_PATH] = "C:\\YTPicture\\ZHPicture";
	Syn_SetPhotoPath(2, szBuffer);	//������Ƭ·��	iOption ·��ѡ��	0=C:	1=��ǰ·��	2=ָ��·��
									//cPhotoPath	����·��,����iOption=2ʱ��Ч
	iPhototype = 1;
	Syn_SetPhotoType(1); //0 = bmp ,1 = Jpg , 2 = base64 , 3 = WLT ,4 = ������
	Syn_SetPhotoName(2); // ������Ƭ�ļ��� 0=tmp 1=���� 2=���֤�� 3=����_���֤�� 

	Syn_SetSexType(1);	// 0=���д洢������	1=����֮�������,�С�Ů��δ֪
	Syn_SetNationType(1);// 0=���д洢������	1=����֮������� 2=����֮���"��"
	Syn_SetBornType(3);			// 0=YYYYMMDD,1=YYYY��MM��DD��,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD
	Syn_SetUserLifeBType(1);	// 0=YYYYMMDD,1=YYYY��MM��DD��,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD
	Syn_SetUserLifeEType(1, 1);	// 0=YYYYMMDD(��ת��),1=YYYY��MM��DD��,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD,
								// 0=���� ��ת��,	1=����ת��Ϊ ��Ч�ڿ�ʼ+50��
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
				sMsg = _T("��ȡ���֤��Ϣ�ɹ�!");
				m_StatVal.SetWindowText(sMsg);
				sMsg.Format(_T("%s"), idcardData.Name); //name
				m_EditName.SetWindowText(sMsg);
				sMsg.Format(_T("%s"), idcardData.Sex); //sex
				sprintf(szTemp, _T("%s"), idcardData.Sex);
				if (0 == strcmp(szTemp, _T("��")))
				{
					m_ComBoxSex.SetCurSel(0);
				}
				else if (0 == strcmp(szTemp, _T("Ů")))
				{
					m_ComBoxSex.SetCurSel(1);
				}

				//sMsg.Format("%s", idcardData.Address);
				//m_vEdit4.SetWindowText(sMsg);
				sMsg.Format("%s", idcardData.IDCardNo);
				m_EditIDNo.SetWindowText(sMsg);
		
				if (nRet == 1)
				{
					sMsg = _T("������Ƭʧ��");
				}
				else
				{
					CString strTimeFile;    //��Ƭ���ļ������õ�ʱ������
					CTime tm;          //��ȡϵͳʱ��
					tm = CTime::GetCurrentTime();
					strTimeFile = tm.Format("%y%m%d%H%M%S");

					sMsg.Format(_T("%s"), idcardData.PhotoFileName);
					sprintf(szTempPath, _T("%s"), idcardData.PhotoFileName);  //old name XXX.Jpg
					sMsg = sMsg.Left(sMsg.Find('.'));
					CString strTemp = _T("C:\\YTPicture\\ZHPicture\\FZ");

					sMsg = sMsg.Right(sMsg.GetLength() - 1 - sMsg.ReverseFind('\\')); //���֤��
					sMsg = strTimeFile + _T("E") + _T(".jpg");

					m_ID_String = _T("FZ") + strTimeFile + _T("E");
					m_Edit_ID_Values.SetWindowTextA(m_ID_String);	 //id��				

					sMsg = strTemp + sMsg;
					m_csFileName = sMsg; //·��
					strPath = sMsg;

					USES_CONVERSION;
					path = sMsg.GetBuffer(sMsg.GetLength() + 1);


					if (rename(szTempPath, path) == 0)
					{
						m_StatVal.SetWindowText("������Ƭ�ɹ���");
					}
					else
					{
						if (remove(szTempPath) == 0)
						{
							m_StatVal.SetWindowText("������Ƭ�ɹ���");
						}
						else
						{
							m_StatVal.SetWindowText("������Ƭʧ�ܣ�");
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
				sMsg = "��ȡ���֤��Ϣ����!";
				m_StatVal.SetWindowText(sMsg);
			}
		}
	}
	else
	{
		sMsg = "�򿪶˿ڴ���";
		m_StatVal.SetWindowText(sMsg);
	}
	Syn_ClosePort(m_iPort);
}
