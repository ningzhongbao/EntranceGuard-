#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "YCodec.h"//解析中文编码
#include <atlconv.h>
#include <iostream>
// CPersComprResult 对话框


typedef struct DatePack
{
	SOCKET *pClientSocket;
	unsigned char *recvline;
};

class CPersComprResult : public CDialogEx
{
	DECLARE_DYNAMIC(CPersComprResult)

public:
	CPersComprResult(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPersComprResult();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGPERSCOMRELT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL InitSocket();
	static DWORD WINAPI WaitProc(LPVOID lpPar);
	static DWORD WINAPI RespondProc(LPVOID lpPar);

	static DWORD WINAPI FKThreadProc(LPVOID lpPar);
	static DWORD WINAPI FZThreadProc(LPVOID lpPar);
	HANDLE m_hWaitThread; /* 等待连接线程 */
	HANDLE m_hRespondThread; /* 通信线程句柄 */
	SOCKADDR_IN ListenAddr;
	int g_nSockConn = 0;//请求连接的数目
	int nRet = 0;
	int nRcv = 0;
	SOCKET ListenSock;
	SOCKET AccepSock;

	void ShouResult();    //刷脸结果展示和写入数据库中
	void SKResuldShow();  //刷卡结果展示和写入数据库中
	BOOL StartService();
	BOOL PushToPlatfrom();  //推送到第三方平台
	void WriteSqlResult();  //把识别结果写入数据库
	void ClearVaules();    //清空
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
