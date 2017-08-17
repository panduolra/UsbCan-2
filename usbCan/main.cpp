#include "widget.h"

#include "initDefine.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DWORD err = ZCOMA_Open(DEV_TYPE_USBCAN_E_P, 0, 0);
    qDebug()<<"err code!!!"<<err;

    Widget* widget = new Widget;
    widget->show();
    return a.exec();
}
