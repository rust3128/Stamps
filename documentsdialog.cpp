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


    QStringList list;
    list << "id" << "Дата" << "Номер"
                       << "Тип документа"
                       << "Количество"
                       << "Серия"
                       << "Начальнй\nномер"
                       << "Конечный\nномер"
                       << "Примечание";
    this->setupModelDocs(list);
    createUI();


}

DocumentsDialog::~DocumentsDialog()
{
    delete ui;
}

void DocumentsDialog::setupModelDocs(const QStringList &headers)
{
    modelDocs = new QSqlRelationalTableModel(this);
    modelDocs->setTable("docs");

    modelDocs->setRelation(3, QSqlRelation("doctype", "doctypeid", "doctypename"));

    for(int i = 0, j = 0; i < modelDocs->columnCount(); i++, j++){
            modelDocs->setHeaderData(i,Qt::Horizontal,headers[j]);
    }

    modelDocs->setSort(1,Qt::AscendingOrder);
    modelDocs->select(); // Делаем выборку данных из таблицы

}

void DocumentsDialog::createUI()
{
    ui->tableView->setModel(modelDocs);
    ui->tableView->hideColumn(0);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->verticalHeader()->setDefaultSectionSize(ui->tableView->verticalHeader()->minimumSectionSize());

    modelDocs->select();
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
    modelDocs->select();
}




