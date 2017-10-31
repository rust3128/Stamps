#include "regionsdialog.h"
#include "ui_regionsdialog.h"
#include <QInputDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

RegionsDialog::RegionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegionsDialog)
{
    ui->setupUi(this);
    createUI();
}

RegionsDialog::~RegionsDialog()
{
    delete ui;
}

void RegionsDialog::createUI()
{
    model = new QSqlTableModel();
    model->setTable("regions");
    model->select();

    ui->listView->setModel(model);
    ui->listView->setModelColumn(1);
}


void RegionsDialog::on_pbAdd_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this,
                                 QString::fromUtf8("Новый регион"),
                                 QString::fromUtf8("Введите регион:"),
                                 QLineEdit::Normal, "",
                                 &ok);
    if (ok && !text.isEmpty()) {
        QSqlQuery q;
        q.prepare("INSERT INTO regions(name) VALUES(:nameRegion)");
        q.bindValue(":nameRegion", text.trimmed());
        if(!q.exec()) qDebug() << "Не могу добавить регион" << q.lastError().text();
        model->select();
    }
}
