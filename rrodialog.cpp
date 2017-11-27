#include "rrodialog.h"
#include "ui_rrodialog.h"
#include "vlasnikdialog.h"
#include "versionpodialog.h"
#include "modelrrodialog.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

RroDialog::RroDialog(int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RroDialog)
{
    ui->setupUi(this);
    rroID=id;
    createUI();
}

RroDialog::~RroDialog()
{
    delete ui;
}

void RroDialog::createUI()
{
    modelVlasnik = new QSqlTableModel(this);
    modelVlasnik->setTable("vlasnik");
    modelVlasnik->select();
    ui->comboBoxVlasnik->setModel(modelVlasnik);
    ui->comboBoxVlasnik->setModelColumn(1);

    modelRro = new QSqlTableModel(this);
    modelRro->setTable("rrotype");
    modelRro->select();
    ui->comboBoxModel->setModel(modelRro);
    ui->comboBoxModel->setModelColumn(1);

    modelPo = new QSqlTableModel(this);
    modelPo->setTable("versionpo");
    modelPo->select();
    ui->comboBoxVersion->setModel(modelPo);
    ui->comboBoxVersion->setModelColumn(1);

    if(rroID==-1) {
        ui->comboBoxModel->setCurrentIndex(-1);
        ui->comboBoxVersion->setCurrentIndex(-1);
        ui->comboBoxVlasnik->setCurrentIndex(-1);
    } else {
        QSqlQuery q;
        q.prepare("SELECT * FROM rrolist WHERE rroid=:id");
        q.bindValue(":id", rroID);
        if(!q.exec()) qDebug() << "Не удалось получить данные по РРО" << q.lastError().text();
        q.next();
        ui->comboBoxVlasnik->setCurrentIndex(q.value("brendid").toInt()-1);
        ui->lineEditZN->setText(q.value("zn").toString());
        ui->lineEditFN->setText(q.value("fn").toString());
        ui->comboBoxModel->setCurrentIndex(q.value("rrotype").toInt()-1);
        ui->comboBoxVersion->setCurrentIndex(q.value("verpo").toInt()-1);
        ui->lineEditTerminal->setText(q.value("terminalid").toString());
        ui->lineEditAdress->setText(q.value("adress").toString());
        ui->lineEditAdress->setCursorPosition(0);
    }
}



void RroDialog::on_toolButtonVlasnik_clicked()
{
    VlasnikDialog *vlasDlg = new VlasnikDialog(this);
    vlasDlg->exec();
    modelVlasnik->select();
}

void RroDialog::on_toolButtonModel_clicked()
{
    ModelRroDialog *modDlg = new ModelRroDialog();
    modDlg->exec();
    modelRro->select();
}

void RroDialog::on_toolButtonVersion_clicked()
{
    VersionPODialog *poDlg = new VersionPODialog(this);
    poDlg->exec();
    modelRro->select();
}

void RroDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch (ui->buttonBox->standardButton(button)) {
    case QDialogButtonBox::Save:
        if(validateData())
            databaseChange();
        break;
    case QDialogButtonBox::Close:
        this->reject();
        break;
    default:
        break;
    }
}

bool RroDialog::validateData()
{
    if(ui->comboBoxVlasnik->currentIndex()==-1){
        QMessageBox::information(this, "Ошибка","Не выбран владелец РРО!");
        return false;
    }
    if(ui->lineEditZN->text().length()==0) {
        QMessageBox::information(this, "Ошибка", "Не указан Заводской номер РРО.");
        return false;
    }
    if(ui->lineEditFN->text().length()==0) {
        QMessageBox::information(this, "Ошибка", "Не указан Фискальный номер РРО.");
        return false;
    }
    if(ui->comboBoxModel->currentIndex()==-1){
        QMessageBox::information(this, "Ошибка","Не выбрана модель РРО!");
        return false;
    }
    if(ui->comboBoxVersion->currentIndex()==-1){
        QMessageBox::information(this, "Ошибка","Не выбрана версия ПО!");
        return false;
    }

    return true;
}

void RroDialog::databaseChange()
{
    QSqlQuery q;
    QString strSQL;

    if(rroID==-1) {
        strSQL=QString("INSERT INTO `stamps`.`rrolist` (`brendid`, `terminalid`, `adress`, `zn`, `fn`, `rrotype`, `verpo`) "
                       "VALUES ('%1', '%2', '%3', '%4', '%5', '%6', '%7')")
                .arg(ui->comboBoxVlasnik->currentIndex()+1)
                .arg(ui->lineEditTerminal->text().trimmed())
                .arg(ui->lineEditAdress->text().trimmed())
                .arg(ui->lineEditZN->text().trimmed())
                .arg(ui->lineEditFN->text().toInt())
                .arg(ui->comboBoxModel->currentIndex()+1)
                .arg(ui->comboBoxVersion->currentIndex()+1);
    } else {
        strSQL=QString("UPDATE `stamps`.`rrolist` SET `brendid`='%1', `terminalid`='%2', `adress`='%3', `zn`='%4', `fn`='%5', `rrotype`='%6', `verpo`='%7' "
                       "WHERE `rroid`='%8'")
                .arg(ui->comboBoxVlasnik->currentIndex()+1)
                .arg(ui->lineEditTerminal->text().trimmed())
                .arg(ui->lineEditAdress->text().trimmed())
                .arg(ui->lineEditZN->text().trimmed())
                .arg(ui->lineEditFN->text().toInt())
                .arg(ui->comboBoxModel->currentIndex()+1)
                .arg(ui->comboBoxVersion->currentIndex()+1)
                .arg(rroID);
    }
    qDebug() << "Запрос" << strSQL;
    if(!q.exec(strSQL)) qDebug() << "Не удалось изменить данные по РРО." << q.lastError().text();

}
