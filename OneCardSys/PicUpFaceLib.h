#pragma once
#include "stdafx.h"
#include <vector>
using namespace std;

/*******************************ɾ��******************************************/
BOOL DropFacePicture(CString m_strIdTmp, LONG lFaceLogin); //ɾ��������Ϣ
BOOL DeletePersonInfo(LONG lFaceLogin, unsigned int nPersonID); //�������
/*****************************************************************************/

/********************************�ϴ�***********************************************/
BOOL UpFacePicture(CString g_pic_id, LONG lFaceLogin, CString strFacePicturePath);  //�ϴ������������
STU_FACE_GROUP_INFO* GetCurFaceGroupInfo(int nIndex);  //������
BOOL AddPersonInfo(LONG lFaceLogin, unsigned int nGroupID, STU_PERSON_INFO* pstPersonInfo, std::vector<CString> &vecImages); //�ϴ�����ͼƬ���ĺ��� 
/*************************************************************************************/

BOOL CheckLoginOk(); //����ʶ������Ƿ��½