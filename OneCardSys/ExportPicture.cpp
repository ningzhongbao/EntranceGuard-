// ExportPicture.cpp : 实现文件
//

#include "stdafx.h"
#include "OneCardSys.h"
#include "ExportPicture.h"
#include "afxdialogex.h"


// CExportPicture 对话框

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
		CString IDCardNum = _T("");  //照片的编号
		CString Name = _T("");

		for (int i = 0; !m_pRecordSet->adoEOF; i++)
		{
			m_Len = m_pRecordSet->GetCollect(_variant_t("PictureLength"));
			varTmp = m_pRecordSet->GetFields()->GetItem("PictureDate")->GetChunk(m_Len);//读取字段
			IDCardNum = m_pRecordSet->GetCollect(_variant_t("ID"));
			Name = m_pRecordSet->GetCollect("Name");
			if (varTmp.vt == (VT_ARRAY | VT_UI1))
			{
				pBuf = new char[m_Len];
				if (pBuf)
				{
					char *buff = NULL;
					SafeArrayAccessData(varTmp.parray, (void**)&buff);//把位图数据放到buff中去
					memcpy(pBuf, buff, m_Len);//把位图数据放到pBuff中

					SafeArrayUnaccessData(varTmp.parray);//释放

					m_pBMPBuffer = new char[m_Len];//开辟符数组
					memcpy(m_pBMPBuffer, pBuf, m_Len);

					//截取字符串，创建文件夹
					CString strJQ = _T("C:\\YTPicture");
					if (!PathIsDirectory(strJQ))
					{
						CreateDirectory(strJQ, 0);//不存在则创建
					}
					strJQ = _T("C:\\YTPicture\\AllYZPicture");
					if (!PathIsDirectory(strJQ))
					{
						CreateDirectory(strJQ, 0);//不存在则创建
					}

					strJQ += _T("\\") + IDCardNum + _T(".jpg");
					FILE *pFilePath = fopen(strJQ, _T("w+b")); //效率低
					if (NULL != pFilePath)
					{
						fwrite(m_pBMPBuffer, 1, m_Len, pFilePath);	//写入文件	
						fclose(pFilePath);
						Sleep(10);
						m_ExportPath_string = strJQ;
						Ui_Show(strJQ, IDC_Picture);
						UpdateData(FALSE);
					}
					else
					{
						MessageBox(Name, _T("保存失败~"), MB_ICONERROR);
					    continue;
					}

				}
			}

			m_pRecordSet->MoveNext();
		}
		if (m_pRecordSet->adoEOF)
		{
			if (IDYES == MessageBox(_T("导入完成，是否关闭窗口？"), _T("导入完成"),MB_YESNO))
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


// CExportPicture 消息处理程序


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

	// TODO:  在此添加额外的初始化

	//ExportFun();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CExportPicture::OnEnChangeEditExcout()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
