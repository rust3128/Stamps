#include "vlasnikdialog.h"
#include "ui_vlasnikdialog.h"
#include <QMessageBox>

VlasnikDialog::VlasnikDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VlasnikDialog)
{
    ui->setupUi(this);
    ui->frame->hide();
    createUI();
}

VlasnikDialog::~VlasnikDialog()
{
    delete ui;
}

void VlasnikDialog::userSelectionChanged(QItemSelection selection)
{
    mapper->setCurrentModelIndex(selection.indexes().first());
}

void VlasnikDialog::createUI()
{
    modelVlasnik = new QSqlTableModel(this);
    modelVlasnik->setTable("vlasnik");
    modelVlasnik->setHeaderData(1,Qt::Horizontal,"Владелец");
    modelVlasnik->setHeaderData(2,Qt::Horizontal,"ЕДРПУ");

    modelVlasnik->select();

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(modelVlasnik);
    mapper->addMapping(ui->lineEditName,1);
    mapper->addMapping(ui->lineEditEDRPU,2);

    ui->tableView->setModel(modelVlasnik);
    connect(ui->tableView->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this,SLOT(userSelectionChanged(QItemSelection)));
    ui->tableView->hideColumn(0);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->setDefaultSectionSize(ui->tableView->verticalHeader()->minimumSectionSize());


}

void VlasnikDialog::on_pbNew_clicked()
{
    ui->frame->show();
    ui->tableView->setEnabled(false);
    ui->frame_2->setEnabled(false);
    modelVlasnik->insertRow(modelVlasnik->rowCount());
    mapper->toLast();
}

void VlasnikDialog::on_pbEdit_clicked()
{
    ui->frame->show();
    ui->frame_2->setEnabled(false);
    ui->tableView->setEnabled(false);
}

void VlasnikDialog::on_pbDelete_clicked()
{
    int row =  ui->tableView->currentIndex().row();


    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromUtf8("Удаление склада"),
                          QString::fromUtf8("Вы действительно хотите удалить собственника <b>%1</b>?")
                                  .arg(modelVlasnik->data(modelVlasnik->index(row,1)).toString()),
                          QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){
        modelVlasnik->removeRow(row);
        modelVlasnik->submitAll();
        modelVlasnik->select();
    }
}

void VlasnikDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch (ui->buttonBox->standardButton(button)) {
    case QDialogButtonBox::Save:
        mapper->submit();
        modelVlasnik->submitAll();
        ui->tableView->setEnabled(true);
        ui->frame->hide();
        break;
    case QDialogButtonBox::Cancel:
        ui->tableView->setEnabled(true);
        ui->frame->hide();
    default:
        break;
    }
    ui->frame_2->setEnabled(true);
    modelVlasnik->select();
}

void VlasnikDialog::on_pbClose_clicked()
{
    this->reject();
}
