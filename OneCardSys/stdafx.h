
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����

#include "GdiPlus.h"  //GDI+
using namespace Gdiplus;
#pragma comment(lib,"gdiplus.lib")

#pragma comment(lib,"netmanager.lib")

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��


#include <afxsock.h>            // MFC �׽�����չ
#include <afxdlgs.h>

#import "C://Program Files//Common Files//System//ado//msado15.dll" no_namespace rename("EOF","adoEOF")

#if !defined CATCH_ERROR
#define CATCH_ERROR          \
  {            \
  CString strComError;      \
  strComError.Format(_T("������: %08lx\n������Ϣ: %s\n����Դ: %s\n��������: %s"), \
        e.Error(),                  \
        e.ErrorMessage(),          \
        (LPCSTR) e.Source(),        \
        (LPCSTR) e.Description());  \
   \
  }
#endif

struct MySysTime
{
	int nEvent;
	SYSTEMTIME system_time;
};

/************************************************************************/
/* �����ͷ�ļ�                                                          */
/************************************************************************/
#include "../OneCardSys/NetManager/netmanager.h"
#include "../OneCardSys/StreamAdapter/StreamAdapter.h"
#include "../OneCardSys/NetManager/netstructcolletion.h"


/************************************************************************/
/* �ٶ��㷨sdk                                                          */
/************************************************************************/
#include "../OneCardSys/BaiduSDK/baidu_face_api.h"



/************************************************************************/
/* ȫ��ͷ�ļ�                                                           */
/************************************************************************/
extern int g_UserId;  //�û���
extern CTime tm1;     //�뿪ʱ��
extern CTime tm;      //����ʱ��
extern CString g_Time;
extern CString g_TimeEnd;
extern CString  g_UseName;  //�û�����
extern CString  g_QX;     //�û�Ȩ��
extern CString  g_IDNum;  //�û����֤����
extern CString  g_Action;  //�û���Ϊ
extern CString  g_BeginTime; //�ÿͽ���ʱ��
extern CString  g_EndTime;   //�ÿ��뿪ʱ��
extern CString  g_Ip;      //ip
extern CString  g_SysRunRZ; //ϵͳ������־

extern _ConnectionPtr m_pConnection;  //�������ݿ����ָ��
extern _RecordsetPtr  m_pRecordSet;   //���ݼ�����ָ��

/************************************************************************/
/* ��֤����                                                             */
/************************************************************************/
extern CString g_ReconBackId;  //ʶ����Ƭid
extern float g_ReconBackScore; //���ƶ�
extern CString g_strPictureId; //ԭʼ��Ƭid
extern CString g_strFacePath;  //ԭʼ��Ƭ·��
extern CString g_strReconPicturePath;  //ʶ����Ƭ·��
extern int g_ReconPass;




/************************************************************************/
/* ���������                                                           */
/************************************************************************/
extern CString     m_Str_Ip; //ip
extern INT 	    m_int_port; //�˿�
extern CString 	m_Str_User; //�û���
extern CString 	m_Str_Pwd; //����

extern LLONG m_lLoginID;   //ʶ���������½���
extern LLONG   m_ZPLoginID;   //ץ���������½���
extern int	m_nError;  //�������


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


