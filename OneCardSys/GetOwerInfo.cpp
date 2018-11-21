// GetOwerInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "GetOwerInfo.h"
#include "afxdialogex.h"


// CGetOwerInfo 对话框

IMPLEMENT_DYNAMIC(CGetOwerInfo, CDialogEx)

CGetOwerInfo::CGetOwerInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GETYZINFO, pParent)
{

}

CGetOwerInfo::~CGetOwerInfo()
{
}

void CGetOwerInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CGetOwerInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CGetOwerInfo::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT_XQEDIT_NUM, &CGetOwerInfo::OnEnChangeEditXqeditNum)
END_MESSAGE_MAP()


// CGetOwerInfo 消息处理程序


void CGetOwerInfo::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CGetOwerInfo::OnEnChangeEditXqeditNum()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
