// GetOwerInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "GetOwerInfo.h"
#include "afxdialogex.h"


// CGetOwerInfo �Ի���

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


// CGetOwerInfo ��Ϣ�������


void CGetOwerInfo::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CGetOwerInfo::OnEnChangeEditXqeditNum()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
