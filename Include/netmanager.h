#ifndef _AL_NET_MANAGER_LIB_H
#define _AL_NET_MANAGER_LIB_H

#include "netstructcolletion.h"

#if defined(WIN32) || defined(WIN64)

#ifdef NET_API_EXPORTS
	#ifndef NET_API
		#define NET_API  __declspec(dllexport)
	#endif
#else
	#ifndef NET_API
		#define NET_API  __declspec(dllimport)
	#endif
#endif

#define CALLBACK	__stdcall
#define CALL_METHOD __stdcall  //__cdecl
#else

#ifndef NET_API
	#define NET_API 
#endif

#define CALLBACK
#define CALL_METHOD  //__cdecl

#endif

#ifdef __cplusplus
extern "C" {
#endif

/////////////////////////////////////////////////////////////////////////////////
//							netmanager library 接口定义					       //
/////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
函数：		NET_Init
参数：		[in] fDisConnCB 				设备网络断线回调函数
			[in] dwUser						用户数据
返回值：		成功返回TRUE, 失败返回FALSE。
说明：		用户在使用网络库之前，必须进行初始化
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_Init(fDisConnectCallBack fDisConnCB, LDWORD dwUser);

/********************************************************************************
函数：		NET_Exit
参数：		/	
返回值：		/
说明：		用户确认在不使用网络库任何功能之后，需要调用退出函数清理网络库资源
*********************************************************************************/
NET_API void CALL_METHOD Net_Exit();

/********************************************************************************
函数：		NET_Version
参数：		/	
返回值：		网络库版本号
说明：		获取库版本信息
*********************************************************************************/
NET_API DWORD CALL_METHOD Net_Version();

/********************************************************************************
函数：		NET_LastError
参数：		/	
返回值：		网络库最近一次错误发生时产生的错误码，错误见下表。
说明：		错误码可以帮助用户快速定位问题，开发过程中请注意错误码的收集	
*********************************************************************************/
NET_API DWORD CALL_METHOD Net_LastError(void);

/////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
函数：		NET_SetReconnectCallBack
参数：		[in] fReConnectedCB				设备断线重连成功回调函数
			[in] dwUser						用户数据
返回值：		/
说明：		设置断线时重连成功后的回调函数
*********************************************************************************/
NET_API void CALL_METHOD Net_SetReconnectCallBack(fReConnectedCallBack fReConnectedCB, LDWORD dwUser);

/********************************************************************************
函数：		NET_SetSubDisconnCallBack
参数：		[in] fSubDisConnCB					动态子连接断线回调函数
			[in] dwUser							用户数据
返回值：		成功返回TRUE, 失败返回FALSE。
说明：		设置动态子连接断线回调函数
*********************************************************************************/
NET_API void CALL_METHOD Net_SetSubDisconnCallBack(fSubDisConnectCallBack fSubDisConnCB, LDWORD dwUser);

/********************************************************************************
函数：		void NET_SetConnectTime(int nWaitTime, int nTryTimes)
参数：		[in] nWaitTime						连接等待超时时间（ms）
			[in] nTryTimes						最大连接尝试次数
返回值：		/
说明：		设置连接设备超时时间和尝试次数
*********************************************************************************/
NET_API void CALL_METHOD Net_SetConnectTime(int nWaitTime, int nTryTimes);

/********************************************************************************
函数：		void NET_SetNetworkParam(STU_NET_PARAM *pNetParam)
参数：		[in] pNetParam						设备连接的网络参数
返回值：		/
说明：		设置登陆网络环境, 用户可以在登入设备之前进行设置
*********************************************************************************/
NET_API void CALL_METHOD Net_SetNetworkParam(STU_NET_PARAM* pNetParam);

/********************************************************************************
函数：		NET_LoginDevice
参数：		[in] lpszIP							设备 IP 地址
			[in] nPort							设备登入端口
			[in] lpszUserName					设备登入用户名称
			[in] lpszPassword					设备登入用户密码
			[in] pReserved						预留位
			[out] pnError						登入错误码
												0 - 无错误
												1 - 创建网络连接错误
												2 - 创建设备登录句柄错误
												3 - 登录响应超时
返回值：		成功返回设备登入句柄，失败返回 <= 0
说明：	    登入设备
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_LoginDevice(char *lpszIP, int nPort, char *lpszUserName, char *lpszPassword, void* pReserved = NULL, int *pError = 0);

/********************************************************************************
函数：		NET_LogoutDevice
参数：		[in] lLoginID						设备登入句柄
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		登出设备
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_LogoutDevice(LLONG lLoginID);

/********************************************************************************
函数：		NET_GetSessionID
参数：		[in] lLoginID						设备登入句柄
返回值：		成功返回主连接ID，失败返回 0。
说明：		获取主链接会话ID
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_GetSessionID(LLONG lLoginID);

/////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
函数：		NET_RealPlay
参数：		[in] lLoginID						设备登入句柄
			[in] nChannelID						实时监视通道号
			[in] hWnd							实时播放窗口句柄
			[in] emType							实时流类型，默认为实时预览
返回值：		成功返回实时播放句柄，失败返回 <= 0。
说明：		开始实时监视。用户调用该函数，可以直接在指定窗口播放实时视频；
			当播放的窗口为 NULL, 则用户需要调用播放库相关接口，实现播放控制，
			详细调用可以参见 NetManagerDemos 之 RealplayDemo
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_RealPlay(LLONG lLoginID, int nChannelID, HWND hWnd, EM_REALPLAY_STREAM_TYPE rType = REALPLAY_STREAM_TYPE_REAL);

/********************************************************************************
函数：		NET_StartRealPlay
参数：		[in] lLoginID						设备登入句柄
			[in] nChannelID						实时监视通道号
			[in] hWnd							实时播放窗口句柄
			[in] emType							实时流类型
			[in] fRealDataCB					实时数据回调函数，可设为 NULL
			[in] fRealPlayDisconnCB				实时监视断开回调函数，可设为 NULL
			[in] dwUser							用户数据
			[in] dwWaitTime						实时监视超时时间（ms）
返回值：		成功返回实时监视句柄，失败返回 <= 0。
说明：		开始实时播放。
			用户可以调用该函数在指定窗口播放设备指定通道的指定码流类型的视频流。
			当播放的窗口为 NULL, 则用户需要调用播放库相关接口，实现播放控制，
			详细调用可以参见 NetManagerDemos 之 RealplayDemo
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_StartRealPlay(LLONG lLoginID, int nChannelID, HWND hWnd, EM_REALPLAY_STREAM_TYPE rType, 
	fRealPlayDataCallBackEx fRealDataCB, fRealPlayDisConnectCallBack fRealPlayDisconnCB, LDWORD dwUser, DWORD dwWaitTime = 10000);

/********************************************************************************
函数：		NET_StopRealPlay
参数：		[in] lRealHandle							实时监视句柄
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		停止实时播放			
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StopRealPlay(LLONG lRealHandle);

/********************************************************************************
函数：		Net_StartTalkBack(仅支持Windows)
参数：		[in] lLoginID						设备登入句柄
			[in] nChannelID						语音对讲解码通道号
			[in] rType							实时音频流类型，默认 REALAUDIO_STREAM_TYPE_REAL_MASTER
			[in] cbRealData						实时对讲数据回调函数
			[in] dwUser							对讲数据回调用户参数
			[in] dwWaitTime						对讲请求超时时间
			[in] nVolLevel						对讲音量等级 
												[-2，-1， 0， 1， 2, 3, 4] 等级越高音量越大
												0 表示正常音量
返回值：		成功返回语音对讲句柄，失败返回 <= 0。
说明：		开始语音对讲监视。用户调用该函数，可以开启语音对讲
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_StartTalkBack(LLONG lLoginID, int nChannelID, EM_REALAUDIO_STREAM_TYPE rType,
	fTalkBackDataCallBack cbRealData = NULL, LDWORD dwUser = 0, DWORD dwWaitTime = 3000, int nVolLevel = 0);

/********************************************************************************
函数：		Net_StopTalkBack(仅支持Windows)
参数：		[in] lTalkHandle							语音对讲句柄
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		停止语音对讲			
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StopTalkBack(LLONG lTalkHandle);

/********************************************************************************
函数：		Net_SetTalkBackCallBack(仅支持Windows)
参数：		[in] lTalkHandle					语音对讲句柄
			[in] cbRealData						设备端语音对讲数据回调函数
			[in] dwUser							用户数据
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		设置语音对讲数据回调
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_SetTalkBackCallBack(LLONG lTalkHandle, fTalkBackDataCallBack cbRealData, LDWORD dwUser);

/********************************************************************************
函数：		Net_SetTalkBackVolume(仅支持Windows)
参数：		[in] lTalkHandle					语音对讲句柄
			[in] nVolLevel						对讲音量等级 
												[-2，-1， 0， 1， 2, 3, 4] 等级越高音量越大
												0 表示正常音量
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		设置语音对讲音量大小
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_SetTalkBackVolume(LLONG lTalkHandle, int nVolLevel);

/********************************************************************************
函数：		NET_AdjustStrategyWhenPlayHD
参数：		[in] lPlayHandle						视频播放句柄
			[in] bEnable							是否启用高清播放策略
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		调整播放高清视频的播放策略
			当播放的指定窗口为 NULL 时，接口无效，需要调用播放库相关接口实现。
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_AdjustStrategyWhenPlayHD(LLONG lPlayHandle, BOOL bEnable);

/********************************************************************************
函数：		NET_SetRealDataCallBack
参数：		[in] lRealHandle					实时监视句柄
			[in] cbRealData						实时监视数据回调函数
			[in] dwUser							用户数据
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		设置实时监视数据回调
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_SetRealDataCallBack(LLONG lRealHandle, fRealPlayDataCallBack cbRealData, LDWORD dwUser);

/********************************************************************************
函数：		NET_SetRealDataCallBack
参数：		[in] lRealHandle					实时监视句柄
			[in] cbRealData						实时监视数据回调函数
			[in] dwUser							用户数据
			[in] dwFlag							数据类型（当前为 1）
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		设置实时监视数据回调
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_SetRealDataCallBackEx(LLONG lRealHandle, fRealPlayDataCallBackEx cbRealData, LDWORD dwUser, DWORD dwFlag);

/********************************************************************************
函数：		NET_AdjustFluency
参数：		[in] lRealHandle					实时监视句柄
			[in] nLevel							流畅性值（范围： 0 - 6）
												值越高流畅性越好，
												值越低实时性越好。
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		设置图像流畅性。
			实时监视视频的流畅性越好，实时性就会越低，用户需要选择合理的策略
            当实时播放的指定窗口为 NULL 时，接口无效，需要调用播放库相关接口实现。
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_AdjustFluency(LLONG lRealHandle, int nLevel);

/********************************************************************************
函数：		NET_SetDisplayRegion
参数：		[in] lPlayHandle					视频播放句柄
			[in] nRegionNum						视频区域号（当前为 0）
			[in] pSrcRect						视频电子放大局部区域
			[in] hDestWnd						视频播放窗口句柄
			[in] bEnable						是否电子放大
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		设置视频局部放大区域并显示
			当播放的指定窗口为 NULL 时，接口无效，需要调用播放库相关接口实现
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_SetDisplayRegion(LLONG lPlayHandle, DWORD nRegionNum, STU_RECT_D *pSrcRect, HWND hDestWnd, BOOL bEnable);

/********************************************************************************
函数：		NET_StartSaveRealData
参数：		[in] lRealHandle					实时监视句柄
			[in] lpszFileName				    保存数据的文件名
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		开始保存数据为文件
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StartSaveRealData(LLONG lRealHandle, const char *lpszFileName);

/********************************************************************************
函数：		BOOL NET_StopSaveRealData(LLONG lRealHandle)
参数：		[in] lRealHandle						实时监视句柄
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		结束保存数据为文件
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StopSaveRealData(LLONG lRealHandle);

/********************************************************************************
函数：		NET_SetVideoBasicEffect
参数：		[in] lPlayHandle						视频播放句柄
			[in] nBrightness						亮度值（0-128）
			[in] nContrast							对比度值（0-128）
			[in] nHue								灰度值（0-128）
			[in] nSaturation						饱和度值（0-128）
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		设置视频图像显示属性，设置后不会生效到图像配置
			当播放的指定窗口为 NULL 时，接口无效，需要调用播放库相关接口实现
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_SetVideoBasicEffect(LLONG lPlayHandle, unsigned char nBrightness, unsigned char nContrast, unsigned char nHue, unsigned char nSaturation);

/********************************************************************************
函数：		NET_GetVideoBasicEffect
参数：		[in] lPlayHandle						视频播放句柄
			[out] nBrightness						亮度值（0-128）
			[out] nContrast							对比度值（0-128）
			[out] nHue								灰度值（0-128）
			[out] nSaturation						饱和度值（0-128）
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		获取图像属性
			当播放的指定窗口为 NULL 时，接口无效，需要调用播放库相关接口实现
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_GetVideoBasicEffect(LLONG lPlayHandle, unsigned char *nBrightness, unsigned char *nContrast, unsigned char *nHue, unsigned char *nSaturation);

/********************************************************************************
函数：		Net_RegisterDrawCallBack
参数：		[in] cbDraw								绘图回调函数
			[in] dwUser								用户数据
返回值：		/
说明：		设置屏幕叠加回调，用户注册完绘图回调函数后，可以在该函数中绘图叠加到视频上。
			建议不要在该回调函数中做过多绘图操作，否则会增加视频延迟时间。
*********************************************************************************/
NET_API void CALL_METHOD Net_RegisterDrawCallBack(fCustomDrawCallBack cbDraw, LDWORD dwUser);

/********************************************************************************
函数：		NET_CapturePicture
参数：		[in] lPlayHandle						视频播放句柄
			[in] lpszPicFileName					图片文件名称
			[in] emFormat							抓拍图片格式
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		抓图
			当播放的指定窗口为 NULL 时，接口无效，需要调用播放库相关接口实现
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_CapturePicture(LLONG lPlayHandle, const char *lpszPicFileName, EM_SNAPSHOT_FORMAT_TYPE eFormat);

/********************************************************************************
函数：		LONG Net_GetStatisticFlux(LLONG lLoginID, LLONG lPlayHandle)
参数：		[in] lLoginID							设备登入句柄
			[in] lPlayHandle						视频播放句柄
返回值：		实时码流大小
说明：		用户获取到实时码流大小计算值 * 8 / 1024 = (x) kbps
*********************************************************************************/
NET_API LONG CALL_METHOD Net_GetStatisticFlux(LLONG lLoginID, LLONG lPlayHandle);

/********************************************************************************
函数：		Net_SetPlayMethod
参数：		[in] lRealHandle：						实时监视句柄	
			[in] nStartTime: 						开始播放的时间(ms)
			[in] nSlowTime:  						开始慢放的时间(ms)
			[in] nFastTime:  						开始快放的时间(ms)
			[in] nFailedTime: 						失败时间，超过该时间则数据投递失败（ms）
返回值：		成功返回 TURE，失败返回 FALSE。
说明：		用户可以通过设置以上参数设置实时播放策略，实时流设置有效。
			当实时播放的指定窗口为 NULL 时，接口无效，需要调用播放库相关接口实现。
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_SetPlayMethod(LLONG lRealHandle, int nStartTime, int nSlowTime, int nFastTime, int nFailedTime);

/********************************************************************************
函数：		NET_SetDataDrawEnable
参数：		[in] nRenderType						渲染类型
													0-实时流 1-网络回放流
			[in] lHandle							播放句柄
			[in] enable								绘图使能
			[in] reserved							保留位
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		设置绘制智能数据使能 
			当实时播放的指定窗口为 NULL 时，接口无效，需要调用播放库相关接口实现。
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_SetDataDrawEnable(int nRenderType, LLONG lHandle, BOOL enable, LONG reserved = 0);

/********************************************************************************
函数：		NET_OpenSound（仅Windows）
参数：		[in] lPlayHandle						视频播放句柄
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		打开声音
			NET_OpenSound 和 NET_CloseSound 配套使用
*********************************************************************************/ 
NET_API BOOL CALL_METHOD Net_OpenSound(LLONG lPlayHandle);

/********************************************************************************
函数：		NET_SetVolume（仅Windows）
参数：		[in] lPlayHandle						视频播放句柄
			[in] nVolume							音量大小（0-0xffff）
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		打开声音后可以调节音量
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_SetVolume(LLONG lPlayHandle, int nVolume);

/********************************************************************************
函数：		NET_CloseSound（仅Windows）
参数：		/
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		关闭声音
			NET_OpenSound 和 NET_CloseSound 配套使用
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_CloseSound();

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
函数：		Net_PreFindFile
参数：		[in] lLoginID					设备登入句柄
			[in] nChannelId					查询的通道号
			[in] emDBType					查询的数据库类型， 如 0 表示人脸图片数据库
			[in] pstTimeStart				查询的开始时间
			[in] pstTimeEnd					查询的结束时间
			[in] lpszEvents      			查询的关联事件（数组形式的 Json 字符串）
			[in] lpszDirs					查询的关联目录（数组形式的 Json 字符串）
			[in] emVStreamType				视频码流类型
			[in] emOrderType				查询排序类型
返回值：		成功返回文件查询句柄，失败返回 0。
说明：		预查询文件
			获取到文件查询句柄后，需要调用关闭查询接口，达到闭环处理
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_PreFindFile(LLONG lLoginID, 
										  int nChannelId, 
										  EM_DATABASE_TYPE emDBType, 
										  P_STU_TIME pstTimeStart,
										  P_STU_TIME pstTimeEnd, 
										  char* lpszEvents = NULL,
										  char* lpszDirs = NULL,
										  EM_VIDEO_STREAM_TYPE emVStreamType = VIDEO_STREAM_ERROR,
										  EM_ORDER_TYPE emOrderType = ORDER_TYPE_DESCENT, 
										  int nWaitTime = 3000);

/********************************************************************************
函数：		Net_FindMultiFiles
参数：		[in] lLoginID						设备登入句柄
			[in] lFindHandle					文件查找句柄（预查询文件获取）
			[out] pnFileCount					需要查找的文件总数
			[in] nWaitTime						查找超时时间
返回值：		成功返回 TRUE，失败返回 FALSE。
说明：		预查询成功后才能调用
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_FindFileCount(LLONG lLoginID, LLONG lFindHandle, int *pnFileCount, int nWaitTime = 2000);

/********************************************************************************
函数：		Net_FindOneFile
参数：		[in] lLoginID						设备登入句柄
			[in] lFindHandle					文件查找句柄（预查询文件获取）
			[out] lpFile						查找到的文件（信息）
			[in] nWaitTime						查找超时时间
返回值：		成功返回 1，失败返回<=0。
说明：		预查询成功后，一次只能查找一个文件，可以不断查询直到文件查询结束
			返回值为 0 说明没有查询到，< 0 则查询错误，> 0 则查询到 1 个文件
*********************************************************************************/
NET_API int CALL_METHOD Net_FindOneFile(LLONG lLoginID, LLONG lFindHandle, P_STU_T_FILE lpFile, int nWaitTime = 3000);

/********************************************************************************
函数：		Net_FindMultiFiles
参数：		[in] lLoginID						设备登入句柄
			[in] lFindHandle					文件查找句柄（预查询文件获取）
			[in] nFileCount						需要查找的文件个数
			[out] lpFileList					查找到的文件列表
			[out] nRealFileCount				实际查找到的文件个数
			[in] nWaitTime						查找超时时间
返回值：		成功返回 TRUE，失败返回 FALSE。
说明：		预查询成功后才能调用
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_FindMultiFiles(LLONG lLoginID, LLONG lFindHandle, 
	int nFileCount, STU_T_FILE* lpFileList, int * pnRealFileCount, int nWaitTime = 10000);

/********************************************************************************
函数：		Net_CloseFindFile

参数：		[in] lLoginID						设备登入句柄
			[in] lFindHandle					文件查询句柄
返回值：		成功返回TRUE，失败返回FALSE。
说明：		终止查找文件
			与 NET_PreFindFile 接口配套使用
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_CloseFindFile(LLONG lLoginID, LLONG lFindHandle, int nWaitTime = 3000);

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
函数：		Net_PlayBackByRecordFile
参数：		[in] lLoginID					设备登入句柄
			[in] lpRecordFile				录像文件
			[in] hWnd						播放窗口句柄
			[in] cdDownLoadPos				录像回放进度回调
			[in] dwPosUser					进度回调中的用户参数
			[in] fDataCB					录像回放数据回调
			[in] dwDataUser					数据回调中的用户参数
返回值：		成功返回网络录像回放句柄，失败返回 <= 0。
说明：		按文件方式回放
			网络录像回放成功后，需要调用关闭网络录像回放接口，达到闭环处理。
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_PlayBackByRecordFile(LLONG lLoginID, P_STU_T_FILE lpRecordFile, 
	HWND hWnd, fLoadPosCallBack cbDownLoadPos, LDWORD dwPosUser, fPlaybackDataCallBack fDataCB, LDWORD dwDataUser);

/********************************************************************************
函数：		Net_SeekPlayBackByTime
参数：		[in] lPlayHandle				网络录像回放句柄
			[in] pstTime					定位的时间点（须在起始时间和结束时间之间）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		定位录像回放起始点
*********************************************************************************/ 
NET_API BOOL CALL_METHOD Net_SeekPlayBackByTime(LLONG lPlayHandle, STU_TIME* pstTime);

/********************************************************************************
函数：		Net_SeekPlayBack
参数：		[in] lPlayHandle				网络录像回放句柄
			[in] nOffsetTime				偏移时间（单位：秒/s）
			[in] nOffsetByte				偏移字节（单位：字节/Byte）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		定位录像回放起始点
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_SeekPlayBack(LLONG lPlayHandle, unsigned int nOffsetTime, unsigned int nOffsetByte);

/********************************************************************************
函数：		Net_PausePlayBack
参数：		[in] lPlayHandle				网络录像回放句柄
			[in] bPause						是否暂停，TRUE 暂停，FALSE 播放
返回值：		成功返回TRUE，失败返回FALSE。
说明：		暂停或恢复录像回放
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_PausePlayBack(LLONG lPlayHandle, BOOL bPause);

/********************************************************************************
函数：		Net_FastPlayBack
参数：		[in] lPlayHandle				网络录像回放句柄
返回值：		成功返回TRUE，失败返回FALSE。
说明：		快进录像回放
			网络录像的快放效果受到终端性能和带宽影响，快放速度最优范围[1-8]
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_FastPlayBack(LLONG lPlayHandle);

/********************************************************************************
函数：		Net_SlowPlayBack
参数：		[in] lPlayHandle				网络录像回放句柄
返回值：		成功返回TRUE，失败返回FALSE。
说明：		慢进录像回放
			每调用一次播放速度减半，慢放速度最优范围【1/8 – 1】
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_SlowPlayBack(LLONG lPlayHandle);

/********************************************************************************
函数：		Net_StepPlayBack
参数：		[in] lPlayHandle				网络录像回放句柄
			[in] bStop						是否停止单步跟踪
返回值：		成功返回TRUE，失败返回FALSE。
说明：		步进录像回放
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StepPlayBack(LLONG lPlayHandle, BOOL bStop);

/********************************************************************************
函数：		Net_NormalPlayBack
参数：		[in] lPlayHandle				网络录像回放句柄
返回值：		成功返回TRUE，失败返回FALSE。
说明：		恢复正常回放速度
			调用该接口后，播放速度恢复正常
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_NormalPlayBack(LLONG lPlayHandle);

/********************************************************************************
函数：		Net_StopPlayBack(LLONG lPlayHandle)
参数：		[in] lPlayHandle				网络录像回放句柄
返回值：		成功返回TRUE，失败返回FALSE。
说明：		停止录像回放
			与按文件网络放回接口配套使用，达到闭环处理
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StopPlayBack(LLONG lPlayHandle);

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
函数：		Net_RebootDevice
参数：		[in] lLoginID					设备登入句柄
返回值：		成功返回TRUE，失败返回FALSE。
说明：		重启设备
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_RebootDevice(LLONG lLoginID);

/********************************************************************************
函数：		Net_ResetDevice
参数：		[in] lLoginID					设备登入句柄
返回值：		成功返回TRUE，失败返回FALSE。
说明：		恢复出厂设置
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_ResetDevice(LLONG lLoginID);

/********************************************************************************
函数：		Net_ActivateDevice(暂不启用)
参数：		[in] stActivateInfo				激活参数
			[in] lpszLocalIp				指定发送网卡 IP
			[in] nWaitTime					响应超时时间（单位 ms）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		UDP单播/组播激活设备
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_ActivateDevice(STU_DEVICE_ACTIVATE_INFO* stActivateInfo, char* lpszLocalIp = NULL, int nWaitTime = 3000);

/********************************************************************************
函数：		Net_ModifyDevice(暂不启用)
参数：		[in] pModifyInfo				网络修改参数
			[in] lpszLocalIp				指定发送网卡 IP
			[in] nWaitTime					响应超时时间（单位 ms）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		修改设备网络参数
*********************************************************************************/ 
NET_API BOOL CALL_METHOD Net_ModifyDevice(STU_DEVICE_NETCFG_MODIFY_INFO *pModifyInfo, char* lpszLocalIp = NULL, int nWaitTime = 3000);

/********************************************************************************
函数：		使能设备 telnet
参数：		[in] bEnable					是否使能 telnet
			[in] lpszDstIp					目的 IP
			[in] lpszLocalIp				本地 IP
			[in] nWaitTime					超时时间
返回值：		成功返回TRUE，失败返回FALSE
说明：		修改设备网络参数
*********************************************************************************/ 
NET_API BOOL CALL_METHOD Net_SetDeviceTelnet(BOOL bEnable, char* lpszDstIp, char* lpszLocalIp = NULL, int nWaitTime = 3000);

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
函数：		Net_GetDeviceCaps
参数：		[in] lLoginID					设备登录句柄
			[in] dwCommand					设备能力命令类型
			[in] nChannel					设备通道号(从 0 开始, 0 表示通道 1；-1 表示不使用通道)
			[out] lpOutBuffer				能力输出信息（对应命令类型的结构体）
			[in] dwOutBufferSize			能力输出信息大小
			[in] nWaitTime					响应超时时间（单位 ms）
返回值：	成功返回TRUE，失败返回FALSE。
说明：		查询能力信息
*********************************************************************************/ 
NET_API BOOL CALL_METHOD Net_GetDeviceCaps(LLONG lLoginID, EM_DEVICE_CAPS_TYPE emType, LONG nChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, int nWaitTime = 2000);

/********************************************************************************
函数：		Net_GetDeviceCfg
参数：		[in] lLoginID					设备登录句柄
			[in] dwCommand					设备配置命令类型
			[in] nChannel					设备通道号(从 0 开始, 0 表示通道 1；-1 表示不使用通道)
			[out] lpOutBuffer				配置输出信息（对应命令类型的结构体）
			[in] dwOutBufferSize			配置输出信息大小
			[in] nWaitTime					响应超时时间（单位 ms）
返回值：	成功返回TRUE，失败返回FALSE。
说明：		查询配置信息
*********************************************************************************/ 
NET_API BOOL CALL_METHOD Net_GetDeviceCfg(LLONG lLoginID, DWORD dwCommand, LONG nChannel, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned, int nWaitTime = 2000);

/********************************************************************************
函数：		Net_SetDeviceCfg
参数：		[in] lLoginID					设备登录句柄
			[in] dwCommand					设备配置命令类型
			[in] nChannel					设备通道号(从 0 开始, 0 表示通道 1；-1 表示不使用通道)
			[in] lpInBuffer					配置输入信息（对应命令类型的结构体）
			[in] dwInBufferSize				配置输入信息大小
			[in] nWaitTime					响应超时时间（单位 ms）
返回值：	成功返回TRUE，失败返回FALSE。
说明：		设置配置信息
*********************************************************************************/ 
NET_API BOOL CALL_METHOD Net_SetDeviceCfg(LLONG lLoginID, DWORD dwCommand, LONG nChannel, LPVOID lpInBuffer, DWORD dwInBufferSize, int nWaitTime = 2000);

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
函数：		Net_SetDeviceCfg
参数：		[in] lLoginID					设备登录句柄
			[out] pSysInfo					设备系统信息
			[in] nWaitTime					响应超时时间（单位 ms）
返回值：	成功返回TRUE，失败返回FALSE。
说明：		获取设备系统信息
*********************************************************************************/ 
NET_API BOOL CALL_METHOD Net_GetSysInfo(LLONG lLoginID, STU_SYS_INFO* pSysInfo, int nWaitTime = 2000);

/********************************************************************************
函数：		Net_GetSpecifiedSysInfo
参数：		[in] lLoginID					设备登录句柄
			[in] nType						指定设备系统信息类型
											0 - 系统所有信息 对应 STU_SYS_INFO 结构体
											1 - 系统设备信息 对应 STU_SYS_DEVICE_INFO 结构体
											2 - 系统软件版本信息 对应 STU_SYS_SOFTWARE_VERSION 结构体
											3 - 系统硬件版本信息 对应 STU_SYS_HARDWARE_VERSION 结构体
											4 - 系统处理器信息 对应 STU_SYS_PROCESSOR_INFO 结构体
											5 - 系统内存信息 对应 STU_SYS_MEMORY_INFO 结构体
			[out] pSysInfo					指定的设备系统信息
			[in] nSysInfoSize				指定的设备系统信息大小
			[in] nWaitTime					响应超时时间（单位 ms）
返回值：	成功返回TRUE，失败返回FALSE。
说明：		获取指定的设备系统信息
*********************************************************************************/ 
NET_API	BOOL CALL_METHOD Net_GetSpecifiedSysInfo(LLONG lLoginID, int nType, void* pSysInfo, int nSysInfoSize, int nWaitTime = 2000);

/********************************************************************************
函数：		Net_GetSerialNumber
参数：		[in] lLoginID					设备登入句柄
			[out] lpszSerialNumber			设备序列号
			[in] nSize						序列号字符数组大小
			[in] nWaitTime					超时时间 (ms)
返回值：	成功返回TRUE，失败返回FALSE。
说明：		获取设备序列号
*********************************************************************************/ 
NET_API BOOL CALL_METHOD Net_GetSerialNumber(LLONG lLoginID, char* lpszSerialNumber, int nMaxSize, int nWaitTime = 1500);

/********************************************************************************
函数：		Net_GetDeviceTime
参数：		[in] lLoginID					设备登入句柄
			[out] pDeviceTime				设备时间
			[in] nWaitTime					超时时间 (ms)
返回值：	成功返回TRUE，失败返回FALSE。
说明：		获取设备当前时间
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_GetDeviceTime(LLONG lLoginID, STU_TIME* pDeviceTime, int nWaitTime = 1500);

/********************************************************************************
函数：		Net_SetDeviceTime
参数：		[in] lLoginID					设备登入句柄
			[in] pDeviceTime				需同步的设备时间
			[in] nWaitTime					超时时间 (ms)
返回值：	成功返回TRUE，失败返回FALSE。
说明：		同步设备时间
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_SetDeviceTime(LLONG lLoginID, STU_TIME* pDeviceTime, int nWaitTime = 1500);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 用户管理

/********************************************************************************
函数：		Net_GetDeviceUser
参数：		[in] lLoginID					设备登录句柄
			[out] cfgList					用户信息列表
			[in] nWaitTime					超时时间，单位：ms
返回值：		成功返回TRUE,失败返回FALSE
说明：		获取用户信息
*********************************************************************************/  
NET_API BOOL CALL_METHOD Net_GetDeviceUser(LLONG lLoginID, STU_CFG_USER_GET * cfgList, int nWaitTime);

/********************************************************************************
函数：		Net_AddDeviceUser
参数：		[in] lLoginID					设备登录句柄
			[out] cfgList					用户信息列表
			[in] nWaitTime					超时时间，单位：ms
返回值：		成功返回TRUE,失败返回FALSE
说明：		添加用户信息
*********************************************************************************/  
NET_API BOOL CALL_METHOD Net_AddDeviceUser(LLONG lLoginID, STU_CFG_ADD_USER * cfgList, int nWaitTime);

/********************************************************************************
函数：		Net_DeleteDeviceUser
参数：		[in] lLoginID					设备登录句柄
			[out] cfgList					用户信息列表
			[in] nWaitTime					超时时间，单位：ms
返回值：		成功返回TRUE,失败返回FALSE
说明：		删除用户信息
*********************************************************************************/  
NET_API BOOL CALL_METHOD Net_DeleteDeviceUser(LLONG lLoginID, STU_CFG_DELETE_USER * cfgList, int nWaitTime);

/********************************************************************************
函数：		Net_ModifyDeviceUser
参数：		[in] lLoginID					设备登录句柄
			[out] cfgList					用户信息列表
			[in] nWaitTime					超时时间，单位：ms
返回值：		成功返回TRUE,失败返回FALSE
说明：		修改用户信息
*********************************************************************************/  
NET_API BOOL CALL_METHOD Net_ModifyDeviceUser(LLONG lLoginID, STU_CFG_MODIFY_USER * cfgList, int nWaitTime);

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
函数：		Net_StartUpgrade
参数：		[in] lLoginID							设备登入句柄
			[in] lspzFileName						升级文件的绝对路径
			[in] fUpgradeCB							升级回调函数
			[in] dwUser								用户数据
返回值：		成功返回设备远程升级句柄，失败返回值 <= 0。
说明：		开始升级设备程序
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_StartUpgrade(LLONG lLoginID, char *lspzFileName, fDeviceUpgradeCallBack fUpgradeCB, LDWORD dwUser, int nWaitTime = 30 * 1000);

/********************************************************************************
函数：		Net_SendUpgrade(LLONG lUpgradeID)
参数：		[in] lUpgradeID							设备远程升级句柄
返回值：	成功返回TRUE，失败返回FALSE。
说明：		发送数据
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_SendUpgrade(LLONG lUpgradeID);

/********************************************************************************
函数：		Net_SendUpgrade(LLONG lUpgradeID)
参数：		[in] lUpgradeID							设备远程升级句柄
返回值：	成功返回TRUE，失败返回FALSE。
说明：		结束升级设备程序
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StopUpgrade(LLONG lUpgradeID);

/********************************************************************************
函数：		Net_UpgradeProgress(LLONG lUpgradeID)
参数：		[in] lLoginID							设备登录句柄
			[out] pstProgressInfo					进度信息
			[in] nWaitTime							响应超时时间(ms)
返回值：	成功返回TRUE，失败返回FALSE。
说明：		获取设备端升级进度（数据传输完成后设备的处理进度）
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_UpgradeProgress(LLONG lLoginID, STU_UPGRADE_PROGRESS_INFO* pstProgressInfo, int nWaitTime = 2000);

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
函数：		Net_ImportConfigFile
参数：		[in] lLoginID							设备登入句柄
			[in] szFileName							导入配置文件的绝对路径
			[in] cbUploadPos						导入配置文件进度回调
			[in] dwUser								用户数据
返回值：		成功返回导入配置句柄，失败返回值<=0。
说明：		导入配置文件
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_ImportConfigFile(LLONG lLoginID, char *szFileName, fLoadPosCallBack cbUploadPos, LDWORD dwUserData);

/********************************************************************************
函数：		Net_StopImportCfgFile
参数：		[in] lImportHandle						设备配置导入句柄
返回值：	成功返回TRUE，失败返回FALSE。
说明：		停止导入配置文件
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StopImportCfgFile(LLONG lImportHandle);

/********************************************************************************
函数：		Net_ExportConfigFile
参数：		[in] lLoginID							设备登入句柄
			[in] emConfigFileType					配置文件类型
			[in] szSavedFilePath					导出配置文件的绝对路径
			[in] cbDownLoadPos						导出配置文件进度回调
			[in] dwUser								用户数据
返回值：		成功返回导出配置句柄，失败返回值<=0。
说明：		设备导出通用配置，参数 emConfigFileType = CONFIG_FILE_ALL
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_ExportConfigFile(LLONG lLoginID, EM_DEVICE_CONFIG_TYPE emConfigFileType, char *szSavedFilePath, fLoadPosCallBack cbDownLoadPos, LDWORD dwUserData);

/********************************************************************************
函数：		Net_StopExportCfgFile
参数：		[in] lExportHandle						设备配置导出句柄
返回值：	成功返回TRUE，失败返回FALSE。
说明：		停止导出配置文件
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StopExportCfgFile(LLONG lExportHandle);

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
函数：		Net_StartSearchDevices
参数：		[in] cbSearchDevices					设备搜索回调函数
			[in] pUserData							用户数据
			[in] szLocalIp							本地IP地址
返回值：		成功返回设备搜索句柄，失败返回值<=0。
说明：		异步搜索局域网内设备
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_StartSearchDevices(fSearchDevicesCallBack cbSearchDevices, void* pUserData, char* szLocalIp = NULL);

/********************************************************************************
函数：		Net_StopSearchDevices
参数：		[in] lSearchHandle						设备搜索句柄
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		停止异步搜索局域网内设备
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StopSearchDevices(LLONG lSearchHandle);

// 跨网段单播搜索设备
NET_API BOOL CALL_METHOD Net_SearchDevicesByIPs(STU_DEVICE_IP_SEARCH_INFO* pIpSearchInfo, fSearchDevicesCallBack cbSearchDevices, LDWORD dwUserData, char* lpszLocalIp, void* pReserved, int nWaitTime = 10 * 1000);

/********************************************************************************
函数：		Net_StartSearchDevicesByCondition
参数：		[in] pSearchCondition					搜索条件参数
			[in] cbSearchDevices					设备搜索回调函数
			[in] pUserData							用户数据参数
			[in] szLocalIp							本地IP地址
返回值：		成功返回设备搜索句柄，失败返回值<=0。
说明：		指定搜索条件搜索设备
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_StartSearchDevicesByCondition(STU_DEVICE_SEARCH_CONDITION_INFO* pSearchCondition, fSearchDevicesCallBack cbSearchDevices, void* pUserData, char* szLocalIp = NULL);


///////////////////////////////////////////////////////////////////////////////////////////////////////////
// 智能设备接口

/********************************************************************************
函数：		Net_RealLoadPicture
参数：		[in] lLoginID				设备登入句柄
			[in] nChannelID				订阅通道号
			[in] dwEventType			智能事件类型
			[in] nDataType				需设置的返回的数据类型
										-1 - 不返回数据；0-只返回智能信息；1-返回智能信息和图片数据
			[in] cbAnalyzeData			智能分析数据回调函数
			[in] dwUser				    用户数据
			[in] pReserved				预留位
返回值：		成功返回智能数据实时订阅句柄，失败返回值<=0。
说明：		单通道单事件订阅（支持所有事件订阅）
            用户可以多次调用 Net_RealLoadPicture 来订阅不同通道的不同事件，注意维护订阅句柄并主动释放
			实时上传智能分析数据，用户可以根据订阅的事件类型，获取设备的指定智能分析数据
			客户端直接对接设备时调用, 与 Net_StopLoadPicture 配合使用，闭环处理。
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_RealLoadPicture(
	LLONG lLoginID, 
	int nChannelID, 
	DWORD dwEventType,
	int nDataType, 
	fAnalyzeDataCallBack cbAnalyzerData, 
	LDWORD dwUser,
	void* pReserved);

/********************************************************************************
函数：		Net_RealLoadMultiTypePicture
参数：		[in] lLoginID				设备登入句柄
			[in] nChannelIDArr			订阅通道号数组
			[in] nChannelNum			订阅通道号数目（必须与通道号数组元素个数一致）
			[in] dwEventTypeArr			智能事件类型数组
			[in] nEventTypeNum			智能事件类型数目（必须与智能事件类型数组元素个数一致）
			[in] nDataType				需设置的返回的数据类型
										-1 - 不返回数据；0-只返回智能信息；1-返回智能信息和图片数据
			[in] cbAnalyzeData			智能分析数据回调函数
			[in] dwUser				    用户数据
			[in] pReserved				预留位
返回值：		成功返回智能数据实时订阅句柄，失败返回值<=0。
说明：		多通道多事件订阅
			如果需要订阅所有事件建议使用 Net_RealLoadPicture，事件类型选择 EVENT_SP_ALL
			实时上传智能分析数据，用户可以根据订阅的事件类型，获取设备的指定智能分析数据	
			客户端直接对接设备时调用, 与 Net_StopLoadPicture 配合使用，闭环处理。
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_RealLoadMultiTypePicture(
	LLONG lLoginID, 
	int* nChannelIDArr,
	int nChannelNum, 
	DWORD* dwEventTypeArr, 
	int nEventTypeNum, 
	int nDataType, 
	fAnalyzeDataCallBack cbAnalyzeData,
	LDWORD dwUser, 
	void* pReserved);

/********************************************************************************
函数：		Net_RealLoadPicture
参数：		[in] lLoginID				设备登入句柄
			[in] nChannelID				订阅通道号
			[in] dwEventType			智能事件类型
			[in] nDataType				需设置的返回的数据类型
										-1 - 不返回数据；0-只返回智能信息；1-返回智能信息和图片数据
			[in] cbAnalyzeData			智能分析数据回调函数
			[in] dwUser				    用户数据
			[in] pReserved				预留位
返回值：		成功返回智能数据实时订阅句柄，失败返回值<=0。
说明：		单通道单事件订阅（支持所有事件订阅）
            用户可以多次调用 Net_LoadOfflinePicture 来订阅不同通道的不同事件，注意维护订阅句柄并主动释放
			实时上传智能分析数据，用户可以根据订阅的事件类型，获取设备的指定智能分析数据
			客户端直接对接设备时调用, 与 Net_StopLoadPicture 配合使用，闭环处理。
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_LoadOfflinePicture(
	LLONG lLoginID, 
	int nChannelID, 
	DWORD dwEventType,
	int nDataType, 
	fAnalyzeDataCallBack cbAnalyzerData, 
	LDWORD dwUser,
	void* pReserved);

/********************************************************************************
函数：		Net_StopLoadPicture
参数：		[in] lLoadHandle			智能数据订阅句柄
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		停止上传智能分析数据(智能信息&图片数据)
			与 Net_RealLoadPicture/Net_LoadOfflinePicture 配合使用，闭环处理。
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StopLoadPicture(LLONG lLoadHandle);

/********************************************************************************
函数：		Net_StartRecvNetPicStream
参数：		[in] lLoginID					设备登录句柄
			[in] pstNetPicParam				图片订阅参数
			[in] nParamSize					图片订阅参数大小
			[out] pRecvHandle				图片流接收句柄
			[in] bLoadSingle				是否单张上图
											如果是单张上图，fNetPicStreamCallBackCV1 回调中
											图片数据始终只有一张背景图或人脸抠图
											当设备端配置不抓取背景图时，bLoadSingle 必须是 TRUE
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		开始实时上传智能分析数据（包括图片）
			客户端直接对接设备时调用, 仅订阅人脸检测背景图和人脸抠图
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StartRecvNetPicStream(LLONG lLoginID, 
	NetPicParamCV1* pstNetPicParam, 
	int nParamSize, 
	LLONG* pRecvHandle, 
	BOOL bLoadSingle = FALSE);

/********************************************************************************
函数：		Net_StopRecvNetPicStream
参数：		[in] lRecvHandle				图片流接收句柄
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		停止实时订阅图片，与 Net_StartRecvNetPicStream 配合使用，闭环处理。
            客户端直接对接设备时调用
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StopRecvNetPicStream(LLONG lRecvHandle);

/********************************************************************************
函数：		Net_StartRecvNetPicStreamByCloud
参数：		[in] lLoginID					设备登录句柄
			[in] pstNetPicParam				图片订阅参数
			[in] nParamSize					图片订阅参数大小
			[out] pRecvHandle				图片流接收句柄
			[in] bLoadSingle				是否单张上图
											如果是单张上图，fNetPicStreamCallBackCV1 回调中
											图片数据始终只有一张背景图或人脸抠图
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		开始实时上传智能分析数据（包括图片）
			客户端通过云服务对接设备时调用，仅订阅人脸检测背景图和人脸抠图
			调用成功之后设备抓图配置中会开启显示背景图
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StartRecvNetPicStreamByCloud(LLONG lLoginID, 
	NetPicParamCV1* pstNetPicParam,
	int nParamSize, 
	LLONG* pRecvHandle, 
	BOOL bLoadSingle = FALSE);

/********************************************************************************
函数：		Net_StopRecvNetPicStreamByCloud
参数：		[in] lRecvHandle				图片流接收句柄
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		停止实时订阅图片，与 Net_StartRecvNetPicStreamByCloud 配合使用，闭环处理。
            客户端通过云服务对接设备时调用
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StopRecvNetPicStreamByCloud(LLONG lRecvHandle);

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
函数：		Net_DownLoadMultiFile
参数：		[in] lLoginID					设备登入句柄
			[in] pstInParam					多文件下载输入参数
			[out] pstOutParam				多文件下载输出参数
			[in] nWaitTime					超时等待时间（单位： ms）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		批量下载文件
			与Net_ StopLoadMultiFile配套使用；
			输出参数中带有多文件下载句柄，在关闭句柄时使用
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_DownLoadMultiFile(LLONG lLoginID, STU_IN_MULTI_FILE_DOWNLOAD_PARAM *pstInParam, STU_OUT_MULTI_FILE_DOWNLOAD_PARAM *pstOutParam, int waittime = 5000);

/********************************************************************************
函数：		Net_StopLoadMultiFile
参数：		[in] lDownLoadHandle			文件下载句柄
返回值：		成功返回TRUE，失败返回FALSE。
说明：		停止下载
			与Net_DownLoadMultiFile配套使用
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StopLoadMultiFile(LLONG lDownLoadHandle);

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
函数：		Net_TransJsonByRpc
参数：		[in] lLoginID					设备登入句柄
			[in] szInBuffer					设备配置输入信息（Json格式）
			[in] dwInBufferSize				配置输入信息大小
			[in] szOutBuffer				配置后应答信息（Json格式）
			[in] dwOutBufferSize			应答信息大小
			[in] pReserved					预留参数
			[in] nWaitTime					数据发送超时时间 (ms)
返回值：		成功返回TRUE，失败返回FALSE。
说明：		以JSON 格式的协议进行设备配置
			用户可以根据配置要求对设备进行配置
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_TransJsonByRpc(
	LLONG lLoginID, 
	char* szInBuffer, 
	DWORD dwInBufferSize, 
	char* szOutBuffer, 
	DWORD dwOutBufferSize, 
	void* pReserved,
	int nWaitTime = 6000);

/********************************************************************************
函数：		Net_TransDataByRpc
参数：		[in] lLoginID					设备登入句柄
			[in] szInBuffer					设备配置输入信息（Json格式）
			[in] dwInBufferSize				配置输入信息大小
			[in] szOutBuffer				配置后应答信息（Json格式）
			[in] dwOutBufferSize			应答信息大小
			[in] pReserved					预留参数
			[in] nWaitTime					数据发送超时时间 (ms)
			[in] pBinData					二进制数据			
			[out] pRetJsonLen				返回的Json数据长度
			[out] pRetBinLen				返回的二进制数据长度
返回值：		成功返回TRUE，失败返回FALSE。
说明：		以JSON 格式的协议进行设备配置
			用户可以根据配置要求对设备进行配置
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_TransDataByRpc(
	LLONG lLoginID, 
	char* szInBuffer, 
	DWORD dwInBufferSize, 
	char* szOutBuffer, 
	DWORD dwOutBufferSize, 
	void* pReserved,
	int nWaitTime = 6000,
	STU_BIN_DATA* pBinData = NULL, 
	int* pRetJsonLen = NULL, 
	int* pRetBinLen = NULL);

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// 主动注册接口

/********************************************************************************
函数：		Net_RegStartServer（暂不支持）
参数：		[in] lpszIP						侦听 IP 地址
			[in] nPort						侦听端口
			[in] cbListen					侦听服务器回调函数
			[in] dwUserData					用户数据参数
返回值：		成功返回侦听服务器句柄（>0），失败返回 0。
说明：		主动注册功能，启动服务
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_RegStartServer(
	char* lpszIP,
	WORD nPort, 
	fRegServerCallBack cbListen, 
	LDWORD dwUserData);

/********************************************************************************
函数：		Net_RegStopServer（暂不支持）
参数：		[in] lServerHandle				侦听服务器句柄
返回值：		成功返回TRUE，失败返回FALSE。
说明：		主动注册功能，停止服务
*********************************************************************************/ 
NET_API BOOL CALL_METHOD Net_RegStopServer(LLONG lServerHandle);

/********************************************************************************
函数：		Net_RegAccept（暂不支持）
参数：		[in] lpszDevSerial
			[in] lpszIP
			[in] nPort
			[in] bAccept
返回值：		成功返回TRUE，失败返回FALSE。
说明：		主动注册功能，响应设备的注册请求
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_RegAccept(char* lpszDevSerial, char* lpszIP, WORD nPort, BOOL bAccept);

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// 人脸库 & 人脸操作

/********************************************************************************
函数：		Net_CreateFaceGroup
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_FACE_GROUP_CREATE_IN_PARAM）
			[out] pOutParam					输出参数	（见 STU_FACE_GROUP_CREATE_OUT_PARAM）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		创建人脸组
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_CreateFaceGroup(LLONG lLoginID, STU_FACE_GROUP_CREATE_IN_PARAM* pInParam, STU_FACE_GROUP_CREATE_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_DeleteFaceGroup
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_FACE_GROUP_DELETE_IN_PARAM）
			[out] pOutParam					输出参数	（见 STU_FACE_GROUP_DELETE_OUT_PARAM）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		删除人脸组
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_DeleteFaceGroup(LLONG lLoginID, STU_FACE_GROUP_DELETE_IN_PARAM* pInParam, STU_FACE_GROUP_DELETE_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_EditFaceGroup
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_FACE_GROUP_EDIT_IN_PARAM）
			[out] pOutParam					输出参数	（见 STU_FACE_GROUP_EDIT_OUT_PARAM）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		编辑人脸组
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_EditFaceGroup(LLONG lLoginID, STU_FACE_GROUP_EDIT_IN_PARAM* pInParam, STU_FACE_GROUP_EDIT_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_GetAllFaceGroups
参数：		[in] lLoginID					设备登录句柄
			[out] pOutParam					输出参数	（见 STU_FACE_GROUP_ARRAY_INFO）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		获取所有人脸组信息
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_GetAllFaceGroups(LLONG lLoginID, STU_FACE_GROUP_ARRAY_INFO* pOutInfo);

////////////////////////////////////////////////////////

/********************************************************************************
函数：		Net_AddPersonInfo
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_FACE_ADD_IN_PARAM）
			[out] pOutParam					输出参数	（见 STU_FACE_ADD_OUT_PARAM）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		添加人员信息&人员人脸图
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_AddPersonInfo(LLONG lLoginID, 
	STU_FACE_ADD_IN_PARAM* pInParam, STU_FACE_ADD_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_AddPersonInfoOnly
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_PERSON_INFO_ADD_IN_PARAM）
			[out] pOutParam					输出参数	（见 STU_PERSON_INFO_ADD_OUT_PARAM）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		仅添加人员信息
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_AddPersonInfoOnly(LLONG lLoginID, 
	STU_PERSON_INFO_ADD_IN_PARAM* pInParam, STU_PERSON_INFO_ADD_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_UpdatePersonInfo
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_PERSON_INFO_UPDATE_IN_PARAM）
			[out] pOutParam					输出参数	（见 STU_PERSON_INFO_UPDATE_OUT_PARAM）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		更新人员信息
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_UpdatePersonInfo(LLONG lLoginID, 
	STU_PERSON_INFO_UPDATE_IN_PARAM* pInParam, STU_PERSON_INFO_UPDATE_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_DeletePersonInfo
参数：		[in] lLoginID					设备登录句柄
			[in] nPersonID					人员ID		
返回值：		成功返回TRUE，失败返回FALSE。
说明：		删除人员信息
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_DeletePersonInfo(LLONG lLoginID, unsigned int nPersonID);

/********************************************************************************
函数：		Net_AddPersonFaceImage
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_FACE_IMAGE_ADD_IN_PARAM）
			[out] pOutParam					输出参数	（见 STU_FACE_IMAGE_ADD_OUT_PARAM）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		添加人员人脸图
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_AddPersonFaceImage(LLONG lLoginID, 
	STU_FACE_IMAGE_ADD_IN_PARAM* pInParam, STU_FACE_IMAGE_ADD_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_DeletePersonFaceImage
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_FACE_IMAGE_DELETE_IN_PARAM）
			[out] pOutParam					输出参数	（见 STU_FACE_IMAGE_DELETE_OUT_PARAM）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		删除人员人脸图
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_DeletePersonFaceImage(LLONG lLoginID, 
	STU_FACE_IMAGE_DELETE_IN_PARAM* pInParam, STU_FACE_IMAGE_DELETE_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_UpdatePersonFaceImage
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_FACE_IMAGE_UPDATE_IN_PARAM）
			[out] pOutParam					输出参数	（见 STU_FACE_IMAGE_UPDATE_OUT_PARAM）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		更新人员人脸图
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_UpdatePersonFaceImage(LLONG lLoginID, 
	STU_FACE_IMAGE_UPDATE_IN_PARAM* pInParam, STU_FACE_IMAGE_UPDATE_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_BindFaceToGroup
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_FACE_BIND_GROUP_IN_PARAM）
			[out] pOutParam					输出参数	（见 STU_FACE_BIND_GROUP_OUT_PARAM）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		人员人脸图绑定到人脸组
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_BindFaceToGroup(LLONG lLoginID, 
	STU_FACE_BIND_GROUP_IN_PARAM* pInParam, STU_FACE_BIND_GROUP_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_UnBindFaceFromGroup
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_FACE_UNBIND_GROUP_IN_PARAM）
			[out] pOutParam					输出参数	（见 STU_FACE_UNBIND_GROUP_OUT_PARAM）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		人员人脸图从人脸组解绑
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_UnBindFaceFromGroup(LLONG lLoginID, 
	STU_FACE_UNBIND_GROUP_IN_PARAM* pInParam, STU_FACE_UNBIND_GROUP_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_AsyncAddPersonInfo
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_FACE_ADD_IN_PARAM）
			[out] pOutParam					输出参数	（见 STU_FACE_ADD_OUT_PARAM）
返回值：		成功返回TRUE，失败返回FALSE。
说明：		异步添加人员信息&人员人脸图（只添加到设备，不建模）
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_AsyncAddPersonInfo(LLONG lLoginID,
	STU_FACE_ADD_IN_PARAM* pInParam, STU_FACE_ADD_OUT_PARAM* pOutParam);

////////////////////////////////////////////////////////
// 人脸信息查找操作

/********************************************************************************
函数：		Net_PreFindFaceInfo
参数：		[in] lLoginID					设备登录句柄
			[out] pnFindInstance			人脸查找实例
返回值：		成功返回TRUE,失败返回FALSE
说明：		预开始查找人脸信息，成功后可以执行查找人脸信息操作
            与 Net_CloseFindFaceInfo 配对使用
*********************************************************************************/ 
NET_API BOOL CALL_METHOD Net_PreFindFaceInfo(LLONG lLoginID, unsigned int * pnFindInstance);

/********************************************************************************
函数：		Net_CloseFindFaceInfo
参数：		[in] lLoginID					设备登录句柄

返回值：		成功返回TRUE,失败返回FALSE
说明：		终止查找人脸信息，成功后人脸查找句柄无效。
            必须与 Net_PreFindFaceInfo 配对使用
*********************************************************************************/ 
NET_API BOOL CALL_METHOD Net_CloseFindFaceInfo(LLONG lLoginID, unsigned int nFindInstance);

/********************************************************************************
函数：		Net_StartFindFaceInfo
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_FACE_UNBIND_GROUP_IN_PARAM）
			[out] pOutParam					输出参数	（见 STU_FACE_UNBIND_GROUP_OUT_PARAM）
											输出参数中 nFindHandle 即是人脸信息查找句柄 
返回值：		成功返回TRUE,失败返回FALSE
说明：		开始查找人脸信息; Net_PreFindFaceInfo 预查询成功后可以调用
*********************************************************************************/ 
NET_API BOOL CALL_METHOD Net_StartFindFaceInfo(LLONG lLoginID, STU_FACE_INFO_FIND_IN_PARAM* pInParam, STU_FACE_INFO_FIND_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_GetFaceInfoFindResult
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_FACE_INFO_FIND_RESULT_IN_PARAM）
			[out] pOutParam					输出参数	（见 STU_FACE_INFO_FIND_RESULT_OUT_PARAM）
返回值：		成功返回TRUE,失败返回FALSE
说明：		获取查找的人脸信息；Net_StartFindFaceInfo 查询成功后可以调用
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_GetFaceInfoFindResult(LLONG lLoginID,
	STU_FACE_INFO_FIND_RESULT_IN_PARAM* pInParam, STU_FACE_INFO_FIND_RESULT_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_GetPersonCount
参数：		[in] lLoginID					设备登录句柄
			[in] nFindInstance				人脸查找实例
			[out] pnPersonCount				查询到的人员数目
返回值：		成功返回TRUE,失败返回FALSE
说明：		获取当前查询条件下的人员数目；Net_StartFindFaceInfo 查询成功后可以调用
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_GetPersonCount(LLONG lLoginID, unsigned int nFindInstance, int* pnPersonCount);

/********************************************************************************
函数：		Net_GetFaceCount
参数：		[in] lLoginID					设备登录句柄
			[in] nFindInstance				人脸查找实例
			[out] pnFaceCount				查询到的人脸数目
返回值：		成功返回TRUE,失败返回FALSE
说明：		获取当前查询条件下的人脸数目；Net_StartFindFaceInfo 查询成功后可以调用
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_GetFaceCount(LLONG lLoginID, unsigned int nFindInstance, int* pnFaceCount);

/********************************************************************************
函数：		Net_GetFaceImage
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_FACE_IMAGE_GET_IN_PARAM）
			[out] pOutParam					输入参数（见 STU_FACE_IMAGE_GET_OUT_PARAM）
返回值：		成功返回TRUE,失败返回FALSE
说明：		获取人脸图片并保存到本地；Net_PreFindFaceInfo 预查询成功后可以调用
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_GetFaceImage(LLONG lLoginID,
	STU_FACE_IMAGE_GET_IN_PARAM *pInParam, STU_FACE_IMAGE_GET_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_GetPersonInfoByToken
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_PERSON_INFO_GET_BYTOKEN_IN_PARAM）
			[out] pOutParam					输入参数（见 STU_PERSON_INFO_GET_BYTOKEN_OUT_PARAM）
返回值：		成功返回TRUE,失败返回FALSE
说明：		通过人脸图标识获取人脸信息；Net_PreFindFaceInfo 预查询成功后可以调用
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_GetPersonInfoByToken(LLONG lLoginID,
	STU_PERSON_INFO_GET_BYTOKEN_IN_PARAM *pInParam, STU_PERSON_INFO_GET_BYTOKEN_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_GetPeronInfoByID
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_PERSON_INFO_GET_BYID_IN_PARAM）
			[out] pOutParam					输入参数（见 STU_PERSON_INFO_GET_BYID_OUT_PARAM）
返回值：		成功返回TRUE,失败返回FALSE
说明：		通过人脸证件&ID获取人脸信息；Net_PreFindFaceInfo 预查询成功后可以调用
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_GetPersonInfoByID(LLONG lLoginID,
	STU_PERSON_INFO_GET_BYID_IN_PARAM* pInParam, STU_PERSON_INFO_GET_BYID_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_GetPeronInfoByID
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_FACE_IMAGE_INFO_GET_IN_PARAM）
			[out] pOutParam					输入参数（见 STU_FACE_IMAGE_INFO_GET_OUT_PARAM）
返回值：		成功返回TRUE,失败返回FALSE
说明：		获取人脸图信息；Net_PreFindFaceInfo 预查询成功后可以调用
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_GetFaceImageInfo(LLONG lLoginID,
	STU_FACE_IMAGE_INFO_GET_IN_PARAM* pInParam, STU_FACE_IMAGE_INFO_GET_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_CheckPersonNameSuffix
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_PERSON_NAME_CHECK_IN_PARAM）
			[out] pOutParam					输入参数（见 STU_PERSON_NAME_CHECK_OUT_PARAM）
返回值：		成功返回TRUE,失败返回FALSE
说明：		校验人名，并给出建议后缀；Net_PreFindFaceInfo 预查询成功后可以调用
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_CheckPersonNameSuffix(LLONG lLoginID,
	STU_PERSON_NAME_CHECK_IN_PARAM* pInParam, STU_PERSON_NAME_CHECK_OUT_PARAM* pOutParam);

////////////////////////////////////////////////////////
// 人脸识别记录

/********************************************************************************
函数：		Net_PreFindFaceRecognitionRecord
参数：		[in] lLoginID					设备登录句柄
			[out] pnFindInstance			查找实例
返回值：		成功返回TRUE,失败返回FALSE
说明：		预查询人脸比对记录
*********************************************************************************/ 
NET_API BOOL CALL_METHOD Net_PreFindFaceRecognitionRecord(LLONG lLoginID, unsigned int * pnFindInstance);

/********************************************************************************
函数：		Net_StartFindFaceRecognitionRecord
参数：		[in] lLoginID					设备登录句柄
			[in] pnFindInstance				查找实例
			[in] pInParam					输入参数（见 STU_FACE_REC_REC_FIND_IN_PARAM）
			[out] pOutParam					输出参数（见 STU_FACE_REC_REC_FIND_OUT_PARAM）
											输出参数中 nFindHandle 是人脸识别就查询句柄
返回值：		成功返回TRUE,失败返回FALSE
说明：		开始查询人脸比对记录
            Net_PreFindFaceRecognitionRecord 成功后可调用
*********************************************************************************/ 
NET_API BOOL CALL_METHOD Net_StartFindFaceRecognitionRecord(LLONG lLoginID,
	STU_FACE_REC_REC_FIND_IN_PARAM* pInParam, STU_FACE_REC_REC_FIND_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_CloseFindFaceRecognitionRecord
参数：		[in] lLoginID					设备登录句柄
			[in] nFindInstance			    记录查找句柄
返回值：		成功返回TRUE,失败返回FALSE
说明：		关闭查询人脸比对记录，与 Net_PreFindFaceRecognitionRecord 配对使用
            关闭后，人脸识别记录查找句柄无效
*********************************************************************************/ 
NET_API BOOL CALL_METHOD Net_CloseFindFaceRecognitionRecord(LLONG lLoginID, unsigned int nFindInstance);

/********************************************************************************
函数：		Net_GetFaceRecognitionRecordResult
参数：		[in] lLoginID					设备登录句柄
			[in] pInParam					输入参数（见 STU_FACE_REC_REC_FIND_RESULT_IN_PARAM）
			[out] pOutParam					输出参数（见 STU_FACE_REC_REC_FIND_RESULT_OUT_PARAM）
返回值：		成功返回TRUE,失败返回FALSE
说明：		获取人脸比对记录，Net_StartFindFaceRecognitionRecord 查询后可以调用
*********************************************************************************/ 
NET_API BOOL CALL_METHOD Net_GetFaceRecognitionRecordResult(LLONG lLoginID,
	STU_FACE_REC_REC_FIND_RESULT_IN_PARAM* pInParam, STU_FACE_REC_REC_FIND_RESULT_OUT_PARAM* pOutParam);

/********************************************************************************
函数：		Net_GetFaceRecognitionRecordCount
参数：		[in] lLoginID					设备登录句柄
			[out] pnRecordCount				人脸比对记录条数
返回值：		成功返回TRUE,失败返回FALSE
说明：		获取人脸比对记录条数，Net_StartFindFaceRecognitionRecord 查询后可以调用
*********************************************************************************/  
NET_API BOOL CALL_METHOD Net_GetFaceRecognitionRecordCount(LLONG lLoginID, unsigned int nFindInstance, unsigned int* pnRecordCount);

/********************************************************************************
函数：		Net_LoadFaceExtractInfo
参数：		[in] lLoginID							登录句柄
            [in] emType								操作类型
			[in] cbFaceExtInfo						信息回调
			[in] dwUser								用户参数	
返回值：		成功返回订阅句柄
说明：		开启建模并订阅人脸建模信息
			建模之前需要保证设备底库中有未建模的图片
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_StartLoadFaceExtractInfo(LLONG lLoginID, 
	EM_FACE_EXTRACT_OPERATE_TYPE emType, fFaceFeatureExtInfoCallBack cbFaceExtInfo, LDWORD dwUser);

/********************************************************************************
函数：		Net_StopLoadFaceExtractInfo
参数：		[in] lHandle							订阅句柄
返回值：		成功返回TRUE, 失败返回FALSE
说明：		停止订阅人脸建模信息
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StopLoadFaceExtractInfo(LLONG lHandle);

/********************************************************************************
函数：		Net_StartLoadCfgModifyInfo
参数：		[in] lLoginID							登录句柄
            [in] lpszCfgTable						配置表名称
			[in] cbCfgModifyInfo					信息回调
			[in] dwUser								用户参数	
返回值：		成功返回订阅句柄
说明：		开启配置改动信息订阅
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_StartLoadCfgModifyInfo(LLONG lLoginID, const char* lpszCfgTable, fCfgModifyInfoCallBack cbCfgModifyInfo, LDWORD dwUser);

/********************************************************************************
函数：		Net_StopLoadCfgModifyInfo
参数：		[in] lHandle							订阅句柄
返回值：		成功返回TRUE, 失败返回FALSE
说明：		停止配置改动信息订阅
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StopLoadCfgModifyInfo(LLONG lLoginID);

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
函数：		Net_StartEventSubscribe
参数：		[in] lLoginID							设备登入句柄
			[in] nChannelID							设备通道号
返回值：		成功返回报警句柄，失败返回 <= 0。
说明：		开启订阅，指定订阅回调函数
*********************************************************************************/
NET_API LLONG CALL_METHOD Net_StartEventSubscribe(LLONG lLoginID,
	fAlarmInfoCallBack cbAlarmInfo, LDWORD dwUser = 0, DWORD dwWaitTime = 3000);

/********************************************************************************
函数：		Net_EventSubscribe
参数：			
			[in] lAlarmHandle						报警句柄
			[in] nType								为EM_ALARM_TYPE枚举类型，取值为-1时，则订阅所有事件
			[in] nChannelID							设备通道号
返回值：		成功返回0，失败返回 < 0。
说明：		订阅eType所指定的单个报警事件类型
			该接口可以多次被调用，单次只能订阅一个报警事件或者所有报警事件
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_EventSubscribe(LLONG lAlarmHandle, int nChannelID, int nType, DWORD dwWaitTime = 3000);

/********************************************************************************
函数：		Net_UnEventSubscribe
参数：		[in] lAlarmHandle						报警句柄
			[in] nType								为EM_ALARM_TYPE枚举类型，取值为-1时，则取消订阅所有事件
			[in] nChannelID							设备通道号
			
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		取消事件订阅
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_UnEventSubscribe(LLONG lAlarmHandle, int nChannelID, int nType);
	
/********************************************************************************
函数：		Net_StopEventSubscribe
参数：		[in] lAlarmHandle						报警句柄
			
返回值：		成功返回TRUE，失败返回 FALSE。
说明：		停止事件订阅
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_StopEventSubscribe(LLONG lAlarmHandle);

///////////////////////////////////////////////////////////////////////////////////////////////////////////

/********************************************************************************
函数：		Net_ImageWaterMarkCheck
参数：		[in] lpszImagePath						本地图片路径
返回值：		成功返回TRUE, 失败返回FALSE
说明：		图片水印校验
*********************************************************************************/
NET_API BOOL CALL_METHOD Net_ImageWaterMarkCheck(const char* lpszImagePath);

///////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
}
#endif
#endif // _AL_NET_MANAGER_LIB_H