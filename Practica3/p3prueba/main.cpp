#include "mainwindow.h"
#include <QApplication>
#include <time.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand (time(NULL));
    MainWindow w;
    w.show();
    //MainWindow f1(32,5,5,3,3);
    return a.exec();
}
