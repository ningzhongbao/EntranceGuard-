// DeleUser.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "DeleUser.h"
#include "afxdialogex.h"


// CDeleUser 对话框

IMPLEMENT_DYNAMIC(CDeleUser, CDialogEx)

CDeleUser::CDeleUser(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIADEL, pParent)
	, m_User_String(_T(""))
{

}

CDeleUser::~CDeleUser()
{
}

void CDeleUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER, m_User_String);
}


BEGIN_MESSAGE_MAP(CDeleUser, CDialogEx)
	ON_BN_CLICKED(IDC_BtnDel, &CDeleUser::OnBnClickedBtndel)
	ON_BN_CLICKED(IDC_BtnCanl, &CDeleUser::OnBnClickedBtncanl)
END_MESSAGE_MAP()


// CDeleUser 消息处理程序


void CDeleUser::OnBnClickedBtndel()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	try
	{
		CString Sql;

		Sql.Format(_T("DELETE  FROM [FaceContCen].[dbo].[User] WHERE IdNum = '%s'"),m_User_String.GetBuffer(0));
		HRESULT hRes = NULL;

		hRes = m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		AfxMessageBox(_T("删除用户成功!"));
	
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
		AfxMessageBox(_T("用户不存在!"));
		//CATCH_ERROR;
	}

}


void CDeleUser::OnBnClickedBtncanl()
{
	// TODO: 在此添加控件通知处理程序代码

	CDialogEx::OnCancel();
}
