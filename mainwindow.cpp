#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnNumClicked()
{
    QString str=ui->display->text();
    str=str+qobject_cast<QPushButton*>(sender())->text();//准确获取发送信息的对象,因为有很多数字按钮需要区分
    ui->display->setText(str);
}

void MainWindow::on_btnPeriod_clicked()
{
    QString str=ui->display->text();
    if(!str.contains(".")) str=str+".";
    ui->display->setText(str);
}


void MainWindow::on_btnDel_clicked()
{
    QString str=ui->display->text();
    str=str.left(str.length()-1);//从左边开始截取这么多
    ui->display->setText(str);
}

