#ifndef MODELRRODIALOG_H
#define MODELRRODIALOG_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class ModelRroDialog;
}

class ModelRroDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ModelRroDialog(QWidget *parent = 0);
    ~ModelRroDialog();

private slots:
    void on_pbAdd_clicked();

    void on_pbExit_clicked();

    void on_pbEdit_clicked();

    void on_pbDel_clicked();

private:
    Ui::ModelRroDialog *ui;
    QSqlTableModel *model;
    void createUI();

};

#endif // MODELRRODIALOG_H
