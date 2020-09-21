#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QtWidgets/QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(argv[1]);
    w.show();
    return a.exec();
}
