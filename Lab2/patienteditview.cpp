#include "patienteditview.h"
#include "ui_patienteditview.h"
#include <QSqlTableModel>
#include "idatabase.h"

PatientEditView::PatientEditView(QWidget *parent,int index)
    : QWidget(parent)
    , ui(new Ui::PatientEditView)
{
    ui->setupUi(this);

    dataMapper=new QDataWidgetMapper();
    QSqlTableModel *tabModel=IDatabase::getInstance().patientTabModel;
    dataMapper->setModel(tabModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);//在输入框修改马上就更新到模型中

    dataMapper->addMapping(ui->dbEditID,tabModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditName,tabModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbEditIDcard,tabModel->fieldIndex("ID_CARD"));
    dataMapper->addMapping(ui->dbSpinHeight,tabModel->fieldIndex("HEIGHT"));
    dataMapper->addMapping(ui->dbSpinWeight,tabModel->fieldIndex("WEIGHT"));
    dataMapper->addMapping(ui->dbEditPhone,tabModel->fieldIndex("MOBILEPHONE"));
    dataMapper->addMapping(ui->dbDateEditDOB,tabModel->fieldIndex("DOB"));
    dataMapper->addMapping(ui->dbCreatedTimestamp,tabModel->fieldIndex("CREATEDTIMESTAMP"));

    dataMapper->setCurrentIndex(index);
}

PatientEditView::~PatientEditView()
{
    delete ui;
}

void PatientEditView::on_pushButton_clicked()//保存操作
{
    IDatabase::getInstance().submitPatientEdit();
    emit goPreviousView();
}


void PatientEditView::on_pushButton_2_clicked()//取消操作
{
    IDatabase::getInstance().revertPatientEdit();
    emit goPreviousView();
}

