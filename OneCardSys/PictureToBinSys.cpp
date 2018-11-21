#include "stdafx.h"
#include "PictureToBinSys.h"


DWORD g_PictureLen = 0;
DWORD			 m_nFileLen    = 0;           //文件的长度
char			 *m_pJPGBuffer = NULL;        //缓冲图片区
VARIANT			 varBLOB       = { 0 };			   //存储图片的二进制流文件到sql
SAFEARRAY		 *psa;                 //
CFile			 file;                        //文件路径
SAFEARRAYBOUND   rgsabound[1];    //

VARIANT PictureToEJZ(CString strPitctureFilePath)
{
	if (strPitctureFilePath == "" || strPitctureFilePath.IsEmpty())
	{
		varBLOB.iVal = 0;
		return varBLOB;
	}
	
	//定义一个文件变量，把图片转换成二进制存到vardb中，方便加入数据库
	if (!file.Open(strPitctureFilePath, CFile::modeRead | CFile::typeBinary))//以制度的方式打开文件
	{
		varBLOB.iVal = 0;
		return varBLOB;
	}

	m_nFileLen = file.GetLength();//获取文件的长度
	m_pJPGBuffer = new char[m_nFileLen + 1];//开辟符数组
	if (!m_pJPGBuffer)            //如果空间不够大
	{
		varBLOB.iVal = 0;
		return varBLOB;
	}

	if (file.Read(m_pJPGBuffer, m_nFileLen) != m_nFileLen)//读取文件保存在字符数组中
	{
		varBLOB.iVal = 0;
		return varBLOB;
	}
	file.Close();

	///////////////////转换成二进制
	char *pBuf = m_pJPGBuffer;
	if (pBuf)
	{
		rgsabound[0].lLbound = 0;
		rgsabound[0].cElements = m_nFileLen;
		psa = SafeArrayCreate(VT_UI1, 1, rgsabound);
		for (long i = 0; i < (long)m_nFileLen; i++)
		{
			if (FAILED(SafeArrayPutElement(psa, &i, pBuf++)))
			{
				::MessageBox(NULL, _T("转换失败"), _T("提示"), MB_OK | MB_ICONWARNING);
				varBLOB.iVal = 0;
				return varBLOB;
			}

		}
		varBLOB.vt = VT_ARRAY | VT_UI1;
		varBLOB.parray = psa;
		//SafeArrayDestroy(psa);
		g_PictureLen = m_nFileLen;  //把二进制数据大小给word

		return varBLOB;
	}

	varBLOB.iVal = 0;
	return varBLOB;
}


BOOL EJZToPicture(CString strFilePath, int nPicLen, _variant_t _varPicDate)
{
	if (_varPicDate.vt == (VT_ARRAY | VT_UI1))
	{
		char *m_pJPGBuffer = NULL;
		char *pBuf         = NULL;
		pBuf = new char[nPicLen];
		if (pBuf)
		{
			char *buff = NULL;
			SafeArrayAccessData(_varPicDate.parray, (void**)&buff);//把位图数据放到buff中去
			memcpy(pBuf, buff, nPicLen);//把位图数据放到pBuff中

			SafeArrayUnaccessData(_varPicDate.parray);//释放

			m_pJPGBuffer = new char[nPicLen];//开辟符数组
			memcpy(m_pJPGBuffer, pBuf, nPicLen);

			FILE *pFilePath = fopen(strFilePath, "w+b"); 
			if (NULL != pFilePath)
			{
				fwrite(m_pJPGBuffer, 1, nPicLen, pFilePath);	//写入文件
				fclose(pFilePath);

				delete m_pJPGBuffer;
				delete pBuf;

				return TRUE;
			}
			else
			{
				MessageBox(NULL, _T("文件打开失败，重新选择保存图片路径！"), NULL, MB_ICONERROR);

				return FALSE;
			}
		}

		return FALSE;
	}

	return FALSE;
}