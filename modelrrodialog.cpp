#include "modelrrodialog.h"
#include "ui_modelrrodialog.h"
#include <QInputDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

ModelRroDialog::ModelRroDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModelRroDialog)
{
    ui->setupUi(this);
    createUI();
}

ModelRroDialog::~ModelRroDialog()
{
    delete ui;
}

void ModelRroDialog::createUI()
{
    model = new QSqlTableModel();
    model->setTable("rrotype");
    model->select();

    ui->listView->setModel(model);
    ui->listView->setModelColumn(1);
}

void ModelRroDialog::on_pbAdd_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this,
                                 QString::fromUtf8("Новая модель РРО"),
                                 QString::fromUtf8("Введите модель РРО:"),
                                 QLineEdit::Normal, "",
                                 &ok);
    if (ok && !text.isEmpty()) {
        QSqlQuery q;
        q.prepare("INSERT INTO rrotype(typerro) VALUES(:nameRro)");
        q.bindValue(":nameRro", text.trimmed());
        if(!q.exec()) qDebug() << "Не могу добавить модель РРО." << q.lastError().text();
        model->select();
    }
}

void ModelRroDialog::on_pbExit_clicked()
{
    this->reject();
}

void ModelRroDialog::on_pbEdit_clicked()
{
    QModelIndex idx = ui->listView->currentIndex();
//    qDebug() << model->data(model->index(idx.row(),1)).toString();
    bool ok;
    QString text = QInputDialog::getText(this,
                                 QString::fromUtf8("Правка модели РРО"),
                                 QString::fromUtf8("Введите модель РРО:"),
                                 QLineEdit::Normal, model->data(model->index(idx.row(),1)).toString(),
                                 &ok);
    if (ok && !text.isEmpty()) {
        QSqlQuery q;
        q.prepare("UPDATE rrotype SET typerro=:nameRro WHERE typeid=:idtype");
        q.bindValue(":nameRro", text.trimmed());
        q.bindValue(":idtype",model->data(model->index(idx.row(),0)).toInt());
        if(!q.exec()) qDebug() << "Не могу модель РРО!" << q.lastError().text();
        model->select();
    }
}

void ModelRroDialog::on_pbDel_clicked()
{
    QModelIndex idx = ui->listView->currentIndex();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, QString::fromUtf8("Удаление модели РРО"),
                          QString::fromUtf8("Вы действительно хотите удалить %1?")
                                  .arg(model->data(model->index(idx.row(),1)).toString()),
                          QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes){
        QSqlQuery q;
        q.prepare("DELETE FROM rrotype WHERE typeid=:idtype");
        q.bindValue(":idtype",model->data(model->index(idx.row(),0)).toInt());
        if(!q.exec()) qDebug() << "Не могу удалить модель РРО!" << q.lastError().text();
        model->select();
    }
}
