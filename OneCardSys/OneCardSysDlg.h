
// OneCardSysDlg.h : ͷ�ļ�
//

#pragma once
#include "SysMainUi.h"

// COneCardSysDlg �Ի���
class COneCardSysDlg : public CDialogEx
{
// ����
public:
	COneCardSysDlg(CWnd* pParent = NULL);	// ��׼���캯��
	~COneCardSysDlg();
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ONECARDSYS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
	CPropertySheet	m_sheet;	 // ����ҳ��������������4����ǩ��ҳ�棩
	CPicture1       m_Picture;   //��ʾ���������Ϣ����ҳ
	CFont m_Font;
	CStatic m_static;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

public:	//�û��Զ������
	CString m_strUser;
	CString m_strPwd;

	int  User; //�û�id
	CString  Pwd; //����
	_bstr_t        m_bstrConn;     //�洢�������ݿ���ַ���
	_bstr_t        m_sqlCmd;       //�洢sql���

	
public:	//�û��Զ��庯��
	BOOL ConnectionSql();  //�������ݿ�

	CString GetLocalHostIP();  //��ȡip

	//
	//BOOL InitLoginParams();//�����������ʼ��
	//BOOL LogIn();  //��½
	//BOOL LogOut();  //�ǳ�
	void COneCardSysDlg::OperRZ(CString g_Action);//��־



public:
	afx_msg void OnBnClickedBtnlogin();
	afx_msg void OnBnClickedBtncannel();
	afx_msg void OnEnChangeEditUser();
	afx_msg void OnClose();
};
