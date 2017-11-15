#include "changedoctypedialog.h"
#include "ui_changedoctypedialog.h"
#include <QDebug>

ChangeDocTypeDialog::ChangeDocTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeDocTypeDialog)
{
    ui->setupUi(this);
    createUI();
}

ChangeDocTypeDialog::~ChangeDocTypeDialog()
{
    delete ui;
}

int ChangeDocTypeDialog::docTypeIDReturn()
{
    return docTypeID;
}

QString ChangeDocTypeDialog::docTypeNameReturn()
{
    return docTypeName;
}

void ChangeDocTypeDialog::createUI()
{
    modelDocs = new QSqlQueryModel();
    modelDocs->setQuery("SELECT doctypeid, doctypename FROM doctype");
    ui->listView->setModel(modelDocs);
    ui->listView->setModelColumn(1);
    connect(ui->listView->selectionModel(),
            SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this,SLOT(userSelectionChanged(QItemSelection)));

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

}

void ChangeDocTypeDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch (ui->buttonBox->standardButton(button)) {
    case QDialogButtonBox::Ok:
        this->accept();
        break;
    case QDialogButtonBox::Cancel:
        this->reject();
        break;
    default:
        break;
    }

}

void ChangeDocTypeDialog::userSelectionChanged(QItemSelection selection)
{
    QModelIndex idx=selection.indexes().first();
    docTypeID=modelDocs->data(modelDocs->index(idx.row(),0)).toInt();
    docTypeName=modelDocs->data(modelDocs->index(idx.row(),1)).toString();
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}
