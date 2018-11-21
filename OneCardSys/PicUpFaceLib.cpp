#include "stdafx.h"
#include "../OneCardSys/PicUpFaceLib.h"


STU_PERSON_INFO m_stPersonInfo;    //�˵Ļ�����Ϣ
CString m_person_county = _T("�й�");
CString m_person_sex = _T("male");
CString m_person_certificate_type = _T("���֤");
//CString m_person_county = _T("�й�");
CString m_person_birth = _T("2037-12-31");
CString m_person_city = _T("�人��");
CString m_person_certificate_id = _T("00000000000000");
CString m_person_province = _T("����ʡ");
int     m_nCurPersonCount = 0;

STU_FACE_GROUP_ARRAY_INFO* m_pfaceGroupArray;
BOOL DropFacePicture(CString m_strIdTmp, LONG lFaceLogin)  //ɾ�����������
{
	if (!Net_PreFindFaceInfo(lFaceLogin))
	{
		//AfxMessageBox("Net_PreFindFaceInfo");
		return FALSE;
	}

	STU_PERSON_INFO_GET_BYID_IN_PARAM pInParam = { 0 };

	memcpy(pInParam.szCertificateType, m_person_certificate_type.GetBuffer(0), m_person_certificate_type.GetLength());
	m_person_certificate_type.ReleaseBuffer();

	memcpy(pInParam.szID, m_strIdTmp.GetBuffer(0), m_strIdTmp.GetLength());
	m_strIdTmp.ReleaseBuffer();
	STU_PERSON_INFO_GET_BYID_OUT_PARAM pOutParam = { 0 };

	if (!Net_GetPersonInfoByID(lFaceLogin, &pInParam, &pOutParam))
	{
		//AfxMessageBox(_T("û���ҵ������֤��Ӧ������"));

		return FALSE;
	}

	if (TRUE != DeletePersonInfo(lFaceLogin, (&pOutParam)->stPersonInfo.nPersonID))
	{		
		return FALSE;
	}

	return TRUE;
}


BOOL DeletePersonInfo(LONG lFaceLogin, unsigned int nPersonID)  //ɾ�����������
{
	if (TRUE != Net_DeletePersonInfo(lFaceLogin, nPersonID))
	{
		AfxMessageBox(_T("����ʧ�ܣ�������һ��"));

		return FALSE;
	}

	return TRUE;
}



BOOL UpFacePicture(CString g_pic_id, LONG lFaceLogin, CString strFacePicturePath)  //�ϴ������������
{
	m_pfaceGroupArray = new STU_FACE_GROUP_ARRAY_INFO;
	if (NULL == m_pfaceGroupArray)
	{
		return FALSE;
	}
	memset(m_pfaceGroupArray, 0x00, sizeof(STU_FACE_GROUP_ARRAY_INFO));

	if (TRUE != Net_GetAllFaceGroups(lFaceLogin, m_pfaceGroupArray))
	{
		AfxMessageBox(_T("��ȡ���������"), NULL, MB_OK);
		return FALSE;
	}

	STU_FACE_GROUP_INFO* pCurFaceGroup = GetCurFaceGroupInfo(0);
	if (NULL == pCurFaceGroup)
	{
		AfxMessageBox(_T("��ѡ�������飡"));
		return FALSE;
	}

	//��ʼ��
	memset(&m_stPersonInfo, 0x00, sizeof(STU_PERSON_INFO));
	memset(m_stPersonInfo.szName, NULL, 128);
	char szNewName[128] = { 0 };

	memcpy(m_stPersonInfo.szName, g_pic_id.GetBuffer(0), g_pic_id.GetLength()); //����

	CString strPath;
	strPath = strFacePicturePath;

	sscanf(m_person_birth.GetBuffer(0), "%04d-%02d-%02d",
		&m_stPersonInfo.stBirthday.dwYear, &m_stPersonInfo.stBirthday.dwMonth, &m_stPersonInfo.stBirthday.dwDay);
	m_person_birth.ReleaseBuffer();


	m_stPersonInfo.emSexType = SEX_TYPE_FEMALE;  //�Ա�
	memcpy(m_stPersonInfo.szCertificateType, m_person_certificate_type.GetBuffer(0), m_person_certificate_type.GetLength());
	m_person_certificate_type.ReleaseBuffer();

	memcpy(m_stPersonInfo.szID, g_pic_id.GetBuffer(0), g_pic_id.GetLength()); //�ϴ������id�����֤)
	g_pic_id.ReleaseBuffer();


	memcpy(m_stPersonInfo.szCountry, m_person_county.GetBuffer(0), m_person_county.GetLength());
	m_person_county.ReleaseBuffer();


	memcpy(m_stPersonInfo.szProvince, m_person_province.GetBuffer(0), m_person_province.GetLength());
	m_person_province.ReleaseBuffer();

	memcpy(m_stPersonInfo.szCity, m_person_city.GetBuffer(0), m_person_city.GetLength());
	m_person_city.ReleaseBuffer();

	// ��ֵ����
	memcpy(m_stPersonInfo.szName, szNewName, strlen(szNewName));

	std::vector<CString> vecImages;
	if (!strPath.IsEmpty())
		vecImages.push_back(strPath);

	//MessageBox(strPath, NULL, 0);

	if (TRUE != AddPersonInfo(lFaceLogin, pCurFaceGroup->nGroupID, &m_stPersonInfo, vecImages))
	{
		AfxMessageBox(_T("�������������Ƭʧ�ܣ�ԭ������Ǵ���������������У���Ƭ�������������²ɼ���Ƭ,ǩ�������ϵ����Ա"));		

		return FALSE;
	}
	return TRUE;
}

STU_FACE_GROUP_INFO* GetCurFaceGroupInfo(int nIndex)  //������
{
	if (0 > nIndex || MAX_FACE_GROUP_NUM <= nIndex)
		return NULL;
	if (NULL == m_pfaceGroupArray || 0 == m_pfaceGroupArray->nFaceGroupNum)
		return NULL;
	return &m_pfaceGroupArray->stFaceGroupArr[nIndex];
}



//�ϴ�����ͼƬ���ĺ���
BOOL AddPersonInfo(LONG lFaceLogin, unsigned int nGroupID, STU_PERSON_INFO* pstPersonInfo, std::vector<CString> &vecImages)
{
	if (NULL == pstPersonInfo)
		return FALSE;

	STU_FACE_ADD_IN_PARAM stInParam = { 0 };
	STU_FACE_ADD_OUT_PARAM stOutParam = { 0 };

	stInParam.nGroupID = nGroupID;

	stInParam.nImageCount = vecImages.size();
	memcpy(&stInParam.stPersonInfo, pstPersonInfo, sizeof(STU_PERSON_INFO));

	CString strImageFiles = "";
	std::vector<CString>::iterator iter = vecImages.begin();
	while (iter != vecImages.end())
	{
		strImageFiles.Append(*iter);
		strImageFiles.AppendChar('|');  // ͼƬ·���� ��|�� �ָ�
		iter++;
	}
	strImageFiles = strImageFiles.TrimRight('|');

	stInParam.lpszImageFiles = new char[strImageFiles.GetLength() + 1];
	memset(stInParam.lpszImageFiles, 0x00, strImageFiles.GetLength() + 1);
	memcpy(stInParam.lpszImageFiles, strImageFiles.GetBuffer(0), strImageFiles.GetLength());


	if (TRUE != Net_AddPersonInfo(lFaceLogin, &stInParam, &stOutParam))
	{
		delete[] stInParam.lpszImageFiles;
		return FALSE;
	}

	delete[] stInParam.lpszImageFiles;
	return TRUE;
}


BOOL CheckLoginOk()
{
	if (0 < m_lLoginID)
		return TRUE;
	::MessageBox(NULL, _T("��δ��¼��"), _T("��ʾ"), MB_OK|MB_ICONERROR);
	return FALSE;
}