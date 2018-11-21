#pragma once
#include "FaceGroupAdd.h"

#include "stdafx.h"
#include "afxwin.h"
#include <vector>
using namespace std;


// CFaceOper �Ի���
#define MAX_PERSON_IMAGE_NUM		5
#define PER_PERSON_PAGE_NUM			15

class CFaceOper : public CDialogEx
{
	DECLARE_DYNAMIC(CFaceOper)

public:
	CFaceOper(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CFaceOper();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAUPFACEPICTURE };
#endif

public:
	BOOL AddFaceGroup(CString strAlias, BOOL bEnable, float fSearchThreshold, UINT nTopRank);

public:
	//BOOL InitLoginParams();//��ʼ����¼����
	//BOOL LogIn();  //��¼
	//BOOL LogOut();

	/////////////////������//////////////////////
	BOOL CheckLoginOk();
	BOOL RefreshFaceGroup();//ˢ��������
	BOOL ReCreateFaceGroupArray();
	void DeleteFaceGroupArray();
	STU_FACE_GROUP_INFO* GetCurFaceGroupInfo(int nIndex);
	BOOL DeleteFaceGroup(unsigned int nGroupID, BOOL bDelBindFace);

	//�������
	BOOL UI_RefreshFaceGroup();
	BOOL UI_RefreshCurFaceInfo(STU_FACE_GROUP_INFO* pCurFaceInfo);

	BOOL UI_RefreshCurPerson(STU_PERSON_FACE_INFO* pCurPerson);

	//�ϴ�����
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
	//INT 	    m_int_port; //�˿�
	//CString 	m_Str_User; //�û���
	//CString 	m_Str_Pwd; //����
						   // ��������Ϣ
	STU_FACE_GROUP_ARRAY_INFO* m_pfaceGroupArray;

	/////////////////////////////////////////////////////////
	// ҳ����Ϣ
	//CString m_static_string_person_page;
	// ��ѯ�����ڿ���Ա����
	int m_nTotalPersonCount;
	// ������ҳ��
	int m_nTotalPersonPage;
	// ��ǰ����ҳ��, �� 1 ��ʼ
	int m_nCurPersonPage;
	// ��ǰ��Ա����
	int m_nCurPersonIndex;
	// �ڿ���Աƫ��
	int m_nOffsetPerson;

	// ��ǰ��Ա��
	int m_nCurPersonCount;
	// ��ǰҳ����Ա��Ϣ��
	STU_PERSON_FACE_INFO m_stPersonFaceInfoArr[PER_PERSON_PAGE_NUM];	

	////////////////////////////////////////////////////////////////
	CString				m_csFileName;      //·���ļ���
	vector<CString>		m_FileList;        //�ļ���
	CString				csDirParth;        //
	void GetFileFromDir(CString csDirPath);

	void Ui_Show(CString g_strPictureShow);
	inline int CurFaceGroupIndex()
	{ 
		return m_list_face_group.GetCurSel();
	};
	inline int CurPersonIndex() { return m_list_person.GetCurSel(); };


	STU_PERSON_INFO m_stPersonInfo;//�˵Ļ�����Ϣ
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
