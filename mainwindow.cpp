#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
#include "camera.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox->setFixedWidth(100);
    ui->centralWidget->setLayout(ui->horizontalLayout);
    ui->groupBox->setLayout(ui->gridLayout);
    ui->widget->setLayout(ui->gridLayout_2);

    c=new client();
    //CameraManager *cam=new CameraManager();
    render=new YuvRender();
    Config *cfg=new Config;
    Camera *cam=new Camera(cfg->data.camera[0]);
   // connect(&cam->cams[0]->handler,SIGNAL(pic_ok(Mat)),render,SLOT(set_mat(Mat)));
  //  connect(&cam->cams[0]->src,SIGNAL(frame_update(Mat)),render,SLOT(set_mat(Mat)));
    connect(&cam->src,SIGNAL(frame_update(Mat)),render,SLOT(set_mat(Mat) ));
    ui->gridLayout_2->addWidget(render);
    //  ui->gridLayout_2->addWidget(render,1,1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    c->broadcast_to_client();
    //  c->connect_to_server();
    //    render->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    c->get_client_setting();
}

void MainWindow::on_pushButton_clicked()
{
    c->connect_to_server();
}
