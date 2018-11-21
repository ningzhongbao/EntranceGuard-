#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>
#include "afxdtctl.h"
#include "ATLComTime.h"
using namespace std;
#include "../OneCardSys/PicUpFaceLib.h"
#include "PictureToBinSys.h"  //加入照片解析头文件


// CVistorsRecord 对话框

class CVistorsRecord : public CDialogEx
{
	DECLARE_DYNAMIC(CVistorsRecord)

public:
	CVistorsRecord(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVistorsRecord();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLGVISTRECORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:  //人脸操作
	BOOL CheckLoginOk();

public:	//函数
	void Ui_Show();

public:	 //变量
	CComboBox m_vrCobxSex;  //性别
	CListCtrl m_listRcfInfo;
	CString m_SelectName;
	CString m_SelectId;
	CString m_Name_String;
	CString m_Sex_String;
	CString m_ID_String;
	CString m_RG_Stri;
	CString m_End_String;
	CString m_BFZ_String;
	CString m_FK_String;
	CString m_BFZ_LH_String;
	CString m_BFZ_FH_String;
	CString m_BFZ_Addr_String;//住址
	CString m_Picture_Path;
	CStatic m_Picture;
	CString m_YL_String;
	void ReSize();
	POINT old;

	CString m_BeginTime_String;
	CString m_EndTime_Str;
	CString m_ShowPath;
	CString m_HMD_String;


	CString    m_strPath;  //自定义照片路径
	_variant_t varPicDate; //照片数据
	DWORD       m_PicLen;   //照片大小
public:  //消息映射
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLvnItemchangedListvrecord(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnselectall();
	afx_msg void OnBnClickedBtnselect();
	afx_msg void OnEnChangeEvrfname();
	afx_msg void OnBnClickedBtnjionbt();
	afx_msg void OnEnChangeEvrfid();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEnChangeEdit11();
	afx_msg void OnStnClickedStaticpt();
	afx_msg void OnBnClickedBtndelete();
	afx_msg void OnPaint();
	afx_msg void OnCbnDropdownCombvrfsex();
	CString m_strLH;
	CString m_strFH;
	afx_msg void OnBnClickedBtnselectallHmd();
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnselecttime();
	CDateTimeCtrl m_datetimebegin;
	CDateTimeCtrl m_datetimeend;
	COleDateTime m_Begin_String;
	COleDateTime m_EndTime_String;
	CString m_PicId_string;
	afx_msg void OnBnClickedBtndelete2();
	CString m_Tel_String;
};
