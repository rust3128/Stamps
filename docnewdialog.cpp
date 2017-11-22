#include "docnewdialog.h"
#include "ui_docnewdialog.h"
#include <QPushButton>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

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
    docNumber=genDocNumber(docID);
    ui->labelNumDoc->setText(docNumber);
    createComboRegion();

    switch (docID) {
    case 1:
        ui->label2Region->hide();
        ui->comboBox2Region->hide();
        idStorage=1;
        idStatus=1;
        break;
    case 2:
        idStatus=2;
        break;
    default:
        break;
    }

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
    serOK=begOK=endOK=diapOK=reg2OK=false;
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
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK && reg2OK);

}

void DocNewDialog::on_lineEditBeginNum_textChanged(const QString &arg1)
{
    if(arg1.length()!=6) {
        ui->labelInfoBeg->setPixmap(*pixError);
        ui->labelInfoBeg->setToolTip("Не верный начальный номер.");
        begOK=false;
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK && reg2OK);
        return;
    }
    numberBegin=ui->lineEditBeginNum->text().toInt();
    if(numberEnd==0) {
        ui->labelInfoBeg->setPixmap(*pixOk);
        ui->labelInfoBeg->setToolTip("");
        begOK=true;
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK && reg2OK);
        return;
    }
    if(numberBegin>numberEnd){
        ui->labelInfoBeg->setPixmap(*pixError);
        ui->labelInfoBeg->setToolTip("Не верный диапазон номеров.");
        diapOK=false;
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK && reg2OK);
        return;
    }
    ui->labelInfoBeg->setPixmap(*pixOk);
    ui->labelInfoBeg->setToolTip("");
    begOK=true;
    diapOK=true;
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK && reg2OK);

}

void DocNewDialog::on_lineEditEndNum_textChanged(const QString &arg1)
{

    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK && reg2OK);
    if(arg1.length()!=6) {
        ui->labelInfoEnd->setPixmap(*pixError);
        ui->labelInfoEnd->setToolTip("Не верный конечный номер.");
        endOK=false;
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK && reg2OK);
        return;
    }
    numberEnd=ui->lineEditEndNum->text().toInt();
    if(numberBegin==0) {
        ui->labelInfoEnd->setPixmap(*pixOk);
        ui->labelInfoEnd->setToolTip("");
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK && reg2OK);
        endOK=true;
        return;
    }
    if(numberEnd<numberBegin){
        ui->labelInfoEnd->setPixmap(*pixError);
        ui->labelInfoEnd->setToolTip("Не верный диапазон номеров.");
        diapOK=false;
        ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK && reg2OK);
        return;
    }
    ui->labelInfoEnd->setPixmap(*pixOk);
    ui->labelInfoEnd->setToolTip("");
    endOK=true;
    diapOK=true;
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK && reg2OK);

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
    QSqlQuery q;
    QString strSQL;

    if(docID==2) {
        if(!validStamps()) return;
    }

    strSQL = QString("CALL `stamps`.`new_document`('%1', '%2', %3, '%4', %5, %6, '%7', %8, %9)")
            .arg(ui->dateDoc->dateTime().toString("yyyy-MM-dd hh:mm:ss"))
            .arg(docNumber)
            .arg(docID)
            .arg(serial)
            .arg(numberBegin)
            .arg(numberEnd)
            .arg(ui->plainTextEditComments->toPlainText())
            .arg(idStatus)
            .arg(idStorage);

    if(!q.exec(strSQL)) qDebug() << "Не удалось создать документ." << q.lastError().text();
    this->accept();


}

bool DocNewDialog::validStamps()
{
    QSqlQuery q;
    QString strSQL=QString("SELECT COUNT(*) FROM stamps WHERE stampstatusid=1 "
                           "AND stampserial='%1' AND stampnumber BETWEEN %2 AND %3")
            .arg(serial)
            .arg(numberBegin)
            .arg(numberEnd);
    int col = numberEnd - numberBegin + 1;

    q.exec(strSQL);
    q.next();
    if(col != q.value(0).toInt()) {
        QMessageBox::information(this,
                               QString::fromUtf8("Ошибка диапазона марок"),
                               QString::fromUtf8("Марки указанной серии и диапазона отстутсвуют на складе.\n"
                                                 "Проверте диапазон и повторите попытку."));
        return false;
    }

    return true;
}

QString DocNewDialog::genDocNumber(int id)
{
    QString docNum;
    QSqlQuery q;
    q.prepare("SELECT numdoc, docprefix FROM doctype WHERE doctypeid=:typeid");
    q.bindValue(":typeid",id);
    q.exec();
    q.next();
    int numdoc = q.value(0).toInt();
    numdoc++;
    docNum=q.value(1).toString()+QString::number(numdoc).rightJustified(6, '0');;

//    result = QString::number(myNumber).rightJustified(6, '0');

    return docNum;


}

void DocNewDialog::createComboRegion()
{
    modelRegion = new QSqlTableModel();
    modelRegion->setTable("storage");
    modelRegion->select();

    ui->comboBox2Region->setModel(modelRegion);
    ui->comboBox2Region->setModelColumn(1);
    ui->comboBox2Region->setCurrentIndex(-1);
}

void DocNewDialog::on_comboBox2Region_activated(int idx)
{
    reg2OK=true;
    QModelIndex indexModel=modelRegion->index(idx,0,QModelIndex());
    idStorage=modelRegion->data(indexModel, Qt::DisplayRole).toInt();
    ui->buttonBox->button(QDialogButtonBox::Save)->setEnabled(serOK && begOK && endOK && diapOK && reg2OK);
}
