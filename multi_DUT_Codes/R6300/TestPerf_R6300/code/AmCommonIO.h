#ifndef AM_COMMON_IO_H
#define AM_COMMON_IO_H
#define GUI_IO
#include<stdio.h>
#include<stdarg.h>
#include "SocketConnection.h"

extern CSocketConnection SocketConnection;

/*amprintf - print to the UI console*/
long amprintf
    (
    const char * format,
    ...
    );

/*print test result to log file*/
int LogPrint(int PrintMode);   

#endif

