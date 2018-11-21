// ViSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "ViSet.h"
#include "afxdialogex.h"


// CViSet �Ի���

IMPLEMENT_DYNAMIC(CViSet, CDialogEx)

CViSet::CViSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIAVISET, pParent)
	, m_ZPIP_String(_T(""))
	, m_ZPPort_Int(0)
	, m_ZPUser_String(_T(""))
	, m_ZPPWD_String(_T(""))
	, m_SBIP_String(_T(""))
	, m_SBPort_Int(0)
	, m_SBUSer_String(_T(""))
	, m_SBPWD_String(_T(""))
{
	InitViParam();//��ʼ�������ip	
}

CViSet::~CViSet()
{
}

void CViSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ZPIP, m_ZPIP_String);
	DDX_Text(pDX, IDC_ZPPort, m_ZPPort_Int);
	DDX_Text(pDX, IDC_ZPUser, m_ZPUser_String);
	DDX_Text(pDX, IDC_ZPPWD, m_ZPPWD_String);
	DDX_Text(pDX, IDC_SBIP, m_SBIP_String);
	DDX_Text(pDX, IDC_SBPort, m_SBPort_Int);
	DDX_Text(pDX, IDC_SBUser, m_SBUSer_String);
	DDX_Text(pDX, IDC_SBPWD, m_SBPWD_String);
}


BEGIN_MESSAGE_MAP(CViSet, CDialogEx)
	ON_BN_CLICKED(IDC_SBBtnLogin, &CViSet::OnBnClickedSbbtnlogin)
	ON_BN_CLICKED(IDC_ZPBtnLogin, &CViSet::OnBnClickedZpbtnlogin)
	ON_BN_CLICKED(IDC_ZPBtnLogOut, &CViSet::OnBnClickedZpbtnlogout)
	ON_BN_CLICKED(IDC_SBBtnLogOut, &CViSet::OnBnClickedSbbtnlogout)
END_MESSAGE_MAP()


// CViSet ��Ϣ�������


void CViSet::InitViParam()
{
	//UpdateData(TRUE);
	//ץ�Ļ�ip����
	m_ZPIP_String = "192.168.35.8";
	m_ZPPort_Int = 3000;
	m_ZPUser_String = "admin";
	m_ZPPWD_String = "admin123";

	//ʶ���ip����
	m_SBIP_String = "192.168.35.6";
	m_SBPort_Int = 3000;
	m_SBUSer_String = "admin";
	m_SBPWD_String = "admin123";
	
//	this->UpdateData(FALSE);
}

void CViSet::OnBnClickedSbbtnlogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	InitLoginParams();  //��ʼ���������
	m_lLoginID = LogIn(m_SBIP_String, m_SBPort_Int, m_SBUSer_String, m_SBPWD_String); //ʶ��������ֵ

	if (0 >= m_lLoginID)
	{
		MessageBox(_T("�ſ�����ʶ�����½ʧ�ܣ������豸�Ƿ����ߣ�"), _T("ʶ�����½��ʾ"), MB_ICONHAND);

		return;
	}
	else
	{
		MessageBox(_T("�ſ�����ʶ�����½�ɹ���"), _T("ʶ�����½��ʾ"), MB_OK);
	}

}


static void CALLBACK disconnect_callback(LLONG lLoginID, char *lpszIP, LONG nPort, LDWORD dwUser)
{
	// TODO: 
	m_lLoginID = 0;
	m_ZPLoginID = 0;
}


BOOL CViSet::InitLoginParams() //�����ϴ������ʼ��
{
	Net_Init(disconnect_callback, (LDWORD)(void*)this); //��ʼ��sdk��

	return TRUE;
}

LLONG CViSet::LogIn(CString strIp, INT nPort, CString strUser, CString strPwd)
{
	LLONG llogin = 0;
	llogin = Net_LoginDevice(strIp.GetBuffer(), nPort,
		strUser.GetBuffer(), strPwd.GetBuffer(), NULL, &m_nError); //��½

	return llogin;
}


BOOL CViSet::LogOut(LLONG lLoginHand)
{
	if (lLoginHand)
	{
		if (Net_LogoutDevice(lLoginHand))
		{
			lLoginHand = 0;
			// �����������Դ
			Net_Exit();

			return TRUE;
		}
	}

	return FALSE;
}

void CViSet::OnBnClickedZpbtnlogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	InitLoginParams();  //��ʼ���������

	m_ZPLoginID = LogIn(m_ZPIP_String, m_ZPPort_Int, m_ZPUser_String, m_ZPPWD_String); //ץ�Ļ������ֵ

	if (0 >= m_ZPLoginID)
	{
		MessageBox(_T("ץ�Ļ���½ʧ�ܣ������豸�Ƿ����ߣ�"), _T("ץ�Ļ���½"), MB_ICONHAND);

		return ;
	}
	else
	{
		MessageBox(_T("ץ�Ļ���½�ɹ���"), _T("ץ�Ļ���½"), 0);
	}
}


//BOOL CViSet::OnInitDialog()
//{
//	CDialogEx::OnInitDialog();
//
//	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//				  // �쳣: OCX ����ҳӦ���� FALSE
//}


void CViSet::OnBnClickedZpbtnlogout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!LogOut(m_ZPLoginID))
	{
		MessageBox("ץ�Ļ��ǳ�ʧ��", "�ǳ���ʾ ", MB_ICONHAND);
	}
	else
	{
		MessageBox(_T("ץ�Ļ��ǳ��ɹ���"), _T("�ǳ���ʾ"), 0);
	}
}

BOOL CViSet::AllViLogin()
{
	OnBnClickedZpbtnlogin();
	OnBnClickedSbbtnlogin();

	return TRUE;
}


void CViSet::OnBnClickedSbbtnlogout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!LogOut(m_lLoginID))
	{
		MessageBox("ʶ����ǳ�ʧ��", "�ǳ���ʾ ", MB_ICONHAND);
	}
	else
	{
		MessageBox("ʶ����ǳ��ɹ�", "�ǳ���ʾ", MB_OK);
	}
}

void CViSet::AllLogOut()
{
	OnBnClickedSbbtnlogout();
	OnBnClickedZpbtnlogout();
}
