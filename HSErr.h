#ifndef __HS_ERR_H
#define __HS_ERR_H

#define HKI_ERRCODE_BASE	         	0x8010006FL

#define HKI_ERR_DEV_INDEX				HKI_ERRCODE_BASE+0x00000001 //�豸�����ų���
#define HKI_ERR_DEV_INUSE	  			HKI_ERRCODE_BASE+0x00000002 //���豸�Ѵ�������״̬����ȴ������³�������
#define HKI_ERR_DEV_READERLEN			HKI_ERRCODE_BASE+0x00000003 //ȡ�豸����ʱ�����豸������
#define HKI_ERR_DEV_INVALIDCTX			HKI_ERRCODE_BASE+0x00000004 //�ͷ��豸ʱ��ָ�����豸�����Ч���������ѵ��ù�HKDisconnectDev����
#define HKI_ERR_DEV_BYNAME				HKI_ERRCODE_BASE+0x00000005 //�Ҳ���ָ�����豸������豸������
#define HKI_ERR_DEV_INVALIDINDEX		HKI_ERRCODE_BASE+0x00000006 //��Ч���豸������
#define HKI_ERR_DEV_NOTFOUND			HKI_ERRCODE_BASE+0x00000007 //δ���ָ��豸

#define HKI_ERR_DEV_ATR_LENGTH			HKI_ERRCODE_BASE+0x00000008 //ȡ���к�ʱ������ATR�ĳ�������ӦΪ2-32�ֽڡ�
#define HKI_ERR_DEV_ATR_FLAG			HKI_ERRCODE_BASE+0x00000009 //ȡ���к�ʱ������ATR�����ֽڱ�־����ȷ��ӦΪ3B��3F
#define HKI_ERR_DEV_ATR_VALUE			HKI_ERRCODE_BASE+0x0000000a //ȡ���к�ʱ������ʶ��ATR���ݵĸ�ʽ������û���ҵ�0x8888��־

#define HKI_ERR_DEV_HID_CRC				HKI_ERRCODE_BASE+0x00000012 //HID�豸ͨ��ʱ������żУ�����
#define HKI_ERR_DEV_HID_TIMEOUT			HKI_ERRCODE_BASE+0x00000013 //HID�豸ͨ��ʱ������ʱ����
#define HKI_ERR_DEV_HID_RESET 			HKI_ERRCODE_BASE+0x00000014 //HID�豸ͨ��ʱ������Ƭ��λ��ϢTS��BCC����
#define HKI_ERR_DEV_HID_LEN				HKI_ERRCODE_BASE+0x00000015 //HID�豸ͨ��ʱ�������ȴ���
#define HKI_ERR_DEV_HID_BCC				HKI_ERRCODE_BASE+0x00000016 //HID�豸ͨ���У���������͵�����ϵ��У�����
#define HKI_ERR_DEV_HID_WRITE			HKI_ERRCODE_BASE+0x00000017 //HID�豸д��������
#define HKI_ERR_DEV_HID_READ			HKI_ERRCODE_BASE+0x00000018 //HID�豸����������
#define HKI_ERR_CRYPT_INVALIDPARAM		HKI_ERRCODE_BASE+0x00000039 //�����ĺ�����������Чֵ��
#define HKI_ERR_MEM_NULLPTR				HKI_ERRCODE_BASE+0x0000003a //��Ϊ������ָ��Ϊ��
#define HKI_ERR_MEM_BUFTOOSMALL			HKI_ERRCODE_BASE+0x0000003b //������ڴ�ռ䲻��

#define HKI_ERR_EVT_INVALID				HKI_ERRCODE_BASE+0x0000003c //��Ч���豸��δ����¼����
#define HKI_ERR_MUTEX_OBJHOST			HKI_ERRCODE_BASE+0x0000003d //��ǰ�������Ķ�����࣬����ʣ����Դ����
#define HKI_ERR_UNKOWN					HKI_ERRCODE_BASE+0x0000003e //δ�������

#define HKI_PIN_LEN_ERROR				HKI_ERRCODE_BASE+0x00000040//����ȴ���
#define HKI_PIN_RETRY_NUM_ERROR  		HKI_ERRCODE_BASE+0x00000041//������������������
#define HKI_DEVICE_NAME_LEN_ERROR		HKI_ERRCODE_BASE+0x00000042//�豸���ֳ��ȴ���
#define HKI_FILE_TYPE_ERROR				HKI_ERRCODE_BASE+0x00000043//�ļ����ʹ���
#define HKI_WRITE_DATA_LEN_ERROR		HKI_ERRCODE_BASE+0x00000044//д������ݳ��ȴ���
#define HKI_READ_DATA_LEN_ERROR			HKI_ERRCODE_BASE+0x00000045//���������ݳ��ȴ���
#define HKI_RSA_PADDING_TYPE_ERROR		HKI_ERRCODE_BASE+0x00000046//RSA�������ʹ���
#define HKI_RSA_DATA_LEN_ERROR			HKI_ERRCODE_BASE+0x00000047//RSA���ݳ��ȴ���
#define HKI_ACCESS_TYPE_ERROR			HKI_ERRCODE_BASE+0x00000048//Ȩ�����ʹ���
#define HKI_INPUT_DATA_LEN_ERROR		HKI_ERRCODE_BASE+0x00000049//SSF33/DES�㷨��������ݳ��ȴ��󣬱���Ϊ16/8�ı���
#define HKI_DEVICE_CMS_DIFFER_ERROR		HKI_ERRCODE_BASE+0x0000004a//�豸�������Ĵ�С���豸���Ͳ���
#define HKI_SSF33KEY_LEN_ERROR			HKI_ERRCODE_BASE+0x0000004b//SSF33��Կ���ȴ���
#define HKI_SSF33KEY_ID_ERROR			HKI_ERRCODE_BASE+0x0000004c//SSF33��ԿID����
#define HKI_INVALID_PARAM_TYPE			HKI_ERRCODE_BASE+0x0000004d//�Ƿ��Ĳ�������
#define HKI_RET_DATA_LEN_ERROR			HKI_ERRCODE_BASE+0x0000004e//�豸���ص����ݳ��ȴ���
#define HKI_KEY_LEN_ERROR				HKI_ERRCODE_BASE+0x0000004f//��Կ���ȴ���

#define HKI_ERROR_NOT_ENOUGH_MEMORY		HKI_ERRCODE_BASE+0x00000050//�ڴ治��
#define HKI_ENCRYPT_DECRYPT_MODE_ERROR  HKI_ERRCODE_BASE+0x00000051//�ӽ���ģʽ����
#define HKI_STRTOHEX_INPUT_DATA_ERROR	HKI_ERRCODE_BASE+0x00000052//�ַ�ת�����ݴ���
#define HKI_NOT_SUPPORT_ERROR			HKI_ERRCODE_BASE+0x00000053//���ܲ�֧��
#define HKI_FILE_ID_INVALID_ERROR		HKI_ERRCODE_BASE+0x00000054//�ļ�IDȡֵ��Χ���Ϸ�
#define HKI_PADDING_INVALID_ERROR		HKI_ERRCODE_BASE+0x00000055//���ݵĲ�������

#define HK_LENGTH_INVALID_ERROR			HKI_ERRCODE_BASE+0x00006700//д�����ݵĳ��ȴ���
#define HK_ID_EXIST_ERROR				HKI_ERRCODE_BASE+0x00006A80//��ʶ���Ѵ���
#define HK_NOT_SUPPORT_ERROR			HKI_ERRCODE_BASE+0x00006A81//���ܲ�֧��
#define HK_ID_NOT_FOUND_ERROR			HKI_ERRCODE_BASE+0x00006A82//δ�ҵ��ļ�
#define HK_NOT_ENOUGH_SIZE				HKI_ERRCODE_BASE+0x00006A84//�ռ䲻��
#define HK_X_TIMES_LEFT					HKI_ERRCODE_BASE+0x000063CX//У�������󣬻���x�λ��ᣬx���Դ�0xF~0x1
#define HK_NOT_ACCESS_ERROR				HKI_ERRCODE_BASE+0x00006982//��ȫ����������
#define HK_PIN_LOCKED_ERROR				HKI_ERRCODE_BASE+0x00006983//�������

//CSP Error Code
#define HT_PARAM_ERROR				0x88000001	// ��������
#define HT_CONTEXT_ERROR			0x88000002	// PC/SC�������쳣
#define HT_LIST_READER_ERROR		0x88000003	// ö��Ӳ���豸ʧ��
#define HT_LINK_ERROR				0x88000004	// ����Ӳ���豸ʧ��
#define HT_UNLINK_ERROR				0x88000005	// �Ͽ�Ӳ���豸����ʧ��
#define HT_RESET_ERROR				0x88000006	// ��λʧ��
#define HT_PCSC_ERROR				0x88000007	// PC/SCͨѶ����
#define HT_UNKNOWN_ERROR			0x88000008	// δ֪����
#define HT_DATA_ERROR				0x88000020	// ���ݴ���
#define HT_DATA_LEN_ERROR			0x88000021	// ���ݳ��ȴ���
#define HT_CREATE_MF_ERROR			0x88000030	// ����MF����
#define HT_ACTIVE_MF_ERROR			0x88000031	// ����MF����
#define HT_DELETE_MF_ERROR			0x88000032	// ɾ��MF����
#define HT_CREATE_DF_ERROR			0x88000033	// ����DF����
#define HT_CREATE_EF_ERROR			0x88000034	// �����ļ�����
#define HT_NO_MF					0x88000035	// û��MF
#define HT_NO_DF					0x88000036	// û��DF
#define HT_NO_EF					0x88000037	// ���ļ�������
#define HT_EF_EXIST					0x88000038	// �ļ��Ѵ���
#define HT_HW_NO_SPACE				0x88000039	// Ӳ��û�пռ�
#define HT_HW_INVALID_FORMAT		0x8800003A	// Ӳ���ĸ�ʽ����
#define HT_WRITE_KEY_ERROR			0x8800003B	// д��Կ����
#define HT_PIN_LEN_ERROR			0x8800003C	// pin�ĳ��ȴ���
#define HT_PIN_ERROR				0x8800003D	// pin����
#define HT_PIN_LOCK					0x8800003E	// pin������
#define HT_READ_ERROR				0x8800003F	// ������
#define HT_WRITE_ERROR				0x88000040	// д����
#define HT_RSA_MODE_ERROR			0x88000041	// RSAģʽ����
#define HT_LABEL_LEN_ERROR			0x88000042	// Label��HaiKey���֣����ȴ���
#define HT_NEED_RIGHT_ERROR			0x88000043	// ִ�иù�����ҪȨ��
#define HT_COMMAND_ERROR			0x88000044	// Ӳ��ָ��������
#define HT_SERIAL_ATR_ERROR			0x88000045 // ȡ���к�ʱ������ATR������
#define HT_DONT_SUPPORT_ERROR		0x88000046 // ��֧�ָù���
#define HT_CSP_CONTAINER_EXIST		0x88000050	// CSP��Կ�����Ѵ���
#define HT_CSP_SILENT_ERROR			0x88000051	// ������CSP��������UI���û����棩ʱ
#define HT_CSP_NO_KEY				0x88000052	// û���ҵ�RSA��Կ�Ի���ز�������ȷ
#define HT_CSP_ERROR				0x88000053	// ����Haitai CSPʧ��
#define HT_INSTALL_ERROR			0x88000060	// û���ҵ���װ��
#define HT_USER_CANCEL				0x88000061	// ��UI���û����棩���û�ѡ���ˡ�ȡ������ť
#define HT_LOAD_DLL_ERROR			0x88000062	// ���ض�̬��ʧ��
#define HT_SYS_VER_ERROR			0x88000063	// ����ϵͳ�汾Ϊ98,me����֧�ָù���
#define HT_P12_ERROR				0x88000064	// p12֤�鲻����ȷ����
#define HT_P12_PWD_ERROR			0x88000065	// p12֤��������
#define HT_TOO_MORE_FILE_CREATE		0x88000066 //�����˹�����û��Զ����ļ�

#endif