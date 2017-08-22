#include "Service.h"
#include <stdlib.h>
#include <QDebug>

Service *Service::m_instance = NULL;

Service *Service::instance()
{
    if (m_instance == NULL) {
        m_instance = new Service();
    }
    return m_instance;
}

Service::Service()
{
    m_initConfig.dwBaudrate = 1000;
    m_initConfig.dwNodeID = 1;
    m_initConfig.dwHeartbeat = 3000;
}

DWORD Service::init()
{
    qDebug()<<"Device init...";
    DWORD errCode = 0;
    errCode = ZCOMA_Open(DEV_TYPE_USBCAN_E_P, DEV_INDEX_USBCAN_E_P, 0);
    if ( errCode != 0 ) {
        qDebug()<<"ZCOMA_Open error, error code:"<<errCode;
        return errCode;
    }

    errCode = ZCOMA_Init( DEV_TYPE_USBCAN_E_P, /*dev type*/
                          DEV_INDEX_USBCAN_E_P, /*dev index*/
                          CH_INDEX_USBCAN_E_P, /* channels index*/
                          &m_initConfig,
                          &m_pOutHandle );
    if ( errCode != 0 ) {
        qDebug()<<"ZCOMA_Init error, error code:"<<errCode;
        return errCode;
    }

    errCode = ZCOMA_AddNode(m_hdChannel, &m_nodeConfig);
    if ( errCode != 0 ) {
        qDebug()<<"ZCOMA_AddNode error, error code:"<<errCode;
        return errCode;
    }

    errCode = ZCOMA_Start(DEV_TYPE_USBCAN_E_P, DEV_INDEX_USBCAN_E_P);
    if ( errCode != 0 ) {
        qDebug()<<"ZCOMA_Start error, error code:"<<errCode;
        return errCode;
    }

    return ZCOMA_NO_ERROR;
}

DWORD Service::exit()
{
    DWORD errCode = 0;
    errCode = ZCOMA_Stop(DEV_TYPE_USBCAN_E_P, DEV_INDEX_USBCAN_E_P);
    if ( errCode != 0 ) {
        qDebug()<<"ZCOMA_Stop error, error code:"<<errCode;
        return errCode;
    }

    errCode = ZCOMA_Uninit(m_hdChannel);
    if ( errCode != 0 ) {
        qDebug()<<"ZCOMA_Uninit error, error code:"<<errCode;
        return errCode;
    }

    errCode = ZCOMA_Close(DEV_TYPE_USBCAN_E_P, DEV_INDEX_USBCAN_E_P);
    if ( errCode != 0 ) {
        qDebug()<<"ZCOMA_Init error, error code:"<<errCode;
        return errCode;
    }
    qDebug()<<"Device exited!";

    return ZCOMA_NO_ERROR;
}

void Service::printNodeConfigInfo()
{
    ZCOMA_NODECONFIG configInfo = m_nodeConfig;
    qDebug()<<"Node ID: "<<configInfo.dwNodeID;
    qDebug()<<"Guard Mode: "<<configInfo.dwGuardMode;
    qDebug()<<"Guard Time: "<<configInfo.dwGuardTime;
    qDebug()<<"Retry Factor: "<<configInfo.dwRetryFactor;
}
