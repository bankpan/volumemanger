#ifndef _CSPAPI_
#define _CSPAPI_

#include "hserr.h"
#include "windows.h"
//////////////////////////////////////////////////////////////////////////
//Add by jpf 2009.04.27
#define HT_DES_KEY						1				// DES��Կ����Կ��8�ֽ�
#define HT_3DES_112_KEY					2				// 3DES_112��Կ����Կ��16�ֽ�
#define HT_SSF33_KEY					3				// SSF33����Կ��16�ֽ�
#define HT_SCB2_KEY						4				// SCB2, ��Կ��32�ֽڣ�2����Կ��E Key, A Key

#define ENCRYPT_MODE					1				//����
#define DECRYPT_MODE					2				//����
//End add jpf 2009.04.27

//��������
#define HS_SERIAL_LEN					0x08

//�û��Զ����ļ�ID
#define HS_MIN_FILE_ID					0x0000
#define HS_MAX_FILE_ID					0xFFFF

//�û��Զ����ļ���С
#define HS_MIN_FILE_SIZE				0x0000
#define HS_MAX_FILE_SIZE				0x8000-3	// �ļ�����󳤶�,32K-3,3�ֽ�Ϊ�ڲ������ļ���

//���Դ����Զ����ļ���������
#define HS_MAX_FILES_NUM				50

//�ļ�Ȩ��
#define HS_DELETE_RIGHT					0x01
#define HS_READ_RIGHT					0x02
#define HS_WRITE_RIGHT					0x03

//Ȩ������
#define HT_NEEDNT_PIN					0x00
#define HT_SO_PIN						0x01
#define HT_USER_PIN						0x02

//�豸״̬
#define HGS_STATE_EMPTY					0x0010
#define HGS_STATE_PRESENT				0x0020

//�ļ�״̬
#define HT_FILE_NOT_EXIST				0x00
#define HT_FILE_EXIST					0x01


//�豸Ӧ�ø�ʽ
#define HT_UNKNOWN_APP					0x00000000

#define HT_CSP_APP						0x00000001

#define HT_SEC_APP						0x00000004

#define HT_ALL_APP						0x00000005

#define HT_BLANK_HW						0x80000000

#define HT_MAYBE_BAD_HW					0x40000000

// ��Կ��������
#define HC_EXCHANGE_KEY_EXISTING		0x00000001		// ������Կ�Ѵ���
#define HC_EXCHANGE_CERT_EXISTING		0x00000003		// ����֤���Ѵ���	
#define HC_SIGN_KEY_EXISTING			0x00010000		// ǩ����Կ�Ѵ���
#define HC_SIGN_CERT_EXISTING			0x00030000		// ǩ��֤���Ѵ���

//////////////////////////////////////////////////////////////////////////
//�ṹ����

//�ļ��ṹ����
//dwFileID: �ļ�ID
//dwDeleteRight: �ļ���ɾ��Ȩ��
//dwReadRight: �ļ��Ķ�Ȩ��
//dwWriteRight: �ļ���дȨ��
//dwFileLen: �ļ��Ĵ�С��ȡֵΪ 0<dwFileLen<=MAX_FILE_LEN
//�ļ��ṹ����
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

//��Կ�ṹ����
//dwKeyType: ��Կ����HT_SSF33_KEY��HT_SCB2_KEY
//*pbKey����Կֵ
//dwKeyLen: ��Կ����
//dwUserRight: ��Կ��ʹ��Ȩ�ޣ�����ΪHT_SO_PIN��HT_USER_PIN��HT_NEEDNT_PIN֮һ ,
//				�ò���������ʱ��Կ�ӽ��ܺ���ʱ������
//dwReserved: ����ֵ
typedef struct _HS_KEYINFO
{
	DWORD dwKeyType;
	DWORD dwKeyID;	//0: session key, 0x01~0x0F: perpetual key which written in device.
	BYTE *pbKey;
	DWORD dwKeyLen;
	DWORD dwUseRight;
	DWORD dwReserved;
}HS_KEYINFO, *PHS_KEYINFO;

//��ʽ���ṹ����
//szLabel: �豸��ʶ���ƣ�����Ϊ1-32�ֽ�
//szSOPin: ����Ա�������Ϊ1-16�ֽ�
//dwSOPinRetry: ����Ա�������Դ���
//szUserPin: �û��������Ϊ1-16�ֽ�
//dwUserPinRetry: �û��������Դ���
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
//�豸���봦����ԭ�ͣ��μ����� HKSetDevChgFunc
typedef DWORD (__stdcall *DEVINSERTED)(IN void *pParam);//���룬�豸���봦�����Ĳ���
//�豸�γ�������ԭ�ͣ��μ����� HKSetDevChgFunc
typedef DWORD (__stdcall *DEVREMOVED)(IN void *pParam);//���룬�豸�γ��������Ĳ���


#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////
//		�豸������
//////////////////////////////////////////////////////////////////////////

//ȡ���ж�д������
//pszReaderName: ��������ַ��������ж�д�������ƣ�
	//�����ֵΪNULL, ��pdwReaderNameLen���ض�д�����ֵĳ���
//pdwReaderNameLen:���룺�������ĳ��ȣ��������д�����Ƶĳ��ȣ�
//pdwReaderNum:��������ض�д�����ܸ���
//����0�ɹ�������ʧ��
DWORD _stdcall HSListReaders
(
	OUT LPSTR pszReaderName,
	IN	OUT DWORD *pdwReaderNameLen,
	OUT DWORD *pdwReaderNum
);

//ָ����д������ע����Ӧ���豸��δ�����
//szReaderName�����룬��д������
//InsertProc�����룬�豸���봦����
//RemoveProc�����룬�豸�γ�������
//pProcParam�����룬�豸��δ������Ĳ���
//phEvtHandler�����������¼�������
//����0�ɹ�������ʧ��
DWORD _stdcall HSSetDevChgEvent
(
	IN LPCSTR szReaderName,
	IN DEVINSERTED InsertProc,
	IN DEVREMOVED RemoveProc,
	IN void *pProcParam,
	OUT HANDLE *phEvtHandler
);

//�Բ���¼�������ע���豸�Ĳ�δ������������
//hEvtHandler�����룬����¼�������
//InsertProc�����룬�豸���봦����
//RemoveProc�����룬�豸�γ�������
//pProcParam�����룬�豸��δ������Ĳ���
//����0�ɹ�������ʧ��
DWORD _stdcall HSSetDevChgEventParam
(
	IN HANDLE hEvtHandler,    
	IN DEVINSERTED InsertProc,
	IN DEVREMOVED RemoveProc, 
	IN void *pProcParam
);

//��ȡ��д��״̬
//szReaderName: ���룬��д������
//pdwState:�����������״̬. 
	//HGS_STATE_EMPTY ��������û���豸 
	//HGS_STATE_PRESENT �����������豸
//����0�ɹ�������ʧ��
DWORD _stdcall HSGetDevState
(
	IN  LPCSTR szReaderName,
	OUT DWORD *pdwState
);

//���ݿ����豸�����ӵ�һ��Haikey�豸
//szDevName: ���룬�����豸��
//phCard: ������豸�Ĳ������
//����0�ɹ�������ʧ��
DWORD _stdcall HSConnectDev
(
	IN LPCSTR szDevName,
	OUT HANDLE *phCard
);

//�Ͽ��豸
//hCard: ���룬�豸�Ĳ������
//����0�ɹ�������ʧ��
DWORD _stdcall HSDisconnectDev
(
	IN HANDLE hCard
);

//��ʼִ���������������Զ�ռ��ʽ�������豸����֧�ֶ�Ӧ��
//����0�ɹ�������ʧ��
DWORD _stdcall HSBeginTransaction
(
	IN HANDLE hCard
);

////������ǰ����������ֹ���ζ��豸�Ķ�ռ���ʣ���֧�ֶ�Ӧ��
//����0�ɹ�������ʧ��
DWORD _stdcall HSEndTransaction
(
	IN HANDLE hCard
);

//////////////////////////////////////////////////////////////////////////
//		�ļ�����
//////////////////////////////////////////////////////////////////////////

//��Haikey�豸���и�ʽ����������haikey��ʽ����CSPӦ�ø�ʽ���豸
//hCard: ���룬�豸���
//hsFormatInfo: haikey��ʽ����Ϣ�ṹ������μ��ṹ����
//����0�ɹ�������ʧ��
DWORD _stdcall HSFormat
(
	IN HANDLE hCard,
	IN HS_FORMATINFO hsFormatInfo
);

//��Haikey�豸���в�����������haikey�豸�����нṹ���������
//	�ò�����Ҫ���ȵ���У�����Ա����
//hCard: ���룬�豸���
//����0�ɹ�������ʧ��
DWORD _stdcall HSErase
(
	IN HANDLE hCard
);

//��haikey�豸�д����ļ�
//hCard: �豸���
//����0�ɹ�������ʧ��
DWORD _stdcall HSCreateFile
(
	IN HANDLE hCard,
	IN HS_FILEINFO FileInfo
);

//д�ļ�
//hCard: ���룬�豸���
//dwFileIndex: ���룬�ļ�ID
//pbData: д���ļ�������
//dwDataLen: д�����ݵĳ���
DWORD _stdcall HSWriteFile
(
	IN HANDLE hCard,
	IN DWORD dwFileIndex,
	IN DWORD dwOffset,
	IN BYTE *pbData,
	IN DWORD dwDataLen
);

//���ļ�����
//hCard: �����豸���
//dwFileIndex: ���룬�ļ�ID
//*pbData�����ض���������
//*pdwReadLen������ʱ����ʾҪ�������ݵĳ��ȣ���ʱpbDataӦ���Ѿ������ڴ棻���ʱ����ʾʵ�ʶ��������ݵĳ���
//             ��pbDataΪNULLʱ�����ظ��ļ������������ݵĳ���
//             ��*pdwReadLen==MAX_FILE_LEN��pbData!=NULLʱ��һ���ܹ��������ļ�������
//����0�ɹ�������ʧ��
DWORD _stdcall HSReadFile
(
	IN HANDLE hCard,
	IN DWORD dwFileIndex,
	IN DWORD dwOffset,
	IN BYTE *pbData,
	IN DWORD *pdwReadLen
);

//ɾ���ļ�
//hCard: ���룬�豸���
//dwFileIndex: �ļ�ID��
//����0�ɹ�������ʧ��
DWORD _stdcall HSDeleteFile
(
	IN HANDLE hCard,
	IN DWORD dwFileIndex
);

//��ȡ�ļ��Ĵ�С
//hCard: �豸�ľ��
//dwFileIndex: �ļ�ID��
//*pdwFileSize: �����ļ��Ĵ�С
//����0�ɹ�������ʧ��
DWORD _stdcall HSGetFileSize
(
	IN HANDLE hCard,
	IN DWORD dwFileIndex,
	OUT DWORD *pdwFileSize
);

//��ȡ�ļ���ɾ��
//hCard:���豸���
//dwFileIndex: �ļ�ID��
//dwRightType: ȡֵ����ΪHT_DELETE_RIGHT, HT_WRITE_RIGHT, HT_READ_RIGHT
//*pdwPinType: �����ļ���Ȩ������,����ֵ��HT_SO_PIN, HT_USER_PIN, HT_NEEDNT_PIN
// ����0�ɹ�������ʧ��
DWORD _stdcall HSGetFileRight
(
	IN HANDLE hCard,
	IN DWORD dwFileIndex,
	IN DWORD dwRightType,
	OUT DWORD *pdwPinType
);

//�ж��ļ��Ƿ����
//IN HANDLE hCard: ���룬�豸���
//IN DWORD dwFileIndex: �ļ�ID��
//OUT DWORD *pdwFileState: �����ļ�״̬������ֵΪHT_FILE_EXIST, HT_FILE_NOT_EXIST
//// ����0�ɹ�������ʧ��
DWORD _stdcall HSHasFileExist
(
	IN HANDLE hCard,
	IN DWORD dwFileIndex,
	OUT DWORD *pdwFileState
);
//////////////////////////////////////////////////////////////////////////
//			�������
//////////////////////////////////////////////////////////////////////////

//У���û�����
//hCard: �豸���
//szUserPin: haikey���û�����
//pbRetryNum: ���������󣬷������Դ���
// ����0�ɹ�������ʧ��
DWORD _stdcall HSVerifyUserPin
(
	IN HANDLE hCard,
	IN LPCSTR szUserPin,
	OUT DWORD *pdwRetryNum
);

//�޸��û��������
//hCard: �豸���
//szOldPin: haikeyԭ�û�����
//szNewPin: haikey���û�����
//pbRetryNum: ���������󣬷������Դ���
// ����0�ɹ�������ʧ��
DWORD _stdcall HSChangeUserPin
(
	IN HANDLE hCard,
	IN LPCSTR szOldPin,
	IN LPCSTR szNewPin,
	OUT DWORD *pdwRetryNum
);

//У�����Ա����
//hCard: �豸���
//szSOPin������Ա����
//pbRetryNum: ���������󣬷������Դ���
// ����0�ɹ�������ʧ��
DWORD _stdcall HSVerifySOPin
(
	IN HANDLE hCard,
	IN LPCSTR szSOPin,
	OUT DWORD *pdwRetryNum
);

//�޸Ĺ���Ա����
//hCard: �豸���
//szOldPin: haikeyԭ����Ա����
//szNewPin:	haikey�¹���Ա����
//pbRetryNum: ���ԭ������󣬷��ؿ�������Դ���
// ����0�ɹ�������ʧ��
DWORD _stdcall HSChangeSOPin
(
	IN HANDLE hCard,
	IN LPCSTR szOldPin,
	IN LPCSTR szNewPin,
	OUT DWORD *pdwRetryNum
);

// ���������û�����
//hCard: ���룬�豸���
//szSOPin��USBKey�Ĺ���Ա����
//szNewUserPin��USBKey���µ��û�����
//pbRetryNum����USBKey�Ĺ���Ա�������ʱ�����ع���Ա��������ԵĴ���
// ����0�ɹ�������ʧ��
DWORD _stdcall HSReWriteUserPin
(
	IN HANDLE hCard,	
	IN LPCSTR szSOPin,
	IN LPCSTR szNewUserPin,
	OUT DWORD *pdwRetryNum
);

//��ȡ�û��������Դ���
//hCard: ���룬�豸���
//pdwRetryNum:������û��������Դ���
DWORD _stdcall HSGetUserPinRetryNum
(
	IN HANDLE hCard,
	OUT DWORD *pdwRetryNum
);


//��ȡ����Ա�������Դ���
//hCard: ���룬�豸���
//pdwRetryNum:���������Ա�������Դ���
DWORD _stdcall HSGetSOPinRetryNum
(
	IN HANDLE hCard,
	OUT DWORD *pdwRetryNum
);

//��ȡ�û����������ܴ���
//hCard: ���룬�豸���
//pdwRetryNum:������û����������ܴ���
DWORD _stdcall HSGetUserPinRetryNumEx
(
	IN HANDLE hCard,
	OUT DWORD *pdwRetryNum
);


//��ȡ����Ա���������ܴ���
//hCard: ���룬�豸���
//pdwRetryNum:���������Ա���������ܴ���
DWORD _stdcall HSGetSOPinRetryNumEx
(
	IN HANDLE hCard,
	OUT DWORD *pdwRetryNum
);

//////////////////////////////////////////////////////////////////////////
//		����֤�����
//////////////////////////////////////////////////////////////////////////

//ö��������Կ����������
//pszContainerName: ��������ַ�����������Կ���������ƣ�
//�����ֵΪNULL, ��pdwContainerNameLen������Կ�������ֵĳ���
//pdwContainerNameLen:���룺�������ĳ��ȣ��������Կ�������Ƶĳ��ȣ�
//pdwContainerNum:�����������Կ�������ܸ���
//����0�ɹ�������ʧ��
DWORD _stdcall HSListContainers
(
	IN HANDLE hCard,
	OUT LPSTR pszContainersName,
	IN	OUT DWORD *pdwContainersNameLen,
	OUT DWORD *pdwContainerNum
);

//��ȡhaikey��Container����
//hCard: ���룬�豸���
//pdwContainerNum: �����haikey��Container����
DWORD _stdcall HSGetContainerNum
(
	IN HANDLE hCard,
	OUT DWORD *pdwContainerNum
);

//��ȡContainer����
//dwContainerIndex��Ҫ��������Կ����������ֵ��0<=dwContainerIndex<=*pdwContainerNum-1
//pszContainerName�����ص���Կ��������
//			��pszContainerName==NULʱ��pdwContainerNameLen������Կ�������ֵĳ���
//*pdwContainerNameLen������ʱ��ΪpszContainerName�������ĳ��ȣ�
//			  ���ʱ��Ϊ��Կ�������ֵĳ��ȣ�������β��NULL�ַ���
//*pdwContainerParam�����ص���Կ���������ԣ���ֵ��˵��??
//����0�ɹ�������ʧ��
DWORD _stdcall HSGetContainerName
(
	IN HANDLE hCard,
	IN DWORD dwContainerIndex,
	OUT LPSTR pszContainerName,
	IN OUT DWORD *pdwContainerNameLen,
	OUT DWORD *pdwContainerParam
);


//��ȡContainer����
//pszContainerName����Կ��������
//*pdwContainerParam�����ص���Կ���������ԣ���ֵ��˵��
//����0�ɹ�������ʧ��
DWORD _stdcall HSGetContainerParam
(
	IN HANDLE hCard,
	IN LPCSTR pszContainerName,
	OUT DWORD *pdwContainerParam
);

//������Կ����,--ִ�иò���Ҫ���ȵ���У���û��������
//hCard: ���룬�豸���
//szContainerName����Կ�������֣����szContainerNameΪNULL�򳤶�Ϊ0,���ں����ڲ�����GUID��Ϊ��Կ����������
//            ��Կ�������ֵĳ����ΪMAX_CON_NAME_LEN
// ����0�ɹ�������ʧ��
DWORD _stdcall HSCreateContainer
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName
);

//ɾ����Կ����--ִ�иò�����Ҫ��ǰУ���û�����
//hCard: ���룬�豸���
//szContainerName����Կ��������
// ����0�ɹ�������ʧ��
DWORD _stdcall HSDelContainer
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName
);

//��֤��
//szContainerName����Կ��������
//dwKeySpec����Կ���ԣ�ΪAT_KEYEXCHANGE��AT_SIGNATURE֮һ
//*pbCert������֤�����ݣ�der���룬��pbCert==NULLʱ��pdwCertLen����֤�����ݵĳ���
//*pdwCertLen������ʱ��ΪpbCert�������ĳ��ȣ����ʱ��Ϊ֤�����ݵĳ���
// ����0�ɹ�������ʧ��
DWORD _stdcall HSReadCert
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec,
	OUT BYTE *pbCert,
	IN OUT DWORD *pdwCertLen
);

//д֤��----ִ�иò�����Ҫ��ǰУ���û�����
//hCard: ���룬�豸���
//szContainerName����Կ��������
//dwKeySpec����Կ���ԣ�ΪAT_KEYEXCHANGE��AT_SIGNATURE֮һ
//*pbCert��֤�����ݣ�der����
//dwCertLen��֤�����ݵĳ���
//����0�ɹ�������ʧ��
DWORD _stdcall HSWriteCert
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec,
	IN BYTE *pbCert,
	IN DWORD dwCertLen
);

//��Pfx/P12֤��----ִ�иò�����Ҫ��ǰУ���û�����
//hCard: ���룬�豸���
//szContainerName����Կ�������֣����szContainerNameΪNULL�򳤶�Ϊ0,���ں����ڲ�����GUID��Ϊ��Կ����������
//                             ��Կ�������ֵĳ����ΪMAX_CON_NAME_LEN
//dwRSAKeySpec��ָ��֤���е�RSA��Կ��IE�е����ԣ�AT_KEYEXCHANGE=1��AT_SIGNATURE=2��Ϊ����ֵ����0��ʱʹ�ô�p12�н�������RSA��Կ����
//*pbP12Data��PKCS#12֤������
//dwP12DataLen��PKCS#12֤�����ݵĳ���
//szP12PWD��PKCS#12֤��ı�������
//����0�ɹ�������ʧ��
DWORD _stdcall HSImportP12Cert
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwRSAKeySpec,
	IN BYTE *pbP12Data,
	IN DWORD dwP12DataLen,
	IN LPCSTR szP12PWD
);

//���ɹ�˽Կ��----ִ�иò�����Ҫ��ǰУ���û�����
//hCard: �豸���
//szContainerName����Կ��������
//dwKeySpec����Կ���ԣ�ΪAT_KEYEXCHANGE��AT_SIGNATURE֮һ
//����0�ɹ�������ʧ��
DWORD _stdcall HSGenRSA
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec
);

// ����RSA��Կ��˽Կ���ڵ���RSA˽Կʱ����ͬʱ����RSA��Կ----ִ�иò�����Ҫ��ǰУ���û�����
//hCard: ���룬�豸���
//szContainerName����Կ��������
//dwKeySpec����Կ���ԣ�ΪAT_KEYEXCHANGE��AT_SIGNATURE֮һ
//dwRSAKeyType��RSA��Կ��˽Կ�����ͣ�ΪHT_RSA_PUB_KEY��HT_RSA_PRI_KEY֮һ
//*pbRSAKey��RSA��Կ��˽Կ��PKCS#1��DER������ʽ
//dwRSAKeyLen��RSA��Կ��˽Կ����
// ����0�ɹ�������ʧ��
DWORD _stdcall HSImportRSA
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec,
	IN DWORD dwRSAKeyType,
	IN BYTE *pbRSAKey,
	IN DWORD dwRSAKeyLen
);

// ����RSA��Կ
// hCard: ���룬�豸���
// szContainerName����Կ��������
// dwKeySpec����Կ���ԣ�ΪAT_KEYEXCHANGE��AT_SIGNATURE֮һ
// *pbPubKey������RSA��Կ��PKCS#1��DER������ʽ
// *pdwPubKeyLen������ʱ��ΪpbPubKey���������ȣ����ʱ��ΪRSA��Կ��DER����
// ����0�ɹ�������ʧ��
DWORD _stdcall HSExportRSAPubKey
(
	IN HANDLE hCard,
	IN LPCSTR szContainerName,
	IN DWORD dwKeySpec,
	OUT BYTE *pbPubKey,
	IN OUT DWORD *pdwPubKeyLen
);

// RSA��Կ����
// hCard: ���룬�豸���
// IN LPCSTR szContainerName����Կ��������
// IN DWORD dwKeySpec����Կ���ԣ�ΪAT_KEYEXCHANGE��AT_SIGNATURE֮һ
// IN DWORD dwPadMode������ģʽ��ΪRSA_ZERO_PADDING��RSA_PKCS1_PADDING��RSA_NO_PADDING��RSA_PKCS1_OAEP_PADDING֮һ
// IN BYTE *pbInData����������
// IN DWORD dwInDataLen���������ݳ���
// OUT BYTE *pbOutData���������
// IN OUT DWORD *pdwOutDataLen������ʱ��ΪpbOutData���������ȣ����ʱ��Ϊ������ݳ���
// ����0�ɹ�������ʧ��
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

// RSA˽Կ����----ִ�иò�����Ҫ��ǰУ���û�����
// IN HANDLE hCard: ���룬�豸���
// IN LPCSTR szContainerName����Կ��������
// IN DWORD dwKeySpec����Կ���ԣ�ΪAT_KEYEXCHANGE��AT_SIGNATURE֮һ
// IN DWORD dwPadMode������ģʽ��ΪRSA_ZERO_PADDING��RSA_PKCS1_PADDING��RSA_NO_PADDING��RSA_PKCS1_OAEP_PADDING֮һ
// IN BYTE *pbInData����������
// IN DWORD dwInDataLen���������ݳ���
// OUT BYTE *pbOutData���������
// IN OUT DWORD *pdwOutDataLen������ʱ��ΪpbOutData���������ȣ����ʱ��Ϊ������ݳ���
// ����0�ɹ�������ʧ��
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

// RSA˽Կǩ��
// IN HANDLE hCard: ���룬�豸���
// IN LPCSTR szContainerName����Կ��������
// IN DWORD dwKeySpec����Կ���ԣ�ΪAT_KEYEXCHANGE��AT_SIGNATURE֮һ
// IN DWORD dwPadMode������ģʽ��ΪRSA_ZERO_PADDING��RSA_PKCS1_PADDING��RSA_NO_PADDING֮һ
// IN BYTE *pbInData����������
// IN DWORD dwInDataLen���������ݳ���
// OUT BYTE *pbOutData���������
// IN OUT DWORD *pdwOutDataLen������ʱ��ΪpbOutData���������ȣ����ʱ��Ϊ������ݳ���
// ����0�ɹ�������ʧ��
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

// RSA��Կ��֤ǩ��
// IN HANDLE hCard: ���룬�豸���
// IN LPCSTR szContainerName����Կ��������
// IN DWORD dwKeySpec����Կ���ԣ�ΪAT_KEYEXCHANGE��AT_SIGNATURE֮һ
// IN DWORD dwPadMode������ģʽ��ΪRSA_ZERO_PADDING��RSA_PKCS1_PADDING��RSA_NO_PADDING֮һ
// IN BYTE *pbInData����������
// IN DWORD dwInDataLen���������ݳ���
// OUT BYTE *pbOutData���������
// IN OUT DWORD *pdwOutDataLen������ʱ��ΪpbOutData���������ȣ����ʱ��Ϊ������ݳ���
// ����0�ɹ�������ʧ��
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
//		Ӳ����Կ/�ӽ��ܲ���
//////////////////////////////////////////////////////////////////////////

//д��Կ����Կ���Ϳ�����DES��3DES_112(16�ֽ�)��SSF33��Կ��SCB2��Կ
// IN HANDLE hCard: ���룬�豸���
// HS_KEYINFO KeyInfo: ��Կ��Ϣ�ṹ��������ṹ����
// ����0�ɹ�������ʧ��
DWORD _stdcall HSWriteKey
(
	IN HANDLE hCard,
	IN HS_KEYINFO KeyInfo
);


// Ӳ���Գ��㷨����ECB�ӽ��ܣ���Կ���Ϳ�����DES��3DES_112(16�ֽ�)��SSF33��Կ��SCB2��Կ
// IN HANDLE hCard: ���룬�豸���
// IN DWORD dwKeyType����Կ���ͣ�ΪHT_DES_KEY��HT_3DES_112_KEY��HT_SSF33_KEY��HT_SCB2_KEY֮һ
// IN DWORD dwMode�����ܻ����ģʽ��ΪENCRYPT_MODE�����ܣ���DECRYPT_MODE�����ܣ�
// IN CONST BYTE *pbInData����������
// IN DWORD dwDataLen�����ݳ��ȣ�����Ϊ16�����������������ݳ�����������ݳ������
// OUT BYTE *pbOutData���������
// ����0�ɹ�������ʧ��
DWORD _stdcall HSSymEcb
(
	IN HANDLE hCard,
	IN DWORD dwKeyType,
	IN DWORD dwMode,
	IN BYTE *pbInData,
	IN DWORD dwDataLen,
	OUT BYTE *pbOutData
);

//����ʱ��Կ�ӽ�������
// IN HANDLE hCard: ���룬�豸���
// IN HS_KEYINFO KeyInfo: ��ʱ��Կ�ṹ������μ��ṹ����
// IN DWORD dwMode�����ܻ����ģʽ��ΪENCRYPT_MODE�����ܣ���DECRYPT_MODE�����ܣ�
// IN CONST BYTE *pbInData����������
// IN DWORD dwDataLen�����ݳ��ȣ�����Ϊ16�����������������ݳ�����������ݳ������
// OUT BYTE *pbOutData���������
// ����0�ɹ�������ʧ��
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
//		����Ӳ������
//////////////////////////////////////////////////////////////////////////

// ��USBKey������
// IN HANDLE hCard: ���룬�豸���
// OUT char *pszLabel������USBKey������
// IN OUT DWORD *pdwLabelLen������ʱ��ΪpszLabel�������ĳ��ȣ����ʱ��ΪUSBKey���ֵĳ��ȣ�������β��NULL
//                            ��pszLabelΪNULLʱ��*pdwLabelLen����USBKey���ֵĳ��ȣ�������β��NULL
//                            USBKey�����ֵ���󳤶�ΪHT_LABEL_LEN��*pdwLabelLen���Ϊstrlen(pszLabel)+1
// ����0�ɹ�������ʧ��
DWORD _stdcall HSReadLabel
(
	IN HANDLE hCard,
	OUT char *pszLabel,
	IN OUT DWORD *pdwLabelLen
);

// �޸�USBKey������----ִ�иò�����Ҫ��ǰУ���û�����
// IN HANDLE hCard: ���룬�豸���
// IN LPCSTR szLabel��USBKey�����֣���󳤶�ΪHT_LABEL_LEN
// ����0�ɹ�������ʧ��
DWORD _stdcall HSWriteLabel
(
 	IN HANDLE hCard,
	IN LPCSTR szLabel
);

//��ȡ�豸���к�
// IN HANDLE hCard: ���룬�豸���
// OUT BYTE bSerial[SERIAL_LEN]: �����豸���к�
// ����0�ɹ�������ʧ��
DWORD _stdcall HSGetSerial
(
	IN HANDLE hCard,
	OUT BYTE bSerial[HS_SERIAL_LEN]
);

// ȡUSBKey���ܿռ�
// IN HANDLE hCard: ���룬�豸���
// OUT DWORD *pdwTotalSize��USBKey���ܿռ��С
// ����0�ɹ�������ʧ��
DWORD _stdcall HSGetTotalSize
(
	IN HANDLE hCard,
	OUT DWORD *pdwTotalSize
);

// ȡUSBKey��ʣ��ռ�
// IN HANDLE hCard: ���룬�豸���
// OUT DWORD *pdwFreeSize��USBKey��ʣ��ռ��С
// ����0�ɹ�������ʧ��
DWORD _stdcall HSGetFreeSize
(
	IN HANDLE hCard,
	OUT DWORD *pdwFreeSize
);

// ���������
// IN HANDLE hCard: ���룬�豸���
// IN DWORD dwRandomLen�����ɵ�������ĳ���
// OUT BYTE *pbRandom�����ɵ������
// ����0�ɹ�������ʧ��
DWORD _stdcall HSGenRandom
(
	IN HANDLE hCard,
	IN DWORD dwRandomLen,
	OUT BYTE *pbRandom
);

//////////////////////////////////////////////////////////////////////////
//			����㷨
//////////////////////////////////////////////////////////////////////////

// DES��ECB���㣬֧��DES��3DES��3DES_112
// IN CONST BYTE *pbKey��DES��Կ
// IN DWORD dwKeyLen��DES��Կ�ĳ��ȣ�����Ϊ8��16��24
// IN DWORD dwMode�����ܻ����ģʽ��ΪENCRYPT_MODE�����ܣ���DECRYPT_MODE�����ܣ�
// IN CONST BYTE *pbInData����������
// IN DWORD dwDataLen�����ݳ��ȣ�����Ϊ8�����������������ݳ�����������ݳ������
// OUT BYTE *pbOutData���������
// ����0�ɹ�������ʧ��
DWORD _stdcall HSDESEcb
(
	IN CONST BYTE *pbKey,
	IN DWORD dwKeyLen,
	IN DWORD dwMode,
	IN CONST BYTE *pbInData,
	IN DWORD dwDataLen,
	OUT BYTE *pbOutData
);

// DES��CBC���㣬֧��DES��3DES��3DES_112������PKCS#5����
// IN CONST BYTE *pbKey��DES��Կ
// IN DWORD dwKeyLen��DES��Կ�ĳ��ȣ�����Ϊ8��16��24
// IN BYTE bIV[8]����ʼ���������ȱ���Ϊ8�ֽ�
// IN DWORD dwMode�����ܻ����ģʽ��ΪENCRYPT_MODE�����ܣ���DECRYPT_MODE�����ܣ�
// IN CONST BYTE *pbInData����������
// IN DWORD dwInDataLen���������ݳ��ȣ�����ʱ��������8��������
// OUT BYTE *pbOutData���������
// IN OUT DWORD *pdwOutDataLen������ʱ��ΪpbOutData�Ļ��������ȣ������㹻�����ʱ��Ϊ������ݳ���
//                              ����ʱ��������ݳ��ȿ��ܱ��������ݳ���Ҫ��
//                              ����ʱ��������ݳ��ȿ��ܱ��������ݳ���Ҫ��
// ����0�ɹ�������ʧ��
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
// IN CONST BYTE *pbData����������
// IN DWORD dwDataLen���������ݳ���
// OUT BYTE bHash[20]��Hashֵ
// ����0�ɹ�������ʧ��
DWORD _stdcall HSSHA1
(
	IN CONST BYTE *pbData,
	IN DWORD dwDataLen,
	OUT BYTE bHash[20]
);

// MD5
// IN CONST BYTE *pbData����������
// IN DWORD dwDataLen���������ݳ���
// OUT BYTE bHash[16]��Hashֵ
// ����0�ɹ�������ʧ��
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
// ����0�ɹ�������ʧ��
DWORD _stdcall HSSCB2SetKey
(	IN HANDLE hCard,
	IN HS_KEYINFO pKey
);

// SCB2��CBC���㣬����PKCS#5����
// IN HANDLE hCard: ���룬�豸���
// IN HS_KEYINFO *pKey��SCB2��Կ
// IN BYTE bIV[16]����ʼ���������ȱ���Ϊ16�ֽ�
// IN DWORD dwMode�����ܻ����ģʽ��ΪENCRYPT_MODE�����ܣ���DECRYPT_MODE�����ܣ�
// IN CONST BYTE *pbInData����������
// IN DWORD dwInDataLen���������ݳ��ȣ�����ʱ��������16��������
// OUT BYTE *pbOutData���������
// IN OUT DWORD *pdwOutDataLen������ʱ��ΪpbOutData�Ļ��������ȣ������㹻�����ʱ��Ϊ������ݳ���
//                              ����ʱ��������ݳ��ȿ��ܱ��������ݳ���Ҫ��
//                              ����ʱ��������ݳ��ȿ��ܱ��������ݳ���Ҫ��
// ����0�ɹ�������ʧ��
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


// IN HANDLE hCard: �豸���
// OUT SYSTEMTIME * pSystime: ��Ӳ���з��ص�ʱ��
// 0: �ɹ�; ����ֵ: ���� 
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