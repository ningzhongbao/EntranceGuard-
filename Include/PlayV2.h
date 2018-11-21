
/************************************************************************/
/* warning：本头文件仅供内部使用，不对外提供！！！	                                                            */
/************************************************************************/

#ifndef _AL_PLAY_V2_H
#define _AL_PLAY_V2_H

#include "PlayV1.h"

#ifdef	__cplusplus
extern "C" {
#endif

	////////////////////////////////////////////////////////////////////////////////////////////////
	#define MAX_PLAY_PORT_NUM				501					// 最大播放端口数目

	////////////////////////////////////////////////////////////////////////////////////////////////
	#define _DD_RAW_DATA_TYPE				0xFF				// 用于数据绘制的原始数据类型
	#define _DD_INTL_TYPE					0x63				// 数据绘制的智能数据类型
	#define _DD_MOTION_FULL					0x65				// 数据绘制的动检数据类型

	////////////////////////////////////////////////////////////////////////////////////////////////
	// 文件帧类型
	typedef enum
	{
		TYPE_PLAY_INFO_MOTION_DETECT = 1,
		TYPE_PLAY_INFO_EVENT = 2,
	}ENUM_PLAY_INFO_TYPE;

	// BMP图像类型
	typedef enum
	{
		IMAGE_TYPE_BMP32 = 0,
		IMAGE_TYPE_BMP24 = 1,
	}ENUM_BMP_IMAGE_TYPE;

	// 渲染类型
	typedef enum
	{
		TYPE_RENDER_NONE = 0,
		TYPE_RENDER_GDI,
		TYPE_RENDER_D3D,
		TYPE_RENDER_DDRAW,
		TYPE_RENDER_D3D_FAST = 5,
	}ENUM_TYPE_RENDER;

	// SVAC 层类型
 	typedef enum 
 	{
 		TYPE_SVAC_LAYER_BASE = 0x0001,
 		TYPE_SVAC_LAYER_ENHANCE = 0x0002,
 	}ENUM_SVAC_LAYER_TYPE;

	// 水印数据类型
	typedef enum
	{
		// 文字
		TYPE_WATERMARK_DATA_TEXT = 0,
		// JPEG或者BMP图片
		TYPE_WATERMARK_DATA_JPEG_BMP = 1,
		// 帧数据
		TYPE_WATERMARK_DATA_FRAMEDATA = 3,		
	}ENUM_TYPE_WATERMARK_DATA;

	// 帧信息改变类型
	typedef enum
	{
		// 帧率改变
		TYPE_MEDIACHANGE_FRAMERATE = 1,
		// 分辨率改变
		TYPE_MEDIACHANGE_RESOLUTION = 2,
	}ENUM_MEDIACHANGE_TYPE;	

	// 解码类型
	typedef enum 
	{
		TYPE_DECODE_NONE = 0,
		TYPE_DECODE_SW,
		TYPE_DECODE_HW,
		TYPE_DECODE_HW_FAST,
		TYPE_DECODE_MSDK
	}ENUM_DECODE_TYPE;

	// 鱼眼模式
	typedef enum 
	{
		// 无效模式
		ENUM_MODE_FISHEYE_INVALID = 0,
		// 顶装
		ENUM_MODE_FISHEYE_CEIL = 1,
		// 壁装
		ENUM_MODE_FISHEYE_WALL = 2,	
		// 地装
		ENUM_MODE_FISHEYE_FLOOR = 3,

		ENUM_MODE_FISHEYE_NUM
	}ENUM_MODE_FISHEYE;

	// 鱼眼校准类型
	typedef enum 
	{
		// 无效模式
		ENUM_FISHEYE_CALIBRATE_MODE_INVALID = 0,
		// 关闭模式
		ENUM_FISHEYE_CALIBRATE_MODE_OFF = 1,
		// 原始模式
		ENUM_FISHEYE_CALIBRATE_MODE_ORIGINAL = 2,
	}ENUM_FISHEYE_CALIBRATE_MODE;

	// 鱼眼云台命令
	typedef enum 
	{
		// 无效命令
		ENUM_FISHEYE_EPTZ_CMD_INVALID = 0,	
		// 放大
		ENUM_FISHEYE_EPTZ_CMD_ZOOM_IN = 1,
		// 缩小
		ENUM_FISHEYE_EPTZ_CMD_ZOOM_OUT,
		// 向上移动
		ENUM_FISHEYE_EPTZ_CMD_UP,
		// 向下移动
		ENUM_FISHEYE_EPTZ_CMD_DOWN,
		// 向左移动
		ENUM_FISHEYE_EPTZ_CMD_LEFT,
		// 向右移动
		ENUM_FISHEYE_EPTZ_CMD_RIGHT,
		// 自动顺时针旋转
		ENUM_FISHEYE_EPTZ_CMD_AUTO_ROTATE_CLOCKWISE,
		// 自动逆时针旋转
		ENUM_FISHEYE_EPTZ_CMD_AUTO_ROTATE_ANTICLOCKWISE,
		// 停止
		ENUM_FISHEYE_EPTZ_CMD_STOP,
		// 框选放大
		ENUM_FISHEYE_EPTZ_CMD_SHOW_REGION,
		// 退出框选放大
		ENUM_FISHEYE_EPTZ_CMD_EXIT_SHOW_REGION,
		// 圆旋转
		ENUM_FISHEYE_EPTZ_CMD_ORIGIN_ROTATE,
		// 恢复默认
		ENUM_FISHEYE_EPTZ_CMD_DEFAULT,

		ENUM_FISHEYE_EPTZ_CMD_NUM
	}ENUM_FISHEYE_EPTZ_CMD;

	// 格式化图片类型
	typedef enum
	{
		// BMP32类型
		TYPE_IMAGE_FORMAT_BMP_32 = 0,
		// BMP24类型
		TYPE_IMAGE_FORMAT_BMP_24,
		// TIFF类型
		TYPE_IMAGE_FORMAT_TIFF,
		// JPEG类型 100% 质量
		TYPE_IMAGE_FORMAT_JPEG_100,		
		// 80%质量的JPEG类型
		TYPE_IMAGE_FORMAT_JPEG_80,	
		// 60%质量的JPEG类型
		TYPE_IMAGE_FORMAT_JPEG_60,	
		// 40%质量的JPEG类型
		TYPE_IMAGE_FORMAT_JPEG_40,	
		// 20%质量的JPEG类型
		TYPE_IMAGE_FORMAT_JPEG_20,	
		// 10%质量的JPEG类型
		TYPE_IMAGE_FORMAT_JPEG_10,								
	}ENUM_IMAGE_FORMAT_TYPE;

	// 枪机类型
	typedef enum 
	{
		// 枪机类型
		CAMERA_TYPE_200W_FD			= 0,
	}ENUM_CAMERA_TYPE;

	// 镜头类型
	typedef enum 
	{
		// 无畸变镜头
		LENSTYPE_NORMAL				= 0,	
	}ENUM_LENS_TYPE;

	typedef enum 
	{
		FISHEYE_SET_PARAM,
		FISHEYE_GET_PARAM
	}ENUM_FISHEYE_OPERATE_TYPE;

	// 音视频同步类型
	typedef enum 
	{
		// 以视频为基准
		SYNC_VIDEO_MASTER,
		// 以音频为基准
		SYNC_AUDIO_MASTER
	}ENUM_SYNC_TYPE;

	// IVS电子功能类型
	typedef enum 
	{
		IVS_EFUNCTYPE_DEHAZE,	    // 去雾
		IVS_EFUNCTYPE_DENOISE,		// 去噪
		IVS_EFUNCTYPE_WB,			// 偏色校正
		IVS_EFUNCTYPE_LOWLIGHT,		// 低照度增强
		IVS_EFUNCTYPE_HDR,			// 宽动态
		IVS_EFUNCTYPE_NUM			// 支持增强的功能个数
	}ENUM_IVSEFUNC_TYPE;

	typedef enum
	{
		// 智能数据渲染
		RENDER_TYPE_INTL = 0x63,

		// 动检数据渲染
		RENDER_TYPE_MOTION = 0x65,

	}ENUM_RENDER_TYPE;

	////////////////////////////////////////////////////////////////////////////////////////////////

	// 视频显示矩形框
	typedef struct
	{
		LONG left;
		LONG top;
		LONG right;
		LONG bottom;
	}STU_DISPLAY_RECT;

	// 自定义解码信息
	typedef struct
	{
		// 信息类型
		unsigned char type;
		// 信息长度
		unsigned char length;
		// 信息指针
		unsigned char *pbuf;
		// 保留
		unsigned char reserved[2];      
	}STU_CUSTOM_DEC_INFO_EX;

	// 解码附加信息
	typedef struct
	{
		// 码流类型
		LONG			nVideoEncodeType;
		// 解码数据长度
		LONG	        nDataLen;
		// 解码信息
		char*           pUserData;
		// 保留位
		LONG	        nReserved[2];
	}STU_FRAME_DEC_INFO_EX;

	// 多媒体信息
	typedef struct
	{
		int			lWidth;					// 画面宽(单位: 像素)
		int			lHeight;				// 画面高(单位: 像素)
		int			lFrameRate;				// 帧率
		int			lChannel;				// 音频通道数
		int			lBitPerSample;			// 音频采样位数
		int			lSamplesPerSec;			// 音频采样频率
	}STU_MEDIA_INFO;

	// 鱼眼相关尺寸
	typedef struct
	{
		int w;
		int h;
	}STU_FISHEYE_SIZE;

	// 鱼眼相关2D坐标
	typedef struct
	{
		short x;
		short y;
	}STU_FISHEYE_POINT2D;

	// 鱼眼子类型
	typedef struct
	{
		// 子图像安装模式
		ENUM_MODE_FISHEYE				subMountMode;
		// 子图像校正模式
		ENUM_FISHEYE_CALIBRATE_MODE		subCalibrateMode;
		// 子图像输出分辨率
		STU_FISHEYE_SIZE				imgOutput;
		// 子图像偏移
		STU_FISHEYE_POINT2D				upperLeft;
		// 保留位
		int								reserved[3];	
	}STU_FISHEYE_SUBMODE;

	// 鱼眼输出格式
	typedef struct
	{
		// 主显示比例
		STU_FISHEYE_SIZE			mainShowSize;	
		// 浮动窗口的主显示窗口分辨率,
		STU_FISHEYE_SIZE			floatMainShowSize;
		// 缩放前输出图像分辨率
		STU_FISHEYE_SIZE			imgOutput;
		// 子模式信息
		STU_FISHEYE_SUBMODE*		subMode;
		// 子模式数
		int							subModeNum;     
		// 校正输出图像的缩放比
		int							outputSizeRatio;
		// 保留位
		int							reserved[1];
	}STU_FISHEYE_OUT_FORMAT;

	// 鱼眼区域参数
	typedef struct
	{
		int					x;
		int					y;
		int					hAngle;
		int					vAngle;
		int					available;
		int					reserved[3];
	}STU_FISHEYE_REGION_PARAM;

	// 鱼眼模式初始化参数
	typedef struct
	{
		STU_FISHEYE_REGION_PARAM	regionParam[9];
		int							circularOffset;
		int							panoramaOffset;
		int							useRegionParam;
		int							reserved[1];
	}STU_FISHEYE_MODE_INIT_PARAM;

	// MHF 云台配置参数
	typedef struct
	{	
		/*必设参数*/
		int zoom_type;							// 倍数控制模式
		int hcam_wax;							// 期望倍数对应球机角度x（水平）
		int hcam_way;							// 期望倍数对应球机角度y（垂直）
		int hcam_wmul;							// 期望倍数设置（基准倍数）
		int cfg_type;							// 配置方式1：0-使用设备类型配置方式, 1-使用参数配置方式
						         
		//镜头参数
		int prm_re;								// 投影半径
		int prm_mul;							// 投影倍率
		int prm_dx;								// x方向偏移
		int prm_dy;								// y方向偏移
		int prm_cw;								// CMOS宽
		int prm_ch;								// CMOS高

		//主相机和从相机类型配置
		ENUM_LENS_TYPE mlen_type;				// 主相机镜头类型
		ENUM_CAMERA_TYPE mcam_type;				// 主相机类型
		ENUM_CAMERA_TYPE hcam_type;				// 从相机类型

		//球机参数
		int himg_width;                         // 从相机图像宽
		int himg_height;                        // 从相机图像高
		int prm_fax;                            // 球机水平视场角

		//主相机参数
		int mcam_fc;							// 相机等效焦距
		int mcam_cw;							// 镜头靶面高
		int mcam_ch;							// 镜头靶面宽 
		int cam_height;                         // 相机架设高度（米
		int prm_ma;								// 焦距参数
 
		//从相机参数
		int prm_hw;								// CMOS宽
		int prm_hh;								// CMOS高
		int prm_fo;								// 等效焦距
		int prm_ca;								// 视野参数
		int prm_mmul;							// 最大倍率
	}STU_MHF_PTZ_CFG_PARAM;

	// 鱼眼选项参数
	typedef struct
	{
		// 主码流尺寸
		STU_FISHEYE_SIZE				mainStreamSize;
		// 圆心X坐标,8192坐标系
		int								originX;
		// 圆心Y坐标,8192坐标系
		int								originY;
		// 半径大小,8192坐标系
		int								radius;
		// 旋转角度 0-360*128
		int								lensDirection;
		// 主安装模式
		ENUM_MODE_FISHEYE				mainMountMode;
		// 图像主校正模式
		ENUM_FISHEYE_CALIBRATE_MODE		mainCalibrateMode;	
		// 初始化的画面信息
		STU_FISHEYE_MODE_INIT_PARAM		modeInitParam;
		// 输出图像信息
		STU_FISHEYE_OUT_FORMAT			*outputFormat;    
		// 鱼球联动配置参数
		STU_MHF_PTZ_CFG_PARAM			*configParam;      
		// 开启自动对比度, 0关闭, 1开启
		int								enableAutoContrast;
		// 直方图IIR强度0-255, 默认128, 越大越参考当前帧
		int								alphaHistogram;
		// 灰度拉伸强度0-255, 默认245, 越大越对比度弱
		int								alphaGray;  
		// 当前模式下抓图分辨率
		STU_FISHEYE_SIZE				captureSize;
		// IN 鱼球联动球机序号 0,1,2...
		int								mhfptzIndex;
		// 保留位
		int								reserved[1];
	}STU_FISHEYE_OPT_PARAM;

	// 鱼眼电子云台参数
	typedef struct
	{
		ENUM_FISHEYE_EPTZ_CMD			ePtzCmd;
		int								winId;					
		int								arg1;
		int								arg2;
		int								arg3;
		int								arg4;
		int								arg5;
		int								arg6;
		int								reserved0[6];
		void*							pParam;
		void*							pResult;
		void*							pArg;   
		int								reserved1[7];
	}STU_FISHEYE_EPTZ_PARAM;

	// 鱼眼信息回调函数
	typedef void (CALLBACK* fFishEyeInfomationCallBack)( 
		LONG nPort,
		BYTE byCorrectMode,
		WORD wRadius,
		WORD wCircleX,
		WORD wCircleY,
		UINT widthRatio,
		UINT heightRatio,
		BYTE gain,
		BYTE denoiseLevel,
		BYTE installStyle,
		void* pUserData);

	////////////////////////////////////////////////////////////////////////////////////////////////

	typedef struct
	{
		int   himg_width;                       // 从相机图像宽
		int   himg_height;                      // 从相机图像高
		int   *zoom_list;						// 球机倍数表
		int   zoom_list_size;					// 球机倍数表档位个数
	}STU_MHF_PTZ_INIT_PARAM;

	typedef struct
	{
		int								radius;			// 目标鱼眼圆半径——输入为8192坐标系
		int								originX;		// 目标鱼眼圆圆心X——输入为8192坐标
		int								originY;		// 目标鱼眼圆圆心Y——输入为8192坐标
		STU_FISHEYE_SIZE				srcSize;		// 输入鱼眼圆的宽高
		STU_FISHEYE_SIZE				dstSize;		// 输出矫正图的宽高
		int								winId;			// 目标窗口的id
		ENUM_MODE_FISHEYE				mountMode;		// 鱼眼安装模式
		ENUM_FISHEYE_CALIBRATE_MODE		calibMode;		// 矫正模式
		STU_FISHEYE_REGION_PARAM		regionParam;	// 鱼眼区域参数
	}STU_FISH_RECTIFY_INFO;

	// 日期信息
	typedef struct _STU_PLAY_DATE_TIME
	{
		unsigned int					nYear;			// 年
		unsigned int					nMonth;			// 月
		unsigned int					nDay;			// 日
		unsigned int					nHour;			// 时
		unsigned int					nMinute;		// 分
		unsigned int					nSecond;		// 秒
		unsigned int					nMilliSecond;	// 毫秒
	}STU_PLAY_DATE_TIME;

	typedef struct
	{
		// 1:VIDEO, 2:AUDIO, 3:DATA
		int type;		
		// I Frame, BP Frame, PCM8, MS-ADPCM etc.
		int subtype;	
		// MPEG4, H264, STDH264
		int encode;		
		// I帧间隔里面的序号
		int sequence;		

		// 图像宽度
		int width;
		// 图像高度
		int height;

		// 帧率信息
		int rate;

		// 时间信息
		int year;
		int month;
		int day;
		int hour;
		int minute;
		int secode;
		LONG timestamp;

		int channels;
		int bitspersample;
		int samplespersecond;
	}STU_DEMUX_INFO_BASE;

	typedef struct 
	{
		char*							pHead;			// 帧数据
		int								nLen;			// 帧数据长度
		char*							pBody;			// 裸数据
		int								nBodyLen;		// 裸数据长度
		int								nRet;			// 0:继续解码 1:不解码  默认为0
		char							reserved[128];	// 预留位
	}STU_DEMUX_INFO_EX;

	// 文件信息帧
	typedef struct _STU_PLAY_FRAME_INFO
	{
		unsigned int			nFrameSubType;			// 帧子类型，动检数据帧、事件帧等
		STU_PLAY_DATE_TIME*		pstDateTimeStart;		// 开始时间
		STU_PLAY_DATE_TIME*		pstDateTimeEnd;			// 结束时间
		unsigned char*			pFrameData;				// 帧数据
		unsigned int			nFrameDataLen;			// 帧数据长度
	} STU_PLAY_FRAME_INFO;

	typedef struct _STU_PLAY_FRAME_SEARCH_INFO
	{
		unsigned int			nFileFrameType;			// 搜索类型
		STU_PLAY_DATE_TIME		stStartDataTime;		// 开始时间
		STU_PLAY_DATE_TIME		stEndDataTime;			// 结束时间
		STU_DISPLAY_RECT		rtDetectedRegion;		// 总区域中的动检检测范围，动检帧时有效。区域矩形为0时，为全区域搜索
		STU_DISPLAY_RECT		rtTotal;				// 总区域, 动检帧时有效
	} STU_PLAY_FRAME_SEARCH_INFO;

	typedef struct
	{
		ENUM_IMAGE_FORMAT_TYPE	imageType;				// 图片的类型
		unsigned char*			pPicBuf;				// 图片的缓冲指针
		unsigned int			nPicBufLen;				// 图片的长度
	} STU_IMAGE_FILE_INFO;

	typedef struct
	{
		int						x;						// 左上角x坐标
		int						y;						// 左上角y坐标
		int						width;					// 区域宽度
		int						height;					// 区域高度
	}STU_IVS_ROI;

	typedef struct
	{
		ENUM_IVSEFUNC_TYPE		eFuncType;				// 功能选项
		STU_IVS_ROI				cRoi;					// ROI 配置
		int						nMode;					// 0-图片模式, 1-视频模式
		int						nProcess_param[2];		// 处理参数，范围[1,5]
	}STU_IVS_PARAMS;

	////////////////////////////////////////////////////////////////////////////////////////////////

	/**********************************************************************************
	函数:	PlayMS_GetPictureQuality
	描述:	获取图像质量
	参数:	nPort:				端口号
			bHighQuality:		TRUE 表示高质量, FALSE 表示低质量.
	返回:	BOOL,成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetPictureQuality(LONG nPort, BOOL *bHighQuality);

	/**********************************************************************************
	函数: PlayMS_Version
	描述: 获取版本号
	参数: 
	返回: DWORD
	**********************************************************************************/
	PLAYMS_API DWORD CALLMETHOD PlayMS_Version();

	/**********************************************************************************
	函数:	PlayMS_ConvertToBmpFile
	描述:	图像格式转为BMP格式.
	参数:	pBuf			图像数据指针
			nSize			图像数据大小
			nWidth			图像宽度
			nHeight			图像高度
			nType			数据类型
			sFileName		保存的文件名
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_ConvertToBmpFile(char * pBuf, LONG nSize, LONG nWidth, LONG nHeight, LONG nType, char *sFileName);

	/**********************************************************************************
	函数:	PlayMS_ConvertToJpegFile
	描述:	图像格式转为JPEG格式.
	参数:	pYUVBuf			图像数据指针
			nWidth			图像宽度
			nHeight			图像高度
			YUVtype			YUV数据类型
			quality			图片压缩质量,范围(0, 100].
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_ConvertToJpegFile(char *pYUVBuf, LONG nWidth, LONG nHeight, int YUVtype, int quality, char *sFileName);

	/**********************************************************************************
	函数:	PlayMS_SetGPSCallBack
	描述:	GPS信息获取函数
	参数:	nPort:				端口号
			pFunc:				GPS信息回调函数
			pUserData:			用户数据
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef int (CALLBACK *fGPSInfoCallBack)(char* pBuf, LONG nLen, void* pUserData);
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetGPSCallBack(LONG nPort, fGPSInfoCallBack pFunc, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_InitDisk
	描述:	初始化硬盘(Windows32平台)
	参数: 
	返回:	成功返回硬盘数量, 失败返回0   
	**********************************************************************************/
	//PLAYMS_API UINT CALLMETHOD PlayMS_InitDisk();

	/**********************************************************************************
	函数:	PlayMS_QueryFileList
	描述:	文件查询与定位(Windows32平台)
	返回:	成功返回文件数量, 失败返回0 
	**********************************************************************************/
	//PLAYMS_API UINT CALLMETHOD PlayMS_QueryFileList(UINT nChannel, ALTIME start_time, ALTIME end_time,
	//	UINT *pmax_ret_num, pFILE_INFO pfile_info, UINT type, BYTE hint, UINT driver_type);

	/**********************************************************************************
	函数:	PlayMS_SetReordPosition
	描述:	剪切录像
	参数:	nPort				播放端口
			nFileStartPos		文件开始位置
			nFileEndPos			文件结束位置
			pRecPosPerCB		录像文件关联进度回调
			pUserData			用户数据
	返回:	成功返回TRUE, 失败返回FALSE
	**********************************************************************************/
	typedef void (CALLBACK *fRecPosPercentCallBack)(int nPercent, void* pUserData);
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetReordPosition(LONG nPort, 
		LONG nFileStartPos, LONG nFileEndPos, fRecPosPercentCallBack pRecPosPerCB, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_SetDisplayScale
	描述:	设置显示比例大小
	参数:	nPort			端口号
			fScale			显示比例, 默认1.0
			nRegionNum		显示区域序号, 0~(MAX_DISPLAY_WND-1)
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_SetDisplayScale(LONG nPort, float fScale, DWORD nRegionNum);

	/**********************************************************************************
	函数名:	PlayMS_SetSecurityKey
	描述:	设置aes解密密钥
	参数:	nPort			解码通道。
			szKey			密钥的指针
			nKeylen			密钥的长度       
	返回:	成功返回TRUE, 失败返回FALSE.
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_SetSecurityKey(LONG nPort,const char* szKey,DWORD nKeylen);

	/**********************************************************************************
	函数:	PlayMS_StartFisheye
	描述:	开启视频鱼眼算法功能
	参数:	nPort				端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_StartFisheye(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_OperateFisheyeParams
	描述:	设置/获取鱼眼参数
	参数:	nPort				端口号
			emOptType			操作类型
			pOptParam			鱼眼参数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_OptFisheyeParams(LONG nPort,
	//	TYPE_FISHEYE_OPERATE emOptType, STU_FISHEYE_OPT_PARAM* pOptParam);

	/**********************************************************************************
	函数:	PlayMS_FisheyeSecondRegion
	描述:	用于浮动模式下开启或关闭第二个鱼眼窗口
	参数:	nPort				端口号
			hDestWnd			显示窗口句柄
			pOptParam			第二个窗口对应的鱼眼参数
			bEnable				打开或关闭显示区域
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_FisheyeSecondRegion(LONG nPort, 
	//	HWND hDestWnd, STU_FISHEYE_OPT_PARAM* pOptParam, BOOL bEnable);

	/**********************************************************************************
	函数:	PlayMS_FisheyeEptzUpdate
	描述:	开启电子云台,进行操作
	参数:	nPort				端口号
			pEptzParam			调节参数
			bSecondRegion		是否为浮动模式下的第二个窗口
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_FisheyeEptzUpdate(LONG nPort, STU_FISHEYE_EPTZ_PARAM* pEptzParam, BOOL bSecondRegion);

	/**********************************************************************************
	函数:	PlayMS_StopFisheye
	描述:	停止视频鱼眼算法功能
	参数:	nPort				端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_StopFisheye(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_SetFishEyeInfoCallBack
	描述:	设置获取鱼眼回调
	参数:	nPort				端口号
			pFishEyeInfoFun		回调函数指针,不能为NULL,其参数含义如下:
				nPort			端口号
				byCorrectMode	矫正模式
				wRadius			半径
				wCircleX		圆心横坐标
				wCircleY		圆心纵坐标
				widthRatio		宽比率
				heightRatio		高比率
				gain			增益
				denoiseLevel	降噪等级
				InstallStyle	鱼眼安装方式
			pUserData,用户自定义参数.
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	// typedef void (CALLBACK* fFishEyeInfomationCallBack)( 
	// 	LONG nPort,
	// 	BYTE byCorrectMode,
	// 	WORD wRadius,
	// 	WORD wCircleX,
	// 	WORD wCircleY,
	// 	UINT widthRatio,
	// 	UINT heightRatio,
	// 	BYTE gain,
	// 	BYTE denoiseLevel,
	// 	BYTE installStyle,
	// 	void* pUserData );
	// 
	// PLAYMS_API BOOL CALLMETHOD PlayMS_SetFishEyeInfoCallBack(LONG nPort, fFishEyeInfomationCallBack pFishEyeInfoFun, void* pUserData );

	/**********************************************************************************
	函数:	PlayMS_SetEngine
	描述:	指定解码器
	参数:	nPort				端口号
			decodeType			解码模式H264
			renderType, 渲染模式
	返回:	成功返回TRUE,失败返回FALSE. 
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_SetEngine(LONG nPort, DecodeType decodeType, RenderType renderType);

	/**********************************************************************************
	函数:	PlayMS_CheckHWDecEnv
	描述:	指定解码器(Windows平台)
	参数: 
	返回:	支持返回TRUE,不支持返回FALSE.   
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_CheckHWDecEnv();

	/**********************************************************************************
	函数:	PlayMS_SetVisibleDecCallBack(建议使用PlayMS_SetVisibleDecodeCallBack)
	描述:	解码回调(不要在此做长时间的逻辑处理)
	参数:	nPort				端口号
			DecCBFun			回调函数指针,不能为NULL,参数如下
				nPort			端口号
				pBuf			解码后的音视频数据
				nSize			数据长度
				pFrameInfo		帧信息,详见FRAME_ATTRI_INFO结构体.
				pUserData		用户自定义参数
				nReserved		保留位.
			pUserData			用户自定义参数.
	返回:	BOOL,成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef void (CALLBACK* fVisibleDecCallBack)(LONG nPort, char* pBuf, LONG nSize, FRAME_ATTRI_INFO* pFrameInfo, void* pUserData, LONG nReserved);
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetVisibleDecCallBack(LONG nPort, fVisibleDecCallBack fVisibleDecCB, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_SetDecCallBack(建议使用PlayMS_SetDecodeCallBack)
	描述:	设置解码回调（只解码）
	参数:	nPort				端口号
			DecCBFun			解码回调函数指针,不能为NULL.参数如下:
				nPort			端口号
				pBuf			解码后的音视频数据
				nSize			解码后的音视频数据pBuf的长度
				pFrameInfo		图像和声音信息,请参见FRAME_ATTRI_INFO结构体
				nReserved		保留参数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef void (CALLBACK* fFrameDecCallBack)(LONG nPort, char* pBuf, LONG nSize, FRAME_ATTRI_INFO* pFrameInfo, void* pUserData, LONG nReserved);
	//PLAYMS_API BOOL CALLMETHOD PlayMS_SetDecCallBack(LONG nPort, fFrameDecCallBack DecCBFun);

	/**********************************************************************************
	函数:	PlayMS_SetDecCallBackEx(建议使用PlayMS_SetDecodeCallBack)
	描述:	设置解码回调
	参数:	nPort				端口号
			DecCBFun			解码回调函数指针,不能为NULL.参含义如下:
				nPort			端口号
				pBuf			解码后的音视频数据
				nSize			解码后的音视频数据pBuf的长度
				pFrameInfo		图像和声音信息,请参见FRAME_ATTRI_INFO结构体
				nReserved		保留参数
			pUserData			用户自定义参数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_SetDecCallBackEx(LONG nPort, fFrameDecCallBack DecCBFun, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_SetRotateAngle
	描述:	图像翻转
	参数:	nRotateType			翻转类型,范围[0,3]. 
								0不旋转; 1旋转90度; 2旋转180度; 3旋转270度.
	返回:	成功返回TRUE, 失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetRotateAngle(LONG nPort , int nRotateType);

	/**********************************************************************************
	函数:	PlayMS_SetDelayTime
	描述:	设置延迟时间
	参数:	nDelay				延迟时间(ms)
								缓冲多少时间开始播放，缓冲小于此值开始稍微慢放
			nThreshold			阀值时间(ms)
								到达阀值开始稍微快放
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetDelayTime(LONG nPort, int nDelay, int nThreshold);

	/**********************************************************************************
	函数:	PlayMS_SetAudioRecScaling
	描述:	设置音频采集数据缩放比例
	参数:	fRatio				缩放比例.
								大于0小于1为音频缩小; 1为原始音频; 大于1为音频放大.
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetAudioRecScaling(float fRatio);

	/**********************************************************************************
	函数:	PlayMS_GetAudioRecScaling
	描述:	获取音频采集数据缩放比例
	参数:	pfRatio				缩放比例.
								大于0小于1为音频缩小; 1为原始音频; 大于1为音频放大.
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetAudioRecScaling(float* pfRatio);

	/**********************************************************************************
	函数:	PlayMS_SetAudioRenderScaling
	描述:	设置音频解码缩放比例
	参数:	nPort				端口号
			fRatio				缩放比例.
								大于0小于1为音频缩小; 1为原始音频; 大于1为音频放大.
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetAudioRenderScaling(LONG nPort, float fRatio);

	/**********************************************************************************
	函数:	PlayMS_GetAudioRenderScaling
	描述:	获取音频解码缩放比例
	参数:	nPort				端口号
			pfRatio				缩放比例.
								大于0小于1为音频缩小; 1为原始音频; 大于1为音频放大.
	返回:	成功返回TRUE, 失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetAudioRenderScaling(LONG nPort, float* pfRatio);

	/**********************************************************************************
	函数:	PlayMS_SetFileRefCallBackEx
	描述:	设置建立索引回调,以返回索引创建情况.在文件打开时生成文件索引.耗时较长
	参数:	nPort				端口号
			pFileRefDoneEx		回调函数指针,参数含义如下:
				nPort			端口号
				bIndexCreated	索引创建标志,TRUE索引创建成功;FALSE失败.
				pUserData		用户自定义参数
			pUserData,用户自定义参数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef void (CALLBACK *fFileRefDoneCallBackEx)(DWORD nPort, BOOL bIndexCreated, void* pUserData);
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetFileRefCallBackEx(LONG nPort, fFileRefDoneCallBackEx pFileRefDoneCBFunEx, void* pUserData);

	/**********************************************************************************
	函数:	Play_OneByOneBack
	描述:	单帧回退，必须在文件索引生成之后才能调用.每调用一次倒退一帧
	参数:	nPort				端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_OneByOneBack(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_StartAVIConvert
	描述:	开始AVI转换并设置AVI转换状态回调.
	参数:	nPort					端口号
				pAVIConvertCB		回调函数,参数含义如下:
				nPort				端口号
				lMediaChangeType	TYPE_MEDIACHANGE_FRAMERATE表示帧率改变;
									TYPE_MEDIACHANGE_RESOLUTION表示分辨率改变
				pUserData			用户自定义参数
				pIsNewFile			TRUE则分段转换;FALSE不分段；默认不分段
				sNewFileName		如果分段转换,新的录像文件名
			pUserData				用户自定义参数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef void (CALLBACK* fAVIConvertCallBack)(LONG nPort, LONG lMediaChangeType, void* pUserData, BOOL *pIsNewFile, char *sNewFileName);
	PLAYMS_API BOOL CALLMETHOD PlayMS_StartAVIConvert(LONG nPort, char *sFileName, fAVIConvertCallBack pAVIConvertCB, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_StopAVIConvert
	描述:	停止AVI转换.
	参数:	nPort					端口号
	返回:	成功返回TRUE, 失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StopAVIConvert(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_SetEncChangeMsg
	描述:	设置分辨率改变通知消息
	参数:	nPort				端口号
			hWnd				消息发送的窗口
			nMsg				用户输入的消息
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetEncChangeMsg(LONG nPort, HWND hWnd, UINT nMsg);

	/**********************************************************************************
	函数:	PlayMS_CatchResizePic
	描述:	抓图
	参数:	nPort				端口号
			sFileName			文件名称
			lTargetWidth		指定的图像宽度
			lTargetHeight		指定的图像高度
			eImageFormat		图片格式
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_CatchResizePic(LONG nPort, char* sFileName, 
		LONG lTargetWidth, LONG lTargetHeight, ENUM_IMAGE_FORMAT_TYPE eImageFormat);

	/**********************************************************************************
	函数:	PlayMS_GetPicBMP
	描述:	抓取BMP图像
	参数:	nPort				端口号
			pBmpBuf				存放BMP图像数据的缓冲地址
								由用户分配,不得小于bmp 图像大小,
								推荐大小:sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 4 * w * h
								其中w和h分别为图像宽高.
			dwBufSize			缓冲区大小
			pBmpSize			实际BMP图像大小
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetPicBMP(LONG nPort, PBYTE pBmpBuf, DWORD dwBufSize, DWORD* pBmpSize);

	/**********************************************************************************
	函数:	PlayMS_GetPicBMPEx
	描述:	抓取BMP图像
	参数:	nPort			端口号
			pBmpBuf			存放BMP图像数据的缓冲地址
							由用户分配,不得小于bmp 图像大小,
							推荐大小:sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 4 * w * h
							其中w和h分别为图像宽高.
			dwBufSize		缓冲区大小
			pBmpSize		实际BMP图像大小
			nWidth			指定的bmp的宽
			nHeight			指定的bmp的高
			nRgbType		指定RGB格式 0-RGB32; 1-RGB24;
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetPicBMPEx(LONG nPort, PBYTE pBmpBuf,
		DWORD dwBufSize, DWORD* pBmpSize, LONG nWidth, LONG nHeight, int nRgbType);

	/**********************************************************************************
	函数:	PlayMS_GetPicJPEG
	描述:	抓取JPEG图像.
	参数:	nPort			端口号
			pJpegBuf		存放JPEG图像数据的缓冲地址
							由用户分配,不得小于JPEG图像大小,
							推荐大小: w *h * 3 / 2
							其中w和h分别为图像宽高.
			dwBufSize		缓冲区大小.
			pJpegSize		获取到的实际JPEG图像大小.
			quality			JPEG图像的压缩质量, 取值范围为(0,100].
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetPicJPEG(LONG nPort, PBYTE pJpegBuf, DWORD dwBufSize, DWORD* pJpegSize, int quality);

	/**********************************************************************************
	函数:	PlayMS_GetPicTIFF
	描述:	抓取TIFF图像
	参数:	nPort			端口号
			pTiffBuf		存放TIFF图像数据的缓冲地址
							由用户分配,不得小于tiff图像大小,
							推荐大小: w * h * 3 + 1024,
							其中w和h分别为图像宽高.
			dwBufSize		缓冲区大小
			pTiffSize		获取到的实际TIFF图像大小
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetPicTIFF(LONG nPort, PBYTE pTiffBuf, DWORD dwBufSize, DWORD* pTiffSize);

	/**********************************************************************************
	函数:	PlayMS_VerticalSyncEnable
	描述:	垂直同步显示开关，PlayMS_Play 后调用。
	参数:	nPort			端口号
			bEnable			TRUE打开垂直同步, FALSE关闭垂直同步.
	返回:	成功返回TRUE, 失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_VerticalSyncEnable(LONG nPort, BOOL bEnable);

	/**********************************************************************************
	函数:	PlayMS_OpenAudioRecord
	描述:	打开音频采集功能.
	参数:	pOpenAudioRecCB			音频采集数据回调指针,参数含义如下:
				pBuf				回调数据指针
				nLen				回调数据长度
				pUserData			用户数据
			nBitsPerSample			表示每个采样所需要的位数
			nSamplesPerSec			采样率
			nLength					数据缓冲的长度
			nReserved				保留参数
			pUserData				用户自定义数据
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef void (CALLBACK *fOpenAudioRecCallBack)(LPBYTE pBuf, DWORD nLen, void* pUserData);
	PLAYMS_API BOOL CALLMETHOD PlayMS_OpenAudioRecord(fOpenAudioRecCallBack pOpenAudioRecCB, LONG nBitsPerSample, LONG nSamplesPerSec, LONG nLength, LONG nReserved, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_CloseAudioRecord
	描述:	关闭音频采集功能
	参数: 
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_CloseAudioRecord();

	/**********************************************************************************
	函数:	PlayMS_CatchPicEx
	描述:	PlayMS_CatchPic的扩展接口,用法请参详PlayMS_CatchPic.可指定图片格式
	参数:	nPort				端口号
			sFileName			文件名称
			emImagefomat		图片格式	
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_CatchPicEx(LONG nPort, char* sFileName, ENUM_IMAGE_FORMAT_TYPE emImagefomat);

	/**********************************************************************************
	函数:	PlayMS_SetEncTypeChangeCallBack
	描述:	设置图像分辨率改变通知回调
	参数:	nPort				端口号
			pEncChangeCB		回调函数
				nPort			端口号
				pUserData		用户自定义数据
			pUserData,用户自定义参数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef void(CALLBACK *fEncChangeCallBack)(LONG nPort, void* pUserData);
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetEncTypeChangeCallBack(LONG nPort, fEncChangeCallBack pEncChangeCB, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_SetEncTypeChangeCallBackEx
	描述:	设置图像分辨率改变通知回调
	参数:	nPort			端口号
			pEncChangeCB	回调函数
				nPort		端口号
				pUserData	用户自定义数据
			 pUserData		用户自定义参数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef void(CALLBACK *fEncChangeCallBackEx)(LONG nPort, void* pUserData,LONG nWidth, LONG nHeight);
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetEncTypeChangeCallBackEx(LONG nPort, fEncChangeCallBackEx pEncChangeCB, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_ResetBuffer
	描述:	清空缓冲区的剩余数据
	参数:	nPort			端口号
			nBufType
				TYPE_MEDIA_VIDEO_SRC_BUF	1 视频源缓冲
				TYPE_MEDIA_AUDIO_SRC_BUF	2 音频源缓冲
				TYPE_MEDIA_VIDEO_RENDER_BUF 3 解码后视频数据缓冲
				TYPE_MEDIA_AUDIO_RENDER_BUF 4 解码后音频数据缓冲
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_ResetBuffer(LONG nPort, DWORD nBufType);

	/**********************************************************************************
	函数:	PlayMS_GetBufferValue
	描述:	获取指定缓冲区的大小
	参数:	nPort			端口号
			nBufType
				TYPE_MEDIA_VIDEO_SRC_BUF 1 视频源缓冲
				TYPE_MEDIA_AUDIO_SRC_BUF 2 音频源缓冲
				TYPE_MEDIA_VIDEO_RENDER_BUF 3 解码后视频数据缓冲
				TYPE_MEDIA_AUDIO_RENDER_BUF 4 解码后音频数据缓冲
	返回:	根据缓冲区类型返回不同的缓冲区值
	**********************************************************************************/
	PLAYMS_API DWORD CALLMETHOD PlayMS_GetBufferValue(LONG nPort, DWORD nBufType);

	/**********************************************************************************
	函数:	PlayMS_GetRefValue
	描述:	获取文件索引,以便下次打开同一个文件时直接使用这个信息.必须在索引建成后才能获得信息.
	参数:	nPort			端口号
			pBuffer			索引信息
			pSize			输入pBuffer的大小
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetRefValue(LONG nPort, BYTE *pBuffer, DWORD *pSize);

	/**********************************************************************************
	函数:	PlayMS_SetRefValue
	描述:	设置文件索引,索引信息必须准确.
	参数:	nPort,端口号
			pBuffer,索引信息
			nSize,索引信息的长度
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetRefValue(LONG nPort,BYTE *pBuffer, DWORD nSize);

	/**********************************************************************************
	函数:	PlayMS_SetDisplayRegion
	描述:	设置或增加显示区域
	参数:	nPort			端口号
			nRegionNum		显示区域序号,0~(MAX_DISPLAY_WND-1)
							如果为0,则将设置的区域显示在主窗口中.
			pSrcRect		局部显示区域
			hwnd			窗口句柄
			bDisplay		打开或关闭显示区域
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetDisplayRegion(LONG nPort, 
		DWORD nRegionNum, STU_DISPLAY_RECT *pSrcRect, HWND hwnd, BOOL bDisplay);

	/**********************************************************************************
	函数:	PlayMS_AdjustWaveAudio
	描述:	调整WAVE波形,可以改变声音的大小.
	参数:	nPort			端口号
			nCoefficient	调整的参数
							范围从 MIN_WAVE_COEF(-100) 到 MAX_WAVE_COEF(100), 0 是不调整
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_AdjustWaveAudio(LONG nPort, LONG nCoefficient);

	/**********************************************************************************
	函数:	PlayMS_SetPicQuality
	描述:	设置图像质量
	参数:	nPort			端口号
			bHighQuality	TRUE图像高质量, FALSE低质量，默认FALSE
	返回:	成功返回TRUE, 失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetPicQuality(LONG nPort, BOOL bHighQuality);

	/**********************************************************************************
	函数:	PlayMS_PlaySoundShare
	描述:	以共享方式播放声音,播放本路声音而不去关闭其他路的声音.
	参数:	nPort			端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_PlaySoundShare(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_StopSoundShare
	描述:	关闭共享方式打开声音.在同一个进程中,所有通道必须使用相同的方式播放或关闭声音.
	参数:	nPort			端口号
	返回:	成功返回 TRUE, 失败返回 FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StopSoundShare(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_GetSourceBufferRemain
	描述:	获取流播放模式下源缓冲区剩余数据大小
	参数:	nPort			端口号
	返回:	当前源缓冲的大小单位BYTE(字节).
	**********************************************************************************/
	PLAYMS_API DWORD CALLMETHOD PlayMS_GetSourceBufferRemain(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_GetKeyFramePos
	描述:	查找指定位置之前的关键帧位置
	参数:	nPort			端口号
			nValue			当前位置,可以是时间或帧号,类型由nType指定.
			nType			指定nValue的类型.如果nType是TYPE_BY_FRAME_NUMBER,则nValue表示帧号;
							nType是BY_FRAMTIME, 则nValue表示时间, 单位ms.
			pFramePos		关键帧的文件位置信息结构指针
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS_INFO pFramePos);

	/**********************************************************************************
	函数:	PlayMS_GetNextKeyFramePos
	描述:	查找指定位置之后的关键帧位置
	参数:	nPort			端口号
			nValue			当前位置,可以是时间或帧号,类型由nType指定.
			nType			指定nValue的类型.如果nType是TYPE_BY_FRAME_NUMBER,则nValue表示帧号;
							nType是BY_FRAMTIME, 则nValue表示时间, 单位ms.
			pFramePos		关键帧的文件位置信息结构指针
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetNextKeyFramePos(LONG nPort,DWORD nValue, DWORD nType, PFRAME_POS_INFO pFramePos);

	/**********************************************************************************
	函数:	PlayMS_GetColor
	描述:	获取视频参数
	参数:	nPort			端口号
			nRegionNum		显示区域,参考PlayMS_SetDisplayRegion
							如果只有一个显示区域(通常情况)设为0.
			pBrightness		亮度,默认64;范围0-128.
			pContrast		对比度,默认64;范围0-128.
			pSaturation		饱和度,默认64;范围0-128.
			pHue			色调,默认64;范围0-128.
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetColor(LONG nPort, DWORD nRegionNum, int *pBrightness, int *pContrast, int *pSaturation, int *pHue);

	/**********************************************************************************
	函数:	PlayMS_SetColor
	描述:	设置视频参数
	参数:	nPort			端口号
			nRegionNum		显示区域
							如果只有一个显示区域(通常情况)设为0.
			nBrightness		亮度,默认64;范围0-128.
			nContrast		对比度,默认64;范围0-128.
			nSaturation		饱和度,默认64;范围0-128.
			nHue			色调,默认64;范围0-128.
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetColor(LONG nPort, DWORD nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);

	/**********************************************************************************
	函数:	PlayMS_GetLastError
	描述:	获取错误码
	参数:	nPort			端口号
	返回:	获得当前错误的错误码
	**********************************************************************************/
	PLAYMS_API DWORD CALLMETHOD PlayMS_LastError(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_RigisterDrawCallBackEx
	描述:	注册绘图回调函数
	参数:	nPort			端口号
			nReginNum		显示区域序号,范围[0,(MAX_DISPLAY_WND-1)].
							如果nRegionNum为0, 则将设置的区域显示在主窗口中.
			pRegDrawCB		画图回调函数,其参数含义如下:
				nPort		端口号
				hDc			绘图表面的设备上下文(DC)
				pUserData	用户自定义参数
			pUserData		用户自定义参数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef void (CALLBACK* fRegDrawCallBackEx)(LONG nPort,LONG nReginNum, HDC hDc, void* pUserData);
	PLAYMS_API BOOL CALLMETHOD PlayMS_RigisterDrawCallBackEx(LONG nPort, LONG nReginNum, fRegDrawCallBackEx pRegDrawCB, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_CreateFile
	描述:	打开文件并自动分配端口号
	参数:	sFileName		文件名
	返回:	成功返回端口号，失败返回0
	**********************************************************************************/
	PLAYMS_API DWORD CALLMETHOD PlayMS_CreateFile(LPSTR sFileName);

	/**********************************************************************************
	函数:	PlayMS_DestroyFile
	描述:	关闭文件并释放自动分配的端口号
	参数:	nPort			端口号
	返回:	成功返回TRUE，失败返回FALSE
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_DestroyFile(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_RefreshPlay
	描述:	刷新显示
	参数:	
	返回:	成功返回TRUE，失败返回FALSE
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_RefreshPlay(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_SetupPrepareTime
	描述:	设置预录的环境
	参数:	nPort:		解码通道。
			nTime:		预录多少秒
			tmpDir:		临时的预录目录    
	返回值: 成功返回TRUE, 失败返回FALSE
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetupPrepareTime(LONG nPort,int nTime,const char* tmpDirectory);

	/**********************************************************************************
	函数:	PlayMS_StartPrepareRecord
	描述:	开始预录
	参数:	nPort:		解码通道。
			pFileName	录像位置     
	返回:	成功返回TRUE, 失败返回FALSE
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StartPrepareRecord(LONG nPort,const char* pFileName);

	/**********************************************************************************
	函数:	PlayMS_StopPrepareRecord
	描述:	停止预录
	参数:	nPort:		解码通道。       
	返回:	成功返回TRUE, 失败返回FALSE
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StopPrepareRecord(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_SetIVSCallBack
	描述:	设置IVS回调
	参数:	nPort				解码通道
			pGetIVSInfoCB		设置解码回调
				pBuf			数据指针
				nType			数据类型
				nLen			数据大小
				nRealLen		数据真实大小
				pReserved		保留参数
				pUserData		用户自定义数据
			pUserData			用户自定义数据  
	返回:	成功返回TRUE, 失败返回FALSE
	**********************************************************************************/
	typedef void (CALLMETHOD *fGetIVSInfoCallBack)(char* pBuf, LONG nType, LONG nLen, LONG nRealLen, void* pReserved, void* pUserData);
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetIVSCallBack(LONG nPort, fGetIVSInfoCallBack pGetIVSInfoCB, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_GetRealFrameBitRate
	描述:	获取码率大小
	参数:	nPort				解码通道
			pBitRate			码率大小
	返回:	成功返回TRUE, 失败返回FALSE
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetRealFrameBitRate(LONG nPort, double* pBitRate);

	/**********************************************************************************
	函数:	PlayMS_StartAVIResizeConvert
	描述:	改变分辨率的AVI转换
	参数:	nPort				解码通道
			sFileName			AVI的录像存放的文件名
			lWidth				AVI的录像的宽
			lHeight				AVI的录像的高        
	返回:	成功返回TRUE, 失败返回FALSE
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StartAVIResizeConvert(LONG nPort, char *sFileName, LONG lWidth, LONG lHeight);

	/**********************************************************************************
	函数:	PlayMS_StopAVIResizeConvert
	描述:	结束AVI转换
	参数:	nPort:				解码通道。	        
	返回:	成功返回TRUE, 失败返回FALSE
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StopAVIResizeConvert(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_SetPandoraWaterMarkCallBack
	描述:	/
	参数:	/
	返回:	成功返回TRUE, 失败返回FALSE
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_SetPandoraWaterMarkCallBack(LONG nPort, fGetWaterMarkInfoCallBack pFunc, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_SetDigitalSignCallBack
	描述:	设置数字签名回调.
	参数:	nPort					解码通道
			pCheckDigitalSignCB		数字签名回调
				nPort				解码通道
				nFrameID			帧序号
				bSuccess			校验是否通过
				pUserData			用户自定义参数	        
			pUserData				用户自定义参数	     
	返回:	成功返回TRUE, 失败返回FALSE
	**********************************************************************************/
	typedef void (CALLBACK* fCheckDigitalSignCallBack)(LONG nPort, int nFrameID, BOOL bSuccess, void* pUserData);
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetDigitalSignCallBack(LONG nPort, fCheckDigitalSignCallBack pCheckDigitalSignCB, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_GetTimePicture
	描述:	获得绝对时间点上面的图片
	参数:	sFilepath				保存的文件路径
			pstTime					绝对时间
			pDecCB					解码回调
			pUserData				用户自定义参数        
	返回:	成功返回TRUE, 失败返回FALSE
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_GetTimePicture(const char* sFilepath, struct tm* pstTime, fFrameDecCallBack pDecCB, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_StartFisheyeEx
	描述:	鱼球联动功能扩展接口
	参数:	nPort					端口号
			nStartType				开启类型	
									0只开启鱼眼校正, 1同时开启联动和校正, 2只开启鱼球联动算法
			nFuncType				开启功能类型
									0表示都不开启，1表示只开启智能帧功能，2表示只开启抓图，
									3表示智能帧和抓图都开启，开启的功能越多，消耗的内存越大
			pstParam				鱼球联动初始化通道参数，nStartType = 0 时，pstParam = NULL
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_StartFisheyeEx(LONG nPort, int nStartType, int nFuncType, STU_MHF_PTZ_INIT_PARAM* pstParam);

	/**********************************************************************************
	函数:	PlayMS_StartFisheyeMPTZ
	描述:	鱼球联动功能扩展接口，支持一鱼多球
	参数:	nPort					端口号
			nStartType				开启类型
									0只开启鱼眼校正, 1同时开启联动和校正, 2只开启鱼球联动算法
			nFuncType				开启功能
									0表示都不开启，1表示只开启智能帧功能，2表示只开启抓图，
									3表示智能帧和抓图都开启，开启的功能越多，消耗的内存越大
			pstParam				鱼球联动初始化通道参数，nStartType = 0 时，pstParam = NULL
			nPtzChannelNum			鱼球联动初始化通道数  
			pstFishEyeSize			输出图像最大的分辨率
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_StartFisheyeMPTZ(LONG nPort, int nStartType, int nFuncType, STU_MHF_PTZ_INIT_PARAM* pstParam, int nPtzChannelNum, STU_FISHEYE_SIZE* pstFishEyeSize);

	/**********************************************************************************
	函数:	PlayMS_SetFisheyeParams
	描述:	设置鱼眼参数
	参数:	nPort					端口号
			nX						鱼眼圆心横坐标
			nY						鱼眼圆心纵坐标
			nRadius					鱼眼半径
			nLensDirection			镜头方向 
			stMode					图像显示模式
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_SetFisheyeParams(LONG nPort, int nX, int nY, int nRadius, int nLensDirection, FISHSHOWMODES stMode);

	/**********************************************************************************
	函数:	PlayMS_FisheyeGetPosition, 兼容旧版本鱼眼接口
	描述:	获得目标中心对应电子云台的焦点位置
	参数:	nPort				端口号
			nRow				目标中心所在行
			nCol				目标中心所在列
			pX					目标中心所对应电子云台的焦点横坐标
			pY					目标中心所对应电子云台的焦点纵坐标
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_FisheyeGetPosition(LONG nPort, int nRow, int nCol, int *pX, int *pY);

	/**********************************************************************************
	函数:	PlayMS_FisheyeEptzUpdate
	描述:	开启电子云台，进行缩放移动
	参数:	nPort				端口号
			pX					电子云台的焦点横坐标
			pY					eptz的焦点纵坐标
			pHangle				eptz的水平角度范围(0-3600)
			pVangle				eptz的垂直角度范围(0-900)
			ops					FISHEPTZOPTS结构体,
								0时对指定窗口设置焦点，1表示放大，2表示缩小，3表示向上移动，
	                            4表示向下移动，5表示向左移动，6表示向右移动，7表示自动顺时针旋转
								8表示自动逆时针旋转 9表示停止云台操作，10表示获取当前云台窗口所在位置
			nWndNum				要进行eptz的窗口编号，左上角win_num为1，从左到右递增
			nZoomStep			放大缩小的步长, 范围1-8
			nPtStep				上下左右移动的步长, 范围1-8
			nRotateStep			旋转的步长, 范围1-8
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	// PLAYMS_API BOOL CALLMETHOD PlayMS_OldFisheyeEptzUpdate(LONG nPort, int *pX, int *pY, int *pHAngle, int *pVAngle,
	// 	FISHEPTZOPTS ops, int nWndNum, int nZoomStep, int nPtStep, int nRotateStep);

	/**********************************************************************************
	函数:	Fisheye_TrancForm_TrackFrame
	描述:	1模式下，将ivs跟踪帧中的当前帧的目标轨迹坐标转换到原始圆上坐标
	参数:	handle				鱼眼算法实例句柄
			pTrackFrame			跟踪帧
			nTrackFrameSize		跟踪帧大小
			ptrackframe			原始鱼眼圆坐标封装到智能帧
	返回:	AL_FISHEYE_ERROR_NONE: 成功; other: 失败。
	**********************************************************************************/ 	
	//PLAYMS_API BOOL CALLMETHOD PlayMS_FisheyeTrancFormTrackFrame(LONG nPort, void *pTrackFrame, int nTrackFrameSize);

	/**********************************************************************************
	函数:	Fisheye_TrancForm_coordinate
	描述:	给定矫正图上坐标，计算出原始鱼眼圆圆上坐标
	参数:	pstParams				矫正参数	
			pstInPt					输入点，8192坐标系
			pstOutPt				输出点，8192坐标系
	返回:	AL_FISHEYE_ERROR_NONE: 成功; other: 失败。
	**********************************************************************************/ 	
	// PLAYMS_API BOOL CALLMETHOD PlayMS_FisheyeTrancFormCoordinate(STU_FISH_RECTIFY_INFO *pstParams,
	//	STU_FISHEYE_POINT2D* pstInPt, STU_FISHEYE_POINT2D *pstOutPt);

	/**********************************************************************************
	函数:	Fisheye_TrancForm_Curve
	描述:	给定矫正图上坐标，计算出原始鱼眼圆圆上坐标
	参数:	pstParams			矫正参数
			pstPt1				矫正图上的一个点，8192坐标系
			pstPt2				矫正图上的一个点，8192坐标系
			nNum				两点间的点个数
			pstPt				值后得到的点序列，包括两个端点，8192坐标系
	返回: AL_FISHEYE_ERROR_NONE: 成功; other: 失败
	**********************************************************************************/ 	
	// PLAYMS_API BOOL CALLMETHOD PlayMS_FisheyeTrancFormCurve(STU_FISH_RECTIFY_INFO *pstParams, 
	//	STU_FISHEYE_POINT2D* pstPt1, STU_FISHEYE_POINT2D* pstPt2, int *nNum, STU_FISHEYE_POINT2D *pstPt);

	/**********************************************************************************
	函数:	PlayMS_StartDeNoise
	描述:	开启视频去噪算法功能(3d降噪库)
	参数:	nPort			端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StartDeNoise(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_SetDeNoiseParams
	描述:	设置视频去噪参数
	参数:	nPort			端口号
			nTemporal		时域去噪强度 [0,32]
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetDeNoiseParams(LONG nPort, int nTemporal);

	/**********************************************************************************
	函数:	PlayMS_StopDeNoise
	描述:	停止视频去噪算法功能
	参数:	nPort			端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StopDeNoise(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_StartDemistAlg
	描述:	开启视频去雾算法功能
	参数:	nPort			端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StartDemistAlg(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_SetDemistAlgParams
	描述:	设置视频去雾参数
	参数:	nPort					端口号
			nALightValue			设定的大气光强的值，范围0-255
			nAutoLightOn			默认为1, 代表开启自动寻找大气光强；0-关闭自动，开启手动
			nAutoRun				默认为1, 代表一直开启去雾功能，0-自动判断是否雾天并去雾
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetDemistAlgParams(LONG nPort, int nALightValue, int nAutoLightOn, int nAutoRun);

	/**********************************************************************************
	函数:	PlayMS_StopDemistAlg
	描述:	停止视频去雾算法功能
	参数:	nPort			端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StopDemistAlg(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_StartVSAlg
	描述:	开启视频增强算法功能
	参数:	nPort			端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StartVSAlg(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_SetVSAlgParams
	描述:	设置视频增强参数
	参数:	nPort				端口号
			pIVSEParams			结构体参数
			bEnable				使能开关	
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetVSAlgParams(LONG nPort, STU_IVS_PARAMS* pIVSEParams, BOOL bEnable);

	/**********************************************************************************
	函数:	PlayMS_StopVSAlg
	描述:	停止视频增强算法功能
	参数:	nPort			端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StopVSAlg(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_ConvertToBmpFile
	描述:	图像格式转为BMP格式.
	参数:	pBuf		图像数据指针
			nSize		图像数据大小
			nWidth		图像宽度
			nHeight		图像高度
			nType		数据类型
			sFileName	要保存的文件名.
			nBmpType	BMP类型
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_ConvertToBmpFileEx(char* pBuf, LONG nSize, LONG nWidth, LONG nHeight, LONG nType, char *sFileName, int nBmpType);

	/**********************************************************************************
	函数:	PlayMS_EnableLargePicAdjustment
	描述:	是否启用高清图像内部调整策略
	参数:	nPort			端口号
			bEnable			TRUE表示启用，FALSE表示关闭
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_EnableLargePicAdjustment(LONG nPort, BOOL bEnable);

	/**********************************************************************************
	函数:	PlayMS_OpenPlayGroup
	描述:	打开组播放
	参数:	无
	返回:	组播放控制句柄
	**********************************************************************************/
	PLAYMS_API void* CALLMETHOD PlayMS_OpenPlayGroup();

	/**********************************************************************************
	函数:	PlayMS_AddToPlayGroup
	描述:	添加一路已经代开的视频至同步播放中
	参数:	hPlayGroup			同步播放句柄
			nPort				端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_AddToPlayGroup(void* hPlayGroup, LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_DelFromPlayGroup
	描述:	从同步播放组中删除指定端口号
	参数:	hPlayGroup				同步播放句柄
			nPort					端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_DelFromPlayGroup(void* hPlayGroup, LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_SetPlayGroupDirection
	描述:	播放组从当前时间点正放或倒放
	参数:	hPlayGroup			同步播放句柄
			nDirection			播放方向：0，向前，1，向后
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetPlayGroupDirection(void* hPlayGroup, int nDirection);

	/**********************************************************************************
	函数:	PlayMS_SetPlayGroupSpeed
	描述:	设置组播放速度
	参数:	hPlayGroup				同步播放组句柄
			fCoff					播放速度,范围[1/64~64.0]
									小于1表示慢放，大于1表示正放.
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetPlayGroupSpeed(void* hPlayGroup, float fSpeed);

	/**********************************************************************************
	函数:	PlayMS_PausePlayGroup
	描述:	暂停或继续
	参数:	hPlayGroup			同步播放句柄
			bPause				TRUE暂停,FLASE恢复
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_PausePlayGroup(void* hPlayGroup, BOOL bPause);

	/**********************************************************************************
	函数:	PlayMS_StepPlayGroup
	描述:	单帧播放
	参数:	hPlayGroup			同步播放句柄
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StepPlayGroup(void* hPlayGroup);

	/**********************************************************************************
	函数:	PlayMS_StepPlayGroup
	描述:	采用绝对时间进行定位
	参数:	hPlayGroup			同步播放句柄
		    pstDateTime			绝对时间
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SeekPlayGroup(void* hPlayGroup, STU_PLAY_DATE_TIME* pstDateTime);

	/**********************************************************************************
	函数:	PlayMS_ClosePlayGroup
	描述:	关闭同步播放控制
	参数:	hPlayGroup			同步播放句柄
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_ClosePlayGroup(void* hPlayGroup);

	/**********************************************************************************
	函数:	PlayMS_SetFileRefCallBack
	描述:	设置建立索引回调，在文件打开时生成文件索引，过程较长。
	参数:	nPort					端口号
			pFileRefDoneCB			回调函数指针, 参数含义如下:
				nPort				端口号
				pUserData			用户自定义参数
			pUserData				用户自定义参数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef void(CALLBACK *fFileRefDoneCallBack)(DWORD nPort, void* pUserData);									
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetFileRefCallBack(LONG nPort, fFileRefDoneCallBack pFileRefDoneCB, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_SetDemuxCallBack
	描述:	源数据分析完的数据回调
	参数:	nPort				端口号
			pDemuxDecCB			分析数据回调指针
				nPort			端口号
				pBuf			数据指针
				nSize			数据长度
				pMutexInfo		帧信息,指向STU_DEMUX_INFO_BASE结构
				pMutexInfoEx	帧数据或裸数据，指向STU_DEMUX_INFO_EX结构
				pUserData		用户自定义参数
			pUserData			用户自定义参数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef void (CALLBACK* fDemuxDecCallBack)(LONG nPort, char* pBuf, LONG nSize, void* pMutexInfo, void* pMutexInfoEx, void* pUserData);
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetDemuxCallBack(LONG nPort, fDemuxDecCallBack pDemuxDecCB, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_SetFileDoneTimeCallBack
	描述:	文件开始、结束时间回调。分析出文件开始和结束时间后会调用该回调。
	参数:	nPort				端口号
			pFileTimeCB			回调函数指针,参数含义如下:
				nPort			端口号
				nStartTime		文件开始时间(自1970年1月1日0点0分0秒的秒数)
				nEndTime		文件结束时间(自1970年1月1日0点0分0秒的秒数)
				pUserData		用户自定义参数
			pUserData			用户自定义参数.
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef void (CALLBACK* fFileTimeDoneCallBack)(LONG nPort, DWORD nStarTime, DWORD nEndTime, void* pUserData);
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetFileTimeDoneCallBack(LONG nPort, fFileTimeDoneCallBack pFileTimeCB, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_GetKeyFramePosByAbsoluteTime
	描述:	按绝对时间查找指定位置之前的关键帧位置.
	参数:	nPort				端口号
			pstTime				绝对时间
			pstFramePos			关键帧的文件位置信息结构指针,详见PFRAME_POS_INFO.
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetKeyFramePosByAbsTime(LONG nPort, SYSTEMTIME* pstTime, FRAME_POS_INFO* pstFramePos);

	/**********************************************************************************
	函数:	PlayMS_GetNextKeyFramePosByAbsoluteTime
	描述:	按绝对时间查找指定位置之后的关键帧位置.
	参数:	nPort			端口号
			pstTime			绝对时间
			pstFramePos		关键帧的文件位置信息结构指针
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetNextKeyFramePosByAbsTime(LONG nPort, SYSTEMTIME* pstTime, FRAME_POS_INFO* pstFramePos);

	/**********************************************************************************
	函数:	PlayMS_QueryGroupPlayingTime
	描述:	查询当前组中正在播放的时间.
	参数:	nPort			端口号
			pstDateTime		时间
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_QueryGroupPlayingTime(void* hPlayGroup, STU_PLAY_DATE_TIME *pstDateTime);

	/**********************************************************************************
	函数:	PlayMS_GetAudioChannels
	描述:	获取音频通道总数
	参数:	nPort,端口号
			pChannels, 输出参数，[0-255].
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetAudioChannels(LONG nPort, DWORD* pChannels);

	/**********************************************************************************
	函数:	PlayMS_ChooseAudio
	描述:	选择音频通道
	参数:	nPort				端口号
			nChannelID			音频通道从0开始.
			bOpen				TRUE打开,FALSE关闭
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_ChooseAudio(LONG nPort, DWORD nChannelID, BOOL bOpen);

	/**********************************************************************************
	函数:	PlayMS_GetAudioChooseState
	描述:	获取音频通道打开关闭状态
	参数:	nPort			端口号
			nChannelID		音频通道[0-255].
			bOpen			TRUE打开,FALSE关闭
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetAudioChooseState(LONG nPort, DWORD nChannelID, BOOL *bOpen);

	/**********************************************************************************
	函数:	PlayMS_SetPlayedAbsTime
	描述:	按绝对时间设置播放时间
	参数:	nPort			端口号
			pstDateTime		绝对时间
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetPlayedAbsTime(LONG nPort, STU_PLAY_DATE_TIME *pstDateTime);

	/**********************************************************************************
	函数:	PlayMS_SetPlayPosByFileOffset
	描述:	按文件偏移设置播放位置
	参数:	nPort			端口号
			nFileOffset		文件偏移位置
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetPlayPosByFileOffset(LONG nPort, UINT nFileOffset);

	/**********************************************************************************
	函数:	PlayMS_GetCurrentFrameRateEx
	描述:	获得当前帧率（小数形式）
	参数:	nPort			端口号
	返回:	当前帧率
	**********************************************************************************/
	PLAYMS_API float CALLMETHOD PlayMS_GetCurrentFrameRateEx(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_ChangeRate
	描述:	改变播放速率
	参数:	nPort			端口号
			nRate			播放速率
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_ChangeRate(LONG nPort, int nRate);

	typedef void (CALLBACK *fCutProgressCallBack)(DWORD nPort, int nProgress, DWORD dwUser);
	/**********************************************************************************
	// 函数: PlayMS_CutFileSegment
	// 描述: /
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_CutFileSegment(LONG nPort, LONG lBeginTime, LONG lEndTime, fCutProgressCallBack pCutProgressCB, char *sOutFilePath, DWORD dwUser);

	/**********************************************************************************
	函数:	PlayMS_InputVideoData
	描述:	输入视频数据播放
	参数:	nPort			端口号
			pBuf			视频数据
			nSize			数据大小
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_InputVideoData(LONG nPort, PBYTE pBuf, DWORD nSize);

	/**********************************************************************************
	函数:	PlayMS_InputAudioData
	描述:	输入音频数据播放
	参数:	nPort			端口号
			pBuf			音频数据
			nSize			数据大小
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_InputAudioData(LONG nPort, PBYTE pBuf, DWORD nSize);

	typedef void (CALLBACK * fVerifyCallBack)(LONG nPort, FRAME_POS_INFO * pFilePos, DWORD bIsVideo, void* pUserData);
	/**********************************************************************************
	函数:	PlayMS_SetVerifyCallBack
	描述:	/
	参数:	/
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_SetVerifyCallBack(LONG nPort, DWORD nBeginTime, DWORD nEndTime, fVerifyCallBack VerifyFun, void* pUserData);

	typedef void (CALLBACK * fSourceBufCallBack)(LONG nPort, DWORD nBufSize, void* pUserData, void* pReserved);
	/**********************************************************************************
	函数:	PlayMS_SetSourceBufCallBack
	描述:	/
	参数:	/
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_SetSourceBufCallBack(LONG nPort, DWORD nThreShold, fSourceBufCallBack SourceBufCBFun, void* pUserData, void *pReserved);

	/**********************************************************************************
	函数:	PlayMS_AdjustFluency
	描述:	调整图像流畅度
	参数:	nPort			端口号
			nLevel			流畅度等级 等级越高越流畅，越低越实时
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_AdjustFluency(LONG nPort, int nLevel);

	/**********************************************************************************
	函数:	PlayMS_SurfaceChange
	描述:	Phone Surface建立或变化通知
	参数:	nPort			端口号
			hWnd			窗口句柄
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SurfaceChange(LONG nPort, HWND hWnd);

	/**********************************************************************************
	函数:	PLAYER_SetFileInfoFrameCallback
	描述:	设置文件信息帧回调函数
	参数:	nPort						端口号
			pOnFileInfoFrameCB			回调函数
				nPort					端口号
				pstFileInfoImage		图像信息
				pstFileInfoFrame		帧信息
				pUserData				用户自定义参数
			emImageFormat				图片格式
			pUserData					用户自定义参数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef int (CALLBACK* fOnFileInfoFrameCallBack)(LONG nPort,
		STU_IMAGE_FILE_INFO* pstFileInfoImage, STU_PLAY_FRAME_INFO* pstFileInfoFrame, void* pUserData);
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetFileInfoFrameCallback(LONG nPort,
		fOnFileInfoFrameCallBack pOnFileInfoFrameCB, ENUM_IMAGE_FORMAT_TYPE emImageFormat, void* pUserData);

	/**********************************************************************************
	函数:	PLAYER_SetAnalyzePositionCallback
	描述:	设置文件信息帧分析进度回调函数
	参数:	nPort					端口号
			pAnalyzePositionCB		回调函数
				nPort				端口号
				pstDateTime			搜索条件信息
				pUserData			用户自定义参数
			pUserData				用户自定义参数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef int (CALLBACK *fOnAnalyzePosCallBack)(LONG nPort, STU_PLAY_DATE_TIME* pstDateTime, void* pUserData);
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetAnalyzePositionCallback(LONG nPort, fOnAnalyzePosCallBack pAnalyzePositionCB, void* pUserData);

	/**********************************************************************************
	函数:	PLAYER_StartFileFrameDetect
	描述:	需要在索引建立完成之后，开始文件信息帧检测，输入搜索条件
	参数:	nPort			端口号
			pstInfo			搜索条件信息
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StartFileFrameDetect(LONG nPort, STU_PLAY_FRAME_SEARCH_INFO* pstInfo);

	/**********************************************************************************
	函数:	PlayMS_StopFileFrameDetect
	描述:	中止搜索
	参数:	nPort			端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StopFileFrameDetect(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_StartEdgeEnhance
	描述:	开启图像锐化处理
	参数:	nPort			端口号
			nLevel			处理等级, 0-关闭, 6-最强, 默认等级4
			nAlgMode		算法模式,默认 0
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StartEdgeEnhance(LONG nPort, int nLevel, int nAlgMode);

	/**********************************************************************************
	函数:	PlayMS_StopEdgeEnhance
	描述:	关闭图像锐化处理
	参数:	nPort			端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StopEdgeEnhance(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_StartVideoStable
	描述:	开启视频防抖
	参数:	nPort			端口号
	返回:	成功返回TRUE,失败返回FALSE.	
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StartVideoStable(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_StopEdgeEnhance
	描述:	关闭视频防抖
	参数:	nPort			端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_StopVideoStable(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_Scale
	描述:	Phone Ver.图像缩放
	参数:	nPort			端口号
			fScale			缩放比例[1.0, 8.0]
			nRegionNum		显示区域序号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_Scale(LONG nPort, float fScale, DWORD nRegionNum);

	/**********************************************************************************
	函数:	PlayMS_Translate
	描述:	Phone Ver.图像平移
	参数:	nPort			端口号
			fx				x平移坐标，绝对值
			fy				y平移坐标，绝对值
			nRegionNum		显示区域序号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_Translate(LONG nPort, float fx, float fy, DWORD nRegionNum);

	/**********************************************************************************
	函数:	PlayMS_SetIdentity
	描述:	Phone Ver.图像归一化,重置平移,缩放操作。
	参数:	nPort			端口号
			nRegionNum		显示区域序号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetIdentity(LONG nPort, DWORD nRegionNum);

	/**********************************************************************************
	函数:	PlayMS_GetScale
	描述:	Phone Ver.获取当前缩放值。
	参数:	nPort			端口号
			nRegionNum		显示区域序号, 保留。
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API float CALLMETHOD PlayMS_GetScale(LONG nPort, DWORD nRegionNum);

	/**********************************************************************************
	函数:	PlayMS_GetTranslateX
	描述:	Phone Ver.获取当前x轴平移坐标
	参数:	nPort			端口号
			nRegionNum		显示区域序号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API float CALLMETHOD PlayMS_GetTranslateX(LONG nPort, DWORD nRegionNum);

	/**********************************************************************************
	函数:	PlayMS_GetTranslateY
	描述:	Phone Ver.获取当前y轴平移坐标
	参数:	nPort			端口号
			nRegionNum		显示区域序号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API float CALLMETHOD PlayMS_GetTranslateY(LONG nPort, DWORD nRegionNum);

	/**********************************************************************************
	函数:	PlayMS_CleanScreen, PlayMS_Stop前调用有效
	描述:	/
	参数:	
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_CleanScreen(LONG nPort, float red, float green, float blue, float alpha, DWORD nRegionNum);

	/**********************************************************************************
	函数:	PlayMS_ViewResolutionChanged
	描述:	/
	参数:	
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_ViewResolutionChanged(LONG nPort, int nWidth, int nHeight, DWORD nRegionNum);

	/**********************************************************************************
	函数:	PlayMS_StartDataRecordEx
	描述:	开始流数据录像,只对流模式有用,在PlayMS_Play之后调用.
	参数:	nPort				端口号
			sFileName			录像文件名.
			nDataType			0表示原始视频流;
								1表示转换成AVI格式;
								2表示转换成ASF格式;
								3分段保存文件
			pRecErrOccurCB		回调函数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef void (CALLBACK* fRecErrOccurCallBack)(LONG nPort, void* pUserData);
	PLAYMS_API BOOL CALLMETHOD PlayMS_StartDataRecordEx(LONG nPort, char *sFileName, int nDataType, fRecErrOccurCallBack pRecErrOccurCB, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_SetMultiFrameDecCallBack
	描述:	设置解码信息回调
	参数:	nPort				端口号
			pDecInfoCB			回调函数
				nPort			端口号
				nStreamID		码流ID
				pData			数据内容
				nLen			数据长度
				pstFrameInfo	帧信息
				pUserData		用户自定义参数
				nReserved		保留参数
			pUserData			用户自定义参数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef void (CALLBACK* fMultiFrameDecInfoCallBack)(LONG nPort, LONG nStreamID, char* pData, LONG nLen, FRAME_ATTRI_INFO* pstFrameInfo, void* pUserData, LONG nReserved);
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetMultiFrameDecCallBack(LONG nPort, fMultiFrameDecInfoCallBack pDecInfoCB, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_SetMultiFrameCallBack
	描述:	开启多帧信息回调
	参数:	nPort				端口号
			pMultiFrameCB		多帧回调函数
				nPort			端口号
				nStreamID		码流ID
				pUserData		用户自定义参数
				nReserved		保留参数
			pUserData			用户自定义参数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef void (CALLBACK* fMultiFrameInfoCallBack)(LONG nPort, LONG nStreamID, void* pUserData, LONG nReserved);
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetMultiFrameCallBack(LONG nPort, fMultiFrameInfoCallBack pMultiFrameCB, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_SetDecInfoCallBack
	描述:	设置解码信息回调
	参数:	nPort				端口号
			pDecInfoCB			解码信息回调
				nPort			端口号
				pDecInfo		解码信息
				pUserData		用户自定义参数
				nReserved		保留参数
			pUserData			用户自定义参数
	返回:	成功返回 TRUE, 失败返回 FALSE.
	**********************************************************************************/
	typedef void (CALLBACK* fFrameDecInfoCallBack)(LONG nPort, STU_FRAME_DEC_INFO_EX* pDecInfo, void* pUserData, LONG nReserved);
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetDecInfoCallBack(LONG nPort, fFrameDecInfoCallBack pDecInfoCB, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_ChooseFrame
	描述:	选择显示SVAC编码SVC的基本层或增强层
	参数:	nPort			端口号
			nFrameID		要显示的层(0: 基本层，1: 增强层)
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_ChooseFrame(LONG nPort, LONG nFrameID);

	/**********************************************************************************
	函数:	PlayMS_RenderPrivateData
	描述:	显示智能数据图形
	参数:	nPort			端口号
			bShow			TRUE 显示，FALSE 不显示
			nReserved		保留参数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_RenderPrivateData(LONG nPort, BOOL bShow, LONG nReserved);

	/**********************************************************************************
	函数:	PlayMS_SetRenderShapeLineType
	描述:	设置图形边框线条类型
	参数:	nPort			端口号
			nRenderType		图形对象类型  
							ENUM_RENDER_TYPE
	        nLineType		线条类型  
							LINE_TYPE_SOLID_WHOLE = 0x00: 实线，LINE_TYPE_SOLID_HALF - 0x01: 半线
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetRenderShapeLineType(LONG nPort, int nRenderType, int nLineType);

	/**********************************************************************************
	函数:	PlayMS_SetRenderShapeLineType
	描述:	设置渲染类型使能
	参数:	nPort			端口号
			nRenderType		渲染类型  
							ENUM_RENDER_TYPE
	        bEnable			 
							LINE_TYPE_SOLID_WHOLE = 0x00: 实线，LINE_TYPE_SOLID_HALF - 0x01: 半线
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetRenderTypeEnable(LONG nPort, int nRenderType, BOOL bEnable);

	/**********************************************************************************
	函数:	PlayMS_SetFileIndexProgressCallBack
	描述:	设置索引创建进度回调
	参数:	nPort					端口号
			pIndexProgressCB		索引进度回调函数
					nPort			端口号
					fProgress		进度值
					pUserData		用户自定义参数
			pUserData				用户自定义参数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef void (CALLBACK* fIndexProgressCallBack)(LONG nPort, float fProgress, void* pUserData);
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetFileIndexProgressCallBack(LONG nPort, fIndexProgressCallBack pIndexProgressCB, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_GetLastYUVFrame
	描述:	主动获取上一帧对应的YUV数据
	参数:	nPort  端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetLastYUVFrame(LONG nPort, FRAME_DEC_INFO* pFrameDecodeInfo);

	/**********************************************************************************
	函数:	PlayMS_SetMemMinimized
	描述:	设置内存减小版本
	参数:	nPort			端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	//PLAYMS_API BOOL CALLMETHOD PlayMS_SetMemMinimized(LONG nPort);

	/**********************************************************************************
	函数:	PlayMS_SetDecodeThreadNum
	描述:	设置解码线程数
	参数:	nPort			端口号
			nNum			解码线程数
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetDecodeThreadNum(LONG nPort, DWORD nNum);

	/**********************************************************************************
	函数:	PlayMS_SetDecodeKey
	描述:	设置解密密钥，SVAC解码使用
	参数:	nPort			端口号
			sKey			密钥
			nKeyLen			密钥长度
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetDecodeKey(LONG nPort, const unsigned char *sKey, unsigned int nKeyLen);

	/**********************************************************************************
	函数:	PlayMS_GetIRefValue
	描述:	获取I帧数据
	参数:	nPort			端口号
			pBuffer			缓冲数据地址
			pSize			缓冲数据大小
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_GetIRefValue(LONG nPort, BYTE *pBuffer, DWORD *pSize);

#ifdef __native_client__

#define FISHEYE_REGION 16
	/**********************************************************************************
	函数:	PlayMS_OutsideRender
	描述:	nacl ui线程调用此接口
	参数:	nPort			端口号
			nWidth			窗口宽
			nHeight			窗口高
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_OutsideRender(LONG nPort, int nX, int nY, int nWidth, int nHeight, unsigned int nRegionNum = 0);

	namespace pp
	{
		class Instance;
	}

	/**********************************************************************************
	函数:	PlayMS_SetNACLInstance
	描述:	nacl 主线程调用此接口设置句柄地址
	参数:	pInstance			传入pp::instance地址
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetNACLInstance(pp::Instance * pInstance);
#endif

	/**********************************************************************************
	函数:	PlayMS_SetDoubleVisibleDecCallBack
	描述:	
	参数:	
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	typedef void (CALLBACK* fDoubleVisibleDecCallBack)(
		LONG nPort,char * pBuf, int nSize, int nWidth, int nHeight, 
		char* pSecondBuf, int nSecondSize, int nSecondWidth, int nSecondHeight, void* pUserData);
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetDoubleVisibleDecCallBack(
		LONG nPort, fDoubleVisibleDecCallBack DataCBFun, void* pUserData);

	/**********************************************************************************
	函数:	PlayMS_EnableAudioChannel
	描述:	控制左右声道音频播放，仅对左右声道音频有效。
	参数:	nPort			端口号
			nChannel		左右通道，0-左通道，1-右通道
			bEnable			使能 TRUE-启用， FALSE-禁用
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_EnableAudioChannel(LONG nPort, DWORD nChannel, BOOL bEnable);

	/**********************************************************************************
	函数:	PlayMS_SplitProc
	描述:	yuv 拼接算法，用于4k大屏的显示
	参数:	nPort			端口号
	参数:	nMode			模式
						0对应基本模式，1对应1+3模式，2对应1+5模式, 
						3对应1+1模式（电子放大）4对应1P+3, 5对应1P+6
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SplitProc(LONG nPort, int nMode);

	/**********************************************************************************
	函数:	PlayMS_SplitProcUpdate
	描述:	yuv 拼接算法，更新需要放大的矩形位置
	参数:	nPort			端口号
			pAreaRect		矩形坐标数组的起始地址
							如果nMode是0，则应为NULL
							如果nMode是1，则该数组的大小应为3
							如果nMode是2，则该数组的大小应为5
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SplitProcUpdate(LONG nPort, STU_DISPLAY_RECT* pAreaRect);

	/**********************************************************************************
	函数:	PlayMS_SetRenderMode
	描述:	指定渲染模式(Windows平台), PlayMS_Play之前调用有效
	参数:	nPort				端口号
			nMode				渲染模式
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetRenderMode(LONG nPort, ENUM_TYPE_RENDER nMode);

	/**********************************************************************************
	函数:	PlayMS_InitThirdPartyLibrary
	描述:	初始化第三方解密库
	参数:	nPort			端口号
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_InitThirdPartyLibrary(LONG nPort, const char* kmcSvrIP,int kmcSvrPort,const char* macAddr);

	/**********************************************************************************
	函数:	PlayMS_SetDecodeStrategy
	描述:	设置解码策略,错误码流花屏或跳秒
	参数:	nPort			端口号
			nAVSyncType		16:表示解码中遇到frame不连续，提前返回
							8: 表示解码中遇到码流数据不符合协议当成解码错误
							0: 表示解码中遇到码流数据不符合协议继续解码，错误码流会花屏
	返回:	成功返回TRUE,失败返回FALSE.
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetDecodeStrategy(LONG nPort, int nStrategyType);

	/**********************************************************************************
	函数:	PlayMS_SetAVSyncType
	描述:	设置音视频播放策略
	参数:	nPort			端口号
			nAVSyncType		码流播放基准参数
							nAVSyncType=0，以视频为基准；nAVSyncType=1，以音频为基准
	返回:	成功返回TRUE, 失败返回FALSE
	**********************************************************************************/
	PLAYMS_API BOOL CALLMETHOD PlayMS_SetAVSyncType(LONG nPort,	ENUM_SYNC_TYPE nAVSyncType);

#ifdef	__cplusplus
}
#endif

#endif // _AL_PLAY_V2_H