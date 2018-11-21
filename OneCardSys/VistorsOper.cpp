// VistorsOper.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "VistorsOper.h"
#include "afxdialogex.h"
#include "SynPublic.h"

#include <atlconv.h>

#pragma  comment(lib, "SynIDCardAPI.lib")
bool g_bFlag = false;

CString Id_String = "";   //�õ�ҳ���ϵ����֤�ţ�ץͼ��
BOOL bFlage = TRUE;       //����һ����־����ֹ��ѭ��
CString  g_FilePath = ""; //ȫ���ļ���
CString g_pic_id = "";//��Ƭid��

// CVistorsOper �Ի���

IMPLEMENT_DYNAMIC(CVistorsOper, CDialogEx)

CVistorsOper::CVistorsOper(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLGVISITOPER, pParent)
	, m_Name_String(_T(""))
	, m_Sex_String(_T(""))
	, m_ID_String(_T(""))
	, m_FKAddr_String(_T(""))
	, m_BFZName_String(_T(""))
	, m_BFZAddr_String(_T(""))
	, m_Picture_Path(_T(""))
	, m_ShowInfoReg(_T(""))
	, m_SH_String(_T(""))
	, m_LH_String(_T(""))
	, m_PicId_String(_T(""))
	, m_Tel_String(_T(""))
	, m_FWJZTime(COleDateTime::GetCurrentTime())
{

}

CVistorsOper::~CVistorsOper()
{
	//LogOut();
}

void CVistorsOper::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VEDIT1, m_vEdit1);
	DDX_Control(pDX, IDC_VEDIT2, m_vEdit2);
	DDX_Control(pDX, IDC_VEDIT3, m_vEdit3);
	DDX_Control(pDX, IDC_VEDIT4, m_vEdit4);
	DDX_Control(pDX, IDC_VEDIT5, m_vEdit5);
	DDX_Control(pDX, IDC_VEDIT6, m_vEdit6);
	DDX_Control(pDX, IDC_VEDIT7, m_vEdit7);
	DDX_Control(pDX, IDC_VCOBXSEX, m_combxSex);
	DDX_Text(pDX, IDC_VEDIT2, m_Name_String);
	DDX_CBString(pDX, IDC_VCOBXSEX, m_Sex_String);
	DDX_Text(pDX, IDC_VEDIT3, m_ID_String);
	DDX_Text(pDX, IDC_VEDIT4, m_FKAddr_String);
	DDX_Text(pDX, IDC_VEDIT5, m_BFZName_String);
	DDX_Text(pDX, IDC_VEDIT6, m_BFZAddr_String);
	DDX_Text(pDX, IDC_VEDIT7, m_Picture_Path);
	DDX_Control(pDX, IDC_SVPERSHOW, m_Picture);
	DDX_Text(pDX, IDC_ShowInfo, m_ShowInfoReg);
	DDX_Text(pDX, IDC_EDIT_SH, m_SH_String);
	DDX_Text(pDX, IDC_EDIT_LH, m_LH_String);
	DDX_Text(pDX, IDC_Picture_ID, m_PicId_String);
	DDX_Control(pDX, IDC_Picture_ID, m_Edit_ID_Values);
	DDX_Text(pDX, IDC_EDITTel, m_Tel_String);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_FWJZTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_CTCTimeEd);
}


BEGIN_MESSAGE_MAP(CVistorsOper, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTNVINIT, &CVistorsOper::OnBnClickedBtnvinit)
	ON_BN_CLICKED(IDC_BTNVREAD, &CVistorsOper::OnBnClickedBtnvread)
	ON_BN_CLICKED(IDC_BTNVCLEAR, &CVistorsOper::OnBnClickedBtnvclear)
	ON_BN_CLICKED(IDC_BTNVREG, &CVistorsOper::OnBnClickedBtnvreg)
	ON_BN_CLICKED(IDC_BTNVLEAV, &CVistorsOper::OnBnClickedBtnvleav)
	ON_BN_CLICKED(IDC_BUTTON6, &CVistorsOper::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BtnSDSelectPicture, &CVistorsOper::OnBnClickedBtnsdselectpicture)
	ON_BN_CLICKED(IDC_BUTTON1, &CVistorsOper::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



//
//BOOL CVistorsOper::CheckLoginOk()
//{
//	if (0 < m_lLoginID)
//		return TRUE;
//	MessageBox(_T("��δ��¼��"), _T(""), MB_OK);
//	return FALSE;
//}

// CFaceOper ��Ϣ�������


/*****************************************************************************/

// CVistorsOper ��Ϣ�������
BOOL CVistorsOper::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

									// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	m_playHandle = 0;  //��ͼ���

	CRect rect1;
	GetClientRect(&rect1);     //ȡ�ͻ�����С  
	old.x = rect1.right - rect1.left;
	old.y = rect1.bottom - rect1.top;
	this->ShowWindow(SW_SHOWMAXIMIZED);


	m_CTCTimeEd.SetFormat(_T("yyyy-MM-dd    HH:mm:ss"));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVistorsOper::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

void CVistorsOper::OnBnClickedBtnvinit() //ˢ֤��ʼ��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString sMsg, sMsg2;
	unsigned int uiCurrBaud;
	int nRet, nRet2;
	m_iPort = 0;
	nRet = Syn_FindUSBReader();
	if (nRet == 0)
	{
		sMsg = "û���ҵ�������";
		g_bFlag = false;
	}
	else
	{
		m_iPort = nRet;
		Beep(4000, 200);
		if (nRet > 1000)
		{
			sMsg.Format("������������USB�˿� %d", nRet);
		}
		else
		{
			Sleep(200);
			nRet2 = Syn_GetCOMBaud(nRet, &uiCurrBaud);
			sMsg2.Format("%u", uiCurrBaud);
			sMsg.Format("�����������ڴ��� %d,��ǰSAM������Ϊ %u", nRet, uiCurrBaud);
		}
		g_bFlag = true;
	}
	m_vEdit1.SetWindowText(sMsg);
}


void CVistorsOper::OnBnClickedBtnvread()  //���������֤��Ϣ
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnBnClickedBtnvinit(); //ˢ֤��ʼ��

	int nRet;
	CString sMsg;
	CString sText;
	unsigned char pucIIN[4];
	unsigned char pucSN[8];
	IDCardData idcardData;
	int iPhototype;
	WCHAR buf[1024];
	char szTemp[10] = "";
	char szTempPath[200] = "";
	char szNewPath[200] = "";
	char *path = NULL;
	CString strPath = NULL;

	if (g_bFlag == false)
	{
		m_vEdit1.SetWindowText(_T("���ʼ����ȷ�϶�������������"));
		return;
	}

	CString csPath = _T("C:\\YTPicture");
	if (!PathIsDirectory(csPath))
	{
		CreateDirectory(csPath, 0);//�������򴴽�
	}
	csPath = _T("C:\\YTPicture\\FKPicture");//ÿ�ΰ�ѡ��·����cspath����ֹcstring���ӣ�����

	if (!PathIsDirectory(csPath))
	{
		CreateDirectory(csPath, 0);//�������򴴽�	
	}

	char   szBuffer[_MAX_PATH] = "C:\\YTPicture\\FKPicture";
	Syn_SetPhotoPath(2, szBuffer);	//������Ƭ·��	iOption ·��ѡ��	0=C:	1=��ǰ·��	2=ָ��·��
									//cPhotoPath	����·��,����iOption=2ʱ��Ч
	iPhototype = 1;
	Syn_SetPhotoType(1); //0 = bmp ,1 = Jpg , 2 = base64 , 3 = WLT ,4 = ������
	Syn_SetPhotoName(2); // ������Ƭ�ļ��� 0=tmp 1=���� 2=���֤�� 3=����_���֤�� 

	Syn_SetSexType(1);	// 0=���д洢������	1=����֮�������,�С�Ů��δ֪
	Syn_SetNationType(1);// 0=���д洢������	1=����֮������� 2=����֮���"��"
	Syn_SetBornType(3);			// 0=YYYYMMDD,1=YYYY��MM��DD��,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD
	Syn_SetUserLifeBType(1);	// 0=YYYYMMDD,1=YYYY��MM��DD��,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD
	Syn_SetUserLifeEType(1, 1);	// 0=YYYYMMDD(��ת��),1=YYYY��MM��DD��,2=YYYY.MM.DD,3=YYYY-MM-DD,4=YYYY/MM/DD,
								// 0=���� ��ת��,	1=����ת��Ϊ ��Ч�ڿ�ʼ+50��
	nRet = Syn_OpenPort(m_iPort);
	if (nRet == 0)
	{
		if (Syn_SetMaxRFByte(m_iPort, 80, 0) == 0)
		{
			nRet = Syn_StartFindIDCard(m_iPort, pucIIN, 0);
			nRet = Syn_SelectIDCard(m_iPort, pucSN, 0);
			nRet = Syn_ReadMsg(m_iPort, 0, &idcardData);
			if (nRet == 0 || nRet == 1)
			{
				sMsg = _T("��ȡ���֤��Ϣ�ɹ�!");
				m_vEdit1.SetWindowText(sMsg);
				sMsg.Format(_T("%s"), idcardData.Name);
				m_vEdit2.SetWindowText(sMsg);
				sMsg.Format(_T("%s"), idcardData.Sex);
				sprintf(szTemp, _T("%s"), idcardData.Sex);
				if (0 == strcmp(szTemp, _T("��")))
				{
					m_combxSex.SetCurSel(0);
				}
				else if (0 == strcmp(szTemp, _T("Ů")))
				{
					m_combxSex.SetCurSel(1);
				}


				//m_vEdit3.SetWindowText(sMsg);
				//sMsg.Format("����:%s", idcardData.Nation);

				//sMsg.Format("����:%s", idcardData.Born);

				sMsg.Format("%s", idcardData.Address);
				m_vEdit4.SetWindowText(sMsg);
				sMsg.Format("%s", idcardData.IDCardNo);
				m_vEdit3.SetWindowText(sMsg);
				//sMsg.Format("��֤����:%s", idcardData.GrantDept);
				//InsertDebugMes(sMsg);
				//sMsg.Format("��Ч�ڿ�ʼ:%s", idcardData.UserLifeBegin);
				//InsertDebugMes(sMsg);
				//sMsg.Format("��Ч�ڽ���:%s", idcardData.UserLifeEnd);
				//InsertDebugMes(sMsg);
				if (nRet == 1)
				{
					sMsg = _T("������Ƭʧ��");
				}
				else
				{			
					CString strTimeFile;    //��Ƭ���ļ������õ�ʱ������
					CTime tm;          //��ȡϵͳʱ��
					tm = CTime::GetCurrentTime();
					strTimeFile = tm.Format("%y%m%d%H%M%S");

					
					sMsg.Format(_T("%s"), idcardData.PhotoFileName);

					sprintf(szTempPath, _T("%s"), idcardData.PhotoFileName);  //old name XXX.Jpg
	

					sMsg = sMsg.Left(sMsg.Find('.'));		

					CString strTemp = _T("C:\\YTPicture\\FKPicture\\FK");
					
					sMsg = sMsg.Right(sMsg.GetLength() - 1 - sMsg.ReverseFind('\\')); //���֤��
					sMsg = strTimeFile + _T("E") + _T(".jpg");
					
					m_PicId_String =  _T("FK") + strTimeFile + _T("E");					
					m_Edit_ID_Values.SetWindowTextA(m_PicId_String);
					g_pic_id = m_PicId_String; // �����֤id���ϴ�id��

					sMsg = strTemp + sMsg;
					m_Picture_Path = sMsg;					
					strPath = sMsg;

					USES_CONVERSION;
					path = sMsg.GetBuffer(sMsg.GetLength() + 1);
			

					if (rename(szTempPath, path) == 0)
					{
						m_vEdit1.SetWindowText("������Ƭ�ɹ���");
					}
					else
					{
						if (remove(szTempPath) == 0)
						{
							m_vEdit1.SetWindowText("������Ƭ�ɹ���");
						}
						else
						{
							m_vEdit1.SetWindowText("������Ƭʧ�ܣ�");
							AfxMessageBox(_T("������Ƭʧ��"));
						}
					}
					
				}

				//InsertDebugMes(sMsg);
				m_vEdit7.SetWindowText(sMsg);
				sMsg.ReleaseBuffer();
				if (iPhototype == 0 && nRet == 0)
				{
					HBITMAP hBitmap;
					CStatic *pStatic = (CStatic *)GetDlgItem(IDC_SVPERSHOW);
					sText.Format("%s", idcardData.PhotoFileName);
					hBitmap = (HBITMAP) ::LoadImage(NULL, sText, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
					pStatic->ModifyStyle(0XF, SS_BITMAP);
					pStatic->SetBitmap(hBitmap);
				}
				else if (iPhototype == 1 && nRet == 0)
				{
					CRect rect;
					USES_CONVERSION;
					wcscpy(buf, A2W((LPCSTR)strPath));  //CString -> wchar_t
														//Image image(L"C:\\temp1", TRUE);  
					Image image(buf, TRUE);

					CWnd *pWnd = GetDlgItem(IDC_SVPERSHOW);
					Graphics graphics(pWnd->GetDC()->m_hDC);
					GetDlgItem(IDC_SVPERSHOW)->GetClientRect(&rect);
					graphics.DrawImage(&image, 0, 0, rect.Width(), rect.Height());

				}
			}
			else
			{
				sMsg = "��ȡ���֤��Ϣ����!";
				m_vEdit1.SetWindowText(sMsg);
			}
		}
	}
	else
	{
		sMsg = "�򿪶˿ڴ���";
		m_vEdit1.SetWindowText(sMsg);
	}
	Syn_ClosePort(m_iPort);
}

void CVistorsOper::ClearDate()
{
	m_vEdit1.SetWindowText("");
	m_vEdit2.SetWindowText("");
	m_vEdit3.SetWindowText("");
	m_vEdit4.SetWindowText("");
	m_vEdit5.SetWindowText("");
	m_vEdit6.SetWindowText("");
	m_vEdit7.SetWindowText("");
	m_combxSex.SetCurSel(-1);

	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_SVPERSHOW);
	CRect lRect;
	pStatic->GetClientRect(&lRect);
	pStatic->GetDC()->FillSolidRect(lRect.left, lRect.top, lRect.Width(), lRect.Height(), RGB(240, 240, 240));

	m_ID_String = "";
	m_Picture_Path = "";
	Id_String = "";   //�õ�ҳ���ϵ����֤�ţ�ץͼ��
	bFlage = TRUE;       //����һ����־����ֹ��ѭ��
	g_FilePath = ""; //ȫ���ļ���
	m_Sex_String = "";
	m_FKAddr_String = "";
	m_BFZName_String = "";
	m_BFZAddr_String = "";
	m_Name_String = "";
	m_LH_String = "";
	m_SH_String = "";
	m_PicId_String = "";


	InvalidateRect(NULL, FALSE);
}

void CVistorsOper::OnBnClickedBtnvclear()  //�������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRect rect;
	
	CWnd *pWnd = GetDlgItem(IDC_SVPERSHOW);
	Graphics graphics(pWnd->GetDC()->m_hDC);
	GetDlgItem(IDC_SVPERSHOW)->GetClientRect(&rect);
	//graphics.DrawImage(&image, 0, 0, rect.Width(), rect.Height());
	Color color;
	graphics.Clear(color.LightGray);
	
	ClearDate();
	m_ShowInfoReg = "";
							  // CVistorsOper �Ի���
	UpdateData(FALSE);
}

void CVistorsOper::OnBnClickedBtnvreg()      //�Ǽǣ��ϴ��������鿴�����ݾ����Ƿ��м�¼����ǩ���¼��ֱ�Ӹ��ֶΣ��ϴ�������û�м�¼���ϴ�������ע��
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	int upFaceFlage = 0; //��Ƭ�ϴ��ɹ���Ϊ1�����д�����ݿ�ʧ�ܣ�����Ƭ�ϴ��ɹ�����ɾ����Ƭ

	if (TRUE != CheckLoginOk())
		return;

	CString strTime;
	CTime   timTemp;
	timTemp = CTime::GetCurrentTime();
	strTime = timTemp.Format("%Y-%m-%d %H:%M:%S");   //�Ǽ�ʱ��
	CString IDNum = g_pic_id;
	CString HMD = _T("��");
	

	if (m_ID_String.IsEmpty())   //������֤�Ƿ�Ϊ��
	{
		AfxMessageBox(_T("���֤Ϊ�գ���������"));

		return;
	}
	int nLen = m_ID_String.GetLength();  //���֤
	for (int i = 0; i<nLen;i++)
	{
		if (!(m_ID_String.GetAt(i) >= '0' && m_ID_String.GetAt(i) <= '9' || m_ID_String.GetAt(i) >= 'A' && m_ID_String.GetAt(i) <= 'Z'))
		{
			MessageBox(_T("���֤��ʽ����"), _T("����������"), 0);
			return;
		}
	}

	/************************************************************************/
	/* ��֤����                                                             */
	/************************************************************************/
	g_strPictureId = m_PicId_String;
	g_strFacePath = m_Picture_Path;

	CWintCheckVido m_cWintCheck;
	m_cWintCheck.DoModal();

	if (g_ReconPass != 1)
	{
		m_ShowInfoReg = _T("��֤���鲻ͨ����������!");
		return;
	}
	else
	{
		m_ShowInfoReg = g_strPictureId + _T("��֤����ͨ��");
	}

	//// apiʵ��ָ��
	//BaiduFaceApi *api = new BaiduFaceApi();
	//std::string res1 = api->match(m_Picture_Path, 2, "d:\\8.jpg", 2);


   /************************************************************************/
   /* ����Ƭת�ɶ����ƴ������ݿ�                                           */
   /************************************************************************/
	m_varPictureToEJZ = PictureToEJZ(m_Picture_Path); 
	if (0 == m_varPictureToEJZ.iVal)
	{
		m_ShowInfoReg = _T("����ͼƬת���ɶ�����ʧ�ܣ�������");

		return;
	}
	m_nPictureLen = g_PictureLen; //��ȡ��Ƭ�Ķ��������ݴ�С
	

	/************************************************************************/
	/*  �ϴ���Ƭ�������                                                    */
	/************************************************************************/
	if (UpFacePicture(g_pic_id, m_lLoginID, m_Picture_Path) == TRUE)  //
	{
		upFaceFlage = 1;		
	}
	else
	{
		CWnd *pBtn1 = GetDlgItem(IDC_BUTTON1); //����ѡȡ��Ƭ����
		pBtn1->EnableWindow(TRUE);

		return;
	}


	/************************************************************************/
	/* У��ÿ��Ƿ����														*/
	/* ��ʼ																    */
	/************************************************************************/ 
	try             	//���Ȳ�ѯ���ݿ�
	{
		CString ID_Tmp = "";   //id��ʱ����
		CString HMD_Tmp = "";  //��������ʱ����

		CString Sql;
		Sql.Format("SELECT IDCardNum,HMD FROM [FaceContCen].[dbo].[FK_UserTabel] WHERE IDCardNum = '%s'", m_ID_String);

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);
		
		//����������
		ID_Tmp = m_pRecordSet->GetCollect(_variant_t(_T("IDCardNum")));  //�û�������ֱ�ӵ�catch
		if (!ID_Tmp.IsEmpty())
		{
			HMD_Tmp = m_pRecordSet->GetCollect(_variant_t(_T("HMD")));

			if (HMD_Tmp == "��")
			{
				MessageBox(_T("�÷ÿ�Ϊ�������û�,��ע�⣡"),_T("����"),MB_OK|MB_ICONERROR);
				
				goto RegUse;
			}
			else   //�û�����Ҳ���Ǻ������û�
			{
			RegUse:

				try
				{
					if (m_pRecordSet->State)
					{
						m_pRecordSet->Close();
					}

					CString Sql;
					Sql.Format("UPDATE [FaceContCen].[dbo].[FK_UserTabel] SET IDNum = '%s', BeginTime = '%s',SingnOff = '%s',BFZ_Name = '%s',BFZ_LH = '%s',BFZ_FH = '%s',QL_Time = '%s' WHERE IDCardNum = '%s'", IDNum.GetBuffer(0), strTime.GetBuffer(0), "��", m_BFZName_String.GetBuffer(0), m_LH_String.GetBuffer(0), m_SH_String.GetBuffer(0) , _T("δǩ��"), m_ID_String.GetBuffer(0));

					
					m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
						adLockOptimistic, adCmdText);

					m_ShowInfoReg = _T("ID:") + m_ID_String + _T("  ����: ") + m_Name_String + _T(" �ٴεǼǳɹ�");	

					if (m_pRecordSet->State)   //�رռ�¼��
					{
						m_pRecordSet->Close();
					}

					goto FaceReg;
				}
				catch (_com_error e)
				{
					if (m_pRecordSet->State)
					{
						m_pRecordSet->Close();
					}
					CATCH_ERROR;
					if (1 == upFaceFlage) //
					{
						DropFacePicture(g_pic_id, m_lLoginID);	 //ɾ��ע��sqlʧ��ʱ����Ƭ�ϴ��ɹ�����Ƭ
						upFaceFlage = 0;
					}
					MessageBox(_T("ע��ʧ��"), _T("ע��"), MB_OK);

					return;
				}
			}
		}
		if (m_pRecordSet->State)		//�رռ�¼��
		{
			m_pRecordSet->Close();
		}
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}		
	}	

	/************************************************************************/
	/* ���û�ע��                                                           */
	/************************************************************************/
	try    
	{
		CString strSql = _T("");
		strSql.Format(_T("Select * from [FaceContCen].[dbo].[FK_UserTabel]"));  //ѡ�����ݿ��
		m_pRecordSet->Open(_bstr_t(strSql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);  //�򿪱�
		m_pRecordSet->AddNew();  //�������һ����¼
		m_pRecordSet->PutCollect("IDNum", IDNum.GetString());
		m_pRecordSet->PutCollect("Name", m_Name_String.GetString());
		m_pRecordSet->PutCollect("Sex", m_Sex_String.GetString());
		m_pRecordSet->PutCollect("IDCardNum", m_ID_String.GetString());
		m_pRecordSet->PutCollect("BFZ_Name", m_BFZName_String.GetString());
		m_pRecordSet->PutCollect("FK_Addr", m_FKAddr_String.GetString());
		m_pRecordSet->PutCollect("BFZ_LH", m_LH_String.GetString());
		m_pRecordSet->PutCollect("BFZ_FH", m_SH_String.GetString());
		m_pRecordSet->PutCollect("BeginTime", strTime.GetString());
		m_pRecordSet->PutCollect("HMD", HMD.GetString());
		m_pRecordSet->PutCollect("SingnOff", _T("��"));
		if (m_nPictureLen > 0)   //��ͼƬ�浽sql
		{
			m_pRecordSet->PutCollect("PictureLength", m_nPictureLen);
			m_pRecordSet->GetFields()->GetItem("PictureDate")->AppendChunk(m_varPictureToEJZ);
		}

		m_pRecordSet->Update();  //��¼���µ�sql
		m_pRecordSet->Close();

		m_ShowInfoReg = _T(" ID: ") + m_ID_String + _T("\n ����: ") + m_Name_String + _T("�Ǽǳɹ�");
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T(" ID: ") + m_ID_String + _T("\n ����: ") + m_Name_String + _T("\n �Ǽ�ʧ�ܣ������µǼ�"));

		if (m_pRecordSet->State)
		{
			m_pRecordSet->CancelUpdate();  //�ر�updae�쳣
			m_pRecordSet->Close();
		}
		CATCH_ERROR;
	}
	
FaceReg:
	g_Action = _T("�ÿ͵Ǽ�");
	OperRZ(g_Action);          //��־
	
	/************************************************************************/
	/* ����                                                                  */
	/************************************************************************/
	ClearDate();
	UpdateData(FALSE);
}

void CVistorsOper::OperRZ(CString g_Action)
{
	////////////////////////��־////////////////////////////////////////////	
	CTime tmp_tm = CTime::GetCurrentTime();
	CString TimeEnd = tmp_tm.Format("%y-%m-%d %H:%M:%S");
	try
	{
		CString Sql;
		Sql.Format("INSERT INTO [FaceContCen].[dbo].[SysRunLog](IdNum,Name,QX,BeginData,EndData,Action,Ip,SysRun) Values(%d,'%s','%s','%s','%s','%s','%s','%s')", g_UserId, g_UseName, g_QX, g_Time, TimeEnd, g_Action, g_Ip, g_SysRunRZ);

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}
		//CATCH_ERROR;
	}
	/////////////////////////////��־///////////////////////////////////////
}

void CVistorsOper::OnBnClickedBtnvleav()     //ǩ�� �����ݿ��ֶΣ�ɾ������
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

	if (TRUE != CheckLoginOk())
	{
		return;
	}
	CString m_strIdTmp = "";//��Ƭ���
	CString strTime;
	CTime   timTemp;
	timTemp = CTime::GetCurrentTime();
	strTime = timTemp.Format("%Y-%m-%d %H:%M:%S   ");   //ǩ��ʱ��
	try    //�鿴���֤�Ƿ������ݿ��У�����˵���������Ѿ�ǩ�����δ�Ǽ�
	{
		CString Sql;
		Sql.Format("SELECT IDNum FROM [FaceContCen].[dbo].[FK_UserTabel] WHERE IDCardNum = '%s'", m_ID_String);

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);	
		
		_variant_t FP;	
		FP = m_pRecordSet->GetCollect(_variant_t(_T("IDNum")));
		if (FP.vt != VT_NULL)//�����Ϊ��
		{
			m_strIdTmp = FP;
		}
		else
		{
			m_strIdTmp = "";
		}
		
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}
	}
	catch (_com_error e)
	{		
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}

		m_ID_String = "";
		AfxMessageBox("���û�δ�Ǽǣ���Ǽǣ�");

		return;
	}

	if (m_ID_String.IsEmpty())
	{
		AfxMessageBox(_T("���֤Ϊ�գ���������"));

		return;
	}
	//MessageBox(m_strIdTmp, "ǩ��", 0);

	if (TRUE != DropFacePicture(m_strIdTmp, m_lLoginID))
	{
		m_ShowInfoReg = _T("�������Ƭɾ��ʧ��,���ԣ�");
		UpdateData(FALSE);

		return;
	}	

	try
	{	
		CString Sql;
		Sql.Format("UPDATE [FaceContCen].[dbo].[FK_UserTabel] SET QL_Time = '%s', SingnOff = '%s'  WHERE IDCardNum = '%s'", strTime.GetBuffer(0),_T("��"), m_ID_String.GetBuffer(0));

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);

		m_ShowInfoReg = _T(" ID: ") + m_ID_String + _T(" ����: ") + m_Name_String + _T(" ǩ��ɹ�");

		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}
		ClearDate(); //�����Ļ
	}
	catch (_com_error e)
	{
		if (m_pRecordSet->State)
		{
			m_pRecordSet->Close();
		}

		m_ShowInfoReg = (_T(" ID: ") + m_ID_String + _T("\n ����: ") + m_Name_String + _T("\n ǩ��ʧ�ܣ�������һ��"));
	}

	g_Action = m_Name_String + _T("  �ÿ�ǩ��");     //��־
	OperRZ(g_Action);
	
	UpdateData(FALSE);
}


void CVistorsOper::OnBnClickedButton6()     //�ֶ�ѡȡ�ÿ���Ƭ�ϴ�
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

int CALLBACK realload_callback1(LLONG lAnalyzerHandle,
								DWORD dwEventType,
								void* pEventInfo,
								BYTE *pBuffer,
								DWORD dwBufSize,
								LDWORD dwUser,
								int nSequence,
								void *reserved)
{
	if (dwEventType == EVENT_SP_FACE_SNAP_PART)   // ��������ͼ
	{
		STU_EVENT_FACE_SNAP_WHOLE stu = { 0 };
		memcpy(&stu, pEventInfo, sizeof(STU_EVENT_FACE_SNAP_WHOLE));
		
		// pBuffer ��ͼƬ���ݣ�dwBufSize ��ͼƬ���ݴ�С		 	
		CString strJQ = _T("C:\\YTPicture");	//��ȡ�ַ����������ļ���
		if (!PathIsDirectory(strJQ))
		{
			CreateDirectory(strJQ, 0);//�������򴴽� ,һ��Ŀ¼
		}
		strJQ = _T("C:\\YTPicture\\FKPicture");
		if (!PathIsDirectory(strJQ))
		{
			CreateDirectory(strJQ, 0);//�������򴴽�������Ŀ¼
		}
		//strJQ += _T("/FK") + Id_String + _T(".jpg");

		

		CString strTimeFile;
		CTime tm;          //��ȡϵͳʱ��
		tm = CTime::GetCurrentTime();
		strTimeFile = tm.Format("FK%y%m%d%H%M%S");

		strJQ += _T("\\") + strTimeFile + _T("E") + _T(".jpg");
		g_pic_id = strTimeFile + _T("E");
		FILE *pFilePath = fopen(strJQ, _T("w+b")); //Ч�ʵ�
		if (NULL != pFilePath)
		{
			fwrite(pBuffer, 1, dwBufSize, pFilePath);	//д���ļ�		
			g_FilePath = strJQ;
			
			fclose(pFilePath);
		}
		else
		{
			g_FilePath = _T("");
			MessageBox(NULL, _T("ץȡʧ�ܣ�����һ�Σ�"), NULL, MB_ICONERROR);
		}
	}

	return 0;
}


BOOL CVistorsOper::StartRealStream()
{
	// ͼƬ���ݴ����� realload_callback �ص���
	int nChannel = 0;

	m_playHandle = Net_RealLoadPicture(m_ZPLoginID, nChannel, EVENT_SP_FACE_SNAP_PART, 1,
		realload_callback1, NULL, NULL);
	if (0 >= m_playHandle)
	{
		MessageBox(_T("����������������ȡ��������.\n"), NULL, MB_ICONERROR);
		Net_LogoutDevice(m_ZPLoginID);

		return FALSE;
	}

	return TRUE;
}

void CVistorsOper::OnBnClickedBtnsdselectpicture()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
}


void CVistorsOper::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	UpdateData(TRUE);

	Id_String = m_ID_String;

	if (Id_String.IsEmpty())
	{
		MessageBox(_T("���֤Ϊ�գ����������֤����"), NULL, MB_ICONERROR);

		return;
	}
	else
	{
		m_ShowInfoReg = _T("���ڲɼ��������ݣ����Ժ�......");
	}

	if (StartRealStream())
	{
		UiTimer = SetTimer(1, 100, NULL);  //������ʱ����ʵʱˢ�½���

		CWnd *pBtn1 = GetDlgItem(IDC_BUTTON1);
		pBtn1->EnableWindow(FALSE);
	}

	UpdateData(FALSE);
}

void CVistorsOper::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nIDEvent)
	{
	case 1:
	{
		ExecuPicture();//ˢ�½�������ͼƬ++	
	}
	break;
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

BOOL  CVistorsOper::ExecuPicture()
{
	UpdateData(TRUE);
	CString strExt(".jpg");
	if (g_FilePath.IsEmpty() || -1 == g_FilePath.Find(strExt.GetBuffer(0)))
		return FALSE;

	CImage image;
	image.Load(g_FilePath);
	
	CRect rectControl;                        //�ؼ����ζ���
	CRect rectPicture;                        //ͼƬ���ζ���

	int x = image.GetWidth();
	int y = image.GetHeight();
	(&m_Picture)->GetClientRect(rectControl);

	CDC *pDc = (&m_Picture)->GetDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);

	rectPicture = CRect(rectControl.TopLeft(),
		CSize((int)rectControl.Width(),
		(int)rectControl.Height()));

	(&m_Picture)->SetBitmap(NULL);

	//�������ַ������ɻ���ͼƬ
	image.StretchBlt(pDc->m_hDC, rectPicture, SRCCOPY); //��ͼƬ���Ƶ�Picture�ؼ���ʾ�ľ�������

	image.Destroy();
	(&m_Picture)->ReleaseDC(pDc);	

	if (!g_FilePath.IsEmpty() && bFlage)
	{
		bFlage = FALSE;
		if (IDYES == MessageBox(_T("ȷʵʹ�ô�������"), _T("ȷ��"), MB_YESNO | MB_ICONQUESTION))
		{
			if (0 >= m_playHandle)
			{
				MessageBox(_T("�ֶ�ѡȡ�ÿ���Ƭ"), _T("Tip"), MB_ICONERROR);

				return FALSE;
			}
			bFlage = TRUE;

			m_Picture_Path = g_FilePath;  //����edit·��
			Net_StopLoadPicture(m_playHandle); //ֹͣ������������

			KillTimer(1);  //������ʱ��

			CWnd *pBtn1 = GetDlgItem(IDC_BUTTON1);
			pBtn1->EnableWindow(TRUE);
			m_ShowInfoReg = _T("��Ƭ�ɼ��ɹ����������һ��������");
			m_PicId_String = g_pic_id;
			UpdateData(FALSE);

			return TRUE; 
		}
		else
		{
			g_FilePath = _T("");
			bFlage = TRUE;

			CStatic* pStatic = (CStatic*)GetDlgItem(IDC_SVPERSHOW);
			CRect lRect;
			pStatic->GetClientRect(&lRect);
			pStatic->GetDC()->FillSolidRect(lRect.left, lRect.top, lRect.Width(), lRect.Height(), RGB(240, 240, 240));

			CWnd *pBtn1 = GetDlgItem(IDC_BUTTON1);
			pBtn1->EnableWindow(TRUE);
		}
	}

	UpdateData(FALSE);
	return FALSE;
}

void CVistorsOper::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���
	//DestroyWindow();

	CDialogEx::OnCancel();
}


void CVistorsOper::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���
//	delete this;
	CDialogEx::PostNcDestroy();
}


void CVistorsOper::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	CDialogEx::OnClose();
}

void CVistorsOper::ReSize()
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

		if (woc == IDC_VCOBXSEX)
		{
			OldTLPoint = Rect.TopLeft();
			TLPoint.x = float(OldTLPoint.x*fsp[0]) + 0.5;
			TLPoint.y = float(OldTLPoint.y*fsp[1]) + 0.5;
			BRPoint.x = TLPoint.x + Rect.Width();
			BRPoint.y = TLPoint.y + Rect.Height();
			Rect.SetRect(TLPoint, BRPoint);
			GetDlgItem(woc)->MoveWindow(Rect, TRUE);
			hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
		}
		else
		{
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
	}
	old = Newp;
}

void CVistorsOper::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������

	if (nType == SIZE_RESTORED || nType == SIZE_MAXIMIZED)
	{
		ReSize();
	}
}
