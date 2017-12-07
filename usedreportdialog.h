#ifndef USEDREPORTDIALOG_H
#define USEDREPORTDIALOG_H

#include <QDialog>

namespace Ui {
class UsedReportDialog;
}

class UsedReportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UsedReportDialog(QWidget *parent = 0);
    ~UsedReportDialog();

private:
    Ui::UsedReportDialog *ui;

private:
    void createUI();
};

#endif // USEDREPORTDIALOG_H
