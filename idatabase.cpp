#include "idatabase.h"
#include <QUuid>

void IDatabase::initDatabase()
{
    database=QSqlDatabase::addDatabase("QSQLITE");
    QString aFile="E:\\qtC++\\samples\\LAB_SQLlite\\LAB4.db";
    database.setDatabaseName(aFile);

    //不管你的路径是否正确，都会返回打开
    if(!database.open()){
        qDebug()<<"failed to open database";
    }else {
        qDebug()<<"open database is ok";
    }
}

bool IDatabase::initPatientModel()
{
    patientTabModel = new QSqlTableModel(this,database);//创建一个SQL表格模型，用于在Qt中操作数据库表
    patientTabModel->setTable("patient");
    patientTabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//手动提交
    patientTabModel->setSort(patientTabModel->fieldIndex("name"),Qt::AscendingOrder);//升序排序
    if(!(patientTabModel->select())) return false;

    patientSelection=new QItemSelectionModel(patientTabModel);//管理视图中的选择状态
    return true;
}

int IDatabase::addNewPatient()
{
    patientTabModel->insertRow(patientTabModel->rowCount(),QModelIndex());//在末尾添加一个记录
    QModelIndex curIndex=patientTabModel->index(patientTabModel->rowCount()-1,1);//创建最后一行的ModelIndex

    int curRecNo=curIndex.row();
    QSqlRecord curRec=patientTabModel->record(curRecNo);//获取当前记录
    curRec.setValue("CREATEDTIMESTAMP",QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID",QUuid::createUuid().toString(QUuid::WithoutBraces));
    patientTabModel->setRecord(curRecNo,curRec);//写回去

    return curIndex.row();
}

bool IDatabase::searchPatient(QString fliter)
{
    patientTabModel->setFilter(fliter);
    return patientTabModel->select();
}

void IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex=patientSelection->currentIndex();//获取当前选择单元行的模型索引
    patientTabModel->removeRow(curIndex.row());
    patientTabModel->submitAll();//提交所有挂起的修改到数据库
    patientTabModel->select();//重新从数据库加载数据
}

bool IDatabase::submitPatientEdit()
{
    return patientTabModel->submitAll();//提交所有修改
}

void IDatabase::revertPatientEdit()
{
    patientTabModel->revertAll();//撤销所有修改
}

QString IDatabase::userLogin(QString userName, QString password)
{
    QSqlQuery query;
    query.prepare("select username,password from user where username = :USER");//预处理语句，:USER是占位符由后面的变量替换
    query.bindValue(":USER",userName);
    query.exec();
    if(query.first()&&query.value("username").isValid()){
        QString pwd=query.value("password").toString();
        if(pwd==password) {
            qDebug()<<"login OK";
            return "loginOK";
        }
        else {
            qDebug()<<"wrong password";
            return "wrongPassword";
        }
    }
    else {
        qDebug()<<"no such user"<<userName;
        return "wrongUserName";
    }
}

IDatabase::IDatabase(QObject *parent) : QObject{parent}
{
    initDatabase();
}
