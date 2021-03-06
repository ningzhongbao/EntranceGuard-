#ifndef _AL_NET_STRUCT_COLLECTION_H
#define _AL_NET_STRUCT_COLLECTION_H

#include "netdefcollection.h"
#include "netenumcollection.h"

#if !defined(WIN32) && !defined(WIN64)
#include "../Platform/platform.h"
#endif

/*****************************************************************************************
 *							netmanager library 结构体定义									 *
 *****************************************************************************************/

//////////////////////////////////////////////////////////////////////////////////////
// 图形元素相关结构

// 尺寸
typedef struct 
{
	int                 nWidth;                     // 宽度
	int                 nHeight;                    // 高度
} STU_SIZE;

// 二维空间点
typedef struct 
{
	short            nx;
	short            ny;
} STU_POINT, *P_STU_POINT;

// 一对坐标点
typedef struct 
{
	STU_POINT        stuPoints[2];
}STU_POINT_PAIR;

// 区域或曲线顶点信息
typedef struct
{
	int			nPointNum;				// 顶点数
	STU_POINT   stuPoints[COUNT(20)];	// 顶点信息
}STU_POLY_POINTS, *P_STU_POLY_POINTS;

// 区域
typedef struct 
{
	long    left;
	long    top;
	long    right;
	long    bottom;
} STU_RECT_L, *P_STU_RECT_L;

typedef struct
{
	int     nLeft;
	int     nTop;
	int     nRight;
	int     nBottom;
} STU_RECT_I, *P_STU_RECT_I;

typedef struct
{
	float     fLeft;
	float     fTop;
	float     fRight;
	float     fBottom;
} STU_RECT_F, *P_STU_RECT_F;

typedef struct
{
	double    dleft; 
	double    dright; 
	double    dtop;
	double    dbottom;
} STU_RECT_D, *P_STU_RECT_D;

// 图片分辨率
typedef struct
{
	unsigned short   snWidth;		// 宽
	unsigned short   snHeight;		// 高
}STU_RESOLUTION, *P_STU_RESOLUTION;

// 颜色RGBA
typedef struct
{
	int                 nRed;                       // 红
	int                 nGreen;                     // 绿
	int                 nBlue;                      // 蓝
	int                 nAlpha;                     // 透明
}STU_COLOR_RGBA, *P_STU_COLOR_RGBA;

// 颜色BCSH
typedef struct 
{
	int                 nBirghtness;                // 亮度
	int                 nContrast;                  // 对比度
	int                 nSaturation;                // 饱和度
	int                 nHue;                       // 色调
} STU_COLOR_BCSH;

//////////////////////////////////////////////////////////////////////////////////////
// 时间元素相关结构
                                                               
typedef struct 
{
	// 当表示录像时间段时，按位表示四个使能
	int		bEnable;
	int		nStartHour;
	int		nStartMinute;
	int		nStartSecond;
	int		nEndHour;
	int		nEndMinute;
	int		nEndSecond;
} STU_TIME_SECTION, *P_STU_TIME_SECTION;

typedef struct 
{
	unsigned int			dwYear;                  // 年
	unsigned int			dwMonth;                 // 月
	unsigned int			dwDay;                   // 日
	unsigned int			dwHour;                  // 时
	unsigned int			dwMinute;                // 分
	unsigned int			dwSecond;                // 秒
} STU_TIME, *P_STU_TIME;

typedef struct 
{
	unsigned int			dwYear;                  // 年
	unsigned int			dwMonth;                 // 月
	unsigned int			dwDay;                   // 日
	unsigned int			dwHour;                  // 时
	unsigned int			dwMinute;                // 分
	unsigned int			dwSecond;                // 秒
	unsigned int			dwMillisecond;           // 毫秒
	unsigned int			dwReserved[2];           // 保留字段
} STU_TIME_EX,*P_STU_TIME_EX;

// 时间定义
typedef struct
{
	DWORD                second:6;                // 秒    1-60        
	DWORD                minute:6;                // 分    1-60        
	DWORD                hour:5;                  // 时    1-24        
	DWORD                day:5;                   // 日    1-31        
	DWORD                month:4;                 // 月    1-12        
	DWORD                year:6;                  // 年    2000-2063    
} STU_TIME_MIN, *P_STU_TIME_MIN;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 设备系统信息

// 设备信息
typedef struct
{
	char szDeviceType[32];			// 设备类型
	char szDeviceClass[32];			// 设备类别
	char szSerialNumber[64];		// 设备序列号
	unsigned char reserved[1280];	// 保留位
}STU_SYS_DEVICE_INFO, *P_STU_SYS_DEVICE_INFO;

// 软件版本信息
typedef struct  
{
	char szVersion[32];				// 软件版本信息
	char szBuildDate[32];			// 版本发布时间
	unsigned char reserved[256];	// 保留位
}STU_SYS_SOFTWARE_VERSION, *P_STU_SYS_SOFTWARE_VERSION;

// 硬件版本信息
typedef struct 
{
	char szVersion[32];				// 软件版本信息
	char szModel[32];				// 版本发布时间
	unsigned char reserved[256];	// 保留位
}STU_SYS_HARDWARE_VERSION, *P_STU_SYS_HARDWARE_VERSION;

// 处理器信息
typedef struct
{
	char szModel[32];				// 处理器信息
	char szFrequency[16];			// 处理器频率
	unsigned char nUsage;			// 处理器利用率（%）
	unsigned char nTemperature;		// 处理器温度(摄氏度)
	unsigned char reserved1[2];		// 字节对齐
	unsigned char reserved2[60];	// 保留位
}STU_SYS_PROCESSOR_INFO, *P_STU_SYS_PROCESSOR_INFO;

// 内存信息
typedef struct
{
	unsigned int	nTotalSize;		// 总大小（字节）
	unsigned int	nFreeSize;		// 空余大小(字节)
	unsigned char   reserved[64];	// 预留位
}STU_SYS_MEMORY_INFO, *P_STU_SYS_MEMORY_INFO;

// 系统信息
#define MAX_LANGUAGE_LENGTH			20
#define MAX_LANGUAGE_NUM			32
typedef struct  
{
	BOOL						bAppAutoStart;				// 应用程序是否自启动
	int							nSupportLangNum;			// 支持的语言种数
	// 语言字符串,","分隔，如“SimpleChinese,English”，最大支持 32 种语言
	char						szLanguages[MAX_LANGUAGE_LENGTH * MAX_LANGUAGE_NUM];			
	int							nProcessorNum;				// 处理器个数
	STU_SYS_PROCESSOR_INFO		stuProcessorInfoArray[16];	// 处理器信息数组(最大16个处理器信息)
	STU_SYS_DEVICE_INFO			stuDeviceInfo;				// 设备信息
	STU_SYS_SOFTWARE_VERSION	stuSoftWareVer;				// 软件信息
	STU_SYS_HARDWARE_VERSION	stuHardWareVer;				// 硬件信息
	STU_SYS_MEMORY_INFO			stuMemoryInfo;				// 内存信息
	unsigned char				reserved[2048];				// 保留位
}STU_SYS_INFO, *P_STU_SYS_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 事件/报警结构体定义

typedef struct
{
	BYTE					nPicType;					// 图片类型 1、普通；2、合成；3、抠图
	BYTE					reserved1[3];				// 保留字段
	STU_RESOLUTION			stuResolution;				// 分辨率信息
	BYTE					reserved[1016];				// 保留字段
}STU_EVENT_COMMON_INFO, *P_STU_EVENT_COMMON_INFO;

typedef struct
{
	unsigned int			nObjcetID;					// 物体唯一标识 ID
	char					szObjectType[32];			// 物体类型描述
	STU_RECT_L				stuBoundingBox;				// 包围盒
	unsigned char			nBelief;					// 清晰度[0-255]	 值越大表示清晰
	unsigned char			nQuality;					// 质量度[0-255] 值越大质量越好
	BYTE					reserved1[2];				// 字节对齐
	float					fBlur;						// 模糊度, 0 表示最清晰，值越大越模糊
	float					fPosePitch;					// 上下俯仰角度
	float					fPoseRoll;					// 左右摇摆角度
	float					fPoseYaw;					// 水平旋转角度
	unsigned char			reserved2[56];				// 保留字段
}STU_EVENT_FACE_INFO, *P_STU_EVENT_FACE_INFO;

typedef struct  
{
	unsigned int			nPersonID;						// 人员 ID
	char					szName[128];					// 人脸图别名
	EM_SEX_TYPE				emSexType;						// 性别
	STU_TIME				stBirthday;						// 生日
	char					szCertificateType[64];			// 证件类型
	char					szID[128];						// 证件 ID
	BYTE					reserved1[32];					// 保留参数1
	char					szCountry[64];					// 国别
	char					szProvince[64];					// 省份
	char					szCity[128];					// 所在城市
}STU_EVENT_PERSON_INFO, *P_STU_EVENT_PERSON_INFO;

typedef struct  
{
	char					szFaceToken[64];			// 人脸标识符
	float					fSearchScore;				// 人脸识别评分 [0-100]
	float					fSearchThreshold;			// 人脸识别阈值 [0-100]
	STU_EVENT_PERSON_INFO	stPersonInfo;				// 人脸相关的人员信息
	BYTE					reserved[64];				// 保留位
}STU_EVENT_FACE_RECOGNIZE_INFO, *P_STU_EVENT_FACE_RECOGNIZE_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////
// FACE
/////////////////////////////////////////////////////////////////////////////////////////////////////

// N-人脸检测-背景全图
typedef struct
{
	int						nChannel;					// 通道号
	unsigned int			nGroupID;					// 组编号
	unsigned int			nIndexInGroup;				// 组内序号
	unsigned int			nCountInGroup;				// 组包含的图片数目
	char					szEvent[64];				// 事件类型
	char					szClass[64];				// 大类类型
	char					szAction[64];				// 动作类型
	double					dPTS;						// PTS
	unsigned int			nUTC;						// UTC
	unsigned short			nUTCMS;						// UTCMS
	char					szTimeZone[16];				// 时区字符串（GMT+08:00）
	int						nTimeZoneMS;				// 与UTC时区毫秒差（东八区 = -8*60*60*1000）
	unsigned short			nFaceCount;					// 大图内的人脸个数
	P_STU_EVENT_FACE_INFO	pstuFaceInfoArray;			// 人脸抠图信息数组
	STU_TIME_EX				stuTime;					// 事件时间
	unsigned int			nFirstObjectID;				// 第一个抠图的物体 ID 号
	unsigned int			nLastObjectID;				// 最后一个抠图的物体 ID 号
	unsigned char			reserved1[212];				// 保留字节1
	STU_EVENT_COMMON_INFO	stuCommInfo;				// 公共信息描述
	unsigned char			reserved2[1024];			// 保留字段2
}STU_EVENT_FACE_SNAP_WHOLE, *P_STU_EVENT_FACE_SNAP_WHOLE;

// N-人脸检测-人脸抠图
typedef struct
{
	int						nChannel;					// 通道号
	unsigned int			nGroupID;					// 组编号
	unsigned int			nIndexInGroup;				// 组内序号
	unsigned int			nCountInGroup;				// 组包含的图片数目
	char					szEvent[64];				// 事件类型
	char					szClass[64];				// 大类类型
	char					szAction[64];				// 动作类型
	double					dPTS;						// PTS
	unsigned int			nUTC;						// UTC
	unsigned short			nUTCMS;						// UTCMS
	unsigned char			reserved1[2];				// 保留字段1(字节对齐)
	char					szTimeZone[16];				// 时区字符串（GMT+08:00）
	int						nTimeZoneMS;				// 与UTC时区毫秒差（东八区 = -8*60*60*1000）	
	STU_TIME_EX				stuTime;					// 事件时间
	unsigned char			reserved2[220];				// 保留字节2
	STU_EVENT_FACE_INFO		stuFaceInfo;				// 人脸信息
	STU_EVENT_COMMON_INFO	stuCommInfo;				// 公共信息描述
	unsigned char			reserved3[1024];			// 保留字段3
}STU_EVENT_FACE_SNAP_PART, *P_STU_EVENT_FACE_SNAP_PART;

// N-人脸识别-人脸抠图
typedef struct
{
	int									nChannel;					// 通道号
	unsigned int						nGroupID;					// 组编号
	unsigned int						nIndexInGroup;				// 组内序号
	unsigned int						nCountInGroup;				// 组包含的图片数目
	char								szEvent[64];				// 事件类型
	char								szClass[64];				// 大类类型
	char								szAction[64];				// 动作类型
	double								dPTS;						// PTS
	unsigned int						nUTC;						// UTC
	unsigned short						nUTCMS;						// UTCMS
	unsigned char						reserved1[2];				// 保留字段1(字节对齐)
	char								szTimeZone[16];				// 时区字符串（GMT+08:00）
	int									nTimeZoneMS;				// 与UTC时区毫秒差（东八区 = -8*60*60*1000）	
	STU_TIME_EX							stuTime;					// 事件时间
	unsigned int						nObjectID;					// 物体 ID
	char								szFaceGroupAlias[128];		// 人脸库别名
	int									nPass;						// 人脸识别是否通过 0-不通过 1-通过
	unsigned char						reserved2[64];				// 保留字节2
	int									nFaceRecognizeInfoCount;	// 实际人脸识别结果数目	
	STU_EVENT_FACE_RECOGNIZE_INFO		stFaceRecognizeInfoArr[MAX_FACE_REC_INFO_NUM];	// 人脸识别结果数组
	STU_EVENT_COMMON_INFO				stuCommInfo;				// 公共信息描述
	unsigned char						reserved3[1024];			// 保留字段3
}STU_EVENT_FACE_RECOGNIZE_CUTOUT, *P_STU_EVENT_FACE_RECOGNIZE_CUTOUT;

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Traffic
/////////////////////////////////////////////////////////////////////////////////////////////////////

// 交通公共信息
typedef struct
{
	// 车道号（设备中的自定义车道号）
	int					nLane;
	// 速度    单位Km/h
	int					nSpeed;
	// 保留位
	unsigned char		reserved[2560];                      
}STU_TRAFFIC_COMMON_INFO, *P_STU_TRAFFIC_COMMON_INFO;

// 交通物体信息
typedef struct
{
	unsigned int			nObjectID;					// 物体ID
	unsigned int			nRelatedID;					// 关联物体ID 
														// 如果物体ID是车牌，关联物体ID是车辆；反则关联物体ID是车牌	
	char					szObjectType[32];			// 物体类别（车牌 - "Plate" / 车辆 - "Car"）
	char					szObjectSubType[32];		// 物体子类型（车牌 - 车牌类型 / 车辆 - 车辆类型）
	char					szLabel[32];				// 标识（物体是车牌表示车牌号码，物体是车辆表示车标）
	char					szColor[32];				// 颜色（物体是车牌表示车牌颜色，物体是车辆表示车身颜色）
	STU_RECT_L				stuBoundingBox;				// 包围盒
	unsigned char			reserved[2080];				// 保留字段
}STU_TRAFFIC_OBJECT_INFO, *P_STU_TRAFFIC_OBJECT_INFO;

// 交通 - 卡口信息
typedef struct
{
	int							nChannel;					// 通道号
	unsigned int				nGroupID;					// 组编号
	unsigned int				nIndexInGroup;				// 组内序号
	unsigned int				nCountInGroup;				// 组包含的图片数目
	char						szEvent[64];				// 事件类型
	char						szClass[64];				// 大类类型
	char						szAction[64];				// 动作类型
	double						dPTS;						// PTS
	unsigned int				nUTC;						// UTC
	unsigned short				nUTCMS;						// UTCMS
	unsigned char				reserved1[2];				// 保留位1（字节对齐）
	char						szTimeZone[16];				// 时区字符串（GMT+08:00）
	int							nTimeZoneMS;				// 与UTC时区毫秒差（东八区 = -8*60*60*1000）
	STU_TIME_EX					stuTime;					// 事件时间
	unsigned char				reserved2[220];				// 保留字节2
	STU_TRAFFIC_COMMON_INFO		stuTrafficCommInfo;			// 交通公共信息
	STU_TRAFFIC_OBJECT_INFO		stuPlateInfo;				// 车牌信息
	STU_TRAFFIC_OBJECT_INFO		stuVehicleInfo;				// 车辆信息
	STU_EVENT_COMMON_INFO		stuCommInfo;				// 公共信息
	unsigned char				reserved3[1280];			// 保留字节3
}STU_EVENT_TRAFFIC_PASS, *P_STU_EVENT_TRAFFIC_PASS;

// 交通 - 卡口抠图信息
typedef struct
{
	int							nChannel;					// 通道号
	unsigned int				nGroupID;					// 组编号
	unsigned int				nIndexInGroup;				// 组内序号
	unsigned int				nCountInGroup;				// 组包含的图片数目
	char						szEvent[64];				// 事件类型
	char						szClass[64];				// 大类类型
	char						szAction[64];				// 动作类型
	double						dPTS;						// PTS
	unsigned int				nUTC;						// UTC
	unsigned short				nUTCMS;						// UTCMS
	unsigned char				reserved1[2];				// 保留位1（字节对齐）
	char						szTimeZone[16];				// 时区字符串（GMT+08:00）
	int							nTimeZoneMS;				// 与UTC时区毫秒差（东八区 = -8*60*60*1000）
	STU_TIME_EX					stuTime;					// 事件时间
	unsigned char				reserved2[220];				// 保留字节2
	STU_TRAFFIC_COMMON_INFO		stuTrafficCommInfo;			// 交通公共信息
	STU_TRAFFIC_OBJECT_INFO		stuObjectInfo;				// 车牌/车辆信息
	STU_EVENT_COMMON_INFO		stuCommInfo;				// 公共信息
	unsigned char				reserved3[1280];			// 保留字节3
}STU_EVENT_TRAFFIC_PASS_CUTOUT, *P_STU_EVENT_TRAFFIC_PASS_CUTOUT;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 音视频
/////////////////////////////////////////////////////////////////////////////////////////////////////

// 回调视频数据帧的帧参数结构体
typedef struct
{
    BYTE                 encode;                 // 编码类型
    BYTE                 frametype;              // I = 0, P = 1, B = 2...
    BYTE                 format;                 // PAL - 0, NTSC - 1
    BYTE                 size;                   // CIF - 0, HD1 - 1, 2CIF - 2, D1 - 3, VGA - 4, QCIF - 5, QVGA - 6 ,
                                                 // SVCD - 7,QQVGA - 8, SVGA - 9, XVGA - 10,WXGA - 11,SXGA - 12,WSXGA - 13,UXGA - 14,WUXGA - 15, LFT - 16, 720 - 17, 1080 - 18
    DWORD                fourcc;                 // 如果是H264编码则总为0，MPEG4这里总是填写FOURCC('X','V','I','D');
    DWORD                reserved;               // 保留
    STU_TIME             struTime;               // 时间信息
} STU_VIDEO_FRAME_PARAM;

// 回调音频数据帧的帧参数结构体
typedef struct
{
    BYTE                channels;                // 声道数
    BYTE                samples;                 // 采样 
												 // 例:  0 - 8000,   1 - 11025,	 2 - 16000,   3 - 22050, 
												 //      4 - 32000,  5 - 44100,  6 - 48000
    BYTE                depth;                   // 采样深度 取值8或者16等。直接表示
    BYTE                param1;                  // 0 - 指示无符号，1-指示有符号
    DWORD               reserved;                // 保留
} STU_CBPCM_DATA_PARAM;

//回调YUV数据的参数结构体
typedef struct
{
    long                nWidth;                 // 图像的宽
    long                nHeight;                // 图像的高
    DWORD               reserved[8];            // 保留
} STU_CBYUV_DATA_PARAM;

// 音频格式信息
typedef struct
{
    BYTE                byFormatTag;                    // 编码类型，如0：PCM
    WORD                nChannels;                      // 声道数
    WORD                wBitsPerSample;                 // 采样深度            
    DWORD               nSamplesPerSec;                 // 采样率
} STU_AUDIO_FORMAT_INFO, *P_STU_AUDIO_FORMAT_INFO;

// 日夜模式配置参数
typedef struct
{
	BYTE	byMode;						// 色彩切换模式；0-总是彩色，1-根据亮度或时间自动切换，2-总是黑白
	BYTE	byDayNightSensitivity;		// 日夜模式切换灵敏度，范围1-3
	BYTE	byDayNightSwitchDelay;		// 日夜模式切换延迟时间	单位秒，范围2-10
	BYTE	reserved[5];
} STU_CAMERA_DAY_NIGHT_PARAM;

// 视频颜色配置
typedef struct
{
	BYTE      byBrightness;				// 亮度
	BYTE      byContrast;				// 对比度
	BYTE      bySaturation;				// 饱和度
	BYTE      byHue;					// 色调
} STU_CAMERA_COLOR;

// 图像3D降噪相关参数
typedef struct
{
	BYTE	byTridimDenoise;				// 是否开启3D降噪，0-关闭，1-开启，2-只开启视频，3-只开启图片
	BYTE	reserved[3];
	BYTE	byTridimIntensity[2];			// 三维降噪时域降噪强度，下标表示视频、图片，范围0~100
	BYTE	byTridimIntensitySpatial[2];	// 三维降噪空域降噪强度，下标表示视频、图片，范围0~100
} STU_CAMERA_3D_DENOISE;

// 曝光和增益参数
typedef struct
{
	BYTE	bGainAuto;				// 自动增益
	BYTE	byGainMin;				// 自动增益下限	范围0~100，小于GainMax
	BYTE	byGainMax;				// 自动增益上限	范围0~100
	BYTE	byGain;					// 固定增益调节	0~100
} STU_CAMERA_EXPOSURE;

// 光圈调节参数
typedef struct
{
	BYTE	bIrisAuto;			// 自动光圈使能
	BYTE	byIrisType;			// 光圈类型	0-正序光圈P90，1-反序光圈P90，2-DC光圈，3-固定光圈
	BYTE	reserved[2];
	UINT	dwIris;				// 精确的手动光圈大小
} STU_CAMERA_IRIS;

// 白平衡模式调节参数
typedef struct
{
	EM_WHITE_BALANCE	emWhiteBalance;				// 白平衡模式
	BYTE				byColorTemperatureLevel;	// 色温等级调节，白平衡为"WHITEBALANCE_CT_CUSTOM"模式下有效	0~255
	BYTE				byGainRed;					// 红色增益调节，白平衡为"Custom"模式下有效	0~100
	BYTE				byGainBlue;					// 蓝色增益调节，白平衡为"Custom"模式下有效	0~100
	BYTE				byGainGreen;				// 绿色增益调节，白平衡为"Custom"模式下有效	0~100
	BYTE				byPartWhiteBalanceWeight;	// 权重参数，用来调整局部白平衡和全局白平衡的权重比例	范围0-100
} STU_CAMERA_WHITE_BALANCE;

// 去雾模式参数
typedef struct
{
	BYTE		byMode;			// 透雾模式	0-关闭,1-自动,2-手动
	WORD		wValue;			// 手动模式强度
} STU_CAMERA_DEFOG;

// 测光模式
typedef struct
{
	BYTE		byMode;			// 测光类型 0-全局测光，1-局部测光，2-背光补偿，3-强光抑制
	BYTE		byIntensity;	// 测光强度	0-关闭，1-弱，2-中，3-强
} STU_CAMERA_METERING;

// 摄像头参数配置
typedef struct
{
	DWORD						dwSize;				// 结构体大小
	STU_CAMERA_DAY_NIGHT_PARAM	stuDayNightParam;	// 日夜模式参数								VideoInDayNightParam
	STU_CAMERA_COLOR			stuColor[3];		// 颜色配置，下标：0-白天，1-晚上，2-其它   VideoInColor
	STU_CAMERA_IRIS				stuIris[3];			// 光圈配置，下标：0-白天，1-晚上，2-其它   VideoInIrisEx
	STU_CAMERA_3D_DENOISE		stu3DDenoise;		// 图像3D降噪相关参数						VideoInPre3DDenoise
	STU_CAMERA_EXPOSURE			stueExposure[3];	// 增益调节，下标：视频、图片流、抓拍帧     VideoInExposure
	STU_CAMERA_WHITE_BALANCE	stuWhiteBalance[3];	// 白平衡参数，下标：视频、图片流、抓拍帧   VideoInWhiteBalance
	STU_CAMERA_DEFOG			stuDefog[3];		// 去雾配置，下标：0-白天，1-黑夜，2-其它	VideoInDefog
	STU_CAMERA_METERING			stuMetering;		// 测光配置									VideoInMetering
} STU_CFG_CAMERA;

typedef struct
{
	BYTE						bValue;				// 该时段是否有效， 1 有效， 0 无效
	INT							iStartHour;			// 开始时间-小时
	INT							iStartMinute;		// 开始时间-分钟
	INT							iStartSecond;		// 开始时间-秒
	INT							iEndHour;			// 结束时间-小时
	INT							iEndMinute;			// 结束时间-分钟
	INT							iEndSecond;			// 结束时间-秒
}STU_TIME_SECTION_SCHEDULE;

typedef struct
{
	BYTE						bControlMode;		//录像模式 0-自动，1-手动,2-关闭
	STU_TIME_SECTION_SCHEDULE	stuTimeSchedule[WEEK_SECTION][TIME_SECTION];//录像计划

}STU_CFG_RECORD_PLAN;

typedef struct
{
	UINT						uPackSize;		//录像打包长度
	UINT						uPackTime;		//录像打包时间
	BYTE						bPackType;		//录像打包类型	0是按时间录像
	UINT						uPreRecordTime;	//预录时间
	BYTE						bStreamType;	//码流类型,0是主码流，1是副码流1,2是副码流2
}STU_CFG_RECORD_OPTIONS;

//录像配置
typedef struct
{
	DWORD						dwSize;				// 结构体大小
	STU_CFG_RECORD_PLAN			stuRecordPlan;		//录像计划参数
	STU_CFG_RECORD_OPTIONS		stuRecordOptions;	//录像选项

}STU_CFG_RECORD;

//存储点
typedef struct
{
	BOOL bSupportFtp;
	BOOL bSupportLocal;
	BOOL bSupportUsb;
}STU_CFG_STORAGE_POINT;

//存储策略
typedef struct
{
	BOOL bOverWrite;

}STU_CFG_STORAGE_POLICY;

//存储配置
typedef struct
{
	DWORD						dwSize;				// 结构体大小
	STU_CFG_STORAGE_POINT		stuStorPoint[2];//[0]是录像，1是抓图
	STU_CFG_STORAGE_POLICY		stuStoragePolicy;
}STU_CFG_STORAGE;

typedef struct
{
	INT							iMouth;
	INT							iWeek;
	INT							iDay;
	INT							iHour;
}STU_DST_TIME;

//夏令时配置
typedef struct
{
	DWORD						dwSize;				// 结构体大小
	STU_DST_TIME				stuDstStartTime;
	STU_DST_TIME				stuDstEndTime;
	BOOL						bEnable;
	INT							iTimeZone;		//正数标示东，负数标示西，[-12 - 13]
}STU_CFG_DST;

//NTP配置
typedef struct
{
	DWORD						dwSize;				// 结构体大小
	BOOL						bEnable;
	char						bDomainName[64];
	UINT						uInterval;
	UINT						uPort;

}STU_CFG_NTP;

//自动重启配置
typedef struct
{
	DWORD						dwSize;				// 结构体大小
	BOOL						bEnable;
	UINT						uWeekDay;			//周几重启,[0-6],0代表周日，6代表周六
	UINT						uHour;				//几点重启,[0-23]
}STU_CFG_AUTO_MAINTAIN;

typedef struct
{
	UINT						uBaudRate;	//波特率,取值为1200, 2400 ,4800, 9600, 19200, 38400, 57600, 115200
	BYTE						bDataBits;	//数据位,取值为5, 6, 7, 8
	BYTE						bCheckMode;	//校验模式，0表示"Even", 1表示"Mark", 2表示"None", 3表示"Odd", 4表示"Space"
	BYTE						bStopBits;	//停止位，0表示"1", 1表示"1.5", 2表示"2"
}STU_CFG_COMM_ATTRIBUTE;

typedef struct 
{
	STU_CFG_COMM_ATTRIBUTE		stuAttribute;		//串口属性
	BOOL						bEnable;			//串口使能
	BYTE						bProtocol;			//0代表普通串口，1代表透明串口
}STU_CFG_COMM_ITEM;

//串口配置
typedef struct
{
	UINT						uNums;//串口数目
	STU_CFG_COMM_ITEM*			stuCommCfg;//串口配置,内存由外部申请和释放
}STU_CFG_COMM;

typedef struct
{
	BYTE 						bProtocol[3];//支持的串口协议，0代表普通串口，1代表透明串口
	BYTE 						bBusType;//总线类型，0代表"RS232"，1代表"RS485"
	BYTE 						bCommunication;//支持的通信模式，0代表半双工，1代表全双工
}STU_CFG_COMM_PARAM;

//串口能力集
typedef struct
{
	UINT 						uCommCount;//设备所支持的串口数目
	STU_CFG_COMM_PARAM*			stuItems;//串口能力集参数
}STU_CFG_COMM_CAPS;

//Telenet 配置
typedef struct
{
	DWORD						dwSize;	// 结构体大小
	BOOL						bEnale; //telnet使能

}STU_CFG_TELNET;

//日志查询条件
typedef struct
{
	char					cStartTime[32];//日志查询开始时间
	char					cEndTime[32];//日志查询结束时间
	char					cMainType[32]; //主日志类型
	char					cSubType[32];//次日志类型

}STU_CFG_LOG_CONDITION;

//日志详细信息
typedef struct
{
	char					cRemoteIP[32]; 
	INT						iChannel;
	char					cConfigName[32];
	char					cNetAdapter[32];

}STU_CFG_LOG_DETAIL;

//日志查询结果
typedef struct
{
	char					cLogTime[32];//该日志记录时间
	char					cOperUserName[32];//操作用户名
	char					cMainType[32]; //主日志类型
	char					cSubType[32];//次日志类型
	STU_CFG_LOG_DETAIL		stuLogDetail;//日志详细信息

}STU_CFG_LOG_INFO;

#define MAX_LOG_AMOUNT		16
typedef struct
{
	STU_CFG_LOG_INFO		stuResult[MAX_LOG_AMOUNT];//一次最多查询16条日志信息
	UINT					uTotal;					//查询到的总共的日志条数
	UINT					uCurAmount;				//当前返回的日志条数
}STU_CFG_LOG_RESULT;

//日志查询,支持多次查询
typedef struct
{
	STU_CFG_LOG_CONDITION	stuSearchCondition;//日志查询条件
	STU_CFG_LOG_RESULT		stuLogResult;//	日志查询结果

}STU_CFG_LOG;

typedef struct
{
	BYTE					bIPType;//ip地址类型:0代表单个ip地址,1代表ip范围,目前只支持ipv4
	char					cBeginIPAddr[64];//起始ip地址,用于bIPType为0和1的情况
	char					cEndIPAddr[64];//终止ip地址,仅用于bIPType为1情况

	//下面两个仅仅用于修改
	char					cNewBeginIPAddr[64];
	char					cNewEndIPAddr[64];
}STU_CFG_NETWHITE_BLACK_INFO;

//黑白名单配置
typedef struct
{
	DWORD								dwSize;// 结构体大小
	BYTE								bType;//黑白名单类型:0-无;1-黑名单,2-白名单
	BYTE								bOperType;//操作类型：0-获取,1-增加,2-删除,3-修改

	UINT								uCount;//指定stuData中元素个数
	STU_CFG_NETWHITE_BLACK_INFO*		stuData;//黑白名单信息,内存由外部申请和释放

}STU_CFG_NETWHITE_BLACK;

//修改用户时.只支持修改备注信息和用户级别,不支持修改用户名和密码
typedef struct
{
	char						cComment[32];//备注信息
	BYTE						bLevel;//用户级别，0是管理员,1是操作者,2是普通用户,管理员无法删除
	char						cUserName[32];//用户名
	char						cPassword[32];//密码
}STU_CFG_USER_INFO;

typedef struct
{
	BYTE						bOperType;//1:增加,2:删除,3:修改
	STU_CFG_USER_INFO			stuUserInfo;

}STU_CFG_USER_SET;

typedef struct
{
	char						cComment[32];//备注信息
	BYTE						bLevel;//用户级别，0是管理员,1是操作者,2是普通用户,管理员无法删除
	char						cUserName[32];//用户名
	char						cPassword[32];//密码

}STU_CFG_ADD_USER;//用于增加用户

typedef struct
{
	char						cUserName[32];//用户名

}STU_CFG_DELETE_USER;//用于删除用户

typedef struct
{
	char						cComment[32];//备注信息
	BYTE						bLevel;//用户级别，0是管理员,1是操作者,2是普通用户,管理员无法删除
	char						cUserName[32];//用户名
	char						cOldPassword[32];//密码
	char						cNewPassword[32];//新的密码

}STU_CFG_MODIFY_USER;//用于修改用户

typedef struct
{
	UINT						uCount;//想要获取的用户个数
	STU_CFG_USER_INFO*			stuUserInfo;//用户信息，由外部申请和释放

}STU_CFG_USER_GET;

typedef  struct
{
	char						cClientAddr[32];
	char						cClientType[32];
	char						cLoginTime[32];
	BYTE						bUserLevel;
	char						cUserName[32];
}STU_CFG_USER_ONLINE_INFO;

typedef struct
{
	UINT								uCount;//想要获取的用户个数
	STU_CFG_USER_ONLINE_INFO*			stuUserInfo;//用户信息，由外部申请和释放

}STU_CFG_USER_ONLINE;

//抠图配置结构体
typedef struct
{
	BOOL								bEnable;
	BYTE								bType;			// 0是人脸抠图; 1是半身抠图; 2是全身抠图; 3是车牌抠图

}STU_CFG_DIG_PICTURE;

//叠加配置
typedef struct
{
	BOOL		bMajorStreamIntelliTrack;//是否叠加跟踪信息
}STU_CFG_OVERLAP;

//抓图配置
typedef struct
{
	BOOL		bPictureUpload;//是否显示背景图
}STU_CFG_GRAP_PIC;

//叠加与抓图配置
typedef struct
{
	STU_CFG_OVERLAP			stuOverLap;
	STU_CFG_GRAP_PIC		stuGrapPic;
}STU_CFG_OVERLAP_PIC;

//检测区域配置,左上角与右下角坐标[0,0]-[8192,8192]
typedef struct
{
	INT		left;
	INT		top;
	INT		right;
	INT		bottom;
}STU_CFG_INTELLI_SCENCE;

typedef struct
{
	BOOL		bCaptureEnable;

	BOOL		bRecordEnable;
	INT			bPreRecordTime;//预录时间,取值是[0,5]
	INT			iRecordLatch;//录像延时时间

	BOOL		bAlarmOutEnable;
	INT			iAlarmOutChannels;//联动的报警输出通道数，最多联动16个
	INT			iAlarmOutChannelsValue[16];
	INT			iAlarmOutLatch;
	
}STU_CFG_INTELLI_RULE_EVENT_HANDLE;

//智能规则配置
typedef struct
{
	BOOL								bEnable;
	STU_CFG_INTELLI_RULE_EVENT_HANDLE	stuEventHandle;

}STU_CFG_INTELLI_RULE;

//智能参数配置
typedef struct
{
	STU_CFG_INTELLI_SCENCE				stuIntlliScence;
	STU_CFG_INTELLI_RULE				stuIntelliRule;
}STU_CFG_INTELLI_PARAM;

typedef struct
{
	BOOL								bEnable;//28181使能
	UINT								uAlarmInChannelNum;//报警输入通道数
	char								cAlarmInId[32];//报警输入通道编号
	UINT								uChannelNum;//通道总数
	char								cChannelId[32];//通道编号
	char								cCivilCode[16];//行政区识别码
	char								cUserName[32];//用户名,即设备id
	char								cPassword[32];//注册密码
	UINT								uKeepAliveInterval;//心跳时间间隔
	UINT								uLocalSipPort;//本地sip端口号
	UINT								uMaxTimeoutCount;//最大心跳超时时间
	char								cSipDomain[32];//域名
	char								cSipServerId[32];//sip服务器id
	char								cSipServerIP[16];//sip服务器ip
	UINT								uSipServerPort;//sip服务器端口

}STU_CFG_GB28181_PARAM;

//报警输入联动参数
typedef struct
{
	BOOL						bAlarmOutEnable;
	UINT						uAlarmOutLatch;
	UINT						uAlarmOutChannels;//联动的通道个数,最多联动16个通道
	UINT						uAlarmOutChannelsValue[16];//联动的通道值				
	STU_TIME_SECTION_SCHEDULE	stuTimeSchedule[WEEK_SECTION][TIME_SECTION];//布防时间
}STU_ALARM_EVENT_HANDLE;

//报警输入参数
typedef struct
{
	BOOL						bEnable;			//报警输入使能
	BYTE						bSensorType;		//传感器类型,0是常开,1是常闭
	STU_ALARM_EVENT_HANDLE		stuAlarmHandle;		//报警联动参数

}STU_CFG_ALARM_IN_PARAM;

//报警输出参数
typedef struct
{
	BYTE						bMode;//输出模式,0是自动输出,1是强制开启报警,2是强制关闭报警
}STU_CFG_ALARM_OUT_PARAM;


//报警输入输出参数
typedef struct
{
	UINT								uAlarmInChannels;//报警输入通道数
	STU_CFG_ALARM_IN_PARAM*				stuAlarmInParams;//报警输入参数,内存由外部申请和释放
	UINT								uAlarmOutChannels;//报警输出通道数
	STU_CFG_ALARM_OUT_PARAM*			stuAlarmOutParams;//报警输出参数,内存由外部申请和释放

}STU_CFG_ALARM_PARAM;

//编码能力集
typedef struct
{
	
	UINT							uMinMajorStreamBitrate;//设备支持的最小码率
	UINT							uMaxMajorStreamBitrate;//设备支持的最大码率
	UINT							uMaxExtraStreams;//设备支持的最大辅码流数
	UINT							uSupportedStandardNums;//设备最大支持的视频制式数,最大支持4个
	BYTE							bSupportedStandardValues[4];// EM_STANDARD_TYPE 类型

}STU_CFG_ENCODE_CAPS;

typedef struct
{
	UINT							uMiniBitRate;
	UINT							uMaxBitRate;

	UINT							uCompressionTypeNums;//最多10个 EM_VIDEO_STREAM_CODE_TYPE
	BYTE							bCompressionTypeValus[10];

	UINT							uH264ProfilesTypeNums;//最多10个
	BYTE							bH264ProfilesTypeValues[10];//  EM_H264_ENCODE_LEVEL
	 
	UINT							uMaxFps;
	UINT							uMaxRoiCount;

	UINT							uResolutionTypeNums;			// 最多10个
	BYTE							bResolutionTypeValus[10];		// EM_VIDEO_STREAM_RESOLUTION_TYPE

}STU_CFG_VIDEOCONFIG_CAPS;

//编码配置能力集
typedef struct
{
	INT								iMainStreamCapsCount;			// 最大3个
	STU_CFG_VIDEOCONFIG_CAPS*		stuMainStreamVideoCaps;
	INT								iExtraStreamCapsCount;			// 最大3个
	STU_CFG_VIDEOCONFIG_CAPS*		stuExtraStreamVideoCaps;
	INT								iCaptureStreamCapsCount;		// 最大3个
	STU_CFG_VIDEOCONFIG_CAPS*		stuCaptureStreamCaps;
}STU_CFG_CONFIG_CAPS;

//编码参数能力集合
struct STU_CFG_ENCODECAPS_PARAM
{
	STU_CFG_CONFIG_CAPS			stuCfgConfigCaps;
	STU_CFG_ENCODE_CAPS			stuCfgEncodeCaps;
};

typedef struct
{
	BYTE								bCompressionType;//编码类型,取值为 EM_VIDEO_STREAM_CODE_TYPE
	BYTE								bCtrlType;//码流控制类型,取值为 EM_VIDEO_FORMA_CTRL_TYPE
	BYTE								bResolutionType;//分辨率类型,取值为 EM_VIDEO_STREAM_RESOLUTION_TYPE
	UINT								uFPS;//帧率
	UINT								uBitRate;//码率大小
	UINT								uGop;//i帧间隔
	UINT								uQuality;//图像质量,取值[1-6]
	BYTE								bH264SVCTLayer;//h264的svc层数,仅在h264编码时有效
	BYTE								bH264EncodeLevel;//h264编码级别,仅用于h264编码,取值为枚举  EM_H264_ENCODE_LEVEL

}STU_CFG_ENCODE_VIDEO_CONFIG_PARAM;

typedef struct
{
	BOOL											bEnable;//使能
	STU_CFG_ENCODE_VIDEO_CONFIG_PARAM				stuEncodeVideoConfig;
}STU_CFG_ENCODE_CONFIG_PARAM;
//编码配置
typedef struct
{
	UINT								uMainStreamNums;//主码流个数
	STU_CFG_ENCODE_CONFIG_PARAM*		stuMainStreamEncodeConfig;//由外部进行内存申请和释放
	UINT								uExtraStreamNums;//辅码流个数
	STU_CFG_ENCODE_CONFIG_PARAM*		stuExtraStreamEncodeConfig;//由外部进行内存申请和释放
	UINT								uCaptureStreamNums;//抓图码流个数
	STU_CFG_ENCODE_CONFIG_PARAM*		stuCaptureStreamEncodeConfig;//由外部进行内存申请和释放
}STU_CFG_ENCODE_CONFIG;

//编码参数配置
typedef struct
{
	INT									iChannelNo;		//通道号
	STU_CFG_ENCODE_CONFIG				stuEncodeConfig;//编码参数配置

}STU_CFG_ENCODE_PARAM;

#define MAX_NETCARD_NUMS				4//网卡数量最大值

//目前暂时只支持ipv4地址
typedef struct  
{
	char								cIpAddress[32];
	char								cSubnetMask[32];
	char								cDefaultGateway[32];
	char								cMainDnsServer[32];
	char								cExtraDnsServer[32];
	
}STU_CFG_ADDRESS_CONFIG;

typedef struct
{
	BOOL								bDefaultNetCard; //是否是默认网卡,默认网卡只有一张
	BOOL								bDhcpEnable;	 //是否开启dhcp使能
	char								cNetCardName[32];//网卡名 "eth0","wlan0"
	STU_CFG_ADDRESS_CONFIG				stuCfgAddress;

}STU_CFG_NETCARD_INFO;

//网卡配置
typedef struct
{
	UINT								uNetCardNum;//真实的网卡数量
	STU_CFG_NETCARD_INFO				stuNetCardinfo[MAX_NETCARD_NUMS];
			
}STU_CFG_NETCARD_CONFIG;

//端口配置
typedef struct
{
	UINT								uHttpPort;
	UINT								uRtspPort;
	UINT								uServerPort;
}STU_CFG_PORT_CONFIG;

//wifi使能配置
typedef struct
{
	BOOL								bEnable;//wifi使能
}STU_CFG_WIFI_CONFIG;

typedef struct
{
	char									cSsidName[64];//ssid名称
	char									cSsidPasswd[64];//ssid密码
	UINT									uAuthMode;//认证模式
	UINT									uencType;//加密类型
	INT										irssiQuality;//信号强度,单位是dBM
	UINT									uConnectedStatus;//链接状态,0是未连接;1是链接

}STU_CFG_WIFI_INFO;

//wifi操作配置
typedef struct  
{
	UINT								uOperType;//0:扫描;1是链接指定wifi;2是断开指定wifi
	UINT								uNums;	 //指定WiFi数目
	STU_CFG_WIFI_INFO*					stuInfos;//wifi信息,内存由用户进行内存申请和释放

}STU_CFG_WIFI_OPER_CONFIG;

typedef struct  
{
	BOOL							bRecordEnable;			// 录像使能，必须同时有 RecordChannels
	int								nRecordLatch;			// 预录时间 [10s-300s]，单位：秒
	int								nRecordChannelNum;		// 实际录像通道个数
	// 录像通道数组
	int								nRecordChannels[MAX_RECORD_CHANNEL_NUM];
	
	BOOL							bAlarmOutEnable;		// 报警输出使能
	int								nAlarmOutLatch;			// 报警输入停止后，输出延时时间 [1s,300s]，单位：秒
	int								nAlarmOutChannelNum;	// 实际报警输出通道个数
	// 报警输出通道数组
	int								nAlarmOutChannels[MAX_ALARM_OUT_CHANNEL_NUM];
	
	BOOL							bCaptureEnable;			// 抓图使能
	int								nCapturePreRecordTime;	// 图片关联录像的预录时间，不能大于通用的预录时间，单位：秒
	int								nCaptureChannelNum;		// 实际抓图通道数
	// 抓图通道数组
	int								nCaptureChannels[MAX_CAPTURE_CHANNEL_NUM];
	
	// 时段信息
	STU_TIME_SECTION_SCHEDULE		stTimeScheduleArray[WEEK_SECTION][TIME_SECTION];

	// 假日信息
	BOOL							bHolidayEnable;
	STU_TIME_SECTION_SCHEDULE		stHolidaySchedule[TIME_SECTION];

}STU_EVENT_HANDLER;

typedef struct
{
	unsigned int							nGroupID;			// 人脸组 ID
	unsigned int							nTopRank;			// 上报识别得分超过阈值的排名靠前的底库人脸个数
	STU_EVENT_HANDLER						stEventHandler;		// 联动事件
}STU_CFG_FACE_GROUP_RECOGNIZE_RULE;

typedef struct  
{
	int										nRuleCount;			// 人脸识别规则实际数目
	// 人脸识别规则信息
	STU_CFG_FACE_GROUP_RECOGNIZE_RULE		stRuleArray[MAX_FACE_GROUP_NUM];
}STU_CFG_FACE_GROUP_RECOGNIZE_RULES;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 文件信息
typedef struct
{
	// 通道号
	int							channel;
	// 文件名
	char						filename[240];
	// 文件大小
	int							size;
	// 开始时间
	STU_TIME					starttime;
	// 结束时间
	STU_TIME					endtime;
	// 抓拍时间
	STU_TIME					snaptime;
	// 文件类型
	EM_ST_FILE_TYPE				filetype;
	// 视频码流类型
	EM_VIDEO_STREAM_TYPE		emVStreamType;
	// 事件信息，Json格式数组
	char*						pEvents;
	// 预留位
	BYTE						reserved[64];
}STU_T_FILE, *P_STU_T_FILE;

/**********************************************************************************
函数：		fPlaybackDataCallBack
参数：		[in] lPlaybackHandle：		回放句柄
			[in] dwDataType:		    固定为 0（暂不启用）
			[in] pBuffer:				回放数据缓存
			[in] dwBufSize:				回放数据大小
			[in] dwUser:				用户参数
返回值：		/
说明：		回放数据回调函数原形
**********************************************************************************/
typedef int (CALLBACK *fPlaybackDataCallBack)(
	LLONG lPlaybackHandle, 
	DWORD dwDataType,
	BYTE *pBuffer,
	DWORD dwBufSize,
	LDWORD dwUser);

typedef struct 
{
    DWORD                      dwSize; 
    int                        nChannels[COUNT(64)];		// 预览通道号
    int                        nChannelNum;                 // 预览通道数 
    int                        nType;                       // 回放文件类型，0：普通录像；1：报警录像；2：移动检测；3：卡号录像；4：图片
    STU_TIME                   stStartTime;                 // 回放开始时间
    STU_TIME                   stEndTime;                   // 回放结束时间
    int                        nFPS;                        // 帧率,1~25
    int                        nBitRate;                    // 码流值,192~1024
    char                       szResolution[COUNT(64)];		// 分辨率  
    int                        nWaitTime;                   // 超时等待时间 
    HWND                       hWnd;                        // 视频播放窗口句柄
    fPlaybackDataCallBack	   fDownLoadDataCallBack;       // 视频数据回调
    LDWORD                     dwDataUser;					// 用户数据
}STU_MULTI_PLAYBACK_PARAM_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	// 设备端升级的进度
	int nProgress;
	// 设备状态描述
	char szStatus[64];
}STU_UPGRADE_PROGRESS_INFO, *P_STU_UPGRADE_PROGRESS_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//用户管理相关定义

// 权限信息
typedef struct
{
    DWORD               dwID;
    char                name[64];
    char                memo[64];
} STU_AUTHORITY_INFO;

// 用户信息
typedef struct
{
    DWORD               dwID;
    DWORD               dwGroupID;
    char                name[64];
    char                passWord[64];
    DWORD               dwRightNum;
    DWORD               rights[128];
    char                memo[64];
    DWORD				dwReuse;
} STU_USER_INFO;

// 用户组信息
typedef struct
{
    DWORD               dwID;
    char                name[64];
    DWORD               dwRightNum;
    DWORD               rights[128];
    char                memo[64];
} STU_USER_GROUP_INFO;

// 用户信息表
typedef struct
{
    DWORD					dwRightNum;						// 权限信息
    STU_AUTHORITY_INFO		rightList[128];
    DWORD					dwGroupNum;						// 用户组信息
    STU_USER_GROUP_INFO		groupList[32];
    DWORD					dwUserNum;						// 用户信息
    STU_USER_INFO			userList[256];
    DWORD					dwSpecial;						// 用户复用能力
	BYTE					reserved[256];					
} STU_USER_MANAGE_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    DWORD               dwSize;
    LLONG               lPlayBackHandle;        // 回放句柄, Net_MultiPlayBack 接口返回值
    int                 nChannels[64];			// 预览通道号
    int                 nChannelNum;            // 预览通道数 
}STU_CTRL_MULTI_PLAYBACK_CHANNEL_INFO;

typedef struct
{
    DWORD           dwSize;                          
    char            szDevSerial[64];				// 序列号
    char            szToken[MAX_PATH];              // 令牌
}STU_CB_AUTO_REGISTER_INFO;

// 公网代理注册相关结构体
typedef struct
{
    DWORD               dwSize;   
    char                szDstIp[64];				// 服务器IP
    int                 nDstPort;					// 服务器端口号 
    DWORD               dwConnectType;				// 连接类型：0 主连接
    char                szToken[MAX_PATH];			// 设备通道唯一ID令牌
}STU_CLOUD_SERVICE_CONNECT_PARAM;

typedef struct
{
    DWORD               dwSize;  
    DWORD               dwConnectState;				// 当前连接状态：1成功，0失败
    char                szMessage[128];				// 连接状态信息
}STU_CLOUD_SERVICE_CONNECT_RESULT;

// 设备信息
typedef struct
{
    BYTE                sSerialNumber[64];			// 序列号
    BYTE                byAlarmInPortNum;			// 报警输入个数
    BYTE                byAlarmOutPortNum;			// 报警输出个数
    BYTE                byDiskNum;					// 硬盘个数
    BYTE                byType;						// 设备类型
	int                 nChanNum;					// 通道个数
    int					nLimitLoginTime;			// 在线超时时间，为0表示不限制登陆，非0表示限制的分钟数
    int					nLeftLogTimes;				// 剩余登陆次数，0表示此参数无效
    char                reserved[32];				// 保留
} STU_DEVICE_INFO, *P_STU_DEVICE_INFO;

// 修改设备配置返回信息
typedef struct
{
    int					nType;						// 类型
    int					nResultCode;                // 返回码；0：成功，1：失败，2：数据不合法，3：暂时无法设置，4：没有权限
    int					nRebootFlag;                // 重启标志；0：不需要重启，1：需要重启才生效
    BYTE				reserved[16];				// 保留    
} STU_DEVICE_SET_RESULT;

// 请求监视或回放的错误返回信息
typedef struct
{
    DWORD               dwResultCode;               // 错误返回码
    LLONG               lPlayHandle;                // 相应句柄值
    BYTE                reserved[64];				// 保留位                         
}STU_DEVICE_PLAY_RESULT;

// 请求语音对讲的错误返回信息
typedef struct
{
    DWORD               dwResultCode;               // 错误返回码
    LLONG               lTalkHandle;                // 相应句柄值
    BYTE                reserved[64];				// 保留位                         
}STU_DEVICE_TALK_RESULT;

// 串口基本属性
typedef struct
{
	int					nType;
	char				szName[32];
    int					nDataBit;					// 数据位；0：5，1：6，2：7，3：8
    int					nStopBit;					// 停止位；0：1位，1：1.5位，2：2位
    int					nParity;					// 校验位；0：无校验，1：奇校验；2：偶校验; 3:标志校验; 4:空校验
    int					nBaudRate;					// 波特率
	BYTE				reserved[32];
} STU_SERIAL_PORT_ATTRIBUTE;

// 网络登入参数
typedef struct  
{
	int					nNetworkType;                           // 网络类型, 0-LAN, 1-WAN
    int                 nLoginTimeout;							// 登入时的等待超时时间(ms)，默认 5000 ms
    int                 nConnectTimeout;						// 连接等待超时时间(ms)，默认 2000 ms
    int                 nConnectTryNum;                         // 连接尝试次数，默认1次
    int                 nSubConnectTimespan;					// 子连接之间的等待时间(ms)，默认 10 ms
    int                 nGetDevInfoTimeout;						// 获取设备信息超时时间(ms)，默认 2000 ms  
    int                 nGetSubConnInfoTimeout;					// 获取子连接信息超时时间(ms)，为 0 默认 1000 ms
    int                 nSearchRecordTimeout;					// 按时间查询录像文件的超时时间(ms),为0默认为 3000 ms
    int                 nDetectSubDisconnTimespan;				// 检测子链接断线等待时间(ms)，为0默认为 60 * 1000 ms
    int                 nConnectBufSize;                        // 每个连接接收数据缓冲大小(Byte)，为 0 默认 1 * 1024 * 1024
	int                 nPicBufSize;                            // 实时图片接收缓冲大小(Byte)，为 0 默认为 2 * 1024 * 1024	
    int					nPlaybackBufSize;						// 回放数据接收缓冲大小(MB)，为 0 默认为 2M
    BYTE                reserved[128];							// 保留位
} STU_NET_PARAM, *P_STU_NET_PARAM;

///////////////////////////////////////////////////////////////////////////////////////////

typedef struct 
{
	BOOL				valid;									// 是否有效		
	char				szName[32];								// 网卡名称
	char				szMac[40];								// 网卡物理Mac地址
	BYTE				reserved1[64];							// 保留位
	char				IPv4_Address[16];						// IPv4 地址
	char				IPv4_SubnetMask[16];					// IPv4 子网掩码
	char				IPv4_DefaultGateway[16];				// IPv4 默认网关
	BOOL				IPv4_DhcpEnable;						// IPv4 DHCP 使能位
	char				IPv6_Address[64];						// IPv6 地址
	char				IPv6_SubnetMask[64];					// IPv6 子网掩码
	char				IPv6_DefaultGateway[64];				// IPv6 默认网关
	BOOL				IPv6_DhcpEnable;						// IPv6 DHCP 使能位
	BYTE				reserved2[128];							// 保留位
}STU_SEARCH_NETCARD, *P_STU_SEARCH_NETCARD;

#define MAX_SEARCH_NETCARD_NUM	8

// 对应 Net_StartSearchDevices接口
typedef struct
{
	int					nProtocolType;							// 搜索协议类型  
																// 0 - 第一代； 1 - 第二代
	BOOL				bActivated;								// 是否已激活
	char				szDeviceClass[64];						// 设备类别
	char				szDeviceType[64];						// 设备型号
	char				szSerialNumber[64];						// 设备序列号
	char				szSoftVersion[32];						// 软件版本号
	char				szVendorName[64];						// 厂商名称
	char				szMac[40];								// 当前网卡 MAC
	int					nCurNetCardIndex;						// 当前的网卡索引
	int					nDtsPort;								// DTS 端口
	int					nHttpPort;								// HTTP 端口
	char				szDefaultNetCard[16];					// 默认网卡
	STU_SEARCH_NETCARD	stuNetCardArr[MAX_SEARCH_NETCARD_NUM];	// 网卡数组
	BYTE				reserved[256];							// 保留位
}STU_DEVICE_SEARCH_INFO, *P_STU_DEVICE_SEARCH_INFO;

typedef struct
{
    DWORD               dwSize;           
    int                 nIpNum;          // 当前搜索的IP个数
    char                szIP[256][64];	 // 具体待搜索的IP信息
}STU_DEVICE_IP_SEARCH_INFO, *P_STU_DEVICE_IP_SEARCH_INFO;

typedef struct
{
	DWORD				dwSize;
	// 是否具有 MAC 搜索条件
	BOOL				bMac;
	char				szMac[40];
	// 是否具有 IPv4 搜索条件
	BOOL			    bIPv4;
	char				szStartIPv4[16];
	char				szEndIPv4[16];
	char				reserved1[64];
	// 是否具有 IPv6 搜索条件
	BOOL				bIPv6;
	char				szStartIPv6[64];
	char				szEndIPv6[64];
	char				reserved2[128];
}STU_DEVICE_SEARCH_CONDITION_INFO, *P_STU_DEVICE_SEARCH_CONDITION_INFO;

typedef struct  
{
	DWORD				dwSize;
	char				szMac[40];
	char				szPassword[64];
	char				szEncType[32];
	BYTE				reserved[256];
}STU_DEVICE_ACTIVATE_INFO, *P_STU_DEVICE_ACTIVATE_INFO;

// UDP单播/组播获取公钥输入参数
typedef struct
{
	// 结构体大小
	DWORD				dwSize;
	// mac 地址十六进制字符串
	char				szMac[40];
	// 保留参数
	BYTE				reserved[128];
}STU_RSA_PUBLICKEY_IN_PARAM, *P_STU_RSA_PUBLICKEY_IN_PARAM;

// UDP单播/组播获取公钥输出参数
typedef struct  
{
	// 结构体大小
	DWORD				dwSize;
	// mac 地址十六进制字符串
	char				szMac[40];
	// RSA modules 十六进制字符串
	char				szModules[1024];
	// RSA exponent 十六进制字符串
	char				szExponent[64];
	// 保留参数
	BYTE				reserved[256];
}STU_RSA_PUBLICKEY_OUT_PARAM, *P_STU_RSA_PUBLICKEY_OUT_PARAM;

typedef struct  
{
	// 一般只修改指定网卡的网络参数
	char				szEthname[64];							// 网卡名称
	char				szMac[40];								// 网卡物理Mac地址
	char				szUser[64];								// 用户名
	char				szPassword[64];							// 用户密码
	BYTE				reserved1[64];							// 保留位1
	unsigned short		nDtsPort;								// 服务端口
	unsigned short		nHttpPort;								// HTTP 端口
	unsigned short		nHttpsPort;								// HTTPS 端口
	unsigned short		nRtspPort;								// RTSP 端口
	BYTE				reserved2[64];							// 保留位2
	char				IPv4_Address[16];						// IPv4 地址
	char				IPv4_SubnetMask[16];					// IPv4 子网掩码
	char				IPv4_DefaultGateway[16];				// IPv4 默认网关
	BOOL				IPv4_DhcpEnable;						// IPv4 DHCP 使能位
	char				IPv6_Address[64];						// IPv6 地址
	char				IPv6_SubnetMask[64];					// IPv6 子网掩码
	char				IPv6_DefaultGateway[64];				// IPv6 默认网关
	BOOL				IPv6_DhcpEnable;						// IPv6 DHCP 使能位
	BYTE				reserved3[128];							// 保留位3
}STU_DEVICE_NETCFG_MODIFY_INFO, *P_STU_DEVICE_NETCFG_MODIFY_INFO;

///////////////////////////////////////////////////////////////////////////////////////////

// DDNS域名信息
typedef struct
{
    char                szServerType[32];		// 服务器类型
    char                szServerIp[256];		// 服务器ip或者域名
    DWORD               dwServerPort;			// 服务器端口
    char                szDomainName[256];		// 域名，如 www.edu.org
    char                szUserName[64];			// 用户名
    char                szUserPswd[64];          // 密码
    BYTE                reserved[224];			// 保留位
}STU_DDNS_DOMAIN_INFO;

// 主动注册参数配置
typedef struct  
{
    char                szServerIp[64];             // 注册服务器IP
    int                 nServerPort;                // 端口号
    BYTE                reserved[3];				// 对齐
    BYTE                bServerIpExEn;              // 注册服务器IP扩展使能,0-表示无效, 1-表示有效
    char                szServerIpEx[60];           // 注册服务器IP扩展，支持ipv4,ipv6,域名等类型的IP
} STU_SERVER_INFO;

typedef struct  
{
    DWORD               dwSize;
    BYTE                bServerNum;                 // 支持的最大ip数
    STU_SERVER_INFO		lstServer[12];
    BYTE                bEnable;                    // 使能
    char                szDeviceID[32];             // 设备id
    char                reserved[98];
} STU_REGISTER_SERVER_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// IP信息
typedef struct 
{
    DWORD               dwIPNum;					// IP个数
    char                szIP[256][64];				// IP
    char                reserved[32];				// 保留
} STU_IP_FILTER_INFO;

// IP过滤配置结构体
typedef struct
{
    DWORD               dwSize;
    DWORD               dwEnable;					// 使能
    DWORD               dwType;                     // 当前名单类型：0：白名单 1：黑名单
    STU_IP_FILTER_INFO	BannedIP;					// 黑名单
    STU_IP_FILTER_INFO	TrustIP;                    // 白名单
    char                byReserve[256];             // 保留
} STU_IP_FILTER_CFG;

// MAC信息
typedef struct 
{
    DWORD					dwSize; 
    DWORD					dwMacNum;
    char					szMac[512][40];
} STU_MAC_FILTER_INFO;

// MAC过滤配置结构体
typedef struct
{
    DWORD					dwSize;
    DWORD					dwEnable;                 // 使能
    DWORD					dwType;                   // 当前名单类型：0：白名单 1：黑名单
    STU_MAC_FILTER_INFO		stuBannedMac;             // 黑名单Mac
    STU_MAC_FILTER_INFO		stuTrustMac;              // 白名单Mac
} STU_MAC_FILTER_CFG;

// MAC，IP过滤信息
typedef struct
{
    DWORD       dwSize;
    char        szMac[40];
    char        szIp[64];
}STU_MAC_IP_INFO;

// MAC,IP过滤配置结构体
typedef struct
{
    DWORD					dwSize;							// 使用时，用初始化为本结构体大小
    DWORD					dwEnable;						// 使能
    DWORD					dwType;							// 当前名单类型：0：白名单 1：黑名单
    DWORD					dwBannedMacIpNum;				// 黑名单MAC,IP个数(MAC,IP一一对应)
    STU_MAC_IP_INFO			stuBannedMacIp[512];			// 黑名单Mac,IP
    DWORD					dwTrustMacIpNum;				// 白名单MAC,IP个数(MAC,IP一一对应)
    STU_MAC_IP_INFO			stuTrustMacIp[512];				// 白名单Mac,IP
} STU_MAC_IP_FILTER_CFG;

// IP修改配置
typedef struct
{
    int             nStructSize;
    char            szRemoteIP[64];			// 前端设备IP
    char            szSubmask[64];			// 子网掩码
    char            szGateway[64];			// 网关
    char            szMac[40];				// MAC地址
    char            szDeviceType[32];		// 设备类型
}STU_IP_MODIFY_PARAM;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**********************************************************************************
函数：		fMultiFileDownLoadPosCallBack
参数：		[in] lDownLoadHandle：			文件下载句柄	
			[in] dwFileID:					下载文件的序号
			[in] dwFileTotalSize:			当前文件的总数据大小
			[in] dwDownLoadSize:			当前文件已下载的数据大小
			[in] nError:					0 - 无错误；
											-1 - 缓存区不足
											-2 - 反序列化错误
											-3 - 出现错误包
											-255 - 申请内存错误
			[in] dwUser:					用户参数
			[in] pReserved					预留参数
返回值：		/
说明：		多文件下载进度回调函数原型
**********************************************************************************/
typedef void (CALLBACK *fMultiFileDownLoadPosCallBack)(
	LLONG lDownLoadHandle, 
	DWORD dwFileID, 
	DWORD dwFileTotalSize, 
	DWORD dwDownLoadSize, 
	int nError, 
	LDWORD dwUser,
	void* pReserved);

typedef struct
{
    DWORD               dwSize;
    DWORD               dwFileID;							// 文件ID
    int                 nFileSize;							// 查询到的文件大小
    char                szSourceFilePath[MAX_PATH];			// 查询到的文件路径
    char                szSavedFileName[MAX_PATH];			// 文件保存路径
}STU_FILE_DOWNLOAD_PARAM;

typedef struct
{
	DWORD							dwSize;
	int								nFileCount;				// 待下载文件数
    STU_FILE_DOWNLOAD_PARAM*		pFileInfos;				// 待下载文件信息
    fMultiFileDownLoadPosCallBack	cbPosCallBack;			// 进度回调函数
    LDWORD							dwUserData;				// 用户数据
}STU_IN_MULTI_FILE_DOWNLOAD_PARAM;

typedef struct
{
    DWORD               dwSize;
    LLONG               lDownLoadHandle;					// 下载句柄
}STU_OUT_MULTI_FILE_DOWNLOAD_PARAM;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    DWORD						dwSize;
    char						szFilePath[MAX_PATH];		// 文件绝对路径
}STU_LOCAL_FILE_INFO;

typedef struct
{
    DWORD               dwSize;
    char                szIP[MAX_PATH];                     // 远程设备IP
    unsigned int        nPort;                              // 远程设备端口
    char                szName[64];							// 登陆远程设备用户名
    char                szPassword[64];						// 登陆远程设备密码
    BYTE                byProtocolType;                     // 远程设备协议类型
    BYTE                reserved[3];						// 保留位
    char                szFilePath[MAX_PATH];               // 文件绝对路径
    int                 nStartCluster;                      // 起始簇号
    int                 nDiskNo;							// 盘号
}STU_REMOTE_FILE_INFO;

// 文件/目录信息
typedef struct 
{
	DWORD               dwSize;
	BOOL                bDirectory;                     // 是否文件夹
	char                szPath[MAX_PATH];               // 路径
	STU_TIME            stuCreateTime;                  // 创建时间
    STU_TIME            stuModifyTime;                  // 修改时间
    INT64               nFileSize;                      // 文件大小
    char                szFileType[64];					// 文件类型
} STU_COMMON_FILE_INFO;

// 文件位置信息
typedef struct
{
    DWORD					dwSize;
    BOOL					bFileType;						// 服务器本地文件/远程设备文件
    STU_LOCAL_FILE_INFO		stuLocalFile;					// 本地文件信息
    STU_REMOTE_FILE_INFO	stuRemoteFile;					// 远程文件信息
}STU_FILE_LOCATION_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 主动注册服务器信息
typedef struct 
{
    LONG            lConnectionID;                      // 连接ID
    char            szServerIp[64];						// 主动注册服务器的IP
    int             nPort;                              // 主动注册服务器端口0- 65535
    int             nState;                             // 服务器的状态：0－注册失败；1-注册成功; 2-连接失败
    char            reserved[32];
} STU_AUTO_REGISTER_INFO;

typedef struct 
{
    DWORD						dwSize;
    int							nRegisterSeverCount;				// 主动注册服务器个数
    STU_AUTO_REGISTER_INFO		stuDevRegisterSeverInfo[128];		// 各主动注册服务器信息
    char						reserved[256];
} STU_SERVER_AUTO_REGISTER_INFO, *P_STU_SERVER_AUTO_REGISTER_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 多通道打开视频输入
typedef struct
{
    int							nChannelID;			// 通道号
    EM_REALPLAY_STREAM_TYPE     realplayType;		// 视频类型
    char						reserve[32];
}STU_IN_MULTIPLAY_PARAM;

// 多通道打开视频输出
typedef struct
{
    int							nChannelID;			// 通道号
    LLONG						lRealHandle;		// 实时监视句柄
    char						reserved[32];
}STU_OUT_MULTIPLAY_PARAM;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    DWORD               dwSize;
    const char*         pszPath;                // 文件名
    BOOL                bDirectory;             // 是否文件夹
} STU_IN_CREATE_REMOTE_FILE_PARAM;

typedef struct 
{
    DWORD               dwSize;
} STU_OUT_CREATE_REMOTE_FILE_PARAM;

typedef struct
{
    DWORD               dwSize;
    const char**        pszPath;                // 文件路径数组指针
    int                 nFileCount;             // 文件路径数量
} STU_IN_REMOVE_REMOTE_FILES_PARAM;

typedef struct 
{
    DWORD               dwSize;
} STU_OUT_REMOVE_REMOTE_FILES_PARAM;

typedef struct
{
    DWORD               dwSize;
    const char*         pszOldPath;             // 旧文件名
    const char*         pszNewPath;             // 新文件名
} STU_IN_RENAME_REMOTE_FILE_PARAM;

typedef struct 
{
    DWORD               dwSize;
} STU_OUT_RENAME_REMOTE_FILE_PARAM;

typedef struct
{
    DWORD               dwSize;
    const char*         pszPath;                        // 路径
    BOOL                bFileNameOnly;                  // 只获取文件名称
} STU_IN_LIST_REMOTE_FILE_PARAM;

typedef struct 
{
    DWORD                   dwSize;
    STU_COMMON_FILE_INFO*   pstuFiles;					// 文件信息数组, 用户分配内存
    int                     nMaxFileCount;              // 文件信息数组大小
    int                     nRetFileCount;              // 返回的文件数量
} STU_OUT_LIST_REMOTE_FILE_PARAM;

typedef struct
{
    DWORD               dwSize;
    char*				pszFileSrc;                     // 源文件路径
    char*				pszFileDst;                     // 目标文件路径
	char*				pszFolderDst;					// 目标文件夹路径
    unsigned int        nPacketLen;                     // 文件分包大小(字节)
} STU_IN_UPLOAD_REMOTE_FILE_PARAM;

typedef struct
{
    DWORD               dwSize;
} STU_OUT_UPLOAD_REMOTE_FILE_PARAM;

typedef struct
{
    DWORD               dwSize;
    const char*         pszFileName;                    // 需要下载的文件名
    const char*         pszFileDst;                     // 存放文件路径
} STU_IN_DOWNLOAD_REMOTE_FILE_PARAM;

typedef struct
{
    DWORD               dwSize;
} STU_OUT_DOWNLOAD_REMOTE_FILE_PARAM;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    DWORD                   dwSize;
    const char*             pszFilePath;            // 文件路径
    DWORD                   dwOutput;               // 输出途径
} STU_IN_PLAY_AUDIO_FILE_INFO;

typedef struct
{
    DWORD                   dwSize;
} STU_OUT_PLAY_AUDIO_FILE_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    DWORD					dwSize;
    unsigned char*			pInBinBuf;                      // 二进制输入数据缓冲
    DWORD					dwInBinBufSize;                 // 二进制输入数据长度
} STU_BIN_DATA;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 分区状态
typedef struct
{
    DWORD						dwSize;
    int							nStatus;					// 分区状态，0-正常，1-错误 
    DWORD						dwTotalSize;				// 分区总容量，字节为单位
    DWORD						dwRemainSize;				// 剩余容量，字节为单位
}STU_HDD_PARTITION_STATUS;

// 硬盘状态
typedef struct
{
    DWORD						dwSize; 
    int							nState;						// 硬盘状态，0-正常，1-错误   
    DWORD						dwTotalSize;				// 硬盘总容量，字节为单位
	int							nPartitionNum;              // 分区数
    STU_HDD_PARTITION_STATUS	stuPartitions[32];			// 分区状态  
}STU_HDD_STATUS;

//////////////////////////////////////////////////////////////////////////////////////////

// 异步注册设备回调函数原形（暂不启用）
typedef void (CALLBACK *fHaveLoginCallBack)(
	LLONG lLoginID, 
	char *pchDevIP,
	LONG nDevPort, 
	BOOL bOnline, 
	STU_DEVICE_INFO stuDeviceInfo, 
	int nError, 
	LDWORD dwUser,
	void *reserved);

//////////////////////////////////////////////////////////////////////////////////////////

/**********************************************************************************
函数：		fLoadPosCallBack
参数：		[in] lHandle：				文件下载句柄
			[in] dwTotalSize:		    文件的总大小
			[in] dwDownLoadSize:		已下载的文件大小
			[in] dwUser:				用户参数
返回值：		/
说明：		回放/下载进度回调函数原形
**********************************************************************************/
typedef void (CALLBACK *fLoadPosCallBack)(
	LLONG lHandle, 
	DWORD dwTotalSize, 
	DWORD dwDownLoadSize,
	LDWORD dwUser);

// 按文件回放输入参数
typedef struct 
{
	DWORD                   dwSize;
	STU_T_FILE*				lpRecordFile;                   // 录像文件信息
	HWND                    hWnd;                           // 窗口句柄
	fLoadPosCallBack		cbDownLoadPos;					// 回放进度回调
	LDWORD                  dwPosUser;                      // 进度回调用户数据
	fPlaybackDataCallBack	fDownLoadDataCallBack;          // 回放数据回调
	LDWORD                  dwDataUser;                     // 数据回调用户数据
	char                    szDstIP[64];					// 设备IP
	char					reserved[64];					// 保留位
}STU_IN_PLAYBACK_BYFILE_PROXY_PARAM;

// 按文件回放输出参数-代理使用
typedef struct 
{
	DWORD                   dwSize;
}STU_OUT_PLAYBACK_BYFILE_PROXY_PARAM;

// 按时间回放输入参数-代理使用
typedef struct 
{
	DWORD                   dwSize;
	int                     nChannelID;                     // 通道号
	P_STU_TIME              lpStartTime;                    // 开始时间
	P_STU_TIME              lpStopTime;                     // 结束时间
	HWND                    hWnd;                           // 窗口句柄
	fLoadPosCallBack		cbDownLoadPos;                  // 回放进度回调
	LDWORD                  dwPosUser;                      // 进度回调用户数据
	fPlaybackDataCallBack	fDownLoadDataCallBack;          // 回放数据回调
	LDWORD                  dwDataUser;                     // 数据回调用户数据
	char                    szDstIP[64];					// 设备IP
	char					reserved[64];					// 保留位
}STU_IN_PLAYBACK_BYTIME_PROXY_PARAM;

// 按时间回放输出参数-代理使用
typedef struct 
{
	DWORD                   dwSize;
}STU_OUT_PLAYBACK_BYTIME_PROXY_PARAM;

//////////////////////////////////////////////////////////////////////////////////////////

// 网络资源
typedef struct
{
	int						nIPChanneIn;					// IP通道接入速度, 单位: kbps
	int						nNetRemain;						// 网络接收剩余能力, 单位: kbps
	int						nNetCapability;					// 网络接收总能力, 单位: kbps
	int						nRemotePreview;					// 远程预览能力, 单位: kbps
	int						nRmtPlayDownload;				// 远程回放及下载能力, 单位: kbps
	int						nRemoteSendRemain;				// 远程发送剩余能力, 单位: kbps
	int						nRemoteSendCapability;			// 远程发送总能力, 单位: kbps
	BYTE                    reserved[32];					// 保留位
} STU_NET_RESOURCE_STATUS;

// 设备公共信息
typedef struct
{
	char                     szVendor[32];			// 生产厂商
	char                     szDviceType[32];		// 设备型号
	char                     szVersion[32];			// 设备版本信息
	char                     szSerialNo[64];		// 设备编号
	BYTE                     reserved[96];			// 保留位
}STU_DEVICE_COMMON_INFO;

// 回调数据(异步接口)
typedef struct 
{
	int                  nResultCode;            // 返回码；0：成功
	char                 *pBuf;                  // 接收数据, 缓冲是由用户开辟的，从接口形参传入
	int                  nRetLen;                // 接收长度
	LLONG                lOperateHandle;         // 操作句柄
	void*                userdata;               // 操作对应用户参数
	char                 reserved[16];
} STU_CALLBACK_DATA, *P_STU_CALLBACK_DATA;

///////////////////////////////////////////////////////////////////////////////////////////////
// 智能分析-人脸上图（特殊处理）

#define NET_CMD_PICSTREAM_FACE			0x0001

/**********************************************************************************
函数：		fAnalyzeDataCallBack
参数：		[in] lRevcID：				智能分析句柄	
			[in] lCommand:				命令类型，NET_CMD_PICSTREAM_xxx
										当前固定为 NET_CMD_PICSTREAM_FACE
			[in] pBuffer:				智能分析上报的数据
			[in] nBufLen:				智能分析上报的数据大小
			[in] pUser:					用户参数
返回值：		int
说明：		智能分析数据回调
**********************************************************************************/
typedef int (CALLBACK *fNetPicStreamCallBackCV1)(
	LLONG lRevcID,
	LLONG lCommand,
	void* pBuffer,
	int nBufLen, 
	void* pUser);

typedef struct tagNetPicParamCV1
{
	int 						nSize;
	int							nChannel;
	fNetPicStreamCallBackCV1	cbNetPicStreamCV1;
	void*						pUser;
} NetPicParamCV1, *pNetPicParamCV1;

typedef struct tagPicTimeCV1
{
	unsigned int uiYear;
	unsigned int uiMonth;
	unsigned int uiDay;
	unsigned int uiHour;
	unsigned int uiMinute;
	unsigned int uiSecond;
	unsigned int uiMillisecond;
}PicTimeCV1, *pPicTimeCV1;

typedef struct tagPicDataCV1
{
	int						iWidth;
	int						iHeight;
	int						iDataLen;
	char*					pcPicData;
}PicDataCV1, *pPicDataCV1;

typedef struct tagFaceAttributeCV1
{
	int					iType;
	int					iValue;
}FaceAttributeCV1, *pFaceAttributeCV1;

typedef struct tagFacePicDataCV1
{
	int					iFaceId;				// 人脸物体ID	
	int					iDrop;					// 暂时不用
	int					iFacelevel;				// 暂时不用
	STU_RECT_L			tFaceRect;				// 图片矩形框 （8192 * 8192 坐标系）
	int					iWidth;					// 图片像素宽度
	int					iHeight;				// 图片像素高度
	int					iFaceAttrCount;			// 暂时不用
	int					iFaceAttrStructSize;	// 暂时不用
	FaceAttributeCV1*	pstFaceAttr[256];		// 暂时不用
	int					iDataLen;				// 图片数据大小
	char*				pcPicData;				// 图片数据
}FacePicDataCV1, *pFacePicDataCV1;

typedef struct tagFacePicStream
{
	int					nStructSize;			// FacePicStreamCV1结构体大小
	PicTimeCV1			tPicTime;				// 抓图时间
	int					nFullPicSize;			// PicDataCV1结构体大小
	PicDataCV1*			pstFullPicData;			// 背景图数据
	//  一张背景图对应一张/多张人脸抠图，当前为一张
	int					nFaceCount;				// 图片张数
	int					nFacePicSize;			// FacePicDataCV1 数组总大小
	FacePicDataCV1*		pstFaceData;			// 图片数据
}FacePicStreamCV1, *pFacePicStreamCV1;

///////////////////////////////////////////////////////////////////////////////////////////////
// 人脸图片库 & 人脸图片操作相关结构体

/////////////////////////////////////////////
// 人脸组信息
typedef struct  
{
	BOOL				bEnable;					// 使能标志位
	unsigned int		nGroupID;					// 人脸组ID
	char				szGroupName[128];			// 人脸组名称，创建底库时指定，创建后不可更改
	char				szAlias[128];				// 人脸组别名
	char				szGUID[64];					// 人脸组唯一ID
	int					nFaceCount;					// 人脸组在库人脸数(不启用)
	float				fSearchThreshold;			// 识别比对阈值 [0.0-100.0]
	STU_TIME			stCreateTime;				// 人脸组创建时间
	unsigned int		nTopRank;					// 上报识别得分超过阈值的排名靠前的底库人脸个数
	BYTE				reserved[252];				// 保留参数
}STU_FACE_GROUP_INFO, *P_STU_FACE_GROUP_INFO;

// 所有人脸组信息
typedef struct 
{
	// 人脸组实际数目
	unsigned short			nFaceGroupNum;
	// 字节对齐
	BYTE					reserved[2];
	// 人脸组信息
	STU_FACE_GROUP_INFO		stFaceGroupArr[MAX_FACE_GROUP_NUM];
}STU_FACE_GROUP_ARRAY_INFO, *P_STU_FACE_GROUP_ARRAY_INFO;

// 可编辑的人脸组信息
typedef struct  
{
	BOOL				bEnable;					// 使能标志位，非 0 或 1 则不配置
	float				fSearchThreshold;			// 识别比对阈值 [0.0 - 100.0], -1 则不配置
	char				szAlias[128];				// 人脸组别名, 为空则不修改
	char				szGUID[64];					// 全局 ID，为空则不修改
	unsigned int		nTopRank;					// 上报识别得分超过阈值的排名靠前的底库人脸个数 [1-5]
	BYTE				reserved[124];				// 保留参数
}STU_FACE_GROUP_EDIT_INFO, *P_STU_FACE_GROUP_EDIT_INFO;

// 人脸组创建输入参数
typedef struct  
{
	BOOL				bEnable;					// 使能标志位
	float				fSearchThreshold;			// 识别比对阈值 [0.0-100.0]
	char				szAlias[128];				// 人脸组别名（不能包含特殊字符）
	unsigned int		nTopRank;					// 上报识别得分超过阈值的排名靠前的底库人脸个数
	BYTE				reserved[124];				// 保留参数
}STU_FACE_GROUP_CREATE_IN_PARAM, *P_STU_FACE_GROUP_CREATE_IN_PARAM;

// 人脸组创建输出参数
typedef struct  
{
	DWORD					dwSize;					// 结构体大小
	int						nError;					// 错误码，0-无错误
	STU_FACE_GROUP_INFO		stFaceGroupInfo;		// 人脸组信息
	BYTE					reserved[64];			// 保留参数
}STU_FACE_GROUP_CREATE_OUT_PARAM, *P_STU_FACE_GROUP_CREATE_OUT_PARAM;

// 删除人脸组输入参数
typedef struct  
{
	unsigned int			nGroupID;				// 人脸组 ID
	BOOL					bDelBindFace;			// 是否同步删掉绑定到改组的人脸图片
	BYTE					reserved[16];			// 保留参数
}STU_FACE_GROUP_DELETE_IN_PARAM, *P_STU_FACE_GROUP_DELETE_IN_PARAM;

// 删除人脸组输出参数
typedef struct  
{
	DWORD					dwSize;					// 结构体大小
	int						nError;					// 错误码， 0 为无错误
	BYTE					reserved[16];			// 保留参数
}STU_FACE_GROUP_DELETE_OUT_PARAM, *P_STU_FACE_GROUP_DELETE_OUT_PARAM;

// 编辑人脸组输入参数
typedef struct  
{	
	unsigned int				nGroupID;					// 人脸组 ID（不更改）
	STU_FACE_GROUP_EDIT_INFO	stFaceGroupEditInfo;		// 可修改的人脸组信息
	BYTE						reserved[64];				// 保留参数
}STU_FACE_GROUP_EDIT_IN_PARAM, *P_STU_FACE_GROUP_EDIT_IN_PARAM;

// 编辑人脸组输出参数
typedef struct  
{	
	DWORD					dwSize;							// 结构体大小
	int						nError;							// 错误码，0 为无错误
	BYTE					reserved[16];					// 保留参数
}STU_FACE_GROUP_EDIT_OUT_PARAM, *P_STU_FACE_GROUP_EDIT_OUT_PARAM;

/////////////////////////////////////////////
// 人脸图操作
typedef struct  
{
	unsigned int			nPersonID;						// 人员 ID
	char					szName[128];					// 人脸图别名
	EM_SEX_TYPE				emSexType;						// 性别
	STU_TIME				stBirthday;						// 生日
	char					szCertificateType[64];			// 证件类型
	char					szID[128];						// 证件 ID
	BYTE					reserved1[32];					// 保留参数1
	char					szCountry[64];					// 国别
	char					szProvince[64];					// 省份
	char					szCity[128];					// 所在城市
	BYTE					reserved2[1024];				// 保留参数2
}STU_PERSON_INFO, *P_STU_PERSON_INFO;

// 添加人脸操作输入参数
typedef struct  
{	
	unsigned int			nGroupID;						// 人脸组 ID
	STU_PERSON_INFO			stPersonInfo;					// 人员信息
	int						nImageCount;					// 人脸图片张数, 不超过 MAX_PERSON_FACE_NUM
	char					*lpszImageFiles;				// 人脸图片本地路径（如果是多张，以 "|" 分隔路径）
	BOOL					bNoCreate;						// 拒绝创建（不必设置，不启用）
	BYTE					reserved[252];					// 保留参数
}STU_FACE_ADD_IN_PARAM, *P_STU_FACE_ADD_IN_PARAM;

// 添加人脸操作输出参数
typedef struct 
{
	DWORD					dwSize;							// 结构体大小
	int						nError;							// 错误码，0 - 无错误
	int						nFaceTokenCount;				// 添加人脸图片成功后，返回的 facetoken 个数
	// 添加人脸图片成功后，返回的人脸图片对应的 facetoken 字符串
	// 如果是多张，以 "|" 分隔，顺序与添加图片的顺序相同
	char					szFaceTokens[68 * MAX_PERSON_FACE_NUM];
	BYTE					reserved[16];					// 保留参数
}STU_FACE_ADD_OUT_PARAM, *P_STU_FACE_ADD_OUT_PARAM;

// 更新人脸组信息操作输入参数
typedef struct  
{
	STU_PERSON_INFO			stPersonInfo;					// 人脸信息
	BYTE					reserved[128];					// 保留参数
}STU_PERSON_INFO_UPDATE_IN_PARAM, *P_STU_PERSON_INFO_UPDATE_IN_PARAM;

// 更新人脸组信息操作输出参数
typedef struct 
{
	DWORD					dwSize;							// 结构体大小
	int						nError;							// 错误码， 0-无错误
	BYTE					reserved[16];					// 保留参数
}STU_PERSON_INFO_UPDATE_OUT_PARAM, *P_STU_PERSON_INFO_UPDATE_OUT_PARAM;

// 添加人脸图片操作输入参数
typedef struct  
{
	unsigned int			nGroupID;						// 人脸组ID
	unsigned int			nPersonID;						// 人员ID
	char					szImageFile[MAX_PATH];			// 本地图片路径
	BYTE					reserved[64];					// 保留参数
}STU_FACE_IMAGE_ADD_IN_PARAM, *P_STU_FACE_IMAGE_ADD_IN_PARAM;

// 添加人脸图片操作输出参数
typedef struct  
{
	DWORD					dwSize;							// 结构体大小
	int						nError;							// 错误码 0 - 无错误
	char					szFaceToken[64];				// 新的人脸标识码
	BYTE					reserved[64];					// 保留参数
}STU_FACE_IMAGE_ADD_OUT_PARAM, *P_STU_FACE_IMAGE_ADD_OUT_PARAM;

// 删除人脸图片操作输入参数
typedef struct  
{
	char					szFaceToken[64];				// 人脸标识码
	BYTE					reserved[64];					// 保留参数
}STU_FACE_IMAGE_DELETE_IN_PARAM, *P_STU_FACE_IMAGE_DELETE_IN_PARAM;

// 删除人脸图片操作输出参数
typedef struct  
{
	DWORD					dwSize;							// 结构体大小
	int						nError;							// 错误码，0-无错误
	BYTE					reserved[16];					// 保留参数
}STU_FACE_IMAGE_DELETE_OUT_PARAM, *P_STU_FACE_IMAGE_DELETE_OUT_PARAM;

// 更新人脸图片操作输入参数
typedef struct  
{
	char					szFaceToken[64];				// 人脸标识码
	char					szImageFile[MAX_PATH];			// 需更新的人脸图片路径
	BYTE					reserved[64];					// 保留参数
}STU_FACE_IMAGE_UPDATE_IN_PARAM, *P_STU_FACE_IMAGE_UPDATE_IN_PARAM;

// 更新人脸图片操作输出参数
typedef struct  
{
	DWORD					dwSize;							// 结构体大小
	int						nError;							// 错误码，0-无错误
	char					szFaceToken[64];				// 新的人脸标识码
	BYTE					reserved[64];					// 保留参数
}STU_FACE_IMAGE_UPDATE_OUT_PARAM, *P_STU_FACE_IMAGE_UPDATE_OUT_PARAM;

// 人脸图绑定到人脸组操作输入参数
typedef struct 
{
	unsigned int			nGroupID;						// 绑定人脸组的ID
	char					szFaceToken[64];				// 人脸标识码
	BYTE					reserved[64];					// 保留参数
}STU_FACE_BIND_GROUP_IN_PARAM, *P_STU_FACE_BIND_GROUP_IN_PARAM;

// 人脸图绑定到人脸组操作输出参数
typedef struct  
{
	DWORD					dwSize;							// 结构体大小
	int						nError;							// 错误码 0 - 无错误
	BYTE					reserved[16];					// 保留参数
}STU_FACE_BIND_GROUP_OUT_PARAM, *P_STU_FACE_BIND_GROUP_OUT_PARAM;

// 人脸图从人脸组解绑操作输入参数
typedef struct  
{
	unsigned int			nGroupID;						// 人脸组ID
	char					szFaceToken[64];				// 人脸标识码
	BYTE					reserved[64];					// 保留参数
}STU_FACE_UNBIND_GROUP_IN_PARAM, *P_STU_FACE_UNBIND_GROUP_IN_PARAM;

// 人脸图从人脸组解绑操作输出参数
typedef struct  
{
	DWORD					dwSize;							// 结构体大小
	DWORD					nError;							// 错误码，0-无错误
	BYTE					reserved[16];					// 保留参数
}STU_FACE_UNBIND_GROUP_OUT_PARAM, *P_STU_FACE_UNBIND_GROUP_OUT_PARAM;

/////////////////////////////////////////////
// 人脸查询

// 人脸图像信息
typedef struct  
{
	unsigned int			nGroupID;						// 绑定的人脸组ID
	unsigned int			nPersonID;						// 人员ID
	char					szFaceToken[64];				// 人脸标识符
	int						nState;							// 人脸状态，0-禁用，1-启用
	STU_TIME				stTime;							// 人脸入库时间	
	BYTE					reserved[256];					// 保留参数
}STU_FACE_IMAGE_INFO, *P_STU_FACE_IMAGE_INFO;

// 人员人脸图像信息
typedef struct  
{
	// 人员信息
	STU_PERSON_INFO			stPersonInfo;
	// 人脸图像实际数目，不大于 MAX_PERSON_FACE_NUM
	int						nFaceImageCount;
	// 人脸图像信息数组
	STU_FACE_IMAGE_INFO		stFaceImageInfoArr[MAX_PERSON_FACE_NUM];
}STU_PERSON_FACE_INFO, *P_STU_PERSON_FACE_INFO;

// 创建人脸信息查询实例
typedef struct  
{
	DWORD					dwResult;						// 人脸查询实例
}STU_FACE_INFO_FIND_INSTANCE, *P_STU_FACE_INFO_FIND_INSTANCE;

// 人脸信息查询条件
typedef struct  
{
	BOOL					bEnable;						// 是否启用查询条件, 如果不启用则查询所有
	unsigned int			nPersonID;						// 人员ID, -1 表示无效
	char					szName[128];					// 人员名, 空表示无效
	EM_SEX_TYPE				emSexType;						// 人员性别，-1（UNKNOWN）表示无效
	STU_TIME				stMinBirthday;					// 人员生日范围下限, 年份为 0 时无效
	STU_TIME				stMaxBirthday;					// 人员生日范围上限, 年份为 0 时无效
	char					szCertificateType[64];			// 人员证件类型，空表示无效
	char					szID[128];						// 人员证件 ID，空表示无效
	char					reserved1[32];					// 保留参数1
	char					szCountry[64];					// 国别，空表示无效
	char					szProvince[64];					// 省份，空表示无效
	char					szCity[128];					// 城市，控表示无效
	BYTE					reserved2[1024];				// 保留参数2
}STU_FACE_INFO_FIND_CONDITON, *P_STU_FACE_INFO_FIND_CONDITON;

// 查询人脸信息输入参数
typedef struct  
{
	unsigned int				nGroupID;					// 人脸组 ID
	STU_FACE_INFO_FIND_CONDITON	stCondition;				// 人脸信息查询条件
}STU_FACE_INFO_FIND_IN_PARAM, *P_STU_FACE_INFO_FIND_IN_PARAM;

// 查询人脸信息输出参数
typedef struct  
{
	DWORD						dwSize;						// 结构体大小
	int							nError;						// 错误码，0-无错误
	BYTE						reserved[16];				// 保留参数
}STU_FACE_INFO_FIND_OUT_PARAM, *P_STU_FACE_INFO_FIND_OUT_PARAM;

// 获取人脸信息操作输入参数
typedef struct  
{
	unsigned short				nOffset;					// 查询结果偏移，
	unsigned short				nCount;						// 希望获取的查询条数, 不大于 MAX_ONCE_QUERY_PERSON_NUM
	BYTE						reserved[32];				// 保留参数
}STU_FACE_INFO_FIND_RESULT_IN_PARAM, *P_STU_FACE_INFO_FIND_RESULT_IN_PARAM;

// 查找获取人脸信息输出参数
typedef struct  
{
	// 结构体大小
	DWORD					dwSize;
	// 错误码，0-无错误
	int						nError;
	// 人员人脸信息数组实际大小，不大于 MAX_ONCE_QUERY_PERSON_NUM
	int						nPersonFaceInfoArrSize;
	// 人员人脸信息数组
	STU_PERSON_FACE_INFO	stPersonFaceInfoArr[MAX_ONCE_QUERY_PERSON_NUM];
}STU_FACE_INFO_FIND_RESULT_OUT_PARAM, *P_STU_FACE_INFO_FIND_RESULT_OUT_PARAM;

// 查找获取人脸库人脸图片输入参数
typedef struct  
{
	char					szFaceToken[64];				// 人脸标识码
	char					szImageFile[MAX_PATH];			// 本地图片路径
	BYTE					reserved[64];					// 保留参数
}STU_FACE_IMAGE_GET_IN_PARAM, *P_STU_FACE_IMAGE_GET_IN_PARAM;

// 查找获取人脸库人脸图片输出参数
typedef struct  
{
	DWORD					dwSize;							// 结构体大小
	int						nError;							// 错误码 0-无错误
	int						nImageLength;					// 人脸图片大小
	char					szImageFile[MAX_PATH];			// 人脸图片本地路径
	BYTE					reserved[64];					// 保留参数
}STU_FACE_IMAGE_GET_OUT_PARAM, *P_STU_FACE_IMAGE_GET_OUT_PARAM;

// 通过人脸标识码获取人员信息输入参数
typedef struct
{
	char					szFaceToken[64];				// 人脸标识码
	BYTE					reserved[64];					// 保留参数
}STU_PERSON_INFO_GET_BYTOKEN_IN_PARAM, *P_STU_PERSON_INFO_GET_BYTOKEN_IN_PARAM;

// 通过人脸标识码获取人员信息输出参数
typedef struct  
{
	DWORD					dwSize;							// 结构体大小
	int						nError;							// 错误码 0-无错误
	STU_PERSON_INFO			stPersonInfo;					// 人员信息
}STU_PERSON_INFO_GET_BYTOKEN_OUT_PARAM, *P_STU_PERSON_INFO_GET_BYTOKEN_OUT_PARAM;

// 通过人员ID获取人员信息输入参数
typedef struct  
{
	char					szCertificateType[64];			// 人员证件类型
	char					szID[128];						// 人员证件号
	BYTE					reserved[16];					// 保留参数 
}STU_PERSON_INFO_GET_BYID_IN_PARAM, *P_STU_PERSON_INFO_GET_BYID_IN_PARAM;

// 通过人员ID获取人员信息输出参数
typedef struct  
{
	DWORD					dwSize;							// 结构体大小
	int						nError;							// 错误码 0-无错误
	STU_PERSON_INFO			stPersonInfo;					// 人员信息
}STU_PERSON_INFO_GET_BYID_OUT_PARAM, *P_STU_PERSON_INFO_GET_BYID_OUT_PARAM;

// 获取指定人员ID的所有人脸信息输入参数
typedef struct  
{
	unsigned int			nPersonID;						// 人员ID
	BYTE					reserved[16];					// 保留参数
}STU_FACE_IMAGE_INFO_GET_IN_PARAM, *P_STU_FACE_IMAGE_INFO_GET_IN_PARAM;

// 获取指定人员ID的所有人脸信息输出参数
typedef struct
{
	// 结构体大小
	DWORD					dwSize;
	// 错误码，0-无错误
	int						nError;
	// 人脸图像实际数目
	int						nFaceImageCount;
	// 人脸图像信息数组
	STU_FACE_IMAGE_INFO		stFaceImageInfoArr[MAX_PERSON_FACE_NUM];
}STU_FACE_IMAGE_INFO_GET_OUT_PARAM, *P_STU_FACE_IMAGE_INFO_GET_OUT_PARAM;

// 人脸库重名检测输入参数
typedef struct  
{
	char					szName[128];					// 人员名称（不允许带数字后缀）
	BYTE					reserved[64];					// 保留参数
}STU_PERSON_NAME_CHECK_IN_PARAM, *P_STU_PERSON_NAME_CHECK_IN_PARAM;

// 人脸库重名检测输出参数
typedef struct  
{
	DWORD					dwSize;							// 结构体大小
	int						nError;							// 错误码，0-无错误
	int						nSuffix;						// 0 表示无重名，其它表示建议后缀
															// 如果 WH,WH1,WH2, 1和2就是建议后缀
}STU_PERSON_NAME_CHECK_OUT_PARAM, *P_STU_PERSON_NAME_CHECK_OUT_PARAM;

/////////////////////////////////////////////
// 人脸比对

// 人脸比对记录查询条件
typedef struct  
{
	unsigned int			nGroupID;						// 人脸组 ID, 0 表示无效
	int						nRecNo;							// 人脸比对数据库主键号， -1 表示无效
	short					nPass;							// 人脸识别通过标志位
															// -1 表示查询所有
															// 0 表示查询识别不通过的类型
															// 1 表示查询识别通过的类型
	BYTE					reserved1[2];					// 暴力参数1
	unsigned int			nObjectID;						// 物体 ID, 0 表示无效
	STU_TIME				stMinTime;						// 查询时间范围下限，年份为 0 时无效
	STU_TIME				stMaxTime;						// 查询时间范围上限，年份为 0 时无效
    BYTE					reserved2[16];					// 保留参数2
}STU_FACE_REC_REC_FIND_CONDITION, *P_STU_FACE_REC_REC_FIND_CONDITION;

// 人脸比对记过记录
typedef struct  
{
	unsigned int			nResultRecNo;					// 人脸比对结果记录编号				
	float					fSearchScore;					// 人脸相似度 [0-100], 值越大相似度越高
	float					fSearchThreshold;				// 人脸相似度阈值 [0-100]
	float					fLivenessScore;					// 活体检测得分 [0-100]
	float					fLivenessThreshold;				// 活体检测阈值 [0-100]
	char					szFaceToken[64];				// 比对成功的底库人脸图片标识码 
	BYTE					reserved[128];					// 保留参数		
}STU_FACE_RECOGNIZE_RESULT, *P_STU_FACE_RECOGNIZE_RESULT;

// 人脸比对记录查询信息
typedef struct
{
	unsigned int					nRecNo;							// 识别记录编号
	unsigned int					nGroupID;						// 人脸组 ID
	short							nPass;							// 是否识别通过 1-通过; 0-不通过
	BYTE							reserved1[2];					// 保留参数1
	char							szImagePath[MAX_PATH];			// 设备端识别图片存储路径
	STU_TIME						stTime;							// 识别比对时间
	BYTE							reserved2[64];					// 保留参数2
	int								nResultCount;					// 人脸比对结果数目
	STU_FACE_RECOGNIZE_RESULT		stResultArr[MAX_FACE_REC_RESULT_NUM];	// 人脸识别结果信息数组
	BYTE							reserved3[128];					// 保留参数3
}STU_FACE_RECOGNIZE_RECORD_INFO, *P_STU_FACE_RECOGNIZE_RECORD_INFO;

// 人脸比对记录查询实例创建输入参数
typedef struct  
{
	STU_FACE_REC_REC_FIND_CONDITION	stCondition;					// 查询条件
	BYTE							reserved[64];					// 保留参数
}STU_FACE_REC_REC_FIND_IN_PARAM, *P_STU_FACE_REC_REC_FIND_IN_PARAM;

// 人脸比对记录查询实例创建输出参数
typedef struct  
{
	DWORD							dwSize;							// 结构体大小
	int								nError;							// 错误码，0-无错误
	unsigned int					nFindHandle;					// 人脸识别记录查找句柄
	BYTE							reserved[16];					// 保留参数
}STU_FACE_REC_REC_FIND_OUT_PARAM, *P_STU_FACE_REC_REC_FIND_OUT_PARAM;

// 人脸比对记录查找结果输入参数
typedef struct  
{
	unsigned short			nOffset;						// 查询结果偏移
	unsigned short			nCount;							// 期望查询到的结果条数
															// 不超过 MAX_ONCE_QUERY_FACE_REC_REC_NUM
	BYTE					reserved[16];					// 保留参数
}STU_FACE_REC_REC_FIND_RESULT_IN_PARAM, *P_STU_FACE_REC_REC_FIND_RESULT_IN_PARAM;

// 人脸比对记录查找结果输出参数
typedef struct  
{
	// 结构体大小
	DWORD							dwSize;
	// 错误码，0-无错误
	int								nError;
	// 实际查询到的记录条数
	unsigned int					nRecordCount;
	// 人脸比对记录信息数组
	STU_FACE_RECOGNIZE_RECORD_INFO	stRecordInfoArr[MAX_ONCE_QUERY_FACE_REC_REC_NUM];
}STU_FACE_REC_REC_FIND_RESULT_OUT_PARAM, *P_STU_FACE_REC_REC_FIND_RESULT_OUT_PARAM;

//报警信息结构体
typedef struct
{
	EM_ALARM_TYPE 	eAlarmType;//报警类型
	int				iChannelID;//设备通道号
	char 			cAlarmTime[32];//报警发生时间	

}ST_ALARM_INFO;

///////////////////////////////////////////////////////////////////////////////////////////////

/*****************************************************************************************
 *							netmanager library 回调定义									 *
 *****************************************************************************************/

/*******************************************************************************
函数：		fDisConnectCallBack
参数：		[in]lLoginID:		登入设备句柄
			[in]lpszIP:			设备 IP 地址
			[in]nPort:			设备登入端口
			[in]dwUser:			用户参数
返回值：		/
说明：		网络连接断开回调函数原形
********************************************************************************/
typedef void (CALLBACK *fDisConnectCallBack)(
	LLONG lLoginID, 
	char *lpszIP, 
	LONG nPort, 
	LDWORD dwUser);

/*******************************************************************************
函数：		fReConnectedCallBack
参数：		[in]lLoginID:		登入设备句柄
			[in]lpszIP:			设备 IP 地址
			[in]nPort:			设备登入端口
			[in]dwUser:			用户参数
返回值：		/
说明：		网络连接恢复回调函数原形
********************************************************************************/
typedef void (CALLBACK *fReConnectedCallBack)(
	LLONG lLoginID, 
	char *lpszIP, 
	LONG nPort, 
	LDWORD dwUser);

/*******************************************************************************
函数：		fSubDisConnectCallBack
参数：		[in]emInterfaceType:	虚拟接口类型
			[in]bOnline:			设备是否在线
			[in]lOperateHandle:		断线时的操作句柄
			[in]lLoginID:			设备登录句柄
			[in]dwUser:				用户参数
返回值：		/
说明：		动态子连接断开回调函数原形
********************************************************************************/
typedef void (CALLBACK *fSubDisConnectCallBack)(
	EM_VIRTUAL_INTERFACE_TYPE emInterfaceType, 
	BOOL bOnline, 
	LLONG lOperateHandle,
	LLONG lLoginID,
	LDWORD dwUser);

/*******************************************************************************
函数：		fRealPlayDisConnectCallBack
参数：		[in]lOperateHandle:		操作句柄
			[in]dwCodeType:			错误码类型
			[in]param:				预留参数，不启用
			[in]dwUser:				用户参数
返回值：		/
说明：		视频监视断开回调函数原形
********************************************************************************/
typedef void (CALLBACK *fRealPlayDisConnectCallBack)(
	LLONG lOperateHandle, 
	EM_CODE_RETURN_TYPE dwCodeType, 
	void* param, 
	LDWORD dwUser);

/*******************************************************************************
函数：		fRealPlayDataCallBack
参数：		[in]lRealHandle:		实时播放句柄
			[in]dwDataType:			数据类型，当前为 0
			[in]pBuffer:			实时数据Buffer
			[in]dwBufSize:			实时数据Buffer大小
			[in]dwUser:				用户参数
返回值：		/
说明：		实时监视数据回调函数原形
********************************************************************************/
typedef void (CALLBACK *fRealPlayDataCallBack)(
	LLONG lRealHandle, 
	DWORD dwDataType, 
	BYTE *pBuffer, 
	DWORD dwBufSize,
	LDWORD dwUser);

/**********************************************************************************
函数：		fRealPlayDataCallBackEx
参数：		[in] lRealHandle：			实时播放句柄	
			[in] dwDataType:			数据类型，当前为 0
			[in] pBuffer:				实时数据Buffer
			[in] dwBufSize:				实时数据Buffer大小
			[in] param:					预留参数，当前为 0
			[in] dwUser:				用户参数
返回值：		/
说明：		实时监视数据回调函数原形
**********************************************************************************/
typedef void (CALLBACK *fRealPlayDataCallBackEx)(
	LLONG lRealHandle, 
	DWORD dwDataType, 
	BYTE *pBuffer, 
	DWORD dwBufSize, 
	LONG param, 
	LDWORD dwUser);

/**********************************************************************************
函数：		fTalkBackDataCallBack
参数：		[in] lRealHandle：			语音对讲句柄	
			[in] pBuffer:				设备端的语音数据Buffer
			[in] dwBufSize:				设备端的语音数据Buffer大小
			[in] dwUser:				用户参数
返回值：		/
说明：		语音对讲数据回调函数原形
**********************************************************************************/
typedef void (CALLBACK *fTalkBackDataCallBack)(
	LLONG lRealHandle,
	BYTE *pBuffer,
	DWORD dwBufSize,
	LDWORD dwUser);

/**********************************************************************************
函数：		fAlarmInfoCallBack
参数：		[in] lAlarmHandle				报警句柄	
			[in] pBuffer:				报警信息 ST_ALARM_INFO*类型
			[in] dwBufSize:				报警信息结构体大小 sizeof(ST_ALARM_INFO)
			[in] dwUser:				用户参数
返回值：		/
说明：		报警信息回调函数原形
**********************************************************************************/
typedef void (CALLBACK *fAlarmInfoCallBack)(
	LLONG lAlarmHandle,
	BYTE *pBuffer,
	DWORD dwBufSize,
	LDWORD dwUser);

/**********************************************************************************
函数：		fCustomDrawCallBack
参数：		[in] lLoginID：				登入设备句柄	
			[in] lPlayHandle:			实时播放句柄
			[in] hDC:					绘图DC
			[in] dwUser:				用户参数
返回值：		/
说明：		屏幕叠加回调函数原形
**********************************************************************************/
typedef void (CALLBACK *fCustomDrawCallBack)(
	LLONG lLoginID, 
	LLONG lPlayHandle, 
	HDC hDC, 
	LDWORD dwUser);

/**********************************************************************************
函数：		fDownLoadByTimePosCallBack
参数：		[in] lRealHandle：			实时播放句柄	
			[in] dwTotalSize:			总数据大小
			[in] dwDownLoadSize:		下载数据大小
			[in] index:					文件索引号
			[in] param:					预留参数，当前为 0
			[in] dwUser:				用户参数
返回值：		/
说明：		按时间回放进度回调函数原形
**********************************************************************************/
typedef void (CALLBACK *fDownLoadByTimePosCallBack)(
	LLONG lPlayHandle, 
	DWORD dwTotalSize,
	DWORD dwDownLoadSize,
	int index, 
	STU_T_FILE recordfileinfo, 
	LDWORD dwUser);

/**********************************************************************************
函数：		fMsgCallBack
参数：		[in] lCommand：				消息命令	
			[in] lLoginID:				设备登录句柄
			[in] pBuf:					数据缓存
			[in] dwBufLen:				数据缓存大小
			[in] lpszIP:				设备 IP 地址
			[in] nPort:					设备登录端口
			[in] dwUser:				用户参数
返回值：		/
说明：		消息回调函数原形
**********************************************************************************/
typedef BOOL (CALLBACK *fMsgCallBack)(
	LONG lCommand, 
	LLONG lLoginID, 
	char *pBuf, 
	DWORD dwBufLen, 
	char *lpszIP,
	LONG nPort,
	LDWORD dwUser);

/**********************************************************************************
函数：		fRegServerCallBack
参数：		[in] lHandle：				Socket	
			[in] lpszIP:				登录IP
			[in] nPort:					登录端口
			[in] lCommand:				命令类型
			[in] pParam:				参数内容
			[in] dwParamLen:			参数内存大小
			[in] dwUser:				用户参数
返回值：		/
说明：		侦听服务器回调函数原形
**********************************************************************************/
typedef int (CALLBACK *fRegServerCallBack)(
	LLONG lHandle,
	char *lpszIP, 
	WORD nPort, 
	LONG lCommand, 
	void *pParam, 
	DWORD dwParamLen, 
	LDWORD dwUser);

/**********************************************************************************
函数：		fAudioDataCallBack
参数：		[in] lTalkHandle：			语音对讲句柄	
			[in] pDataBuf:				数据缓存
			[in] dwBufSize:				数据缓存大小
			[in] byAudioFlag:			音频标志位
			[in] dwUser:				用户参数
返回值：		/
说明：		语音对讲的音频数据回调函数原形
**********************************************************************************/
typedef void (CALLBACK *fAudioDataCallBack)(
	LLONG lTalkHandle, 
	char *pDataBuf, 
	DWORD dwBufSize, 
	BYTE byAudioFlag, 
	LDWORD dwUser);

/**********************************************************************************
函数：		fDeviceUpgradeCallBack
参数：		[in] lLoginID：				设备登录句柄	
			[in] lUpgradechannel:	    升级通道句柄
			[in] nTotalSize:			总文件大小
			[in] nSendSize:				已发送的文件大小
			[in] dwUser:				用户参数
返回值：		/
说明：		升级设备程序回调函数原形
**********************************************************************************/
typedef void (CALLBACK *fDeviceUpgradeCallBack)(
	LLONG lLoginID, 
	LLONG lUpgradechannel,
	int nTotalSize, 
	int nSendSize, 
	LDWORD dwUser);

/**********************************************************************************
函数：		fTransComDataCallBack
参数：		[in] lLoginID：				设备登录句柄	
			[in] lTransComChannel:	    透明串口句柄
			[in] pBuffer:				数据缓存
			[in] dwBufSize:				数据缓存大小
			[in] dwUser:				用户参数
返回值：		/
说明：		透明串口回调函数原形
**********************************************************************************/
typedef void (CALLBACK *fTransComDataCallBack)(
	LLONG lLoginID, 
	LLONG lTransComChannel, 
	char *pBuffer, 
	DWORD dwBufSize, 
	LDWORD dwUser);

/**********************************************************************************
函数：		fAsyncDataCallBack
参数：		[in] lCommand：				命令类型	
			[in] lpData:				回调数据
			[in] dwUser:				用户参数
返回值：		/
说明：		异步数据回调
**********************************************************************************/
typedef void (CALLBACK *fAsyncDataCallBack)(
	LLONG lCommand, 
	P_STU_CALLBACK_DATA lpData, 
	LDWORD dwUser);

/**********************************************************************************
函数：		fAsyncDataCallBack
参数：		[in] lCommand：				命令类型	
			[in] lpData:				回调数据
			[in] dwUser:				用户参数
返回值：		/
说明：		文件传输回调
**********************************************************************************/
typedef void (CALLBACK *fFileTransCallBack)(
	LLONG lHandle, 
	int nTransType, 
	int nState, 
	int nSendSize, 
	int nTotalSize,
	LDWORD dwUser);

/**********************************************************************************
函数：		fAnalyzeDataCallBack
参数：		[in] lAnalyzeHandle：		智能分析句柄	
			[in] dwEventType:			智能事件类型
			[in] pEventInfo:			智能事件详细信息
			[in] pBuffer:				智能事件关联的数据（图片）
			[in] dwBufSize:				智能事件关联的数据大小
			[in] nSequence:				0，暂不启用
			[in] dwUser:				用户参数
返回值：		int
说明：		智能分析数据回调
**********************************************************************************/
typedef int (CALLBACK *fAnalyzeDataCallBack)(
	LLONG lAnalyzeHandle,
	DWORD dwEventType,
	void* pEventInfo, 
	BYTE *pBuffer, 
	DWORD dwBufSize,
	LDWORD dwUser,
	int nSequence, 
	void *pReserved);

/**********************************************************************************
函数：		fAnalyzeDataCallBack
参数：		[out] pDeviceSearchInfo：	设备搜索信息	
			[in] pUserData:				用户参数
返回值：		/
说明：		异步搜索设备回调
**********************************************************************************/
typedef void (CALLBACK *fSearchDevicesCallBack)(
	STU_DEVICE_SEARCH_INFO *pDeviceSearchInfo, 
	void* pUser);

/**********************************************************************************
函数：		fPlaybackYuvDataCallBack（暂不启用）
参数：		[in] lPlaybackHandle：		录像回放句柄
			[in] pBuffer:				数据缓存
			[in] dwBufSize:				数据缓存大小
			[in] param:					
			[in] dwUser:				用户参数
返回值：		/
说明：		回放YUV数据回调函数
**********************************************************************************/
typedef void (CALLBACK *fPlaybackYuvDataCallBack)(
	LLONG lPlaybackHandle, 
	BYTE *pBuffer,
	DWORD dwBufSize,
	LONG param, 
	LDWORD dwUser,
	void *pReserved);

/**********************************************************************************
函数：		fConnectProxyRegCallBack（暂不启用）
参数：		[in] lConnectHandle：		云服务连接句柄
			[in] pConnectResult:		云服务连接结果
			[in] pReserved:				保留参数
			[in] dwUser:				用户参数
返回值：		/
说明：		公网代理注册
**********************************************************************************/
typedef void (CALLBACK *fConnectProxyRegCallBack)(
	LLONG lConnectHandle, 
	STU_CLOUD_SERVICE_CONNECT_RESULT* pConnectResult,
	void* pReserved, 
	LDWORD dwUser);

/**********************************************************************************
函数：		fPlaybackDecPosCallBack
参数：		[in] lLoginID：				设备登录句柄	
			[in] nEncoderID:			解码ID
			[in] dwTotalSize:			解码播放的总大小
			[in] dwPlaySize:			解码播放的大小
			[in] dwUser:				用户参数
返回值：		/
说明：		回放解码位置回调
**********************************************************************************/
typedef void (CALLBACK *fPlaybackDecPosCallBack)(
	LLONG lLoginID, 
	int nEncoderID, 
	DWORD dwTotalSize, 
	DWORD dwPlaySize, 
	LDWORD dwUser);

#endif //_AL_NET_STRUCT_COLLECTION_H
