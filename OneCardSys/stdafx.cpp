
// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// OneCardSys.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"


int g_UserId = 0;
CTime tm = CTime::GetCurrentTime();
CString g_Time = tm.Format("%Y-%m-%d %H:%M:%S");

CTime tm1 =CTime::GetCurrentTime();
CString g_TimeEnd = tm1.Format("%Y-%m-%d %H:%M:%S");

CString  g_UseName = _T("");

CString  g_QX = _T("");
CString  g_IDNum = _T("");
CString  g_Action = _T("");
CString  g_BeginTime = _T("");
CString  g_EndTime = _T("");
CString  g_Ip = _T("");
CString  g_SysRunRZ = _T("ϵͳ��������");


_ConnectionPtr m_pConnection;
_RecordsetPtr  m_pRecordSet;



/*******************FACE_BEGIN********************************/
CString     m_Str_Ip = _T(""); //ip
INT 	    m_int_port = 0; //�˿�
CString 	m_Str_User = _T(""); //�û���
CString 	m_Str_Pwd = _T(""); //����

LLONG   m_lLoginID = 0;    //ʶ���½���
LLONG   m_ZPLoginID = 0;   //ץ���������½���
int  	m_nError = 0;      //�������
/*******************FACE_END********************************/

CString g_ReconBackId  = _T("");  //ʶ�𷵻ص�id(����)
float   g_ReconBackScore = 0;        //ʶ��Żصķ���
CString g_strPictureId = _T("");  //ץ�Ļ�ץȡ����Ƭid��
CString g_strFacePath = _T("");
CString g_strReconPicturePath = _T("");
int g_ReconPass = 0; //��֤����ͨ�����