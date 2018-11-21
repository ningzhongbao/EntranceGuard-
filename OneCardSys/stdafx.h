
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类

#include "GdiPlus.h"  //GDI+
using namespace Gdiplus;
#pragma comment(lib,"gdiplus.lib")

#pragma comment(lib,"netmanager.lib")

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持


#include <afxsock.h>            // MFC 套接字扩展
#include <afxdlgs.h>

#import "C://Program Files//Common Files//System//ado//msado15.dll" no_namespace rename("EOF","adoEOF")

#if !defined CATCH_ERROR
#define CATCH_ERROR          \
  {            \
  CString strComError;      \
  strComError.Format(_T("错误编号: %08lx\n错误信息: %s\n错误源: %s\n错误描述: %s"), \
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
/* 摄像机头文件                                                          */
/************************************************************************/
#include "../OneCardSys/NetManager/netmanager.h"
#include "../OneCardSys/StreamAdapter/StreamAdapter.h"
#include "../OneCardSys/NetManager/netstructcolletion.h"


/************************************************************************/
/* 百度算法sdk                                                          */
/************************************************************************/
#include "../OneCardSys/BaiduSDK/baidu_face_api.h"



/************************************************************************/
/* 全局头文件                                                           */
/************************************************************************/
extern int g_UserId;  //用户名
extern CTime tm1;     //离开时间
extern CTime tm;      //进入时间
extern CString g_Time;
extern CString g_TimeEnd;
extern CString  g_UseName;  //用户姓名
extern CString  g_QX;     //用户权限
extern CString  g_IDNum;  //用户身份证号码
extern CString  g_Action;  //用户行为
extern CString  g_BeginTime; //访客进入时间
extern CString  g_EndTime;   //访客离开时间
extern CString  g_Ip;      //ip
extern CString  g_SysRunRZ; //系统运行日志

extern _ConnectionPtr m_pConnection;  //连接数据库对象指针
extern _RecordsetPtr  m_pRecordSet;   //数据集对象指针

/************************************************************************/
/* 人证核验                                                             */
/************************************************************************/
extern CString g_ReconBackId;  //识别照片id
extern float g_ReconBackScore; //相似度
extern CString g_strPictureId; //原始照片id
extern CString g_strFacePath;  //原始照片路径
extern CString g_strReconPicturePath;  //识别照片路径
extern int g_ReconPass;




/************************************************************************/
/* 人脸库操作                                                           */
/************************************************************************/
extern CString     m_Str_Ip; //ip
extern INT 	    m_int_port; //端口
extern CString 	m_Str_User; //用户名
extern CString 	m_Str_Pwd; //密码

extern LLONG m_lLoginID;   //识别摄像机登陆句柄
extern LLONG   m_ZPLoginID;   //抓拍摄像机登陆句柄
extern int	m_nError;  //错误代码


#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


