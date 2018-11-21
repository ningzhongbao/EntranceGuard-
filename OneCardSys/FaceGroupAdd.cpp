// FaceGroupAdd.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "FaceGroupAdd.h"
#include "afxdialogex.h"


// CFaceGroupAdd 对话框

IMPLEMENT_DYNAMIC(CFaceGroupAdd, CDialogEx)

CFaceGroupAdd::CFaceGroupAdd(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIA_ADDFACE, pParent)	
	, m_edit_alias_string(_T(""))
	, m_edit_int_enable(1)
	, m_edit_string_search_threshold(_T("73.00"))
	, m_edit_int_top_rank(0)
{
	
}

CFaceGroupAdd::~CFaceGroupAdd()
{
}

void CFaceGroupAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BN, m_edit_alias_string);
	DDX_Text(pDX, IDC_EDIT_GN, m_edit_int_enable);
	DDX_Text(pDX, IDC_EDIT_SBFZ, m_edit_string_search_threshold);
	DDX_Text(pDX, IDC_EDIT_DBSX, m_edit_int_top_rank);
}


BEGIN_MESSAGE_MAP(CFaceGroupAdd, CDialogEx)
	ON_BN_CLICKED(IDC_Btn_Create, &CFaceGroupAdd::OnBnClickedBtnCreate)
	ON_BN_CLICKED(IDC_BtnCannel, &CFaceGroupAdd::OnBnClickedBtncannel)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////////////////////
CString CFaceGroupAdd::GetAliasString()
{
	return m_edit_alias_string;
}

BOOL CFaceGroupAdd::GetFaceGroupEnable()
{
	return (0 != m_edit_int_enable) ? TRUE : FALSE;
}

float CFaceGroupAdd::GetSearchThreshold()
{
	float fRet = atof(m_edit_string_search_threshold.GetBuffer(0));
	m_edit_string_search_threshold.ReleaseBuffer();
	return fRet;
}

UINT CFaceGroupAdd::GetTopRank()
{
	return m_edit_int_top_rank;
}

/////////////////////////////////////////////////////////////////////////////////////////////

// CFaceGroupAdd 消息处理程序


void CFaceGroupAdd::OnBnClickedBtnCreate()
{
	// TODO: 在此添加控件通知处理程序代码

	this->UpdateData(TRUE);

	CDialog::OnOK();
}


void CFaceGroupAdd::OnBnClickedBtncannel()
{
	// TODO: 在此添加控件通知处理程序代码

	CDialog::OnCancel();
}
