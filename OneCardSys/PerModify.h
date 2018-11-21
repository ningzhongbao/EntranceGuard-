#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "stdafx.h"
#include "../OneCardSys/PicUpFaceLib.h"
#include "PictureToBinSys.h"   //��Ƭת���ļ�ͷ



// CPerModify �Ի���

class CPerModify : public CDialogEx
{
	DECLARE_DYNAMIC(CPerModify)

public:
	CPerModify(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPerModify();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIAMODIFY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	void InitData();
	void Ui_Show(CString strPicture_Path); //add 2018-9-14
	void OperRZ(CString g_Action);
	BOOL DeletePersonInfo(LONG lFaceLoginId, unsigned int nPersonID);  //ɾ���������е���Ƭ
	BOOL DropApointFace(LONG lFaceLoginId);

public:
	CString m_ID_String;
	CString m_Name_String;
	CStatic m_Picture;
	CString m_ShowTip;
	CString m_IDs;
	CString m_Names;
	CString m_XB;
	CString m_Tel;
	CString m_RegDateTime;
	CListCtrl m_ListShowInfo;
	CString m_Type_string;
	CString m_FH_String;
	CString m_LD;
	CString m_strPath;  //�Զ�����Ƭ·��
	CString m_ShowPath;
	void ReSize();
	POINT old;

	CString m_person_certificate_type; //�������

	_variant_t varPicDate; //��Ƭ����
	int       m_PicLen;   //��Ƭ��С
public:
	afx_msg void OnBnClickedBtnselect();
	afx_msg void OnBnClickedBtnModify();
	afx_msg void OnBnClickedBtnDele();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnseleall();
	afx_msg void OnLvnItemchangedListshowinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedBtnzhperlogout();
	CString m_UseLogOut_String;
};
