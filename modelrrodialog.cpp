#include "modelrrodialog.h"
#include "ui_modelrrodialog.h"

ModelRroDialog::ModelRroDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModelRroDialog)
{
    ui->setupUi(this);
}

ModelRroDialog::~ModelRroDialog()
{
    delete ui;
}
