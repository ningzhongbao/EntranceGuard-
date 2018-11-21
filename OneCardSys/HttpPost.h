#pragma once


#define  POST_IP  "192.168.36.171"
#define  POST_TIP  "/agbox/device/entrance"
#define  DEVICEID   "EN000001"  
#define  ID          123

//认证类型 certifiedType
#define   ICCARD                  1      //IC卡识别
#define   FACERECOGNITION         2      //人脸识别
#define   FGRPRINTRECOGNITION     3      //指纹识别
#define   PALMPRINTRECOGNITION    4      //掌纹识别
#define   IRISRECOGNITION         5      //虹膜识别
#define   VINERECGNITION          6      //静脉识别
#define   OTHERRECOGNITION        7      //其他识别
#define   PHONECERTIFIED          8      //手机认证
#define   TDIMCODECERTIFIED       9      //二维码认证
#define   RFIDCERTIFIED           10     //RFID认证
#define   GPSCERTIFIED            11     //GPS认证
#define   OTHERCERTIFED           12     //其他认证
//事件 eventCode 
#define   HOUSEHOLDIN             1      //住户人员进
#define   HOUSEHOLDOUT            2      //住户人员出
#define   TENANTPERSONIN          3      //租户人员进
#define   TENANTPERSONOUT         4      //租户人员出
#define   FAMILYPERSONIN          5      //亲情人员进
#define   FAMILYPERSONOUT         6      //亲情人员出
#define   VISITIN                 7      //访客人员进
#define   VISITOUT                8      //访客人员出
#define   DELIVERPERIN            9      //快递人员进
#define   DELIVERPEROUT           10     //快递人员出
#define   TAKEOUTPERIN            11     //外卖人员进
#define   TAKEOUTPEROUT           12     //外卖人员出
#define   HSERVICEPERIN           13     //住户服务人员进
#define   HSERVICEPEROUT          14     //住户服务人员出
#define   CSERVICEPERIN           15     //小区服务人员进
#define   CSERVICEPEROUT          16     //小区服务人员出
#define   CWORKMANIN              17     //小区工作人员进
#define   CWORKMANOUT             18     //小区工作人员出
#define   NCOMMUNITYPERIN         19     //非小区人员进（路人）
#define   NCOMMUNITYPEROUT        20     //非小区人员出（路人）
#define   IMPORTCONCERNIN         21     //重点关注人员进
#define   IMPORTCONCERNOUT        22     //重点关注人员出
#define   IMPORTCONTROLIN         23     //重点布控人员进
#define   IMPORTCONTROLOUT        24     //重点布控人员出
#define   OTHERPERSONIN           25     //其它人员进
#define   OTHERPERSONOUT          26     //其它人员出
#define   DEVICEBAD               27     //设备故障
#define   DEVICEOK                28     //设备故障消除
#define   SYSTEMBAD               29     //系统故障
#define   SYSTEMOK                30     //系统故障消除
//人员类型  PersonType
#define   HOUSEHOLD               1      //住户人员
#define   TENANTPERSON            2      //租户人员
#define   FAMILYPER               3      //亲情人员
#define   HSERVICER               4      //住户服务
#define   VISIT                   5      //访客人员
#define   DELIVERPER              6      //快递人员
#define   TAKEOUTPER              7      //外卖人员 
#define   WORKMAN                 8      //工作人员
#define   SERVICERS               11     //服务人员
#define   OTHERPER                12     //其他类型人员
#define   PEOPLECOUNT             32     //人数统计
#define   PERCOUNTABNORMAL        33     //人数异常
#define   PASSERBY                100     //路人
#define   FAMOUSPER               901     //知名人员
#define   IMPORTCTRLPER           900      //重点布控人员
//credentialType
#define   IDNUM                   111     //身份证
#define   MILICERTIFICATE         114     //军官证
#define   TEMPPASSPORT            153     //临时出入证
#define   WORKCERTIFICATE         131     //工作证
#define   HONGKONGPASS            516     //港澳同胞回乡证
#define   TAIWANPASS              511     //台湾居民来网大陆通行证
#define   ORDINARYPASSPORT        414     //普通护照
#define   FORGINPERMIT            554     //外国人居留证 
#define   OTHER                   990     //其他



// deviceId:设备ID填DEVICEID  channel：通道号  CertifiedType：证件类型（身份证：111） certifiedNo：身份证号 name：访客姓名  cardId：卡号（刷脸方式填“”空，刷卡卡号） visit：访客姓名  houseCode：房屋编码（目前：1a896cd5-51c2-47e8-a93f-7ecf834ad900）
// similarity:识别相似度  note：备注  pickey："pic"  picPath:图片路径
//刷卡事件上传  参数：例子Post_Dev_Entrance_addEventICCard(DEVICEID, 1, 111, g_IDCardNum, g_Name, g_Tel, 1, "182A1FF4", g_BFZName, "1a896cd5-51c2-47e8-a93f-7ecf834ad900", "备注信息");  //eventCode参数需具体事件号
int Post_Dev_Entrance_addEventICCard(CString deviceId, int channel, int CertifiedType, CString certifiedNo, CString name, CString phone, int eventCode, CString cardId, CString visit, CString houseCode, CString note);
//人脸识别事件上传
int Post_Dev_Entrance_AddEventPic(CString deviceId, int channel, int CertifiedType, CString certifiedNo, CString name, CString phone, int eventCode, CString cardId, CString visit, CString houseCode, int similarity, CString note, CString pickey, CString picPath);


size_t process_http(int sockfd, char *host, char *page, char *poststr);   // application/x-www-form-urlencoded
size_t process_http_pic(int sockfd, char *host, char *page, char *postHead, char *postPic, int piclen, char *postEnd);  //multipart/form-data


int HttpUpdateHeart();  //OnInitDialog中开CreateThread调用次函数，心跳函数
int InitHttpConnect(SOCKET &sock);

// GB2312到UTF - 8的转换
char* G2U1(const char* gb2312);
//UTF-8到GB2312的转换
char* U2G1(const char* utf8);