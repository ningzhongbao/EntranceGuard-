#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "YCodec.h"//�������ı���
#include <atlconv.h>
#include <iostream>
// CPersComprResult �Ի���


typedef struct DatePack
{
	SOCKET *pClientSocket;
	unsigned char *recvline;
};

class CPersComprResult : public CDialogEx
{
	DECLARE_DYNAMIC(CPersComprResult)

public:
	CPersComprResult(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPersComprResult();

	// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGPERSCOMRELT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	BOOL InitSocket();
	static DWORD WINAPI WaitProc(LPVOID lpPar);
	static DWORD WINAPI RespondProc(LPVOID lpPar);

	static DWORD WINAPI FKThreadProc(LPVOID lpPar);
	static DWORD WINAPI FZThreadProc(LPVOID lpPar);
	HANDLE m_hWaitThread; /* �ȴ������߳� */
	HANDLE m_hRespondThread; /* ͨ���߳̾�� */
	SOCKADDR_IN ListenAddr;
	int g_nSockConn = 0;//�������ӵ���Ŀ
	int nRet = 0;
	int nRcv = 0;
	SOCKET ListenSock;
	SOCKET AccepSock;

	void ShouResult();    //ˢ�����չʾ��д�����ݿ���
	void SKResuldShow();  //ˢ�����չʾ��д�����ݿ���
	BOOL StartService();
	BOOL PushToPlatfrom();  //���͵�������ƽ̨
	void WriteSqlResult();  //��ʶ����д�����ݿ�
	void ClearVaules();    //���
public:


	CStatic m_ZQ_String;
	CStatic m_RG_String;
	CString m_XSD_String;
	CString m_HMD_String;
	CEdit m_Edit_test;
	CString m_TypeReg_String;
	CListCtrl m_ListRes_String;

	void ReSize();
	POINT old;
	void Ui_Show(CString strPicture_Path, int myIDC_Picture);	
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnsendclouds();

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedBtn();
	afx_msg void OnBnClickedBtnjjdoor();
};
