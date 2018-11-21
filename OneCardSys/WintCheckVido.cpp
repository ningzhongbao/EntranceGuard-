// WintCheckVido.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "WintCheckVido.h"
#include "afxdialogex.h"
#include "../Include/netmanager.h"
#include "../Include/PlayV1.h"
#include "../Include/PlayV2.h"
#include "WintnessCheck.h"




// CWintCheckVido 对话框
CWintCheckVido *g_cWinteCheck = NULL;
LLONG g_lRealPlayId = 0;
LONG  g_nPlayPort;   // 视频播放虚拟通道号
CString g_strResTip = _T("");



IMPLEMENT_DYNAMIC(CWintCheckVido, CDialogEx)

CWintCheckVido::CWintCheckVido(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIAWITCHECKVIDO, pParent)
	, m_TipString(_T(""))
	, m_ScoreString(_T(""))
	, m_FloatScore(0)
{
	g_cWinteCheck = this;
}

CWintCheckVido::~CWintCheckVido()
{
}

void CWintCheckVido::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITTIP, m_TipString);
	DDX_Text(pDX, IDC_EDIT3, m_FloatScore);
}


BEGIN_MESSAGE_MAP(CWintCheckVido, CDialogEx)
	ON_STN_CLICKED(IDC_SVLC, &CWintCheckVido::OnStnClickedSvlc)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CWintCheckVido 消息处理程序


void CALLBACK realdata_callback(long lRealHandle,
	DWORD dwDataType,
	BYTE *pBuffer,
	DWORD dwBufSize,
	LDWORD dwUser)
{
	// 此处仅是将数据投递到播放库播放
	LONG* pPlayPort = (LONG*)dwUser;
	PlayMS_InputData(*pPlayPort, pBuffer, dwBufSize);
}


DWORD CWintCheckVido::PVCThread(LPVOID lpar)
{
	int   nError = 0;
	LLONG lRealPlayId = 0;
	int   nChannel = 0;
	LONG  nPlayPort;   // 视频播放虚拟通道号


	// 获取空闲播放通道号
	PlayMS_GetFreePort(&nPlayPort);
	//播放
	HWND hwnd = g_cWinteCheck->GetDlgItem(IDC_SVLC)->GetSafeHwnd();
	//HWND hwnd1 = GetDlgItem(IDC_STATIC_Play2)->GetSafeHwnd();

	// 设置实时流模式（如果是文件可以选择 STREAM_TYPE_FILE）
	BOOL bRet = PlayMS_SetStreamOpenMode(nPlayPort, STREAM_TYPE_REALTIME);

	// 打开流，并初始化缓存池（大小 MIN_SOURCE_BUF_SIZE - MAX_SOURCE_BUF_SIZE）
	bRet &= PlayMS_OpenStream(nPlayPort, 1024 * 1024 * 20);
	// 在窗口 hwnd 播放流数据
	bRet &= PlayMS_Play(nPlayPort, hwnd);

	//// 设置解码回调函数，解码回调中获取帧内容和帧信息
	//bRet &= PlayMS_SetVisibleDecodeCallBack(nPlayPort, (fDecodeCallBack)visible_decode_callback, NULL);

	// 指定播放窗口 hwnd = NULL，此时网络流数据通过 Net_SetRealDataCallBack 设置实时数据回调后，
	// 由 PlayMS_InputData 直接由播放库控制播放
	lRealPlayId = Net_RealPlay(m_ZPLoginID, nChannel, NULL, REALPLAY_STREAM_TYPE_REAL);
	if (0 >= lRealPlayId)
	{
		return 0;
	}

	PlayMS_RenderPrivateData(nPlayPort, TRUE, 0);

	// 设置实时数据回调函数
	Net_SetRealDataCallBack(lRealPlayId, (fRealPlayDataCallBack)realdata_callback, (DWORD)&nPlayPort);

	g_lRealPlayId = lRealPlayId;
	g_nPlayPort = nPlayPort;
	while (TRUE);
}

void CWintCheckVido::OnShutVidoStream()
{
	//TerminateThread(pPlayerThread->m_hThread, 0); //强制终止线程执行

	if (0 < g_nPlayPort)
	{		

		// 设置解码回调为 NULL
		PlayMS_SetVisibleDecodeCallBack(g_nPlayPort, NULL, NULL);

		// 停止播放码流
		PlayMS_Stop(g_nPlayPort);

		// 关闭码流
		PlayMS_CloseStream(g_nPlayPort);

		// 释放流播放模式下的缓存数据
		//（关闭码流后必须清空缓存数据，否则会出现帧残留的现象）
		PlayMS_ResetSourceBuffer(g_nPlayPort);

		PlayMS_RenderPrivateData(g_nPlayPort, FALSE, 0); //关闭绘制人脸框
	}

	// 停止实时预览
	if (0 < g_lRealPlayId)
		Net_StopRealPlay(g_lRealPlayId);

	g_lRealPlayId = 0;
	g_nPlayPort = 0;
}

void CWintCheckVido::OnStnClickedSvlc()
{
	// TODO: 在此添加控件通知处理程序代码
}


BOOL CWintCheckVido::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	pPlayerThread = NULL;
	pPlayerThread = AfxBeginThread((AFX_THREADPROC)PVCThread, this); //CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PVCThread, (LPVOID)NULL, 0, 0);
	PerCardCheck();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CWintCheckVido::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	
	CDialogEx::OnClose();
}


void CWintCheckVido::OnDestroy()
{
	CDialogEx::OnDestroy();
	
	// TODO: 在此处添加消息处理程序代码

   PostMessage(WM_CLOSE,NULL,NULL);
}

void CWintCheckVido::OnMyCloseWind() {
	OnShutVidoStream();
	DropFacePicture(g_strPictureId, m_ZPLoginID);

	OnClose();
	OnDestroy();
    PostMessage(WM_CLOSE, NULL, NULL);
}

HANDLE hMutex2;
BOOL CWintCheckVido::PerCardCheck()        //人证核验
{
	// 1. 上传比对人脸库
	//::MessageBox(NULL, g_strFacePath, NULL, 0);
	//::MessageBox(NULL, g_strPictureId, NULL, 0);
	if (!UpFacePicture(g_strPictureId, m_ZPLoginID, g_strFacePath))
	{
		return FALSE;
	}
	
	// 2. 开启视频检测


	// 3. 获取对比结果
	if (WintnesCheck())
	{
		CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE(GetRresult)), (LPVOID)NULL, 0, NULL));
		hMutex2 = CreateMutex(NULL, FALSE, _T("GetResult"));
		CloseHandle(hMutex2);
	}

	return TRUE;
}

void CWintCheckVido::SetShow()
{
	m_TipString = g_strPictureId + g_strResTip;	
	m_FloatScore = g_ReconBackScore;

	UpdateData(FALSE);
}

DWORD CWintCheckVido::GetRresult()
{
	WaitForSingleObject(hMutex2, INFINITE);
	int i = 0;

	while (i < 3)
	{
		if (g_strPictureId == g_ReconBackId)  //id相等且分数大于70分
		{
			if (70 <= g_ReconBackScore)// 4. 关闭视频，删除人脸库人脸，获取结果
			{				
				g_strResTip = _T("人证核验成功");
				DropFacePicture(g_strPictureId, m_ZPLoginID);
				WintCheckStop();	
				g_ReconPass = 1;
				g_cWinteCheck->SetShow();
				Sleep(5000);
				g_cWinteCheck->OnMyCloseWind();

				return 1;
			}	
			else
			{
				g_strResTip = _T("人证核验失败，再试一次。");
				g_ReconBackId = _T("");
			}					
			g_cWinteCheck->SetShow(); //显示结果

			i++;
		}
		if (i == 3)
		{
			g_ReconPass = 0;
			DropFacePicture(g_strPictureId, m_ZPLoginID);

			Sleep(3000);
			g_cWinteCheck->OnMyCloseWind(); //3次不过，直接关闭窗口

			return -2;
		}
	}

	ReleaseMutex(hMutex2);

	return 0;
}