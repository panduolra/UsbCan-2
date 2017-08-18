#ifndef SERVICE_H
#define SERVICE_H

#include "initDefine.h"

class Service
{
public:
    static Service* instance();

    DWORD init();
    DWORD exit();

    void printNodeConfigInfo();

private:
    Service();

private:
    static Service *m_instance;
    ZCOMA_INITCFG m_initConfig;
    ZCOMA_NODECONFIG m_nodeConfig;
    HANDLE m_pOutHandle;
    HANDLE m_hdChannel;
};

#endif // SERVICE_H
