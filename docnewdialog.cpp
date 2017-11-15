#include "docnewdialog.h"
#include "ui_docnewdialog.h"

DocNewDialog::DocNewDialog(int ID, QString Type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DocNewDialog)
{
    ui->setupUi(this);
    docID=ID;
    docType=Type;
    createUI();
}

DocNewDialog::~DocNewDialog()
{
    delete ui;
}

void DocNewDialog::createUI()
{
    this->setWindowTitle("Новый документ " + docType);
    ui->labelTitle->setText("Новый документ\n"+docType);
}
