// Picture1.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "Picture1.h"
#include "afxdialogex.h"


// CPicture1 对话框

IMPLEMENT_DYNAMIC(CPicture1, CDialogEx)

CPicture1::CPicture1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PERSON_INFO, pParent)
	, m_Image_String(_T(""))
	, m_Name(_T(""))
	, m_IDCard(_T(""))
	, m_DyId(_T(""))
	, m_LcId(_T(""))
	, m_LcIdd(_T(""))
	, m_ShId(_T(""))
{
	pBufImgDate = NULL;
}

CPicture1::~CPicture1()
{
}

void CPicture1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Picture, m_Image);
	DDX_Text(pDX, IDC_Face_Path, m_Image_String);
	DDX_Text(pDX, IDC_Name, m_Name);
	DDX_Text(pDX, IDC_ID, m_IDCard);
	DDX_Text(pDX, IDC_Ele, m_DyId);
	DDX_Text(pDX, IDC_LD, m_LcId);
	DDX_Text(pDX, IDC_CH, m_LcIdd);
	DDX_Text(pDX, IDC_SH, m_ShId);
	DDX_Control(pDX, IDC_LIST2, m_ListBox);
}


BEGIN_MESSAGE_MAP(CPicture1, CDialogEx)
	ON_BN_CLICKED(IDC_Add_PerFace, &CPicture1::OnBnClickedAddPerface)
	ON_BN_CLICKED(IDC_Dele_PerFace, &CPicture1::OnBnClickedDelePerface)
	ON_BN_CLICKED(IDC_Cannel, &CPicture1::OnBnClickedCannel)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_IDOK, &CPicture1::OnBnClickedIdok)
	ON_BN_CLICKED(IDC_Open_FacePath, &CPicture1::OnBnClickedOpenFacepath)
	ON_LBN_SELCHANGE(IDC_LIST2, &CPicture1::OnLbnSelchangeList2)
	ON_BN_CLICKED(IDC_Dele_List, &CPicture1::OnBnClickedDeleList)
END_MESSAGE_MAP()


// CPicture1 消息处理程序


void _ShowCtrlImage(CStatic* imageCtrl, CString strImagePath, CString strExt)
{
	if (strImagePath.IsEmpty() || -1 == strImagePath.Find(strExt.GetBuffer(0)))
		return;

	CImage image;
	image.Load(strImagePath);

	//以下两个矩形主要作用是，获取对话框上面的Picture Control的width和height，
	//并设置到图片矩形rectPicture，根据图片矩形rectPicture对图片进行处理，
	//最后绘制图片到对话框上Picture Control上面
	CRect rectControl;                        //控件矩形对象
	CRect rectPicture;                        //图片矩形对象

	int x = image.GetWidth();
	int y = image.GetHeight();
	imageCtrl->GetClientRect(rectControl);

	CDC *pDc = imageCtrl->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(),
		CSize((int)rectControl.Width(),
		(int)rectControl.Height()));

	imageCtrl->SetBitmap(NULL);

	//以下两种方法都可绘制图片
	image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); //将图片绘制到Picture控件表示的矩形区域
	//image.Draw(pDc->m_hDC, rectPicture);                //将图片绘制到Picture控件表示的矩形区域

	image.Destroy();
	imageCtrl->ReleaseDC(pDc);
}


CString _ShowFileDialog()
{
	CFileDialog fileDlg(TRUE, _T("jpg"), NULL, 0,
		_T("image Files(*.jpg)|*.JPG|All Files (*.*) |*.*"), NULL);
	fileDlg.DoModal();
	return fileDlg.GetPathName();
}

void CPicture1::OnPaint()
{
	CPaintDC dc(this);

	_ShowCtrlImage(&m_Image, m_image_path, CString(".jpg"));

}

//读取文件长度和数据
char * CPicture1::LoadImaData(CString imagPath)
{
	CFile     file;                        //定义一个文件变量
	if (!file.Open(imagPath, CFile::modeRead | CFile::typeBinary))//以只读二进制的方式打开文件
	{
		return NULL;
	}

	if (NULL  != pBufImgDate)//回收pBufImgDate分配的内存空间
	{
		delete []pBufImgDate;
		pBufImgDate = NULL;
	}
	
	m_nFileLen = file.GetLength();//获取文件的长度
	pBufImgDate = new char[m_nFileLen + 1];//开辟符数组
	if (!pBufImgDate)            //如果控件不够大
	{
		throw "内存分配失败";		
	}
	if (file.Read(pBufImgDate, m_nFileLen) != m_nFileLen)//读取文件保存在字符数组中
	{
		throw "文件读取错误";		
	}

	return pBufImgDate;
}

void CPicture1::OnBnClickedAddPerface()
{
	// TODO: 在此添加控件通知处理程序代码
	/*UpdateData(TRUE);
	m_image_path = _ShowFileDialog();

	LoadImaData(m_image_path);

	m_Image_String = m_image_path;

	UpdateData(FALSE);

	Invalidate(TRUE);*/
}


void CPicture1::OnBnClickedDelePerface()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_image_path = "";
	m_Image_String = m_image_path;
	
	UpdateData(FALSE);

	Invalidate(TRUE);
}


void CPicture1::OnBnClickedCannel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}

//解析文件名的name,idcard,ld,lc,dy,sh
void JxFNToArr(int nCount, int nMemLen, CString strTemp, unsigned char sendLine[10])
{
	bool   bFalge;
	int    posEnd;
	int    j;
	int    k;
	char *ch;
	bFalge = false;
	j = 0;
	int nPos = strTemp.Find(_T("#"));       //查找第一个","的位置

	for (int i = 0; i < nMemLen; i++)
	{
		//截取姓名
		if (0 == nCount && i < nPos)
		{
			CString tmp = strTemp.Mid(0, nPos);
			int val;
			k = 0;
			ch = (char *)tmp.GetBuffer(8);
			char *a = NULL;
			while (*ch)
			{
				//a = new char[sizeof(char)*sizeof(ch)];
				//strncpy(a, ch, 10);
				sscanf(ch, "%c", &val);
				sendLine[14 + k] = val;
				ch++;
				k++;
				//free(a);
			}
			sendLine[14 + k] = '\0';

			i = nPos;
			/*sendLine[14 + i] = strTemp.GetAt(i);
			i++;
			sendLine[14 + i] = strTemp.GetAt(i);*/
		}
		if (0 == nCount && i == nPos)
		{
			bFalge = true;
		}
		if (bFalge)
		{
			int nLen = strTemp.Delete(0, nPos + 1);		
			strTemp = strTemp.Right(nLen);

			nPos = strTemp.Find(_T("#"));       //查找第2个"#"的位置

			nCount++;
			j = 0;
			bFalge = false;
		}

		//截取身份证号
		if (1 == nCount && j < nPos)
		{
			CString tmp = strTemp.Mid(0, nPos);
			int val;
			k = 0;
			ch = (char *)tmp.GetBuffer(18);
			while (*ch)
			{
				sscanf(ch, "%02d", &val);
				sendLine[30 + k] = val;
				ch += 2;
				k++;
			}
			j = nPos;
		}
		else if (1 == nCount && j == nPos)
		{
			bFalge = true;
		}
		if (bFalge)
		{
			int nLen = strTemp.Delete(0, nPos + 1);
			strTemp = strTemp.Right(nLen);
			
			//小区楼层，单元，楼栋，室号
			posEnd = strTemp.ReverseFind('.');
			strTemp = strTemp.Left(posEnd);
			//
			nCount++;
			j = 0;
			bFalge = false;
		}

		//截取小区信息
		if (2 == nCount && j < posEnd)
		{
			int val;
			k = 0;
			ch = (char *)strTemp.GetBuffer(8);
			while (*ch)
			{
				sscanf(ch, "%02d", &val);
				sendLine[4 + k] = val;
				ch += 2;
				k++;
			}
			j = posEnd;
		}
	}
}

//发送协议包到控制器
void CPicture1::OnBnClickedIdok()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

/***********************************socket*******************************************************/
	SOCKET cliSockfd;

	SOCKADDR_IN  ser_Addr;

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		MessageBox(_T("WSAStartup Error!"), NULL, MB_OK);
		return ;
	}
	
	cliSockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == cliSockfd)
	{
		MessageBox(_T("socket_Init Error!"), NULL, MB_OK);
		return;
	}
	ser_Addr.sin_family = AF_INET;
	ser_Addr.sin_addr.s_addr = inet_addr("192.168.7.22");
	ser_Addr.sin_port = htons(6660);

	if (SOCKET_ERROR == connect(cliSockfd, (SOCKADDR*)&ser_Addr, sizeof(SOCKADDR)))
	{
		MessageBox(_T("connect Error!"), NULL, MB_OK);
		return;
	}
	/***************************************sendline***************************************************/
	
	//变量定义
	unsigned char sendLine[200];

	CString strTemp;
	int i;
	vector<CString>::iterator fileList;         //定义一个迭代器t	
										  //变量初始化
	int nCount = 0;
	int nMemLen = 0;
	
	for (fileList = m_FileList.begin(); fileList != m_FileList.end(); fileList++)
	{
		memset(sendLine, 0, sizeof(sendLine));
		nCount = 0;
		i = 0;
		i +=49;
		nMemLen = fileList->GetLength();
		strTemp = *fileList;
		//发送图片数据
		m_AllPath = csDirParth + "\\" + strTemp;
		//加载图片数据到pictmp
		try
		{
			char *picTmp = LoadImaData(m_AllPath);
		}
		catch (char *e)
		{
			MessageBox(e, NULL, MB_ICONERROR);
			break;
		}
		catch (...)
		{
			MessageBox(_T("未知错误"), NULL, MB_ICONERROR);
			break;
		}		

		sendLine[0] = 0x7e;
		sendLine[1] = 0x7e;
		sendLine[2] = 0x7e;
		sendLine[3] = 0x8b;
		sendLine[48] = 0x0d;
		sendLine[22] = 0x02;
		//图片文件大小
		sendLine[25] = m_nFileLen / 65536;
		sendLine[26] = m_nFileLen / 256;
		sendLine[27] = m_nFileLen;
		sendLine[28] = 0x02;
		sendLine[29] = 0x01;
		sendLine[30] = 0x01;

		//解析文件名中的信息
		JxFNToArr(nCount, nMemLen, strTemp, sendLine);

		//发送协议包
		if (SOCKET_ERROR == send(cliSockfd, (char *)sendLine, 49, 0))
		{
			MessageBox(_T("send data error"),NULL, MB_OK);	
		}
		else
		{
			CString t;
			t.Format(_T("send data %s success"), strTemp);			
			MessageBox(t, NULL, 0);
			
			//发送人脸照片
			if (SOCKET_ERROR != send(cliSockfd, pBufImgDate, m_nFileLen, 0))
			{
				CString t;
				t.Format(_T("send Picture %s success"), strTemp);
				MessageBox(t, NULL, 0);
			}
			else
			{
				MessageBox(_T("send picture error"), NULL, MB_OK);
			}
		}			
	}
}

void CPicture1::OnBnClickedOpenFacepath()
{
	// TODO: 在此添加控件通知处理程序代码
	ClearData();  //情况vector

	CFileDialog dlg(TRUE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框  
	if (dlg.DoModal() == IDOK)
		m_csFileName = dlg.GetPathName();
	else
		m_csFileName.Empty();

	int iEndPos = 0;
	iEndPos = m_csFileName.ReverseFind('\\');
	csDirParth = m_csFileName.Left(iEndPos);

	//获取文件名
	GetFileFromDir(csDirParth);

	if (m_FileList.empty())
	{
		return;
	}

	for (int i = 0; i < m_FileList.size(); i++)
	{
		m_ListBox.AddString(m_FileList.at(i));
	}
}

void CPicture1::GetFileFromDir(CString csDirPath)
{
	csDirPath += "\\*.jpg";

	HANDLE file;
	WIN32_FIND_DATA fileData;
	char line[1024];
	char fn[1000];

	//获取第一个文件名
	file = FindFirstFile(csDirPath.GetBuffer(0), &fileData);
	m_FileList.push_back(fileData.cFileName);

	//根据第一个文件名，向下获取
	bool bState = false;
	bState = FindNextFile(file, &fileData);
	while (bState)
	{
		m_FileList.push_back(fileData.cFileName);
		bState = FindNextFile(file, &fileData);
	}
}

//清空数据
void CPicture1::ClearData()
{
	if (!m_FileList.empty())
	{
		m_FileList.clear();
		vector<CString>().swap(m_FileList);
	}

	m_ListBox.ResetContent();
	m_LcId = "";
	m_LcIdd = "";
	m_DyId = "";
	m_ShId = "";
	m_Name = "";
	m_IDCard = "";
}


void CPicture1::Ui_Show_Info(CString m_filename)
{
	//名字
	int pos = m_filename.Find(_T("#"));
	m_Name = m_filename.Mid(0, pos);
	
	//删除已经截取的名字
	int nLen = m_filename.Delete(0, pos + 1);
	m_filename = m_filename.Right(nLen);
	
	//身份证
	pos = m_filename.Find(_T("#"));
	if (-1 != pos)
	{
		m_IDCard = m_filename.Mid(0, pos);
		//删除已经截取的身份证
		nLen = m_filename.Delete(0, pos + 1);
		m_filename = m_filename.Right(nLen);
		
		//小区楼层，单元，楼栋，室号
		int posEnd = m_filename.ReverseFind('.');
		m_filename = m_filename.Left(posEnd);
		//单元号
		m_DyId = m_filename.Left(2); //最左边的两个数字
		//楼层号
		nLen = m_filename.Delete(0, 2);
		m_filename = m_filename.Right(nLen);
		m_LcId = m_filename.Left(2);
		//楼栋号
		nLen = m_filename.Delete(0, 2);
		m_filename = m_filename.Right(nLen);
		m_LcIdd = m_filename.Left(2);
		//室号
		m_ShId = m_filename.Right(2);//最右边的两个数字	
	}
}

void CPicture1::OnLbnSelchangeList2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	int nIndex;//用于指定被选中项索引号的INT变量    
	nIndex = 0;
	CString m_filename;

	nIndex = m_ListBox.GetCurSel();//获取ListBox中选中项的索引号  
	m_ListBox.GetText(nIndex, m_filename);//将选中项索引号传入GetText函数中，把选中项内容赋给m_filename变量 

	m_AllPath = csDirParth + "\\" + m_filename;

	//LoadImaData(m_AllPath);

	m_Image_String = m_AllPath;
	m_image_path = m_AllPath;

	Ui_Show_Info(m_filename);

	UpdateData(FALSE);
	Invalidate(FALSE);
}


void CPicture1::OnBnClickedDeleList()
{
	// TODO: 在此添加控件通知处理程序代码
	ClearData();

	UpdateData(FALSE);
}
