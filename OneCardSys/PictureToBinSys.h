#pragma once
#include "stdafx.h"

extern DWORD g_PictureLen; //��Ƭ����

/************************************************************************/
/* ��ͼƬת�ɶ�����                                                     */
/************************************************************************/
VARIANT PictureToEJZ(CString strPitctureFilePath);  

/************************************************************************/
/* ������������ת��ͼƬ                                                 */
/************************************************************************/
BOOL EJZToPicture(CString strFilePath, int nPicLen, _variant_t _varPicDate);