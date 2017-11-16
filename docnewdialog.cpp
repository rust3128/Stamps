#include "docnewdialog.h"
#include "ui_docnewdialog.h"
#include <QPushButton>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>

DocNewDialog::DocNewDialog(int ID, QString Type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DocNewDialog)
{
    ui->setupUi(this);
    docID=ID;
    docType=Type;
    createUI();
}

DocNewDialog::~DocNewDialog()
{
    delete ui;
}

void DocNewDialog::createUI()
{
    this->setWindowTitle("Новый документ " + docType);
    ui->labelTitle->setText("Новый документ\n"+docType);

    QRegExp markaRegex("[А-Я][А-Я]");
    QRegExp number("\\d{6}");

    QRegExpValidator *markaValidator = new QRegExpValidator(markaRegex,this);
    ui->lineEditSerial->setValidator(markaValidator);
    QRegExpValidator *numberValid = new QRegExpValidator(number,this);
    ui->lineEditBeginNum->setValidator(numberValid);
    ui->lineEditEndNum->setValidator(numberValid);

    pixOk = new QPixmap();
    pixError = new QPixmap();
    pixOk->load(":/Image/ok.png");
    pixError->load(":/Image/error.png");

    resetData();
}

void DocNewDialog::resetData()
{
    ui->dateDoc->setDateTime(QDateTime().currentDateTime());
    ui->labelInfoSer->clear();
    ui->labelInfoSer->setPixmap(*pixError);
    ui->labelInfoSer->setToolTip("Не указана серия.");
    ui->lineEditSerial->clear();
    ui->labelInfoBeg->setPixmap(*pixError);
    ui->labelInfoBeg->setToolTip("Не указан начальный номер.");
    ui->lineEditBeginNum->clear();
    ui->labelInfoEnd->setPixmap(*pixError);
    ui->labelInfoEnd->setToolTip("Не указан конечнй номер.");
    ui->lineEditEndNum->clear();
    serOK=begOK=endOK=diapOK=false;
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(false);
    numberBegin=numberEnd=0;
}

void DocNewDialog::on_lineEditSerial_textChanged(const QString &arg1)
{
    if(arg1.length()==2){
        ui->labelInfoSer->setPixmap(*pixOk);
        ui->labelInfoSer->setToolTip("");
        serOK=true;
        serial=ui->lineEditSerial->text();
    } else {
        ui->labelInfoSer->setPixmap(*pixError);
        ui->labelInfoSer->setToolTip("Не верная серия.");
        serOK=false;
    }
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK);

}

void DocNewDialog::on_lineEditBeginNum_textChanged(const QString &arg1)
{
    if(arg1.length()!=6) {
        ui->labelInfoBeg->setPixmap(*pixError);
        ui->labelInfoBeg->setToolTip("Не верный начальный номер.");
        begOK=false;
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK);
        return;
    }
    numberBegin=ui->lineEditBeginNum->text().toInt();
    if(numberEnd==0) {
        ui->labelInfoBeg->setPixmap(*pixOk);
        ui->labelInfoBeg->setToolTip("");
        begOK=true;
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK);
        return;
    }
    if(numberBegin>numberEnd){
        ui->labelInfoBeg->setPixmap(*pixError);
        ui->labelInfoBeg->setToolTip("Не верный диапазон номеров.");
        diapOK=false;
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK);
        return;
    }
    ui->labelInfoBeg->setPixmap(*pixOk);
    ui->labelInfoBeg->setToolTip("");
    begOK=true;
    diapOK=true;
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK);

}

void DocNewDialog::on_lineEditEndNum_textChanged(const QString &arg1)
{

    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK);
    if(arg1.length()!=6) {
        ui->labelInfoEnd->setPixmap(*pixError);
        ui->labelInfoEnd->setToolTip("Не верный конечный номер.");
        endOK=false;
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK);
        return;
    }
    numberEnd=ui->lineEditEndNum->text().toInt();
    if(numberBegin==0) {
        ui->labelInfoEnd->setPixmap(*pixOk);
        ui->labelInfoEnd->setToolTip("");
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK);
        endOK=true;
        return;
    }
    if(numberEnd<numberBegin){
        ui->labelInfoEnd->setPixmap(*pixError);
        ui->labelInfoEnd->setToolTip("Не верный диапазон номеров.");
        diapOK=false;
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK);
        return;
    }
    ui->labelInfoEnd->setPixmap(*pixOk);
    ui->labelInfoEnd->setToolTip("");
    endOK=true;
    diapOK=true;
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK);

}

void DocNewDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    switch (ui->buttonBox->standardButton(button)) {
    case QDialogButtonBox::Save:
        documentCreate();
        break;
    case QDialogButtonBox::Close:
        this->reject();
        break;
    case QDialogButtonBox::Reset:
        resetData();
        break;
    default:
        break;
    }
}

void DocNewDialog::documentCreate()
{
    qDebug() << genDocNumber(docID);
}

QString DocNewDialog::genDocNumber(int id)
{
    QString docNum;
    QSqlQuery q;
    q.prepare("SELECT numdoc FROM doctype WHERE doctypeid=:typeid");
    q.bindValue(":typeid",id);
    q.exec();
    docNum=q.value(0).toString();

    return docNum;


}
