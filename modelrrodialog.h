#ifndef MODELRRODIALOG_H
#define MODELRRODIALOG_H

#include <QDialog>

namespace Ui {
class ModelRroDialog;
}

class ModelRroDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModelRroDialog(QWidget *parent = 0);
    ~ModelRroDialog();

private:
    Ui::ModelRroDialog *ui;
};

#endif // MODELRRODIALOG_H
