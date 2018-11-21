// ExportPicture.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "ExportPicture.h"
#include "afxdialogex.h"


// CExportPicture �Ի���

IMPLEMENT_DYNAMIC(CExportPicture, CDialogEx)

CExportPicture::CExportPicture(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIAEXPORT, pParent)
	, m_ExportPath_string(_T(""))
{

}

CExportPicture::~CExportPicture()
{
}

void CExportPicture::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ExcOut, m_ExportPath_string);
	DDX_Control(pDX, IDC_Picture, m_ExportPicture);
}

BOOL CExportPicture::ExportFun()
{
	try
	{
		CString Sql;
		Sql.Format(_T("SELECT * FROM [FaceContCen].[dbo].[PersonInfo] "));

		m_pRecordSet->Open(_bstr_t(Sql), m_pConnection.GetInterfacePtr(), adOpenDynamic,
			adLockOptimistic, adCmdText);
		CString IDCardNum = _T("");  //��Ƭ�ı��
		CString Name = _T("");

		for (int i = 0; !m_pRecordSet->adoEOF; i++)
		{
			m_Len = m_pRecordSet->GetCollect(_variant_t("PictureLength"));
			varTmp = m_pRecordSet->GetFields()->GetItem("PictureDate")->GetChunk(m_Len);//��ȡ�ֶ�
			IDCardNum = m_pRecordSet->GetCollect(_variant_t("ID"));
			Name = m_pRecordSet->GetCollect("Name");
			if (varTmp.vt == (VT_ARRAY | VT_UI1))
			{
				pBuf = new char[m_Len];
				if (pBuf)
				{
					char *buff = NULL;
					SafeArrayAccessData(varTmp.parray, (void**)&buff);//��λͼ���ݷŵ�buff��ȥ
					memcpy(pBuf, buff, m_Len);//��λͼ���ݷŵ�pBuff��

					SafeArrayUnaccessData(varTmp.parray);//�ͷ�

					m_pBMPBuffer = new char[m_Len];//���ٷ�����
					memcpy(m_pBMPBuffer, pBuf, m_Len);

					//��ȡ�ַ����������ļ���
					CString strJQ = _T("C:\\YTPicture");
					if (!PathIsDirectory(strJQ))
					{
						CreateDirectory(strJQ, 0);//�������򴴽�
					}
					strJQ = _T("C:\\YTPicture\\AllYZPicture");
					if (!PathIsDirectory(strJQ))
					{
						CreateDirectory(strJQ, 0);//�������򴴽�
					}

					strJQ += _T("\\") + IDCardNum + _T(".jpg");
					FILE *pFilePath = fopen(strJQ, _T("w+b")); //Ч�ʵ�
					if (NULL != pFilePath)
					{
						fwrite(m_pBMPBuffer, 1, m_Len, pFilePath);	//д���ļ�	
						fclose(pFilePath);
						Sleep(10);
						m_ExportPath_string = strJQ;
						Ui_Show(strJQ, IDC_Picture);
						UpdateData(FALSE);
					}
					else
					{
						MessageBox(Name, _T("����ʧ��~"), MB_ICONERROR);
					    continue;
					}

				}
			}

			m_pRecordSet->MoveNext();
		}
		if (m_pRecordSet->adoEOF)
		{
			if (IDYES == MessageBox(_T("������ɣ��Ƿ�رմ��ڣ�"), _T("�������"),MB_YESNO))
			{
				CDialogEx::OnCancel();
			}
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
		CATCH_ERROR;
	}
	

	return 0;
}


BEGIN_MESSAGE_MAP(CExportPicture, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT_ExcOut, &CExportPicture::OnEnChangeEditExcout)
END_MESSAGE_MAP()


// CExportPicture ��Ϣ�������


void CExportPicture::Ui_Show(CString strPicture_Path, int myIDC)
{
	WCHAR buf[1024];
	CRect rect;
	USES_CONVERSION;
	wcscpy(buf, A2W((LPCSTR)strPicture_Path));  //CString -> wchar_t

	Image image(buf, TRUE);
	CWnd *pWnd = GetDlgItem(myIDC);
	Graphics graphics(pWnd->GetDC()->m_hDC);
	GetDlgItem(myIDC)->GetClientRect(&rect);
	graphics.DrawImage(&image, 0, 0, rect.Width(), rect.Height());
}


BOOL CExportPicture::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	//ExportFun();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CExportPicture::OnEnChangeEditExcout()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
