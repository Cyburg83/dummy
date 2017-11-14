//#include <QtWidgets>
#include <QApplication>

#include <stdlib.h>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    return a.exec();
}

