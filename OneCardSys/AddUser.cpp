// AddUser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "AddUser.h"
#include "afxdialogex.h"


// CAddUser �Ի���

IMPLEMENT_DYNAMIC(CAddUser, CDialogEx)

CAddUser::CAddUser(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIAADDUSER, pParent)
	, m_User(_T(""))
	, m_PWD(_T(""))
	, m_Name(_T(""))
	, m_Sex(_T(""))
	, m_User_Type(_T(""))
	, m_Addr_String(_T(""))
	, m_ID_String(_T(""))
{

}

CAddUser::~CAddUser()
{
}

void CAddUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ZH, m_User);
	DDX_Text(pDX, IDC_EDIT_PWD, m_PWD);
	DDX_Text(pDX, IDC_EDIT_Name, m_Name);
	DDX_CBString(pDX, IDC_COMBO1, m_Sex);
	DDX_Control(pDX, IDC_EDIT_IDNUM, m_Id);
	DDX_CBString(pDX, IDC_COMBO2, m_User_Type);
	DDX_Text(pDX, IDC_EDIT_Addr, m_Addr_String);
	DDX_Text(pDX, IDC_EDIT_IDNUM, m_ID_String);
}


BEGIN_MESSAGE_MAP(CAddUser, CDialogEx)
	ON_BN_CLICKED(IDC_BtnCannel, &CAddUser::OnBnClickedBtncannel)
	ON_BN_CLICKED(IDC_BtnOK, &CAddUser::OnBnClickedBtnok)
END_MESSAGE_MAP()


// CAddUser ��Ϣ�������


void CAddUser::OnBnClickedBtncannel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CDialogEx::OnCancel();
}

void CAddUser::ClearDate()
{
	m_User = "";
	m_PWD = "";
	m_Name = "";
	m_Sex = "";
	m_User_Type = "";
	m_Addr_String = "";
	m_ID_String = "";
}

void CAddUser::OnBnClickedBtnok()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);  //2018-9-21 add

	if ((m_User == "" || m_User.IsEmpty()) && (m_PWD == "" || m_PWD.IsEmpty()))
	{
		AfxMessageBox("�˺ź����벻��Ϊ�գ�");
		return;
	}

	if (m_User_Type.IsEmpty() || m_User_Type == "")
	{
		AfxMessageBox(_T("�˻����Ͳ���Ϊ��!"));
		return;
	}
	if (m_ID_String == "" || m_ID_String.IsEmpty())
	{
		AfxMessageBox(_T("���֤����Ϊ��!"));
		return;
	}

	int nLen = m_ID_String.GetLength();
	for (int i = 0; i < nLen; i++)
	{
		if (!(m_ID_String.GetAt(i) >= '0' && m_ID_String.GetAt(i) <= '9' || m_ID_String.GetAt(i) >= 'A' && m_ID_String.GetAt(i) <= 'Z'))
		{
			MessageBox(_T("���֤��ʽ����"), _T("����������"), 0);
			return;
		}
	}

	if (m_Name.IsEmpty() || m_Name == "")
	{
		MessageBox(_T("����Ϊ��", NULL, 0));
		return;
	}

	try
	{
		CString Sql;

		Sql.Format("INSERT INTO  [FaceContCen].[dbo].[User] (IdNum,PWD,Type,Name,IDCard,Addr) VALUES('%s','%s','%s','%s','%s','%s')",m_User.GetBuffer(0),m_PWD.GetBuffer(0),m_User_Type.GetBuffer(0),m_Name.GetBuffer(0),m_Sex.GetBuffer(0), m_ID_String.GetBuffer(0),m_Addr_String.GetBuffer(0));

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();			
		}
		AfxMessageBox(_T("����û��ɹ�!"));
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}

		CATCH_ERROR;
	}	

	ClearDate();

	UpdateData(FALSE);
}
