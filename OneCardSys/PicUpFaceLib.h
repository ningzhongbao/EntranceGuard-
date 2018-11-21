#pragma once
#include "stdafx.h"
#include <vector>
using namespace std;

/*******************************删除******************************************/
BOOL DropFacePicture(CString m_strIdTmp, LONG lFaceLogin); //删除人脸信息
BOOL DeletePersonInfo(LONG lFaceLogin, unsigned int nPersonID); //具体操作
/*****************************************************************************/

/********************************上传***********************************************/
BOOL UpFacePicture(CString g_pic_id, LONG lFaceLogin, CString strFacePicturePath);  //上传人脸到摄像机
STU_FACE_GROUP_INFO* GetCurFaceGroupInfo(int nIndex);  //人脸库
BOOL AddPersonInfo(LONG lFaceLogin, unsigned int nGroupID, STU_PERSON_INFO* pstPersonInfo, std::vector<CString> &vecImages); //上传人脸图片核心函数 
/*************************************************************************************/

BOOL CheckLoginOk(); //检验识别相机是否登陆