#include "documentsdialog.h"
#include "ui_documentsdialog.h"
#include <QVBoxLayout>
#include <QToolBar>
#include <QMainWindow>


DocumentsDialog::DocumentsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DocumentsDialog)
{
    ui->setupUi(this);


}

DocumentsDialog::~DocumentsDialog()
{
    delete ui;
}
