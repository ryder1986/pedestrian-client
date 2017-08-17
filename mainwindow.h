#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "yuvrender.h"
#include "camera.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "protocol.h"
#include "camera.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit  MainWindow(QWidget *parent=0) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
        ui->groupBox->setFixedWidth(100);
        ui->centralWidget->setLayout(ui->horizontalLayout);
        ui->groupBox->setLayout(ui->gridLayout);
        ui->widget->setLayout(ui->gridLayout_2);

        cam_manager=new CameraManager();
        client=new Client();

    //    clt=new client();
    //    //CameraManager *cam=new CameraManager();
    //    render=new YuvRender();
    //    clt->get_client_setting();
    //    Config *cfg=new Config;
    //    Camera *cam=new Camera(cfg->data.camera[0]);
    //    connect(&cam->src,SIGNAL(frame_update(Mat)),render,SLOT(set_mat(Mat) ));
    #if 0
        QPushButton *b1=new QPushButton("1");
        QPushButton *b2=new QPushButton("2");
        QPushButton *b3=new QPushButton("3");
        ui->gridLayout_2->addWidget(b1,1,1);
        ui->gridLayout_2->addWidget(b2,2,1);
        ui->gridLayout_2->addWidget(b3,2,2);
    #endif
     }

    ~MainWindow()
    {
        delete cam_manager;
        delete ui;
    }


private slots:
//    void on_pushButton_2_clicked(){

//    }

//    void on_pushButton_4_clicked(){

//    }

//    void on_pushButton_clicked(){

//    }

void test(int t)
{
    qDebug()<<"get pic "<<t;
}


void on_pushButton_search_device_clicked();

void on_pushButton_connect_server_clicked();



void on_pushButton_get_config_clicked();

void on_pushButton_3_clicked();

private:
//    client *  clt;
    Ui::MainWindow *ui;
    CameraManager *cam_manager;
    Client *client;
    char buf[BUF_MAX_LEN];
 //   YuvRender *render;
    QList <YuvRender *> renders;
};

#endif // MAINWINDOW_H



