#include "usersdialog.h"
#include "ui_usersdialog.h"

#include <QSqlRecord>
#include <QDebug>
#include <QSqlRelationalDelegate>
#include <QMessageBox>

UsersDialog::UsersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsersDialog)
{
    ui->setupUi(this);
    ui->groupBox->hide();
    createUI();
}

UsersDialog::~UsersDialog()
{
    delete ui;
}

void UsersDialog::createUI()
{
    modelUsers = new QSqlRelationalTableModel(this);
    modelUsers->setTable("users");
    modelUsers->setEditStrategy(QSqlTableModel::OnFieldChange);

    modelUsers->setHeaderData(1,Qt::Horizontal,"Регион");
    modelUsers->setHeaderData(2,Qt::Horizontal,"Имя");
    modelUsers->setHeaderData(3,Qt::Horizontal,"Пароль");
    modelUsers->setHeaderData(4,Qt::Horizontal,"Телефон");
    modelUsers->setHeaderData(5,Qt::Horizontal,"E-Mail");

    modelUsers->setRelation(1, QSqlRelation("regions","regionid","name"));

    modelUsers->select();

    QSqlTableModel *modelComboRegions = modelUsers->relationModel(1);
    ui->cbRegions->setModel(modelComboRegions);
    ui->cbRegions->setModelColumn(1);

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(modelUsers);
    mapper->setItemDelegate(new QSqlRelationalDelegate(this));
    mapper->addMapping(ui->cbRegions,1);
    mapper->addMapping(ui->leName,2);
    mapper->addMapping(ui->lePass,3);
    mapper->addMapping(ui->lePhone,4);
    mapper->addMapping(ui->leEmail,5);

    ui->tableView->setModel(modelUsers);
    connect(ui->tableView->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(userSelectionChanged(QItemSelection)));

    ui->tableView->hideColumn(0);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->verticalHeader()->hide();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->setDefaultSectionSize(ui->tableView->verticalHeader()->minimumSectionSize());
    ui->tableView->setCurrentIndex(modelUsers->index(0,0));


}


void UsersDialog::on_pbNew_clicked()
{
    ui->groupBox->show();
    ui->tableView->setEnabled(false);
    ui->cbRegions->setCurrentIndex(-1);
    modelUsers->insertRow(modelUsers->rowCount(QModelIndex()));
    mapper->toLast();
}

void UsersDialog::on_pbEdit_clicked()
{
    ui->groupBox->show();
    ui->tableView->setEnabled(false);
}

void UsersDialog::userSelectionChanged(QItemSelection selection)
{
    mapper->setCurrentModelIndex(selection.indexes().first());
}


void UsersDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch (ui->buttonBox->standardButton(button)) {
    case QDialogButtonBox::Save:
        mapper->submit();
        modelUsers->submitAll();
        ui->tableView->setEnabled(true);
        ui->groupBox->hide();
        break;
    default:
        break;
    }
}

void UsersDialog::on_pbClose_clicked()
{
    this->reject();
}

void UsersDialog::on_pbDelete_clicked()
{
    int row =  ui->tableView->currentIndex().row();


    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromUtf8("Удаление сотрудника"),
                          QString::fromUtf8("Вы действительно хотите удалить сотрудника %1?")
                                  .arg(modelUsers->data(modelUsers->index(row,2)).toString()),
                          QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){
        modelUsers->removeRow(row);
        modelUsers->submitAll();
        modelUsers->select();
    }

}
