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
	void *reserved)   //��֤����ص�����
{
	if (dwEventType == EVENT_SP_FACE_RECOGNIZE_CUTOUT)
	{
		STU_EVENT_FACE_RECOGNIZE_CUTOUT stu = { 0 };
		memcpy(&stu, pEventInfo, sizeof(STU_EVENT_FACE_RECOGNIZE_CUTOUT));
		g_ReconBackId = stu.stFaceRecognizeInfoArr[0].stPersonInfo.szName; //��ȡid
		g_ReconBackScore = stu.stFaceRecognizeInfoArr[0].fSearchScore;  //��ȡʶ��ķ���

		FILE *pFilePath = fopen(g_strFacePath, _T("w+b"));
		if (NULL != pFilePath)
		{
			fwrite(pBuffer, 1, dwBufSize, pFilePath);	//д���ļ�		
			fclose(pFilePath);
		}

	}

	return 0;
}


BOOL WintnesCheck()
{
	if (m_ZPLoginID <= 0)
	{
		::MessageBox(NULL,_T("ץ�Ļ�δ��¼"), _T("����"), MB_ICONERROR);

		return FALSE;
	}

	int nChannel = 0;
	netPicHandle = Net_RealLoadPicture(m_ZPLoginID, nChannel, EVENT_SP_FACE_RECOGNIZE_CUTOUT, 1,
		realload_callbackWintnessCheck, NULL, NULL);
	if (0 >= netPicHandle)
	{
		::MessageBox(NULL,_T("��֤���鲻ͨ��"), _T("����"), MB_ICONERROR);
		Net_LogoutDevice(m_ZPLoginID);

		return FALSE;
	}

	return TRUE;
}

BOOL WintCheckStop()  //
{
	if (0 <= netPicHandle)
	{
		Net_StopLoadPicture(netPicHandle); //ֹͣ������������

		return TRUE;
	}
	
	return FALSE;
}