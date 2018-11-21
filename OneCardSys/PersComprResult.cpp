// PersComprResult.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "PersComprResult.h"
#include "afxdialogex.h"
#include <WinSock2.h>
#include <stdio.h>
#include "HttpPost.h"

#pragma comment(lib, "ws2_32.lib")
#define  port 5050

CPersComprResult *perComRes = NULL;
CString g_PicPath = _T(""); //���ݿ���Ƭ·��
CString SFHMD = _T("");     //�Ƿ������
CString g_PicResPath = _T(""); //���ص���Ƭ·��
CString g_XSD_String = _T("");  //���ƶ�
CString g_TypeReg_string = _T("");  //ʶ������
CString g_Name = _T("");   //����
CString g_FKAddr = _T("");  //�ÿ�סַ
CString g_BFZName = _T("");
CString g_BFZAddr = _T(""); //�����߼�ͥסַ
CString g_InputTime = _T("");
CString g_OutPutTime = _T(""); //�뿪ʱ��

CString g_Sex = _T("");    //�Ա�
CString g_Tel = _T("");    //�绰
CString g_LD = _T("");    //¥����
CString g_FH = _T("");    //�����
CString g_IDCardNum = _T("");  //���֤��
CString g_SBFS = _T("");
CString g_SKCardNum = _T("");//ˢ���Ŀ���

HANDLE hMutex = 0;
HANDLE hMutex1 = 0;

struct sockaddr_in g_IpSa;  //�������ŶԷ�ip��ַ


CString tmpAddr = _T("");  //��ʱסַ����
// CPersComprResult �Ի���

IMPLEMENT_DYNAMIC(CPersComprResult, CDialogEx)

CPersComprResult::CPersComprResult(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLGPERSCOMRELT, pParent)
	, m_XSD_String(_T(""))
	, m_HMD_String(_T(""))
	, m_TypeReg_String(_T(""))
{

}

CPersComprResult::~CPersComprResult()
{
	//if (NULL != perComRes)
	//{
	//	delete perComRes;
	//	perComRes = NULL;
	//}
}

void CPersComprResult::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SXJZQ, m_ZQ_String);
	DDX_Control(pDX, IDC_RegPicture, m_RG_String);
	DDX_Text(pDX, IDC_EDIT2, m_XSD_String);
	DDX_Text(pDX, IDC_EDITBT, m_HMD_String);
	DDX_Text(pDX, IDC_EDIT_Type, m_TypeReg_String);
	DDX_Control(pDX, IDC_LIST_Result, m_ListRes_String);
}


BEGIN_MESSAGE_MAP(CPersComprResult, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BtnSendClouds, &CPersComprResult::OnBnClickedBtnsendclouds)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BtnJJDoor, &CPersComprResult::OnBnClickedBtnjjdoor)
END_MESSAGE_MAP()


// CPersComprResult ��Ϣ�������

void  CPersComprResult:: ClearVaules()
{
	g_PicPath = ""; //���ݿ���Ƭ·��
	SFHMD = "";     //�Ƿ������
	g_PicResPath = ""; //���ص���Ƭ·��
	g_XSD_String = "";  //���ƶ�
	g_TypeReg_string = "";  //ʶ������
	g_Name = "";   //����
	g_FKAddr = "";  //�ÿ�סַ
	g_BFZName = "";
	g_BFZAddr = ""; //�����߼�ͥסַ
	g_InputTime = "";
	g_OutPutTime = "";//�뿪ʱ��

	g_Sex = "";    //�Ա�
	g_Tel = "";    //�绰
	g_LD = "";    //¥����
	g_FH = "";    //�����
	g_IDCardNum = "";  //���֤��
	g_SBFS = "";      //ʶ��ʽ
	g_SKCardNum = ""; //ˢ������

	CRect rect;//ɾ���������ͼƬ
	CWnd *pWnd = GetDlgItem(IDC_SXJZQ);
	Graphics graphics(pWnd->GetDC()->m_hDC);
	GetDlgItem(IDC_SXJZQ)->GetClientRect(&rect);
	Color color;
	graphics.Clear(color.LightGray);

	CRect rect1;//ɾ��ע�����ͼƬ
	CWnd *pWnd1 = GetDlgItem(IDC_RegPicture);
	Graphics graphics1(pWnd1->GetDC()->m_hDC);
	GetDlgItem(IDC_RegPicture)->GetClientRect(&rect1);
	Color color1;
	graphics1.Clear(color1.LightGray);

}

BOOL CPersComprResult::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	if (NULL == perComRes)
	{
		perComRes = new CPersComprResult;
	}

	perComRes = this;
	CRect rect1;
	GetClientRect(&rect1);     //ȡ�ͻ�����С  
	old.x = rect1.right - rect1.left;
	old.y = rect1.bottom - rect1.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);

	CRect rect;

	// ��ȡ��������б���ͼ�ؼ���λ�úʹ�С   
	m_ListRes_String.GetClientRect(&rect);
	m_ListRes_String.SetExtendedStyle(m_ListRes_String.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_ListRes_String.InsertColumn(0, _T("����"), LVCFMT_LEFT, rect.Width() / 8, 0);
	m_ListRes_String.InsertColumn(1, _T("�Ա�"), LVCFMT_LEFT, rect.Width() / 8, 1);
	m_ListRes_String.InsertColumn(2, _T("ʶ��ʽ"), LVCFMT_LEFT, rect.Width() / 7, 2);
	m_ListRes_String.InsertColumn(3, _T("���֤��"), LVCFMT_LEFT, rect.Width() / 5, 3);
	m_ListRes_String.InsertColumn(4, _T("�绰"), LVCFMT_LEFT, rect.Width() / 5, 4);
	m_ListRes_String.InsertColumn(5, _T("¥����"), LVCFMT_LEFT, rect.Width() / 10, 5);
	m_ListRes_String.InsertColumn(6, _T("�����"), LVCFMT_LEFT, rect.Width() / 10, 6);
	m_ListRes_String.InsertColumn(7, _T("��ͥסַ"), LVCFMT_LEFT, rect.Width() / 5, 7);
	m_ListRes_String.InsertColumn(8, _T("����������"), LVCFMT_LEFT, rect.Width() / 5, 8);
	m_ListRes_String.InsertColumn(9, _T("������סַ"), LVCFMT_LEFT, rect.Width() / 5, 9);
	m_ListRes_String.InsertColumn(10, _T("����ʱ��"), LVCFMT_LEFT, rect.Width() / 5, 10);
	m_ListRes_String.InsertColumn(11, _T("ǩ��ʱ��"), LVCFMT_LEFT, rect.Width() / 5, 11);
	m_ListRes_String.InsertColumn(12, _T("����"), LVCFMT_LEFT, rect.Width() / 8, 12);


	m_ListRes_String.SetBkColor((DWORD)RGB(255, 255, 255));   //ListCtrl����ɫ(��ɫ)
															  //m_ListRes_String.SetTextBkColor((DWORD)RGB(20, 50, 70));      //ÿһ�еı���ɫ(��ɫ)
	m_ListRes_String.SetTextColor((DWORD)RGB(255, 0, 130));      //ÿһ�е�������ɫ(��ɫ)


	if (InitSocket() )
	{
		StartService();
	}

	//CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HttpUpdateHeart, (LPVOID)NULL, 0, 0));   //���������� HttpHeartBeat

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


BOOL CPersComprResult::InitSocket()
{
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);

	if (WSAStartup(sockVersion, &wsaData))
	{
		AfxMessageBox(_T("δ��װ��winsock!"), MB_OK | MB_ICONSTOP);

		return FALSE;
	}

	ListenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSock == SOCKET_ERROR)
	{
		closesocket(ListenSock);
		WSACleanup();
		return FALSE;
	}
	ListenAddr = { 0 };
	ListenAddr.sin_family = AF_INET;
	//ListenAddr.sin_addr.S_un.S_addr = inet_addr("192.168.31.171");
	ListenAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	ListenAddr.sin_port = htons(port);

	/*int  flag = 1, len = sizeof(int);
	if (setsockopt(ListenSock, SOL_SOCKET, SO_REUSEADDR, (const char*)&flag, len) == -
		1)
	{
		closesocket(ListenSock);
		WSACleanup();
		return FALSE;
	}
*/
	
	if (SOCKET_ERROR == bind(ListenSock, (SOCKADDR *)&ListenAddr, sizeof(ListenAddr)))
	{
		closesocket(ListenSock);
		WSACleanup();
		return FALSE;
	}

	if (SOCKET_ERROR == listen(ListenSock, 3))
	{
		closesocket(ListenSock);
		WSACleanup();
		return FALSE;
	}

	return TRUE;
}


BOOL CPersComprResult::StartService()
{
	/* �����ȴ������߳� */
	DWORD dwThreadId = 0;

	m_hWaitThread = ::CreateThread(NULL, NULL, CPersComprResult::WaitProc, ((LPVOID)this), 0, &dwThreadId);
	CloseHandle(m_hWaitThread);

	return TRUE;
}

DWORD WINAPI CPersComprResult::WaitProc(LPVOID lpPar)
{
	sockaddr_in remoteAddr;
	CString strNotice; /* ֪ͨ��Ϣ */
	int nAddrLen = sizeof(remoteAddr);

	CPersComprResult *pThis = (CPersComprResult*)lpPar;

	while (1)
	{
		Sleep(10);
		/* ����ͨ���׽��� */

		SOCKET *pClientSocket = new SOCKET;

		*pClientSocket = ::accept(pThis->ListenSock, (SOCKADDR*)&remoteAddr, &nAddrLen);
		if (INVALID_SOCKET == *pClientSocket)
		{
			strNotice = "accept()ʧ�ܣ��ٴγ��� ...... ";
			::AfxMessageBox(strNotice);

			continue;
		}

		DWORD dwThreadId = 1;

		/* ������Ӧ�߳���ͻ���ͨ�� */
		pThis->m_hRespondThread = ::CreateThread(NULL, NULL, CPersComprResult::RespondProc, ((LPVOID)pClientSocket), 0, &dwThreadId);

		CloseHandle(pThis->m_hRespondThread);
	}

	return 0;
}

void SetPerType(int nType)
{
	switch (nType)
	{
	case 1:
		g_TypeReg_string = _T("ס����Ա");
		break;
	case 2:
		g_TypeReg_string = _T("�⻧��Ա");
		break;
	case 3:
		g_TypeReg_string = _T("������Ա");
		break;
	case 4:
		g_TypeReg_string = _T("ס������");
		break;
	case 5:
		g_TypeReg_string = _T("�ÿ���Ա");
		break;
	case 6:
		g_TypeReg_string = _T("�����Ա");
		break;
	case 7:
		g_TypeReg_string = _T("������Ա");
		break;
	case 8:
		g_TypeReg_string = _T("С��������Ա");
		break;
	case 9:
		g_TypeReg_string = _T("С����ҵ��Ա");
		break;
	case 10:
		g_TypeReg_string = _T("С��������Ա");
		break;
	case 11:
		g_TypeReg_string = _T("С��������Ա");
		break;
	case 12:
		g_TypeReg_string = _T("����������Ա");
		break;
	default:
		break;
	}	
}


void ShowSKInfo(unsigned char *recvline)
{
	char buf[100] = "";
	memset(buf, 0, 100);
	for (int i = 0; i < 9; i++)  //ҵ�����֤��
	{
		sprintf(buf, "%02d", recvline[i + 5]);
		g_IDCardNum += buf;
	}

	char buf1[10] = "";
	CString strTmp = "";
	for (size_t i = 14; i < 20; i++) //����
	{
		memset(buf1, 0, 10);
		if (recvline[i] != '\0')
		{
			sprintf(buf1, "%02x", recvline[i]);
			strTmp += buf1;
		}

	}
	YCodec yCodec;  //����������
	CString tmp;

	int strlen = strTmp.GetLength();
	char* str = new char[strlen + 1];
	memset(str, 0, strlen + 1);
	for (int i = 0; i < strlen; i++)
	{
		str[i] = strTmp.GetAt(i);
	}

	// hex string to wchar_t*
	int wchslen = 0;
	if (yCodec.HexStr2WChars(str, strlen, 4, NULL, &wchslen) != -1)
	{
		wchar_t* wchs = new wchar_t[wchslen + 1];
		memset(wchs, 0, sizeof(wchar_t)*(wchslen + 1));
		int n = yCodec.HexStr2WChars(str, strlen, 4, wchs, &wchslen);
		if (n != -1)
		{
			// wchar_t to CString
			wchar_t* pwch = wchs;
			for (int i = 0; i < wchslen; i++)
			{
				tmp.AppendChar(*pwch++);
			}
		}
		g_Name = wchs;
		if (wchs)
		{
			delete[]wchs;
		}
	}
	

	memset(buf, 0, 100);
	sprintf(buf, "%d", recvline[20]);
	g_Tel += buf;
	memset(buf, 0, 100);
	for (size_t i = 0; i < 5; i++) //�绰
	{
		sprintf(buf, "%02d", recvline[i + 21]);
		g_Tel += buf;
	}

	memset(buf, 0, 100);
	for (size_t i = 0; i < 4; i++)  //����
	{
		sprintf(buf, "%0d", recvline[i + 26]);
		g_SKCardNum += buf;
	}

	memset(buf, 0, 100);  //��Ա����					
	sprintf(buf, "%d", recvline[31]);
	int nPerType = atoi(buf);
	SetPerType(nPerType);  //�ж�ˢ����Ա������

	CString strType = "";
	memset(buf, 0, 100); //��Ա����
	CString strTZ = "";
	sprintf(buf, "%d", recvline[32]);
	strType += buf;

	perComRes->SKResuldShow();  //ˢ�����չʾ
}

void RecvPicture(SOCKET *pClientSocket, unsigned char *recvline)
{
	int remain_len = 0, receive_len = 0;                  //����ͼƬ��С
	char * FaceBuf = NULL;						 //����ͼƬ������
	int nRetPictLen;                     //ͼƬ�ķ��س���
	int nCountSleep = 0;

	remain_len = recvline[25] * 65536 + recvline[26] * 256 + recvline[27];//ͼƬ��С

	CString filePath;
	CTime tm;
	tm = CTime::GetCurrentTime();
	filePath = tm.Format("RES%y%m%d%H%M%S"); //ʱ������

	CString strJQ = _T("C:\\YTPicture");	//�������������͸��ҵ�ͼƬ�ļ���
	if (!PathIsDirectory(strJQ))
	{
		CreateDirectory(strJQ, 0);//�������򴴽�
	}
	strJQ = _T("C:\\YTPicture\\ZQResultPicture");
	if (!PathIsDirectory(strJQ))
	{
		CreateDirectory(strJQ, 0);//�������򴴽�
	}

	FaceBuf = (char*)malloc(sizeof(char)*remain_len);
	if (NULL == FaceBuf)
	{
		return;
	}

	if (remain_len > 0)  //ͼƬ���ȴ�����
	{
		while (remain_len)
		{
			nRetPictLen = recv(*pClientSocket, (char*)&FaceBuf[receive_len], remain_len, 0);
			if (nRetPictLen > 0)
			{
				receive_len += nRetPictLen;
				remain_len -= nRetPictLen;
			}
			else
			{
				if (nCountSleep > 8)
				{
					break;
				}
				nCountSleep++;
				Sleep(100);
			}

			if (remain_len == 0)  // ���������
			{
				strJQ += "\\" + filePath + ".jpg";
				FILE *pFilePath = fopen(strJQ, "ab+"); //			
				if (pFilePath != NULL)
				{
					fwrite(FaceBuf, 1, receive_len, pFilePath);
					g_PicResPath = strJQ;
					::InvalidateRect(perComRes->m_hWnd, NULL, FALSE);
					fclose(pFilePath);
				}
			}
		}
	}//���ܿ�������������ץȡ����������ͼƬ----����
}



DWORD WINAPI CPersComprResult::RespondProc(LPVOID lpPar)
{
	SOCKET *pClientSocket = (SOCKET*)lpPar;
	unsigned char recvline[200];        // �������ݻ����� 
	memset(recvline, 0, sizeof(recvline));

	int len = sizeof(g_IpSa);
	getpeername(*pClientSocket, (struct sockaddr *)&g_IpSa, &len);

	int nRecv = 0;
	char szTimeBuf[100] = "";

	while (1)
	{
		Sleep(50);

		if (_T("����") == g_QX)  //Ϊ��Уʱ
		{
			if ((nRecv = recv(*pClientSocket, (char *)szTimeBuf, 100, 0)) > 0)
			{
				CString strTime = "";
				SYSTEMTIME system_time = { 0 };
				GetLocalTime(&system_time);

				for (int i = 0; i<4; i++)  //��
				{
					strTime += szTimeBuf[i];
				}
				system_time.wYear = atoi(strTime);
				strTime = "";
				strTime.ReleaseBuffer(0);
				for (int i = 0; i<2;i++)
				{
					strTime += szTimeBuf[i+4];
				}
				system_time.wMonth = atoi(strTime);
				strTime = "";
				strTime.ReleaseBuffer(0);

				for (int i = 0; i < 2; i++)
				{
					strTime += szTimeBuf[i + 6];
				}
				system_time.wDay = atoi(strTime);
				strTime = "";
				strTime.ReleaseBuffer(0);
				
				for (int i = 0; i < 2; i++)
				{
					strTime += szTimeBuf[i + 8];
				}
				system_time.wHour = atoi(strTime);
				strTime = "";
				strTime.ReleaseBuffer(0);

				for (int i = 0; i < 2; i++)
				{
					strTime += szTimeBuf[i + 10];
				}
				system_time.wMinute = atoi(strTime);
				strTime = "";
				strTime.ReleaseBuffer(0);

				for (int i = 0; i < 2; i++)
				{
					strTime += szTimeBuf[i + 12];
				}
				system_time.wMilliseconds = atoi(strTime);
				strTime = "";
				strTime.ReleaseBuffer(0);

				int val = 0;
				val = SetLocalTime(&system_time);
			}
			Sleep(5000);
		}
		else
		{
			if ((nRecv = recv(*pClientSocket, (char *)recvline, 49, 0)) > 0)
			{
				if (nRecv < 49)
				{
					closesocket(*pClientSocket);
					break;
				}

				///////////////////�Խ��յ����ݽ��д���/////////////////////////////////////
				/************************************************************************/
				/* �������ź�ˢ������                                                    */
				/************************************************************************/
				if (recvline[0] == 0x7e && recvline[1] == 0x7e && recvline[2] == 0x7e
					&& recvline[3] == 0x8b && recvline[48] == 0x0d)
				{
					if (34 == recvline[30])
					{
						::MessageBox(NULL, _T("����ˢ��δʶ��"), _T("ˢ����ʾ"), MB_ICONERROR);
					}

					if (12 == recvline[30])
					{
						::MessageBox(NULL, _T("2����δ����"), _T("��ʾ"), MB_ICONERROR);
					}
					if (0x02 == recvline[30])  //ˢ������
					{
						g_XSD_String = "";  //���ƶ�
						g_XSD_String += recvline[28];
						g_XSD_String += recvline[29];

						DatePack *stuDatPack = new DatePack;  //Ԥ���ӿڣ����������չ
						stuDatPack->pClientSocket = pClientSocket;
						stuDatPack->recvline = new unsigned char[200];
						memcpy(stuDatPack->recvline, recvline, 200);

						if (recvline[4] == 'F' && recvline[5] == 'K') //�ÿͽ��չʾ
						{
							HANDLE a = CreateThread(NULL, 0, FKThreadProc, (LPVOID)recvline, 0, 0);
							hMutex = CreateMutex(NULL, FALSE, "screen");
							CloseHandle(a);
							CloseHandle(hMutex);
						}
						else if (recvline[4] == 'F' && recvline[5] == 'Z' || 'P' == recvline[5]) //�������չʾ
						{
							HANDLE b = CreateThread(NULL, 0, FZThreadProc, (LPVOID)recvline, 0, 0);
							hMutex1 = CreateMutex(NULL, FALSE, _T("screen1"));
							CloseHandle(b);
							CloseHandle(hMutex1);
						}

						//���ܿ�������������ץȡ����������ͼƬ----��ʼ
						RecvPicture(stuDatPack->pClientSocket, stuDatPack->recvline);
					}
					if (0x03 == recvline[30]) //ˢ������
					{
						perComRes->ClearVaules();  //�������

						ShowSKInfo(recvline);	//��ʾˢ����Ϣ			  
					}
				}

				closesocket(*pClientSocket);
				break;
			}
		}		
	}

	return 0;
}

void CPersComprResult::SKResuldShow()  //ˢ�����չʾ��д�����ݿ���
{
	InvalidateRect(NULL, FALSE);

	m_TypeReg_String = g_TypeReg_string;  //��Ա����
	g_SBFS = _T("ˢ����ʽ");
	g_XSD_String = _T("ˢ�������ƶ�");
	g_Sex = _T("ˢ�����Ա�");

	CTime tTime = CTime::GetCurrentTime();
	g_OutPutTime = tTime.Format("%Y-%m-%d %H:%M:%S");//�뿪ʱ��


	if (m_TypeReg_String == _T("ס����Ա") && !m_TypeReg_String.IsEmpty())
	{
		g_FKAddr = _T("��");  //�ÿ�סַ
		g_BFZName = _T("��");
		g_BFZAddr = _T("��"); //�����߼�ͥסַ
		g_InputTime = _T("��");
	
	}
	else
	{
		g_LD = _T("��");
		g_FH = _T("��");
	}
	
	m_ListRes_String.DeleteAllItems();
	m_ListRes_String.InsertItem(0, g_Name.GetString());
	m_ListRes_String.SetItemText(0, 1, g_Sex.GetString());
	m_ListRes_String.SetItemText(0, 2, g_SBFS.GetBuffer(0));
	m_ListRes_String.SetItemText(0, 3, g_IDCardNum.GetBuffer(0));
	m_ListRes_String.SetItemText(0, 4, g_Tel.GetBuffer(0));
	m_ListRes_String.SetItemText(0, 5,"��");
	m_ListRes_String.SetItemText(0, 6, "��");
	m_ListRes_String.SetItemText(0, 7, g_FKAddr.GetBuffer(0));
	m_ListRes_String.SetItemText(0, 8, g_BFZName);
	m_ListRes_String.SetItemText(0, 9, g_BFZAddr);
	m_ListRes_String.SetItemText(0, 10, g_InputTime);
	m_ListRes_String.SetItemText(0, 11, g_OutPutTime);
	m_ListRes_String.SetItemText(0, 12, g_SKCardNum);
	
	PushToPlatfrom();
	WriteSqlResult();
	UpdateData(FALSE);
}

DWORD CPersComprResult::FKThreadProc(LPVOID lpPar)  //�ÿͽ����߳�
{
	WaitForSingleObject(hMutex, INFINITE);
	CString strCmpTmp = "";
	unsigned char *recvline = (unsigned char*)lpPar;

	for (int i = 0; i < 15; i++)
	{
		if ('E' == recvline[18])
		{
			strCmpTmp += recvline[i + 4];
		}
		else
		{
			::MessageBox(NULL, _T("�ļ�������12λ"), _T("����"), MB_ICONERROR);
			break;
		}
	}
	//::MessageBox(NULL, strCmpTmp, NULL, 0);
	try
	{
		CString strSql;
		strSql.Format(_T("SELECT * FROM [FaceContCen].[dbo].[FK_UserTabel] WHERE IDNum = '%s'"), strCmpTmp.GetBuffer(0));

		m_pRecordSet->Open(_bstr_t(strSql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);
		_variant_t varWN;

		varWN  = m_pRecordSet->GetCollect(_variant_t(_T("Name"))); //�����ߵ�����
		if (varWN.vt != VT_NULL)
		{
			g_Name = varWN;
		}
		else
		{
			g_Name = "";
		}

		varWN = m_pRecordSet->GetCollect(_variant_t(_T("Sex"))); //�����ߵ��Ա�
		if (varWN.vt != VT_NULL)
		{
			g_Sex = varWN;
		}
		else
		{
			g_Sex = "";
		}

		varWN = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_Name"))); //�������ߵ�����
		if (varWN.vt != VT_NULL)
		{
			g_BFZName = varWN;
		}
		else
		{
			g_BFZName = "";
		}

		varWN = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_LH"))); //�������ߵ�¥����
		if (varWN.vt != VT_NULL)
		{
			g_BFZAddr = varWN;
		}
		else
		{
			g_BFZAddr = "";
		}

		varWN = m_pRecordSet->GetCollect(_variant_t(_T("FK_Addr")));  //�ÿ����֤�ϵļ�ͥסַ
		if (varWN.vt != VT_NULL)
		{
			g_FKAddr = varWN;
		}
		else
		{
			g_FKAddr = "";
		}
	
		varWN = m_pRecordSet->GetCollect(_variant_t(_T("PicturePath")));  //�ÿ���Ƭ·��
		if (varWN.vt != VT_NULL)
		{
			g_PicPath = varWN;
		}
		else
		{
			g_PicPath = "";
		}
	
		varWN = m_pRecordSet->GetCollect(_variant_t(_T("HMD")));  //�Ƿ������
		if (varWN.vt != VT_NULL)//�����Ϊ��
		{
			SFHMD = varWN;
		}
		else
		{
			SFHMD = "";
		}
		
		varWN = m_pRecordSet->GetCollect(_variant_t(_T("BeginTime")));  //����ʱ��
		if (varWN.vt != VT_NULL)//�����Ϊ��
		{
			g_InputTime = varWN;
		}
		else
		{
			g_InputTime = "";
		}	
		
		varWN = m_pRecordSet->GetCollect(_variant_t(_T("QL_Time")));//ǩ��ʱ��
		if (varWN.vt != VT_NULL)//�����Ϊ��
		{
			g_OutPutTime = varWN;
		}
		else
		{
			g_OutPutTime = "";
		}

		varWN = m_pRecordSet->GetCollect(_variant_t(_T("IDCardNum"))); //���֤����
		if (varWN.vt != VT_NULL)//�����Ϊ��
		{
			g_IDCardNum = varWN;
		}
		else
		{
			g_IDCardNum = "";
		}
		int m_Len;
		_variant_t varTmp;
		char *pBuf = NULL;
		char *m_pBMPBuffer1 = NULL;

		m_Len = m_pRecordSet->GetCollect(_variant_t("PictureLength"));
		varTmp = m_pRecordSet->GetFields()->GetItem("PictureDate")->GetChunk(m_Len);//��ȡ�ֶ�
		if (varTmp.vt == (VT_ARRAY | VT_UI1))
		{
			pBuf = new char[m_Len];
			if (pBuf)
			{
				char *buff = NULL;
				SafeArrayAccessData(varTmp.parray, (void**)&buff);//��λͼ���ݷŵ�buff��ȥ
				memcpy(pBuf, buff, m_Len);//��λͼ���ݷŵ�pBuff��

				SafeArrayUnaccessData(varTmp.parray);//�ͷ�

				m_pBMPBuffer1 = new char[m_Len];//���ٷ�����
				memcpy(m_pBMPBuffer1, pBuf, m_Len);

				CString strJQ = _T("C:\\YTPicture");	//�������ݿ�ͼƬ���ļ���
				if (!PathIsDirectory(strJQ))
				{
					CreateDirectory(strJQ, 0);//�������򴴽� ,һ��Ŀ¼
				}
				strJQ = _T("C:\\YTPicture\\FKPicture");
				if (!PathIsDirectory(strJQ))
				{
					CreateDirectory(strJQ, 0);//�������򴴽�������Ŀ¼
				}

				strJQ += _T("\\") + g_IDCardNum + _T(".jpg");  //���ļ�
				FILE *pFilePath = fopen(strJQ, "w+b"); //Ч�ʵ�
				if (NULL != pFilePath)
				{
					fwrite(m_pBMPBuffer1, 1, m_Len, pFilePath);	//д���ļ�		
					g_PicPath = strJQ;

					fclose(pFilePath);
				}

				delete m_pBMPBuffer1;
				m_pBMPBuffer1 = NULL;
				delete pBuf;
				pBuf = NULL;
			}
		}


		g_TypeReg_string = "�ÿ�";


		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //�رռ�¼�� 
		}
		strSql.ReleaseBuffer(0);
		perComRes->ShouResult();//��ѯ��������ʾ������
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //�رռ�¼�� 
		}
		CATCH_ERROR;		
	}	

	ReleaseMutex(hMutex);
	strCmpTmp.ReleaseBuffer(0);

	return 0;
}

DWORD CPersComprResult::FZThreadProc(LPVOID lpPar)
{
	WaitForSingleObject(hMutex1, INFINITE);
	CString strCmpTmp = _T("");
	unsigned char *recvline = (unsigned char*)lpPar;

	for (int i = 0; i < 15; i++)
	{
		if ('E' == recvline[18])
		{
			strCmpTmp += recvline[i + 4];
		}
		else
		{
			::MessageBox(NULL, _T("�ļ�������15λ"), _T("����"), MB_ICONERROR);
			break;
		}
	}
	try
	{
		CString strSql;
		strSql.Format("SELECT * FROM [FaceContCen].[dbo].[PersonInfo] WHERE ID = '%s'", strCmpTmp.GetBuffer(0));

		m_pRecordSet->Open(_bstr_t(strSql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		g_TypeReg_string = "����";
		_variant_t FP;

		FP = m_pRecordSet->GetCollect(_variant_t(_T("Name")));
		if (FP.vt != VT_NULL)//�����Ϊ��
		{
			g_Name = FP;
		}
		else
		{
			g_Name = "";
		}

		FP = m_pRecordSet->GetCollect(_variant_t(_T("Sex")));
		if (FP.vt != VT_NULL)//�����Ϊ��
		{
			g_Sex = FP;
		}
		else
		{
			g_Sex = "";
		}
		FP = m_pRecordSet->GetCollect(_variant_t(_T("Tel")));
		if (FP.vt != VT_NULL)//�����Ϊ��
		{
			g_Tel = FP;
		}
		else
		{
			g_Tel = "";
		}
		FP = m_pRecordSet->GetCollect(_variant_t(_T("LD")));
		if (FP.vt != VT_NULL)//�����Ϊ��
		{
			g_LD = FP;
		}
		else
		{
			g_LD = "";
		}
		FP = m_pRecordSet->GetCollect(_variant_t(_T("FH")));
		if (FP.vt != VT_NULL)//�����Ϊ��
		{
			g_FH = FP;
		}
		else
		{
			g_FH = "";
		}

		FP = m_pRecordSet->GetCollect(_variant_t(_T("RegType")));
		if (FP.vt != VT_NULL)//�����Ϊ��
		{
			g_IDCardNum = FP;
		}
		else
		{
			g_IDCardNum = "";
		}
		SFHMD = "��";

		CString IDNum;//��Ƭ���
		FP = m_pRecordSet->GetCollect(_variant_t(_T("ID")));
		if (FP.vt != VT_NULL)//�����Ϊ��
		{
			IDNum = FP;
		}
		else
		{
			IDNum = "";
		}

		int m_Len;
		_variant_t varTmp;
		char *pBuf = NULL;
		char *m_pBMPBuffer1 = NULL;

		m_Len = m_pRecordSet->GetCollect(_variant_t("PictureLength"));
		varTmp = m_pRecordSet->GetFields()->GetItem("PictureDate")->GetChunk(m_Len);//��ȡ�ֶ�
		if (varTmp.vt == (VT_ARRAY | VT_UI1))
		{
			pBuf = new char[m_Len];
			if (pBuf)
			{
				char *buff = NULL;
				SafeArrayAccessData(varTmp.parray, (void**)&buff);//��λͼ���ݷŵ�buff��ȥ
				memcpy(pBuf, buff, m_Len);//��λͼ���ݷŵ�pBuff��

				SafeArrayUnaccessData(varTmp.parray);//�ͷ�

				m_pBMPBuffer1 = new char[m_Len];//���ٷ�����
				memcpy(m_pBMPBuffer1, pBuf, m_Len);
			
				CString strJQ = _T("C:\\YTPicture");	//�������ݿ�ͼƬ���ļ���
				if (!PathIsDirectory(strJQ))
				{
					CreateDirectory(strJQ, 0);//�������򴴽� ,һ��Ŀ¼
				}
				strJQ = _T("C:\\YTPicture\\ZHPictureReg");
				if (!PathIsDirectory(strJQ))
				{
					CreateDirectory(strJQ, 0);//�������򴴽�������Ŀ¼
				}

				strJQ += _T("\\") + g_IDCardNum;  //���ļ�
				FILE *pFilePath = fopen(strJQ, "w+b"); //Ч�ʵ�
				if (NULL != pFilePath)
				{
					fwrite(m_pBMPBuffer1, 1, m_Len, pFilePath);	//д���ļ�		
					g_PicPath = strJQ;

					fclose(pFilePath);
				}
	
				delete m_pBMPBuffer1;
				m_pBMPBuffer1 = NULL;
				delete pBuf;
				pBuf = NULL;
			}			
		}
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //�رռ�¼�� 
		}

		strSql.ReleaseBuffer(0);
		perComRes->ShouResult(); //��ѯ��������ʾ������
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //�رռ�¼�� 
		}
		CATCH_ERROR;
	}
	
	ReleaseMutex(hMutex1);

	return 0;
}


void CPersComprResult::ShouResult()
{
	InvalidateRect(NULL, FALSE);
	g_SBFS = _T("����ʶ��");
	if (!g_XSD_String.IsEmpty())
	{
		m_XSD_String = g_XSD_String;
	}

	m_HMD_String = SFHMD;  //�Ƿ�Ϊ������
	m_TypeReg_String = g_TypeReg_string;  //��Ա����

	
	if (m_TypeReg_String == _T("����") && !m_TypeReg_String.IsEmpty())
	{
		g_FKAddr = _T("��");  //�ÿ�סַ
		g_BFZName = _T("��");
		g_BFZAddr = _T("��"); //�����߼�ͥסַ
		g_InputTime = _T("��");
		g_OutPutTime = _T("��");//�뿪ʱ��
		tmpAddr = _T("¥��: ") + g_LD + _T(" ;����: ") + g_FH;
	}
	else
	{
		g_LD = _T("��");
		g_FH = _T("��");
		tmpAddr = g_FKAddr;
	}
	if (g_OutPutTime == _T("") || g_OutPutTime.IsEmpty())
	{
		g_OutPutTime = _T("δǩ��");
	}

	m_ListRes_String.DeleteAllItems();
	m_ListRes_String.InsertItem(0, g_Name.GetString());
	m_ListRes_String.SetItemText(0, 1, g_Sex.GetBuffer(0));
	m_ListRes_String.SetItemText(0, 2, g_SBFS.GetBuffer(0));
	m_ListRes_String.SetItemText(0, 3, g_IDCardNum.GetBuffer(0));
	m_ListRes_String.SetItemText(0, 4, g_Tel.GetBuffer(0));
	m_ListRes_String.SetItemText(0, 5, g_LD.GetBuffer(0));
	m_ListRes_String.SetItemText(0, 6, g_FH.GetBuffer(0));
	m_ListRes_String.SetItemText(0, 7, g_FKAddr.GetBuffer(0));
	m_ListRes_String.SetItemText(0, 8, g_BFZName.GetBuffer(0));
	m_ListRes_String.SetItemText(0, 9, g_BFZAddr.GetBuffer(0));
	m_ListRes_String.SetItemText(0, 10, g_InputTime.GetBuffer(0));
	m_ListRes_String.SetItemText(0, 11, g_OutPutTime.GetBuffer(0));

	InvalidateRect(NULL, FALSE);
	WriteSqlResult(); //��ʶ����д�����ݿ�


	Ui_Show(g_PicResPath, IDC_SXJZQ);
	Ui_Show(g_PicPath, IDC_RegPicture);
	UpdateData(FALSE);
	
	//��һ�ַ�ʽ���Զ�����
	PushToPlatfrom();   //���͵�������ƽ̨
}

void CPersComprResult::WriteSqlResult()  //��ʶ����д�����ݿ�
{
	try
	{
		CTime tmOut = CTime::GetCurrentTime();
		CString strTimeEnd = tmOut.Format("%Y-%m-%d %H:%M:%S");

		CString Sql;
		Sql.Format("Insert into [FaceContCen].[dbo].[ReconResult_T](Name,Sex,ReconMothed,IDNum,Tel,Addr,PerType,Similarity,OutTime)\
		                    values('%s','%s','%s','%s','%s','%s','%s','%s','%s')", g_Name.GetBuffer(0), g_Sex.GetBuffer(0), g_SBFS.GetBuffer(0), g_IDCardNum.GetBuffer(0), g_Tel.GetBuffer(0), tmpAddr.GetBuffer(0), m_TypeReg_String.GetBuffer(0), m_XSD_String.GetBuffer(0), strTimeEnd);
		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();     //�رռ�¼��
		}
		Sql.ReleaseBuffer(0);
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();     //�رռ�¼��
		}
		CATCH_ERROR;
	}
}

BOOL CPersComprResult::PushToPlatfrom()   //���͵�������ƽ̨
{
	//SFHMD = _T("");     //�Ƿ������
	//g_PicResPath = _T(""); //���ص���Ƭ·�� �������·������ͼƬ
	//g_XSD_String = _T("");  //���ƶ�
	//g_TypeReg_string = _T("");  //ʶ������
	//g_Name = _T("");   //����
	//g_FKAddr = _T("");  //�ÿ�סַ
	//g_BFZName = _T("");
	//g_BFZAddr = _T(""); //�����߼�ͥסַ
	//g_InputTime = _T("");
	//g_OutPutTime = _T(""); //�뿪ʱ��

	//g_Sex = _T("");    //�Ա�
	//g_Tel = _T("");    //�绰
	//g_LD = _T("");    //¥����
	//g_FH = _T("");    //�����
	//g_IDCardNum = _T("");  //���֤��
	//g_SBFS = _T("");         //����ʶ�� ˢ����ʽ

	int nSimlary = atoi(g_XSD_String);


	if (0 == strcmp(g_SBFS, "ˢ����ʽ"))
	{
		//CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Post_Dev_Entrance_addEventICCard(DEVICEID, 1, 111, g_IDCardNum, "liming", g_Tel, 1, "182A1FF4", "lisi", "1a896cd5-51c2-47e8-a93f-7ecf834ad900", "beizhu"), (LPVOID)NULL, 0, 0));
		//TODO:
		Post_Dev_Entrance_addEventICCard(DEVICEID, 1, 111, g_IDCardNum, g_Name, g_Tel, 1, "182A1FF4", g_BFZName, "1a896cd5-51c2-47e8-a93f-7ecf834ad900", "��ע");
	
	
	}
	else if (0 == strcmp(g_SBFS, "����ʶ��"))
	{
		//TODO:
		Post_Dev_Entrance_AddEventPic(DEVICEID, 0, 111, g_IDCardNum, g_Name, g_Tel, 1, "", g_BFZName, "1a896cd5-51c2-47e8-a93f-7ecf834ad900", nSimlary, "��ע", "pic", g_PicResPath);
	}

	return TRUE;
}

void CPersComprResult::Ui_Show(CString strPicture_Path, int myIDC_Picture)
{  
	WCHAR buf[1024];
	CRect rect;
	USES_CONVERSION;
	wcscpy(buf, A2W((LPCSTR)strPicture_Path));  //CString -> wchar_t

	Image image(buf, TRUE);
	CWnd *pWnd = GetDlgItem(myIDC_Picture);
	Graphics graphics(pWnd->GetDC()->m_hDC);
	GetDlgItem(myIDC_Picture)->GetClientRect(&rect);
	graphics.DrawImage(&image, 0, 0, rect.Width(), rect.Height());
}



void CPersComprResult::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	Ui_Show(g_PicResPath, IDC_SXJZQ);
	Ui_Show(g_PicPath, IDC_RegPicture);
}


void CPersComprResult::OnBnClickedBtnsendclouds()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//�ڶ��ַ�ʽ���ֶ�����
	//PushToPlatfrom();   //���͵�������ƽ̨


	MessageBox(_T("Test"), _T("��ʾ"), 0);
}



void CPersComprResult::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}

void CPersComprResult::ReSize()
{
	float fsp[2];
	POINT Newp; //��ȡ���ڶԻ���Ĵ�С
	CRect recta;
	GetClientRect(&recta);     //ȡ�ͻ�����С  
	Newp.x = recta.right - recta.left;
	Newp.y = recta.bottom - recta.top;
	fsp[0] = (float)Newp.x / old.x;
	fsp[1] = (float)Newp.y / old.y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint, TLPoint; //���Ͻ�
	CPoint OldBRPoint, BRPoint; //���½�
	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //�г����пؼ�  
	while (hwndChild)
	{
		woc = ::GetDlgCtrlID(hwndChild);//ȡ��ID
		GetDlgItem(woc)->GetWindowRect(Rect);
		ScreenToClient(Rect);
		OldTLPoint = Rect.TopLeft();
		TLPoint.x = long(OldTLPoint.x*fsp[0]);
		TLPoint.y = long(OldTLPoint.y*fsp[1]);
		OldBRPoint = Rect.BottomRight();
		BRPoint.x = long(OldBRPoint.x *fsp[0]);
		BRPoint.y = long(OldBRPoint.y *fsp[1]);
		Rect.SetRect(TLPoint, BRPoint);
		GetDlgItem(woc)->MoveWindow(Rect, TRUE);
		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}
	old = Newp;
}

void CPersComprResult::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	
	CDialogEx::OnClose();
}


void CPersComprResult::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	
}


void CPersComprResult::OnBnClickedBtn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CPersComprResult::OnBnClickedBtnjjdoor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	WSADATA wd;
	int err;
	int iResult;//�󶨽��
	
	err = WSAStartup(MAKEWORD(2, 2), &wd);
	if (0 != err)
	{
		WSACleanup();
		return;
	}

	SOCKET sockClient = NULL;
	sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (SOCKET_ERROR == sockClient)
	{
		closesocket(sockClient);
		return;
	}

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = g_IpSa.sin_addr.S_un.S_addr;
	addrSrv.sin_family = g_IpSa.sin_family;
	addrSrv.sin_port = htons(26711);

	iResult = connect(sockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	if (iResult == SOCKET_ERROR)
	{
		::MessageBox(NULL, "SOCKET ������������ʧ��", NULL, 0);
		closesocket(sockClient);
		WSACleanup();
		return;
	}
	//CString strPoto = "method" = "pc_open_door", "data" = "";

	char szBuf[100] = { "method = pc_open_door, data = " };
	int res = ::send(sockClient, (char *)szBuf, sizeof(szBuf), 0);
}

