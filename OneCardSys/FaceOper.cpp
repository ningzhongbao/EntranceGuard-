// FaceOper.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "FaceOper.h"
#include "afxdialogex.h"

CFaceOper *g_FaceOper = nullptr;
int g_KillThread = 0; //�ж��̵߳�ִ��

// CFaceOper �Ի���

IMPLEMENT_DYNAMIC(CFaceOper, CDialogEx)

CFaceOper::CFaceOper(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIAUPFACEPICTURE, pParent)
	, m_Name_ID(_T(""))	
	, m_static_string_person_page(_T(""))
	, m_edit_person_page(_T(""))
	, m_ShowTip_String(_T(""))
{
	//InitLoginParams(); //��ʼ���������
	g_FaceOper = this;

	m_pfaceGroupArray = NULL;
	//LogIn();//��¼	
		
	//ˢ����Ա������Ϣ
	m_nTotalPersonCount = 0;
	m_nTotalPersonPage = 0;
	m_nCurPersonPage = 0;
	m_nCurPersonIndex = 0;
	m_nCurPersonCount = 0;
	m_nOffsetPerson = 0;
	memset(&m_stPersonFaceInfoArr, 0x00, sizeof(STU_PERSON_FACE_INFO) * PER_PERSON_PAGE_NUM);

	//�ϴ�������Ĭ������
	m_person_county = _T("�й�");
	m_person_sex = _T("male");
	m_person_certificate_type = _T("���֤");
	m_person_county = _T("�й�");
	m_person_birth = _T("2037-12-31");
	m_person_city = _T("�人��");
	m_person_certificate_id = _T("00000000000000");
	m_person_province = _T("����ʡ");
	m_nCurPersonCount = 0;

}

CFaceOper::~CFaceOper()
{
	//LogOut();
}

void CFaceOper::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_list_face_group);
	DDX_Control(pDX, IDC_STATIC_PICTURE, m_Picture);
	DDX_Text(pDX, IDC_EDIT_ID, m_Name_ID);
	DDX_Control(pDX, IDC_LIST2, m_list_person);
	DDX_Text(pDX, IDC_LABEL_PAGE_INFO, m_static_string_person_page);
	DDX_Text(pDX, IDC_EDIT_PERSON_PAGE, m_edit_person_page);
	DDX_Text(pDX, IDC_ShowInfo, m_ShowTip_String);
	DDX_Control(pDX, IDC_LIST1, m_Test);
}


BEGIN_MESSAGE_MAP(CFaceOper, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_ADD_FACE_GROUP, &CFaceOper::OnBnClickedBtnAddFaceGroup)
	ON_BN_CLICKED(IDC_BTN_REFRESH_FACE_GROUP, &CFaceOper::OnBnClickedBtnRefreshFaceGroup)
	ON_BN_CLICKED(IDC_BTN_DELETE_FACE_GROUP, &CFaceOper::OnBnClickedBtnDeleteFaceGroup)
	ON_BN_CLICKED(IDC_BTN_PERSON_ADD, &CFaceOper::OnBnClickedBtnPersonAdd)
	ON_BN_CLICKED(IDC_Btn_UP, &CFaceOper::OnBnClickedBtnUp)
	ON_BN_CLICKED(IDC_Btn_Cannel, &CFaceOper::OnBnClickedBtnCannel)
	ON_LBN_SELCHANGE(IDC_LIST3, &CFaceOper::OnLbnSelchangeList3)
	ON_BN_CLICKED(IDC_BTN_PERSON_REFRESH, &CFaceOper::OnBnClickedBtnPersonRefresh)
	ON_BN_CLICKED(IDC_BTN_PERSON_PAGE_PRE, &CFaceOper::OnBnClickedBtnPersonPagePre)
	ON_BN_CLICKED(IDC_BTN_PERSON_PAGE_NEXT, &CFaceOper::OnBnClickedBtnPersonPageNext)
	ON_BN_CLICKED(IDC_BTN_PERSON_PAGE_FRONT, &CFaceOper::OnBnClickedBtnPersonPageFront)
	ON_BN_CLICKED(IDC_BTN_PERSON_PAGE_BACK, &CFaceOper::OnBnClickedBtnPersonPageBack)
	ON_BN_CLICKED(IDC_BTN_PERSON_PAGE_GO, &CFaceOper::OnBnClickedBtnPersonPageGo)
	ON_BN_CLICKED(IDC_BTN_PERSON_DELETE, &CFaceOper::OnBnClickedBtnPersonDelete)
	ON_LBN_SELCHANGE(IDC_LIST2, &CFaceOper::OnLbnSelchangeList2)
	ON_WM_SIZE()
	//ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_PER_ALONE, &CFaceOper::OnBnClickedBtnPerAlone)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_LABEL_PAGE_INFO, &CFaceOper::OnEnChangeLabelPageInfo)
END_MESSAGE_MAP()

BOOL CFaceOper::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	CWnd *pUP_Face = GetDlgItem(IDC_Btn_UP);
	pUP_Face->EnableWindow(FALSE);

	CWnd *pCan = GetDlgItem(IDC_Btn_Cannel);
	pCan->EnableWindow(FALSE);

	/*CWnd *pDelte = GetDlgItem(IDC_BTN_PERSON_DELETE);
	pDelte->EnableWindow(FALSE);
*/


	CRect rect1;
	GetClientRect(&rect1);     //ȡ�ͻ�����С  
	old.x = rect1.right - rect1.left;
	old.y = rect1.bottom - rect1.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);

	return TRUE;
}

/*void CFaceOper::OnPaint()
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
		Image image(L"./res/BG_BKALL.jpg", TRUE);
		graphics.DrawImage(&image, 0, 0, rect.right, rect.bottom);  //���Ʊ���

		CDialogEx::OnPaint();
	}*/

///////////////////////////////////////////////////////////////////////////////////
//static void CALLBACK disconnect_callback(LLONG lLoginID, char *lpszIP, LONG nPort, LDWORD dwUser)
//{
//	// TODO: 
//	CFaceOper* pDlg = (CFaceOper*)dwUser;
//	pDlg->m_lLoginID = 0;
//}
//
//BOOL CFaceOper::InitLoginParams()
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
//BOOL CFaceOper::LogIn()
//{
//	m_lLoginID = Net_LoginDevice(m_Str_Ip.GetBuffer(), m_int_port,
//		m_Str_User.GetBuffer(), m_Str_Pwd.GetBuffer(), NULL, &m_nError); //��½
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
//BOOL CFaceOper::LogOut()
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
///////////////////////////////////////////////////////////////////////////////////

// CFaceOper ��Ϣ�������


/*****************************************************************************/
// �������
BOOL CFaceOper::UI_RefreshFaceGroup()
{
	m_list_face_group.ResetContent();
	for (int i = 0; i < m_pfaceGroupArray->nFaceGroupNum; i++)
	{
		CString strGroupInfo = _T("");
		strGroupInfo.Format(_T("%d-%u-%s"), i, m_pfaceGroupArray->stFaceGroupArr[i].nGroupID,
			m_pfaceGroupArray->stFaceGroupArr[i].szGroupName);
		m_list_face_group.AddString(strGroupInfo.GetBuffer(0));
		strGroupInfo.ReleaseBuffer();
	}
	m_list_face_group.SetCurSel(-1);
	return TRUE;
}

BOOL CFaceOper::UI_RefreshCurFaceInfo(STU_FACE_GROUP_INFO* pCurFaceInfo)
{
	/*if (NULL == pCurFaceInfo)
	{
		m_edit_uint_group_id = 0;
		m_edit_string_group_name = "";
		m_edit_string_group_alias = "";
		m_edit_string_create_time = "";
		m_edit_int_group_enable = 0;
		m_edit_int_group_top_rank = 0;
		m_edit_string_group_guid = "";
	}
	else
	{
		m_edit_uint_group_id = pCurFaceInfo->nGroupID;
		m_edit_string_group_name.Format("%s", pCurFaceInfo->szGroupName);
		m_edit_string_group_alias.Format("%s", pCurFaceInfo->szAlias);
		m_edit_string_create_time.Format("%04d-%02d-%02d %02d:%02d:%02d",
			pCurFaceInfo->stCreateTime.dwYear, pCurFaceInfo->stCreateTime.dwMonth, pCurFaceInfo->stCreateTime.dwDay,
			pCurFaceInfo->stCreateTime.dwHour, pCurFaceInfo->stCreateTime.dwMinute, pCurFaceInfo->stCreateTime.dwSecond);
		m_edit_int_group_enable = pCurFaceInfo->bEnable;
		m_edit_string_group_search_threshold.Format("%0.2f", pCurFaceInfo->fSearchThreshold);
		m_edit_int_group_top_rank = pCurFaceInfo->nTopRank;
		m_edit_string_group_guid.Format("%s", pCurFaceInfo->szGUID);
	}*/

	UpdateData(FALSE);
	return TRUE;
}

BOOL CFaceOper::UI_RefreshCurPerson(STU_PERSON_FACE_INFO* pCurPerson)
{
	/*if (!m_person_face_image_1.IsEmpty())
	DeleteFile(m_person_face_image_1.GetBuffer(0));
	if (!m_person_face_image_2.IsEmpty())
	DeleteFile(m_person_face_image_2.GetBuffer(0));
	if (!m_person_face_image_3.IsEmpty())
	DeleteFile(m_person_face_image_3.GetBuffer(0));
	*/
	/*if (NULL == pCurPerson)
	{
		m_edit_uint_person_id = 0;
		m_edit_string_person_name = "";
		m_edit_string_person_birth = "";
		m_edit_string_person_sex = "";
		m_edit_string_person_certificate_type = "";
		m_edit_string_person_certificate_id = "";
		m_edit_string_person_country = "";
		m_edit_string_person_province = "";
		m_edit_string_person_city = "";

	}
	else
	{
		m_edit_uint_person_id = pCurPerson->stPersonInfo.nPersonID;
		m_edit_string_person_name.Format("%s", pCurPerson->stPersonInfo.szName);
		m_edit_string_person_birth.Format("%04d-%02d-%02d",
			pCurPerson->stPersonInfo.stBirthday.dwYear, pCurPerson->stPersonInfo.stBirthday.dwMonth, pCurPerson->stPersonInfo.stBirthday.dwDay);
		m_edit_string_person_sex = pCurPerson->stPersonInfo.emSexType == SEX_TYPE_MALE ? "male" :
			pCurPerson->stPersonInfo.emSexType == SEX_TYPE_FEMALE ? "female" : "unknown";
		m_edit_string_person_certificate_type.Format("%s", pCurPerson->stPersonInfo.szCertificateType);
		m_edit_string_person_certificate_id.Format("%s", pCurPerson->stPersonInfo.szID);
		m_edit_string_person_country.Format("%s", pCurPerson->stPersonInfo.szCountry);
		m_edit_string_person_province.Format("%s", pCurPerson->stPersonInfo.szProvince);
		m_edit_string_person_city.Format("%s", pCurPerson->stPersonInfo.szCity);

		m_edit_string_person_1_img_facetoken.Format("%s", pCurPerson->stFaceImageInfoArr[0].szFaceToken);
		m_edit_string_person_2_img_facetoken.Format("%s", pCurPerson->stFaceImageInfoArr[1].szFaceToken);
		m_edit_string_person_3_img_facetoken.Format("%s", pCurPerson->stFaceImageInfoArr[2].szFaceToken);
*/
		// ����ͼƬ������

		/*for (int i = 0; i < pCurPerson->nFaceImageCount; i++)
		{
		CString strPath = "";
		strPath.Format("C:\\Tmp\\face_image_tmp_%d.jpg", i + 1);
		if (TRUE == GetFaceImage(i, strPath))
		{
		if (0 == i)
		m_person_face_image_1 = strPath;
		else if (1 == i)
		m_person_face_image_2 = strPath;
		else if (2 == i)
		m_person_face_image_3 = strPath;
		}
		}*/
	

	UpdateData(FALSE);
	Invalidate(TRUE);
	return TRUE;
}

void CFaceOper::DeleteFaceGroupArray()
{
	if (NULL != m_pfaceGroupArray) {
		delete m_pfaceGroupArray;
		m_pfaceGroupArray = NULL;
	}
}


BOOL CFaceOper::CheckLoginOk()
{
	if (0 < m_lLoginID)
		return TRUE;
	MessageBox(_T("��δ��¼��"), _T(""), MB_OK);
	return FALSE;
}

/*****************************************************************************/


//////////////////////////////////////////////////////////////////
// ������ & ��������
void CFaceOper::OnBnClickedBtnAddFaceGroup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	CFaceGroupAdd dlgFGAdd;
	if (IDOK != dlgFGAdd.DoModal())
		return;
	// ��������ӵ��б�
	CString strAlias = dlgFGAdd.GetAliasString();
	BOOL bEnable = dlgFGAdd.GetFaceGroupEnable();
	float fSearchThreshold = dlgFGAdd.GetSearchThreshold();
	UINT nTopRank = dlgFGAdd.GetTopRank();

	if (TRUE != AddFaceGroup(strAlias, bEnable, fSearchThreshold, nTopRank))
	{
		MessageBox(_T("���������ʧ��."));
		return;
	}
	else
	{
		MessageBox(_T("��ӳɹ�"));
	}
}


BOOL CFaceOper::AddFaceGroup(CString strAlias, BOOL bEnable, float fSearchThreshold, UINT nTopRank)
{
	STU_FACE_GROUP_CREATE_IN_PARAM stInParam = { 0 };
	STU_FACE_GROUP_CREATE_OUT_PARAM stOutParam = { 0 };

	stInParam.bEnable = bEnable;
	sprintf(stInParam.szAlias, "%s", strAlias.GetBuffer(0));
	strAlias.ReleaseBuffer();
	stInParam.fSearchThreshold = fSearchThreshold;
	stInParam.nTopRank = nTopRank;

	if (TRUE != Net_CreateFaceGroup(m_lLoginID, &stInParam, &stOutParam))
	{
		AfxMessageBox(_T("���󣬴������������.\n"));

		return FALSE;
	}

	return TRUE;
}

BOOL CFaceOper::ReCreateFaceGroupArray()
{
	DeleteFaceGroupArray();
	m_pfaceGroupArray = new STU_FACE_GROUP_ARRAY_INFO;
	if (NULL == m_pfaceGroupArray)
	{
		return FALSE;
	}
	memset(m_pfaceGroupArray, 0x00, sizeof(STU_FACE_GROUP_ARRAY_INFO));
	return TRUE;
}

BOOL CFaceOper::RefreshFaceGroup()
{
	if (TRUE != ReCreateFaceGroupArray()) 
	{
		MessageBox(_T("ReCreateFaceGroupArray���������"), NULL, MB_OK);		
		return FALSE;
	}

	if (TRUE != Net_GetAllFaceGroups(m_lLoginID, m_pfaceGroupArray))
	{
		MessageBox(_T("��ȡ���������"), NULL, MB_OK);
		return FALSE;
	}

	return TRUE;
}

void CFaceOper::OnBnClickedBtnRefreshFaceGroup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (TRUE != CheckLoginOk())
		return;

	if (TRUE != RefreshFaceGroup())
		return;

	UI_RefreshFaceGroup();
	//UI_RefreshCurFaceInfo(NULL);
	//UI_RefreshCurPerson(NULL);
}

//////////////////////////������/////////////////////////////////////////
STU_FACE_GROUP_INFO* CFaceOper::GetCurFaceGroupInfo(int nIndex)
{
	if (0 > nIndex || MAX_FACE_GROUP_NUM <= nIndex)
		return NULL;
	if (NULL == m_pfaceGroupArray || 0 == m_pfaceGroupArray->nFaceGroupNum)
		return NULL;
	return &m_pfaceGroupArray->stFaceGroupArr[nIndex];
}

BOOL CFaceOper::DeleteFaceGroup(unsigned int nGroupID, BOOL bDelBindFace)
{
	STU_FACE_GROUP_DELETE_IN_PARAM stInParam = { 0 };
	STU_FACE_GROUP_DELETE_OUT_PARAM stOutParam = { 0 };

	stInParam.nGroupID = nGroupID;
	stInParam.bDelBindFace = bDelBindFace;

	if (TRUE != Net_DeleteFaceGroup(m_lLoginID, &stInParam, &stOutParam))
	{
		CString str;
		str.Format(_T("Error | Delete face group error, nGrouID = %u, bDelBindFace = %d.\n"),
			nGroupID, bDelBindFace);

		MessageBox(str, NULL, MB_OK);
		str.ReleaseBuffer(0);
		/*_OutputDebugString("Error | Delete face group error, nGrouID = %u, bDelBindFace = %d.\n",
			nGroupID, bDelBindFace);*/

		return FALSE;
	}

	return TRUE;
}

//ɾ��������
void CFaceOper::OnBnClickedBtnDeleteFaceGroup()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (TRUE != CheckLoginOk())
		return;

	// �Ƿ�ѡ����
	int nIndex = m_list_face_group.GetCurSel();
	if (nIndex < 0) {
		MessageBox(_T("δѡ�������飡"), _T(""), MB_OK);
		return;
	}

	STU_FACE_GROUP_INFO* pCurFaceGroup = GetCurFaceGroupInfo(nIndex);
	if (NULL == pCurFaceGroup)
	{
		MessageBox("��ȡ��������Ϣʧ�ܣ�");
		return;
	}

	BOOL bDelBindFace = FALSE;
	if (IDYES == MessageBox(_T("�Ƿ�ɾ��������󶨵���������ͼƬ��") , _T(""), MB_YESNO))
	{
		bDelBindFace = TRUE;
	}

	if (TRUE != DeleteFaceGroup(pCurFaceGroup->nGroupID, bDelBindFace))
	{
		MessageBox(_T("ɾ��������ʧ�ܣ���ˢ�������⣡"));
	}

	// ��ˢ��һ��
	RefreshFaceGroup();
	UI_RefreshFaceGroup();
	UI_RefreshCurFaceInfo(NULL);
}


//�������
void CFaceOper::ClearData()
{
	if (!m_FileList.empty())
	{
		m_FileList.clear();
		vector<CString>().swap(m_FileList);
	}	
}

///////////////////////Ui_Show_Begin//////////////////////////////////////////////////////
void CFaceOper::Ui_Show(CString g_strPictureShow)
{
	CString strExt(".jpg");
	if (g_strPictureShow.IsEmpty() || -1 == g_strPictureShow.Find(strExt.GetBuffer(0)))
	{
		AfxMessageBox(_T("����jpg�ļ�")); 
		return;
	}		

	CImage image;
	image.Load(g_strPictureShow);
	
	CRect rectControl;                        //�ؼ����ζ���
	CRect rectPicture;                        //ͼƬ���ζ���

	int x = image.GetWidth();
	int y = image.GetHeight();
	(&m_Picture)->GetClientRect(rectControl);

	CDC *pDc = (&m_Picture)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(),
		CSize((int)rectControl.Width(),
		(int)rectControl.Height()));

	(&m_Picture)->SetBitmap(NULL);

	//�������ַ������ɻ���ͼƬ
	image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); //��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������

	image.Destroy();
	(&m_Picture)->ReleaseDC(pDc);

	UpdateData(FALSE);
}

//////////////////////////ui_end///////////////////////////////////////////////////

//////////////////////////�ϴ���ʼ///////////////////////////////////////////////////
//�����Ա��Ϣ������
void CFaceOper::OnBnClickedBtnPersonAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);


	if (TRUE != CheckLoginOk())
		return;

	ClearData();  //���vector

	CFileDialog dlg(TRUE);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���  
	if (dlg.DoModal() == IDOK)
		m_csFileName = dlg.GetPathName();
	else
		m_csFileName.Empty();

	int iEndPos = 0;
	iEndPos = m_csFileName.ReverseFind('\\');
	csDirParth = m_csFileName.Left(iEndPos);

	//��ȡ�ļ���
	GetFileFromDir(csDirParth);

	if (m_FileList.empty())
	{
		return;
	}

	CString strTmp = m_FileList.at(0);
	int posEnd = strTmp.ReverseFind('.');
	m_Name_ID = strTmp.Left(posEnd);

	CString strPath;
	//strPath = csDirParth + "\\" + m_FileList.front();
	//Ui_Show(strPath);

	CString strTmpFileName = m_FileList.front();
	int nFlageLen = strTmpFileName.Find("E");

	strTmpFileName = strTmpFileName.Mid(2, nFlageLen - 2);

	strPath = csDirParth + "\\" + strTmpFileName + _T(".jpg");
	Ui_Show(strPath); //test
	//�ϴ���ȡ����ť����
	CWnd *pUP_Face = GetDlgItem(IDC_Btn_UP);
	pUP_Face->EnableWindow(TRUE);

	CWnd *pCan = GetDlgItem(IDC_Btn_Cannel);
	pCan->EnableWindow(TRUE);

	UpdateData(FALSE);
}


//��ȡ�ļ�����vector
void CFaceOper::GetFileFromDir(CString csDirPath)
{
	csDirPath += "\\*.jpg";

	HANDLE file;
	WIN32_FIND_DATA fileData;
	char line[1024];
	char fn[1000];

	////��ȡ��һ���ļ���
	//file = FindFirstFile(csDirPath.GetBuffer(0), &fileData);
	//m_FileList.push_back(fileData.cFileName);


	////���ݵ�һ���ļ��������»�ȡ
	//bool bState = false;
	//bState = FindNextFile(file, &fileData);
	//while (bState)
	//{
	//	m_FileList.push_back(fileData.cFileName);
	//	bState = FindNextFile(file, &fileData);
	//}
	CString tmp = "";
	CString tmp2 = "";
	//����������
	file = FindFirstFile(csDirPath.GetBuffer(0), &fileData);
	CString t1 = fileData.cFileName;
	int nPos = t1.Find(".");
	t1 = t1.Mid(0, nPos);
	INT nLen = t1.GetLength();
	if (15 == nLen && 'F' == t1[0] && 'Z' == t1[1] && 'E' == t1[14]  || 'P' == t1[1])
	{
		goto Label;
	}
	
	if (12<nLen)
	{
		MessageBox(_T("�ļ�������12λ", _T("����"), MB_ICONERROR));
		return;
	}

	for (int i = 0; i < 12 - nLen;i++)
	{
		t1.Insert(i + nLen,'E');
	}

	if ('F' == t1[0] && 'Z' == t1[1] && 'E' == t1[14])
	{
	Label:

		tmp = t1;
	}
	else if('F' == t1[0] && 'Z' == t1[1] && 'E' != t1[14])
	{
		tmp = t1 + _T("E");
	}
	else
	{
		tmp = "FP" + t1 + _T("E");
	}	
	tmp += _T(".jpg");
	m_FileList.push_back(tmp);

	//���ݵ�һ���ļ��������»�ȡ
	bool bState = false;
	bState = FindNextFile(file, &fileData);
	while (bState)
	{
		CString t2 = fileData.cFileName;
		nPos = t2.Find(".");
		t2 = t2.Mid(0, nPos);
		nLen = t2.GetLength();

		if (15 == nLen && 'F' == t2[0] && 'Z' == t2[1] && 'E' == t2[14] || 'P' == t2[1]) //�����ļ��Ѿ���fz��eЭ��ͷβ
		{
			goto Label1;
		}
		if (12 < nLen)
		{
			MessageBox(_T("�ļ���λ������12λ", _T("����"), MB_ICONERROR));
			return;
		}
		for (int i = 0; i < 12 - nLen; i++)
		{
			t2.Insert(i + nLen, 'E');
		}

		if ('F' == t2[0] && 'Z' == t2[1] && 'E' == t2[14])
		{
		Label1:

			tmp2 = t2;
		}
		else if ('F' == t2[0] && 'Z' == t2[1] && 'E' != t2[14])
		{
			tmp2 = t2 + _T("E");
		}
		else
		{
			tmp2 = "FP" + t2 + _T("E");
		}
		tmp2 += _T(".jpg");
		m_FileList.push_back(tmp2);
		bState = FindNextFile(file, &fileData);
	}
}

void CFaceOper::FaceUp()
{
	UpdateData(TRUE);
	if (TRUE != CheckLoginOk())
		return;

	int nIndex = CurFaceGroupIndex();
	STU_FACE_GROUP_INFO* pCurFaceGroup = GetCurFaceGroupInfo(nIndex);
	if (NULL == pCurFaceGroup)
	{
		MessageBox(_T("��ѡ��һ�������飡"));
		return;
	}

	for (int i = 0; i < m_FileList.size(); i++)
	{
		//��ʼ��
		memset(&m_stPersonInfo, 0x00, sizeof(STU_PERSON_INFO));
		memset(m_stPersonInfo.szName, NULL, 128);
		char szNewName[128] = { 0 };
		m_Name_ID = "";

		CString m_person_name = m_FileList.at(i);
		int posEnd = m_person_name.ReverseFind('.');
		m_Name_ID = m_person_name.Left(posEnd);

		m_person_certificate_id = m_person_name.Left(posEnd);//���֤Ҳ��Ψһid
															 //
		memcpy(m_stPersonInfo.szName, m_Name_ID.GetBuffer(0), m_Name_ID.GetLength());

		CString strPath;
		//strPath = csDirParth + "\\" + m_FileList.at(i);
		//strPath = csDirParth + "\\" + m_FileList.at(i).Mid(2);  //test
		CString strTmpFileName = m_FileList.at(i);
		
		if ('P' == strTmpFileName[1])   //�����ϴ�Э��ڶ�λp
		{
			int nFlageLen = strTmpFileName.Find("E", 0);
			strTmpFileName = strTmpFileName.Mid(2, nFlageLen - 2);
		}

		strPath = csDirParth + "\\" + strTmpFileName + _T(".jpg");
		Ui_Show(strPath);


		sscanf(m_person_birth.GetBuffer(0), "%04d-%02d-%02d",
			&m_stPersonInfo.stBirthday.dwYear, &m_stPersonInfo.stBirthday.dwMonth, &m_stPersonInfo.stBirthday.dwDay);
		m_person_birth.ReleaseBuffer();

		if (m_person_sex == "male")
			m_stPersonInfo.emSexType = SEX_TYPE_MALE;
		else if (m_person_sex == "female")
			m_stPersonInfo.emSexType = SEX_TYPE_FEMALE;
		else
			m_stPersonInfo.emSexType = SEX_TYPE_UNKNOWN;

		memcpy(m_stPersonInfo.szCertificateType, m_person_certificate_type.GetBuffer(0), m_person_certificate_type.GetLength());
		m_person_certificate_type.ReleaseBuffer();

		memcpy(m_stPersonInfo.szID, m_person_certificate_id.GetBuffer(0), m_person_certificate_id.GetLength());
		m_person_certificate_id.ReleaseBuffer();


		memcpy(m_stPersonInfo.szCountry, m_person_county.GetBuffer(0), m_person_county.GetLength());
		m_person_county.ReleaseBuffer();


		memcpy(m_stPersonInfo.szProvince, m_person_province.GetBuffer(0), m_person_province.GetLength());
		m_person_province.ReleaseBuffer();

		memcpy(m_stPersonInfo.szCity, m_person_city.GetBuffer(0), m_person_city.GetLength());
		m_person_city.ReleaseBuffer();


		//// �����Ա֮ǰ��ҪУ��������
		if (TRUE != CheckNameSuffix(m_stPersonInfo.szName, szNewName, 128))
		{
			MessageBox(_T("����У��ʧ�ܣ�"));
			return;
		}
		// ��ֵ����
		memcpy(m_stPersonInfo.szName, szNewName, strlen(szNewName));

		std::vector<CString> vecImages;
		if (!strPath.IsEmpty())
			vecImages.push_back(strPath);

		if (TRUE != AddPersonInfo(pCurFaceGroup->nGroupID, &m_stPersonInfo, vecImages))
		{
			//AfxMessageBox(m_FileList.at(i) + _T("--�����Ա��Ϣʧ��, ͼƬ���������������ظ���"));
			m_ShowTip_String = m_FileList.at(i) + _T("--�����Ա��Ϣʧ��, ͼƬ���������������ظ���");
			m_Test.AddString(m_FileList.at(i));

			continue;
		}
		else
		{
			m_ShowTip_String = m_FileList.at(i) + _T("�ϴ��ɹ�");
		}

		UpdateData(FALSE);
		m_Name_ID.ReleaseBuffer();
		//InvalidateRect(NULL, FALSE);

		//if (g_KillThread == 1)  //����û������жϣ����߳��˳�
		//{
		//	return;
		//}
	}
}

DWORD CFaceOper::UpProc(LPVOID lpPar)   //�ϴ������߳�
{
	g_FaceOper->FaceUp();

	return 0;
}


//�ϴ���ť
void CFaceOper::OnBnClickedBtnUp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//g_KillThread == 0; //�߳�ִ�б�־
	CloseHandle(CreateThread(NULL, 0, UpProc, NULL, 0, NULL));   //���������ϴ��߳�

	CWnd *pUP_Face = GetDlgItem(IDC_Btn_UP);
	pUP_Face->EnableWindow(FALSE);

	CWnd *pCan = GetDlgItem(IDC_Btn_Cannel);
	pCan->EnableWindow(FALSE);
}

//�ϴ�����ͼƬ���ĺ���
BOOL CFaceOper::AddPersonInfo(unsigned int nGroupID, STU_PERSON_INFO* pstPersonInfo, std::vector<CString> &vecImages)
{
	if (NULL == pstPersonInfo)
		return FALSE;

	STU_FACE_ADD_IN_PARAM stInParam = { 0 };
	STU_FACE_ADD_OUT_PARAM stOutParam = { 0 };

	stInParam.nGroupID = nGroupID;
	
	stInParam.nImageCount = vecImages.size();
	memcpy(&stInParam.stPersonInfo, pstPersonInfo, sizeof(STU_PERSON_INFO));

	CString strImageFiles = "";
	std::vector<CString>::iterator iter = vecImages.begin();
	while (iter != vecImages.end())
	{
		strImageFiles.Append(*iter);
		strImageFiles.AppendChar('|');  // ͼƬ·���� ��|�� �ָ�
		iter++;
	}
	strImageFiles = strImageFiles.TrimRight('|');

	stInParam.lpszImageFiles = new char[strImageFiles.GetLength() + 1];
	memset(stInParam.lpszImageFiles, 0x00, strImageFiles.GetLength() + 1);
	memcpy(stInParam.lpszImageFiles, strImageFiles.GetBuffer(0), strImageFiles.GetLength());
	

	if (TRUE != Net_AddPersonInfo(m_lLoginID, &stInParam, &stOutParam))
	{
		//AfxMessageBox("Error | AddPersonInfo fail.\n");
		delete[] stInParam.lpszImageFiles;
		return FALSE;
	}

	delete[] stInParam.lpszImageFiles;
	return TRUE;
}

//У�������Ƿ��ظ�
BOOL CFaceOper::CheckNameSuffix(IN const char* lpszName, OUT char* lpszNewName, int nNewNameLen)
{
	if (NULL == lpszName || NULL == lpszNewName)
	{
		AfxMessageBox("Error | Person page error.\n");
		return FALSE;
	}

	memset(lpszNewName, 0x00, nNewNameLen);

	STU_PERSON_NAME_CHECK_IN_PARAM stInParam = { 0 };
	STU_PERSON_NAME_CHECK_OUT_PARAM stOutParam = { 0 };
	memcpy(stInParam.szName, lpszName, strlen(lpszName));

	if (TRUE != Net_CheckPersonNameSuffix(m_lLoginID, &stInParam, &stOutParam))
	{
		AfxMessageBox("Error | Get face info find result fail.\n");

		return FALSE;
	}

	if (0 == stOutParam.nSuffix)
	{
		memcpy(lpszNewName, lpszName, strlen(lpszName));
	}
	else
	{
		sprintf_s(lpszNewName, nNewNameLen, "%s%d", lpszName, stOutParam.nSuffix);
	}

	return TRUE;
}

//////////////////////////�ϴ�����///////////////////////////////////////////////////
//ȡ���ϴ�
void CFaceOper::OnBnClickedBtnCannel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ClearData();

	CWnd *pUP_Face = GetDlgItem(IDC_Btn_UP);
	pUP_Face->EnableWindow(FALSE);

	CWnd *pCan = GetDlgItem(IDC_Btn_Cannel);
	pCan->EnableWindow(FALSE);

	m_Name_ID = "";
	(&m_Picture)->SetBitmap(NULL);

	//g_KillThread = 1;

	Invalidate(FALSE);
	UpdateData(FALSE);
}

//////////////////////////////////////ˢ����Ա��Ϣbegin///////////////////////////////////////////////////////////////
//������list��Ӧ
void CFaceOper::OnLbnSelchangeList3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (TRUE != CheckLoginOk())
		return;

	int nIndex = m_list_face_group.GetCurSel();

	STU_FACE_GROUP_INFO* pCurFaceGroup = GetCurFaceGroupInfo(nIndex);


	OnBnClickedBtnPersonRefresh();
}


void CFaceOper::OnBnClickedBtnPersonRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (TRUE != CheckLoginOk())
		return;

	if (TRUE != RefreshTotalPersonCount())
	{
		
		return;
	}

	if (0 == m_nTotalPersonPage)
	{
		m_nCurPersonCount = 0;
		m_nCurPersonPage = 0;
		memset(&m_stPersonFaceInfoArr, 0x00, sizeof(STU_PERSON_FACE_INFO) * PER_PERSON_PAGE_NUM);
	}
	else
	{
		m_nCurPersonPage = 1;
	}

	m_ShowTip_String = _T("");

	if (TRUE != FrontPagePerson())
	{
	}

	// ˢ���б�
	UI_RefreshPersonList();
	UpdateData(FALSE);
}


BOOL CFaceOper::UI_RefreshPersonList()
{
	m_list_person.ResetContent();
	for (int i = 0; i < m_nCurPersonCount; i++)
	{
		CString strInfo = _T("");
		strInfo.Format(_T("%d-%u-%s"), i + 1, m_stPersonFaceInfoArr[i].stPersonInfo.nPersonID,
			m_stPersonFaceInfoArr[i].stPersonInfo.szName);
		m_list_person.AddString(strInfo.GetBuffer(0));
		strInfo.ReleaseBuffer();
	}

	m_static_string_person_page.Format("%d/%d", m_nCurPersonPage, m_nTotalPersonPage);

	

	UpdateData(FALSE);
	return TRUE;
}

BOOL CFaceOper::RefreshTotalPersonCount()
{
	int nFaceGroupIndex = CurFaceGroupIndex();
	if (0 > nFaceGroupIndex)
	{
		m_ShowTip_String =_T("û�������飬�������");
		UpdateData(FALSE);
		return FALSE;
	}

	// Ԥ����������Ա��Ϣ
	STU_FACE_INFO_FIND_IN_PARAM stInParam = { 0 };
	stInParam.nGroupID = m_pfaceGroupArray->stFaceGroupArr[nFaceGroupIndex].nGroupID;
	stInParam.stCondition.bEnable = FALSE; // û��������ѯ��Ҳ������ΪTRUE������������ѯ

    //��ʼ����������Ϣ; Net_PreFindFaceInfo Ԥ��ѯ�ɹ�����Ե���
	STU_FACE_INFO_FIND_OUT_PARAM stOutParam = { 0 };
	
	if (TRUE != Net_StartFindFaceInfo(m_lLoginID, &stInParam, &stOutParam))
	{
		AfxMessageBox(_T("����Ԥ��������Ϣʧ�ܡ�"));
		return FALSE;
	}

	//��ȡ��ǰ��ѯ�����µ���Ա��Ŀ��Net_StartFindFaceInfo ��ѯ�ɹ�����Ե���
	if (TRUE != Net_GetPersonCount(m_lLoginID, &m_nTotalPersonCount))
	{
		AfxMessageBox(_T("�������˼���ʧ�ܡ�"));
		return FALSE;
	}

	int nFaceCount;
	//��ȡ��ǰ��ѯ�����µ�������Ŀ��Net_StartFindFaceInfo ��ѯ�ɹ�����Ե���
	Net_GetFaceCount(m_lLoginID, &nFaceCount);

	if (m_nTotalPersonCount % PER_PERSON_PAGE_NUM == 0)
		m_nTotalPersonPage = m_nTotalPersonCount / PER_PERSON_PAGE_NUM;
	else
		m_nTotalPersonPage = m_nTotalPersonCount / PER_PERSON_PAGE_NUM + 1;

	return TRUE;
}


BOOL CFaceOper::FrontPagePerson()
{
	if (0 == m_nTotalPersonCount)
	{
		m_ShowTip_String = _T("��������û������ͼƬ");

		UpdateData(FALSE);
		return FALSE;
	}

	STU_FACE_INFO_FIND_RESULT_IN_PARAM stInParam = { 0 };
	STU_FACE_INFO_FIND_RESULT_OUT_PARAM stOutParam = { 0 };
	stInParam.nCount = PER_PERSON_PAGE_NUM;
	stInParam.nOffset = 0;

	if (TRUE != Net_GetFaceInfoFindResult(m_lLoginID, &stInParam, &stOutParam))
	{
		int E = Net_LastError();
		AfxMessageBox("Error | Get face info find result fail.\n");
		return FALSE;
	}

	m_nCurPersonPage = 1;
	m_nCurPersonCount = stOutParam.nPersonFaceInfoArrSize;
	memcpy(&m_stPersonFaceInfoArr, &stOutParam.stPersonFaceInfoArr, sizeof(STU_PERSON_FACE_INFO) * m_nCurPersonCount);

	return TRUE;
}

//////////////////////////////////////ˢ����Ա��Ϣend///////////////////////////////////////////////////////////////

void CFaceOper::OnBnClickedBtnPersonPagePre()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (TRUE != CheckLoginOk())
		return;
	if (TRUE != PrePagePerson())
		return;
	// ˢ���б�
	UI_RefreshPersonList();
}


BOOL CFaceOper::PrePagePerson()
{
	if (0 == m_nTotalPersonCount)
	{
		AfxMessageBox(_T("Error | Person page error.\n"));
		return FALSE;
	}

	if ((m_nCurPersonPage - 1) < 1)
	{
		AfxMessageBox(_T("Info | Already min person page.\n"));
		return TRUE;
	}

	STU_FACE_INFO_FIND_RESULT_IN_PARAM stInParam = { 0 };
	STU_FACE_INFO_FIND_RESULT_OUT_PARAM stOutParam = { 0 };
	stInParam.nCount = PER_PERSON_PAGE_NUM;
	stInParam.nOffset = (m_nCurPersonPage - 2) * PER_PERSON_PAGE_NUM;

	if (TRUE != Net_GetFaceInfoFindResult(m_lLoginID, &stInParam, &stOutParam))
	{
		AfxMessageBox("Error | Get face info find result fail.\n");
		return FALSE;
	}

	m_nCurPersonPage -= 1;
	m_nCurPersonCount = stOutParam.nPersonFaceInfoArrSize;
	memcpy(&m_stPersonFaceInfoArr, &stOutParam.stPersonFaceInfoArr, sizeof(STU_PERSON_FACE_INFO) * m_nCurPersonCount);

	return TRUE;
}

void CFaceOper::OnBnClickedBtnPersonPageNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (TRUE != CheckLoginOk())
		return;
	if (TRUE != NextPagePerson())
		return;
	// ˢ���б�
	UI_RefreshPersonList();
}

BOOL CFaceOper::NextPagePerson()
{
	if (0 == m_nTotalPersonCount)
	{
		AfxMessageBox("Error | Person page error.\n");
		return FALSE;
	}

	if ((m_nCurPersonPage + 1) > m_nTotalPersonPage)
	{
		AfxMessageBox(_T("Info | Already max person page.\n"));
		return TRUE;
	}

	STU_FACE_INFO_FIND_RESULT_IN_PARAM stInParam = { 0 };
	STU_FACE_INFO_FIND_RESULT_OUT_PARAM stOutParam = { 0 };
	stInParam.nCount = PER_PERSON_PAGE_NUM;
	stInParam.nOffset = m_nCurPersonPage * PER_PERSON_PAGE_NUM;

	if (TRUE != Net_GetFaceInfoFindResult(m_lLoginID, &stInParam, &stOutParam))
	{
		AfxMessageBox("Error | Get face info find result fail.\n");
		return FALSE;
	}

	m_nCurPersonPage += 1;
	m_nCurPersonCount = stOutParam.nPersonFaceInfoArrSize;
	memcpy(&m_stPersonFaceInfoArr, &stOutParam.stPersonFaceInfoArr, sizeof(STU_PERSON_FACE_INFO) * m_nCurPersonCount);

	return TRUE;
}



void CFaceOper::OnBnClickedBtnPersonPageFront()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (TRUE != CheckLoginOk())
		return;
	if (TRUE != FrontPagePerson())
		return;
	// ˢ���б�
	UI_RefreshPersonList();
}


void CFaceOper::OnBnClickedBtnPersonPageBack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (TRUE != CheckLoginOk())
		return;
	if (TRUE != BackPagePerson())
		return;
	// ˢ���б�
	UI_RefreshPersonList();
	//UI_RefreshCurPerson(NULL);

	UpdateData(FALSE);
}

BOOL CFaceOper::BackPagePerson()
{
	if (0 == m_nTotalPersonCount)
	{
		AfxMessageBox(_T("Error | Person page error.\n"));
		return FALSE;
	}

	STU_FACE_INFO_FIND_RESULT_IN_PARAM stInParam = { 0 };
	STU_FACE_INFO_FIND_RESULT_OUT_PARAM stOutParam = { 0 };
	stInParam.nCount = PER_PERSON_PAGE_NUM;
	stInParam.nOffset = (m_nTotalPersonPage - 1) * PER_PERSON_PAGE_NUM;

	if (TRUE != Net_GetFaceInfoFindResult(m_lLoginID, &stInParam, &stOutParam))
	{
		AfxMessageBox("Error | Get face info find result fail.\n");
		return FALSE;
	}

	m_nCurPersonPage = m_nTotalPersonPage;
	m_nCurPersonCount = stOutParam.nPersonFaceInfoArrSize;
	memcpy(&m_stPersonFaceInfoArr, &stOutParam.stPersonFaceInfoArr, sizeof(STU_PERSON_FACE_INFO) * m_nCurPersonCount);

	return TRUE;
}


void CFaceOper::OnBnClickedBtnPersonPageGo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (TRUE != CheckLoginOk())
		return;

	UpdateData(TRUE);

	int nPage = atoi(m_edit_person_page.GetBuffer(0));
	m_edit_person_page.ReleaseBuffer();

	if (nPage <= 0 || nPage > m_nTotalPersonPage)
		return;

	if (TRUE != GoPagePerson(nPage))
		return;

	// ˢ���б�
	UI_RefreshPersonList();

}

BOOL CFaceOper::GoPagePerson(int page)
{
	if (0 == m_nTotalPersonCount)
	{
		AfxMessageBox(_T("Error | Person page error.\n"));
		return FALSE;
	}

	if (0 >= page || m_nTotalPersonPage < page)
	{
		AfxMessageBox(_T("Error | Error page, page = %d.\n", page));
		return TRUE;
	}

	STU_FACE_INFO_FIND_RESULT_IN_PARAM stInParam = { 0 };
	STU_FACE_INFO_FIND_RESULT_OUT_PARAM stOutParam = { 0 };
	stInParam.nCount = PER_PERSON_PAGE_NUM;
	stInParam.nOffset = (page - 1) * PER_PERSON_PAGE_NUM;

	if (TRUE != Net_GetFaceInfoFindResult(m_lLoginID, &stInParam, &stOutParam))
	{
		AfxMessageBox("Error | Get face info find result fail.\n");
		return FALSE;
	}

	m_nCurPersonPage = page;
	m_nCurPersonCount = stOutParam.nPersonFaceInfoArrSize;
	memcpy(&m_stPersonFaceInfoArr, &stOutParam.stPersonFaceInfoArr, sizeof(STU_PERSON_FACE_INFO) * m_nCurPersonCount);

	return TRUE;
}

void CFaceOper::OnBnClickedBtnPersonDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (TRUE != CheckLoginOk())
		return;

	int nIndex = CurPersonIndex();
	STU_PERSON_FACE_INFO* pCurPerson = GetCurPersonFaceInfo(nIndex);
	if (NULL == pCurPerson)
		return;

	if (TRUE != DeletePersonInfo(pCurPerson->stPersonInfo.nPersonID))
	{
		MessageBox(_T("ɾ����Ա��Ϣʧ�ܣ�"));
		return;
	}

	// ������Ա��Ϣ
	OnBnClickedBtnPersonRefresh();
}


BOOL CFaceOper::DeletePersonInfo(unsigned int nPersonID)
{
	if (TRUE != Net_DeletePersonInfo(m_lLoginID, nPersonID))
	{
		AfxMessageBox("Error | DeletePersonInfo fail.\n");
		return FALSE;
	}

	return TRUE;
}


STU_PERSON_FACE_INFO* CFaceOper::GetCurPersonFaceInfo(int nIndex)
{
	if (0 > nIndex || PER_PERSON_PAGE_NUM <= nIndex)
		return NULL;
	STU_FACE_IMAGE_INFO_GET_IN_PARAM stInParam = { 0 };
	stInParam.nPersonID = m_stPersonFaceInfoArr[nIndex].stPersonInfo.nPersonID;
	STU_FACE_IMAGE_INFO_GET_OUT_PARAM stOutParam = { 0 };

	if (TRUE != Net_GetFaceImageInfo(m_lLoginID, &stInParam, &stOutParam))
	{
		AfxMessageBox(_T("Error | Get face image info fail.\n"));
	}
	else
	{
		// ��Ա��Ϣ����

		m_stPersonFaceInfoArr[nIndex].nFaceImageCount = stOutParam.nFaceImageCount;
		memset(&m_stPersonFaceInfoArr[nIndex].stFaceImageInfoArr, 0x00, MAX_PERSON_FACE_NUM * sizeof(STU_FACE_IMAGE_INFO));
		memcpy(&m_stPersonFaceInfoArr[nIndex].stFaceImageInfoArr, &stOutParam.stFaceImageInfoArr, stOutParam.nFaceImageCount * sizeof(STU_FACE_IMAGE_INFO));
	}

	return &m_stPersonFaceInfoArr[nIndex];
}


void CFaceOper::OnLbnSelchangeList2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CFaceOper::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}

void CFaceOper::ReSize()
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

void CFaceOper::OnBnClickedBtnPerAlone()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (TRUE != CheckLoginOk())
		return;

	ClearData();  //���vector

	CFileDialog dlg(TRUE);///TRUEΪOPEN�Ի���FALSEΪSAVE AS�Ի���  
	if (dlg.DoModal() == IDOK)
		m_csFileName = dlg.GetPathName();
	else
		m_csFileName.Empty();

	int iEndPos = 0;
	iEndPos = m_csFileName.ReverseFind('\\');
	csDirParth = m_csFileName.Left(iEndPos);
	CString tmp = "";

	CString t1 = m_csFileName.Mid(iEndPos + 1);
	int nPos = t1.Find(".");
	t1 = t1.Mid(0, nPos);
	INT nLen = t1.GetLength();
	if (15 == nLen && 'F' == t1[0] && 'Z' == t1[1] && 'E' == t1[14] || 'P' == t1[1])
	{
		goto Label;
	}
	if (12 < nLen)
	{
		MessageBox(_T("�ļ�������12λ", _T("����"), MB_ICONERROR));
		return;
	}

	for (int i = 0; i < 12 - nLen; i++)
	{
		t1.Insert(i + nLen, 'E');
	}

	if ('F' == t1[0] && 'Z' == t1[1] && 'E' == t1[14])
	{
	Label:
		tmp = t1;
	}
	else if ('F' == t1[0] && 'Z' == t1[1] && 'E' != t1[14])
	{
		tmp = t1 + _T("E");
	}
	else
	{
		tmp = "FP" + t1 + _T("E");
	}

	tmp += _T(".jpg");
	m_FileList.push_back(tmp);

	CString strTmp = m_FileList.front();
	int posEnd = strTmp.ReverseFind('.');
	m_Name_ID = strTmp.Left(posEnd);

	Ui_Show(m_csFileName);

	//�ϴ���ȡ����ť����
	CWnd *pUP_Face = GetDlgItem(IDC_Btn_UP);
	pUP_Face->EnableWindow(TRUE);

	CWnd *pCan = GetDlgItem(IDC_Btn_Cannel);
	pCan->EnableWindow(TRUE);

	UpdateData(FALSE);
}


void CFaceOper::OnPaint()
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


void CFaceOper::OnEnChangeLabelPageInfo()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
