#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "camera.h"
//MainWindow::MainWindow(QWidget *parent) :
//    QMainWindow(parent),
//    ui(new Ui::MainWindow)
//{
//    ui->setupUi(this);
//    ui->groupBox->setFixedWidth(100);
//    ui->centralWidget->setLayout(ui->horizontalLayout);
//    ui->groupBox->setLayout(ui->gridLayout);
//    ui->widget->setLayout(ui->gridLayout_2);

//    cam_manager=new CameraManager();

////    clt=new client();
////    //CameraManager *cam=new CameraManager();
////    render=new YuvRender();
////    clt->get_client_setting();
////    Config *cfg=new Config;
////    Camera *cam=new Camera(cfg->data.camera[0]);
////    connect(&cam->src,SIGNAL(frame_update(Mat)),render,SLOT(set_mat(Mat) ));
//#if 0
//    QPushButton *b1=new QPushButton("1");
//    QPushButton *b2=new QPushButton("2");
//    QPushButton *b3=new QPushButton("3");
//    ui->gridLayout_2->addWidget(b1,1,1);
//    ui->gridLayout_2->addWidget(b2,2,1);
//    ui->gridLayout_2->addWidget(b3,2,2);
//#endif
// }

//MainWindow::~MainWindow()
//{
//          delete cam_manager;
//    delete ui;
//}

void MainWindow::on_pushButton_search_device_clicked()
{
    client->search_device();
}

void MainWindow::on_pushButton_connect_server_clicked()
{
    client->connect_to_server();
}
#include "protocol.h"

void MainWindow::on_pushButton_get_config_clicked()
{

  //  QByteArray cc("12345");
//    cc=cc.remove(2,2);



    int len=Protocol::encode_configuration_request(buf);
    QByteArray rst=client->call_server(buf,Protocol::HEAD_LENGTH);
    rst=rst.remove(0,Protocol::HEAD_LENGTH);
    cam_manager->cfg->set_ba(rst);
    cam_manager->reconfig_camera(ui->gridLayout_2);
   // YuvRender *r=new YuvRender();
  //  connect(cam_manager->cams,SIGNAL())


}


void MainWindow::on_pushButton_3_clicked()
{
    int len=Protocol::encode_addcam_request(buf);
    QByteArray rst=client->call_server(buf,Protocol::HEAD_LENGTH);
    cam_manager->cfg->set_ba(rst);
}
