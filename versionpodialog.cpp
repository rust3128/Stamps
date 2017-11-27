#include "versionpodialog.h"
#include "ui_versionpodialog.h"
#include <QInputDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

VersionPODialog::VersionPODialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VersionPODialog)
{
    ui->setupUi(this);
    createUI();
}

VersionPODialog::~VersionPODialog()
{
    delete ui;
}

void VersionPODialog::createUI()
{
    model = new QSqlTableModel();
    model->setTable("versionpo");
    model->select();

    ui->listView->setModel(model);
    ui->listView->setModelColumn(1);
}

void VersionPODialog::on_pbAdd_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this,
                                 QString::fromUtf8("Новая версия ПО"),
                                 QString::fromUtf8("Введите версию ПО:"),
                                 QLineEdit::Normal, "",
                                 &ok);
    if (ok && !text.isEmpty()) {
        QSqlQuery q;
        q.prepare("INSERT INTO versionpo(version) VALUES(:version)");
        q.bindValue(":version", text.trimmed());
        if(!q.exec()) qDebug() << "Не могу добавить версию ПО." << q.lastError().text();
        model->select();
    }
}

void VersionPODialog::on_pbExit_clicked()
{
    this->reject();
}

void VersionPODialog::on_pbEdit_clicked()
{
    QModelIndex idx = ui->listView->currentIndex();
//    qDebug() << model->data(model->index(idx.row(),1)).toString();
    bool ok;
    QString text = QInputDialog::getText(this,
                                 QString::fromUtf8("Правка версии ПО"),
                                 QString::fromUtf8("Введите версию ПО:"),
                                 QLineEdit::Normal, model->data(model->index(idx.row(),1)).toString(),
                                 &ok);
    if (ok && !text.isEmpty()) {
        QSqlQuery q;
        q.prepare("UPDATE versionpo SET version=:version WHERE poid=:poid");
        q.bindValue(":version", text.trimmed());
        q.bindValue(":poid",model->data(model->index(idx.row(),0)).toInt());
        if(!q.exec()) qDebug() << "Не могу обновить версию ПО!" << q.lastError().text();
        model->select();
    }
}

void VersionPODialog::on_pbDel_clicked()
{
    QModelIndex idx = ui->listView->currentIndex();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromUtf8("Удаление версии ПО"),
                          QString::fromUtf8("Вы действительно хотите удалить %1?")
                                  .arg(model->data(model->index(idx.row(),1)).toString()),
                          QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){
        QSqlQuery q;
        q.prepare("DELETE FROM versionpo WHERE poid=:poid");
        q.bindValue(":poid",model->data(model->index(idx.row(),0)).toInt());
        if(!q.exec()) qDebug() << "Не могу удалить версию ПО!" << q.lastError().text();
        model->select();
    }
}
