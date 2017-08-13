#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->groupBox->setFixedWidth(100);
    ui->centralWidget->setLayout(ui->horizontalLayout);
    ui->groupBox->setLayout(ui->gridLayout);
    ui->widget->setLayout(ui->gridLayout_2);
}

MainWindow::~MainWindow()
{
    delete ui;
}
