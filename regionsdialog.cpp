#include "regionsdialog.h"
#include "ui_regionsdialog.h"

RegionsDialog::RegionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegionsDialog)
{
    ui->setupUi(this);
}

RegionsDialog::~RegionsDialog()
{
    delete ui;
}
