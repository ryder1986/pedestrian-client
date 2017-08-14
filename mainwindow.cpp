#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    c->write_client_msg();
}
