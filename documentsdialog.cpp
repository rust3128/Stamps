#include "documentsdialog.h"
#include "ui_documentsdialog.h"
#include "changedoctypedialog.h"
#include "docnewdialog.h"
#include <QDebug>


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



void DocumentsDialog::on_toolButtonNewDoc_clicked()
{
    ChangeDocTypeDialog *docTypeDlg = new ChangeDocTypeDialog();
    int res = docTypeDlg->exec();
    if(res == QDialog::Accepted){
        DocNewDialog *docNewDlg = new DocNewDialog(docTypeDlg->docTypeIDReturn(), docTypeDlg->docTypeNameReturn());
        docNewDlg->exec();        
    }
    else
        qDebug() << "Не выбрали";
    delete docTypeDlg;
}


