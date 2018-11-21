#ifndef _AL_PLAY_V1_H
#define _AL_PLAY_V1_H

#if (defined(WIN32) || defined(WIN64))
#ifdef PLAYMS_API_EXPORTS
#define PLAYMS_API __declspec(dllexport)
#else
#define PLAYMS_API __declspec(dllimport)
#endif
#define CALLBACK   __stdcall
#define CALLMETHOD __stdcall
#else
#define CALLMETHOD
#define CALLBACK
#define PLAYMS_API
#endif

#if defined(WIN32) || defined(WIN64)
	#include <windows.h>
#else
	#ifdef __OBJC__
		#include "objc/objc.h"
	#endif

#ifndef BYTE
	#define BYTE		unsigned char
#endif

#ifndef PBYTE
	#define PBYTE		BYTE*
#endif

#ifndef LPBYTE
	#define LPBYTE		BYTE*
#endif

#ifndef LONG
	#define LONG		long
#endif

#ifndef DWORD
	#define DWORD		unsigned long
#endif

#ifndef NULL
#define NULL 0
#endif

#ifndef WORD
#define WORD		unsigned short
#endif

#ifndef COLORREF
#define COLORREF	DWORD
#endif

#ifndef HDC
#define HDC			void*
#endif

#ifndef HWND
#define HWND		void*
#endif

#ifndef LPSTR
#define LPSTR		char*
#endif

#ifndef UINT
#define UINT		unsigned int
#endif

#ifndef BOOL
#define BOOL	int
#endif

#ifndef TRUE
#define TRUE		1
#endif

#ifndef FALSE
#define FALSE		0
#endif

#ifndef ULONGLONG
#define ULONGLONG	unsigned long long
#endif

#ifndef LONGLONG
#define LONGLONG	long long
#endif

#ifndef INT64
#define INT64 int64
#endif

#ifndef UINT64
#define UINT64 uint64
#endif

typedef struct _SYSTEMTIME
{
    WORD wYear;
    WORD wMonth;
    WORD wDayOfWeek;
    WORD wDay;
    WORD wHour;
    WORD wMinute;
    WORD wSecond;
    WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;

#endif

#ifdef	__cplusplus
extern "C" {
#endif

///////////////////////////////////////////////////////////////////////////////////

// 按帧序号获取关键帧
#define TYPE_BY_FRAME_NUMBER			1
// 按帧事件获取关键帧
#define TYPE_BY_FRAME_TIME				2

#define MAX_SOURCE_BUF_SIZE				1024 * 1024 * 100	// 数据流缓冲区最大长度
#define MIN_SOURCE_BUF_SIZE				1024 * 50			// 数据流缓冲区最小长度

#define STREAM_TYPE_REALTIME			0					// 实时流模式
#define STREAM_TYPE_FILE				1					// 文件流模式

#define PlayMS_QueryTime				1					//编码中时间信息
#define PlayMS_QueryFileRate			2					//帧率信息
#define PlayMS_QueryMediaInfo			3					//媒体信息
#define PlayMS_QueryRenderNum			4					//当前要渲染的帧号
#define PlayMS_QueryRenderTime			5					//当前要渲染的时间
#define PlayMS_QuerySrcTime				6					//视频源中的时间信息
#define PlayMS_QueryCurRenderNum		7					//当前帧号。4是上一帧的帧号
#define PlayMS_QueryRenderPTS			8					//当前要渲染的帧时间戳

///////////////////////////////////////////////////////////////////////////////////
// YUV 数据类型
typedef enum
{
	// UYVY类型的YUV数据
	TYPE_UYUV = 1,
	// 4:2:0类型YUV数据
	TYPE_IYUV = 3,
	// RGB32类型YUV数据
	TYPE_RGB32 = 7,
}ENUM_YUV_TYPE;

// 音频数据类型
typedef enum
{
	// 8位音频数据类型
	TYPE_AUDIO_DATA_8 = 100,
	// 16位音频数据类型
	TYPE_AUDIO_DATA_16 = 101,	
}ENUM_AUDIO_DATA_TYPE;

// 帧缓冲类型
typedef enum
{
	// 视频源缓冲
	TYPE_MEDIA_VIDEO_SRC_BUF = 1,
	// 音频源缓冲
	TYPE_MEDIA_AUDIO_SRC_BUF = 2,
	// 解码后视频数据缓冲
	TYPE_MEDIA_VIDEO_RENDER_BUF = 3,
	// 解码后音频数据缓冲
	TYPE_MEDIA_AUDIO_RENDER_BUF = 4,
}ENUM_MEDIA_BUF_TYPE;

// 多媒体帧类型
typedef enum
{
	MEDIA_FRAME_TYPE_VIDEO = 0,		// 视频帧类型
	MEDIA_FRAME_TYPE_AUDIO = 1,		// 音频帧类型
}ENUM_MEDIA_FRAME_TYPE;

// 帧子类型
typedef enum
{
	SUB_FRAME_TYPE_VIDEO_I = 0,				// I帧
	SUB_FRAME_TYPE_VIDEO_P,					// P帧
	SUB_FRAME_TYPE_VIDEO_B,					// B帧
	SUB_FRAME_TYPE_VIDEO_S,					// S帧
	
	SUB_FRAME_TYPE_VIDEO_MJPEG = 8,			// MJPEG
}ENUM_SUB_FRAME_TYPE;

// 编码格式
typedef enum
{
	VIDEO_ENCODE_TYPE_UNKNOWN = 0x00,		// 未知视频编码格式
	VIDEO_ENCODE_TYPE_MPEG4 = 0x01,			// MPEG4 视频编码格式
	VIDEO_ENCODE_TYPE_HISI_H264 = 0x02,		// 海思H264视频编码格式
	VIDEO_ENCODE_TYPE_JPEG = 0x03,			// 标准JPEG视频编码格式

	VIDEO_ENCODE_TYPE_AVS = 0x07,			// 标准AVS视频编码格式
	VIDEO_ENCODE_TYPE_STD_H264 = 0x08,		// 标准H264视频编码格式
	VIDEO_ENCODE_TYPE_MPEG2 = 0x09,			// MPEG2视频编码格式

	VIDEO_ENCODE_TYPE_RY_H264 = 0x0D,		// 我司H264视频编码格式
	VIDEO_ENCODE_TYPE_RY_H265 = 0x0E,		// 我司H265视频编码格式
}ENUM_VIDEO_ENCODE_TYPE;

typedef enum
{
	STREAM_PACKAGE_TYPE_UNKNOWN = 0x00,		// 未知码流
	STREAM_PACKAGE_TYPE_MPEG4 = 0x01,		// MPEG4

	STREAM_PACKAGE_TYPE_AUDIO = 0x06,		// 音频
	STREAM_PACKAGE_TYPE_PS = 0x07,			// PS（MPEG-2）

	STREAM_PACKAGE_TYPE_ASF = 0x09,			// ASF

	STREAM_PACKAGE_TYPE_TS = 0x0C,			// TS（MPEG-2）
	STREAM_PACKAGE_TYPE_SVC = 0x0D,			// SVC
	STREAM_PACKAGE_TYPE_AVI = 0x0E,			// AVI
	STREAM_PACKAGE_TYPE_MP4 = 0x0F,			// MP4
	STREAM_PACKAGE_TYPE_CGI = 0x10,			// CGI
	STREAM_PACKAGE_TYPE_WAV = 0x11,			// WAV音频
	STREAM_PACKAGE_TYPE_FLV = 0x12,			// FLV
	
	STREAM_PACKAGE_TYPE_RYMS = 0x13,		// 我司码流

	STREAM_PACKAGE_TYPE_MKV = 0x14,			// MKV
	STREAM_PACKAGE_TYPE_RTP = 0x15,			// RTP
	STREAM_PACKAGE_TYPE_RAW_MPEG4 = 0x16,	// MPEG4裸码流
	STREAM_PACKAGE_TYPE_RAW_H264 = 0x17,	// H264裸码流
	STREAM_PACKAGE_TYPE_RAW_H265 = 0x18,	// H265裸码流
	STREAM_PACKAGE_TYPE_WMV = 0x19,			// WMV
	STREAM_PACKAGE_TYPE_RAW_MPEG2 = 0x20,	// MPEG2裸码流
	STREAM_PACKAGE_TYPE_RAW_SVAC = 0x21,	// SVAC裸码流
	STREAM_PACKAGE_TYPE_MOV = 0x22,			// MOV
	STREAM_PACKAGE_TYPE_VOB = 0x23,			// VOB

}ENUM_STREAM_PACKAGE_TYPE;

///////////////////////////////////////////////////////////////////////////////////
//时间结构
#ifndef _ALTIME_
#define _ALTIME_
typedef struct _ALTIME								
{
	DWORD second	:6;					//	秒	0-59		
	DWORD minute	:6;					//	分	0-59		
	DWORD hour		:5;					//	时	0-23		
	DWORD day		:5;					//	日	1-31		
	DWORD month		:4;					//	月	1-12		
	DWORD year		:6;					//	年	2000-2063	
} ALTIME, *pALTIME;
#endif

// 帧定位信息
typedef struct
{
	LONGLONG		nFilePos;				// 帧在文件中的偏移位置
	LONG			nFrameLen;				// 帧长度
	LONG			nFrameNum;				// 帧序号
	LONG			nFrameTime;				// 帧时间
	LONG			nErrorFrameNum;			// 未启用
	SYSTEMTIME*		pErrorTime;				// 未启用
	LONG			nErrorLostFrameNum;		// 未启用
	LONG			nErrorFrameSize;		// 未启用		
}FRAME_POS_INFO, *PFRAME_POS_INFO;

// 解码帧属性信息
typedef struct
{
	LONG			nWidth;					// 画面宽,单位像素
	LONG			nHeight;				// 画面高,单位像素
	LONG			nStamp;					// 时标信息,单位毫秒
	LONG			nType;					// 视频帧类型,TYPE_IYUV,TYPE_AUDIODATA_16,TYPE_RGB32
	LONG			nFrameRate;				// 图像帧率
}FRAME_ATTRI_INFO;

// 解码帧属性信息
typedef struct
{
	int				nFrameType;				// 帧类型
											// 0 - MEDIA_FRAME_TYPE_VIDEO（视频帧）
											// 1 - MEDIA_FRAME_TYPE_AUDIO（音频帧）
	int				nSubFrameType;			// 帧子类型（参见 ENUM_SUB_FRAME_TYPE 枚举值）
	int				nEncodeType;			// 解码类型（参见 ENUM_VIDEO_ENCODE_TYPE 枚举值）
	int				nStreamType;			// 码流封装类型（参见 ENUM_STREAM_PACKAGE_TYPE 枚举值）
	
	unsigned char*	pFrameData;				// 帧数据
	unsigned int	nFrameDataLen;			// 帧数据长度
	unsigned char*	pFrameBodyData;			// 帧裸数据
	unsigned int	nFrameBodyLen;			// 帧裸数据长度

	int				nFrameSeq;				// 帧序号
	int				nStamp;					// 时标信息(单位:ms)
	int				nWidth;					// 画面宽(单位:像素)
	int 			nHeight;				// 画面高(单位:像素)
	int				nFrameRate;				// 图像帧率
	int				nChannels;				// 音频通道数
	int				nBitPerSample;			// 音频采样位数
	int				nSamplesPerSec;			// 音频采样频率
	int				nRemainData;			// 缓冲剩余数据量
	SYSTEMTIME		nDataTime;				// 时间
	int				nReserved[48];			// 保留位
}FRAME_ATTRI_INFO_EX;

// 解码帧内容
typedef struct 
{
	int				nFrameType;				// 帧类型 
											// 0 - MEDIA_FRAME_TYPE_VIDEO（视频帧）
											// 1 - MEDIA_FRAME_TYPE_AUDIO（音频帧）
	int				nSubFrameType;			// 帧子类型（参见 ENUM_SUB_FRAME_TYPE 枚举值）
	
	void*			pAudioData;				// 音频数据（音频帧有效）
	int				nAudioDataLen;			// 音频数据长度

	void*			pVideoData[3];			// 分别表示视频的YUV三个分量（视频帧有效）
	int				nStride[3];				// 分别表示YUV三个分量的跨距（视频帧有效）
	int				nWidth[3];				// 分别表示YUV三个分量的宽度（视频帧有效）
	int				nHeight[3];				// 分别表示YUV三个分量的高度（视频帧有效）
	int				nReserved[64];			// 保留位
}FRAME_DEC_INFO;

/////////////////////////////////////////////////////////////////////////////////////////

/**********************************************************************************
函数：		PlayMS_Play
参数：		[in] LONG nPort：			通道号
			[in] HWND hWnd：    		播放窗口句柄
返回值：	成功返回TRUE, 失败返回FALSE
说明：		开始播放。 如果当前已经是播放状态，则恢复到正常播放速度。
			在解码线程中，如果窗口句柄为NULL，不显示画面，但不影响解码。
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_Play(LONG nPort, HWND hWnd);

/**********************************************************************************
函数：		PlayMS_Stop
参数：		[in] LONG nPort：			通道号
返回值：	成功返回TRUE, 失败返回FALSE
说明：		停止播放。
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_Stop(LONG nPort);

/**********************************************************************************
函数：		PlayMS_GetCurrentFrameRate
参数：		[in] LONG nPort：			通道号
返回值：	当前帧率
说明：		获取当前帧率。
**********************************************************************************/
PLAYMS_API DWORD CALLMETHOD PlayMS_GetCurrentFrameRate(LONG nPort);

/**********************************************************************************
函数：		PlayMS_GetCurrentFrameRate
参数：		[in] LONG nPort：			通道号
			[out] double *pBitRate:		实时码率值
返回值：	实时码率
说明：		获取实时码率。
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_GetRealFrameBitRate(LONG nPort, double* pBitRate);

/**********************************************************************************
函数：		PlayMS_GetPictureSize
参数：		[in] LONG nPort：			通道号
			[in] LONG *pWidth:			图片宽度
			[in] LONG *pHeight:			图片高度
返回值：	成功返回TRUE, 失败返回FALSE
说明：		获取码流中原始图像的大小，该函数只有当播放开始后才能获取准确的值。
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_GetPictureSize(LONG nPort, LONG *pWidth, LONG *pHeight);

/**********************************************************************************
函数：		PlayMS_GetStreamOpenMode
参数：		[in] LONG nPort：			通道号
返回值：	成功返回流模式，失败返回-1
说明：		获取码流打开模式。
			0 - STREAM_TYPE_REALTIME（实时流模式） 
			1 - STREAM_TYPE_FILE（文件流模式）
**********************************************************************************/
PLAYMS_API LONG CALLMETHOD PlayMS_GetStreamOpenMode(LONG nPort);

/**********************************************************************************
函数：		PlayMS_SetStreamOpenMode
参数：		[in] LONG nPort：			通道号
			[in] DWORD nMode：			播放模式
返回值：	成功返回TRUE, 失败返回FALSE
说明：		设置码流打开模式，需在PlayMS_Play之前调用
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_SetStreamOpenMode(LONG nPort, DWORD dwMode);

/**********************************************************************************
函数：		BOOL PlayMS_GetFreePort
参数：		[out] LONG *pnPort			通道号	
返回值：	成功返回TRUE, 失败返回FALSE
说明：		获取未使用的通道号，通道号的上限为500。
			通过该通道号来区分不同路的视频，与PlayMS_ReleasePort匹对使用。
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_GetFreePort(LONG *pnPort);

/**********************************************************************************
函数：		BOOL PlayMS_ReleasePort
参数：		[in] LONG nPort				通道号	
返回值：	成功返回TRUE, 失败返回FALSE
说明：		释放通道号，与PlayMS_GetFreePort匹对使用。
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_ReleasePort(LONG nPort);

/**********************************************************************************
函数：		PlayMS_ResetSourceBuffer
参数：		[in] LONG nPort：			通道号
返回值：	成功返回TRUE, 失败返回 FLASE.
说明：		清空流播放模式下源缓冲数据，一般在关闭码流后调用。
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_ResetSourceBuffer(LONG nPort);

/**********************************************************************************
函数:		PlayMS_RegisterDrawCallBack
描述:		注册一个画图函数
参数:		[in]nPort			端口号
			[in]fRegDrawCB		绘图回调函数
					nPort		端口号
					hDc			绘图设备上下文句柄
					pUserData	用户参数
			[in]pUserData		回调函数的用户参数
返回值:		成功返回TRUE, 失败返回FALSE
说明:		注册一个绘图回调函数，用户可以在该绘图回调函数中绘制用户私有数据，
			如用户可以在视频表面绘制一个矩形框。绘图回调函数中不能作过多操作，
			否则会由于该类操作消耗过多时间，从而导致视频实时性受到影响。
**********************************************************************************/
typedef void (CALLBACK* fRegDrawCallBack)(LONG nPort, HDC hDc, void* pUserData);
PLAYMS_API BOOL CALLMETHOD PlayMS_RegisterDrawCallBack(LONG nPort, fRegDrawCallBack fRegDrawCB, void* pUserData);

/**********************************************************************************
函数：		PlayMS_OpenStream
参数：		[in] LONG nPort:			通道号
			[in] DWORD nBufPoolSize:	设置码流数据的缓冲区大小，
										范围是[SOURCE_BUF_MIN~ SOURCE_BUF_MAX]
										如果码流数据较均匀，可调小该值；
										如果码流数据不均匀，可调大该值。
返回值：	成功返回TRUE, 失败返回FALSE
说明：		打开码流播放。
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_OpenStream(LONG nPort, DWORD nBufPoolSize);

/**********************************************************************************
函数：		BOOL PlayMS_CloseStream(LONG nPort)
参数：		[in] LONG nPort：			通道号
返回值：	成功返回TRUE, 失败返回FALSE
说明：		关闭码流播放。
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_CloseStream(LONG nPort);

/**********************************************************************************
函数：		PlayMS_InputData
参数：		[in] LONG nPort：			通道号
			[in] PBYTE pBuf：			缓冲区数据地址		
			[in] DWORD nSize：			缓冲区数据大小
返回值：	成功返回TRUE, 失败返回FALSE。
说明：		输入数据流，需在打开流（PlayMS_OpenStream）且播放（PlayMS_Play）后才能输入数据。
			如果返回FALSE，很可能是缓冲区溢满，可等待一会儿再输入数据，或者扩大缓冲区。
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_InputData(LONG nPort, PBYTE pBuf, DWORD nSize);

/**********************************************************************************
函数：		PlayMS_SetDecodeCallBack
参数：		[in] LONG nPort：						通道号	
			[in] fDecodeCallBack fDecCB:  			解码回调函数指针
					nPort:							通道号
					pFrameDecodeInfo:				帧内容
					pFrameInfo:						帧信息
					pUser:							用户参数
			[in] void* pUser:  						用户自定义参数
返回值：	成功返回TRUE, 失败返回FALSE
说明：		设置解码数据回调，适用于只解码不显示的情况。
			需在PlayMS_Play之后调用，在调用PlayMS_Stop之后自动失效
**********************************************************************************/
typedef void (CALLBACK* fDecodeCallBack)(LONG nPort, FRAME_DEC_INFO* pFrameDecodeInfo, FRAME_ATTRI_INFO_EX* pFrameInfo, void* pUserData);
PLAYMS_API BOOL CALLMETHOD PlayMS_SetDecodeCallBack(LONG nPort, fDecodeCallBack fDecCB, void* pUserData);

/**********************************************************************************
函数：		PlayMS_SetVisibleDecodeCallBack
参数：		[in] LONG nPort：						通道号	
			[in] fDecodeCallBack fDecCB:  			解码回调函数指针
					nPort:							通道号
					pFrameDecodeInfo:				帧内容
					pFrameInfo:						帧信息
					pUser:							用户参数
			[in] void* pUserData:  					用户自定义参数
返回值：	成功返回TRUE, 失败返回FALSE
说明：		设置解码数据回调，适用于解码且显示的情况。
			需在PlayMS_Play之后调用，在调用PlayMS_Stop之后自动失效
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_SetVisibleDecodeCallBack(LONG nPort, fDecodeCallBack fDecCB, void* pUserData);

/**********************************************************************************
函数：		PlayMS_SetDisplayCallBack
参数：		[in] LONG nPort：						通道号	
			[in] fDisplayCallBack fDisplayCB:		显示回调函数指针
					nPort:							通道号
					pYuvBuf:						视频帧 YUV 数据
					nYuvSize:						YUV 数据大小	
					nWidth:							画面宽,单位像素
					nHeight:						画面高,单位像素
					nStamp:							时间戳信息
					nType:							视频帧类型, TYPE_IYUV, TYPE_AUDIODATA_16, TYPE_RGB32
					pReserved:						保留参数
			[in] void* pUserData: 					用户自定义参数
返回值：	成功返回TRUE, 失败返回FALSE
说明：		设置视频抓图回调函数。当用户想得到一段时间内的抓图数据，可调用该函数。
			当将回调函数设置为NULL时, 停止函数回调。
			其中设置的回调函数，只有在有解码数据时才被调用，并由用户处理抓图数据。
			该函数可在任何时候调用
**********************************************************************************/
typedef void (CALLBACK* fDisplayCallBack)(LONG nPort, char * pYuvBuf, LONG nYuvSize, LONG nWidth, LONG nHeight, LONG nStamp, LONG nType, void* pReserved);
PLAYMS_API BOOL CALLMETHOD PlayMS_SetDisplayCallBack(LONG nPort, fDisplayCallBack fDisplayCB, void* pUserData);

/**********************************************************************************
函数：		PlayMS_CatchPic
参数：		[in] LONG nPort：			通道号	
			[in] char* sFileName: 		图片的文件名称
返回值：	成功返回TRUE, 失败返回FALSE
说明：		抓图，当用户想实现一次抓一张图，可调用该函数。
			该函数在视频暂停、单帧播放时也可使用。
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_CatchPic(LONG nPort, char* sFileName);

/**********************************************************************************
函数：		PlayMS_SetPlayMethod
参数：		[in] LONG nPort：			通道号	
			[in] int nStartTime: 		开始播放的时间(ms)
			[in] int nSlowTime:  		开始慢放的时间(ms)
			[in] int nFastTime:  		开始快放的时间(ms)
			[in] int nFailedTime: 		失败时间，超过该时间则数据投递失败（ms）
返回值：	成功返回TRUE, 失败返回FALSE
说明：		设置播放的方法策略，该函数只有在实时码流时调用才有效。
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_SetPlayMethod(LONG nPort, int nStartTime, int nSlowTime, int nFastTime, int nFailedTime);

/**********************************************************************************
函数：		PlayMS_SetDecCBStream
参数：		[in] LONG nPort：			通道号	
			[in] DWORD dwStream:  		码流类型，1为视频流，2为音频流，3为复合流
返回值：	成功返回TRUE, 失败返回FALSE
说明：		设置解码回调的码流类型，该函数需在PlayMS_Play之前调用
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_SetDecCBStream(LONG nPort, DWORD dwStream);

/**********************************************************************************
函数：		PlayMS_SetAudioCallBack
参数：		[in] LONG nPort：						通道号	
			[in] fAudioCallBack fAudioCB: 			音频回调函数指针
						nPort:						通道号
						pAudioBuf:					音频缓存数据
						nSize:						缓存数据大小
						nStamp:						时标信息,单位毫秒
						nType:						音频数据类型
													8位音频数据类型 TYPE_AUDIO_DATA_8 = 100,
													16位音频数据类型 TYPE_AUDIO_DATA_16 = 101,
						pUserData:					用户参数
			[in] void* pUserData:  					用户参数
返回值：	成功返回TRUE, 失败返回FALSE
说明：		设置音频解码数据回调
**********************************************************************************/
typedef void (CALLBACK * fAudioCallBack)(LONG nPort, char * pAudioBuf, LONG nSize, LONG nStamp, LONG nType, void* pUserData);
PLAYMS_API BOOL CALLMETHOD PlayMS_SetAudioCallBack(LONG nPort, fAudioCallBack fAudioCB, void* pUserData);

/**********************************************************************************
函数：		PlayMS_StartDataRecord
参数：		[in] LONG nPort：			通道号	
			[in] char *sFileName:  		录像文件名，
										如果文件名中有不存在的文件夹,就创建该文件夹
			[in] int nDataType:  		0表示原始视频流; 1表示转换成AVI格式;
										2表示转换成ASF格式; 3分段保存文件
返回值：	成功返回TRUE, 失败返回FALSE
说明：		开始流数据录像，该函数需在PlayMS_Play之后调用，只有在实时码流时调用才有效
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_StartDataRecord(LONG nPort, char *sFileName, int nDataType);

/**********************************************************************************
函数：		PlayMS_WriteData
参数：		[in] LONG nPort：			通道号
			[in] PBYTE pBuf:      		码流数据
			[in] DWORD nSize:   		码流大小	
返回值：	成功返回TRUE, 失败返回FALSE
说明：		保存原始码流数据
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_WriteData(LONG nPort, PBYTE pBuf, DWORD nSize);

/**********************************************************************************
函数：		BOOL PlayMS_StopDataRecord(LONG nPort)
参数：		[in] LONG nPort：			通道号	
返回值：	成功返回TRUE, 失败返回FALSE
说明：		停止流数据录像
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_StopDataRecord(LONG nPort);

/**********************************************************************************
函数：		PlayMS_QueryInfo
			[in] LONG nPort：				通道号
			[in] int nQueryType:  			指定查询类型，主要类型如下：
				PlayMS_QueryTime  			编码中时间信息
				PlayMS_QueryFileRate  		帧率信息
				PlayMS_QueryMediaInfo  		媒体信息
				PlayMS_QueryRenderNum 		当前要渲染的帧号，上一帧的帧号
				PlayMS_QueryRenderTime		当前要渲染的时间
				PlayMS_QuerySrcTime    		视频源中的时间信息
				PlayMS_QueryCurRenderNum  	当前帧号
				PlayMS_QueryRenderPTS		当前时间戳
			[out] char* pBuffer:  			存放查询到的缓冲数据
			[in] int nBufLen:  				输入的缓冲区大小
			[out] int* pRetLen:  			存放查询的有效数据大小
返回值：	成功返回TRUE, 失败返回FALSE
说明：		查询指定通道的时间、帧率等信息
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_QueryInfo(LONG nPort, int nQueryType, char* pBuffer, int nBufLen, int* pRetLen);

/**********************************************************************************
函数：		PlayMS_CreateStream
参数：		[in] DWORD nBufPoolSize：		设置码流数据的缓冲区大小
											范围是[MIN_SOURCE_BUF_SIZE, MAX_SOURCE_BUF_SIZE].
返回值：	成功返回TRUE, 失败返回FALSE
说明：		分配空闲通道号并打开码流，就是PlayMS_GetFreePort和PlayMS_OpenStream接口的合集
**********************************************************************************/
PLAYMS_API DWORD CALLMETHOD PlayMS_CreateStream(DWORD nBufPoolSize);

/**********************************************************************************
函数：		PlayMS_DestroyStream
参数：		[in] LONG nPort:				通道号
返回值：	成功返回TRUE, 失败返回FALSE
说明：		关闭码流并释放申请的通道号
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_DestroyStream(LONG nPort);

/**********************************************************************************
函数：		BOOL PlayMS_OpenFile(LONG nPort, LPSTR sFileName)
参数：		[in] LONG nPort:		通道号
			[in] LPSTR sFileName:	文件名
返回值：	成功返回TRUE, 失败返回FALSE
说明：		打开文件，需在PlayMS_Play之前调用。
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_OpenFile(LONG nPort, LPSTR sFileName);

/**********************************************************************************
函数：		BOOL PlayMS_CloseFile(LONG nPort)
参数：		[in] LONG nPort:		通道号
返回值：	成功返回TRUE, 失败返回FALSE
说明：		关闭文件，需在PlayMS_Stop之后调用。
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_CloseFile(LONG nPort);

/**********************************************************************************
函数：		BOOL PlayMS_Pause(LONG nPort, DWORD nPause)
参数：		[in] LONG nPort：			通道号
			[in] DWORD nPause: 		1为暂停，0为恢复播放
返回值：	成功返回TRUE, 失败返回FALSE
说明：		暂停播放, 或者恢复播放。
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_Pause(LONG nPort,DWORD nPause);

/**********************************************************************************
函数：		PlayMS_Fast
参数：		[in] LONG nPort：			通道号
返回值：	成功返回TRUE, 失败返回FALSE
说明：		播放提速。每调用一次，播放速度乘2，播放速度范围为[1/64,64]
			调用PlayMS_Play后从当前位置恢复到正常播放速度
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_Fast(LONG nPort);

/**********************************************************************************
函数：		PlayMS_Slow
参数：		[in] LONG nPort：			通道号
返回值：	成功返回TRUE, 失败返回FALSE
说明：		播放减速。每调用一次，播放速度除2，播放速度范围为[1/64, 64]。
			调用PlayMS_Play后从当前位置恢复到正常播放速度
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_Slow(LONG nPort);

/**********************************************************************************
函数：		PlayMS_SetPlaySpeed
参数：		[in] LONG nPort：			通道号
			[in] float fCoff：			播放速度，范围为[1/64,64]
返回值：	成功返回TRUE, 失败返回FALSE
说明：		设置视频播放速度
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_SetPlaySpeed(LONG nPort, float fCoff);

/**********************************************************************************
函数：		PlayMS_OneByOne
参数：		[in] LONG nPort：			通道号
返回值：	成功返回TRUE, 失败返回FALSE
说明：		单帧播放，每调用一次播放一帧。调用PlayMS_Play后恢复正常播放
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_OneByOne(LONG nPort);

/**********************************************************************************
函数：		PlayMS_SetPlayPos
参数：		[in] LONG nPort：			通道号
			[in] float fRelativePos:	文件长度的百分比
返回值：	成功返回TRUE, 失败返回FALSE
说明：		设置播放文件的相对位置(百分比)。需在PlayMS_Play之后调用
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_SetPlayPos(LONG nPort, float fRelativePos);

/**********************************************************************************
函数：		PlayMS_SetPlayDirection
参数：		[in] LONG nPort：			通道号
			[in] DWORD nDirection：		播放方向（0: 向前，1: 向后)
返回值：	成功返回TRUE, 失败返回FALSE
说明：		设置视频文件的播放方向
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_SetPlayDirection(LONG nPort, DWORD nDirection);

/**********************************************************************************
函数：		PlayMS_GetPlayPos
参数：		[in] LONG nPort：			通道号
返回值：	成功返回TRUE, 失败返回FALSE
说明：		获取播放文件的相对位置(百分比)。需在PlayMS_Play之后调用
**********************************************************************************/
PLAYMS_API float CALLMETHOD PlayMS_GetPlayPos(LONG nPort);

/**********************************************************************************
函数：		PlayMS_SetVolume
参数：		[in] LONG nPort：			通道号
			[in] WORD nVolum: 			音量值，范围为[0,0xFFFF]
返回值：	成功返回TRUE, 失败返回FALSE
说明：		设置音量大小。该接口设置的音量是声卡输出的主音量，
			会对其他应用的音量有影响
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_SetVolume(LONG nPort, WORD nVolume);

/**********************************************************************************
函数：		PlayMS_GetVolume
参数：		[in] LONG nPort：			通道号
返回值：	成功返回音量值，失败返回值 <= 0
说明：		获取声卡输出的音量
**********************************************************************************/
PLAYMS_API WORD CALLMETHOD PlayMS_GetVolume(LONG nPort);

/**********************************************************************************
函数：		PlayMS_PlaySound
参数：		[in] LONG nPort：			通道号
返回值：	成功返回TRUE, 失败返回FALSE
说明：		以独占方式打开声音。也就是一次只能打开一路声音。
			如果打开当前的声音，则自动关闭之前已经打开的声音。
			建议和PlayMS_StopSound匹配使用
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_PlaySound(LONG nPort);

/**********************************************************************************
函数：		PlayMS_StopSound
参数：		无
返回值：	成功返回TRUE, 失败返回FALSE
说明：		关闭声音
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_StopSound();

/**********************************************************************************
函数：		PlayMS_GetFileTime
参数：		[in] LONG nPort：			通道号
返回值：	四舍五入后文件时长的长度值
说明：		获取文件的总时长，单位为秒。需在PlayMS_Play之后调用
**********************************************************************************/
PLAYMS_API DWORD CALLMETHOD PlayMS_GetFileTime(LONG nPort);

/**********************************************************************************
函数：		PlayMS_GetPlayedTime
参数：		[in] LONG nPort：			通道号
返回值：	成功时返回文件已播放时间，失败时返回0
说明：		获取文件已播放的时间，单位为秒。需在PlayMS_Play之后调用
**********************************************************************************/
PLAYMS_API DWORD CALLMETHOD PlayMS_GetPlayedTime(LONG nPort);

/**********************************************************************************
函数：		PlayMS_GetPlayedTimeEx
参数：		[in] LONG nPort：			通道号
返回值：	成功返回TRUE, 失败返回FALSE
说明：		获取文件当前播放的时间，单位为毫秒。需在PlayMS_Play之后调用
**********************************************************************************/
PLAYMS_API DWORD CALLMETHOD PlayMS_GetPlayedTimeEx(LONG nPort);

/**********************************************************************************
函数：		PlayMS_GetPlayedFrames
参数：		[in] LONG nPort：			通道号
返回值：	文件已经解码的帧数
说明：		获取文件已经解码的帧数
**********************************************************************************/
PLAYMS_API DWORD CALLMETHOD PlayMS_GetPlayedFrames(LONG nPort);

/**********************************************************************************
函数：		PlayMS_GetFileTotalFrames
参数：		[in] LONG nPort：			通道号
返回值：	文件总帧数
说明：		获取文件的总帧数。需在PlayMS_Play之后调用
**********************************************************************************/
PLAYMS_API DWORD CALLMETHOD PlayMS_GetFileTotalFrames(LONG nPort);

/**********************************************************************************
函数：		BOOL PlayMS_SetPlayedTimeEx(LONG nPort,DWORD nTime)
参数：		[in] LONG nPort：			通道号
			[in] DWORD nTime: 			播放时间
返回值：	成功返回TRUE, 失败返回FALSE
说明：		设置文件播放到指定时间，单位为毫秒。需在PlayMS_Play之后调用
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_SetPlayedTimeEx(LONG nPort, DWORD nTime);

/**********************************************************************************
函数：		DWORD PlayMS_GetCurrentFrameNum(LONG nPort)
参数：		[in] LONG nPort：			通道号
返回值：	文件当前播放的帧序号
说明：		获取文件当前播放的帧序号。
			如果视频不丢失，该数值接近PlayMS_GetPlayedFrames的返回值
**********************************************************************************/
PLAYMS_API DWORD CALLMETHOD PlayMS_GetCurrentFrameNum(LONG nPort);

/**********************************************************************************
函数：		DWORD PlayMS_SetCurrentFrameNum(LONG nPort,DWORD nFrameNum)
参数：		[in] LONG nPort：			通道号
			[in] DWORD nFrameNum: 	帧序号
返回值：	成功返回TRUE,失败返回FALSE
说明：		设置文件当前播放的帧序号
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_SetCurrentFrameNum(LONG nPort,DWORD nFrameNum);

/**********************************************************************************
函数：		PlayMS_SetFileEndCallBack
参数：		[in] LONG nPort：						通道号	
			[in] fFileEndCallBack fFileEndCB: 		回调函数指针
					nPort  							通道号
					pUserData  						用户自定义参数
			[in] void* pUserData:  					用户自定义参数
返回值：	成功返回TRUE, 失败返回FALSE
说明：		设置文件结束回调。当文件播放结束时，触发回调函数。
			需在PlayMS_OpenSteam或PlayMS_OpenFile之前调用
**********************************************************************************/
typedef void (CALLBACK *fFileEndCallBack)(DWORD nPort, void* pUserData);
PLAYMS_API BOOL CALLMETHOD PlayMS_SetFileEndCallBack(LONG nPort, fFileEndCallBack pFileEndCBFun, void* pUserData);

/**********************************************************************************
函数：		PlayMS_SetFileEndMsg
参数：		[in] LONG nPort：				通道号	
			[in] HWND hWnd:  				消息发送窗口
			[in] UINT nMsg:  				用户自定义需发送的消息数据
返回值：	成功返回TRUE, 失败返回FALSE
说明：		设置文件播放结束时，用户自定义发送的消息
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_SetFileEndMsg(LONG nPort, HWND hWnd, UINT nMsg);

/**********************************************************************************
函数:	PlayMS_SetWaterMarkCallBack
描述:	设置水印数据回调。注意：水印校验回调设置后将不会进行解码显示
参数:	nPort			端口号
		pFunc			水印信息获取回调函数, 参数含义如下:
			pBuf		水印数据buffer指针
			nKey		区分不同水印信息
			nLen		缓冲的最大长度
			nRealLen	缓冲的实际长度
			nType		数值范围[0,3],含义如下
						0  I帧帧数据水印信息
						1  帧水印
						2  水印校验 
						3  智能分析帧
			pUserData	用户自定义参数 
		pUserData		用户自定义参数 
返回:	成功返回TRUE,失败返回FALSE.
**********************************************************************************/
typedef int (CALLBACK* fGetWaterMarkInfoCallBack)(char* pBuf, LONG nKey, LONG nLen, LONG nRealLen, LONG nType, void* pUserData);	
PLAYMS_API BOOL CALLMETHOD PlayMS_SetWaterMarkCallBack(LONG nPort, fGetWaterMarkInfoCallBack pFunc, void* pUserData);

/**********************************************************************************
函数:	PlayMS_SetWaterMarkCallBackEx
描述:	设置水印数据回调(成功后解码不显示)
参数:	nPort				端口号
		pGetWaterMarkCB		函数指针, 参数含义如下:
			nPort			端口号
			buf				水印数据缓冲
			lTimeStamp		水印的时间戳
			lInfoType		水印信息类型
			len				缓冲的最大长度
			reallen			缓冲的实际长度
			lCheckResult	1-没有错误; 2-水印错误; 3-帧数据错误; 4-帧号错误
			pUserData		用户自定义参数
		pUserData		用户自定义参数
返回:	成功返回TRUE,失败返回FALSE.
**********************************************************************************/
typedef int (CALLBACK* fGetWaterMarkInfoCallBackEx)(LONG nPort, char* buf, LONG lTimeStamp, LONG lInfoType, LONG len, LONG reallen, LONG lCheckResult, void* pUserData);
PLAYMS_API BOOL CALLMETHOD PlayMS_SetWaterMarkCallBackEx(LONG nPort, fGetWaterMarkInfoCallBackEx pGetWaterMarkCB, void* pUserData);

/**********************************************************************************
函数：		PlayMS_ImageWatermarkCheck
参数：		[in] const char* pImagePath：	图片本地路径	
返回值：	成功返回TRUE, 失败返回FALSE
说明：		图片水印校验
**********************************************************************************/
PLAYMS_API BOOL CALLMETHOD PlayMS_ImageWatermarkCheck(const char* pImagePath);

#ifdef __cplusplus
}
#endif

#endif