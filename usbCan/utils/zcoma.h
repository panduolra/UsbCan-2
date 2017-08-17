#ifndef _ZCOMA_H
#define _ZCOMA_H

#ifdef _LINUX
typedef unsigned char BOOL;
typedef void *HANDLE;
typedef char CHAR;
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;
typedef float FLOAT;

#define __stdcall
#endif

/* �豸�ͺ� */
enum DEV_TYPE {
    PCI_5010_P = 1, /* PCI��·CANopen��վ�� */
    USBCAN_E_P = 101 /* USB��·CANopen��վ�� */
};

/* ��վ���� */
enum SLAVE_MANAGEMENT {
    SLAVE_START = 1, /* ������վ */
    SLAVE_STOP = 2, /* ֹͣ��վ */
    SLAVE_PRE_OPERATIONAL = 128, /* ʹ��վ����Ԥ����״̬ */
    SLAVE_RESET = 129, /* ��λ��վ */
    SLAVE_RESET_CONNECTION = 130 /* ��λ��վ���� */
};

/* ��վ״̬ */
enum SLAVE_STATUS {
    SLAVESTATUS_INIT = 1, /* ��վ���ڳ�ʼ��(Ҳ�п��ܴ��ڵ���״̬) */
    SLAVESTATUS_STOP = 4, /* ��վ��ֹͣ */
    SLAVESTATUS_WORK = 5, /* ��վ���ڹ��� */
    SLAVESTATUS_PREWORK = 127, /* ��վ����Ԥ����״̬ */
    SLAVESTATUS_DISCONNECT = 255 /* ��վδ���� */
};

/* ��վ���߼�鷽ʽ */
enum SLAVE_GUARDING {
    GUARDING = 0, /* �ڵ��ػ� */
    HEARTBEAT = 1, /* ������ */
    DISABLE_GUARDING = 2 /* ���� */
};

/* �¼�ID���ص����������������¼� */
enum EVENT_ID {
    EVENT_RECV_EMDATA = 1, /* ���յ��������� */
    EVENT_RECV_PDO = 2 /* ���յ�PDO */
};

/* �豸������� */
enum DEV_ERR {
    ERR_LOADLIB = 11, /* װ��DLLʧ�� */
    ERR_GETPROC = 12, /* ��ȡ������ַʧ�� */
    ERR_OPENED = 13, /* �豸�Ѿ����� */
    ERR_NOTEXIST = 14, /* �豸������ */
    ERR_INITDEV = 15, /* ��ʼ���豸ʧ�� */
    ERR_NOTOPEN = 16, /* �豸û�д� */
    ERR_INVALIDPARAM = 17, /* ��Ч���� */
    ERR_INVALIDHANDLE = 18, /* ��Ч���豸��� */
    ERR_CLOSEDEV = 19, /* �޷��ر��豸 */
    ERR_INSTALLDRIVER = 20, /* ������װ����ȷ */
    ERR_BUFFERTOOSMALL = 22, /* �û�ָ���Ĵ洢�ռ�̫С */
    ERR_CHANNELOPENED = 24, /* ͨ���ѱ��� */
    ERR_CHANNELNOTOPEN = 25, /* ͨ��δ�� */
    ERR_NOMEMORY = 26, /* �ڴ治�� */
    ERR_INTERNAL = 27, /* δ֪�ڲ����� */
    ERR_PDONOTINSTALLED = 28, /* δע��PDO���� */
    ERR_TIMEOUT = 29, /* �ȴ���ʱ */
    ERR_SLAVEEXIST = 30, /* ��վ�Ѵ��� */
    ERR_SLAVENOTEXIST = 31, /* ��վ������ */
    ERR_SENDFAILED = 32, /* ��������ʧ�� */
    ERR_NODATA = 33, /* û������ */
    ERR_NOTIMPLEMENTED = 34 /* ����û��ʵ�� */
};

/* Ӳ������������ */
enum BUFFER_TYPE {
    RX_BUFFER = 1, /* ���ջ����� */
    TX_BUFFER = 2 /* ���ͻ����� */
};

/* �����ݽṹ�洢��վ�豸�����Ϣ�����ú�����ZCOMA_ReadBoardInfo�� */
typedef struct _tagZCOMA_BoardInfo {
    DWORD dwHardwareVer; /* Ӳ���汾�� */
    DWORD dwFirmwareVer; /* �̼��汾�� */
    DWORD dwMasterVer; /* ��վ��汾�� */
    CHAR szSerialNum[16]; /* �豸���к� */
    DWORD dwReserved[2]; /* ���� */
} ZCOMA_BOARDINFO, *LPZCOMA_BOARDINFO;

/* �����ݽṹ�洢��վ�豸��ʼ�����������ú�����ZCOMA_Init�� */
typedef struct _tagZCOMA_InitCfg {
    DWORD dwBaudrate; /* CAN�����ʣ�����1000��ʾ1000Kbps */
    DWORD dwNodeID; /* ��վ���ڵ�ID */
    DWORD dwHeartbeat; /* ��վ��������(0~65535, ��λms) */
    DWORD dwReserved[2]; /* ���� */
} ZCOMA_INITCFG, *LPZCOMA_INITCFG;

/* �����ݽṹ�洢��վ�豸��ʼ�����������ú�����ZCOMA_AddNode�� */
typedef struct _tagZCOMA_NodeConfig {
    DWORD dwNodeID; /* ��վID */
    DWORD dwGuardMode; /* ��վ���߼�鷽ʽ */
    DWORD dwGuardTime; /* ��վ���߼�����ڣ���λms����dwGuardModeΪ������ʱ����ʾ��վ�������������� */
    DWORD dwRetryFactor; /* û�м�⵽��վʱ���Լ���������dwGuardModeΪ2ʱ��Ч */
    DWORD dwReserved[4]; /* ���� */
} ZCOMA_NODECONFIG, *LPZCOMA_NODECONFIG;

/* �����ݽṹ�洢��վ�豸�������ݣ����ú�����ZCOMA_GetEmergencyData�� */
typedef struct _tagZCOMA_EmData {
    WORD dwEmErrCode; /* ����������� */
    BYTE dwErrRegCode; /* ��ǰ����Ĵ���ֵ */
    BYTE bAdditionErr[5]; /* �Զ��������� */
} ZCOMA_EMDATA, *LPZCOMA_EMDATA;

/* �����ݽṹ�洢��վ�豸�������ݣ����ú�����ZCOMA_SendTimeStamp�� */
typedef struct _tagZCOMA_TimeofDay {
    DWORD dwYear; /* �� */
    DWORD dwMonth; /* �� */
    DWORD dwDay; /* �� */
    DWORD dwHour; /* Сʱ */
    DWORD dwMinute; /* ���� */
    DWORD dwSecond; /* �� */
    DWORD dwMilliSecond; /* ���� */
} ZCOMA_TIMEOFDAY, *LPZCOMA_TIMEOFDAY;

/* �����ݽṹ�洢PDO��Ϣ�������¼��ص������� */
typedef struct _tagZCOMA_PDOInfo {
    DWORD dwNodeID; /* ��վ��ַ */
    DWORD dwPDOID; /* PDO ID */
    BYTE bPDOData[8]; /* PDO���� */
    BYTE bPDODataLen; /* PDO���ݳ��� */
} ZCOMA_PDOINFO, *LPZCOMA_PDOINFO;


#ifdef __cplusplus
extern "C" {
#endif

typedef DWORD (__stdcall * LPZCOMA_EVENTCB)(DWORD EventID, LPVOID pBuf, DWORD BufLen, LPVOID UserData);

/* ���ô˺������豸 */
DWORD __stdcall ZCOMA_Open(DWORD DevType, DWORD DevIndex, DWORD Reserved);

/* ���ô˺�����ȡ��վ�豸�����Ϣ */
DWORD __stdcall ZCOMA_ReadBoardInfo(DWORD DevType, DWORD DevIndex, ZCOMA_BOARDINFO *pInfo);

/* ���ô˺����ر��豸 */
DWORD __stdcall ZCOMA_Close(DWORD DevType, DWORD DevIndex);

/* ���ô˺�����ʼ����վͨ�� */
DWORD __stdcall ZCOMA_Init(DWORD DevType, DWORD DevIndex, DWORD ChIndex, ZCOMA_INITCFG *Config, HANDLE *pOutHandle);

/* ���ô˺����ر�ͨ�� */
DWORD __stdcall ZCOMA_Uninit(HANDLE hdChannel);

/* ���ô˺�����������ͨ����CANopenЭ��ջ */
DWORD __stdcall ZCOMA_Start(DWORD DevType, DWORD DevIndex);

/* ���ô˺���ֹͣ����ͨ����CANopenЭ��ջ */
DWORD __stdcall ZCOMA_Stop(DWORD DevType, DWORD DevIndex);

/* ���ô˺�������ָ��ͨ����CANopenЭ��ջ */
DWORD __stdcall ZCOMA_StartRoute(HANDLE hdChannel);

/* ���ô˺���ָֹͣ��ͨ����CANopenЭ��ջ */
DWORD __stdcall ZCOMA_StopRoute(HANDLE hdChannel);

/* ���ô˺�����Ӵ�վ */
DWORD __stdcall ZCOMA_AddNode(HANDLE hdChannel, ZCOMA_NODECONFIG *Config);

/* ���ô˺�����Ӵ�վ */
DWORD __stdcall ZCOMA_AddNodebyEDS(HANDLE hdChannel, CHAR *szEDSPath, DWORD NodeID);

/* ���ô˺���ɾ����վ */
DWORD __stdcall ZCOMA_RemoveNode(HANDLE hdChannel, DWORD NodeID);

/* ���ô˺�����ȡ��վ�������� */
DWORD __stdcall ZCOMA_UploadDatabySDO(HANDLE hdChannel, DWORD NodeID, DWORD Index, DWORD SubIndex, BYTE *pRecData, DWORD *pRecLen, DWORD WaitTm);

/* ���ô˺�������վ���ͷ������� */
DWORD __stdcall ZCOMA_DownloadDatabySDO(HANDLE hdChannel, DWORD NodeID, DWORD Index, DWORD SubIndex, BYTE *pSendData, DWORD SendLen, DWORD WaitTm);

/* ���ô˺������ָ����վ��PDO����վ��ʹ��վ���Խ��մ�վ�������Ĳɼ����� */
DWORD __stdcall ZCOMA_InstallPDOforInput(HANDLE hdChannel, DWORD NodeID, DWORD PDOID);

/* ���ô˺���ɾ��ָ����վ��PDO */
DWORD __stdcall ZCOMA_RemovePDOforInput(HANDLE hdChannel, DWORD NodeID, DWORD PDOID);

/* ���ô˺�����ȡָ����վ��PDO�������� */
DWORD __stdcall ZCOMA_GetPDOInputData(HANDLE hdChannel, DWORD NodeID, DWORD PDOID, BYTE *pRecData, DWORD *pRecLen, DWORD WaitTm);

/* ���ô˺�����ָ����վ����PDO������� */
DWORD __stdcall ZCOMA_SetPDOOutputData(HANDLE hdChannel, DWORD NodeID, DWORD PDOID, BYTE *pSendData, DWORD SendLen, DWORD WaitTm);

/* ���ô˺�����ָ����վ����Զ��PDO���������ݣ�����վ�յ�������վ�ط�PDO�������� */
DWORD __stdcall ZCOMA_SendRemotePDO(HANDLE hdChannel, DWORD NodeID, DWORD PDOID, DWORD dwReserved);

/* ���ô˺�����ȡ��վ�����Ľ������� */
DWORD __stdcall ZCOMA_GetEmergencyData(HANDLE hdChannel, DWORD *pNodeID, ZCOMA_EMDATA *pEmData);

/* ���ô˺�����ȡ��վ�����Ľ������� */
DWORD __stdcall ZCOMA_SetNodeState(HANDLE hdChannel, DWORD NodeID, DWORD State);

/* ���ô˺�����ȡ��վ����״̬ */
DWORD __stdcall ZCOMA_GetNodeStatus(HANDLE hdChannel, DWORD NodeID);

/* ���ô˺�������ͬ��֡����վ����վÿ��ָ�������������Ϸ���ָ��ͬ��֡ */
DWORD __stdcall ZCOMA_InstallSYNC(HANDLE hdChannel, DWORD SYNCID, DWORD CycleTm);

/* ���ô˺���ж��ͬ��֡ */
DWORD __stdcall ZCOMA_RemoveSYNC(HANDLE hdChannel, DWORD SYNCID);

/* ���ô˺�������ʱ���ʶ������ */
DWORD __stdcall ZCOMA_SendTimeStamp(HANDLE hdChannel, ZCOMA_TIMEOFDAY *tmDay);

/* ���ô˺������������ */
DWORD __stdcall ZCOMA_ClearBuffer(HANDLE hdChannel, DWORD BufferType);

/* �����¼��ص����� */
DWORD __stdcall ZCOMA_SetEventCallback(HANDLE hdChannel, LPZCOMA_EVENTCB lpCallback, LPVOID UserData, DWORD Reserved1, DWORD Reserved2);


#ifdef __cplusplus
}
#endif

#endif // _ZCOMA_H

