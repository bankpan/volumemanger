#ifndef _CSPAPI_
#define _CSPAPI_

#include "hserr.h"
#include "windows.h"
//////////////////////////////////////////////////////////////////////////
//Add by jpf 2009.04.27
#define HT_DES_KEY						1				// DES密钥，密钥长8字节
#define HT_3DES_112_KEY					2				// 3DES_112密钥，密钥长16字节
#define HT_SSF33_KEY					3				// SSF33，密钥长16字节
#define HT_SCB2_KEY						4				// SCB2, 密钥长32字节，2个密钥：E Key, A Key

#define ENCRYPT_MODE					1				//加密
#define DECRYPT_MODE					2				//解密
//End add jpf 2009.04.27

//常量定义
#define HS_SERIAL_LEN					0x08

//用户自定义文件ID
#define HS_MIN_FILE_ID					0x0000
#define HS_MAX_FILE_ID					0xFFFF

//用户自定义文件大小
#define HS_MIN_FILE_SIZE				0x0000
#define HS_MAX_FILE_SIZE				0x8000-3	// 文件的最大长度,32K-3,3字节为内部管理文件用

//可以创建自定义文件的最多个数
#define HS_MAX_FILES_NUM				50

//文件权限
#define HS_DELETE_RIGHT					0x01
#define HS_READ_RIGHT					0x02
#define HS_WRITE_RIGHT					0x03

//权限类型
#define HT_NEEDNT_PIN					0x00
#define HT_SO_PIN						0x01
#define HT_USER_PIN						0x02

//设备状态
#define HGS_STATE_EMPTY					0x0010
#define HGS_STATE_PRESENT				0x0020

//文件状态
#define HT_FILE_NOT_EXIST				0x00
#define HT_FILE_EXIST					0x01


//设备应用格式
#define HT_UNKNOWN_APP					0x00000000

#define HT_CSP_APP						0x00000001

#define HT_SEC_APP						0x00000004

#define HT_ALL_APP						0x00000005

#define HT_BLANK_HW						0x80000000

#define HT_MAYBE_BAD_HW					0x40000000

// 密钥容器属性
#define HC_EXCHANGE_KEY_EXISTING		0x00000001		// 加密密钥已存在
#define HC_EXCHANGE_CERT_EXISTING		0x00000003		// 加密证书已存在	
#define HC_SIGN_KEY_EXISTING			0x00010000		// 签名密钥已存在
#define HC_SIGN_CERT_EXISTING			0x00030000		// 签名证书已存在

//////////////////////////////////////////////////////////////////////////
//结构定义

//文件结构定义
//dwFileID: 文件ID
//dwDeleteRight: 文件的删除权限
//dwReadRight: 文件的读权限
//dwWriteRight: 文件的写权限
//dwFileLen: 文件的大小，取值为 0<dwFileLen<=MAX_FILE_LEN
//文件结构定义
typedef struct _HS_FILEINFO
{
    DWORD  dwFileID;
    DWORD dwDeleteRight;
	DWORD dwReadRight;
	DWORD dwWriteRight;
	DWORD dwFileSize;
    DWORD dwReserved1;
    DWORD dwReserved2;
}HS_FILEINFO, *PHS_FILEINFO;

//密钥结构定义
//dwKeyType: 密钥类型HT_SSF33_KEY、HT_SCB2_KEY
//*pbKey：密钥值
//dwKeyLen: 密钥长度
//dwUserRight: 密钥的使用权限，可以为HT_SO_PIN、HT_USER_PIN或HT_NEEDNT_PIN之一 ,
//				该参数对于临时密钥加解密函数时被忽略
//dwReserved: 保留值
typedef struct _HS_KEYINFO
{
	DWORD dwKeyType;
	DWORD dwKeyID;	//0: session key, 0x01~0x0F: perpetual key which written in device.
	BYTE *pbKey;
	DWORD dwKeyLen;
	DWORD dwUseRight;
	DWORD dwReserved;
}HS_KEYINFO, *PHS_KEYINFO;

//格式化结构定义
//szLabel: 设备标识名称，长度为1-32字节
//szSOPin: 管理员口令，长度为1-16字节
//dwSOPinRetry: 管理员口令重试次数
//szUserPin: 用户口令，长度为1-16字节
//dwUserPinRetry: 用户口令重试次数
typedef struct _HS_FORMATINFO
{
	LPCSTR szLabel;
	LPCSTR szSOPin;
	DWORD dwSOPinRetry;
	LPCSTR szUserPin;
	DWORD dwUserPinRetry;
	DWORD dwReserved;
}HS_FORMATINFO, *PHS_FORMATINFO;

typedef struct _HS_CERTINFO
{
	char szSubjectCN[256];
	char szSubjectO[256];
	char szSubjectOU[256];
	char szSubjectL[256];
	char szSubjectC[256];
	char szSubjectS[256];
	char szIssuer[256];
	char szBeginTime[256];
	char szEndTime[256];
	char szSerialNumber[256];
}HS_CERTINFO, *PHS_CERTINFO;
//////////////////////////////////////////////////////////////////////////
//设备插入处理函数原型，参见函数 HKSetDevChgFunc
typedef DWORD (__stdcall *DEVINSERTED)(IN void *pParam);//输入，设备插入处理函数的参数
//设备拔除处理函数原型，参见函数 HKSetDevChgFunc
typedef DWORD (__stdcall *DEVREMOVED)(IN void *pParam);//输入，设备拔除处理函数的参数


#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////
//		设备管理类
//////////////////////////////////////////////////////////////////////////

//取所有读写器名字
//pszReaderName: 输出，多字符串，所有读写器的名称，
	//如果该值为NULL, 由pdwReaderNameLen返回读写器名字的长度
//pdwReaderNameLen:输入：缓冲区的长度，输出：读写器名称的长度，
//pdwReaderNum:输出，返回读写器的总个数
//返回0成功，其他失败
DWORD _stdcall HSListReaders
(
	OUT LPSTR pszReaderName,
	IN	OUT DWORD *pdwReaderNameLen,
	OUT DWORD *pdwReaderNum
);

//指定读写器名，注册相应的设备插拔处理函数
//szReaderName：输入，读写器名称
//InsertProc：输入，设备插入处理函数
//RemoveProc：输入，设备拔除处理函数
//pProcParam：输入，设备插拔处理函数的参数
//phEvtHandler：输出，插拔事件处理句柄
//返回0成功，其他失败
DWORD _stdcall HSSetDevChgEvent
(
	IN LPCSTR szReaderName,
	IN DEVINSERTED InsertProc,
	IN DEVREMOVED RemoveProc,
	IN void *pProcParam,
	OUT HANDLE *phEvtHandler
);

//以插拔事件处理句柄注册设备的插拔处理函数或其参数
//hEvtHandler：输入，插拔事件处理句柄
//InsertProc：输入，设备插入处理函数
//RemoveProc：输入，设备拔除处理函数
//pProcParam：输入，设备插拔处理函数的参数
//返回0成功，其他失败
DWORD _stdcall HSSetDevChgEventParam
(
	IN HANDLE hEvtHandler,    
	IN DEVINSERTED InsertProc,
	IN DEVREMOVED RemoveProc, 
	IN void *pProcParam
);

//获取读写器状态
//szReaderName: 输入，读写器名称
//pdwState:输出，读卡器状态. 
	//HGS_STATE_EMPTY 读卡器中没有设备 
	//HGS_STATE_PRESENT 读卡器中有设备
//返回0成功，其他失败
DWORD _stdcall HSGetDevState
(
	IN  LPCSTR szReaderName,
	OUT DWORD *pdwState
);

//根据可用设备名连接到一个Haikey设备
//szDevName: 输入，可用设备名
//phCard: 输出，设备的操作句柄
//返回0成功，其他失败
DWORD _stdcall HSConnectDev
(
	IN LPCSTR szDevName,
	OUT HANDLE *phCard
);

//断开设备
//hCard: 输入，设备的操作句柄
//返回0成功，其他失败
DWORD _stdcall HSDisconnectDev
(
	IN HANDLE hCard
);

//开始执行事务处理，即请求以独占方式操作该设备，以支持多应用
//返回0成功，其他失败
DWORD _stdcall HSBeginTransaction
(
	IN HANDLE hCard
);

////结束当前事务处理，即终止本次对设备的独占访问，以支持多应用
//返回0成功，其他失败
DWORD _stdcall HSEndTransaction
(
	IN HANDLE hCard
);

//////////////////////////////////////////////////////////////////////////
//		文件操作
//////////////////////////////////////////////////////////////////////////

//对Haikey设备进行格式化操作，把haikey格式化成CSP应用格式的设备
//hCard: 输入，设备句柄
//hsFormatInfo: haikey格式化信息结构，具体参见结构定义
//返回0成功，其他失败
DWORD _stdcall HSFormat
(
	IN HANDLE hCard,
	IN HS_FORMATINFO hsFormatInfo
);

//对Haikey设备进行擦除操作，把haikey设备中所有结构和数据清除
//	该操作需要首先调用校验管理员口令
//hCard: 输入，设备句柄
//返回0成功，其他失败
DWORD _stdcall HSErase
(
	IN HANDLE hCard
);

//在haikey设备中创建文件
//hCard: 设备句柄
//返回0成功，其他失败
DWORD _stdcall HSCreateFile
(
	IN HANDLE hCard,
	IN HS_FILEINFO FileInfo
);

//写文件
//hCard: 输入，设备句柄
//dwFileIndex: 输入，文件ID
//pbData: 写入文件的数据
//dwDataLen: 写入数据的长度
DWORD _stdcall HSWriteFile
(
	IN HANDLE hCard,
	IN DWORD dwFileIndex,
	IN DWORD dwOffset,
	IN BYTE *pbData,
	IN DWORD dwDataLen
);

//读文件操作
//hCard: 输入设备句柄
//dwFileIndex: 输入，文件ID
//*pbData：返回读出的数据
//*pdwReadLen：输入时，表示要读的数据的长度，此时pbData应当已经分配内存；输出时，表示实际读出的数据的长度
//             当pbData为NULL时，返回该文件中所保存数据的长度
//             当*pdwReadLen==MAX_FILE_LEN且pbData!=NULL时，一定能够读出该文件的数据
//返回0成功，其他失败
DWORD _stdcall HSReadFile
(
	IN HANDLE hCard,
	IN DWORD dwFileIndex,
	IN DWORD dwOffset,
	IN BYTE *pbData,
	IN DWORD *pdwReadLen
);

//删除文件
//hCard: 输入，设备句柄
//dwFileIndex: 文件ID号
//返回0成功，其他失败
DWORD _stdcall HSDeleteFile
(
	IN HANDLE hCard,
	IN DWORD dwFileIndex
);

//获取文件的大小
//hCard: 设备的句柄
//dwFileIndex: 文件ID号
//*pdwFileSize: 返回文件的大小
//返回0成功，其他失败
DWORD _stdcall HSGetFileSize
(
	IN HANDLE hCard,
	IN DWORD dwFileIndex,
	OUT DWORD *pdwFileSize
);

//获取文件的删除
//hCard:　设备句柄
//dwFileIndex: 文件ID号
//dwRightType: 取值可以为HT_DELETE_RIGHT, HT_WRITE_RIGHT, HT_READ_RIGHT
//*pdwPinType: 返回文件的权限类型,返回值有HT_SO_PIN, HT_USER_PIN, HT_NEEDNT_PIN
// 返回0成功，其它失败
DWORD _stdcall HSGetFileRight
(
	IN HANDLE hCard,
	IN DWORD dwFileIndex,
	IN DWORD dwRightType,
	OUT DWORD *pdwPinType
);

//判断文件是否存在
//IN HANDLE hCard: 输入，设备句柄
//IN DWORD dwFileIndex: 文件ID号
//OUT DWORD *pdwFileState: 返回文件状态，返回值为HT_FILE_EXIST, HT_FILE_NOT_EXIST
//// 返回0成功，其它失败
DWORD _stdcall HSHasFileExist
(
	IN HANDLE hCard,
	IN DWORD dwFileIndex,
	OUT DWORD *pdwFileState
);
//////////////////////////////////////////////////////////////////////////
//			口令操作
//////////////////////////////////////////////////////////////////////////

//校验用户口令
//hCard: 设备句柄
//szUserPin: haikey的用户口令
//pbRetryNum: 如果口令错误，返回重试次数
// 返回0成功，其它失败
DWORD _stdcall HSVerifyUserPin
(
	IN HANDLE hCard,
	IN LPCSTR szUserPin,
	OUT DWORD *pdwRetryNum
);

//修改用户口令操作
//hCard: 设备句柄
//szOldPin: haikey原用户口令
//szNewPin: haikey新用户口令
//pbRetryNum: 如果口令错误，返回重试次数
// 返回0成功，其它失败
DWORD _stdcall HSChangeUserPin
(
	IN HANDLE hCard,
	IN LPCSTR szOldPin,
	IN LPCSTR szNewPin,
	OUT DWORD *pdwRetryNum
);

//校验管理员口令
//hCard: 设备句柄
//szSOPin：管理员口令
//pbRetryNum: 如果口令错误，返回重试次数
// 返回0成功，其它失败
DWORD _stdcall HSVerifySOPin
(
	IN HANDLE hCard,
	IN LPCSTR szSOPin,
	OUT DWORD *pdwRetryNum
);

//修改管理员口令
//hCard: 设备句柄
//szOldPin: haikey原管理员口令
//szNewPin:	haikey新管理员口令
//pbRetryNum: 如果原口令错误，返回口令的重试次数
// 返回0成功，其它失败
DWORD _stdcall HSChangeSOPin
(
	IN HANDLE hCard,
	IN LPCSTR szOldPin,
	IN LPCSTR szNewPin,
	OUT DWORD *pdwRetryNum
);

// 重新设置用户口令
//hCard: 输入，设备句柄
//szSOPin：USBKey的管理员口令
//szNewUserPin：USBKey的新的用户口令
//pbRetryNum：当USBKey的管理员口令错误时，返回管理员口令还能重试的次数
// 返回0成功，其它失败
DWORD _stdcall HSReWriteUserPin
(
	IN HANDLE hCard,	
	IN LPCSTR szSOPin,
	IN LPCSTR szNewUserPin,
	OUT DWORD *pdwRetryNum
);

//获取用户口令重试次数
//hCard: 输入，设备句柄
//pdwRetryNum:输出，用户口令重试次数
DWORD _stdcall HSGetUserPinRetryNum
(
	IN HANDLE hCard,
	OUT DWORD *pdwRetryNum
);


//获取管理员口令重试次数
//hCard: 输入，设备句柄
//pdwRetryNum:输出，管理员口令重试次数
DWORD _stdcall HSGetSOPinRetryNum
(
	IN HANDLE hCard,
	OUT DWORD *pdwRetryNum
);

//获取用户口令重试总次数
//hCard: 输入，设备句柄
//pdwRetryNum:输出，用户口令重试总次数
DWORD _stdcall HSGetUserPinRetryNumEx
(
	IN HANDLE hCard,
	OUT DWORD *pdwRetryNum
);


//获取管理员口令重试总次数
//hCard: 输入，设备句柄
//pdwRetryNum:输出，管理员口令重试总次数
DWORD _stdcall HSGetSOPinRetryNumEx
(
	IN HANDLE hCard,
	OUT DWORD *pdwRetryNum
);

//////////////////////////////////////////////////////////////////////////
//		容器证书操作
//////////////////////////////////////////////////////////////////////////

//枚举所有密钥容器的名字
//pszContainerName: 输出，多字符串，所有密钥容器的名称，
//如果该值为NULL, 由pdwContainerNameLen返回密钥容器名字的长度
//pdwContainerNameLen:输入：缓冲区的长度，输出：密钥容器名称的长度，
//pdwContainerNum:输出，返回密钥容器的总个数
//返回0成功，其他失败
DWORD _stdcall HSListContainers
(
	IN HANDLE hCard,
	OUT LPSTR pszContainersName,
	IN	OUT DWORD *pdwContainersNameLen,
	OUT DWORD *pdwContainerNum
);

//获取haikey中Container个数
//hCard: 输入，设备句柄
//pdwContainerNum: 输出，haikey中Container个数
DWORD _stdcall HSGetContainerNum
(
	IN HANDLE hCard,
	OUT DWORD *pdwContainerNum
);

//获取Container名称
//dwContainerIndex：要检索的密钥容器的索引值，0<=dwContainerIndex<=*pdwContainerNum-1
//pszContainerName：返回的密钥容器名字
//			当pszContainerName==NUL时，pdwContainerNameLen返回密钥容器名字的长度
//*pdwContainerNameLen：输入时，为pszContainerName缓冲区的长度，
//			  输出时，为密钥容器名字的长度（包括结尾的NULL字符）
//*pdwContainerParam：返回的密钥容器的属性，其值见说明??
//返回0成功，其它失败
DWORD _stdcall HSGetContainerName
(
	IN HANDLE hCard,
	IN DWORD dwContainerIndex,
	OUT LPSTR pszContainerName,
	IN OUT DWORD *pdwContainerNameLen,
	OUT DWORD *pdwContainerParam
);


//获取Container属性
//pszContainerName：密钥容器名字
//*pdwContainerParam：返回的密钥容器的属性，其值见说明
//返回0成功，其它失败
DWORD _stdcall HSGetContainerParam
(
	IN HANDLE hCard,
	IN LPCSTR pszContainerName,
	OUT DWORD *pdwContainerParam
);

//创建密钥容器,--执行该操作要首先调用校验用户口令操作
//hCard: 输入，设备句柄
//szContainerName：密钥容器名字，如果szContainerName为NULL或长度为0,则在函数内部生成GUID做为密钥容器的名字
//            密钥容器名字的长度最长为MAX_CON_NAME_LEN
// 返回0成功，其它失败
DWORD _stdcall HSCreateContainer
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName
);

//删除密钥容器--执行该操作需要提前校验用户口令
//hCard: 输入，设备句柄
//szContainerName：密钥容器名字
// 返回0成功，其它失败
DWORD _stdcall HSDelContainer
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName
);

//读证书
//szContainerName：密钥容器名字
//dwKeySpec：密钥属性，为AT_KEYEXCHANGE或AT_SIGNATURE之一
//*pbCert：返回证书数据，der编码，当pbCert==NULL时，pdwCertLen返回证书数据的长度
//*pdwCertLen：输入时，为pbCert缓冲区的长度；输出时，为证书数据的长度
// 返回0成功，其它失败
DWORD _stdcall HSReadCert
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec,
	OUT BYTE *pbCert,
	IN OUT DWORD *pdwCertLen
);

//写证书----执行该操作需要提前校验用户口令
//hCard: 输入，设备句柄
//szContainerName：密钥容器名字
//dwKeySpec：密钥属性，为AT_KEYEXCHANGE或AT_SIGNATURE之一
//*pbCert：证书数据，der编码
//dwCertLen：证书数据的长度
//返回0成功，其它失败
DWORD _stdcall HSWriteCert
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec,
	IN BYTE *pbCert,
	IN DWORD dwCertLen
);

//导Pfx/P12证书----执行该操作需要提前校验用户口令
//hCard: 输入，设备句柄
//szContainerName：密钥容器名字，如果szContainerName为NULL或长度为0,则在函数内部生成GUID做为密钥容器的名字
//                             密钥容器名字的长度最长为MAX_CON_NAME_LEN
//dwRSAKeySpec：指定证书中的RSA密钥在IE中的属性，AT_KEYEXCHANGE=1或AT_SIGNATURE=2，为其它值（如0）时使用从p12中解析出的RSA密钥属性
//*pbP12Data：PKCS#12证书数据
//dwP12DataLen：PKCS#12证书数据的长度
//szP12PWD：PKCS#12证书的保护口令
//返回0成功，其它失败
DWORD _stdcall HSImportP12Cert
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwRSAKeySpec,
	IN BYTE *pbP12Data,
	IN DWORD dwP12DataLen,
	IN LPCSTR szP12PWD
);

//生成公私钥对----执行该操作需要提前校验用户口令
//hCard: 设备句柄
//szContainerName：密钥容器名字
//dwKeySpec：密钥属性，为AT_KEYEXCHANGE或AT_SIGNATURE之一
//返回0成功，其它失败
DWORD _stdcall HSGenRSA
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec
);

// 导入RSA公钥或私钥，在导入RSA私钥时，将同时导入RSA公钥----执行该操作需要提前校验用户口令
//hCard: 输入，设备句柄
//szContainerName：密钥容器名字
//dwKeySpec：密钥属性，为AT_KEYEXCHANGE或AT_SIGNATURE之一
//dwRSAKeyType：RSA公钥或私钥的类型，为HT_RSA_PUB_KEY或HT_RSA_PRI_KEY之一
//*pbRSAKey：RSA公钥或私钥，PKCS#1的DER编码形式
//dwRSAKeyLen：RSA公钥或私钥长度
// 返回0成功，其它失败
DWORD _stdcall HSImportRSA
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec,
	IN DWORD dwRSAKeyType,
	IN BYTE *pbRSAKey,
	IN DWORD dwRSAKeyLen
);

// 导出RSA公钥
// hCard: 输入，设备句柄
// szContainerName：密钥容器名字
// dwKeySpec：密钥属性，为AT_KEYEXCHANGE或AT_SIGNATURE之一
// *pbPubKey：返回RSA公钥，PKCS#1的DER编码形式
// *pdwPubKeyLen：输入时，为pbPubKey缓冲区长度；输出时，为RSA公钥的DER长度
// 返回0成功，其它失败
DWORD _stdcall HSExportRSAPubKey
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec,
	OUT BYTE *pbPubKey,
	IN OUT DWORD *pdwPubKeyLen
);

// RSA公钥加密
// hCard: 输入，设备句柄
// IN LPCSTR szContainerName：密钥容器名字
// IN DWORD dwKeySpec：密钥属性，为AT_KEYEXCHANGE或AT_SIGNATURE之一
// IN DWORD dwPadMode：补码模式，为RSA_ZERO_PADDING、RSA_PKCS1_PADDING、RSA_NO_PADDING、RSA_PKCS1_OAEP_PADDING之一
// IN BYTE *pbInData：输入数据
// IN DWORD dwInDataLen：输入数据长度
// OUT BYTE *pbOutData：输出数据
// IN OUT DWORD *pdwOutDataLen：输入时，为pbOutData缓冲区长度；输出时，为输出数据长度
// 返回0成功，其它失败
DWORD _stdcall HSRSAEncrypt
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec,
	IN DWORD dwPadMode,
	IN BYTE *pbInData,
	IN DWORD dwInDataLen,
	OUT BYTE *pbOutData,
	IN OUT DWORD *pdwOutDataLen
);

// RSA私钥解密----执行该操作需要提前校验用户口令
// IN HANDLE hCard: 输入，设备句柄
// IN LPCSTR szContainerName：密钥容器名字
// IN DWORD dwKeySpec：密钥属性，为AT_KEYEXCHANGE或AT_SIGNATURE之一
// IN DWORD dwPadMode：补码模式，为RSA_ZERO_PADDING、RSA_PKCS1_PADDING、RSA_NO_PADDING、RSA_PKCS1_OAEP_PADDING之一
// IN BYTE *pbInData：输入数据
// IN DWORD dwInDataLen：输入数据长度
// OUT BYTE *pbOutData：输出数据
// IN OUT DWORD *pdwOutDataLen：输入时，为pbOutData缓冲区长度；输出时，为输出数据长度
// 返回0成功，其它失败
DWORD _stdcall HSRSADecrypt
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec,
	IN DWORD dwPadMode,
	IN BYTE *pbInData,
	IN DWORD dwInDataLen,
	OUT BYTE *pbOutData,
	IN OUT DWORD *pdwOutDataLen
);

// RSA私钥签名
// IN HANDLE hCard: 输入，设备句柄
// IN LPCSTR szContainerName：密钥容器名字
// IN DWORD dwKeySpec：密钥属性，为AT_KEYEXCHANGE或AT_SIGNATURE之一
// IN DWORD dwPadMode：补码模式，为RSA_ZERO_PADDING、RSA_PKCS1_PADDING、RSA_NO_PADDING之一
// IN BYTE *pbInData：输入数据
// IN DWORD dwInDataLen：输入数据长度
// OUT BYTE *pbOutData：输出数据
// IN OUT DWORD *pdwOutDataLen：输入时，为pbOutData缓冲区长度；输出时，为输出数据长度
// 返回0成功，其它失败
DWORD _stdcall HSRSASign
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec,
	IN DWORD dwPadMode,
	IN BYTE *pbInData,
	IN DWORD dwInDataLen,
	OUT BYTE *pbOutData,
	IN OUT DWORD *pdwOutDataLen
);

// RSA公钥验证签名
// IN HANDLE hCard: 输入，设备句柄
// IN LPCSTR szContainerName：密钥容器名字
// IN DWORD dwKeySpec：密钥属性，为AT_KEYEXCHANGE或AT_SIGNATURE之一
// IN DWORD dwPadMode：补码模式，为RSA_ZERO_PADDING、RSA_PKCS1_PADDING、RSA_NO_PADDING之一
// IN BYTE *pbInData：输入数据
// IN DWORD dwInDataLen：输入数据长度
// OUT BYTE *pbOutData：输出数据
// IN OUT DWORD *pdwOutDataLen：输入时，为pbOutData缓冲区长度；输出时，为输出数据长度
// 返回0成功，其它失败
DWORD _stdcall HSRSAVerify
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec,
	IN DWORD dwPadMode,
	IN BYTE *pbInData,
	IN DWORD dwInDataLen,
	OUT BYTE *pbOutData,
	IN OUT DWORD *pdwOutDataLen
);

//////////////////////////////////////////////////////////////////////////
//		硬件密钥/加解密操作
//////////////////////////////////////////////////////////////////////////

//写密钥，密钥类型可以是DES、3DES_112(16字节)、SSF33密钥、SCB2密钥
// IN HANDLE hCard: 输入，设备句柄
// HS_KEYINFO KeyInfo: 密钥信息结构，具体见结构定义
// 返回0成功，其它失败
DWORD _stdcall HSWriteKey
(
	IN HANDLE hCard,
	IN HS_KEYINFO KeyInfo
);


// 硬件对称算法高速ECB加解密，密钥类型可以是DES、3DES_112(16字节)、SSF33密钥、SCB2密钥
// IN HANDLE hCard: 输入，设备句柄
// IN DWORD dwKeyType：密钥类型，为HT_DES_KEY、HT_3DES_112_KEY、HT_SSF33_KEY、HT_SCB2_KEY之一
// IN DWORD dwMode：加密或解密模式，为ENCRYPT_MODE（加密）或DECRYPT_MODE（解密）
// IN CONST BYTE *pbInData：输入数据
// IN DWORD dwDataLen：数据长度，必须为16的整数倍，输入数据长度与输出数据长度相等
// OUT BYTE *pbOutData：输出数据
// 返回0成功，其它失败
DWORD _stdcall HSSymEcb
(
	IN HANDLE hCard,
	IN DWORD dwKeyType,
	IN DWORD dwMode,
	IN BYTE *pbInData,
	IN DWORD dwDataLen,
	OUT BYTE *pbOutData
);

//用临时密钥加解密数据
// IN HANDLE hCard: 输入，设备句柄
// IN HS_KEYINFO KeyInfo: 临时密钥结构，具体参见结构定义
// IN DWORD dwMode：加密或解密模式，为ENCRYPT_MODE（加密）或DECRYPT_MODE（解密）
// IN CONST BYTE *pbInData：输入数据
// IN DWORD dwDataLen：数据长度，必须为16的整数倍，输入数据长度与输出数据长度相等
// OUT BYTE *pbOutData：输出数据
// 返回0成功，其它失败
DWORD _stdcall HSSymSessionEcb
(
	IN HANDLE hCard,
	IN HS_KEYINFO KeyInfo,
	IN DWORD dwMode,
	IN BYTE *pbInData,
	IN DWORD dwDataLen,
	OUT BYTE *pbOutData
);
//////////////////////////////////////////////////////////////////////////
//		其他硬件操作
//////////////////////////////////////////////////////////////////////////

// 读USBKey的名字
// IN HANDLE hCard: 输入，设备句柄
// OUT char *pszLabel：返回USBKey的名字
// IN OUT DWORD *pdwLabelLen：输入时，为pszLabel缓冲区的长度；输出时，为USBKey名字的长度，包括结尾的NULL
//                            当pszLabel为NULL时，*pdwLabelLen返回USBKey名字的长度，包括结尾的NULL
//                            USBKey的名字的最大长度为HT_LABEL_LEN，*pdwLabelLen最大为strlen(pszLabel)+1
// 返回0成功，其它失败
DWORD _stdcall HSReadLabel
(
	IN HANDLE hCard,
	OUT char *pszLabel,
	IN OUT DWORD *pdwLabelLen
);

// 修改USBKey的名字----执行该操作需要提前校验用户口令
// IN HANDLE hCard: 输入，设备句柄
// IN LPCSTR szLabel：USBKey的名字，最大长度为HT_LABEL_LEN
// 返回0成功，其它失败
DWORD _stdcall HSWriteLabel
(
 	IN HANDLE hCard,
	IN LPCSTR szLabel
);

//获取设备序列号
// IN HANDLE hCard: 输入，设备句柄
// OUT BYTE bSerial[SERIAL_LEN]: 返回设备序列号
// 返回0成功，其它失败
DWORD _stdcall HSGetSerial
(
	IN HANDLE hCard,
	OUT BYTE bSerial[HS_SERIAL_LEN]
);

// 取USBKey的总空间
// IN HANDLE hCard: 输入，设备句柄
// OUT DWORD *pdwTotalSize：USBKey的总空间大小
// 返回0成功，其它失败
DWORD _stdcall HSGetTotalSize
(
	IN HANDLE hCard,
	OUT DWORD *pdwTotalSize
);

// 取USBKey的剩余空间
// IN HANDLE hCard: 输入，设备句柄
// OUT DWORD *pdwFreeSize：USBKey的剩余空间大小
// 返回0成功，其它失败
DWORD _stdcall HSGetFreeSize
(
	IN HANDLE hCard,
	OUT DWORD *pdwFreeSize
);

// 生成随机数
// IN HANDLE hCard: 输入，设备句柄
// IN DWORD dwRandomLen：生成的随机数的长度
// OUT BYTE *pbRandom：生成的随机数
// 返回0成功，其它失败
DWORD _stdcall HSGenRandom
(
	IN HANDLE hCard,
	IN DWORD dwRandomLen,
	OUT BYTE *pbRandom
);

//////////////////////////////////////////////////////////////////////////
//			软件算法
//////////////////////////////////////////////////////////////////////////

// DES的ECB运算，支持DES、3DES、3DES_112
// IN CONST BYTE *pbKey：DES密钥
// IN DWORD dwKeyLen：DES密钥的长度，可以为8、16或24
// IN DWORD dwMode：加密或解密模式，为ENCRYPT_MODE（加密）或DECRYPT_MODE（解密）
// IN CONST BYTE *pbInData：输入数据
// IN DWORD dwDataLen：数据长度，必须为8的整数倍，输入数据长度与输出数据长度相等
// OUT BYTE *pbOutData：输出数据
// 返回0成功，其它失败
DWORD _stdcall HSDESEcb
(
	IN CONST BYTE *pbKey,
	IN DWORD dwKeyLen,
	IN DWORD dwMode,
	IN CONST BYTE *pbInData,
	IN DWORD dwDataLen,
	OUT BYTE *pbOutData
);

// DES的CBC运算，支持DES、3DES、3DES_112，采用PKCS#5补码
// IN CONST BYTE *pbKey：DES密钥
// IN DWORD dwKeyLen：DES密钥的长度，可以为8、16或24
// IN BYTE bIV[8]：初始向量，长度必须为8字节
// IN DWORD dwMode：加密或解密模式，为ENCRYPT_MODE（加密）或DECRYPT_MODE（解密）
// IN CONST BYTE *pbInData：输入数据
// IN DWORD dwInDataLen：输入数据长度，解密时，必须是8的整数倍
// OUT BYTE *pbOutData：输出数据
// IN OUT DWORD *pdwOutDataLen：输入时，为pbOutData的缓冲区长度，必须足够大；输出时，为输出数据长度
//                              加密时，输出数据长度可能比输入数据长度要长
//                              解密时，输出数据长度可能比输入数据长度要短
// 返回0成功，其它失败
DWORD _stdcall HSDESCbc
(
	IN CONST BYTE *pbKey,
	IN DWORD dwKeyLen,
	IN BYTE bIV[8],
	IN DWORD dwMode,
	IN CONST BYTE *pbInData,
	IN DWORD dwInDataLen,
	OUT BYTE *pbOutData,
	IN OUT DWORD *pdwOutDataLen
);


// SHA1
// IN CONST BYTE *pbData：输入数据
// IN DWORD dwDataLen：输入数据长度
// OUT BYTE bHash[20]：Hash值
// 返回0成功，其它失败
DWORD _stdcall HSSHA1
(
	IN CONST BYTE *pbData,
	IN DWORD dwDataLen,
	OUT BYTE bHash[20]
);

// MD5
// IN CONST BYTE *pbData：输入数据
// IN DWORD dwDataLen：输入数据长度
// OUT BYTE bHash[16]：Hash值
// 返回0成功，其它失败
DWORD _stdcall HSMD5
(
	IN CONST BYTE *pbData,
	IN DWORD dwDataLen,
	OUT BYTE bHash[16]
);

DWORD _stdcall HSClearPin
(
	IN HANDLE hCard
);

DWORD _stdcall HSFormatEx
(
	IN HANDLE hCard
);

DWORD _stdcall HSEraseEx
(
	IN HANDLE hCard
);

DWORD _stdcall HSGetHWApp
(
	IN HANDLE hCard,
	OUT DWORD *pdwHWApp
);


//////////////////////////////////////////////////////////////////////////
//						SCB2 CBC crypt									//
//////////////////////////////////////////////////////////////////////////
// Set SCB2 key
// if dwKeyID == 0, set it as a session key, other set it as perpetual key
// 返回0成功，其它失败
DWORD _stdcall HSSCB2SetKey
(	IN HANDLE hCard,
	IN HS_KEYINFO pKey
);

// SCB2的CBC运算，采用PKCS#5补码
// IN HANDLE hCard: 输入，设备句柄
// IN HS_KEYINFO *pKey：SCB2密钥
// IN BYTE bIV[16]：初始向量，长度必须为16字节
// IN DWORD dwMode：加密或解密模式，为ENCRYPT_MODE（加密）或DECRYPT_MODE（解密）
// IN CONST BYTE *pbInData：输入数据
// IN DWORD dwInDataLen：输入数据长度，解密时，必须是16的整数倍
// OUT BYTE *pbOutData：输出数据
// IN OUT DWORD *pdwOutDataLen：输入时，为pbOutData的缓冲区长度，必须足够大；输出时，为输出数据长度
//                              加密时，输出数据长度可能比输入数据长度要长
//                              解密时，输出数据长度可能比输入数据长度要短
// 返回0成功，其它失败
DWORD _stdcall HSSCB2Cbc
(
	IN HANDLE hCard,
	IN HS_KEYINFO *pKey,
	IN BYTE bIV[16],
	IN DWORD dwMode,
	IN CONST BYTE *pbInData,
	IN DWORD dwInDataLen,
	OUT BYTE *pbOutData,
	IN OUT DWORD *pdwOutDataLen
);


// IN HANDLE hCard: 设备句柄
// OUT SYSTEMTIME * pSystime: 从硬件中返回的时钟
// 0: 成功; 其它值: 错误 
DWORD _stdcall HSGetTimepiece(IN HANDLE hCard, OUT SYSTEMTIME * pSystime);

DWORD _stdcall HSLoadcerttoieCert(IN LPCSTR szDevName);

DWORD _stdcall HSDelieCert(IN LPCSTR szDevName);

DWORD _stdcall HSShowCertProperty(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec,
	OUT BYTE *pbCert,
	IN OUT DWORD *pdwCertLen);

DWORD _stdcall HSGetCertInfo(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec,
	OUT BYTE *pbCert,
	IN OUT DWORD *pdwCertLen,
	OUT HS_CERTINFO* pszrdnName);

DWORD _stdcall HSGetCertOid1171(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec,
	OUT BYTE *pbCert,
	IN OUT DWORD *pdwCertLen,
	OUT LPSTR pszrdnName);

DWORD _stdcall HSGetCertOid(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec,
	OUT BYTE *pbCert,
	IN OUT DWORD *pdwCertLen,
	IN LPCSTR szOidName,
	OUT LPSTR pszOidCode);

DWORD HSSoftAESEnc
(
	IN CONST BYTE *pbInData,
	IN DWORD dwInDataLen,
	IN CONST BYTE *pbKey,
	IN DWORD dwKeyLen,
	OUT BYTE *pbOutData
);

DWORD HSSoftAESDec
(
	IN CONST BYTE *pbInData,
	IN DWORD dwDataLen,
	IN CONST BYTE *pbKey,
	IN DWORD dwKeyLen,
	OUT BYTE *pbOutData
);

DWORD _stdcall HSGetHTSection(
	IN HANDLE hCard,
	OUT LPCSTR szHTSection
);
#ifdef __cplusplus
}

DWORD _stdcall HSSetHTSection(
	IN HANDLE hCard,
	IN LPCSTR szHTSection,
	IN DWORD  HTSectionLen
);
#endif

#endif