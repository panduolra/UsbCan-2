#include "widget.h"
#include <QApplication>
#include <QDebug>

#include "Service.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if ( Service::instance()->init() == ZCOMA_NO_ERROR ) {
        Service::instance()->printNodeConfigInfo();
    }

    Service::instance()->exit();

    Widget* widget = new Widget;
    widget->show();
    return a.exec();
}
