#ifndef __PLATFORM_H__
#define __PLATFORM_H__
//
// basic primitive data types:
//   byte, int8, uint8, int16, uint16, int32, uint32, float32, float64
//   char, string, boolean, time, octetString, binaryString, octet, displayString
//   octetString
//
//#if (defined(WIN32) || defined(WIN64))


#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#endif

#if defined(WIN32) || defined(WIN64)
#define OS_THREAD_ID	DWORD
#else
#define OS_THREAD_ID	pthread_t
#endif

#if defined(__APPLE__) && defined(IOS)
#include "objc/objc.h"
#endif

#if defined(ANDROID)
int pthread_cancel(pthread_t thread);
#ifndef BOOL
#define BOOL  int
#endif
#endif

#if !defined(byte)
typedef unsigned char byte;
#endif

#if !defined(int8)
typedef char int8;
#endif

#if !defined(uint8)
typedef unsigned char uint8;
#endif

#if !defined(int16)
typedef short int16;
#endif

#if !defined(uint16)
typedef unsigned short uint16;
#endif

#if !defined(int32)
typedef int int32;
#endif

#if !defined(uint32)
typedef unsigned int uint32;
#endif

#if !defined(float32)
typedef float float32;
#endif

#if !defined(float64)
typedef double float64;
#endif

#if !defined(octet)
typedef unsigned char octet;
#endif

#if !defined(sstring)
typedef char* sstring;
#endif

#if !defined(displayString)
typedef char* displayString;
#endif

#if !defined(octetString)
typedef unsigned char* octetString;
#endif

#if !defined(binaryString)
typedef unsigned char* binaryString;
#endif

#if !defined(uint64)
#if (defined(WIN32) || defined(WIN64))
typedef unsigned __int64	uint64;
#else
typedef unsigned long long	uint64;
#endif
#endif

#if !defined(int64)
#if (defined(WIN32) || defined(WIN64))
typedef __int64	int64;
#else
typedef long long	int64;
#endif
#endif

#if !defined(uint128)
typedef struct { unsigned char octet[16]; } uint128;
#endif

#if !defined(boolean)
typedef uint8 boolean;
#endif

#if !defined(ip_Address)
typedef unsigned char* ip_Address;
#endif

#if !defined(DateTime)
typedef unsigned long DateTime;
#endif

#if !defined(TRUE)
#define TRUE ((boolean)1)
#endif

#if !defined(FALSE)
#define FALSE ((boolean)0)
#endif

#if !defined(NULL)
#define NULL ((int32)0)
#endif

#if defined(WIN32) || defined(WIN64)
#else

#if !defined(BOOL)
typedef	int BOOL;
#endif

#if !defined(__uint64)
typedef unsigned long long	__uint64;
#endif

#if !defined(LONGLONG)
typedef long long	LONGLONG;
#endif

#if ((!defined(__int64))&&(!defined(ICPC)))
typedef long long	__int64;
#endif

#if !defined(LPCSTR)
typedef	char*  LPCSTR;
#endif

#if !defined(UINT)
typedef	unsigned int UINT;
#endif

#if !defined(LRESULT)
typedef uint32 LRESULT;
#endif

#if !defined(TCHAR)
typedef char TCHAR;
#endif

#if !defined(LPCTSTR)
typedef const char* LPCTSTR;
#endif

#if !defined(DWORD)
typedef unsigned long DWORD;
#endif

#if !defined(LPDWORD)
typedef	DWORD*		LPDWORD;
#endif

#if !defined(FOURCC)
typedef DWORD FOURCC;
#endif

#if !defined(LPTSTR)
typedef TCHAR*  LPTSTR;
#endif

#endif

#if !defined(INT)
typedef int INT;
#endif

 #if !defined(UINT)
 typedef unsigned int UINT;
 #endif

#if !defined(BYTE)
typedef unsigned char BYTE;
#endif

#if !defined(WORD)
typedef unsigned short WORD;
#endif

#if !defined(PBYTE)
typedef unsigned char*	PBYTE;
#endif

#if !defined(LPBYTE)
typedef	BYTE*		LPBYTE;
#endif

#if !defined(LONG)
#if (defined(WIN32) || defined(WIN64))
typedef long LONG;
#else
typedef long LONG;
#endif
#endif

#if defined(WIN32) || defined(WIN64)
#else
typedef	void*		HANDLE;
typedef HANDLE*		PHANDLE;

#if !defined(HWND)
typedef	void*		HWND;
#endif

#if !defined(HDC)
typedef	void*		HDC;
#endif

#if !defined(LPVOID)
typedef	void*		LPVOID;
#endif

#if !defined(SOCKET)
typedef	unsigned int	SOCKET;
#endif

#if !defined(HINSTANCE)
typedef	void*	HINSTANCE;
#endif

#define STATUS_WAIT_0   ((DWORD)0x00000000L)
#define WAIT_OBJECT_0   ((STATUS_WAIT_0) + 0)
#define INFINITE		0xFFFFFFFF
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR    (-1)
#define SD_RECEIVE      SHUT_RD
#define SD_SEND         SHUT_WR
#define SD_BOTH         SHUT_RDWR
#define closesocket(S)	close(S)
#define WINAPI
#define Sleep(x)		usleep(x*1000)
#define __stdcall		
#define CALLBACK

typedef DWORD (WINAPI *LPTHREAD_START_ROUTINE)(LPVOID lpThreadParameter);

#ifndef DEF_RECT

typedef struct  tagRECT
{
    LONG left;
    LONG top;
    LONG right;
    LONG bottom;
} RECT;

#define DEF_RECT

#endif

#define FAR
typedef union _LARGE_INTEGER
{
    struct 
	{
        DWORD LowPart;
        long HighPart;
    };

    struct 
	{
        DWORD LowPart;
        long HighPart;
    } u;

    LONGLONG QuadPart;
} LARGE_INTEGER;

typedef struct waveformat_tag 
{
	WORD    wFormatTag;        /* format type */
	WORD    nChannels;         /* number of channels (i.e. mono, stereo...) */
	DWORD   nSamplesPerSec;    /* sample rate */
	DWORD   nAvgBytesPerSec;   /* for buffer estimation */
	WORD    nBlockAlign;       /* block size of data */
} WAVEFORMAT;

typedef struct tWAVEFORMATEX
{
    WORD    wFormatTag;        /* format type */
    WORD    nChannels;         /* number of channels (i.e. mono, stereo...) */
    DWORD   nSamplesPerSec;    /* sample rate */
    DWORD   nAvgBytesPerSec;   /* for buffer estimation */
    WORD    nBlockAlign;       /* block size of data */
    WORD    wBitsPerSample;    /* Number of bits per sample of mono data */
    WORD    cbSize;            /* The count in bytes of the size of
                                    extra information (after cbSize) */
} WAVEFORMATEX; 

typedef struct tagRGBQUAD 
{
	BYTE    rgbBlue;
	BYTE    rgbGreen;
	BYTE    rgbRed;
	BYTE    rgbReserved;
} RGBQUAD;
typedef RGBQUAD FAR* LPRGBQUAD;

typedef struct tagBITMAPINFOHEADER
{
	DWORD      biSize;
	LONG       biWidth;
	LONG       biHeight;
	WORD       biPlanes;
	WORD       biBitCount;
	DWORD      biCompression;
	DWORD      biSizeImage;
	LONG       biXPelsPerMeter;
	LONG       biYPelsPerMeter;
	DWORD      biClrUsed;
	DWORD      biClrImportant;
} BITMAPINFOHEADER, FAR *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagBITMAPINFO
{
	BITMAPINFOHEADER    bmiHeader;
	RGBQUAD             bmiColors[1];
} BITMAPINFO, FAR *LPBITMAPINFO, *PBITMAPINFO;

#endif

#ifndef MAX_PATH
#define MAX_PATH	260
#endif

#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct _GUID 
{
	DWORD	Data1;
    WORD	Data2;
    WORD	Data3;
    BYTE	Data4[8];
} GUID;
#endif

#if !defined(INT64)
typedef __int64 INT64;
#endif

#ifndef MAKEFOURCC
#define MAKEFOURCC(ch0, ch1, ch2, ch3) ((DWORD)(BYTE)(ch0) | ((DWORD)(BYTE)(ch1) << 8) | ((DWORD)(BYTE)(ch2) << 16) | ((DWORD)(BYTE)(ch3) << 24 ))
#endif

#ifndef __max
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#endif
#ifndef __min
#define __min(a,b) (((a) < (b)) ? (a) : (b))
#endif

//#endif

#ifndef LLONG
#if (defined(WIN32) || defined(WIN64))
#ifdef WIN64
#define LLONG __int64
#else //WIN32 
#define LLONG LONG
#endif
#else	//linux
#define LLONG long 
#endif
#endif

#ifndef LDWORD
#if (defined(WIN32) || defined(WIN64))
#ifdef WIN64
#define LDWORD __int64
#else //WIN32 
#define LDWORD DWORD
#endif
#else	//linux
#define LDWORD long 
#endif
#endif

#if !defined(INT64)
#if (defined(WIN32) || defined(WIN64) || defined(ICPC))
typedef __int64 INT64;
#else
typedef long long INT64;
#endif
#endif

#ifndef RGB
#define RGB(r,g,b) ((DWORD)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))
#endif

#ifndef RGBA
#define RGBA(r,g,b,a) ((DWORD)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)|(((DWORD)(BYTE)(a))<<24)))
#endif

#endif //__PLATFORM_H__
