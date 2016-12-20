#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    setbuf(stdout,NULL);
    QApplication a(argc, argv);
    MainWindow w;
    printf("main\n");
    w.show();
    printf("mainshow\n");
    return a.exec();
}
