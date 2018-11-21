#include "stdafx.h"
#include "WintnessCheck.h"

LONG netPicHandle = 0;

int CALLBACK realload_callbackWintnessCheck(LLONG lAnalyzerHandle,
	DWORD dwEventType,
	void* pEventInfo,
	BYTE *pBuffer,
	DWORD dwBufSize,
	LDWORD dwUser,
	int nSequence,
	void *reserved)   //人证核验回调函数
{
	if (dwEventType == EVENT_SP_FACE_RECOGNIZE_CUTOUT)
	{
		STU_EVENT_FACE_RECOGNIZE_CUTOUT stu = { 0 };
		memcpy(&stu, pEventInfo, sizeof(STU_EVENT_FACE_RECOGNIZE_CUTOUT));
		g_ReconBackId = stu.stFaceRecognizeInfoArr[0].stPersonInfo.szName; //获取id
		g_ReconBackScore = stu.stFaceRecognizeInfoArr[0].fSearchScore;  //获取识别的分数

		FILE *pFilePath = fopen(g_strFacePath, _T("w+b"));
		if (NULL != pFilePath)
		{
			fwrite(pBuffer, 1, dwBufSize, pFilePath);	//写入文件		
			fclose(pFilePath);
		}

	}

	return 0;
}


BOOL WintnesCheck()
{
	if (m_ZPLoginID <= 0)
	{
		::MessageBox(NULL,_T("抓拍机未登录"), _T("警告"), MB_ICONERROR);

		return FALSE;
	}

	int nChannel = 0;
	netPicHandle = Net_RealLoadPicture(m_ZPLoginID, nChannel, EVENT_SP_FACE_RECOGNIZE_CUTOUT, 1,
		realload_callbackWintnessCheck, NULL, NULL);
	if (0 >= netPicHandle)
	{
		::MessageBox(NULL,_T("认证核验不通过"), _T("警告"), MB_ICONERROR);
		Net_LogoutDevice(m_ZPLoginID);

		return FALSE;
	}

	return TRUE;
}

BOOL WintCheckStop()  //
{
	if (0 <= netPicHandle)
	{
		Net_StopLoadPicture(netPicHandle); //停止网络数据拉流

		return TRUE;
	}
	
	return FALSE;
}