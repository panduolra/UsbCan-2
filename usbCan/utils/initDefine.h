#ifndef INITDEFINE_H
#define INITDEFINE_H

#ifdef _LINUX
    #define LPVOID void*
#else
    typedef unsigned char BOOL;
    typedef void *HANDLE;
    typedef char CHAR;
    typedef unsigned char BYTE;
    typedef unsigned short WORD;
    typedef unsigned int DWORD;
    typedef float FLOAT;
    #define LPVOID void*
#endif

#define DEV_TYPE_USBCAN_E_P 101
#define CHANNELS_USBCAN_E_P 1
#include "zcoma.h"
#endif // INITDEFINE_H
