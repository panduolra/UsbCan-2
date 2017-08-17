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

/* 设备型号 */
enum DEV_TYPE {
    PCI_5010_P = 1, /* PCI单路CANopen主站卡 */
    USBCAN_E_P = 101 /* USB单路CANopen主站卡 */
};

/* 从站管理 */
enum SLAVE_MANAGEMENT {
    SLAVE_START = 1, /* 启动从站 */
    SLAVE_STOP = 2, /* 停止从站 */
    SLAVE_PRE_OPERATIONAL = 128, /* 使从站进入预工作状态 */
    SLAVE_RESET = 129, /* 复位从站 */
    SLAVE_RESET_CONNECTION = 130 /* 复位从站连接 */
};

/* 从站状态 */
enum SLAVE_STATUS {
    SLAVESTATUS_INIT = 1, /* 从站正在初始化(也有可能处于掉线状态) */
    SLAVESTATUS_STOP = 4, /* 从站已停止 */
    SLAVESTATUS_WORK = 5, /* 从站正在工作 */
    SLAVESTATUS_PREWORK = 127, /* 从站处于预工作状态 */
    SLAVESTATUS_DISCONNECT = 255 /* 从站未连接 */
};

/* 从站在线检查方式 */
enum SLAVE_GUARDING {
    GUARDING = 0, /* 节点守护 */
    HEARTBEAT = 1, /* 心跳包 */
    DISABLE_GUARDING = 2 /* 禁用 */
};

/* 事件ID，回调函数中用于区分事件 */
enum EVENT_ID {
    EVENT_RECV_EMDATA = 1, /* 接收到紧急数据 */
    EVENT_RECV_PDO = 2 /* 接收到PDO */
};

/* 设备错误代码 */
enum DEV_ERR {
    ERR_LOADLIB = 11, /* 装载DLL失败 */
    ERR_GETPROC = 12, /* 获取函数地址失败 */
    ERR_OPENED = 13, /* 设备已经被打开 */
    ERR_NOTEXIST = 14, /* 设备不存在 */
    ERR_INITDEV = 15, /* 初始化设备失败 */
    ERR_NOTOPEN = 16, /* 设备没有打开 */
    ERR_INVALIDPARAM = 17, /* 无效参数 */
    ERR_INVALIDHANDLE = 18, /* 无效的设备句柄 */
    ERR_CLOSEDEV = 19, /* 无法关闭设备 */
    ERR_INSTALLDRIVER = 20, /* 驱动安装不正确 */
    ERR_BUFFERTOOSMALL = 22, /* 用户指定的存储空间太小 */
    ERR_CHANNELOPENED = 24, /* 通道已被打开 */
    ERR_CHANNELNOTOPEN = 25, /* 通道未打开 */
    ERR_NOMEMORY = 26, /* 内存不足 */
    ERR_INTERNAL = 27, /* 未知内部错误 */
    ERR_PDONOTINSTALLED = 28, /* 未注册PDO类型 */
    ERR_TIMEOUT = 29, /* 等待超时 */
    ERR_SLAVEEXIST = 30, /* 从站已存在 */
    ERR_SLAVENOTEXIST = 31, /* 从站不存在 */
    ERR_SENDFAILED = 32, /* 发送数据失败 */
    ERR_NODATA = 33, /* 没有数据 */
    ERR_NOTIMPLEMENTED = 34 /* 函数没有实现 */
};

/* 硬件缓冲区类型 */
enum BUFFER_TYPE {
    RX_BUFFER = 1, /* 接收缓冲区 */
    TX_BUFFER = 2 /* 发送缓冲区 */
};

/* 此数据结构存储主站设备相关信息，调用函数：ZCOMA_ReadBoardInfo。 */
typedef struct _tagZCOMA_BoardInfo {
    DWORD dwHardwareVer; /* 硬件版本号 */
    DWORD dwFirmwareVer; /* 固件版本号 */
    DWORD dwMasterVer; /* 主站库版本号 */
    CHAR szSerialNum[16]; /* 设备序列号 */
    DWORD dwReserved[2]; /* 保留 */
} ZCOMA_BOARDINFO, *LPZCOMA_BOARDINFO;

/* 此数据结构存储主站设备初始化参数，调用函数：ZCOMA_Init。 */
typedef struct _tagZCOMA_InitCfg {
    DWORD dwBaudrate; /* CAN波特率，比如1000表示1000Kbps */
    DWORD dwNodeID; /* 主站卡节点ID */
    DWORD dwHeartbeat; /* 主站心跳周期(0~65535, 单位ms) */
    DWORD dwReserved[2]; /* 保留 */
} ZCOMA_INITCFG, *LPZCOMA_INITCFG;

/* 此数据结构存储从站设备初始化参数，调用函数：ZCOMA_AddNode。 */
typedef struct _tagZCOMA_NodeConfig {
    DWORD dwNodeID; /* 从站ID */
    DWORD dwGuardMode; /* 从站在线检查方式 */
    DWORD dwGuardTime; /* 从站在线检查周期，单位ms，当dwGuardMode为心跳包时，表示从站发送心跳包周期 */
    DWORD dwRetryFactor; /* 没有检测到从站时重试检查次数，当dwGuardMode为2时无效 */
    DWORD dwReserved[4]; /* 保留 */
} ZCOMA_NODECONFIG, *LPZCOMA_NODECONFIG;

/* 此数据结构存储从站设备紧急数据，调用函数：ZCOMA_GetEmergencyData。 */
typedef struct _tagZCOMA_EmData {
    WORD dwEmErrCode; /* 紧急错误代码 */
    BYTE dwErrRegCode; /* 当前错误寄存器值 */
    BYTE bAdditionErr[5]; /* 自定义错误代码 */
} ZCOMA_EMDATA, *LPZCOMA_EMDATA;

/* 此数据结构存储从站设备紧急数据，调用函数：ZCOMA_SendTimeStamp。 */
typedef struct _tagZCOMA_TimeofDay {
    DWORD dwYear; /* 年 */
    DWORD dwMonth; /* 月 */
    DWORD dwDay; /* 日 */
    DWORD dwHour; /* 小时 */
    DWORD dwMinute; /* 分钟 */
    DWORD dwSecond; /* 秒 */
    DWORD dwMilliSecond; /* 毫秒 */
} ZCOMA_TIMEOFDAY, *LPZCOMA_TIMEOFDAY;

/* 此数据结构存储PDO信息，用于事件回调函数。 */
typedef struct _tagZCOMA_PDOInfo {
    DWORD dwNodeID; /* 从站地址 */
    DWORD dwPDOID; /* PDO ID */
    BYTE bPDOData[8]; /* PDO数据 */
    BYTE bPDODataLen; /* PDO数据长度 */
} ZCOMA_PDOINFO, *LPZCOMA_PDOINFO;


#ifdef __cplusplus
extern "C" {
#endif

typedef DWORD (__stdcall * LPZCOMA_EVENTCB)(DWORD EventID, LPVOID pBuf, DWORD BufLen, LPVOID UserData);

/* 调用此函数打开设备 */
DWORD __stdcall ZCOMA_Open(DWORD DevType, DWORD DevIndex, DWORD Reserved);

/* 调用此函数获取主站设备相关信息 */
DWORD __stdcall ZCOMA_ReadBoardInfo(DWORD DevType, DWORD DevIndex, ZCOMA_BOARDINFO *pInfo);

/* 调用此函数关闭设备 */
DWORD __stdcall ZCOMA_Close(DWORD DevType, DWORD DevIndex);

/* 调用此函数初始化主站通道 */
DWORD __stdcall ZCOMA_Init(DWORD DevType, DWORD DevIndex, DWORD ChIndex, ZCOMA_INITCFG *Config, HANDLE *pOutHandle);

/* 调用此函数关闭通道 */
DWORD __stdcall ZCOMA_Uninit(HANDLE hdChannel);

/* 调用此函数启动所有通道的CANopen协议栈 */
DWORD __stdcall ZCOMA_Start(DWORD DevType, DWORD DevIndex);

/* 调用此函数停止所有通道的CANopen协议栈 */
DWORD __stdcall ZCOMA_Stop(DWORD DevType, DWORD DevIndex);

/* 调用此函数启动指定通道的CANopen协议栈 */
DWORD __stdcall ZCOMA_StartRoute(HANDLE hdChannel);

/* 调用此函数停止指定通道的CANopen协议栈 */
DWORD __stdcall ZCOMA_StopRoute(HANDLE hdChannel);

/* 调用此函数添加从站 */
DWORD __stdcall ZCOMA_AddNode(HANDLE hdChannel, ZCOMA_NODECONFIG *Config);

/* 调用此函数添加从站 */
DWORD __stdcall ZCOMA_AddNodebyEDS(HANDLE hdChannel, CHAR *szEDSPath, DWORD NodeID);

/* 调用此函数删除从站 */
DWORD __stdcall ZCOMA_RemoveNode(HANDLE hdChannel, DWORD NodeID);

/* 调用此函数获取从站服务数据 */
DWORD __stdcall ZCOMA_UploadDatabySDO(HANDLE hdChannel, DWORD NodeID, DWORD Index, DWORD SubIndex, BYTE *pRecData, DWORD *pRecLen, DWORD WaitTm);

/* 调用此函数往从站发送服务数据 */
DWORD __stdcall ZCOMA_DownloadDatabySDO(HANDLE hdChannel, DWORD NodeID, DWORD Index, DWORD SubIndex, BYTE *pSendData, DWORD SendLen, DWORD WaitTm);

/* 调用此函数添加指定从站的PDO到主站，使主站可以接收从站发出来的采集数据 */
DWORD __stdcall ZCOMA_InstallPDOforInput(HANDLE hdChannel, DWORD NodeID, DWORD PDOID);

/* 调用此函数删除指定从站的PDO */
DWORD __stdcall ZCOMA_RemovePDOforInput(HANDLE hdChannel, DWORD NodeID, DWORD PDOID);

/* 调用此函数获取指定从站的PDO输入数据 */
DWORD __stdcall ZCOMA_GetPDOInputData(HANDLE hdChannel, DWORD NodeID, DWORD PDOID, BYTE *pRecData, DWORD *pRecLen, DWORD WaitTm);

/* 调用此函数往指定从站发送PDO输出数据 */
DWORD __stdcall ZCOMA_SetPDOOutputData(HANDLE hdChannel, DWORD NodeID, DWORD PDOID, BYTE *pSendData, DWORD SendLen, DWORD WaitTm);

/* 调用此函数往指定从站发送远程PDO（不带数据），从站收到后往主站回发PDO输入数据 */
DWORD __stdcall ZCOMA_SendRemotePDO(HANDLE hdChannel, DWORD NodeID, DWORD PDOID, DWORD dwReserved);

/* 调用此函数获取从站发出的紧急数据 */
DWORD __stdcall ZCOMA_GetEmergencyData(HANDLE hdChannel, DWORD *pNodeID, ZCOMA_EMDATA *pEmData);

/* 调用此函数获取从站发出的紧急数据 */
DWORD __stdcall ZCOMA_SetNodeState(HANDLE hdChannel, DWORD NodeID, DWORD State);

/* 调用此函数获取从站工作状态 */
DWORD __stdcall ZCOMA_GetNodeStatus(HANDLE hdChannel, DWORD NodeID);

/* 调用此函数加载同步帧到主站，主站每隔指定周期往网络上发送指定同步帧 */
DWORD __stdcall ZCOMA_InstallSYNC(HANDLE hdChannel, DWORD SYNCID, DWORD CycleTm);

/* 调用此函数卸载同步帧 */
DWORD __stdcall ZCOMA_RemoveSYNC(HANDLE hdChannel, DWORD SYNCID);

/* 调用此函数发送时间标识到网络 */
DWORD __stdcall ZCOMA_SendTimeStamp(HANDLE hdChannel, ZCOMA_TIMEOFDAY *tmDay);

/* 调用此函数清除缓冲区 */
DWORD __stdcall ZCOMA_ClearBuffer(HANDLE hdChannel, DWORD BufferType);

/* 设置事件回调函数 */
DWORD __stdcall ZCOMA_SetEventCallback(HANDLE hdChannel, LPZCOMA_EVENTCB lpCallback, LPVOID UserData, DWORD Reserved1, DWORD Reserved2);


#ifdef __cplusplus
}
#endif

#endif // _ZCOMA_H

