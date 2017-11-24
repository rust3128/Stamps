#include "rrolistdialog.h"
#include "ui_rrolistdialog.h"

RroListDialog::RroListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RroListDialog)
{
    ui->setupUi(this);

    createUI();
}

RroListDialog::~RroListDialog()
{
    delete ui;
}

void RroListDialog::createUI()
{
    modelRro = new QSqlRelationalTableModel();
    modelRro->setTable("rrolist");

    modelRro->setRelation(1,QSqlRelation("vlasnik","vlasnikid","name"));
    modelRro->select();
    modelRro->setHeaderData(1,Qt::Horizontal,"Владелец");
    modelRro->setHeaderData(2,Qt::Horizontal,"Терминал");
    modelRro->setHeaderData(3,Qt::Horizontal,"Адрес");
    modelRro->setHeaderData(4,Qt::Horizontal,"ЗН");
    modelRro->setHeaderData(5,Qt::Horizontal,"ФН");
    modelRro->setHeaderData(6,Qt::Horizontal,"Модель");
    modelRro->setHeaderData(7,Qt::Horizontal,"Версия ПО");

    ui->tableView->setModel(modelRro);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->hideColumn(0);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->setDefaultSectionSize(ui->tableView->verticalHeader()->minimumSectionSize());
    ui->tableView->selectRow(0);

}
