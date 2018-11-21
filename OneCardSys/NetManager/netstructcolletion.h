#ifndef _AL_NET_STRUCT_COLLECTION_H
#define _AL_NET_STRUCT_COLLECTION_H

#include "netdefcollection.h"
#include "netenumcollection.h"

#if !defined(WIN32) && !defined(WIN64)
#include "../Platform/platform.h"
#endif

/*****************************************************************************************
 *							netmanager library �ṹ�嶨��									 *
 *****************************************************************************************/

//////////////////////////////////////////////////////////////////////////////////////
// ͼ��Ԫ����ؽṹ

// �ߴ�
typedef struct 
{
	int                 nWidth;                     // ����
	int                 nHeight;                    // �߶�
} STU_SIZE;

// ��ά�ռ��
typedef struct 
{
	short            nx;
	short            ny;
} STU_POINT, *P_STU_POINT;

// һ�������
typedef struct 
{
	STU_POINT        stuPoints[2];
}STU_POINT_PAIR;

// ��������߶�����Ϣ
typedef struct
{
	int			nPointNum;				// ������
	STU_POINT   stuPoints[COUNT(20)];	// ������Ϣ
}STU_POLY_POINTS, *P_STU_POLY_POINTS;

// ����
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

// ͼƬ�ֱ���
typedef struct
{
	unsigned short   snWidth;		// ��
	unsigned short   snHeight;		// ��
}STU_RESOLUTION, *P_STU_RESOLUTION;

// ��ɫRGBA
typedef struct
{
	int                 nRed;                       // ��
	int                 nGreen;                     // ��
	int                 nBlue;                      // ��
	int                 nAlpha;                     // ͸��
}STU_COLOR_RGBA, *P_STU_COLOR_RGBA;

// ��ɫBCSH
typedef struct 
{
	int                 nBirghtness;                // ����
	int                 nContrast;                  // �Աȶ�
	int                 nSaturation;                // ���Ͷ�
	int                 nHue;                       // ɫ��
} STU_COLOR_BCSH;

//////////////////////////////////////////////////////////////////////////////////////
// ʱ��Ԫ����ؽṹ
                                                               
typedef struct 
{
	// ����ʾ¼��ʱ���ʱ����λ��ʾ�ĸ�ʹ��
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
	unsigned int			dwYear;                  // ��
	unsigned int			dwMonth;                 // ��
	unsigned int			dwDay;                   // ��
	unsigned int			dwHour;                  // ʱ
	unsigned int			dwMinute;                // ��
	unsigned int			dwSecond;                // ��
} STU_TIME, *P_STU_TIME;

typedef struct 
{
	unsigned int			dwYear;                  // ��
	unsigned int			dwMonth;                 // ��
	unsigned int			dwDay;                   // ��
	unsigned int			dwHour;                  // ʱ
	unsigned int			dwMinute;                // ��
	unsigned int			dwSecond;                // ��
	unsigned int			dwMillisecond;           // ����
	unsigned int			dwReserved[2];           // �����ֶ�
} STU_TIME_EX,*P_STU_TIME_EX;

// ʱ�䶨��
typedef struct
{
	DWORD                second:6;                // ��    1-60        
	DWORD                minute:6;                // ��    1-60        
	DWORD                hour:5;                  // ʱ    1-24        
	DWORD                day:5;                   // ��    1-31        
	DWORD                month:4;                 // ��    1-12        
	DWORD                year:6;                  // ��    2000-2063    
} STU_TIME_MIN, *P_STU_TIME_MIN;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �豸ϵͳ��Ϣ

// �豸��Ϣ
typedef struct
{
	char szDeviceType[32];			// �豸����
	char szDeviceClass[32];			// �豸���
	char szSerialNumber[64];		// �豸���к�
	unsigned char reserved[1280];	// ����λ
}STU_SYS_DEVICE_INFO, *P_STU_SYS_DEVICE_INFO;

// �����汾��Ϣ
typedef struct  
{
	char szVersion[32];				// �����汾��Ϣ
	char szBuildDate[32];			// �汾����ʱ��
	unsigned char reserved[256];	// ����λ
}STU_SYS_SOFTWARE_VERSION, *P_STU_SYS_SOFTWARE_VERSION;

// Ӳ���汾��Ϣ
typedef struct 
{
	char szVersion[32];				// �����汾��Ϣ
	char szModel[32];				// �汾����ʱ��
	unsigned char reserved[256];	// ����λ
}STU_SYS_HARDWARE_VERSION, *P_STU_SYS_HARDWARE_VERSION;

// ��������Ϣ
typedef struct
{
	char szModel[32];				// ��������Ϣ
	char szFrequency[16];			// ������Ƶ��
	unsigned char nUsage;			// �����������ʣ�%��
	unsigned char nTemperature;		// �������¶�(���϶�)
	unsigned char reserved1[2];		// �ֽڶ���
	unsigned char reserved2[60];	// ����λ
}STU_SYS_PROCESSOR_INFO, *P_STU_SYS_PROCESSOR_INFO;

// �ڴ���Ϣ
typedef struct
{
	unsigned int	nTotalSize;		// �ܴ�С���ֽڣ�
	unsigned int	nFreeSize;		// �����С(�ֽ�)
	unsigned char   reserved[64];	// Ԥ��λ
}STU_SYS_MEMORY_INFO, *P_STU_SYS_MEMORY_INFO;

// ϵͳ��Ϣ
#define MAX_LANGUAGE_LENGTH			20
#define MAX_LANGUAGE_NUM			32
typedef struct  
{
	BOOL						bAppAutoStart;				// Ӧ�ó����Ƿ�������
	int							nSupportLangNum;			// ֧�ֵ���������
	// �����ַ���,","�ָ����硰SimpleChinese,English�������֧�� 32 ������
	char						szLanguages[MAX_LANGUAGE_LENGTH * MAX_LANGUAGE_NUM];			
	int							nProcessorNum;				// ����������
	STU_SYS_PROCESSOR_INFO		stuProcessorInfoArray[16];	// ��������Ϣ����(���16����������Ϣ)
	STU_SYS_DEVICE_INFO			stuDeviceInfo;				// �豸��Ϣ
	STU_SYS_SOFTWARE_VERSION	stuSoftWareVer;				// ������Ϣ
	STU_SYS_HARDWARE_VERSION	stuHardWareVer;				// Ӳ����Ϣ
	STU_SYS_MEMORY_INFO			stuMemoryInfo;				// �ڴ���Ϣ
	unsigned char				reserved[2048];				// ����λ
}STU_SYS_INFO, *P_STU_SYS_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �¼�/�����ṹ�嶨��

typedef struct
{
	BYTE					nPicType;					// ͼƬ���� 1����ͨ��2���ϳɣ�3����ͼ
	BYTE					reserved1[3];				// �����ֶ�
	STU_RESOLUTION			stuResolution;				// �ֱ�����Ϣ
	BYTE					reserved[1016];				// �����ֶ�
}STU_EVENT_COMMON_INFO, *P_STU_EVENT_COMMON_INFO;

typedef struct
{
	unsigned int			nObjcetID;					// ����Ψһ��ʶ ID
	char					szObjectType[32];			// ������������
	STU_RECT_L				stuBoundingBox;				// ��Χ��
	unsigned char			nBelief;					// ������[0-255]	 ֵԽ���ʾ����
	unsigned char			nQuality;					// ������[0-255] ֵԽ������Խ��
	BYTE					reserved1[2];				// �ֽڶ���
	float					fBlur;						// ģ����, 0 ��ʾ��������ֵԽ��Խģ��
	float					fPosePitch;					// ���¸����Ƕ�
	float					fPoseRoll;					// ����ҡ�ڽǶ�
	float					fPoseYaw;					// ˮƽ��ת�Ƕ�
	unsigned char			reserved2[56];				// �����ֶ�
}STU_EVENT_FACE_INFO, *P_STU_EVENT_FACE_INFO;

typedef struct  
{
	unsigned int			nPersonID;						// ��Ա ID
	char					szName[128];					// ����ͼ����
	EM_SEX_TYPE				emSexType;						// �Ա�
	STU_TIME				stBirthday;						// ����
	char					szCertificateType[64];			// ֤������
	char					szID[128];						// ֤�� ID
	BYTE					reserved1[32];					// ��������1
	char					szCountry[64];					// ����
	char					szProvince[64];					// ʡ��
	char					szCity[128];					// ���ڳ���
}STU_EVENT_PERSON_INFO, *P_STU_EVENT_PERSON_INFO;

typedef struct  
{
	char					szFaceToken[64];			// ������ʶ��
	float					fSearchScore;				// ����ʶ������ [0-100]
	float					fSearchThreshold;			// ����ʶ����ֵ [0-100]
	STU_EVENT_PERSON_INFO	stPersonInfo;				// ������ص���Ա��Ϣ
	BYTE					reserved[64];				// ����λ
}STU_EVENT_FACE_RECOGNIZE_INFO, *P_STU_EVENT_FACE_RECOGNIZE_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////
// FACE
/////////////////////////////////////////////////////////////////////////////////////////////////////

// N-�������-����ȫͼ
typedef struct
{
	int						nChannel;					// ͨ����
	unsigned int			nGroupID;					// ����
	unsigned int			nIndexInGroup;				// �������
	unsigned int			nCountInGroup;				// �������ͼƬ��Ŀ
	char					szEvent[64];				// �¼�����
	char					szClass[64];				// ��������
	char					szAction[64];				// ��������
	double					dPTS;						// PTS
	unsigned int			nUTC;						// UTC
	unsigned short			nUTCMS;						// UTCMS
	char					szTimeZone[16];				// ʱ���ַ�����GMT+08:00��
	int						nTimeZoneMS;				// ��UTCʱ������������ = -8*60*60*1000��
	unsigned short			nFaceCount;					// ��ͼ�ڵ���������
	P_STU_EVENT_FACE_INFO	pstuFaceInfoArray;			// ������ͼ��Ϣ����
	STU_TIME_EX				stuTime;					// �¼�ʱ��
	unsigned int			nFirstObjectID;				// ��һ����ͼ������ ID ��
	unsigned int			nLastObjectID;				// ���һ����ͼ������ ID ��
	unsigned char			reserved1[212];				// �����ֽ�1
	STU_EVENT_COMMON_INFO	stuCommInfo;				// ������Ϣ����
	unsigned char			reserved2[1024];			// �����ֶ�2
}STU_EVENT_FACE_SNAP_WHOLE, *P_STU_EVENT_FACE_SNAP_WHOLE;

// N-�������-������ͼ
typedef struct
{
	int						nChannel;					// ͨ����
	unsigned int			nGroupID;					// ����
	unsigned int			nIndexInGroup;				// �������
	unsigned int			nCountInGroup;				// �������ͼƬ��Ŀ
	char					szEvent[64];				// �¼�����
	char					szClass[64];				// ��������
	char					szAction[64];				// ��������
	double					dPTS;						// PTS
	unsigned int			nUTC;						// UTC
	unsigned short			nUTCMS;						// UTCMS
	unsigned char			reserved1[2];				// �����ֶ�1(�ֽڶ���)
	char					szTimeZone[16];				// ʱ���ַ�����GMT+08:00��
	int						nTimeZoneMS;				// ��UTCʱ������������ = -8*60*60*1000��	
	STU_TIME_EX				stuTime;					// �¼�ʱ��
	unsigned char			reserved2[220];				// �����ֽ�2
	STU_EVENT_FACE_INFO		stuFaceInfo;				// ������Ϣ
	STU_EVENT_COMMON_INFO	stuCommInfo;				// ������Ϣ����
	unsigned char			reserved3[1024];			// �����ֶ�3
}STU_EVENT_FACE_SNAP_PART, *P_STU_EVENT_FACE_SNAP_PART;

// N-����ʶ��-������ͼ
typedef struct
{
	int									nChannel;					// ͨ����
	unsigned int						nGroupID;					// ����
	unsigned int						nIndexInGroup;				// �������
	unsigned int						nCountInGroup;				// �������ͼƬ��Ŀ
	char								szEvent[64];				// �¼�����
	char								szClass[64];				// ��������
	char								szAction[64];				// ��������
	double								dPTS;						// PTS
	unsigned int						nUTC;						// UTC
	unsigned short						nUTCMS;						// UTCMS
	unsigned char						reserved1[2];				// �����ֶ�1(�ֽڶ���)
	char								szTimeZone[16];				// ʱ���ַ�����GMT+08:00��
	int									nTimeZoneMS;				// ��UTCʱ������������ = -8*60*60*1000��	
	STU_TIME_EX							stuTime;					// �¼�ʱ��
	unsigned int						nObjectID;					// ���� ID
	char								szFaceGroupAlias[128];		// ���������
	int									nPass;						// ����ʶ���Ƿ�ͨ�� 0-��ͨ�� 1-ͨ��
	unsigned char						reserved2[64];				// �����ֽ�2
	int									nFaceRecognizeInfoCount;	// ʵ������ʶ������Ŀ	
	STU_EVENT_FACE_RECOGNIZE_INFO		stFaceRecognizeInfoArr[MAX_FACE_REC_INFO_NUM];	// ����ʶ��������
	STU_EVENT_COMMON_INFO				stuCommInfo;				// ������Ϣ����
	unsigned char						reserved3[1024];			// �����ֶ�3
}STU_EVENT_FACE_RECOGNIZE_CUTOUT, *P_STU_EVENT_FACE_RECOGNIZE_CUTOUT;

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Traffic
/////////////////////////////////////////////////////////////////////////////////////////////////////

// ��ͨ������Ϣ
typedef struct
{
	// �����ţ��豸�е��Զ��峵���ţ�
	int					nLane;
	// �ٶ�    ��λKm/h
	int					nSpeed;
	// ����λ
	unsigned char		reserved[2560];                      
}STU_TRAFFIC_COMMON_INFO, *P_STU_TRAFFIC_COMMON_INFO;

// ��ͨ������Ϣ
typedef struct
{
	unsigned int			nObjectID;					// ����ID
	unsigned int			nRelatedID;					// ��������ID 
														// �������ID�ǳ��ƣ���������ID�ǳ����������������ID�ǳ���	
	char					szObjectType[32];			// ������𣨳��� - "Plate" / ���� - "Car"��
	char					szObjectSubType[32];		// ���������ͣ����� - �������� / ���� - �������ͣ�
	char					szLabel[32];				// ��ʶ�������ǳ��Ʊ�ʾ���ƺ��룬�����ǳ�����ʾ���꣩
	char					szColor[32];				// ��ɫ�������ǳ��Ʊ�ʾ������ɫ�������ǳ�����ʾ������ɫ��
	STU_RECT_L				stuBoundingBox;				// ��Χ��
	unsigned char			reserved[2080];				// �����ֶ�
}STU_TRAFFIC_OBJECT_INFO, *P_STU_TRAFFIC_OBJECT_INFO;

// ��ͨ - ������Ϣ
typedef struct
{
	int							nChannel;					// ͨ����
	unsigned int				nGroupID;					// ����
	unsigned int				nIndexInGroup;				// �������
	unsigned int				nCountInGroup;				// �������ͼƬ��Ŀ
	char						szEvent[64];				// �¼�����
	char						szClass[64];				// ��������
	char						szAction[64];				// ��������
	double						dPTS;						// PTS
	unsigned int				nUTC;						// UTC
	unsigned short				nUTCMS;						// UTCMS
	unsigned char				reserved1[2];				// ����λ1���ֽڶ��룩
	char						szTimeZone[16];				// ʱ���ַ�����GMT+08:00��
	int							nTimeZoneMS;				// ��UTCʱ������������ = -8*60*60*1000��
	STU_TIME_EX					stuTime;					// �¼�ʱ��
	unsigned char				reserved2[220];				// �����ֽ�2
	STU_TRAFFIC_COMMON_INFO		stuTrafficCommInfo;			// ��ͨ������Ϣ
	STU_TRAFFIC_OBJECT_INFO		stuPlateInfo;				// ������Ϣ
	STU_TRAFFIC_OBJECT_INFO		stuVehicleInfo;				// ������Ϣ
	STU_EVENT_COMMON_INFO		stuCommInfo;				// ������Ϣ
	unsigned char				reserved3[1280];			// �����ֽ�3
}STU_EVENT_TRAFFIC_PASS, *P_STU_EVENT_TRAFFIC_PASS;

// ��ͨ - ���ڿ�ͼ��Ϣ
typedef struct
{
	int							nChannel;					// ͨ����
	unsigned int				nGroupID;					// ����
	unsigned int				nIndexInGroup;				// �������
	unsigned int				nCountInGroup;				// �������ͼƬ��Ŀ
	char						szEvent[64];				// �¼�����
	char						szClass[64];				// ��������
	char						szAction[64];				// ��������
	double						dPTS;						// PTS
	unsigned int				nUTC;						// UTC
	unsigned short				nUTCMS;						// UTCMS
	unsigned char				reserved1[2];				// ����λ1���ֽڶ��룩
	char						szTimeZone[16];				// ʱ���ַ�����GMT+08:00��
	int							nTimeZoneMS;				// ��UTCʱ������������ = -8*60*60*1000��
	STU_TIME_EX					stuTime;					// �¼�ʱ��
	unsigned char				reserved2[220];				// �����ֽ�2
	STU_TRAFFIC_COMMON_INFO		stuTrafficCommInfo;			// ��ͨ������Ϣ
	STU_TRAFFIC_OBJECT_INFO		stuObjectInfo;				// ����/������Ϣ
	STU_EVENT_COMMON_INFO		stuCommInfo;				// ������Ϣ
	unsigned char				reserved3[1280];			// �����ֽ�3
}STU_EVENT_TRAFFIC_PASS_CUTOUT, *P_STU_EVENT_TRAFFIC_PASS_CUTOUT;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����Ƶ
/////////////////////////////////////////////////////////////////////////////////////////////////////

// �ص���Ƶ����֡��֡�����ṹ��
typedef struct
{
    BYTE                 encode;                 // ��������
    BYTE                 frametype;              // I = 0, P = 1, B = 2...
    BYTE                 format;                 // PAL - 0, NTSC - 1
    BYTE                 size;                   // CIF - 0, HD1 - 1, 2CIF - 2, D1 - 3, VGA - 4, QCIF - 5, QVGA - 6 ,
                                                 // SVCD - 7,QQVGA - 8, SVGA - 9, XVGA - 10,WXGA - 11,SXGA - 12,WSXGA - 13,UXGA - 14,WUXGA - 15, LFT - 16, 720 - 17, 1080 - 18
    DWORD                fourcc;                 // �����H264��������Ϊ0��MPEG4����������дFOURCC('X','V','I','D');
    DWORD                reserved;               // ����
    STU_TIME             struTime;               // ʱ����Ϣ
} STU_VIDEO_FRAME_PARAM;

// �ص���Ƶ����֡��֡�����ṹ��
typedef struct
{
    BYTE                channels;                // ������
    BYTE                samples;                 // ���� 
												 // ��:  0 - 8000,   1 - 11025,	 2 - 16000,   3 - 22050, 
												 //      4 - 32000,  5 - 44100,  6 - 48000
    BYTE                depth;                   // ������� ȡֵ8����16�ȡ�ֱ�ӱ�ʾ
    BYTE                param1;                  // 0 - ָʾ�޷��ţ�1-ָʾ�з���
    DWORD               reserved;                // ����
} STU_CBPCM_DATA_PARAM;

//�ص�YUV���ݵĲ����ṹ��
typedef struct
{
    long                nWidth;                 // ͼ��Ŀ�
    long                nHeight;                // ͼ��ĸ�
    DWORD               reserved[8];            // ����
} STU_CBYUV_DATA_PARAM;

// ��Ƶ��ʽ��Ϣ
typedef struct
{
    BYTE                byFormatTag;                    // �������ͣ���0��PCM
    WORD                nChannels;                      // ������
    WORD                wBitsPerSample;                 // �������            
    DWORD               nSamplesPerSec;                 // ������
} STU_AUDIO_FORMAT_INFO, *P_STU_AUDIO_FORMAT_INFO;

// ��ҹģʽ���ò���
typedef struct
{
	BYTE	byMode;						// ɫ���л�ģʽ��0-���ǲ�ɫ��1-�������Ȼ�ʱ���Զ��л���2-���Ǻڰ�
	BYTE	byDayNightSensitivity;		// ��ҹģʽ�л������ȣ���Χ1-3
	BYTE	byDayNightSwitchDelay;		// ��ҹģʽ�л��ӳ�ʱ��	��λ�룬��Χ2-10
	BYTE	reserved[5];
} STU_CAMERA_DAY_NIGHT_PARAM;

// ��Ƶ��ɫ����
typedef struct
{
	BYTE      byBrightness;				// ����
	BYTE      byContrast;				// �Աȶ�
	BYTE      bySaturation;				// ���Ͷ�
	BYTE      byHue;					// ɫ��
} STU_CAMERA_COLOR;

// ͼ��3D������ز���
typedef struct
{
	BYTE	byTridimDenoise;				// �Ƿ���3D���룬0-�رգ�1-������2-ֻ������Ƶ��3-ֻ����ͼƬ
	BYTE	reserved[3];
	BYTE	byTridimIntensity[2];			// ��ά����ʱ����ǿ�ȣ��±��ʾ��Ƶ��ͼƬ����Χ0~100
	BYTE	byTridimIntensitySpatial[2];	// ��ά���������ǿ�ȣ��±��ʾ��Ƶ��ͼƬ����Χ0~100
} STU_CAMERA_3D_DENOISE;

// �ع���������
typedef struct
{
	BYTE	bGainAuto;				// �Զ�����
	BYTE	byGainMin;				// �Զ���������	��Χ0~100��С��GainMax
	BYTE	byGainMax;				// �Զ���������	��Χ0~100
	BYTE	byGain;					// �̶��������	0~100
} STU_CAMERA_EXPOSURE;

// ��Ȧ���ڲ���
typedef struct
{
	BYTE	bIrisAuto;			// �Զ���Ȧʹ��
	BYTE	byIrisType;			// ��Ȧ����	0-�����ȦP90��1-�����ȦP90��2-DC��Ȧ��3-�̶���Ȧ
	BYTE	reserved[2];
	UINT	dwIris;				// ��ȷ���ֶ���Ȧ��С
} STU_CAMERA_IRIS;

// ��ƽ��ģʽ���ڲ���
typedef struct
{
	EM_WHITE_BALANCE	emWhiteBalance;				// ��ƽ��ģʽ
	BYTE				byColorTemperatureLevel;	// ɫ�µȼ����ڣ���ƽ��Ϊ"WHITEBALANCE_CT_CUSTOM"ģʽ����Ч	0~255
	BYTE				byGainRed;					// ��ɫ������ڣ���ƽ��Ϊ"Custom"ģʽ����Ч	0~100
	BYTE				byGainBlue;					// ��ɫ������ڣ���ƽ��Ϊ"Custom"ģʽ����Ч	0~100
	BYTE				byGainGreen;				// ��ɫ������ڣ���ƽ��Ϊ"Custom"ģʽ����Ч	0~100
	BYTE				byPartWhiteBalanceWeight;	// Ȩ�ز��������������ֲ���ƽ���ȫ�ְ�ƽ���Ȩ�ر���	��Χ0-100
} STU_CAMERA_WHITE_BALANCE;

// ȥ��ģʽ����
typedef struct
{
	BYTE		byMode;			// ͸��ģʽ	0-�ر�,1-�Զ�,2-�ֶ�
	WORD		wValue;			// �ֶ�ģʽǿ��
} STU_CAMERA_DEFOG;

// ���ģʽ
typedef struct
{
	BYTE		byMode;			// ������� 0-ȫ�ֲ�⣬1-�ֲ���⣬2-���ⲹ����3-ǿ������
	BYTE		byIntensity;	// ���ǿ��	0-�رգ�1-����2-�У�3-ǿ
} STU_CAMERA_METERING;

// ����ͷ��������
typedef struct
{
	DWORD						dwSize;				// �ṹ���С
	STU_CAMERA_DAY_NIGHT_PARAM	stuDayNightParam;	// ��ҹģʽ����								VideoInDayNightParam
	STU_CAMERA_COLOR			stuColor[3];		// ��ɫ���ã��±꣺0-���죬1-���ϣ�2-����   VideoInColor
	STU_CAMERA_IRIS				stuIris[3];			// ��Ȧ���ã��±꣺0-���죬1-���ϣ�2-����   VideoInIrisEx
	STU_CAMERA_3D_DENOISE		stu3DDenoise;		// ͼ��3D������ز���						VideoInPre3DDenoise
	STU_CAMERA_EXPOSURE			stueExposure[3];	// ������ڣ��±꣺��Ƶ��ͼƬ����ץ��֡     VideoInExposure
	STU_CAMERA_WHITE_BALANCE	stuWhiteBalance[3];	// ��ƽ��������±꣺��Ƶ��ͼƬ����ץ��֡   VideoInWhiteBalance
	STU_CAMERA_DEFOG			stuDefog[3];		// ȥ�����ã��±꣺0-���죬1-��ҹ��2-����	VideoInDefog
	STU_CAMERA_METERING			stuMetering;		// �������									VideoInMetering
} STU_CFG_CAMERA;

typedef struct
{
	BYTE						bValue;				// ��ʱ���Ƿ���Ч�� 1 ��Ч�� 0 ��Ч
	INT							iStartHour;			// ��ʼʱ��-Сʱ
	INT							iStartMinute;		// ��ʼʱ��-����
	INT							iStartSecond;		// ��ʼʱ��-��
	INT							iEndHour;			// ����ʱ��-Сʱ
	INT							iEndMinute;			// ����ʱ��-����
	INT							iEndSecond;			// ����ʱ��-��
}STU_TIME_SECTION_SCHEDULE;

typedef struct
{
	BYTE						bControlMode;		//¼��ģʽ 0-�Զ���1-�ֶ�,2-�ر�
	STU_TIME_SECTION_SCHEDULE	stuTimeSchedule[WEEK_SECTION][TIME_SECTION];//¼��ƻ�

}STU_CFG_RECORD_PLAN;

typedef struct
{
	UINT						uPackSize;		//¼��������
	UINT						uPackTime;		//¼����ʱ��
	BYTE						bPackType;		//¼��������	0�ǰ�ʱ��¼��
	UINT						uPreRecordTime;	//Ԥ¼ʱ��
	BYTE						bStreamType;	//��������,0����������1�Ǹ�����1,2�Ǹ�����2
}STU_CFG_RECORD_OPTIONS;

//¼������
typedef struct
{
	DWORD						dwSize;				// �ṹ���С
	STU_CFG_RECORD_PLAN			stuRecordPlan;		//¼��ƻ�����
	STU_CFG_RECORD_OPTIONS		stuRecordOptions;	//¼��ѡ��

}STU_CFG_RECORD;

//�洢��
typedef struct
{
	BOOL bSupportFtp;
	BOOL bSupportLocal;
	BOOL bSupportUsb;
}STU_CFG_STORAGE_POINT;

//�洢����
typedef struct
{
	BOOL bOverWrite;

}STU_CFG_STORAGE_POLICY;

//�洢����
typedef struct
{
	DWORD						dwSize;				// �ṹ���С
	STU_CFG_STORAGE_POINT		stuStorPoint[2];//[0]��¼��1��ץͼ
	STU_CFG_STORAGE_POLICY		stuStoragePolicy;
}STU_CFG_STORAGE;

typedef struct
{
	INT							iMouth;
	INT							iWeek;
	INT							iDay;
	INT							iHour;
}STU_DST_TIME;

//����ʱ����
typedef struct
{
	DWORD						dwSize;				// �ṹ���С
	STU_DST_TIME				stuDstStartTime;
	STU_DST_TIME				stuDstEndTime;
	BOOL						bEnable;
	INT							iTimeZone;		//������ʾ����������ʾ����[-12 - 13]
}STU_CFG_DST;

//NTP����
typedef struct
{
	DWORD						dwSize;				// �ṹ���С
	BOOL						bEnable;
	char						bDomainName[64];
	UINT						uInterval;
	UINT						uPort;

}STU_CFG_NTP;

//�Զ���������
typedef struct
{
	DWORD						dwSize;				// �ṹ���С
	BOOL						bEnable;
	UINT						uWeekDay;			//�ܼ�����,[0-6],0�������գ�6��������
	UINT						uHour;				//��������,[0-23]
}STU_CFG_AUTO_MAINTAIN;

typedef struct
{
	UINT						uBaudRate;	//������,ȡֵΪ1200, 2400 ,4800, 9600, 19200, 38400, 57600, 115200
	BYTE						bDataBits;	//����λ,ȡֵΪ5, 6, 7, 8
	BYTE						bCheckMode;	//У��ģʽ��0��ʾ"Even", 1��ʾ"Mark", 2��ʾ"None", 3��ʾ"Odd", 4��ʾ"Space"
	BYTE						bStopBits;	//ֹͣλ��0��ʾ"1", 1��ʾ"1.5", 2��ʾ"2"
}STU_CFG_COMM_ATTRIBUTE;

typedef struct 
{
	STU_CFG_COMM_ATTRIBUTE		stuAttribute;		//��������
	BOOL						bEnable;			//����ʹ��
	BYTE						bProtocol;			//0������ͨ���ڣ�1����͸������
}STU_CFG_COMM_ITEM;

//��������
typedef struct
{
	UINT						uNums;//������Ŀ
	STU_CFG_COMM_ITEM*			stuCommCfg;//��������,�ڴ����ⲿ������ͷ�
}STU_CFG_COMM;

typedef struct
{
	BYTE 						bProtocol[3];//֧�ֵĴ���Э�飬0������ͨ���ڣ�1����͸������
	BYTE 						bBusType;//�������ͣ�0����"RS232"��1����"RS485"
	BYTE 						bCommunication;//֧�ֵ�ͨ��ģʽ��0������˫����1����ȫ˫��
}STU_CFG_COMM_PARAM;

//����������
typedef struct
{
	UINT 						uCommCount;//�豸��֧�ֵĴ�����Ŀ
	STU_CFG_COMM_PARAM*			stuItems;//��������������
}STU_CFG_COMM_CAPS;

//Telenet ����
typedef struct
{
	DWORD						dwSize;	// �ṹ���С
	BOOL						bEnale; //telnetʹ��

}STU_CFG_TELNET;

//��־��ѯ����
typedef struct
{
	char					cStartTime[32];//��־��ѯ��ʼʱ��
	char					cEndTime[32];//��־��ѯ����ʱ��
	char					cMainType[32]; //����־����
	char					cSubType[32];//����־����

}STU_CFG_LOG_CONDITION;

//��־��ϸ��Ϣ
typedef struct
{
	char					cRemoteIP[32]; 
	INT						iChannel;
	char					cConfigName[32];
	char					cNetAdapter[32];

}STU_CFG_LOG_DETAIL;

//��־��ѯ���
typedef struct
{
	char					cLogTime[32];//����־��¼ʱ��
	char					cOperUserName[32];//�����û���
	char					cMainType[32]; //����־����
	char					cSubType[32];//����־����
	STU_CFG_LOG_DETAIL		stuLogDetail;//��־��ϸ��Ϣ

}STU_CFG_LOG_INFO;

#define MAX_LOG_AMOUNT		16
typedef struct
{
	STU_CFG_LOG_INFO		stuResult[MAX_LOG_AMOUNT];//һ������ѯ16����־��Ϣ
	UINT					uTotal;					//��ѯ�����ܹ�����־����
	UINT					uCurAmount;				//��ǰ���ص���־����
}STU_CFG_LOG_RESULT;

//��־��ѯ,֧�ֶ�β�ѯ
typedef struct
{
	STU_CFG_LOG_CONDITION	stuSearchCondition;//��־��ѯ����
	STU_CFG_LOG_RESULT		stuLogResult;//	��־��ѯ���

}STU_CFG_LOG;

typedef struct
{
	BYTE					bIPType;//ip��ַ����:0��������ip��ַ,1����ip��Χ,Ŀǰֻ֧��ipv4
	char					cBeginIPAddr[64];//��ʼip��ַ,����bIPTypeΪ0��1�����
	char					cEndIPAddr[64];//��ֹip��ַ,������bIPTypeΪ1���

	//�����������������޸�
	char					cNewBeginIPAddr[64];
	char					cNewEndIPAddr[64];
}STU_CFG_NETWHITE_BLACK_INFO;

//�ڰ���������
typedef struct
{
	DWORD								dwSize;// �ṹ���С
	BYTE								bType;//�ڰ���������:0-��;1-������,2-������
	BYTE								bOperType;//�������ͣ�0-��ȡ,1-����,2-ɾ��,3-�޸�

	UINT								uCount;//ָ��stuData��Ԫ�ظ���
	STU_CFG_NETWHITE_BLACK_INFO*		stuData;//�ڰ�������Ϣ,�ڴ����ⲿ������ͷ�

}STU_CFG_NETWHITE_BLACK;

//�޸��û�ʱ.ֻ֧���޸ı�ע��Ϣ���û�����,��֧���޸��û���������
typedef struct
{
	char						cComment[32];//��ע��Ϣ
	BYTE						bLevel;//�û�����0�ǹ���Ա,1�ǲ�����,2����ͨ�û�,����Ա�޷�ɾ��
	char						cUserName[32];//�û���
	char						cPassword[32];//����
}STU_CFG_USER_INFO;

typedef struct
{
	BYTE						bOperType;//1:����,2:ɾ��,3:�޸�
	STU_CFG_USER_INFO			stuUserInfo;

}STU_CFG_USER_SET;

typedef struct
{
	char						cComment[32];//��ע��Ϣ
	BYTE						bLevel;//�û�����0�ǹ���Ա,1�ǲ�����,2����ͨ�û�,����Ա�޷�ɾ��
	char						cUserName[32];//�û���
	char						cPassword[32];//����

}STU_CFG_ADD_USER;//���������û�

typedef struct
{
	char						cUserName[32];//�û���

}STU_CFG_DELETE_USER;//����ɾ���û�

typedef struct
{
	char						cComment[32];//��ע��Ϣ
	BYTE						bLevel;//�û�����0�ǹ���Ա,1�ǲ�����,2����ͨ�û�,����Ա�޷�ɾ��
	char						cUserName[32];//�û���
	char						cOldPassword[32];//����
	char						cNewPassword[32];//�µ�����

}STU_CFG_MODIFY_USER;//�����޸��û�

typedef struct
{
	UINT						uCount;//��Ҫ��ȡ���û�����
	STU_CFG_USER_INFO*			stuUserInfo;//�û���Ϣ�����ⲿ������ͷ�

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
	UINT								uCount;//��Ҫ��ȡ���û�����
	STU_CFG_USER_ONLINE_INFO*			stuUserInfo;//�û���Ϣ�����ⲿ������ͷ�

}STU_CFG_USER_ONLINE;

//��ͼ���ýṹ��
typedef struct
{
	BOOL								bEnable;
	BYTE								bType;			// 0��������ͼ; 1�ǰ�����ͼ; 2��ȫ����ͼ; 3�ǳ��ƿ�ͼ

}STU_CFG_DIG_PICTURE;

//��������
typedef struct
{
	BOOL		bMajorStreamIntelliTrack;//�Ƿ���Ӹ�����Ϣ
}STU_CFG_OVERLAP;

//ץͼ����
typedef struct
{
	BOOL		bPictureUpload;//�Ƿ���ʾ����ͼ
}STU_CFG_GRAP_PIC;

//������ץͼ����
typedef struct
{
	STU_CFG_OVERLAP			stuOverLap;
	STU_CFG_GRAP_PIC		stuGrapPic;
}STU_CFG_OVERLAP_PIC;

//�����������,���Ͻ������½�����[0,0]-[8192,8192]
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
	INT			bPreRecordTime;//Ԥ¼ʱ��,ȡֵ��[0,5]
	INT			iRecordLatch;//¼����ʱʱ��

	BOOL		bAlarmOutEnable;
	INT			iAlarmOutChannels;//�����ı������ͨ�������������16��
	INT			iAlarmOutChannelsValue[16];
	INT			iAlarmOutLatch;
	
}STU_CFG_INTELLI_RULE_EVENT_HANDLE;

//���ܹ�������
typedef struct
{
	BOOL								bEnable;
	STU_CFG_INTELLI_RULE_EVENT_HANDLE	stuEventHandle;

}STU_CFG_INTELLI_RULE;

//���ܲ�������
typedef struct
{
	STU_CFG_INTELLI_SCENCE				stuIntlliScence;
	STU_CFG_INTELLI_RULE				stuIntelliRule;
}STU_CFG_INTELLI_PARAM;

typedef struct
{
	BOOL								bEnable;//28181ʹ��
	UINT								uAlarmInChannelNum;//��������ͨ����
	char								cAlarmInId[32];//��������ͨ�����
	UINT								uChannelNum;//ͨ������
	char								cChannelId[32];//ͨ�����
	char								cCivilCode[16];//������ʶ����
	char								cUserName[32];//�û���,���豸id
	char								cPassword[32];//ע������
	UINT								uKeepAliveInterval;//����ʱ����
	UINT								uLocalSipPort;//����sip�˿ں�
	UINT								uMaxTimeoutCount;//���������ʱʱ��
	char								cSipDomain[32];//����
	char								cSipServerId[32];//sip������id
	char								cSipServerIP[16];//sip������ip
	UINT								uSipServerPort;//sip�������˿�

}STU_CFG_GB28181_PARAM;

//����������������
typedef struct
{
	BOOL						bAlarmOutEnable;
	UINT						uAlarmOutLatch;
	UINT						uAlarmOutChannels;//������ͨ������,�������16��ͨ��
	UINT						uAlarmOutChannelsValue[16];//������ͨ��ֵ				
	STU_TIME_SECTION_SCHEDULE	stuTimeSchedule[WEEK_SECTION][TIME_SECTION];//����ʱ��
}STU_ALARM_EVENT_HANDLE;

//�����������
typedef struct
{
	BOOL						bEnable;			//��������ʹ��
	BYTE						bSensorType;		//����������,0�ǳ���,1�ǳ���
	STU_ALARM_EVENT_HANDLE		stuAlarmHandle;		//������������

}STU_CFG_ALARM_IN_PARAM;

//�����������
typedef struct
{
	BYTE						bMode;//���ģʽ,0���Զ����,1��ǿ�ƿ�������,2��ǿ�ƹرձ���
}STU_CFG_ALARM_OUT_PARAM;


//���������������
typedef struct
{
	UINT								uAlarmInChannels;//��������ͨ����
	STU_CFG_ALARM_IN_PARAM*				stuAlarmInParams;//�����������,�ڴ����ⲿ������ͷ�
	UINT								uAlarmOutChannels;//�������ͨ����
	STU_CFG_ALARM_OUT_PARAM*			stuAlarmOutParams;//�����������,�ڴ����ⲿ������ͷ�

}STU_CFG_ALARM_PARAM;

//����������
typedef struct
{
	
	UINT							uMinMajorStreamBitrate;//�豸֧�ֵ���С����
	UINT							uMaxMajorStreamBitrate;//�豸֧�ֵ��������
	UINT							uMaxExtraStreams;//�豸֧�ֵ����������
	UINT							uSupportedStandardNums;//�豸���֧�ֵ���Ƶ��ʽ��,���֧��4��
	BYTE							bSupportedStandardValues[4];// EM_STANDARD_TYPE ����

}STU_CFG_ENCODE_CAPS;

typedef struct
{
	UINT							uMiniBitRate;
	UINT							uMaxBitRate;

	UINT							uCompressionTypeNums;//���10�� EM_VIDEO_STREAM_CODE_TYPE
	BYTE							bCompressionTypeValus[10];

	UINT							uH264ProfilesTypeNums;//���10��
	BYTE							bH264ProfilesTypeValues[10];//  EM_H264_ENCODE_LEVEL
	 
	UINT							uMaxFps;
	UINT							uMaxRoiCount;

	UINT							uResolutionTypeNums;			// ���10��
	BYTE							bResolutionTypeValus[10];		// EM_VIDEO_STREAM_RESOLUTION_TYPE

}STU_CFG_VIDEOCONFIG_CAPS;

//��������������
typedef struct
{
	INT								iMainStreamCapsCount;			// ���3��
	STU_CFG_VIDEOCONFIG_CAPS*		stuMainStreamVideoCaps;
	INT								iExtraStreamCapsCount;			// ���3��
	STU_CFG_VIDEOCONFIG_CAPS*		stuExtraStreamVideoCaps;
	INT								iCaptureStreamCapsCount;		// ���3��
	STU_CFG_VIDEOCONFIG_CAPS*		stuCaptureStreamCaps;
}STU_CFG_CONFIG_CAPS;

//���������������
struct STU_CFG_ENCODECAPS_PARAM
{
	STU_CFG_CONFIG_CAPS			stuCfgConfigCaps;
	STU_CFG_ENCODE_CAPS			stuCfgEncodeCaps;
};

typedef struct
{
	BYTE								bCompressionType;//��������,ȡֵΪ EM_VIDEO_STREAM_CODE_TYPE
	BYTE								bCtrlType;//������������,ȡֵΪ EM_VIDEO_FORMA_CTRL_TYPE
	BYTE								bResolutionType;//�ֱ�������,ȡֵΪ EM_VIDEO_STREAM_RESOLUTION_TYPE
	UINT								uFPS;//֡��
	UINT								uBitRate;//���ʴ�С
	UINT								uGop;//i֡���
	UINT								uQuality;//ͼ������,ȡֵ[1-6]
	BYTE								bH264SVCTLayer;//h264��svc����,����h264����ʱ��Ч
	BYTE								bH264EncodeLevel;//h264���뼶��,������h264����,ȡֵΪö��  EM_H264_ENCODE_LEVEL

}STU_CFG_ENCODE_VIDEO_CONFIG_PARAM;

typedef struct
{
	BOOL											bEnable;//ʹ��
	STU_CFG_ENCODE_VIDEO_CONFIG_PARAM				stuEncodeVideoConfig;
}STU_CFG_ENCODE_CONFIG_PARAM;
//��������
typedef struct
{
	UINT								uMainStreamNums;//����������
	STU_CFG_ENCODE_CONFIG_PARAM*		stuMainStreamEncodeConfig;//���ⲿ�����ڴ�������ͷ�
	UINT								uExtraStreamNums;//����������
	STU_CFG_ENCODE_CONFIG_PARAM*		stuExtraStreamEncodeConfig;//���ⲿ�����ڴ�������ͷ�
	UINT								uCaptureStreamNums;//ץͼ��������
	STU_CFG_ENCODE_CONFIG_PARAM*		stuCaptureStreamEncodeConfig;//���ⲿ�����ڴ�������ͷ�
}STU_CFG_ENCODE_CONFIG;

//�����������
typedef struct
{
	INT									iChannelNo;		//ͨ����
	STU_CFG_ENCODE_CONFIG				stuEncodeConfig;//�����������

}STU_CFG_ENCODE_PARAM;

#define MAX_NETCARD_NUMS				4//�����������ֵ

//Ŀǰ��ʱֻ֧��ipv4��ַ
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
	BOOL								bDefaultNetCard; //�Ƿ���Ĭ������,Ĭ������ֻ��һ��
	BOOL								bDhcpEnable;	 //�Ƿ���dhcpʹ��
	char								cNetCardName[32];//������ "eth0","wlan0"
	STU_CFG_ADDRESS_CONFIG				stuCfgAddress;

}STU_CFG_NETCARD_INFO;

//��������
typedef struct
{
	UINT								uNetCardNum;//��ʵ����������
	STU_CFG_NETCARD_INFO				stuNetCardinfo[MAX_NETCARD_NUMS];
			
}STU_CFG_NETCARD_CONFIG;

//�˿�����
typedef struct
{
	UINT								uHttpPort;
	UINT								uRtspPort;
	UINT								uServerPort;
}STU_CFG_PORT_CONFIG;

//wifiʹ������
typedef struct
{
	BOOL								bEnable;//wifiʹ��
}STU_CFG_WIFI_CONFIG;

typedef struct
{
	char									cSsidName[64];//ssid����
	char									cSsidPasswd[64];//ssid����
	UINT									uAuthMode;//��֤ģʽ
	UINT									uencType;//��������
	INT										irssiQuality;//�ź�ǿ��,��λ��dBM
	UINT									uConnectedStatus;//����״̬,0��δ����;1������

}STU_CFG_WIFI_INFO;

//wifi��������
typedef struct  
{
	UINT								uOperType;//0:ɨ��;1������ָ��wifi;2�ǶϿ�ָ��wifi
	UINT								uNums;	 //ָ��WiFi��Ŀ
	STU_CFG_WIFI_INFO*					stuInfos;//wifi��Ϣ,�ڴ����û������ڴ�������ͷ�

}STU_CFG_WIFI_OPER_CONFIG;

typedef struct  
{
	BOOL							bRecordEnable;			// ¼��ʹ�ܣ�����ͬʱ�� RecordChannels
	int								nRecordLatch;			// Ԥ¼ʱ�� [10s-300s]����λ����
	int								nRecordChannelNum;		// ʵ��¼��ͨ������
	// ¼��ͨ������
	int								nRecordChannels[MAX_RECORD_CHANNEL_NUM];
	
	BOOL							bAlarmOutEnable;		// �������ʹ��
	int								nAlarmOutLatch;			// ��������ֹͣ�������ʱʱ�� [1s,300s]����λ����
	int								nAlarmOutChannelNum;	// ʵ�ʱ������ͨ������
	// �������ͨ������
	int								nAlarmOutChannels[MAX_ALARM_OUT_CHANNEL_NUM];
	
	BOOL							bCaptureEnable;			// ץͼʹ��
	int								nCapturePreRecordTime;	// ͼƬ����¼���Ԥ¼ʱ�䣬���ܴ���ͨ�õ�Ԥ¼ʱ�䣬��λ����
	int								nCaptureChannelNum;		// ʵ��ץͼͨ����
	// ץͼͨ������
	int								nCaptureChannels[MAX_CAPTURE_CHANNEL_NUM];
	
	// ʱ����Ϣ
	STU_TIME_SECTION_SCHEDULE		stTimeScheduleArray[WEEK_SECTION][TIME_SECTION];

	// ������Ϣ
	BOOL							bHolidayEnable;
	STU_TIME_SECTION_SCHEDULE		stHolidaySchedule[TIME_SECTION];

}STU_EVENT_HANDLER;

typedef struct
{
	unsigned int							nGroupID;			// ������ ID
	unsigned int							nTopRank;			// �ϱ�ʶ��÷ֳ�����ֵ��������ǰ�ĵ׿���������
	STU_EVENT_HANDLER						stEventHandler;		// �����¼�
}STU_CFG_FACE_GROUP_RECOGNIZE_RULE;

typedef struct  
{
	int										nRuleCount;			// ����ʶ�����ʵ����Ŀ
	// ����ʶ�������Ϣ
	STU_CFG_FACE_GROUP_RECOGNIZE_RULE		stRuleArray[MAX_FACE_GROUP_NUM];
}STU_CFG_FACE_GROUP_RECOGNIZE_RULES;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// �ļ���Ϣ
typedef struct
{
	// ͨ����
	int							channel;
	// �ļ���
	char						filename[240];
	// �ļ���С
	int							size;
	// ��ʼʱ��
	STU_TIME					starttime;
	// ����ʱ��
	STU_TIME					endtime;
	// ץ��ʱ��
	STU_TIME					snaptime;
	// �ļ�����
	EM_ST_FILE_TYPE				filetype;
	// ��Ƶ��������
	EM_VIDEO_STREAM_TYPE		emVStreamType;
	// �¼���Ϣ��Json��ʽ����
	char*						pEvents;
	// Ԥ��λ
	BYTE						reserved[64];
}STU_T_FILE, *P_STU_T_FILE;

/**********************************************************************************
������		fPlaybackDataCallBack
������		[in] lPlaybackHandle��		�طž��
			[in] dwDataType:		    �̶�Ϊ 0���ݲ����ã�
			[in] pBuffer:				�ط����ݻ���
			[in] dwBufSize:				�ط����ݴ�С
			[in] dwUser:				�û�����
����ֵ��		/
˵����		�ط����ݻص�����ԭ��
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
    int                        nChannels[COUNT(64)];		// Ԥ��ͨ����
    int                        nChannelNum;                 // Ԥ��ͨ���� 
    int                        nType;                       // �ط��ļ����ͣ�0����ͨ¼��1������¼��2���ƶ���⣻3������¼��4��ͼƬ
    STU_TIME                   stStartTime;                 // �طſ�ʼʱ��
    STU_TIME                   stEndTime;                   // �طŽ���ʱ��
    int                        nFPS;                        // ֡��,1~25
    int                        nBitRate;                    // ����ֵ,192~1024
    char                       szResolution[COUNT(64)];		// �ֱ���  
    int                        nWaitTime;                   // ��ʱ�ȴ�ʱ�� 
    HWND                       hWnd;                        // ��Ƶ���Ŵ��ھ��
    fPlaybackDataCallBack	   fDownLoadDataCallBack;       // ��Ƶ���ݻص�
    LDWORD                     dwDataUser;					// �û�����
}STU_MULTI_PLAYBACK_PARAM_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	// �豸�������Ľ���
	int nProgress;
	// �豸״̬����
	char szStatus[64];
}STU_UPGRADE_PROGRESS_INFO, *P_STU_UPGRADE_PROGRESS_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�û�������ض���

// Ȩ����Ϣ
typedef struct
{
    DWORD               dwID;
    char                name[64];
    char                memo[64];
} STU_AUTHORITY_INFO;

// �û���Ϣ
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

// �û�����Ϣ
typedef struct
{
    DWORD               dwID;
    char                name[64];
    DWORD               dwRightNum;
    DWORD               rights[128];
    char                memo[64];
} STU_USER_GROUP_INFO;

// �û���Ϣ��
typedef struct
{
    DWORD					dwRightNum;						// Ȩ����Ϣ
    STU_AUTHORITY_INFO		rightList[128];
    DWORD					dwGroupNum;						// �û�����Ϣ
    STU_USER_GROUP_INFO		groupList[32];
    DWORD					dwUserNum;						// �û���Ϣ
    STU_USER_INFO			userList[256];
    DWORD					dwSpecial;						// �û���������
	BYTE					reserved[256];					
} STU_USER_MANAGE_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    DWORD               dwSize;
    LLONG               lPlayBackHandle;        // �طž��, Net_MultiPlayBack �ӿڷ���ֵ
    int                 nChannels[64];			// Ԥ��ͨ����
    int                 nChannelNum;            // Ԥ��ͨ���� 
}STU_CTRL_MULTI_PLAYBACK_CHANNEL_INFO;

typedef struct
{
    DWORD           dwSize;                          
    char            szDevSerial[64];				// ���к�
    char            szToken[MAX_PATH];              // ����
}STU_CB_AUTO_REGISTER_INFO;

// ��������ע����ؽṹ��
typedef struct
{
    DWORD               dwSize;   
    char                szDstIp[64];				// ������IP
    int                 nDstPort;					// �������˿ں� 
    DWORD               dwConnectType;				// �������ͣ�0 ������
    char                szToken[MAX_PATH];			// �豸ͨ��ΨһID����
}STU_CLOUD_SERVICE_CONNECT_PARAM;

typedef struct
{
    DWORD               dwSize;  
    DWORD               dwConnectState;				// ��ǰ����״̬��1�ɹ���0ʧ��
    char                szMessage[128];				// ����״̬��Ϣ
}STU_CLOUD_SERVICE_CONNECT_RESULT;

// �豸��Ϣ
typedef struct
{
    BYTE                sSerialNumber[64];			// ���к�
    BYTE                byAlarmInPortNum;			// �����������
    BYTE                byAlarmOutPortNum;			// �����������
    BYTE                byDiskNum;					// Ӳ�̸���
    BYTE                byType;						// �豸����
	int                 nChanNum;					// ͨ������
    int					nLimitLoginTime;			// ���߳�ʱʱ�䣬Ϊ0��ʾ�����Ƶ�½����0��ʾ���Ƶķ�����
    int					nLeftLogTimes;				// ʣ���½������0��ʾ�˲�����Ч
    char                reserved[32];				// ����
} STU_DEVICE_INFO, *P_STU_DEVICE_INFO;

// �޸��豸���÷�����Ϣ
typedef struct
{
    int					nType;						// ����
    int					nResultCode;                // �����룻0���ɹ���1��ʧ�ܣ�2�����ݲ��Ϸ���3����ʱ�޷����ã�4��û��Ȩ��
    int					nRebootFlag;                // ������־��0������Ҫ������1����Ҫ��������Ч
    BYTE				reserved[16];				// ����    
} STU_DEVICE_SET_RESULT;

// ������ӻ�طŵĴ��󷵻���Ϣ
typedef struct
{
    DWORD               dwResultCode;               // ���󷵻���
    LLONG               lPlayHandle;                // ��Ӧ���ֵ
    BYTE                reserved[64];				// ����λ                         
}STU_DEVICE_PLAY_RESULT;

// ���������Խ��Ĵ��󷵻���Ϣ
typedef struct
{
    DWORD               dwResultCode;               // ���󷵻���
    LLONG               lTalkHandle;                // ��Ӧ���ֵ
    BYTE                reserved[64];				// ����λ                         
}STU_DEVICE_TALK_RESULT;

// ���ڻ�������
typedef struct
{
	int					nType;
	char				szName[32];
    int					nDataBit;					// ����λ��0��5��1��6��2��7��3��8
    int					nStopBit;					// ֹͣλ��0��1λ��1��1.5λ��2��2λ
    int					nParity;					// У��λ��0����У�飬1����У�飻2��żУ��; 3:��־У��; 4:��У��
    int					nBaudRate;					// ������
	BYTE				reserved[32];
} STU_SERIAL_PORT_ATTRIBUTE;

// ����������
typedef struct  
{
	int					nNetworkType;                           // ��������, 0-LAN, 1-WAN
    int                 nLoginTimeout;							// ����ʱ�ĵȴ���ʱʱ��(ms)��Ĭ�� 5000 ms
    int                 nConnectTimeout;						// ���ӵȴ���ʱʱ��(ms)��Ĭ�� 2000 ms
    int                 nConnectTryNum;                         // ���ӳ��Դ�����Ĭ��1��
    int                 nSubConnectTimespan;					// ������֮��ĵȴ�ʱ��(ms)��Ĭ�� 10 ms
    int                 nGetDevInfoTimeout;						// ��ȡ�豸��Ϣ��ʱʱ��(ms)��Ĭ�� 2000 ms  
    int                 nGetSubConnInfoTimeout;					// ��ȡ��������Ϣ��ʱʱ��(ms)��Ϊ 0 Ĭ�� 1000 ms
    int                 nSearchRecordTimeout;					// ��ʱ���ѯ¼���ļ��ĳ�ʱʱ��(ms),Ϊ0Ĭ��Ϊ 3000 ms
    int                 nDetectSubDisconnTimespan;				// ��������Ӷ��ߵȴ�ʱ��(ms)��Ϊ0Ĭ��Ϊ 60 * 1000 ms
    int                 nConnectBufSize;                        // ÿ�����ӽ������ݻ����С(Byte)��Ϊ 0 Ĭ�� 1 * 1024 * 1024
	int                 nPicBufSize;                            // ʵʱͼƬ���ջ����С(Byte)��Ϊ 0 Ĭ��Ϊ 2 * 1024 * 1024	
    int					nPlaybackBufSize;						// �ط����ݽ��ջ����С(MB)��Ϊ 0 Ĭ��Ϊ 2M
    BYTE                reserved[128];							// ����λ
} STU_NET_PARAM, *P_STU_NET_PARAM;

///////////////////////////////////////////////////////////////////////////////////////////

typedef struct 
{
	BOOL				valid;									// �Ƿ���Ч		
	char				szName[32];								// ��������
	char				szMac[40];								// ��������Mac��ַ
	BYTE				reserved1[64];							// ����λ
	char				IPv4_Address[16];						// IPv4 ��ַ
	char				IPv4_SubnetMask[16];					// IPv4 ��������
	char				IPv4_DefaultGateway[16];				// IPv4 Ĭ������
	BOOL				IPv4_DhcpEnable;						// IPv4 DHCP ʹ��λ
	char				IPv6_Address[64];						// IPv6 ��ַ
	char				IPv6_SubnetMask[64];					// IPv6 ��������
	char				IPv6_DefaultGateway[64];				// IPv6 Ĭ������
	BOOL				IPv6_DhcpEnable;						// IPv6 DHCP ʹ��λ
	BYTE				reserved2[128];							// ����λ
}STU_SEARCH_NETCARD, *P_STU_SEARCH_NETCARD;

#define MAX_SEARCH_NETCARD_NUM	8

// ��Ӧ Net_StartSearchDevices�ӿ�
typedef struct
{
	int					nProtocolType;							// ����Э������  
																// 0 - ��һ���� 1 - �ڶ���
	BOOL				bActivated;								// �Ƿ��Ѽ���
	char				szDeviceClass[64];						// �豸���
	char				szDeviceType[64];						// �豸�ͺ�
	char				szSerialNumber[64];						// �豸���к�
	char				szSoftVersion[32];						// �����汾��
	char				szVendorName[64];						// ��������
	char				szMac[40];								// ��ǰ���� MAC
	int					nCurNetCardIndex;						// ��ǰ����������
	int					nDtsPort;								// DTS �˿�
	int					nHttpPort;								// HTTP �˿�
	char				szDefaultNetCard[16];					// Ĭ������
	STU_SEARCH_NETCARD	stuNetCardArr[MAX_SEARCH_NETCARD_NUM];	// ��������
	BYTE				reserved[256];							// ����λ
}STU_DEVICE_SEARCH_INFO, *P_STU_DEVICE_SEARCH_INFO;

typedef struct
{
    DWORD               dwSize;           
    int                 nIpNum;          // ��ǰ������IP����
    char                szIP[256][64];	 // �����������IP��Ϣ
}STU_DEVICE_IP_SEARCH_INFO, *P_STU_DEVICE_IP_SEARCH_INFO;

typedef struct
{
	DWORD				dwSize;
	// �Ƿ���� MAC ��������
	BOOL				bMac;
	char				szMac[40];
	// �Ƿ���� IPv4 ��������
	BOOL			    bIPv4;
	char				szStartIPv4[16];
	char				szEndIPv4[16];
	char				reserved1[64];
	// �Ƿ���� IPv6 ��������
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

// UDP����/�鲥��ȡ��Կ�������
typedef struct
{
	// �ṹ���С
	DWORD				dwSize;
	// mac ��ַʮ�������ַ���
	char				szMac[40];
	// ��������
	BYTE				reserved[128];
}STU_RSA_PUBLICKEY_IN_PARAM, *P_STU_RSA_PUBLICKEY_IN_PARAM;

// UDP����/�鲥��ȡ��Կ�������
typedef struct  
{
	// �ṹ���С
	DWORD				dwSize;
	// mac ��ַʮ�������ַ���
	char				szMac[40];
	// RSA modules ʮ�������ַ���
	char				szModules[1024];
	// RSA exponent ʮ�������ַ���
	char				szExponent[64];
	// ��������
	BYTE				reserved[256];
}STU_RSA_PUBLICKEY_OUT_PARAM, *P_STU_RSA_PUBLICKEY_OUT_PARAM;

typedef struct  
{
	// һ��ֻ�޸�ָ���������������
	char				szEthname[64];							// ��������
	char				szMac[40];								// ��������Mac��ַ
	char				szUser[64];								// �û���
	char				szPassword[64];							// �û�����
	BYTE				reserved1[64];							// ����λ1
	unsigned short		nDtsPort;								// ����˿�
	unsigned short		nHttpPort;								// HTTP �˿�
	unsigned short		nHttpsPort;								// HTTPS �˿�
	unsigned short		nRtspPort;								// RTSP �˿�
	BYTE				reserved2[64];							// ����λ2
	char				IPv4_Address[16];						// IPv4 ��ַ
	char				IPv4_SubnetMask[16];					// IPv4 ��������
	char				IPv4_DefaultGateway[16];				// IPv4 Ĭ������
	BOOL				IPv4_DhcpEnable;						// IPv4 DHCP ʹ��λ
	char				IPv6_Address[64];						// IPv6 ��ַ
	char				IPv6_SubnetMask[64];					// IPv6 ��������
	char				IPv6_DefaultGateway[64];				// IPv6 Ĭ������
	BOOL				IPv6_DhcpEnable;						// IPv6 DHCP ʹ��λ
	BYTE				reserved3[128];							// ����λ3
}STU_DEVICE_NETCFG_MODIFY_INFO, *P_STU_DEVICE_NETCFG_MODIFY_INFO;

///////////////////////////////////////////////////////////////////////////////////////////

// DDNS������Ϣ
typedef struct
{
    char                szServerType[32];		// ����������
    char                szServerIp[256];		// ������ip��������
    DWORD               dwServerPort;			// �������˿�
    char                szDomainName[256];		// �������� www.edu.org
    char                szUserName[64];			// �û���
    char                szUserPswd[64];          // ����
    BYTE                reserved[224];			// ����λ
}STU_DDNS_DOMAIN_INFO;

// ����ע���������
typedef struct  
{
    char                szServerIp[64];             // ע�������IP
    int                 nServerPort;                // �˿ں�
    BYTE                reserved[3];				// ����
    BYTE                bServerIpExEn;              // ע�������IP��չʹ��,0-��ʾ��Ч, 1-��ʾ��Ч
    char                szServerIpEx[60];           // ע�������IP��չ��֧��ipv4,ipv6,���������͵�IP
} STU_SERVER_INFO;

typedef struct  
{
    DWORD               dwSize;
    BYTE                bServerNum;                 // ֧�ֵ����ip��
    STU_SERVER_INFO		lstServer[12];
    BYTE                bEnable;                    // ʹ��
    char                szDeviceID[32];             // �豸id
    char                reserved[98];
} STU_REGISTER_SERVER_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// IP��Ϣ
typedef struct 
{
    DWORD               dwIPNum;					// IP����
    char                szIP[256][64];				// IP
    char                reserved[32];				// ����
} STU_IP_FILTER_INFO;

// IP�������ýṹ��
typedef struct
{
    DWORD               dwSize;
    DWORD               dwEnable;					// ʹ��
    DWORD               dwType;                     // ��ǰ�������ͣ�0�������� 1��������
    STU_IP_FILTER_INFO	BannedIP;					// ������
    STU_IP_FILTER_INFO	TrustIP;                    // ������
    char                byReserve[256];             // ����
} STU_IP_FILTER_CFG;

// MAC��Ϣ
typedef struct 
{
    DWORD					dwSize; 
    DWORD					dwMacNum;
    char					szMac[512][40];
} STU_MAC_FILTER_INFO;

// MAC�������ýṹ��
typedef struct
{
    DWORD					dwSize;
    DWORD					dwEnable;                 // ʹ��
    DWORD					dwType;                   // ��ǰ�������ͣ�0�������� 1��������
    STU_MAC_FILTER_INFO		stuBannedMac;             // ������Mac
    STU_MAC_FILTER_INFO		stuTrustMac;              // ������Mac
} STU_MAC_FILTER_CFG;

// MAC��IP������Ϣ
typedef struct
{
    DWORD       dwSize;
    char        szMac[40];
    char        szIp[64];
}STU_MAC_IP_INFO;

// MAC,IP�������ýṹ��
typedef struct
{
    DWORD					dwSize;							// ʹ��ʱ���ó�ʼ��Ϊ���ṹ���С
    DWORD					dwEnable;						// ʹ��
    DWORD					dwType;							// ��ǰ�������ͣ�0�������� 1��������
    DWORD					dwBannedMacIpNum;				// ������MAC,IP����(MAC,IPһһ��Ӧ)
    STU_MAC_IP_INFO			stuBannedMacIp[512];			// ������Mac,IP
    DWORD					dwTrustMacIpNum;				// ������MAC,IP����(MAC,IPһһ��Ӧ)
    STU_MAC_IP_INFO			stuTrustMacIp[512];				// ������Mac,IP
} STU_MAC_IP_FILTER_CFG;

// IP�޸�����
typedef struct
{
    int             nStructSize;
    char            szRemoteIP[64];			// ǰ���豸IP
    char            szSubmask[64];			// ��������
    char            szGateway[64];			// ����
    char            szMac[40];				// MAC��ַ
    char            szDeviceType[32];		// �豸����
}STU_IP_MODIFY_PARAM;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**********************************************************************************
������		fMultiFileDownLoadPosCallBack
������		[in] lDownLoadHandle��			�ļ����ؾ��	
			[in] dwFileID:					�����ļ������
			[in] dwFileTotalSize:			��ǰ�ļ��������ݴ�С
			[in] dwDownLoadSize:			��ǰ�ļ������ص����ݴ�С
			[in] nError:					0 - �޴���
											-1 - ����������
											-2 - �����л�����
											-3 - ���ִ����
											-255 - �����ڴ����
			[in] dwUser:					�û�����
			[in] pReserved					Ԥ������
����ֵ��		/
˵����		���ļ����ؽ��Ȼص�����ԭ��
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
    DWORD               dwFileID;							// �ļ�ID
    int                 nFileSize;							// ��ѯ�����ļ���С
    char                szSourceFilePath[MAX_PATH];			// ��ѯ�����ļ�·��
    char                szSavedFileName[MAX_PATH];			// �ļ�����·��
}STU_FILE_DOWNLOAD_PARAM;

typedef struct
{
	DWORD							dwSize;
	int								nFileCount;				// �������ļ���
    STU_FILE_DOWNLOAD_PARAM*		pFileInfos;				// �������ļ���Ϣ
    fMultiFileDownLoadPosCallBack	cbPosCallBack;			// ���Ȼص�����
    LDWORD							dwUserData;				// �û�����
}STU_IN_MULTI_FILE_DOWNLOAD_PARAM;

typedef struct
{
    DWORD               dwSize;
    LLONG               lDownLoadHandle;					// ���ؾ��
}STU_OUT_MULTI_FILE_DOWNLOAD_PARAM;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    DWORD						dwSize;
    char						szFilePath[MAX_PATH];		// �ļ�����·��
}STU_LOCAL_FILE_INFO;

typedef struct
{
    DWORD               dwSize;
    char                szIP[MAX_PATH];                     // Զ���豸IP
    unsigned int        nPort;                              // Զ���豸�˿�
    char                szName[64];							// ��½Զ���豸�û���
    char                szPassword[64];						// ��½Զ���豸����
    BYTE                byProtocolType;                     // Զ���豸Э������
    BYTE                reserved[3];						// ����λ
    char                szFilePath[MAX_PATH];               // �ļ�����·��
    int                 nStartCluster;                      // ��ʼ�غ�
    int                 nDiskNo;							// �̺�
}STU_REMOTE_FILE_INFO;

// �ļ�/Ŀ¼��Ϣ
typedef struct 
{
	DWORD               dwSize;
	BOOL                bDirectory;                     // �Ƿ��ļ���
	char                szPath[MAX_PATH];               // ·��
	STU_TIME            stuCreateTime;                  // ����ʱ��
    STU_TIME            stuModifyTime;                  // �޸�ʱ��
    INT64               nFileSize;                      // �ļ���С
    char                szFileType[64];					// �ļ�����
} STU_COMMON_FILE_INFO;

// �ļ�λ����Ϣ
typedef struct
{
    DWORD					dwSize;
    BOOL					bFileType;						// �����������ļ�/Զ���豸�ļ�
    STU_LOCAL_FILE_INFO		stuLocalFile;					// �����ļ���Ϣ
    STU_REMOTE_FILE_INFO	stuRemoteFile;					// Զ���ļ���Ϣ
}STU_FILE_LOCATION_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ����ע���������Ϣ
typedef struct 
{
    LONG            lConnectionID;                      // ����ID
    char            szServerIp[64];						// ����ע���������IP
    int             nPort;                              // ����ע��������˿�0- 65535
    int             nState;                             // ��������״̬��0��ע��ʧ�ܣ�1-ע��ɹ�; 2-����ʧ��
    char            reserved[32];
} STU_AUTO_REGISTER_INFO;

typedef struct 
{
    DWORD						dwSize;
    int							nRegisterSeverCount;				// ����ע�����������
    STU_AUTO_REGISTER_INFO		stuDevRegisterSeverInfo[128];		// ������ע���������Ϣ
    char						reserved[256];
} STU_SERVER_AUTO_REGISTER_INFO, *P_STU_SERVER_AUTO_REGISTER_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ��ͨ������Ƶ����
typedef struct
{
    int							nChannelID;			// ͨ����
    EM_REALPLAY_STREAM_TYPE     realplayType;		// ��Ƶ����
    char						reserve[32];
}STU_IN_MULTIPLAY_PARAM;

// ��ͨ������Ƶ���
typedef struct
{
    int							nChannelID;			// ͨ����
    LLONG						lRealHandle;		// ʵʱ���Ӿ��
    char						reserved[32];
}STU_OUT_MULTIPLAY_PARAM;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    DWORD               dwSize;
    const char*         pszPath;                // �ļ���
    BOOL                bDirectory;             // �Ƿ��ļ���
} STU_IN_CREATE_REMOTE_FILE_PARAM;

typedef struct 
{
    DWORD               dwSize;
} STU_OUT_CREATE_REMOTE_FILE_PARAM;

typedef struct
{
    DWORD               dwSize;
    const char**        pszPath;                // �ļ�·������ָ��
    int                 nFileCount;             // �ļ�·������
} STU_IN_REMOVE_REMOTE_FILES_PARAM;

typedef struct 
{
    DWORD               dwSize;
} STU_OUT_REMOVE_REMOTE_FILES_PARAM;

typedef struct
{
    DWORD               dwSize;
    const char*         pszOldPath;             // ���ļ���
    const char*         pszNewPath;             // ���ļ���
} STU_IN_RENAME_REMOTE_FILE_PARAM;

typedef struct 
{
    DWORD               dwSize;
} STU_OUT_RENAME_REMOTE_FILE_PARAM;

typedef struct
{
    DWORD               dwSize;
    const char*         pszPath;                        // ·��
    BOOL                bFileNameOnly;                  // ֻ��ȡ�ļ�����
} STU_IN_LIST_REMOTE_FILE_PARAM;

typedef struct 
{
    DWORD                   dwSize;
    STU_COMMON_FILE_INFO*   pstuFiles;					// �ļ���Ϣ����, �û������ڴ�
    int                     nMaxFileCount;              // �ļ���Ϣ�����С
    int                     nRetFileCount;              // ���ص��ļ�����
} STU_OUT_LIST_REMOTE_FILE_PARAM;

typedef struct
{
    DWORD               dwSize;
    char*				pszFileSrc;                     // Դ�ļ�·��
    char*				pszFileDst;                     // Ŀ���ļ�·��
	char*				pszFolderDst;					// Ŀ���ļ���·��
    unsigned int        nPacketLen;                     // �ļ��ְ���С(�ֽ�)
} STU_IN_UPLOAD_REMOTE_FILE_PARAM;

typedef struct
{
    DWORD               dwSize;
} STU_OUT_UPLOAD_REMOTE_FILE_PARAM;

typedef struct
{
    DWORD               dwSize;
    const char*         pszFileName;                    // ��Ҫ���ص��ļ���
    const char*         pszFileDst;                     // ����ļ�·��
} STU_IN_DOWNLOAD_REMOTE_FILE_PARAM;

typedef struct
{
    DWORD               dwSize;
} STU_OUT_DOWNLOAD_REMOTE_FILE_PARAM;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    DWORD                   dwSize;
    const char*             pszFilePath;            // �ļ�·��
    DWORD                   dwOutput;               // ���;��
} STU_IN_PLAY_AUDIO_FILE_INFO;

typedef struct
{
    DWORD                   dwSize;
} STU_OUT_PLAY_AUDIO_FILE_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    DWORD					dwSize;
    unsigned char*			pInBinBuf;                      // �������������ݻ���
    DWORD					dwInBinBufSize;                 // �������������ݳ���
} STU_BIN_DATA;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����״̬
typedef struct
{
    DWORD						dwSize;
    int							nStatus;					// ����״̬��0-������1-���� 
    DWORD						dwTotalSize;				// �������������ֽ�Ϊ��λ
    DWORD						dwRemainSize;				// ʣ���������ֽ�Ϊ��λ
}STU_HDD_PARTITION_STATUS;

// Ӳ��״̬
typedef struct
{
    DWORD						dwSize; 
    int							nState;						// Ӳ��״̬��0-������1-����   
    DWORD						dwTotalSize;				// Ӳ�����������ֽ�Ϊ��λ
	int							nPartitionNum;              // ������
    STU_HDD_PARTITION_STATUS	stuPartitions[32];			// ����״̬  
}STU_HDD_STATUS;

//////////////////////////////////////////////////////////////////////////////////////////

// �첽ע���豸�ص�����ԭ�Σ��ݲ����ã�
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
������		fLoadPosCallBack
������		[in] lHandle��				�ļ����ؾ��
			[in] dwTotalSize:		    �ļ����ܴ�С
			[in] dwDownLoadSize:		�����ص��ļ���С
			[in] dwUser:				�û�����
����ֵ��		/
˵����		�ط�/���ؽ��Ȼص�����ԭ��
**********************************************************************************/
typedef void (CALLBACK *fLoadPosCallBack)(
	LLONG lHandle, 
	DWORD dwTotalSize, 
	DWORD dwDownLoadSize,
	LDWORD dwUser);

// ���ļ��ط��������
typedef struct 
{
	DWORD                   dwSize;
	STU_T_FILE*				lpRecordFile;                   // ¼���ļ���Ϣ
	HWND                    hWnd;                           // ���ھ��
	fLoadPosCallBack		cbDownLoadPos;					// �طŽ��Ȼص�
	LDWORD                  dwPosUser;                      // ���Ȼص��û�����
	fPlaybackDataCallBack	fDownLoadDataCallBack;          // �ط����ݻص�
	LDWORD                  dwDataUser;                     // ���ݻص��û�����
	char                    szDstIP[64];					// �豸IP
	char					reserved[64];					// ����λ
}STU_IN_PLAYBACK_BYFILE_PROXY_PARAM;

// ���ļ��ط��������-����ʹ��
typedef struct 
{
	DWORD                   dwSize;
}STU_OUT_PLAYBACK_BYFILE_PROXY_PARAM;

// ��ʱ��ط��������-����ʹ��
typedef struct 
{
	DWORD                   dwSize;
	int                     nChannelID;                     // ͨ����
	P_STU_TIME              lpStartTime;                    // ��ʼʱ��
	P_STU_TIME              lpStopTime;                     // ����ʱ��
	HWND                    hWnd;                           // ���ھ��
	fLoadPosCallBack		cbDownLoadPos;                  // �طŽ��Ȼص�
	LDWORD                  dwPosUser;                      // ���Ȼص��û�����
	fPlaybackDataCallBack	fDownLoadDataCallBack;          // �ط����ݻص�
	LDWORD                  dwDataUser;                     // ���ݻص��û�����
	char                    szDstIP[64];					// �豸IP
	char					reserved[64];					// ����λ
}STU_IN_PLAYBACK_BYTIME_PROXY_PARAM;

// ��ʱ��ط��������-����ʹ��
typedef struct 
{
	DWORD                   dwSize;
}STU_OUT_PLAYBACK_BYTIME_PROXY_PARAM;

//////////////////////////////////////////////////////////////////////////////////////////

// ������Դ
typedef struct
{
	int						nIPChanneIn;					// IPͨ�������ٶ�, ��λ: kbps
	int						nNetRemain;						// �������ʣ������, ��λ: kbps
	int						nNetCapability;					// �������������, ��λ: kbps
	int						nRemotePreview;					// Զ��Ԥ������, ��λ: kbps
	int						nRmtPlayDownload;				// Զ�̻طż���������, ��λ: kbps
	int						nRemoteSendRemain;				// Զ�̷���ʣ������, ��λ: kbps
	int						nRemoteSendCapability;			// Զ�̷���������, ��λ: kbps
	BYTE                    reserved[32];					// ����λ
} STU_NET_RESOURCE_STATUS;

// �豸������Ϣ
typedef struct
{
	char                     szVendor[32];			// ��������
	char                     szDviceType[32];		// �豸�ͺ�
	char                     szVersion[32];			// �豸�汾��Ϣ
	char                     szSerialNo[64];		// �豸���
	BYTE                     reserved[96];			// ����λ
}STU_DEVICE_COMMON_INFO;

// �ص�����(�첽�ӿ�)
typedef struct 
{
	int                  nResultCode;            // �����룻0���ɹ�
	char                 *pBuf;                  // ��������, ���������û����ٵģ��ӽӿ��βδ���
	int                  nRetLen;                // ���ճ���
	LLONG                lOperateHandle;         // �������
	void*                userdata;               // ������Ӧ�û�����
	char                 reserved[16];
} STU_CALLBACK_DATA, *P_STU_CALLBACK_DATA;

///////////////////////////////////////////////////////////////////////////////////////////////
// ���ܷ���-������ͼ�����⴦����

#define NET_CMD_PICSTREAM_FACE			0x0001

/**********************************************************************************
������		fAnalyzeDataCallBack
������		[in] lRevcID��				���ܷ������	
			[in] lCommand:				�������ͣ�NET_CMD_PICSTREAM_xxx
										��ǰ�̶�Ϊ NET_CMD_PICSTREAM_FACE
			[in] pBuffer:				���ܷ����ϱ�������
			[in] nBufLen:				���ܷ����ϱ������ݴ�С
			[in] pUser:					�û�����
����ֵ��		int
˵����		���ܷ������ݻص�
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
	int					iFaceId;				// ��������ID	
	int					iDrop;					// ��ʱ����
	int					iFacelevel;				// ��ʱ����
	STU_RECT_L			tFaceRect;				// ͼƬ���ο� ��8192 * 8192 ����ϵ��
	int					iWidth;					// ͼƬ���ؿ���
	int					iHeight;				// ͼƬ���ظ߶�
	int					iFaceAttrCount;			// ��ʱ����
	int					iFaceAttrStructSize;	// ��ʱ����
	FaceAttributeCV1*	pstFaceAttr[256];		// ��ʱ����
	int					iDataLen;				// ͼƬ���ݴ�С
	char*				pcPicData;				// ͼƬ����
}FacePicDataCV1, *pFacePicDataCV1;

typedef struct tagFacePicStream
{
	int					nStructSize;			// FacePicStreamCV1�ṹ���С
	PicTimeCV1			tPicTime;				// ץͼʱ��
	int					nFullPicSize;			// PicDataCV1�ṹ���С
	PicDataCV1*			pstFullPicData;			// ����ͼ����
	//  һ�ű���ͼ��Ӧһ��/����������ͼ����ǰΪһ��
	int					nFaceCount;				// ͼƬ����
	int					nFacePicSize;			// FacePicDataCV1 �����ܴ�С
	FacePicDataCV1*		pstFaceData;			// ͼƬ����
}FacePicStreamCV1, *pFacePicStreamCV1;

///////////////////////////////////////////////////////////////////////////////////////////////
// ����ͼƬ�� & ����ͼƬ������ؽṹ��

/////////////////////////////////////////////
// ��������Ϣ
typedef struct  
{
	BOOL				bEnable;					// ʹ�ܱ�־λ
	unsigned int		nGroupID;					// ������ID
	char				szGroupName[128];			// ���������ƣ������׿�ʱָ���������󲻿ɸ���
	char				szAlias[128];				// ���������
	char				szGUID[64];					// ������ΨһID
	int					nFaceCount;					// �������ڿ�������(������)
	float				fSearchThreshold;			// ʶ��ȶ���ֵ [0.0-100.0]
	STU_TIME			stCreateTime;				// �����鴴��ʱ��
	unsigned int		nTopRank;					// �ϱ�ʶ��÷ֳ�����ֵ��������ǰ�ĵ׿���������
	BYTE				reserved[252];				// ��������
}STU_FACE_GROUP_INFO, *P_STU_FACE_GROUP_INFO;

// ������������Ϣ
typedef struct 
{
	// ������ʵ����Ŀ
	unsigned short			nFaceGroupNum;
	// �ֽڶ���
	BYTE					reserved[2];
	// ��������Ϣ
	STU_FACE_GROUP_INFO		stFaceGroupArr[MAX_FACE_GROUP_NUM];
}STU_FACE_GROUP_ARRAY_INFO, *P_STU_FACE_GROUP_ARRAY_INFO;

// �ɱ༭����������Ϣ
typedef struct  
{
	BOOL				bEnable;					// ʹ�ܱ�־λ���� 0 �� 1 ������
	float				fSearchThreshold;			// ʶ��ȶ���ֵ [0.0 - 100.0], -1 ������
	char				szAlias[128];				// ���������, Ϊ�����޸�
	char				szGUID[64];					// ȫ�� ID��Ϊ�����޸�
	unsigned int		nTopRank;					// �ϱ�ʶ��÷ֳ�����ֵ��������ǰ�ĵ׿��������� [1-5]
	BYTE				reserved[124];				// ��������
}STU_FACE_GROUP_EDIT_INFO, *P_STU_FACE_GROUP_EDIT_INFO;

// �����鴴���������
typedef struct  
{
	BOOL				bEnable;					// ʹ�ܱ�־λ
	float				fSearchThreshold;			// ʶ��ȶ���ֵ [0.0-100.0]
	char				szAlias[128];				// ��������������ܰ��������ַ���
	unsigned int		nTopRank;					// �ϱ�ʶ��÷ֳ�����ֵ��������ǰ�ĵ׿���������
	BYTE				reserved[124];				// ��������
}STU_FACE_GROUP_CREATE_IN_PARAM, *P_STU_FACE_GROUP_CREATE_IN_PARAM;

// �����鴴���������
typedef struct  
{
	DWORD					dwSize;					// �ṹ���С
	int						nError;					// �����룬0-�޴���
	STU_FACE_GROUP_INFO		stFaceGroupInfo;		// ��������Ϣ
	BYTE					reserved[64];			// ��������
}STU_FACE_GROUP_CREATE_OUT_PARAM, *P_STU_FACE_GROUP_CREATE_OUT_PARAM;

// ɾ���������������
typedef struct  
{
	unsigned int			nGroupID;				// ������ ID
	BOOL					bDelBindFace;			// �Ƿ�ͬ��ɾ���󶨵����������ͼƬ
	BYTE					reserved[16];			// ��������
}STU_FACE_GROUP_DELETE_IN_PARAM, *P_STU_FACE_GROUP_DELETE_IN_PARAM;

// ɾ���������������
typedef struct  
{
	DWORD					dwSize;					// �ṹ���С
	int						nError;					// �����룬 0 Ϊ�޴���
	BYTE					reserved[16];			// ��������
}STU_FACE_GROUP_DELETE_OUT_PARAM, *P_STU_FACE_GROUP_DELETE_OUT_PARAM;

// �༭�������������
typedef struct  
{	
	unsigned int				nGroupID;					// ������ ID�������ģ�
	STU_FACE_GROUP_EDIT_INFO	stFaceGroupEditInfo;		// ���޸ĵ���������Ϣ
	BYTE						reserved[64];				// ��������
}STU_FACE_GROUP_EDIT_IN_PARAM, *P_STU_FACE_GROUP_EDIT_IN_PARAM;

// �༭�������������
typedef struct  
{	
	DWORD					dwSize;							// �ṹ���С
	int						nError;							// �����룬0 Ϊ�޴���
	BYTE					reserved[16];					// ��������
}STU_FACE_GROUP_EDIT_OUT_PARAM, *P_STU_FACE_GROUP_EDIT_OUT_PARAM;

/////////////////////////////////////////////
// ����ͼ����
typedef struct  
{
	unsigned int			nPersonID;						// ��Ա ID
	char					szName[128];					// ����ͼ����
	EM_SEX_TYPE				emSexType;						// �Ա�
	STU_TIME				stBirthday;						// ����
	char					szCertificateType[64];			// ֤������
	char					szID[128];						// ֤�� ID
	BYTE					reserved1[32];					// ��������1
	char					szCountry[64];					// ����
	char					szProvince[64];					// ʡ��
	char					szCity[128];					// ���ڳ���
	BYTE					reserved2[1024];				// ��������2
}STU_PERSON_INFO, *P_STU_PERSON_INFO;

// �������������������
typedef struct  
{	
	unsigned int			nGroupID;						// ������ ID
	STU_PERSON_INFO			stPersonInfo;					// ��Ա��Ϣ
	int						nImageCount;					// ����ͼƬ����, ������ MAX_PERSON_FACE_NUM
	char					*lpszImageFiles;				// ����ͼƬ����·��������Ƕ��ţ��� "|" �ָ�·����
	BOOL					bNoCreate;						// �ܾ��������������ã������ã�
	BYTE					reserved[252];					// ��������
}STU_FACE_ADD_IN_PARAM, *P_STU_FACE_ADD_IN_PARAM;

// �������������������
typedef struct 
{
	DWORD					dwSize;							// �ṹ���С
	int						nError;							// �����룬0 - �޴���
	int						nFaceTokenCount;				// ��������ͼƬ�ɹ��󣬷��ص� facetoken ����
	// ��������ͼƬ�ɹ��󣬷��ص�����ͼƬ��Ӧ�� facetoken �ַ���
	// ����Ƕ��ţ��� "|" �ָ���˳��������ͼƬ��˳����ͬ
	char					szFaceTokens[68 * MAX_PERSON_FACE_NUM];
	BYTE					reserved[16];					// ��������
}STU_FACE_ADD_OUT_PARAM, *P_STU_FACE_ADD_OUT_PARAM;

// ������������Ϣ�����������
typedef struct  
{
	STU_PERSON_INFO			stPersonInfo;					// ������Ϣ
	BYTE					reserved[128];					// ��������
}STU_PERSON_INFO_UPDATE_IN_PARAM, *P_STU_PERSON_INFO_UPDATE_IN_PARAM;

// ������������Ϣ�����������
typedef struct 
{
	DWORD					dwSize;							// �ṹ���С
	int						nError;							// �����룬 0-�޴���
	BYTE					reserved[16];					// ��������
}STU_PERSON_INFO_UPDATE_OUT_PARAM, *P_STU_PERSON_INFO_UPDATE_OUT_PARAM;

// ��������ͼƬ�����������
typedef struct  
{
	unsigned int			nGroupID;						// ������ID
	unsigned int			nPersonID;						// ��ԱID
	char					szImageFile[MAX_PATH];			// ����ͼƬ·��
	BYTE					reserved[64];					// ��������
}STU_FACE_IMAGE_ADD_IN_PARAM, *P_STU_FACE_IMAGE_ADD_IN_PARAM;

// ��������ͼƬ�����������
typedef struct  
{
	DWORD					dwSize;							// �ṹ���С
	int						nError;							// ������ 0 - �޴���
	char					szFaceToken[64];				// �µ�������ʶ��
	BYTE					reserved[64];					// ��������
}STU_FACE_IMAGE_ADD_OUT_PARAM, *P_STU_FACE_IMAGE_ADD_OUT_PARAM;

// ɾ������ͼƬ�����������
typedef struct  
{
	char					szFaceToken[64];				// ������ʶ��
	BYTE					reserved[64];					// ��������
}STU_FACE_IMAGE_DELETE_IN_PARAM, *P_STU_FACE_IMAGE_DELETE_IN_PARAM;

// ɾ������ͼƬ�����������
typedef struct  
{
	DWORD					dwSize;							// �ṹ���С
	int						nError;							// �����룬0-�޴���
	BYTE					reserved[16];					// ��������
}STU_FACE_IMAGE_DELETE_OUT_PARAM, *P_STU_FACE_IMAGE_DELETE_OUT_PARAM;

// ��������ͼƬ�����������
typedef struct  
{
	char					szFaceToken[64];				// ������ʶ��
	char					szImageFile[MAX_PATH];			// ����µ�����ͼƬ·��
	BYTE					reserved[64];					// ��������
}STU_FACE_IMAGE_UPDATE_IN_PARAM, *P_STU_FACE_IMAGE_UPDATE_IN_PARAM;

// ��������ͼƬ�����������
typedef struct  
{
	DWORD					dwSize;							// �ṹ���С
	int						nError;							// �����룬0-�޴���
	char					szFaceToken[64];				// �µ�������ʶ��
	BYTE					reserved[64];					// ��������
}STU_FACE_IMAGE_UPDATE_OUT_PARAM, *P_STU_FACE_IMAGE_UPDATE_OUT_PARAM;

// ����ͼ�󶨵�����������������
typedef struct 
{
	unsigned int			nGroupID;						// ���������ID
	char					szFaceToken[64];				// ������ʶ��
	BYTE					reserved[64];					// ��������
}STU_FACE_BIND_GROUP_IN_PARAM, *P_STU_FACE_BIND_GROUP_IN_PARAM;

// ����ͼ�󶨵�����������������
typedef struct  
{
	DWORD					dwSize;							// �ṹ���С
	int						nError;							// ������ 0 - �޴���
	BYTE					reserved[16];					// ��������
}STU_FACE_BIND_GROUP_OUT_PARAM, *P_STU_FACE_BIND_GROUP_OUT_PARAM;

// ����ͼ��������������������
typedef struct  
{
	unsigned int			nGroupID;						// ������ID
	char					szFaceToken[64];				// ������ʶ��
	BYTE					reserved[64];					// ��������
}STU_FACE_UNBIND_GROUP_IN_PARAM, *P_STU_FACE_UNBIND_GROUP_IN_PARAM;

// ����ͼ��������������������
typedef struct  
{
	DWORD					dwSize;							// �ṹ���С
	DWORD					nError;							// �����룬0-�޴���
	BYTE					reserved[16];					// ��������
}STU_FACE_UNBIND_GROUP_OUT_PARAM, *P_STU_FACE_UNBIND_GROUP_OUT_PARAM;

/////////////////////////////////////////////
// ������ѯ

// ����ͼ����Ϣ
typedef struct  
{
	unsigned int			nGroupID;						// �󶨵�������ID
	unsigned int			nPersonID;						// ��ԱID
	char					szFaceToken[64];				// ������ʶ��
	int						nState;							// ����״̬��0-���ã�1-����
	STU_TIME				stTime;							// �������ʱ��	
	BYTE					reserved[256];					// ��������
}STU_FACE_IMAGE_INFO, *P_STU_FACE_IMAGE_INFO;

// ��Ա����ͼ����Ϣ
typedef struct  
{
	// ��Ա��Ϣ
	STU_PERSON_INFO			stPersonInfo;
	// ����ͼ��ʵ����Ŀ�������� MAX_PERSON_FACE_NUM
	int						nFaceImageCount;
	// ����ͼ����Ϣ����
	STU_FACE_IMAGE_INFO		stFaceImageInfoArr[MAX_PERSON_FACE_NUM];
}STU_PERSON_FACE_INFO, *P_STU_PERSON_FACE_INFO;

// ����������Ϣ��ѯʵ��
typedef struct  
{
	DWORD					dwResult;						// ������ѯʵ��
}STU_FACE_INFO_FIND_INSTANCE, *P_STU_FACE_INFO_FIND_INSTANCE;

// ������Ϣ��ѯ����
typedef struct  
{
	BOOL					bEnable;						// �Ƿ����ò�ѯ����, ������������ѯ����
	unsigned int			nPersonID;						// ��ԱID, -1 ��ʾ��Ч
	char					szName[128];					// ��Ա��, �ձ�ʾ��Ч
	EM_SEX_TYPE				emSexType;						// ��Ա�Ա�-1��UNKNOWN����ʾ��Ч
	STU_TIME				stMinBirthday;					// ��Ա���շ�Χ����, ���Ϊ 0 ʱ��Ч
	STU_TIME				stMaxBirthday;					// ��Ա���շ�Χ����, ���Ϊ 0 ʱ��Ч
	char					szCertificateType[64];			// ��Ա֤�����ͣ��ձ�ʾ��Ч
	char					szID[128];						// ��Ա֤�� ID���ձ�ʾ��Ч
	char					reserved1[32];					// ��������1
	char					szCountry[64];					// ���𣬿ձ�ʾ��Ч
	char					szProvince[64];					// ʡ�ݣ��ձ�ʾ��Ч
	char					szCity[128];					// ���У��ر�ʾ��Ч
	BYTE					reserved2[1024];				// ��������2
}STU_FACE_INFO_FIND_CONDITON, *P_STU_FACE_INFO_FIND_CONDITON;

// ��ѯ������Ϣ�������
typedef struct  
{
	unsigned int				nGroupID;					// ������ ID
	STU_FACE_INFO_FIND_CONDITON	stCondition;				// ������Ϣ��ѯ����
}STU_FACE_INFO_FIND_IN_PARAM, *P_STU_FACE_INFO_FIND_IN_PARAM;

// ��ѯ������Ϣ�������
typedef struct  
{
	DWORD						dwSize;						// �ṹ���С
	int							nError;						// �����룬0-�޴���
	BYTE						reserved[16];				// ��������
}STU_FACE_INFO_FIND_OUT_PARAM, *P_STU_FACE_INFO_FIND_OUT_PARAM;

// ��ȡ������Ϣ�����������
typedef struct  
{
	unsigned short				nOffset;					// ��ѯ���ƫ�ƣ�
	unsigned short				nCount;						// ϣ����ȡ�Ĳ�ѯ����, ������ MAX_ONCE_QUERY_PERSON_NUM
	BYTE						reserved[32];				// ��������
}STU_FACE_INFO_FIND_RESULT_IN_PARAM, *P_STU_FACE_INFO_FIND_RESULT_IN_PARAM;

// ���һ�ȡ������Ϣ�������
typedef struct  
{
	// �ṹ���С
	DWORD					dwSize;
	// �����룬0-�޴���
	int						nError;
	// ��Ա������Ϣ����ʵ�ʴ�С�������� MAX_ONCE_QUERY_PERSON_NUM
	int						nPersonFaceInfoArrSize;
	// ��Ա������Ϣ����
	STU_PERSON_FACE_INFO	stPersonFaceInfoArr[MAX_ONCE_QUERY_PERSON_NUM];
}STU_FACE_INFO_FIND_RESULT_OUT_PARAM, *P_STU_FACE_INFO_FIND_RESULT_OUT_PARAM;

// ���һ�ȡ����������ͼƬ�������
typedef struct  
{
	char					szFaceToken[64];				// ������ʶ��
	char					szImageFile[MAX_PATH];			// ����ͼƬ·��
	BYTE					reserved[64];					// ��������
}STU_FACE_IMAGE_GET_IN_PARAM, *P_STU_FACE_IMAGE_GET_IN_PARAM;

// ���һ�ȡ����������ͼƬ�������
typedef struct  
{
	DWORD					dwSize;							// �ṹ���С
	int						nError;							// ������ 0-�޴���
	int						nImageLength;					// ����ͼƬ��С
	char					szImageFile[MAX_PATH];			// ����ͼƬ����·��
	BYTE					reserved[64];					// ��������
}STU_FACE_IMAGE_GET_OUT_PARAM, *P_STU_FACE_IMAGE_GET_OUT_PARAM;

// ͨ��������ʶ���ȡ��Ա��Ϣ�������
typedef struct
{
	char					szFaceToken[64];				// ������ʶ��
	BYTE					reserved[64];					// ��������
}STU_PERSON_INFO_GET_BYTOKEN_IN_PARAM, *P_STU_PERSON_INFO_GET_BYTOKEN_IN_PARAM;

// ͨ��������ʶ���ȡ��Ա��Ϣ�������
typedef struct  
{
	DWORD					dwSize;							// �ṹ���С
	int						nError;							// ������ 0-�޴���
	STU_PERSON_INFO			stPersonInfo;					// ��Ա��Ϣ
}STU_PERSON_INFO_GET_BYTOKEN_OUT_PARAM, *P_STU_PERSON_INFO_GET_BYTOKEN_OUT_PARAM;

// ͨ����ԱID��ȡ��Ա��Ϣ�������
typedef struct  
{
	char					szCertificateType[64];			// ��Ա֤������
	char					szID[128];						// ��Ա֤����
	BYTE					reserved[16];					// �������� 
}STU_PERSON_INFO_GET_BYID_IN_PARAM, *P_STU_PERSON_INFO_GET_BYID_IN_PARAM;

// ͨ����ԱID��ȡ��Ա��Ϣ�������
typedef struct  
{
	DWORD					dwSize;							// �ṹ���С
	int						nError;							// ������ 0-�޴���
	STU_PERSON_INFO			stPersonInfo;					// ��Ա��Ϣ
}STU_PERSON_INFO_GET_BYID_OUT_PARAM, *P_STU_PERSON_INFO_GET_BYID_OUT_PARAM;

// ��ȡָ����ԱID������������Ϣ�������
typedef struct  
{
	unsigned int			nPersonID;						// ��ԱID
	BYTE					reserved[16];					// ��������
}STU_FACE_IMAGE_INFO_GET_IN_PARAM, *P_STU_FACE_IMAGE_INFO_GET_IN_PARAM;

// ��ȡָ����ԱID������������Ϣ�������
typedef struct
{
	// �ṹ���С
	DWORD					dwSize;
	// �����룬0-�޴���
	int						nError;
	// ����ͼ��ʵ����Ŀ
	int						nFaceImageCount;
	// ����ͼ����Ϣ����
	STU_FACE_IMAGE_INFO		stFaceImageInfoArr[MAX_PERSON_FACE_NUM];
}STU_FACE_IMAGE_INFO_GET_OUT_PARAM, *P_STU_FACE_IMAGE_INFO_GET_OUT_PARAM;

// ��������������������
typedef struct  
{
	char					szName[128];					// ��Ա���ƣ������������ֺ�׺��
	BYTE					reserved[64];					// ��������
}STU_PERSON_NAME_CHECK_IN_PARAM, *P_STU_PERSON_NAME_CHECK_IN_PARAM;

// ��������������������
typedef struct  
{
	DWORD					dwSize;							// �ṹ���С
	int						nError;							// �����룬0-�޴���
	int						nSuffix;						// 0 ��ʾ��������������ʾ�����׺
															// ��� WH,WH1,WH2, 1��2���ǽ����׺
}STU_PERSON_NAME_CHECK_OUT_PARAM, *P_STU_PERSON_NAME_CHECK_OUT_PARAM;

/////////////////////////////////////////////
// �����ȶ�

// �����ȶԼ�¼��ѯ����
typedef struct  
{
	unsigned int			nGroupID;						// ������ ID, 0 ��ʾ��Ч
	int						nRecNo;							// �����ȶ����ݿ������ţ� -1 ��ʾ��Ч
	short					nPass;							// ����ʶ��ͨ����־λ
															// -1 ��ʾ��ѯ����
															// 0 ��ʾ��ѯʶ��ͨ��������
															// 1 ��ʾ��ѯʶ��ͨ��������
	BYTE					reserved1[2];					// ��������1
	unsigned int			nObjectID;						// ���� ID, 0 ��ʾ��Ч
	STU_TIME				stMinTime;						// ��ѯʱ�䷶Χ���ޣ����Ϊ 0 ʱ��Ч
	STU_TIME				stMaxTime;						// ��ѯʱ�䷶Χ���ޣ����Ϊ 0 ʱ��Ч
    BYTE					reserved2[16];					// ��������2
}STU_FACE_REC_REC_FIND_CONDITION, *P_STU_FACE_REC_REC_FIND_CONDITION;

// �����ȶԼǹ���¼
typedef struct  
{
	unsigned int			nResultRecNo;					// �����ȶԽ����¼���				
	float					fSearchScore;					// �������ƶ� [0-100], ֵԽ�����ƶ�Խ��
	float					fSearchThreshold;				// �������ƶ���ֵ [0-100]
	float					fLivenessScore;					// ������÷� [0-100]
	float					fLivenessThreshold;				// ��������ֵ [0-100]
	char					szFaceToken[64];				// �ȶԳɹ��ĵ׿�����ͼƬ��ʶ�� 
	BYTE					reserved[128];					// ��������		
}STU_FACE_RECOGNIZE_RESULT, *P_STU_FACE_RECOGNIZE_RESULT;

// �����ȶԼ�¼��ѯ��Ϣ
typedef struct
{
	unsigned int					nRecNo;							// ʶ���¼���
	unsigned int					nGroupID;						// ������ ID
	short							nPass;							// �Ƿ�ʶ��ͨ�� 1-ͨ��; 0-��ͨ��
	BYTE							reserved1[2];					// ��������1
	char							szImagePath[MAX_PATH];			// �豸��ʶ��ͼƬ�洢·��
	STU_TIME						stTime;							// ʶ��ȶ�ʱ��
	BYTE							reserved2[64];					// ��������2
	int								nResultCount;					// �����ȶԽ����Ŀ
	STU_FACE_RECOGNIZE_RESULT		stResultArr[MAX_FACE_REC_RESULT_NUM];	// ����ʶ������Ϣ����
	BYTE							reserved3[128];					// ��������3
}STU_FACE_RECOGNIZE_RECORD_INFO, *P_STU_FACE_RECOGNIZE_RECORD_INFO;

// �����ȶԼ�¼��ѯʵ�������������
typedef struct  
{
	STU_FACE_REC_REC_FIND_CONDITION	stCondition;					// ��ѯ����
	BYTE							reserved[64];					// ��������
}STU_FACE_REC_REC_FIND_IN_PARAM, *P_STU_FACE_REC_REC_FIND_IN_PARAM;

// �����ȶԼ�¼��ѯʵ�������������
typedef struct  
{
	DWORD							dwSize;							// �ṹ���С
	int								nError;							// �����룬0-�޴���
	unsigned int					nFindHandle;					// ����ʶ���¼���Ҿ��
	BYTE							reserved[16];					// ��������
}STU_FACE_REC_REC_FIND_OUT_PARAM, *P_STU_FACE_REC_REC_FIND_OUT_PARAM;

// �����ȶԼ�¼���ҽ���������
typedef struct  
{
	unsigned short			nOffset;						// ��ѯ���ƫ��
	unsigned short			nCount;							// ������ѯ���Ľ������
															// ������ MAX_ONCE_QUERY_FACE_REC_REC_NUM
	BYTE					reserved[16];					// ��������
}STU_FACE_REC_REC_FIND_RESULT_IN_PARAM, *P_STU_FACE_REC_REC_FIND_RESULT_IN_PARAM;

// �����ȶԼ�¼���ҽ���������
typedef struct  
{
	// �ṹ���С
	DWORD							dwSize;
	// �����룬0-�޴���
	int								nError;
	// ʵ�ʲ�ѯ���ļ�¼����
	unsigned int					nRecordCount;
	// �����ȶԼ�¼��Ϣ����
	STU_FACE_RECOGNIZE_RECORD_INFO	stRecordInfoArr[MAX_ONCE_QUERY_FACE_REC_REC_NUM];
}STU_FACE_REC_REC_FIND_RESULT_OUT_PARAM, *P_STU_FACE_REC_REC_FIND_RESULT_OUT_PARAM;

//������Ϣ�ṹ��
typedef struct
{
	EM_ALARM_TYPE 	eAlarmType;//��������
	int				iChannelID;//�豸ͨ����
	char 			cAlarmTime[32];//��������ʱ��	

}ST_ALARM_INFO;

///////////////////////////////////////////////////////////////////////////////////////////////

/*****************************************************************************************
 *							netmanager library �ص�����									 *
 *****************************************************************************************/

/*******************************************************************************
������		fDisConnectCallBack
������		[in]lLoginID:		�����豸���
			[in]lpszIP:			�豸 IP ��ַ
			[in]nPort:			�豸����˿�
			[in]dwUser:			�û�����
����ֵ��		/
˵����		�������ӶϿ��ص�����ԭ��
********************************************************************************/
typedef void (CALLBACK *fDisConnectCallBack)(
	LLONG lLoginID, 
	char *lpszIP, 
	LONG nPort, 
	LDWORD dwUser);

/*******************************************************************************
������		fReConnectedCallBack
������		[in]lLoginID:		�����豸���
			[in]lpszIP:			�豸 IP ��ַ
			[in]nPort:			�豸����˿�
			[in]dwUser:			�û�����
����ֵ��		/
˵����		�������ӻָ��ص�����ԭ��
********************************************************************************/
typedef void (CALLBACK *fReConnectedCallBack)(
	LLONG lLoginID, 
	char *lpszIP, 
	LONG nPort, 
	LDWORD dwUser);

/*******************************************************************************
������		fSubDisConnectCallBack
������		[in]emInterfaceType:	����ӿ�����
			[in]bOnline:			�豸�Ƿ�����
			[in]lOperateHandle:		����ʱ�Ĳ������
			[in]lLoginID:			�豸��¼���
			[in]dwUser:				�û�����
����ֵ��		/
˵����		��̬�����ӶϿ��ص�����ԭ��
********************************************************************************/
typedef void (CALLBACK *fSubDisConnectCallBack)(
	EM_VIRTUAL_INTERFACE_TYPE emInterfaceType, 
	BOOL bOnline, 
	LLONG lOperateHandle,
	LLONG lLoginID,
	LDWORD dwUser);

/*******************************************************************************
������		fRealPlayDisConnectCallBack
������		[in]lOperateHandle:		�������
			[in]dwCodeType:			����������
			[in]param:				Ԥ��������������
			[in]dwUser:				�û�����
����ֵ��		/
˵����		��Ƶ���ӶϿ��ص�����ԭ��
********************************************************************************/
typedef void (CALLBACK *fRealPlayDisConnectCallBack)(
	LLONG lOperateHandle, 
	EM_CODE_RETURN_TYPE dwCodeType, 
	void* param, 
	LDWORD dwUser);

/*******************************************************************************
������		fRealPlayDataCallBack
������		[in]lRealHandle:		ʵʱ���ž��
			[in]dwDataType:			�������ͣ���ǰΪ 0
			[in]pBuffer:			ʵʱ����Buffer
			[in]dwBufSize:			ʵʱ����Buffer��С
			[in]dwUser:				�û�����
����ֵ��		/
˵����		ʵʱ�������ݻص�����ԭ��
********************************************************************************/
typedef void (CALLBACK *fRealPlayDataCallBack)(
	LLONG lRealHandle, 
	DWORD dwDataType, 
	BYTE *pBuffer, 
	DWORD dwBufSize,
	LDWORD dwUser);

/**********************************************************************************
������		fRealPlayDataCallBackEx
������		[in] lRealHandle��			ʵʱ���ž��	
			[in] dwDataType:			�������ͣ���ǰΪ 0
			[in] pBuffer:				ʵʱ����Buffer
			[in] dwBufSize:				ʵʱ����Buffer��С
			[in] param:					Ԥ����������ǰΪ 0
			[in] dwUser:				�û�����
����ֵ��		/
˵����		ʵʱ�������ݻص�����ԭ��
**********************************************************************************/
typedef void (CALLBACK *fRealPlayDataCallBackEx)(
	LLONG lRealHandle, 
	DWORD dwDataType, 
	BYTE *pBuffer, 
	DWORD dwBufSize, 
	LONG param, 
	LDWORD dwUser);

/**********************************************************************************
������		fTalkBackDataCallBack
������		[in] lRealHandle��			�����Խ����	
			[in] pBuffer:				�豸�˵���������Buffer
			[in] dwBufSize:				�豸�˵���������Buffer��С
			[in] dwUser:				�û�����
����ֵ��		/
˵����		�����Խ����ݻص�����ԭ��
**********************************************************************************/
typedef void (CALLBACK *fTalkBackDataCallBack)(
	LLONG lRealHandle,
	BYTE *pBuffer,
	DWORD dwBufSize,
	LDWORD dwUser);

/**********************************************************************************
������		fAlarmInfoCallBack
������		[in] lAlarmHandle				�������	
			[in] pBuffer:				������Ϣ ST_ALARM_INFO*����
			[in] dwBufSize:				������Ϣ�ṹ���С sizeof(ST_ALARM_INFO)
			[in] dwUser:				�û�����
����ֵ��		/
˵����		������Ϣ�ص�����ԭ��
**********************************************************************************/
typedef void (CALLBACK *fAlarmInfoCallBack)(
	LLONG lAlarmHandle,
	BYTE *pBuffer,
	DWORD dwBufSize,
	LDWORD dwUser);

/**********************************************************************************
������		fCustomDrawCallBack
������		[in] lLoginID��				�����豸���	
			[in] lPlayHandle:			ʵʱ���ž��
			[in] hDC:					��ͼDC
			[in] dwUser:				�û�����
����ֵ��		/
˵����		��Ļ���ӻص�����ԭ��
**********************************************************************************/
typedef void (CALLBACK *fCustomDrawCallBack)(
	LLONG lLoginID, 
	LLONG lPlayHandle, 
	HDC hDC, 
	LDWORD dwUser);

/**********************************************************************************
������		fDownLoadByTimePosCallBack
������		[in] lRealHandle��			ʵʱ���ž��	
			[in] dwTotalSize:			�����ݴ�С
			[in] dwDownLoadSize:		�������ݴ�С
			[in] index:					�ļ�������
			[in] param:					Ԥ����������ǰΪ 0
			[in] dwUser:				�û�����
����ֵ��		/
˵����		��ʱ��طŽ��Ȼص�����ԭ��
**********************************************************************************/
typedef void (CALLBACK *fDownLoadByTimePosCallBack)(
	LLONG lPlayHandle, 
	DWORD dwTotalSize,
	DWORD dwDownLoadSize,
	int index, 
	STU_T_FILE recordfileinfo, 
	LDWORD dwUser);

/**********************************************************************************
������		fMsgCallBack
������		[in] lCommand��				��Ϣ����	
			[in] lLoginID:				�豸��¼���
			[in] pBuf:					���ݻ���
			[in] dwBufLen:				���ݻ����С
			[in] lpszIP:				�豸 IP ��ַ
			[in] nPort:					�豸��¼�˿�
			[in] dwUser:				�û�����
����ֵ��		/
˵����		��Ϣ�ص�����ԭ��
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
������		fRegServerCallBack
������		[in] lHandle��				Socket	
			[in] lpszIP:				��¼IP
			[in] nPort:					��¼�˿�
			[in] lCommand:				��������
			[in] pParam:				��������
			[in] dwParamLen:			�����ڴ��С
			[in] dwUser:				�û�����
����ֵ��		/
˵����		�����������ص�����ԭ��
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
������		fAudioDataCallBack
������		[in] lTalkHandle��			�����Խ����	
			[in] pDataBuf:				���ݻ���
			[in] dwBufSize:				���ݻ����С
			[in] byAudioFlag:			��Ƶ��־λ
			[in] dwUser:				�û�����
����ֵ��		/
˵����		�����Խ�����Ƶ���ݻص�����ԭ��
**********************************************************************************/
typedef void (CALLBACK *fAudioDataCallBack)(
	LLONG lTalkHandle, 
	char *pDataBuf, 
	DWORD dwBufSize, 
	BYTE byAudioFlag, 
	LDWORD dwUser);

/**********************************************************************************
������		fDeviceUpgradeCallBack
������		[in] lLoginID��				�豸��¼���	
			[in] lUpgradechannel:	    ����ͨ�����
			[in] nTotalSize:			���ļ���С
			[in] nSendSize:				�ѷ��͵��ļ���С
			[in] dwUser:				�û�����
����ֵ��		/
˵����		�����豸����ص�����ԭ��
**********************************************************************************/
typedef void (CALLBACK *fDeviceUpgradeCallBack)(
	LLONG lLoginID, 
	LLONG lUpgradechannel,
	int nTotalSize, 
	int nSendSize, 
	LDWORD dwUser);

/**********************************************************************************
������		fTransComDataCallBack
������		[in] lLoginID��				�豸��¼���	
			[in] lTransComChannel:	    ͸�����ھ��
			[in] pBuffer:				���ݻ���
			[in] dwBufSize:				���ݻ����С
			[in] dwUser:				�û�����
����ֵ��		/
˵����		͸�����ڻص�����ԭ��
**********************************************************************************/
typedef void (CALLBACK *fTransComDataCallBack)(
	LLONG lLoginID, 
	LLONG lTransComChannel, 
	char *pBuffer, 
	DWORD dwBufSize, 
	LDWORD dwUser);

/**********************************************************************************
������		fAsyncDataCallBack
������		[in] lCommand��				��������	
			[in] lpData:				�ص�����
			[in] dwUser:				�û�����
����ֵ��		/
˵����		�첽���ݻص�
**********************************************************************************/
typedef void (CALLBACK *fAsyncDataCallBack)(
	LLONG lCommand, 
	P_STU_CALLBACK_DATA lpData, 
	LDWORD dwUser);

/**********************************************************************************
������		fAsyncDataCallBack
������		[in] lCommand��				��������	
			[in] lpData:				�ص�����
			[in] dwUser:				�û�����
����ֵ��		/
˵����		�ļ�����ص�
**********************************************************************************/
typedef void (CALLBACK *fFileTransCallBack)(
	LLONG lHandle, 
	int nTransType, 
	int nState, 
	int nSendSize, 
	int nTotalSize,
	LDWORD dwUser);

/**********************************************************************************
������		fAnalyzeDataCallBack
������		[in] lAnalyzeHandle��		���ܷ������	
			[in] dwEventType:			�����¼�����
			[in] pEventInfo:			�����¼���ϸ��Ϣ
			[in] pBuffer:				�����¼����������ݣ�ͼƬ��
			[in] dwBufSize:				�����¼����������ݴ�С
			[in] nSequence:				0���ݲ�����
			[in] dwUser:				�û�����
����ֵ��		int
˵����		���ܷ������ݻص�
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
������		fAnalyzeDataCallBack
������		[out] pDeviceSearchInfo��	�豸������Ϣ	
			[in] pUserData:				�û�����
����ֵ��		/
˵����		�첽�����豸�ص�
**********************************************************************************/
typedef void (CALLBACK *fSearchDevicesCallBack)(
	STU_DEVICE_SEARCH_INFO *pDeviceSearchInfo, 
	void* pUser);

/**********************************************************************************
������		fPlaybackYuvDataCallBack���ݲ����ã�
������		[in] lPlaybackHandle��		¼��طž��
			[in] pBuffer:				���ݻ���
			[in] dwBufSize:				���ݻ����С
			[in] param:					
			[in] dwUser:				�û�����
����ֵ��		/
˵����		�ط�YUV���ݻص�����
**********************************************************************************/
typedef void (CALLBACK *fPlaybackYuvDataCallBack)(
	LLONG lPlaybackHandle, 
	BYTE *pBuffer,
	DWORD dwBufSize,
	LONG param, 
	LDWORD dwUser,
	void *pReserved);

/**********************************************************************************
������		fConnectProxyRegCallBack���ݲ����ã�
������		[in] lConnectHandle��		�Ʒ������Ӿ��
			[in] pConnectResult:		�Ʒ������ӽ��
			[in] pReserved:				��������
			[in] dwUser:				�û�����
����ֵ��		/
˵����		��������ע��
**********************************************************************************/
typedef void (CALLBACK *fConnectProxyRegCallBack)(
	LLONG lConnectHandle, 
	STU_CLOUD_SERVICE_CONNECT_RESULT* pConnectResult,
	void* pReserved, 
	LDWORD dwUser);

/**********************************************************************************
������		fPlaybackDecPosCallBack
������		[in] lLoginID��				�豸��¼���	
			[in] nEncoderID:			����ID
			[in] dwTotalSize:			���벥�ŵ��ܴ�С
			[in] dwPlaySize:			���벥�ŵĴ�С
			[in] dwUser:				�û�����
����ֵ��		/
˵����		�طŽ���λ�ûص�
**********************************************************************************/
typedef void (CALLBACK *fPlaybackDecPosCallBack)(
	LLONG lLoginID, 
	int nEncoderID, 
	DWORD dwTotalSize, 
	DWORD dwPlaySize, 
	LDWORD dwUser);

#endif //_AL_NET_STRUCT_COLLECTION_H