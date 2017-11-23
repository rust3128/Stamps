#include "rrolistdialog.h"
#include "ui_rrolistdialog.h"

RroListDialog::RroListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RroListDialog)
{
    ui->setupUi(this);
}

RroListDialog::~RroListDialog()
{
    delete ui;
}
