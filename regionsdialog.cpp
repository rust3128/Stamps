#include "regionsdialog.h"
#include "ui_regionsdialog.h"
#include <QInputDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

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
        if(!q.exec()) qDebug() << "Не могу добавить регион." << q.lastError().text();
        model->select();
    }
}

void RegionsDialog::on_pbExit_clicked()
{
    this->reject();
}

void RegionsDialog::on_pbEdit_clicked()
{
    QModelIndex idx = ui->listView->currentIndex();
//    qDebug() << model->data(model->index(idx.row(),1)).toString();
    bool ok;
    QString text = QInputDialog::getText(this,
                                 QString::fromUtf8("Правка регина"),
                                 QString::fromUtf8("Введите регион:"),
                                 QLineEdit::Normal, model->data(model->index(idx.row(),1)).toString(),
                                 &ok);
    if (ok && !text.isEmpty()) {
        QSqlQuery q;
        q.prepare("UPDATE regions SET name=:nameRegion WHERE regionid=:idregion");
        q.bindValue(":nameRegion", text.trimmed());
        q.bindValue(":idregion",model->data(model->index(idx.row(),0)).toInt());
        if(!q.exec()) qDebug() << "Не могу обновить регион!" << q.lastError().text();
        model->select();
    }
}



void RegionsDialog::on_pbDel_clicked()
{
    QModelIndex idx = ui->listView->currentIndex();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromUtf8("Удаление региона"),
                          QString::fromUtf8("Вы действительно хотите удалить %1?")
                                  .arg(model->data(model->index(idx.row(),1)).toString()),
                          QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){
        QSqlQuery q;
        q.prepare("DELETE FROM regions WHERE regionid=:idregion");
        q.bindValue(":idregion",model->data(model->index(idx.row(),0)).toInt());
        if(!q.exec()) qDebug() << "Не могу удалить регион!" << q.lastError().text();
        model->select();
    }

}
