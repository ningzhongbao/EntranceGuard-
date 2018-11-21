#ifndef _SA_STREAM_ADAPTER_1_H
#define _SA_STREAM_ADAPTER_1_H

#define IN  
#define OUT 

#if (defined(WIN32) || defined(WIN64))
#ifdef SA_API_EXPORTS
	#define SA_API __declspec(dllexport)
#elif defined(SA_API_IMPORTS)
	#define SA_API __declspec(dllimport)
#else
	#define SA_API 
#endif
	#define CALLMETHOD __stdcall
#else 
	#define SA_API
	#define CALLMETHOD
#endif

#ifndef NULL
#define NULL 0
#endif

#ifdef __cplusplus
extern "C" {
#endif

// 接口返回值
enum SA_RESULT
{
    SA_SUCCESS = 0,                     // 成功
    SA_ERROR_INVALID_HANDLE,            // 无效句柄
    SA_ERROR_FILE_TYPE_NOSUPPORT,       // 文件类型不支持
    SA_ERROR_STREAM_NOSUPPORT,          // 流类型不支持
    SA_ERROR_THREAD_CREATE_FAILED,      // 线程创建失败
    SA_ERROR_THREAD_CLOSE_FAILED,       // 线程关闭失败
    SA_ERROR_PARAMETER,                 // 参数有误
    SA_ERROR_INDEX_OUTOFRANGE,	        // 索引超过范围
    SA_ERROR_FILE_SIZE_ZERO,			// 文件大小为0
    SA_ERROR_BAD_FORMATTED,     	    // 文件格式错误
    SA_ERROR_FILE_READ,	                // 读取文件失败
    SA_ERROR_FILE_OPEN,                 // 打开文件失败
    SA_ERROR_BUFFER_OVERFLOW,           // 内部缓冲区溢出
    SA_ERROR_SYSTEM_OUT_OF_MEMORY,      // 系统内存不够
    SA_ERROR_LIST_EMPTY,                // 列表为空
	SA_ERROR_UNGET_STREAM_TYPE,			// 未获取到码流类型
	SA_ERROR_EMPTY_PTR,					// 空指针
};

// 帧类型
enum
{
	SA_FRAME_TYPE_UNKNOWN = 0,			// 帧类型不可知
	SA_FRAME_TYPE_VIDEO,				// 帧类型是视频帧
	SA_FRAME_TYPE_AUDIO,				// 帧类型是音频帧
	SA_FRAME_TYPE_DATA					// 帧类型是数据帧
};

// 帧子类型
enum
{
	SA_FRAME_SUB_TYPE_DATA_INVALID = -1,			// 数据无效

	SA_FRAME_SUB_TYPE_VIDEO_I_FRAME = 0,			// I帧
	SA_FRAME_SUB_TYPE_VIDEO_P_FRAME,				// P帧
	SA_FRAME_SUB_TYPE_VIDEO_B_FRAME,				// B帧
	SA_FRAME_SUB_TYPE_VIDEO_S_FRAME,				// S帧

	SA_FRAME_SUB_TYPE_WATERMARK_TEXT,				// 水印数据为TEXT类型
	SA_FRAME_SUB_TYPE_WATERMARK_JPEG,				// 水印数据为JPEG类型
	SA_FRAME_SUB_TYPE_WATERMARK_BMP,				// 水印数据为BMP类型

	SA_FRAME_SUB_TYPE_DATA_INTL,					// 智能分析帧
	SA_FRAME_SUB_TYPE_VIDEO_JPEG_FRAME,             // JPEG 帧
	SA_FRAME_SUB_TYPE_DATA_ITS,				        // ITS信息帧
	SA_FRAME_SUB_TYPE_DATA_GPS,					    // GPS
	SA_FRAME_SUB_TYPE_DATA_INTLEX,                  // 扩展智能分析帧
	SA_FRAME_SUB_TYPE_DATA_MOTION_FULL,				// 全屏动检
	SA_FRAME_SUB_TYPE_DATA_MOTION_CARD,				// 全屏动检(板卡)
	SA_FRAME_SUB_TYPE_DATA_LIGHT,					// 光照
	SA_FRAME_SUB_TYPE_DATA_RAW,						// 原始数据
	SA_FRAME_SUB_TYPE_DATA_CHAR,					// 字符数据信息帧
	SA_FRAME_SUB_TYPE_DATA_PASSWORD,				// 密码信息帧
	
	SA_FRAME_SUB_TYPE_DATA_VIDEO_SYNOPSIS,			// 视频浓缩信息
	SA_FRAME_SUB_TYPE_DATA_SDP,						// SDP信息

	SA_FRAME_SUB_TYPE_VIDEO_SMART_I_FRAME,			// smartH264 I帧
	SA_FRAME_SUB_TYPE_VIDEO_SMART_P_FRAME,			// smartH264 P帧 只参考smart I帧
	SA_FRAME_SUB_TYPE_VIDEO_SMART_I_NORENDER,		// smartH264 I帧,只解码不显示，用于seek和倒放功能

	SA_FRAME_SUB_TYPE_DATA_I_INDEX = 128,           // I帧索引帧
	SA_FRAME_SUB_TYPE_DATA_MOTION,                  // 动检数据帧
	SA_FRAME_SUB_TYPE_DATA_LABEL,                   // 标签帧
	SA_FRAME_SUB_TYPE_DATA_SCREEN_CAPTION,          // 字幕
	SA_FRAME_SUB_TYPE_DATA_EVENT,                   // 事件帧

	SA_FRAME_SUB_TYPE_DATA_FILEHEAD = 255,          // 文件头帧
	SA_FRAME_SUB_TYPE_DATA_UNKOWN,                  // 未知类型
};

// 编码类型
enum SA_ENCODE_VIDEO_TYPE
{
	SA_ENCODE_VIDEO_UNKNOWN = 0,		// 视频编码格式不可知
	SA_ENCODE_VIDEO_MPEG4 ,			    // 视频编码格式是MPEG4
	SA_ENCODE_VIDEO_HI_H264,			// 视频编码格式是海思H264
	SA_ENCODE_VIDEO_JPEG,				// 视频编码格式是标准JPEG
	SA_ENCODE_VIDEO_DH_H264,			// 视频编码格式是大华码流H264
	SA_ENCODE_VIDEO_JPEG2000 = 6,		// 视频编码格式是标准JPEG2000
	SA_ENCODE_VIDEO_AVS = 7,			// 视频编码格式是标准AVS
	SA_ENCODE_VIDEO_STD_H264 = 8,		// 视频编码格式是标准H264
	SA_ENCODE_VIDEO_MPEG2 = 9,          // 视频编码格式是MPEG2
	SA_ENCODE_VIDEO_VNC = 10,         	// 视频编码格式是VNC
	SA_ENCODE_VIDEO_SVAC = 11,          // 视频编码格式是SVAC
	SA_ENCODE_VIDEO_DH_H265 = 12,		// 视频编码格式是H265
	SA_ENCODE_VIDEO_RY_H264,			// 视频编码格式是RY码流H264
	SA_ENCODE_VIDEO_RY_H265,			// 视频编码格式是RY码流H265

	//视频编码类型扩展类型
	SA_ENCODE_VIDEO_H263 = 35,			// 视频编码格式是H263
	SA_ENCODE_VIDEO_PACKET,				// 视频包
	SA_ENCODE_VIDEO_MSMPEG4V1,			// 视频编码格式是MS MPEG4 V1
	SA_ENCODE_VIDEO_MSMPEG4V2,			// 视频编码格式是MS MPEG4 V2
	SA_ENCODE_VIDEO_MSMPEG4V3,			// 视频编码格式是MS MPEG4 V3
	SA_ENCODE_VIDEO_WMV1,				// 视频编码格式是MS MPEG4 V4
	SA_ENCODE_VIDEO_WMV2,				// 视频编码格式是MS MPEG4 V5
	SA_ENCODE_VIDEO_RV10,				// 视频编码格式是RV10
	SA_ENCODE_VIDEO_RV20,				// 视频编码格式是RV20
	SA_ENCODE_VIDEO_RV30,				// 视频编码格式是RV30
	SA_ENCODE_VIDEO_RV40,				// 视频编码格式是RV40
	SA_ENCODE_VIDEO_FLV1,				// 视频编码格式是FLV1
	SA_ENCODE_VIDEO_FLASHSV,			// 视频编码格式是FLASHSV
	SA_ENCODE_VIDEO_FLASHSV2,			// 视频编码格式是FLASHSV2
	SA_ENCODE_VIDEO_VP6,				// 视频编码格式是VP6
	SA_ENCODE_VIDEO_VP6A,				// 视频编码格式是VP6A
	SA_ENCODE_VIDEO_VP6F,				// 视频编码格式是VP6F
	
	// 私有编码格式
	SA_ENCODE_VIDEO_HIK_H264 = 0x81,	// 海康私有H264码流
	SA_ENCODE_VIDEO_HIK_HKH4 = 0x82,	// 海康私有码流
};

enum SA_AUDIO_ENCODED_TYPE
{
	SA_AUDIO_ENCODED_PCM = 0,			// 音频编码格式是PCM8
	SA_AUDIO_ENCODED_ADPCM,				// 音频编码格式是ADPCM
	SA_AUDIO_ENCODED_G711A,				// 音频编码格式是G711A
	SA_AUDIO_ENCODED_G711Mu,			// 音频编码格式是G711Mu
	SA_AUDIO_ENCODED_G726,				// 音频编码格式是G726
	SA_AUDIO_ENCODED_MPEGLayer1,		// 音频编码格式是MPEGLayer1
	SA_AUDIO_ENCODED_AMR,				// 音频编码格式是AMR
	SA_AUDIO_ENCODED_AAC,				// 音频编码格式是AAC
	SA_AUDIO_ENCODED_MPEGLayer2,		// 音频编码格式是MPEGLayer2
	SA_AUDIO_ENCODED_OggVorbis,			// 音频编码格式是OggVorbis
	SA_AUDIO_ENCODED_Mp3,				// 音频编码格式是Mp3
	SA_AUDIO_ENCODED_G722_1,			// 音频编码格式是G722_1
	SA_AUDIO_ENCODED_G729,				// 音频编码格式是G729
	SA_AUDIO_ENCODED_OPUS,				// 音频编码格式是OPUS
	SA_AUDIO_ENCODED_G723S,				// 音频编码格式是G723S
};

enum SA_ENCODE_AUDIO_TYPE
{
	SA_ENCODE_AUDIO_UNKNOWN = 0,
	SA_ENCODE_AUDIO_PCM = 7,			// 音频编码格式是PCM8
	SA_ENCODE_AUDIO_G729,				// 音频编码格式是G729
	SA_ENCODE_AUDIO_IMA,				// 音频编码格式是IMA
	SA_ENCODE_PCM_MULAW,				// 音频编码格式是PCM MULAW
	SA_ENCODE_AUDIO_G721,				// 音频编码格式是G721
	SA_ENCODE_PCM8_VWIS,				// 音频编码格式是PCM8_VWIS
	SA_ENCODE_MS_ADPCM,				    // 音频编码格式是MS_ADPCM
	SA_ENCODE_AUDIO_G711A,				// 音频编码格式是G711A
	SA_ENCODE_AUDIO_AMR,				// 音频编码格式是AMR-NB 窄带
	SA_ENCODE_AUDIO_PCM16,				// 音频编码格式是PCM16
	SA_ENCODE_AUDIO_G711U = 22,		    // 音频编码格式是G711U
	SA_ENCODE_AUDIO_G723 = 25,			// 音频编码格式是G723
	SA_ENCODE_AUDIO_AAC,			    // 音频编码格式是AAC Low Delay
	SA_ENCODE_AUDIO_G726_40,            // 40kbps,以下32/24/16
	SA_ENCODE_AUDIO_G726_32,            // 分别表示比特率的不同
	SA_ENCODE_AUDIO_G726_24,            // 相对于8k采样率的
	SA_ENCODE_AUDIO_G726_16,            // 情况下
	SA_ENCODE_AUDIO_MP2,				// 音频编码格式是mp2
	SA_ENCODE_AUDIO_OGG,				// 音频编码格式是ogg vorbis
	SA_ENCODE_AUDIO_MP3,				// 音频编码格式是mp3
	SA_ENCODE_AUDIO_G722_1,				// 音频编码格式是G722.1

	SA_ENCODE_AUDIO_TALK = 0x30,		// 音频编码格式是对讲
	SA_ENCODE_AUDIO_AC3,				// 音频编码格式是AC3
};

// 码流封装格式
enum
{
	SA_STREAM_TYPE_UNKNOWN = 0,			// 未知码流
	SA_STREAM_TYPE_MPEG4,				// MPEG4
	SA_STREAM_TYPE_DHPT =3,				// 大华老码流：DHPT
	SA_STREAM_TYPE_NEW,					// 大华老码流：NEW
	SA_STREAM_TYPE_HB,					// 大华老码流：HB
	SA_STREAM_TYPE_AUDIO,				// 音频流
	SA_STREAM_TYPE_PS,					// MPEG-2：PS
	SA_STREAM_TYPE_DHSTD,				// 大华最新的标准码流
	SA_STREAM_TYPE_ASF,					// ASF
	SA_STREAM_TYPE_3GPP,				// 3GP
	SA_STREAM_TYPE_RAW,					// 大华老码流：裸码流
	SA_STREAM_TYPE_TS,					// MPEG-2：TS
	SA_STREAM_TYPE_SVC,					// svc
	SA_STREAM_TYPE_AVI,					// AVI
	SA_STREAM_TYPE_MP4,					// MP4
	SA_STREAM_TYPE_CGI,					// CGI
	SA_STREAM_TYPE_WAV,					// WAV音频
	SA_STREAM_TYPE_FLV,					// FLV
	SA_STREAM_TYPE_RYMS,				// RY码流

	SA_STREAM_TYPE_MKV,					// MKV
	SA_STREAM_TYPE_RTP,					// RTP
	SA_STREAM_TYPE_RAW_MPEG4,			// MPEG4裸码流
	SA_STREAM_TYPE_RAW_H264,			// H264裸码流
	SA_STREAM_TYPE_RAW_H265,			// H265裸码流
	SA_STREAM_TYPE_WMV,					// WMV
	SA_STREAM_TYPE_RAW_MPEG2,			// MPEG2裸码流
	SA_STREAM_TYPE_RAW_SVAC,			// SVAC裸码流
	SA_STREAM_TYPE_MOV,					// MOV
	SA_STREAM_TYPE_VOB,					// VOB
	SA_STREAM_TYPE_RAW_H263,			// H263
	SA_STREAM_TYPE_RM,					// RM
	SA_STREAM_TYPE_DHPS,				// MPEG-2：PS
	SA_STREAM_TYPE_MIDI,				// MIDI

	// 第三方厂商类型
	SA_STREAM_TYPE_HENGYI = 0x81,		//HENGYI
	SA_STREAM_TYPE_HUANGHE,				//HUANGHE
	SA_STREAM_TYPE_LANGCHI,				//LANGCHI
	SA_STREAM_TYPE_TDWY,				//TDWY
	SA_STREAM_TYPE_DALI,				//DALI
	SA_STREAM_TYPE_LVFF,				//LVFF
	SA_STREAM_TYPE_H3C,					//H3C
	SA_STREAM_TYPE_FENGDA,				//FENGDA
	SA_STREAM_TYPE_MDVRX,				//MDVRX
	SA_STREAM_TYPE_PU8000,				//PU8000
	SA_STREAM_TYPE_DVR,					//DVR
	SA_STREAM_TYPE_IFV,					//IFV
	SA_STREAM_TYPE_264DV,				//264DV
	SA_STREAM_TYPE_ZWSJ,				//ZWSJ
	SA_STREAM_TYPE_SANLI,				//SANLI
	SA_STREAM_TYPE_HIK_PRIVATE,			//HIK_PRIVATE
	SA_STREAM_TYPE_HIK_PS,				//HIK_PS
	SA_STREAM_TYPE_STAR,				//STAR
	SA_STREAM_TYPE_LIYUAN,				//LIYUAN
};

enum
{
	SA_PARSE_TYPE_NOT_SUPPORT = 0,
	SA_PARSE_TYPE_ONLY_STREAM = 1,
	SA_PARSE_TYPE_ONLY_FILE = 2,
	SA_PARSE_TYPE_SUPPORT_ALL = 3,
};

// 错误标志位
enum
{
	SA_ERROR_FLAGS_NOERROR = 0,		    // 数据校验无误
	SA_ERROR_FLAGS_TIMESTAND,			// 时间戳错误
	SA_ERROR_FLAGS_LENGTH,				// 长度出错
	SA_ERROR_FLAGS_HEAD_VERIFY,		    // 帧头内部数据校验
	SA_ERROR_FLAGS_DATA_VERIFY,		    // 数据校验失败
	SA_ERROR_FLAGS_LOST_HEADER,		    // 数据丢失帧头
	SA_ERROR_FLAGS_UNKNOWN,			    // 不可知错误
	SA_ERROR_FLAGS_LOSTFRAME,           // 丢帧
	SA_ERROR_FLAGS_WATERMARK,           // 水印校验错误
	SA_ERROR_FLAGS_CONTEXT,             // 上下文错误
	SA_ERROR_FLAGS_NOSUPPORT,           // 不支持的码流
    SA_ERROR_FLAGS_FRAME_HALF_BAKED,    // 帧不完整
	SA_ERROR_FLAGS_SUBTYPE_UNKNOWN		// 未知帧类型
};

// 解交错标志
enum
{
	SA_DEINTERLACE_PAIR = 0 ,			// 解码后拉伸
	SA_DEINTERLACE_SINGLE,				// 解码两次
	SA_DEINTERLACE_NONE					// 无解交错
};

// 索引类型标志位
enum
{
	SA_INDEX_BIT_FLAG_VIDEO_I = 1,			// 视频I帧
	SA_INDEX_BIT_FLAG_VIDEO_P = 2,			// 视频P帧
	SA_INDEX_BIT_FLAG_VIDEO_B = 4,			// 视频B帧
	SA_INDEX_BIT_FLAG_AUDIO = 8,			// 音频帧
	SA_INDEX_BIT_FLAG_DATA = 16,			// 数据帧
	SA_INDEX_BIT_FLAG_ALL = 0xffffffff		// 所有帧
};

// 时间信息
typedef struct
{
	int nYear;					// 年
	int nMonth;					// 月
	int nDay;					// 日
	int nHour;					// 小时
	int nMinute;				// 分钟
	int nSecond;				// 秒
	int nMilliSecond;			// 毫秒
} SA_TIME;

// 透雾参数
typedef struct
{
    int bIsExist;				// 是否存在此结构 0:不存在 1:存在
    int nMode;					// 透雾模式 1:关闭 2:自动 3:手动 其它:保留
    int nIntension;				// 透雾强度0-2
    int nAirLightMode;			// 大气光模式1:自动 2: 手动 其它:保留
    int nAirLightIntesion;		// 大气光强度0-15
}SA_FOG_THROUGH;

// 厂商类型
enum 
{
    SA_COMPANY_TYPE_HIK = 1,                    // 海康码流
    SA_COMPANY_TYPE_HANBANG,                    // 汉邦码流
    SA_COMPANY_TYPE_YUSHI,                      // 宇视码流
    SA_COMPANY_TYPE_INTERNATIONAL_DEVICE_PS,    // 国际设备PS码流
    SA_COMPANY_TYPE_XINCHAN,                    // 信产码流
    SA_COMPANY_TYPE_LIYUAN,                     // 立元码流
    SA_COMPANY_TYPE_BIT,                        // 比特码流
    SA_COMPANY_TYPE_OLD_DH,                     // 老大华码流
    SA_COMPANY_TYPE_STD_TS,                     // 标准ts流
    SA_COMPANY_TYPE_TDYG,                       // 天地阳光
    SA_COMPANY_TYPE_ANXUNSHI,                   // 安迅士
    SA_COMPANY_TYPE_DFWL,                       // 东方网力
    SA_COMPANY_TYPE_JUFENG,                     // 巨峰
    SA_COMPANY_TYPE_KEDA,                       // 科达
    SA_COMPANY_TYPE_LG,                         // LG
    SA_COMPANY_TYPE_MAISHI,                     // 迈视
    SA_COMPANY_TYPE_TONGZUN,                    // 同尊
    SA_COMPANY_TYPE_VIVO,                       // vivo
    SA_COMPANY_TYPE_WEIHAO,                     // 伟昊
    SA_COMPANY_TYPE_XINGWANG,                   // 星望
    SA_COMPANY_TYPE_BJWS,                       // 北京蛙视
    SA_COMPANY_TYPE_XJSX,                       // 先进视讯
    SA_COMPANY_TYPE_SZXY,                       // 深圳信义
    SA_COMPANY_TYPE_ZSYH,                       // 中盛益华
    SA_COMPANY_TYPE_ZXLW,                       // 中兴力维
    SA_COMPANY_TYPE_ZXTX,                       // 中兴通讯
	SA_COMPANY_TYPE_HIK_NOHEAD	= 57,			// 海康码流 无40字节头
};

// 加密类型
enum
{
    SA_ENCRYPT_UNKOWN = 0,
    SA_ENCRYPT_AES,
    SA_ENCRYPT_DES,
    SA_ENCRYPT_3DES
};

// 数字签名摘要算法类型
enum
{
	SA_DIGEST_ALGORITHM_UNKOWN = 0,
	SA_DIGEST_ALGORITHM_SHA1
};

// 数字签名加密算法类型
enum
{
	SA_DIGTAL_SIGNATURE_ENCRYPT_UNKOWN = 0,
	SA_DIGTAL_SIGNATURE_ENCRYPT_RSA

};

typedef struct  
{
    int nVideoEncodeType;				// 视频编码类型
    int nFrameRate;						// 帧率
    int nWidth;							// 宽
    int nHeight;						// 高
    int nSPS_PPSLen;					// sps和pps信息长
    unsigned char* pSPS_PPSData;		// sps和pps信息
    int nAudioEncodeType;				// 音频编码类型
    int nSamplerPerSec;					// 音频采样率
    int bitsPerSample;					// 音频采样位数
}SA_SDP_INFO;

typedef struct
{
	unsigned char chType;				// 1:按字节（无符号数）进行算数＋
	unsigned char chLength;				// type中规定的操作单元长度
	unsigned char chValue;				// 操作数
	unsigned char nReserved;			// 保留参数
}SA_DATA_CUSTOM_CHANGE;

#ifdef STREAM_ADAPTER_FOR_RELEASE
#pragma pack(1)
#endif

// 帧信息
typedef struct
{
	// 类型
	int						frameType;							// 帧类型
	int						frameSubType;						// 帧子类型
	int						frameEncodeType;					// 帧编码类型
	int						streamType;							// 码流类型

	// 数据
	unsigned char*			streamPointer;						// 指向码流数据,去除帧头,NULL表示无效数据
	int						streamLen;							// 码流长度(不包括帧头、尾)
	unsigned char*			framePointer;						// 指向帧头,NULL表示无效数据
	int						frameLen;							// 帧长度(包括帧头、帧体、帧尾)

	// 时间
	SA_TIME					frameTime;							// 时间信息
	int						timeStamp;							// 时间戳

	// 序号
	int						frameSeq;							// 帧序号
	
	// 视频属性，关键帧才有
	int						frameRate;							// 帧率
	int						width;								// 宽
	int						height;								// 高
	int						deinterlace;						// 解交错
	int						mediaFlag;							// 流类型标记，h264解码用(0：本地码流；2：HS 码流)
	
	// 音频属性
	int						samplesPerSec;						// 采样频率
	int						bitsPerSample;						// 采样位数
	int						channels;							// 声道数

	/*错误标志*/
	int						errorFlags;							// 按错误标志位

    SA_FOG_THROUGH			fogThrough;							// 透雾参数

    unsigned char			allLevels;							// svc总层数
    unsigned char			levelOrder;							// 当前帧处于第几层

    unsigned short			companyType;						// 厂商类型
    unsigned short			tpStreamHeaderLen;					// 三方码流文件头信息长度，tp:third party

    /*支持双音频部分*/
    unsigned char			totalChannels;						// 通道数
    unsigned char			curChannel;							// 通道号

    int						nEncryptType;						// 加密类型
    int						nEncryptLen;						// 加密长度

	SA_DATA_CUSTOM_CHANGE	customChangeInfo;					// 描述数据被特殊修改的情况，用于用户特殊需求
	
	// 分数帧率支持
	unsigned short			rateValue;							// 帧率分子
	unsigned short			rateDenominator;					// 帧率分母

	// 分屏支持
	unsigned short			n_slice;
	unsigned short			m_slice;
	unsigned short			srcPicWidth;
	unsigned short			srcPicHeight;
	unsigned short			sliceInfoOffset;					// 相对于framePointer*/
	unsigned short			sliceInfoLength;					// 分块图像信息的长度*/

	// 鱼眼信息
	unsigned char			fishEyeGain;						// 增益，取值0-100*/
	unsigned char			fishEyeDenoiseLevel;				// 降噪等级，取值0-100*/
	unsigned char			fishInstallStyle;					// 鱼眼安装方式，0：无意义 1：顶装 2：壁装 3：地装*/
																// 如果无意义，说明不是鱼眼信息
	unsigned char			fishEyeCorrectMode;					// 鱼眼矫正模式
																// 1:"Original"原始图像模式
																// 2:"Config"配置模式
																// 3:"Panorama"全景模式
																// 4:"DoublePanorama"双全景模式
																// 5:"OriginalPlusThreeEPtsRegion"1+3模式
																// 6:"Single"单画面EPts模式
																// 7:"FourEPtsRegion"4画面模式
																// 8:"Normal"Narmal模式

	unsigned short			fishEyeCircleX;						// 鱼眼圆心坐标X
	unsigned short			fishEyeCircleY;						// 鱼眼圆心坐标Y

	unsigned short			fishEyeRadius;						// 鱼眼半径
	unsigned char			encryptOffset;						// 0x95
	unsigned char			encryptReserved;					// 保留参数

	int						pictrueStructure;

	// 视频宽高比例0x9B
	unsigned char			ratioWidth;							// 0x9b 编码前宽高比例
	unsigned char			ratioHeigth;
	unsigned char			ratioEncodeWidth;					// 编码后宽高比例
	unsigned char			ratioEncodeHeight;
 
	unsigned int			digtalSignatureSamplenlen;			// 0x9C

	unsigned short			digtalSignatureEncdeclen;
	unsigned char			digtalSignatureDigestType;
	unsigned char			digtalSignatureEncryptType;

	unsigned char*			digtalSignatureEncdecDataPtr;
	
	unsigned char			rotationAngle;						// 码流旋转角度

	unsigned char			svacEncryptKeyLen;
	unsigned short			svacEncryptDataLen;

	unsigned char*			svacEncryptKeyData;

	// 音频属性
	unsigned int			audioBitrate;						// 音频比特率

	unsigned char*			extDataPtr;							// 扩展数据
	unsigned int			extDataLen;							// 扩展数据长度

	unsigned char			bFrameNum;							// 两个P帧之间的B帧数

	unsigned char			nFsMcfRow;							// FS MCF 行数
	unsigned char			nFsMcfCol;							// FS MCF 列数

	unsigned char			reserved[41];						// 保留字节
} SA_FRAME_INFO;
#ifdef STREAM_ADAPTER_FOR_RELEASE
#pragma pack()
#endif

#if (defined(WIN32) || defined(WIN64))
typedef __int64 SPint64;
#else // linux
typedef long long SPint64;
#endif

/*文件方式的帧信息*/
typedef	struct
{
	SPint64 streamOffset;			// 码流裸数据的偏移量(去除帧头)
	SPint64 frameOffset;			// 帧头的偏移量
	unsigned char	reserved[64];	// 保留字节
}SA_INDEX_INFO;

typedef	struct
{
	unsigned char*	modulePath;		// 当前模块路径
	void*			moduleHandle;	// 模块句柄
	unsigned char	reserved[56];	// 保留字节
}SA_INIT_INFO;

// 结构体128字节
typedef	struct
{
	unsigned int filesize;			// 文件总长度
	unsigned int 	createtime;		// 创建时间 utc时间
	unsigned int 	duration;		// 总时长(单位s)

	unsigned int 	framenum;		// 总帧数
	unsigned int videonum;			// 视频总帧数
	unsigned int audionum;			// 音频总帧数

	unsigned int keyframenum;		// 关键帧数
	unsigned int maxframesize;		// 最大帧长度, 预估值

	unsigned char	reserved[96];	// 保留字节
}SA_FILE_INFO;

// 文件索引回调函数
typedef int (CALLMETHOD *fFileIndexCallBack)(IN void* handle,				
									 IN SA_FRAME_INFO* frameInfo,  
									 IN SA_INDEX_INFO* indexInfo,	
									 IN int process,				
									 IN void* userData);			

// 文件信息回调函数
typedef int (CALLMETHOD *fFileInfoCallBack)(IN void* handle,				
									IN SA_FILE_INFO* fileInfo,  		
									IN void* userData);	

// 初始化资源
SA_API SA_RESULT CALLMETHOD SA_LoadLibrary(SA_INIT_INFO* initInfo = NULL);

// 释放链接库资源
SA_API SA_RESULT CALLMETHOD SA_ReleaseLibrary(void);

// 创建流分析器
SA_API void* CALLMETHOD SA_CreateStreamParser(IN int nBufferSize);

// 获取码流类型，在SA_ParseData成功后调用
SA_API SA_RESULT CALLMETHOD SA_GetStreamType(IN void* handle, OUT int* streamType);

// 输入数据流,并同步进行分析
SA_API SA_RESULT CALLMETHOD SA_ParseData(IN void* handle, IN unsigned char* stream, IN int length);

// 同步获取一帧信息,反复调用直到失败
SA_API SA_RESULT CALLMETHOD SA_GetOneFrame(IN void* handle, IN SA_FRAME_INFO* frameInfo);

#ifndef STREAM_ADAPTER_FOR_RELEASE

// 获取解析类型，在SA_ParseData成功后调用
SA_API SA_RESULT CALLMETHOD SA_GetParseType(IN int streamType, OUT int* parseType);

// 获取码流分析器中残留数据
SA_API SA_RESULT CALLMETHOD SA_GetRemainData(IN void* handle, OUT unsigned char** dataPointer, OUT int* sizePointer);

// 清除码流分析器内部的缓冲
SA_API SA_RESULT CALLMETHOD SA_ClearBuffer(IN void* handle);

// 创建文件分析器
SA_API void* CALLMETHOD SA_CreateFileParser(IN char* file, IN fFileIndexCallBack fileIndex, IN void* userData);

// 创建文件分析器
SA_API void* CALLMETHOD SA_CreateFileParserEx1(IN int nType, IN char* file, IN fFileIndexCallBack fileIndex, IN fFileInfoCallBack fileInfo, IN void* userData);

// 创建文件片段分析器
SA_API void* CALLMETHOD SA_CreateSliceParser(IN char* file, IN fFileIndexCallBack fileIndex, IN void* userData, SPint64 sliceoffset, SPint64 slicesize);

// 获取文件索引信息进度信息
SA_API SA_RESULT CALLMETHOD SA_GetProcess(IN void* handle, OUT int* process);

// 得到指定位置的帧信息和帧偏移信息
SA_API SA_RESULT CALLMETHOD SA_GetOneIndex(IN void* handle, IN int index, OUT SA_INDEX_INFO* indexInfo, OUT SA_FRAME_INFO* frameInfo);

// 返回文件索引条数，flags: 索引类型比特标志位，参见SA_INDEX_BIT_FLAG_xxx
SA_API SA_RESULT CALLMETHOD SA_GetIndexCount(IN void* handle, IN int flags, OUT int* indexCount);

// 一次获取多条索引信息
SA_API SA_RESULT CALLMETHOD SA_GetAllIndex(IN void* handle, IN int flags, OUT SA_INDEX_INFO* indexInfo, OUT SA_FRAME_INFO* frameInfo, IN int structCount, OUT int* indexCount);

// 通过索引得到SA_FRAME_INFO结构体信息。
SA_API SA_RESULT CALLMETHOD SA_GetFrameByIndex(IN void* handle, IN SA_INDEX_INFO* indexInfo, OUT SA_FRAME_INFO* frameInfo);

// 设置实时流解析秘钥  type : 秘钥类型，如SA_ENCRYPT_AES；key：秘钥数据；keylen：秘钥长度
SA_API SA_RESULT CALLMETHOD SA_StreamEncryptKey(IN void* handle,IN unsigned int type, IN unsigned char* key, IN int keylen);

// 设置文件解析秘钥 type : 秘钥类型，如SA_ENCRYPT_AES；key：秘钥数据；keylen：秘钥长度
SA_API SA_RESULT CALLMETHOD SA_FileEncryptKey(IN void* handle,IN unsigned int type, IN unsigned char* key, IN int keylen);

#endif

//  销毁码流分析器
SA_API SA_RESULT CALLMETHOD SA_Destroy(IN void* handle);

// 获得码流分析库错误码
SA_API SA_RESULT CALLMETHOD SA_GetLastError(IN void* handle);

#ifndef STREAM_ADAPTER_FOR_RELEASE
// 将错误码转换为字符串
SA_API SA_RESULT CALLMETHOD SA_ErrorToString(IN int error, OUT char** text);
#endif

#ifdef __cplusplus
}
#endif

#endif