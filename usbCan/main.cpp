#include "widget.h"
#include "initDefine.h"
#include <QApplication>
#include <QDebug>

#ifdef WIN32MINGW

#else
#include <QLibrary>

typedef DWORD (*zcoma_uninit)(HANDLE handle);

#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#ifdef WIN32MINGW
    HANDLE hdChannel;
    DWORD err = ZCOMA_Uninit(hdChannel);
    qDebug()<<"success!!!";
#else
    QLibrary mylib("./zcoma.dll");
    qDebug()<<mylib.load()<<mylib.errorString();
    zcoma_uninit init = (zcoma_uninit)mylib.resolve("ZCOMA_Uninit");
    HANDLE hdChannel = NULL;
    DWORD err = init(hdChannel); //ZCOMA_Uninit == init function
    qDebug()<<"success!!!";
#endif

    Widget* widget = new Widget;
    widget->show();
    return a.exec();
}
