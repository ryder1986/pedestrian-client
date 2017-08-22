#include "mainwindow.h"
#include <QApplication>
#include "client.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    MainWindow w;
  //  w.setWindowFlags(Qt::WindowFullScreen);
 //  w.setWindowState(Qt::WindowFullScreen);
     w.setWindowState(Qt::WindowMaximized);
     w.show();

    return a.exec();
}
