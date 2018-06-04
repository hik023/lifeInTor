#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("gol_ic.icns"));
    MainWindow w;
    w.show();

    return a.exec();
}
