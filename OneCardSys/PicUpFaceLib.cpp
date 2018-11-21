#include "stdafx.h"
#include "../OneCardSys/PicUpFaceLib.h"


STU_PERSON_INFO m_stPersonInfo;    //人的基本信息
CString m_person_county = _T("中国");
CString m_person_sex = _T("male");
CString m_person_certificate_type = _T("身份证");
//CString m_person_county = _T("中国");
CString m_person_birth = _T("2037-12-31");
CString m_person_city = _T("武汉市");
CString m_person_certificate_id = _T("00000000000000");
CString m_person_province = _T("湖北省");
int     m_nCurPersonCount = 0;

STU_FACE_GROUP_ARRAY_INFO* m_pfaceGroupArray;
BOOL DropFacePicture(CString m_strIdTmp, LONG lFaceLogin)  //删除摄像机人脸
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
		//AfxMessageBox(_T("没有找到该身份证对应的人脸"));

		return FALSE;
	}

	if (TRUE != DeletePersonInfo(lFaceLogin, (&pOutParam)->stPersonInfo.nPersonID))
	{		
		return FALSE;
	}

	return TRUE;
}


BOOL DeletePersonInfo(LONG lFaceLogin, unsigned int nPersonID)  //删除摄像机人脸
{
	if (TRUE != Net_DeletePersonInfo(lFaceLogin, nPersonID))
	{
		AfxMessageBox(_T("操作失败，请再试一次"));

		return FALSE;
	}

	return TRUE;
}



BOOL UpFacePicture(CString g_pic_id, LONG lFaceLogin, CString strFacePicturePath)  //上传人脸到摄像机
{
	m_pfaceGroupArray = new STU_FACE_GROUP_ARRAY_INFO;
	if (NULL == m_pfaceGroupArray)
	{
		return FALSE;
	}
	memset(m_pfaceGroupArray, 0x00, sizeof(STU_FACE_GROUP_ARRAY_INFO));

	if (TRUE != Net_GetAllFaceGroups(lFaceLogin, m_pfaceGroupArray))
	{
		AfxMessageBox(_T("获取人脸库错误"), NULL, MB_OK);
		return FALSE;
	}

	STU_FACE_GROUP_INFO* pCurFaceGroup = GetCurFaceGroupInfo(0);
	if (NULL == pCurFaceGroup)
	{
		AfxMessageBox(_T("请选择人脸组！"));
		return FALSE;
	}

	//初始化
	memset(&m_stPersonInfo, 0x00, sizeof(STU_PERSON_INFO));
	memset(m_stPersonInfo.szName, NULL, 128);
	char szNewName[128] = { 0 };

	memcpy(m_stPersonInfo.szName, g_pic_id.GetBuffer(0), g_pic_id.GetLength()); //名字

	CString strPath;
	strPath = strFacePicturePath;

	sscanf(m_person_birth.GetBuffer(0), "%04d-%02d-%02d",
		&m_stPersonInfo.stBirthday.dwYear, &m_stPersonInfo.stBirthday.dwMonth, &m_stPersonInfo.stBirthday.dwDay);
	m_person_birth.ReleaseBuffer();


	m_stPersonInfo.emSexType = SEX_TYPE_FEMALE;  //性别
	memcpy(m_stPersonInfo.szCertificateType, m_person_certificate_type.GetBuffer(0), m_person_certificate_type.GetLength());
	m_person_certificate_type.ReleaseBuffer();

	memcpy(m_stPersonInfo.szID, g_pic_id.GetBuffer(0), g_pic_id.GetLength()); //上传摄像机id（身份证)
	g_pic_id.ReleaseBuffer();


	memcpy(m_stPersonInfo.szCountry, m_person_county.GetBuffer(0), m_person_county.GetLength());
	m_person_county.ReleaseBuffer();


	memcpy(m_stPersonInfo.szProvince, m_person_province.GetBuffer(0), m_person_province.GetLength());
	m_person_province.ReleaseBuffer();

	memcpy(m_stPersonInfo.szCity, m_person_city.GetBuffer(0), m_person_city.GetLength());
	m_person_city.ReleaseBuffer();

	// 赋值名字
	memcpy(m_stPersonInfo.szName, szNewName, strlen(szNewName));

	std::vector<CString> vecImages;
	if (!strPath.IsEmpty())
		vecImages.push_back(strPath);

	//MessageBox(strPath, NULL, 0);

	if (TRUE != AddPersonInfo(lFaceLogin, pCurFaceGroup->nGroupID, &m_stPersonInfo, vecImages))
	{
		AfxMessageBox(_T("添加人脸开门照片失败，原因可能是此人脸已在摄像机中，照片不清晰，请重新采集照片,签离或者联系管理员"));		

		return FALSE;
	}
	return TRUE;
}

STU_FACE_GROUP_INFO* GetCurFaceGroupInfo(int nIndex)  //人脸库
{
	if (0 > nIndex || MAX_FACE_GROUP_NUM <= nIndex)
		return NULL;
	if (NULL == m_pfaceGroupArray || 0 == m_pfaceGroupArray->nFaceGroupNum)
		return NULL;
	return &m_pfaceGroupArray->stFaceGroupArr[nIndex];
}



//上传人脸图片核心函数
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
		strImageFiles.AppendChar('|');  // 图片路径以 “|” 分隔
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
	::MessageBox(NULL, _T("还未登录！"), _T("提示"), MB_OK|MB_ICONERROR);
	return FALSE;
}