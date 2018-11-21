// WintCheckVido.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "WintCheckVido.h"
#include "afxdialogex.h"
#include "../Include/netmanager.h"
#include "../Include/PlayV1.h"
#include "../Include/PlayV2.h"
#include "WintnessCheck.h"




// CWintCheckVido �Ի���
CWintCheckVido *g_cWinteCheck = NULL;
LLONG g_lRealPlayId = 0;
LONG  g_nPlayPort;   // ��Ƶ��������ͨ����
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


// CWintCheckVido ��Ϣ�������


void CALLBACK realdata_callback(long lRealHandle,
	DWORD dwDataType,
	BYTE *pBuffer,
	DWORD dwBufSize,
	LDWORD dwUser)
{
	// �˴����ǽ�����Ͷ�ݵ����ſⲥ��
	LONG* pPlayPort = (LONG*)dwUser;
	PlayMS_InputData(*pPlayPort, pBuffer, dwBufSize);
}


DWORD CWintCheckVido::PVCThread(LPVOID lpar)
{
	int   nError = 0;
	LLONG lRealPlayId = 0;
	int   nChannel = 0;
	LONG  nPlayPort;   // ��Ƶ��������ͨ����


	// ��ȡ���в���ͨ����
	PlayMS_GetFreePort(&nPlayPort);
	//����
	HWND hwnd = g_cWinteCheck->GetDlgItem(IDC_SVLC)->GetSafeHwnd();
	//HWND hwnd1 = GetDlgItem(IDC_STATIC_Play2)->GetSafeHwnd();

	// ����ʵʱ��ģʽ��������ļ�����ѡ�� STREAM_TYPE_FILE��
	BOOL bRet = PlayMS_SetStreamOpenMode(nPlayPort, STREAM_TYPE_REALTIME);

	// ����������ʼ������أ���С MIN_SOURCE_BUF_SIZE - MAX_SOURCE_BUF_SIZE��
	bRet &= PlayMS_OpenStream(nPlayPort, 1024 * 1024 * 20);
	// �ڴ��� hwnd ����������
	bRet &= PlayMS_Play(nPlayPort, hwnd);

	//// ���ý���ص�����������ص��л�ȡ֡���ݺ�֡��Ϣ
	//bRet &= PlayMS_SetVisibleDecodeCallBack(nPlayPort, (fDecodeCallBack)visible_decode_callback, NULL);

	// ָ�����Ŵ��� hwnd = NULL����ʱ����������ͨ�� Net_SetRealDataCallBack ����ʵʱ���ݻص���
	// �� PlayMS_InputData ֱ���ɲ��ſ���Ʋ���
	lRealPlayId = Net_RealPlay(m_ZPLoginID, nChannel, NULL, REALPLAY_STREAM_TYPE_REAL);
	if (0 >= lRealPlayId)
	{
		return 0;
	}

	PlayMS_RenderPrivateData(nPlayPort, TRUE, 0);

	// ����ʵʱ���ݻص�����
	Net_SetRealDataCallBack(lRealPlayId, (fRealPlayDataCallBack)realdata_callback, (DWORD)&nPlayPort);

	g_lRealPlayId = lRealPlayId;
	g_nPlayPort = nPlayPort;
	while (TRUE);
}

void CWintCheckVido::OnShutVidoStream()
{
	//TerminateThread(pPlayerThread->m_hThread, 0); //ǿ����ֹ�߳�ִ��

	if (0 < g_nPlayPort)
	{		

		// ���ý���ص�Ϊ NULL
		PlayMS_SetVisibleDecodeCallBack(g_nPlayPort, NULL, NULL);

		// ֹͣ��������
		PlayMS_Stop(g_nPlayPort);

		// �ر�����
		PlayMS_CloseStream(g_nPlayPort);

		// �ͷ�������ģʽ�µĻ�������
		//���ر������������ջ������ݣ���������֡����������
		PlayMS_ResetSourceBuffer(g_nPlayPort);

		PlayMS_RenderPrivateData(g_nPlayPort, FALSE, 0); //�رջ���������
	}

	// ֹͣʵʱԤ��
	if (0 < g_lRealPlayId)
		Net_StopRealPlay(g_lRealPlayId);

	g_lRealPlayId = 0;
	g_nPlayPort = 0;
}

void CWintCheckVido::OnStnClickedSvlc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


BOOL CWintCheckVido::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	pPlayerThread = NULL;
	pPlayerThread = AfxBeginThread((AFX_THREADPROC)PVCThread, this); //CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)PVCThread, (LPVOID)NULL, 0, 0);
	PerCardCheck();


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CWintCheckVido::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	
	CDialogEx::OnClose();
}


void CWintCheckVido::OnDestroy()
{
	CDialogEx::OnDestroy();
	
	// TODO: �ڴ˴������Ϣ����������

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
BOOL CWintCheckVido::PerCardCheck()        //��֤����
{
	// 1. �ϴ��ȶ�������
	//::MessageBox(NULL, g_strFacePath, NULL, 0);
	//::MessageBox(NULL, g_strPictureId, NULL, 0);
	if (!UpFacePicture(g_strPictureId, m_ZPLoginID, g_strFacePath))
	{
		return FALSE;
	}
	
	// 2. ������Ƶ���


	// 3. ��ȡ�ԱȽ��
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
		if (g_strPictureId == g_ReconBackId)  //id����ҷ�������70��
		{
			if (70 <= g_ReconBackScore)// 4. �ر���Ƶ��ɾ����������������ȡ���
			{				
				g_strResTip = _T("��֤����ɹ�");
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
				g_strResTip = _T("��֤����ʧ�ܣ�����һ�Ρ�");
				g_ReconBackId = _T("");
			}					
			g_cWinteCheck->SetShow(); //��ʾ���

			i++;
		}
		if (i == 3)
		{
			g_ReconPass = 0;
			DropFacePicture(g_strPictureId, m_ZPLoginID);

			Sleep(3000);
			g_cWinteCheck->OnMyCloseWind(); //3�β�����ֱ�ӹرմ���

			return -2;
		}
	}

	ReleaseMutex(hMutex2);

	return 0;
}