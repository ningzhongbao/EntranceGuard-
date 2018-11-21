#pragma once


#define  POST_IP  "192.168.36.171"
#define  POST_TIP  "/agbox/device/entrance"
#define  DEVICEID   "EN000001"  
#define  ID          123

//��֤���� certifiedType
#define   ICCARD                  1      //IC��ʶ��
#define   FACERECOGNITION         2      //����ʶ��
#define   FGRPRINTRECOGNITION     3      //ָ��ʶ��
#define   PALMPRINTRECOGNITION    4      //����ʶ��
#define   IRISRECOGNITION         5      //��Ĥʶ��
#define   VINERECGNITION          6      //����ʶ��
#define   OTHERRECOGNITION        7      //����ʶ��
#define   PHONECERTIFIED          8      //�ֻ���֤
#define   TDIMCODECERTIFIED       9      //��ά����֤
#define   RFIDCERTIFIED           10     //RFID��֤
#define   GPSCERTIFIED            11     //GPS��֤
#define   OTHERCERTIFED           12     //������֤
//�¼� eventCode 
#define   HOUSEHOLDIN             1      //ס����Ա��
#define   HOUSEHOLDOUT            2      //ס����Ա��
#define   TENANTPERSONIN          3      //�⻧��Ա��
#define   TENANTPERSONOUT         4      //�⻧��Ա��
#define   FAMILYPERSONIN          5      //������Ա��
#define   FAMILYPERSONOUT         6      //������Ա��
#define   VISITIN                 7      //�ÿ���Ա��
#define   VISITOUT                8      //�ÿ���Ա��
#define   DELIVERPERIN            9      //�����Ա��
#define   DELIVERPEROUT           10     //�����Ա��
#define   TAKEOUTPERIN            11     //������Ա��
#define   TAKEOUTPEROUT           12     //������Ա��
#define   HSERVICEPERIN           13     //ס��������Ա��
#define   HSERVICEPEROUT          14     //ס��������Ա��
#define   CSERVICEPERIN           15     //С��������Ա��
#define   CSERVICEPEROUT          16     //С��������Ա��
#define   CWORKMANIN              17     //С��������Ա��
#define   CWORKMANOUT             18     //С��������Ա��
#define   NCOMMUNITYPERIN         19     //��С����Ա����·�ˣ�
#define   NCOMMUNITYPEROUT        20     //��С����Ա����·�ˣ�
#define   IMPORTCONCERNIN         21     //�ص��ע��Ա��
#define   IMPORTCONCERNOUT        22     //�ص��ע��Ա��
#define   IMPORTCONTROLIN         23     //�ص㲼����Ա��
#define   IMPORTCONTROLOUT        24     //�ص㲼����Ա��
#define   OTHERPERSONIN           25     //������Ա��
#define   OTHERPERSONOUT          26     //������Ա��
#define   DEVICEBAD               27     //�豸����
#define   DEVICEOK                28     //�豸��������
#define   SYSTEMBAD               29     //ϵͳ����
#define   SYSTEMOK                30     //ϵͳ��������
//��Ա����  PersonType
#define   HOUSEHOLD               1      //ס����Ա
#define   TENANTPERSON            2      //�⻧��Ա
#define   FAMILYPER               3      //������Ա
#define   HSERVICER               4      //ס������
#define   VISIT                   5      //�ÿ���Ա
#define   DELIVERPER              6      //�����Ա
#define   TAKEOUTPER              7      //������Ա 
#define   WORKMAN                 8      //������Ա
#define   SERVICERS               11     //������Ա
#define   OTHERPER                12     //����������Ա
#define   PEOPLECOUNT             32     //����ͳ��
#define   PERCOUNTABNORMAL        33     //�����쳣
#define   PASSERBY                100     //·��
#define   FAMOUSPER               901     //֪����Ա
#define   IMPORTCTRLPER           900      //�ص㲼����Ա
//credentialType
#define   IDNUM                   111     //���֤
#define   MILICERTIFICATE         114     //����֤
#define   TEMPPASSPORT            153     //��ʱ����֤
#define   WORKCERTIFICATE         131     //����֤
#define   HONGKONGPASS            516     //�۰�ͬ������֤
#define   TAIWANPASS              511     //̨�����������½ͨ��֤
#define   ORDINARYPASSPORT        414     //��ͨ����
#define   FORGINPERMIT            554     //����˾���֤ 
#define   OTHER                   990     //����



// deviceId:�豸ID��DEVICEID  channel��ͨ����  CertifiedType��֤�����ͣ����֤��111�� certifiedNo�����֤�� name���ÿ�����  cardId�����ţ�ˢ����ʽ����գ�ˢ�����ţ� visit���ÿ�����  houseCode�����ݱ��루Ŀǰ��1a896cd5-51c2-47e8-a93f-7ecf834ad900��
// similarity:ʶ�����ƶ�  note����ע  pickey��"pic"  picPath:ͼƬ·��
//ˢ���¼��ϴ�  ����������Post_Dev_Entrance_addEventICCard(DEVICEID, 1, 111, g_IDCardNum, g_Name, g_Tel, 1, "182A1FF4", g_BFZName, "1a896cd5-51c2-47e8-a93f-7ecf834ad900", "��ע��Ϣ");  //eventCode����������¼���
int Post_Dev_Entrance_addEventICCard(CString deviceId, int channel, int CertifiedType, CString certifiedNo, CString name, CString phone, int eventCode, CString cardId, CString visit, CString houseCode, CString note);
//����ʶ���¼��ϴ�
int Post_Dev_Entrance_AddEventPic(CString deviceId, int channel, int CertifiedType, CString certifiedNo, CString name, CString phone, int eventCode, CString cardId, CString visit, CString houseCode, int similarity, CString note, CString pickey, CString picPath);


size_t process_http(int sockfd, char *host, char *page, char *poststr);   // application/x-www-form-urlencoded
size_t process_http_pic(int sockfd, char *host, char *page, char *postHead, char *postPic, int piclen, char *postEnd);  //multipart/form-data


int HttpUpdateHeart();  //OnInitDialog�п�CreateThread���ôκ�������������
int InitHttpConnect(SOCKET &sock);

// GB2312��UTF - 8��ת��
char* G2U1(const char* gb2312);
//UTF-8��GB2312��ת��
char* U2G1(const char* utf8);