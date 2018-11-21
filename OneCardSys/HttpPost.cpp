#include "stdafx.h"
#include "HttpPost.h"

#define MAXLINE  1024*4
int Post_Dev_Entrance_updateHeart();


// 刷卡开门事件
//参数说明：deviceId 设备编号、channel 通道号、certifiedType 证件类型、certifiedNo 证件号码、name 姓名、phone 电话、eventCode 事件编码、
//certifiedTypeCode认证类型编码、cardId  卡号、visit 被访人、houseCode房屋编码、similarity 比对相似度、note备注说明、picture 二进制图片数据，键为 eventPic 的值
int Post_Dev_Entrance_addEventICCard(CString deviceId, int channel, int CertifiedType, CString certifiedNo, CString name, CString phone, int eventCode, CString cardId, CString visit, CString houseCode, CString note)
{
	WSADATA wsaData;
	int err;
	 err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (err != 0) {
	//printf("WSAStartup failed with error: %d\n", err);
	 return -1;
	}
	char szSendLine[1024] = "";
	SOCKET sockfd = INVALID_SOCKET;
	
	SYSTEMTIME st;
	CString strDateTime;
	char *pnote = G2U1(note);
	char *pname = G2U1(name);
	char *pvisit = G2U1(visit);

	GetLocalTime(&st);
	strDateTime.Format("%d-%d-%d %d:%d:%d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	sprintf_s(szSendLine,
		"key=80e6ca54-267c-46a4-b305-960c9807c9b9&json={\"json-rpc\":\"2.0\",\"method\":\"addEvent\",\"params\":{\"deviceId\":\"%s\",\"channel\":%d,\"certifiedType\":%d,\"certifiedNo\":\"%s\",\"name\":\"%s\",\"phone\":\"%s\",\"triggerTime\":\"%s\",\"eventCode\":%d,\"certifiedTypeCode\":\"1\",\"cardId\":\"%s\",\"visit\":\"%s\",\"houseCode\":\"%s\",\"note\":\"%s\"},\"id\":%d}\r\n",
		deviceId, channel, CertifiedType, certifiedNo, pname, phone, strDateTime, eventCode, cardId, pvisit, houseCode, pnote, ID);
	//char *poststr = "key=80e6ca54-267c-46a4-b305-960c9807c9b9&json={\"json-rpc\":\"2.0\",\"method\":\"addEvent\",\"params\":{\"deviceId\":\"AL0000000001\",\"channel\":0,\"certifiedType\":111,\"certifiedNo\":\"420104199403193033\",\"name\":\"张山\",\"phone\":\"18637994388\",\"triggerTime\":\"2018-3-4 12:12:23\",\"eventCode\":3,\"certifiedTypeCode\":1,\"cardId\":\"abcdef123\",\"visit\":\"李四\",\"houseCode\":\"1a896cd5-51c2-47e8-a93f-7ecf834ad900\",\"similarity\":81,\"note\":\"\",\"eventPic\": \"pic\"},\"id\":123}\r\n";
	char *poststr = "key=80e6ca54-267c-46a4-b305-960c9807c9b9&json={\"json-rpc\":\"2.0\",\"method\":\"addEvent\",\"params\":{\"deviceId\":\"AL0000000001\",\"channel\":0,\"certifiedType\":111,\"certifiedNo\":\"420104199403193033\",\"name\":\"张三\",\"phone\":\"18637994388\",\"triggerTime\":\"2018-3-4 12:12:23\",\"eventCode\":3,\"certifiedTypeCode\":1,\"cardId\":\"abcdef123\",\"visit\":\"李四\",\"houseCode\":\"1a896cd5-51c2-47e8-a93f-7ecf834ad900\"},\"id\":123}\r\n";


	err = InitHttpConnect(sockfd);

	//printf("start Post3\n");
	if (err < 0)
	{
		goto END;
	}
	process_http(sockfd, POST_IP, POST_TIP, szSendLine);
	//closesocket(sockfd);
	WSACleanup();
	return 0;
END:
	//closesocket(sockfd);
	WSACleanup();
	return -1;
}

//人脸识别开门事件
int Post_Dev_Entrance_AddEventPic(CString deviceId, int channel, int CertifiedType, CString certifiedNo, CString name, CString phone, int eventCode, CString cardId, CString visit, CString houseCode, int similarity, CString note, CString pickey, CString picPath)
{
	WSADATA wsaData;
	int err;
	err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (err != 0) {
		//printf("WSAStartup failed with error: %d\n", err);
		return -1;
	}
	char szContHead[1024] = "";
	char szContEnd[255] = "";
	int PicSize = 0;
	//int ContentLength = 0;
	char *pPicBuf = NULL;
	//char *pSendBuf = NULL;
	//BYTE * send_Pic;
	int ret = 0;
	SOCKET sockfd = INVALID_SOCKET;
	

	SYSTEMTIME st;
	CString strDateTime;

	char *pnote = G2U1(note);
	char *pname = G2U1(name);
	char *pVisit = G2U1(visit);
	char strEnd[] = "\r\n------WebKitFormBoundaryJWwUn5U22G4AsccA--\r\n";


	GetLocalTime(&st);
	strDateTime.Format("%d-%d-%d %2d:%2d:%2d", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);

	//sprintf_s(szSendLine,
	//"key=80e6ca54-267c-46a4-b305-960c9807c9b9&json={\"json-rpc\":\"2.0\",\"method\":\"addEvent\",\"params\":{\"deviceId\":\"%s\",\"gis\":{\"lon\":121.487989,\"lat\":31.29023,\"alt\":5.2,\"floor\":3}},\"id\":%d}\r\n", DEVICEID, ID);

	FILE* fp;
	err = fopen_s(&fp, picPath, "rb");
	if (err != 0)
	{
		//printf("open picure file  error!\n");
		return -1;
	}

	fseek(fp, SEEK_SET, SEEK_END);
	PicSize = ftell(fp);
	rewind(fp);
	//printf("PicLen: %d\n", PicSize);
	pPicBuf = (char *)malloc(sizeof(char)*(PicSize));
	//printf("strlen(pPicBuf)： %d\n", strlen(pPicBuf));
	int nRet = fread((char*)pPicBuf, 1, PicSize, fp);
	fclose(fp);
	
	//fseek(fp, 0, SEEK_SET);


	// ;filename = "1.jpg"
	sprintf_s(szContHead,
		"------WebKitFormBoundaryJWwUn5U22G4AsccA\r\n"
		"Content-Disposition: form-data; name=\"key\"\r\n\r\n"
		"80e6ca54-267c-46a4-b305-960c9807c9b9\r\n"
		"------WebKitFormBoundaryJWwUn5U22G4AsccA\r\n"
		"Content-Disposition: form-data; name=\"json\"\r\n\r\n"
		"{\"json-rpc\":\"2.0\",\"method\":\"addevent\",\"params\":{\"deviceId\":\"%s\",\"channel\":%d,\"certifiedType\":%d,\"certifiedNo\":\"%s\",\"name\":\"%s\",\"phone\":\"%s\",\"triggerTime\":\"%s\",\"eventCode\":%d,\"certifiedTypeCode\":\"2\",\"event\":\"1\",\"cardId\":\"%s\",\"visit\":\"%s\",\"houseCode\":\"%s\",\"similarity\":%d,\"note\":\"%s\",\"eventPic\":\"%s\"},\"id\":%d}\r\n"
		//"{\"json-rpc\":\"2.0\",\"method\":\"addevent\",\"params\":{\"deviceId\":\"AL0000000001\",\"channel\":0,\"certifiedType\":1,\"certifiedNo\":\"420104199403193033\",\"name\":\"张三\",\"phone\":\"18637994388\",\"triggerTime\":\"2018-10-23 11:11:11\",\"eventCode\":1,\"cardId\":\"182A1FF4\",\"visit\":\"李四\",\"houseCode\":\"1a896cd5-51c2-47e8-a93f-7ecf834ad900\",\"similarity\":81,\"note\":\"beizhu\",\"eventPic\":\"pic\"},\"id\":123}\r\n"
		"------WebKitFormBoundaryJWwUn5U22G4AsccA\r\n"
		"Content-Disposition: form-data; name=\"%s\"\r\n"
		"Content-Type: image/jpeg\r\n\r\n"
		, deviceId, channel, CertifiedType, certifiedNo, pname, phone, strDateTime, eventCode, cardId, pVisit, houseCode, similarity, pnote, pickey, ID, pickey
		//图片二进制数据
		//"------WebKitFormBoundaryJWwUn5U22G4AsccU--\r\n"
	);


	err = InitHttpConnect(sockfd);
	//printf("start Post3\n");
	if (err < 0)
	{
		goto END;
	}

	process_http_pic(sockfd, POST_IP, POST_TIP, szContHead, pPicBuf, PicSize, strEnd);
	//closesocket(sockfd);
	WSACleanup();
	free(pPicBuf);
	return  0;
END:
	//closesocket(sockfd);
	WSACleanup();
	free(pPicBuf);
}

int HttpUpdateHeart()
{
	while (1)
	{
		Post_Dev_Entrance_updateHeart();
		Sleep(5000);  //5s
	}
}

int Post_Dev_Entrance_updateHeart()
{
	char szSendLine[1024] = "";
	WSADATA wsaData;
	int err;
	err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (err != 0) {
		//printf("WSAStartup failed with error: %d\n", err);
		return -1;
	}

	SOCKET sockfd = INVALID_SOCKET;
	
	sprintf_s(szSendLine,
		"key=80e6ca54-267c-46a4-b305-960c9807c9b9&json={\"json-rpc\":\"2.0\",\"method\":\"updateHeart\",\"params\":{\"deviceId\":\"%s\",\"gis\":{\"lon\":121.487989,\"lat\":31.29023,\"alt\":5.2,\"floor\":3}},\"id\":%d}\r\n", DEVICEID, ID);

	//char *poststr1 = "key=80e6ca54-267c-46a4-b305-960c9807c9b9&json={\"json-rpc\":\"2.0\",\"method\":\"updateHeart\",\"params\":{\"deviceId\":\"AL0000000001\",\"gis\":{\"lon\":121.487989,\"lat\":31.29023,\"alt\":5.2,\"floor\":3}},\"id\":123}\r\n";

	err = InitHttpConnect(sockfd);
	//printf("start Post3\n");
	if (err < 0)
	{
		goto END;
	}

	process_http(sockfd, POST_IP, POST_TIP, szSendLine);
	//closesocket(sockfd);
	WSACleanup();
	return  0;
END:
	//closesocket(sockfd);
	WSACleanup();
}



//multipart/form-data  发送包含图片数据 此二进制
//x - www - form - urlencoded：只能上传键值对，并且键值对都是间隔分开的。multipart / form - data：既可以上传文件等二进制数据，也可以上传表单键值对，只是最后会转化为一条信息；
size_t process_http_pic(int sockfd, char *host, char *page, char *postHead, char *postPic, int piclen, char *postEnd)
{
	char sendline[MAXLINE + 1], recvline[MAXLINE + 1];
	size_t n;
	int DataLen = strlen(postHead) + strlen(postEnd) + piclen;
	char *send_Data = new char[DataLen + 2048];
	memset(send_Data, 0, DataLen);

	//multipart/form-data 可上传文件
	sprintf_s(sendline,
		"POST %s HTTP/1.1\r\n"  //
		"Host: %s\r\n"   //
		"Connection: keep-alive\r\n"
		"Content-Length: %d\r\n"   //
		"Cache-Control: no-cache\r\n"
		//"Origin: chrome-extension://hedcijldnleebpckaalmjhdkeelccflg\r\n"
		"Origin: http://127.0.0.1\r\n"   //192.168.1.201
		"Content-Type: multipart/form-data; boundary=----WebKitFormBoundaryJWwUn5U22G4AsccA\r\n"
		//"User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.36 Safari/537.36\r\n"
		//"Postman-Token: 5c778e37-84f4-d7aa-1b1c-ba0a394f8c6d\r\n"
		"Accept: */*\r\n"
		"Accept-Encoding: gzip, deflate\r\n"
		"Accept-Language: zh-CN,zh;q=0.8\r\n\r\n"
		, page, host, DataLen);

	memcpy(send_Data, sendline, strlen(sendline));
	memcpy(send_Data + strlen(sendline), postHead, strlen(postHead));
	memcpy(send_Data + strlen(sendline) + strlen(postHead), postPic, piclen);
	memcpy(send_Data + strlen(sendline) + strlen(postHead) + piclen, postEnd, strlen(postEnd));

	
	send(sockfd, send_Data, DataLen + strlen(sendline), 0);

	/*while ((n = recv(sockfd, recvline, MAXLINE, 0)) > 0) {
		recvline[n] = '\0';
		printf("\n%s", recvline);
	}
*/
	//p = NULL;
	delete send_Data;

	return n;

}


//处理无图片数据  application/x-www-form-urlencoded
size_t process_http(int sockfd, char *host, char *page, char *poststr)
{
	char sendline[MAXLINE + 1], recvline[MAXLINE + 1];
	size_t n;

	//multipart/form-data 可上传文件
	sprintf_s(sendline,
		"POST %s HTTP/1.1\r\n"
		"Progma: no-cache\r\n"
		"Cach-control: no-cache\r\n"
		"Host: %s\r\n"
		"Origin: http://127.0.0.1\r\n"   //192.168.1.201
										 //"Content-type: application/json\r\n"
		"Content-type: application/x-www-form-urlencoded;charset=UTF-8\r\n"
		"Content-length: %d\r\n\r\n"
		"%s", page, host, strlen(poststr), poststr);
	//printf(sendline);
	//char *p = G2U(sendline);
	send(sockfd, sendline, strlen(sendline), 0);

	while ((n = recv(sockfd, recvline, MAXLINE, 0)) > 0) {
		recvline[n] = '\0';
		//printf("\n%s", recvline);
	}

	//p = NULL;
	return n;

}




int InitHttpConnect(SOCKET &sock)
{
	//WSADATA wsaData;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	int err;

	/*err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (err != 0) {
		printf("WSAStartup failed with error: %d\n", err);
		return -1;
	}*/
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port  
	err = getaddrinfo(POST_IP, "80", &hints, &result);
	if (err != 0) {
	//	printf("getaddrinfo failed with error: %d\n", err);
	//	WSACleanup();
		return -1;
	}

	//// Attempt to connect to an address until one succeeds  
	//for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
	//{

		// Create a SOCKET for connecting to server  
	    ptr = result;
		sock = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);
		if (sock == INVALID_SOCKET) {
		//	printf("socket failed with error: %ld\n", WSAGetLastError());
		//	WSACleanup();
			return -1;
		}

		// Connect to server.  
		err = connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (err == SOCKET_ERROR) {
			
			closesocket(sock);
			return -1;
			//sock = INVALID_SOCKET;
		//	continue;
		}

	//}

	return 0;
}




//UTF-8到GB2312的转换
char* U2G1(const char* utf8)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, wstr, len);
	len = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

//GB2312到UTF-8的转换
char* G2U1(const char* gb2312)
{
	int len = MultiByteToWideChar(CP_ACP, 0, gb2312, -1, NULL, 0);
	wchar_t* wstr = new wchar_t[len + 1];
	memset(wstr, 0, len + 1);
	MultiByteToWideChar(CP_ACP, 0, gb2312, -1, wstr, len);
	len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
	char* str = new char[len + 1];
	memset(str, 0, len + 1);
	WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
	if (wstr) delete[] wstr;
	return str;
}

