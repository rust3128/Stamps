#include "storagedialog.h"
#include "ui_storagedialog.h"

#include <QSqlRelationalDelegate>
#include <QMessageBox>

StorageDialog::StorageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StorageDialog)
{
    ui->setupUi(this);
    ui->frame->hide();
    createUI();
}

StorageDialog::~StorageDialog()
{
    delete ui;
}

void StorageDialog::userSelectionChanged(QItemSelection selection)
{
    mapper->setCurrentModelIndex(selection.indexes().first());
}

void StorageDialog::createUI()
{
    modelStorage = new QSqlRelationalTableModel(this);
    modelStorage->setTable("storage");
    modelStorage->setHeaderData(1,Qt::Horizontal,"Место хранения");
    modelStorage->setHeaderData(2,Qt::Horizontal,"МОЛ");
    modelStorage->setEditStrategy(QSqlTableModel::OnFieldChange);

    modelStorage->setRelation(2, QSqlRelation("users","userid","username"));
    modelStorage->select();

    QSqlTableModel *modelComboUsers = modelStorage->relationModel(2);
    ui->comboBoxMOL->setModel(modelComboUsers);
    ui->comboBoxMOL->setModelColumn(2);

    mapper = new QDataWidgetMapper(this);
    mapper->setModel(modelStorage);
    mapper->setItemDelegate( new QSqlRelationalDelegate(this));
    mapper->addMapping(ui->lineEditName,1);
    mapper->addMapping(ui->comboBoxMOL,2);

    ui->tableView->setModel(modelStorage);
    connect(ui->tableView->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this,SLOT(userSelectionChanged(QItemSelection)));
    ui->tableView->hideColumn(0);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView));
    ui->tableView->verticalHeader()->hide();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->setDefaultSectionSize(ui->tableView->verticalHeader()->minimumSectionSize());
    ui->tableView->setCurrentIndex(modelStorage->index(0,0));
}

void StorageDialog::on_pbNew_clicked()
{
    ui->frame->show();
    ui->tableView->setEnabled(false);
    ui->frame_2->setEnabled(false);
    ui->comboBoxMOL->setCurrentIndex(-1);
    modelStorage->insertRow(modelStorage->rowCount(QModelIndex()));
    mapper->toLast();
}

void StorageDialog::on_pbEdit_clicked()
{
    ui->frame->show();
    ui->frame_2->setEnabled(false);
    ui->tableView->setEnabled(false);
}

void StorageDialog::on_pbDelete_clicked()
{
    int row =  ui->tableView->currentIndex().row();


    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromUtf8("Удаление склада"),
                          QString::fromUtf8("Вы действительно хотите удалить склад <b>%1</b>?")
                                  .arg(modelStorage->data(modelStorage->index(row,1)).toString()),
                          QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){
        modelStorage->removeRow(row);
        modelStorage->submitAll();
        modelStorage->select();
    }
}

void StorageDialog::on_pbClose_clicked()
{
    this->reject();
}

void StorageDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch (ui->buttonBox->standardButton(button)) {
    case QDialogButtonBox::Save:
        mapper->submit();
        modelStorage->submitAll();
        ui->tableView->setEnabled(true);
        ui->frame->hide();
        break;
    default:
        break;
    }
    ui->frame_2->setEnabled(true);
}
