#include "usedreportdialog.h"
#include "ui_usedreportdialog.h"

UsedReportDialog::UsedReportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UsedReportDialog)
{
    ui->setupUi(this);
    createUI();
}

UsedReportDialog::~UsedReportDialog()
{
    delete ui;
}

void UsedReportDialog::createUI()
{
    QDate curDate = QDate::currentDate();
    QDate begDate;
    ui->dateEditEnd->setDate(curDate);
    switch (curDate.month()) {
    case 1:
    case 2:
    case 3:
        begDate.setDate(curDate.year(),1,1);
        break;
    case 4:
    case 5:
    case 6:
        begDate.setDate(curDate.year(),4,1);
        break;
    case 7:
    case 8:
    case 9:
        begDate.setDate(curDate.year(),7,1);
        break;
    case 10:
    case 11:
    case 12:
        begDate.setDate(curDate.year(),10,1);
        break;
    default:
        break;
    }
    ui->dateEditBeg->setDate(begDate);
}
