#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setMinimumHeight(500);
    w.setMaximumHeight(500);
    w.setMinimumWidth(303);
    w.setMaximumWidth(303);
    w.show();

    return a.exec();
}
