#ifndef _AL_NET_ENUM_COLLECTION_H
#define _AL_NET_ENUM_COLLECTION_H

/*****************************************************************************************
 *							netmanager library 枚举定义									 *
 *****************************************************************************************/

// 语言种类
typedef enum
{
	LANGUAGE_CHINESE_SIMPLIFIED,		// 简体中文    
	LANGUAGE_CHINESE_TRADITIONAL,		// 繁体中文   
	LANGUAGE_ENGLISH,					// 英文       
	LANGUAGE_JAPANESE,					// 日文版    
	LANGUAGE_RUSSIAN,					// 俄文版        
	LANGUAGE_FRENCH,					// 法文版        
	LANGUAGE_GERMAN,					// 德文版  
	LANGUAGE_FARSI,						// 波斯语     
}EM_SP_LANGUAGE_TYPE;

// 连接状态
typedef enum
{
	EM_LINK_STATUS_UNKNOWN,                  // 未知
	EM_LINK_STATUS_CONNECTED,                // 已连接
	EM_LINK_STATUS_NOT_CONNECTED,            // 未连接
	EM_LINK_STATUS_CONNECT_FAILED,           // 连接失败
	EM_LINK_STATUS_AUTHENTICATION_FAILED,    // 认证失败
	EM_LINK_STATUS_CONNECT_TIMEOUT,          // 连接超时
	EM_LINK_STATUS_NOT_EXIST,                // 设备不存在
}EM_LINK_STATUS;

// 登录协议类型
typedef enum
{
	EM_LOGIN_PROTOCAL_TYPE_INVALID      = 0x00,		// 无效的登陆方式
	EM_LOGIN_PROTOCAL_TYPE_TCP          = 0x01,		// TCP登陆
	EM_LOGIN_PROTOCAL_TYPE_UDP          = 0x02,		// UDP登陆
	EM_LOGIN_PROTOCAL_TYPE_MULTICAST    = 0x03,		// 组播登陆

	EM_LOGIN_PROTOCAL_TYPE_CLOUD        = 0x04,		// 云登陆方式
	EM_LOGIN_PROTOCAL_TYPE_SERVER		= 0x05,		// 服务器方式登入
}EM_LOGIN_PROTOCAL_TYPE;

// 抓图类型
typedef enum
{
	// BMP32类型
	SNAPSHOT_FORMAT_TYPE_BMP32 = 0,
	// BMP24类型
	SNAPSHOT_FORMAT_TYPE_BMP24,
	// TIFF类型
	SNAPSHOT_FORMAT_TYPE_TIFF,
	// JPEG类型 100% 质量
	SNAPSHOT_FORMAT_TYPE_JPEG_100,		
	// 80%质量的JPEG类型
	SNAPSHOT_FORMAT_TYPE_JPEG_80,	
	// 60%质量的JPEG类型
	SNAPSHOT_FORMAT_TYPE_JPEG_60,	
	// 40%质量的JPEG类型
	SNAPSHOT_FORMAT_TYPE_JPEG_40,	
	// 20%质量的JPEG类型
	SNAPSHOT_FORMAT_TYPE_JPEG_20,	
	// 10%质量的JPEG类型
	SNAPSHOT_FORMAT_TYPE_JPEG_10,	
}EM_SNAPSHOT_FORMAT_TYPE;

// 虚拟接口类型
typedef enum
{
	VINTERFACE_TYPE_UNKNOWN = -1,			// 未知虚拟接口
    VINTERFACE_TYPE_REALPLAY,				// 实时监视接口
    VINTERFACE_TYPE_MULTI_PREVIEW,			// 多画面预览接口
    VINTERFACE_TYPE_PLAYBACK,				// 回放接口
	VINTERFACE_TYPE_REALLOAD,				// 下载智能图片接口
    VINTERFACE_TYPE_DOWNLOAD,				// 下载接口
	VINTERFACE_TYPE_UPLOAD,					// 上传接口 
} EM_VIRTUAL_INTERFACE_TYPE;

// 返回码通用定义
typedef enum
{		
	CODE_RETURN_TYPE_UNKNONW = -1,						// 未知
	CODE_RETURN_TYPE_NORMAL = 0,						// 正常
	CODE_RETURN_TYPE_NOAUTH = 1,						// 无权限错误
	CODE_RETURN_TYPE_NOSUPPORT = 2,						// 不支持错误
	CODE_RETURN_TYPE_RESLIMIT = 3,						// 资源受限返回码
	CODE_RETURN_TYPE_DATA_NOORDER = 4,					// 数据错乱返回码
	CODE_RETURN_TYPE_DATA_END = 5,						// 数据结束返回码

	CODE_RETURN_TYPE_VIDEO_STREAM_DISCONNECT = 0x8000,	// 视频流断开错误返回码
}EM_CODE_RETURN_TYPE;

// H264 编码等级
typedef enum
{
	// 提供I/P帧，仅支持progressiv和CAVLC
    EM_H264_ENCODE_LEVEL_BASELINE = 1,   
	// 提供I/P/B帧，支持progressiv和interlaced，提供CAVLC或CABAC
    EM_H264_ENCODE_LEVEL_MAIN,
	// 提供I/P/B/SP/SI帧，仅支持progressive(逐行扫描)和CAVLC
    EM_H264_ENCODE_LEVEL_EXTEND,
	// FRExt，Main_Profile基础上新增：8x8 intra prediction(8x8 帧内预测)
    EM_H264_ENCODE_LEVEL_HIGH,
}EM_H264_ENCODE_LEVEL;

/////////////////////////////////监视相关/////////////////////////////////

// 预览类型
typedef enum
{
    REALPLAY_STREAM_TYPE_REAL = 0,             // 实时预览
    REALPLAY_STREAM_TYPE_MULTI,                // 多画面预览
    REALPLAY_STREAM_TYPE_REAL_MASTER,          // 实时监视-主码流
    REALPLAY_STREAM_TYPE_REAL_SLAVE_1,         // 实时监视-从码流1
    REALPLAY_STREAM_TYPE_REAL_SLAVE_2,         // 实时监视-从码流2
    REALPLAY_STREAM_TYPE_REAL_SLAVE_3,         // 实时监视-从码流3    
} EM_REALPLAY_STREAM_TYPE;


// 音频类型
typedef enum
{
	REALAUDIO_STREAM_TYPE_REAL_MASTER,          // 实时监视-主码流
	REALAUDIO_STREAM_TYPE_REAL_SLAVE_1,         // 实时监视-从码流1
	REALAUDIO_STREAM_TYPE_REAL_SLAVE_2,         // 实时监视-从码流2
	REALAUDIO_STREAM_TYPE_REAL_SLAVE_3,         // 实时监视-从码流3    
} EM_REALAUDIO_STREAM_TYPE;

// 配置文件类型
typedef enum
{
	DEVICE_CONFIG_ALL = 0,						// 全部配置文件
	DEVICE_CONFIG_LOCAL,						// 本地配置文件
	DEVICE_CONFIG_NETWORK,						// 网络配置文件
	DEVICE_CONFIG_USER,							// 用户配置文件
} EM_DEVICE_CONFIG_TYPE;

// 设备协议类型
typedef enum
{
	DEVICE_PROTOCOL_TYPE_GB28181 = 0x0000,	// GB28181
	DEVICE_PROTOCOL_TYPE_ONVIF,				// Onvif  
	DEVICE_PROTOCOL_TYPE_TS,                // 标准TS
	DEVICE_PROTOCOL_TYPE_VNC,               // 虚拟网络计算机

	DEVICE_PROTOCOL_TYPE_SELF = 0x0080,		// 我司协议

	DEVICE_PROTOCOL_TYPE_UNKNOWN = 0xFFFF,	// 由用户自定义   
} EM_DEVICE_PROTOCOL_TYPE;

// 视频流封装格式
typedef enum
{
	VIDEO_PACK_FORMAT_RYMS,             // RYMS
	VIDEO_PACK_FORMAT_PS,               // PS
	VIDEO_PACK_FORMAT_ASF,              // ASF
	VIDEO_PACK_FORMAT_MP4,              // MP4
	VIDEO_PACK_FORMAT_TS,               // TS
} EM_VIDEO_PACK_FORMAT_TYPE;

// 视频码流类型
typedef enum
{
	VIDEO_STREAM_ERROR,                    // 其它
	VIDEO_STREAM_MASTER,                   // 主码流
	VIDEO_STREAM_SLAVE_1,                  // 辅码流1
	VIDEO_STREAM_SLAVE_2,                  // 辅码流2
	VIDEO_STREAM_SLAVE_3,                  // 辅码流3
}EM_VIDEO_STREAM_TYPE;

/////////////////////////////////////////////////////////////////////////////////

// 能力类型
typedef enum
{
	// 音视频编码能力
	DEVICE_CAPS_TYPE_ENCODE,

	// 录像能力集
	DEVICE_CAPS_TYPE_RECORD,

	///////////////////////////////////////

	// 视频输入能力集-全局能力
	DEVICE_CAPS_VIDEOIN,	

	// 视频输入能力集-精确设置光圈能力
	DEVICE_CAPS_VIDEOIN_IRIS,

	// 视频输入能力集-减光晕能力
	DEVICE_CAPS_VIDEOIN_HALOCUT,

	// 视频输入能力集-区域测光能力
	DEVICE_CAPS_VIDEOIN_METERING,

	// 视频输入能力集-图像控制设置能力
	DEVICE_CAPS_VIDEOIN_IMAGE_CTRL,

	// 视频输入能力集-曝光设置能力
	DEVICE_CAPS_VIDEOIN_EXPOSURE,

	// 视频输入能力集-日夜设置能力
	DEVICE_CAPS_VIDEOIN_DAY_NIGHT,

	// 视频输入能力集-白平衡设置能力
	DEVICE_CAPS_VIDEOIN_WHITE_BALANCE,

	// 视频输入能力集-红外能力
	DEVICE_CAPS_VIDEOIN_IR,

	// 视频输入能力集-降噪能力
	DEVICE_CAPS_VIDEOIN_DENOISE,

	// 视频输入能力集-透雾能力
	DEVICE_CAPS_VIDEOIN_DEFOG,	

	// 视频编码能力
	DEVICE_CAPS_VIDEO_ENCODE,

	// 字符叠加能力
	DEVICE_CAPS_OSD,

	// 视频检测能力
	DEVICE_CAPS_VIDEO_DETECT,
		
	// 音频输入能力
	DEVICE_CAPS_AUDIOIN,

	// 音频输出能力
	DEVICE_CAPS_AUDIOOUT,	

	///////////////////////////////////////
	// 支持的平台能力
	DEVICE_CAPS_INTER_PROTOCOL,

	///////////////////////////////////////
	// 人脸识别能力
	DEVICE_CAPS_TYPE_FACE_RECOGNIZE,

	///////////////////////////////////////

	// 能力个数
	DEVICE_CAPS_COUNT,
}EM_DEVICE_CAPS_TYPE;

//配置类型
typedef enum
{
	// 设备系统配置
	DEVICE_CFG_SYS = 0x0000,
	// 网络配置
	DEVICE_CFG_NET,
	// 时间配置
	DEVICE_CFG_SYS_TIME,
	// 夏令时配置
	DEVICE_CFG_TIME_DST,
	// NTP配置
	DEVICE_CFG_NTP,
	// 通道配置
	DEVICE_CFG_CHANNEL,
	// 录像配置
	DEVICE_CFG_RECORD,
	// 串口配置
	DEVICE_CFG_SERIAL_PORT,
	// 对讲配置
	DEVICE_CFG_TALK,
	// 自动维护配置
	DEVICE_CFG_AUTO_MAINTAIN,
	// 人脸识别规则配置
	DEVICE_CFG_FACE_RECOGNIZE_RULES,
	// 抓拍模式配置
	DEVICE_CFG_CAPTURE_MODE,
	// 抓拍张数配置
	DEVICE_CFG_SNAP_TIMES,

	// Web HTTP/HTTPS 配置
	DEVICE_CFG_WEB,
	// RTSP 配置
	DEVICE_CFG_RTSP,
	// NetService 配置
	DEVICE_CFG_NET_SERVICE,
	// 端口配置
	DEVICE_CFG_NET_PORT,
	// WIFI使能配置 设置或者获取wifi使能配置
	DEVICE_CFG_WIFI_ENALE,
	// WIFI操作配置,包括扫描,链接,断开链接
	DEVICE_CFG_WIFI_OPERATE,

	// 水印配置
	DEVICE_CFG_WATERMARK,
	// 摄像头属性配置
	DEVICE_CFG_CAMERA,

	// 视频OSD叠加配置
	DEVICE_CFG_VIDEO_OSD,

	// 存储配置
	DEVICE_CFG_STORAGE,
	// 网络存储传输配置
	DEVICE_CFG_NET_STORAGE_TRANS,

	// Telnet配置
	DEVICE_CFG_TELNET,

	// 日志搜索
	DEVICE_CFG_LOGSEARCH,
	// 黑白名单
	DEVICE_CFG_NETWHITEBLACK,

	// 用户管理
	DEVICE_CFG_USER,
	// 获取在线用户
	DEVICE_CFG_USER_ONLINE,

	// 抠图配置
	DEVICE_CFG_SNAP_CUTOUT,
	// 叠加与抓图配置
	DEVICE_CFG_OVERLAP_PIC,
	// 人脸检测智能场景配置
	DEVICE_CFG_INTELLI_SCENE_FACE_DETECT,
	// 人脸检测规则配置
	DEVICE_CFG_INTELLI_RULE_FACE_DETECT,
	// 人脸检测统计配置
	DEVICE_CFG_INTELLI_RULE_FACE_DETECT_STAT,
	// 报警参数
	DEVICE_CFG_ALARM_PARAM,
	// 编码配置
	DEVICE_CFG_ENCODE_PARAM,

	// GB28181参数配置
	DEVICE_CFG_GB28181_PARAM,
	// ONVIF 配置
	DEVICE_CFG_ONVIF,
	// 云服务配置
	DEVICE_CFG_CLOUD_SERVICE,

	// CFG 配置个数
	DEVICE_CFG_COUNT,
}EM_DEVICE_CFG_TYPE;        

// 报警类型
typedef enum 
{
	// 设备重启报警(事件)
	DEVICE_ALARM_TYPE_REBOOT,
	// 网络故障报警(事件)
	DEVICE_ALARM_TYPE_NET_BROKEN,
	// IP冲突报警(事件)
	DEVICE_ALARM_TYPE_IP_CONFLICT,
	// MAC冲突报警(事件)
	DEVICE_ALARM_TYPE_MAC_CONFLICT,
	// 电源故障报警(事件)
	DEVICE_ALARM_TYPE_POWER_BROKEN,
	// 登陆失败报警(事件)
	DEVICE_ALARM_TYPE_LOGIN_FAIL,
	// 主动注册设备重新登陆(事件)
	DEVICE_ALARM_TYPE_REGISTER_RELOGIN,
	// 修改配置返回报警(事件)
	DEVICE_ALARM_TYPE_CONFIG_RETURN,
	// 设备主动邀请开始语音对讲(事件)
	DEVICE_ALARM_TYPE_AUTO_START_TALK,
	// 设备主动停止语音对讲(事件)
	DEVICE_ALARM_TYPE_AUTO_STOP_TALK,
	// IP搜索(事件)
	DEVICE_ALARM_TYPE_IP_SEARCH,
	// 自动重连失败(事件)
	DEVICE_ALARM_TYPE_RECONNECT_FAIL,
	// 监视失败(事件)
	DEVICE_ALARM_TYPE_REALPLAY_FAIL,
	// 回放失败(事件)
	DEVICE_ALARM_TYPE_PLAYBACK_FAIL,
	// 请求语音对讲失败(事件)
	DEVICE_ALARM_TYPE_TALK_FAIL,
}EM_DEVICE_ALARM_TYPE;

// 白平衡类型
typedef enum
{
	WHITEBALANCE_DISABLE,		// "Disable"(禁止)
	WHITEBALANCE_AUTO,			// "Auto"(自动)
	WHITEBALANCE_SUNNY,			// "Sunny"(晴天,6500K左右)
	WHITEBALANCE_CLOUDY,		// "Cloudy"(阴天,7500K左右)
	WHITEBALANCE_HOME,			// "Home"(家里 5000K左右)
	WHITEBALANCE_OFFICE,		// "Office"(办公 4400K左右)
	WHITEBALANCE_NIGHT,			// "Night"(夜晚 2800K左右)
	WHITEBALANCE_CT_HIGH,		// "HighColorTemperature"(高色温区间),
	WHITEBALANCE_CT_LOW,		// "LowColorTemperature"(低色温区间), 
	WHITEBALANCE_CT_AUTO,		// "AutoColorTemperature"(自动色温区间),
	WHITEBALANCE_CT_CUSTOM,		// "CustomColorTemperature"(自定义色温等级),
	WHITEBALANCE_PART,			// "PartWhiteBalance"(自定义多区域白平衡),

} EM_WHITE_BALANCE;

// 抓图视频编码类型
typedef enum 
{
	VS_CODE_TYPE_MPEG4 = 0,
	VS_CODE_TYPE_H264 = 1,
	VS_CODE_TYPE_H265 = 2,
	VS_CODE_TYPE_JPEG = 3,
}EM_VIDEO_STREAM_CODE_TYPE;

// 码流控制列表
typedef enum
{
	VIDEO_FORMA_CTRL_CBR = 0,
	VIDEO_FORMA_CTRL_VBR = 1,
	VIDEO_FORMA_CTRL_MBR = 2,
}EM_VIDEO_FORMA_CTRL_TYPE;

//分辨率类型
typedef enum
{
	EM_VIDEO_RESOLUTION_CIF = 0,//CIF  352 * 288 
	EM_VIDEO_RESOLUTION_D1,// 704*576
	EM_VIDEO_RESOLUTION_720P,//1280*720
	EM_VIDEO_RESOLUTION_1080P,//1920*1080
	EM_VIDEO_RESOLUTION_TOTAL,

}EM_VIDEO_STREAM_RESOLUTION_TYPE;

typedef enum
{
	EM_STANDARD_PAL = 0,
	EM_STANDARD_NTSC,
	EM_STANDARD_TOTAL,
}EM_STANDARD_TYPE;

/////////////////////////////////////////////////////////////////////////////////

typedef enum
{
	// 人脸图片数据库
	DB_TYPE_FACE_PICTRUE = 0,
	// 普通录像数据库
	DB_TYPE_RECORD = 10,
}EM_DATABASE_TYPE;

typedef enum
{
	ST_FILE_TYPE_UNKNOWN = -1,
	ST_FILE_TYPE_RECORD = 0,
	ST_FILE_TYPE_IMAGE = 1,
}EM_ST_FILE_TYPE;

// 排序类型
typedef enum
{
	// 升序
	ORDER_TYPE_ASCENT = 0,
	// 降序
	ORDER_TYPE_DESCENT,
}EM_ORDER_TYPE;

/////////////////////////////////////////////////////////////////////////////////
// 人脸组 & 人脸

// 性别类型
typedef enum
{
	SEX_TYPE_UNKNOWN = -1,		// 未知，不能设置
	SEX_TYPE_MALE = 0,			// 男性
	SEX_TYPE_FEMALE = 1,		// 女性
}EM_SEX_TYPE;

/////////////////////////////////////////////////////////////////////////////////

// 事件类型
typedef enum
{
	// 订阅所有图片
	EVENT_SP_ALL = 0x00000001,

	/////////////////////////////////////////////////////////////////
	// 抓取人脸背景图事件
	EVENT_SP_FACE_SNAP_WHOLE = 0x00001000,
	// 人脸抠图事件
	EVENT_SP_FACE_SNAP_PART	= 0x00001001,

	// 人脸识别背景图事件
	EVENT_SP_FACE_RECOGNIZE_WHOLE = 0x00001002,
	// 人脸识别抠图事件
	EVENT_SP_FACE_RECOGNIZE_CUTOUT = 0x00001003,

	/////////////////////////////////////////////////////////////////
	// 交通手动抓拍事件
	EVENT_SP_TRAFFIC_SNAP_MANUAL = 0x00004000,

	// 交通卡口事件
	EVENT_SP_TRAFFIC_PASS = 0x00004001,
	// 交通卡口抠图事件
	EVENT_SP_TRAFFIC_PASS_CUTOUT = 0x00004002,

}EM_EVENT_SP_TYPE;

typedef enum
{
	EMVIDEO_MOVING_DETECT,						// 动态检测 "VideoMovingDetect"
	EMSWITCH_IN_ALAM,							// 本地报警 "SwitchInAlarm"
	EMNETWORK,									// 网络状态 "Network"
	EMNETCONFIG_CHANGE,							// 网络参数修改 "NetconfigChange"
	EMSYSTEM_WORKING_STATE,						// 系统工作状态 "SystemWorkingState"
	EMUPGARDE,									// 升级 "Upgrade"
	EMRESET,									// 系统复位		 "Reset"							
} EM_ALARM_TYPE;

typedef enum
{
	FACE_EXTRACT_OPT_ADD = 0x01,				// 人脸库建模操作-添加人脸
	FACE_EXTRACT_OPT_DELETE = 0x02,				// 人脸库建模操作-删除人脸
}EM_FACE_EXTRACT_OPERATE_TYPE;
/////////////////////////////////////////////////////////////////////////////////

#endif //_AL_NET_ENUM_COLLECTION_H