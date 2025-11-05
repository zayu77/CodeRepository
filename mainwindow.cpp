#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusLabel.setMinimumWidth(150);
    statusLabel.setText("length:"+QString::number(0)+"    line:"+QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);

    statusCursorLabel.setMinimumWidth(150);
    statusCursorLabel.setText("Ln:"+QString::number(0)+"    Col:"+QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCursorLabel);

    QLabel *author=new QLabel(ui->statusbar);//调用后可以自动销毁，一定要传个父组件
    author->setText(tr("李宝辉"));
    ui->statusbar->addPermanentWidget(author);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_About_triggered()
{
    AboutDialog dlg;//相当于是创建了一个类
    dlg.exec();
}


void MainWindow::on_action_Find_triggered()
{
    SearchDialog dlg;
    dlg.exec();
}


void MainWindow::on_action_Replace_triggered()
{
    ReplaceDialog dlg;
    dlg.exec();
}

