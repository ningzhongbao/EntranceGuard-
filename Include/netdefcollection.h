#ifndef _AL_NET_DEF_COLLECTION_H
#define _AL_NET_DEF_COLLECTION_H

/*****************************************************************************************
 *							netmanager library 宏定义									 *
 *****************************************************************************************/

#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#ifndef INT64
	#define INT64  __int64
#endif
#endif

#ifndef LLONG
	#ifdef WIN64
		#define LLONG INT64
	#else 
		#define LLONG long
	#endif
#endif

#ifndef LDWORD
#if (defined(WIN32) || defined(WIN64))
#ifdef WIN64
#define LDWORD  __int64
#else //WIN32 
#define LDWORD  DWORD
#endif
#else    //linux
#define LDWORD	long 
#endif
#endif

#if !defined(WIN32) && !defined(WIN64)
#include "../Platform/platform.h"
#endif

////////////////////////////////////////////////////////////////////////////////////////////
// COMMON
#ifndef _COMMON_DEFINITION_
#define _COMMON_DEFINITION_
#define VALUE(value)		(value)
#define STRLEN(length)		(length)
#define COUNT(count)		(count)
#define ROW(row)			(row)
#define COL(col)			(col)
#endif

////////////////////////////////////////////////////////////////////////////////////////////
// DEVICE
#define MAX_CHANNEL_NUM							32						// 最大通道数
#define MAX_VIDEO_CHANNEL_NUM					32						// 视频最大通道数
#define	MAX_RECORD_CHANNEL_NUM					32						// 最大录像通道数
#define MAX_ALARM_OUT_CHANNEL_NUM				32						// 最大报警输出通道数
#define MAX_CAPTURE_CHANNEL_NUM					32						// 最大抓图通道数

#define MAX_NETCARD_NUM							8						// 网卡数量最大值
#define MAX_LOG_AMOUNT							16						// 一次查询的最大日志数量

#define	WEEK_SECTION							7
#define	TIME_SECTION							6

#define MAX_VIDEO_OSD_CUSTOM_NUM				6						// 最大自定义视频 OSD 个数
#define MAX_IRIS_TYPE_NUM						6						// 最大光圈类型个数
#define MAX_CAPS_PICTURE_OSD_NUM				3						// 图片 OSD 数组最大个数

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 语言简写最大长度
#define MAX_LANGUAGE_LENGTH					20

// 支持的最大语言数量
#define MAX_LANGUAGE_NUM					32

// IPv4 和 IPv6最大黑白名单数目
#define MAX_NET_WB_ITEM_NUM					50

// 网络存储服务最大条目
#define MAX_NET_STORAGE_ITEM_NUM			4

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 智能事件

// 人脸识别信息最大数目
#define MAX_FACE_REC_INFO_NUM				5

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 人脸库 & 人脸

// 最大人脸组数目
#define MAX_FACE_GROUP_NUM					3

// 人员最大人脸数目
#define MAX_PERSON_FACE_NUM					3

// 一次查询的人员最大数目
#define MAX_ONCE_QUERY_PERSON_NUM			64

// 一次查询的人脸识别比对记录最大数目
#define MAX_ONCE_QUERY_FACE_REC_REC_NUM		128

// 最大人脸识别记录结果
#define MAX_FACE_REC_RESULT_NUM				8

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 人脸库相关错误码
#define _FACE_ERR_CODE(x)						(0x00090000|x)
#define FACE_ERR_UNKNOWN						_FACE_ERR_CODE(1)		// 未知错误
#define FACE_ERR_GROUP_NAME_CONFLICT			_FACE_ERR_CODE(2)		// 人脸底库组名冲突
#define FACE_ERR_GROUP_ALIAS_CONFLICT			_FACE_ERR_CODE(3)		// 人脸底库组别名冲突
#define FACE_ERR_GROUP_GUID_CONFLICT			_FACE_ERR_CODE(4)		// 人脸底库组GUID冲突
#define FACE_ERR_GROUP_NUM						_FACE_ERR_CODE(5)		// 人脸底库组数已达上限
#define FACE_ERR_PERSON_NAME_CONFLICT			_FACE_ERR_CODE(6)		// 人脸库入库人员名字冲突
#define FACE_ERR_PERSON_CERTID_CONFLICT			_FACE_ERR_CODE(7)		// 人脸库入库人员证件和证件号冲突
#define FACE_ERR_FACETOKEN_CONFLICT				_FACE_ERR_CODE(8)		// 入库的人脸图片 Token 冲突
#define FACE_ERR_FACEIMAGE_BIND					_FACE_ERR_CODE(9)		// 人脸图片重复绑定
#define FACE_ERR_FACEIMAGE_NUM					_FACE_ERR_CODE(0x0a)	// 入库人脸数已达上限
#define FACE_ERR_PERSON_FACEIMAGE_NUM			_FACE_ERR_CODE(0x0b)	// 此人待入库人脸数已达上限
#define FACE_ERR_PERSON_FACEIMAGE_OVERFLOW		_FACE_ERR_CODE(0x0c)	// 此人待入库人脸数超过上限
#define FACE_ERR_FACEIMAGE_EMPTY				_FACE_ERR_CODE(0x0d)	// 人脸图片数据空
#define FACE_ERR_PERSON_NOT_EXIST				_FACE_ERR_CODE(0x0e)	// 人员不存在
#define FACE_ERR_FACEIMAGE_NOT_EXIST			_FACE_ERR_CODE(0x0f)	// 人脸不存在
#define FACE_ERR_FACEIMAGE_ALREADY_EXIST		_FACE_ERR_CODE(0x10)	// 人脸图片已入库
#define FACE_ERR_FACEIMAGE_NO_FACE				_FACE_ERR_CODE(0x11)	// 人脸图片无人脸
#define FACE_ERR_FACEIMAGE_LOW_QUALITY			_FACE_ERR_CODE(0x12)	// 人脸底库组不存在
#define FACE_ERR_GROUP_NOT_EXIST				_FACE_ERR_CODE(0x13)	// 人脸图片质量过低
#define	FACE_ERR_FACEIMAGE_TOO_LARGE			_FACE_ERR_CODE(0x14)	// 人脸图片数据过大
#define FACE_ERR_SYSTEM_BUSY					_FACE_ERR_CODE(0x15)	// 系统忙

// 错误类型代号，对应 Net_LastError 接口的返回值
#define _ERR_CODE(x)                            (0xEC000000|x)
#define NET_NOERR								0						// 没有错误
#define NET_ERR_UNKNOWN							-1						// 未知错误
#define NET_ERR_INVALID_HANDLE                  _ERR_CODE(1)            // 句柄无效错误
#define NET_ERR_SYS								_ERR_CODE(2)            // 系统错误
#define NET_ERR_NETWORK							_ERR_CODE(3)            // 网络错误
#define NET_ERR_PROTOCOL						_ERR_CODE(4)            // 协议错误
#define NET_ERR_INIT							_ERR_CODE(5)            // 初始化错误
#define NET_ERR_UNINIT							_ERR_CODE(6)            // 清理错误
#define NET_ERR_NO_INIT                         _ERR_CODE(7)			// 未经初始化错误
#define NET_ERR_NOT_AUTHORIZED                  _ERR_CODE(8)            // 无操作权限错误
#define NET_ERR_ILLEGAL_PARAM                   _ERR_CODE(9)            // 用户参数不合法错误
#define NET_ERR_RENDER_OPEN						_ERR_CODE(10)			// 申请render资源错误
#define NET_ERR_OPEN_CHANNEL					_ERR_CODE(11)           // 打开通道失败错误
#define NET_ERR_CLOSE_CHANNEL					_ERR_CODE(12)           // 关闭通道失败错误
#define NET_ERR_NO_CHANNEL						_ERR_CODE(13)           // 通道数为0错误
#define NET_ERR_DEC_OPEN						_ERR_CODE(14)           // 打开解码库错误
#define NET_ERR_DEC_CLOSE						_ERR_CODE(15)           // 关闭解码库错误
#define NET_ERR_REAL_DATA_ALREADY_SAVED         _ERR_CODE(16)           // 实时数据已保存的错误
#define NET_ERR_REAL_DATA_NOT_SAVED             _ERR_CODE(17)           // 实时数据未保存的错误
#define NET_ERR_OPEN_FILE						_ERR_CODE(18)           // 打开文件错误
#define NET_ERR_RETURN_VERIFY                   _ERR_CODE(19)           // 返回数据校验错误
#define NET_ERR_BUFFER_NOT_ENOUGH               _ERR_CODE(20)           // 缓存不足错误
#define NET_ERR_NOT_SUPPORT                     _ERR_CODE(21)           // 未支持错误
#define NET_ERR_RECORD_NOT_FOUND                _ERR_CODE(22)           // 查询不到录像错误
#define NET_ERR_BUSY                            _ERR_CODE(23)			// 进程/线程正忙错误
#define NET_ERR_NO_TALK_CHANNEL                 _ERR_CODE(24)           // 未发现对讲通道错误
#define NET_ERR_NO_AUDIO                        _ERR_CODE(25)           // 未发现音频错误
#define NET_ERR_DOWNLOAD_END                    _ERR_CODE(26)           // 下载已结束错误
#define NET_ERR_EMPTY_LIST                      _ERR_CODE(27)           // 查询结果为空错误
#define NET_ERR_AUDIO_ENCODE_NOT_INIT           _ERR_CODE(28)           // 音频编码接口没有成功初始化的错误
#define NET_ERR_DATA_TOO_LONG                   _ERR_CODE(29)           // 数据过长的错误
#define NET_ERR_OPT_NOT_SUPPORT					_ERR_CODE(30)           // 设备不支持该操作的错误
#define NET_ERR_RESOURCE_NOT_ENOUGH             _ERR_CODE(31)           // 设备资源不足的错误
#define NET_ERR_SERVER_STARTED					_ERR_CODE(32)           // 服务器已经启动的错误
#define NET_ERR_SERVER_STOPPED                  _ERR_CODE(33)           // 服务器尚未成功启动的错误
#define NET_ERR_INPUT_SERIAL					_ERR_CODE(34)           // 输入序列号有误的错误
#define NET_ERR_QUERY_DISK_INFO					_ERR_CODE(35)           // 获取硬盘信息失败的错误
#define NET_ERR_USER_PWD_TRYTIME				_ERR_CODE(36)           // 输入密码错误超过限制次数的错误
#define NET_ERR_NOT_SUPPORT_SUB_PARTITION       _ERR_CODE(37)			// 不支持网络硬盘分区的错误
#define NET_ERR_GET_AUTO_REG_SERVER             _ERR_CODE(38)			// 获取设备上主动注册服务器信息失败的错误
#define NET_ERR_CONTROL_AUTO_REGISTER			_ERR_CODE(39)			// 主动注册重定向注册错误的错误
#define NET_ERR_DISCONNECT_AUTO_REGISTER		_ERR_CODE(40)			// 断开主动注册服务器错误的错误
#define NET_ERR_CONNECT_FAIL					_ERR_CODE(41)			// 请求建立连接失败的错误
#define NET_ERR_QUERY_SERIAL_PORT               _ERR_CODE(42)			// 查询串口参数失败的错误
#define NET_ERR_LOGOUT							_ERR_CODE(43)			// 登出设备的错误
#define NET_ERR_GET_REQUEST_DATA				_ERR_CODE(44)			// 设备无法获取当前请求数据
#define NET_ERR_MAC_VALIDATE					_ERR_CODE(45)			// MAC地址验证失败 
#define NET_ERR_GET_SERVER_INSTANCE             _ERR_CODE(46)			// 获取服务器实例失败
#define NET_ERR_JSON_REQUEST					_ERR_CODE(47)			// 生成的json字符串错误
#define NET_ERR_JSON_RESPONSE					_ERR_CODE(48)			// 响应的json字符串错误
#define NET_ERR_VERSION_HIGHER					_ERR_CODE(49)			// 协议版本低于当前使用的版本
#define NET_ERR_SPARE_NO_CAPACITY               _ERR_CODE(50)			// 热备操作失败, 容量不足
#define NET_ERR_DISPLAY_SOURCE_OCCUPPIED        _ERR_CODE(51)			// 显示源被其他输出占用
#define NET_ERR_REAVE							_ERR_CODE(52)			// 高级用户抢占低级用户资源
#define NET_ERR_NET_FORBID						_ERR_CODE(53)			// 禁止入网 
#define NET_ERR_OPERATE_OVERTIME				_ERR_CODE(54)			// 当前操作超时 
#define NET_ERR_SENIOR_VALIDATE_FAIL			_ERR_CODE(55)			// 高级校验失败 
#define NET_ERR_DEVICE_ID_NOT_EXIST				_ERR_CODE(56)			// 设备ID不存在
#define NET_ERR_PROXY_DLL_LOAD					_ERR_CODE(57)			// 代理库加载失败
#define NET_ERR_PROXY_ILLEGAL_PARAM				_ERR_CODE(58)			// 代理用户参数不合法
#define NET_ERR_PROXY_INVALID_HANDLE			_ERR_CODE(59)			// 代理句柄无效
#define NET_ERR_PROXY_LOGIN_DEVICE				_ERR_CODE(60)			// 代理登入前端设备失败
#define NET_ERR_PROXY_START_SERVER				_ERR_CODE(61)			// 启动代理服务失败
#define NET_ERR_SPEAK_FAIL						_ERR_CODE(62)			// 请求喊话失败
#define NET_ERR_CD_NOT_READY                    _ERR_CODE(63)			// 光盘未就绪
#define NET_ERR_DIR_NOT_EXIST					_ERR_CODE(64)			// 目录不存在
#define NET_ERR_SPLIT_MODE_NOT_SUPPORT			_ERR_CODE(65)			// 设备不支持的分割模式
#define NET_ERR_OPEN_WND_PARAM					_ERR_CODE(66)			// 打开窗口参数不合法
#define NET_ERR_LIMITED_WND_COUNT				_ERR_CODE(67)			// 打开窗口数量超过限制
#define NET_ERR_REQUEST_NOT_MATCH				_ERR_CODE(68)			// 请求命令与当前模式不匹配
#define NET_ERR_UPGRADE_FAIL					_ERR_CODE(69)			// 设备升级失败
#define NET_ERR_NO_TARGET_DEVICE				_ERR_CODE(70)			// 找不到目标设备
#define NET_ERR_NO_VERIFY_DEVICE				_ERR_CODE(71)			// 找不到验证设备
#define NET_ERR_CASCADE_NO_AUTHORIZED           _ERR_CODE(72)			// 无级联权限
#define NET_ERR_LOW_PRIORITY					_ERR_CODE(73)			// 低优先级
#define NET_ERR_REMOTE_REQUEST_TIMEOUT			_ERR_CODE(74)			// 远程设备请求超时
#define NET_ERR_LIMITED_INPUT_SOURCE			_ERR_CODE(75)			// 输入源超出最大路数限制
#define NET_ERR_SET_LOG_PRINT					_ERR_CODE(76)			// 设置日志打印失败
#define NET_ERR_PARAM_SIZE						_ERR_CODE(77)			// 入参的dwsize字段出错
#define NET_ERR_LIMITED_MONITOR_WALL_COUNT		_ERR_CODE(78)			// 电视墙数量超过上限
#define NET_ERR_ACCESS_FILE						_ERR_CODE(79)			// 访问文件失败
#define NET_ERR_DEVICE_STATUS_BUSY				_ERR_CODE(80)			// 设备正忙
#define NET_ERR_CTRL_DECODER_TOUR				_ERR_CODE(81)			// 控制解码器解码轮巡失败
#define NET_ERR_GROUP_SUPPORT_NUM_EXCEED        _ERR_CODE(82)			// 超出设备支持最大用户组数目
#define NET_ERR_USER_SUPPORT_NUM_EXCEED         _ERR_CODE(83)			// 超出设备支持最大用户数目
#define NET_ERR_FILE_NOT_FOUND					_ERR_CODE(84)           // 查询不到文件错误

#define NET_ERR_MEMORY							_ERR_CODE(100)			// 内存错误

#define NET_ERR_LOCAL_FILE_NOT_EXIST			_ERR_CODE(120)			// 本地文件不存在
#define NET_ERR_LOCAL_FILE_ACCESS				_ERR_CODE(121)			// 本地文件访问错误
#define NET_ERR_LOCAL_FILE_SAVE					_ERR_CODE(122)			// 本地文件保存错误

#define NET_ERR_FACE_GROUP_CREATE				_ERR_CODE(125)			// 创建人脸库失败
#define NET_ERR_FACE_GROUP_DELETE				_ERR_CODE(126)			// 删除人脸库失败
#define NET_ERR_FACE_GROUP_EDIT					_ERR_CODE(127)			// 编辑人脸库失败
#define NET_ERR_FACE_GROUPS_GET					_ERR_CODE(128)			// 获取所有人脸库信息失败
#define NET_ERR_PERSON_INFO_UPDATE				_ERR_CODE(129)			// 人员信息更新失败
#define NET_ERR_PERSON_INFO_DELETE				_ERR_CODE(130)			// 删除人员信息
#define NET_ERR_PERSON_INFO_ADD					_ERR_CODE(131)			// 添加人脸信息和人脸图片失败
#define NET_ERR_FACE_IMAGE_ADD					_ERR_CODE(132)			// 添加人脸图片失败
#define NET_ERR_FACE_IMAGE_DELETE				_ERR_CODE(133)			// 删除人脸图片失败
#define NET_ERR_FACE_IMAGE_UPDATE				_ERR_CODE(134)			// 更新人脸图片失败
#define NET_ERR_FACE_BIND						_ERR_CODE(135)			// 绑定人脸到人脸库失败
#define NET_ERR_FACE_UNBIND						_ERR_CODE(136)			// 人脸从人脸库解绑失败
#define NET_ERR_FI_UPDATE_INSTANCE_CREATE		_ERR_CODE(137)			// 人脸信息更新句柄创建失败
#define NET_ERR_FI_UPDATE_INSTANCE_DELETE		_ERR_CODE(138)			// 人脸信息更新句柄销毁失败
#define NET_ERR_FACE_FEATRUE_EXTRACT			_ERR_CODE(139)			// 抽取人脸特征失败				
#define NET_ERR_FACE_FIND_HANDLE_CREATE			_ERR_CODE(140)			// 人脸查找句柄创建失败
#define NET_ERR_FACE_FIND_HANDLE_CLOSE			_ERR_CODE(141)			// 人脸查找句柄关闭失败
#define NET_ERR_FACE_FIND_HANDLE_DESTROY		_ERR_CODE(142)			// 人脸查找句柄销毁失败
#define NET_ERR_FACE_PRE_FIND					_ERR_CODE(143)			// 预查找人脸信息失败
#define NET_ERR_FACE_QUERY_NO_RESULT			_ERR_CODE(144)			// 查询人脸信息无结果
#define NET_ERR_PERSON_COUNT_QUERY				_ERR_CODE(145)			// 获取查询条件下人员数失败
#define NET_ERR_FACE_COUNT_QUERY				_ERR_CODE(146)			// 获取查询条件下人脸数目失败				
#define NET_ERR_PERSON_INFO_QUERY				_ERR_CODE(147)			// 查询人员信息失败
#define NET_ERR_FACE_IMAGE_INFO_QUERY			_ERR_CODE(148)			// 查询人脸图像信息失败
#define NET_ERR_FACE_IMAGE_GET					_ERR_CODE(149)			// 获取人脸图像失败
#define NET_ERR_PERSON_NAME_CHECK				_ERR_CODE(150)			// 人名检测失败
#define NET_ERR_FACE_REC_REC_FIND_HANDLE_CREATE	_ERR_CODE(151)			// 人脸比对记录查找句柄创建失败
#define NET_ERR_FACE_REC_REC_FIND_HANDLE_CLOSE	_ERR_CODE(152)			// 人脸比对记录查找句柄关闭失败
#define NET_ERR_FACE_REC_REC_FIND_HANDLE_DESTROY	_ERR_CODE(153)		// 人脸比对记录查找句柄销毁失败
#define NET_ERR_FACE_REC_REC_PRE_FIND			_ERR_CODE(154)			// 预查询人脸比对结果失败
#define NET_ERR_FACE_REC_REC_QUERY_NO_RESULT	_ERR_CODE(155)			// 查询人脸比对结果失败
#define NET_ERR_FACE_REC_REC_COUNT_QUERY		_ERR_CODE(156)			// 查询获取人脸比对结果数目失败

#define NET_ERR_TALK_REJECT						_ERR_CODE(160)          // 拒绝对讲
#define NET_ERR_TALK_ALREADY_OPEN               _ERR_CODE(161)          // 对讲被其他客户端打开
#define NET_ERR_TALK_RESOURCE_CONFLICIT			_ERR_CODE(162)          // 资源冲突
#define NET_ERR_TALK_ENCODE_NOT_SUPPORTED       _ERR_CODE(163)          // 不支持的语音编码格式
#define NET_ERR_TALK_NO_AUTHORIZED              _ERR_CODE(164)          // 无权限
#define NET_ERR_TALK_FAIL						_ERR_CODE(165)          // 请求对讲失败

#define NET_ERR_LOGIN_PWD						_ERR_CODE(201)          // 密码不正确的错误
#define NET_ERR_LOGIN_USER						_ERR_CODE(202)          // 帐户不存在的错误
#define NET_ERR_LOGIN_TIMEOUT					_ERR_CODE(203)          // 等待登录返回超时的错误
#define NET_ERR_LOGIN_RELOGIN					_ERR_CODE(204)          // 帐号已登录的错误
#define NET_ERR_LOGIN_LOCKED					_ERR_CODE(205)          // 帐号已被锁定的错误
#define NET_ERR_LOGIN_BLACKLIST					_ERR_CODE(206)          // 帐号已被列为黑名单的错误
#define NET_ERR_LOGIN_BUSY						_ERR_CODE(207)          // 资源不足，系统忙的错误
#define NET_ERR_LOGIN_CONNECT					_ERR_CODE(208)          // 登录设备超时的错误
#define NET_ERR_LOGIN_NETWORK					_ERR_CODE(209)          // 网络连接失败
#define NET_ERR_LOGIN_SUB_CONNECT				_ERR_CODE(210)          // 子链接（如视频拉流链接）失败的错误
#define NET_ERR_LOGIN_MAX_CONNECT				_ERR_CODE(211)          // 超过最大连接数的错误
#define NET_ERR_LOGIN_NO_AUTHORIZED				_ERR_CODE(212)          // 客户端IP地址没有登录权限的错误 
#define NET_ERR_LOGIN_USER_PWD					_ERR_CODE(213)			// 登录用户名或密码错误
#define NET_ERR_LOGIN_PEER_BLOCKED				_ERR_CODE(214)			// 用户登录被阻塞

#define NET_ERR_RENDER_AUDIO_ON					_ERR_CODE(240)          // Render库打开音频出错的错误
#define NET_ERR_RENDER_AUDIO_OFF				_ERR_CODE(241)          // Render库关闭音频出错的错误
#define NET_ERR_RENDER_SET_VOLUME				_ERR_CODE(242)          // Render库控制音量出错的错误
#define NET_ERR_RENDER_ADJUST					_ERR_CODE(243)          // Render库设置画面参数出错的错误
#define NET_ERR_RENDER_PAUSE					_ERR_CODE(245)          // Render库暂停播放出错的错误
#define NET_ERR_RENDER_SNAP						_ERR_CODE(246)          // Render库抓图出错的错误
#define NET_ERR_RENDER_STEP						_ERR_CODE(247)          // Render库步进出错的错误
#define NET_ERR_RENDER_FRAMERATE				_ERR_CODE(248)          // Render库设置帧率出错的错误
#define NET_ERR_RENDER_DISPLAY_REGION			_ERR_CODE(249)          // Render库设置显示区域出错的错误
#define NET_ERR_RENDER_HPIC_ADJUST_ENABLE		_ERR_CODE(250)			// Render库高清图像调整策略使能错误
#define NET_ERR_RENDER_PRIVATE_DATA				_ERR_CODE(251)			// Render库使能绘制智能数据错误

#define NET_ERR_GROUP_EXIST                     _ERR_CODE(280)          // 组名已存在的错误
#define NET_ERR_GROUP_NOT_EXIST                 _ERR_CODE(281)          // 组名不存在的错误
#define NET_ERR_GROUP_RIGHT_OVER				_ERR_CODE(282)          // 组的权限超出权限列表范围的错误
#define NET_ERR_GROUP_USER_EXIST                _ERR_CODE(283)          // 组下有用户，不能删除的错误
#define NET_ERR_GROUP_RIGHT_NOT_RELEASE         _ERR_CODE(284)          // 组的某个权限被用户占用，不能删除的错误
#define NET_ERR_GROUP_SAME_NAME					_ERR_CODE(285)          // 新组名同已有组名重复的错误

#define NET_ERR_USER_EXIST						_ERR_CODE(300)          // 用户已存在的错误
#define NET_ERR_USER_NOEXIST                    _ERR_CODE(301)          // 用户不存在的错误
#define NET_ERR_USER_RIGHT_EXCEED               _ERR_CODE(302)          // 用户权限超出组权限的错误
#define NET_ERR_USER_PWD                        _ERR_CODE(303)          // 保留帐号，不容许修改密码的错误
#define NET_ERR_USER_WRONG_PWD                  _ERR_CODE(304)          // 密码不正确的错误
#define NET_ERR_USER_PWD_NOT_MATCH              _ERR_CODE(305)          // 密码不匹配的错误
#define NET_ERR_USER_WORKING                    _ERR_CODE(306)          // 账号正在使用中的错误

#define NET_ERR_CFG_DATA_ILLEGAL                _ERR_CODE(360)          // 配置数据不合法的错误
#define NET_ERR_CFG_BUSY						_ERR_CODE(361)          // 暂时无法设置的错误

#define NET_ERR_GET_SYS_ATTRI_CFG               _ERR_CODE(370)          // 获取系统属性配置失败的错误
#define NET_ERR_GET_SERIAL_NUMBER               _ERR_CODE(371)          // 获取序列号失败的错误
#define NET_ERR_GET_GENERAL_CFG					_ERR_CODE(371)          // 获取常规属性失败的错误
#define NET_ERR_GET_DSP_CAP_CFG                 _ERR_CODE(373)          // 获取DSP能力描述失败的错误
#define NET_ERR_GET_NET_CFG						_ERR_CODE(374)          // 获取网络配置失败的错误
#define NET_ERR_GET_CHANNEL_NAME_CFG            _ERR_CODE(375)          // 获取通道名称失败的错误
#define NET_ERR_GET_VIDEO_CFG					_ERR_CODE(376)          // 获取视频属性失败的错误
#define NET_ERR_GET_RECORD_CFG					_ERR_CODE(377)			// 获取录像配置失败的错误
#define NET_ERR_GET_DEC_PROTOCOL_NAME_CFG       _ERR_CODE(378)          // 获取解码器协议名称失败的错误
#define NET_ERR_GET_232_FUNC_NAME_CFG           _ERR_CODE(379)          // 获取232串口功能名称失败的错误
#define NET_ERR_GET_485_DECODER_CFG             _ERR_CODE(380)          // 获取解码器属性失败的错误
#define NET_ERR_GET_232_CFG						_ERR_CODE(381)          // 获取232串口配置失败的错误
#define NET_ERR_GET_ALARM_IN_CFG                _ERR_CODE(382)          // 获取外部报警输入配置失败的错误
#define NET_ERR_GET_ALARM_DETECT_CFG            _ERR_CODE(383)          // 获取动态检测报警失败的错误
#define NET_ERR_GET_SYSTIME_CFG					_ERR_CODE(384)          // 获取设备时间失败的错误
#define NET_ERR_GET_PREVIEW_CFG					_ERR_CODE(385)          // 获取预览参数失败的错误
#define NET_ERR_GET_AUTO_MAINTAIN_CFG           _ERR_CODE(386)          // 获取自动维护配置失败的错误
#define NET_ERR_GET_VIDEO_MTRIX_CFG             _ERR_CODE(387)          // 获取视频矩阵配置失败的错误
#define NET_ERR_GET_COVER_CFG					_ERR_CODE(388)          // 获取区域遮挡配置失败的错误
#define NET_ERR_GET_WATERMARK_CFG				_ERR_CODE(389)          // 获取图像水印配置失败的错误
#define NET_ERR_GET_MULTICAST_CFG				_ERR_CODE(390)          // 获取组播端口按通道配置失败的错误
#define NET_ERR_GET_SESSION_CFG					_ERR_CODE(391)          // 获取连接Session信息的错误
#define NET_ERR_GET_ETHERNET_CFG				_ERR_CODE(392)          // 获取网卡配置失败的错误
#define NET_ERR_GET_WLAN_CFG					_ERR_CODE(393)          // 获取无线网络信息失败的错误
#define NET_ERR_GET_WLAN_DEVICE_CFG             _ERR_CODE(394)          // 获取无线网络设备失败的错误
#define NET_ERR_GET_REGISTER_CFG				_ERR_CODE(395)          // 获取主动注册参数失败的错误
#define NET_ERR_GET_CAMERA_CFG					_ERR_CODE(396)          // 获取摄像头属性失败的错误
#define NET_ERR_GET_INFRARED_CFG				_ERR_CODE(397)          // 获取红外报警配置失败的错误
#define NET_ERR_GET_AUDIO_ALARM_CFG             _ERR_CODE(398)          // 获取音频报警配置失败的错误
#define NET_ERR_GET_STORAGE_CFG					_ERR_CODE(399)          // 获取存储位置配置失败的错误
#define NET_ERR_GET_MAIL_CFG					_ERR_CODE(400)          // 获取邮件配置失败的错误
#define NET_ERR_GET_TIME_DST_CFG                _ERR_CODE(401)          // 获取夏令时配置失败的错误
#define NET_ERR_GET_VIDEO_OSD_CFG				_ERR_CODE(402)          // 获取视频OSD叠加配置失败的错误
#define NET_ERR_GET_GPRS_CDMA_CFG               _ERR_CODE(403)          // 获取CDMA\GPRS网络配置失败的错误
#define NET_ERR_GET_IP_FILTER_CFG               _ERR_CODE(404)          // 获取IP过滤配置失败的错误
#define NET_ERR_GET_TALK_ENCODE_CFG             _ERR_CODE(405)          // 获取语音对讲编码配置失败的错误
#define NET_ERR_GET_RECORD_LENGTH_CFG           _ERR_CODE(406)          // 获取录像打包长度配置失败的错误
#define NET_ERR_GET_VIDEO_OUT_CFG               _ERR_CODE(407)          // 查询视频输出参数配置失败的错误
#define NET_ERR_GET_OSD_ENABLE_CFG              _ERR_CODE(408)          // 获取osd叠加使能配置失败的错误
#define NET_ERR_GET_TV_ADJUST_CFG               _ERR_CODE(409)          // 获取TV调节配置失败的错误
#define NET_ERR_GET_SNIFFER_CFG					_ERR_CODE(410)          // 获取抓包配置信息失败的错误
#define NET_ERR_GET_DOWNLOAD_RATE_CFG           _ERR_CODE(411)          // 查询下载限制信息失败的错误
#define NET_ERR_GET_POINT_CFG					_ERR_CODE(412)          // 获取预制点信息错误的错误
#define NET_ERR_GET_VEHICLE_CFG					_ERR_CODE(413)          // 获取车载配置失败的错误
#define NET_ERR_GET_DECODER_TOUR_CFG			_ERR_CODE(414)          // 获取解码器解码轮巡配置失败
#define NET_ERR_GET_SIP_CFG						_ERR_CODE(415)          // 获取SIP配置失败
#define NET_ERR_GET_SIP_CAPS					_ERR_CODE(416)          // 获取SIP能力失败
#define NET_ERR_GET_WIFI_AP_CFG					_ERR_CODE(417)          // 获取WIFI ap配置失败
#define NET_ERR_GET_DECODE_STRATEGY_CFG         _ERR_CODE(418)          // 获取解码策略配置失败
#define NET_ERR_GET_MACHINE_CFG					_ERR_CODE(419)          // 获取机器相关配置失败
#define NET_ERR_GET_MAC_FILTER_CFG              _ERR_CODE(420)          // 获取MAC过滤配置失败
#define NET_ERR_GET_IP_MAC_FILTER_CFG           _ERR_CODE(421)          // 获取IP/MAC过滤配置失败

#define NET_ERR_SET_GENERAL_CFG					_ERR_CODE(480)          // 修改常规属性失败的错误
#define NET_ERR_SET_NET_CFG						_ERR_CODE(481)          // 修改网络配置失败的错误
#define NET_ERR_SET_CHANNEL_NAME_CFG            _ERR_CODE(482)          // 修改通道名称失败的错误
#define NET_ERR_SET_VIDEO_CFG					_ERR_CODE(483)          // 修改视频属性失败的错误
#define NET_ERR_SET_RECORD_CFG					_ERR_CODE(484)          // 修改录像配置失败的错误
#define NET_ERR_SET_485_DECODER_CFG             _ERR_CODE(485)          // 修改解码器属性失败的错误
#define NET_ERR_SET_232_CFG						_ERR_CODE(486)          // 修改232串口配置失败的错误
#define NET_ERR_SET_ALARM_IN_CFG                _ERR_CODE(487)          // 修改外部输入报警配置失败的错误
#define NET_ERR_SET_ALARM_DETECT_CFG            _ERR_CODE(488)          // 修改动态检测报警配置失败的错误
#define NET_ERR_SET_SYSTIME_CFG					_ERR_CODE(489)          // 修改设备时间失败的错误
#define NET_ERR_SET_PREVIEW_CFG					_ERR_CODE(490)          // 修改预览参数失败的错误
#define NET_ERR_SET_AUTO_MAINTAIN_CFG           _ERR_CODE(491)          // 修改自动维护配置失败的错误
#define NET_ERR_SET_VIDEO_MTRIX_CFG             _ERR_CODE(492)          // 修改视频矩阵配置失败的错误
#define NET_ERR_SET_COVER_CFG					_ERR_CODE(493)          // 修改区域遮挡配置失败的错误
#define NET_ERR_SET_WATERMARK_CFG				_ERR_CODE(494)			// 修改图像水印配置失败的错误
#define NET_ERR_SET_WLAN_CFG					_ERR_CODE(495)          // 修改无线网络信息失败的错误
#define NET_ERR_SET_WLAN_DEVICE_CFG             _ERR_CODE(496)          // 选择无线网络设备失败的错误
#define NET_ERR_SET_REGISTER_CFG				_ERR_CODE(497)          // 修改主动注册参数配置失败的错误
#define NET_ERR_SET_CAMERA_CFG					_ERR_CODE(498)          // 修改摄像头属性配置失败的错误
#define NET_ERR_SET_INFRARED_CFG				_ERR_CODE(499)          // 修改红外报警配置失败的错误
#define NET_ERR_SET_AUDIO_ALARM_CFG             _ERR_CODE(500)          // 修改音频报警配置失败的错误
#define NET_ERR_SET_STORAGE_CFG					_ERR_CODE(501)          // 修改存储位置配置失败的错误
#define NET_ERR_SET_TIME_DST_CFG                _ERR_CODE(502)          // 设置夏令时配置失败的错误
#define NET_ERR_SET_VIDEO_OSD_CFG				_ERR_CODE(503)          // 设置视频OSD叠加配置失败的错误
#define NET_ERR_SET_GPRS_CDMA_CFG               _ERR_CODE(504)          // 设置CDMA\GPRS网络配置失败的错误
#define NET_ERR_SET_IP_FILTER_CFG               _ERR_CODE(505)          // 设置IP过滤配置失败的错误
#define NET_ERR_SET_TALK_ENCODE_CFG             _ERR_CODE(506)          // 设置语音对讲编码配置失败的错误
#define NET_ERR_SET_RECORD_LENGTH_CFG           _ERR_CODE(507)          // 设置录像打包长度配置失败的错误
#define NET_ERR_SET_VIDEO_OUT_CFG               _ERR_CODE(508)          // 设置视频输出参数配置失败的错误
#define NET_ERR_SET_OSD_ENABLE_CFG              _ERR_CODE(509)          // 设置osd叠加使能配置失败的错误
#define NET_ERR_SET_ENCODER_INFO_CFG            _ERR_CODE(510)          // 设置数字通道前端编码接入配置失败的错误
#define NET_ERR_SET_IP_MAC_FILTER_CFG           _ERR_CODE(511)          // 设置IP/MAC过滤配置失败
#define NET_ERR_SET_TV_ADJUST_CFG               _ERR_CODE(512)          // 设置TV调节配置失败的错误
#define NET_ERR_SET_BURN_FILE_CFG               _ERR_CODE(513)          // 请求刻录文件上传失败的错误
#define NET_ERR_SET_SNIFFER_CFG					_ERR_CODE(514)          // 设置抓包配置信息失败的错误
#define NET_ERR_SET_DOWNLOAD_RATE_CFG           _ERR_CODE(515)          // 设置下载限制信息失败的错误
#define NET_ERR_SET_POINT_CFG					_ERR_CODE(516)          // 设置预制点信息错误的错误
#define NET_ERR_SET_VEHICLE_CFG					_ERR_CODE(517)          // 设置车载配置失败的错误
#define NET_ERR_SET_ATM_OVERLAY_CFG				_ERR_CODE(518)          // 设置atm叠加配置失败的错误
#define NET_ERR_SET_DECODER_TOUR_CFG			_ERR_CODE(519)          // 设置解码器解码轮巡配置失败
#define NET_ERR_SET_SIP_CFG						_ERR_CODE(520)          // 设置SIP配置失败
#define NET_ERR_SET_WIFI_AP_CFG					_ERR_CODE(521)          // 设置WIFI ap配置失败
#define NET_ERR_SET_DECODE_STRATEGY_CFG         _ERR_CODE(522)          // 设置解码策略配置失败
#define NET_ERR_SET_MACHINE_CFG					_ERR_CODE(523)          // 设置机器相关配置失败
#define NET_ERR_SET_MAC_FILTER_CFG              _ERR_CODE(524)          // 设置MAC过滤配置失败

#endif // _AL_NET_DEF_COLLECTION_H