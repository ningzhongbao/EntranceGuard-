#pragma once
#include "afxwin.h"
#include "stdafx.h"
#include <vector>
using namespace std;
#include  "../OneCardSys/PicUpFaceLib.h"
#include  "PictureToBinSys.h"
#include "WintCheckVido.h" //��֤����ʵʱ��Ƶ��
#include "WintnessCheck.h"  //��֤����ʵ�ֹ���


#include "SynPublic.h"
#pragma  comment(lib, "SynIDCardAPI.lib")



// CPerReg �Ի���

class CPerReg : public CDialogEx
{
	DECLARE_DYNAMIC(CPerReg)

public:
	CPerReg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPerReg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum {
		IDD = IDD_DIAREGISTER
};
#endif

public://�Զ�����
	void Ui_Show(CString strPicture_Path, int myIDC_Picture);
	BOOL StartRealStream();
	BOOL  ExecuPicture();
	//BOOL PictureToEJZ();        //��ͼƬ����ת���ɶ����ƴ浽���ܱ�����
	void OperRZ(CString g_Action);//��־
		
	BOOL CheckLoginOk();         //�ж��Ƿ��¼����������

	void ClearScreen();          //�����Ļ

	BOOL PerCardCheck();        //��֤����
	static DWORD GetRresult();  


	/************************************************************************/
	/* ˢ���֤                                                       */
	/************************************************************************/
	void IDCardInit();  //ˢ���֤��ʼ��
	int m_iPort;      //���֤�������˿�


public://�Զ�����
	CString m_csFileName;  //�ļ���
	CString ID;            //��Ƭ��ip��
	void ReSize();         //���������С������
	POINT old;             //������󻯱���

	VARIANT      varBLOB;  //�洢ͼƬ�Ķ��������ļ���sql
	DWORD        m_nFileLen;


	CString m_IdCard_String; //���֤
	CString m_RegTip;        //��ʾ
	CString m_ID_String;     //����id���ӳ��
	CString m_Name_String;   //��������ӳ��
	CString m_Tel_String;    //�绰
	CString m_LD_String;     //¥��
	CString m_FH_String;     //�����
	CString m_Path_String;   //����ͼƬ·��
	CStatic m_Picture;       //��Ƭ����ӳ��
	CString m_COM_XB_String; //�Ա�
	LLONG    m_playHandle;   //ץͼ���
	UINT     UiTimer;         //��ʱ��
	
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnReg();
	afx_msg void OnBnClickedBtnCannel();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnStreg();
	afx_msg void OnBnClickedBtntwocard();
	CEdit m_StatVal;
	CComboBox m_ComBoxSex;
	CEdit m_EditIDNo;
	CEdit m_Edit_ID_Values;
	CEdit m_vEdit7;
	CEdit m_EditName;
};
