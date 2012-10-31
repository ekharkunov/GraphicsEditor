#include <QtGui/QApplication>
#include "widget.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.showMaximized();
    
    return a.exec();
}
