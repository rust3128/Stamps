#ifndef REGIONSDIALOG_H
#define REGIONSDIALOG_H

#include <QDialog>

namespace Ui {
class RegionsDialog;
}

class RegionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RegionsDialog(QWidget *parent = 0);
    ~RegionsDialog();

private:
    Ui::RegionsDialog *ui;
};

#endif // REGIONSDIALOG_H
