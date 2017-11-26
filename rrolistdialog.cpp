#include "rrolistdialog.h"
#include "ui_rrolistdialog.h"
#include <QKeyEvent>

RroListDialog::RroListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RroListDialog)
{
    ui->setupUi(this);

    filter.clear();

    createUI();
}

RroListDialog::~RroListDialog()
{
    delete ui;
}

void RroListDialog::createUI()
{
    ui->checkBox->setChecked(true);
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
    ui->tableView->selectRow(1);
//    QModelIndex newIndex = ui->tableView->model()->index(0, 0);
//    ui->tableView->setCurrentIndex(newIndex);

}

void RroListDialog::on_lineEditFind_textChanged(const QString &arg1)
{
    if(ui->lineEditFind->text().length()!=0){

        ui->checkBox->setChecked(false);
        filter = QString("terminalid =%1 OR zn like '%%1%' or fn=%1")
                                 .arg(arg1);
        modelRro->setFilter(filter);
    }
}


void RroListDialog::on_checkBox_clicked()
{
    if(ui->checkBox->isChecked()){
        filter.clear();
        modelRro->setFilter(filter);
    }
    modelRro->select();

}
