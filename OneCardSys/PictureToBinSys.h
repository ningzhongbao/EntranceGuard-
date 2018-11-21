#pragma once
#include "stdafx.h"

extern DWORD g_PictureLen; //照片长度

/************************************************************************/
/* 将图片转成二进制                                                     */
/************************************************************************/
VARIANT PictureToEJZ(CString strPitctureFilePath);  

/************************************************************************/
/* 将二进制数据转成图片                                                 */
/************************************************************************/
BOOL EJZToPicture(CString strFilePath, int nPicLen, _variant_t _varPicDate);