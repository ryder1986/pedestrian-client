#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "yuvrender.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();
void test(int t)
{
    qDebug()<<"get pic "<<t;
}


void on_pushButton_4_clicked();

void on_pushButton_clicked();

private:
    client *  c;
    Ui::MainWindow *ui;
    YuvRender *render;
};

#endif // MAINWINDOW_H
