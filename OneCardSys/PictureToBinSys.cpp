#include "stdafx.h"
#include "PictureToBinSys.h"


DWORD g_PictureLen = 0;
DWORD			 m_nFileLen    = 0;           //�ļ��ĳ���
char			 *m_pJPGBuffer = NULL;        //����ͼƬ��
VARIANT			 varBLOB       = { 0 };			   //�洢ͼƬ�Ķ��������ļ���sql
SAFEARRAY		 *psa;                 //
CFile			 file;                        //�ļ�·��
SAFEARRAYBOUND   rgsabound[1];    //

VARIANT PictureToEJZ(CString strPitctureFilePath)
{
	if (strPitctureFilePath == "" || strPitctureFilePath.IsEmpty())
	{
		varBLOB.iVal = 0;
		return varBLOB;
	}
	
	//����һ���ļ���������ͼƬת���ɶ����ƴ浽vardb�У�����������ݿ�
	if (!file.Open(strPitctureFilePath, CFile::modeRead | CFile::typeBinary))//���ƶȵķ�ʽ���ļ�
	{
		varBLOB.iVal = 0;
		return varBLOB;
	}

	m_nFileLen = file.GetLength();//��ȡ�ļ��ĳ���
	m_pJPGBuffer = new char[m_nFileLen + 1];//���ٷ�����
	if (!m_pJPGBuffer)            //����ռ䲻����
	{
		varBLOB.iVal = 0;
		return varBLOB;
	}

	if (file.Read(m_pJPGBuffer, m_nFileLen) != m_nFileLen)//��ȡ�ļ��������ַ�������
	{
		varBLOB.iVal = 0;
		return varBLOB;
	}
	file.Close();

	///////////////////ת���ɶ�����
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
				::MessageBox(NULL, _T("ת��ʧ��"), _T("��ʾ"), MB_OK | MB_ICONWARNING);
				varBLOB.iVal = 0;
				return varBLOB;
			}

		}
		varBLOB.vt = VT_ARRAY | VT_UI1;
		varBLOB.parray = psa;
		//SafeArrayDestroy(psa);
		g_PictureLen = m_nFileLen;  //�Ѷ��������ݴ�С��word

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
			SafeArrayAccessData(_varPicDate.parray, (void**)&buff);//��λͼ���ݷŵ�buff��ȥ
			memcpy(pBuf, buff, nPicLen);//��λͼ���ݷŵ�pBuff��

			SafeArrayUnaccessData(_varPicDate.parray);//�ͷ�

			m_pJPGBuffer = new char[nPicLen];//���ٷ�����
			memcpy(m_pJPGBuffer, pBuf, nPicLen);

			FILE *pFilePath = fopen(strFilePath, "w+b"); 
			if (NULL != pFilePath)
			{
				fwrite(m_pJPGBuffer, 1, nPicLen, pFilePath);	//д���ļ�
				fclose(pFilePath);

				delete m_pJPGBuffer;
				delete pBuf;

				return TRUE;
			}
			else
			{
				MessageBox(NULL, _T("�ļ���ʧ�ܣ�����ѡ�񱣴�ͼƬ·����"), NULL, MB_ICONERROR);

				return FALSE;
			}
		}

		return FALSE;
	}

	return FALSE;
}