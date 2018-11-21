#pragma once
#include "afxwin.h"


// CPicture1 对话框
	
#include <vector>
#include "afxcmn.h"
using namespace std;
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

class CPicture1 : public CDialogEx
{
	DECLARE_DYNAMIC(CPicture1)

public:
	CPicture1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPicture1();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PERSON_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnPaint();

	DECLARE_MESSAGE_MAP()

public:
	CString				m_image_path;			//图像路径 
	DWORD				m_nFileLen;			//文件长度
	long                lSizeOfFile;
	char				*pBufImgDate;      //存储二进制图片数据
	CString				m_csFileName;      //路径文件名
	vector<CString>		m_FileList;        //文件名
	CString				csDirParth;        //
	CString				m_AllPath;				//listbox选择的路径；	



public:
	void ClearData();
	char *LoadImaData(CString imagPath);     //获取图片数据 
	void GetFileFromDir(CString csDirPath);  //获取图片路径
	void JxFileName(CString jpgName);
	void Ui_Show_Info(CString filename);

public:	
	CStatic m_Image;
	CString m_Image_String;
	CString m_Name;
	CString m_IDCard;
	CString m_DyId;
	CString m_LcId;
	CString m_LcIdd;
	CString m_ShId;
	CListBox m_ListBox;

	afx_msg void OnBnClickedAddPerface();
	afx_msg void OnBnClickedDelePerface();
	afx_msg void OnBnClickedCannel();
	afx_msg void OnBnClickedIdok();
	afx_msg void OnBnClickedOpenFacepath();	
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnBnClickedDeleList();
	afx_msg void OnEnChangeEle();
};
