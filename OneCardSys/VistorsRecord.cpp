// VistorsRecord.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "VistorsRecord.h"
#include "afxdialogex.h"


// CVistorsRecord �Ի���

IMPLEMENT_DYNAMIC(CVistorsRecord, CDialogEx)

CVistorsRecord::CVistorsRecord(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLGVISTRECORD, pParent)
	, m_SelectName(_T(""))
	, m_SelectId(_T(""))
	, m_Name_String(_T(""))
	, m_Sex_String(_T(""))
	, m_ID_String(_T(""))
	, m_RG_Stri(_T(""))	
	, m_BFZ_String(_T(""))
	, m_FK_String(_T(""))
	, m_BFZ_FH_String(_T(""))
	, m_BFZ_LH_String(_T(""))
	, m_BFZ_Addr_String(_T(""))
	, m_Picture_Path(_T(""))
	, m_YL_String(_T(""))
	, m_BeginTime_String(_T(""))
	, m_EndTime_Str(_T(""))
	, m_HMD_String(_T(""))
	, m_strLH(_T(""))
	, m_strFH(_T(""))
	, m_Begin_String(COleDateTime::GetCurrentTime())
	, m_EndTime_String(COleDateTime::GetCurrentTime())
	, m_PicId_string(_T(""))
	, m_Tel_String(_T(""))
{

}

CVistorsRecord::~CVistorsRecord()
{
}

void CVistorsRecord::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBVRFSEX, m_vrCobxSex);
	DDX_Control(pDX, IDC_LISTVRECORD, m_listRcfInfo);
	DDX_Text(pDX, IDC_EVRFNAME, m_SelectName);
	DDX_Text(pDX, IDC_EVRFID, m_SelectId);
	DDX_Text(pDX, IDC_EDIT4, m_Name_String);
	DDX_CBString(pDX, IDC_COMBVRFSEX, m_Sex_String);
	DDX_Text(pDX, IDC_EDIT5, m_ID_String);
	DDX_Text(pDX, IDC_EDIT7, m_RG_Stri);
	DDX_Text(pDX, IDC_EDIT8, m_BFZ_String);
	DDX_Text(pDX, IDC_EDIT9, m_FK_String);
	DDX_Text(pDX, IDC_EDIT10, m_Picture_Path);
	DDX_Control(pDX, IDC_SVRCDSHOW, m_Picture);
	DDX_Text(pDX, IDC_EDSHOW, m_YL_String);
	DDX_Text(pDX, IDC_EDIT_BeginTime, m_BeginTime_String);
	DDX_Text(pDX, IDC_EDIT_EndTime, m_EndTime_Str);
	DDX_Text(pDX, IDC_EDITHMD, m_HMD_String);
	DDX_Text(pDX, IDC_EDIT_LH, m_strLH);
	DDX_Text(pDX, IDC_EDIT_FH, m_strFH);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_datetimebegin);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_datetimeend);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Begin_String);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_EndTime_String);
	DDX_Text(pDX, IDC_PicID, m_PicId_string);
	DDX_Text(pDX, IDC_EDITEL, m_Tel_String);
}


BEGIN_MESSAGE_MAP(CVistorsRecord, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CVistorsRecord::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON2, &CVistorsRecord::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CVistorsRecord::OnBnClickedButton1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTVRECORD, &CVistorsRecord::OnLvnItemchangedListvrecord)
	ON_BN_CLICKED(IDC_BtnSelectAll, &CVistorsRecord::OnBnClickedBtnselectall)
	ON_BN_CLICKED(IDC_BtnSelect, &CVistorsRecord::OnBnClickedBtnselect)
	ON_EN_CHANGE(IDC_EVRFNAME, &CVistorsRecord::OnEnChangeEvrfname)
	ON_BN_CLICKED(IDC_BtnJionBT, &CVistorsRecord::OnBnClickedBtnjionbt)
	ON_EN_CHANGE(IDC_EVRFID, &CVistorsRecord::OnEnChangeEvrfid)
	ON_WM_SIZE()
	ON_EN_CHANGE(IDC_EDIT11, &CVistorsRecord::OnEnChangeEdit11)
	ON_STN_CLICKED(IDC_STATICPT, &CVistorsRecord::OnStnClickedStaticpt)
	ON_BN_CLICKED(IDC_BtnDelete, &CVistorsRecord::OnBnClickedBtndelete)
	ON_WM_PAINT()	
	ON_CBN_DROPDOWN(IDC_COMBVRFSEX, &CVistorsRecord::OnCbnDropdownCombvrfsex)
	ON_BN_CLICKED(IDC_BtnSelectAll_HMD, &CVistorsRecord::OnBnClickedBtnselectallHmd)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CVistorsRecord::OnDtnDatetimechangeDatetimepicker1)
	ON_BN_CLICKED(IDC_BtnSelectTime, &CVistorsRecord::OnBnClickedBtnselecttime)
	ON_BN_CLICKED(IDC_BtnDelete2, &CVistorsRecord::OnBnClickedBtndelete2)
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////////
//static void CALLBACK disconnect_callback(LLONG lLoginID, char *lpszIP, LONG nPort, LDWORD dwUser)
//{
//	// TODO: 
//	CVistorsRecord* pDlg = (CVistorsRecord*)dwUser;
//	pDlg->m_lLoginID = 0;
//}
//
//BOOL CVistorsRecord::InitLoginParams()
//{
//	m_lLoginID = 0;
//	m_Str_Ip = "192.168.7.2";
//	m_int_port = 3000;
//	m_Str_User = "admin";
//	m_Str_Pwd = "admin123";
//
//
//	Net_Init(disconnect_callback, (LDWORD)(void*)this); //��ʼ��sdk��
//
//	return TRUE;
//}
//
//BOOL CVistorsRecord::LogIn()
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
//BOOL CVistorsRecord::LogOut()
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

BOOL CVistorsRecord::CheckLoginOk()
{
	if (0 < m_lLoginID)
		return TRUE;
	MessageBox(_T("��δ��¼��"), "", MB_OK);
	return FALSE;
}
///////////////////////////////////////////////////////////////////////////////////

// CVistorsRecord ��Ϣ�������
BOOL CVistorsRecord::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

   // TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_datetimebegin.SetFormat(_T("yyyy-MM-dd    HH:mm:ss"));
	m_datetimeend.SetFormat(_T("yyyy-MM-dd    HH:mm:ss"));

	CRect rect;
	m_listRcfInfo.GetClientRect(&rect);

	m_listRcfInfo.SetExtendedStyle(m_listRcfInfo.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listRcfInfo.InsertColumn(0, _T("����"), LVCFMT_LEFT, rect.Width() / 10, 0);
	m_listRcfInfo.InsertColumn(1, _T("�Ա�"), LVCFMT_LEFT, rect.Width() / 12, 1);
	m_listRcfInfo.InsertColumn(2, _T("���֤��"), LVCFMT_LEFT, rect.Width() / 7, 2);
	m_listRcfInfo.InsertColumn(3, _T("�Ǽ�ʱ��"), LVCFMT_LEFT, rect.Width() / 7, 3);
	m_listRcfInfo.InsertColumn(4, _T("ǩ��ʱ��"), LVCFMT_LEFT, rect.Width() / 7, 4);
	m_listRcfInfo.InsertColumn(5, _T("����������"), LVCFMT_LEFT, rect.Width() / 8, 5);
	m_listRcfInfo.InsertColumn(6, _T("�ÿ�סַ"), LVCFMT_LEFT, rect.Width() / 3, 6);
	m_listRcfInfo.InsertColumn(7, _T("������סַ"), LVCFMT_LEFT, rect.Width() / 3, 7);
	m_listRcfInfo.InsertColumn(8, _T("�Ƿ������"), LVCFMT_LEFT, rect.Width() / 7, 8);
	m_listRcfInfo.InsertColumn(9, _T("�Ƿ�ǩ��"), LVCFMT_LEFT, rect.Width() / 7, 9);


	CRect rect1;
	GetClientRect(&rect1);     //ȡ�ͻ�����С  
	old.x = rect1.right - rect1.left;
	old.y = rect1.bottom - rect1.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);
	m_ShowPath = "";

	/**************************�����ϴ� ��ʼ************************************/
	//InitLoginParams(); //��ʼ���������

	
	/*if (!LogIn())
	{
		return FALSE;
	}*/
	/**************************�����ϴ� ����**************************************/


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}



void CVistorsRecord::OnBnClickedButton3()  //���������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CVistorsRecord::OnBnClickedButton2() //������ѯ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CVistorsRecord::OnBnClickedButton1()  //ȫ����ѯ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CVistorsRecord::OnLvnItemchangedListvrecord(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	UpdateData(TRUE);
	m_SelectId = "";
	m_SelectName = "";
	NMLISTVIEW *pNMListView = (NMLISTVIEW*)pNMHDR;
	if (-1 != pNMListView->iItem)        // ���iItem����-1����˵�����б��ѡ��   
	{
		// ��ȡ��ѡ���б����һ��������ı�   
		m_SelectId = m_listRcfInfo.GetItemText(pNMListView->iItem, 2);
		m_SelectName = m_listRcfInfo.GetItemText(pNMListView->iItem, 0);

		UpdateData(FALSE);
		OnBnClickedBtnselect();
	}
}


void CVistorsRecord::OnBnClickedBtnselectall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		m_listRcfInfo.DeleteAllItems();

		m_pRecordSet->Open("SELECT * FROM [FaceContCen].[dbo].[FK_UserTabel]", m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		CString BFZName = _T(""); 
		CString Name = _T("");
		CString Sex = _T("");
		CString BFZAddr = _T("");
		CString BeginTime = _T("");
		CString EndTime = _T("");
		CString FZAddr = _T("");
		CString QL = _T("");
		CString SFHMD = _T("");
		CString ID = _T("");

		for (int i = 0; !m_pRecordSet->adoEOF; i++)
		{			
			Name = m_pRecordSet->GetCollect(_variant_t(_T("Name")));
			Sex = m_pRecordSet->GetCollect(_variant_t(_T("Sex")));
			BFZName = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_Name")));
			FZAddr = m_pRecordSet->GetCollect(_variant_t(_T("FK_Addr")));		
			ID = m_pRecordSet->GetCollect(_variant_t(_T("IDCardNum")));//����id�ţ�Ψһ
			m_BFZ_FH_String = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_FH")));
			m_BFZ_LH_String = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_LH")));
			BFZAddr = _T("¥�ţ�") + m_BFZ_FH_String + _T("   ���ţ�") + m_BFZ_LH_String;
			SFHMD = m_pRecordSet->GetCollect(_variant_t(_T("HMD")));
			BeginTime = m_pRecordSet->GetCollect(_variant_t(_T("BeginTime")));

			
			_variant_t varSFQL;			//�Ƿ�ǩ��
			varSFQL = m_pRecordSet->GetCollect(_variant_t(_T("SingnOff")));
			if (varSFQL.vt != VT_NULL)   //�����Ϊ��
			{
				QL = varSFQL;
			}			
			_variant_t varEndTime;//ǩ��ʱ��			
			varEndTime = m_pRecordSet->GetCollect(_variant_t(_T("QL_Time")));
			if (varEndTime.vt != VT_NULL)//�����Ϊ��
			{
				EndTime = varEndTime;
			}


			m_listRcfInfo.InsertItem(i, Name.GetString());
			m_listRcfInfo.SetItemText(i, 1, Sex.GetBuffer(0));
			m_listRcfInfo.SetItemText(i, 2, ID.GetString());
			m_listRcfInfo.SetItemText(i, 3, BeginTime.GetString());
			m_listRcfInfo.SetItemText(i, 4, EndTime.GetString());
			m_listRcfInfo.SetItemText(i, 5, BFZName.GetString());
			m_listRcfInfo.SetItemText(i, 6, FZAddr.GetString());
			m_listRcfInfo.SetItemText(i, 7, BFZAddr.GetString());
			m_listRcfInfo.SetItemText(i, 8, SFHMD.GetString());
			m_listRcfInfo.SetItemText(i, 9, QL.GetString());
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
			m_pRecordSet->Close(); //�رռ�¼�� 
		}
		CATCH_ERROR;
	}
	

	////////////////////////��־////////////////////////////////////////////
	g_Action = _T("��ѯ���зÿ��û�");

	CTime tmp_tm = CTime::GetCurrentTime();
	CString TimeEnd = tmp_tm.Format("%Y-%m-%d %H:%M:%S");
	try
	{
		CString Sql;
		Sql.Format(_T("INSERT INTO [FaceContCen].[dbo].[SysRunLog](IdNum,Name,QX,BeginData,EndData,Action,Ip,SysRun) Values(%d,'%s','%s','%s','%s','%s','%s','%s')"), g_UserId, g_UseName, g_QX, g_Time, TimeEnd, g_Action, g_Ip, g_SysRunRZ);
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


}


void CVistorsRecord::OnBnClickedBtnselect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_SelectId.IsEmpty() && m_SelectId == "" && m_SelectName.IsEmpty() && m_SelectName == "")
	{
		MessageBox( _T("��ѯ��������Ϊ�գ�"),_T("����"),MB_OK|MB_ICONERROR);
		UpdateData(FALSE);

		return;
	}
	try
	{
		CString Sql = _T("");  //
		Sql.Format(_T("SELECT * FROM [FaceContCen].[dbo].[FK_UserTabel] WHERE IDCardNum = '%s' OR Name = '%s'"), m_SelectId.GetBuffer(0), m_SelectName.GetBuffer(0));

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		_variant_t varName;		 //����
		varName = m_pRecordSet->GetCollect(_variant_t(_T("Name")));
		if (VT_NULL != varName.vt){
			m_Name_String = varName;
		}else{
			m_Name_String = "";
		}

		_variant_t varId;		 //��Ƭ���
		varId = m_pRecordSet->GetCollect(_variant_t(_T("IDNum")));
		if (VT_NULL != varId.vt){
			m_PicId_string = varId;
		}else{
			m_PicId_string = "";
		}

		_variant_t varSex;  //�Ա�
		varSex = m_pRecordSet->GetCollect(_variant_t(_T("Sex")));
		if (VT_NULL != varSex.vt)		{
			m_Sex_String = varSex;	
		}		else		{
			m_Sex_String = "";
		}

		_variant_t varBeginTime;  //����ʱ��
		varBeginTime = m_pRecordSet->GetCollect(_variant_t(_T("BeginTime")));
		if (VT_NULL != varBeginTime.vt)		{
			m_BeginTime_String = varBeginTime;
		}		else		{
			m_BeginTime_String = "";
		}

		_variant_t varFKAddr;  //�ÿ�סַ
		varFKAddr = m_pRecordSet->GetCollect(_variant_t(_T("FK_Addr")));
		if (VT_NULL != varFKAddr.vt)		{
			m_FK_String = varFKAddr;
		}		else		{
			m_FK_String = "";
		}

		_variant_t varFH;  //�����ߵķ����
		varFH = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_FH")));
		if (VT_NULL != varFH.vt)		{
			m_strFH = varFH;
		}
		else		{
			m_strFH = "";
		}

		_variant_t varLH;   //�����ߵ�¥���
		varLH = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_LH")));
		if (VT_NULL != varLH.vt){
			m_strLH = varLH;
		}else{
			m_strLH = "";
		}

		_variant_t varPicturePath;   //��Ƭ��·��
		varPicturePath = m_pRecordSet->GetCollect(_variant_t(_T("PicturePath")));
		if (VT_NULL != varPicturePath.vt){
			m_Picture_Path = varPicturePath;
		}else{
			m_Picture_Path = "";
		}

		_variant_t varHMD;  //�Ƿ������
		varHMD = m_pRecordSet->GetCollect(_variant_t(_T("HMD")));
		if (VT_NULL != varHMD.vt){
			m_HMD_String = varHMD;
		}else{
			m_HMD_String = "";
		}

		_variant_t FP; //Ψһ����id��
		FP = m_pRecordSet->GetCollect(_variant_t(_T("IDCardNum"))); //id
		if (VT_NULL != FP.vt){
			m_ID_String = FP;
		}else		{
			m_ID_String = "";
		} 

		_variant_t varEndTime; //ǩ��ʱ��
		varEndTime = m_pRecordSet->GetCollect(_variant_t(_T("QL_Time")));
		if (varEndTime.vt != VT_NULL){
			m_EndTime_Str = varEndTime;
		}else{
			m_EndTime_Str = "";
		}
		
		_variant_t varBFZName;//����������
		varBFZName = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_Name")));
		if (varBFZName.vt != VT_NULL){
			m_BFZ_String = varBFZName;
		}else{
			m_BFZ_String = "";
		}		
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
		m_strPath = _T("C:\\YTPicture\\FKPicture");//ÿ�ΰ�ѡ��·����cspath����ֹcstring���ӣ�����
		if (!PathIsDirectory(m_strPath))
		{
			CreateDirectory(m_strPath, 0);//�������򴴽�	}��
		}
		m_strPath += _T("\\") + m_PicId_string + _T(".jpg");  //��Ƭ·��

	    /************************************************************************/
	    /*  EJZToPicture()�����ݿ��еĶ�������Ƭ���ݴ浽����c��                 */
	    /************************************************************************/
		if (EJZToPicture(m_strPath, m_PicLen, varPicDate) != TRUE)
		{
			m_YL_String = _T("������Ƭ����ʧ�ܣ�");
		}

		Sql.ReleaseBuffer();
	}
	catch (_com_error e)
	{

		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //�رռ�¼�� 
		}
		CATCH_ERROR;
	}
	Ui_Show();

	UpdateData(FALSE);
}


void CVistorsRecord::OnEnChangeEvrfname()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CVistorsRecord::OnBnClickedBtnjionbt()  //ֱ��ɾ�����������������sql�ֶ�Ϊ������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (TRUE != CheckLoginOk())
		return;

	/*if (UpFacePicture(m_PicId_string, m_lLoginID, m_Picture_Path) != TRUE){
		return;
	}*/

	if (DropFacePicture(m_PicId_string, m_lLoginID) == TRUE) 
	{
		m_YL_String = _T("��Ƭ����������ɹ���");
	}

	try
	{		
		CString Sql;
		Sql.Format(_T("UPDATE [FaceContCen].[dbo].[FK_UserTabel] SET HMD = '%s' WHERE IDCardNum = '%s'"),_T("��"), m_ID_String);

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}

		m_YL_String = m_ID_String + _T("\n  ����: ") + m_Name_String + _T("\n  ����������ɹ�");
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}
		m_YL_String = _T("���������ʧ��,����һ��");
		CATCH_ERROR;	
	}

	UpdateData(FALSE);
}


void CVistorsRecord::OnEnChangeEvrfid()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CVistorsRecord::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}

	
}


void CVistorsRecord::ReSize()
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
		
		if (woc == IDC_COMBVRFSEX)
		{
			OldTLPoint = Rect.TopLeft();
			TLPoint.x = float(OldTLPoint.x*fsp[0]) + 0.5;
			TLPoint.y = float(OldTLPoint.y*fsp[1]) + 0.5;
			BRPoint.x = TLPoint.x + Rect.Width();
			BRPoint.y = TLPoint.y + Rect.Height();
			Rect.SetRect(TLPoint, BRPoint);
			GetDlgItem(woc)->MoveWindow(Rect, TRUE);
			//hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
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
			//hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
		}
		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}
	old = Newp;
}


void CVistorsRecord::OnEnChangeEdit11()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CVistorsRecord::OnStnClickedStaticpt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CVistorsRecord::Ui_Show()
{

	CString g_strPictureShow;
	g_strPictureShow = m_strPath;

	CString strExt(".jpg");
	if (g_strPictureShow.IsEmpty() || -1 == g_strPictureShow.Find(strExt.GetBuffer(0)))
	{
		return;
	}

	CImage image;
	if (image.Load(g_strPictureShow))
	{
		return;
	}	

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


void CVistorsRecord::OnBnClickedBtndelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/************************ǩ��ɾ������***��ʼ*********************************************/
	if (TRUE != CheckLoginOk())
		return;

	/*if (DropFacePicture(m_PicId_string, m_lLoginID) != TRUE){
		return;
	}*/

	try
	{
		CString Sql;
		Sql.Format(_T("UPDATE [FaceContCen].[dbo].[FK_UserTabel] SET  HMD = '%s'  WHERE IDCardNum = '%s'"), "��",m_ID_String.GetBuffer(0));

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		m_YL_String = _T(" ID: ") + m_ID_String + _T(" ����: ") + m_Name_String + _T(" ɾ���������ɹ�");

	}
	catch (_com_error e)
	{
		AfxMessageBox(_T(" ID: ") + m_ID_String + _T("\n ����: ") + m_Name_String + _T("\n ɾ��������ʧ�ܣ�������һ��"));

		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}
	}
	if (m_pRecordSet->State)
	{
		m_pRecordSet->Close();
	}

	UpdateData(FALSE);
}



void CVistorsRecord::OnPaint()
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
	//Image image(L"./res/BG_BKALL.jpg", TRUE);
	//graphics.DrawImage(&image, 0, 0, rect.right, rect.bottom);  //���Ʊ���
}



void CVistorsRecord::OnCbnDropdownCombvrfsex()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CVistorsRecord::OnBnClickedBtnselectallHmd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	try
	{
		m_listRcfInfo.DeleteAllItems();

		m_pRecordSet->Open("SELECT * FROM [FaceContCen].[dbo].[FK_UserTabel] WHERE HMD = '��'", m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		CString BFZName = _T("");
		CString Name = _T("");
		CString Sex = _T("");
		CString BFZAddr = _T("");
		CString BeginTime = _T("");
		CString EndTime = _T("");
		CString FZAddr = _T("");
		CString QL = _T("");
		CString SFHMD = _T("");
		CString ID = _T("");

		for (int i = 0; !m_pRecordSet->adoEOF; i++)
		{
			Name = m_pRecordSet->GetCollect(_variant_t(_T("Name")));
			Sex = m_pRecordSet->GetCollect(_variant_t(_T("Sex")));
			BFZName = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_Name")));
			FZAddr = m_pRecordSet->GetCollect(_variant_t(_T("FK_Addr")));
			ID = m_pRecordSet->GetCollect(_variant_t(_T("IDCardNum")));//����id�ţ�Ψһ
			m_BFZ_FH_String = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_FH")));
			m_BFZ_LH_String = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_LH")));
			BFZAddr = _T("¥�ţ�") + m_BFZ_FH_String + _T("   ���ţ�") + m_BFZ_LH_String;
			SFHMD = m_pRecordSet->GetCollect(_variant_t(_T("HMD")));
			BeginTime = m_pRecordSet->GetCollect(_variant_t(_T("BeginTime")));


			_variant_t varSFQL;			//�Ƿ�ǩ��
			varSFQL = m_pRecordSet->GetCollect(_variant_t(_T("SingnOff")));
			if (varSFQL.vt != VT_NULL)   //�����Ϊ��
			{
				QL = varSFQL;
			}
			_variant_t varEndTime;//ǩ��ʱ��			
			varEndTime = m_pRecordSet->GetCollect(_variant_t(_T("QL_Time")));
			if (varEndTime.vt != VT_NULL)//�����Ϊ��
			{
				EndTime = varEndTime;
			}


			m_listRcfInfo.InsertItem(i, Name.GetString()); //����list����
			m_listRcfInfo.SetItemText(i, 1, Sex.GetBuffer(0));
			m_listRcfInfo.SetItemText(i, 2, ID.GetString());
			m_listRcfInfo.SetItemText(i, 3, BeginTime.GetString());
			m_listRcfInfo.SetItemText(i, 4, EndTime.GetString());
			m_listRcfInfo.SetItemText(i, 5, BFZName.GetString());
			m_listRcfInfo.SetItemText(i, 6, FZAddr.GetString());
			m_listRcfInfo.SetItemText(i, 7, BFZAddr.GetString());
			m_listRcfInfo.SetItemText(i, 8, SFHMD.GetString());
			m_listRcfInfo.SetItemText(i, 9, QL.GetString());
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
			m_pRecordSet->Close(); //�رռ�¼�� 
		}
		CATCH_ERROR;
	}

	UpdateData(FALSE);
}


void CVistorsRecord::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}


void CVistorsRecord::OnBnClickedBtnselecttime()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_listRcfInfo.DeleteAllItems();
	try
	{
		CString Sql;

		Sql.Format("SELECT * FROM [FaceContCen].[dbo].[FK_UserTabel] WHERE AutoTime BETWEEN '%d-%d-%d %d:%d:%d' and '%d-%d-%d %d:%d:%d'", m_Begin_String.GetYear(), m_Begin_String.GetMonth(), m_Begin_String.GetDay(), m_Begin_String.GetHour(), m_Begin_String.GetMinute(), m_Begin_String.GetSecond(), m_EndTime_String.GetYear(), m_EndTime_String.GetMonth(), m_EndTime_String.GetDay(), m_EndTime_String.GetHour(), m_EndTime_String.GetMinute(), m_EndTime_String.GetSecond());

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);
		CString BFZName = _T("");
		CString Name = _T("");
		CString Sex = _T("");
		CString BFZAddr = _T("");
		CString BeginTime = _T("");
		CString EndTime = _T("");
		CString FZAddr = _T("");
		CString QL = _T("");
		CString SFHMD = _T("");
		CString ID = _T("");

		for (int i = 0; !m_pRecordSet->adoEOF; i++)
		{
			Name = m_pRecordSet->GetCollect(_variant_t(_T("Name")));
			Sex = m_pRecordSet->GetCollect(_variant_t(_T("Sex")));
			BFZName = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_Name")));
			FZAddr = m_pRecordSet->GetCollect(_variant_t(_T("FK_Addr")));
			ID = m_pRecordSet->GetCollect(_variant_t(_T("IDCardNum")));//����id�ţ�Ψһ
			m_BFZ_FH_String = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_FH")));
			m_BFZ_LH_String = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_LH")));
			BFZAddr = _T("¥�ţ�") + m_BFZ_FH_String + _T("   ���ţ�") + m_BFZ_LH_String;
			SFHMD = m_pRecordSet->GetCollect(_variant_t(_T("HMD")));
			BeginTime = m_pRecordSet->GetCollect(_variant_t(_T("BeginTime")));


			_variant_t varSFQL;			//�Ƿ�ǩ��
			varSFQL = m_pRecordSet->GetCollect(_variant_t(_T("SingnOff")));
			if (varSFQL.vt != VT_NULL)   //�����Ϊ��
			{
				QL = varSFQL;
			}
			_variant_t varEndTime;//ǩ��ʱ��			
			varEndTime = m_pRecordSet->GetCollect(_variant_t(_T("QL_Time")));
			if (varEndTime.vt != VT_NULL)//�����Ϊ��
			{
				EndTime = varEndTime;
			}


			m_listRcfInfo.InsertItem(i, Name.GetString()); //����list����
			m_listRcfInfo.SetItemText(i, 1, Sex.GetBuffer(0));
			m_listRcfInfo.SetItemText(i, 2, ID.GetString());
			m_listRcfInfo.SetItemText(i, 3, BeginTime.GetString());
			m_listRcfInfo.SetItemText(i, 4, EndTime.GetString());
			m_listRcfInfo.SetItemText(i, 5, BFZName.GetString());
			m_listRcfInfo.SetItemText(i, 6, FZAddr.GetString());
			m_listRcfInfo.SetItemText(i, 7, BFZAddr.GetString());
			m_listRcfInfo.SetItemText(i, 8, SFHMD.GetString());
			m_listRcfInfo.SetItemText(i, 9, QL.GetString());
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
			m_pRecordSet->Close(); //�رռ�¼�� 
		}
		CATCH_ERROR;
	}

	UpdateData(FALSE);
}


void CVistorsRecord::OnBnClickedBtndelete2() //�����������������ɾ����Ϣ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (m_PicId_string.IsEmpty())
	{
		m_YL_String = _T("��ƬidΪ�գ�ɾ��ʧ��");
		UpdateData(FALSE);

		return;
	}

	if (DropFacePicture(m_PicId_string, m_lLoginID) == TRUE)
	{
		//m_YL_String = _T("��Ƭ����������ɹ���");
	}

	try    //ɾ�����ݿ⻧������
	{
		CString Sql;
		Sql.Format("DELETE  FROM [FaceContCen].[dbo].[FK_UserTabel] WHERE IDNum = '%s'", m_PicId_string);

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //�رռ�¼�� 
		}

		Sql.ReleaseBuffer();
		m_YL_String = _T(" ID: ") + m_PicId_string + _T("\n  ����: ") + m_Name_String + _T("\n  ɾ���ɹ�");
	
	}
	catch (_com_error e)
	{
		m_YL_String = _T(" ID: ") + m_PicId_string + _T("\n ����: ") + m_Name_String + _T("\n ɾ��ʧ�ܣ�������ɾ��");

		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}
	}

	InvalidateRect(NULL, FALSE);

	UpdateData(FALSE);
}
