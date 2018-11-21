// PersComprResult.cpp : 实现文件
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
CString g_PicPath = _T(""); //数据库照片路径
CString SFHMD = _T("");     //是否黑名单
CString g_PicResPath = _T(""); //传回的照片路径
CString g_XSD_String = _T("");  //相似度
CString g_TypeReg_string = _T("");  //识别类型
CString g_Name = _T("");   //姓名
CString g_FKAddr = _T("");  //访客住址
CString g_BFZName = _T("");
CString g_BFZAddr = _T(""); //被访者家庭住址
CString g_InputTime = _T("");
CString g_OutPutTime = _T(""); //离开时间

CString g_Sex = _T("");    //性别
CString g_Tel = _T("");    //电话
CString g_LD = _T("");    //楼栋号
CString g_FH = _T("");    //房间号
CString g_IDCardNum = _T("");  //身份证号
CString g_SBFS = _T("");
CString g_SKCardNum = _T("");//刷卡的卡号

HANDLE hMutex = 0;
HANDLE hMutex1 = 0;

struct sockaddr_in g_IpSa;  //紧急开门对方ip地址


CString tmpAddr = _T("");  //临时住址变量
// CPersComprResult 对话框

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


// CPersComprResult 消息处理程序

void  CPersComprResult:: ClearVaules()
{
	g_PicPath = ""; //数据库照片路径
	SFHMD = "";     //是否黑名单
	g_PicResPath = ""; //传回的照片路径
	g_XSD_String = "";  //相似度
	g_TypeReg_string = "";  //识别类型
	g_Name = "";   //姓名
	g_FKAddr = "";  //访客住址
	g_BFZName = "";
	g_BFZAddr = ""; //被访者家庭住址
	g_InputTime = "";
	g_OutPutTime = "";//离开时间

	g_Sex = "";    //性别
	g_Tel = "";    //电话
	g_LD = "";    //楼栋号
	g_FH = "";    //房间号
	g_IDCardNum = "";  //身份证号
	g_SBFS = "";      //识别方式
	g_SKCardNum = ""; //刷卡卡号

	CRect rect;//删除结果界面图片
	CWnd *pWnd = GetDlgItem(IDC_SXJZQ);
	Graphics graphics(pWnd->GetDC()->m_hDC);
	GetDlgItem(IDC_SXJZQ)->GetClientRect(&rect);
	Color color;
	graphics.Clear(color.LightGray);

	CRect rect1;//删除注册界面图片
	CWnd *pWnd1 = GetDlgItem(IDC_RegPicture);
	Graphics graphics1(pWnd1->GetDC()->m_hDC);
	GetDlgItem(IDC_RegPicture)->GetClientRect(&rect1);
	Color color1;
	graphics1.Clear(color1.LightGray);

}

BOOL CPersComprResult::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	if (NULL == perComRes)
	{
		perComRes = new CPersComprResult;
	}

	perComRes = this;
	CRect rect1;
	GetClientRect(&rect1);     //取客户区大小  
	old.x = rect1.right - rect1.left;
	old.y = rect1.bottom - rect1.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);

	CRect rect;

	// 获取编程语言列表视图控件的位置和大小   
	m_ListRes_String.GetClientRect(&rect);
	m_ListRes_String.SetExtendedStyle(m_ListRes_String.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_ListRes_String.InsertColumn(0, _T("姓名"), LVCFMT_LEFT, rect.Width() / 8, 0);
	m_ListRes_String.InsertColumn(1, _T("性别"), LVCFMT_LEFT, rect.Width() / 8, 1);
	m_ListRes_String.InsertColumn(2, _T("识别方式"), LVCFMT_LEFT, rect.Width() / 7, 2);
	m_ListRes_String.InsertColumn(3, _T("身份证号"), LVCFMT_LEFT, rect.Width() / 5, 3);
	m_ListRes_String.InsertColumn(4, _T("电话"), LVCFMT_LEFT, rect.Width() / 5, 4);
	m_ListRes_String.InsertColumn(5, _T("楼栋号"), LVCFMT_LEFT, rect.Width() / 10, 5);
	m_ListRes_String.InsertColumn(6, _T("房间号"), LVCFMT_LEFT, rect.Width() / 10, 6);
	m_ListRes_String.InsertColumn(7, _T("家庭住址"), LVCFMT_LEFT, rect.Width() / 5, 7);
	m_ListRes_String.InsertColumn(8, _T("被访者姓名"), LVCFMT_LEFT, rect.Width() / 5, 8);
	m_ListRes_String.InsertColumn(9, _T("被访者住址"), LVCFMT_LEFT, rect.Width() / 5, 9);
	m_ListRes_String.InsertColumn(10, _T("进入时间"), LVCFMT_LEFT, rect.Width() / 5, 10);
	m_ListRes_String.InsertColumn(11, _T("签离时间"), LVCFMT_LEFT, rect.Width() / 5, 11);
	m_ListRes_String.InsertColumn(12, _T("卡号"), LVCFMT_LEFT, rect.Width() / 8, 12);


	m_ListRes_String.SetBkColor((DWORD)RGB(255, 255, 255));   //ListCtrl背景色(白色)
															  //m_ListRes_String.SetTextBkColor((DWORD)RGB(20, 50, 70));      //每一行的背景色(黑色)
	m_ListRes_String.SetTextColor((DWORD)RGB(255, 0, 130));      //每一行的文字颜色(红色)


	if (InitSocket() )
	{
		StartService();
	}

	//CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HttpUpdateHeart, (LPVOID)NULL, 0, 0));   //发送心跳包 HttpHeartBeat

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


BOOL CPersComprResult::InitSocket()
{
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(2, 2);

	if (WSAStartup(sockVersion, &wsaData))
	{
		AfxMessageBox(_T("未能装入winsock!"), MB_OK | MB_ICONSTOP);

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
	/* 启动等待连接线程 */
	DWORD dwThreadId = 0;

	m_hWaitThread = ::CreateThread(NULL, NULL, CPersComprResult::WaitProc, ((LPVOID)this), 0, &dwThreadId);
	CloseHandle(m_hWaitThread);

	return TRUE;
}

DWORD WINAPI CPersComprResult::WaitProc(LPVOID lpPar)
{
	sockaddr_in remoteAddr;
	CString strNotice; /* 通知消息 */
	int nAddrLen = sizeof(remoteAddr);

	CPersComprResult *pThis = (CPersComprResult*)lpPar;

	while (1)
	{
		Sleep(10);
		/* 创建通信套接字 */

		SOCKET *pClientSocket = new SOCKET;

		*pClientSocket = ::accept(pThis->ListenSock, (SOCKADDR*)&remoteAddr, &nAddrLen);
		if (INVALID_SOCKET == *pClientSocket)
		{
			strNotice = "accept()失败，再次尝试 ...... ";
			::AfxMessageBox(strNotice);

			continue;
		}

		DWORD dwThreadId = 1;

		/* 启动相应线程与客户端通信 */
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
		g_TypeReg_string = _T("住户人员");
		break;
	case 2:
		g_TypeReg_string = _T("租户人员");
		break;
	case 3:
		g_TypeReg_string = _T("亲情人员");
		break;
	case 4:
		g_TypeReg_string = _T("住户服务");
		break;
	case 5:
		g_TypeReg_string = _T("访客人员");
		break;
	case 6:
		g_TypeReg_string = _T("快递人员");
		break;
	case 7:
		g_TypeReg_string = _T("外卖人员");
		break;
	case 8:
		g_TypeReg_string = _T("小区保安人员");
		break;
	case 9:
		g_TypeReg_string = _T("小区物业人员");
		break;
	case 10:
		g_TypeReg_string = _T("小区工作人员");
		break;
	case 11:
		g_TypeReg_string = _T("小区服务人员");
		break;
	case 12:
		g_TypeReg_string = _T("其他类型人员");
		break;
	default:
		break;
	}	
}


void ShowSKInfo(unsigned char *recvline)
{
	char buf[100] = "";
	memset(buf, 0, 100);
	for (int i = 0; i < 9; i++)  //业主身份证号
	{
		sprintf(buf, "%02d", recvline[i + 5]);
		g_IDCardNum += buf;
	}

	char buf1[10] = "";
	CString strTmp = "";
	for (size_t i = 14; i < 20; i++) //姓名
	{
		memset(buf1, 0, 10);
		if (recvline[i] != '\0')
		{
			sprintf(buf1, "%02x", recvline[i]);
			strTmp += buf1;
		}

	}
	YCodec yCodec;  //解码中文类
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
	for (size_t i = 0; i < 5; i++) //电话
	{
		sprintf(buf, "%02d", recvline[i + 21]);
		g_Tel += buf;
	}

	memset(buf, 0, 100);
	for (size_t i = 0; i < 4; i++)  //卡号
	{
		sprintf(buf, "%0d", recvline[i + 26]);
		g_SKCardNum += buf;
	}

	memset(buf, 0, 100);  //人员类型					
	sprintf(buf, "%d", recvline[31]);
	int nPerType = atoi(buf);
	SetPerType(nPerType);  //判断刷卡人员的类型

	CString strType = "";
	memset(buf, 0, 100); //人员特征
	CString strTZ = "";
	sprintf(buf, "%d", recvline[32]);
	strType += buf;

	perComRes->SKResuldShow();  //刷卡结果展示
}

void RecvPicture(SOCKET *pClientSocket, unsigned char *recvline)
{
	int remain_len = 0, receive_len = 0;                  //接受图片大小
	char * FaceBuf = NULL;						 //接收图片缓冲区
	int nRetPictLen;                     //图片的返回长度
	int nCountSleep = 0;

	remain_len = recvline[25] * 65536 + recvline[26] * 256 + recvline[27];//图片大小

	CString filePath;
	CTime tm;
	tm = CTime::GetCurrentTime();
	filePath = tm.Format("RES%y%m%d%H%M%S"); //时间命名

	CString strJQ = _T("C:\\YTPicture");	//创建控制器发送给我的图片文件夹
	if (!PathIsDirectory(strJQ))
	{
		CreateDirectory(strJQ, 0);//不存在则创建
	}
	strJQ = _T("C:\\YTPicture\\ZQResultPicture");
	if (!PathIsDirectory(strJQ))
	{
		CreateDirectory(strJQ, 0);//不存在则创建
	}

	FaceBuf = (char*)malloc(sizeof(char)*remain_len);
	if (NULL == FaceBuf)
	{
		return;
	}

	if (remain_len > 0)  //图片长度大于零
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

			if (remain_len == 0)  // 接收完成了
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
	}//接受控制器传过来的抓取人脸进出入图片----结束
}



DWORD WINAPI CPersComprResult::RespondProc(LPVOID lpPar)
{
	SOCKET *pClientSocket = (SOCKET*)lpPar;
	unsigned char recvline[200];        // 接收数据缓冲区 
	memset(recvline, 0, sizeof(recvline));

	int len = sizeof(g_IpSa);
	getpeername(*pClientSocket, (struct sockaddr *)&g_IpSa, &len);

	int nRecv = 0;
	char szTimeBuf[100] = "";

	while (1)
	{
		Sleep(50);

		if (_T("保安") == g_QX)  //为了校时
		{
			if ((nRecv = recv(*pClientSocket, (char *)szTimeBuf, 100, 0)) > 0)
			{
				CString strTime = "";
				SYSTEMTIME system_time = { 0 };
				GetLocalTime(&system_time);

				for (int i = 0; i<4; i++)  //年
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

				///////////////////对接收的数据进行处理/////////////////////////////////////
				/************************************************************************/
				/* 人脸开门和刷卡开门                                                    */
				/************************************************************************/
				if (recvline[0] == 0x7e && recvline[1] == 0x7e && recvline[2] == 0x7e
					&& recvline[3] == 0x8b && recvline[48] == 0x0d)
				{
					if (34 == recvline[30])
					{
						::MessageBox(NULL, _T("三次刷卡未识别"), _T("刷卡提示"), MB_ICONERROR);
					}

					if (12 == recvline[30])
					{
						::MessageBox(NULL, _T("2分钟未关门"), _T("提示"), MB_ICONERROR);
					}
					if (0x02 == recvline[30])  //刷脸进入
					{
						g_XSD_String = "";  //相似度
						g_XSD_String += recvline[28];
						g_XSD_String += recvline[29];

						DatePack *stuDatPack = new DatePack;  //预留接口，方便后面扩展
						stuDatPack->pClientSocket = pClientSocket;
						stuDatPack->recvline = new unsigned char[200];
						memcpy(stuDatPack->recvline, recvline, 200);

						if (recvline[4] == 'F' && recvline[5] == 'K') //访客结果展示
						{
							HANDLE a = CreateThread(NULL, 0, FKThreadProc, (LPVOID)recvline, 0, 0);
							hMutex = CreateMutex(NULL, FALSE, "screen");
							CloseHandle(a);
							CloseHandle(hMutex);
						}
						else if (recvline[4] == 'F' && recvline[5] == 'Z' || 'P' == recvline[5]) //户主结果展示
						{
							HANDLE b = CreateThread(NULL, 0, FZThreadProc, (LPVOID)recvline, 0, 0);
							hMutex1 = CreateMutex(NULL, FALSE, _T("screen1"));
							CloseHandle(b);
							CloseHandle(hMutex1);
						}

						//接受控制器传过来的抓取人脸进出入图片----开始
						RecvPicture(stuDatPack->pClientSocket, stuDatPack->recvline);
					}
					if (0x03 == recvline[30]) //刷卡进入
					{
						perComRes->ClearVaules();  //清空数据

						ShowSKInfo(recvline);	//显示刷卡信息			  
					}
				}

				closesocket(*pClientSocket);
				break;
			}
		}		
	}

	return 0;
}

void CPersComprResult::SKResuldShow()  //刷卡结果展示和写入数据库中
{
	InvalidateRect(NULL, FALSE);

	m_TypeReg_String = g_TypeReg_string;  //人员类型
	g_SBFS = _T("刷卡方式");
	g_XSD_String = _T("刷卡无相似度");
	g_Sex = _T("刷卡无性别");

	CTime tTime = CTime::GetCurrentTime();
	g_OutPutTime = tTime.Format("%Y-%m-%d %H:%M:%S");//离开时间


	if (m_TypeReg_String == _T("住户人员") && !m_TypeReg_String.IsEmpty())
	{
		g_FKAddr = _T("无");  //访客住址
		g_BFZName = _T("无");
		g_BFZAddr = _T("无"); //被访者家庭住址
		g_InputTime = _T("无");
	
	}
	else
	{
		g_LD = _T("无");
		g_FH = _T("无");
	}
	
	m_ListRes_String.DeleteAllItems();
	m_ListRes_String.InsertItem(0, g_Name.GetString());
	m_ListRes_String.SetItemText(0, 1, g_Sex.GetString());
	m_ListRes_String.SetItemText(0, 2, g_SBFS.GetBuffer(0));
	m_ListRes_String.SetItemText(0, 3, g_IDCardNum.GetBuffer(0));
	m_ListRes_String.SetItemText(0, 4, g_Tel.GetBuffer(0));
	m_ListRes_String.SetItemText(0, 5,"无");
	m_ListRes_String.SetItemText(0, 6, "无");
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

DWORD CPersComprResult::FKThreadProc(LPVOID lpPar)  //访客接收线程
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
			::MessageBox(NULL, _T("文件名不足12位"), _T("错误"), MB_ICONERROR);
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

		varWN  = m_pRecordSet->GetCollect(_variant_t(_T("Name"))); //访问者的名字
		if (varWN.vt != VT_NULL)
		{
			g_Name = varWN;
		}
		else
		{
			g_Name = "";
		}

		varWN = m_pRecordSet->GetCollect(_variant_t(_T("Sex"))); //访问者的性别
		if (varWN.vt != VT_NULL)
		{
			g_Sex = varWN;
		}
		else
		{
			g_Sex = "";
		}

		varWN = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_Name"))); //被访问者的名字
		if (varWN.vt != VT_NULL)
		{
			g_BFZName = varWN;
		}
		else
		{
			g_BFZName = "";
		}

		varWN = m_pRecordSet->GetCollect(_variant_t(_T("BFZ_LH"))); //被访问者的楼栋号
		if (varWN.vt != VT_NULL)
		{
			g_BFZAddr = varWN;
		}
		else
		{
			g_BFZAddr = "";
		}

		varWN = m_pRecordSet->GetCollect(_variant_t(_T("FK_Addr")));  //访客身份证上的家庭住址
		if (varWN.vt != VT_NULL)
		{
			g_FKAddr = varWN;
		}
		else
		{
			g_FKAddr = "";
		}
	
		varWN = m_pRecordSet->GetCollect(_variant_t(_T("PicturePath")));  //访客照片路径
		if (varWN.vt != VT_NULL)
		{
			g_PicPath = varWN;
		}
		else
		{
			g_PicPath = "";
		}
	
		varWN = m_pRecordSet->GetCollect(_variant_t(_T("HMD")));  //是否黑名单
		if (varWN.vt != VT_NULL)//如果不为空
		{
			SFHMD = varWN;
		}
		else
		{
			SFHMD = "";
		}
		
		varWN = m_pRecordSet->GetCollect(_variant_t(_T("BeginTime")));  //进入时间
		if (varWN.vt != VT_NULL)//如果不为空
		{
			g_InputTime = varWN;
		}
		else
		{
			g_InputTime = "";
		}	
		
		varWN = m_pRecordSet->GetCollect(_variant_t(_T("QL_Time")));//签离时间
		if (varWN.vt != VT_NULL)//如果不为空
		{
			g_OutPutTime = varWN;
		}
		else
		{
			g_OutPutTime = "";
		}

		varWN = m_pRecordSet->GetCollect(_variant_t(_T("IDCardNum"))); //身份证号码
		if (varWN.vt != VT_NULL)//如果不为空
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
		varTmp = m_pRecordSet->GetFields()->GetItem("PictureDate")->GetChunk(m_Len);//读取字段
		if (varTmp.vt == (VT_ARRAY | VT_UI1))
		{
			pBuf = new char[m_Len];
			if (pBuf)
			{
				char *buff = NULL;
				SafeArrayAccessData(varTmp.parray, (void**)&buff);//把位图数据放到buff中去
				memcpy(pBuf, buff, m_Len);//把位图数据放到pBuff中

				SafeArrayUnaccessData(varTmp.parray);//释放

				m_pBMPBuffer1 = new char[m_Len];//开辟符数组
				memcpy(m_pBMPBuffer1, pBuf, m_Len);

				CString strJQ = _T("C:\\YTPicture");	//创建数据库图片的文件夹
				if (!PathIsDirectory(strJQ))
				{
					CreateDirectory(strJQ, 0);//不存在则创建 ,一级目录
				}
				strJQ = _T("C:\\YTPicture\\FKPicture");
				if (!PathIsDirectory(strJQ))
				{
					CreateDirectory(strJQ, 0);//不存在则创建，二级目录
				}

				strJQ += _T("\\") + g_IDCardNum + _T(".jpg");  //打开文件
				FILE *pFilePath = fopen(strJQ, "w+b"); //效率低
				if (NULL != pFilePath)
				{
					fwrite(m_pBMPBuffer1, 1, m_Len, pFilePath);	//写入文件		
					g_PicPath = strJQ;

					fclose(pFilePath);
				}

				delete m_pBMPBuffer1;
				m_pBMPBuffer1 = NULL;
				delete pBuf;
				pBuf = NULL;
			}
		}


		g_TypeReg_string = "访客";


		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //关闭记录集 
		}
		strSql.ReleaseBuffer(0);
		perComRes->ShouResult();//查询出来并显示到界面
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //关闭记录集 
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
			::MessageBox(NULL, _T("文件名不足15位"), _T("错误"), MB_ICONERROR);
			break;
		}
	}
	try
	{
		CString strSql;
		strSql.Format("SELECT * FROM [FaceContCen].[dbo].[PersonInfo] WHERE ID = '%s'", strCmpTmp.GetBuffer(0));

		m_pRecordSet->Open(_bstr_t(strSql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		g_TypeReg_string = "户主";
		_variant_t FP;

		FP = m_pRecordSet->GetCollect(_variant_t(_T("Name")));
		if (FP.vt != VT_NULL)//如果不为空
		{
			g_Name = FP;
		}
		else
		{
			g_Name = "";
		}

		FP = m_pRecordSet->GetCollect(_variant_t(_T("Sex")));
		if (FP.vt != VT_NULL)//如果不为空
		{
			g_Sex = FP;
		}
		else
		{
			g_Sex = "";
		}
		FP = m_pRecordSet->GetCollect(_variant_t(_T("Tel")));
		if (FP.vt != VT_NULL)//如果不为空
		{
			g_Tel = FP;
		}
		else
		{
			g_Tel = "";
		}
		FP = m_pRecordSet->GetCollect(_variant_t(_T("LD")));
		if (FP.vt != VT_NULL)//如果不为空
		{
			g_LD = FP;
		}
		else
		{
			g_LD = "";
		}
		FP = m_pRecordSet->GetCollect(_variant_t(_T("FH")));
		if (FP.vt != VT_NULL)//如果不为空
		{
			g_FH = FP;
		}
		else
		{
			g_FH = "";
		}

		FP = m_pRecordSet->GetCollect(_variant_t(_T("RegType")));
		if (FP.vt != VT_NULL)//如果不为空
		{
			g_IDCardNum = FP;
		}
		else
		{
			g_IDCardNum = "";
		}
		SFHMD = "否";

		CString IDNum;//照片编号
		FP = m_pRecordSet->GetCollect(_variant_t(_T("ID")));
		if (FP.vt != VT_NULL)//如果不为空
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
		varTmp = m_pRecordSet->GetFields()->GetItem("PictureDate")->GetChunk(m_Len);//读取字段
		if (varTmp.vt == (VT_ARRAY | VT_UI1))
		{
			pBuf = new char[m_Len];
			if (pBuf)
			{
				char *buff = NULL;
				SafeArrayAccessData(varTmp.parray, (void**)&buff);//把位图数据放到buff中去
				memcpy(pBuf, buff, m_Len);//把位图数据放到pBuff中

				SafeArrayUnaccessData(varTmp.parray);//释放

				m_pBMPBuffer1 = new char[m_Len];//开辟符数组
				memcpy(m_pBMPBuffer1, pBuf, m_Len);
			
				CString strJQ = _T("C:\\YTPicture");	//创建数据库图片的文件夹
				if (!PathIsDirectory(strJQ))
				{
					CreateDirectory(strJQ, 0);//不存在则创建 ,一级目录
				}
				strJQ = _T("C:\\YTPicture\\ZHPictureReg");
				if (!PathIsDirectory(strJQ))
				{
					CreateDirectory(strJQ, 0);//不存在则创建，二级目录
				}

				strJQ += _T("\\") + g_IDCardNum;  //打开文件
				FILE *pFilePath = fopen(strJQ, "w+b"); //效率低
				if (NULL != pFilePath)
				{
					fwrite(m_pBMPBuffer1, 1, m_Len, pFilePath);	//写入文件		
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
			m_pRecordSet->Close(); //关闭记录集 
		}

		strSql.ReleaseBuffer(0);
		perComRes->ShouResult(); //查询出来并显示到界面
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close(); //关闭记录集 
		}
		CATCH_ERROR;
	}
	
	ReleaseMutex(hMutex1);

	return 0;
}


void CPersComprResult::ShouResult()
{
	InvalidateRect(NULL, FALSE);
	g_SBFS = _T("人脸识别");
	if (!g_XSD_String.IsEmpty())
	{
		m_XSD_String = g_XSD_String;
	}

	m_HMD_String = SFHMD;  //是否为黑名单
	m_TypeReg_String = g_TypeReg_string;  //人员类型

	
	if (m_TypeReg_String == _T("户主") && !m_TypeReg_String.IsEmpty())
	{
		g_FKAddr = _T("无");  //访客住址
		g_BFZName = _T("无");
		g_BFZAddr = _T("无"); //被访者家庭住址
		g_InputTime = _T("无");
		g_OutPutTime = _T("无");//离开时间
		tmpAddr = _T("楼号: ") + g_LD + _T(" ;房号: ") + g_FH;
	}
	else
	{
		g_LD = _T("无");
		g_FH = _T("无");
		tmpAddr = g_FKAddr;
	}
	if (g_OutPutTime == _T("") || g_OutPutTime.IsEmpty())
	{
		g_OutPutTime = _T("未签离");
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
	WriteSqlResult(); //把识别结果写入数据库


	Ui_Show(g_PicResPath, IDC_SXJZQ);
	Ui_Show(g_PicPath, IDC_RegPicture);
	UpdateData(FALSE);
	
	//第一种方式，自动推送
	PushToPlatfrom();   //推送到第三方平台
}

void CPersComprResult::WriteSqlResult()  //把识别结果写入数据库
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
			m_pRecordSet->Close();     //关闭记录集
		}
		Sql.ReleaseBuffer(0);
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();     //关闭记录集
		}
		CATCH_ERROR;
	}
}

BOOL CPersComprResult::PushToPlatfrom()   //推送到第三方平台
{
	//SFHMD = _T("");     //是否黑名单
	//g_PicResPath = _T(""); //传回的照片路径 根据这个路径加载图片
	//g_XSD_String = _T("");  //相似度
	//g_TypeReg_string = _T("");  //识别类型
	//g_Name = _T("");   //姓名
	//g_FKAddr = _T("");  //访客住址
	//g_BFZName = _T("");
	//g_BFZAddr = _T(""); //被访者家庭住址
	//g_InputTime = _T("");
	//g_OutPutTime = _T(""); //离开时间

	//g_Sex = _T("");    //性别
	//g_Tel = _T("");    //电话
	//g_LD = _T("");    //楼栋号
	//g_FH = _T("");    //房间号
	//g_IDCardNum = _T("");  //身份证号
	//g_SBFS = _T("");         //人脸识别 刷卡方式

	int nSimlary = atoi(g_XSD_String);


	if (0 == strcmp(g_SBFS, "刷卡方式"))
	{
		//CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Post_Dev_Entrance_addEventICCard(DEVICEID, 1, 111, g_IDCardNum, "liming", g_Tel, 1, "182A1FF4", "lisi", "1a896cd5-51c2-47e8-a93f-7ecf834ad900", "beizhu"), (LPVOID)NULL, 0, 0));
		//TODO:
		Post_Dev_Entrance_addEventICCard(DEVICEID, 1, 111, g_IDCardNum, g_Name, g_Tel, 1, "182A1FF4", g_BFZName, "1a896cd5-51c2-47e8-a93f-7ecf834ad900", "备注");
	
	
	}
	else if (0 == strcmp(g_SBFS, "人脸识别"))
	{
		//TODO:
		Post_Dev_Entrance_AddEventPic(DEVICEID, 0, 111, g_IDCardNum, g_Name, g_Tel, 1, "", g_BFZName, "1a896cd5-51c2-47e8-a93f-7ecf834ad900", nSimlary, "备注", "pic", g_PicResPath);
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
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	Ui_Show(g_PicResPath, IDC_SXJZQ);
	Ui_Show(g_PicPath, IDC_RegPicture);
}


void CPersComprResult::OnBnClickedBtnsendclouds()
{
	// TODO: 在此添加控件通知处理程序代码

	//第二种方式，手动推送
	//PushToPlatfrom();   //推送到第三方平台


	MessageBox(_T("Test"), _T("提示"), 0);
}



void CPersComprResult::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}

void CPersComprResult::ReSize()
{
	float fsp[2];
	POINT Newp; //获取现在对话框的大小
	CRect recta;
	GetClientRect(&recta);     //取客户区大小  
	Newp.x = recta.right - recta.left;
	Newp.y = recta.bottom - recta.top;
	fsp[0] = (float)Newp.x / old.x;
	fsp[1] = (float)Newp.y / old.y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint, TLPoint; //左上角
	CPoint OldBRPoint, BRPoint; //右下角
	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //列出所有控件  
	while (hwndChild)
	{
		woc = ::GetDlgCtrlID(hwndChild);//取得ID
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	
	CDialogEx::OnClose();
}


void CPersComprResult::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	
}


void CPersComprResult::OnBnClickedBtn()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CPersComprResult::OnBnClickedBtnjjdoor()
{
	// TODO: 在此添加控件通知处理程序代码
	WSADATA wd;
	int err;
	int iResult;//绑定结果
	
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
		::MessageBox(NULL, "SOCKET 紧急开门连接失败", NULL, 0);
		closesocket(sockClient);
		WSACleanup();
		return;
	}
	//CString strPoto = "method" = "pc_open_door", "data" = "";

	char szBuf[100] = { "method = pc_open_door, data = " };
	int res = ::send(sockClient, (char *)szBuf, sizeof(szBuf), 0);
}

