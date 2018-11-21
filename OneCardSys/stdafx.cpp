
// stdafx.cpp : 只包括标准包含文件的源文件
// OneCardSys.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

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
CString  g_SysRunRZ = _T("系统运行正常");


_ConnectionPtr m_pConnection;
_RecordsetPtr  m_pRecordSet;



/*******************FACE_BEGIN********************************/
CString     m_Str_Ip = _T(""); //ip
INT 	    m_int_port = 0; //端口
CString 	m_Str_User = _T(""); //用户名
CString 	m_Str_Pwd = _T(""); //密码

LLONG   m_lLoginID = 0;    //识别登陆句柄
LLONG   m_ZPLoginID = 0;   //抓拍摄像机登陆句柄
int  	m_nError = 0;      //错误代码
/*******************FACE_END********************************/

CString g_ReconBackId  = _T("");  //识别返回的id(姓名)
float   g_ReconBackScore = 0;        //识别放回的分数
CString g_strPictureId = _T("");  //抓拍机抓取的照片id号
CString g_strFacePath = _T("");
CString g_strReconPicturePath = _T("");
int g_ReconPass = 0; //人证核验通过与否