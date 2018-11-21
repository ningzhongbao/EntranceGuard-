#pragma once
#include "FaceGroupAdd.h"

#include "stdafx.h"
#include "afxwin.h"
#include <vector>
using namespace std;


// CFaceOper 对话框
#define MAX_PERSON_IMAGE_NUM		5
#define PER_PERSON_PAGE_NUM			15

class CFaceOper : public CDialogEx
{
	DECLARE_DYNAMIC(CFaceOper)

public:
	CFaceOper(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFaceOper();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAUPFACEPICTURE };
#endif

public:
	BOOL AddFaceGroup(CString strAlias, BOOL bEnable, float fSearchThreshold, UINT nTopRank);

public:
	//BOOL InitLoginParams();//初始化登录参数
	//BOOL LogIn();  //登录
	//BOOL LogOut();

	/////////////////人脸库//////////////////////
	BOOL CheckLoginOk();
	BOOL RefreshFaceGroup();//刷新人脸库
	BOOL ReCreateFaceGroupArray();
	void DeleteFaceGroupArray();
	STU_FACE_GROUP_INFO* GetCurFaceGroupInfo(int nIndex);
	BOOL DeleteFaceGroup(unsigned int nGroupID, BOOL bDelBindFace);

	//界面操作
	BOOL UI_RefreshFaceGroup();
	BOOL UI_RefreshCurFaceInfo(STU_FACE_GROUP_INFO* pCurFaceInfo);

	BOOL UI_RefreshCurPerson(STU_PERSON_FACE_INFO* pCurPerson);

	//上传人脸
	void ClearData();
	BOOL CheckNameSuffix(IN const char* lpszName, OUT char* lpszNewName, int nNewNameLen);
	BOOL AddPersonInfo(unsigned int nGroupID, STU_PERSON_INFO* pstPersonInfo, std::vector<CString> &vecImages);


	//show face

	BOOL RefreshTotalPersonCount();
	BOOL UI_RefreshPersonList();
	BOOL FrontPagePerson();
	BOOL PrePagePerson();
	BOOL NextPagePerson();
	BOOL BackPagePerson();
	BOOL GoPagePerson(int page);
	STU_PERSON_FACE_INFO* GetCurPersonFaceInfo(int nIndex);
	BOOL DeletePersonInfo(unsigned int nPersonID);


public:
	//LLONG m_lLoginID;
	//int	m_nError;

	void ReSize();
	POINT old;

	//CString     m_Str_Ip; //ip
	//INT 	    m_int_port; //端口
	//CString 	m_Str_User; //用户名
	//CString 	m_Str_Pwd; //密码
						   // 人脸库信息
	STU_FACE_GROUP_ARRAY_INFO* m_pfaceGroupArray;

	/////////////////////////////////////////////////////////
	// 页码信息
	//CString m_static_string_person_page;
	// 查询到的在库人员总数
	int m_nTotalPersonCount;
	// 总人数页码
	int m_nTotalPersonPage;
	// 当前人数页码, 从 1 开始
	int m_nCurPersonPage;
	// 当前人员索引
	int m_nCurPersonIndex;
	// 在库人员偏移
	int m_nOffsetPerson;

	// 当前人员数
	int m_nCurPersonCount;
	// 当前页码人员信息组
	STU_PERSON_FACE_INFO m_stPersonFaceInfoArr[PER_PERSON_PAGE_NUM];	

	////////////////////////////////////////////////////////////////
	CString				m_csFileName;      //路径文件名
	vector<CString>		m_FileList;        //文件名
	CString				csDirParth;        //
	void GetFileFromDir(CString csDirPath);

	void Ui_Show(CString g_strPictureShow);
	inline int CurFaceGroupIndex()
	{ 
		return m_list_face_group.GetCurSel();
	};
	inline int CurPersonIndex() { return m_list_person.GetCurSel(); };


	STU_PERSON_INFO m_stPersonInfo;//人的基本信息
	CString m_person_birth;
	CString m_person_sex;
	CString m_person_certificate_type;
	CString m_person_certificate_id;
	CString m_person_county;
	CString m_person_province;
	CString m_person_city;

	/////////////////////////////////////////////////////////////
	void FaceUp();
	static DWORD WINAPI UpProc(LPVOID lpPar);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnAddFaceGroup();
	afx_msg void OnBnClickedBtnRefreshFaceGroup();
	CListBox m_list_face_group;
	afx_msg void OnBnClickedBtnDeleteFaceGroup();
	CStatic m_Picture;
	afx_msg void OnBnClickedBtnPersonAdd();
	afx_msg void OnBnClickedBtnUp();
	CString m_Name_ID;
	afx_msg void OnBnClickedBtnCannel();
	afx_msg void OnLbnSelchangeList3();
	afx_msg void OnBnClickedBtnPersonRefresh();

	//afx_msg void OnPaint();
	
	CListBox m_list_person;
	CString m_static_string_person_page;
	afx_msg void OnBnClickedBtnPersonPagePre();
	afx_msg void OnBnClickedBtnPersonPageNext();
	afx_msg void OnBnClickedBtnPersonPageFront();
	afx_msg void OnBnClickedBtnPersonPageBack();
	afx_msg void OnBnClickedBtnPersonPageGo();
	CString m_edit_person_page;
	afx_msg void OnBnClickedBtnPersonDelete();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CString m_ShowTip_String;
	afx_msg void OnBnClickedBtnPerAlone();
	afx_msg void OnPaint();
	CListBox m_Test;
	afx_msg void OnEnChangeLabelPageInfo();
};
