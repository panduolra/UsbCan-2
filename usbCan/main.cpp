#include "widget.h"

#include "initDefine.h"

#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DWORD err = ZCOMA_Start(0, 0);
    qDebug()<<"success!!!"<<err;

    Widget* widget = new Widget;
    widget->show();
    return a.exec();
}
